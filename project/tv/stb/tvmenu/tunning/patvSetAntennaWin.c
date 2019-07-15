/**@file patvSetAntennaWin.c
*@brief 设置卫星天线
*@author 刘军鸿
*@copyright Haier-IC
*@date 2018-04-24  刘军鸿 操作说明
*@note 注解
*/
#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "pConfig.h"
#include "pStbAtvMenus.h"
#include "pMem.h"
#include "pDBaseDefault.h"
#include "pTs2net.h"
#include "set_antenna_window.c"

#define D_TIMEOUT_FEND (250)

#define D_SATELLITE_NUM_MAX 1
#define D_SATELLITE_NAME_LEN 32//D_DB_SATE_NAME_LEN
#define D_TRANSPONDER_NUM_MAX (256)
#define TEXT_BUFF_LEN (24)
#define D_LNB_TYPE_NUM_MAX  15//P_DB_MAX_ANTE_CNT
#define D_LNB_NAME_LEN (24)

#define D_COLOR_RED atv_COLOR_ENUM_96
#define D_COLOR_GREEN atv_COLOR_ENUM_34
#define D_COLOR_BLUE atv_COLOR_ENUM_108
static D_ID cur_db_sat_id = -1;
static D_ID cur_db_ts_id = -1;

typedef struct
{
    D_DBRecset sateRset;
    D_ID db_sat_id[D_SATELLITE_NUM_MAX];
    D_Char  SatName[D_SATELLITE_NUM_MAX][D_SATELLITE_NAME_LEN + 12];
    D_Char  *SatContent[D_SATELLITE_NUM_MAX];
    D_U16   sate_cnt;
    D_U16   curr_sate;
    D_DBRecset tpRset;
    D_ID db_tp_id[D_TRANSPONDER_NUM_MAX];
    D_Char  TpName[D_TRANSPONDER_NUM_MAX][TEXT_BUFF_LEN];
    D_Char  * TpContent[D_TRANSPONDER_NUM_MAX];
    D_U16   tp_cnt;
    D_U16   curr_tp;
    D_Char  LNBName[D_LNB_TYPE_NUM_MAX][D_LNB_NAME_LEN];
    D_Char  * LNBContent[D_LNB_TYPE_NUM_MAX];
    D_U8    lnb_cnt;
    D_Char curr_lnb;
    D_ID db_ant_id[D_LNB_TYPE_NUM_MAX];
    D_U8  ku_doubble[D_LNB_TYPE_NUM_MAX];
    D_U8   old_22k;
    D_DBRecset AntRset;

    D_Char  strenth[8];
    D_Char  quality[8];
    D_Bool      change_enable;

    D_HFMan hfman;
    D_HTimer htimer;
    D_DBSateInfo sateinfo;
    D_DBAnteInfo anteinfo;
    D_DBTSInfo tsinfo;
    D_Bool  set_param_flag;  /*是否已经设定过频点参数*/
} D_FixedAntennaSetMenuData;

static D_FixedAntennaSetMenuData  *FixedAntennaSet_Data = NULL;

static D_Result
start_single_satellite_scan(D_U32 mode) D_FUNCPOSTFIT
{
    P_ScanConfig scanConf = {0};
    D_DBTSInfo tsinfo;
    D_S16 val;

    if(mode)
    {
        scanConf.mode = STB_SCAN_MODE_BLIND;
        scanConf.type = STB_SCAN_TYPE_SINGLE_SATELLITE;
    }
    else
    {
        d_dbase_get_ts_info(FixedAntennaSet_Data->tpRset.ids[FixedAntennaSet_Data->curr_tp], &tsinfo);
        scanConf.mode = STB_SCAN_MODE_OTHERS;
        scanConf.type = STB_SCAN_TYPE_TP;
        scanConf.fendparam = tsinfo.param;
    }

    scanConf.freeFlag = (D_U32)D_TRUE;
    scanConf.progType = STB_SCAN_PROG_TYPE_TV_RADIO;
    scanConf.netFlag = D_FALSE;
    scanConf.fendtype = D_FEND_DVBS;
    scanConf.valid = D_TRUE;
    scanConf.satelliteNo = FixedAntennaSet_Data->sateRset.ids[FixedAntennaSet_Data->curr_sate];
    p_atv_dvbs_scan_window_show (&scanConf);
    return D_OK;
}

/** @brief取得卫星信息*/
static D_Result
get_satellite_info(void) D_FUNCPOSTFIT
{
    D_ID idx;
    D_DBSateInfo sateinfo;
    D_Result ret;

    d_dbase_rset_init(&FixedAntennaSet_Data->sateRset, D_SATELLITE_NUM_MAX, FixedAntennaSet_Data->db_sat_id);
    d_dbase_get_sates_selected(&FixedAntennaSet_Data->sateRset);

    FixedAntennaSet_Data->sate_cnt = (D_U16)(FixedAntennaSet_Data->sateRset.cnt);
    FixedAntennaSet_Data->curr_sate = 0;
    for(idx = 0; idx < FixedAntennaSet_Data->sate_cnt; idx++)
    {
        if(cur_db_sat_id == FixedAntennaSet_Data->sateRset.ids[idx])
        {
            FixedAntennaSet_Data->curr_sate = idx;
        }
        ret = d_dbase_get_sat_info(FixedAntennaSet_Data->sateRset.ids[idx], &sateinfo);
        FixedAntennaSet_Data->SatContent[idx] = FixedAntennaSet_Data->SatName[idx];
        if(D_OK == ret)
        {
            snprintf(FixedAntennaSet_Data->SatName[idx], (D_SATELLITE_NAME_LEN + 10), "(%d/%d) %s", (idx + 1), FixedAntennaSet_Data->sate_cnt, sateinfo.sate_name);
        }
        else
        {
            snprintf(FixedAntennaSet_Data->SatName[idx], (D_SATELLITE_NAME_LEN + 10), "(%d/%d) %s", (idx + 1), FixedAntennaSet_Data->sate_cnt, "####");
        }
    }
    return D_OK;
}

/** @brief取得LNB频率信息*/
static D_Result
get_lnbfreq_info(void) D_FUNCPOSTFIT
{
    D_DBAnteInfo anteinfo;
    D_Result ret;
    D_ID idx;

    d_dbase_rset_init(&FixedAntennaSet_Data->AntRset, D_LNB_TYPE_NUM_MAX, FixedAntennaSet_Data->db_ant_id);
    d_dbase_get_antes(&FixedAntennaSet_Data->AntRset);
    FixedAntennaSet_Data->lnb_cnt = (D_U8)(FixedAntennaSet_Data->AntRset.cnt);

    for(idx = 0; idx < FixedAntennaSet_Data->lnb_cnt; idx++)
    {
        ret = d_dbase_get_ante_info(FixedAntennaSet_Data->AntRset.ids[idx], &anteinfo);
        FixedAntennaSet_Data->LNBContent[idx] = FixedAntennaSet_Data->LNBName[idx];
        FixedAntennaSet_Data->ku_doubble[idx] = 0;

        if((anteinfo.freq2 != 0) && (anteinfo.freq1 != 0))
        {
            if((anteinfo.freq2 >= 9000) && (anteinfo.freq1 >= 9000))
            {
                FixedAntennaSet_Data->ku_doubble[idx] = 1;
            }
            snprintf(FixedAntennaSet_Data->LNBName[idx] , D_LNB_NAME_LEN, "%d-%d", anteinfo.freq1, anteinfo.freq2);
        }
        else
        {
            snprintf(FixedAntennaSet_Data->LNBName[idx] , D_LNB_NAME_LEN, "%d",  (anteinfo.freq1) ? anteinfo.freq1 : anteinfo.freq2);
        }
    }

    return D_OK;
}

/** @brief取得当前卫星下的转发器信息*/
static D_Result
get_transponder_info(D_U32 action) D_FUNCPOSTFIT
{
    D_ID idx;
    D_DBTSInfo tsinfo;
    D_Result ret;

    if(action == 0)
    {
        d_dbase_rset_empty(&FixedAntennaSet_Data->tpRset);
        d_dbase_get_ts_by_sat(&FixedAntennaSet_Data->tpRset, FixedAntennaSet_Data->sateRset.ids[FixedAntennaSet_Data->curr_sate]);
    }

    FixedAntennaSet_Data->tp_cnt = (D_U16)(FixedAntennaSet_Data->tpRset.cnt);

    for(idx = 0; idx < FixedAntennaSet_Data->tp_cnt; idx++)
    {
        if(cur_db_ts_id == FixedAntennaSet_Data->tpRset.ids[idx])
        {
            FixedAntennaSet_Data->curr_tp = idx;
        }
        ret = d_dbase_get_ts_info(FixedAntennaSet_Data->tpRset.ids[idx], &tsinfo);
        FixedAntennaSet_Data->TpContent[idx] = FixedAntennaSet_Data->TpName[idx];
        if(D_OK == ret)
        {
            snprintf(FixedAntennaSet_Data->TpName[idx], TEXT_BUFF_LEN, "(%d/%d) %d%s%d", (idx + 1), FixedAntennaSet_Data->tp_cnt, tsinfo.param.dvbs.freq, (tsinfo.param.dvbs.pol == D_FEND_HOR_POL) ? "H" : "V", tsinfo.param.dvbs.baud);
        }
        else
        {
            snprintf(FixedAntennaSet_Data->TpName[idx], TEXT_BUFF_LEN, "(%d/%d) %s", (idx + 1), FixedAntennaSet_Data->tp_cnt, "####");
        }
    }

    /*没有转发器时，显示"0/0"*/
    if( FixedAntennaSet_Data->tp_cnt == 0)
    {
        sprintf (FixedAntennaSet_Data->TpName[0], "(0/0)");
        FixedAntennaSet_Data->TpContent[0] = FixedAntennaSet_Data->TpName[0];
        FixedAntennaSet_Data->tpRset.ids[0] = -1;
    }

    return D_OK;
}

/**@brief 保存当前混合天线菜单设置参数*/
static D_Result
restore_fixed_antenna_set(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &set_antenna_window;
    D_Visual *vis;
    D_U16  val;
    D_DBSateInfo sateinfo;
    D_ID dbid;

    dbid = FixedAntennaSet_Data->sateRset.ids[FixedAntennaSet_Data->curr_sate];
    d_dbase_get_sat_info(dbid, &sateinfo);
    vis = d_frame_get_control(frm, ID_LNB_FREQ_SELECT);
    if(vis)
    {
        val = (D_U16)d_select_box_get_val(vis);
        sateinfo.antenna_slot = FixedAntennaSet_Data->AntRset.ids[val];
    }

    vis = d_frame_get_control(frm, ID_22K_SELECT);
    if(vis)
    {
        val = (D_U16)d_select_box_get_val(vis);
        sateinfo.diseqc_22k = (D_U8)val;
    }
    sateinfo.diseqc_12v = (D_Bool)0;
    sateinfo.diseqc_port = (D_U8)0;
    d_dbase_update_sat_param(dbid, &sateinfo, D_TRUE);
    return D_OK;
}

/*显示信号信息(强度与质量)*/
static D_Result
show_signal_status(D_Bool locked, D_U8 strength, D_U8 quality)
{
    D_Frame *frm = &set_antenna_window;
    D_Visual    *vis;
    D_U16   frontcolorid;

    strength = D_MIN(strength, 100);
    quality = D_MIN(quality, 100);

    frontcolorid = (locked) ? D_COLOR_BLUE : D_COLOR_RED;
    vis = d_frame_get_control (frm, ID_TP_PROGRESS_S);
    if (vis)
    {
        d_progress_bar_set_front_colour(vis, frontcolorid);
        d_progress_bar_set_val(vis, strength);
    }

    frontcolorid = (locked) ? D_COLOR_GREEN : D_COLOR_RED;
    vis = d_frame_get_control (frm, ID_TP_PROGRESS_Q);
    if (vis)
    {
        d_progress_bar_set_front_colour(vis, frontcolorid);
        d_progress_bar_set_val(vis, quality);
    }
    vis = d_frame_get_control (frm, ID_TP_LABEL_SVAL);
    if (vis)
    {
        sprintf (FixedAntennaSet_Data->strenth, "%d%%", strength);
        d_label_set_text(vis, FixedAntennaSet_Data->strenth);
    }

    vis = d_frame_get_control (frm, ID_TP_LABEL_QVAL);
    if (vis)
    {
        sprintf (FixedAntennaSet_Data->quality, "%d%%", quality);
        d_label_set_text(vis, FixedAntennaSet_Data->quality);
    }

    return D_OK;
}

/** @brief  显示卫星相关参数信息*/
static D_Result
satellite_info_show(void)
{
    D_Frame *frm = &set_antenna_window;
    D_Visual    *vis;
    D_DBSateInfo sateinfo;
    D_ID idx;

    FixedAntennaSet_Data->curr_lnb = 0;
    FixedAntennaSet_Data->curr_tp = 0;
    FixedAntennaSet_Data->set_param_flag = D_FALSE;

    d_dbase_get_sat_info(FixedAntennaSet_Data->sateRset.ids[FixedAntennaSet_Data->curr_sate], &sateinfo);
    get_transponder_info(0);
    for(idx = 0; idx < FixedAntennaSet_Data->AntRset.cnt; idx++)
    {
        if(sateinfo.antenna_slot == FixedAntennaSet_Data->AntRset.ids[idx])
        {
            FixedAntennaSet_Data->curr_lnb = idx;
            break;
        }
    }

    for(idx = 0; idx < FixedAntennaSet_Data->tp_cnt; idx++)
    {
        if(cur_db_ts_id == FixedAntennaSet_Data->tpRset.ids[idx])
        {
            FixedAntennaSet_Data->curr_tp = idx;
            break;
        }
    }

    vis = d_frame_get_control(frm, ID_LNB_FREQ_SELECT);
    if(vis)
    {
        d_select_box_set_val(vis, FixedAntennaSet_Data->curr_lnb);
    }

    vis = d_frame_get_control(frm, ID_TRANSPONDER_LIST_SELECT);
    if(vis)
    {
        d_select_box_set_content(vis, FixedAntennaSet_Data->TpContent, D_MAX(FixedAntennaSet_Data->tp_cnt, 1));
        d_select_box_set_val(vis, FixedAntennaSet_Data->curr_tp);
    }

    vis = d_frame_get_control(frm, ID_22K_SELECT);
    if(vis)
    {
        if(FixedAntennaSet_Data->ku_doubble[FixedAntennaSet_Data->curr_lnb])
        {
            FixedAntennaSet_Data->old_22k = OFF_22K;
            sateinfo.diseqc_22k = AUTO_22K;
            d_select_box_set_content(vis, NULL, 3);
            d_select_box_set_val(vis, sateinfo.diseqc_22k);
            d_vis_enable(vis, D_FALSE);
        }
        else
        {
            sateinfo.diseqc_22k = (sateinfo.diseqc_22k >= AUTO_22K) ? OFF_22K : sateinfo.diseqc_22k;
            FixedAntennaSet_Data->old_22k = sateinfo.diseqc_22k;
            d_select_box_set_content(vis, NULL, 2);
            d_select_box_set_val(vis, sateinfo.diseqc_22k);
            d_vis_enable(vis, D_TRUE);
        }
    }
    show_signal_status(0, 0, 0);

    /*进行信号设定，进行锁频*/
    FixedAntennaSet_Data->sateinfo = sateinfo;
    d_dbase_get_ante_info(sateinfo.antenna_slot, &(FixedAntennaSet_Data->anteinfo));

    if(D_OK != d_dbase_get_ts_info(FixedAntennaSet_Data->tpRset.ids[FixedAntennaSet_Data->curr_tp], &(FixedAntennaSet_Data->tsinfo)))
    {
        /*无转发器时使用一个无效的数据*/
        memset(&(FixedAntennaSet_Data->tsinfo), 0x00, sizeof(D_DBTSInfo));
    }

    if(FixedAntennaSet_Data->hfman != D_INVALID_HANDLE)
    {
        if(FixedAntennaSet_Data->tp_cnt)
        {
            FixedAntennaSet_Data->set_param_flag = D_TRUE;
        }
        d_fman_set_param(FixedAntennaSet_Data->hfman, &(FixedAntennaSet_Data->tsinfo.param), D_FALSE, D_FEND_DVBS, &sateinfo, &(FixedAntennaSet_Data->anteinfo));
        d_fman_get_status_req(FixedAntennaSet_Data->hfman, d_gui_get_queue());
    }

    return D_OK;
}

/** @brief  设定前端设备参数，进行锁频*/
static D_Result
set_fend_param(D_Visual *vis) D_FUNCPOSTFIT
{
    D_Frame * frm = &set_antenna_window;
    D_U16 val;
    D_ID visid;

    visid = d_frame_get_control_id(frm, vis);
    val = (D_U16)d_select_box_get_val(vis);
    switch(visid)
    {
        case ID_LNB_FREQ_SELECT:
            FixedAntennaSet_Data->sateinfo.antenna_slot = FixedAntennaSet_Data->AntRset.ids[val];
            d_dbase_get_ante_info(FixedAntennaSet_Data->AntRset.ids[val], &(FixedAntennaSet_Data->anteinfo));
            break;
        case ID_TRANSPONDER_LIST_SELECT:
            d_dbase_get_ts_info(FixedAntennaSet_Data->tpRset.ids[val], &(FixedAntennaSet_Data->tsinfo));
            break;
        case ID_22K_SELECT:
            FixedAntennaSet_Data->sateinfo.diseqc_22k = (D_U8)val;
            break;
        default:
            break;
    }

    FixedAntennaSet_Data->sateinfo.diseqc_12v = (D_Bool)0;
    FixedAntennaSet_Data->sateinfo.diseqc_port = (D_U8)0;

    if(FixedAntennaSet_Data->hfman != D_INVALID_HANDLE)
    {
        FixedAntennaSet_Data->set_param_flag = D_TRUE;
        d_fman_set_param(FixedAntennaSet_Data->hfman, &(FixedAntennaSet_Data->tsinfo.param), D_FALSE, D_FEND_DVBS, &(FixedAntennaSet_Data->sateinfo), &(FixedAntennaSet_Data->anteinfo));
        d_fman_get_status_req(FixedAntennaSet_Data->hfman, d_gui_get_queue());
    }

    show_signal_status(0, 0, 0);

    return D_OK;
}

/** @brief  卫星选择框事件处理*/
static D_Result
select_satellite_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_SELECTED:
            restore_fixed_antenna_set();
            FixedAntennaSet_Data->curr_sate = d_select_box_get_val(vis);
            FixedAntennaSet_Data->change_enable = D_FALSE;
            satellite_info_show();
            FixedAntennaSet_Data->change_enable = D_TRUE;
            cur_db_sat_id = FixedAntennaSet_Data->sateRset.ids[FixedAntennaSet_Data->curr_sate];
            break;
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    //return p_select_box_show_list(vis);
                    break;
                default:
                    break;
            }
            break;
        case D_EVT_DESTROY:
            //p_select_box_hide_list(vis);
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief  lnb天线选择框事件处理*/
static D_Result
select_lnb_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &set_antenna_window;
    D_Visual    *svis;

    switch (evt->type)
    {
        case D_EVT_SELECTED:
            FixedAntennaSet_Data->curr_lnb = vis->element.select.val;
            if(FixedAntennaSet_Data->change_enable)
            {
                svis = d_frame_get_control(frm, ID_22K_SELECT);
                if(svis)
                {
                    if(FixedAntennaSet_Data->ku_doubble[FixedAntennaSet_Data->curr_lnb])
                    {
                        FixedAntennaSet_Data->sateinfo.diseqc_22k = AUTO_22K;
                        d_select_box_set_content(svis, NULL, 3);
                        d_select_box_set_val(svis, FixedAntennaSet_Data->sateinfo.diseqc_22k);
                        d_vis_enable(svis, D_FALSE);
                    }
                    else
                    {
                        FixedAntennaSet_Data->sateinfo.diseqc_22k = FixedAntennaSet_Data->old_22k;
                        d_select_box_set_val(svis, FixedAntennaSet_Data->old_22k);
                        d_select_box_set_content(svis, NULL, 2);
                        d_vis_enable(svis, D_TRUE);
                    }
                }
                set_fend_param(vis);
            }
            break;
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    //return p_select_box_show_list(vis);
                    break;
                default:
                    break;
            }
            break;
        case D_EVT_DESTROY:
            //p_select_box_hide_list(vis);
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief  转发器选择框事件处理*/
static D_Result
select_ts_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_SELECTED:
            FixedAntennaSet_Data->curr_tp = d_select_box_get_val( vis);
            cur_db_ts_id = FixedAntennaSet_Data->tpRset.ids[FixedAntennaSet_Data->curr_tp];
            if(FixedAntennaSet_Data->change_enable)
            {
                set_fend_param(vis);
            }
            break;
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    //return p_select_box_show_list(vis);
                    break;
                default:
                    break;
            }
            break;
        case D_EVT_DESTROY:
            //p_select_box_hide_list(vis);
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief  22k 事件处理*/
static D_Result
select_22k_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_SELECTED:
            if(vis->element.select.cnt < 3)
            {
                /*不是ku双本振时，修改后记录*/
                FixedAntennaSet_Data->old_22k = vis->element.select.val;
            }
            if(FixedAntennaSet_Data->change_enable)
            {
                set_fend_param(vis);
            }
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief  开始搜索事件处理*/
static D_Result
start_tp_scan_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            restore_fixed_antenna_set();
            start_single_satellite_scan(0);
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief  开始搜索事件处理*/
static D_Result
start_sate_scan_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            restore_fixed_antenna_set();
            start_single_satellite_scan(1);
            break;
        default:
            break;
    }
    return D_ERR;
}

static D_Result
tp_add_handler (D_FEndParam *fparam, D_U32 param) D_FUNCPOSTFIT
{
    D_Frame *frm = &set_antenna_window;
    D_Visual *vis;
    D_ID dbtsid;
    D_DBTSInfo tsinfo;
    D_U32 idx;
    D_Bool add = D_TRUE;

    if(FixedAntennaSet_Data)
    {
        for(idx = 0; idx < FixedAntennaSet_Data->tpRset.cnt; idx++)
        {
            d_dbase_get_ts_info(FixedAntennaSet_Data->tpRset.ids[idx], &tsinfo);
            if(D_OK == d_dbase_check_ts_dvbs(&(tsinfo.param), fparam))
            {
                add = D_FALSE;
                FixedAntennaSet_Data->curr_tp = idx;
                break;
            }
        }

        if(add)
        {
            D_DB_TS_INFO_INIT(&tsinfo);
            tsinfo.param = *fparam;
            tsinfo.db_sat_id = FixedAntennaSet_Data->sateRset.ids[FixedAntennaSet_Data->curr_sate];
            tsinfo.tuner_type = D_FEND_DVBS;
            tsinfo.db_net_id = D_DB_DEF_NET_ID;

            dbtsid = d_dbase_insert_ts_ex(&tsinfo, D_FALSE);
            if(dbtsid >= 0)
            {
                FixedAntennaSet_Data->tpRset.ids[FixedAntennaSet_Data->tpRset.cnt] = dbtsid;
                FixedAntennaSet_Data->tpRset.cnt++;
                get_transponder_info(1);
                FixedAntennaSet_Data->curr_tp = FixedAntennaSet_Data->tpRset.cnt - 1;
            }
        }

        vis = d_frame_get_control(frm, ID_TRANSPONDER_LIST_SELECT);
        if(vis)
        {
            if(add)
            {
                d_select_box_set_content(vis, FixedAntennaSet_Data->TpContent, D_MAX(FixedAntennaSet_Data->tp_cnt, 1));
            }
            d_select_box_set_val(vis, FixedAntennaSet_Data->curr_tp);
            set_fend_param(vis);
        }
    }
    return D_OK;
}

static D_Result
tp_edit_handler (D_FEndParam *fparam, D_U32 param) D_FUNCPOSTFIT
{
    D_Frame *frm = &set_antenna_window;
    D_Visual *vis;
    D_ID dbtsid = (D_ID)param;
    D_DBTSInfo tsinfo;

    if(FixedAntennaSet_Data)
    {
        if((D_OK == d_dbase_get_ts_info(dbtsid, &tsinfo)) && (D_ERR == d_dbase_check_ts_dvbs(&(tsinfo.param), fparam)))
        {
            tsinfo.param = *fparam;
            d_dbase_updata_ts_info(dbtsid, &tsinfo);
            get_transponder_info(1);
            vis = d_frame_get_control(frm, ID_TRANSPONDER_LIST_SELECT);
            if(vis)
            {
                d_select_box_set_content(vis, FixedAntennaSet_Data->TpContent, D_MAX(FixedAntennaSet_Data->tp_cnt, 1));
                set_fend_param(vis);
            }
        }
    }
    return D_OK;
}

static D_Result
tp_add_edit_start (D_Bool edit) D_FUNCPOSTFIT
{
    D_U32 param = 0;
    D_DBTSInfo tsinfo;
    D_FEndParam fparam = {0};

    if(edit)
    {
        param = (D_U32)FixedAntennaSet_Data->tpRset.ids[FixedAntennaSet_Data->curr_tp];
        d_dbase_get_ts_info(FixedAntennaSet_Data->tpRset.ids[FixedAntennaSet_Data->curr_tp], &tsinfo);
        fparam = tsinfo.param;
        p_atv_add_edit_tp_menu_show(edit, &fparam, tp_edit_handler, param);
    }
    else
    {
        p_atv_add_edit_tp_menu_show(edit, &fparam, tp_add_handler, param);
    }

    return D_OK;
}


/** @brief窗口 事件处理*/
static D_Result
set_fixed_antenna_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual    *list;
    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                case D_KEY_BACK:
                    restore_fixed_antenna_set();
                    d_gui_upper_menu();
                    break;
                case D_KEY_RED:
                    tp_add_edit_start(D_FALSE);
                    break;
                case D_KEY_GREEN:
                    tp_add_edit_start(D_TRUE);
                    break;
                default:
                    break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            if(evt->timer.htimer == FixedAntennaSet_Data->htimer)
            {
                return d_fman_get_status_req(FixedAntennaSet_Data->hfman, d_gui_get_queue());
            }
            break;
        case D_EVT_FEND_STATUS:
            if(evt->fend.hfman == FixedAntennaSet_Data->hfman && FixedAntennaSet_Data->set_param_flag == D_TRUE
               && evt->fend.param.freq == FixedAntennaSet_Data->tsinfo.param.freq)
            {
                return show_signal_status(evt->fend.status.locked, evt->fend.status.strength, evt->fend.status.quanlity);
            }
            break;
        case D_EVT_DESTROY:
            p_atv_add_edit_tp_menu_close();
            d_vis_unsubscribe_evt (vis);
            if(FixedAntennaSet_Data)
            {
                d_fman_set_fast_mode(FixedAntennaSet_Data->hfman, D_FALSE);
                if(FixedAntennaSet_Data->htimer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(FixedAntennaSet_Data->htimer);
                    FixedAntennaSet_Data->htimer = D_INVALID_HANDLE;
                }
                PROJECT_FREE(FixedAntennaSet_Data);
                FixedAntennaSet_Data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}



/** @brief 窗口初始化*/
D_Result
set_antenna_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual    *vis;

    FixedAntennaSet_Data = (D_FixedAntennaSetMenuData*)PROJECT_ALLOC(sizeof(D_FixedAntennaSetMenuData));
    if(!FixedAntennaSet_Data)
    {
        return D_ERR;
    }

#ifdef D_TV_SUPPORT_TS2NET
    ts2net_check_enable = D_FALSE;
    d_ts2net_close();
#endif

    /*因为有信号的锁定，要停播*/
    d_stb_stop_play();
    /*清除残留视频帧*/
    p_stb_player_clear_vid(0);

    memset(FixedAntennaSet_Data, 0x00, sizeof(D_FixedAntennaSetMenuData));
    FixedAntennaSet_Data->htimer = D_INVALID_HANDLE;
    FixedAntennaSet_Data->hfman = d_fman_get_handle_by_type(D_FEND_DVBS, 0);
    d_dbase_rset_init(&FixedAntennaSet_Data->tpRset, D_TRANSPONDER_NUM_MAX, FixedAntennaSet_Data->db_tp_id);
    d_dbase_rset_init(&FixedAntennaSet_Data->AntRset, D_LNB_TYPE_NUM_MAX, FixedAntennaSet_Data->db_ant_id);
    d_dbase_rset_init(&FixedAntennaSet_Data->sateRset, D_SATELLITE_NUM_MAX, FixedAntennaSet_Data->db_sat_id);

    /*如果没有卫星数据库，则预置*/
    d_dbase_get_antes(&FixedAntennaSet_Data->AntRset);
    d_dbase_get_sates(&FixedAntennaSet_Data->sateRset);
    if(FixedAntennaSet_Data->AntRset.cnt == 0 || FixedAntennaSet_Data->sateRset.cnt == 0)
    {
#ifdef HI_SOFT_TYPE_DVBS
        d_dbase_set_rset_en(0);
        d_dbase_add_default_data_dvbs();
        d_dbase_flush();
#endif
    }

    vis = d_frame_get_control(frm, ID_FIXED_ANTENNA_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        vis->evt_mask &= ~D_EVT_LEFT_RIGHT_KEY_MASK;
    }

    get_lnbfreq_info();
    get_satellite_info();

    vis = d_frame_get_control(frm, ID_SET_FIXED_ANTENNA_SELECT);
    if(vis)
    {
        d_select_box_set_content(vis, FixedAntennaSet_Data->SatContent, FixedAntennaSet_Data->sate_cnt);
        d_select_box_set_val(vis, FixedAntennaSet_Data->curr_sate);
        /*注册按键事件*/
        d_vis_subscribe_evt (vis, D_EVT_OK_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, select_satellite_handler);
    }

    vis = d_frame_get_control(frm, ID_LNB_FREQ_SELECT);
    if(vis)
    {
        d_select_box_set_content(vis, FixedAntennaSet_Data->LNBContent, FixedAntennaSet_Data->lnb_cnt);
        /*注册按键事件*/
        d_vis_subscribe_evt (vis, D_EVT_OK_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, select_lnb_handler);
    }

    vis = d_frame_get_control(frm, ID_TRANSPONDER_LIST_SELECT);
    if(vis)
    {
        /*注册按键事件*/
        d_vis_subscribe_evt (vis, D_EVT_OK_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, select_ts_handler);
    }

    vis = d_frame_get_control(frm, ID_22K_SELECT);
    if(vis)
    {
        d_vis_set_handler (vis, select_22k_handler);
    }
    vis = d_frame_get_control(frm, ID_START_TP_SCAN);
    if(vis)
    {
        d_vis_set_handler (vis, start_tp_scan_handler);
    }
    vis = d_frame_get_control(frm, ID_START_SATE_SCAN);
    if(vis)
    {
        d_vis_set_handler (vis, start_sate_scan_handler);
    }

    FixedAntennaSet_Data->htimer = d_timer_create(NULL, D_TIMEOUT_FEND, d_gui_get_queue());

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_FEND_MASK, FixedAntennaSet_Data->hfman);
        if(FixedAntennaSet_Data->htimer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, FixedAntennaSet_Data->htimer);
        }
        d_vis_set_handler (vis, set_fixed_antenna_window_handler);
    }

    /*显示当前卫星的相关信息*/
    satellite_info_show();
    FixedAntennaSet_Data->change_enable = D_TRUE;

    /*使fman快速处理消息与事件，及时执行diseqc命令，
    实时显示信号强度与质量。退出菜单时恢复@qiny 2013-11-22*/
    d_fman_set_fast_mode(FixedAntennaSet_Data->hfman, D_TRUE);

    return D_OK;
}

/** @brief 获取当前选择的卫星编号*/
D_ID p_get_cur_sel_sate_id( void )
{
    return cur_db_sat_id;
}

/** @brief 卫星天线设置菜单*/
D_Result
p_atv_set_antenna_window_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu(&set_antenna_window, D_CLEAR_ALL);
}

