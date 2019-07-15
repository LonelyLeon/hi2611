/**@file pUmt.c
*@brief Umt 解析并触发升级
*详细描述
*@author sunzy
*@copyright Haier-IC
*@date 2013-09-4
*/
#include "dMonitorTable.h"
#include "pCustomConfig.h"
#include "pMonitorRegister.h"
#include "dMsg.h"
#include "pConfig.h"
#include "dCBMan.h"
#include "pCheck_updata.h"
#include "pUmt.h"

#define P_UMT_PARSE_DUMP(_x_)  D_DUMP _x_   ///<调试打印信息
#define P_UMT_PARSE_DERR(_x_)  D_ERROR _x_  ///<错误打印信息

#ifdef  D_UMT_UP_DATA_TYPE
typedef struct
{
    D_U8            *buf;
    D_HMMan         hmm;
    D_U8            umt_version;
    D_U16           umt_pid;
    D_TabMask       *umt_mask;
    D_U8                    power_on;

} D_UmtScan;

static D_UmtScan *Umtps = NULL;
static D_PMonitorData   gUmt_Data = {0xFF, 0xFFFF, {0}, {{0}}, {0}};

static D_Result umt_parse(TVData *tv, D_U8 *buf, D_Size size, D_HMMan umt_mm_handle)D_FUNCPOSTFIT;

#else
static D_Result umt_event_to_gui(D_MsgType type, D_SiMonParam param) D_FUNCPOSTFIT;

DPCB_STRUCT stDPCB;
#endif
D_Result
p_umt_monitor_stop(void)D_FUNCPOSTFIT;

D_Result
p_umt_set_destory(void)D_FUNCPOSTFIT;

static D_MonitorHandle g_umt_monitor_handle = -1;

#ifdef D_UMT_UP_DATA_TYPE
/** @brief  接收UMT表
* @param[in] TVData *tv    电视数据
* @param[in] D_U8 *buf     umt 数据指针
* @param[in] D_Size length   数据长度
* @retval D_OK  成功
* @retval D_ERR  失败
*/
static D_Result
p_umt_parse_table(TVData *tv, D_U8 *buf, D_Size length)D_FUNCPOSTFIT
{
    D_U8    *ptr;
    D_S16   len;
    D_U8    tab_id;
    D_U8    sec_num;
    D_U8    last_sec_num;
    D_U8    version;
    D_HMMan hmm;
    D_U8        *Umt_buf;

    if (!buf)
    {
        P_UMT_PARSE_DERR (("Buffer is NULL\n"));
        return D_ERR;
    }

    if (length < 3)
    {
        P_UMT_PARSE_DERR (("Section size < 3 bytes\n"));
        return D_ERR;
    }

    ptr = buf;
    len = D_SI_HILO (D_SI_BIT(ptr[1], 4, 4), ptr[2]) + 3 - 4;

    if(len > length)
    {
        P_UMT_PARSE_DERR (("Sction length error\n"));
        return D_ERR;
    }

    tab_id = ptr[0];
    version = D_SI_BIT(ptr[5], 2, 5);
    sec_num = ptr[6];
    last_sec_num = ptr[7];

    /*得到新版本umt表*/
    if (Umtps->umt_version != version)
    {
        Umtps->umt_version = version;
        d_tab_mask_clear (Umtps->umt_mask);
    }
    if (d_tab_mask_is_set (Umtps->umt_mask, tab_id, version, sec_num))
    {
        P_UMT_PARSE_DERR (("umt section duplicated\n"));
        return D_ERR;
    }
    P_UMT_PARSE_DERR (("umt section %d %d\n", sec_num, last_sec_num));

    d_tab_mask_add (Umtps->umt_mask, tab_id, version, sec_num, last_sec_num);

    ptr += 8;
    len -= 8;

    Umt_buf = (D_U8*)d_mem_alloc (0, 4096);
    if (! Umt_buf)
    {
        return D_ERR;
    }

    hmm = d_mman_create (Umt_buf, 4096, D_MMAN_SIMPLE);
    if (hmm == D_INVALID_HANDLE)
    {
        d_mem_free (Umt_buf);
        Umt_buf = NULL;
        return D_ERR;
    }

    umt_parse(tv, ptr, len, hmm);

    d_mman_destroy (hmm);
    d_mem_free (Umt_buf);
    Umt_buf = NULL;

    if (Umtps->umt_mask)
    {
        if (d_tab_mask_full (Umtps->umt_mask))
        {
            P_UMT_PARSE_DERR (("umt end\n"));

            /*搜索下一个版本*/
            p_umt_monitor_stop ();
            d_tab_mask_clear (Umtps->umt_mask);
            if(Umtps->power_on)
            {
                d_cbman_notify(D_MON_GET_UMT_FULL, D_INVALID_HANDLE, (D_Ptr)(&gUmt_Data));
                p_umt_stop();
            }
            else
            {
                return D_OK;
            }
        }
    }

    return D_ERR;

}

#else

/** @brief  umt 发送消息
* @param[in] D_MsgType type       消息类型
* @param[in] D_SiMonParam param   消息信息
* @retval D_OK  成功
* @retval D_ERR  失败
*/
static D_Result umt_event_to_gui(D_MsgType type, D_SiMonParam param) D_FUNCPOSTFIT
{
    D_SIMsg msg;

    msg.type = type;
    msg.hscan = d_app_self ();
    msg.param = param;

    return d_queue_try_send (d_gui_get_queue (), (D_U8*)&msg, sizeof (msg));
}

/** @brief  解析UMT表并触发
* @param[in] TVData *tv    电视数据
* @param[in] D_U8 *buf     umt 数据指针
* @param[in] D_Size size   暂时没用到
* @retval D_OK  成功
* @retval D_ERR  失败
*/
static D_Result
umt_parse(TVData *tv, D_U8 *buf, D_Size size)D_FUNCPOSTFIT
{
    //D_S16         NoOfBytesParsedSoFar = 0;
    D_U8            *pucSectionData;
    D_U16           manufacturer_code, Manufacturer_code, cnt;
    D_U32           hardware_code, Hardware_code;
    D_U32           loader_version;
    D_Bool          version_sign = D_FALSE;
    D_U8            Download_Mode;
    D_U32           new_soft_ver, new_log_ver, current_ver;
    D_SiMonParam    msgparam;
    D_LoaderParam   sys_sw_temp ;
    D_U32           cur_area_code;
    D_U32           new_area_code;

    p_conf_get_loader_param(&sys_sw_temp);

    Hardware_code = (CUSTOM_CONFIG.sys.hw_id << 24) | (CUSTOM_CONFIG.sys.hw_major << 16) | (CUSTOM_CONFIG.sys.hw_minor);

    Manufacturer_code = (D_U16)CUSTOM_CONFIG.sys.manu_id & 0xffff;

    stDPCB.current_software_version =  ((D_U32)sys_sw_temp.stb_param_copy.sw_major << 24) \
    | ((D_U32)sys_sw_temp.stb_param_copy.sw_minor << 16) \
    | (D_U32)sys_sw_temp.stb_param_copy.sw_build_num;


    pucSectionData = buf + 1;

    if (buf[0] == UPDATE_INFO_TABLEID)
    {
        stDPCB.download_type = pucSectionData[31] & 0x0f;
        Download_Mode = pucSectionData[31] >> 4;

        cnt = 17;
        if(stDPCB.download_type == 1)
        {
            stDPCB.new_software_version  = (D_U32)pucSectionData[cnt++] << 24;
            stDPCB.new_software_version |= (D_U32)pucSectionData[cnt++] << 16;
            stDPCB.new_software_version |= (D_U32)pucSectionData[cnt++] << 8;
            stDPCB.new_software_version |= (D_U32)(pucSectionData[cnt]);

            new_soft_ver = stDPCB.new_software_version;
            new_area_code = new_soft_ver >> 8;
            new_soft_ver = new_soft_ver & 0xff;

            cnt ++;
        }
        else if(stDPCB.download_type == 2)
        {
            stDPCB.new_logo_version  = (D_U32)pucSectionData[cnt++] << 24;
            stDPCB.new_logo_version |= (D_U32)pucSectionData[cnt++] << 16;
            stDPCB.new_logo_version |= (D_U32)pucSectionData[cnt++] << 8;
            stDPCB.new_logo_version |= (D_U32)(pucSectionData[cnt]);
            new_log_ver = stDPCB.new_logo_version;
            cnt ++;
        }

        manufacturer_code = pucSectionData[cnt++] << 8 ;
        manufacturer_code |= pucSectionData[cnt++];

        hardware_code  = (D_U32)pucSectionData[cnt++] << 24;
        hardware_code |= (D_U32)pucSectionData[cnt++] << 16;
        hardware_code |= (D_U32)pucSectionData[cnt++] << 8;
        hardware_code |= (D_U32)pucSectionData[cnt++] ;

        loader_version  = (D_U32)pucSectionData[cnt++] << 24;
        loader_version |= (D_U32)pucSectionData[cnt++] << 16;
        loader_version |= (D_U32)pucSectionData[cnt++] << 8;
        loader_version |= (D_U32)pucSectionData[cnt++] ;


        version_sign = D_FALSE;
        if(stDPCB.download_type == 1)
        {
            current_ver = stDPCB.current_software_version;
            cur_area_code = current_ver >> 8;
            current_ver = current_ver & 0xff;

            if( cur_area_code == new_area_code )
            {
                if((new_soft_ver > current_ver) || (current_ver == -1) || (0 == new_soft_ver && 0 != current_ver))
                {
                    version_sign = D_TRUE;
                }
                if( sys_sw_temp.download_flag == 1)
                {
                    version_sign = D_FALSE;
                }
            }
        }
        else if(stDPCB.download_type == 2)
        {
            current_ver = stDPCB.current_software_version;
            cur_area_code = current_ver >> 8;
            current_ver = current_ver & 0xff;

            if( cur_area_code == new_area_code )
            {
                if((new_soft_ver > current_ver) || (current_ver == -1) || (0 == new_soft_ver && 0 != current_ver))
                {
                    version_sign = D_TRUE;
                }
            }
        }

        if( manufacturer_code == Manufacturer_code && hardware_code == Hardware_code && version_sign == D_TRUE )
        {
            stDPCB.EnableOtaDL = D_TRUE;

            cnt = 4;
            stDPCB.TransponderFreq  = (D_U32)pucSectionData[cnt++] << 24;
            stDPCB.TransponderFreq |= (D_U32)pucSectionData[cnt++] << 16;
            stDPCB.TransponderFreq |= (D_U32)pucSectionData[cnt++] << 8;
            stDPCB.TransponderFreq |= (D_U32)pucSectionData[cnt++] ;

            stDPCB.SymbolRate  = (D_U32)pucSectionData[cnt++] << 24;
            stDPCB.SymbolRate |= (D_U32)pucSectionData[cnt++] << 16;
            stDPCB.SymbolRate |= (D_U32)pucSectionData[cnt++] << 8;
            stDPCB.SymbolRate |= (D_U32)pucSectionData[cnt++] ;

            stDPCB.Modulation = (D_U8)pucSectionData[cnt++] ;

            stDPCB.DataPID  = (D_U16)pucSectionData[cnt++] << 8;
            stDPCB.DataPID |= (D_U16)pucSectionData[cnt++] ;

            stDPCB.TableID  = (D_U16)pucSectionData[cnt++] << 8;
            stDPCB.TableID |= (D_U16)pucSectionData[cnt++] ;

            sys_sw_temp.download_flag = 1;
            sys_sw_temp.new_loader_ver = stDPCB.new_software_version;
            sys_sw_temp.fparam.freq = stDPCB.TransponderFreq;
            sys_sw_temp.fparam.baud = stDPCB.SymbolRate;
            sys_sw_temp.fparam.mod = stDPCB.Modulation;
            sys_sw_temp.tid = stDPCB.TableID;
            sys_sw_temp.pid = stDPCB.DataPID;

            p_conf_set_loader_param(&sys_sw_temp);

            if( Download_Mode == MANUAL_SW_UPDATE )
            {
                msgparam.swparam.type = D_MSG_MON_SW_UPDATE;
                msgparam.swparam.version = 0;
                msgparam.swparam.pdata = NULL;
                umt_event_to_gui(D_MSG_SI_SW_UPDATE, msgparam);
                return D_OK;
            }
            else if( Download_Mode == FORCE_SW_UPDATE )
            {
                msgparam.swparam.type = D_MSG_MON_SW_UPDATE_MUST;
                msgparam.swparam.version = 0;
                msgparam.swparam.pdata = NULL;
                umt_event_to_gui(D_MSG_SI_SW_UPDATE, msgparam);
                return D_OK;
            }
        }
    }

    //p_umt_monitor_stop();//停止，不停止则会一直收到数据
    //p_umt_set_destory();
    d_cbman_notify(D_MON_GET_UMT_FULL, D_INVALID_HANDLE, (D_Ptr)(&stDPCB));

    return D_OK;
}
#endif

#ifdef D_UMT_UP_DATA_TYPE

/** @brief  解析UMT表并触发
* @param[in] TVData *tv    电视数据
* @param[in] D_U8 *buf     umt 数据指针
* @param[in] D_Size size   暂时没用到
* @retval D_OK  成功
* @retval D_ERR  失败
*/
static D_Result
umt_parse(TVData *tv, D_U8 *buf, D_Size size, D_HMMan umt_mm_handle)D_FUNCPOSTFIT
{
    D_U8            tag;
    D_U16           len;
    D_U8            * pucSectionData;

    pucSectionData = buf;
    tag = pucSectionData[0];
    len = pucSectionData[1] + 2;

    if(tag == UMT_DESCR_LOADER_TAG)
    {
        D_Loader_Descr      *dLoader_Descriptor;
        // D_Loader_Descr      *descr_next;
        D_Loader                *dLoader_List;
        D_U16               des_len;

        D_SI_ALLOC (umt_mm_handle, dLoader_List);

        if (dLoader_List)
        {
            dLoader_List->tag = pucSectionData[0];
            dLoader_List->manufacturer_code = D_SI_HILO(pucSectionData[2], pucSectionData[3]);
            dLoader_List->loader_list = NULL;

            len -= 4; //NIT 升级描述子的总长度
            pucSectionData += 4; //指针向下指4个位置到d_si_parse_descr里

            while( len > 0 )
            {
                D_SI_ALLOC(umt_mm_handle, dLoader_Descriptor);

                if( !dLoader_Descriptor )
                {
                    return D_ERR;
                }
                dLoader_Descriptor->delivery = (D_Descr*)d_si_parse_descr(pucSectionData, umt_mm_handle);
                des_len = pucSectionData[1] +  2; //d_si_parse_descr描述的总长度

                dLoader_Descriptor->download_table_id = pucSectionData[des_len];
                dLoader_Descriptor->download_pid = (((pucSectionData[des_len + 1] << 8) | (pucSectionData[des_len + 2])) & 0xfff8) >> 3;
                dLoader_Descriptor->upgrade_mode = ((pucSectionData[des_len + 1] << 8) | (pucSectionData[des_len + 2])) & 0x7;
                dLoader_Descriptor->hardware_version = (pucSectionData[des_len + 4] << 24) | (pucSectionData[des_len + 5] << 16) | \
                                                       (pucSectionData[des_len + 6] << 8) | (pucSectionData[des_len + 7]);
                dLoader_Descriptor->software_version = (pucSectionData[des_len + 8] << 24) | (pucSectionData[des_len + 9] << 16) | \
                                                       (pucSectionData[des_len + 10] << 8) | (pucSectionData[des_len + 11]);

                D_SI_LIST_ADD(dLoader_List->loader_list, dLoader_Descriptor);

                des_len += pucSectionData[des_len + 12] + 12 + 2; //nit 升级描述的总长度

                len = len - des_len;
                pucSectionData = pucSectionData + des_len; //指针+ 总长度的偏移，如果有另外一张nit描述用

            }
        }
        else
        {
            return D_ERR;
        }

        p_check_download_condition(dLoader_List, 0);

    }

    //p_umt_monitor_stop();//停止，不停止则会一直收到数据
    //p_umt_set_destory();

    return D_OK;
}
#endif

/** @brief  在监控里创建UMT
* @param[in] void   注释
* @retval D_OK  成功
* @retval D_ERR  失败
*/
D_Result
p_umt_monitor_create(D_U8 poweron)D_FUNCPOSTFIT
{
    D_TimerAttr ta;
    D_U32 time_out;

#ifdef D_UMT_UP_DATA_TYPE
    if(poweron)
    {
        ta.id = -1;
        ta.one_shot = D_TRUE;
        time_out = 0;
    }
    else
    {
        ta.id = 0;
        ta.one_shot = D_TRUE;
        time_out = 10000;
    }
    g_umt_monitor_handle = d_monitor_create(p_umt_parse_table, ta, time_out);
    if(g_umt_monitor_handle != -1)
    {
        D_U8    *buf;
        D_HMMan  hmm;

        /*内存分配*/
        buf = (D_U8*) d_mem_alloc (0, 4096);
        if (! buf)
        {
            P_UMT_PARSE_DERR (("Cannot allocate memory for umt scan\n"));
            return D_ERR;
        }

        hmm = d_mman_create (buf, 4096, D_MMAN_SIMPLE);
        if (hmm == D_INVALID_HANDLE)
        {
            P_UMT_PARSE_DERR (("Cannot create mman for prog scan\n"));
            d_mem_free (buf);
            return D_ERR;
        }

        Umtps = d_mman_alloc (hmm, sizeof (D_UmtScan));
        if (! Umtps)
        {
            d_mman_destroy (hmm);
            d_mem_free (buf);
            return D_ERR;
        }

        memset(Umtps, 0x00, sizeof (D_UmtScan));
        Umtps->buf = buf;
        Umtps->hmm = hmm;

        /*分配表屏蔽*/
        Umtps->umt_mask = d_tab_mask_new (hmm, 1);
        if (! Umtps->umt_mask)
        {
            d_mman_destroy (hmm);
            d_mem_free (buf);
            return D_ERR;
        }
        Umtps->power_on = poweron;
    }
#else
    ta.id = -1;
    ta.one_shot = D_TRUE;
    time_out = 0;

    g_umt_monitor_handle = d_monitor_create(umt_parse, ta, time_out);
#endif
    return D_OK;
}

#if 0
D_Result
p_umt_monitor_create(void)D_FUNCPOSTFIT
{
    g_umt_monitor_handle = d_monitor_create(umt_parse);
    return D_OK;
}
#endif

/** @brief  开启umt 监控过滤
* @param[in] void   注释
* @retval D_OK  成功
* @retval D_ERR  失败
*/
#ifdef D_UMT_UP_DATA_TYPE
D_Result
p_umt_monitor_start(void)D_FUNCPOSTFIT
{
    if(g_umt_monitor_handle != -1)
    {
        if ((! Umtps) || (! Umtps->umt_mask))
        {
            return D_ERR;
        }
        d_tab_mask_clear (Umtps->umt_mask);
        return d_monitor_start(g_umt_monitor_handle);
    }
    return D_ERR;
}
#else
D_Result
p_umt_monitor_start(void)D_FUNCPOSTFIT
{
    if(g_umt_monitor_handle != -1)
    {
        return d_monitor_start(g_umt_monitor_handle);
    }
    return D_ERR;
}
#endif

/** @brief  停止umt 监控过滤
* @param[in] void   注释
* @retval D_OK  成功
* @retval D_ERR  失败
*/
D_Result
p_umt_monitor_stop(void)D_FUNCPOSTFIT
{
    if(g_umt_monitor_handle != -1)
    {
        return d_monitor_stop(g_umt_monitor_handle);
    }
    return D_ERR;
}

/** @brief  设置过滤umt表的过滤条件
* @param[in] void   注释
* @retval D_OK  成功
* @retval D_ERR  失败
*/
D_Result
p_umt_set_param(void)D_FUNCPOSTFIT
{
    D_DemuxFilter filter;

    memset(&filter, 0, sizeof(D_DemuxFilter)); //初始化

    filter.pid = UPDATE_INFO_PID; //设置pid

    filter.sec.length = 16;
    filter.sec.filter[0] = UPDATE_INFO_TABLEID; //设置tbid
    filter.sec.mask[0] = 0xff;

    if(g_umt_monitor_handle != -1)
    {
        return d_monitor_set_param(g_umt_monitor_handle, filter);
    }
    return D_ERR;
}

/** @brief  释放umt 监控
* @param[in] void   注释
* @retval D_OK  成功
* @retval D_ERR  失败
*/
#ifdef D_UMT_UP_DATA_TYPE
D_Result
p_umt_set_destory(void)D_FUNCPOSTFIT
{
    D_Ptr *buf;

    if(g_umt_monitor_handle != -1)
    {
        d_monitor_destory(g_umt_monitor_handle);
        g_umt_monitor_handle  = -1;
    }

    if (! Umtps)
        return D_ERR;

    buf = Umtps->buf;
    if (Umtps->hmm != D_INVALID_HANDLE)
    {
        d_mman_destroy (Umtps->hmm);
    }

    if (buf)
    {
        d_mem_free (buf);
    }

    Umtps = NULL;

    return D_OK;
}
#else
D_Result
p_umt_set_destory(void)D_FUNCPOSTFIT
{
    if(g_umt_monitor_handle != -1)
    {
        d_monitor_destory(g_umt_monitor_handle);
        g_umt_monitor_handle  = -1;
    }
    return D_OK;
}
#endif


/** @brief  umt 开始接收入口函数
* @param[in] void   注释
* @retval 无
*/
void p_umt_start( D_U8 poweron)D_FUNCPOSTFIT
{
    p_umt_monitor_create(poweron);
    p_umt_set_param();
    p_umt_monitor_start();

    return;
}
#if 0
void p_umt_start(void)D_FUNCPOSTFIT
{
    p_umt_monitor_create();
    p_umt_set_param();
    p_umt_monitor_start();
    return;
}
#endif

/** @brief  umt 注销接收函数
* @param[in] void   注释
* @retval 无
*/
void p_umt_stop(void)D_FUNCPOSTFIT
{
    p_umt_monitor_stop();
    p_umt_set_destory();
    return;
}

