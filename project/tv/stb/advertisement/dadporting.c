/** @file
* @brief 广告模块支撑接口
* @author hegx
* @date 2014-03-03 和光雄: 建立文件
*/
#include "dDebug.h"
#include <string.h>
#include "dadporting.h"
#include "dApp.h"
#include "dDemux.h"
#include "dTask.h"
#include "dScan.h"
#include "dad_data_store.h"
#include "dNVPart.h"
#include "dDBaseInternal.h"

#define D_AD_SCAN_BUF_SIZE                   (1024*32)
#define D_AD_SCAN_SEC_BUF_SIZE               (4096)     /**@brief section缓冲区大小*/
#define D_AD_SCAN_MM_SIZE                    (4096*2)   /**@brief 搜索模块内存大小*/
#define D_AD_CTRL_MM_SIZE                    (0x10000)      /**@brief 广告控制模块内存大小*/

#define D_AD_IMAGE_MAX   5

#define DAD_PRINT_EN 0

#if DAD_PRINT_EN
#define DAD_DUMP D_DUMP
#define DAD_ERROR D_ERROR
#else
#define DAD_DUMP(_s,...)
#define DAD_ERROR(_s,...)
#endif


/** @brief AD搜索资源*/
typedef struct
{
    D_U8        *buf;           /**@brief < 为搜索分配的内存地址*/
    D_U8        *sec;           /**@brief < 过滤demux接收的数据*/
    D_HMMan     hmm;            /**@brief < 为搜索分配的内存创建的内存管理器句柄*/
    D_HApp      happ;           /**@brief< 搜索应用句柄*/
    D_HQueue    queue;
    D_U8        ucPriority;
    D_HSem      sem;
    D_Ad_Event_Param back[DAD_DEMUX_TOTAL_TYPE];
    D_DemuxFilter filter[DAD_DEMUX_TOTAL_TYPE];
    D_DemuxAttr   dmx_attr[DAD_DEMUX_TOTAL_TYPE];

    D_U8        maxdemux;           /**@brief < 当前使用的最大数*/

} D_AdScanEsData;
/** @brief AD应用的状态*/
typedef enum
{
    DAD_ST_CLOSE,            //关闭
    DAD_ST_OPEN,             //开
} D_Ad_Status_Ctrl;

/** @brief AD应用数据的状态*/
typedef enum
{
    DAD_DATA_WAIT,           //等待数据
    DAD_DATA_OK,             //数据已准备好
} D_Ad_Data_Ctrl;

/** @brief 组织数据*/
typedef struct
{
    D_U8        *buf;           /**@brief < 为搜索分配的内存地址*/
    D_HSem      hsem;
    D_HSem      hsem1;
    D_HMMan     hmm;            /**@brief < 为搜索分配的内存创建的内存管理器句柄*/
    D_HApp      happ;           /**@brief< 搜索应用句柄*/
    D_HQueue    queue;          /**@brief< 该任务消息队列*/
    D_Ad_Op*    op;             /**@brief< 底层广告操作句柄*/
    /********初始化第三方库时候需要使用*********/
    D_Ad_Stb_Decode_Type type;
    D_U8 ttag[AD_STB_MAX];
    D_U8 ucPriority;
    D_U32 uiFlashStartAddress;
    /********广告控制需要使用*********/
    D_Ad_Service_Param  param;//记录上次查询的条件
    D_Ad_Status_Ctrl stflag[DAD_STB_POS_UNKNOWN];//应用状态
    D_Ad_Data_Ctrl   dataflag[DAD_STB_POS_UNKNOWN];//数据状态
    D_Ptr            hand[DAD_STB_POS_UNKNOWN][DAD_PIC_TOTAL_TYPE];
    D_HTimer         htimer[DAD_STB_POS_UNKNOWN];//定时器
    D_U8             index[DAD_STB_POS_UNKNOWN];//用来记录下次取的ID
    D_Ad_Event_Param back[DAD_TIMER_TOTAL_TYPE];

} D_AdEsData;

static D_AdScanEsData   *adscan = NULL;
static D_AdEsData   *ades = NULL;
static D_HApp       hscanapp = D_INVALID_HANDLE;            /**@brief< 搜索应用句柄*/
static D_HApp       happ = D_INVALID_HANDLE;            /**@brief< 应用句柄*/

/** @brief 通过内存管理器释放一块内存
* @param hmm 内存管理器句柄
* @param ptr 释放空间指针
* @return 成功返回D_OK,失败返回D_ERR
*/
static D_Result ad_mman_free (D_HMMan hmm, D_Ptr ptr) D_FUNCPOSTFIT
{
    D_Result    ret = D_OK;
    ret = d_mman_free (hmm, ptr);
    DAD_DUMP("[admem]ad_mman_free[mm:0x%x][ptr:0x%x][ret:0x%x]\n", hmm, ptr, ret);
    return ret;
}

/** @brief 通过内存管理器重新设定一块内存的大小
* @param hmm 内存管理器句柄
* @param old 旧区域指针
* @param size 新的区域大小
* @return 成功返回内存指针,失败返回NULL
*/
static D_Ptr ad_mman_alloc (D_HMMan hmm, D_Size size) D_FUNCPOSTFIT
{
    D_Ptr        ptr = NULL;

    ptr = d_mman_alloc(hmm, size);
    DAD_DUMP("[admem]ad_mman_alloc[mm:0x%x][size:0x%x][ptr:0x%x]\n", hmm, size, ptr);

    return ptr;
}

/*将消息发送到广告任务*/
static D_Result ad_send_msg(D_Ad_Msg_Type msg, D_Ad_Pos_Type type, D_Ptr handle, D_U16 nitid, D_U16 tsid, D_U16 svid)D_FUNCPOSTFIT
{
    D_AdMsg smsg;

    smsg.type = D_MSG_USER;
    smsg.param1 = (D_U32)msg;
    smsg.param2 = (D_U32)type;
    smsg.handle = (D_U8*)handle;
    smsg.usNetworkId = nitid;
    smsg.usTsId = tsid;
    smsg.usServiceId = svid;

    d_queue_send(ades->queue, (D_U8*)&smsg, sizeof (smsg));

    return D_OK;
}

/** @brief 初始化一个广告应用
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
static void ad_init_app(D_AdEsData  *es, D_U8 num)D_FUNCPOSTFIT
{
    D_U8 i;

    for(i = 0; i < DAD_PIC_TOTAL_TYPE; i ++)
    {
        es->hand[num][i] = NULL;
    }
    es->htimer[num] = D_INVALID_HANDLE;
    es->stflag[num] = DAD_ST_CLOSE;
    es->dataflag[num] = DAD_DATA_WAIT;
    es->index[num] = 0;
}

/** @brief  退出一个广告应用
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
static void ad_exit_app(D_AdEsData  *es, D_U8 num)D_FUNCPOSTFIT
{
    D_U8 j;

    for(j = 0; j < DAD_PIC_TOTAL_TYPE; j ++)
    {
        if(es->hand[num][j] != NULL)
        {
            if((D_Ad_Pos_Type)num == DAD_STB_OSD)
            {
                D_Ad_Osd_Param* datahandle = (D_Ad_Osd_Param*)es->hand[num][j];
                if(es->op->release_img)
                    es->op->release_img((D_Ad_Pos_Type)num, (D_U8*)datahandle->data_rsc_ptr);
                ad_mman_free(es->hmm, (D_Ptr)es->hand[num][j]);
            }
            else
            {
                D_Ad_Image_Param* datahandle = (D_Ad_Image_Param*)es->hand[num][j];
                if(es->op->release_img)
                    es->op->release_img((D_Ad_Pos_Type)num, (D_U8*)datahandle->data_rsc_ptr);
                ad_mman_free(es->hmm, (D_Ptr)es->hand[num][j]);
            }
            es->hand[num][j] = NULL;
        }
    }
    if(D_INVALID_HANDLE != es->htimer[num])
    {
        DAD_DUMP("[ad]d_timer_destroy[%d]\n", es->htimer[num]);
        d_timer_destroy (es->htimer[num]);
        es->htimer[num] = D_INVALID_HANDLE;
    }
    es->stflag[num] = DAD_ST_CLOSE;
    es->dataflag[num] = DAD_DATA_WAIT;
    es->index[num] = 0;
}
/** @brief 查找推送广告一个可用ID
* @param
* @return 成功返回D_OK,失败返回D_ERR
* @note
*/
static D_Result d_dad_find_idle(D_AdEsData  *es, D_U8 num, D_U8* idx)
{
    D_U8 i;

    for(i = 0 ; i < DAD_PIC_TOTAL_TYPE ; i++)
    {
        if(es->hand[num][i] == NULL)
        {
            *idx = i;
            return D_OK;
        }
    }
    return D_ERR;
}

/** @brief  准备一个广告应用 的数据
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
static D_Result ad_prepare_data(D_AdEsData  *es, D_U8 num)D_FUNCPOSTFIT
{
    D_Ptr        ptr = NULL;
    D_Size size;
    if(es->stflag[num] == DAD_ST_CLOSE)
        return D_ERR;
    if(!es->op->get_img)
        return D_ERR;
    if((D_Ad_Pos_Type)num == DAD_STB_PICOSD)
    {
        return D_ERR;
    }
    if((D_Ad_Pos_Type)num == DAD_STB_OSD)
    {
        D_Ad_Osd_Param data;
        D_U8 idx;

        size = sizeof(D_Ad_Osd_Param);
        if(es->op->get_img(&es->param, (D_Ad_Pos_Type)num, es->index[num], (D_U8*)(&data)) == D_OK)
        {
            ptr = ad_mman_alloc(es->hmm, size);
            if(ptr == NULL)
                return D_ERR;
            d_sem_wait(es->hsem);
            memcpy(ptr, (D_U8*)(&data), size);
            if(d_dad_find_idle(es, num, &idx) == D_OK)
            {
                es->hand[num][idx] = ptr;
                if(data.uctotal <= (es->index[num] + 1))
                {
                    es->index[num] = 0;
                }
                else
                {
                    es->index[num] = es->index[num] + 1;
                }
                es->dataflag[num] = DAD_DATA_OK;
            }
            d_sem_post (es->hsem);
            if(D_INVALID_HANDLE == ades->htimer[num])
            {
                ades->htimer[num] = d_timer_create(NULL, 1000, ades->queue);
                DAD_DUMP("[ad]d_timer_create[%d]\n", ades->htimer[num]);
            }
            else
            {
                DAD_DUMP("[ad]d_timer_reset[%d]\n", ades->htimer[num]);
                d_timer_reset(ades->htimer[num], 1000);
            }

            return D_OK;
        }
        else
        {
            if(D_INVALID_HANDLE == ades->htimer[num])
            {
                ades->htimer[num] = d_timer_create(NULL, 1000, ades->queue);
                DAD_DUMP("[ad]d_timer_create[%d]\n", ades->htimer[num]);
            }
            else
            {
                DAD_DUMP("[ad]d_timer_reset[%d]\n", ades->htimer[num]);
                d_timer_reset(ades->htimer[num], 1000);
            }
        }

    }
    else
    {
        D_Ad_Image_Param data;
        size = sizeof(D_Ad_Image_Param);
        if(es->op->get_img(&es->param, (D_Ad_Pos_Type)num, es->index[num], (D_U8*)(&data)) == D_OK)
        {
            D_U8 idx;
            ptr = ad_mman_alloc(es->hmm, size);
            if(ptr == NULL)
                return D_ERR;
            d_sem_wait(es->hsem);
            memcpy(ptr, (D_U8*)(&data), size);

            if(d_dad_find_idle(es, num, &idx) == D_OK)
            {
                es->hand[num][idx] = ptr;
                if(data.uctotal <= (es->index[num] + 1))
                {
                    es->index[num] = 0;
                }
                else
                {
                    es->index[num] = es->index[num] + 1;
                }
                es->dataflag[num] = DAD_DATA_OK;
            }
            d_sem_post (es->hsem);
            if((D_Ad_Pos_Type)num == DAD_STB_FULLSCREEN)
            {
                if(D_INVALID_HANDLE == ades->htimer[num])
                {
                    ades->htimer[num] = d_timer_create(NULL, 100, ades->queue);
                    DAD_DUMP("[ad]d_timer_create[%d]\n", ades->htimer[num]);
                }
                else
                {
                    DAD_DUMP("[ad]d_timer_reset[%d]\n", ades->htimer[num]);
                    d_timer_reset(ades->htimer[num], 100);
                }
            }
            else
            {
                if(D_INVALID_HANDLE != ades->htimer[num])
                {
                    DAD_DUMP("[ad]d_timer_destroy[%d]\n", ades->htimer[num]);
                    d_timer_destroy(ades->htimer[num]);
                }
            }
            return D_OK;
        }
        else
        {
            if(D_INVALID_HANDLE == ades->htimer[num])
            {
                ades->htimer[num] = d_timer_create(NULL, 1000, ades->queue);
                DAD_DUMP("[ad]d_timer_create[%d]\n", ades->htimer[num]);
            }
            else
            {
                DAD_DUMP("[ad]d_timer_reset[%d]\n", ades->htimer[num]);
                d_timer_reset(ades->htimer[num], 1000);
            }
        }

    }

    return  D_ERR;
}
static D_Result Erase_data(D_AdEsData  *es, D_U8 num)D_FUNCPOSTFIT
{
    D_Ptr        ptr = NULL;
    D_Size size;
    if(es->stflag[num] == DAD_ST_CLOSE)
        return D_ERR;
    if(!es->op->get_img)
        return D_ERR;
    if((D_Ad_Pos_Type)num == DAD_STB_PICOSD)
    {
        return D_ERR;
    }
    if((D_Ad_Pos_Type)num == DAD_STB_OSD)
    {
        D_Ad_Osd_Param data;
        D_U8 idx;

        size = sizeof(D_Ad_Osd_Param);
        ptr = ad_mman_alloc(es->hmm, size);
        if(ptr == NULL)
            return D_ERR;
        d_sem_wait(es->hsem);
				data.if_erase = 0xff;
				data.data_rsc_ptr = NULL;
        memcpy(ptr, (D_U8*)(&data), size);
        if(d_dad_find_idle(es, num, &idx) == D_OK)
        {
            es->hand[num][idx] = ptr;
            if(data.uctotal <= (es->index[num] + 1))
            {
                es->index[num] = 0;
            }
            else
            {
                es->index[num] = es->index[num] + 1;
            }
            es->dataflag[num] = DAD_DATA_OK;
        }
        d_sem_post (es->hsem);

        return D_OK;
    }
    else
    {
        D_U8 idx;
        D_Ad_Image_Param data;
				
        size = sizeof(D_Ad_Image_Param);
        ptr = ad_mman_alloc(es->hmm, size);
        if(ptr == NULL)
            return D_ERR;
        d_sem_wait(es->hsem);
				data.if_erase = 0xff;
				data.data_rsc_ptr = NULL;
        memcpy(ptr, (D_U8*)(&data), size);

        if(d_dad_find_idle(es, num, &idx) == D_OK)
        {
            es->hand[num][idx] = ptr;
            if(data.uctotal <= (es->index[num] + 1))
            {
                es->index[num] = 0;
            }
            else
            {
                es->index[num] = es->index[num] + 1;
            }
            es->dataflag[num] = DAD_DATA_OK;
        }
        d_sem_post (es->hsem);

        return D_OK;

    }

    return  D_ERR;
}

/** @brief  换台操作的时候清楚所有保存的数据信息
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
static void ad_change_chan(D_AdEsData   *es)D_FUNCPOSTFIT
{
    D_U8 i, j;

    for(i = (D_U8)DAD_STB_LOG; i < DAD_STB_POS_UNKNOWN; i ++)
    {
        for(j = 0; j < DAD_PIC_TOTAL_TYPE; j ++)
        {
            if(es->hand[i][j] != NULL)
            {
                if((D_Ad_Pos_Type)i == DAD_STB_OSD)
                {
#if 0
                    D_Ad_Osd_Param* datahandle = (D_Ad_Osd_Param*)es->hand[i][j];
                    if(es->op->release_img)
                        es->op->release_img((D_Ad_Pos_Type)i, (D_U8*)datahandle->data_rsc_ptr);
                    ad_mman_free(es->hmm, (D_Ptr)es->hand[i][j]);
#endif
                }
                else
                {
                    D_Ad_Image_Param* datahandle = (D_Ad_Image_Param*)es->hand[i][j];
                    if(es->op->release_img)
                        es->op->release_img((D_Ad_Pos_Type)i, (D_U8*)datahandle->data_rsc_ptr);
                    ad_mman_free(es->hmm, (D_Ptr)es->hand[i][j]);
                }
                es->hand[i][j] = NULL;
            }
        }
        if(D_INVALID_HANDLE != es->htimer[i])
        {
            DAD_DUMP("[ad]d_timer_destroy[%d]\n", es->htimer[i]);
            d_timer_destroy(es->htimer[i]);
            es->htimer[i] = D_INVALID_HANDLE;
        }
        es->dataflag[i] = DAD_DATA_WAIT;
        es->index[i] = 0;
    }
}
/** @brief  清楚一个应用的数据
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
static void ad_req_data(D_AdEsData  *es, D_U8 num)D_FUNCPOSTFIT
{
    D_U8 i, j;
    i = num;
    for(j = 0; j < DAD_PIC_TOTAL_TYPE; j ++)
    {
        if(es->hand[i][j] != NULL)
        {
            if((D_Ad_Pos_Type)i == DAD_STB_OSD)
            {
                D_Ad_Osd_Param* datahandle = (D_Ad_Osd_Param*)es->hand[i][j];
                if(es->op->release_img)
                    es->op->release_img((D_Ad_Pos_Type)i, (D_U8*)datahandle->data_rsc_ptr);
                ad_mman_free(es->hmm, (D_Ptr)es->hand[i][j]);
            }
            else
            {
                D_Ad_Image_Param* datahandle = (D_Ad_Image_Param*)es->hand[i][j];
                if(es->op->release_img)
                    es->op->release_img((D_Ad_Pos_Type)i, (D_U8*)datahandle->data_rsc_ptr);
                ad_mman_free(es->hmm, (D_Ptr)es->hand[i][j]);
            }
            es->hand[i][j] = NULL;
        }
    }
    if(D_INVALID_HANDLE != es->htimer[i])
    {
        DAD_DUMP("[ad]d_timer_destroy[%d]\n", es->htimer[i]);
        d_timer_destroy(es->htimer[i]);
        es->htimer[i] = D_INVALID_HANDLE;
    }
    es->dataflag[i] = DAD_DATA_WAIT;
    es->index[i] = 0;
}

/** @brief  判断过滤器是否可以共用
* @param[in]
* @return 成功返回过滤器id,失败返回D_INVALID_HANDLE
*/
static D_Handle ad_check_filter(D_AdScanEsData  *es, D_DemuxFilter *filter, D_DemuxType   type)D_FUNCPOSTFIT
{
    D_U8 i;

    for(i = 0; i <= es->maxdemux; i ++)
    {
        if((es->back[i].use_flag == 1) && (D_INVALID_HANDLE != es->back[i].hdemux))
        {
            if((es->filter[i].pid == filter->pid) \
            && (es->dmx_attr[i].type == type)\
            && ((es->filter[i].sec.filter[0] == filter->sec.filter[0])\
            && (es->filter[i].sec.mask[0] == filter->sec.mask[0]) || (filter->sec.length == 0) || (es->filter[i].sec.length == 0)))
            {
                return adscan->back[i].hdemux;
            }
        }
    }

    return D_INVALID_HANDLE;
}

/** @brief  重新计算新的过滤条件
* @param[in]
* @return 成功返回过滤器id,失败返回D_INVALID_HANDLE
*/
static D_Result ad_get_newfilter(D_AdScanEsData  *es, D_HDemux    hdemux, D_DemuxFilter *newfilter)D_FUNCPOSTFIT
{
    D_U8 i, j, head = 1;
    D_Result ret = D_ERR;

    d_sec_filter_init (newfilter);

    ///处理多个相同pid的数据请求
    for(i = 0; i <= es->maxdemux; i ++)
    {
        if((es->back[i].use_flag == 1) && (es->back[i].hdemux == hdemux))
        {
            if(es->dmx_attr[i].type == D_DEMUX_SEC)
            {
                ret = D_OK;
                if(head == 1)
                {
                    memcpy((D_U8*)newfilter, (D_U8*)(&es->filter[i]), sizeof(D_DemuxFilter));
                    head = 0;
                }
                else
                {
                    D_U8  mask;

                    newfilter->sec.length = (newfilter->sec.length >= es->filter[i].sec.length)\
                                            ? newfilter->sec.length : es->filter[i].sec.length;
                    for(j = 0; j <= newfilter->sec.length; j ++)
                    {
                        mask = newfilter->sec.filter[j] ^ es->filter[i].sec.filter[j];
                        mask = ~mask;
                        newfilter->sec.filter[j] &= es->filter[i].sec.filter[j];

                        newfilter->sec.mask[j] &= es->filter[i].sec.mask[j];
                        newfilter->sec.mask[j] &= mask;

                        newfilter->sec.positive[j] &= es->filter[i].sec.positive[j];
                        newfilter->sec.positive[j] &= mask;

                    }
                }
            }
        }
    }
#if 0
    D_DUMP("filter:");
    for(i = 0; i < 16; i ++)
    {
        D_DUMP("[0x%x]", newfilter->sec.filter[i]);
    }
    D_DUMP("\n mask:");
    for(i = 0; i < 16; i ++)
    {
        D_DUMP("[0x%x]", newfilter->sec.mask[i]);
    }
    D_DUMP("\n positive:");
    for(i = 0; i < 16; i ++)
    {
        D_DUMP("[0x%x]", newfilter->sec.positive[i]);
    }
    D_DUMP("\n");
#endif
    return ret;
}

/*提供底层的回调函数*/
static D_Handle ad_EventCallback(D_U8 event, D_Ad_Event_Param *param)
{
    D_U8 i;
    switch(event)
    {
        case DAD_EVENT_CREATE_DEMUX: // 创建通道
        {
            for(i = 0; i < DAD_DEMUX_TOTAL_TYPE; i ++)
            {
                if(adscan->back[i].use_flag == 0)
                {
                    d_mutex_lock(adscan->back[i].hm);
                    adscan->back[i].Function = NULL;
                    adscan->back[i].use_flag = 1;
                    adscan->back[i].hdemux = D_INVALID_HANDLE;
                    memset((D_U8*)(&adscan->filter[i]), 0, sizeof(D_DemuxFilter));
                    adscan->maxdemux = (i > adscan->maxdemux) ? i : adscan->maxdemux;
                    d_mutex_unlock(adscan->back[i].hm);
                    return i;
                }
            }
            return D_INVALID_HANDLE;
        }
        case DAD_EVENT_START_DEMUX: // 开启通道
        {
            if((param->hdemux <= adscan->maxdemux) && (param->param.param1 != 0))
            {
                D_U8 id;

                id = param->hdemux;
                if(adscan->back[id].use_flag == 1)
                {
                    D_DemuxFilter *filter;
                    D_DemuxAttr    dmx_attr;
                    D_HDemux       hdemux;
                    D_DemuxFilter newfilter;

                    filter = (D_DemuxFilter *)param->param.param3;
                    adscan->back[id].hdemux = ad_check_filter(adscan, filter, param->type);
                    if(adscan->back[id].hdemux == D_INVALID_HANDLE)
                    {
                        /*初始化demux*/
                        D_DEMUX_ATTR_INIT (&dmx_attr);
                        dmx_attr.buf_size = param->buf_size;
                        dmx_attr.type = param->type;
                        hdemux = d_demux_create(&dmx_attr, adscan->queue);
                        if(D_INVALID_HANDLE == hdemux)
                        {
                            DAD_ERROR ("[ad]d_demux_create\n");
                            return D_INVALID_HANDLE;
                        }
                        DAD_DUMP("[ad]d_demux_create[%d]\n", hdemux);
                        adscan->back[id].hdemux = hdemux;
                        memcpy((D_U8*)(&adscan->dmx_attr[id]), &dmx_attr, sizeof(D_DemuxAttr));
                    }
                    memcpy((D_U8*)(&adscan->filter[id]), (D_U8*)filter, sizeof(D_DemuxFilter));
                    if(ad_get_newfilter(adscan, adscan->back[id].hdemux, &newfilter) ==  D_OK)
                    {
                        d_mutex_lock(adscan->back[id].hm);
                        DAD_DUMP("[ad]d_demux_start[%d]\n", param->hdemux);
                        adscan->back[id].Function = param->Function;
                        adscan->back[id].param.param1 = param->param.param1;
                        adscan->back[id].param.param2 = param->param.param2;

                        d_demux_stop(adscan->back[id].hdemux);
                        if(d_demux_set_filter (adscan->back[id].hdemux, &newfilter) < 0)
                        {
                            DAD_ERROR ("[ad]d_demux_set_filter\n");
                            return D_INVALID_HANDLE;
                        }
                        d_demux_start(adscan->back[id].hdemux);
                        if(param->starttime != 0 && param->starttime != 0xffffffff)
                        {
                            D_TimerAttr attr;
                            attr.one_shot = 0;
                            adscan->back[id].htimer = d_timer_create(&attr, param->starttime, adscan->queue);
                            if(D_INVALID_HANDLE == adscan->back[id].htimer)
                            {
                                DAD_ERROR ("[ad]Cannot create timer\n");
                                d_mutex_unlock(adscan->back[id].hm);
                                return D_INVALID_HANDLE;
                            }
                            DAD_DUMP("[ad]d_timer_create[%d]\n", adscan->back[id].htimer);
                        }
                        d_mutex_unlock(adscan->back[id].hm);
                        ///
                        return id;
                    }
                }
            }
            return D_INVALID_HANDLE;
        }
        case DAD_EVENT_STOP_DEMUX://停止通道
        {
            if(param->hdemux <= adscan->maxdemux)
            {
                D_U8 id;
                D_HDemux    hdemux;
                D_DemuxFilter newfilter;

                id = param->hdemux;

                hdemux = adscan->back[id].hdemux;

                if((adscan->back[id].use_flag == 1) && (D_INVALID_HANDLE != hdemux))
                {
                    d_mutex_lock(adscan->back[id].hm);
                    if(D_INVALID_HANDLE != adscan->back[id].htimer)
                    {
                        DAD_DUMP("[ad]d_timer_destroy[%d]\n", adscan->back[id].htimer);
                        d_timer_destroy (adscan->back[id].htimer);
                        adscan->back[id].htimer = D_INVALID_HANDLE;
                    }
                    adscan->back[id].hdemux = D_INVALID_HANDLE;
                    adscan->back[id].Function = NULL;
                    if(ad_get_newfilter(adscan, hdemux, &newfilter) == D_ERR)
                    {
                        DAD_DUMP("[ad]d_demux_stop[%d]\n", hdemux);
                        d_demux_stop(hdemux);
                        DAD_DUMP("[ad]d_demux_destroy[%d]\n", hdemux);
                        d_demux_destroy(hdemux);
                    }
                    else
                    {
                        d_demux_stop(hdemux);
                        if(d_demux_set_filter (hdemux, &newfilter) < 0)
                        {
                            DAD_ERROR ("[ad]d_demux_set_filter\n");
                            return D_INVALID_HANDLE;
                        }
                        d_demux_start(hdemux);
                    }
                    d_mutex_unlock(adscan->back[id].hm);
                    return param->hdemux;
                }
            }
            return D_INVALID_HANDLE;
        }
        case DAD_EVENT_DESTROY_DEMUX://销毁通道
        {
            if(param->hdemux <= adscan->maxdemux)
            {
                D_HDemux    hdemux;
                D_U8 id;
                D_DemuxFilter newfilter;

                id = param->hdemux;

                hdemux = adscan->back[id].hdemux;

                if((adscan->back[id].use_flag == 1) && (D_INVALID_HANDLE != hdemux))
                {
                    d_mutex_lock(adscan->back[id].hm);
                    if(D_INVALID_HANDLE != adscan->back[id].htimer)
                    {
                        DAD_DUMP("[ad]d_timer_destroy[%d]\n", adscan->back[id].htimer);
                        d_timer_destroy (adscan->back[id].htimer);
                        adscan->back[id].htimer = D_INVALID_HANDLE;
                    }
                    adscan->back[id].hdemux = D_INVALID_HANDLE;
                    adscan->back[id].use_flag = 0;
                    adscan->back[id].Function = NULL;
//                  if(adscan->maxdemux == id)
                    {
                        D_U8 j, max = 0;
                        for(j = 0; j <= adscan->maxdemux; j ++)
                        {
                            if(adscan->back[j].use_flag == 1)
                            {
                                max  = (j > max ) ? j : max ;
                            }
                        }
                        adscan->maxdemux = max;
                    }
                    if(ad_get_newfilter(adscan, hdemux, &newfilter) == D_ERR)
                    {
                        DAD_DUMP("[ad]d_demux_stop[%d]\n", hdemux);
                        d_demux_stop(hdemux);
                        DAD_DUMP("[ad]d_demux_destroy[%d]\n", hdemux);
                        d_demux_destroy(hdemux);
                    }
                    else
                    {
                        d_demux_stop(hdemux);
                        if(d_demux_set_filter (hdemux, &newfilter) < 0)
                        {
                            DAD_ERROR ("[ad]d_demux_set_filter\n");
                            return D_INVALID_HANDLE;
                        }
                        d_demux_start(hdemux);
                    }
                    d_mutex_unlock(adscan->back[id].hm);

                    return 0;
                }
            }
            return D_INVALID_HANDLE;
        }
        case DAD_EVENT_CREATE_TIMER://用作定时器
        {
            for(i = 0; i < DAD_TIMER_TOTAL_TYPE; i ++)
            {
                if(ades->back[i].use_flag == 0)
                {
                    D_HTimer    htimer;
                    D_TimerAttr attr;

                    attr.one_shot = param->one_shot;
                    d_mutex_lock(ades->back[i].hm);
                    ades->back[i].Function = param->Function;
                    ades->back[i].param.param1 = param->param.param1;
                    ades->back[i].param.param2 = param->param.param2;
                    ades->back[i].hdemux = D_INVALID_HANDLE;
                    htimer = d_timer_create(&attr, param->starttime, ades->queue);
                    if(D_INVALID_HANDLE == htimer)
                    {
                        DAD_ERROR ("[ad]Cannot create timer\n");
                        d_mutex_unlock(ades->back[i].hm);
                        return D_INVALID_HANDLE;
                    }
                    ades->back[i].htimer = htimer;
                    ades->back[i].one_shot = param->one_shot;
                    DAD_DUMP("[ad]d_timer_create[%d]\n", ades->back[i].htimer);
                    ades->back[i].use_flag = 1;
                    d_mutex_unlock(ades->back[i].hm);
                    return htimer;
                }
            }
            return D_INVALID_HANDLE;
        }
        case DAD_EVENT_DESTROY_TIMER://关闭定时器
        {
            for(i = 0; i < DAD_TIMER_TOTAL_TYPE; i ++)
            {
                if(ades->back[i].use_flag == 1)
                {
                    if((D_INVALID_HANDLE != ades->back[i].htimer) && (param->htimer == ades->back[i].htimer))
                    {
                        d_mutex_lock(ades->back[i].hm);
                        DAD_DUMP("[ad]d_timer_destroy[%d]\n", ades->back[i].htimer);
                        d_timer_destroy (ades->back[i].htimer);
                        ades->back[i].htimer = D_INVALID_HANDLE;
                        ades->back[i].use_flag = 0;
                        ades->back[i].Function = NULL;
                        d_mutex_unlock(ades->back[i].hm);
                        return 1;
                    }
                }
            }
            return D_INVALID_HANDLE;
        }
        case DAD_EVENT_UPDATE_DATA://关闭定时器
        {
            ad_send_msg(DAD_UPDATE_DATA, (D_Ad_Pos_Type)param->param.param1, NULL, 0, 0, 0);
            return D_INVALID_HANDLE;
        }
        case DAD_EVENT_ERASE_DATA://关闭定时器
        {
            ad_send_msg(DAD_ERASE_DATA, (D_Ad_Pos_Type)param->param.param1, NULL, 0, 0, 0);
            return D_INVALID_HANDLE;
        }
        default:
            return D_INVALID_HANDLE;
    }
}

/*处理广告任务的消息*/
static D_Result ad_deal_msg(D_AdMsg *msg, D_AdEsData *es)D_FUNCPOSTFIT
{
    D_Ad_Msg_Type para1 = (D_Ad_Msg_Type)(msg->param1);
    D_Ad_Pos_Type para2 = (D_Ad_Pos_Type)(msg->param2);

    switch(para1)
    {
        case DAD_APP_INIT:
        {
            es->param.usNetworkId = msg->usNetworkId;
            es->param.usTsId = msg->usTsId;
            es->param.usServiceId = msg->usServiceId;

            ad_init_app(es, para2);
            es->stflag[para2] = DAD_ST_OPEN;
            if(es->op->enter_app)
                es->op->enter_app(para2);
            ad_prepare_data(es, para2);
            d_sem_post (es->hsem1);
            break;
        }
        case DAD_APP_EXIT:
        {
            ad_exit_app(es, (D_U8)para2);
            if(es->op->exit_app)
                es->op->exit_app(para2);
            d_sem_post (es->hsem1);
            break;
        }
        case DAD_SET_PARAM:
        {
            D_U8 i;
            es->param.usNetworkId = msg->usNetworkId;
            es->param.usTsId = msg->usTsId;
            es->param.usServiceId = msg->usServiceId;
            ad_change_chan(es);
            if(es->op->reset)
                es->op->reset();

            for(i = 0; i < DAD_STB_POS_UNKNOWN; i ++)
            {
                ad_prepare_data(es, i);
            }

            d_sem_post (es->hsem1);
            break;
        }
        case DAD_RESET_DATA:
        {
            ad_req_data(es, (D_U8)para2);
            ad_prepare_data(es, (D_U8)para2);
            d_sem_post (es->hsem1);
            break;
        }
        case DAD_APP_RELEASEDATA:
        {
            if(msg->handle != NULL)
            {
                if((D_Ad_Pos_Type)para2 == DAD_STB_OSD)
                {
                    D_Ad_Osd_Param* datahandle = (D_Ad_Osd_Param*)msg->handle;
                    if(es->op->release_img)
                        es->op->release_img(para2, (D_U8*)datahandle->data_rsc_ptr);
                    ad_mman_free(es->hmm, (D_Ptr)msg->handle);
                    ad_prepare_data(es, para2);
                }
                else
                {
                    D_Ad_Image_Param* datahandle = (D_Ad_Image_Param*)msg->handle;
                    if(es->op->release_img)
                        es->op->release_img(para2, (D_U8*)datahandle->data_rsc_ptr);
                    ad_mman_free(es->hmm, (D_Ptr)msg->handle);
                }
            }
            d_sem_post (es->hsem1);
            break;
        }
        case DAD_UPDATE_DATA:
        {
						ad_prepare_data(es, para2);
            break;
        }
        case DAD_ERASE_DATA:
        {
            Erase_data(es, para2);
            break;
        }

        default:
            break;
    }
    return D_OK;
}

/** 初始化广告任务的资源*/
static D_AdEsData* ad_start (d_ad_config *cfg)D_FUNCPOSTFIT
{
    D_AdEsData  *es;
    D_U8    *buf;
    D_U8    i, j;
    D_HMMan hmm;
    D_HSem  hsem;
    D_SemAttr attr;
    D_MutexAttr mattr;

    buf = (D_U8*) d_mem_alloc (0, D_AD_CTRL_MM_SIZE);//分配内存的大小
    if(! buf)
    {
        DAD_ERROR ("Cannot allocate ad scan memory\n");
        return NULL;
    }

    hmm = d_mman_create (buf, D_AD_CTRL_MM_SIZE, D_MMAN_HEAP);//创建一个内存管理器
    DAD_DUMP("[ad]ad_start[buf:0x%x][hmm:0x%x][size:0x%x]\n", buf, hmm, D_AD_CTRL_MM_SIZE);

    if(D_INVALID_HANDLE == hmm)
    {
        DAD_ERROR ("[ad]Cannot create memory manager\n");
        d_mem_free (buf);
        return NULL;
    }

    es = (D_AdEsData*) ad_mman_alloc (hmm, sizeof (D_AdEsData));//通过内存管理器分配一块内存
    if(! es)
    {
        DAD_ERROR ("[ad]Cannot allocate ad scan data\n");
        d_mman_destroy (hmm);
        d_mem_free (buf);
        return NULL;
    }
    DAD_DUMP("[ad]ad_mman_alloc[es:0x%x]\n", es);
    memset(es, 0, sizeof (D_AdEsData));

    es->hmm = hmm;
    es->buf = buf;
    es->op = (D_Ad_Op*)d_dad_getop();
    if(es->op == NULL)
    {
        DAD_ERROR ("[ad]Cannot allocate ad scan buf data\n");
        d_mman_destroy (hmm);
        d_mem_free (buf);
        return NULL;
    }
    es->type = cfg->type;
    es->ttag[AD_STB_HAIERV2] = cfg->hitag ;                 /*广告TAG*/
    es->ttag[AD_STB_DESAI]  = cfg->dstag ;                  /*广告TAG*/
    es->ttag[AD_STB_MG]     = cfg->mgtag ;                  /*广告TAG*/
    es->ttag[AD_STB_IFABOO] = cfg->ifabootag;               /*广告TAG*/

    es->ucPriority = cfg->ucPriority;
    es->uiFlashStartAddress = cfg->uiFlashStartAddress;

    es->hsem = D_INVALID_HANDLE;
    D_SEM_ATTR_INIT (&attr);
    hsem = d_sem_create (&attr);
    es->hsem = hsem;
    d_sem_post (es->hsem);

    es->hsem1 = D_INVALID_HANDLE;
    D_SEM_ATTR_INIT (&attr);
    hsem = d_sem_create (&attr);
    es->hsem1 = hsem;
    d_sem_post (es->hsem1);
    for(i = 0; i < DAD_STB_POS_UNKNOWN; i ++)
    {
        es->htimer[i] = D_INVALID_HANDLE;
        es->stflag[i] = DAD_ST_CLOSE;
        es->dataflag[i] = DAD_DATA_WAIT;
        es->index[i] = 0;
        for(j = 0; j < DAD_STB_POS_UNKNOWN; j ++)
        {
            es->hand[i][j] = NULL;
        }
    }
    for(i = 0; i < DAD_TIMER_TOTAL_TYPE; i ++)
    {
        es->back[i].htimer = D_INVALID_HANDLE;
        es->back[i].hdemux = D_INVALID_HANDLE;
        es->back[i].Function = NULL;
        es->back[i].use_flag = 0;
        D_MUTEX_ATTR_INIT(&mattr);
        es->back[i].hm = d_mutex_create(&mattr);

    }
    return es;
}

/** @brief  销毁广告任务分配的资源*/
static D_Result ad_stop (D_AdEsData *es)D_FUNCPOSTFIT
{
    D_U8 i;
    D_U8 *buf = es->buf;

    if(es->hsem != D_INVALID_HANDLE)
    {
        d_sem_destroy (es->hsem);
        es->hsem = D_INVALID_HANDLE;
    }
    if(es->hsem1 != D_INVALID_HANDLE)
    {
        d_sem_destroy (es->hsem1);
        es->hsem1 = D_INVALID_HANDLE;
    }

    for(i = 0; i < DAD_STB_POS_UNKNOWN; i ++)
    {
        if(D_INVALID_HANDLE != es->htimer[i])
        {
            DAD_DUMP("[ad]d_timer_destroy[%d]\n", es->htimer[i]);
            d_timer_destroy (es->htimer[i]);
            es->htimer[i] = D_INVALID_HANDLE;
        }
    }
    for(i = 0; i < DAD_TIMER_TOTAL_TYPE; i ++)
    {
        if(D_INVALID_HANDLE != es->back[i].htimer)
        {
            DAD_DUMP("[ad]d_timer_destroy[%d]\n", es->back[i].htimer);
            d_timer_destroy (es->back[i].htimer);
            es->back[i].htimer = D_INVALID_HANDLE;
        }
        if(es->back[i].hdemux != D_INVALID_HANDLE)
        {
            DAD_DUMP("[ad]d_demux_stop[%d]\n", es->back[i].hdemux);
            d_demux_stop(es->back[i].hdemux);
            DAD_DUMP("[ad]d_demux_destroy[%d]\n", es->back[i].hdemux);
            d_demux_destroy(es->back[i].hdemux);
            es->back[i].hdemux = D_INVALID_HANDLE;
        }
        d_mutex_destroy (es->back[i].hm);
        es->back[i].hm = D_INVALID_HANDLE;

        es->back[i].use_flag = 0;
        es->back[i].Function = NULL;
    }
    if(D_INVALID_HANDLE != es->hmm)
    {
        DAD_DUMP("[ad]d_mman_destroy[ es->hmm:0x%x]\n", es->hmm);
        d_mman_destroy (es->hmm);
        es->hmm = D_INVALID_HANDLE;
    }
    if(buf)
    {
        DAD_DUMP("[ad]d_mem_free[buf:0x%x]\n", buf);
        d_mem_free (buf);
    }
    return D_OK;
}

/** 初始化广告搜索任务的资源*/
static D_AdScanEsData* ad_scan_start (void)D_FUNCPOSTFIT
{
    D_AdScanEsData  *es;
    D_U8    *buf;
    D_HMMan hmm;
    D_U8    i;
    D_MutexAttr mattr;

    buf = (D_U8*) d_mem_alloc (0, D_AD_SCAN_MM_SIZE); //分配内存的大小
    if(! buf)
    {
        DAD_ERROR ("Cannot allocate ad scan memory\n");
        return NULL;
    }

    hmm = d_mman_create (buf, D_AD_SCAN_MM_SIZE, D_MMAN_HEAP);//创建一个内存管理器
    DAD_DUMP("[ad]ad_scan_start[buf:0x%x][hmm:0x%x][size:0x%x]\n", buf, hmm, D_AD_SCAN_MM_SIZE);

    if(D_INVALID_HANDLE == hmm)
    {
        DAD_ERROR ("[ad]Cannot create memory manager\n");
        d_mem_free (buf);
        return NULL;
    }

    es = (D_AdScanEsData*) ad_mman_alloc (hmm, sizeof (D_AdScanEsData));//通过内存管理器分配一块内存
    if(! es)
    {
        DAD_ERROR ("[ad]Cannot allocate ad scan data\n");
        d_mman_destroy (hmm);
        d_mem_free (buf);
        return NULL;
    }
    memset(es, 0, sizeof (D_AdScanEsData));

    DAD_DUMP("[ad]ad_mman_alloc[es:0x%x]\n", es);
    es->sec = (D_U8*) ad_mman_alloc (hmm, D_AD_SCAN_SEC_BUF_SIZE);//通过内存管理器分配一块内存
    if(!  es->sec)
    {
        DAD_ERROR ("[ad]Cannot allocate ad scan buf data\n");
        d_mman_destroy (hmm);
        d_mem_free (buf);
        return NULL;
    }
    DAD_DUMP("[ad]ad_mman_alloc[es:0x%x]\n", es->sec);


    es->hmm = hmm;
    es->buf = buf;
    for(i = 0; i < DAD_DEMUX_TOTAL_TYPE; i ++)
    {
        es->back[i].htimer = D_INVALID_HANDLE;
        es->back[i].hdemux = D_INVALID_HANDLE;
        es->back[i].Function = NULL;
        es->back[i].use_flag = 0;
        D_MUTEX_ATTR_INIT(&mattr);
        es->back[i].hm = d_mutex_create(&mattr);
    }
    return es;
}

/** @brief  销毁广告搜索任务分配的资源*/
static D_Result ad_scan_stop (D_AdScanEsData *es)D_FUNCPOSTFIT
{
    D_U8 i;
    D_U8 *buf = es->buf;

    for(i = 0; i < DAD_DEMUX_TOTAL_TYPE; i ++)
    {
        if(D_INVALID_HANDLE != es->back[i].htimer)
        {
            DAD_DUMP("[ad]d_timer_destroy[%d]\n", es->back[i].htimer);
            d_timer_destroy (es->back[i].htimer);
            es->back[i].htimer = D_INVALID_HANDLE;
        }
        if(es->back[i].hdemux != D_INVALID_HANDLE)
        {
            DAD_DUMP("[ad]d_demux_stop[%d]\n", es->back[i].hdemux);
            d_demux_stop(es->back[i].hdemux);
            DAD_DUMP("[ad]d_demux_destroy[%d]\n", es->back[i].hdemux);
            d_demux_destroy(es->back[i].hdemux);
            es->back[i].hdemux = D_INVALID_HANDLE;
        }
        d_mutex_destroy (es->back[i].hm);
        es->back[i].hm = D_INVALID_HANDLE;
        es->back[i].use_flag = 0;
        es->back[i].Function = NULL;

    }
    if(D_INVALID_HANDLE != es->hmm)
    {
        DAD_DUMP("[ad]d_mman_destroy[ es->hmm:0x%x]\n", es->hmm);
        d_mman_destroy (es->hmm);
        es->hmm = D_INVALID_HANDLE;
    }
    if(buf)
    {
        DAD_DUMP("[ad]d_mem_free[buf:0x%x]\n", buf);
        d_mem_free (buf);
    }
    return D_OK;
}

/** @brief 广告任务主处理函数*/
static D_Result ad_callback (D_Msg *msg)D_FUNCPOSTFIT
{
    D_AdEsData  *es;

    es = (D_AdEsData*) d_app_get_data (d_app_self ());

    switch (msg->type)
    {
        case D_MSG_APP_CREATE:
            es = msg->app.arg;
            d_app_set_data (d_app_self (), (D_Ptr) es);
            es->queue = d_app_get_queue (d_app_self ());
            break;
        case D_MSG_USER:
            ad_deal_msg((D_AdMsg*)msg, es);
            break;
        case D_MSG_TIMER:
        {
            ADFunctionBack Function;
            D_AdFunBack param;
            D_U8 i;
            for(i = 0; i < DAD_TIMER_TOTAL_TYPE; i ++)
            {
                if(es->back[i].use_flag == 1)
                {
                    if(msg->timer.htimer == es->back[i].htimer)
                    {
                        d_mutex_lock(es->back[i].hm);
                        if(es->back[i].one_shot)
                        {
                            DAD_DUMP("[ad]d_timer_destroy[%d]\n", es->back[i].htimer);
                            d_timer_destroy (es->back[i].htimer);
                            es->back[i].htimer = D_INVALID_HANDLE;
                            es->back[i].use_flag = 0;
                        }
                        Function = es->back[i].Function;
                        memcpy((D_U8*)(&param), (D_U8*)(&(es->back[i].param)), sizeof(D_AdFunBack));
                        d_mutex_unlock(es->back[i].hm);
                        if(Function)
                        {
                            Function(&param, NULL, 0);
                        }
                        return D_OK;
                    }
                }
            }
            for(i = 0; i < DAD_STB_POS_UNKNOWN; i ++)
            {
                if(msg->timer.htimer == es->htimer[i])
                {
                    DAD_DUMP("[ad]d_timer_destroy[%d]\n", es->htimer[i]);
                    d_timer_destroy (es->htimer[i]);
                    es->htimer[i] = D_INVALID_HANDLE;
                    ad_prepare_data(es, i);
                    return D_OK;
                }
            }
        }
        break;
        case D_MSG_APP_DESTROY:
        {
            D_U8 i;

            for(i = 0; i < DAD_STB_POS_UNKNOWN; i ++)
            {
                ad_exit_app(es, i);
            }
            if(es->op->exit)
                es->op->exit();

            ad_stop (es);
        }
        break;
        default:
            break;
    }

    return D_OK;
}
static D_Result ad_filter_match(D_AdScanEsData *es, D_U8 *sec, D_U8 id)D_FUNCPOSTFIT
{
    if(es->dmx_attr[id].type == D_DEMUX_SEC)
    {
        D_U8 i, *data = sec;
        D_U8  *match = &(es->filter[id].sec.filter[0]); /**< 过滤器*/
        D_U8  *mask   = &(es->filter[id].sec.mask[0]);  /**< 过滤器屏蔽位*/
        D_U8  length = (es->filter[id].sec.length); /**< Section filter长度*/

        for(i = 0; i < length; i ++)
        {
            if((data[i]&mask[i]) != (match[i] & mask[i]))
                return D_ERR;
        }
        return D_OK;
    }
    return D_ERR;
}
/** @brief 广告搜索任务主处理函数*/
static D_Result ad_callbackscan (D_Msg *msg)D_FUNCPOSTFIT
{
    D_AdScanEsData  *es;

    es = (D_AdScanEsData*) d_app_get_data (d_app_self ());

    switch (msg->type)
    {
        case D_MSG_APP_CREATE:
            es = msg->app.arg;
            d_app_set_data (d_app_self (), (D_Ptr) es);
            es->queue = d_app_get_queue (d_app_self ());
            break;
        case D_MSG_TIMER:
        {
            ADFunctionBack Function;
            D_AdFunBack param;
            D_U8 i;

            for(i = 0; i <= es->maxdemux; i ++)
            {
                if(es->back[i].use_flag == 1)
                {
                    if(msg->timer.htimer == es->back[i].htimer)
                    {
                        d_mutex_lock(es->back[i].hm);
                        Function = es->back[i].Function;
                        memcpy((D_U8*)(&param), (D_U8*)(&(es->back[i].param)), sizeof(D_AdFunBack));
                        d_mutex_unlock(es->back[i].hm);
                        if(Function)
                        {
                            Function(&param, NULL, 0);
                        }
                        return D_OK;
                    }
                }
            }
        }
        break;
        case D_MSG_DEMUX_DATA:
        {
            ADFunctionBack Function;
            D_AdFunBack param;
            D_Size   cnt;
            D_U8 i, first = 1;

            for(i = 0; i <= es->maxdemux; i ++)
            {
                if(es->back[i].use_flag == 1 && es->back[i].Function)
                {
                    if(msg->demux.hdemux == es->back[i].hdemux)
                    {
                        if(first ==  1)
                        {
                            cnt = d_demux_read (msg->demux.hdemux, es->sec, D_AD_SCAN_SEC_BUF_SIZE);
                            first = 0;
                        }
                        Function = NULL;
                        d_mutex_lock(es->back[i].hm);
                        if(ad_filter_match(es, es->sec, i) == D_OK)
                        {
                            Function = es->back[i].Function;
                            memcpy((D_U8*)(&param), (D_U8*)(&(es->back[i].param)), sizeof(D_AdFunBack));
                        }
                        d_mutex_unlock(es->back[i].hm);
                        if(cnt > 0 && Function)
                        {
                            if(D_INVALID_HANDLE != es->back[i].htimer)
                            {
                                DAD_DUMP("[ad]d_timer_destroy[%d]\n", es->back[i].htimer);
                                d_timer_destroy (es->back[i].htimer);
                                es->back[i].htimer = D_INVALID_HANDLE;
                            }
                            Function(&param, es->sec, (D_U32)cnt);
                        }
//                             return D_OK;
                    }
                }
            }
        }
        break;
        case D_MSG_APP_DESTROY:
            ad_scan_stop (es);
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 创建广告搜索任务*/
static D_Handle ad_scan_create( D_S8 priority)D_FUNCPOSTFIT
{
    D_Ad_Op*    op;

    op = (D_Ad_Op*)d_dad_getop();
    if(op == NULL)
    {
        return D_INVALID_HANDLE;
    }
    if(op->check_scan == NULL)
    {
        return D_INVALID_HANDLE;
    }
    if(op->check_scan() == D_ERR)
    {
        return D_INVALID_HANDLE;
    }

    /*分配空间*/
    adscan = ad_scan_start ();
    if(! adscan)
    {
        DAD_ERROR ("[ad]Cannot allocate ad scan data\n");
        ad_stop (ades);
        return D_INVALID_HANDLE;
    }
    /*创建搜索应用*/
    adscan->happ = d_app_create ("adscan", priority, D_AD_MODULE_TASK_STACK_SIZE, D_AD_MODULE_QUEUE_SIZE, ad_callbackscan, (D_Ptr)adscan);

    if(D_INVALID_HANDLE ==  adscan->happ)
    {
        DAD_ERROR ("[ad]Cannot create ad scan app\n");
        ad_scan_stop (adscan);
        return D_INVALID_HANDLE;
    }
    /*同步，等待设备创建完成*/
    d_app_sync (adscan->happ);

    return adscan->happ;
}

/** @brief 创建广告任务*/
static D_Handle ad_app_create(d_ad_config *cfg)D_FUNCPOSTFIT
{
    /*分配空间*/
    ades = ad_start (cfg);
    if(! ades)
    {
        DAD_ERROR ("[ad]Cannot allocate ad scan data\n");
        return D_INVALID_HANDLE;
    }

    /*创建应用*/
    ades->happ = d_app_create ("adapp", ades->ucPriority, D_AD_MODULE_TASK_STACK_SIZE, D_AD_MODULE_QUEUE_SIZE, ad_callback, (D_Ptr)ades);

    if(D_INVALID_HANDLE == ades->happ)
    {
        DAD_ERROR ("[ad]Cannot create ad scan app\n");
        ad_stop (ades);
        return ades->happ;
    }

    /*同步，等待设备创建完成*/
    d_app_sync (ades->happ);
    DAD_DUMP("[ad]d_ad_scan_create[es->happ:0x%x]\n", ades->happ);
    return ades->happ;
}

/** @brief 销毁任务*/
static D_Result ad_app_destroy (D_Handle app)D_FUNCPOSTFIT
{
    DAD_DUMP("[ad]d_ttx_scan_destroy[hscan:0x%x]\n", app);
    d_app_destroy (app);

    return D_OK;
}

/** @brief  打开广告模块
* @param[in] hscan 搜索句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ad_modlue_Open(d_ad_config *cfg)D_FUNCPOSTFIT
{
    D_HNVPart   hnvp = D_INVALID_HANDLE;
    D_NVPartInfo info;
    D_Ad_Init_Param  param;
    D_U8 i;

    hnvp = d_nvpart_create(D_DB_NVRAM_ID, D_NV_PART_LOGO);
    if(hnvp != D_INVALID_HANDLE)
    {
        if(d_nvpart_get_info (hnvp, &info) != D_OK)
        {
            DAD_ERROR("[adv]d_nvpart_get_info error!\n");
            return D_ERR;
        }
        cfg->uiFlashStartAddress = info.nv_offset;
    }
    else
    {
        DAD_ERROR("[adv]D_NV_PART_LOGO err!\n");
    }
    hscanapp = ad_scan_create(cfg->ucPriority);
    if(D_INVALID_HANDLE != hscanapp)
    {
        DAD_ERROR("[adv]ad_scan_create !\n");
        param.queue = adscan->queue;
    }

    happ = ad_app_create(cfg);
    if(D_INVALID_HANDLE == happ)
    {
        ad_app_destroy(hscanapp);
        return D_ERR;
    }
    if(ades->op->init)
    {
        for(i = 0; i < DAD_STB_POS_UNKNOWN; i ++)
        {
            ad_init_app(ades, i);
        }
        param.uiFlashStartAddress  = ades->uiFlashStartAddress;
        param.buf_size = D_AD_SCAN_BUF_SIZE;
        param.ucPriority = ades->ucPriority;
        param.type = ades->type;
        param.cb = ad_EventCallback;

        ades->op->init(&param);
        if(ades->op->settag)
        {
            for(i = 0; i < AD_STB_MAX; i ++)
            {
                ades->op->settag(ades->ttag[i], i);
            }
        }
    }
    return D_OK;
}

/** @brief 开启广告模块
* @param[in] hscan 搜索句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ad_modlue_start(D_Ad_Start_Param *cfg)D_FUNCPOSTFIT
{
    D_Ad_Start_Param param;
    if(!ades)
        return D_ERR;

    if(ades->op->start)
    {
        memcpy((D_U8*)&param, (D_U8*)cfg, sizeof(D_Ad_Start_Param));
        ades->op->start(&param);
    }
    return D_OK;
}

/** @brief  关闭广告模块
* @param[in] hscan 搜索句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ad_modlue_Close()D_FUNCPOSTFIT
{
    if(D_INVALID_HANDLE != hscanapp)
    {
        ad_app_destroy(hscanapp);
    }
    if(D_INVALID_HANDLE != happ)
    {
        ad_app_destroy(happ);
    }
    adscan = NULL;
    return D_OK;
}

/** @brief  打开广告应用
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ad_enter_menu_ex(D_Ad_Pos_Type type, D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT
{
    if(!ades)
        return D_ERR;

    ad_send_msg(DAD_APP_INIT, type, NULL, chan_param->usNetworkId, chan_param->usTsId, chan_param->usServiceId);
    d_sem_wait (ades->hsem1);
    d_sem_wait (ades->hsem1);
    d_sem_post (ades->hsem1);

    return D_OK;
}

/** @brief  退出广告应用
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ad_exit_menu_ex(D_Ad_Pos_Type type)D_FUNCPOSTFIT
{
    if(!ades)
        return D_ERR;

    ad_send_msg(DAD_APP_EXIT, type, NULL, 0, 0, 0);
    d_sem_wait (ades->hsem1);
    d_sem_wait (ades->hsem1);
    d_sem_post (ades->hsem1);

    return D_OK;
}

/** @brief  取广告信息
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Ptr d_ad_get_img_ex(D_Ad_Pos_Type type)D_FUNCPOSTFIT
{
    D_U8 i = type;
    D_U8 j;
    D_U32          times;       //显示时间
    D_Ptr pic = NULL;

    if(!ades)
        return NULL;

    d_sem_wait(ades->hsem);
    if((D_Ad_Pos_Type)type == DAD_STB_PICOSD)
    {
        D_Size size;
        D_Ad_Image_Param data;
        D_Ptr        ptr = NULL;

        size = sizeof(D_Ad_Image_Param);
        if(!ades->op->get_img)
            return NULL;
        if(ades->op->get_img(&ades->param, type, 0, (D_U8*)(&data)) == D_OK)
        {
            ptr = ad_mman_alloc(ades->hmm, size);
            if(ptr == NULL)
            {
                d_sem_post (ades->hsem);
                return NULL;
            }
            memcpy(ptr, (D_U8*)(&data), size);
            d_sem_post (ades->hsem);
            return ptr;
        }
        d_sem_post(ades->hsem);
        return NULL;
    }

    if(ades->dataflag[i] == DAD_DATA_OK)
    {
        for(j = 0; j < DAD_PIC_TOTAL_TYPE ; j++)
        {
            if(ades->hand[i][j] != NULL)
            {
                if(type == DAD_STB_OSD)
                {
                    pic = ades->hand[i][j];
                }
                else
                {
                    D_Ad_Image_Param *tmp;

                    pic = ades->hand[i][j];
                    tmp = (D_Ad_Image_Param *)pic;
                    if(tmp->uctotal > 1)
                    {
                        times = (tmp->times == 0) ? 2000 : tmp->times;
                        if(D_INVALID_HANDLE == ades->htimer[i])
                        {
                            ades->htimer[i] = d_timer_create(NULL, times, ades->queue);
                            DAD_DUMP("[ad]d_timer_create[%d]\n", ades->htimer[i]);
                        }
                        else
                        {
                            DAD_DUMP("[ad]d_timer_reset[%d]\n", ades->htimer[i]);
                            d_timer_reset(ades->htimer[i], times);
                        }
                    }
                }
                ades->hand[i][j] = NULL;
                break;
            }
        }
        for(j = 0; j < DAD_PIC_TOTAL_TYPE ; j++)
        {
            if(ades->hand[i][j] != NULL)
            {
                break;
            }
        }
        if(j == DAD_PIC_TOTAL_TYPE)
        {
            ades->dataflag[i] = DAD_DATA_WAIT;
        }
    }
    d_sem_post(ades->hsem);
    return pic;
}

/** @brief  设置节目信息
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ad_set_chan_ex(D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT
{
    if(!ades)
        return D_ERR;

    if(memcmp(&ades->param, chan_param, sizeof(D_Ad_Service_Param)) != 0)
    {
        if(ades->op->chan_change)
            ades->op->chan_change(chan_param);
        ad_send_msg(DAD_SET_PARAM, DAD_STB_LOG, NULL, chan_param->usNetworkId, chan_param->usTsId, chan_param->usServiceId);
        d_sem_wait (ades->hsem1);
        d_sem_wait (ades->hsem1);
        d_sem_post (ades->hsem1);
    }

    return D_OK;
}

/** @brief
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ad_check_fpkey_ex(D_Ad_Pos_Type type, D_U8 key)D_FUNCPOSTFIT
{
    if(!ades)
        return D_ERR;

    if(!ades->op->check_fp_key)
        return D_ERR;
    if(ades->op->check_fp_key(type, key) == D_OK)
    {
        ad_send_msg(DAD_RESET_DATA, type, NULL, 0, 0, 0);
        d_sem_wait (ades->hsem1);
        d_sem_wait (ades->hsem1);
        d_sem_post (ades->hsem1);
        return D_OK;
    }
    return D_ERR;
}
/** @brief  给ifaboo传递按键值
* @param[in]    key 键值
* @return 按键由ifaboo系统处理返回D_OK,ifaboo未处理返回D_ERR
*/
D_Result d_ad_set_fpkey_ex(D_U8 key)D_FUNCPOSTFIT
{
    if(!ades)
        return D_ERR;

    if(!ades->op->set_fp_key)
        return D_ERR;
    return ades->op->set_fp_key(key);
}

/** @brief  释放资源
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ad_release_img_ex(D_Ad_Pos_Type type, D_Ptr handle)D_FUNCPOSTFIT
{
    if(!ades)
        return D_ERR;

    ad_send_msg(DAD_APP_RELEASEDATA, type, handle, 0, 0, 0);
    d_sem_wait (ades->hsem1);
    d_sem_wait (ades->hsem1);
    d_sem_post (ades->hsem1);

    return D_OK;
}
/** @brief  释放资源
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ad_scroll_callback(D_U8 idx, D_U8 total)D_FUNCPOSTFIT
{
    if(!ades)
        return D_ERR;

    if(!ades->op->scroll_callback)
        return D_ERR;
    return ades->op->scroll_callback(idx, total);
}

/****************************************以下几个直接取，不通过任务********************/
/** @brief  取版本号
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ad_GetVersion(D_U8 *sversion)D_FUNCPOSTFIT
{
    if(!ades)
        return D_ERR;
    if(!ades->op->getversion)
        return D_ERR;
    return ades->op->getversion(sversion);
}

/** @brief  检查是否支持某一类广告
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ad_Check_App(D_Ad_Pos_Type type, D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT
{
    if(!ades)
        return D_ERR;

    if(!ades->op->check_app)
        return D_ERR;
    return ades->op->check_app(type, chan_param);
}

/** @brief  设置tag
* @param[in]
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_ad_SetDescr(D_U8 * descr, D_U32 id)D_FUNCPOSTFIT
{
    if(!ades)
        return D_ERR;
    if(!ades->op->setdescr)
        return D_ERR;
    return ades->op->setdescr(descr, id);
}

/****************************************以下几个函数是直接取保存的数据，用来给上层自己显示的时候使用********************/
/** @brief 获取某种应用的图片数量
* @param  type 图片应用类型
* @return 返回这种应用的图片的数量
*/
D_U8 d_ad_get_img_count (D_Ad_Pos_Type type) D_FUNCPOSTFIT
{
    if(!ades)
        return 0;
    if(!ades->op->get_img_count_ex)
        return 0;
    return ades->op->get_img_count_ex(type);
}
/** @brief 获取某种应用的图片数据和信息
* @param  type 图片应用类型
* @param  no 第几个这个类型的图片
* @return 返回图片信息的指针
*/
D_Result d_ad_load_img_data(D_Ad_Pos_Type type, D_U8 no, d_ad_pict_info *info)D_FUNCPOSTFIT
{
    if(!ades)
        return D_ERR;
    if(!ades->op->load_img_data_ex)
        return D_ERR;
    return ades->op->load_img_data_ex(type, no, info);
}

/** @brief 释放某个图片
* @param img_data   图片信息的指针
* @return 成功返回D_OK,失败返回D_ERR
* @note   给外部使用的接口
*/
D_Result d_ad_release_img_data(d_ad_pict_info *img_data)D_FUNCPOSTFIT
{
    if(!ades)
        return D_ERR;
    if(!ades->op->release_img_data_ex)
        return D_ERR;
    return ades->op->release_img_data_ex(img_data);

}


