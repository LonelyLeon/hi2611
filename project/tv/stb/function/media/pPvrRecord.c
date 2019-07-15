/** @file pHaierPvrRecord.c
* @brief pvr record 模块
* pvr 录像功能
* @author 覃宜
* @date 20180413 覃宜: 建立文件
*/

#include <stdio.h>
#include <string.h>
#include "dTypes.h"
#include "dSem.h"
#include "dMsg.h"
#include "dApp.h"
#include "dSys.h"
#include "dMem.h"
#include "dDebug.h"
#include "dResource.h"
#include "dPvrPorting.h"
#include "dRTCTimer.h"
#include "dCBMan.h"
#include "dFMan.h"
#include "dSI.h"
#include "pPvrRecord.h"

#define HAIER_PVR_DEV_CNT (1)               /* 录制设备总数*/

#define HAIER_PVR_REC_BUF_ALIGN (8*K)       /* demux通道寄存器要求8K对齐*/
#define HAIER_PVR_REC_INTERRUPT_TIMEOUT (5) /* 等待中断信号量超时时间 ms*/
#define HAIER_PVR_REC_BUF_SIZE (2*M)   /* 录像缓冲区大小*/
#define HAIER_PVR_INT_BUF_SIZE (64*K) /* 数据中断阀值*/

typedef struct
{
    D_HFMan hfman;
    D_DBSrvID dbsrvid;      /**< 节目dbsrid*/
    D_Char chan_name[32];   /**< 节目名*/
    D_U8 rec_tv_num; /**< tv几，即demux几*/
    D_U8 video_type; /**< 视频编码类型*/
    D_U8 audio_type; /**< 音频编码类型*/
    D_U32 duration_time;  /**< 持续时间,单位秒*/
    PVR_CH_OUT_MODE record_mode; /**< 录制模式，pid还是ts*/
    D_U16 rec_pid[24];  /**< 录制pid列表*/
    D_U8 rec_cw[8];     /**< 录制的节目的cw*/
    PVR_REC_NAV_TYPE    rec_nav_type[4];    //0x00-- mpeg nav, 0x01-- h264 nav, 0x02-- avs nav, 0x03-- user define
    //录像缓冲区寄存器和导航寄存器配置
    D_Bool recbuf_use_sys;  /**< 录像缓冲区是否使用程序分区 */
    D_U32 recbuf_size;      /**< 录像缓冲区大小， demux通道寄存器要求8K对齐*/
    D_U32 recbuf_int_value; /**< 引发中断的最小数据大小*/
    D_U32 recbuf_addr ;     /**< 内存分配时得到的地址*/
    D_U32 recbuf_physaddr;  /**< 录像缓冲区物理地址, 驱动使用 */
    D_U8 *recbuf_align_addr;    /**< 8K对齐后的地址*/

    D_PvrHandle hpvr;       /**< pvr设备句柄*/
    D_Handle hcbman_interrupt; /**< 中断里回调注册句柄*/
    D_U8    interrupt_state;/**< 中断类型记录*/
    D_HSem hsem_record; /**< 中断信号量*/
    D_Bool record_ing;  /**< 正在录制标示*/
    D_U32   rec_total_size;
    D_U32   print_cnt;
} D_HaierPvrRecordDat;

/** @brief 录像app句柄*/
static D_HApp happ_pvr_record = D_INVALID_HANDLE;
static D_HaierPvrRecordDat *pPvrRecordDat = NULL;

/** @brief 录制数据处理回调，返回处理的结果，负数是错误代码，0或正数是处理的字节数*/
static D_HaierPvrDataDealCallback DataDealFunction = NULL;



/** @brief PVR录像内存释放
*@param[in]
*@return D_OK成功
*/
static D_Result
haier_pvr_rec_free(void) D_FUNCPOSTFIT
{
    if(pPvrRecordDat)
    {
        if(pPvrRecordDat->recbuf_addr)
        {
            d_sys_unmap_address((D_Ptr)pPvrRecordDat->recbuf_physaddr);
#ifndef D_SYSTEM_LINUX
            if(pPvrRecordDat->recbuf_use_sys)
            {
                d_sys_unmap_address(pPvrRecordDat->recbuf_align_addr);
                d_mem_free((D_Ptr)pPvrRecordDat->recbuf_addr);
            }
            else
#endif
            {
                d_sys_free_dev_mem((D_Ptr)pPvrRecordDat->recbuf_addr);
            }
        }

        if(pPvrRecordDat->hsem_record != D_INVALID_HANDLE)
        {
            d_sem_destroy(pPvrRecordDat->hsem_record);
            pPvrRecordDat->hsem_record = D_INVALID_HANDLE;

        }

        if(pPvrRecordDat->hcbman_interrupt != D_INVALID_HANDLE)
        {
            d_cbman_unsubscribe(pPvrRecordDat->hcbman_interrupt);
            pPvrRecordDat->hcbman_interrupt = D_INVALID_HANDLE;

        }

        d_mem_free(pPvrRecordDat);
        pPvrRecordDat = NULL;
    }
    return D_OK;
}

/** @brief PVR录像内存申请
*@param[in] config用户配置
*@return D_OK成功
*/
static D_Result
haier_pvr_rec_alloc(void) D_FUNCPOSTFIT
{
    if(pPvrRecordDat == NULL)
    {
        pPvrRecordDat = (D_HaierPvrRecordDat*)d_mem_alloc(0, sizeof(D_HaierPvrRecordDat));
        if(pPvrRecordDat == NULL)
        {
            return D_ERR;
        }

        memset(pPvrRecordDat, 0x00, sizeof(D_HaierPvrRecordDat));
        pPvrRecordDat->hpvr = D_INVALID_HANDLE;
        pPvrRecordDat->hsem_record = D_INVALID_HANDLE;
        pPvrRecordDat->hcbman_interrupt = D_INVALID_HANDLE;
        pPvrRecordDat->recbuf_size = (HAIER_PVR_REC_BUF_SIZE + HAIER_PVR_REC_BUF_ALIGN - 1) & (~(HAIER_PVR_REC_BUF_ALIGN - 1));
        pPvrRecordDat->recbuf_int_value = HAIER_PVR_INT_BUF_SIZE;
        pPvrRecordDat->recbuf_use_sys = D_TRUE;

        pPvrRecordDat->hsem_record = d_sem_create(NULL);
        if(pPvrRecordDat->hsem_record == D_INVALID_HANDLE)
        {
            return D_ERR;
        }

#ifndef D_SYSTEM_LINUX
        if(pPvrRecordDat->recbuf_use_sys)
        {
            pPvrRecordDat->recbuf_addr = (D_U32)d_mem_alloc(0, pPvrRecordDat->recbuf_size + HAIER_PVR_REC_BUF_ALIGN);
            if(!pPvrRecordDat->recbuf_addr)
                return D_ERR_NO_SPACE;

            pPvrRecordDat->recbuf_align_addr = (D_U8*)d_sys_map_address(D_SysAddr_UnCached, (D_Ptr)((pPvrRecordDat->recbuf_addr + (HAIER_PVR_REC_BUF_ALIGN - 1)) & ~(HAIER_PVR_REC_BUF_ALIGN - 1)), pPvrRecordDat->recbuf_size);
        }
        else
#endif
        {
            pPvrRecordDat->recbuf_addr = (D_U32)d_sys_alloc_dev_mem(pPvrRecordDat->recbuf_size, HAIER_PVR_REC_BUF_ALIGN);
            if(!pPvrRecordDat->recbuf_addr)
                return D_ERR_NO_SPACE;

            pPvrRecordDat->recbuf_align_addr = (D_U8*)pPvrRecordDat->recbuf_addr;
        }

        pPvrRecordDat->recbuf_physaddr = (D_U32)d_sys_map_address(D_SysAddr_Phys, (D_Ptr)pPvrRecordDat->recbuf_align_addr, pPvrRecordDat->recbuf_size);
    }
    return D_OK;
}

/** @brief pvr录制中断函数里的回调函数，主要设置信号量，通知录像的app
* @param[in]
* @return 无
*/
static void
haier_PvrRecIntCallback(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_PvrIntReason reason = (D_PvrIntReason)obj_data;

    if(reason & \
    (D_PvrInt_RecDataReady | D_PvrInt_RecNavReady | D_PvrInt_RecDataOverflow | D_PvrInt_RecNavOverflow))
    {
        D_HaierPvrRecordDat *rec = (D_HaierPvrRecordDat*)cb_data;

        d_sem_post(rec->hsem_record);
    }
}

/** @brief 开始pvr录制
* @param[in] config 录像信息结构体
* @return 成功返回D_OK
*/
static D_Result
haier_pvr_record_start(D_HaierPvrRecordDat *rec, D_U32 dev_id) D_FUNCPOSTFIT
{
    D_Result ret = D_OK;
    D_U32 i;
    D_DBSrvInfo srvinfo;
    D_DBTSInfo tsinfo;
    D_DBSateInfo satinfo;
    D_DBAnteInfo antinfo;
    PVR_REC_NAV_TYPE type;
    D_PvrRecSetRegValue rec_reg_value;

    /*业务有效性检查，取得业务信息*/
    if(D_OK != d_dbase_get_srv_info(rec->dbsrvid, &srvinfo))
    {
        return D_ERR;
    }

    if (d_dbase_get_ts_info (srvinfo.db_ts_id, &tsinfo) < 0)
    {
        return D_ERR;
    }

    if(tsinfo.db_sat_id != (D_U8) - 1)
    {
        if(d_dbase_get_sat_info(tsinfo.db_sat_id, &satinfo) < 0)
            return D_ERR;

        if(satinfo.antenna_slot != (D_U8) - 1)
        {
            if(d_dbase_get_ante_info(satinfo.antenna_slot, &antinfo) < 0)
                return D_ERR;
        }
    }
    rec->hfman = d_fman_get_handle_by_type((D_FEndType)tsinfo.tuner_type, 0);
    d_fman_set_param (rec->hfman, &tsinfo.param, D_TRUE, (D_FEndType)tsinfo.tuner_type, &satinfo, &antinfo);
    d_task_wait(5);

    rec->rec_tv_num = TV1;
    rec->video_type = srvinfo.vid_codec;
    rec->audio_type = srvinfo.aud1_codec;
    rec->record_mode = (PVR_CH_OUT_MODE)0;
    rec->duration_time = (D_U32)(-1);
    memset(rec->rec_cw, 0x00, sizeof(rec->rec_cw));

    for(i = 0; i < 24; i++)
    {
        rec->rec_pid[i] = 0x000fL;//PID_RESERVED;
    }

    sprintf(rec->chan_name, "TestPvr");
    rec->rec_pid[0] = srvinfo.vid_pid;
    rec->rec_pid[4] = srvinfo.aud1_pid;
    // 如果pcr 独立，也录制pcr
    if(srvinfo.pcr_pid != 0x1FFF && srvinfo.pcr_pid != srvinfo.vid_pid && srvinfo.pcr_pid != srvinfo.aud1_pid)
    {
        rec->rec_pid[5] = srvinfo.pcr_pid;
    }
    rec->rec_pid[6] = PID_PAT;            // 录制PAT
    rec->rec_pid[7] = srvinfo.pmt_pid;   // 录制对应的PMT

//    D_DUMP("[HaierPvrRec]:vpid %04x, apid %04x, pcrpid %04x, pmtpid %04x\n", srvinfo.vid_pid, srvinfo.aud1_pid, srvinfo.pcr_pid, srvinfo.pmt_pid);
    rec_reg_value.recbuf_addr = rec->recbuf_physaddr;
    rec_reg_value.recbuf_size = rec->recbuf_size;
    rec_reg_value.recbuf_int_value = rec->recbuf_int_value;
    rec_reg_value.rec_nav_int_value = 4;

    switch(rec->video_type)
    {
        case D_VID_CODEC_MPEG:
            type = REC_MPEG_NAV_TYPE;
            break;
        case D_VID_CODEC_AVS:
            type = REC_AVS_NAV_TYPE;
            break;
        case D_VID_CODEC_H264:
            type = REC_H264_NAV_TYPE;
            break;
        default:
            type = REC_USER_DEFINE_NAV_TYPE;
            break;
    }

    for(i = 0; i < 4; i++)
    {
        rec->rec_nav_type[i] = type;
    }

    /* 清掉上次录制时产生的中断信号量 的遗留*/
    while(rec->hsem_record != D_INVALID_HANDLE)
    {
        if(D_OK != d_sem_wait_timeout(rec->hsem_record, 2))
        {
            break;
        }
    }

    rec->hpvr = d_pvr_porting_rec_create(rec->rec_tv_num, rec_reg_value);
    if(rec->hcbman_interrupt == D_INVALID_HANDLE)
    {
        rec->hcbman_interrupt = d_cbman_subscribe(PL_INTERRUPT_PVR, D_INVALID_HANDLE, haier_PvrRecIntCallback, (D_Ptr)rec);
    }

    d_pvr_porting_rec_start(rec->hpvr, rec->rec_pid, rec->rec_cw, (D_U8 *)rec->rec_nav_type, 0, rec->record_mode);
    d_pvr_porting_rec_nav_enable(rec->hpvr, 0); /* 不要导航*/

    rec->record_ing = D_TRUE;
    rec->print_cnt = 3;
    D_DUMP("[HaierPvrRec]:Start Record.\n");
    return ret;
}

/** @brief 停止pvr录制
* @return 成功返回D_OK
*/
static D_Result
haier_pvr_record_stop(D_HaierPvrRecordDat *rec, D_U32 dev_id) D_FUNCPOSTFIT
{
    d_pvr_porting_rec_stop(rec->hpvr);
    d_pvr_porting_rec_destroy(rec->hpvr);
    rec->hpvr = D_INVALID_HANDLE;
    rec->record_ing = D_FALSE;
    D_DUMP("[HaierPvrRec]:Stop Record.\n");
    return D_OK;
}


/** @brief pvr录制app的回调函数
* @param[in] msg 消息
* @return 成功返回D_OK
*/
static D_Result
haier_pvr_rec_callback(D_Msg *msg)D_FUNCPOSTFIT
{
    D_HaierPvrRecordDat *rec;

    rec = (D_HaierPvrRecordDat *)d_app_get_data (d_app_self ());

    switch (msg->type)
    {
        case D_MSG_APP_CREATE:
        {
            /* the this param of this task */
            rec = msg->app.arg;
            d_app_set_data (d_app_self (), (D_Ptr)rec);
            d_app_set_timeout(d_app_self(), 1);
        }
        break;
        case D_MSG_PVR_REC_START:
            if(rec->record_ing) /* 如果正在录制，则停止*/
            {
                haier_pvr_record_stop(rec, 0);
            }

            rec->dbsrvid = (D_DBSrvID)msg->pvr.jump_value;
            haier_pvr_record_start(rec, 0);
            break;
        case D_MSG_PVR_REC_STOP:
            if(rec->record_ing)
            {
                haier_pvr_record_stop(rec, 0);
            }
            break;
        case D_MSG_APP_TIMEOUT:
        {
            D_Result ret, REC_Read_Buf_Flag, REC_Nav_Buf_Flag;
            D_PvrIntReason Rec_INT_Flag = D_PvrInt_Null; /* 中断标志*/
            D_U32 REC_Buf_Addr = 0, REC_Buf_Data_Length = 0;
            static D_U32 last_size = 0;
            static D_U32 last_time = 0;
            
            /* 超时等待录像中断信号量*/
            ret = d_sem_wait_timeout(rec->hsem_record, HAIER_PVR_REC_INTERRUPT_TIMEOUT);

            if(ret == D_OK)
            {
                Rec_INT_Flag = d_pvr_porting_get_rec_int_status(rec->hpvr);

                if(Rec_INT_Flag & D_PvrInt_RecNavOverflow)
                {
                    //处理录像中断导航溢出
                    D_ERROR("[HaierPvrRec]:NAV_OVERFLOW.\n");
                    d_pvr_porting_rec_nav_enable(rec->hpvr, 0); /* 不要导航*/
                }

                if(Rec_INT_Flag & D_PvrInt_RecDataOverflow)
                {
                    //处理录像中断数据溢出，复位
                    D_ERROR("[HaierPvrRec]:REC_OVERFLOW.\n");
                    d_pvr_porting_rec_nav_enable(rec->hpvr, 0); /* 不要导航*/
                    d_pvr_porting_rec_restart(rec->hpvr);
                }

                if(Rec_INT_Flag & D_PvrInt_RecNavReady)
                {
                    d_pvr_porting_rec_nav_enable(rec->hpvr, 0); /* 不要导航*/
                    REC_Nav_Buf_Flag = d_pvr_porting_get_recbuf_data(rec->hpvr, &REC_Buf_Addr, &REC_Buf_Data_Length, NAV_BUF);
                    if((REC_Nav_Buf_Flag == D_ERR) || (REC_Buf_Data_Length > 16))
                    {
                        //参数的保护   导航个数最大为16
                        D_DUMP("[HaierPvrRec]:REC_Nav_Buf_Flag ERROR.\n");
                    }
                    else
                    {
                        REC_Buf_Addr = (D_U32)d_sys_map_address(D_SysAddr_UnCached, (D_Ptr)REC_Buf_Addr, REC_Buf_Data_Length << 2);
                        d_pvr_porting_set_navrp(rec->hpvr, REC_Buf_Data_Length);  // 之前是  4        因为固定是读取4个  现在不是
                    }
                }

                if(Rec_INT_Flag & D_PvrInt_RecDataReady)
                {
                    /* 获取可读地址和长度*/
                    REC_Read_Buf_Flag = d_pvr_porting_get_recbuf_data(rec->hpvr, &REC_Buf_Addr, &REC_Buf_Data_Length, REC_BUF);
                    if(REC_Read_Buf_Flag == D_ERR)
                    {
                        REC_Buf_Data_Length = 0;
                        D_ERROR("[HaierPvrRec]:REC_Read_Buf_Flag ERROR.\n");
                    }
                    else
                    {
                        REC_Buf_Addr = (D_U32)rec->recbuf_align_addr + (REC_Buf_Addr - rec->recbuf_physaddr);
                    }

                    if(rec->print_cnt)
                    {
                        D_DUMP("[HaierPvrRec]:RecDataReady, addr 0x%08x, len 0x%x.\n", REC_Buf_Addr, REC_Buf_Data_Length);
                        rec->print_cnt--;
                    }

                    if(REC_Buf_Data_Length)
                    {
                        D_Size ret_deal;
                        // 读取数据，并更新读指针位置
                        if(DataDealFunction)
                        {
                            ret_deal = DataDealFunction(0, (D_U8*)REC_Buf_Addr, (D_Size)REC_Buf_Data_Length);
                        }
                        else
                        {
                            ret_deal = (D_Size)REC_Buf_Data_Length;
                        }

                        if(ret_deal > 0)
                        {
                            REC_Buf_Data_Length = (D_U32)ret_deal;
                            d_pvr_porting_set_recrp(rec->hpvr, REC_Buf_Data_Length);
                            
                            last_size += REC_Buf_Data_Length;
                            if((d_rtc_timer_get_counter() - last_time) >= d_rtc_timer_get_freq())
                            {
                                D_DUMP("\nW: %u Kbps", (last_size << 3) / 1000);

                                last_size = 0;
                                last_time = d_rtc_timer_get_counter();
                            }
                        }
                    }
                }
                d_pvr_porting_reset_rec_int_status(rec->hpvr, (D_PvrIntMask)(/*D_PvrInt_RecDataReady | */D_PvrInt_RecDataOverflow/* | D_PvrInt_RecNavReady | D_PvrInt_RecNavOverflow*/));
            }
            else if(rec->record_ing)
            {
                    /* 获取可读地址和长度*/
                    REC_Read_Buf_Flag = d_pvr_porting_get_recbuf_data(rec->hpvr, &REC_Buf_Addr, &REC_Buf_Data_Length, REC_BUF);
                    if(REC_Read_Buf_Flag == D_ERR)
                    {
                        REC_Buf_Data_Length = 0;
                        D_ERROR("[HaierPvrRec]:REC_Read_Buf_Flag ERROR.\n");
                    }
                    else
                    {
                        REC_Buf_Addr = (D_U32)rec->recbuf_align_addr + (REC_Buf_Addr - rec->recbuf_physaddr);
                    }

                    if(REC_Buf_Data_Length >= (16*1024) || ((D_U32)rec->recbuf_align_addr + rec->recbuf_size) <= (REC_Buf_Addr + REC_Buf_Data_Length))
                    {
                        D_Size ret_deal;

                        if(rec->print_cnt)
                        {
                            D_DUMP("[HaierPvrRec]:RecDataReady, addr 0x%08x, len 0x%x.\n", REC_Buf_Addr, REC_Buf_Data_Length);
                            rec->print_cnt--;
                        }
                        
                        // 读取数据，并更新读指针位置
                        if(DataDealFunction)
                        {
                            ret_deal = DataDealFunction(0, (D_U8*)REC_Buf_Addr, (D_Size)REC_Buf_Data_Length);
                        }
                        else
                        {
                            ret_deal = (D_Size)REC_Buf_Data_Length;
                        }

                        if(ret_deal > 0)
                        {
                            REC_Buf_Data_Length = (D_U32)ret_deal;
                            d_pvr_porting_set_recrp(rec->hpvr, REC_Buf_Data_Length);
                            
                            last_size += REC_Buf_Data_Length;
                            if((d_rtc_timer_get_counter() - last_time) >= d_rtc_timer_get_freq())
                            {
                                D_DUMP("\nW: %u Kbps", (last_size << 3) / 1000);

                                last_size = 0;
                                last_time = d_rtc_timer_get_counter();
                            }
                        }
                        else
                        {
                            D_DUMP("[HaierPvrRec]:DataDealFunction len %d, ret %d\n", REC_Buf_Data_Length, ret_deal);
                        }
                    }
            }
        }
        break;
        case D_MSG_APP_DESTROY:
            if(rec->record_ing)
            {
                haier_pvr_record_stop(rec, 0);
            }
            d_pvr_porting_rec_close();
            break;
        default:
            break;
    }
    return D_OK;
}

/** @brief 应用交互任务创建
* @return 成功返回D_OK
*/
static D_Result
haier_pvr_record_create(void) D_FUNCPOSTFIT
{
    D_Result ret = D_OK;

    if(happ_pvr_record == D_INVALID_HANDLE)
    {
        if(D_OK == haier_pvr_rec_alloc())
        {
            d_pvr_porting_open();
            d_pvr_porting_rec_open();
            happ_pvr_record = d_app_create("HaierPvrRec", D_PVR_REC_TASK_PRIO, D_PVR_REC_TASK_STACK_SIZE, D_PVR_REC_QUEUE_SIZE, haier_pvr_rec_callback, (D_Ptr)pPvrRecordDat);
            if(happ_pvr_record != D_INVALID_HANDLE)
            {
                /*同步，等待设备创建完成*/
                d_app_sync(happ_pvr_record);
                D_DUMP("[HaierPvrRec]:record app create ok!!\n");
                ret = D_OK;
            }
        }

        if(happ_pvr_record == D_INVALID_HANDLE)
        {
            D_DUMP("[HaierPvrRec]:record app create error!!\n");
            d_pvr_porting_rec_close();
            haier_pvr_rec_free();
            ret = D_ERR;
        }
    }
    return ret;
}

/** @brief 应用交互任务注销
* @return 成功返回D_OK
*/
static D_Result
haier_pvr_record_destroy(void) D_FUNCPOSTFIT
{
    if(happ_pvr_record != D_INVALID_HANDLE)
    {
        d_app_destroy(happ_pvr_record);
        d_pvr_porting_rec_close();
        D_DUMP("[HaierPvrRec]:record app destroy !!\n");
    }
    haier_pvr_rec_free();
    happ_pvr_record = D_INVALID_HANDLE;
    return D_OK;
}

/** @brief 开始pvr录制
* @param[in] dev_id 设备号，可用于标识哪一路解复用
* @param[in] dbsrvid 录制的节目的dbsrvid
* @return 成功返回D_OK
*/
D_Result p_haier_pvr_record_start(D_U32 dev_id, D_ID dbsrvid) D_FUNCPOSTFIT
{
    D_DBSrvInfo srvinfo;

    /*业务有效性检查*/
    if(D_OK != d_dbase_get_srv_info(dbsrvid, &srvinfo))
    {
        return D_ERR;
    }

    /*检查创建交互app*/
    haier_pvr_record_create();
    /*发送开始录制消息*/
    if(happ_pvr_record != D_INVALID_HANDLE)
    {
        D_PvrMsg msg;
        dev_id = (dev_id >= HAIER_PVR_DEV_CNT) ? (HAIER_PVR_DEV_CNT - 1) : dev_id;
        msg.type = D_MSG_PVR_REC_START;
        msg.handle = happ_pvr_record;
        msg.param = dev_id;
        msg.jump_value = (D_U32)dbsrvid;
        return d_app_send (msg.handle, (D_Msg*)&msg, sizeof(msg));
    }

    return D_ERR;
}

/** @brief pvrrec stop函数
* @param[in] dev_id 设备号，可用于标识哪一路解复用
* @return  成功返回D_OK,失败返回D_ERR
*/
D_Result p_haier_pvr_record_stop(D_U32 dev_id)D_FUNCPOSTFIT
{
    if (happ_pvr_record != D_INVALID_HANDLE)
    {
        D_PvrMsg msg;
        dev_id = (dev_id >= HAIER_PVR_DEV_CNT) ? (HAIER_PVR_DEV_CNT - 1) : dev_id;
        msg.type = D_MSG_PVR_REC_STOP;
        msg.handle = happ_pvr_record;
        msg.param = dev_id;
        return d_app_send (msg.handle, (D_Msg*)&msg, sizeof(msg));
    }
    return D_OK;
}

/** @brief 初始化
* @return 成功返回D_OK
*/
D_Result p_haier_pvr_record_open(void) D_FUNCPOSTFIT
{
    return D_OK;
}

/** @brief 反初始化
* @return 成功返回D_OK
*/
D_Result p_haier_pvr_record_close(void) D_FUNCPOSTFIT
{
    haier_pvr_record_destroy();
    return D_OK;
}

/** @brief 注册pvr录制后的数据处理回调
* @return 成功返回D_OK
*/
D_Result p_haier_pvr_record_register(D_U32 dev_id, D_HaierPvrDataDealCallback callback) D_FUNCPOSTFIT
{
    DataDealFunction = callback;
    return D_OK;
}

