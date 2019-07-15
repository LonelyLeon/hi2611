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
#include "srs_window.c"

#define AVC_LEVEL_NUM (D_AVC_DAC_CTL_LEVEL_NUM)
#define BUF_LINE 8


static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_U32 srs_time , weight_coefficient;

    D_Char srs_time_buf[BUF_LINE] , weight_coefficient_buf[BUF_LINE];
} D_SrsDate;

static D_SrsDate *srs_data;

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
get_set_of_srs(void) D_FUNCPOSTFIT
{
    D_SRS_SET srs;
    p_tvconf_get_srs(&srs);

    srs_data->srs_time = srs.srs_time;
    srs_data->weight_coefficient = srs.weight_coefficient;

    sprintf(srs_data->srs_time_buf, "%d", srs_data->srs_time);
    sprintf(srs_data->weight_coefficient_buf, "%d", srs_data->weight_coefficient);

    return D_OK;
}

static D_Result
set_param_of_srs(void) D_FUNCPOSTFIT
{
    d_av_audio_srs_param_set(srs_data->srs_time , srs_data->weight_coefficient);

    return D_OK;
}

static D_Result
save_param_of_srs(void) D_FUNCPOSTFIT
{
    D_SRS_SET srs;

    srs.srs_time = srs_data->srs_time;
    srs.weight_coefficient = srs_data->weight_coefficient;

    p_tvconf_set_srs(&srs);

    return D_OK;
}

static D_Result
set_srs_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &srs_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_SRS_BUTTON_1:
            if(flag)
            {
                (srs_data->srs_time == 70) ? (srs_data->srs_time = 0) : (srs_data->srs_time++);
            }
            else
            {
                (srs_data->srs_time == 0) ? (srs_data->srs_time = 70) : (srs_data->srs_time--);
            }

            vis = d_frame_get_control(frm, ID_SRS_LABEL_1);
            {
                sprintf(srs_data->srs_time_buf, "%d", srs_data->srs_time);
                d_label_set_text(vis, srs_data->srs_time_buf);
            }
            break;
        case ID_SRS_BUTTON_2:
            if(flag)
            {
                (srs_data->weight_coefficient== 100) ? (srs_data->weight_coefficient = 50) : (srs_data->weight_coefficient++);
            }
            else
            {
                (srs_data->weight_coefficient == 50) ? (srs_data->weight_coefficient = 100) : (srs_data->weight_coefficient--);
            }
			
            vis = d_frame_get_control(frm, ID_SRS_LABEL_2);
            {
                sprintf(srs_data->weight_coefficient_buf, "%d", srs_data->weight_coefficient);
                d_label_set_text(vis, srs_data->weight_coefficient_buf);
            }
            break;
        default:
            break;
    }

    set_param_of_srs();
    return D_OK;
}

static D_Result
button1_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &srs_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_SRS_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_srs_data(id, D_TRUE);
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
button2_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &srs_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_SRS_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_srs_data(id, D_TRUE);
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
srs_vis_set(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &srs_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_SRS_LABEL_SRS);
    d_label_set_text(vis, "SRS");

    vis = d_frame_get_control(frm, ID_SRS_BUTTON_1);
    d_button_set_text(vis, "SRS_TIME ");
    d_vis_set_handler(vis, button1_handler);

    vis = d_frame_get_control(frm, ID_SRS_BUTTON_2);
    d_button_set_text(vis, "WEIGHT_COEFFICIENT");
    d_vis_set_handler(vis, button2_handler);

    vis = d_frame_get_control(frm, ID_SRS_LABEL_1);
    d_label_set_text(vis, srs_data->srs_time_buf);

    vis = d_frame_get_control(frm, ID_SRS_LABEL_2);
    d_label_set_text(vis, srs_data->weight_coefficient_buf);

    return D_OK;
}


static D_Result
srs_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &srs_window;
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
                    set_srs_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_srs_data(id, D_FALSE);
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
            save_param_of_srs();
            if(srs_data)
            {
                PROJECT_FREE(srs_data);
                srs_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
srs_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    srs_data = (D_SrsDate*)PROJECT_ALLOC(sizeof(D_SrsDate));
    if(!srs_data)
    {
        return D_ERR;
    }
    memset(srs_data, 0, sizeof(D_SrsDate));

    get_set_of_srs();
    srs_vis_set();

    vis = d_frame_get_control(frm, ID_SRS_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, srs_window_handler);
    }

    return D_OK;
}

/** @brief  avc dac ctl菜单*/
D_Result
p_atv_srs_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&srs_window, D_TRUE);
}

