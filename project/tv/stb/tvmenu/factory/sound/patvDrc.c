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
#include "drc_window.c"

#define AVC_LEVEL_NUM (D_AVC_DAC_CTL_LEVEL_NUM)
#define BUF_LINE 8


static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_U8 en, threshold, compress;
    D_Char threshold_buf[BUF_LINE], compress_buf[BUF_LINE];
} D_DrcDate;

static D_DrcDate *drc_data;

/** @brief  判断焦点位置
* @param    vis 控件指针
* @return   控件ID号
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
get_set_of_drc(void) D_FUNCPOSTFIT
{
    D_U8 bdinput;
    D_DRC_SET audio_drc;

    p_tvconf_get_audio_drc(&audio_drc, p_vip_get_dbinput(p_conf_get_vid_input ()));

    drc_data->en = audio_drc.drc_en;
    drc_data->threshold = audio_drc.drc_threshold;
    drc_data->compress = audio_drc.drc_compress;

    sprintf(drc_data->threshold_buf, "%d", drc_data->threshold);
    sprintf(drc_data->compress_buf, "%d", drc_data->compress);

    return D_OK;
}

static D_Result
set_param_of_drc(void) D_FUNCPOSTFIT
{
    d_av_audio_bo_drc_set(drc_data->threshold, drc_data->compress);

    return D_OK;
}
static D_Result
save_param_of_drc(void) D_FUNCPOSTFIT
{
    D_U8 bdinput;
    D_DRC_SET audio_drc;

    audio_drc.drc_en = drc_data->en;
    audio_drc.drc_threshold = drc_data->threshold ;
    audio_drc.drc_compress = drc_data->compress;
    p_tvconf_set_audio_drc(&audio_drc, p_vip_get_dbinput(p_conf_get_vid_input ()));

    return D_OK;
}
static D_Result
set_drc_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &drc_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_DRC_BUTTON_1:
            drc_data->en = (!drc_data->en);
            vis = d_frame_get_control(frm, ID_DRC_LABEL_1);
            {
                d_label_set_text(vis, d_gui_get_text((drc_data->en == 0) ? (atv_IDS_OFF) : (atv_IDS_ON)));
            }
            d_av_audio_bo_drc_enable(drc_data->en);
            break;
        case ID_DRC_BUTTON_2:
            if(flag)
            {
                (drc_data->threshold == 31) ? (drc_data->threshold = 0) : (drc_data->threshold++);
            }
            else
            {
                (drc_data->threshold == 0) ? (drc_data->threshold = 31) : (drc_data->threshold--);
            }

            vis = d_frame_get_control(frm, ID_DRC_LABEL_2);
            {
                sprintf(drc_data->threshold_buf, "%d", drc_data->threshold);
                d_label_set_text(vis, drc_data->threshold_buf);
            }
            break;
        case ID_DRC_BUTTON_3:
            if(flag)
            {
                (drc_data->compress == 5) ? (drc_data->compress = 0) : (drc_data->compress++);
            }
            else
            {
                (drc_data->compress == 0) ? (drc_data->compress = 5) : (drc_data->compress--);
            }

            vis = d_frame_get_control(frm, ID_DRC_LABEL_3);
            {
                sprintf(drc_data->compress_buf, "%d", drc_data->compress);
                d_label_set_text(vis, drc_data->compress_buf);
            }
            break;
        default:
            break;
    }
    if(drc_data->en == 1)
        set_param_of_drc();
    return D_OK;
}

static D_Result
drc_button1_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &drc_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_DRC_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_drc_data(id, D_TRUE);
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
drc_button2_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &drc_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_DRC_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_drc_data(id, D_TRUE);
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
drc_button3_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &drc_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_DRC_LABEL_3);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_drc_data(id, D_TRUE);
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
drc_vis_set(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &drc_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_DRC_LABEL_DRC);
    d_label_set_text(vis, "DRC");

    vis = d_frame_get_control(frm, ID_DRC_BUTTON_1);
    d_button_set_text(vis, "DRC_EN ");
    d_vis_set_handler(vis, drc_button1_handler);

    vis = d_frame_get_control(frm, ID_DRC_BUTTON_2);
    d_button_set_text(vis, "THRESHOLD ");
    d_vis_set_handler(vis, drc_button2_handler);

    vis = d_frame_get_control(frm, ID_DRC_BUTTON_3);
    d_button_set_text(vis, "COMPRESS");
    d_vis_set_handler(vis, drc_button3_handler);

    vis = d_frame_get_control(frm, ID_DRC_LABEL_1);
    d_label_set_text(vis, d_gui_get_text((drc_data->en == 0) ? (atv_IDS_OFF) : (atv_IDS_ON)));

    vis = d_frame_get_control(frm, ID_DRC_LABEL_2);
    d_label_set_text(vis, drc_data->threshold_buf);

    vis = d_frame_get_control(frm, ID_DRC_LABEL_3);
    d_label_set_text(vis, drc_data->compress_buf);

    return D_OK;
}


static D_Result
drc_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &drc_window;
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
                    set_drc_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_drc_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                    //case D_KEY_BACK:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
	     save_param_of_drc();
            if(drc_data)
            {
                PROJECT_FREE(drc_data);
                drc_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
drc_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    drc_data = (D_DrcDate*)PROJECT_ALLOC(sizeof(D_DrcDate));
    if(!drc_data)
    {
        return D_ERR;
    }
    memset(drc_data, 0, sizeof(D_DrcDate));

    get_set_of_drc();
    drc_vis_set();

    vis = d_frame_get_control(frm, ID_DRC_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, drc_window_handler);
    }

    return D_OK;
}

/** @brief  drc菜单*/
D_Result
p_atv_drc_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&drc_window, D_TRUE);
}

