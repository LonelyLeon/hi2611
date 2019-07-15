/**@file pCheck_updata.c
*@brief 检查升级条件判断
*详细描述
*@author dingl
*@copyright Haier-IC
*@date 2014-06-26
*/
#include "dMonitorTable.h"
#include "pCustomConfig.h"
#include "pMonitorRegister.h"
#include "dMsg.h"
#include "pConfig.h"
#include "dCBMan.h"
#include "pCheck_updata.h"
#include "pStb.h"

/** @brief  umt 发送消息
* @param[in] D_MsgType type       消息类型
* @param[in] D_SiMonParam param   消息信息
* @retval D_OK  成功
* @retval D_ERR  失败
*/
static D_Result updata_event_to_gui(D_MsgType type, D_SiMonParam param) D_FUNCPOSTFIT
{
    D_SIMsg msg;

    msg.type = type;
    msg.hscan = d_app_self ();
    msg.param = param;

    return d_queue_try_send (d_gui_get_queue (), (D_U8*)&msg, sizeof (msg));
}

#ifdef   HI_SOFT_TYPE_DVBS
D_Result p_dvbs_set_tp_info(D_Loader_Descr *descr_info)D_FUNCPOSTFIT
{
    D_SatelliteDeliverySystemDescr  *loader_delivery;
    D_DBTSInfo ts_info;
    D_ID            db_lnb_id;
    D_FDiSEqCType   diseqc_type;
    D_S16 longitude = 0;
    D_DBSateInfo        Sat_delivery_info;
    D_DBAnteInfo        Lnb_info;
    D_FEndLnbInfo   Antinfo, Ret_antinfo;
    D_FEndParam     tp = {0};
    D_LoaderParam   e2p_info ;

    p_conf_get_loader_param(&e2p_info);

    e2p_info.download_flag = 1;
    e2p_info.new_loader_ver = descr_info->software_version;
    e2p_info.tid = descr_info->download_table_id;
    e2p_info.pid = descr_info->download_pid;

    loader_delivery = (D_SatelliteDeliverySystemDescr *)(descr_info->delivery);

    if(loader_delivery->freq == 0)
    {
        if(d_tv_get_curr_db_ts_id() == -1)
        {
            return D_ERR;
        }

        if(d_dbase_get_ts_info (d_tv_get_curr_db_ts_id(), &ts_info) != D_ERR)
        {
            e2p_info.fparam.freq = ts_info.param.dvbs.freq;
            e2p_info.fparam.baud = ts_info.param.dvbs.baud;
            e2p_info.fparam.mod = ts_info.param.dvbs.pol;
        }
        else
        {
            return D_ERR;
        }
        p_conf_set_loader_param(&e2p_info);
    }
    else
    {
        e2p_info.fparam.freq = loader_delivery->freq;
        e2p_info.fparam.baud = loader_delivery->baud;
        e2p_info.fparam.mod = (D_FEndMod)loader_delivery->pol;

        if(loader_delivery->west)
        {
            longitude = 0 - loader_delivery->position * 10;
        }
        else
        {
            longitude = loader_delivery->position * 10;
        }
        D_DUMP("\n longitude = %d \n", longitude);
        /*通过经度获取卫星信息*/
        if( d_dbase_get_sat_info_by_longitude(longitude, &Sat_delivery_info) != D_OK )
            return D_ERR;

        db_lnb_id = (D_ID)Sat_delivery_info.antenna_slot;
        diseqc_type = Sat_delivery_info.diseqc_type;
#if 0
        if(p_conf_get_lnb())
        {
            if(p_conf_get_motortype())
            {
                diseqc_type = D_DISEQC_TYPE_USALS;
            }
            else
            {
                diseqc_type = D_DISEQC_TYPE_12;
            }
            db_lnb_id = (D_ID)p_conf_get_db_ante_id();
        }
#endif
        if((diseqc_type == D_DISEQC_TYPE_10 || diseqc_type == D_DISEQC_TYPE_11 || diseqc_type == D_DISEQC_TYPE_12)
           && D_OK == d_dbase_get_ante_info(db_lnb_id, &Lnb_info))
        {
            D_DUMP("\n Lnb_info.freq1 = %d \n", Lnb_info.freq1);
            /*获取当前的lnb 频率*/
            Antinfo.f22k_state = Sat_delivery_info.diseqc_22k;
            Antinfo.lnbfreq1 = Lnb_info.freq1;
            Antinfo.lnbfreq2 = Lnb_info.freq2;
            tp.dvbs.freq = loader_delivery->freq;
            tp.dvbs.baud = loader_delivery->baud;
            tp.dvbs.pol = loader_delivery->pol;
            d_fman_select_lnb_osc_dvbs(&Antinfo, &tp, &Ret_antinfo);
            e2p_info.lnbfreq1 = Ret_antinfo.lnbfreq1;
            e2p_info.f22kstate = Ret_antinfo.f22k_state;
            e2p_info.diseqc_type = diseqc_type;

            if(diseqc_type == D_DISEQC_TYPE_12)
            {
                e2p_info.diseqc_port = Sat_delivery_info.diseqc_pos;
            }
            else
            {
                e2p_info.diseqc_port = Sat_delivery_info.diseqc_port;
            }

            p_conf_set_loader_param(&e2p_info);
            return D_OK;
        }
        else
        {
            return D_ERR;
        }
    }
}
#else
D_Result p_set_tp_info(D_Loader_Descr *descr_info)D_FUNCPOSTFIT
{
    D_LoaderParam               e2p_info;
    D_CableDeliverySystemDescr      *loader_delivery;
    D_U32 freq;
    D_DBTSInfo ts_info;

    p_conf_get_loader_param(&e2p_info);

    if(descr_info->upgrade_mode == NONE_LOADER_UI)
        e2p_info.download_flag = 2;
    else
        e2p_info.download_flag = 1;

    e2p_info.new_loader_ver = descr_info->software_version;

    loader_delivery = (D_CableDeliverySystemDescr *)(descr_info->delivery);
#ifdef HI_SOFT_TYPE_DVBC
    freq = (loader_delivery->freq) / 10000;
#else if HI_SOFT_TYPE_DTMB
	if(loader_delivery->tag == DESCR_TERR_DEL_SYS)
	{
		#ifdef D_CA_SUPPORT_CDCA
		    freq = (loader_delivery->freq) / 10000;
		#else
		    freq = (loader_delivery->freq) / 100000;
		#endif
	}
	else
	{
		freq = (loader_delivery->freq) / 10000;
	}
#endif
    if(freq >= 100)
    {
#ifdef HI_SOFT_TYPE_DVBC
        e2p_info.fparam.freq = (loader_delivery->freq) / 10000;
        e2p_info.fparam.baud = loader_delivery->baud;
        e2p_info.fparam.mod = loader_delivery->mod;
#else if HI_SOFT_TYPE_DTMB
	if(loader_delivery->tag == DESCR_TERR_DEL_SYS)
	{
		#ifdef D_CA_SUPPORT_CDCA
		e2p_info.fparam.freq = (loader_delivery->freq) / 10000;
		#else
		e2p_info.fparam.freq = (loader_delivery->freq) / 100000;
		#endif
	}
	else
        e2p_info.fparam.freq = (loader_delivery->freq) / 10000;
#endif
    }
    else if(freq == 0)
    {
        if(d_tv_get_curr_db_ts_id() == -1)
        {
            return D_ERR;
        }

        if(d_dbase_get_ts_info (d_tv_get_curr_db_ts_id(), &ts_info) != D_ERR)
        {
#ifdef HI_SOFT_TYPE_DVBC
            e2p_info.fparam.freq = ts_info.param.dvbc.freq;
            e2p_info.fparam.baud = ts_info.param.dvbc.baud;
            e2p_info.fparam.mod = ts_info.param.dvbc.mod;
#else if HI_SOFT_TYPE_DTMB
            e2p_info.fparam.freq = ts_info.param.dtmb.freq;
#endif
        }
        else
        {
            return D_ERR;
        }
    }
    else if((freq >= 1) && (freq < 100))
    {
        D_DBTSID db_ts_id;
        db_ts_id = d_dbase_get_dbtsid_by_tsid(freq);
        if(-1 == db_ts_id)
        {
            return D_ERR;
        }

        if(d_dbase_get_ts_info (db_ts_id, &ts_info) != D_ERR)
        {
#ifdef HI_SOFT_TYPE_DVBC
            e2p_info.fparam.freq = ts_info.param.dvbc.freq;
            e2p_info.fparam.baud = ts_info.param.dvbc.baud;
            e2p_info.fparam.mod = ts_info.param.dvbc.mod;
#else if HI_SOFT_TYPE_DTMB
            e2p_info.fparam.freq = ts_info.param.dtmb.freq;
#endif
        }
        else
        {
            return D_ERR;
        }
    }
    e2p_info.tid = descr_info->download_table_id;
    e2p_info.pid = descr_info->download_pid;

    p_conf_set_loader_param(&e2p_info);
    return D_OK;
}
#endif

D_Result p_check_download_condition(D_Loader *loader_list, D_U8 tag)D_FUNCPOSTFIT
{
    D_U16           Manufacturer_code;
    D_U32           Hardware_code;
    D_U32           sys_sw_id;
    D_U32           sys_area_code;
    D_U8            sys_fuc_id;
    D_U16           sys_sw_ver;
    D_LoaderParam   sys_sw_temp ;
    D_U32           cur_area_code;
    D_U8            new_fuc_id;
    D_U16           new_sw_ver;
    D_Loader_Descr      *descr_next;
    D_U16           sys_parse_sw;
    D_U32               sys_stb_id;

    Manufacturer_code = (D_U16)(CUSTOM_CONFIG.sys.manu_id & 0xffff);
    D_DUMP("\n Manufacturer_code = %x \n", Manufacturer_code);
    Hardware_code = ((D_U32)CUSTOM_CONFIG.sys.hw_id << 24) \
    | ((D_U32)CUSTOM_CONFIG.sys.hw_major << 16) \
    | CUSTOM_CONFIG.sys.hw_minor;
    D_DUMP("\n Hardware_code = %x \n", Hardware_code);
    /*比较厂家id*/
    if(loader_list->manufacturer_code != Manufacturer_code)
    {
        return D_ERR;
    }

    p_conf_get_loader_param(&sys_sw_temp);

    /* 机顶盒的版本号 */
    sys_sw_id =  ((D_U32)sys_sw_temp.stb_param_copy.sw_major << 24) \
    | ((D_U32)sys_sw_temp.stb_param_copy.sw_minor << 16) \
    | (D_U32)sys_sw_temp.stb_param_copy.sw_build_num;
    D_DUMP("\n sys_sw_id = %x \n", sys_sw_id);
    sys_area_code = sys_sw_id >> 12;
    sys_fuc_id = (sys_sw_id & 0xf00) >> 8;
    sys_sw_ver = sys_sw_id & 0xff;

    D_SI_FOR_EACH_BEGIN(D_Loader_Descr, loader_list->loader_list, descr_next)\

    /* linkage 解析出来的版本号 */
    cur_area_code = descr_next->software_version >> 12;
    new_fuc_id = (descr_next->software_version & 0xf00) >> 8;
    new_sw_ver = descr_next->software_version & 0xff;
    
    /* 机顶盒存入解析后的版本号*/
    sys_parse_sw = sys_sw_temp.new_loader_ver & 0xff;
    D_DUMP("\n descr_next->software_version = %x \n", descr_next->software_version);
    if( (descr_next->upgrade_mode == POW_ON_SW_UPDATE) || (descr_next->upgrade_mode == NONE_LOADER_UI))
    {
        if(descr_next->hardware_version != Hardware_code)
        {
            continue;
        }

        if( descr_next->software_version != sys_sw_id )
        {
#ifdef   HI_SOFT_TYPE_DVBS
            if(p_dvbs_set_tp_info(descr_next) != D_OK)
                continue;
            else
                return D_OK;
#else
            if(p_set_tp_info(descr_next) != D_OK)
                continue;
            else
                return D_OK;
#endif
        }
        else
        {
            continue;
        }
    }
    //D_DUMP("\n[p_check_download_condition]:0x%x,0x%x,0x%x,0x%x,0x%x,0x%x \n", descr_next->hardware_version,\
       // Hardware_code, sys_area_code, cur_area_code, sys_fuc_id, new_fuc_id);
    if( (descr_next->hardware_version != Hardware_code) || (sys_area_code != cur_area_code) || (sys_fuc_id != new_fuc_id) )
    {
        continue;
    }

    if( sys_sw_ver == new_sw_ver )
    {
        continue;
    }

    if( (new_sw_ver == sys_parse_sw) && sys_sw_temp.download_flag == 1 )
    {
        continue;
    }

    if(tag == 0xa1) // 永新tag
    {
        sys_stb_id = strtoul(sys_sw_temp.stb_param_copy.stb_id, NULL, 10);
        if( (sys_stb_id < descr_next->stb_sn_start) && (sys_stb_id > descr_next->stb_sn_end) )
        {
            continue;
        }
    }
	
    if( (new_sw_ver == 0 && sys_sw_ver != 0 ) || new_sw_ver > sys_sw_ver )
    {
        D_SiMonParam    msgparam;

#ifdef   HI_SOFT_TYPE_DVBS
        if(p_dvbs_set_tp_info(descr_next) != D_OK)
            continue;
#else
        if(p_set_tp_info(descr_next) != D_OK)
            continue;
#endif

        if( descr_next->upgrade_mode == MANUAL_SW_UPDATE )
        {
            msgparam.swparam.type = D_MSG_MON_SW_UPDATE;
            msgparam.swparam.version = 0;
            msgparam.swparam.pdata = NULL;
            updata_event_to_gui(D_MSG_SI_SW_UPDATE, msgparam);
            return D_OK;
        }
        else if( descr_next->upgrade_mode == FORCE_SW_UPDATE )
        {
            msgparam.swparam.type = D_MSG_MON_SW_UPDATE_MUST;
            msgparam.swparam.version = 0;
            msgparam.swparam.pdata = NULL;
            updata_event_to_gui(D_MSG_SI_SW_UPDATE, msgparam);
            return D_OK;
        }
    }
    D_SI_FOR_EACH_END(D_Loader_Descr, loader_list->loader_list, descr_next)

}

#ifdef D_LOADER_CA_UPDATE
static D_Result ca_event_to_gui(D_MsgType type, D_SiMonParam param) D_FUNCPOSTFIT
{
	D_SIMsg	msg;

	msg.type = type;
	msg.hscan = 	g_stb->player->htv;
	msg.param = param;

	return d_queue_try_send (d_gui_get_queue (), (D_U8*)&msg, sizeof (msg));
}

static D_CA_Loaderinfo PCa_download_Data = {0xFF, 0xFFFF,0xFF,{0},{0},{0},{0},{0},{0},{0},{0}};
D_Result Check_Loader_info(D_CA_Loaderinfo *download_info)
{
	D_U16			sys_manu_id;
	D_U32			sys_hw_id;
	D_U32			sys_sw_id;
	D_LoaderParam	sys_sw_temp ;
	D_U32 			sys_area_code;
	D_U8			sys_fuc_id;
	D_U16			sys_sw_ver;
	D_U32 			cur_area_code;
	D_U8			new_fuc_id;
	D_U16			new_sw_ver;
    	D_U16			sys_parse_sw;

	download_info->tag = 0x85;
	download_info->download_table_id = 0x83;
	
	if(download_info->tag == 0x85)
	{	
		sys_manu_id = (D_U16)(CUSTOM_CONFIG.sys.manu_id&0xffff);
		sys_hw_id = ((D_U32)CUSTOM_CONFIG.sys.hw_id << 24) \
				| ((D_U32)CUSTOM_CONFIG.sys.hw_major << 16) \
				| CUSTOM_CONFIG.sys.hw_minor;

		/*比较厂家id*/
		if(download_info->manufacturer_code != sys_manu_id)
		{
		    return D_ERR;
		}

		p_conf_get_loader_param(&sys_sw_temp);

		/* 机顶盒的版本号 */
		sys_sw_id =  ((D_U32)sys_sw_temp.stb_param_copy.sw_major<< 24) \
		| ((D_U32)sys_sw_temp.stb_param_copy.sw_minor<< 16) \
		| (D_U32)sys_sw_temp.stb_param_copy.sw_build_num;

		sys_area_code = sys_sw_id >> 12;			
		sys_fuc_id = (sys_sw_id & 0xf00) >> 8;
		sys_sw_ver = sys_sw_id & 0xff;
		
		/* 联广CA 的LOADER 版本号 */
		cur_area_code = download_info->software_version>>12;
		new_fuc_id = (download_info->software_version&0xf00)>>8;
		new_sw_ver = download_info->software_version & 0xff;
		/* 机顶盒存入解析后的版本号*/
		sys_parse_sw = sys_sw_temp.new_loader_ver & 0xff;

		if( (download_info->hardware_version != sys_hw_id) ||(sys_area_code != cur_area_code) || (sys_fuc_id != new_fuc_id) )
		{
		    return D_ERR;
		}
			
		if( sys_sw_ver == new_sw_ver )  
		{
		    return D_ERR;
		}

		if( (new_sw_ver == sys_parse_sw) && sys_sw_temp.download_flag == 1 ) 
		{
		    return D_ERR;
		}
		#if 1
		if( new_sw_ver == 0xff )
			new_sw_ver = 0x00;
		#endif
		if( (new_sw_ver == 0 && sys_sw_ver != 0 ) || new_sw_ver > sys_sw_ver )        
		{
			D_SiMonParam	msgparam;
			memcpy(&(PCa_download_Data), download_info, sizeof(D_CA_Loaderinfo));
			msgparam.swparam.type = D_MSG_MON_CA_UPDATE_FORCE;
			msgparam.swparam.version = 0;
			msgparam.swparam.pdata = (D_Ptr)(&(PCa_download_Data));
			ca_event_to_gui(D_MSG_SI_SW_UPDATE,msgparam);
			return D_OK;
		}
	}		
}
#endif


