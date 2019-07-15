/** @file
* @brief DVBC 搜索时的的一些注册函数
* @author 覃宜
* @date 2013-4-4 覃宜: 建立文件
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dSI.h"
#include "dDescr.h"
#include "dSIParse.h"
#include "dDBase.h"
#include "dMem.h"
#include "dSys.h"
#include "dDebug.h"
#include "dScan.h"
#include "pStbScan.h"
#include "pMem.h"
#include "pConfig.h"
#include "pStb.h"
#include "pCustomConfig.h"
#include "pDBaseDefault.h"
#include "pSIParse.h"
#include "dConfigFile.h"

#define MAX_SEARCH_FREQ_C   874
#define MIN_SEARCH_FERQ_C   47

#define DVBC_PAT_TIMEOUT            2000
#define DVBC_CAT_TIMEOUT            3000
#define DVBC_SDT_TIMEOUT            10000
#define DVBC_PMT_TIMEOUT            2000
#define DVBC_SDT_OTH_TIMEOUT        10000
#define DVBC_NIT_TIMEOUT            10000
#define DVBC_BAT_TIMEOUT            10000


/** @brief DVBC频率表(单位KHz)*/
#if 0
const static D_U32
as_dvbc_freq_list[] =
{
    52500,  60250,  68500,  80000,
    88000, 115000, 123000, 131000,
    139000, 147000, 155000, 163000,
    171000, 179000, 187000, 195000,
    203000, 211000, 219000, 227000,
    235000, 243000, 251000, 259000,
    267000, 275000, 283000, 291000,
    299000, 307000, 315000, 323000,
    331000, 339000, 347000, 355000,
    363000, 371000, 379000, 387000,
    395000, 403000, 411000, 419000,
    427000, 435000, 443000, 451000,
    459000, 467000, 474000, 482000,
    490000, 498000, 506000, 514000,
    522000, 530000, 538000, 546000,
    554000, 562000, 570000, 578000,
    586000, 594000, 602000, 610000,
    618000, 626000, 634000, 642000,
    650000, 658000, 666000, 674000,
    682000, 690000, 698000, 706000,
    714000, 722000, 730000, 738000,
    746000, 754000, 762000, 770000,
    778000, 786000, 794000, 802000,
    810000, 818000, 826000, 834000,
    842000, 850000, 858000, 866000,
    874000
};
#endif

static D_WaveBand wave_band[] =
{
    {80, 88, 8},
    {115, 459, 8},
    {474, 874, 8},
};





static D_ASGroupOp DVBC_AutoScanGroup_Op;

/*bit0表示是否有节目没有lcn， bit1表示是否有节目有lcn*/
static D_U32    AllTVChanLcnStatus = 0;
static D_U32    AllRadioChanLcnStatus = 0;

#define SCAN_MEM_ALLOC(_s) d_mem_alloc(0,_s)
#define SCAN_MEM_FREE(_p) if(_p){d_mem_free(_p);_p = NULL;}


/*处理并保存排序后的节目*/
static D_Result
save_type_service(D_ScanSrvInfoNode *srvlist, D_ID *db_ts_id, D_U32 ts_cnt, D_ID *db_bouq_id, D_U32 bouq_cnt)
{
    D_ScanSrvInfoNode *srvnode;
    D_DBSrvInfo srvinfo;
    D_DBID dbid;
    D_Char strtype[3][16] = {"TV", "Radio", "Other"};
    D_U32   typeid;

    if(!srvlist)
        return D_ERR;

    D_SI_FOR_EACH_BEGIN(D_ScanSrvInfoNode, srvlist, srvnode)
    if(!srvnode->valid || !(srvnode->srvinfo.valid))
    {
        continue;
    }
    D_DB_SRV_INFO_INIT(&srvinfo);
    D_SCANSRVINFO_TO_DBSRVINFO(&srvinfo, &(srvnode->srvinfo));

    typeid = (srvinfo.srv_type == (D_U8)D_DB_SRV_TV) ? 0 : 2;
    typeid = (srvinfo.srv_type == (D_U8)D_DB_SRV_RADIO) ? 1 : typeid;

    if(srvnode->ts_no < ts_cnt)
    {
        srvinfo.db_ts_id = db_ts_id[srvnode->ts_no];
    }

    if(srvnode->srvinfo.ca_mask)
    {
        srvinfo.ca_flag = D_TRUE;
    }

    if(!g_custom_config.sys_setup.vol_compensate)
    {
        if(g_custom_config.scan.volume > D_STB_VOLUME_MAX)
        {
            g_custom_config.scan.volume = 0;
        }
        srvinfo.volume = g_custom_config.scan.volume;
    }

    if(g_custom_config.scan.track <= 3 )
    {
        srvinfo.aud_track = g_custom_config.scan.track;
    }

    if(srvinfo.name[0] == '\0')
    {
        if(srvinfo.srv_type == (D_U8)D_DB_SRV_TV)
        {
            sprintf(srvinfo.name, "ChannelDTV %d", srvinfo.srv_id);
        }
        else if(srvinfo.srv_type == (D_U8)D_DB_SRV_RADIO)
        {
            sprintf(srvinfo.name, "ChannelRadio %d", srvinfo.srv_id);
        }
        else
        {
            sprintf(srvinfo.name, "no name %d", srvinfo.srv_id);
        }
    }

    if(srvinfo.db_ts_id == -1)
    {
        D_ERROR ("[Scan] %s srvinfo.db_ts_id == -1 !!!\n", strtype[typeid]);
    }
    else
    {
        if (g_custom_config.scan.use_lcn == D_FALSE || srvinfo.chan_num == -1)
        {
            srvinfo.chan_num = d_dbase_get_free_chan_num((D_DBSrvType)srvinfo.srv_type);
        }

        dbid = p_dbase_insert_srv (&srvinfo);
        if (-1 == dbid)
        {
            D_ERROR ("[Scan] Cannot add new %s service !!!\n", strtype[typeid]);
        }
        else
        {
            D_DUMP("[Scan] Add %-5s dbtsid: %03d dbsrvid:%03d -> num:%03d srvid:%04x vid:%04x aud1:%04x aud2:%04x pcr:%04x vtype:%-2x a1type:%-2x a2type:%-2x ca_flag:%x bat_mask:%08x%08x lcn:%04x  %s\n", \
                   strtype[typeid], \
                   srvinfo.db_ts_id, \
                   dbid, \
                   srvinfo.chan_num, \
                   srvinfo.srv_id, \
                   srvinfo.vid_pid, \
                   srvinfo.aud1_pid, \
                   srvinfo.aud2_pid, \
                   srvinfo.pcr_pid, \
                   (D_S32)(srvinfo.vid_codec), \
                   (D_S32)(srvinfo.aud1_codec), \
                   (D_S32)(srvinfo.aud2_codec), \
                   srvinfo.ca_flag, \
                   (D_U32)(srvinfo.db_bouq_mask >> 32), (D_U32)(srvinfo.db_bouq_mask & 0xffffffff), \
                   srvinfo.chan_lcn, \
                   srvinfo.name);
        }
    }
    D_SI_FOR_EACH_END(D_ScanSrvInfoNode, srvlist, srvnode);

    return D_OK;
}


/*私有初始化, 对各组进行分配并初始化。主要设定搜索策略与频率列表*/
static D_Result dvbc_auto_scan_init (D_ASGroup **group, D_U32*group_cnt, D_ScanTaskConfig *as_config, D_HMMan hmm)
{
    D_ASGroup*scan_group = NULL;
    D_U32   group_id = 0;
    D_U32  num, i;
    D_FEndFreq freq;
    D_ScanFendParamNode *fendnode;
    D_FEndParam *fendparam;

    AllTVChanLcnStatus = 0;
    AllRadioChanLcnStatus = 0;
    as_config->group_end_save = D_FALSE;

    /*搜索配置*/
    D_SCAN_GROUP_ALLOC(hmm, scan_group);
    if(!scan_group)
    {
        D_ERROR ("[AutoScan] Cannot allocate group\n");
        return D_ERR;
    }

    group[group_id++] = scan_group;

    //scan_group->type = D_SCAN_TYPE_DVBC;
    scan_group->db_sat_id = -1;
    scan_group->fend_type = D_FEND_DVBC;
    scan_group->hfman = d_fman_get_handle_by_type(D_FEND_DVBC, 0);
    scan_group->findSrvInfoInMain = D_FALSE;
    scan_group->sdt_srv_type_en = as_config->sdt_srv_type_en;
    scan_group->groupOp = &DVBC_AutoScanGroup_Op;

    if(as_config->scan_type == STB_SCAN_TYPE_AUTO)
    {
        D_U8 *payload;
        D_U16 len, temp;

        scan_group->scan_mode = D_AUTO_SCAN_MODE_NIT;
#ifdef D_CA_SUPPORT_DSCA
        scan_group->findSrvInfoInMain = D_TRUE;
#endif
        /*主频点*/
        D_SI_ALLOC(hmm, fendnode);
        if(!fendnode)
        {
            return D_ERR;
        }

        fendnode->fendparam.dvbc = as_config->fend_param.dvbc;
        //fendnode->fendparam.dvbc.baud = 6875;
        //fendnode->fendparam.dvbc.mod = D_FEND_QAM64;
        D_SI_LIST_ADD(scan_group->scanFendParamList, fendnode);
        scan_group->scanFendParamList_cnt++;
        /* 预置频点搜索列表 */
        if(g_custom_config.scan.multi_maintp)
        {
            payload = d_conf_file_search_tag(CUSTOM_CONFIG_SEARCH_LIST, &len);
            if(payload && (len >= 4))
            {
                for(i = 0; i < (len / 4); i++)
                {
                    temp = (payload[0]);
                    temp = (temp << 5);
                    temp |= (payload[1] >> 3);
                    if(temp > 0)
                    {
                        D_SI_ALLOC(hmm, fendnode);
                        if(!fendnode)
                        {
                            return D_ERR;
                        }
                        fendnode->fendparam.dvbc.freq = temp;
                        fendnode->fendparam.dvbc.mod = (payload[1] & 0x07);
                        temp = (payload[2]);
                        temp = (temp << 8);
                        temp |= (payload[3]);
                        fendnode->fendparam.dvbc.baud = temp;

                        D_SI_LIST_ADD(scan_group->scanFendParamList, fendnode);
                        scan_group->scanFendParamList_cnt++;
                    }
                    payload += 4;
                }
            }
        }
    }
    else if(as_config->scan_type == STB_SCAN_TYPE_FULL)
    {
        if(as_config->bandwitch == 0 || (as_config->startfreq > as_config->endfreq))
        {
            return D_ERR;
        }

        scan_group->scan_mode = D_AUTO_SCAN_MODE_TP;
        scan_group->nit_strategy = D_NIT_STRA_NONE;

        if(as_config->Reserved)
        {
            /*其它频点列表*/
            num = sizeof(wave_band) / sizeof(wave_band[0]);
            for(i = 0; i < num; i++)
            {
                if(wave_band[i].start_freq <= as_config->endfreq  && wave_band[i].end_freq >= as_config->startfreq)
                {
                    freq = wave_band[i].start_freq;
                    while(freq <= wave_band[i].end_freq)
                    {
                        if(freq >= as_config->startfreq && freq <= as_config->endfreq)
                        {
                            D_SI_ALLOC(hmm, fendnode);
                            if(!fendnode)
                            {
                                return D_ERR;
                            }

                            fendnode->fendparam.dvbc.freq = freq;
                            fendnode->fendparam.dvbc.baud = 6875;
                            fendnode->fendparam.dvbc.mod = D_FEND_QAM64;

                            D_SI_LIST_ADD(scan_group->scanFendParamList, fendnode);
                            scan_group->scanFendParamList_cnt++;
                        }

                        freq += wave_band[i].band;
                    }
                }
            }
        }
        else
        {
            scan_group->freq_start = as_config->startfreq;
            scan_group->freq_end = as_config->endfreq;
            scan_group->freq_bw = as_config->bandwitch;
            scan_group->freq_step = as_config->bandwitch;
            scan_group->scanFendParamList_cnt = ((as_config->endfreq - as_config->startfreq) / as_config->bandwitch) + 1;

            fendparam = (D_FEndParam *)d_mman_alloc(hmm, sizeof (D_FEndParam));
            if(!fendparam)
            {
                return D_ERR;
            }

            fendparam->dvbc.freq = scan_group->freq_start;
            fendparam->dvbc.baud = 6875;
            fendparam->dvbc.mod = D_FEND_QAM64;
            scan_group->base_fparam = fendparam;
        }
    }
    else if(as_config->scan_type == STB_SCAN_TYPE_LIST)
    {
        D_U8 *payload;
        D_U16 len, temp;

        scan_group->scan_mode = D_AUTO_SCAN_MODE_TP;
        scan_group->nit_strategy = D_NIT_STRA_NONE;

        /* 预置频点搜索列表 */
        payload = d_conf_file_search_tag(CUSTOM_CONFIG_SEARCH_LIST, &len);
        if(payload && (len >= 4))
        {
            for(i = 0; i < (len / 4); i++)
            {
                temp = (payload[0]);
                temp = (temp << 5);
                temp |= (payload[1] >> 3);
                if(temp > 0)
                {
                    D_SI_ALLOC(hmm, fendnode);
                    if(!fendnode)
                    {
                        return D_ERR;
                    }
                    fendnode->fendparam.dvbc.freq = temp;
                    fendnode->fendparam.dvbc.mod = (payload[1] & 0x07);
                    temp = (payload[2]);
                    temp = (temp << 8);
                    temp |= (payload[3]);
                    fendnode->fendparam.dvbc.baud = temp;

                    D_SI_LIST_ADD(scan_group->scanFendParamList, fendnode);
                    scan_group->scanFendParamList_cnt++;
                }
                payload += 4;

            }
        }
        else
        {
            D_SI_ALLOC(hmm, fendnode);
            if(!fendnode)
            {
                return D_ERR;
            }
            fendnode->fendparam.dvbc.freq = 0;
            fendnode->fendparam.dvbc.baud = 6875;
            fendnode->fendparam.dvbc.mod = D_FEND_QAM64;

            D_SI_LIST_ADD(scan_group->scanFendParamList, fendnode);
            scan_group->scanFendParamList_cnt++;
        }
    }
    else
    {
        D_ERROR("%s:   Error : scan_type %d\n", __FUNCTION__, as_config->scan_type);
    }

    /*记录组数*/
    *group_cnt = group_id;

    return D_OK;
}


/** @brief将搜索结果保存至数据库。*/
static D_Result dvbc_auto_scan_store(D_ASGroup **group, D_U32 group_cnt, D_ScanTaskConfig *as_config)
{
    D_U16 groupid, idx;
    D_DBID dbid;
    D_ASGroup   *scan_group;
    D_ScanTsInfoNode *scants;
    D_DBTSID *db_ts_id;
    D_ID db_bouq_id[D_SCAN_MAX_BOUQ_CNT] = {0};
    D_DBTSInfo ts_info;
    D_SIParam si_param;

    if(!group)
    {
        return D_ERR;
    }

    /*对每组的搜索结果进行保存*/
    groupid = 0;
    scan_group = group[groupid];

    if(g_custom_config.scan.adelete == 1)
    {
        //===
    }
    else
    {
        /*搜索不到节目时，不删除原有节目*/
        if(scan_group->scanResult.scan_tsinfo_cnt == 0 || (scan_group->scanResult.tv_cnt + scan_group->scanResult.radio_cnt) <= 0)
        {
            return D_OK;
        }
    }

    p_conf_get_si_param(&si_param);

    d_dbase_set_rset_en(0);

	d_dbase_clear_evt ();
	d_dbase_clear_bouq();

	/*可能也预定电视广播之外的节目，如atv，因此这里不能删除所有
	在clear srv，即删除节目时，会删除此节目的预定记录。qiny*/
	//d_dbase_clear_srv(); 
	//clear srv
	d_dbase_clear_srv_by_type(D_DB_SRV_ACTION_TV | D_DB_SRV_ACTION_RADIO);
	d_dbase_delete_ts_by_type(D_FEND_DVBC);

    db_ts_id = (D_DBTSID*)SCAN_MEM_ALLOC(sizeof(D_DBTSID) * scan_group->scanResult.scan_tsinfo_cnt);
    if(scan_group->scanResult.scan_tsinfo_cnt && db_ts_id)
    {
        memset(db_ts_id, 0xff, sizeof(D_DBTSID) * scan_group->scanResult.scan_tsinfo_cnt);

        /*存储频点信息*/
        D_SI_FOR_EACH_BEGIN(D_ScanTsInfoNode, scan_group->scanResult.scan_tsinfo_list, scants)
        if(scants->valid && (scants->ts_no < scan_group->scanResult.scan_tsinfo_cnt) && ((scants->ts_info.tv_cnt + scants->ts_info.radio_cnt) > 0))
        {
            D_DB_TS_INFO_INIT(&ts_info);
            D_SCANTSINFO_TO_DBSRVINFO(&ts_info, &(scants->ts_info));
            ts_info.db_net_id = as_config->db_net_id;
            ts_info.tuner_type = scan_group->fend_type;
            ts_info.db_sat_id = (D_U8) - 1;

            /*保存频点信息*/
            dbid = d_dbase_get_ts_by_param (as_config->db_net_id, scan_group->fend_type, &ts_info.param);
            if (-1 != dbid)
            {
                /*更新频点信息*/
                p_dbase_updata_ts_info(dbid, &ts_info);
            }
            else
            {
                /*添加频点，并更新频点记录集信息*/
                dbid = p_dbase_insert_ts (&ts_info);
            }

            /*每个频点在数据库里的id*/
            db_ts_id[scants->ts_no] = dbid;

            D_DUMP("[scan] add ts -> dbtsid: %03d tsid: 0x%04x orgnetid: 0x%04x freq: %d\n", dbid, ts_info.ts_id, ts_info.org_net_id, ts_info.param.freq);
#ifdef D_CA_SUPPORT_XGCA
            /*新光查找主频点*/
            if(0x0001 == ts_info.ts_id)
            {
                si_param.main.freq = ts_info.param.freq;
                p_conf_set_si_param(&si_param);
            }
#endif
        }
        D_SI_FOR_EACH_END(D_ScanTsInfoNode, scan_group->scanResult.scan_tsinfo_list, scants);

        /*保存业务群信息*/
        for(idx = 0; idx < scan_group->scanResult.bouq_cnt; idx++)
        {
            dbid = d_dbase_insert_bouq (scan_group->scanResult.bouq_info[idx]);
            db_bouq_id[idx] = dbid;
        }

        /*对所有节目进行排序*/
        p_scan_sort_srv_set_dbtsid_list(db_ts_id, scan_group->scanResult.scan_tsinfo_cnt);

#ifdef D_CA_SUPPORT_DSCA
        if(AllTVChanLcnStatus & 0x01)
        {
            p_scan_sort_srv((D_ScanSrvInfoNode *)scan_group->scanResult.srvList_tv, D_SCAN_SORT_MODE_SRVID);
        }
        if(AllTVChanLcnStatus & 0x02)
        {
            p_scan_sort_srv((D_ScanSrvInfoNode *)scan_group->scanResult.srvList_tv, D_SCAN_SORT_MODE_LCN);
        }

        if(AllRadioChanLcnStatus & 0x01)
        {
            p_scan_sort_srv((D_ScanSrvInfoNode *)scan_group->scanResult.srvList_radio, D_SCAN_SORT_MODE_SRVID);
        }
        if(AllRadioChanLcnStatus & 0x02)
        {
            p_scan_sort_srv((D_ScanSrvInfoNode *)scan_group->scanResult.srvList_radio, D_SCAN_SORT_MODE_LCN);
        }
#else
        if(g_custom_config.scan.asort)
        {
            D_ScanSortMode mode = D_SCAN_SORT_MODE_NOT;

            if(g_custom_config.scan.asort == 1)mode = D_SCAN_SORT_MODE_TS;
            else if(g_custom_config.scan.asort == 2)mode = D_SCAN_SORT_MODE_SRVID;
            else if(g_custom_config.scan.asort == 3)mode = D_SCAN_SORT_MODE_LCN;
            else if(g_custom_config.scan.asort == 4)mode = D_SCAN_SORT_MODE_FREECA;
            else if(g_custom_config.scan.asort == 5)mode = D_SCAN_SORT_MODE_NAME;
            else if(g_custom_config.scan.asort == 6)mode = D_SCAN_SORT_MODE_TSID;
            else if(g_custom_config.scan.asort == 7)mode = D_SCAN_SORT_MODE_TSID_SRVID;
            else if(g_custom_config.scan.asort == 8)mode = D_SCAN_SORT_MODE_CAFREE_TS_SRVID;

            if(mode != D_SCAN_SORT_MODE_NOT)
            {
                p_scan_sort_srv((D_ScanSrvInfoNode *)scan_group->scanResult.srvList_tv, mode);
                p_scan_sort_srv((D_ScanSrvInfoNode *)scan_group->scanResult.srvList_radio, mode);
            }
        }
#endif
        p_scan_sort_srv_set_dbtsid_list(NULL, 0);

        /*保存所有节目*/
        save_type_service((D_ScanSrvInfoNode *)scan_group->scanResult.srvList_tv, db_ts_id, scan_group->scanResult.scan_tsinfo_cnt, db_bouq_id, scan_group->scanResult.bouq_cnt);
        save_type_service((D_ScanSrvInfoNode *)scan_group->scanResult.srvList_radio, db_ts_id, scan_group->scanResult.scan_tsinfo_cnt, db_bouq_id, scan_group->scanResult.bouq_cnt);
    }

    SCAN_MEM_FREE(db_ts_id);

    if(scan_group->scanResult.found_nit)
    {
        if(as_config->scan_type == STB_SCAN_TYPE_AUTO)
        {
#ifndef D_CA_SUPPORT_XGCA
            if(g_custom_config.scan.multi_maintp && scan_group->scanResult.main_fparam.freq)
            {
                si_param.main.freq = scan_group->scanResult.main_fparam.dvbc.freq;
                si_param.main.baud = scan_group->scanResult.main_fparam.dvbc.baud;
                si_param.main.mod = scan_group->scanResult.main_fparam.dvbc.mod;
            }
#endif
        }
        si_param.nit_version = scan_group->scanResult.nit_version;
        p_conf_set_si_param(&si_param);
    }

    d_dbase_flush();

    return D_OK;
}

static D_Result dvbc_auto_scan_destroy (D_ASGroup **group, D_U32 group_cnt, D_ScanTaskConfig *as_config)
{
    D_U16 groupid;
    D_ASGroup   *scan_group;

    if(!group)
    {
        return D_ERR;
    }

    for(groupid = 0; groupid < group_cnt; groupid++)
    {
        scan_group = group[groupid];
        //其它处理
    }

    return D_OK;
}


D_AutoScanOp DVBC_AutoScan_Op =
{
    dvbc_auto_scan_init,
    dvbc_auto_scan_store,
    dvbc_auto_scan_destroy
};





/*私有初始化*/
static D_Result dvbc_group_start (D_ASGroup *scan_group, D_ScanTaskConfig *as_config, D_HMMan hmm)
{
    return D_OK;
}

/*私有反初始化*/
static D_Result dvbc_group_end(D_ASGroup *scan_group, D_ScanTaskConfig *as_config)
{
    return D_OK;
}

/*检查ca_sys_id是否符合定制要求*/
static D_Bool dvbc_check_ca_sys_id (D_U32 type, D_U16 ca_sys_id)
{
    D_Bool ret = D_TRUE;
#if 0
    //if(type == )
    {
        ret = d_ca_sys_check (ca_sys_id);
    }
#endif
    return ret;
}

/*检查业务群id 是否符合定制要求*/
static D_Bool dvbc_check_bouq_id (D_U32 type, D_U16 bouq_id)
{
    return D_TRUE;
}


/*检查服务是否符合定制要求*/
static D_Bool dvbc_check_srvice (D_U32 type, D_ScanSrvInfo *srvinfo)
{
    D_Bool ret = D_TRUE;

    if(!srvinfo->valid)
    {
        ret = D_FALSE;
    }

    if(!(g_custom_config.scan.caflag & CA_FLAG_IN_PMT))
    {
        srvinfo->ca_mask &= ~(SRV_CA_MASK_PMT | SRV_CA_MASK_PMT_ES);
    }

    if(!(g_custom_config.scan.caflag & CA_FLAG_IN_SDT))
    {
        srvinfo->ca_mask &= ~SRV_CA_MASK_SDT;
    }

    if(srvinfo->ca_mask)
    {
        srvinfo->ca_mask = 1;
        if(p_conf_get_save_type() == 1)
        {
            ret = D_FALSE;
        }
    }
    else/*非加扰节目*/
    {
        srvinfo->ca_mask = 0;
        if(p_conf_get_save_type() == 2)
        {
            ret = D_FALSE;
        }
    }
    if(srvinfo->srv_type == D_DB_SRV_TV)
    {
        if(srvinfo->chan_lcn != (D_U16)(-1))
        {
            AllTVChanLcnStatus |= 0x02;
        }
        else
        {
            AllTVChanLcnStatus |= 0x01;
        }
    }

    if(srvinfo->srv_type == D_DB_SRV_RADIO)
    {
        if(srvinfo->chan_lcn != (D_U16)(-1))
        {
            AllRadioChanLcnStatus |= 0x02;
        }
        else
        {
            AllRadioChanLcnStatus |= 0x01;
        }
    }
    return ret;
}

/*sdt表里提取服务信息*/
static D_Result dvbc_get_private_descrs_info_in_sdt(D_U32 type, D_Descr *descr, D_ScanSrvInfo *srv_info)
{
    switch(descr->tag)
    {
        case DESCR_ML_SERVICE_NAME:
        {
            D_MultilingualServiceNameDescr *dmsd;
            D_MultilingualSrvText *dmst;

            dmsd = (D_MultilingualServiceNameDescr*)descr;
            D_SI_FOR_EACH_BEGIN(D_MultilingualSrvText, dmsd->multi_text, dmst)
            if(0 == memcmp(dmst->country, "chi", 3) || 0 == memcmp(dmst->country, "zho", 3))
            {
                if(dmst->prov_name)
                {
                    strncpy (srv_info->prov_name, dmst->prov_name, sizeof (srv_info->prov_name) - 1);
                }

                if(dmst->srv_name)
                {
                    strncpy (srv_info->name, dmst->srv_name, sizeof (srv_info->name) - 1);
                }
            }
            D_SI_FOR_EACH_END(D_MultilingualSrvText, dmsd->multi_text, dmst)
        }
        default:
            break;
    }

    return D_OK;
}

/*bat表里提取服务信息*/
static D_Result dvbc_get_srvinfo_in_bat(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srv_info, D_ScanResultValue *result)
{
    return D_OK;
}


/*nit表里提取服务信息*/
static D_Result dvbc_get_srvinfo_in_nit(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srv_info, D_ScanResultValue *result)
{
#ifdef D_CA_SUPPORT_DSCA
    D_NitTS *ts;
    D_Descr *descr;
    D_Nit      *nit;
    D_Bool  get_lcn_flag = D_FALSE;

    if(!srv_info)
    {
        return D_ERR;
    }

    if(scants && (scants->scantp) && (scants->scantp->nits))
    {
        D_SI_FOR_EACH_BEGIN (D_Nit, scants->scantp->nits, nit)
        D_SI_FOR_EACH_BEGIN (D_NitTS, nit->tses, ts)
        D_SI_FOR_EACH_BEGIN (D_Descr, ts->descrs, descr)
        switch (descr->tag)
        {
            case P_DESCR_ABV_LCN_TAG:
            {
                D_LCNDescr *lcn_decr = (D_LCNDescr *)descr;

                if(srv_info->srv_id == lcn_decr->srv_id)
                {
                    get_lcn_flag = D_TRUE;
                    srv_info->chan_lcn = lcn_decr->lcn;
                    //D_DUMP("[Scan] srv_id = %d, logic_number = %d\n",srv_info->srvinfo.srv_id,srv_info->srvinfo.chan_lcn);
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

    if(get_lcn_flag == D_FALSE && result && (result->main_tp) && (result->main_tp->nits))
    {
        D_SI_FOR_EACH_BEGIN (D_Nit, result->main_tp->nits, nit)
        D_SI_FOR_EACH_BEGIN (D_NitTS, nit->tses, ts)
        D_SI_FOR_EACH_BEGIN (D_Descr, ts->descrs, descr)
        switch (descr->tag)
        {
            case P_DESCR_ABV_LCN_TAG:
            {
                D_LCNDescr *lcn_decr = (D_LCNDescr *)descr;

                if(srv_info->srv_id == lcn_decr->srv_id)
                {
                    srv_info->chan_lcn = lcn_decr->lcn;
                    //D_DUMP("[Scan] srv_id = %d, logic_number = %d\n",srv_info->srvinfo.srv_id,srv_info->srvinfo.chan_lcn);
                }
            }
            break;
            default:
                break;
        }
        D_SI_FOR_EACH_END (D_Descr, ts->descrs, descr)
        D_SI_FOR_EACH_END (D_NitTS, nit->tses, ts)
        D_SI_FOR_EACH_END (D_Nit, result->main_tp->nits, nit)
    }
#endif
    return D_OK;
}

/*其它私有表里提取服务信息*/
static D_Result dvbc_get_srvinfo_in_others(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srv_info, D_ScanResultValue *result)
{
    return D_OK;
}


/*单频点搜索配置*/
static D_Result dvbc_set_tpsiscan_config(D_ASGroup *scan_group, D_TpSiScanTaskConfig *conf)
{
    conf->pat_timeout = DVBC_PAT_TIMEOUT;
    conf->pmt_timeout = DVBC_PMT_TIMEOUT;
    conf->cat_timeout = DVBC_CAT_TIMEOUT;
    conf->bat_timeout = DVBC_BAT_TIMEOUT;
    conf->nit_timeout = DVBC_NIT_TIMEOUT;
    conf->sdt_timeout = DVBC_SDT_TIMEOUT;
    conf->sdt_oth_timeout = DVBC_SDT_OTH_TIMEOUT;

    conf->lock_enable = D_FALSE;
    conf->table_mask = 0;

    if(scan_group->scan_mode == D_AUTO_SCAN_MODE_NIT && scan_group->scanResult.found_nit == D_FALSE)
    {
        conf->table_mask |= TABLE_MASK_NIT | TABLE_MASK_PAT | TABLE_MASK_PMT  | TABLE_MASK_SDT;
    }
    else
    {
        conf->table_mask |= TABLE_MASK_PAT | TABLE_MASK_PMT  | TABLE_MASK_SDT/* | TABLE_MASK_NIT*/;
    }
    return D_OK;
}

/*nit表里提取频率列表信息*/
D_Result dvbc_get_freqlist_in_nit(D_U32 type, D_ScanTsInfoNode *scants, D_FEndParam*fparam, D_U32 *fcnt)
{
    D_NitTS *ts;
    D_Descr *descr;
    D_Nit      *nit;
    D_FEndParam param;

    if(!scants || !(scants->scantp) || !(scants->scantp->nits) || !fparam || !fcnt)
    {
        return D_ERR;
    }

    //if(scan_group->group_type == D_GROUP_TYPE_DVBC)
    {
        D_SI_FOR_EACH_BEGIN (D_Nit, scants->scantp->nits, nit)
        D_SI_FOR_EACH_BEGIN (D_NitTS, nit->tses, ts)
        D_SI_FOR_EACH_BEGIN (D_Descr, ts->descrs, descr)
        switch (descr->tag)
        {
            case DESCR_CABLE_DEL_SYS:/*有线*/
                if(scants->scantp->type == D_FEND_DVBC)
                {
                    D_CableDeliverySystemDescr *cds = (D_CableDeliverySystemDescr*) descr;

                    memset(&param, 0x00, sizeof(D_FEndParam));
                    param.dvbc.freq = cds->freq / 10000;
                    param.dvbc.baud = cds->baud / 10;
                    param.dvbc.mod = cds->mod;
                    D_DUMP("[AutoScan] nit CABLE_DEL_SYS find freq:%d baud:%d mod:%d\n", param.freq, param.dvbc.baud, param.dvbc.mod);
                    if ((param.freq >= MIN_SEARCH_FERQ_C) && (param.freq <= MAX_SEARCH_FREQ_C) )
                    {
                        if((*fcnt) < D_SCAN_GROUP_MAX_TP_CNT)
                            fparam[(*fcnt)++] = param;
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
D_Result dvbc_get_tp_info(D_U32 type, D_ScanTsInfoNode *scants, D_ScanResultValue *scanResult)
{
    if(scants && (scants->scantp) && (scants->scantp->nits))
    {
        scants->ts_info.version = ((D_Nit*)(scants->scantp->nits))->version;
    }

    return D_OK;
}

#if 0
static D_Result dvbc_group_end_private_op(D_ASGroup *scan_group, D_HMMan hmm)
{
    return D_OK;
}
#endif


/*DVBC 自动搜索操作*/
static D_ASGroupOp DVBC_AutoScanGroup_Op =
{
    dvbc_group_start,
    dvbc_group_end,
    dvbc_set_tpsiscan_config,
    dvbc_check_ca_sys_id,
    dvbc_check_bouq_id,
    NULL,//dvbc_group_end_private_op,
    dvbc_get_freqlist_in_nit,
    NULL,
    dvbc_get_private_descrs_info_in_sdt,
    dvbc_get_srvinfo_in_bat,
    dvbc_get_srvinfo_in_nit,
    dvbc_get_srvinfo_in_others,
    dvbc_check_srvice
};






/*私有初始化, 对各组进行分配并初始化。主要设定搜索策略与频率列表，此时搜索任务还没启动*/
static D_Result dvbc_manual_scan_init(D_U32 type, D_ScanTaskConfig *ms_config)
{
    AllTVChanLcnStatus = 0;
    AllRadioChanLcnStatus = 0;
    return D_OK;
}

/*开始搜索用户回调，此时任务已经启动，在任务回调时执行*/
static D_Result dvbc_manual_scan_start(D_U32 type, D_ScanTaskConfig *ms_config)
{
    return D_OK;
}

static D_Result dvbc_manual_scan_store(D_U32 type, D_ScanTaskConfig *ms_config, D_ScanResultValue*ms_result)
{
    D_DBID dbid, idx;
    D_ID db_ts_id;
    D_ScanTsInfoNode *scants;
    D_ID db_bouq_id[D_SCAN_MAX_BOUQ_CNT] = {0};
    D_DBTSInfo ts_info;
    D_ScanSortMode mode = D_SCAN_SORT_MODE_NOT;

    if((!ms_result) || (!(ms_result->scan_tsinfo_list)))
    {
        return D_ERR;
    }

    if(g_custom_config.scan.mdelete == 1)
    {
        //===
    }
    else
    {
        /*搜索不到节目时，不删除原有节目*/
        if((ms_result->tv_cnt + ms_result->radio_cnt) <= 0)
        {
            return D_OK;
        }
    }

    d_dbase_set_rset_en(0);

    scants = (D_ScanTsInfoNode*)ms_result->scan_tsinfo_list;
    D_DB_TS_INFO_INIT(&ts_info);
    D_SCANTSINFO_TO_DBSRVINFO(&ts_info, &(scants->ts_info));
    ts_info.db_net_id = ms_config->db_net_id;
    ts_info.tuner_type = ms_config->fend_type;
    ts_info.db_sat_id = (D_U8) - 1;

    /*保存频点信息*/
    db_ts_id = d_dbase_get_ts_by_param (ms_result->db_net_id, ms_result->fend_type, &scants->ts_info.param);
    if (-1 != db_ts_id)
    {
        /*删除当前频点下原有的节目，并更新频点信息*/
        d_dbase_delete_srvs_of_ts(db_ts_id);
        p_dbase_updata_ts_info(db_ts_id, &ts_info);
    }
    else
    {
        /*添加频点，并更新频点记录集信息*/
        db_ts_id = p_dbase_insert_ts (&ts_info);
        d_dbase_get_ts_total_num();
    }

    if(db_ts_id == -1)
    {
        D_ERROR ("[ManualScan] db_ts_id == -1 !!!\n");
        return D_ERR;
    }
#ifdef D_CA_SUPPORT_XGCA
    /*新光查找主频点*/
    if(0x0001 == ts_info.ts_id)
    {
        D_SIParam si_param;
        p_conf_get_si_param(&si_param);
        si_param.main.freq = ts_info.param.freq;
        p_conf_set_si_param(&si_param);
    }
#endif
    D_DUMP("[scan] add ts -> dbtsid: %03d tsid: 0x%04x orgnetid: 0x%04x freq: %d\n", db_ts_id, ts_info.ts_id, ts_info.org_net_id, ts_info.param.freq);

    /*保存业务群信息*/
    for(idx = 0; idx < ms_result->bouq_cnt; idx++)
    {
        dbid = d_dbase_insert_bouq (ms_result->bouq_info[idx]);
        db_bouq_id[idx] = dbid;
    }

    /*对所有节目进行排序*/
    p_scan_sort_srv_set_dbtsid_list(&db_ts_id, 1);
#ifdef D_CA_SUPPORT_DSCA
    if(AllTVChanLcnStatus & 0x01)
    {
        p_scan_sort_srv((D_ScanSrvInfoNode *)ms_result->srvList_tv, D_SCAN_SORT_MODE_SRVID);
    }
    if(AllTVChanLcnStatus & 0x02)
    {
        p_scan_sort_srv((D_ScanSrvInfoNode *)ms_result->srvList_tv, D_SCAN_SORT_MODE_LCN);
    }

    if(AllRadioChanLcnStatus & 0x01)
    {
        p_scan_sort_srv((D_ScanSrvInfoNode *)ms_result->srvList_radio, D_SCAN_SORT_MODE_SRVID);
    }
    if(AllRadioChanLcnStatus & 0x02)
    {
        p_scan_sort_srv((D_ScanSrvInfoNode *)ms_result->srvList_radio, D_SCAN_SORT_MODE_LCN);
    }
#else
    if(g_custom_config.scan.msort)
    {
        if(g_custom_config.scan.msort == 1)mode = D_SCAN_SORT_MODE_TS;
        else if(g_custom_config.scan.msort == 2)mode = D_SCAN_SORT_MODE_SRVID;
        else if(g_custom_config.scan.msort == 3)mode = D_SCAN_SORT_MODE_LCN;
        else if(g_custom_config.scan.msort == 4)mode = D_SCAN_SORT_MODE_FREECA;
        else if(g_custom_config.scan.msort == 5)mode = D_SCAN_SORT_MODE_NAME;
        else if(g_custom_config.scan.msort == 6)mode = D_SCAN_SORT_MODE_TSID;
        else if(g_custom_config.scan.msort == 7)mode = D_SCAN_SORT_MODE_TSID_SRVID;
        else if(g_custom_config.scan.msort == 8)mode = D_SCAN_SORT_MODE_CAFREE_TS_SRVID;

        if(mode != D_SCAN_SORT_MODE_NOT)
        {
            p_scan_sort_srv((D_ScanSrvInfoNode *)ms_result->srvList_tv, mode);
            p_scan_sort_srv((D_ScanSrvInfoNode *)ms_result->srvList_radio, mode);
        }
    }
#endif
    p_scan_sort_srv_set_dbtsid_list(NULL, 0);
    /*保存所有节目*/
    save_type_service((D_ScanSrvInfoNode *)ms_result->srvList_tv, &db_ts_id, 1, db_bouq_id, ms_result->bouq_cnt);
    save_type_service((D_ScanSrvInfoNode *)ms_result->srvList_radio, &db_ts_id, 1, db_bouq_id, ms_result->bouq_cnt);

#ifndef D_CA_SUPPORT_DSCA
    /*对所有节目排序*/
    p_scan_sort_all_srv(D_DB_SRV_TV, mode, D_FALSE);
    p_scan_sort_all_srv(D_DB_SRV_RADIO, mode, D_FALSE);
#endif
    d_dbase_flush();

    return D_OK;
}


static D_Result dvbc_manual_scan_destroy(D_U32 type, D_ScanTaskConfig *ms_config, D_ScanResultValue*ms_result)
{
    return D_OK;
}


/*单频点搜索配置*/
static D_Result dvbc_manual_scan_set_tpsiscan_config(D_U32 type, D_TpSiScanTaskConfig *conf)
{
    conf->pat_timeout = DVBC_PAT_TIMEOUT;
    conf->pmt_timeout = DVBC_PMT_TIMEOUT;
    conf->cat_timeout = DVBC_CAT_TIMEOUT;
    conf->bat_timeout = DVBC_BAT_TIMEOUT;
    conf->nit_timeout = DVBC_NIT_TIMEOUT;
    conf->sdt_timeout = DVBC_SDT_TIMEOUT;
    conf->sdt_oth_timeout = DVBC_SDT_OTH_TIMEOUT;
    conf->network_id = 0;
    conf->lock_enable = D_FALSE;
    conf->table_mask = 0;

    conf->table_mask |= TABLE_MASK_PAT | TABLE_MASK_PMT  | TABLE_MASK_SDT/* | TABLE_MASK_NIT*/;

    return D_OK;
}





/*直播星手动动搜索操作*/
D_ManualScanOp DVBC_ManualScan_Op =
{
    dvbc_manual_scan_init,
    dvbc_manual_scan_start,
    dvbc_manual_scan_store,
    dvbc_manual_scan_destroy,
    dvbc_manual_scan_set_tpsiscan_config,
    dvbc_check_ca_sys_id,
    dvbc_check_bouq_id,
    dvbc_get_tp_info,
    dvbc_get_private_descrs_info_in_sdt,
    dvbc_get_srvinfo_in_bat,
    dvbc_get_srvinfo_in_nit,
    dvbc_get_srvinfo_in_others,
    dvbc_check_srvice
};





