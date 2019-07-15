#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "pConfig.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "tv_scan_config_window.c"

#define BUF_LINE 4
#define MAX_CHAN_CNT            P_DB_MAX_SRV_CNT

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_S16 fltcenteradj, fltbwadj;
    D_FEndParam fendparam;
    D_HFMan hfman;
    D_DBRecset      rset;
    D_ID                chan_ids[MAX_CHAN_CNT];
    D_Char fltcenteradj_buf[BUF_LINE];
    D_Char fltbwadj_buf[BUF_LINE];
} D_TvScanConfigDate;

static D_TvScanConfigDate *scan_config_data;

/** @brief  ≈–∂œΩπµ„Œª÷√
* @param    vis øÿº˛÷∏’Î
* @return   øÿº˛ID∫≈
*/
static D_ID
get_focus_control_id(D_Frame *frm)
{
    D_Visual *vis;
    D_ID id;
    vis = d_vis_get_focus(d_frame_get_control(frm, 0));
    id = d_frame_get_control_id(frm, vis);
    return id;
}

static D_Result
set_label_focus_attribute(D_Visual *vis, D_Bool flag) D_FUNCPOSTFIT
{
    D_Ptr pattr;

    if(flag)
    {
        pattr = (D_Ptr)&GUID_label_focus;
        d_vis_set_attribute(vis, pattr);
    }
    else
    {
        pattr = (D_Ptr)&GUID_label_normal;
        d_vis_set_attribute(vis, pattr);
    }

    return D_OK;
}

static D_Result
set_param_of_tv_scan_config(void) D_FUNCPOSTFIT
{
    if(scan_config_data->hfman == D_INVALID_HANDLE)
        return D_ERR;

    scan_config_data->fendparam.atv.fltCenterAdj = scan_config_data->fltcenteradj;
    scan_config_data->fendparam.atv.fltBwAdj = scan_config_data->fltbwadj;
    d_fman_set_param (scan_config_data->hfman, &scan_config_data->fendparam, D_FALSE, D_FEND_ANALOG, NULL, NULL);
    return D_OK;
}

static D_Result
save_param_of_tv_scan_config(void) D_FUNCPOSTFIT
{
    D_ATVSCAN_SET scan_set;
    D_ID    i = 0;
    D_DBSrvInfo srv_info;
    D_DBTSInfo  tinfo;

    scan_set.fltCenterAdj = scan_config_data->fltcenteradj;
    scan_set.fltBwAdj = scan_config_data->fltbwadj;

    p_tvconf_set_cur_atvscan(&scan_set);
    d_dbase_rset_init (&scan_config_data->rset, MAX_CHAN_CNT, scan_config_data->chan_ids);
    d_dbase_get_srvs_by_type_ex(&scan_config_data->rset, D_FALSE, D_DB_SRV_ATV, D_FALSE, 0);
    for(i = 0; i < scan_config_data->rset.cnt; i++)
    {
        if(d_dbase_get_srv_info (scan_config_data->chan_ids[i], &srv_info) == D_OK)
        {
            if(d_dbase_get_ts_info (srv_info.db_ts_id, &tinfo) >= 0)
            {
                tinfo.param.atv.fltCenterAdj = scan_set.fltCenterAdj;
                tinfo.param.atv.fltBwAdj = scan_set.fltBwAdj;
                d_dbase_updata_ts_info(srv_info.db_ts_id, &tinfo);
            }
        }
    }

    return D_OK;
}

static D_Result
set_scan_config_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &tv_scan_config_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_SCAN_CONFIG_BUTTON_1:
            if(flag)
            {
                if(scan_config_data->fltcenteradj == 64)
                    scan_config_data->fltcenteradj = -64;
                else
                    scan_config_data->fltcenteradj ++;
            }
            else
            {
                if(scan_config_data->fltcenteradj == -64)
                    scan_config_data->fltcenteradj = 64;
                else
                    scan_config_data->fltcenteradj --;
            }
            vis = d_frame_get_control(frm, ID_SCAN_CONFIG_LABEL_1);
            {
                sprintf(scan_config_data->fltcenteradj_buf, "%d", scan_config_data->fltcenteradj);
                d_label_set_text(vis, scan_config_data->fltcenteradj_buf);
            }
            break;
        case ID_SCAN_CONFIG_BUTTON_2:
            if(flag)
            {
                if(scan_config_data->fltbwadj == 8)
                    scan_config_data->fltbwadj = -8;
                else
                    scan_config_data->fltbwadj ++;
            }
            else
            {
                if(scan_config_data->fltbwadj == -8)
                    scan_config_data->fltbwadj = 8;
                else
                    scan_config_data->fltbwadj --;
            }
            vis = d_frame_get_control(frm, ID_SCAN_CONFIG_LABEL_2);
            {
                sprintf(scan_config_data->fltbwadj_buf, "%d", scan_config_data->fltbwadj);
                d_label_set_text(vis, scan_config_data->fltbwadj_buf);
            }
            break;
        default:
            break;
    }
    set_param_of_tv_scan_config();

    return D_OK;
}


static D_Result
fltcenteradj_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &tv_scan_config_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_SCAN_CONFIG_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_scan_config_data(id, D_TRUE);
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
fltbwadj_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &tv_scan_config_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_SCAN_CONFIG_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_scan_config_data(id, D_TRUE);
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
get_set_of_scan_config(void) D_FUNCPOSTFIT
{
    D_ATVSCAN_SET scan_set;
    p_tvconf_get_cur_atvscan(&scan_set);

    scan_config_data->fltcenteradj = scan_set.fltCenterAdj;
    scan_config_data->fltbwadj = scan_set.fltBwAdj;

    sprintf(scan_config_data->fltcenteradj_buf, "%d", scan_config_data->fltcenteradj);
    sprintf(scan_config_data->fltbwadj_buf, "%d", scan_config_data->fltbwadj);

    return D_OK;
}

static D_Result
scan_config_vis_set(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &tv_scan_config_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_SCAN_CONFIG_BUTTON_1);
    d_label_set_text(vis, "FltCenterAdj");
    d_vis_set_handler(vis, fltcenteradj_handler);

    vis = d_frame_get_control(frm, ID_SCAN_CONFIG_BUTTON_2);
    d_label_set_text(vis, "FltBwAdj");
    d_vis_set_handler(vis, fltbwadj_handler);

    vis = d_frame_get_control(frm, ID_SCAN_CONFIG_LABEL_1);
    d_label_set_text(vis, scan_config_data->fltcenteradj_buf);

    vis = d_frame_get_control(frm, ID_SCAN_CONFIG_LABEL_2);
    d_label_set_text(vis, scan_config_data->fltbwadj_buf);

    return D_OK;
}


static D_Result
tv_scan_config_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &tv_scan_config_window;
    D_ID id;

    id = get_focus_control_id(frm);

    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                    return d_gui_clear_menu();
                case D_KEY_RIGHT:

                case D_KEY_PNL_R:

                    set_scan_config_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_scan_config_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            save_param_of_tv_scan_config();
            if(scan_config_data)
            {
                PROJECT_FREE(scan_config_data);
                scan_config_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
tv_scan_config_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_DBSrvID  curr_srv_id;
    D_DBSrvInfo sinfo;
    D_DBTSInfo  tinfo;

    scan_config_data = (D_TvScanConfigDate*)PROJECT_ALLOC(sizeof(D_TvScanConfigDate));
    if(!scan_config_data)
    {
        return D_ERR;
    }
    memset(scan_config_data, 0, sizeof(D_TvScanConfigDate));
    scan_config_data->hfman = D_INVALID_HANDLE;
    curr_srv_id = p_stb_player_get_curr_srv(0);
    if (curr_srv_id != -1)
    {
        if (d_dbase_get_srv_info(curr_srv_id, &sinfo) >= 0)
        {
            if (d_dbase_get_ts_info (sinfo.db_ts_id, &tinfo) >= 0)
            {
                scan_config_data->hfman = d_fman_get_handle_by_type((D_FEndType)tinfo.tuner_type, 0);
                if(D_INVALID_HANDLE != scan_config_data->hfman)
                {
                    memcpy (&scan_config_data->fendparam, &tinfo.param, sizeof (D_FEndParam));
                }
            }
        }
    }
    get_set_of_scan_config();
    scan_config_vis_set();

    vis = d_frame_get_control(frm, ID_SCAN_CONFIG_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, tv_scan_config_window_handler);
    }

    return D_OK;
}

/** @brief tvÀ—À˜≈‰÷√≤Àµ•*/
D_Result
p_atv_tv_scan_config_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&tv_scan_config_window, D_TRUE);
}

