/** @file
* @brief DVBS 搜索时的的一些注册函数
* @author 覃宜
* @date 2013-4-4 覃宜: 建立文件
*/

#include "dSI.h"
#include "dDescr.h"
#include "dSIParse.h"
#include "dDBase.h"
#include "dMem.h"
#include "dSys.h"
#include "dSem.h"
#include "dDebug.h"
#include "dScan.h"
#include "pStbScan.h"
#include "pMem.h"
#include "pConfig.h"
#include "pStb.h"
#include "pCustomConfig.h"


#define MAX_SEARCH_FREQ_S_KU    12750
#define MIN_SEARCH_FERQ_S_KU    10700
#define MAX_SEARCH_FREQ_S_C 4200
#define MIN_SEARCH_FERQ_S_C 3600

#define LNB_SWITCH_FREQ_S_KU    11700        /*ku双本振时高低本振分界 */
#define FREQ_SWITCH_S_C_KU  9000          /*c波段ku波段判断分界 */

#define DVBS_PAT_TIMEOUT            2000
#define DVBS_CAT_TIMEOUT            3000
#define DVBS_SDT_TIMEOUT            6000
#define DVBS_PMT_TIMEOUT            3000
#define DVBS_SDT_OTH_TIMEOUT        10000
#define DVBS_NIT_TIMEOUT            10000
#define DVBS_BAT_TIMEOUT            10000

#define SATE_MAX_NUM (100)
#define SATE_TS_MAX_NUM (256)

static D_ASGroupOp DVBS_AutoScanGroup_Op;


/*盲扫分段示例。程序运行时会根据卫星与本振信息修改相应参数*/
static D_FBlindParam dvbs_blindparam_single[] =
{
    {SINGLE, 5150, 0, 950, 1200, D_FEND_HOR_POL, D_F22KOff, {D_DISEQC_TYPE_10, D_PORT_A, 0}},
    {SINGLE, 5150, 0, 950, 1200, D_FEND_VER_POL, D_F22KOff, {D_DISEQC_TYPE_10, D_PORT_A, 0}},
};

static D_FBlindParam dvbs_blindparam_ku_double[] =
{
    {KU_DOUBLE, 9750, 0, 950, 1080, D_FEND_HOR_POL, D_F22KOff, {D_DISEQC_TYPE_10, D_PORT_A, 0}},
    {KU_DOUBLE, 9750, 0, 950, 1080, D_FEND_VER_POL, D_F22KOff, {D_DISEQC_TYPE_10, D_PORT_A, 0}},
    {KU_DOUBLE, 10600, 0, 1150, 1000, D_FEND_HOR_POL, D_F22KOn, {D_DISEQC_TYPE_10, D_PORT_A, 0}},
    {KU_DOUBLE, 10600, 0, 1150, 1000, D_FEND_VER_POL, D_F22KOn, {D_DISEQC_TYPE_10, D_PORT_A, 0}},
};

static D_FBlindParam dvbs_blindparam_c_double[] =
{
    {C_DOUBLE, 5150, 0, 950, 600, D_FEND_HOR_POL, D_F22KOff, {D_DISEQC_TYPE_10, D_PORT_A, 0}},
    {C_DOUBLE, 5750, 0, 1550, 600, D_FEND_VER_POL, D_F22KOff, {D_DISEQC_TYPE_10, D_PORT_A, 0}},
};




static P_StbScanProgType ScanProgType = STB_SCAN_PROG_TYPE_TV_RADIO;
static D_FDiSEqCType curr_diseqc_type = D_DISEQC_TYPE_10;
static D_U32  ScanOnlyFreeFlag = 0;
static D_ID _db_sat_id[SATE_MAX_NUM];
static D_ID _db_ant_id[SATE_MAX_NUM];
static D_HSem hsem_scan = D_INVALID_HANDLE;

/*不保存非法转发器下的节目*/
/* 138上屏蔽12429 H 3330 频点节目（美国之音等）。*/
#define INVALID_TP_FREQ (12429)
#define INVALID_TP_BAUD (3330)
static D_Bool  curr_tp_invalid = D_FALSE;



#define SCAN_MEM_ALLOC(_s) d_mem_alloc(0,_s)
#define SCAN_MEM_FREE(_p) if(_p){d_mem_free(_p);_p = NULL;}

static D_Result
scan_set_diseqc(D_HFMan hfman, D_U8 param)D_FUNCPOSTFIT
{
#if 0
    D_FEndDiSEqC diseqc;
    D_GeoCoord localpos = {0};
    D_UserMsg usermsg = {0};

    if(curr_diseqc_type == D_DISEQC_TYPE_12)
    {
        diseqc.diseqc_type = D_DISEQC_TYPE_12;
        diseqc.motor_cmd.type = D_MOTOR_GOTO_NN;
        diseqc.motor_cmd.NN_cmd.nn_value = D_MIN(63, param);
    }
    else if(curr_diseqc_type == D_DISEQC_TYPE_USALS)
    {
        p_conf_get_local_position(&localpos);
        diseqc.diseqc_type = D_DISEQC_TYPE_USALS;
        diseqc.motor_cmd.type = D_MOTOR_GOTO_AZIMUTH;
        //经纬度信息
    }

    d_fman_set_diseqc_cmd(hfman, &diseqc);
    hsem_scan = d_sem_create(NULL);
    if(hsem_scan != D_INVALID_HANDLE)
    {
        usermsg.type = D_MSG_USER1;
        usermsg.handle = d_app_self();
        usermsg.param1 = (D_U32)hsem_scan;
        d_queue_send(d_gui_get_queue(), (D_U8*)&usermsg, sizeof (usermsg));
        d_sem_wait_timeout(hsem_scan, 20000);
        d_sem_destroy(hsem_scan);
        hsem_scan = D_INVALID_HANDLE;
    }
#endif
    return D_OK;
}

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

    if (g_custom_config.scan.use_lcn == D_FALSE || srvinfo.chan_num == -1)
    {
        srvinfo.chan_num = d_dbase_get_free_chan_num((D_DBSrvType)srvinfo.srv_type);
    }

    typeid = (srvinfo.srv_type == (D_U8)D_DB_SRV_TV) ? 0 : 2;
    typeid = (srvinfo.srv_type == (D_U8)D_DB_SRV_RADIO) ? 1 : typeid;

    if(srvinfo.db_ts_id == -1)
    {
        D_ERROR ("[Scan] %s srvinfo.db_ts_id == -1 !!!\n", strtype[typeid]);
    }
    else
    {
        /*检查是否已经存在此节目*/
        dbid = d_dbase_get_srv_by_id(srvinfo.db_ts_id, srvinfo.srv_id);
        if(-1 == dbid)
        {
            dbid = d_dbase_insert_srv (&srvinfo);
        }
        else
        {
            d_dbase_update_srv_name(dbid, srvinfo.name);
            d_dbase_update_srv_pmt_ex(dbid, srvinfo.vid_pid, srvinfo.vid_codec, srvinfo.aud1_pid, srvinfo.aud1_codec,
                                      srvinfo.aud2_pid, srvinfo.aud2_codec, srvinfo.pcr_pid, srvinfo.pmt_pid);
        }

        if (-1 == dbid)
        {
            D_ERROR ("[Scan] Cannot add new %s service !!!\n", strtype[typeid]);
        }
        else
        {
            D_DUMP("[Scan] Add %s dbtsid: %03d dbsrvid:%03d -> num:%03d srvid:%04x vid:%04x aud1:%04x aud2:%04x pcr:%04x vtype:%x a1type:%x a2type:%x ca_flag:%x bat_mask:%08x%08x lcn:%04x  %s\n", \
                   strtype[typeid], \
                   srvinfo.db_ts_id, \
                   dbid, \
                   srvinfo.chan_num, \
                   srvinfo.srv_id, \
                   srvinfo.vid_pid, \
                   srvinfo.aud1_pid, \
                   srvinfo.aud2_pid, \
                   srvinfo.pcr_pid,
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


/*根据天线与卫星信息拆分盲扫参数*/
static D_FBlindParam* dvbs_set_blind_param(D_ScanTaskConfig *as_config, D_HMMan hmm, D_DBAnteInfo AnteInfo, D_DBSateInfo SateInfo, D_U32 *blindparam_cnt)
{
    D_FBlindParam* blindparam = NULL;
    D_U32 param_cnt, idx;
    D_FEndFreq lnb_freq1, lnb_freq2;
    D_U8    lnb_type;
    D_FDiSEqCType  diseqc_type;  /**<diseqc 版本(类型)*/
#if 0
    D_GeoCoord localpos = {0};
#endif
    diseqc_type = (D_FDiSEqCType)SateInfo.diseqc_type;
#if 0
    if(curr_diseqc_type == D_DISEQC_TYPE_12)
    {
        diseqc_type = D_DISEQC_TYPE_12;
    }
    else if(curr_diseqc_type == D_DISEQC_TYPE_USALS)
    {
        diseqc_type = D_DISEQC_TYPE_USALS;
        p_conf_get_local_position(&localpos);
    }
#endif
    lnb_freq1 = AnteInfo.freq1;
    lnb_freq2 = AnteInfo.freq2;

    if(lnb_freq1 == 0 && lnb_freq2 == 0)
    {
        *blindparam_cnt = 0;
        return NULL;
    }
    else if(lnb_freq1 == 0 || lnb_freq2 == 0)
    {
        lnb_type = SINGLE;
        param_cnt = 2;
        lnb_freq1 = D_MAX(lnb_freq1, lnb_freq2);
    }
    else if(lnb_freq1 < FREQ_SWITCH_S_C_KU)
    {
        lnb_type = C_DOUBLE;
        param_cnt = 2;
    }
    else
    {
        lnb_freq1 = D_MIN(AnteInfo.freq1, AnteInfo.freq2);
        lnb_freq2 = D_MAX(AnteInfo.freq1, AnteInfo.freq2);
        lnb_type = KU_DOUBLE;
        param_cnt = 4;
    }

    blindparam = (D_FBlindParam*)d_mman_alloc(hmm, sizeof(D_FBlindParam) * param_cnt);
    if(!blindparam)
        param_cnt = 0;

    if(lnb_type == SINGLE)
    {
        for(idx = 0; idx < param_cnt; idx++)
        {
            blindparam[idx] = dvbs_blindparam_single[idx];
            blindparam[idx].lnbfreq1 = lnb_freq1;
            blindparam[idx].f22kstate = SateInfo.diseqc_22k;
            blindparam[idx].diseqc.diseqc_type = diseqc_type;
            blindparam[idx].diseqc.diseqc_port = 0;//SateInfo.diseqc_port;
            blindparam[idx].diseqc.position_no = 0;//SateInfo.diseqc_pos;
            blindparam[idx].diseqc.sate_longitude = 0;// SateInfo.longitude;
            blindparam[idx].diseqc.local_longitude = 0;//localpos.longitude;
            blindparam[idx].diseqc.local_latitude = 0;//localpos.latitude;
        }
    }
    else if(lnb_type == C_DOUBLE)
    {
        for(idx = 0; idx < param_cnt; idx++)
        {
            blindparam[idx] = dvbs_blindparam_c_double[idx];
            blindparam[idx].lnbfreq1 = (idx < 1) ? lnb_freq1 : lnb_freq2;
            blindparam[idx].startfreq = blindparam[idx].lnbfreq1 - MAX_SEARCH_FREQ_S_C;
            blindparam[idx].f22kstate = SateInfo.diseqc_22k;
            blindparam[idx].diseqc.diseqc_type = diseqc_type;
            blindparam[idx].diseqc.diseqc_port = 0;//SateInfo.diseqc_port;
            blindparam[idx].diseqc.position_no = 0;//SateInfo.diseqc_pos;
            blindparam[idx].diseqc.sate_longitude = 0;// SateInfo.longitude;
            blindparam[idx].diseqc.local_longitude = 0;//localpos.longitude;
            blindparam[idx].diseqc.local_latitude = 0;//localpos.latitude;
        }
    }
    else if(lnb_type == KU_DOUBLE)
    {
        for(idx = 0; idx < param_cnt; idx++)
        {
            blindparam[idx] = dvbs_blindparam_ku_double[idx];
            blindparam[idx].lnbfreq1 = (idx < 2) ? lnb_freq1 : lnb_freq2;
            blindparam[idx].diseqc.diseqc_type = diseqc_type;
            blindparam[idx].diseqc.diseqc_port = 0;//SateInfo.diseqc_port;
            blindparam[idx].diseqc.position_no = 0;//SateInfo.diseqc_pos;
            blindparam[idx].diseqc.sate_longitude = 0;// SateInfo.longitude;
            blindparam[idx].diseqc.local_longitude = 0;//localpos.longitude;
            blindparam[idx].diseqc.local_latitude = 0;//localpos.latitude;
        }
    }

    *blindparam_cnt = param_cnt;

    return blindparam;
}


static D_Result dvbs_init_group (D_ASGroup *scan_group, D_ScanTaskConfig *as_config, D_HMMan hmm)
{
    P_ScanConfig *pScanconf;
    D_U32 n;
    D_ID dbid;
    D_ID *db_ts_id;
    D_DBRecset tsrset;
    D_DBTSInfo tsinfo;
    D_DBSateInfo sateinfo;
    D_DBAnteInfo anteinfo;
    D_ScanFendParamNode *fendnode;

    pScanconf = (P_ScanConfig *)(as_config->pReserved);
    if(!pScanconf)
    {
        return D_ERR;
    }

    dbid = _db_sat_id[scan_group->group_id];
    if(D_OK != d_dbase_get_sat_info(dbid, &sateinfo))
    {
        D_ERROR("Error : get sateinfo error.  %s:%d \n", __FUNCTION__, __LINE__);
        return D_ERR;
    }

    dbid = _db_ant_id[scan_group->group_id];

    if(D_OK != d_dbase_get_ante_info(dbid, &anteinfo))
    {
        D_ERROR("Error : get anteinfo error.  %s:%d \n", __FUNCTION__, __LINE__);
        return D_ERR;
    }

    scan_group->AnteInfo = anteinfo;
    scan_group->SateInfo = sateinfo;
    scan_group->db_sat_id = _db_sat_id[scan_group->group_id];
    scan_group->sdt_srv_type_en = as_config->sdt_srv_type_en;

    if(pScanconf->mode == STB_SCAN_MODE_BLIND)
    {
        scan_group->scan_mode = D_AUTO_SCAN_MODE_BLIND;
        scan_group->nit_strategy = D_NIT_STRA_NONE;
        scan_group->findSrvInfoInMain = D_FALSE;
        scan_group->blindparam = dvbs_set_blind_param(as_config, hmm, anteinfo, sateinfo, &(scan_group->blindparam_cnt));
    }
    else
    {
        db_ts_id = (D_ID *)SCAN_MEM_ALLOC(sizeof(D_ID) * SATE_TS_MAX_NUM);
        d_dbase_rset_init(&tsrset, SATE_TS_MAX_NUM, db_ts_id);

        d_dbase_get_ts_by_sat(&tsrset, scan_group->db_sat_id);

        for(n = 0; n < tsrset.cnt; n++)
        {
            if(D_OK == d_dbase_get_ts_info(tsrset.ids[n], &tsinfo))
            {
                D_SI_ALLOC(hmm, fendnode);
                if(!fendnode)
                {
                    return D_ERR;
                }

                fendnode->fendparam = tsinfo.param;
                D_SI_LIST_ADD(scan_group->scanFendParamList, fendnode);
                scan_group->scanFendParamList_cnt++;
            }
        }

        SCAN_MEM_FREE(db_ts_id);

        if(pScanconf->netFlag)
        {
            scan_group->scan_mode = D_AUTO_SCAN_MODE_NIT;
            scan_group->nit_strategy = D_NIT_STRA_NONE;
            scan_group->findSrvInfoInMain = D_FALSE;
        }
        else
        {
            scan_group->scan_mode = D_AUTO_SCAN_MODE_TP;
            scan_group->nit_strategy = D_NIT_STRA_NONE;
            scan_group->findSrvInfoInMain = D_FALSE;
        }
    }

    return D_OK;
}

static D_Result dvbs_save_group(D_ASGroup *scan_group, D_ScanTaskConfig *as_config)
{
    D_U16 idx;
    D_DBID dbid, db_sat_id;
    D_ScanTsInfoNode *scants;
    D_DBTSID *db_ts_id;
    D_ID db_bouq_id[D_SCAN_MAX_BOUQ_CNT] = {0};
    D_DBTSInfo ts_info;

    if(scan_group->scanResult.scan_tsinfo_cnt == 0 ||
       ((scan_group->scan_mode != D_AUTO_SCAN_MODE_BLIND) && (scan_group->scanResult.tv_cnt + scan_group->scanResult.radio_cnt) == 0))
    {
        return D_OK;
    }

    db_sat_id = scan_group->db_sat_id;
    db_ts_id = (D_DBTSID*)SCAN_MEM_ALLOC(sizeof(D_DBTSID) * scan_group->scanResult.scan_tsinfo_cnt);
    if(scan_group->scanResult.scan_tsinfo_cnt && db_ts_id)
    {
        memset(db_ts_id, 0xff, sizeof(D_DBTSID) * scan_group->scanResult.scan_tsinfo_cnt);

        /*存储频点信息*/
        D_SI_FOR_EACH_BEGIN(D_ScanTsInfoNode, scan_group->scanResult.scan_tsinfo_list, scants)
        if(scants->valid && (scants->ts_no < scan_group->scanResult.scan_tsinfo_cnt)/* && ((scants->ts_info.tv_cnt + scants->ts_info.radio_cnt) > 0)*/)
        {
            D_DB_TS_INFO_INIT(&ts_info);
            D_SCANTSINFO_TO_DBSRVINFO(&ts_info, &(scants->ts_info));
            ts_info.db_net_id = 0;
            ts_info.tuner_type = scan_group->fend_type;
            ts_info.db_sat_id = db_sat_id;

            /*保存频点信息*/
            //dbid = d_dbase_get_ts_by_param_ex(db_sat_id, scan_group->fend_type, &scants->ts_info.param);
            dbid = d_dbase_get_same_ts_num_dvbs(&ts_info, D_FEND_DVBS);
            if (-1 != dbid)
            {
                /*更新频点信息*/
                d_dbase_updata_ts_info(dbid, &ts_info);
            }
            else
            {
                /*添加频点，并更新频点记录集信息*/
                dbid = d_dbase_insert_ts (&ts_info);
            }

            /*每个频点在数据库里的id*/
            db_ts_id[scants->ts_no] = dbid;

            D_DUMP("[scan] add ts -> dbtsid: %03d tsid: 0x%04x orgnetid: 0x%04x freq: %d\n", dbid, ts_info.ts_id, ts_info.org_net_id, ts_info.param.freq);
        }
        D_SI_FOR_EACH_END(D_ScanTsInfoNode, scan_group->scanResult.scan_tsinfo_list, scants);

        /*保存业务群信息*/
        for(idx = 0; idx < scan_group->scanResult.bouq_cnt; idx++)
        {
            dbid = d_dbase_insert_bouq (scan_group->scanResult.bouq_info[idx]);
            db_bouq_id[idx] = dbid;
        }

        if((scan_group->scanResult.tv_cnt + scan_group->scanResult.radio_cnt) > 0)
        {
#if 0
            /*对所有节目进行排序*/
            if(g_custom_config.scan.asort)
            {
                D_ScanSortMode mode = D_SCAN_SORT_MODE_NOT;

                if(g_custom_config.scan.asort == 1)mode = D_SCAN_SORT_MODE_TS;
                else if(g_custom_config.scan.asort == 2)mode = D_SCAN_SORT_MODE_SRVID;
                else if(g_custom_config.scan.asort == 3)mode = D_SCAN_SORT_MODE_LCN;
                else if(g_custom_config.scan.asort == 4)mode = D_SCAN_SORT_MODE_FREECA;
                else if(g_custom_config.scan.asort == 5)mode = D_SCAN_SORT_MODE_NAME;

                if(mode != D_SCAN_SORT_MODE_NOT)
                {
                    p_scan_sort_srv((D_ScanSrvInfoNode *)scan_group->scanResult.srvList_tv, mode);
                    p_scan_sort_srv((D_ScanSrvInfoNode *)scan_group->scanResult.srvList_radio, mode);
                }
            }
#endif
            /*保存所有节目*/
            save_type_service((D_ScanSrvInfoNode *)scan_group->scanResult.srvList_tv, db_ts_id, scan_group->scanResult.scan_tsinfo_cnt, db_bouq_id, scan_group->scanResult.bouq_cnt);
            save_type_service((D_ScanSrvInfoNode *)scan_group->scanResult.srvList_radio, db_ts_id, scan_group->scanResult.scan_tsinfo_cnt, db_bouq_id, scan_group->scanResult.bouq_cnt);
        }
    }

    SCAN_MEM_FREE(db_ts_id);

    return D_OK;
}







/*私有初始化, 对各组进行分配并初始化。主要设定搜索策略与频率列表*/
static D_Result dvbs_auto_scan_init (D_ASGroup **group, D_U32*group_cnt, D_ScanTaskConfig *as_config, D_HMMan hmm)
{
    D_ASGroup*scan_group;
    D_U32   group_id = 0;
    P_ScanConfig *pScanconf;
    D_U32 idx;
    D_DBRecset satrset;
    D_DBSateInfo sateinfo;
    D_DBAnteID ante_dbid;

    pScanconf = (P_ScanConfig *)(as_config->pReserved);
    if(!pScanconf)
    {
        return D_ERR;
    }

    ScanProgType = pScanconf->progType;
    ScanOnlyFreeFlag = pScanconf->freeFlag;

    d_dbase_rset_init(&satrset, SATE_MAX_NUM, _db_sat_id);
#if 0
    curr_diseqc_type = D_DISEQC_TYPE_10;
    if(p_conf_get_lnb())
    {
        if(p_conf_get_motortype())
        {
            curr_diseqc_type = D_DISEQC_TYPE_USALS;
        }
        else
        {
            curr_diseqc_type = D_DISEQC_TYPE_12;
        }
    }
#endif
    if(as_config->scan_type == STB_SCAN_TYPE_SINGLE_SATELLITE)
    {
        satrset.cnt = 1;
        satrset.ids[0] = pScanconf->satelliteNo;
    }
    else
    {
        d_dbase_get_sates_selected(&satrset);
    }

    if(satrset.cnt == 1)
    {
        as_config->group_end_save = D_FALSE;
    }

    for(idx = 0; idx < satrset.cnt; idx++)
    {
        if(group_id >= (D_SCAN_GROUP_MAX_CNT - 1))
        {
            break;
        }

        /*搜索配置*/
        D_SCAN_GROUP_ALLOC(hmm, scan_group);
        if(!scan_group)
        {
            D_ERROR ("[AutoScan] Cannot allocate group\n");
            return D_ERR;
        }

        group[group_id++] = scan_group;

        //scan_group->type = D_SCAN_TYPE_DVBS;
        scan_group->group_id = idx;
        scan_group->fend_type = as_config->fend_type;
        scan_group->sdt_srv_type_en = as_config->sdt_srv_type_en;
        scan_group->hfman = d_fman_get_handle_by_type(scan_group->fend_type, 0);
        scan_group->groupOp = &DVBS_AutoScanGroup_Op;

        if(D_OK != d_dbase_get_sat_info(satrset.ids[idx], &sateinfo))
        {
            D_ERROR("Error : get sateinfo error.  %s:%d \n", __FUNCTION__, __LINE__);
            return D_ERR;
        }

        //if(curr_diseqc_type == D_DISEQC_TYPE_12 || curr_diseqc_type == D_DISEQC_TYPE_USALS)
        //{
        //ante_dbid = (D_DBAnteID)p_conf_get_db_ante_id();
        //}
        else
        {
            ante_dbid = sateinfo.antenna_slot;
        }

        _db_ant_id[idx] = ante_dbid;

        if(!as_config->group_end_save)
        {
            dvbs_init_group(scan_group, as_config, hmm);
        }
    }

    /*记录组数*/
    *group_cnt = group_id;

    return D_OK;
}


/** @brief将搜索结果保存至数据库。*/
static D_Result dvbs_auto_scan_store(D_ASGroup **group, D_U32 group_cnt, D_ScanTaskConfig *as_config)
{
    D_U16 groupid;
    D_ASGroup   *scan_group;

    if(!group)
    {
        return D_ERR;
    }

    d_dbase_set_rset_en(0);

    /*对每组的搜索结果进行保存*/
    for(groupid = 0; groupid < group_cnt; groupid++)
    {
        scan_group = group[groupid];

        D_DUMP("scan store : group %d,   dbsatid %d\n", groupid, scan_group->db_sat_id);
        if(!scan_group->have_save)
        {
            dvbs_save_group(scan_group, as_config);
        }
    }

    d_dbase_flush();

    return D_OK;
}

static D_Result dvbs_auto_scan_destroy (D_ASGroup **group, D_U32 group_cnt, D_ScanTaskConfig *as_config)
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


D_AutoScanOp DVBS_AutoScan_Op =
{
    dvbs_auto_scan_init,
    dvbs_auto_scan_store,
    dvbs_auto_scan_destroy
};





/*私有初始化*/
static D_Result dvbs_group_start (D_ASGroup *scan_group, D_ScanTaskConfig *as_config, D_HMMan hmm)
{
    if(as_config->group_end_save)
    {
        dvbs_init_group(scan_group, as_config, hmm);
    }

    if(curr_diseqc_type == D_DISEQC_TYPE_12)
    {
        if(scan_group->SateInfo.diseqc_pos)
        {
            scan_set_diseqc(scan_group->hfman, scan_group->SateInfo.diseqc_pos);
        }
    }
    else if(curr_diseqc_type == D_DISEQC_TYPE_USALS)
    {
        scan_set_diseqc(scan_group->hfman, scan_group->SateInfo.diseqc_pos);
    }

    return D_OK;
}

/*私有反初始化*/
static D_Result dvbs_group_end(D_ASGroup *scan_group, D_ScanTaskConfig *as_config)
{
    if(!as_config->group_end_save)
    {
        return D_OK;
    }

    D_DUMP("group_end store    dbsatid %d\n", scan_group->db_sat_id);

    scan_group->have_save = D_TRUE;
    if(scan_group->scanResult.scan_tsinfo_cnt == 0 && (scan_group->scanResult.tv_cnt + scan_group->scanResult.radio_cnt) == 0)
    {
        return D_OK;
    }

    d_dbase_set_rset_en(0);
    dvbs_save_group(scan_group, as_config);
    //d_dbase_flush();

    return D_OK;
}


/*检查ca_sys_id是否符合定制要求*/
static D_Bool dvbs_check_ca_sys_id (D_U32 type, D_U16 ca_sys_id)
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
static D_Bool dvbs_check_bouq_id (D_U32 type, D_U16 bouq_id)
{
    return D_TRUE;
}



/*检查服务是否符合定制要求*/
static D_Bool dvbs_check_srvice (D_U32 type, D_ScanSrvInfo *srvinfo)
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
    }

    if(ScanProgType == STB_SCAN_PROG_TYPE_TV_RADIO)
    {
        if(srvinfo->srv_type != D_DB_SRV_TV && srvinfo->srv_type != D_DB_SRV_RADIO)
        {
            ret = D_FALSE;
        }
    }
    else if(ScanProgType == STB_SCAN_PROG_TYPE_TV)
    {
        if(srvinfo->srv_type != D_DB_SRV_TV)
        {
            ret = D_FALSE;
        }
    }
    else if(ScanProgType == STB_SCAN_PROG_TYPE_RADIO)
    {
        if(srvinfo->srv_type != D_DB_SRV_RADIO)
        {
            ret = D_FALSE;
        }
    }
    else
    {
        ret = D_FALSE;
    }

    if(ScanOnlyFreeFlag)
    {
        if(srvinfo->ca_mask)
        {
            ret = D_FALSE;
        }
    }

#ifdef HI_P_SHUZITAIHE
    /* 138上屏蔽12429 H 3330 频点节目（美国之音等）。*/
    if(curr_tp_invalid)
    {
        ret = D_FALSE;
    }
#endif

    return ret;
}

/*sdt表里提取服务信息*/
static D_Result dvbs_get_private_descrs_info_in_sdt(D_U32 type, D_Descr *descr, D_ScanSrvInfo *srv_info)
{
    switch(descr->tag)
    {
        default:
            break;
    }

    return D_OK;
}

/*bat表里提取服务信息*/
static D_Result dvbs_get_srvinfo_in_bat(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srv_info, D_ScanResultValue *result)
{
    return D_OK;
}


/*nit表里提取服务信息*/
static D_Result dvbs_get_srvinfo_in_nit(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srv_info, D_ScanResultValue *result)
{
    return D_OK;
}

/*其它私有表里提取服务信息*/
static D_Result dvbs_get_srvinfo_in_others(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srv_info, D_ScanResultValue *result)
{
    return D_OK;
}


/*单频点搜索配置*/
static D_Result dvbs_set_tpsiscan_config(D_ASGroup *scan_group, D_TpSiScanTaskConfig *conf)
{
    conf->pat_timeout = DVBS_PAT_TIMEOUT;
    conf->pmt_timeout = DVBS_PMT_TIMEOUT;
    conf->cat_timeout = DVBS_CAT_TIMEOUT;
    conf->bat_timeout = DVBS_BAT_TIMEOUT;
    conf->nit_timeout = DVBS_NIT_TIMEOUT;
    conf->sdt_timeout = DVBS_SDT_TIMEOUT;
    conf->sdt_oth_timeout = DVBS_SDT_OTH_TIMEOUT;

    conf->lock_enable = D_FALSE;
    conf->table_mask = 0;

    if(scan_group->scan_mode == D_AUTO_SCAN_MODE_NIT && scan_group->scanResult.found_nit == D_FALSE)
    {
        conf->table_mask |= TABLE_MASK_NIT;
    }
    else
    {
        conf->table_mask |= TABLE_MASK_PAT | TABLE_MASK_PMT  | TABLE_MASK_SDT;
    }
    return D_OK;
}

/*nit表里提取频率列表信息*/
D_Result dvbs_get_freqlist_in_nit(D_U32 type, D_ScanTsInfoNode *scants, D_FEndParam*fparam, D_U32 *fcnt)
{
    D_NitTS *ts;
    D_Descr *descr;
    D_Nit      *nit;
    D_FEndParam param;

    if(!scants || !(scants->scantp) || !(scants->scantp->nits) || !fparam || !fcnt)
    {
        return D_ERR;
    }

    //if(type == D_SCAN_TYPE_DVBS)
    {
        D_SI_FOR_EACH_BEGIN (D_Nit, scants->scantp->nits, nit)
        D_SI_FOR_EACH_BEGIN (D_NitTS, nit->tses, ts)
        D_SI_FOR_EACH_BEGIN (D_Descr, ts->descrs, descr)
        switch (descr->tag)
        {
            case DESCR_SAT_DEL_SYS:/*卫星*/
                if(scants->scantp->type == D_FEND_DVBS)
                {
                    D_SatelliteDeliverySystemDescr*sds = (D_SatelliteDeliverySystemDescr*) descr;

                    memset(&param, 0x00, sizeof(D_FEndParam));
                    param.dvbs.freq = sds->freq;
                    param.dvbs.baud = sds->baud;
                    param.dvbs.pol = (D_FEndPol)sds->pol;
                    D_DUMP("[AutoScan] nit SAT_DEL_SYS find freq:%d baud:%d pol\n", param.freq, param.dvbs.baud, param.dvbs.pol);
                    if ((param.freq >= MIN_SEARCH_FERQ_S_KU) && (param.freq <= MAX_SEARCH_FREQ_S_KU)
                        || (param.freq >= MIN_SEARCH_FERQ_S_C) && (param.freq <= MAX_SEARCH_FREQ_S_C))
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
D_Result dvbs_get_tp_info(D_U32 type, D_ScanTsInfoNode *scants, D_ScanResultValue *scanResult)
{
    /* 138上屏蔽12429 H 3330 频点节目（美国之音等）。*/
#ifdef HI_P_SHUZITAIHE
    D_FEndParam tp1, tp2;

    tp1.dvbs.freq = INVALID_TP_FREQ;
    tp1.dvbs.baud = INVALID_TP_BAUD;
    tp1.dvbs.pol = D_FEND_HOR_POL;

    tp2.dvbs.freq = INVALID_TP_FREQ;
    tp2.dvbs.baud = INVALID_TP_BAUD;
    tp2.dvbs.pol = D_FEND_VER_POL;

    curr_tp_invalid = D_FALSE;

    if(D_OK == d_dbase_check_ts_dvbs(&tp1, &(scants->ts_info.param)) || D_OK == d_dbase_check_ts_dvbs(&tp2, &(scants->ts_info.param)))
    {
        curr_tp_invalid = D_TRUE;
    }
#endif
    return D_OK;
}

static D_Result dvbs_group_end_private_op(D_ASGroup *scan_group, D_HMMan hmm)
{
    return D_OK;
}

/*DVBS自动搜索操作*/
static D_ASGroupOp DVBS_AutoScanGroup_Op =
{
    dvbs_group_start,
    dvbs_group_end,
    dvbs_set_tpsiscan_config,
    dvbs_check_ca_sys_id,
    dvbs_check_bouq_id,
    NULL,                   //dvbc_group_end_private_op,
    dvbs_get_freqlist_in_nit,
    dvbs_get_tp_info,
    dvbs_get_private_descrs_info_in_sdt,
    dvbs_get_srvinfo_in_bat,
    dvbs_get_srvinfo_in_nit,
    dvbs_get_srvinfo_in_others,
    dvbs_check_srvice
};








/*私有初始化, 对各组进行分配并初始化。主要设定搜索策略与频率列表，此时搜索任务还没启动*/
static D_Result dvbs_manual_scan_init(D_U32 type, D_ScanTaskConfig *ms_config)
{
    P_ScanConfig *pScanconf;
    pScanconf =  (P_ScanConfig *)(ms_config->pReserved);
    if(!pScanconf)
    {
        return D_ERR;
    }

    ScanProgType = pScanconf->progType;
    ScanOnlyFreeFlag = pScanconf->freeFlag;
    curr_diseqc_type = D_DISEQC_TYPE_10;
#if 0
    if(p_conf_get_lnb())
    {
        if(p_conf_get_motortype())
        {
            curr_diseqc_type = D_DISEQC_TYPE_USALS;
        }
        else
        {
            curr_diseqc_type = D_DISEQC_TYPE_12;
        }
    }
#endif
    return D_OK;
}

/*开始搜索用户回调，此时任务已经启动，在任务回调时执行*/
static D_Result dvbs_manual_scan_start(D_U32 type, D_ScanTaskConfig *ms_config)
{
    if(curr_diseqc_type == D_DISEQC_TYPE_12)
    {
        if(ms_config->SateInfo.diseqc_pos)
        {
            scan_set_diseqc(ms_config->hfman, ms_config->SateInfo.diseqc_pos);
        }
    }
    else if(curr_diseqc_type == D_DISEQC_TYPE_USALS)
    {
        scan_set_diseqc(ms_config->hfman, ms_config->SateInfo.diseqc_pos);
    }

    return D_OK;
}

static D_Result dvbs_manual_scan_store(D_U32 type, D_ScanTaskConfig *ms_config, D_ScanResultValue*ms_result)
{
    D_DBID dbid, idx;
    D_ID db_ts_id;
    D_ScanTsInfoNode *scants;
    D_ID db_bouq_id[D_SCAN_MAX_BOUQ_CNT] = {0};
    D_DBTSInfo ts_info;

    if((!ms_result) || (!(ms_result->scan_tsinfo_list)))
    {
        return D_ERR;
    }

#if 1
    if(g_custom_config.scan.mdelete == 1)
    {
        //delete srvs
    }
    else
    {
        /*搜索不到节目时，不删除原有节目*/
        if((ms_result->tv_cnt + ms_result->radio_cnt) <= 0)
        {
            return D_OK;
        }
        else
        {
            //delete srvs
        }
    }
#endif

    d_dbase_set_rset_en(0);

    scants = (D_ScanTsInfoNode*)ms_result->scan_tsinfo_list;
    D_DB_TS_INFO_INIT(&ts_info);
    D_SCANTSINFO_TO_DBSRVINFO(&ts_info, &(scants->ts_info));
    ts_info.db_net_id = 0;
    ts_info.db_sat_id = ms_config->db_sat_id;
    ts_info.tuner_type = ms_config->fend_type;

    /*保存频点信息*/
    //db_ts_id = d_dbase_get_ts_by_param_ex (dbid, ms_result->fend_type, &scants->ts_info.param);
    db_ts_id = d_dbase_get_same_ts_num_dvbs(&ts_info, D_FEND_DVBS);
    if (-1 != db_ts_id)
    {
        /*删除当前频点下原有的节目，并更新频点信息*/
        //d_dbase_delete_srvs_of_ts(db_ts_id);
        d_dbase_updata_ts_info(db_ts_id, &ts_info);
    }
    else
    {
        /*添加频点，并更新频点记录集信息*/
        db_ts_id = d_dbase_insert_ts (&ts_info);
        d_dbase_get_ts_total_num();
    }

    if(db_ts_id == -1)
    {
        D_ERROR ("[ManualScan] db_ts_id == -1 !!!\n");
        d_dbase_set_rset_en(1);
        return D_ERR;
    }

    D_DUMP("[scan] add ts -> dbtsid: %03d tsid: 0x%04x orgnetid: 0x%04x freq: %d\n", db_ts_id, ts_info.ts_id, ts_info.org_net_id, ts_info.param.freq);

    /*保存业务群信息*/
    for(idx = 0; idx < ms_result->bouq_cnt; idx++)
    {
        dbid = d_dbase_insert_bouq (ms_result->bouq_info[idx]);
        db_bouq_id[idx] = dbid;
    }

    /*搜索到节目时*/
    if((ms_result->tv_cnt + ms_result->radio_cnt) > 0)
    {
#if 0
        /*对所有节目进行排序*/
        if(g_custom_config.scan.msort)
        {
            D_ScanSortMode mode = D_SCAN_SORT_MODE_NOT;

            if(g_custom_config.scan.msort == 1)mode = D_SCAN_SORT_MODE_TS;
            else if(g_custom_config.scan.msort == 2)mode = D_SCAN_SORT_MODE_SRVID;
            else if(g_custom_config.scan.msort == 3)mode = D_SCAN_SORT_MODE_LCN;
            else if(g_custom_config.scan.msort == 4)mode = D_SCAN_SORT_MODE_FREECA;
            else if(g_custom_config.scan.msort == 5)mode = D_SCAN_SORT_MODE_NAME;

            if(mode != D_SCAN_SORT_MODE_NOT)
            {
                p_scan_sort_srv((D_ScanSrvInfoNode *)ms_result->srvList_tv, mode);
                p_scan_sort_srv((D_ScanSrvInfoNode *)ms_result->srvList_radio, mode);
            }
        }
#endif
        /*保存所有节目*/
        save_type_service((D_ScanSrvInfoNode *)ms_result->srvList_tv, &db_ts_id, 1, db_bouq_id, ms_result->bouq_cnt);
        save_type_service((D_ScanSrvInfoNode *)ms_result->srvList_radio, &db_ts_id, 1, db_bouq_id, ms_result->bouq_cnt);
    }

    d_dbase_flush();

    return D_OK;
}


static D_Result dvbs_manual_scan_destroy(D_U32 type, D_ScanTaskConfig *ms_config, D_ScanResultValue*ms_result)
{
    return D_OK;
}


/*单频点搜索配置*/
static D_Result dvbs_manual_scan_set_tpsiscan_config(D_U32 type, D_TpSiScanTaskConfig *conf)
{
    conf->pat_timeout = DVBS_PAT_TIMEOUT;
    conf->pmt_timeout = DVBS_PMT_TIMEOUT;
    conf->cat_timeout = DVBS_CAT_TIMEOUT;
    conf->bat_timeout = DVBS_BAT_TIMEOUT;
    conf->nit_timeout = DVBS_NIT_TIMEOUT;
    conf->sdt_timeout = DVBS_SDT_TIMEOUT;
    conf->sdt_oth_timeout = DVBS_SDT_OTH_TIMEOUT;
    conf->network_id = 0;
    conf->lock_enable = D_FALSE;
    conf->table_mask = 0;

    conf->table_mask |= TABLE_MASK_PAT | TABLE_MASK_PMT  | TABLE_MASK_SDT;

    return D_OK;
}





/*直播星手动动搜索操作*/
D_ManualScanOp DVBS_ManualScan_Op =
{
    dvbs_manual_scan_init,
    dvbs_manual_scan_start,
    dvbs_manual_scan_store,
    dvbs_manual_scan_destroy,
    dvbs_manual_scan_set_tpsiscan_config,
    dvbs_check_ca_sys_id,
    dvbs_check_bouq_id,
    dvbs_get_tp_info,
    dvbs_get_private_descrs_info_in_sdt,
    dvbs_get_srvinfo_in_bat,
    dvbs_get_srvinfo_in_nit,
    dvbs_get_srvinfo_in_others,
    dvbs_check_srvice
};




