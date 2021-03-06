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
#include "dce_window.c"

#define BUF_LINE 4
#define BUF_TEXT 16

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_S16 dce_idx;
    D_VidInput input;
    D_U8 hdflag;
    D_DCE_SET param;
} D_DceDate;

static D_DceDate *dce_data;
static D_Char *str_dce[] = {"Linear", "S curve", "Inc_S", "Dark", "Inc_Dark", "Bright", "Inc_Bright"};

static D_Result
save_param_of_dce(void) D_FUNCPOSTFIT
{
    if(dce_data->hdflag)
    {
        //p_tvconf_set_hdgamma_set_param(&dce_data->param, p_vip_get_dbinput(dce_data->input));
    }
    else
    {
        p_tvconf_set_dce_set_param(&dce_data->param, p_vip_get_dbinput(dce_data->input));
    }
    return D_OK;
}

static D_Result
set_param_of_dce(void) D_FUNCPOSTFIT
{
    dce_data->param.dce_idx = dce_data->dce_idx;
    //dce_data->param.dce_on = dce_data->dce_on;
    d_vip_setDce((D_U8*)&dce_data->param);
    return D_OK;
}

static D_Result
get_set_of_dce(void) D_FUNCPOSTFIT
{
    if(dce_data->hdflag)
    {
        //p_tvconf_get_hdgamma_set_param(&dce_data->param, p_vip_get_dbinput(dce_data->input));
    }
    else
    {
        p_tvconf_get_dce_set_param(&dce_data->param, p_vip_get_dbinput(dce_data->input));
    }
    //dce_data->dce_on = dce_data->param.dce_on;
    dce_data->dce_idx = dce_data->param.dce_idx;
    return D_OK;
}

static D_Result
vis_switch_text_init(D_S16 value, D_Visual *vis)
{
    d_label_set_text(vis, str_dce[value]);
    return D_OK;
}

/** @brief  �жϽ���λ��
* @param    vis �ؼ�ָ��
* @return   �ؼ�ID��
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
set_dce_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &dce_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_GAMMA_BUTTON_1:
            if(flag)
            {
                dce_data->dce_idx = (dce_data->dce_idx + 1) % 7;
            }
            else
            {
                dce_data->dce_idx = (dce_data->dce_idx + 7 - 1) % 7;
            }
            vis = d_frame_get_control(frm, ID_GAMMA_LABEL_1);
            {
                vis_switch_text_init( dce_data->dce_idx , vis);
            }
            break;
        default:
            break;
    }
    set_param_of_dce();

    return D_OK;
}


static D_Result
dce_idx_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &dce_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_GAMMA_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_dce_data(id, D_TRUE);
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
dce_vis_set(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &dce_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_GAMMA_LABEL_GAMMA);
    d_label_set_text(vis, "Dce");

    vis = d_frame_get_control(frm, ID_GAMMA_BUTTON_1);
    d_button_set_text(vis, "Dce Idx");
    d_vis_set_handler(vis, dce_idx_handler);

    vis = d_frame_get_control(frm, ID_GAMMA_LABEL_1);
    vis_switch_text_init( dce_data->dce_idx , vis);

    return D_OK;
}


static D_Result
dce_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &dce_window;
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
                    set_dce_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_dce_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            save_param_of_dce();
            if(dce_data)
            {
                PROJECT_FREE(dce_data);
                dce_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
dce_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    dce_data = (D_DceDate*)PROJECT_ALLOC(sizeof(D_DceDate));
    if(!dce_data)
    {
        return D_ERR;
    }
    memset(dce_data, 0, sizeof(D_DceDate));
    dce_data->input = p_conf_get_vid_input();
    if(dce_data->input == D_VID_IUTPUT_AV1 || dce_data->input == D_VID_IUTPUT_AV2 || dce_data->input == D_VID_IUTPUT_TV)
    {
        dce_data->hdflag = p_vip_get_ntscflag();
    }
    else
    {
        dce_data->hdflag = p_vip_get_hdflag();
    }
    get_set_of_dce();
    dce_vis_set();

    vis = d_frame_get_control(frm, ID_GAMMA_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, dce_window_handler);
    }

    return D_OK;
}

/** @brief gamma�˵�*/
D_Result
p_atv_dce_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&dce_window, D_TRUE);
}

