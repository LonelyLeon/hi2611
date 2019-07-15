/**@defgroup MonitorTable SI表监控
*@{*/
/** @file
* @brief 节目监控模块
* @author sunzy
* @date 2013-06-03 sunzy: 建立文件
* @date 2013-06-05 sunzy: 移动原模块相关代码
* @date 2013-07-25 hegx: 根据要求实现注册函数
*/
#include "dCA.h"
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
#include "dScan.h"
#include "dProgScan.h"
#include <string.h>
#include "dTV.h"
//#include "pPlayer.h"
#include "dNVPart.h"
#include "pMonitorRegister.h"
#include "dCBMan.h"
#include "pConfig.h"
#include "dMonitorTable.h"
#include "pCustomConfig.h"
#include "pSIParse.h"
#include "pUmt.h"
#include "pSdk.h"
#include "dadporting.h"
#include "pBat.h"
#include "dGUI.h"
#include "pCheck_updata.h"

#define PMON_DUMP(_x_) //D_DUMP _x_   ///<调试打印信息
#define PMON_DERR(_x_)  D_ERROR _x_  ///<错误打印信息

#define HAIER_DOWNLOAD_DESCR_TAG (P_DESCR_LOADER_TAG)
#define YONGXIN_DOWNLOAD_DESCR_TAG (P_YONGXIN_DESCR_LOADER_TAG)
#define MANUAL_SW_UPDATE  0x1
#define FORCE_SW_UPDATE  0x2

static D_PMonitorData PMonitorData = {0xFF, 0xFFFF, {0}, {0}, {0}};


/** @brief monitor register 通知应用层消息函数
*@param[in] type 消息类型
*@param[in] param 消息参数
*/
static D_Result mon_event_to_gui(D_MsgType type, D_SiMonParam param) D_FUNCPOSTFIT
{
    D_SIMsg msg;

    msg.type = type;
    msg.hscan = d_app_self ();
    msg.param = param;

    return d_queue_try_send (d_gui_get_queue (), (D_U8*)&msg, sizeof (msg));
}
/** @brief monitor register 通知TV消息函数
*@param[in] hq 消息队列
*@param[in] type 消息类型
*/
static D_Result mon_event_to_tv(D_HQueue hq, D_MsgType type) D_FUNCPOSTFIT
{
    D_SIMsg msg;

    msg.type = type;
    msg.hscan = d_app_self ();
    PMON_DUMP (("Prog send PMT message\n"));
    return d_queue_try_send (hq, (D_U8*)&msg, sizeof (msg));
}

/** @brief 监控升级描述符*/
D_Result
check_sw_update_descr(D_Descr*descr, D_Bool power_on_check)
{
    D_Loader            *loader_descr;

    if(descr->tag == HAIER_DOWNLOAD_DESCR_TAG)
    {
        loader_descr = (D_Loader*)descr;

        p_check_download_condition(loader_descr, 0);
    }
    else if(descr->tag == YONGXIN_DOWNLOAD_DESCR_TAG)
    {
        loader_descr = (D_Loader*)descr;

        p_check_download_condition(loader_descr, YONGXIN_DOWNLOAD_DESCR_TAG);
    }

    return D_ERR;
}


/** @brief 监控网络ID*/
D_Result
check_network_id(D_U16 net_id, D_Bool power_on_check)
{
    static D_SIParam si_param = {0};
    D_SiMonParam    msgparam;

    if(si_param.network_id == 0)
    {
        p_conf_get_si_param (&si_param);
    }

    if(PMonitorData.currNetworkId != net_id)
    {
        PMonitorData.currNetworkId = net_id;

        msgparam.siparam.version = 0;
        /*与系统配置的网络ID不匹配*/
        if(PMonitorData.currNetworkId != si_param.network_id)
        {
            msgparam.siparam.version = 1;
        }

        msgparam.siparam.type = D_MSG_MON_NETWORK_ID_CHANGED;
        msgparam.siparam.pdata = (D_Ptr)(&PMonitorData.currNetworkId);
        mon_event_to_gui(D_MSG_SI_CHAN_UPDATE, msgparam);
    }
    return D_OK;
}

/** @brief 监控网络名*/
D_Result
check_network_name(D_Descr*descr, D_Bool power_on_check)
{
    static D_SIParam si_param = {0};
    D_SiMonParam    msgparam;
    D_NetworkNameDescr *dnn;
    D_U32 len;

    if(si_param.network_id == 0)
    {
        p_conf_get_si_param (&si_param);
    }

    if(descr->tag == DESCR_NW_NAME)
    {
        dnn = (D_NetworkNameDescr*)descr;
        if(dnn->name && (strcmp(dnn->name, PMonitorData.currNetworkName) != 0))
        {
            len = D_MIN(NET_NAME_MAX_LEN, strlen(dnn->name));
            memcpy(PMonitorData.currNetworkName, dnn->name, len);
            PMonitorData.currNetworkName[len] = '\0';

            msgparam.siparam.version = 0;
            /*与系统配置的网络名不匹配*/
            if(strcmp(si_param.network_name, PMonitorData.currNetworkName) != 0)
            {
                msgparam.siparam.version = 1;
            }

            msgparam.siparam.type = D_MSG_MON_NETWORK_NAME_CHANGED;
            msgparam.siparam.pdata = (D_Ptr)PMonitorData.currNetworkName;
            mon_event_to_gui(D_MSG_SI_CHAN_UPDATE, msgparam);
        }

        return D_OK;
    }
    return D_ERR;
}

/** @brief 注册nit表处理*/
void mon_nit_register (D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)D_FUNCPOSTFIT
{
    D_ProgScan *ps = (D_ProgScan*)obj;
    D_List  *nits = (D_List   *)obj_data;
    D_Nit      *nit;
    D_NitTS *tses;
    D_Descr *descr;
    D_SIParam si_param;
    D_U8 prog_version = 0xFF;
    D_U8 prog_update_force = 0;
    D_Bool check_version = D_FALSE;
#ifdef D_CA_SUPPORT_XGCA
    D_U8 cdxg_updata_flag = 0;
    D_U8 cdxg_desc_version_num = 0;
#endif
    D_SI_FOR_EACH_BEGIN(D_Nit, nits, nit)
    if((ps->power_on_checking == D_FALSE && (g_custom_config.si_mon.flag & P_SIMON_NIT_NETWORK_ID)) \
    || (ps->power_on_checking && (g_custom_config.si_mon.power_on.flag & P_SIMON_NIT_NETWORK_ID)))
    {
        check_network_id(nit->net_id, ps->power_on_checking);
    }

    /*第一层描述符循环*/
    D_SI_FOR_EACH_BEGIN(D_Descr, nit->descrs, descr)
    if((ps->power_on_checking == D_FALSE && (g_custom_config.si_mon.flag & P_SIMON_NIT_NETWORK_NAME)) \
    || (ps->power_on_checking && (g_custom_config.si_mon.power_on.flag & P_SIMON_NIT_NETWORK_NAME)))
    {
        check_network_name(descr, ps->power_on_checking);
    }
    check_sw_update_descr(descr, ps->power_on_checking);
#ifdef D_CA_SUPPORT_XGCA

    if(DESCR_CDXG_SERVICE_UPDATE == descr->tag)
    {
        D_CDXGDescr*cdxg = (D_CDXGDescr*)descr;
        cdxg_updata_flag = cdxg->update_flag;
        cdxg_desc_version_num = cdxg->version_number;

	p_conf_get_si_param (&si_param);/// 取得SI设置

	if(si_param.cdxg_desc_pid == 0xffff)/*第一次*/
	{
		si_param.cdxg_desc_pid =  cdxg->fm_pid;
		p_conf_set_si_param(&si_param);/// 设置SI
		PMON_DUMP(("dxg_desc_pid == %d\n," si_param.cdxg_desc_pid ));
                if(cdxg->fm_pid != 0)
		p_fm_start();
	}
	else if(si_param.cdxg_desc_pid !=  cdxg->fm_pid)/*pid 变化,重启*/
	{
		si_param.cdxg_desc_pid =  cdxg->fm_pid;
		p_conf_set_si_param(&si_param);/// 设置SI
                if(cdxg->fm_pid != 0)
{
		p_fm_stop();
		p_fm_start();
}
	}	
        PMON_DUMP(("cdxg_service_update_descriptor"));
    }
#endif
    if(P_DESCR_DSAD_TAG == descr->tag)
    {
        D_DSADDescr*dsadxg = (D_DSADDescr*)descr;
        d_ad_SetDescr(dsadxg, AD_STB_DESAI);
        PMON_DUMP(("cdxg_service_update_descriptor"));
    }


	if (descr->tag == P_DESCR_DVTAD_TAG)
        {
            D_NormalDescr*dvtaddescr = (D_NormalDescr*)descr;
            d_ad_SetDescr(dvtaddescr, AD_STB_DVT);
        }



#ifdef D_STB_SUPPORT_HAIER_PROGRAM_VERSION
    if(P_DESCR_HAIER_PROGRAM_VERSION_TAG == descr->tag)
    {
        /*使用私有描述里的版本 @qiny 2016.04.15*/
        D_HrProgramVersionDescr *puDescr = (D_HrProgramVersionDescr *)descr;
        D_Bool match_flag = D_TRUE;
        if(puDescr->match)
        {
            if(puDescr->match_code == ((g_custom_config.dvbc_main.software_version >> 16) & 0x0000FFFF))
            {
                match_flag = D_TRUE;
            }
            else
            {
                match_flag = D_FALSE;
            }
        }

        if(match_flag == D_TRUE)
        {
            prog_version = puDescr->version;
            prog_update_force = puDescr->force;
        }
    }
#endif

    D_SI_FOR_EACH_END(D_Descr, nit->descrs, descr)

#if 0
    /*第二层描述符循环*/
    D_SI_FOR_EACH_BEGIN(D_NitTS, nit->tses, tses)
    D_SI_FOR_EACH_BEGIN (D_Descr, tses->descrs, descr)

    D_SI_FOR_EACH_END (D_Descr, tses->descrs, descr)
    D_SI_FOR_EACH_END(D_NitTS, nit->tses, tses)
#endif
    D_SI_FOR_EACH_END(D_Nit, nits, nit)

#ifdef D_STB_SUPPORT_HAIER_PROGRAM_VERSION
        check_version = D_TRUE;
        prog_version = prog_version;
        prog_update_force = prog_update_force;
#else
    if(g_custom_config.si_mon.flag & P_SIMON_NIT_VER_CHANGED_NOTIFY)
    {
        check_version = D_TRUE;
    }
        prog_version = ps->nit_version;
        prog_update_force = 0;
#endif
    
#ifndef D_CA_SUPPORT_XGCA        
    /*节目版本号改变*/
    if(PMonitorData.nit_version != prog_version && prog_version != 0xFF && check_version)
    {
        D_Bool flag_send = D_TRUE;//发送搜索消息标识
        D_SiMonParam    msgparam;
        
        if(d_moniter_nit_check(ps))//只监控主频点
        {
            p_conf_get_si_param (&si_param);/// 取得SI设置

            if(si_param.nit_version == 0xff)
            {
                flag_send = D_FALSE;//初始化第一次不重新搜索
            }
            else if(prog_version == si_param.nit_version)
            {
                flag_send = D_FALSE; // 版本号不变
            }

            si_param.nit_version = prog_version;
                p_conf_set_si_param(&si_param);/// 设置SI
            PMonitorData.nit_version = prog_version;

                if((flag_send) && (g_custom_config.chan_update.scan_enable))
                {
                msgparam.siparam.type = (prog_update_force) ? D_MSG_MON_CHAN_UPDATE_MUST : D_MSG_MON_CHAN_UPDATE;
                    msgparam.siparam.version = PMonitorData.nit_version;
                    msgparam.siparam.pdata = (D_Ptr)(ps->db_ts_id);
                    mon_event_to_gui(D_MSG_SI_CHAN_UPDATE, msgparam);
                }
        }
    }
#endif  

#ifdef D_CA_SUPPORT_XGCA
    {
        D_Bool flag_send = D_TRUE;//发送搜索消息标识
        if(d_moniter_nit_check(ps))//只监控主频点
        {
            p_conf_get_si_param (&si_param);/// 取得SI设置

            if(si_param.cdxg_desc_version_num == 0xff)
                flag_send = D_FALSE;//初始化第一次不重新搜索
            if(cdxg_updata_flag && (cdxg_desc_version_num != si_param.cdxg_desc_version_num))
            {
                si_param.cdxg_desc_version_num = cdxg_desc_version_num;
                p_conf_set_si_param(&si_param);/// 设置SI
                if(flag_send)
                {
                    D_SiMonParam    msgparam;
                    msgparam.siparam.type = D_MSG_MON_CHAN_UPDATE;
                    msgparam.siparam.version = PMonitorData.nit_version;
                    msgparam.siparam.pdata = (D_Ptr)(ps->db_ts_id);
                    mon_event_to_gui(D_MSG_SI_CHAN_UPDATE, msgparam);
                }
            }
        }
    }
#endif
    /*nit表搜索完全*/
    if(d_tab_mask_full (ps->nit_mask) && ps->power_on_checking)
    {
        d_cbman_notify(D_MON_GET_NIT_FULL, D_INVALID_HANDLE, (D_Ptr)(&PMonitorData));
    }

    return;
}

/** @brief 注册pat表处理*/
static void mon_pat_register (D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)D_FUNCPOSTFIT
{
    D_List  *pats = (D_List   *)obj_data;
    D_ProgScan*ps = (D_ProgScan*)obj;
    D_Pat     *pat = NULL;
    D_DBTSID    db_ts_id;
    D_DBSrvID   db_srv_id;
    D_DBSrvInfo info;
    D_DBRecset rset_tv;
    D_DBID  ids_tv[36];
    D_DBRecset rset_radio;
    D_DBID  ids_radio[36];
    D_Size i, cnt;
    D_U8 found, update;
    D_DBTSInfo tsinfo;
    D_Result ret;

    if (! pats)
    {
        PMON_DERR (("mon_pat_register pats error\n"));
        return;
    }
    if (! ps)
    {
        PMON_DERR (("mon_pat_register ps error\n"));
        return;
    }
    if (ps->fparam.freq)
    {
        db_ts_id = d_dbase_get_ts_by_param (ps->db_net_id, ps->ftype, &ps->fparam);
    }
    if((db_ts_id == -1) || (db_ts_id != ps->db_ts_id))
    {
        PMON_DERR (("mon_pat_register d_dbase_get_ts_by_param error\n"));
        return;
    }

    ret = d_dbase_get_ts_info(db_ts_id, &tsinfo);
    if((tsinfo.ts_id != ps->ts_id) && (ret != D_OK))
    {
        PMON_DERR (("mon_pat_register d_dbase_get_ts_by_id_ex error\n"));
        return;
    }
    D_SI_FOR_EACH_BEGIN (D_Pat, pats, pat)
    if(tsinfo.ts_id != pat->ts_id)
    {
        PMON_DERR (("mon_pat_register tsinfo.ts_id != pat->ts_id error\n"));
        return;
    }
    else
    {
        d_dbase_rset_init (&rset_tv, 36, ids_tv);
        d_dbase_rset_init (&rset_radio, 36, ids_radio);
        d_dbase_get_srvs_by_ts( &rset_tv, db_ts_id, D_DB_SRV_TV);
        d_dbase_get_srvs_by_ts( &rset_radio, db_ts_id, D_DB_SRV_RADIO);
        break;
    }
    D_SI_FOR_EACH_END (D_Pat, pats, pat)

    update = 0; //检测电视节目
    for(i = 0; i < rset_tv.cnt; i++)
    {
        if(d_dbase_get_srv_info (rset_tv.ids[i], &info) == D_OK)
        {
            found   = 0;
            D_SI_FOR_EACH_BEGIN (D_Pat, pats, pat)
            if(pat->prog_num == info.srv_id && pat->prog_num)
            {
                found   = 1;
            }
            D_SI_FOR_EACH_END (D_Pat, pats, pat)
            if(found == 0)
            {
                update = 1;
                break;
            }
        }
    }
    if(update == 0)//检测广播节目
    {
        for(i = 0; i < rset_radio.cnt; i++)
        {
            if(d_dbase_get_srv_info (rset_radio.ids[i], &info) == D_OK)
            {
                found   = 0;
                D_SI_FOR_EACH_BEGIN (D_Pat, pats, pat)
                if(pat->prog_num == info.srv_id && pat->prog_num)
                {
                    found   = 1;
                }
                D_SI_FOR_EACH_END (D_Pat, pats, pat)
                if(found == 0)
                {
                    update = 1;
                    break;
                }
            }
        }
    }
    if((update == 1) && (g_custom_config.chan_change.scan_enable))
    {
        D_SiMonParam    msgparam;

        PMON_DUMP (("call function change channel list\n"));

        msgparam.siparam.type = D_MSG_MON_CHAN_CHANGE;
        msgparam.siparam.version = 0;
        mon_event_to_gui(D_MSG_SI_CHAN_UPDATE, msgparam);
    }
    return;
}
/** @brief 检查PMT,如果更新通知TV
*@param[in] ps 节目数据
*@param[in] prog_num 节目号
*/
static D_Result prog_scan_check_pmt (D_ProgScan *ps, D_U16 prog_num )  D_FUNCPOSTFIT
{
    D_SIMsg      msg;
    D_ProgMap   *prog;
    D_DBTSID     db_ts_id = -1;
    D_DBSrvID    srv = -1;

    if (! ps)
    {
        PMON_DERR (("prog_scan_check_pmt ps error\n"));
        return D_ERR;
    }
    if (ps->fparam.freq)
    {
        db_ts_id = d_dbase_get_ts_by_param (ps->db_net_id, ps->ftype, &ps->fparam);
    }
    if((db_ts_id == -1) || (db_ts_id != ps->db_ts_id))
    {
        PMON_DERR (("prog_scan_check_pmt d_dbase_get_ts_by_param error\n"));
        return D_ERR;
    }
    prog = d_prog_scan_get_pmt (ps, prog_num);
    if (! prog)
    {
        PMON_DERR (("prog_scan_check_pmt d_prog_scan_get_pmt error\n"));
        return D_ERR;
    }
    if (db_ts_id != -1)
    {
        srv = d_dbase_get_srv_by_id (db_ts_id, prog->prog_num);
    }
    if (srv != -1)
    {
        /*更新记录*/
        if (d_dbase_update_srv_pmt_ex2 (srv, prog->vid_pid, prog->vid_codec, prog->aud1_pid, prog->aud1_codec, \
        prog->aud2_pid, prog->aud2_codec, prog->aud3_pid, prog->aud3_codec, prog->aud4_pid, prog->aud4_codec, \
        prog->pcr_pid, prog->pmt_pid) == D_OK)
        {
            if ((ps->hq != D_INVALID_HANDLE) && (g_custom_config.si_mon.flag & P_SIMON_PAT_PMT_CHANGED_NOTIFY))
            {
                /*发送SI消息*/
                mon_event_to_tv(ps->hq, D_MSG_SI_GET_PMT);
            }
        }
    }

    return D_OK;
}
/** @brief 注册pmt表处理*/
static void mon_pmt_register (D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)D_FUNCPOSTFIT
{
    D_List *pmts = (D_List*)obj_data;
    D_Pmt *pmt;
    D_U16 prog_num;

    pmt = (D_Pmt*)pmts;
    prog_num = pmt->prog_num;

    prog_scan_check_pmt ((D_ProgScan*)obj, prog_num);
}
/** @brief 注册pmt表处理*/
static void nit_loader_register (D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)D_FUNCPOSTFIT
{
    D_U8 *buf = (D_U8 *)obj_data;
    PMON_DUMP (("recive buf from nit loader\n"));
    return ;
}
/** @brief 注册sdt表处理*/
static void mon_sdt_register (D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_List  *sdts = (D_List   *)obj_data;
    D_ProgScan*ps = (D_ProgScan*)obj;
    D_Descr *descr;
    D_Sdt     *sdt;
    int map_num = 0;
    D_DBTSID    db_ts_id;
    D_DBSrvID   db_srv_id;
    D_DBSrvInfo info;
    D_U8 event_to_gui = 0;
    D_DBTSInfo tsinfo;
    D_Result ret;

    if (! sdts)
    {
        PMON_DERR (("mon_sdt_register sdts error\n"));
        return;
    }
    if (! ps)
    {
        PMON_DERR (("mon_sdt_register ps error\n"));
        return;
    }

    D_SI_FOR_EACH_BEGIN (D_Sdt, sdts, sdt)
    PMON_DUMP (("num:%x\n", sdt->srv_id));
    //by hegx 解决多个频点tsid和serviceid都一样的时候更新错的问题
    if (ps->fparam.freq)
    {
        db_ts_id = d_dbase_get_ts_by_param (ps->db_net_id, ps->ftype, &ps->fparam);
    }
    if(db_ts_id == -1)
    {
        PMON_DERR (("mon_sdt_register d_dbase_get_ts_by_id_ex error\n"));
        return;
    }
    ret = d_dbase_get_ts_info(db_ts_id, &tsinfo);
    if((tsinfo.ts_id == sdt->ts_id) && ret == D_OK)
    {
        db_srv_id = d_dbase_get_srv_by_id(ps->db_ts_id, sdt->srv_id);
        if((db_srv_id != -1) && (d_dbase_get_srv_info (db_srv_id, &info) == D_OK))
        {
            D_SI_FOR_EACH_BEGIN (D_Descr, sdt->descrs, descr)
            if (DESCR_ML_SERVICE_NAME == descr->tag)
            {
                D_MultilingualServiceNameDescr *dmsd;
		D_MultilingualSrvText *dmst;

                info.ca_flag = (info.ca_flag) ? D_TRUE : D_FALSE;
                sdt->ca = (sdt->ca) ? D_TRUE : D_FALSE;
                if((g_custom_config.si_mon.flag & P_SIMON_SDT_CA_FREEMODE_EN) && (info.ca_flag != sdt->ca))
                {
                    event_to_gui = 1;
                }
 
                dmsd = (D_MultilingualServiceNameDescr*)descr;
                D_SI_FOR_EACH_BEGIN(D_MultilingualSrvText, dmsd->multi_text, dmst)
                if(0 == memcmp(dmst->country, "chi", 3) || 0 == memcmp(dmst->country, "zho", 3))
                {
                    if((g_custom_config.si_mon.flag & P_SIMON_SDT_NAME_EN) &&  (dmst->srv_name != NULL) && (strcmp(info.name, dmst->srv_name) != 0 ))
                    {
                         strcpy(info.name, dmst->srv_name);
                    }
                                        
                    d_dbase_update_srv_name(db_srv_id, info.name);

                    PMON_DUMP (("call function change channel list\n"));
                    /*通知上层*/
                    event_to_gui = 1;
                }
                D_SI_FOR_EACH_END(D_MultilingualSrvText, dmsd->multi_text, dmst)
            }
            else if (DESCR_SERVICE == descr->tag)
            {
                D_ServiceDescr *sdt_descr = (D_ServiceDescr*) descr;

                info.ca_flag = (info.ca_flag) ? D_TRUE : D_FALSE;
                sdt->ca = (sdt->ca) ? D_TRUE : D_FALSE;
                if((g_custom_config.si_mon.flag & P_SIMON_SDT_CA_FREEMODE_EN) && (info.ca_flag != sdt->ca))
                {
                    event_to_gui = 1;
                }

                if((g_custom_config.si_mon.flag & P_SIMON_SDT_NAME_EN) && (sdt_descr->srv_name != NULL) && (strcmp(info.name, sdt_descr->srv_name) != 0 ))
                {
                    strcpy(info.name, sdt_descr->srv_name);
                    d_dbase_update_srv_name(db_srv_id, info.name);

                    PMON_DUMP (("call function change channel list\n"));
                    /*通知上层*/
                    event_to_gui = 1;
                }
            }

            D_SI_FOR_EACH_END (D_Descr, sdt->descrs, descr)
        }
    }

    D_SI_FOR_EACH_END (D_Sdt, sdts, sdt)

    if(event_to_gui)
    {
        D_SiMonParam    msgparam;
        msgparam.siparam.type = D_MSG_MON_SDT_CHANGED;
        msgparam.siparam.version = 0;
        mon_event_to_gui(D_MSG_SI_CHAN_UPDATE, msgparam);
    }
    return;
}

/** @brief 供外部调用注册表处理
* @param ps 事件关联对象,实际上是 dtv的ps数据
*/
static void mon_regsiter(D_ProgScan *ps)D_FUNCPOSTFIT
{
    d_cbman_subscribe(D_MONITOR_REG_PMT, (D_Handle) ps, mon_pmt_register, NULL );
    if(g_custom_config.si_mon.flag & P_SIMON_NIT_EN) ///设置该位后注册函数
        d_cbman_subscribe(D_MONITOR_REG_NIT, (D_Handle) ps, mon_nit_register, NULL );
    d_cbman_subscribe(D_MONITOR_REG_SDT, (D_Handle) ps, mon_sdt_register, NULL );
    if(g_custom_config.chan_change.scan_enable)
    {
        d_cbman_subscribe(D_MONITOR_REG_PAT, (D_Handle) ps, mon_pat_register, NULL );
    }
    d_cbman_subscribe(D_MONITOR_REG_NIT_TO_LOADER, D_INVALID_HANDLE, nit_loader_register, NULL );

}

#ifdef D_CA_SUPPORT
/** @brief 注册ca获得数据*/
static void ca_mon_get_pmt_data_regsiter(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)D_FUNCPOSTFIT
{
    D_Size size;
    D_U8 *buf = (D_U8 *)obj_data;
    if(buf != NULL)
    {
        size = ((buf[1] & 0x0F) << 8) | buf[2] + 3;
        PMON_DUMP (("[pMonitorRegister]send PMT size %d\n", size));
        d_ca_demux_data_cmp (1, buf, size);
    }
}
/** @brief 注册ca获得数据*/
static void ca_mon_get_cat_data_regsiter(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)D_FUNCPOSTFIT
{
	D_U16 SecLength;
	D_U16 NoOfBytesParsedSoFar;
	D_U16 iCASystemID;
	D_U8 DescTag;
	D_U8 DescrLength;
    D_Size size;
    D_U8 *buf = (D_U8 *)obj_data;

	//CA的处理
    if(buf != NULL)
    {
        size = ((buf[1] & 0x0F) << 8) | buf[2] + 3;
        PMON_DUMP (("[pMonitorRegister]send CAT size %d\n", size));
        d_ca_demux_data_cmp (0, buf, size);
    }

	//广告的处理
	SecLength = ((buf[1]&0x0F)<<8) | buf[2];	
		
	buf = buf + 8;
	SecLength -= 9; 
	
	if (SecLength >0)
	{
		NoOfBytesParsedSoFar = 0;
		while (NoOfBytesParsedSoFar < SecLength)
		{
		    DescTag = buf[0];
		    DescrLength = buf[1];
		    if (DescTag == DESCR_CA)
		    {
			    iCASystemID = ((D_U16)buf[2] << 8) + buf[3];
				#if D_CA_SUPPORT_DIVICA
			    if ( HRDIVICASTB_SysIDCheck(iCASystemID))//数视通CA SYSTEM ID 
			    #else
			    if ( iCASystemID == 0xd00 || iCASystemID == 0xd03)//配置其他厂家ca时，目前只有河北冀广专用版本是0x0d03，其他正常版本都是按照0x0d00
#endif
			    {
					D_U16 emmpid_ad;
					
					emmpid_ad = ((D_U16)(buf[4]&0x1f)<<8) + buf[5];
					d_ad_SetDescr((D_U8*)&emmpid_ad,AD_STB_DIVI);
					return ;
				}	
		    }
		    buf += DescrLength+2;
		    NoOfBytesParsedSoFar += DescrLength+2;			
		}
    }
    
}

/** @brief 注册ca获得数据*/
static void ca_mon_get_nit_data_regsiter(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)D_FUNCPOSTFIT
{
    D_Size size;
    D_U8 *buf = (D_U8 *)obj_data;
    if(buf != NULL)
    {
        size = ((buf[1] & 0x0F) << 8) | buf[2] + 3;
        PMON_DUMP (("[pMonitorRegister]send NIT size %d\n", size));
        d_ca_demux_data_cmp (0x40, buf, size);
    }
}
#endif
/** @brief可供外部调用,注册ca 获得数据*/
void p_ca_mon_get_data_regsiter(void)D_FUNCPOSTFIT
{
#ifdef D_CA_SUPPORT
    d_cbman_subscribe(D_MONITOR_PMT_TO_CA, D_INVALID_HANDLE, ca_mon_get_pmt_data_regsiter, NULL );
    d_cbman_subscribe(D_MONITOR_CAT_TO_CA, D_INVALID_HANDLE, ca_mon_get_cat_data_regsiter, NULL );
    d_cbman_subscribe(D_MONITOR_NIT_TO_CA, D_INVALID_HANDLE, ca_mon_get_nit_data_regsiter, NULL );
#endif
}
/** @brief检查是否是主频点
*@param[in] ftype 前端类型
*@param[in] fparam 前端参数
*@return 1 是主频点 0 不是主频点
*/
static D_U8 nit_freq_check(D_FEndType ftype, D_FEndParam fparam)
{
    D_SIParam si_param;
    D_U8 ret;

    ret = p_conf_get_si_param (&si_param);
    if(ret)
    {
        PMON_DERR (("nit_freq_check p_conf_get_si_param error\n"));
        return 0;
    }

    ret = 0;
    switch(ftype)
    {
        case D_FEND_DVBC:
        {
            if(memcmp((void*)&fparam.dvbc, (void*)&si_param.main, sizeof(si_param.main)) == 0)
                ret = 1;
            break;
        }
        case D_FEND_DVBT:
        {
            if(fparam.freq == si_param.main.freq)
                ret = 1;
            break;
        }
        case D_FEND_DVBS:
        {
            if(fparam.freq == si_param.main.freq)
                ret = 1;
            break;
        }
        case D_FEND_DTMB:
        {
            if(fparam.freq == si_param.main.freq)
                ret = 1;
            break;
        }
        case D_FEND_ABS:
        {
            break;
        }
        case D_FEND_ANALOG:
        {
            break;
        }
        default:
            break;
    }
    PMON_DUMP (("nit freq_check\n"));
    return ret;
}
/** @brief nit表监控初始化*/
static void nit_monitor_init(void)
{
    D_NITConfigMoniter nitconfig = {0};

    if(g_custom_config.si_mon.flag & P_SIMON_NIT_EN)
    {
        nitconfig.enable = 1;
    }

    if(g_custom_config.si_mon.flag & P_SIMON_NIT_MAIN_FREQ)
    {
        nitconfig.freq_mode = 1; //只监控主频点
    }

    nitconfig.freq_check = nit_freq_check;

    if(g_custom_config.si_mon.flag & P_SIMON_NIT_NONE_VER)
    {
        nitconfig.moniter_mode = 1; //版本号控制
    }

    nitconfig.time_out = 5000;
    nitconfig.time_hand = D_INVALID_HANDLE;

    d_set_need_version(D_TV_SCAN_NIT, (D_Ptr)&nitconfig);
}
/** @brief pat表监控初始化*/
static void pat_monitor_init(void)
{
    D_PATConfigMoniter patconfig;
    if(g_custom_config.si_mon.flag & P_SIMON_PAT_PMT_CHNAGED_EN)
    {
        patconfig.enable = 1;
    }
    else
    {
        patconfig.enable = 0;
    }
    if(g_custom_config.si_mon.flag & P_SIMON_PAT_NONE_VER) //0不需要版本号控制，1为需要版本号控制
    {
        patconfig.moniter_mode = 1;
    }
    else
    {
        patconfig.moniter_mode = 0;
    }
    patconfig.time_out = 5000;
    patconfig.time_hand = D_INVALID_HANDLE;
    d_set_need_version(D_TV_SCAN_PAT, (D_Ptr)&patconfig);
}
/** @brief cat表监控初始化*/
static void cat_monitor_init(void)
{
    D_CATConfigMoniter catconfig;
    if(g_custom_config.si_mon.flag & P_SIMON_CAT_EN)
        catconfig.enable = 1;
    else
        catconfig.enable = 0;

    if(g_custom_config.si_mon.flag & P_SIMON_CAT_NONE_VER) ///0不需要版本号控制，1为需要版本号控制
        catconfig.moniter_mode = 1;
    else
        catconfig.moniter_mode = 0;

    catconfig.time_out = 5000;
    catconfig.time_hand = D_INVALID_HANDLE;
    d_set_need_version(D_TV_SCAN_CAT, (D_Ptr)&catconfig);
}
/** @brief tdt表监控初始化*/
static void tdt_monitor_init(void)
{
    D_TDTConfigMoniter tdtconfig;

    tdtconfig.enable = 1;
    tdtconfig.moniter_mode = 0; ///0不需要版本号控制，1为需要版本号控制
    tdtconfig.time_out = 5000;
    tdtconfig.time_hand = D_INVALID_HANDLE;
    d_set_need_version(D_TV_SCAN_TDT, (D_Ptr)&tdtconfig);
}
/** @brief sdt表监控初始化*/
static void sdt_monitor_init(void)
{
    D_SDTConfigMoniter sdtconfig;

    sdtconfig.enable = 0;
    if(g_custom_config.si_mon.flag & P_SIMON_SDT_NAME_EN)
    {
        sdtconfig.enable = 1;
        sdtconfig.nameenable = 1;
    }
    else
    {
        sdtconfig.nameenable = 0;
    }
    if(g_custom_config.si_mon.flag & P_SIMON_SDT_CA_FREEMODE_EN)
    {
        sdtconfig.enable = 1;
        sdtconfig.caenable = 1;
    }
    else
    {
        sdtconfig.caenable = 0;
    }
    if(g_custom_config.si_mon.flag & P_SIMON_SDT_NONE_VER)
        sdtconfig.moniter_mode = 1; ///1为需要版本号控制
    else
        sdtconfig.moniter_mode = 0; ///0不需要版本号控制
    sdtconfig.time_out = 5000;
    sdtconfig.time_hand = D_INVALID_HANDLE;
    d_set_need_version(D_TV_SCAN_SDT, (D_Ptr)&sdtconfig);
}

/** @brief 表监控初始化
*@return D_ERR 初始化失败 D_OK 初始化成功
*/
D_Result p_monitor_init(void)D_FUNCPOSTFIT
{
    TVData  *tv_data;

    if (g_htv == D_INVALID_HANDLE)
    {
        PMON_DERR (("Si_init htv error\n"));
        return D_ERR;
    }
    /*取得TV相关数据*/
    tv_data = d_app_get_data (g_htv);
    if(!tv_data)
    {
        PMON_DERR (("Si_init d_app_get_data error\n"));
        return D_ERR;
    }
    /*为解析函数注册回调函数*/
    mon_regsiter(tv_data->ps);
    nit_monitor_init();
    sdt_monitor_init();
    pat_monitor_init();
    tdt_monitor_init();
#if   D_CA_SUPPORT_DEF
    cat_monitor_init();
    if(p_conf_get_curr_ca() != ((1 << 14))) //not abvca
    {
        p_ca_mon_get_data_regsiter();
    }
#endif
    if(g_custom_config.si_mon.flag & P_SIMON_UMT_EN)
    {
        p_umt_start(0);
    }
//    p_bat_start();//add by Wansb 20140402
    return D_OK;
}

/** @brief 进入其它通道时候关掉外挂的通道
*@return D_ERR 初始化失败 D_OK 初始化成功
*/
D_Result p_monitor_close(void)D_FUNCPOSTFIT
{
    if(g_custom_config.si_mon.flag & P_SIMON_UMT_EN)
    {
        p_umt_stop();
    }
//    p_bat_stop();
    return D_OK;
}
/** @brief 重新开启外挂通道
*@return D_ERR 初始化失败 D_OK 初始化成功
*/
D_Result p_monitor_restart(void)D_FUNCPOSTFIT
{
    if(g_custom_config.si_mon.flag & P_SIMON_UMT_EN)
    {
        p_umt_stop();
        p_umt_start(0);
    }
//    p_bat_stop();
 //   p_bat_start();
    return D_OK;
}
/* @}*/
