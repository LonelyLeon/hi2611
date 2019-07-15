/**@defgroup MonitorTable 
*@{*/
/** @file
* @brief 开机SI检查(例如网络锁、升级描述等)
* @author qiny
* @date 2013-09-09 qiny: 建立文件
*/
#include <stdio.h>
#include <string.h>
#include "dMMan.h"
#include "dMem.h"
#include "dMsg.h"
#include "dResource.h"
#include "dTimer.h"
#include "dDebug.h"
#include "dSI.h"
#include "dDescr.h"
#include "dSIParse.h"
#include "dDBase.h"
#include "dScan.h"
#include "dProgScan.h"
#include "dTV.h"
#include "pMonitorRegister.h"
#include "dCBMan.h"
#include "pConfig.h"
#include "dMonitorTable.h"
#include "pCustomConfig.h"
#include "pPlayer.h"
#include "pPowerOnCheck.h"
#include "pSIParse.h"
#include "pUmt.h"
#include "pSdk.h"

#define CHECK_MASK_NIT 0x01
#define CHECK_MASK_UMT 0x02


/** @brief开机检查数据结构定义*/
typedef struct
{
    D_TVScanMode scan_mode;
    D_U32  power_on_check_status; 
    D_HSem hsem_power_on_check;

    D_Handle power_on_notlock_hcbm;
    D_Handle power_on_nit_hcbm;
    D_Handle nit_full_hcbm;
    
    D_Bool Sys_Network_match;
    D_Char Sys_Network_name[32+1];
    D_U16 Sys_Network_id;

    D_Bool software_change;
    D_Handle umt_full_hcbm;
}D_PowerOnCheckData;

static D_PowerOnCheckData *checkData = NULL;
static D_Time start_time = 0;

/** @brief开机检查数据结构初始化*/
#define PowerOnCheckDataInit(_p)\
    _p->scan_mode = 0;\
    _p->hsem_power_on_check = D_INVALID_HANDLE;\
    _p->power_on_check_status = 0;\
    _p->power_on_notlock_hcbm = D_INVALID_HANDLE;\
    _p->power_on_nit_hcbm = D_INVALID_HANDLE;\
    _p->nit_full_hcbm = D_INVALID_HANDLE;\
    _p->Sys_Network_match = D_FALSE;\
    _p->Sys_Network_id = 0;\
    _p->Sys_Network_name[0] = '\0';\
    _p->software_change = D_FALSE;\
    _p->umt_full_hcbm = D_INVALID_HANDLE;




extern void mon_nit_register(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)D_FUNCPOSTFIT;



/** @brief检查是否是主频点
*@param[in] ftype 前端类型
*@param[in] fparam 前端参数
*@return 1 是主频点 0 不是主频点
*/
static D_U8 nit_freq_check(D_FEndType ftype, D_FEndParam fparam)
{
    D_U8 ret = 1;
    return ret;
}


/** @brief 注册锁不定时回调*/  	
static void power_on_check_not_lock (D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)D_FUNCPOSTFIT
{
     if(checkData && checkData->hsem_power_on_check != D_INVALID_HANDLE)
    {
        checkData->power_on_check_status = 0;
        d_sem_post(checkData->hsem_power_on_check);
    }

    return ;
}

/** @brief 注册nit搜全时回调*/ 
static void power_on_get_nit(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)D_FUNCPOSTFIT
{
    D_PMonitorData *pMon = (D_PMonitorData *)obj_data;
    
    if(checkData && pMon)
    {   
        checkData->power_on_check_status &= (~CHECK_MASK_NIT);
        
        if((g_custom_config.si_mon.power_on.flag & P_SIMON_NIT_NETWORK_ID) && (pMon->currNetworkId == checkData->Sys_Network_id))
        {
            checkData->Sys_Network_match = D_TRUE;
        }
        
        if((g_custom_config.si_mon.power_on.flag & P_SIMON_NIT_NETWORK_NAME) && (strcmp(pMon->currNetworkName, checkData->Sys_Network_name) == 0))
        {
            checkData->Sys_Network_match = D_TRUE;
        }
        
        if(checkData->power_on_check_status == 0 && checkData->hsem_power_on_check != D_INVALID_HANDLE)
        {
            d_sem_post(checkData->hsem_power_on_check);  
        }
    }

    return ;
}

/** @brief 注册umt搜全时回调*/ 
static void power_on_get_umt(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)D_FUNCPOSTFIT
{
    DPCB_STRUCT *pstDPCB = (DPCB_STRUCT *)obj_data;
    
    if(checkData && pstDPCB)
    {   
        checkData->power_on_check_status &= (~CHECK_MASK_UMT);
        
        checkData->software_change = pstDPCB->EnableOtaDL;
        
        if(checkData->power_on_check_status == 0 && checkData->hsem_power_on_check != D_INVALID_HANDLE)
        {
            d_sem_post(checkData->hsem_power_on_check);  
        }
    }

    return ;
}

/** @brief 开机nit表检查初始化*/ 
static D_Result power_on_check_nit_init(TVData	*tv_data)
{
    D_NITConfigMoniter nitconfig = {0};
    D_SIParam si_param; 
    
    if(checkData && tv_data)
    {
        p_conf_get_si_param (&si_param);
        
        checkData->Sys_Network_id = si_param.network_id;
        sprintf(checkData->Sys_Network_name, "%s", si_param.network_name);
        
        checkData->power_on_check_status |= CHECK_MASK_NIT;
        checkData->scan_mode |= D_TV_SCAN_NIT;
        
        /*为解析函数注册回调函数*/
        checkData->power_on_nit_hcbm = d_cbman_subscribe(D_MONITOR_REG_NIT, ((D_Handle)(tv_data->ps)), mon_nit_register, NULL );
        checkData->nit_full_hcbm = d_cbman_subscribe(D_MON_GET_NIT_FULL, D_INVALID_HANDLE, power_on_get_nit, NULL);
        
        nitconfig.enable = 1;
        nitconfig.freq_mode = 0;
        nitconfig.freq_check = nit_freq_check;
        nitconfig.moniter_mode = 1;//需要版本号控制
        nitconfig.time_out = 5000;
        nitconfig.time_hand = D_INVALID_HANDLE;
        d_set_need_version(D_TV_SCAN_NIT, (D_Ptr)(&nitconfig));    
    }

    return D_OK;
}
/** @brief 开机nit表检查反初始化*/ 
static D_Result power_on_check_nit_deinit(void)
{
    D_NITConfigMoniter nitconfig = {0};
    
    if(checkData)
    {  
        d_cbman_unsubscribe(checkData->power_on_nit_hcbm);
        checkData->power_on_nit_hcbm = D_INVALID_HANDLE;

        d_cbman_unsubscribe(checkData->nit_full_hcbm);
        checkData->nit_full_hcbm = D_INVALID_HANDLE;  
        
        nitconfig.time_hand = D_INVALID_HANDLE;
        d_set_need_version(D_TV_SCAN_NIT, (D_Ptr)(&nitconfig)); 
    }

    return D_OK;
}

/** @brief 开机umt表检查初始化*/ 
static D_Result power_on_check_umt_init(TVData *tv_data)
{    
    if(checkData)
    {       
        checkData->power_on_check_status |= CHECK_MASK_UMT;
        
        /*为解析函数注册回调函数*/
        checkData->umt_full_hcbm = d_cbman_subscribe(D_MON_GET_UMT_FULL, D_INVALID_HANDLE, power_on_get_umt, NULL);
        p_umt_start(1);
    }

    return D_OK;
}

/** @brief 开机umt表检查反初始化*/ 
static D_Result power_on_check_umt_deinit(void)
{    
    if(checkData)
    {  
        p_umt_stop();     
        d_cbman_unsubscribe(checkData->umt_full_hcbm);
        checkData->umt_full_hcbm = D_INVALID_HANDLE;    
    }

    return D_OK;
}


/** @brief 开机检查表监控初始化
*@return D_ERR 初始化失败 D_OK 初始化成功
*/
D_Result p_power_on_check_init(void)D_FUNCPOSTFIT
{
    TVData	*tv_data;

    if(!(g_custom_config.si_mon.power_on.enable))
    {
        return D_ERR;
    }
  
    if (g_htv == D_INVALID_HANDLE)
    {
        D_ERROR ("power on Si_init htv error\n");
        return D_ERR;
    }
	/*取得TV相关数据*/
    tv_data = d_app_get_data (g_htv);
    if(!tv_data)
    {
        D_ERROR ("power on Si_init d_app_get_data error\n");
        return D_ERR;
    }

    checkData = (D_PowerOnCheckData *)d_mem_alloc(0, sizeof(D_PowerOnCheckData));
    if(!checkData)
    {
        D_ERROR ("power on Si_init mem alloc err\n");
        return D_ERR;
    }

    PowerOnCheckDataInit(checkData);

    checkData->hsem_power_on_check = d_sem_create(NULL);
    if(checkData->hsem_power_on_check == D_INVALID_HANDLE)
    {
        D_ERROR ("power on Si_init sem create error\n");
        return D_ERR;        
    }
       
    /*锁不定时回调*/    
    checkData->power_on_notlock_hcbm = d_cbman_subscribe(D_MON_TS_NOT_LOCK, D_INVALID_HANDLE, power_on_check_not_lock, NULL );
    
    /*Nit检查初始化*/
    if(g_custom_config.si_mon.power_on.flag & P_SIMON_NIT_EN)
    {
        power_on_check_nit_init(tv_data);
    }

    /*umt升级描述检查*/
    if(g_custom_config.si_mon.power_on.flag & P_SIMON_UMT_EN)
    {    
        power_on_check_umt_init(tv_data);
    }

    if(checkData->power_on_check_status == 0)
    {
        p_power_on_check_deinit();
        return D_ERR;
    }

    return D_OK;
}


/** @brief 开机检查表监控反初始化
*@return D_ERR 反初始化失败 D_OK 反初始化成功
*/
D_Result p_power_on_check_deinit(void)D_FUNCPOSTFIT
{
    D_NITConfigMoniter nitconfig = {0};
    
    if(!(g_custom_config.si_mon.power_on.enable))
    {
        return D_ERR;
    }
    
    if(checkData)
    {
        if(g_custom_config.si_mon.power_on.flag & P_SIMON_NIT_EN)
        {    
            power_on_check_nit_deinit();
        }
        
        if(g_custom_config.si_mon.power_on.flag & P_SIMON_UMT_EN)
        {        
            power_on_check_umt_deinit();
        }
        
        /*反注册注册回调函数*/
        d_cbman_unsubscribe(checkData->power_on_notlock_hcbm);
        checkData->power_on_notlock_hcbm = D_INVALID_HANDLE;
        
        if(checkData->hsem_power_on_check != D_INVALID_HANDLE)
        {
            d_sem_destroy(checkData->hsem_power_on_check);
        }
        
        checkData->hsem_power_on_check = D_INVALID_HANDLE;

        d_mem_free(checkData);
        checkData = NULL;
    } 
    
    return D_OK;
}

/** @brief 启动开机检查表监控
*@return D_ERR 反初始化失败 D_OK 反初始化成功
*/
D_Result p_power_on_check_start(D_FEndType fendtype)D_FUNCPOSTFIT
{
    D_SIParam  si_param;
    D_DBTSInfo ts_info;
    D_ID    dbtsid;
    D_FEndParam fendparam = {0};
    
    if((!checkData) || (!(g_custom_config.si_mon.power_on.enable)))
    {
        return D_ERR;
    } 
       
    if (g_htv == D_INVALID_HANDLE)
    {
        return D_ERR;
    }

    if(g_custom_config.si_mon.power_on.use_main)
    {
        p_conf_get_si_param(&si_param);
        fendparam.freq = si_param.main.freq;
        fendparam.dvbc.baud = si_param.main.baud;
        fendparam.dvbc.mod = si_param.main.mod;    
    }
    else
    {
        fendparam.freq = g_custom_config.si_mon.power_on.freq;
        fendparam.dvbc.baud = g_custom_config.si_mon.power_on.baud;
        fendparam.dvbc.mod = g_custom_config.si_mon.power_on.mod;           
    }
    
    D_DB_TS_INFO_INIT(&ts_info);
    ts_info.param = fendparam;
    ts_info.tuner_type = fendtype;
    ts_info.db_net_id = 0;
    dbtsid = d_dbase_get_ts_by_param(ts_info.db_net_id, ts_info.tuner_type, &(ts_info.param));
    dbtsid = (dbtsid < 0)? P_DB_MAX_TS_CNT : dbtsid;  

    d_tv_power_on_check(g_htv, D_TRUE, ts_info, dbtsid, checkData->scan_mode);    
    start_time = d_sys_get_time();
    return D_OK;
}

/** @brief 停止开机检查表监控
*@return D_ERR 反初始化失败 D_OK 反初始化成功
*/
D_Result p_power_on_check_stop(D_FEndType fendtype)D_FUNCPOSTFIT
{
    D_DBTSInfo ts_info;

    if((!checkData) || (!(g_custom_config.si_mon.power_on.enable)))
    {
        return D_ERR;
    } 
       
    if (g_htv == D_INVALID_HANDLE)
    {
            return D_ERR;
    }

    D_DB_TS_INFO_INIT(&ts_info);
    ts_info.tuner_type = fendtype;
    d_tv_power_on_check(g_htv, D_FALSE, ts_info, -1, D_TV_SCAN_ALL);

    return D_OK;
}



/** @brief 取得开机检查结果
*@return D_OK \D_ERR
*/
D_Result p_power_on_check(D_PowerOnCheck *check)D_FUNCPOSTFIT
{
    D_Time timeout;
    
    if((!checkData) || (!(g_custom_config.si_mon.power_on.enable)))
    {
        return D_ERR;
    } 
    
    timeout = D_MIN(20000, g_custom_config.si_mon.power_on.timeout);
    start_time = d_sys_get_time() - start_time;

	timeout = (timeout > start_time) ? D_MAX((timeout - start_time), 100) : 100;
   
    if(checkData->hsem_power_on_check != D_INVALID_HANDLE)
    {
        d_sem_wait_timeout(checkData->hsem_power_on_check, timeout);
    }

    if(check)
    {
        check->network_match = checkData->Sys_Network_match;
    }

    return D_OK;
}

/* @}*/
