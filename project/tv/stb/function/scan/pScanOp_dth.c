/** @file
* @brief 直播星村村通户户通搜索时的的一些注册函数
* @author 覃宜
* @date 2013-4-4 覃宜: 建立文件
*/

#include "dSI.h"
#include "dDescr.h"
#include "dSIParse.h"
#include "dDBase.h"
#include "pDBaseDefault.h"
#include "dMem.h"
#include "dSys.h"
#include "dDebug.h"
#include "dScan.h"
#include "pConfig.h"

#define MAX_SEARCH_FREQ_S	12900
#define MIN_SEARCH_FERQ_S	11700

#define DTH_PAT_TIMEOUT			2000
#define DTH_CAT_TIMEOUT			3000
#define DTH_SDT_TIMEOUT			10000
#define DTH_PMT_TIMEOUT  			2000
#define DTH_SDT_OTH_TIMEOUT		10000
#define DTH_NIT_TIMEOUT			10000
#define DTH_BAT_TIMEOUT			10000


/** @brief 直播星项目国标T 频点(单位KHz)*/
#if 0
const static D_U32 
as_dth_dmbt_freq_list[] = 
{
52500,60500,68500,80000,
88000,171000,179000,187000,
195000,203000,211000,219000,
474000,482000,490000,498000,
506000,514000,522000,530000,
538000,546000,554000,562000,
610000,618000,626000,634000,
642000,650000,658000,666000,
674000,682000,690000,698000,
706000,714000,722000,730000,
738000,746000,754000,762000,
770000,778000,786000,794000
};
#endif

static D_U8 search_ca_prompt;  // CA 控制音视频是否播放 与 节目自动搜索是否由CA BOU ID 控制
static D_U16 ca_bouq_id = 0xffff;
static D_Bool got_bouq_id_flag = D_FALSE;


//extern D_Bool		nit_changed;
extern D_Bool		si_param_got;
extern D_Bool       ts_info_got;
extern D_Bool 	HHT_dan_mode;


#ifdef D_SUPPORT_NDS_CA
extern D_U32 ca_get_bouguet_ID();
#endif


static D_ASGroupOp DTH_AutoScanGroup_Op;




/*私有初始化, 对各组进行分配并初始化。主要设定搜索策略与频率列表*/
static D_Result dth_auto_scan_init (D_ASGroup **group, D_U32*group_cnt, D_ScanTaskConfig *as_config, D_HMMan hmm)
{
	D_ASGroup*scan_group = NULL;
	D_U32	group_id = 0;
	D_U32  ts_num, i;
	D_DBTSInfo tsinfo;	
	D_FEndParam *fendp;


	/*根据各搜索类型配置各组*/	
	if(as_config->scan_type & D_SCAN_TYPE_ABS)
	{

		scan_group = (D_ASGroup*) d_mman_alloc (hmm, sizeof (D_ASGroup));
		if(!scan_group)
		{
			D_ERROR ("[AutoScan] Cannot allocate group\n");
			return D_ERR;
		}
		
		group[group_id++] = scan_group;
		
		memset(scan_group, 0x00, sizeof (D_ASGroup));	
		scan_group->type = D_SCAN_TYPE_ABS;
		scan_group->scan_mode = D_AUTO_SCAN_MODE_TP;
		scan_group->nit_strategy = D_NIT_STRA_NOT_COVER;
		scan_group->fend_type = D_FEND_DVBS;
		scan_group->hfman = d_fman_get_handle_by_type(D_FEND_DVBS, 0);
		scan_group->findSrvInfoInMain = D_TRUE;		
		scan_group->groupOp = &DTH_AutoScanGroup_Op;


				
		ts_num = d_dbase_get_ts_total_num();
		for (i=0; i<ts_num; i++)
		{
			if(D_OK != d_dbase_get_ts_info_by_num(i, &tsinfo))
				continue;
			
			if(tsinfo.tuner_type == D_FEND_DVBS)
			{
				fendp = (D_FEndParam *)d_mman_alloc(hmm, sizeof (D_FEndParam));
				if(fendp)
				{
					memcpy(fendp, &tsinfo.param, sizeof (D_FEndParam));
					scan_group->fend_param_list[scan_group->scanFendParamList_cnt++] = fendp;
				}			
			}
		}
	}

	if(as_config->scan_type & D_SCAN_TYPE_DMBT)
	{
		scan_group = (D_ASGroup*) d_mman_alloc (hmm, sizeof (D_ASGroup));
		if(!scan_group)
		{
			D_ERROR ("[AutoScan] Cannot allocate group\n");
			return D_ERR;
		}
		
		group[group_id++] = scan_group;
		
		memset(scan_group, 0x00, sizeof (D_ASGroup));
		scan_group->type = D_SCAN_TYPE_DMBT;
		scan_group->scan_mode = D_AUTO_SCAN_MODE_TP;
		scan_group->nit_strategy = D_NIT_STRA_NONE;
		scan_group->fend_type = D_FEND_DTMB;
		scan_group->hfman = d_fman_get_handle_by_type(D_FEND_DTMB, 0);
		scan_group->findSrvInfoInMain = D_FALSE;			
		scan_group->groupOp = &DTH_AutoScanGroup_Op;

				
		ts_num = d_dbase_get_ts_total_num();
		for (i=0; i<ts_num; i++)
		{
			if(D_OK != d_dbase_get_ts_info_by_num(i, &tsinfo))
				continue;
			
			if(tsinfo.tuner_type == D_FEND_DTMB)
			{
				fendp = (D_FEndParam *)d_mman_alloc(hmm, sizeof (D_FEndParam));
				if(fendp)
				{
					memcpy(fendp, &tsinfo.param, sizeof (D_FEndParam));
					scan_group->fend_param_list[scan_group->scanFendParamList_cnt++] = fendp;
				}
			}
		}
	}

	/*记录组数*/
	*group_cnt = group_id;

	return D_OK;
}


/** @brief将搜索结果保存至数据库。*/
static D_Result dth_auto_scan_store(D_ASGroup **group, D_U32 group_cnt, D_ScanTaskConfig *as_config)
{
	D_U16 groupid, idx;
	D_DBID dbid;
	D_ScanSrvInfoNode *srv;
	D_DBSrvInfo srvinfo;
	D_ASGroup	*scan_group;
	D_ID db_ts_id[D_SCAN_GROUP_MAX_TP_CNT];
	D_ID db_bouq_id[D_SCAN_MAX_BOUQ_CNT] = {0};

	/*对每组的搜索结果进行保存*/
	for(groupid = 0; groupid < group_cnt; groupid++)
	{
		scan_group = group[groupid];
		
		//d_dbase_delete_srvs_bytype(scan_group->fend_type);		

		/*存储频点信息*/
		for(idx = 0; idx < D_SCAN_GROUP_MAX_TP_CNT; idx++)
		{
			db_ts_id[idx] = -1;
			
			if(scan_group->scanResult.tsinfo[idx])
			{
				/*保存频点信息*/
				dbid = d_dbase_get_ts_by_param (as_config->db_net_id, scan_group->fend_type, &scan_group->scanResult.tsinfo[idx]->param);
				if (-1 != dbid) 
				{
					/*更新频点信息*/
					d_dbase_updata_ts_info(dbid, scan_group->scanResult.tsinfo[idx]);
				}	
				else
				{
					/*添加频点，并更新频点记录集信息*/
					dbid = d_dbase_insert_ts (scan_group->scanResult.tsinfo[idx]);
				}

				/*每个频点在数据库里的id*/
				db_ts_id[idx] = dbid;
			}
		}

		/*保存业务群信息*/
		for(idx = 0; idx < scan_group->scanResult.bouq_cnt; idx++)
		{
			dbid = d_dbase_insert_bouq (scan_group->scanResult.bouq_info[idx]);
			db_bouq_id[idx] = dbid;
		}

		/*对所有节目进行排序*/

		/*保存所有节目*/
		srv = scan_group->scanResult.srvList_tv;
		while(srv)
		{
			if(!srv->valid)
			{
				srv = srv->next;
				continue;
			}
			
			srvinfo = srv->srvinfo;
			if (srvinfo.chan_num == -1)
			{
				if(HHT_dan_mode)
				{
					srvinfo.chan_num = d_dbase_get_free_chan_num((D_DBSrvType)srvinfo.srv_type);
				}
				else
				{
					srvinfo.chan_num = d_dbase_get_free_chan_num_ex((D_DBSrvType)srvinfo.srv_type, scan_group->fend_type);
				}
			}

			if(srv->tpid < scan_group->scanFendParamList_cnt)
			{
				srvinfo.db_ts_id = db_ts_id[srv->tpid];
			}
			if(srv->bouq_idx < scan_group->scanResult.bouq_cnt)
			{
				srvinfo.db_bouq_id = db_bouq_id[srv->bouq_idx];
			}

			if(srvinfo.db_ts_id == -1)
			{
				D_ERROR ("[AutoScan] tv srvinfo.db_ts_id == -1 !!!\n");
			}
			else
			{			
				dbid = d_dbase_insert_srv (&srvinfo);
				if (-1 == dbid)
				{
					D_ERROR ("[AutoScan] Cannot add new tv service !!!\n");
				}
				
				D_DUMP("[AutoScan] Add TV db_srv_id: %d -> %s %03d srvid:%x vid:%x aud1:%x aud2:%x pcr:%x\n", \
					dbid, \
					srvinfo.name,\
					srvinfo.chan_num,\
					srvinfo.srv_id,\
					srvinfo.vid_pid,\
					srvinfo.aud1_pid,\
					srvinfo.aud2_pid,\
					srvinfo.pcr_pid);
			}
			
			srv = srv->next;
		}

		srv = scan_group->scanResult.srvList_radio;
		while(srv)
		{
			if(!srv->valid)
			{
				srv = srv->next;
				continue;
			}
			
			srvinfo = srv->srvinfo;
			if (srvinfo.chan_num == -1)
			{
				if(HHT_dan_mode)
				{
					srvinfo.chan_num = d_dbase_get_free_chan_num((D_DBSrvType)srvinfo.srv_type);
				}
				else
				{
					srvinfo.chan_num = d_dbase_get_free_chan_num_ex((D_DBSrvType)srvinfo.srv_type, scan_group->fend_type);
				}
			}

			if(srv->tpid < scan_group->scanFendParamList_cnt)
			{
				srvinfo.db_ts_id = db_ts_id[srv->tpid];
			}
			if(srv->bouq_idx < scan_group->scanResult.bouq_cnt)
			{
				srvinfo.db_bouq_id = db_bouq_id[srv->bouq_idx];
			}
			
			if(srvinfo.db_ts_id == -1)
			{
				D_ERROR ("[AutoScan] radio srvinfo.db_ts_id == -1 !!!\n");
			}
			else
			{			
				dbid = d_dbase_insert_srv (&srvinfo);
				if (-1 == dbid)
				{
					D_ERROR ("[AutoScan] Cannot add new tv service !!!\n");
				}
				
				D_DUMP("[AutoScan] Add Radio db_srv_id: %d -> %s %03d srvid:%x vid:%x aud1:%x aud2:%x pcr:%x\n", \
					dbid, \
					srvinfo.name,\
					srvinfo.chan_num,\
					srvinfo.srv_id,\
					srvinfo.vid_pid,\
					srvinfo.aud1_pid,\
					srvinfo.aud2_pid,\
					srvinfo.pcr_pid);
			}
			
			srv = srv->next;
		}
	}

	return D_OK;
}

static D_Result dth_auto_scan_destroy (D_ASGroup **group, D_U32 group_cnt, D_ScanTaskConfig *as_config)
{	
	D_U16 groupid;
	D_ASGroup	*scan_group;
	D_SIParam si_param;
	D_U32 store_bouq_id;
	D_U16 flag;

	for(groupid = 0; groupid < group_cnt; groupid++)
	{
		scan_group = group[groupid];
		
		if(scan_group && scan_group->type == D_SCAN_TYPE_ABS)
		{
			if(got_bouq_id_flag)
			{
				flag = D_CONF_BOUQUET_ID_FLAG;
				store_bouq_id = ((D_U32)flag << 16) | (D_U32)ca_bouq_id;
				p_conf_set_bouquet_id(store_bouq_id);
				D_DUMP("dth store_bouq_id: 0x%x\n", ca_bouq_id);
			}
					
			p_conf_get_si_param(&si_param , 0);	
			if (scan_group->scanResult.found_chan_ver)/*搜索不到也不再更新*/
			{
				si_param.nit_version = scan_group->scanResult.chan_version;
			}

			si_param.chan_update_flag = D_FALSE;
			p_conf_set_si_param(&si_param, 0);
			D_DUMP("dth store s_chan_update_ver: 0x%x\n", si_param.nit_version);		
		}
		else if(scan_group && scan_group->type == D_SCAN_TYPE_DMBT)
		{
			p_conf_get_si_param(&si_param , 1);
			si_param.chan_update_flag = D_FALSE;
			p_conf_set_si_param(&si_param, 1);
		}		
	}

	/*搜索结束后全局变量复位 */
	nit_changed = D_FALSE;
	si_param_got = D_FALSE;
	ts_info_got = D_FALSE;
	
	return D_OK;
}


D_AutoScanOp DTH_AutoScan_Op = 
{
	dth_auto_scan_init,
	dth_auto_scan_store,
	dth_auto_scan_destroy
};








/*私有初始化*/
static D_Result dth_group_start (D_ASGroup *scan_group)
{
	if(scan_group->type == D_SCAN_TYPE_ABS)
	{
		got_bouq_id_flag = D_FALSE;
		p_conf_get_ca_mode(&search_ca_prompt);
	}
	return D_OK;
}

/*私有反初始化*/
static D_Result dth_group_end(D_ASGroup *scan_group)
{	
	return D_OK;
}


/*检查ca_sys_id是否符合定制要求*/
static D_Bool dth_check_ca_sys_id (D_U32 type, D_U16 ca_sys_id)
{	
	D_Bool ret = D_TRUE;
		
	if(type == D_SCAN_TYPE_ABS)
	{
#ifdef D_SUPPORT_NDS_CA
		ret = d_ca_sys_check (ca_sys_id);
#endif
	}

	return ret;
}


/*检查业务群id 是否符合定制要求*/
static D_Bool dth_check_bouq_id (D_U32 type, D_U16 bouq_id) 
{
	D_Bool ret = D_TRUE;
	
	if(type == D_SCAN_TYPE_ABS)
	{	
		if(bouq_id != ca_bouq_id)
		{
			ret = D_FALSE;
		}
	}

	return ret;
}


/*检查服务是否符合定制要求*/
static D_Bool dth_check_srvice (D_U32 type, D_ScanSrvInfoNode *srvinfo) 
{
	D_Bool ret = D_TRUE;

	if(type == D_SCAN_TYPE_ABS)
	{
		if(!(srvinfo->valid))
		{
			ret = D_FALSE;
		}
		
		if(srvinfo->bouq_mask == 0 && search_ca_prompt == 1)
		{
			ret = D_FALSE;
		}
	}

	return ret;
}

/*sdt表里提取服务信息*/
static D_Result dth_get_private_descrs_info_in_sdt(D_U32 type, D_Descr *descr, D_ScanSrvInfoNode *srv_info)
{
	if(type == D_SCAN_TYPE_ABS)
	{
		switch(descr->tag)
		{			
			/*音量补偿描述符*/
			case DESCR_VOLUME_COMPENSATE:
			{
				D_VolumeCompensationDescr *volume_compensate_descr = (D_VolumeCompensationDescr*)descr;
				srv_info->srvinfo.volume = volume_compensate_descr->compensation;
			}
			break;
			
			default:
				break;
		}
	}

	return D_OK;
}

/*bat表里提取服务信息*/
static D_Result dth_get_srvinfo_in_bat(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfoNode *srv_info, D_ScanResultValue *result)
{
	D_BatTS	*ts;
	D_Bat	*bat;
	D_Descr	*descr;
	D_Bool	got_srv_list, got_srv_num;
	
	D_ScanTp *tp = scants->scantp;
	
	if(type == D_SCAN_TYPE_ABS)
	{	
		got_srv_list = D_FALSE;
		got_srv_num = D_FALSE;
		
		/* 取bat表的ts描述子 ，即第二层*/
		D_SI_FOR_EACH_BEGIN (D_Bat, tp->bats, bat)
			if(!dth_check_bouq_id(type, bat->bouq_id))
			{
				continue;
			}
			
			D_SI_FOR_EACH_BEGIN (D_BatTS, bat->tses, ts)
				if (/*(ts->org_net_id == tp->org_net_id) &&*/(ts->ts_id == tp->ts_id))
				{
					D_SI_FOR_EACH_BEGIN (D_Descr, ts->descrs, descr)
						if (descr->tag == DESCR_SERVICE_LIST) 
						{
							D_ServiceListDescr	*dsl = (D_ServiceListDescr*) descr;
							
							if (dsl->srv_id == srv_info->srvinfo.srv_id && got_srv_list == D_FALSE && srv_info->bouq_mask == 0) 
							{
								D_Int	i;
								
								for (i = 0; i < result->bouq_cnt; i++) 
								{
									if (result->bouq_info[i]->bouq_id == bat->bouq_id) 
									{
										srv_info->bouq_mask !=(1 << i);
										break;
									}
								}
								got_srv_list = D_TRUE;
							}
						}
						else if(descr->tag == DESCR_CHANNEL_NUM)
						{
							D_ChannelOrderDescr *dcod = (D_ChannelOrderDescr*)descr;

							if(dcod->service_id == srv_info->srvinfo.srv_id && got_srv_num == D_FALSE)
							{
								srv_info->srvinfo.chan_num = dcod->logical_chan_num;
								/*直播星只在bat里第二层找visible_service_flag*/
								if(!dcod->visible_flag)
								{
									srv_info->valid = D_FALSE;
								}
								got_srv_num = D_TRUE;
							}
						}
					D_SI_FOR_EACH_END (D_Descr, ts->descrs, descr)
				}
			D_SI_FOR_EACH_END (D_BatTS, bat->tses, ts)

			if(got_srv_list && got_srv_num)
			{
				break;
			}
		D_SI_FOR_EACH_END (D_Bat, tp->bats, bat)
		
		if(srv_info->srvinfo.chan_num == -1)
		{
			got_srv_num = D_FALSE;
			
		   	/* 取bat 表描述子 ，即第一层*/
			D_SI_FOR_EACH_BEGIN (D_Bat, tp->bats, bat)
				if(!dth_check_bouq_id(type, bat->bouq_id))
				{
					continue;
				}			
				D_SI_FOR_EACH_BEGIN (D_Descr, bat->descrs, descr)
				if(descr->tag == DESCR_CHANNEL_NUM)
		   		{
					D_ChannelOrderDescr *dcod = (D_ChannelOrderDescr*)descr;

					if(dcod->service_id == srv_info->srvinfo.srv_id && got_srv_num == D_FALSE)
					{
						srv_info->srvinfo.chan_num = dcod->logical_chan_num;
						/*直播星只在bat里第二层找visible_service_flag*/
						//if(!dcod->visible_flag)srv_info->valid = D_FALSE;
						got_srv_num = D_TRUE;
						break;
					}
		   		}
				D_SI_FOR_EACH_END (D_Descr, bat->descrs, descr)
				if(got_srv_num)
				{
					break;
				}
			D_SI_FOR_EACH_END (D_Bat, tp->bats, bat)
		}
	}

	return D_OK;
}


/*nit表里提取服务信息*/
static D_Result dth_get_srvinfo_in_nit(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfoNode *srv_info, D_ScanResultValue *result)
{
	D_Nit      *nit;
	D_NitTS	*ts;
	D_Descr	*descr;
	
	D_ScanTp *tp = scants->scantp;
	
	if(type == D_SCAN_TYPE_ABS)
	{		
		/*BAT表内找不到频道号再在NIT表内查找*/
              if(srv_info->srvinfo.chan_num == -1)
              {
			D_SI_FOR_EACH_BEGIN(D_Nit, tp->nits, nit)
				D_SI_FOR_EACH_BEGIN(D_NitTS, nit->tses, ts)
					D_SI_FOR_EACH_BEGIN (D_Descr, ts->descrs, descr)
					if(descr->tag == DESCR_CHANNEL_NUM)
					{
						D_ChannelOrderDescr *dcod = (D_ChannelOrderDescr*)descr;

						if(dcod->service_id == srv_info->srvinfo.srv_id)
						{
							srv_info->srvinfo.chan_num = dcod->logical_chan_num;
							/*直播星只在bat里第二层找visible_service_flag*/
							//if(!dcod->visible_flag)srv_info->valid = D_FALSE;
						}
					}
					D_SI_FOR_EACH_END (D_Descr, ts->descrs, descr)
				D_SI_FOR_EACH_END(D_NitTS, nit->tses, ts)
			D_SI_FOR_EACH_END(D_Nit, tp->nits, nit)
		}
	}

	return D_OK;
}

/*其它私有表里提取服务信息*/
static D_Result dth_get_srvinfo_in_others(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfoNode *srv_info, D_ScanResultValue *result)
{
	return D_OK;
}


/*单频点搜索配置*/
static D_Result dth_set_tpsiscan_config(D_ASGroup *scan_group, D_TpSiScanTaskConfig *conf)
{
	conf->pat_timeout = DTH_PAT_TIMEOUT;
	conf->pmt_timeout = DTH_PMT_TIMEOUT;
	conf->cat_timeout = DTH_CAT_TIMEOUT;
	conf->bat_timeout = DTH_BAT_TIMEOUT;
	conf->nit_timeout = DTH_NIT_TIMEOUT;
	conf->sdt_timeout = DTH_SDT_TIMEOUT;	
	conf->sdt_oth_timeout = DTH_SDT_OTH_TIMEOUT;
	
	conf->lock_enable = D_FALSE;									
	conf->table_mask = 0;
	
	if(!got_bouq_id_flag)
	{
#ifdef D_SUPPORT_NDS_CA
		ca_bouq_id = ca_get_bouguet_ID();
#endif
		got_bouq_id_flag = D_TRUE;
	}
		
	if(scan_group->scan_mode == D_AUTO_SCAN_MODE_NIT && scan_group->scanResult.found_nit == D_FALSE)
	{
		conf->table_mask |= TABLE_MASK_NIT;
	}
	else
	{
		conf->table_mask |= TABLE_MASK_PAT | TABLE_MASK_PMT | TABLE_MASK_CAT | TABLE_MASK_SDT | TABLE_MASK_NIT;
		if(scan_group->type == D_SCAN_TYPE_ABS)
		{
			conf->bouq_id = ca_bouq_id;
			{
				conf->table_mask |= TABLE_MASK_BAT;
			}
		}
	}
	return D_OK;
}

/*nit表里提取频率列表信息*/
D_Result dth_get_freqlist_in_nit(D_U32 type, D_ScanTsInfoNode *scants, D_FEndParam*fparam, D_U32 *fcnt)
{
	D_NitTS	*ts;
	D_Descr	*descr;
	D_Nit      *nit;
	D_DBTSID	db_ts_id = -1;
	D_DBTSInfo	ts_info;
	D_FEndParam param;

	if(!scants ||!scants->scantp || !scants->scantp->nits || !fparam || !fcnt)
	{
		return D_ERR;
	}

	if(type == D_SCAN_TYPE_ABS)
	{
		D_SI_FOR_EACH_BEGIN (D_Nit, scants->scantp->nits, nit)			
			D_SI_FOR_EACH_BEGIN (D_NitTS, nit->tses, ts)
				D_SI_FOR_EACH_BEGIN (D_Descr, ts->descrs, descr)
					switch (descr->tag) 
					{
						case DESCR_SAT_DEL_SYS:/*卫星*/
							if(tp->type == D_FEND_DVBS)
							{
								D_SatelliteDeliverySystemDescr *sds = (D_SatelliteDeliverySystemDescr*) descr;
								
								memset(&param, 0x00, sizeof(D_FEndParam));
								param.abs.freq = sds->freq;
								param.abs.baud = sds->baud;
								param.abs.pol = (D_FEndPol)sds->pol;
								D_DUMP("[AutoScan] nit SAT_DEL_SYS find freq:%d baud:%d, pol:%d\n",param.abs.freq, param.abs.baud, param.abs.pol);
								if((param.freq >= MIN_SEARCH_FERQ_S) && (param.freq <= MAX_SEARCH_FREQ_S) )
								{	
									if((*fcnt) < D_SCAN_GROUP_MAX_TP_CNT)
									{
										fparam[(*fcnt)++] = param;
										
										db_ts_id = d_dbase_get_ts_by_param (0, D_FEND_DVBS, &param);
										if (db_ts_id == -1)
										{
											D_DB_TS_INFO_INIT(&ts_info);
											ts_info.param = param;
											ts_info.tuner_type= D_FEND_DVBS;
											d_dbase_insert_ts (&ts_info);
											D_DUMP("[AutoScan] add the freq:%d \n",param.abs.freq);
										}
									}
								}
							}
							break;
						default:
							break;
					}
				D_SI_FOR_EACH_END (D_Descr, ts->descrs, descr)
			D_SI_FOR_EACH_END (D_NitTS, nit->tses, ts)
		D_SI_FOR_EACH_END (D_Nit, scants->scantp->nits, nit)
	}
	
	return D_OK;
}


/*提取频点上关心的一些信息, 比如节目版本号等*/
D_Result dth_get_tp_info(D_U32 type,  D_ScanTsInfoNode *scants, D_ScanResultValue *scanResult, D_DBTSInfo  *tsinfo)
{
	D_Descr	*descr;
	D_Nit      *nit;	
	D_ScanTp *tp = scants->scantp;
	
	/*查找节目更新描述符*/
	D_SI_FOR_EACH_BEGIN(D_Nit, tp->nits, nit)
		D_SI_FOR_EACH_BEGIN (D_Descr, nit->descrs, descr)
			if(descr->tag == DESCR_CHANNEL_UPDATE)
			{
				D_ChanVersionDescr *dcvd = (D_ChanVersionDescr*)descr;

				//tsinfo->srv_update_ver = dcvd->version;
				scanResult->found_chan_ver = D_TRUE;
				scanResult->chan_version = dcvd->version;
				D_DUMP("[AutoScan] find chan_update_ver :%d\n", dcvd->version);
			}
		D_SI_FOR_EACH_END (D_Descr, nit->descrs, descr)
	D_SI_FOR_EACH_END(D_Nit, tp->nits, nit)

	return D_OK;
}

static D_Result dth_group_end_private_op(D_ASGroup *scan_group, D_HMMan hmm)
{
	D_U8 ts_num, i;
	D_DBTSInfo tsinfo;
	D_FEndParam *fendp;
	
	if(scan_group->type == D_SCAN_TYPE_ABS)
	{
		if(!scan_group->scanResult.locked_flag)
		{
			//添加直播星其它频点
			i = d_dbase_get_ts_total_num();
			
			/*数据库里增加其它可用的频点*/
			d_dbase_rset_add_ts_ex();
			
			ts_num = d_dbase_get_ts_total_num();
		
			for (; i<ts_num; i++)
			{
				if(D_OK != d_dbase_get_ts_info_by_num(i, &tsinfo))
					continue;
				
				if(tsinfo.tuner_type == D_FEND_DVBS)
				{
					fendp = (D_FEndParam *)d_mman_alloc(hmm, sizeof (D_FEndParam));
					if(fendp)
					{
						memcpy(fendp, &tsinfo.param, sizeof (D_FEndParam));
						scan_group->fend_param_list[scan_group->scanFendParamList_cnt++] = fendp;
					}
				}
			}			
		}
	}
	return D_OK;
}

/*直播星自动搜索操作*/
static D_ASGroupOp DTH_AutoScanGroup_Op = 
{
	dth_group_start,
	dth_group_end,
	dth_set_tpsiscan_config,
	dth_check_ca_sys_id,
	dth_check_bouq_id,
	dth_group_end_private_op,
	dth_get_freqlist_in_nit,
	dth_get_tp_info,	
	dth_get_private_descrs_info_in_sdt,
	dth_get_srvinfo_in_bat,
	dth_get_srvinfo_in_nit,
	dth_get_srvinfo_in_others,
	dth_check_srvice
};








/*私有初始化, 对各组进行分配并初始化。主要设定搜索策略与频率列表*/
static D_Result dth_manual_scan_init(D_U32 type, D_ScanTaskConfig *ms_config)
{
	if(type == D_SCAN_TYPE_ABS)
	{
		p_conf_get_ca_mode(&search_ca_prompt);	
#ifdef D_SUPPORT_NDS_CA
		ca_bouq_id = ca_get_bouguet_ID();
#endif
	}
	
	return D_OK;
}


static D_Result dth_manual_scan_store(D_U32 type, D_ScanTaskConfig *ms_config, D_ScanResultValue*ms_result)
{
	D_DBID dbid, idx;
	D_ID db_ts_id;
	D_ScanSrvInfoNode *srv;
	D_DBSrvInfo srvinfo;
	D_ID db_bouq_id[D_SCAN_MAX_BOUQ_CNT] = {0};

	if((!ms_result) || (!(ms_result->tsinfo[0])))
	{
		return D_ERR;
	}

	/*保存频点信息*/
	db_ts_id = d_dbase_get_ts_by_param (ms_result->db_net_id, ms_result->fend_type, &ms_result->tsinfo[0]->param);
	if (-1 != db_ts_id) 
	{
		/*删除当前频点下原有的节目，并更新频点信息*/
		d_dbase_delete_srvs_of_ts(db_ts_id);
		d_dbase_updata_ts_info(db_ts_id, ms_result->tsinfo[0]);
	}	
	else
	{
		/*添加频点，并更新频点记录集信息*/
		db_ts_id = d_dbase_insert_ts (ms_result->tsinfo[0]);
		d_dbase_get_ts_total_num();
	}

	if(db_ts_id == -1)
	{
		D_ERROR ("[ManualScan] db_ts_id == -1 !!!\n");
		return D_ERR;
	}

	/*保存业务群信息*/
	for(idx = 0; idx < ms_result->bouq_cnt; idx++)
	{
		dbid = d_dbase_insert_bouq (ms_result->bouq_info[idx]);
		db_bouq_id[idx] = dbid;
	}

	/*对所有节目进行排序*/

	/*保存所有节目*/
	srv = ms_result->srvList_tv;
	while(srv)
	{
		if(!srv->valid)
		{
			srv = srv->next;
			continue;
		}
		
		srvinfo = srv->srvinfo;
		if (srvinfo.chan_num == -1)
		{
			if(HHT_dan_mode)
			{
				srvinfo.chan_num = d_dbase_get_free_chan_num((D_DBSrvType)srvinfo.srv_type);
			}
			else
			{
				srvinfo.chan_num = d_dbase_get_free_chan_num_ex((D_DBSrvType)srvinfo.srv_type, ms_result->fend_type);
			}
		}

		srvinfo.db_ts_id = db_ts_id;

		if(srv->bouq_idx < ms_result->bouq_cnt)
		{
			srvinfo.db_bouq_id = db_bouq_id[srv->bouq_idx];
		}
		
		dbid = d_dbase_insert_srv (&srvinfo);
		if (-1 == dbid)
		{
			D_ERROR ("[ManualScan] Cannot add new tv service !!!\n");
		}
		
		D_DUMP("[ManualScan] Add TV db_srv_id: %d -> %s %03d srvid:%x vid:%x aud1:%x aud2:%x pcr:%x\n", \
			dbid, \
			srvinfo.name,\
			srvinfo.chan_num,\
			srvinfo.srv_id,\
			srvinfo.vid_pid,\
			srvinfo.aud1_pid,\
			srvinfo.aud2_pid,\
			srvinfo.pcr_pid);
		
		srv = srv->next;
	}

	srv = ms_result->srvList_radio;
	while(srv)
	{
		if(!srv->valid)
		{
			srv = srv->next;
			continue;
		}
		
		srvinfo = srv->srvinfo;
		if (srvinfo.chan_num == -1)
		{
			if(HHT_dan_mode)
			{
				srvinfo.chan_num = d_dbase_get_free_chan_num((D_DBSrvType)srvinfo.srv_type);
			}
			else
			{
				srvinfo.chan_num = d_dbase_get_free_chan_num_ex((D_DBSrvType)srvinfo.srv_type, ms_result->fend_type);
			}
		}

		srvinfo.db_ts_id = db_ts_id;

		if(srv->bouq_idx < ms_result->bouq_cnt)
		{
			srvinfo.db_bouq_id = db_bouq_id[srv->bouq_idx];
		}
		
		dbid = d_dbase_insert_srv (&srvinfo);
		if (-1 == dbid)
		{
			D_ERROR ("[ManualScan] Cannot add new tv service !!!\n");
		}
		
		D_DUMP("[ManualScan] Add Radio db_srv_id: %d -> %s %03d srvid:%x vid:%x aud1:%x aud2:%x pcr:%x\n", \
			dbid, \
			srvinfo.name,\
			srvinfo.chan_num,\
			srvinfo.srv_id,\
			srvinfo.vid_pid,\
			srvinfo.aud1_pid,\
			srvinfo.aud2_pid,\
			srvinfo.pcr_pid);
		
		srv = srv->next;
	}	

	return D_OK;
}


static D_Result dth_manual_scan_destroy(D_U32 type, D_ScanTaskConfig *ms_config, D_ScanResultValue*ms_result)
{
	return D_OK;
}


/*单频点搜索配置*/
static D_Result dth_manual_scan_set_tpsiscan_config(D_U32 type, D_TpSiScanTaskConfig *conf)
{
	conf->pat_timeout = DTH_PAT_TIMEOUT;
	conf->pmt_timeout = DTH_PMT_TIMEOUT;
	conf->cat_timeout = DTH_CAT_TIMEOUT;
	conf->bat_timeout = DTH_BAT_TIMEOUT;
	conf->nit_timeout = DTH_NIT_TIMEOUT;
	conf->sdt_timeout = DTH_SDT_TIMEOUT;	
	conf->sdt_oth_timeout = DTH_SDT_OTH_TIMEOUT;
	conf->network_id = 0;
	conf->lock_enable = D_FALSE;						
	conf->table_mask = 0;
	
	if(type == D_SCAN_TYPE_ABS)
	{
		conf->bouq_id = ca_bouq_id;		
		conf->table_mask |= TABLE_MASK_PAT | TABLE_MASK_PMT | TABLE_MASK_CAT | TABLE_MASK_SDT | TABLE_MASK_NIT;		
		conf->table_mask |= TABLE_MASK_BAT;
	}
	else
	{
		conf->table_mask |= TABLE_MASK_PAT | TABLE_MASK_PMT | TABLE_MASK_CAT | TABLE_MASK_SDT | TABLE_MASK_NIT;
	}
	
	return D_OK;
}





/*直播星手动动搜索操作*/
D_ManualScanOp DTH_ManualScan_Op = 
{
	dth_manual_scan_init,
	dth_manual_scan_store,
	dth_manual_scan_destroy,
	dth_manual_scan_set_tpsiscan_config,
	dth_check_ca_sys_id,
	dth_check_bouq_id,
	dth_get_tp_info,	
	dth_get_private_descrs_info_in_sdt,
	dth_get_srvinfo_in_bat,
	dth_get_srvinfo_in_nit,
	dth_get_srvinfo_in_others,
	dth_check_srvice
};


