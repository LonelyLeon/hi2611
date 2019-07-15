/** @file
* @brief DVBT ����ʱ�ĵ�һЩע�ắ��
* @author ����
* @date 2013-4-4 ����: �����ļ�
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
#include "dConfigFile.h"
#include "pStbScan.h"
#include "pMem.h"
#include "pConfig.h"
#include "pStb.h"
#include "pCustomConfig.h"
#include "pDBaseDefault.h"
#include "pSIParse.h"


/*dtmb���Ƿ����������������Ŀ�ظ�������*/
#define DVBT_DEAL_SAME_TS_PROG_ENABLE (0)

#define MAX_SEARCH_FREQ_T   874
#define MIN_SEARCH_FERQ_T   47

#define DVBT_PAT_TIMEOUT            2000
#define DVBT_CAT_TIMEOUT            3000
#define DVBT_SDT_TIMEOUT            10000
#define DVBT_PMT_TIMEOUT            2000
#define DVBT_SDT_OTH_TIMEOUT        10000
#define DVBT_NIT_TIMEOUT            10000
#define DVBT_BAT_TIMEOUT            10000


#define MAX_SCANTS_CNT (128)
#define MAX_PROGS_CNT (512)

/*Ƶ�����������Ϣ����ڵ�*/
typedef struct
{
    D_U16   ts_cnt;
    D_U16   srv_cnt;
    D_ScanTsInfoNode *tsNode[MAX_SCANTS_CNT];
    D_ScanSrvInfoNode *srvNode[MAX_PROGS_CNT];
} D_CheckTsSrv;

#if 0
const static D_U32
as_dvbt_freq_list[] =
{
    52500, 60500, 68500, 80000,
    88000, 171000, 179000, 187000,
    195000, 203000, 211000, 219000,
    474000, 482000, 490000, 498000,
    506000, 514000, 522000, 530000,
    538000, 546000, 554000, 562000,
    610000, 618000, 626000, 634000,
    642000, 650000, 658000, 666000,
    674000, 682000, 690000, 698000,
    706000, 714000, 722000, 730000,
    738000, 746000, 754000, 762000,
    770000, 778000, 786000, 794000
};
#endif

static D_WaveBand wave_band[] =
{
    {52, 68, 8},
    {80, 88, 8},
    {115, 459, 8},
    {474, 874, 8},
};

static D_ASGroupOp DVBT_AutoScanGroup_Op;

/*bit0��ʾ�Ƿ��н�Ŀû��lcn�� bit1��ʾ�Ƿ��н�Ŀ��lcn*/
static D_U32    AllTVChanLcnStatus = 0;
static D_U32    AllRadioChanLcnStatus = 0;
static D_U16 scan_prog_version = 0xFFFF;

#define SCAN_MEM_ALLOC(_s) d_mem_alloc(0,_s)
#define SCAN_MEM_FREE(_p) if(_p){d_mem_free(_p);_p = NULL;}


/*�������������Ľ�Ŀ*/
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

/*���������������Ƶ�����Ŀ���ݣ�
dtmb���ڷ��������������н��棬���ܴ�����������ͬ���ݵĲ�ͬƵ�㣬
���ﾭ���ź�������С��ѡ��@qiny 2015.11.10*/

#if DVBT_DEAL_SAME_TS_PROG_ENABLE
static D_Result
check_deal_ts_progs(D_U16 tsno1, D_U16 tsno2, D_CheckTsSrv *check_tssrv, D_ScanTaskConfig *as_config)
{
    D_U32 i, j, start_j, tsidx;
    D_S32 num;
    D_U8 srv_type;
    D_U16 srv_id;

    if(tsno1 == tsno2)
    {
        return D_ERR;
    }

    srv_id = 0;
    start_j = 0;
    for(i = 0; i < check_tssrv->srv_cnt; i++)
    {
        if(srv_id < check_tssrv->srvNode[i]->srvinfo.srv_id)
        {
            srv_id = check_tssrv->srvNode[i]->srvinfo.srv_id;
            start_j = i;
        }

        if(check_tssrv->srvNode[i]->ts_no != tsno1 || (!check_tssrv->srvNode[i]->valid))
        {
            continue;
        }
        for(j = start_j; j < check_tssrv->srv_cnt; j++)
        {
            /*��srvid���������*/
            if(check_tssrv->srvNode[i]->srvinfo.srv_id < check_tssrv->srvNode[j]->srvinfo.srv_id)
            {
                break;
            }
            if(check_tssrv->srvNode[j]->ts_no != tsno2 || i == j || (!check_tssrv->srvNode[j]->valid))
            {
                continue;
            }
            if((check_tssrv->srvNode[i]->srvinfo.srv_id == check_tssrv->srvNode[j]->srvinfo.srv_id)
               && (check_tssrv->srvNode[i]->srvinfo.srv_type == check_tssrv->srvNode[j]->srvinfo.srv_type))
            {
                if(check_tssrv->tsNode[tsno1]->ts_info.quality < check_tssrv->tsNode[tsno2]->ts_info.quality)
                {
                    check_tssrv->srvNode[i]->valid = 0;
                    tsidx = tsno1;
                    srv_type = check_tssrv->srvNode[i]->srvinfo.srv_type;
                }
                else
                {
                    check_tssrv->srvNode[j]->valid = 0;
                    tsidx = tsno2;
                    srv_type = check_tssrv->srvNode[j]->srvinfo.srv_type;
                }

                if(srv_type == D_DB_SRV_TV)
                {
                    num = (D_S32)check_tssrv->tsNode[tsidx]->ts_info.tv_cnt;
                    num = D_MAX(0, (num - 1));
                    check_tssrv->tsNode[tsidx]->ts_info.tv_cnt = (D_U8)num;
                }
                else
                {
                    num = (D_S32)check_tssrv->tsNode[tsidx]->ts_info.radio_cnt;
                    num = D_MAX(0, (num - 1));
                    check_tssrv->tsNode[tsidx]->ts_info.radio_cnt = (D_U8)num;
                }
            }
        }
    }

    return D_OK;
}

static int cmp_srv_val(const void*a, const void*b)
{
    D_ScanSrvInfoNode *srvnode1, *srvnode2;

    srvnode1 = (D_ScanSrvInfoNode *)(a);
    srvnode2 = (D_ScanSrvInfoNode *)(b);

    return (int)((int)srvnode1->srvinfo.srv_id - (int)srvnode2->srvinfo.srv_id);
}

static D_Result
check_data_before_save(D_ASGroup *scan_group, D_ScanTaskConfig *as_config)
{
    D_U32 i, j;
    D_ScanSrvInfoNode *srvnode;
    D_ScanTsInfoNode *scants;
    D_CheckTsSrv *check_tssrv;

    if(scan_group->scanResult.scan_tsinfo_cnt < 2)
    {
        return D_OK;
    }

    check_tssrv = (D_CheckTsSrv*)SCAN_MEM_ALLOC(sizeof(D_CheckTsSrv));
    if(!check_tssrv)
    {
        return D_ERR;
    }
    memset(check_tssrv, 0x00, sizeof(D_CheckTsSrv));

    /*��ȡƵ����Ϣ*/
    check_tssrv->ts_cnt = scan_group->scanResult.scan_tsinfo_cnt;
    D_SI_FOR_EACH_BEGIN(D_ScanTsInfoNode, scan_group->scanResult.scan_tsinfo_list, scants)
    if(scants->valid && (scants->ts_no < scan_group->scanResult.scan_tsinfo_cnt) && ((scants->ts_info.tv_cnt + scants->ts_info.radio_cnt) > 0))
    {
        if(scants->ts_no < MAX_SCANTS_CNT)
        {
            check_tssrv->tsNode[scants->ts_no] = scants;
        }
    }
    D_SI_FOR_EACH_END(D_ScanTsInfoNode, scan_group->scanResult.scan_tsinfo_list, scants);

    /*��ȡƵ����Ϣ*/
    D_SI_FOR_EACH_BEGIN(D_ScanSrvInfoNode, scan_group->scanResult.srvList_tv, srvnode)
    if((!srvnode->valid) || (!(srvnode->srvinfo.valid)) || (!(check_tssrv->tsNode[srvnode->ts_no]))\
       || (!(check_tssrv->tsNode[srvnode->ts_no]->valid)))
    {
        continue;
    }

    if(check_tssrv->srv_cnt < (MAX_PROGS_CNT - 1))
    {
        check_tssrv->srvNode[check_tssrv->srv_cnt++] = srvnode;
    }
    D_SI_FOR_EACH_END(D_ScanSrvInfoNode, scan_group->scanResult.srvList_tv, srvnode);

    D_SI_FOR_EACH_BEGIN(D_ScanSrvInfoNode, scan_group->scanResult.srvList_radio, srvnode)
    if((!srvnode->valid) || (!(srvnode->srvinfo.valid)) || (!(check_tssrv->tsNode[srvnode->ts_no]))\
       || (!(check_tssrv->tsNode[srvnode->ts_no]->valid)))
    {
        continue;
    }

    if(check_tssrv->srv_cnt < (MAX_PROGS_CNT - 1))
    {
        check_tssrv->srvNode[check_tssrv->srv_cnt++] = srvnode;
    }
    D_SI_FOR_EACH_END(D_ScanSrvInfoNode, scan_group->scanResult.srvList_radio, srvnode);

    if(check_tssrv->srv_cnt < 2)
    {
        goto __CHECK_END;
    }

    /*��Ƶ������srv id����*/
    qsort(check_tssrv->srvNode, check_tssrv->srv_cnt, sizeof(D_ScanSrvInfoNode*), cmp_srv_val);

    for(i = 0; i < (check_tssrv->ts_cnt - 1); i++)
    {
        if((!(check_tssrv->tsNode[i])) || (!(check_tssrv->tsNode[i]->valid)))
        {
            continue;
        }

        for(j = (i + 1); j < check_tssrv->ts_cnt; j++)
        {
            if((!(check_tssrv->tsNode[j])) || (!(check_tssrv->tsNode[j]->valid)))
            {
                continue;
            }
            /*tsid��ͬʱ������Ƿ�����ͬ�Ľ�Ŀ���������ͬ�Ľ�Ŀ��˵��Ƶ���ظ�*/
            if(check_tssrv->tsNode[i]->ts_info.ts_id == check_tssrv->tsNode[j]->ts_info.ts_id)
            {
                check_deal_ts_progs(i, j, check_tssrv, as_config);
            }
        }
    }

__CHECK_END:
    if(check_tssrv)
    {
        SCAN_MEM_FREE(check_tssrv);
    }
    return D_OK;
}
#endif

/*˽�г�ʼ��, �Ը�����з��䲢��ʼ������Ҫ�趨����������Ƶ���б�*/
static D_Result dvbt_auto_scan_init (D_ASGroup **group, D_U32*group_cnt, D_ScanTaskConfig *as_config, D_HMMan hmm)
{
    D_ASGroup*scan_group = NULL;
    D_U32   group_id = 0;
    D_U32  num, i;
    D_FEndFreq freq;
    D_ScanFendParamNode *fendnode;
    D_FEndParam *fendparam;

    scan_prog_version = 0xFFFF;
    AllTVChanLcnStatus = 0;
    AllRadioChanLcnStatus = 0;
    as_config->group_end_save = D_FALSE;

    /*��������*/
    D_SCAN_GROUP_ALLOC(hmm, scan_group);
    if(!scan_group)
    {
        D_ERROR ("[AutoScan] Cannot allocate group\n");
        return D_ERR;
    }

    group[group_id++] = scan_group;

    //scan_group->type = D_SCAN_TYPE_DTMB;
    scan_group->db_sat_id = -1;
    scan_group->fend_type = D_FEND_DTMB;
    scan_group->hfman = d_fman_get_handle_by_type(D_FEND_DTMB, 0);
    scan_group->findSrvInfoInMain = D_FALSE;
    scan_group->sdt_srv_type_en = as_config->sdt_srv_type_en;
    scan_group->groupOp = &DVBT_AutoScanGroup_Op;

    if(as_config->scan_type == STB_SCAN_TYPE_AUTO)
    {
        D_U8 *payload;
        D_U16 len, temp;

        scan_group->scan_mode = D_AUTO_SCAN_MODE_NIT;
#ifdef D_CA_SUPPORT_DSCA
        scan_group->findSrvInfoInMain = D_TRUE;
#endif
        /*��Ƶ��*/
        D_SI_ALLOC(hmm, fendnode);
        if(!fendnode)
        {
            return D_ERR;
        }

        fendnode->fendparam.dtmb.freq = as_config->fend_param.dtmb.freq;
        D_SI_LIST_ADD(scan_group->scanFendParamList, fendnode);
        scan_group->scanFendParamList_cnt++;

        /* Ԥ��Ƶ�������б� */
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
                    payload += 4;
                    if(temp > 0 && p_scan_judge_freq_valid(temp))
                    {
                        D_SI_ALLOC(hmm, fendnode);
                        if(!fendnode)
                        {
                            return D_ERR;
                        }
                        fendnode->fendparam.dtmb.freq = temp;

                        D_SI_LIST_ADD(scan_group->scanFendParamList, fendnode);
                        scan_group->scanFendParamList_cnt++;
                    }
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
            D_FEndFreq freq_k;
            D_FEndFreq freq_start;
            D_FEndFreq freq_end;

            freq_start = as_config->startfreq * 10 + as_config->fend_param.freq;
            freq_end = as_config->endfreq * 10 + as_config->fend_param.dtmb.freq_k;

            /*����Ƶ���б�*/
            num = sizeof(wave_band) / sizeof(wave_band[0]);
            for(i = 0; i < num; i++)
            {
                if(wave_band[i].start_freq <= as_config->endfreq  && wave_band[i].end_freq >= as_config->startfreq)
                {
                    freq = wave_band[i].start_freq;
                    while(freq <= wave_band[i].end_freq)
                    {
                        freq_k = freq * 10 + ((i == 0) ? 5 : 0);
                        if(freq_k >= freq_start && freq_k <= freq_end)
                        {
                            D_SI_ALLOC(hmm, fendnode);
                            if(!fendnode)
                            {
                                return D_ERR;
                            }

                            fendnode->fendparam.dtmb.freq = freq;
                            fendnode->fendparam.dtmb.freq_k = (i == 0) ? 5 : 0;
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
            memset(fendparam, 0x00, sizeof(D_FEndParam));
            fendparam->dtmb.freq = scan_group->freq_start;
            fendparam->dtmb.freq_k = as_config->fend_param.freq;
            scan_group->base_fparam = fendparam;
        }
    }
    else if(as_config->scan_type == STB_SCAN_TYPE_LIST)
    {
        D_U8 *payload;
        D_U16 len, temp;

        scan_group->scan_mode = D_AUTO_SCAN_MODE_TP;
        scan_group->nit_strategy = D_NIT_STRA_NONE;
        if(as_config->Reserved)
        {
            D_FEndFreq *freqlist;
            if(!as_config->pReserved)
            {
                return D_ERR;
            }
            freqlist = (D_FEndFreq *)as_config->pReserved;
            for(i = 0; i < as_config->Reserved; i++)
            {
                if(p_scan_judge_freq_valid(*freqlist))
                {
                    D_SI_ALLOC(hmm, fendnode);
                    if(!fendnode)
                    {
                        return D_ERR;
                    }
                    fendnode->fendparam.dtmb.freq = *freqlist;
                    D_SI_LIST_ADD(scan_group->scanFendParamList, fendnode);
                    scan_group->scanFendParamList_cnt++;
                }
                freqlist ++;
            }
        }
        else
        {
            /* Ԥ��Ƶ�������б� */
            payload = d_conf_file_search_tag(CUSTOM_CONFIG_SEARCH_LIST, &len);
            if(payload && (len >= 4))
            {
                for(i = 0; i < (len / 4); i++)
                {
                    temp = (payload[0]);
                    temp = (temp << 5);
                    temp |= (payload[1] >> 3);
                    payload += 4;
                    if(temp > 0 && p_scan_judge_freq_valid(temp))
                    {
                        D_SI_ALLOC(hmm, fendnode);
                        if(!fendnode)
                        {
                            return D_ERR;
                        }
                        fendnode->fendparam.dtmb.freq = temp;

                        D_SI_LIST_ADD(scan_group->scanFendParamList, fendnode);
                        scan_group->scanFendParamList_cnt++;
                    }
                }
            }
            else
            {
                D_SI_ALLOC(hmm, fendnode);
                if(!fendnode)
                {
                    return D_ERR;
                }

                fendnode->fendparam.dtmb.freq = 0;
                D_SI_LIST_ADD(scan_group->scanFendParamList, fendnode);
                scan_group->scanFendParamList_cnt++;
            }
        }
    }
    else
    {
        D_ERROR("%s:   Error : scan_type %d\n", __FUNCTION__, as_config->scan_type);
    }

    /*��¼����*/
    *group_cnt = group_id;

    return D_OK;
}


/** @brief������������������ݿ⡣*/
static D_Result dvbt_auto_scan_store(D_ASGroup **group, D_U32 group_cnt, D_ScanTaskConfig *as_config)
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

    /*��ÿ�������������б���*/
    groupid = 0;
    scan_group = group[groupid];

    if(g_custom_config.scan.adelete == 1)
    {
        //===
    }
    else
    {
        /*����������Ŀʱ����ɾ��ԭ�н�Ŀ*/
        if(scan_group->scanResult.scan_tsinfo_cnt == 0 || (scan_group->scanResult.tv_cnt + scan_group->scanResult.radio_cnt) <= 0)
        {
            return D_OK;
        }
    }

    p_conf_get_si_param(&si_param);

    d_dbase_set_rset_en(0);

	d_dbase_clear_evt ();
	d_dbase_clear_bouq();

	/*����ҲԤ�����ӹ㲥֮��Ľ�Ŀ����atv��������ﲻ��ɾ������
	��clear srv����ɾ����Ŀʱ����ɾ���˽�Ŀ��Ԥ����¼��qiny*/
	//d_dbase_clear_subscribe ();
	//clear srv
	d_dbase_clear_srv_by_type(D_DB_SRV_ACTION_TV | D_DB_SRV_ACTION_RADIO);
	d_dbase_delete_ts_by_type(D_FEND_DTMB);

#if DVBT_DEAL_SAME_TS_PROG_ENABLE
    /*dtmb������������Ƶ�����Ŀ��Ϣ��@qiny 2015.11.10*/
    //if(as_config->scan_type == STB_SCAN_TYPE_FULL)
    {
        check_data_before_save(scan_group, as_config);
    }
#endif

    db_ts_id = (D_DBTSID*)SCAN_MEM_ALLOC(sizeof(D_DBTSID) * scan_group->scanResult.scan_tsinfo_cnt);
    if(scan_group->scanResult.scan_tsinfo_cnt && db_ts_id)
    {
        memset(db_ts_id, 0xff, sizeof(D_DBTSID) * scan_group->scanResult.scan_tsinfo_cnt);

        /*�洢Ƶ����Ϣ*/
        D_SI_FOR_EACH_BEGIN(D_ScanTsInfoNode, scan_group->scanResult.scan_tsinfo_list, scants)
        if(scants->valid && (scants->ts_no < scan_group->scanResult.scan_tsinfo_cnt) && ((scants->ts_info.tv_cnt + scants->ts_info.radio_cnt) > 0))
        {
            D_DB_TS_INFO_INIT(&ts_info);
            D_SCANTSINFO_TO_DBSRVINFO(&ts_info, &(scants->ts_info));
            ts_info.db_net_id = as_config->db_net_id;
            ts_info.tuner_type = scan_group->fend_type;
            ts_info.db_sat_id = (D_U8) - 1;

            /*����Ƶ����Ϣ*/
            dbid = d_dbase_get_ts_by_param (as_config->db_net_id, scan_group->fend_type, &ts_info.param);
            if (-1 != dbid)
            {
                /*����Ƶ����Ϣ*/
                p_dbase_updata_ts_info(dbid, &ts_info);
            }
            else
            {
                /*���Ƶ�㣬������Ƶ���¼����Ϣ*/
                dbid = p_dbase_insert_ts (&ts_info);
            }

            /*ÿ��Ƶ�������ݿ����id*/
            db_ts_id[scants->ts_no] = dbid;

            D_DUMP("[scan] add ts -> dbtsid: %03d tsid: 0x%04x orgnetid: 0x%04x freq: %d\n", dbid, ts_info.ts_id, ts_info.org_net_id, ts_info.param.freq);
#ifdef D_CA_SUPPORT_XGCA
            /*�¹������Ƶ��*/
            if(0x0001 == ts_info.ts_id)
            {
                si_param.main.freq = ts_info.param.freq;
                p_conf_set_si_param(&si_param);
            }
#endif
        }
        D_SI_FOR_EACH_END(D_ScanTsInfoNode, scan_group->scanResult.scan_tsinfo_list, scants);

        /*����ҵ��Ⱥ��Ϣ*/
        for(idx = 0; idx < scan_group->scanResult.bouq_cnt; idx++)
        {
            dbid = d_dbase_insert_bouq (scan_group->scanResult.bouq_info[idx]);
            db_bouq_id[idx] = dbid;
        }

        /*�����н�Ŀ��������*/
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

        /*�������н�Ŀ*/
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
                si_param.main.freq = scan_group->scanResult.main_fparam.freq;
            }
#endif
        }

#ifdef D_STB_SUPPORT_HAIER_PROGRAM_VERSION
        if(scan_prog_version != 0xFFFF)
        {
            si_param.nit_version = scan_prog_version;
        }
#else
        si_param.nit_version = scan_group->scanResult.nit_version;
#endif
        p_conf_set_si_param(&si_param);
    }

    d_dbase_flush();

    return D_OK;
}

static D_Result dvbt_auto_scan_destroy (D_ASGroup **group, D_U32 group_cnt, D_ScanTaskConfig *as_config)
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
        //��������
    }

    return D_OK;
}


D_AutoScanOp DVBT_AutoScan_Op =
{
    dvbt_auto_scan_init,
    dvbt_auto_scan_store,
    dvbt_auto_scan_destroy
};





/*˽�г�ʼ��*/
static D_Result dvbt_group_start (D_ASGroup *scan_group, D_ScanTaskConfig *as_config, D_HMMan hmm)
{
    return D_OK;
}

/*˽�з���ʼ��*/
static D_Result dvbt_group_end(D_ASGroup *scan_group, D_ScanTaskConfig *as_config)
{
    return D_OK;
}

/*���ca_sys_id�Ƿ���϶���Ҫ��*/
static D_Bool dvbt_check_ca_sys_id (D_U32 type, D_U16 ca_sys_id)
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

/*���ҵ��Ⱥid �Ƿ���϶���Ҫ��*/
static D_Bool dvbt_check_bouq_id (D_U32 type, D_U16 bouq_id)
{
    return D_TRUE;
}


/*�������Ƿ���϶���Ҫ��*/
static D_Bool dvbt_check_srvice (D_U32 type, D_ScanSrvInfo *srvinfo)
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
    else/*�Ǽ��Ž�Ŀ*/
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

/*sdt������ȡ������Ϣ*/
static D_Result dvbt_get_private_descrs_info_in_sdt(D_U32 type, D_Descr *descr, D_ScanSrvInfo *srv_info)
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

/*bat������ȡ������Ϣ*/
static D_Result dvbt_get_srvinfo_in_bat(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srv_info, D_ScanResultValue *result)
{
    return D_OK;
}


/*nit������ȡ������Ϣ*/
static D_Result dvbt_get_srvinfo_in_nit(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srv_info, D_ScanResultValue *result)
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

/*����˽�б�����ȡ������Ϣ*/
static D_Result dvbt_get_srvinfo_in_others(D_U32 type, D_ScanTsInfoNode *scants, D_ScanSrvInfo *srv_info, D_ScanResultValue *result)
{
    return D_OK;
}


/*��Ƶ����������*/
static D_Result dvbt_set_tpsiscan_config(D_ASGroup *scan_group, D_TpSiScanTaskConfig *conf)
{
    conf->pat_timeout = DVBT_PAT_TIMEOUT;
    conf->pmt_timeout = DVBT_PMT_TIMEOUT;
    conf->cat_timeout = DVBT_CAT_TIMEOUT;
    conf->bat_timeout = DVBT_BAT_TIMEOUT;
    conf->nit_timeout = DVBT_NIT_TIMEOUT;
    conf->sdt_timeout = DVBT_SDT_TIMEOUT;
    conf->sdt_oth_timeout = DVBT_SDT_OTH_TIMEOUT;

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

/*nit������ȡƵ���б���Ϣ*/
D_Result dvbt_get_freqlist_in_nit(D_U32 type, D_ScanTsInfoNode *scants, D_FEndParam*fparam, D_U32 *fcnt)
{
    D_NitTS *ts;
    D_Descr *descr;
    D_Nit      *nit;
    D_FEndParam param;

    if(!scants || !scants->scantp || !scants->scantp->nits || !fparam || !fcnt)
    {
        return D_ERR;
    }

    //if(scan_group->group_type == D_GROUP_TYPE_DVBT)
    {
        D_SI_FOR_EACH_BEGIN (D_Nit, scants->scantp->nits, nit)
        D_SI_FOR_EACH_BEGIN (D_NitTS, nit->tses, ts)

        memset(&param, 0x00, sizeof(D_FEndParam));

        D_SI_FOR_EACH_BEGIN (D_Descr, ts->descrs, descr)
        switch (descr->tag)
        {
            case DESCR_TERR_DEL_SYS:/*����*/
                //if(scants->scantp->type == D_FEND_DVBT)
            {
                D_TerrestrialDeliverySystemDescr*tds = (D_TerrestrialDeliverySystemDescr*) descr;

                memset(&param, 0x00, sizeof(D_FEndParam));
                param.dtmb.freq = tds->freq / 100000;
                param.dtmb.freq_k = (tds->freq / 10000) % 10;
                //param.dvbt.BandWidth = (tds->band == 0)? 8 : 7;
                D_DUMP("[AutoScan] nit DESCR_TERR_DEL_SYS find freq:%d\n", param.freq);
                if ((param.freq >= MIN_SEARCH_FERQ_T) && (param.freq <= MAX_SEARCH_FREQ_T) && p_scan_judge_freq_valid(param.freq) )
                {
                    if((*fcnt) < D_SCAN_GROUP_MAX_TP_CNT)
                        fparam[(*fcnt)++] = param;
                }
            }
            break;
            case DESCR_CABLE_DEL_SYS:/*����*/
                //if(scants->scantp->type == D_FEND_DVBC)
            {
                D_CableDeliverySystemDescr *cds = (D_CableDeliverySystemDescr*) descr;

                memset(&param, 0x00, sizeof(D_FEndParam));
                param.dtmb.freq = cds->freq / 10000;
                param.dtmb.freq_k = (cds->freq / 1000) % 10;
                D_DUMP("[AutoScan] nit CABLE_DEL_SYS find freq:%d\n", param.freq);
                if ((param.freq >= MIN_SEARCH_FERQ_T) && (param.freq <= MAX_SEARCH_FREQ_T) && p_scan_judge_freq_valid(param.freq))
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

/*��ȡƵ���Ϲ��ĵ�һЩ��Ϣ, �����Ŀ�汾�ŵ�*/
D_Result dvbt_get_tp_info(D_U32 type, D_ScanTsInfoNode *scants, D_ScanResultValue *scanResult)
{
    if(scants && (scants->scantp) && (scants->scantp->nits))
    {
        D_Nit *nit;
        D_NitTS *tses;
        D_Descr *descr;

        scants->ts_info.version = ((D_Nit*)(scants->scantp->nits))->version;

        D_SI_FOR_EACH_BEGIN(D_Nit, scants->scantp->nits, nit)
        /*��һ��������ѭ��*/
        D_SI_FOR_EACH_BEGIN(D_Descr, nit->descrs, descr)

#ifdef D_STB_SUPPORT_HAIER_PROGRAM_VERSION
        if(P_DESCR_HAIER_PROGRAM_VERSION_TAG == descr->tag)
        {
            /*ʹ��˽��������İ汾 @qiny 2016.04.15*/
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

            if(match_flag == D_TRUE && scan_prog_version == 0xFFFF)
            {
                scan_prog_version = puDescr->version;
            }
        }
#endif
        D_SI_FOR_EACH_END(D_Descr, nit->descrs, descr)
#if 0
        /*�ڶ���������ѭ��*/
        D_SI_FOR_EACH_BEGIN(D_NitTS, nit->tses, tses)
        D_SI_FOR_EACH_BEGIN (D_Descr, tses->descrs, descr)

        D_SI_FOR_EACH_END (D_Descr, tses->descrs, descr)
        D_SI_FOR_EACH_END(D_NitTS, nit->tses, tses)
#endif
        D_SI_FOR_EACH_END(D_Nit, scants->scantp->nits, nit)

    }
    return D_OK;
}

#if 0
static D_Result dvbt_group_end_private_op(D_ASGroup *scan_group, D_HMMan hmm)
{
    return D_OK;
}
#endif

/*DVBT �Զ���������*/
static D_ASGroupOp DVBT_AutoScanGroup_Op =
{
    dvbt_group_start,
    dvbt_group_end,
    dvbt_set_tpsiscan_config,
    dvbt_check_ca_sys_id,
    dvbt_check_bouq_id,
    NULL,                   //dvbt_group_end_private_op,
    dvbt_get_freqlist_in_nit,
    dvbt_get_tp_info,
    dvbt_get_private_descrs_info_in_sdt,
    dvbt_get_srvinfo_in_bat,
    dvbt_get_srvinfo_in_nit,
    dvbt_get_srvinfo_in_others,
    dvbt_check_srvice
};






/*˽�г�ʼ��, �Ը�����з��䲢��ʼ������Ҫ�趨����������Ƶ���б���ʱ��������û����*/
static D_Result dvbt_manual_scan_init(D_U32 type, D_ScanTaskConfig *ms_config)
{
    scan_prog_version = 0xFFFF;
    AllTVChanLcnStatus = 0;
    AllRadioChanLcnStatus = 0;
    return D_OK;
}

/*��ʼ�����û��ص�����ʱ�����Ѿ�������������ص�ʱִ��*/
static D_Result dvbt_manual_scan_start(D_U32 type, D_ScanTaskConfig *ms_config)
{
    return D_OK;
}

static D_Result dvbt_manual_scan_store(D_U32 type, D_ScanTaskConfig *ms_config, D_ScanResultValue*ms_result)
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
        /*����������Ŀʱ����ɾ��ԭ�н�Ŀ*/
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

    /*����Ƶ����Ϣ*/
    db_ts_id = d_dbase_get_ts_by_param (ms_result->db_net_id, ms_result->fend_type, &scants->ts_info.param);
    if (-1 != db_ts_id)
    {
        /*ɾ����ǰƵ����ԭ�еĽ�Ŀ��������Ƶ����Ϣ*/
        d_dbase_delete_srvs_of_ts(db_ts_id);
        p_dbase_updata_ts_info(db_ts_id, &ts_info);
    }
    else
    {
        /*���Ƶ�㣬������Ƶ���¼����Ϣ*/
        db_ts_id = p_dbase_insert_ts (&ts_info);
        d_dbase_get_ts_total_num();
    }

    if(db_ts_id == -1)
    {
        D_ERROR ("[ManualScan] db_ts_id == -1 !!!\n");
        return D_ERR;
    }
#ifdef D_CA_SUPPORT_XGCA
    /*�¹������Ƶ��*/
    if(0x0001 == ts_info.ts_id)
    {
        D_SIParam si_param;
        p_conf_get_si_param(&si_param);
        si_param.main.freq = ts_info.param.freq;
        p_conf_set_si_param(&si_param);
    }
#endif

    D_DUMP("[scan] add ts -> dbtsid: %03d tsid: 0x%04x orgnetid: 0x%04x freq: %d\n", db_ts_id, ts_info.ts_id, ts_info.org_net_id, ts_info.param.freq);

    /*����ҵ��Ⱥ��Ϣ*/
    for(idx = 0; idx < ms_result->bouq_cnt; idx++)
    {
        dbid = d_dbase_insert_bouq (ms_result->bouq_info[idx]);
        db_bouq_id[idx] = dbid;
    }

    /*�����н�Ŀ��������*/
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
    /*�������н�Ŀ*/
    save_type_service((D_ScanSrvInfoNode *)ms_result->srvList_tv, &db_ts_id, 1, db_bouq_id, ms_result->bouq_cnt);
    save_type_service((D_ScanSrvInfoNode *)ms_result->srvList_radio, &db_ts_id, 1, db_bouq_id, ms_result->bouq_cnt);

#if 1 //ndef D_CA_SUPPORT_DSCA
    /*�����н�Ŀ����*/
    p_scan_sort_all_srv(D_DB_SRV_TV, mode, D_FALSE);
    p_scan_sort_all_srv(D_DB_SRV_RADIO, mode, D_FALSE);
#endif
    d_dbase_flush();

    return D_OK;
}


static D_Result dvbt_manual_scan_destroy(D_U32 type, D_ScanTaskConfig *ms_config, D_ScanResultValue*ms_result)
{
    return D_OK;
}


/*��Ƶ����������*/
static D_Result dvbt_manual_scan_set_tpsiscan_config(D_U32 type, D_TpSiScanTaskConfig *conf)
{
    conf->pat_timeout = DVBT_PAT_TIMEOUT;
    conf->pmt_timeout = DVBT_PMT_TIMEOUT;
    conf->cat_timeout = DVBT_CAT_TIMEOUT;
    conf->bat_timeout = DVBT_BAT_TIMEOUT;
    conf->nit_timeout = DVBT_NIT_TIMEOUT;
    conf->sdt_timeout = DVBT_SDT_TIMEOUT;
    conf->sdt_oth_timeout = DVBT_SDT_OTH_TIMEOUT;
    conf->network_id = 0;
    conf->lock_enable = D_FALSE;
    conf->table_mask = 0;

    conf->table_mask |= TABLE_MASK_PAT | TABLE_MASK_PMT  | TABLE_MASK_SDT/* | TABLE_MASK_NIT*/;

    return D_OK;
}





/*ֱ�����ֶ�����������*/
D_ManualScanOp DVBT_ManualScan_Op =
{
    dvbt_manual_scan_init,
    dvbt_manual_scan_start,
    dvbt_manual_scan_store,
    dvbt_manual_scan_destroy,
    dvbt_manual_scan_set_tpsiscan_config,
    dvbt_check_ca_sys_id,
    dvbt_check_bouq_id,
    dvbt_get_tp_info,
    dvbt_get_private_descrs_info_in_sdt,
    dvbt_get_srvinfo_in_bat,
    dvbt_get_srvinfo_in_nit,
    dvbt_get_srvinfo_in_others,
    dvbt_check_srvice
};





