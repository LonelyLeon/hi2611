/** @file pTs2NetRecord.c
* @brief ts2net record 模块
* 通过解利用pvr通道录制频道音视频ts流数据功能
* @author 覃宜
* @date 20180608 覃宜: 建立文件
*/

#include <stdio.h>
#include <string.h>
#include "dTypes.h"
#include "dSem.h"
#include "dMsg.h"
#include "dApp.h"
#include "dSys.h"
#include "dMem.h"
#include "dAV.h"
#include "dCrc.h"
#include "dScan.h"
#include "dDemux.h"
#include "dDebug.h"
#include "dResource.h"
#include "dPvrPorting.h"
#include "dRTCTimer.h"
#include "dCBMan.h"
#include "dFMan.h"
#include "dSI.h"
#include "element.h"
#include "pConfig.h"
#include "pPlayer.h"
#include "pTs2NetRecord.h"

/* 使能打印*/
#define TS2NET_DEBUG_EN (0)


#define TS2NET_DEV_CNT (2)               /* 录制设备总数*/

#define TS2NET_DEV_TYPE_PVR (0)
#define TS2NET_DEV_TYPE_PES (1)

#define TS2NET_REC_BUF_ALIGN (8*K)       /* demux通道寄存器要求8K对齐*/
#define TS2NET_REC_CHECK_TIME (10)      /* 检查数据时间间隔 ms*/
#define TS2NET_REC_BUF_SIZE (188*8*K)   /* 录像缓冲区大小*/
#define TS2NET_REC_INT_BUF_SIZE (64*K) /* 数据中断阀值*/

#define TS2NET_REC_SEND_MIN_SIZE (16*K)  /* 发送的包最小大小*/


#define TS2NET_REC_PATPMT_SEND_CNT (50)
#define TS2NET_REC_PMT_MAX_SIZE (512)

#define TS2NET_REC_STATUS_STOP    (0)
#define TS2NET_REC_STATUS_PAUSE  (1)
#define TS2NET_REC_STATUS_RECING (2)


typedef struct
{
    element_t list;
    D_U16 srv_id;
    D_U16 pmt_pid;
    D_U16 pcrpid;
    D_U16 v_pid;
    D_U16 a_pid;
    D_U16 sec_len;
    D_U8  sec_buf[4];
} D_PmtRecInfo;

typedef struct
{
    D_U32 user_id;  /**< 用户号，记录此设备所属用户*/
    D_DBSrvID dbsrvid;      /**< 节目dbsrid*/
    D_U32 cb_data;    /**< 回调参数*/
    D_Ts2NetDataCBFunc cbfunc; /** @brief 录制数据处理回调，返回处理的结果，负数是错误代码，0或正数是处理的字节数*/
} D_Ts2NetUserInfo;

typedef struct
{
    D_Handle handle;       /**< pvr设备句柄*/
    D_U32     dev_type;  /**< 设备类型，pvr还是pes通道*/
    D_HFMan hfman;      /**< 节目dbsrid*/
    D_Char chan_name[32];   /**< 节目名*/
    D_U8 demux_id; /**< 即demux解利用序号*/
    D_U8 video_type; /**< 视频编码类型*/
    D_U8 audio_type; /**< 音频编码类型*/
    D_U32 duration_time;  /**< 持续时间,单位秒*/
    D_U16 video_pid;  /**< 录制视频pid列表*/
    D_U16 audio_pid;  /**< 录制音频pid列表*/
    D_U16 pcr_pid;  /**< 录制pcr pid列表*/

    D_HDemux hpmt;
    D_Ts2NetUserInfo user_info;  /**< 用户信息*/

    //录像缓冲区相关
    D_Bool recbuf_use_sys;  /**< 录像缓冲区是否使用程序分区 */
    D_U32 recbuf_size;      /**< 录像缓冲区大小， demux通道寄存器要求8K对齐*/
    D_U32 recbuf_int_value; /**< 引发中断的最小数据大小*/
    D_U32 recbuf_addr ;     /**< 内存分配时得到的地址*/
    D_U32 recbuf_physaddr;  /**< 录像缓冲区物理地址, 驱动使用 */
    D_U8 *recbuf_align_addr;    /**< 8K对齐后的地址*/

    D_U32 rec_consumer;    /**< 消费者指针，偏移量*/
    D_U32 addr_near_end;    /**< 靠近结尾的地址标记*/

    D_Bool share_handle;  /**< 共享通道句柄*/

    D_Handle hcbman_interrupt; /**< 中断里回调注册句柄*/
    D_U8    interrupt_state;/**< 中断类型记录*/
    D_HSem hsem_record; /**< 中断信号量*/
    D_U32 record_status;  /**< 正在录制标示*/
    D_U32   rec_total_size;             /**< 已发送的总数据量*/
    D_U32   packet_remain_size;   /**< 188 对齐要补齐的数据*/
    D_U32   print_cnt;
    D_Bool  rec_pmt;  /**< 是否已经录制了pmt*/
    D_U64 last_patpmt_time; /**< 上一次发送patpmt时间点*/
    D_U64 patpmt_interval;  /**< 发送patpmt时间间隔*/
    D_U32  patpmt_send;     /**< 发送patpmt次数*/
    D_Bool  pmt_got;
    D_U8    pat_counter;
    D_U8    pat_tsbuf[188];
    D_U8    pmt_counter;
    D_U8    pmt_tsbuf[188];
    D_U32 last_size;
    D_U64 last_time;
} D_Ts2NetRecDevice;

/** @brief 录像app句柄*/
static D_HApp happ_ts2net_record = D_INVALID_HANDLE;
static D_Ts2NetRecDevice *Ts2NetRecDev = NULL;
static D_HMutex hmutex_ts2net = D_INVALID_HANDLE;
/** @brief缓存pmt记录*/
static D_HMutex hmutex_pmt = D_INVALID_HANDLE;
static list_t pmt_rec_list;
static D_U8  *pmt_sec_buf = NULL;

/** @brief当前dtv正在播放的频道*/
static D_ID cur_dtv_dbsrvid = -1;

extern D_DBTSID d_tv_get_curr_db_ts_id (void);


#define ts2net_record_lock() if(hmutex_ts2net != D_INVALID_HANDLE){d_mutex_lock(hmutex_ts2net);}
#define ts2net_record_unlock() if(hmutex_ts2net != D_INVALID_HANDLE){d_mutex_unlock(hmutex_ts2net);}

#define pmt_record_lock() if(hmutex_pmt != D_INVALID_HANDLE){d_mutex_lock(hmutex_pmt);}
#define pmt_record_unlock() if(hmutex_pmt != D_INVALID_HANDLE){d_mutex_unlock(hmutex_pmt);}



/** @brief  ts包的counter加1*/
#define ts_counter_add(_buf, _counter) {_counter++; _counter &= 0x0F; _buf[3] = (0x10 + (D_U8)(0x0f & _counter));}

/** @brief 生成一个pat表的ts包
action >= 0x10 时，打整个包的数据，并以(action & 0x0f) 作为ts counter
action < 0x10 时，只以(action & 0x0f) 来修改ts_buf里的ts counter*/
void ts2net_record_make_pat(D_U32 counter, D_U8 *ts_buf, D_Size ts_buf_size,
                            D_U16 srvid, D_U16 pmtpid)
{
    D_U32 crc_val;
    D_U8 def_buf[] = {0x47, 0x40, 0x00, 0x10, 0x00,   // ts head   +  pointer field
                      0x00, 0xb0, 0x11, 0x00, 0x01, 0x03, 0x00, 0x00,  // tid  len tsid ver secnum last_secnum
                      0x00, 0x00, 0x00, 0x10,     // program_num == 0    nit pid
                      0x00, 0x01, 0x1f, 0xff,     // program_num   pmt_pid
                      0x00, 0x00, 0x00, 0x00
                     };   // crc32 value

    memset(ts_buf, 0xFF, ts_buf_size);
    def_buf[3] = (0x10 + (D_U8)(0x0f & counter));     // ts counter
    def_buf[17] = (D_U8)(0xFF & (srvid >> 8));
    def_buf[18] = (D_U8)(0xFF & (srvid));
    def_buf[19] = (D_U8)(0xFF & (pmtpid >> 8));
    def_buf[20] = (D_U8)(0xFF & (pmtpid));
    crc_val = d_crc_compute_32(&def_buf[5], (sizeof(def_buf) - 9));
    def_buf[21] = (D_U8)(0xFF & (crc_val >> 24));
    def_buf[22] = (D_U8)(0xFF & (crc_val >> 16));
    def_buf[23] = (D_U8)(0xFF & (crc_val >> 8));
    def_buf[24] = (D_U8)(0xFF & (crc_val));
    memcpy(ts_buf, def_buf, sizeof(def_buf));
}

/** @brief 生成一个pmt表的ts包
action >= 0x10 时，打整个包的数据，并以(action & 0x0f) 作为ts counter
action < 0x10 时，只以(action & 0x0f) 来修改ts_buf里的ts counter*/
void ts2net_record_make_pmt(D_U32 counter, D_U8 *ts_buf, D_Size ts_buf_size,
                            D_U16 srvid, D_U16 pmtpid, D_U16 pcrpid,
                            D_U16 vpid, D_VidCodecType vtype,
                            D_U16 apid, D_AudCodecType atype)
{
    D_U32 idx, stream_idx, crc_val;
    D_U16 sec_len, stream_len, es_info_len;
    D_U8  stream_type;

    memset(ts_buf, 0xFF, ts_buf_size);
    ts_buf[0] = 0x47;
    ts_buf[1] = 0x40 | (0x1F & (pmtpid >> 8));
    ts_buf[2] = (pmtpid & 0xFF);
    ts_buf[3] = (0x10 + (D_U8)(0x0f & counter));     // ts counter
    ts_buf[4] = 0x00;     // ts counter
    idx = 5;
    sec_len = 0;
    ts_buf[idx + 0] = TID_PMT;     // ts counter
    ts_buf[idx + 1] = 0xb0;     //
    ts_buf[idx + 2] = 0x00;     // sec_len
    ts_buf[idx + 3] = (D_U8)(0xFF & (srvid >> 8));     // srvid
    ts_buf[idx + 4] = (D_U8)(0xFF & (srvid));     // srvid
    ts_buf[idx + 5] = 0xc3;     // 0xc1 & ((ver 0x1F) << 1)       version = 0x01
    ts_buf[idx + 6] = 0x00;     // sec_num
    ts_buf[idx + 7] = 0x00;     // last_sec_num
    pcrpid &= 0x1FFF;
    ts_buf[idx + 8] = (D_U8)(0xFF & (pcrpid >> 8));     // srvid
    ts_buf[idx + 9] = (D_U8)(0xFF & (pcrpid));     // srvid

    ts_buf[idx + 10] = 0xF0;     // program_info_length = 0
    ts_buf[idx + 11] = 0x00;     // program_info_length = 0
    sec_len = 12;

    vpid &= 0x1FFF;
    apid &= 0x1FFF;
    stream_len = 0;
    stream_idx = idx + 12;

    if(vpid != 0x1FFF)
    {
        switch(vtype)
        {
            case D_VID_CODEC_MPEG2:
                stream_type = 0x02;
                break;
            case D_VID_CODEC_AVS:
                stream_type = 0x42;
                break;
            case D_VID_CODEC_H264:
                stream_type = 0x1b;
                break;
            case D_VID_CODEC_MPEG4:
                stream_type = 0x10;
                break;
            default:
                stream_type = 0x06;
                break;
        }

        es_info_len = 0;
        ts_buf[stream_idx + 0] = stream_type; // stream_type;
        ts_buf[stream_idx + 1] = (D_U8)(0xFF & (vpid >> 8));     // vpid
        ts_buf[stream_idx + 2] = (D_U8)(0xFF & (vpid));     // vpid
        ts_buf[stream_idx + 3] = (D_U8)(0xFF & (es_info_len >> 8));     // es_info_len
        ts_buf[stream_idx + 4] = (D_U8)(0xFF & (es_info_len >> 8));     // es_info_len
        stream_idx += (5 + es_info_len);
        stream_len += (5 + es_info_len);
    }

    if(apid != 0x1FFF)
    {
        switch(atype)
        {
            case D_AUD_CODEC_MPEG2:
                stream_type = 0x04;
                break;
            case D_AUD_CODEC_AC3:
                stream_type = 0x81;
                break;
            case D_AUD_CODEC_AAC:
                stream_type = 0x0F;
                break;
            case D_AUD_CODEC_DRA:
                stream_type = 0x06;
                break;
            case D_AUD_CODEC_DTS:
                stream_type = 0x06;
                break;
            default:
                stream_type = 0x06;
                break;
        }
        es_info_len = 0;
        ts_buf[stream_idx + 0] =  stream_type; // stream_type;
        ts_buf[stream_idx + 1] = (D_U8)(0xFF & (apid >> 8));     // vpid
        ts_buf[stream_idx + 2] = (D_U8)(0xFF & (apid));     // vpid
        ts_buf[stream_idx + 3] = (D_U8)(0xFF & (es_info_len >> 8));     // es_info_len
        ts_buf[stream_idx + 4] = (D_U8)(0xFF & (es_info_len >> 8));     // es_info_len

        if(atype == D_AUD_CODEC_DRA)
        {
            ts_buf[stream_idx + 5] = DESCR_REGISTRATION;
            ts_buf[stream_idx + 6] = 4;
            ts_buf[stream_idx + 7] = 0x44;
            ts_buf[stream_idx + 8] = 0x52;
            ts_buf[stream_idx + 9] = 0x41;
            ts_buf[stream_idx + 10] = 0x31;
            es_info_len = 6;
        }
        else if(atype == D_AUD_CODEC_DTS)
        {
            ts_buf[stream_idx + 5] = DESCR_REGISTRATION;
            ts_buf[stream_idx + 6] = 4;
            ts_buf[stream_idx + 7] = 0x44;
            ts_buf[stream_idx + 8] = 0x54;
            ts_buf[stream_idx + 9] = 0x53;
            ts_buf[stream_idx + 10] = 0x31;
            es_info_len = 6;
        }

        ts_buf[stream_idx + 3] = (D_U8)(0xFF & (es_info_len >> 8));     // es_info_len
        ts_buf[stream_idx + 4] = (D_U8)(0xFF & (es_info_len >> 8));     // es_info_len
        stream_idx += (5 + es_info_len);
        stream_len += (5 + es_info_len);
    }

    sec_len  +=  stream_len;
    sec_len += 4;   // crc 4 byte
    ts_buf[idx + 1] = (D_U8)(0xb0 | ((0x0F & ((sec_len - 3) >> 8))));     // sec_len
    ts_buf[idx + 2] = (D_U8)(0xFF & ((sec_len - 3)));     // sec_len

    crc_val = d_crc_compute_32(&ts_buf[5], (sec_len - 4));
    ts_buf[stream_idx + 0] = (D_U8)(0xFF & (crc_val >> 24));
    ts_buf[stream_idx + 1] = (D_U8)(0xFF & (crc_val >> 16));
    ts_buf[stream_idx + 2] = (D_U8)(0xFF & (crc_val >> 8));
    ts_buf[stream_idx + 3] = (D_U8)(0xFF & (crc_val));
}

/** @brief 取得pmt的缓存记录
* @param 频道相关参数
* @return 失败返回NULL
*/
static D_PmtRecInfo* ts2net_record_get_pmt(D_U16 srvid, D_U16 pmtpid, D_U16 pcrpid, D_U16 vpid,  D_U16 apid)
{
    D_PmtRecInfo* ret = NULL, * info;
    element_t *e;

    if(hmutex_pmt == D_INVALID_HANDLE)
    {
        hmutex_pmt = d_mutex_create(NULL);
        init_list(&pmt_rec_list);
    }

    pmt_record_lock();

    for(e = HEAD(&pmt_rec_list); e != (element_t*)(&pmt_rec_list); e = NEXT(e))
    {
        info = (D_PmtRecInfo*)e;
        if((info->srv_id == srvid) && \
           (info->pmt_pid == pmtpid) && \
           (info->pcrpid == pcrpid) && \
           (info->v_pid == vpid) && \
           (info->a_pid == apid))
        {
            ret = info;
            D_DUMP("[Ts2NetRec]: get pmt len %d\n", info->sec_len);
            break;
        }
    }

    pmt_record_unlock();
    return ret;
}

/** @brief 保存pmt的缓存记录
* @param 频道相关参数
* @return 失败返回NULL
*/
static D_PmtRecInfo* ts2net_record_set_pmt(D_U16 srvid, D_U16 pmtpid, D_U16 pcrpid, D_U16 vpid,  D_U16 apid, D_U8* sec, D_U16 sec_len)
{
    D_PmtRecInfo* info = NULL;

    if(hmutex_pmt == D_INVALID_HANDLE)
    {
        hmutex_pmt = d_mutex_create(NULL);
        init_list(&pmt_rec_list);
    }

    pmt_record_lock();
    info = (D_PmtRecInfo*)d_mem_alloc(0, sizeof(D_PmtRecInfo) + sec_len);
    if(info)
    {
        info->srv_id = srvid;
        info->pmt_pid = pmtpid;
        info->pcrpid = pcrpid;
        info->v_pid = vpid;
        info->a_pid = apid;
        info->sec_len = sec_len;
        memcpy(info->sec_buf, sec, sec_len);
        add_tail(&pmt_rec_list, &info->list);
        D_DUMP("[Ts2NetRec]: set pmt len %d\n", info->sec_len);
    }

    pmt_record_unlock();
    return info;
}

/** @brief 和一个应用进行消息同步
* @param happ 应用句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
ts2net_record_sync (D_HApp happ) D_FUNCPOSTFIT
{
    D_Result    ret = D_OK;
    D_AppMsg    amsg;
    D_Bool  force_exit = D_FALSE;
    D_HSem hsync = D_INVALID_HANDLE;

    if(D_INVALID_HANDLE != d_app_self())
    {
        return d_app_sync(happ);
    }

    hsync = d_sem_create(NULL);
    if(hsync == D_INVALID_HANDLE)
    {
        return D_ERR;
    }

    /*发送同步请求消息*/
    amsg.happ = happ;
    amsg.type = D_MSG_APP_SYNC_REQ;
    amsg.handle = hsync;

    if ((ret = d_app_send (happ, (D_U8*)&amsg, sizeof(amsg))) < 0)
    {
#ifdef D_DEBUG
        D_ERROR ("[Ts2NetRec]: Send message error\n");
#endif
        return ret;
    }

    /*等待信号量*/
    while(d_sem_wait_timeout(hsync, 500) != D_OK)
    {
        if(force_exit)
        {
            ret = D_ERR_TIMEOUT;
            break;
        }
    }

    d_sem_destroy(hsync);

    return ret;
}

/** @brief ts2net录像内存释放
*@param[in]
*@return D_OK成功
*/
static D_Result
ts2net_record_dev_free(D_U32 dev_id) D_FUNCPOSTFIT
{
    if(Ts2NetRecDev && (dev_id < TS2NET_DEV_CNT))
    {
        D_Ts2NetRecDevice *dev = &Ts2NetRecDev[dev_id];

        if(dev->recbuf_addr)
        {
            d_sys_unmap_address((D_Ptr)dev->recbuf_physaddr);
#ifndef D_SYSTEM_LINUX
            if(dev->recbuf_use_sys)
            {
                d_sys_unmap_address(dev->recbuf_align_addr);
                d_mem_free((D_Ptr)dev->recbuf_addr);
            }
            else
#endif
            {
                d_sys_free_dev_mem((D_Ptr)dev->recbuf_addr);
            }
        }

        dev->recbuf_size = 0;
        dev->recbuf_addr = 0;
        dev->recbuf_physaddr = 0;
        dev->recbuf_align_addr = NULL;
        dev->addr_near_end = 0;

        if(dev->hsem_record != D_INVALID_HANDLE)
        {
            d_sem_destroy(dev->hsem_record);
            dev->hsem_record = D_INVALID_HANDLE;
        }

        if(dev->hcbman_interrupt != D_INVALID_HANDLE)
        {
            d_cbman_unsubscribe(dev->hcbman_interrupt);
            dev->hcbman_interrupt = D_INVALID_HANDLE;
        }
    }
    return D_OK;
}

/** @brief ts2net录像内存申请
*@param[in] config用户配置
*@return D_OK成功
*/
static D_Result
ts2net_record_dev_alloc(D_U32 dev_id) D_FUNCPOSTFIT
{
    if(Ts2NetRecDev && (dev_id < TS2NET_DEV_CNT))
    {
        D_Ts2NetRecDevice *dev = &Ts2NetRecDev[dev_id];

        if(dev->recbuf_physaddr != 0)
        {
            return D_OK;
        }

        dev->handle = D_INVALID_HANDLE;
        dev->hsem_record = D_INVALID_HANDLE;
        dev->hcbman_interrupt = D_INVALID_HANDLE;
        dev->recbuf_size = (TS2NET_REC_BUF_SIZE + TS2NET_REC_BUF_ALIGN - 1) & (~(TS2NET_REC_BUF_ALIGN - 1));
        dev->recbuf_int_value = TS2NET_REC_INT_BUF_SIZE;
        dev->recbuf_use_sys = D_TRUE;
#if 0
        if(dev->hsem_record == D_INVALID_HANDLE)
        {
            dev->hsem_record = d_sem_create(NULL);
            if(dev->hsem_record == D_INVALID_HANDLE)
            {
                return D_ERR;
            }
        }
#endif
#ifndef D_SYSTEM_LINUX
        if(dev->recbuf_use_sys)
        {
            dev->recbuf_addr = (D_U32)d_mem_alloc(0, dev->recbuf_size + TS2NET_REC_BUF_ALIGN);
            if(!dev->recbuf_addr)
                return D_ERR_NO_SPACE;

            dev->recbuf_align_addr = (D_U8*)d_sys_map_address(D_SysAddr_UnCached, (D_Ptr)((dev->recbuf_addr + (TS2NET_REC_BUF_ALIGN - 1)) & ~(TS2NET_REC_BUF_ALIGN - 1)), dev->recbuf_size);
        }
        else
#endif
        {
            dev->recbuf_addr = (D_U32)d_sys_alloc_dev_mem(dev->recbuf_size, TS2NET_REC_BUF_ALIGN);
            if(!dev->recbuf_addr)
                return D_ERR_NO_SPACE;

            dev->recbuf_align_addr = (D_U8*)dev->recbuf_addr;
        }

        dev->recbuf_physaddr = (D_U32)d_sys_map_address(D_SysAddr_Phys, (D_Ptr)dev->recbuf_align_addr, dev->recbuf_size);
        dev->addr_near_end = (D_U32)dev->recbuf_align_addr + dev->recbuf_size - TS2NET_REC_SEND_MIN_SIZE - 188;

        D_DUMP ("[Ts2NetRec]: dev%d alloc:\n", dev_id);
        D_DUMP ("[Ts2NetRec]: recbuf_size %x\n", dev->recbuf_size);
        D_DUMP ("[Ts2NetRec]: recbuf_align_addr %x\n", (D_U32)dev->recbuf_align_addr);
        D_DUMP ("[Ts2NetRec]: recbuf_physaddr %x\n", dev->recbuf_physaddr);
    }
    return D_OK;
}

/** @brief为用户查找或创建一个设备
* @return 成功返回D_OK
*/
static D_Result
ts2net_record_get_dev(D_U32 user_id) D_FUNCPOSTFIT
{
    D_Ts2NetRecDevice *rec;
    D_U32 id, devid = (D_U32)(-1);

    for(id = 0; id < TS2NET_DEV_CNT; id++)
    {
        rec = &Ts2NetRecDev[id];
        /* 找到相同用户的设备*/
        if(rec->user_info.user_id == user_id)
        {
            return id;
        }

        /* 记录未使用过的设备*/
        if((devid == (D_U32)(-1)) && (rec->user_info.user_id == (D_U32)(-1)))
        {
            devid = id;
        }
    }
    return devid;
}

/** @brief信息交换
* @return 成功返回D_OK
*/
static void
ts2net_record_swap_info(D_Ts2NetRecDevice *rec0, D_Ts2NetRecDevice *rec1) D_FUNCPOSTFIT
{
    D_Ts2NetUserInfo userinfo;
    D_Handle hmd;

    userinfo = rec0->user_info;
    rec0->user_info = rec1->user_info;
    rec1->user_info = userinfo;

    hmd = rec0->hpmt;
    rec0->hpmt = rec1->hpmt;
    rec1->hpmt = hmd;
}

/** @brief信息共享
* @return 成功返回D_OK
*/
static void
ts2net_record_share_info(D_Ts2NetRecDevice *rec1, D_Ts2NetRecDevice *rec0) D_FUNCPOSTFIT
{
    rec1->share_handle = rec0->handle;
    rec1->recbuf_size = rec0->recbuf_size;
    rec1->recbuf_align_addr = rec0->recbuf_align_addr;
    rec1->recbuf_physaddr = rec0->recbuf_physaddr;
    rec1->addr_near_end = rec0->addr_near_end;
    rec1->rec_consumer = (rec0->rec_consumer/188)*188;
    rec1->rec_pmt = rec0->rec_pmt;
}

/** @brief 开始ts2net录制
* @param[in] config 录像信息结构体
* @return 成功返回D_OK
*/
static D_Result
ts2net_record_start(D_Ts2NetRecDevice *rec, D_U32 dev_id) D_FUNCPOSTFIT
{
    D_U32 i;
    D_DBSrvInfo srvinfo;
    D_DBTSInfo tsinfo;
    D_DBSateInfo satinfo;
    D_DBAnteInfo antinfo;
    D_VidInput      input;
    D_U16 pids[24];
    D_DemuxAttr attr;

    if(rec->record_status == TS2NET_REC_STATUS_RECING)
    {
        return D_OK;
    }

    input = p_conf_get_vid_input ();

    /*业务有效性检查，取得业务信息*/
    if(D_OK != d_dbase_get_srv_info(rec->user_info.dbsrvid, &srvinfo))
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
#if 0
    if(input != D_VID_IUTPUT_DTV) /*非DTV下，进行频点锁频*/
    {
        rec->hfman = d_fman_get_handle_by_type((D_FEndType)tsinfo.tuner_type, 0);
        d_fman_set_param (rec->hfman, &tsinfo.param, D_TRUE, (D_FEndType)tsinfo.tuner_type, &satinfo, &antinfo);
        d_task_wait(5);
    }
    else
    {
        /*DTV下，只能录制当前频点下的频道*/
        if(srvinfo.db_ts_id != d_tv_get_curr_db_ts_id())
        {
            return D_ERR;
        }
    }
#endif

    //D_DUMP("[HaierPvrRec]:vpid %04x, apid %04x, pcrpid %04x, pmtpid %04x\n", srvinfo.vid_pid, srvinfo.aud1_pid, srvinfo.pcr_pid, srvinfo.pmt_pid);
    rec->packet_remain_size = 0;
    rec->rec_total_size = 0;
    rec->print_cnt = 3;
    rec->last_size = 0;
    rec->last_time = 0;
    rec->pat_counter = 0;
    rec->pmt_counter = 0;
    rec->last_patpmt_time = 0;
    rec->patpmt_interval = 50 * d_sys_get_tick_per_sec() / 1000;
    rec->patpmt_send = 0;
    rec ->pmt_got = D_FALSE;

    if(rec->share_handle == D_INVALID_HANDLE)
    {
        if(D_OK != ts2net_record_dev_alloc(dev_id))
        {
            D_ERROR("[Ts2NetRec]: dev%d record_dev_alloc failed !\n", dev_id);
            return D_ERR;
        }

        for(i = 0; i < 24; i++)
        {
            pids[i] = 0x000fL;//PID_RESERVED;
        }

        pids[1] = srvinfo.vid_pid;
        pids[2] = srvinfo.aud1_pid;
        rec->rec_pmt = D_FALSE;
        // 如果pcr 独立，也录制pcr
        if(srvinfo.pcr_pid != 0x1FFF && srvinfo.pcr_pid != srvinfo.vid_pid && srvinfo.pcr_pid != srvinfo.aud1_pid)
        {
            pids[3] = srvinfo.pcr_pid;
            rec->rec_pmt = D_FALSE;
        }
        else
        {
            /*非DTV下或者demux1下才过滤pmt，避免正常电视应用功能收不到pmt*/
            if(input != D_VID_IUTPUT_DTV || rec->demux_id == 1)
            {
                pids[3] = srvinfo.pmt_pid;
                rec->rec_pmt = D_TRUE;
            }
        }

        // 与当前的dtv播放的频道相同，暂停
        if(input == D_VID_IUTPUT_DTV && rec->demux_id == 0 && cur_dtv_dbsrvid == rec->user_info.dbsrvid)
        {
            rec->record_status = TS2NET_REC_STATUS_PAUSE;
            D_DUMP("[Ts2NetRec]: dev%d record pause !\n", dev_id);
            return D_OK;
        }
    }

    memset(rec->pat_tsbuf, 0xFF, sizeof(rec->pat_tsbuf));
    ts2net_record_make_pat(rec->pat_counter, rec->pat_tsbuf, 188, srvinfo.srv_id, srvinfo.pmt_pid);

    if(rec->rec_pmt == D_FALSE)
    {
        D_PmtRecInfo *pmtinfo;

        memset(rec->pmt_tsbuf, 0xFF, sizeof(rec->pmt_tsbuf));
        ts2net_record_make_pmt(rec->pmt_counter, rec->pmt_tsbuf, 188, srvinfo.srv_id, srvinfo.pmt_pid, srvinfo.pcr_pid, srvinfo.vid_pid, srvinfo.vid_codec, srvinfo.aud1_pid, srvinfo.aud1_codec);
        pmtinfo = ts2net_record_get_pmt(srvinfo.srv_id, srvinfo.pmt_pid, srvinfo.pcr_pid, srvinfo.vid_pid, srvinfo.aud1_pid);
        if(pmtinfo && pmtinfo->sec_len > 0 && pmtinfo->sec_len < 184)
        {
            rec ->pmt_got = D_TRUE;
            memcpy(&rec->pmt_tsbuf[5], pmtinfo->sec_buf, pmtinfo->sec_len);
        }
        else
        {
            D_DemuxFilter   filter;
            /* 搜索pmt*/
            D_DEMUX_ATTR_INIT(&attr);
            attr.type = D_DEMUX_SEC;
            attr.id = rec->demux_id;
            d_sec_filter_init (&filter);
            d_sec_filter_set_tid (&filter, TID_PMT);
            d_sec_filter_set_pid (&filter, srvinfo.pmt_pid);
            d_sec_filter_set_ext_tid (&filter, srvinfo.srv_id);
            rec->hpmt = d_demux_create(&attr, d_app_get_queue(d_app_self ()));
            d_demux_set_filter (rec->hpmt, &filter);
            d_demux_start (rec->hpmt);
        }
    }

    if(rec->share_handle == D_INVALID_HANDLE)
    {
        D_DEMUX_ATTR_INIT(&attr);
        attr.type = D_DEMUX_TS;
        attr.id = rec->demux_id;
        rec->handle = (D_Handle)d_demux_createpvr(&attr, D_INVALID_HANDLE);
        if(rec->handle == D_INVALID_HANDLE)
        {
            ts2net_record_dev_free(dev_id);
            D_ERROR("[Ts2NetRec]: dev%d demux create failed !\n", dev_id);
            return D_ERR;
        }

        d_demux_setpvrpara(rec->handle, pids, 4, D_DMX_PES_OUT_PID_TS);
        d_demux_setpvrbuffer(rec->handle, rec->recbuf_physaddr, rec->recbuf_size);
        d_demux_startpvr(rec->handle);
        rec->rec_consumer = 0;
    }

    rec->record_status = TS2NET_REC_STATUS_RECING;
    D_DUMP("[Ts2NetRec]: dev%d Start Record %d.\n", dev_id, rec->user_info.dbsrvid);
    return D_OK;
}

/** @brief 停止ts2net录制
* @return 成功返回D_OK
*/
static D_Result
ts2net_record_stop(D_Ts2NetRecDevice *rec, D_U32 dev_id) D_FUNCPOSTFIT
{
    if(rec->handle != D_INVALID_HANDLE)
    {
        d_demux_stoppvr(rec->handle);
        d_demux_destroypvr(rec->handle);
        rec->handle = D_INVALID_HANDLE;
    }

    if(rec->hpmt != D_INVALID_HANDLE)
    {
        d_demux_stop(rec->hpmt);
        d_demux_destroy(rec->hpmt);
        rec->hpmt = D_INVALID_HANDLE;
    }

    ts2net_record_dev_free(dev_id);
    rec->share_handle = D_INVALID_HANDLE;
    rec->record_status = TS2NET_REC_STATUS_STOP;
    rec->user_info.user_id = (D_U32)(- 1);
    rec->user_info.dbsrvid = (D_ID)(- 1);

    D_DUMP("[Ts2NetRec]: dev%d Stop Record.\n", dev_id);
    return D_OK;
}

/** @brief 停止ts2net录制
* @return 成功返回D_OK
*/
static D_Result
ts2net_record_pause(D_Ts2NetRecDevice *rec, D_U32 dev_id) D_FUNCPOSTFIT
{
    if(rec->handle != D_INVALID_HANDLE)
    {
        d_demux_stoppvr(rec->handle);
        d_demux_destroypvr(rec->handle);
        rec->handle = D_INVALID_HANDLE;
    }

    if(rec->hpmt != D_INVALID_HANDLE)
    {
        d_demux_stop(rec->hpmt);
        d_demux_destroy(rec->hpmt);
        rec->hpmt = D_INVALID_HANDLE;
    }

    rec->share_handle = D_INVALID_HANDLE;
    if(rec->record_status != TS2NET_REC_STATUS_STOP)
    {
        rec->record_status = TS2NET_REC_STATUS_PAUSE;
    }

    D_DUMP("[Ts2NetRec]: dev%d Pause Record.\n", dev_id);
    return D_OK;
}

/** @brief 处理数据
* @param wait 是否等待处理完成
* @param timeout 超时时间
* @return 返回处理的长度
*/
static D_Size ts2net_record_deal_data(D_Ts2NetRecDevice *rec, D_U8* data_buf, D_U32 data_len, D_Bool wait, D_U32 timeout)
{
    D_U64 start, t, c_ms = 0;
    D_Size total, ret, len;

    total = 0;
    len = (D_Size)data_len;
    if(rec->user_info.cbfunc)
    {
        if(wait && timeout != 0 && timeout != (D_U32) - 1)
        {
            c_ms = d_sys_get_tick_per_sec() / 1000;
            c_ms = c_ms * (D_U64)timeout;
        }

        start = d_sys_get_tick();
        while(len)
        {
            ret = rec->user_info.cbfunc(rec->user_info.cb_data, (D_U8*)(data_buf + total), len);
            if(ret < 0)
            {
                return ret;
            }

            len -= ret;
            total += ret;
            if(len == 0 || wait == D_FALSE)
                break;

            t = d_sys_get_tick() - start;
            if(t >= c_ms)
            {
                break;
            }
            else
            {
                d_task_wait(2);
            }
        }
    }
    return total;
}


/** @brief ts2net录制app的回调函数
* @param[in] msg 消息
* @return 成功返回D_OK
*/
static D_Result
ts2net_record_callback(D_Msg *msg)D_FUNCPOSTFIT
{
    D_Ts2NetRecDevice * rec, *rec_oth;
    D_U32 devid;
    D_VidInput      input;
    D_U32 rec_status;

    rec = (D_Ts2NetRecDevice *)d_app_get_data (d_app_self ());

    switch (msg->type)
    {
        case D_MSG_APP_CREATE:
        {
            /* the this param of this task */
            rec = msg->app.arg;
            d_app_set_data (d_app_self (), (D_Ptr)rec);
            d_app_set_timeout(d_app_self(), (D_MSec) - 1);
        }
        break;
        case D_MSG_DEMUX_DATA:
            if(msg->demux.hdemux != D_INVALID_HANDLE)
            {
                D_Size cnt;
                D_DBSrvInfo srvinfo;

                for(devid = 0; devid < TS2NET_DEV_CNT; devid++)
                {
                    rec = &Ts2NetRecDev[devid];
                    if(msg->demux.hdemux == rec->hpmt)
                    {
                        /* 保存pmt信息*/
                        cnt = d_demux_read(msg->demux.hdemux, pmt_sec_buf, TS2NET_REC_PMT_MAX_SIZE);
                        if(cnt > 0 && cnt < 184)
                        {
                            D_PmtRecInfo *pmtinfo;

                            d_dbase_get_srv_info(rec->user_info.dbsrvid, &srvinfo);
                            pmtinfo = ts2net_record_set_pmt(srvinfo.srv_id, srvinfo.pmt_pid, srvinfo.pcr_pid, srvinfo.vid_pid, srvinfo.aud1_pid, pmt_sec_buf, cnt);
                            if(pmtinfo)
                            {
                                memcpy(&rec->pmt_tsbuf[5], pmtinfo->sec_buf, pmtinfo->sec_len);
                                rec ->pmt_got = D_TRUE;
                            }
                        }
                        rec->hpmt = D_INVALID_HANDLE;
                    }
                }
                d_demux_stop(msg->demux.hdemux);
                d_demux_destroy(msg->demux.hdemux);
            }
            break;
        case D_MSG_PVR_REC_START:
            devid = ts2net_record_get_dev((D_U32)msg->user.param1);
            if(devid < TS2NET_DEV_CNT)
            {
                rec = &Ts2NetRecDev[devid];
                if(rec->record_status > TS2NET_REC_STATUS_STOP) /* 如果正在录制，则停止*/
                {
                    ts2net_record_pause(rec, devid);
                }
                rec->user_info.user_id = (D_U32)msg->user.param1;
                rec->user_info.dbsrvid = (D_DBSrvID)msg->user.param2;
                rec->user_info.cbfunc = (D_Ts2NetDataCBFunc)msg->user.param3;
                rec->user_info.cb_data = (D_U32)msg->user.param4;

                input = p_conf_get_vid_input ();
                // 与当前的dtv播放的频道相同，暂停
                if(input == D_VID_IUTPUT_DTV && devid == 1 && cur_dtv_dbsrvid == rec->user_info.dbsrvid)
                {
                    rec_oth = &Ts2NetRecDev[0];
                    if(rec_oth->record_status > TS2NET_REC_STATUS_STOP)
                    {
                        rec_status = rec_oth->record_status;
                        if(rec_oth->user_info.dbsrvid != cur_dtv_dbsrvid)
                        {
                            ts2net_record_pause(rec_oth, 0);
                            /*信息交换*/
                            ts2net_record_swap_info(rec, rec_oth);
                            if(rec_status == TS2NET_REC_STATUS_RECING)
                            {
                                ts2net_record_start(rec_oth, 0);
                            }
                        }
                        else
                        {
                            /*共享通道*/
                            ts2net_record_share_info(rec, rec_oth);
                        }
                    }
                }

                ts2net_record_start(rec, devid);
                /* 如果有用户录制，设置检查时间*/
                d_app_set_timeout(d_app_self(), TS2NET_REC_CHECK_TIME);
            }
            break;
        case D_MSG_PVR_REC_STOP:
            devid = ts2net_record_get_dev((D_U32)msg->user.param1);
            if(devid < TS2NET_DEV_CNT)
            {
                rec = &Ts2NetRecDev[devid];
                if(rec->record_status > TS2NET_REC_STATUS_STOP)
                {
                    ts2net_record_stop(rec, devid);
                }

                /* 第1路是demux 0，如果停止了第0路，且第1路属于暂停状态，
                可能是第1路与电视播放冲突，可换到第0路来录制*/
                if(TS2NET_DEV_CNT > 1)
                {
                    input = p_conf_get_vid_input ();
                    rec_oth = &Ts2NetRecDev[1];
                    if(input == D_VID_IUTPUT_DTV && devid == 0)
                    {
                        if(rec_oth->share_handle != D_INVALID_HANDLE || (rec_oth->record_status == TS2NET_REC_STATUS_PAUSE && rec_oth->user_info.dbsrvid == cur_dtv_dbsrvid))
                        {
                            /*信息交换*/
                            ts2net_record_swap_info(rec, rec_oth);
                            ts2net_record_stop(rec_oth, 1);
                            ts2net_record_start(rec, 0);
                        }
                    }
                }

                /* 如果都已经停止，检查时间加长*/
                if(TS2NET_DEV_CNT < 2 || (Ts2NetRecDev[0].record_status != TS2NET_REC_STATUS_RECING && Ts2NetRecDev[0].record_status  != TS2NET_REC_STATUS_RECING))
                {
                    d_app_set_timeout(d_app_self(), (D_MSec) - 1);
                }
            }
            break;
        case D_MSG_PVR_REC_PAUSE:
            if(msg->user.param1 < 1)
            {
                rec = &Ts2NetRecDev[0];
                ts2net_record_pause(rec, 0);
            }

            if(msg->user.param2 < 2)
            {
                rec = &Ts2NetRecDev[1];
                ts2net_record_pause(rec, 1);
            }
            break;
        case D_MSG_PVR_REC_RESUME:
            if(msg->user.param1 < 1)
            {
                rec = &Ts2NetRecDev[0];
                ts2net_record_start(rec, 0);
            }

            if(msg->user.param2 < 2)
            {
                rec = &Ts2NetRecDev[1];
                ts2net_record_start(rec, 1);
            }
            break;
        case D_MSG_APP_TIMEOUT:
        {
            D_Result ret;
            D_U32 read_addr = 0, read_len = 0;
            D_U32 producer, consumer, len2send;
            D_Handle  hrec;

            for(devid = 0; devid < TS2NET_DEV_CNT; devid++)
            {
                rec = &Ts2NetRecDev[devid];
                if(rec->record_status < TS2NET_REC_STATUS_RECING)
                {
                    continue;
                }

                consumer = 0;
                producer = 0;
                hrec = (rec->share_handle != D_INVALID_HANDLE) ? rec->share_handle : rec->handle;

                /* 获取读写指针信息*/
                ret = d_demux_getpvr_info(hrec, NULL, NULL, &producer, &consumer);
                if(ret != D_OK)
                {
                    read_len = 0;
#if 0   /* pvr通道没有溢出中断*/
                    if(ret == D_ERR_OVERFLOW)
                    {
                        /* 溢出复位*/
                        rec->packet_remain_size = 0;
                        rec->rec_total_size = 0;
                        rec->rec_consumer = 0;
                        D_ERROR("[HaierPvrRec]: dev%d REC D_ERR_OVERFLOW.\n", devid);
                    }
#endif
                    continue;
                }
                else
                {
                    /* 硬件consumer是8字节对齐的，所以自己维护*/
                    consumer = rec->rec_consumer;
                    if (producer > consumer)
                    {
                        read_len = producer - consumer;
                        ret = D_OK;
                    }
                    else if (producer < consumer)
                    {
                        read_len = rec->recbuf_size - consumer;
                    }

                    read_addr = (D_U32)rec->recbuf_align_addr + consumer;
                }

                /* 一次读188对齐的字节，方便插入pat与pmt包*/
                len2send = read_len / 188;
                len2send = len2send * 188;
                len2send += rec->packet_remain_size; /* 上一个包要补齐的数据量*/
                if(len2send > read_len)
                {
                    len2send = (len2send > 188) ? (len2send - 188) : read_len;
                }
                else if(len2send == 0)
                {
                    len2send = read_len;
                }

                if(len2send > 0 && (len2send >= TS2NET_REC_SEND_MIN_SIZE || read_addr >= rec->addr_near_end))
                {
                    D_Size ret_deal;
#if TS2NET_DEBUG_EN
                    if(rec->print_cnt)
                    {
                        D_DUMP("[HaierPvrRec]: dev%d RecDataReady, addr 0x%08x, len 0x%x.\n", devid, read_addr, (read_addr % 188), len2send);
                        rec->print_cnt--;
                    }
#endif
                    // 读取数据，并更新读指针位置
                    if(rec->user_info.cbfunc)
                    {
                        ret_deal = -1;
                        if(rec->patpmt_send <= TS2NET_REC_PATPMT_SEND_CNT && rec->packet_remain_size == 0)
                        {
                            if((d_sys_get_tick() - rec->last_patpmt_time) >= rec->patpmt_interval)
                            {
                                rec->last_patpmt_time = d_sys_get_tick();
                                if(188 == ts2net_record_deal_data(rec, (D_U8*)rec->pat_tsbuf, (D_Size)188, D_TRUE, 50))
                                {
                                    ts_counter_add(rec->pat_tsbuf, rec->pat_counter);
                                }
                                if(rec->rec_pmt == D_FALSE && rec ->pmt_got)
                                {
                                    if(188 == ts2net_record_deal_data(rec, (D_U8*)rec->pmt_tsbuf, (D_Size)188, D_TRUE, 50))
                                    {
                                        ts_counter_add(rec->pmt_tsbuf, rec->pmt_counter);
                                    }
                                }
                                rec->patpmt_send++;
                                if(rec->patpmt_send > 40)
                                {
                                    rec->patpmt_interval =  500 * d_sys_get_tick_per_sec() / 1000;
                                }
                                else
                                {
                                    rec->patpmt_interval =  ((rec->patpmt_send + 9) / 10) * 50 * d_sys_get_tick_per_sec() / 1000;
                                }
                            }
                        }
#if TS2NET_DEBUG_EN
                        {
                            D_U8 *recbuf = (D_U8*)read_addr;
                            if(rec->packet_remain_size == 0 && (recbuf[0] != 0x47))
                            {
                                D_DUMP("[Ts2NetRec]: dev%d data error ! addr %x %d: %02x != 0x47\n", devid, read_addr, recbuf[0]);
                            }
                        }
#endif
                        ret_deal = ts2net_record_deal_data(rec, (D_U8*)read_addr, (D_Size)len2send, D_TRUE, 20);
                    }
                    else
                    {
                        ret_deal = (D_Size)len2send;
                    }

                    if(ret_deal > 0)
                    {
#if TS2NET_DEBUG_EN
                        if(len2send !=  (D_U32)ret_deal)
                        {
                            D_DUMP("\nDataDealFunction %d != ret %d \n", len2send, ret_deal);
                        }
#endif
                        /* 计算下一次发送时要补齐的数据量*/
                        rec->rec_total_size += ret_deal;
                        rec->packet_remain_size = rec->rec_total_size % 188;
                        rec->packet_remain_size = (rec->packet_remain_size > 0) ? (188 - rec->packet_remain_size) : 0;
                        if((rec->rec_total_size & 0xc0000000) == 0xc0000000)
                        {
                            rec->rec_total_size %= 188;
                        }

                        /* 计算消费者指针并设置*/
                        len2send = (read_addr + ret_deal - (D_U32)rec->recbuf_align_addr) % rec->recbuf_size;
                        rec->rec_consumer = len2send;
#if 0   /* pvr通道没有溢出中断，设置消费者指针也没有太大意义*/
                        len2send &= (~7);
                        read_addr = rec->recbuf_physaddr + len2send;
                        d_demux_setpvr_rp(rec->handle, read_addr);
#endif
                        rec->last_size += ret_deal;
                        if(rec->last_time == 0)
                        {
                            rec->last_time = d_sys_get_tick();
                        }
                        else if((d_sys_get_tick() - rec->last_time) >= d_sys_get_tick_per_sec())
                        {
#if TS2NET_DEBUG_EN
                            D_DUMP("\ndev%d W: %u Kbps", devid, (rec->last_size << 3) / 1000);
#endif
                            rec->last_size = 0;
                            rec->last_time = d_sys_get_tick();

                            if(rec->packet_remain_size == 0 && rec->patpmt_send > TS2NET_REC_PATPMT_SEND_CNT && rec->user_info.cbfunc)
                            {
                                ts2net_record_deal_data(rec, (D_U8*)rec->pat_tsbuf, (D_Size)188, D_TRUE, 50);
                                ts_counter_add(rec->pat_tsbuf, rec->pat_counter);
                                if(rec->rec_pmt == D_FALSE && rec ->pmt_got)
                                {
                                    ts2net_record_deal_data(rec, (D_U8*)rec->pmt_tsbuf, (D_Size)188, D_TRUE, 50);
                                    ts_counter_add(rec->pmt_tsbuf, rec->pmt_counter);
                                }
                            }
                        }
                    }
#if TS2NET_DEBUG_EN
                    else
                    {
                        D_DUMP("[Ts2NetRec]: dev%d DataDealFunction addr %x len %d, ret %d\n", devid, read_addr, len2send, ret_deal);
                    }
#endif
                }
#if TS2NET_DEBUG_EN
                else if(len2send == 0)
                {
                    D_DUMP("[Ts2NetRec]: dev%d w %x, r %x, len %d, send %d, %d, no deal !!!!\n", devid, producer, consumer, read_len, len2send, rec->packet_remain_size);
                }
#endif
            }
        }
        break;
        case D_MSG_APP_DESTROY:
            if(Ts2NetRecDev)
            {
                for(devid = 0; devid < TS2NET_DEV_CNT; devid++)
                {
                    rec = &Ts2NetRecDev[devid];
                    ts2net_record_stop(rec, devid);
                }
            }
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
ts2net_record_create(void) D_FUNCPOSTFIT
{
    D_Result ret = D_OK;

    if(happ_ts2net_record == D_INVALID_HANDLE)
    {
        if(D_OK == p_ts2net_record_open())
        {
            happ_ts2net_record = d_app_create("Ts2NetRec", D_PVR_REC_TASK_PRIO, D_PVR_REC_TASK_STACK_SIZE, D_PVR_REC_QUEUE_SIZE, ts2net_record_callback, (D_Ptr)Ts2NetRecDev);
            if(happ_ts2net_record != D_INVALID_HANDLE)
            {
                /*同步，等待设备创建完成*/
                d_app_sync(happ_ts2net_record);
                D_DUMP("[Ts2NetRec]:record app create ok!!\n");
                ret = D_OK;
            }
        }

        if(happ_ts2net_record == D_INVALID_HANDLE)
        {
            D_DUMP("[Ts2NetRec]:record app create error!!\n");
            ret = D_ERR;
        }
    }
    return ret;
}

/** @brief 应用交互任务注销
* @return 成功返回D_OK
*/
static D_Result
ts2net_record_destroy(void) D_FUNCPOSTFIT
{
    D_U32 devid;

    if(happ_ts2net_record != D_INVALID_HANDLE)
    {
        d_app_destroy(happ_ts2net_record);
        happ_ts2net_record = D_INVALID_HANDLE;
        D_DUMP("[Ts2NetRec]:record app destroy !!\n");
    }

    for(devid = 0; devid < TS2NET_DEV_CNT; devid++)
    {
        ts2net_record_dev_free(devid);
    }

    return D_OK;
}

/** @brief 开始ts2net录制
* @param[in] user_id 用户标识号，用户自己维护。与stop时匹配
* @param[in] dbsrvid 录制的节目的dbsrvid
* @param[in] cb 录制数据处理回调，返回处理的结果，负数是错误代码，0或正数是处理的字节数
* @param cb_data 回调注册传入参数, 回调函数会带入此参数，可以是user_id
* @return 成功返回D_OK
*/
D_Result p_ts2net_record_start(D_U32 user_id, D_ID dbsrvid, D_Ts2NetDataCBFunc cb, D_U32 cb_data) D_FUNCPOSTFIT
{
    D_Result ret = D_OK;
    D_DBSrvInfo srvinfo;
    D_VidInput      input;

    /*业务有效性检查*/
    if(D_OK != d_dbase_get_srv_info(dbsrvid, &srvinfo))
    {
        return D_ERR;
    }

    input = p_conf_get_vid_input ();
#if 0
    if(input == D_VID_IUTPUT_DTV)
    {
        /*DTV下，只能录制当前频点下的频道*/
        if(srvinfo.db_ts_id != d_tv_get_curr_db_ts_id())
        {
            return D_ERR;
        }
    }
#endif

    if(input == D_VID_IUTPUT_DTV)
    {
        cur_dtv_dbsrvid = p_stb_player_get_curr_srv(0);
    }
    else
    {
        cur_dtv_dbsrvid = -1;
    }

    /*检查创建交互app*/
    if(D_OK != ts2net_record_create())
    {
        return D_ERR;
    }

    ts2net_record_lock();

    /*检查用户量是否已满*/
    if(TS2NET_DEV_CNT <=  ts2net_record_get_dev(user_id))
    {
        ret = D_ERR_NO_DEV;
    }
    else
    {
        D_UserMsg msg;
        /*发送开始录制消息*/
        msg.type = D_MSG_PVR_REC_START;
        msg.handle = happ_ts2net_record;
        msg.param1 = user_id;
        msg.param2 = (D_U32)dbsrvid;
        msg.param3 = (D_U32)cb;
        msg.param4 = (D_U32)cb_data;
        d_app_send (msg.handle, (D_Msg*)&msg, sizeof(msg));
        ts2net_record_sync(happ_ts2net_record);
        D_DUMP("[Ts2NetRec]:p_ts2net_record_start %d\n", user_id);
    }
    ts2net_record_unlock();
    return ret;
}

/** @brief ts2net 停止录制函数
* @param[in] user_id 用户标识号，用户自己维护。与start时匹配
* @return  成功返回D_OK,失败返回D_ERR
*/
D_Result p_ts2net_record_stop(D_U32 user_id)D_FUNCPOSTFIT
{
    ts2net_record_lock();
    if (happ_ts2net_record != D_INVALID_HANDLE)
    {
        D_UserMsg msg;
        msg.type = D_MSG_PVR_REC_STOP;
        msg.handle = happ_ts2net_record;
        msg.param1 = user_id;
        d_app_send (msg.handle, (D_Msg*)&msg, sizeof(msg));
        ts2net_record_sync(happ_ts2net_record);
    }
    D_DUMP("[Ts2NetRec]:p_ts2net_record_stop %d\n", user_id);
    ts2net_record_unlock();
    return D_OK;
}

/** @brief 初始化
* @return 成功返回D_OK
*/
D_Result p_ts2net_record_open(void) D_FUNCPOSTFIT
{
    if(hmutex_ts2net == D_INVALID_HANDLE)
    {
        hmutex_ts2net = d_mutex_create(NULL);
    }

    if(Ts2NetRecDev == NULL)
    {
        D_U32 idx;

        Ts2NetRecDev = d_mem_alloc(0, (TS2NET_DEV_CNT * sizeof(D_Ts2NetRecDevice)) + TS2NET_REC_PMT_MAX_SIZE);
        if(Ts2NetRecDev == NULL)
        {
            return D_ERR;
        }

        pmt_sec_buf = (D_U8*)((D_U32)Ts2NetRecDev + TS2NET_DEV_CNT * sizeof(D_Ts2NetRecDevice));
        memset(Ts2NetRecDev, 0x00, TS2NET_DEV_CNT * sizeof(D_Ts2NetRecDevice));
        for(idx = 0; idx < TS2NET_DEV_CNT; idx++)
        {
            Ts2NetRecDev[idx].handle = D_INVALID_HANDLE;
            Ts2NetRecDev[idx].hfman = D_INVALID_HANDLE;
            Ts2NetRecDev[idx].hpmt = D_INVALID_HANDLE;
            Ts2NetRecDev[idx].share_handle = D_INVALID_HANDLE;
            Ts2NetRecDev[idx].hcbman_interrupt = D_INVALID_HANDLE;
            Ts2NetRecDev[idx].hsem_record = D_INVALID_HANDLE;
            Ts2NetRecDev[idx].user_info.user_id = (D_U32) - 1;
            Ts2NetRecDev[idx].demux_id = (idx == 1) ? 0 : 1;
            Ts2NetRecDev[idx].dev_type = (idx < 2) ? TS2NET_DEV_TYPE_PVR : TS2NET_DEV_TYPE_PES;
            Ts2NetRecDev[idx].record_status = TS2NET_REC_STATUS_STOP;
        }
    }

    return D_OK;
}

/** @brief 反初始化
* @return 成功返回D_OK
*/
D_Result p_ts2net_record_close(void) D_FUNCPOSTFIT
{
    ts2net_record_lock();
    ts2net_record_destroy();
    if(Ts2NetRecDev)
    {
        d_mem_free(Ts2NetRecDev);
        Ts2NetRecDev = NULL;
    }
    ts2net_record_unlock();
    return D_OK;
}


/** @brief 电视机切换频道时调用，判断电视要播放的频道是否与当前录制的频道相同，
以便处理，避免同一路demux过滤相同的pid而失败的问题
* @return 成功返回D_OK
*/
D_Result p_ts2net_record_swich_channel(D_ID dbsrvid) D_FUNCPOSTFIT
{
    D_Result ret = D_OK;
    D_VidInput      input;
    D_Ts2NetRecDevice * rec0, *rec1;
    D_Ts2NetUserInfo userinfo;
    D_UserMsg msg;

    ts2net_record_lock();

    cur_dtv_dbsrvid = dbsrvid;
    if(TS2NET_DEV_CNT < 2 || Ts2NetRecDev == NULL || happ_ts2net_record == D_INVALID_HANDLE)
    {
        ret = D_OK;
        goto _check_end;
    }

    input = p_conf_get_vid_input ();
    if(input != D_VID_IUTPUT_DTV)
    {
        cur_dtv_dbsrvid = -1;
        ret = D_OK;
        goto _check_end;
    }


    rec0 = &Ts2NetRecDev[0];
    rec1 = &Ts2NetRecDev[1];
    /* 只有一路录制，则没有冲突*/
    if(rec1->record_status == TS2NET_REC_STATUS_STOP)
    {
        ret = D_OK;
        goto _check_end;
    }

    if(dbsrvid == rec1->user_info.dbsrvid && rec1->record_status == TS2NET_REC_STATUS_RECING && rec1->share_handle == D_INVALID_HANDLE)
    {
        if(dbsrvid != rec0->user_info.dbsrvid)
        {
            msg.type = D_MSG_PVR_REC_PAUSE;
            msg.handle = happ_ts2net_record;
            msg.param1 = 0;
            msg.param2 = 1;
            D_DUMP("[Ts2NetRec]: record pause %d %d!\n", msg.param1, msg.param2);
            d_app_send (msg.handle, (D_Msg*)&msg, sizeof(msg));
            ts2net_record_sync(happ_ts2net_record);

            /*信息交换*/
            ts2net_record_swap_info(rec0, rec1);

            /*重启录制*/
            msg.type = D_MSG_PVR_REC_RESUME;
            msg.handle = happ_ts2net_record;
            msg.param1 = 0;
            msg.param2 = 1;
            D_DUMP("[Ts2NetRec]: record resume %d %d!\n", msg.param1, msg.param2);
            d_app_send (msg.handle, (D_Msg*)&msg, sizeof(msg));
            ts2net_record_sync(happ_ts2net_record);
        }
        else
        {
            userinfo = rec1->user_info;
            msg.type = D_MSG_PVR_REC_STOP;
            msg.handle = happ_ts2net_record;
            msg.param1 = userinfo.user_id;
            D_DUMP("[Ts2NetRec]: record pause userid %d!\n", msg.param1);
            d_app_send (msg.handle, (D_Msg*)&msg, sizeof(msg));
            ts2net_record_sync(happ_ts2net_record);

            /*重启录制*/
            msg.type = D_MSG_PVR_REC_START;
            msg.handle = happ_ts2net_record;
            msg.param1 = userinfo.user_id;
            msg.param2 = (D_U32)userinfo.dbsrvid;
            msg.param3 = (D_U32)userinfo.cbfunc;
            msg.param4 = (D_U32)userinfo.cb_data;
            D_DUMP("[Ts2NetRec]: record resume  userid %d!\n", msg.param1);
            d_app_send (msg.handle, (D_Msg*)&msg, sizeof(msg));
            ts2net_record_sync(happ_ts2net_record);
        }
    }
    else if(dbsrvid != rec1->user_info.dbsrvid && rec1->record_status == TS2NET_REC_STATUS_PAUSE)
    {
        /*重启录制*/
        msg.type = D_MSG_PVR_REC_RESUME;
        msg.handle = happ_ts2net_record;
        msg.param1 = (D_U32)(-1);
        msg.param2 = 1;
        D_DUMP("[Ts2NetRec]: record resume %d %d!\n", msg.param1, msg.param2);
        d_app_send (msg.handle, (D_Msg*)&msg, sizeof(msg));
        ts2net_record_sync(happ_ts2net_record);
    }

_check_end:
    ts2net_record_unlock();
    return ret;
}

