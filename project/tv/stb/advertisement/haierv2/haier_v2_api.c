/** @file
* @brief  haier广告2.0版本
* @author huangq
* @date 2014-06-16 huangq:实现2.0版本haier广告功能，包括开机LOGO和信息条广告
*/
#include "dMMan.h"
#include "dMem.h"
#include "dMsg.h"
#include "dResource.h"
#include "dTimer.h"
#include "dDebug.h"
#include "dSI.h"
#include "dDescr.h"
#include "dSIParse.h"
#include "dApp.h"
#include "dDate.h"
#include "dDBase.h"
#include "dProgScan.h"
#include <string.h>
#include <stdarg.h>
#include "dTV.h"
#include "pPlayer.h"
#include "dNVPart.h"
#include "dDBaseInternal.h"
#include "pMonitorRegister.h"
#include "dCBMan.h"
#include "pConfig.h"
#include "dMonitorTable.h"
#include "pCustomConfig.h"
#include "pSIParse.h"
#include "dSem.h"
#include "dSys.h"
#include "dEvent.h"
#include "dDemux.h"
#include "dNVRam.h"
#include "dGDev.h"
#include "dTypes.h"
#include "dadporting.h"
#include "dad_data_store.h"
#include "dTask.h"
#include "dScan.h"
#include "dQueue.h"
#include "dCrc.h"
#include "haier_v2_ad_api.h"
#include "dad_data_store.h"

#define HIV2AD_API_PRINT_EN 1

#if HIV2AD_API_PRINT_EN
#define HIV2AD_API_DUMP D_DUMP
#define HIV2AD_API_ERROR D_ERROR
#else
#define HIV2AD_API_DUMP(_s,...)
#define HIV2AD_API_ERROR(_s,...)
#endif


#define D_HIV2_DEMUX_MAX            5  //最多的DEMUX数目
#define D_HIV2_FILTER_MAX       5 //最多的FILTER数目
#define D_HIV2_MAX_AD               (0x20)//最多支持的组
#define D_HIV2_MAX_PIC_MAX   (0x20) //每组最多图片数
#define PICTURE_MAX_NUM         100//图片资源个数
#define D_HIV2_FULL_MAX            5  //单个最多的挂角数目

#define D_HIV2_VER_TAG                  0x55AA//用来判断从falsh中读到的数据是否是该广告数据

#define D_HIV2_TIMER_HIDEGIF   0x55
#define D_HIV2_TIMER_SHOWGIF   0x66

/**  Definitions *************************************************************/
typedef struct                                          //单条广告信息
{
    play_paras_t        play_paras;                         //广告显示参数
    D_U8                area_code_num;                      //广告关联的区域ID的个数
    D_U32               area_code[MAX_AREA_CODE_NUM];       //关联的区域ID
    D_U8                link_pic_num;                       //广告关联的图片的数目
    D_U16               link_pic_id[AD_LINK_PIC_MAX_NUM];   //关联的图片(id)
    D_U8                ser_num;                        //广告关联的图片的数目
    service_id_info_t   service[AD_LINK_SERV_MAX_NUM];
    D_U8                txt_num;                        //广告关联的图片的数目
    txt_res_info_t      txt[TXT_MAX_NUM];
} ad_des_info;

typedef struct                                          //单条广告信息
{
    D_U8                ser_num;                        //广告关联的图片的数目
    service_id_info_t   service[TOTAL_TXT_SERV_MAX_NUM];
    D_U8                txt_num;                        //广告关联的图片的数目
    hiv2ad_osd_show_info txt[TOTAL_TXT_MAX_NUM];
} txt_cont_info;

typedef struct                                  //广告控制表中描述的单条广告信息
{
    D_U16   ad_id;                      //广告id
    D_U8    flag;                           //广告类型
    D_U8    ad_version;                     //广告版本
    D_U8    ad_des_table_id;                //广告描述表的table_id
    D_U8    ad_type;                              //广告类型
    ad_des_info des;
} adlist_tb_desc;

typedef struct                                  //广告控制表信息
{
    D_U16   tag;                                            //广告id
    D_U8    cnt;                            //记录tb_desc的个数
    D_S8    ver;                                //广告列表的版本
    adlist_tb_desc  tb_desc[D_HIV2_MAX_AD];//广告列表的子描述表
} adlist_tb_info_t;

typedef struct                                      //广告总体信息
{
    D_U8            flag;                                                                           //广告类型
    D_U16           data_pid;                   //广告总个数
    D_U8            memory;                         //记录tb_desc的个数
    D_U16           pic_id;                         //记录tb_desc的个数
    pic_res_info_t  image;
} ad_pic_res_info;

typedef struct
{
    D_U8    cnt;
    D_U16   cur_pic_id;
    ad_pic_res_info res[PIC_MAX_NUM];
} ad_pic_res_info_t;

/** @brief haier 广告播放参数*/
typedef struct                                          //单条广告显示参数
{
    D_U16       pic_id;
    D_HTimer    htimer;
    D_hiv2_fullscan  info;
    D_U32       times;
} fullscan_timer_t;

/** @brief AD搜索资源*/
typedef struct
{
    D_U8                *buf;            /**@brief < 为搜索分配的内存地址*/
    D_U8                *sec;            /**@brief < 过滤demux接收的数据*/
    D_HMMan             hmm;            /**@brief < 为搜索分配的内存创建的内存管理器句柄*/
    D_HNVPart           hnvp;
    D_HApp              happ;           /**@brief< 搜索应用句柄*/
    D_HQueue            queue;          /**@brief< 消息队列句柄*/
    D_Size              buf_size;       /**< 解复用设备缓冲区大小*/
    D_HSem              sem;            /**@brief< 信号量句柄*/
    ADEVENTCALLBACK     cb;
    D_HDemux            AdvDemux[HIV2AD_PID_TYPE_MAX_NUM];   /**@brief<广告的DEMUX>*/
    D_TabMask           *ad_mask[HIV2AD_PID_TYPE_MAX_NUM];   /**@brief<广告表是否收齐>*/
    fullscan_timer_t     timer[D_HIV2_FULL_MAX];
    D_U8                    ad_version;                     //广告版本
    D_U8                    useflag;                                                                           //广告类型
    D_U8                    txtuseflag;                                                                           //广告类型
    hiv2ad_program_para   curprog;
    adlist_tb_info_t        adlist;
    ad_pic_res_info_t       pic_res;
    adlist_tb_info_t        oldlist;
    ad_pic_res_info_t       oldpic_res;
    txt_cont_info           txt_cont;//每次搜索完TXT之后保存到该变量中
    adlist_tb_info_t        storelist;//用于组织保持的版本信息
} d_hiv2ad_esdata;

#define D_HIV2_AD_MEM_SIZE (0x200000+(sizeof (d_hiv2ad_esdata)))
#define D_HIV2AD_SCAN_SEC_BUF_SIZE (0x1000)   /**@brief ad section缓冲区大小*/
#define D_HIV2AD_SCAN_PES_BUF_SIZE (0x10000)
#define D_HIV2AD_DEMUX_PSIBUF_SIZE (0x10000)
#define D_HIV2AD_DEMUX_PESBUF_SIZE (0x80000)


static D_HApp   happ = D_INVALID_HANDLE;/**@brief< 搜索应用句柄*/
static d_hiv2ad_esdata *hiv2adapies = NULL;
static void d_FullScanTimerCallback(D_AdFunBack *param, D_U8* sec, D_U32 len);

static void set_pic_eraseflag(d_hiv2ad_esdata *es)D_FUNCPOSTFIT
{
    D_Ad_Event_Param param;

    param.param.param1 = DAD_STB_BANNER;
    es->cb(DAD_EVENT_ERASE_DATA, &param);
    param.param.param1 = DAD_STB_VOLUME;
    es->cb(DAD_EVENT_ERASE_DATA, &param);
    param.param.param1 = DAD_STB_MENU;
    es->cb(DAD_EVENT_ERASE_DATA, &param);
    param.param.param1 = DAD_STB_EPG;
    es->cb(DAD_EVENT_ERASE_DATA, &param);
    param.param.param1 = DAD_STB_ProgramList;
    es->cb(DAD_EVENT_ERASE_DATA, &param);

}
static void set_osd_eraseflag(d_hiv2ad_esdata *es)D_FUNCPOSTFIT
{
    D_Ad_Event_Param param;

    param.param.param1 = DAD_STB_OSD;
    es->cb(DAD_EVENT_ERASE_DATA, &param);

}
static void set_full_eraseflag(d_hiv2ad_esdata *es)D_FUNCPOSTFIT
{
    D_Ad_Event_Param param;

    param.param.param1 = DAD_STB_FULLSCREEN;
    es->cb(DAD_EVENT_ERASE_DATA, &param);

}
static void set_pic_update(d_hiv2ad_esdata *es)D_FUNCPOSTFIT
{
    D_Ad_Event_Param param;

    param.param.param1 = DAD_STB_BANNER;
    es->cb(DAD_EVENT_UPDATE_DATA, &param);
    param.param.param1 = DAD_STB_VOLUME;
    es->cb(DAD_EVENT_UPDATE_DATA, &param);
    param.param.param1 = DAD_STB_MENU;
    es->cb(DAD_EVENT_UPDATE_DATA, &param);
    param.param.param1 = DAD_STB_EPG;
    es->cb(DAD_EVENT_UPDATE_DATA, &param);
    param.param.param1 = DAD_STB_ProgramList;
    es->cb(DAD_EVENT_UPDATE_DATA, &param);

}
static void set_osd_update(d_hiv2ad_esdata *es)D_FUNCPOSTFIT
{
    D_Ad_Event_Param param;

    param.param.param1 = DAD_STB_OSD;
    es->cb(DAD_EVENT_UPDATE_DATA, &param);

}
static void set_full_update(d_hiv2ad_esdata *es)D_FUNCPOSTFIT
{
    D_Ad_Event_Param param;

    param.param.param1 = DAD_STB_FULLSCREEN;
    es->cb(DAD_EVENT_UPDATE_DATA, &param);

}

D_Result set_full_timer(D_U16 pic_id, D_hiv2_fullscan *info, D_U32 times1, D_U32 times2, D_U32 ctrl)D_FUNCPOSTFIT
{
    D_U8 i;
    D_Ad_Event_Param param;
    D_HTimer        fullscantimer;

    if(hiv2adapies == NULL)
    {
        return D_ERR;
    }
    for(i = 0; i < D_HIV2_FULL_MAX ; i ++)
    {
        if((hiv2adapies->timer[i].htimer != D_INVALID_HANDLE) && \
        (hiv2adapies->timer[i].pic_id == pic_id))
        {
            param.htimer = (D_U32)hiv2adapies->timer[i].htimer;
            hiv2adapies->cb(DAD_EVENT_DESTROY_TIMER, &param);
            hiv2adapies->timer[i].htimer = D_INVALID_HANDLE;
        }
    }

    param.starttime = times1;
    param.param.param1 = ctrl;
    param.param.param2 =  pic_id;
    param.Function = d_FullScanTimerCallback;
    param.one_shot = 1;

    fullscantimer = hiv2adapies->cb(DAD_EVENT_CREATE_TIMER, &param);
    if(D_INVALID_HANDLE == fullscantimer)
    {
        return D_ERR;
    }
    for(i = 0; i < D_HIV2_FULL_MAX ; i ++)
    {
        if(hiv2adapies->timer[i].htimer == D_INVALID_HANDLE)
        {
            hiv2adapies->timer[i].htimer = fullscantimer;
            hiv2adapies->timer[i].pic_id = pic_id;
            hiv2adapies->timer[i].times = times2;
            memcpy((D_U8*) & (hiv2adapies->timer[i].info), (D_U8*)info, sizeof(D_hiv2_fullscan));
            return D_OK;
        }
    }
    return D_ERR;
}

/** @brief  d_mtr_ad_FullScanTimerCallback
* @param[in] D_AdFunBack *param   注释
* @param[in] D_U8* sec            注释
* @param[in] D_U32 len            注释
* @retval D_OK  成功
* @retval D_ERR  失败
* @note 注解
*/
static void d_FullScanTimerCallback(D_AdFunBack *param, D_U8* sec, D_U32 len)
{
    D_U8 i;

    if(param != NULL)
    {
        if(param->param1 == D_HIV2_TIMER_HIDEGIF)//挂角消失的定时器
        {
            D_Ad_Event_Param tparam;
            D_hiv2_fullscan  pucmsg;

            pucmsg.id = param->param2;
            d_hiv2ad_ShowMessage(HIV2AD_MSEEAGE_HIDEFULLSRCEEN_TYPE, (D_U8*)&pucmsg);
            for(i = 0; i < D_HIV2_FULL_MAX ; i ++)
            {
                if((hiv2adapies->timer[i].htimer != D_INVALID_HANDLE) && \
                   (hiv2adapies->timer[i].pic_id == pucmsg.id) && \
                   (hiv2adapies->timer[i].times != 0))
                {
                    hiv2adapies->timer[i].htimer = D_INVALID_HANDLE;
                    tparam.starttime = hiv2adapies->timer[i].times;
                    tparam.param.param1 = D_HIV2_TIMER_SHOWGIF ;
                    tparam.param.param2 = param->param2;
                    tparam.Function = d_FullScanTimerCallback;
                    tparam.one_shot = 1;

                    hiv2adapies->timer[i].htimer = hiv2adapies->cb(DAD_EVENT_CREATE_TIMER, &tparam);
                    if(D_INVALID_HANDLE == hiv2adapies->timer[i].htimer)
                    {
                        return;
                    }
                }
            }
        }
        else if(param->param1 == D_HIV2_TIMER_SHOWGIF)//挂角重新显示的定时器
        {
            D_hiv2_fullscan  pucmsg;
            pucmsg.id = param->param2;
            for(i = 0; i < D_HIV2_FULL_MAX ; i ++)
            {
                if((hiv2adapies->timer[i].htimer != D_INVALID_HANDLE) && \
                   (hiv2adapies->timer[i].pic_id == pucmsg.id))
                {
                    memcpy((D_U8*)&pucmsg, (D_U8*) & (hiv2adapies->timer[i].info), sizeof(D_hiv2_fullscan));
                    d_hiv2ad_ShowMessage(HIV2AD_MSEEAGE_SHOWFULLSRCEEN_TYPE, &pucmsg);
                    set_full_timer(pucmsg.id, &pucmsg, pucmsg.duration * 1000, 10000, D_HIV2_TIMER_HIDEGIF);
                }
            }
        }
    }
}
D_Result clear_full_timer(void)D_FUNCPOSTFIT
{
    D_U8 i;
    D_Ad_Event_Param param;

    if(hiv2adapies == NULL)
    {
        return D_ERR;
    }
    for(i = 0; i < D_HIV2_FULL_MAX ; i ++)
    {
        if(hiv2adapies->timer[i].htimer != D_INVALID_HANDLE)
        {
            param.htimer = (D_U32)hiv2adapies->timer[i].htimer;
            hiv2adapies->cb(DAD_EVENT_DESTROY_TIMER, &param);
            hiv2adapies->timer[i].htimer = D_INVALID_HANDLE;
        }
    }
    return D_OK;
}

static ad_pic_res_info * get_data_info_by_id(ad_pic_res_info_t* info, D_U16 id)D_FUNCPOSTFIT
{
    D_U8    i = 0;
    for(i = 0; i < info->cnt; i++)
    {
        if(info->res[i].pic_id == id)
            return &(info->res[i]);
    }
    return NULL;
}

static D_Result hiv2ad_get_fullscan_by_prog( hiv2ad_program_para *prog)D_FUNCPOSTFIT
{
    D_U8 i, j, k, listcnt, piccnt, sercnt;
    ad_des_info *des;
    d_hiv2ad_esdata *es = hiv2adapies;
    adlist_tb_info_t *list = &hiv2adapies->oldlist;
    HIV2_Ad_Pos_Type HiAd_type = HIV2AD_STB_FULLSCREEN;

    d_sem_wait (es->sem);
    if(es->useflag == 0)
    {
        d_sem_post (es->sem);
        return D_ERR;
    }
    listcnt = list->cnt;

    for(i = 0; i < listcnt; i++)
    {
        if(list->tb_desc[i].ad_type == HiAd_type)
        {
            des = &(list->tb_desc[i].des);
            piccnt = des->link_pic_num;
            sercnt = des->ser_num;
            for(j = 0; j < piccnt; j++)
            {
                D_U16  link_pic_id = des->link_pic_id[j];
                for(k = 0; k < sercnt; k++)
                {
                    D_U16   service_id = des->service[k].service_id; //指定服务ID
                    D_U16   pic_id = des->service[k].pic_id;        //对应的广告ID,txt时候对应TXTID
                    if(pic_id == link_pic_id)
                    {
                        if((service_id == 0) || (prog->usServiceId == service_id))
                        {
                            //满足条件
                            break;
                        }
                    }
                }
                if((k == sercnt) && (sercnt != 0)) //不满足条件
                {
                    continue;
                }
                else //找到对应的图片
                {
                    ad_pic_res_info *resinfo;
                    D_hiv2_fullscan  pucmsg;
                    resinfo =  get_data_info_by_id(&es->oldpic_res, link_pic_id);
                    if((resinfo == NULL) || (resinfo->flag == 0))
                    {
                        continue;
                    }
                    pucmsg.id = link_pic_id;          /*图片ID       */
                    pucmsg.data_type = DAD_PIC_DATA;   /*图片类型*/
                    pucmsg.data_ptr = resinfo->image.image;    /*图片数据指针*/
                    pucmsg.data_len = resinfo->image.pic_length;    /*图片数据长度*/
                    pucmsg.erase = 0;   /*图片擦除*/
                    pucmsg.left = des->play_paras.posx;    /*图片左边距*/
                    pucmsg.top = des->play_paras.posy;     /*图片上边距*/
                    pucmsg.duration = des->play_paras.duration;     /*图片上边距*/
                    d_hiv2ad_ShowMessage(HIV2AD_MSEEAGE_SHOWFULLSRCEEN_TYPE, &pucmsg);
                    set_full_timer(link_pic_id, &pucmsg, pucmsg.duration * 1000, 10000, D_HIV2_TIMER_HIDEGIF);
                }
            }
        }
    }
    d_sem_post (es->sem);
    return D_ERR;
}

/** @brief  判断接收下来的图片数据是否有效
* @param[in] D_U8 *_SectionData  图片数据
* @return 成功返回D_OK,失败返回D_ERR
*/
static D_Result check_picdata_valid(D_U8 *_SectionData)D_FUNCPOSTFIT
{
    D_U32   pic_tag;
    D_U32   pic_end_tag;
    D_U32   pic_data_length;

    pic_tag = (D_U32)_SectionData[6] << 24;
    pic_tag |= (D_U32)_SectionData[7] << 16;
    pic_tag |= (D_U32)_SectionData[8] << 8;
    pic_tag |= (D_U32)_SectionData[9];
    if(pic_tag != 0x55aa)
    {
        HIV2AD_API_ERROR("PIC ERR! pic_tag != 0x55aa\n");
        return D_ERR;
    }
    _SectionData += 30;
    pic_data_length = ((D_U32)_SectionData[0]) << 24;
    pic_data_length |= ((D_U32)_SectionData[1]) << 16;
    pic_data_length |= ((D_U32)_SectionData[2]) << 8;
    pic_data_length |= ((D_U32)_SectionData[3]);

    _SectionData += (pic_data_length + 4);

    pic_end_tag = ((D_U32)_SectionData[0]) << 24;
    pic_end_tag |= ((D_U32)_SectionData[1]) << 16;
    pic_end_tag |= ((D_U32)_SectionData[2]) << 8;
    pic_end_tag |= ((D_U32)_SectionData[3]);
    if(pic_end_tag != 0xaa55)
    {
        HIV2AD_API_ERROR("PIC ERR! pic_end_tag != 0xaa55\n");
        return D_ERR;
    }

    return D_OK;
}


/** @brief  按广告描述表类型关闭对应过滤器
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
static D_Result stop_filter( d_hiv2ad_esdata* es, D_U8 Adv_des_type )D_FUNCPOSTFIT
{
    D_U8 type;
    type = Adv_des_type;

    d_demux_stop(es->AdvDemux[type]);
    d_demux_destroy(es->AdvDemux[type]);
    es->AdvDemux[type] = D_INVALID_HANDLE;

    return D_OK;
}


/** @brief  设置数据过滤条件
* @param[in] es  资源指针
* @return 成功返回D_OK,失败返回D_ERR
*/
static D_Result start_filter(d_hiv2ad_esdata *es, D_S8 version, D_U8 Adv_des_type)D_FUNCPOSTFIT
{
    D_DemuxAttr      dmx_attr;
    D_DemuxFilter    filter;
    D_U8 type = Adv_des_type;
    D_U8    i = 0;

    D_DEMUX_ATTR_INIT (&dmx_attr);
    if(type == HIV2AD_PID_TYPE_ADLIST || type == HIV2AD_PID_TYPE_DESCRIPTOR)
    {
        dmx_attr.type = D_DEMUX_SEC;
        dmx_attr.buf_size = D_HIV2AD_DEMUX_PSIBUF_SIZE;
    }
    else if(type == HIV2AD_PID_TYPE_PIC_DATA)
    {
        dmx_attr.type = D_DEMUX_PES;
        dmx_attr.buf_size = D_HIV2AD_DEMUX_PESBUF_SIZE;
    }
    es->AdvDemux[type] = d_demux_create(&dmx_attr, es->queue);

    if(D_INVALID_HANDLE == es->AdvDemux[type])
    {
        HIV2AD_API_ERROR ("d_demux_create PicAdvDemuxCon error\n");
        return D_ERR;
    }

    memset ((&filter), 0, sizeof (D_DemuxFilter));
    if(type == HIV2AD_PID_TYPE_ADLIST)
    {
        d_sec_filter_set_pid (&filter, 0x26);
        d_sec_filter_set_tid (&filter, 0xf0);

        if(version != -1)
        {
            filter.sec.filter[5] = (D_U8)(version << 1);
            filter.sec.mask[5] = 0x3e;
            filter.sec.positive[5] |= 1;
        }
        filter.sec.length = 16;
        if(d_demux_set_filter(es->AdvDemux[type], &filter) < 0)
        {
            HIV2AD_API_ERROR ("Cannot set sch eit filter\n");
            d_demux_destroy(es->AdvDemux[type]);
            es->AdvDemux[type] = D_INVALID_HANDLE;
            return D_ERR;
        }
        d_tab_mask_clear(es->ad_mask[type]);
        d_demux_start(es->AdvDemux[type]);
        return D_OK;
    }
    else if(type == HIV2AD_PID_TYPE_DESCRIPTOR)
    {
        d_sec_filter_set_pid (&filter, 0x26);
        for(i = 0; i < es->adlist.cnt; i++)
        {
            if(es->adlist.tb_desc[i].flag == 0)
            {
                d_sec_filter_set_tid (&filter, es->adlist.tb_desc[i].ad_des_table_id);
                filter.sec.filter[3] = (D_U16)es->adlist.tb_desc[i].ad_id >> 8;       /*adv_id高八位*/
                filter.sec.mask[3] = 0xff;
                filter.sec.filter[4] = (D_U16)es->adlist.tb_desc[i].ad_id & 0x00ff;   /*adv_id低八位*/
                filter.sec.mask[4] = 0xff;
                filter.sec.filter[5] = (D_U8)(es->adlist.tb_desc[i].ad_version << 1);
                filter.sec.mask[5] = 0x3e;
                filter.sec.length = 16;
                if(d_demux_set_filter(es->AdvDemux[type], &filter) < 0)
                {
                    HIV2AD_API_ERROR ("Cannot set sch eit filter\n");
                    d_demux_destroy(es->AdvDemux[type]);
                    es->AdvDemux[type] = D_INVALID_HANDLE;
                    return D_ERR;
                }
                d_tab_mask_clear(es->ad_mask[type]);
                d_demux_start(es->AdvDemux[type]);
                es->adlist.tb_desc[i].flag = 1;
                return D_OK;
            }
        }
    }
    else if(type == HIV2AD_PID_TYPE_PIC_DATA)
    {
        D_U16 pic_pid;
        for(i = 0; i < es->pic_res.cnt; i++)
        {
            if(es->pic_res.res[i].flag == 0)
            {
                pic_pid = es->pic_res.res[i].data_pid;
                d_sec_filter_set_pid (&filter, pic_pid);
                filter.sec.filter[4] = (D_U16)es->pic_res.res[i].pic_id >> 8;           /*pic_id高八位*/
                filter.sec.mask[4] = 0xff;
                filter.sec.filter[5] = (D_U16)es->pic_res.res[i].pic_id & 0x00ff;   /*pic_id低八位*/
                filter.sec.mask[5] = 0xff;
                if(d_demux_set_filter(es->AdvDemux[type], &filter) < 0)
                {
                    HIV2AD_API_ERROR ("Cannot set sch eit filter\n");
                    d_demux_destroy(es->AdvDemux[type]);
                    es->AdvDemux[type] = D_INVALID_HANDLE;
                    return D_ERR;
                }
                d_tab_mask_clear(es->ad_mask[type]);
                d_demux_start(es->AdvDemux[type]);
                es->pic_res.res[i].flag = 1;
                es->pic_res.cur_pic_id = es->pic_res.res[i].pic_id;
                return D_OK;
            }
        }
    }

    d_demux_destroy(es->AdvDemux[type]);
    es->AdvDemux[type] = D_INVALID_HANDLE;
    return D_ERR;
}


static D_Result init_descriptor(d_hiv2ad_esdata* es)
{
    D_U8    i = 0;
    for(i = 0; i < es->adlist.cnt; i++)
    {
        es->adlist.tb_desc[i].flag = 0;
        es->adlist.tb_desc[i].des.area_code_num = 0;
        es->adlist.tb_desc[i].des.link_pic_num = 0;
        es->adlist.tb_desc[i].des.ser_num = 0;
        es->adlist.tb_desc[i].des.txt_num = 0;
    }
    return D_OK;
}
static D_Result init_resource(d_hiv2ad_esdata* es)
{
    D_U8    i = 0;
    for(i = 0; i < es->pic_res.cnt; i++)
    {
        if(es->pic_res.res[i].image.image != NULL)
        {
            d_mman_free (es->hmm, es->pic_res.res[i].image.image);
            es->pic_res.res[i].image.image = NULL;
        }
        es->pic_res.res[i].image.flag = 0;
        es->pic_res.res[i].flag = 0;
    }

    return D_OK;
}

static D_Result add_pic_source(d_hiv2ad_esdata* es, ad_pic_res_info *info)
{
    D_U8        i = 0;

    for(i = 0; i < es->pic_res.cnt; i++)
    {
        if(info->pic_id == es->pic_res.res[i].pic_id)
        {
            return D_OK;
        }
    }
    es->pic_res.res[i].data_pid = info->data_pid ;
    es->pic_res.res[i].pic_id = info->pic_id;
    es->pic_res.res[i].memory = info->memory;
    es->pic_res.cnt++;
    return D_OK;
}
static D_Ad_Pos_Type switch_pic_type(HIV2_Ad_Pos_Type type)
{
    switch(type)
    {
        case HIV2AD_STB_LOG:                //0 开机广告
            return DAD_STB_LOG;
        case HIV2AD_STB_BANNER:                     //1换台吧
            return DAD_STB_BANNER;
        case HIV2AD_STB_VOLUME:                     //2音量条
            return DAD_STB_VOLUME;
        case HIV2AD_STB_MENU:                           //3主菜单
            return DAD_STB_MENU;
        case HIV2AD_STB_PROGRAM_LIST:       //4节目列表
            return DAD_STB_ProgramList;
        case HIV2AD_STB_EPG:                            //5 EPG广告
            return DAD_STB_EPG;
        case HIV2AD_STB_RADIO_BACK:             //6 广播背景
            return DAD_STB_RadioBackGround;
        case HIV2AD_STB_NOSIGNAL:               //7 无信号
            return DAD_STB_Nosignal;
        case HIV2AD_STB_NOPROGRAM:              //8 无节目
            return DAD_STB_NoProgram;
        case HIV2AD_STB_FULLSCREEN:             //9 挂角广告
            return DAD_STB_FULLSCREEN;
        case HIV2AD_STB_ROLL_TXT:       //10 滚动字幕广告
            return DAD_STB_OSD;
        case HIV2AD_STB_POS_UNKNOWN:            //11 未知类型
            return DAD_STB_POS_UNKNOWN;
    }
    return DAD_STB_POS_UNKNOWN;
}

static adlist_tb_desc * get_des_struct_by_id(d_hiv2ad_esdata* es, D_U16 id)D_FUNCPOSTFIT
{
    D_U8    i = 0;
    for(i = 0; i < es->adlist.cnt; i++)
    {
        if(es->adlist.tb_desc[i].ad_id == id)
            return &(es->adlist.tb_desc[i]);
    }
    return NULL;
}
static ad_pic_res_info * get_data_struct_by_id(d_hiv2ad_esdata* es, D_U16 id)D_FUNCPOSTFIT
{
    D_U8    i = 0;
    for(i = 0; i < es->pic_res.cnt; i++)
    {
        if(es->pic_res.res[i].pic_id == id)
            return &(es->pic_res.res[i]);
    }
    return NULL;
}
static D_Result flush_pic_data(d_hiv2ad_esdata* es, D_U8 ad_type)
{
    D_Ad_Img_Param img_param;
    D_U8        i, j, cnt;
    D_U16           pic_id;
    ad_pic_res_info *info;
    D_U8 del = 0;

    for(i = 0; i < es->adlist.cnt; i++)
    {
        if((es->adlist.tb_desc[i].ad_type == ad_type) && \
           (es->adlist.tb_desc[i].flag == 1))
        {
            cnt = es->adlist.tb_desc[i].des.link_pic_num;
            for(j = 0; j < cnt; j++)
            {
                pic_id = es->adlist.tb_desc[i].des.link_pic_id[j];
                info = get_data_struct_by_id(es, pic_id);
                if(info)
                {
                    if(del == 0)
                    {
                        d_ad_store_delete_by_type(switch_pic_type(ad_type));
                        del = 1;
                    }
                    img_param.id = pic_id;
                    img_param.imgType = info->image.img_type;// 图片类型
                    img_param.times = es->adlist.tb_desc[i].des.play_paras.duration * 1000;      // img显示时间 100ms
                    img_param.left = es->adlist.tb_desc[i].des.play_paras.posx;     // img显示相对坐标
                    img_param.top = es->adlist.tb_desc[i].des.play_paras.posy;          // img显示相对坐标
                    img_param.width = info->image.pic_width;      // img显示宽度
                    img_param.height = info->image.pic_height;     // img显示高度
                    img_param.buf = info->image.image;          // img数据区指针
                    img_param.img_size = info->image.pic_length;    // img数据大小
                    if(d_ad_store_insert_by_type(switch_pic_type(ad_type), &img_param) != D_OK)
                    {
                        HIV2AD_API_ERROR (" hiv2ad	d_ad_store_insert_by_type ERROR \n");
                        return D_ERR;
                    }
                }
            }
            memcpy((D_U8*) & (es->storelist.tb_desc[es->storelist.cnt]), (D_U8*) & (es->adlist.tb_desc[i]), sizeof(adlist_tb_desc));
            es->storelist.cnt += 1;
        }
    }
    return D_OK;
}
static D_Result flush_txt_data(d_hiv2ad_esdata* es)
{
    D_U8        i, j, cnt;
    hiv2ad_osd_show_info *destxt;
    txt_res_info_t *srctxt;

    for(i = 0; i < es->txt_cont.txt_num; i++)
    {
        if(es->txt_cont.txt[i].pucDisplayBuffer != NULL)
        {
            d_mman_free (es->hmm, es->txt_cont.txt[i].pucDisplayBuffer);
            es->txt_cont.txt[i].pucDisplayBuffer = NULL;
        }
    }
    memset((D_U8*)&es->txt_cont, 0, sizeof(txt_cont_info));
    for(i = 0; i < es->adlist.cnt; i++)
    {
        if((es->adlist.tb_desc[i].ad_type == HIV2AD_STB_ROLL_TXT) && \
           (es->adlist.tb_desc[i].flag == 1))
        {
            cnt = es->adlist.tb_desc[i].des.txt_num;
            for(j = 0; j < cnt; j++)
            {
                srctxt = &(es->adlist.tb_desc[i].des.txt[j]);
                destxt = &(es->txt_cont.txt[es->txt_cont.txt_num]);
                destxt->txtId = srctxt->txt_id;//背景颜色
                destxt->aucBackgroundColor = srctxt->back_color; //背景颜色
                destxt->aucDisplayColor = srctxt->font_color; //字体颜色
                destxt->usContentSize = srctxt->txt_length;      //osd内容长度
                destxt->usGetBufferSize = srctxt->txt_length;
                destxt->pucDisplayBuffer = srctxt->content;   //osd内容
                destxt->ucFontType = 0;           //字体类型
                destxt->ucFontSize = srctxt->font_size;           //字体大小
                destxt->txtSpeed = srctxt->txt_speed;                       //总数
                destxt->ucShowTimes = es->adlist.tb_desc[i].des.play_paras.duration;          //显示次数
                destxt->ucstartposx = es->adlist.tb_desc[i].des.play_paras.posx;                        //总数
                destxt->ucstartposy = es->adlist.tb_desc[i].des.play_paras.posy;                        //总数
                destxt->ucendposx = es->adlist.tb_desc[i].des.play_paras.disp_w;                        //总数
                destxt->ucendposy = es->adlist.tb_desc[i].des.play_paras.disp_h;                        //总数
                destxt->scrollend = 0;          //显示次数
                es->txt_cont.txt_num ++;
            }
            es->adlist.tb_desc[i].des.txt_num = 0;
            cnt = es->adlist.tb_desc[i].des.ser_num;
            for(j = 0; j < cnt; j++)
            {
                memcpy((D_U8*) & (es->txt_cont.service[es->txt_cont.ser_num]), (D_U8*) & (es->adlist.tb_desc[i].des.service[j]), sizeof(service_id_info_t));
                es->txt_cont.ser_num ++;
            }
            es->adlist.tb_desc[i].des.ser_num = 0;
        }
    }
    return D_OK;
}

static D_Result flush_last_ver(adlist_tb_info_t* lastinfo, adlist_tb_info_t* info)
{
    D_U8        i;

    for(i = 0; i < lastinfo->cnt; i++)
    {
        if(lastinfo->tb_desc[i].flag == 1)
        {
            info->cnt += 1;
            memcpy((D_U8*) & (info->tb_desc[info->cnt]), (D_U8*) & (lastinfo->tb_desc[i]), sizeof(adlist_tb_desc));
        }
    }
    return D_OK;
}

static D_Result flush_ver_data( adlist_tb_info_t* info)
{
    D_Ad_Img_Param img_param;
    info->tag = D_HIV2_VER_TAG;
    img_param.id = 0;
    img_param.imgType = D_IMAGE_MPEG2_FRAME_I;// 图片类型
    img_param.buf = (D_U8 *)info;                   // img数据区指针
    img_param.img_size = sizeof(adlist_tb_info_t);       // img数据大小
    if(d_ad_store_insert_by_type(switch_pic_type(HIV2AD_STB_POS_UNKNOWN), &img_param) != D_OK)
    {
        HIV2AD_API_ERROR (" hiv2ad	d_ad_store_insert_by_type ERROR \n");
        return D_ERR;
    }
    return D_OK;
}
static D_Result set_cur_ver( adlist_tb_info_t* lastinfo, adlist_tb_info_t* info)
{
    memcpy((D_U8*)lastinfo, (D_U8*)info, sizeof(adlist_tb_info_t));
    return D_OK;
}
static D_Result set_cur_data( ad_pic_res_info_t* lastinfo, ad_pic_res_info_t* info)
{
    D_U8    i, j, found;
    for(i = 0; i < info->cnt; i++)
    {
        found = 0;
        for(j = 0; j < lastinfo->cnt; j++)
        {
            if(info->res[i].pic_id == lastinfo->res[j].pic_id)
            {
                found = 1;
                break;
            }
        }
        if(found == 0)
        {
            memcpy((D_U8*)(&lastinfo->res[lastinfo->cnt]), (D_U8*)(&info->res[i]), sizeof(ad_pic_res_info));
            lastinfo->cnt++;
        }
    }
    return D_OK;
}

static D_Result get_ver_data(adlist_tb_info_t* info)
{
    Ad_Data_Info *img_param;

    img_param = (Ad_Data_Info *)d_ad_store_get_by_type(switch_pic_type(HIV2AD_STB_POS_UNKNOWN), 0);
    if(img_param)
    {
        memcpy((D_U8*)info, (D_U8*)img_param->buffer, sizeof(adlist_tb_info_t));
        if(info->tag != D_HIV2_VER_TAG)
        {
            memset((D_U8*)info, 0, sizeof(adlist_tb_info_t));
        }
        return D_OK;
    }
    return D_ERR;
}
static D_Result get_old_pic_data(d_hiv2ad_esdata* es, adlist_tb_info_t* info, ad_pic_res_info_t* res)
{
    D_U8    i, j;
    D_U8    ad_type, cnt;
    Ad_Data_Info *pic;//广告类型

    for(i = 0; i < info->cnt; i++)
    {
        if(info->tb_desc[i].flag == 1)
        {
            ad_type = info->tb_desc[i].ad_type;
            switch(ad_type)
            {
                case HIV2AD_STB_LOG:                //0 开机广告
                case HIV2AD_STB_BANNER:             //1换台吧
                case HIV2AD_STB_VOLUME:             //2音量条
                case HIV2AD_STB_MENU:               //3主菜单
                case HIV2AD_STB_PROGRAM_LIST:       //4节目列表
                case HIV2AD_STB_EPG:                //5 EPG广告
                case HIV2AD_STB_RADIO_BACK:         //6 广播背景
                case HIV2AD_STB_NOSIGNAL:           //7 无信号
                case HIV2AD_STB_NOPROGRAM:          //8 无节目
                {
                    cnt = d_ad_store_get_img_count (switch_pic_type(ad_type));
                    if(cnt)
                    {
                        for(j = 0; j < cnt; j++)
                        {
                            pic = d_ad_store_get_by_type(switch_pic_type(ad_type), j);
                            if(pic)
                            {
                                res->res[res->cnt].pic_id = pic->item.id;
                                res->res[res->cnt].image.pic_id = pic->item.id;
                                res->res[res->cnt].image.img_type = pic->item.advType;      //图片类型
                                res->res[res->cnt].image.pic_width = pic->item.width;       //图片宽度
                                res->res[res->cnt].image.pic_height = pic->item.height;     //图片高度
                                res->res[res->cnt].image.pic_length = pic->item.img_size;       //广告数据长度
                                res->res[res->cnt].image.image = d_mman_alloc(es->hmm, pic->item.img_size + 1);
                                if(res->res[res->cnt].image.image == NULL)
                                {
                                    HIV2AD_API_DUMP(" malloc err!\n");
                                    return D_ERR;
                                }
                                memcpy(res->res[res->cnt].image.image, pic->buffer, pic->item.img_size);
                                res->res[res->cnt].flag = 1;
                                res->cnt++;
                                d_ad_store_free_mem(pic);
                            }
                        }
                    }
                }
            }
        }
    }
    return D_OK;
}
static D_Result del_disabled_des_data( adlist_tb_info_t* lastlist,  adlist_tb_info_t* newlist)
{
    D_U8    i, j, found = 0;

    for(i = 0; i < lastlist->cnt; i++)
    {
        if(lastlist->tb_desc[i].flag == 1)
        {
            found = 0;
            for(j = 0; j < newlist->cnt; j++)
            {
                if(newlist->tb_desc[j].ad_id == lastlist->tb_desc[i].ad_id)
                {
                    found = 1;
                    break;
                }
            }
            if(found == 0)//新的描述表里面未找到这个组,需要删除
            {
                lastlist->tb_desc[i].flag   = 0;
                d_ad_store_delete_by_type(switch_pic_type(lastlist->tb_desc[i].ad_type));
            }
        }
    }
    for(i = 0; i < lastlist->cnt; i++)
    {
        if(lastlist->tb_desc[i].flag == 0)
        {
            lastlist->cnt--;
            if(i != lastlist->cnt)
                memcpy((D_U8*) & (lastlist->tb_desc[i]), (D_U8*) & (lastlist->tb_desc[i + 1]), sizeof(adlist_tb_desc) * (lastlist->cnt - i));
        }
    }
    return D_OK;
}
static D_Result check_des_ver(adlist_tb_info_t* lastlist,  adlist_tb_info_t* newlist)
{
    D_U8    i, j;

    for(i = 0; i < lastlist->cnt; i++)
    {
        if(lastlist->tb_desc[i].flag == 1)
        {
            for(j = 0; j < newlist->cnt; j++)
            {
                if((newlist->tb_desc[j].ad_id == lastlist->tb_desc[i].ad_id) && \
                   (newlist->tb_desc[j].ad_version == lastlist->tb_desc[i].ad_version))
                {
                    memcpy((D_U8*) & (newlist->tb_desc[j]), (D_U8*) & (lastlist->tb_desc[i]), sizeof(adlist_tb_desc));
                    newlist->tb_desc[j].flag = 2;
                    break;
                }
            }
        }
    }
    return D_OK;
}

/** @brief 解析广告列表描述信息
* @param[in] d_hiv2ad_esdata es  任务资源数据
* @param[in] D_U8 type数据类型
* @retval D_OK  成功
* @retval D_ERR  失败
*/
static D_Result parse_adlist_data(d_hiv2ad_esdata* es, D_U8 type)
{
    D_U16   ad_num;
    D_U16   ad_id;
    D_S8    version_number;
    D_U8    SectionNo;
    D_U8    LastSectionNo;
    D_U32   desc_len, Descriptor_Parsed;
    D_U8    *SectionData = es->sec;

    ad_num = ((SectionData[3]) << 8) | (SectionData[4]);
    version_number = (SectionData[5] >> 1) & 0x1f;
    HIV2AD_API_DUMP("ad_num  = %d, version_number = %d!\n", ad_num, version_number);

    SectionNo = SectionData[6];//Section_number
    LastSectionNo = SectionData[7];

    if(version_number != es->ad_version)
    {
        d_tab_mask_clear(es->ad_mask[type]);
        memset((D_U8*)(&es->adlist), 0, sizeof(adlist_tb_info_t));
        es->adlist.cnt = 0;
    }

    if (d_tab_mask_is_set (es->ad_mask[HIV2AD_PID_TYPE_ADLIST], 0, 0, SectionNo ))
    {
        HIV2AD_API_ERROR (" hiv2ad  data section duplicated \n");
        return D_ERR;
    }
    es->ad_version = version_number;
    desc_len = ((SectionData[10]) << 8) | (SectionData[11]);
    Descriptor_Parsed = 0;
    SectionData += 12;

    d_tab_mask_add (es->ad_mask[HIV2AD_PID_TYPE_ADLIST], (D_U16)0, 0, SectionNo, LastSectionNo); //因为没有0表，为了判断，所以添加0；

    //保存广告的信息，从+12之后开始的
    while(Descriptor_Parsed < desc_len)
    {
        D_U8    ad_type, idx;
        ad_type = SectionData[4];

        idx = es->adlist.cnt;

        if((ad_type < HIV2AD_STB_POS_UNKNOWN) && (idx < D_HIV2_MAX_AD))
        {
            ad_id = (D_U16)SectionData[0] << 8;
            ad_id |= (D_U16)SectionData[1] & 0x00ff;
            es->adlist.tb_desc[idx].ad_id = ad_id;
            es->adlist.tb_desc[idx].ad_version = (D_U8)SectionData[2] >> 3;
            es->adlist.tb_desc[idx].ad_des_table_id = (D_U8)SectionData[3];
            es->adlist.tb_desc[idx].ad_type = (D_U8)SectionData[4];
            es->adlist.cnt++;
        }
        Descriptor_Parsed += 5;//5字节是一个循环
        SectionData += 5;
    }
    if(d_tab_mask_full(es->ad_mask[HIV2AD_PID_TYPE_ADLIST]))
    {
        es->adlist.ver = version_number;
        stop_filter(es, type);
        //有新版本，需要停止正在搜索的属性表，数据表
        stop_filter(es, HIV2AD_PID_TYPE_DESCRIPTOR);
        stop_filter(es, HIV2AD_PID_TYPE_PIC_DATA);
        //释放描述子资源
        init_descriptor(es);
        //释放数据资源
        init_resource(es);
        //删除无效的组和数据

        d_sem_wait(es->sem);
        es->useflag = 0;//标识数据不可用
        d_sem_post(es->sem);

        del_disabled_des_data(&es->oldlist, &es->adlist);
        //比较有相同版本的不在搜索
        check_des_ver(&es->oldlist, &es->adlist);
        es->useflag = 1;//标识数据可用

#ifdef D_SYSTEM_WIN32
#else
        start_filter(es, version_number, HIV2AD_PID_TYPE_ADLIST);//监控不同版本的描述子
#endif
        start_filter(es, -1, HIV2AD_PID_TYPE_DESCRIPTOR);
    }
    return D_OK;
}

/** @brief 解析广告描述子
* @param[in] D_U8 *ptrSectionData  任务资源
* @param[in] ad_des_info *info 广告描述子
* @retval D_OK  成功
* @retval D_ERR  失败
*/
static D_U16 parse_descriptor(d_hiv2ad_esdata* es, D_U8 *ptrSectionData, adlist_tb_desc *para)D_FUNCPOSTFIT
{
    D_U16   DesLength;
    D_U16   DesInfoLength;
    D_U8    *pucSectionData;
    ad_des_info *info = &(para->des);

    pucSectionData = ptrSectionData;
    //根据不同的描述子类型进行不同的操作
    if(pucSectionData[0] == ADL_PLAY_PARAS_DES)//0x80广告参数描述符
    {
        D_U8    ad_type;

        DesInfoLength = pucSectionData[1];
        DesLength = DesInfoLength + 2;  //descriptor_tag占8bit，descriptor_length占8bit所以此处加2.返回的值才是接收到的长度

        ad_type = pucSectionData[2];
        HIV2AD_API_DUMP("ad_type[%d]!\n", ad_type);

        info->play_paras.duration  = ((D_U32)pucSectionData[3]) << 16;
        info->play_paras.duration |= ((D_U32)pucSectionData[4]) << 8;
        info->play_paras.duration |= ((D_U32)pucSectionData[5]) ;

        info->play_paras.posx = (((D_U16)pucSectionData[6]) << 4) | (((D_U16)(pucSectionData[7] & 0xf0)) >> 4);
        info->play_paras.posy = (((D_U16)(pucSectionData[7] & 0x0f)) << 8) | ((D_U16)pucSectionData[8]);
        info->play_paras.disp_w = (((D_U16)pucSectionData[9]) << 4) | (((D_U16)(pucSectionData[10] & 0xf0)) >> 4);
        info->play_paras.disp_h = (((D_U16)(pucSectionData[10] & 0x0f)) << 8) | ((D_U16)pucSectionData[11]);
    }
    else if(pucSectionData[0] == SCROLL_TXT_DES)//0x84滚动字幕描述符
    {
        D_U8    idx;
        D_U16 txt_id;
        D_U16 font_size;
        D_U32 back_color;
        D_U32 font_color;
        D_U32 language_code;
        D_U8  txt_speed;
        D_U16 txt_length;
        DesInfoLength = (((D_U16)pucSectionData[1]) << 8) | ((D_U16)pucSectionData[2]);
        DesLength = DesInfoLength + 3;

        txt_id = (((D_U16)pucSectionData[3]) << 8) | ((D_U16)pucSectionData[4]);
        font_size = (((D_U16)pucSectionData[5]) << 8) | ((D_U16)pucSectionData[6]);
        back_color  = (D_U32)pucSectionData[7] << 24;
        back_color |= (D_U32)pucSectionData[8] << 16;
        back_color |= (D_U32)pucSectionData[9] << 8;
        back_color |= (D_U32)pucSectionData[10];
        font_color  = (D_U32)pucSectionData[11] << 24;
        font_color |= (D_U32)pucSectionData[12] << 16;
        font_color |= (D_U32)pucSectionData[13] << 8;
        font_color |= (D_U32)pucSectionData[14];
        language_code  = (D_U32)pucSectionData[15] << 16;
        language_code |= (D_U32)pucSectionData[16] << 8;
        language_code |= (D_U32)pucSectionData[17];
        txt_speed = pucSectionData[18]>>4;
        txt_length = (D_U16)((pucSectionData[18] & 0x0f) << 8 | pucSectionData[19]);
        pucSectionData += 20;

        if(info->txt_num >= TXT_MAX_NUM)
            return  DesLength;
        idx = info->txt_num;
        info->txt[idx].txt_id = txt_id;
        info->txt[idx].txt_length = txt_length;
        info->txt[idx].font_size = font_size;
        info->txt[idx].back_color = back_color;
        info->txt[idx].font_color = font_color;
        info->txt[idx].language_code = language_code;
        info->txt[idx].txt_speed = txt_speed;
        if(info->txt[idx].content == NULL)
        {
            info->txt[idx].content = d_mman_alloc(es->hmm, txt_length + 1);
            if(info->txt[idx].content == NULL)
            {
                HIV2AD_API_DUMP("txt content malloc err!\n");
                return DesLength;
            }
            memset(info->txt[idx].content, 0, txt_length + 1);
        }
        memcpy(info->txt[idx].content, pucSectionData, txt_length);
        info->txt_num  += 1;
    }
    else if(pucSectionData[0] == ADL_AREA_ID_DES)//0x82区域ID描述符
    {
        D_U16       Descriptor_Parsed;

        DesInfoLength = (((D_U16)pucSectionData[1]) << 8) | ((D_U16)pucSectionData[2]);
        DesLength = DesInfoLength + 3;

        Descriptor_Parsed = 0;
        pucSectionData += 3;
        while(Descriptor_Parsed < DesInfoLength)
        {
            if(info->area_code_num >= MAX_AREA_CODE_NUM)
                break;
            memcpy((D_U8 *) & (info->area_code[info->area_code_num]), pucSectionData, 4);
            info->area_code_num ++;
            Descriptor_Parsed += 4;
            pucSectionData += 4;
        }
    }
    else if(pucSectionData[0] == ADL_DATA_DES)//0x83广告数据描述符
    {
        D_U16   pic_id, PicPID;
        D_U8    memory_type;
        D_U16   Descriptor_Parsed;
        ad_pic_res_info res_info;

        DesInfoLength = (((D_U16)pucSectionData[1]) << 8) | ((D_U16)pucSectionData[2]);
        DesLength = DesInfoLength + 3;

        PicPID = (((D_U16)pucSectionData[3]) << 8) | ((D_U16)pucSectionData[4]);
        PicPID = PicPID >> 3;
        memory_type = ((D_U8)pucSectionData[4] & 0x04) >> 2;

        Descriptor_Parsed = 0;
        DesInfoLength = pucSectionData[5];
        pucSectionData += 6;

        while(Descriptor_Parsed < DesInfoLength)
        {
            pic_id = (((D_U16)pucSectionData[0]) << 8) | ((D_U16)pucSectionData[1]);
            info->link_pic_id[info->link_pic_num] = pic_id;
            info->link_pic_num ++;
            res_info.data_pid = PicPID;
            res_info.memory = memory_type;
            res_info.pic_id = pic_id;

            add_pic_source(es, &res_info);
            pucSectionData += 2;
            Descriptor_Parsed += 2;
        }
    }
    else if(pucSectionData[0] == SERVICE_ID_DES)//0x85服务描述符
    {
        D_U8    idx;
        D_U16   Descriptor_Parsed;
        DesInfoLength = (((D_U16)pucSectionData[1]) << 8) | ((D_U16)pucSectionData[2]);
        DesLength = DesInfoLength + 3;

        Descriptor_Parsed = 0;
        pucSectionData += 3;

        while(Descriptor_Parsed < DesInfoLength)
        {
            if(info->ser_num >= AD_LINK_SERV_MAX_NUM)
                break;
            idx = info->ser_num;
            info->service[idx].pic_id = (((D_U16)pucSectionData[0]) << 8) | ((D_U16)pucSectionData[1]);
            info->service[idx].service_id = (((D_U16)pucSectionData[2]) << 8) | ((D_U16)pucSectionData[3]);
            info->service[idx].pic_id = (((D_U16)pucSectionData[4]) << 8) | ((D_U16)pucSectionData[5]);
            pucSectionData += 6;
            Descriptor_Parsed += 6;
            info->ser_num++;
        }
    }

    return  DesLength;
}


/** @brief 解析广告属性描述信息
* @param[in] d_hiv2ad_esdata es  任务资源数据
* @param[in] D_U8 type数据类型
* @retval D_OK  成功
* @retval D_ERR  失败
*/
static D_Result parse_descriptor_data(d_hiv2ad_esdata* es, D_U8 type)D_FUNCPOSTFIT
{
    D_U16   adv_ID;
    D_U16   DescLoopLength;
    D_U8    SectionNo;
    D_U8    LastSectionNo;
    D_S8    ad_ver;
    D_U16   NoOfDataBytes, Descriptor_Parsed;
    adlist_tb_desc *ad_des_struct = NULL;
    D_U8    *SectionData = es->sec;

    adv_ID = (((D_U16)SectionData[3]) << 8) | (D_U16)SectionData[4];

    ad_ver =  (SectionData[5] >> 1) & 0x1f;

    SectionNo = SectionData[6];
    LastSectionNo = SectionData[7];

    if (d_tab_mask_is_set (es->ad_mask[HIV2AD_PID_TYPE_DESCRIPTOR], 0, 0, SectionNo ))
    {
        HIV2AD_API_DUMP (" hiv2ad  data section duplicated \n");
        return D_ERR;
    }

    HIV2AD_API_DUMP("[hiv2ad] adv_ID = [%d] SectionNo = [%d] LastSectionNo = [%d]ad_ver[%d]\n", (D_U16)adv_ID, (D_U16)SectionNo, (D_U16)LastSectionNo, ad_ver);

    DescLoopLength = (SectionData[8] << 8) | SectionData[9];
    Descriptor_Parsed = 0;
    SectionData += 10;

    d_tab_mask_add (es->ad_mask[HIV2AD_PID_TYPE_DESCRIPTOR], (D_U16)0, 0, SectionNo, LastSectionNo);
    ad_des_struct = get_des_struct_by_id(es, adv_ID);

    while(Descriptor_Parsed < DescLoopLength)
    {
        NoOfDataBytes = parse_descriptor(es, SectionData, ad_des_struct);
        Descriptor_Parsed += NoOfDataBytes;
        SectionData += NoOfDataBytes;
    }

    if(d_tab_mask_full(es->ad_mask[HIV2AD_PID_TYPE_DESCRIPTOR]))
    {
        D_U8 i;
        D_Result        ret = D_ERR;
        //接收完成一组
        stop_filter(es, type);
        //判断是否所有描述表搜已搜索完成
        for(i = 0; i < es->adlist.cnt; i++)
        {
            if(es->adlist.tb_desc[i].flag == 0)
            {
                ret = D_OK;
                break;
            }
        }
        if(ret == D_OK)
        {
            start_filter(es, -1, HIV2AD_PID_TYPE_DESCRIPTOR);
        }
        else
        {

            d_sem_wait(es->sem);
            es->txtuseflag = 0;//标识数据不可用
            d_sem_post(es->sem);
            //处理txt
            //add txt已搜索完成
            flush_txt_data(es);
            es->txtuseflag = 1;//标识数据不可用
            set_osd_eraseflag(es);
            set_osd_update(es);
            start_filter(es, -1, HIV2AD_PID_TYPE_PIC_DATA);
        }
    }
    return D_OK;
}


/** @brief 解析广告数据
* @param[in] d_hiv2ad_esdata es  任务资源数据
* @param[in] D_U8 type数据类型
* @retval D_OK  成功
* @retval D_ERR  失败
*/
static D_Result parse_pic_data(d_hiv2ad_esdata* es, D_U8 type)D_FUNCPOSTFIT
{
    D_U16   pic_id;
    D_ImageType pic_type;
    D_U8    pic_datagram;
    D_U8    pic_datagram_total;
    D_U32   pic_original_size;
    D_U16   pic_width;
    D_U16   pic_height;
    D_U32   pic_data_length;
    D_U8    pic_compressed;
    D_U8    pic_compressedsize;
    D_U8 *SectionData = es->sec;
    ad_pic_res_info *info;


    if(check_picdata_valid(SectionData) == D_ERR)
        return D_ERR;
    SectionData += 10;
    pic_id  = (D_U16)SectionData[0] << 8;
    pic_id |= (D_U16)SectionData[1];
    if(es->pic_res.cur_pic_id != pic_id)
    {
        return D_ERR;
    }
    pic_type = (D_ImageType)SectionData[2];
//  pic_datagram = (D_U16)SectionData[3] << 8;
    pic_datagram = (D_U16)SectionData[4];
//  pic_datagram_total = (D_U16)SectionData[5] << 8;
    pic_datagram_total = (D_U16)SectionData[6];
    pic_datagram_total = pic_datagram_total >= 1 ? (pic_datagram_total - 1) : 0;
    pic_original_size  = (D_U32)SectionData[7] << 24;
    pic_original_size |= (D_U32)SectionData[8] << 16;
    pic_original_size |= (D_U32)SectionData[9] << 8;
    pic_original_size |= (D_U32)SectionData[10];
    pic_compressedsize  = (D_U32)SectionData[11] << 24;
    pic_compressedsize |= (D_U32)SectionData[12] << 16;
    pic_compressedsize |= (D_U32)SectionData[13] << 8;
    pic_compressedsize |= (D_U32)SectionData[14];
    pic_compressed = (D_U8)(SectionData[15] & 0x80) >> 7;

    if(pic_type == HIV2AD_IMAGE_JPEG)
    {
        pic_type = D_IMAGE_JPEG;
    }
    else if(pic_type == HIV2AD_IMAGE_GIF)
    {
        pic_type = D_IMAGE_GIF;
    }
    else if(pic_type == HIV2AD_IMAGE_MPEG2_FRAME_I)
    {
        pic_type = D_IMAGE_MPEG2_FRAME_I;
    }
    else if(pic_type == HIV2AD_IMAGE_BMP)
    {
        pic_type = D_IMAGE_BMP;
    }
    else if(pic_type == HIV2AD_IMAGE_AUTO)
    {
        pic_type = D_IMAGE_AUTO;
    }
    info = get_data_struct_by_id(es, pic_id);
    if(info == NULL)
        return D_ERR;

    if (d_tab_mask_is_set (es->ad_mask[type], 0, 0, pic_datagram ))
    {
        HIV2AD_API_DUMP (" hiv2ad  data section duplicated \n");
        return D_ERR;
    }

    SectionData += 16;
    pic_width = (D_U16)SectionData[0] << 8;
    pic_width |= (D_U16)SectionData[1];
    pic_height = (D_U16)SectionData[2] << 8;
    pic_height |= (D_U16)SectionData[3];
    pic_data_length = (D_U32)SectionData[4] << 24;
    pic_data_length |= (D_U32)SectionData[5] << 16;
    pic_data_length |= (D_U32)SectionData[6] << 8;
    pic_data_length |= (D_U32)SectionData[7];
    if(info->image.image == NULL)
    {
        info->image.pic_id = pic_id;        //图片ID
        info->image.img_type = pic_type;    //图片类型
        info->image.pic_width = pic_width;      //图片宽度
        info->image.pic_height = pic_height;    //图片高度
        if(pic_compressed)
        {
            info->image.image = d_mman_alloc(es->hmm, pic_compressedsize);
            info->image.pic_length = pic_compressedsize;
        }
        else
        {
            info->image.image = d_mman_alloc(es->hmm, pic_original_size);
            info->image.pic_length = pic_original_size;
        }

        if(info->image.image == NULL)
        {
            HIV2AD_API_DUMP("[hiv2ad]temp_pic_info img d_mman_alloc err!\n");
            return D_ERR;
        }
    }

    SectionData += 8;
    d_tab_mask_add (es->ad_mask[type], (D_U16)0, 0, pic_datagram, pic_datagram_total);

    memcpy((D_U8 *)(info->image.image + 0xff9c * pic_datagram), SectionData, pic_data_length);

    if(d_tab_mask_full(es->ad_mask[type]))
    {
        D_Result        ret = D_ERR;
        D_U8        i;
#ifdef D_SYSTEM_WIN32
        char String_p[20];
        FILE *file = NULL;
        {
            memset(String_p, 0, 20);
            sprintf(String_p, "PICID%02d.GIF", pic_id);

            file = fopen(String_p, "wb+");
            if(file == NULL)
                return D_ERR;
            fwrite((D_U8*)info->image.image, sizeof(char),  (D_Size)pic_original_size, file);
            fclose(file);
        }
#endif

        //接收完成一组
        stop_filter(es, type);
        //判断是否所有图片数据都已搜索完成
        for(i = 0; i < es->pic_res.cnt; i++)
        {
            if(es->pic_res.res[i].flag == 0)
            {
                ret = D_OK;
                break;
            }
        }
        if(ret == D_OK)
        {
            start_filter(es, -1, HIV2AD_PID_TYPE_PIC_DATA);
        }
        else
        {
            //全部数据搜索完成
            HIV2AD_API_DUMP (" hiv2ad  all pic data ok \n");
            es->storelist.cnt = 0;
            es->storelist.ver = -1;
            flush_pic_data(es, HIV2AD_STB_LOG);
            flush_pic_data(es, HIV2AD_STB_RADIO_BACK);
            flush_pic_data(es, HIV2AD_STB_NOSIGNAL);
            flush_pic_data(es, HIV2AD_STB_NOPROGRAM);
            flush_pic_data(es, HIV2AD_STB_BANNER);
            flush_pic_data(es, HIV2AD_STB_VOLUME);
            flush_pic_data(es, HIV2AD_STB_MENU);
            flush_pic_data(es, HIV2AD_STB_PROGRAM_LIST);
            flush_pic_data(es, HIV2AD_STB_EPG);

            flush_last_ver(&(es->oldlist), &(es->storelist));//将本次未更新的组信息也添加到storelist
            flush_ver_data(&(es->storelist));//将storelist信息保存到Flash中

            d_sem_wait(es->sem);
            es->useflag = 0;//标识数据不可用
            d_sem_post(es->sem);
            set_pic_eraseflag(es);
            set_full_eraseflag(es);
            clear_full_timer();

            set_cur_data(&(es->oldpic_res), &(es->pic_res)); //将新搜到的图片资源添加oldpic_res  ，供上层使用
            set_cur_ver(&(es->oldlist), &(es->adlist));     //将新  的属性信息添加      oldlist，供上层使用
            es->pic_res.cnt = 0;
            es->adlist.cnt = 0;
            memset((D_U8*)(&es->adlist), 0, sizeof(adlist_tb_info_t));
            es->storelist.cnt = 0;
            es->useflag = 1;//标识数据可用
            clear_full_timer();
            d_hiv2ad_ShowMessage(HIV2AD_MSEEAGE_HIDEFULLSRCEEN_TYPE, NULL);
            hiv2ad_get_fullscan_by_prog(&es->curprog);
            set_pic_update(es);
            set_full_update(es);
        }
        return D_OK;
    }
    return D_ERR;
}

/** @brief 搜索开始
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
static d_hiv2ad_esdata  * start_create(void)D_FUNCPOSTFIT
{
    d_hiv2ad_esdata    *es;
    D_U8        *buf;
    D_HMMan hmm;
    D_HSem  hsem;
    D_SemAttr attr;
    D_U8 i;

    buf = (D_U8*) d_mem_alloc(0, D_HIV2_AD_MEM_SIZE);

    if(! buf)
    {
        HIV2AD_API_ERROR ("Cannot allocate hiv2ad scan memory\n");
        return NULL;
    }
    hmm = d_mman_create((D_Ptr)buf, (D_Size)D_HIV2_AD_MEM_SIZE, (D_MManType)D_MMAN_HEAP); //创建一个内存管理器
    HIV2AD_API_DUMP("[ad]ad_start[buf:0x%x][hmm:0x%x][size:0x%x]\n", buf, hmm, D_HIV2_AD_MEM_SIZE);

    if(D_INVALID_HANDLE == hmm)
    {
        HIV2AD_API_ERROR ("Cannot create hiv2ad memory manager\n");
        d_mem_free (buf);
        return NULL;
    }

    es = (d_hiv2ad_esdata*) d_mman_alloc((D_HMMan)hmm, sizeof (d_hiv2ad_esdata)); //通过内存管理器分配一块内存
    if(! es)
    {
        HIV2AD_API_ERROR ("Cannot allocate hiv2ad scan data\n");
        d_mman_destroy (hmm);
        d_mem_free (buf);
        return NULL;
    }
    memset(es, 0, sizeof (d_hiv2ad_esdata));

    es->sec = (D_U8*) d_mman_alloc((D_HMMan) hmm, (D_Size) D_HIV2AD_SCAN_PES_BUF_SIZE);//通过内存管理器分配一块内存
    if(! es->sec)
    {
        HIV2AD_API_ERROR ("Cannot allocate hiv2ad scan buf sec data\n");
        d_mman_destroy (hmm);
        d_mem_free (buf);
        return NULL;
    }
    memset(es->sec, 0, D_HIV2AD_SCAN_PES_BUF_SIZE);

    es->hmm = hmm;
    es->buf = buf;
    for(i = 0; i < HIV2AD_PID_TYPE_MAX_NUM ; i ++)
    {
        es->AdvDemux[i] = D_INVALID_HANDLE;
        es->ad_mask[i] = d_tab_mask_new (es->hmm, 1);
    }
    for(i = 0; i < D_HIV2_FULL_MAX ; i ++)
    {
        es->timer[i].htimer = D_INVALID_HANDLE;
    }
    es->ad_version = -1;
    es->adlist.cnt = 0;
    es->adlist.ver = -1;
    es->storelist.cnt = 0;
    es->storelist.ver = -1;
    es->oldlist.cnt = 0;
    es->oldlist.ver = -1;
    get_ver_data(&(es->oldlist));
    es->oldpic_res.cnt = 0;
    get_old_pic_data(es, &(es->oldlist), &(es->oldpic_res));
    es->useflag = 1;//标识数据可用

    /* 用缺省值初始化信号量属性*/
    es->sem = D_INVALID_HANDLE;
    D_SEM_ATTR_INIT (&attr);
    hsem = d_sem_create (&attr);
    es->sem = hsem;
    d_sem_post (es->sem);
    return es;
}

/** @brief 搜索停止
* @param[in] es  资源指针
* @return 成功返回D_OK,失败返回D_ERR
*/
static D_Result stop_create (d_hiv2ad_esdata *es)D_FUNCPOSTFIT
{
    D_U8 *buf = es->buf;
    if(D_INVALID_HANDLE  != es->sem)
    {
        d_sem_destroy (es->sem);                   /*释放一个内存管理器*/
        es->sem = D_INVALID_HANDLE;
    }

    if(D_INVALID_HANDLE  != es->hmm)
    {
        HIV2AD_API_DUMP("[ad]d_mman_destroy[ es->hmm:0x%x]\n", es->hmm);
        d_mman_destroy (es->hmm);                   /*释放一个内存管理器*/
        es->hmm = D_INVALID_HANDLE;
    }
    if(buf)
    {
        HIV2AD_API_DUMP("[ad]d_mem_free[buf:0x%x]\n", buf);
        d_mem_free (buf);                           /*释放分配的内存*/
    }
    return D_OK;
}

static D_Result send_msg(D_HQueue queue, D_HIV2AD_Msg_Type msg, D_U8 type, D_U16 pid)D_FUNCPOSTFIT
{
    D_HIV2AD_Msg smsg;

    smsg.type = (D_HIV2AD_Msg_Type) D_MSG_USER;
    smsg.param1 = (D_U32)msg;
    smsg.param2 = (D_U32)type;
    smsg.param3 = (D_U32)pid;

    d_queue_send(queue, (D_U8*)&smsg, sizeof (smsg));

    return D_OK;
}

static D_Result deal_msg(D_HIV2AD_Msg * msg, d_hiv2ad_esdata  * es)D_FUNCPOSTFIT
{
    D_HIV2AD_Msg_Type para1 = (D_HIV2AD_Msg_Type)(msg->param1);

    switch(para1)
    {
        case HIV2AD_SETPID:
        {
            start_filter(es, -1, HIV2AD_PID_TYPE_ADLIST);
            break;
        }
        default:
            break;
    }
    return D_OK;
}

/** @brief  获取OSD广告数据
* @param[in] MGAD_PROGRAM_PARA stProgramPara                    注释 数据
* @param[in] ST_MGAD_OSD_PROGRAM_SHOW_INFO *pstOsdProgramShow   注释 显示信息
* @param[in] MGAD_ALL_ADV_TYPE_E type                           注释 类型
* @retval D_OK  成功
* @retval D_ERR  失败
* @note 注解
*/
D_Result   hiv2ad_ProgramGetOSD(hiv2ad_program_para prog, hiv2ad_osd_prog_show_info * pstOsdProgramShow)D_FUNCPOSTFIT
{
    D_U8 i, j, sercnt, num;
    D_U16  txt_id, txt_id1;
    D_U16 usServiceId;
    hiv2ad_osd_show_info *txtinfo;

    pstOsdProgramShow ->ucOsdNum = 0;
    d_sem_wait (hiv2adapies->sem);
    if(hiv2adapies->txtuseflag == 0)
    {
        d_sem_post (hiv2adapies->sem);
        return D_ERR;
    }
    sercnt = hiv2adapies->txt_cont.ser_num;
    for(i = 0; i < hiv2adapies->txt_cont.txt_num; i++)      /*根据serviceID为0~FFF8，AdvID为1时serviceID与节目对应*/
    {
        txt_id = hiv2adapies->txt_cont.txt[i].txtId;
        for(j = 0; j < sercnt; j++)
        {
            txt_id1 = hiv2adapies->txt_cont.service[j].pic_id;        //对应的广告ID,txt时候对应TXTID
            usServiceId = hiv2adapies->txt_cont.service[j].service_id;

            if(txt_id1 == txt_id)
            {
                if((usServiceId == 0) || (prog.usServiceId == usServiceId))
                {
                    //满足条件
                    break;
                }
            }
        }
        if((j == sercnt) && (sercnt != 0)) //不满足条件
        {
            continue;
        }
        txtinfo = &(hiv2adapies->txt_cont.txt[i]);
        num = pstOsdProgramShow->ucOsdNum;
        memcpy((D_U8*) & (pstOsdProgramShow->stTextShow[num]), (D_U8*)txtinfo, sizeof(hiv2ad_osd_show_info));
        pstOsdProgramShow->ucOsdNum += 1;

    }
    if(pstOsdProgramShow->ucOsdNum > 0)
    {
        d_sem_post (hiv2adapies->sem);
        return D_OK;
    }
    else
    {
        d_sem_post (hiv2adapies->sem);
        return D_ERR;
    }
}

D_Image *hiv2ad_get_image_by_idx(HIV2_Ad_Pos_Type HiAd_type, hiv2ad_program_para *prog, D_U8 _idx, D_U8 *uctotal, D_U16 *left, D_U16 *top, D_U32 *time)D_FUNCPOSTFIT
{
    D_U8 i, j, k, listcnt, piccnt, sercnt;
    D_U8* image_buf = NULL;
    D_Image *image = NULL;
    D_U8 num = 0;
    ad_des_info *des;
    d_hiv2ad_esdata *es = hiv2adapies;
    adlist_tb_info_t *list = &hiv2adapies->oldlist;

    d_sem_wait (es->sem);
    if(es->useflag == 0)
    {
        d_sem_post (es->sem);
        return NULL;
    }
    listcnt = list->cnt;

    for(i = 0; i < listcnt; i++)
    {
        if(list->tb_desc[i].ad_type == HiAd_type)
        {
            des = &(list->tb_desc[i].des);
            piccnt = des->link_pic_num;
            sercnt = des->ser_num;
            for(j = 0; j < piccnt; j++)
            {
                D_U16  link_pic_id = des->link_pic_id[j];
                for(k = 0; k < sercnt; k++)
                {
                    D_U16   service_id = des->service[k].service_id; //指定服务ID
                    D_U16   pic_id = des->service[k].pic_id;        //对应的广告ID,txt时候对应TXTID
                    if(pic_id == link_pic_id)
                    {
                        if((service_id == 0) || (prog->usServiceId == service_id))
                        {
                            //满足条件
                            break;
                        }
                    }
                }
                if((k == sercnt) && (sercnt != 0)) //不满足条件
                {
                    continue;
                }
                else if(num == _idx)//找到对应的图片
                {
                    ad_pic_res_info *resinfo;
                    resinfo =  get_data_info_by_id(&es->oldpic_res, link_pic_id);
                    if((resinfo == NULL) || (resinfo->flag == 0))
                    {
                        HIV2AD_API_DUMP("get_data_struct_by_id err!\n");
                        d_sem_post (es->sem);
                        return NULL;
                    }
                    image = (D_Image*)d_g_load_image (d_gui_get_surface(), D_IMAGE_AUTO, (D_U8*)resinfo->image.image, (D_Size)resinfo->image.pic_length);
                    if(image == NULL)
                    {
                        d_sem_post (es->sem);
                        return NULL;
                    }

                    *uctotal = des->link_pic_num;
                    *left = des->play_paras.posx;
                    *top = des->play_paras.posy;
                    *time = des->play_paras.duration * 1000;
                    HIV2AD_API_DUMP("d_ad_get_img  [ptr:0x%x]\n", image);
                    d_sem_post (es->sem);
                    return image;
                }
                else
                {
                    num ++;
                }
            }
        }
    }
    d_sem_post (es->sem);

    return NULL;
}

/** @brief 搜索消息回调函数
* @param[in] D_Msg *msg   注释      广告处理消息
* @retval D_OK  成功
* @retval D_ERR  失败
*/
static D_Result hiv2ad_callback (D_Msg * msg)D_FUNCPOSTFIT
{
    D_U8 i;
    D_Size cnt;
    d_hiv2ad_esdata  *es;
    es = (d_hiv2ad_esdata*) d_app_get_data ((D_HApp) d_app_self ()); /* 获取资源指针 */

    switch (msg->type)
    {
        case D_MSG_APP_CREATE:
        {
            es = msg->app.arg;
            d_app_set_data ((D_HApp) d_app_self (), (D_Ptr) es);
            es->queue = d_app_get_queue (d_app_self ());
        }
        break;
        case D_MSG_USER:
        {
            deal_msg((D_HIV2AD_Msg*)msg, es);
            break;
        }
        case D_MSG_DEMUX_DATA:      /* demux数据处理部分 */
        {
            for(i = 0; i < HIV2AD_PID_TYPE_MAX_NUM ; i ++)
            {
                if((es->AdvDemux[i] == msg->demux.hdemux) && (D_INVALID_HANDLE != es->AdvDemux[i]))
                {
                    cnt = 0;
                    if(i <= 1)
                    {
                        cnt = d_demux_read(es->AdvDemux[i], es->sec, D_HIV2AD_SCAN_SEC_BUF_SIZE);
                    }
                    else if(i == 2)
                    {
                        cnt = d_demux_read (es->AdvDemux[i], es->sec, D_HIV2AD_SCAN_PES_BUF_SIZE);
                    }
                    if(cnt > 0)
                    {
                        HIV2AD_API_DUMP("HIV2ad_start_parse [size:0x%x],%d \n", D_HIV2AD_SCAN_SEC_BUF_SIZE, i);
                        if(i == HIV2AD_PID_TYPE_ADLIST)
                        {
                            parse_adlist_data(es, i);/* 广告列表描述信息表的处理 */
                        }
                        else if(i == HIV2AD_PID_TYPE_DESCRIPTOR)
                        {
                            parse_descriptor_data(es, i);/* 广告属性描述信息表的处理 */
                        }
                        else if(i == HIV2AD_PID_TYPE_PIC_DATA)
                        {
                            parse_pic_data(es, i);/* 全部广告数据的处理 */
                        }
                    }
                    break;
                }
            }
            break;
        }
        case D_MSG_TIMER:
        {
            break;
        }
        case D_MSG_APP_DESTROY:
        {
            stop_create (es);
            break;
        }
        default:
            break;
    }

    return D_OK;
}

/** @brief创建ad搜索任务
* @param[in] D_S8 priority   注释 优先级
* @retval D_OK   成功
* @retval D_ERR  失败
* @note 注解
*/
static D_HScan hiv2ad_scan_create(D_S8 priority, ADEVENTCALLBACK cb)D_FUNCPOSTFIT
{
    d_hiv2ad_esdata  *es;

    es = start_create();
    if(! es)
    {
        HIV2AD_API_ERROR ("Cannot allocate ad scan data\n");
        return D_INVALID_HANDLE;
    }
    hiv2adapies = es;
    es->cb = cb;

    /*创建hiv2admask*/
    es->happ = d_app_create ("Hiv2AdScan", priority, D_AD_MODULE_TASK_STACK_SIZE, D_AD_MODULE_QUEUE_SIZE, hiv2ad_callback, (D_Ptr)es);
    if(D_INVALID_HANDLE == es->happ)
    {
        HIV2AD_API_ERROR ("Cannot create ad scan app\n");
        stop_create (es);
        return es->happ;
    }

    /*同步，等待设备创建完成*/
    d_app_sync (es->happ);
    HIV2AD_API_DUMP("[ad]d_ad_scan_create[es->happ:0x%x]\n", es->happ);
    return es->happ;
}
D_Result hiv2ad_scan_destroy (D_HScan hscan)D_FUNCPOSTFIT
{
    HIV2AD_API_DUMP("[scan]d_scan_destroy[hscan:0x%x]\n", hscan);
    d_app_destroy (hscan);
    hiv2adapies = NULL;

    return D_OK;
}

/** @brief  广告入口
* @param[in] D_U8 ucPriority   注释:优先级
* @retval D_OK  成功
* @retval D_ERR 失败
*/
D_Result hiv2ad_open(D_U8 ucPriority, ADEVENTCALLBACK cb)D_FUNCPOSTFIT
{
    happ = hiv2ad_scan_create(ucPriority, cb);
    if(D_INVALID_HANDLE == happ)
    {
        return D_ERR;
    }

    return D_OK;
}


D_Result hiv2ad_Close(void)D_FUNCPOSTFIT
{
    if(D_INVALID_HANDLE != happ)
    {
        hiv2ad_scan_destroy(happ);
        return D_OK;
    }
    return D_OK;
}

D_Result hiv2ad_SetDataPid(void)D_FUNCPOSTFIT
{
    if(hiv2adapies == NULL)
    {
        return D_ERR;
    }
    send_msg(hiv2adapies->queue, HIV2AD_SETPID, 0, 0);

    return D_OK;
}
D_Result hiv2ad_chan_change(D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT
{
    D_Image *image;
    D_U8 i, cnt = 0;
    D_U16 left, top;
    D_U32 time;

    if(hiv2adapies == NULL)
    {
        return D_ERR;
    }
    hiv2adapies->curprog.usNetworkId = chan_param->usNetworkId;
    hiv2adapies->curprog.usTsId = chan_param->usTsId;
    hiv2adapies->curprog.usServiceId = chan_param->usServiceId;
    clear_full_timer();
    d_hiv2ad_ShowMessage(HIV2AD_MSEEAGE_HIDEFULLSRCEEN_TYPE, NULL);
    hiv2ad_get_fullscan_by_prog(chan_param);

    return D_OK;
}

D_Result hiv2ad_CallBackOSD(D_U32 txtid)D_FUNCPOSTFIT
{
    D_U8 i;
    hiv2ad_osd_show_info *txt;

    if(hiv2adapies == NULL)
    {
        return D_ERR;
    }
    d_sem_wait (hiv2adapies->sem);
    if(hiv2adapies->txtuseflag == 0)
    {
        d_sem_post (hiv2adapies->sem);
        return D_ERR;
    }
    for(i = 0; i < hiv2adapies->txt_cont.txt_num; i++)          /*根据serviceID为0~FFF8，AdvID为1时serviceID与节目对应*/
    {
        if(hiv2adapies->txt_cont.txt[i].txtId == txtid) //不满足条件
        {
            txt = &(hiv2adapies->txt_cont.txt[i]);
            if(txt->ucShowTimes == 1)
            {
                txt->scrollend = 1;
            }
            else if(txt->ucShowTimes > 1)
            {
                txt->ucShowTimes --;
            }
        }
    }
    d_sem_post (hiv2adapies->sem);
    return D_ERR;
}

