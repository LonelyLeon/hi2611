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
#include "colorset_window.c"

#define BUF_LINE 4

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_S16 ase, ase_weight, icm;
    D_VidInput input;
    D_U8 hdflag;
    D_CHROMA_SET param;

    D_Char ase_weight_buf[BUF_LINE];
} D_ColorsetDate;

static D_ColorsetDate *colorset_data;

static D_Result
save_param_of_colorset(void) D_FUNCPOSTFIT
{
    if(colorset_data->hdflag)
    {
        //  p_tvconf_set_hdase_set_param(&ase_set_data->param, p_vip_get_dbinput(ase_set_data->input));
    }
    else
    {
        p_tvconf_set_colorsetting_param(&colorset_data->param, p_vip_get_dbinput(colorset_data->input));
    }

    return D_OK;
}



static D_Result
get_set_of_colorset(void) D_FUNCPOSTFIT
{
    if(colorset_data->hdflag)
    {
        //   p_tvconf_get_hdase_set_param(&colorset_data->param, p_vip_get_dbinput(colorset_data->input));
    }
    else
    {
        p_tvconf_get_colorsettng_param(&colorset_data->param, p_vip_get_dbinput(colorset_data->input));
    }

    colorset_data->icm = colorset_data->param.icm_on;
    colorset_data->ase = colorset_data->param.ase_on;
    colorset_data->ase_weight = colorset_data->param.ase_weight;

    sprintf(colorset_data->ase_weight_buf, "%d", colorset_data->ase_weight);
    return D_OK;
}

static D_Result
set_param_of_colorset(void) D_FUNCPOSTFIT
{
    colorset_data->param.ase_on = colorset_data->ase;
    colorset_data->param.icm_on = colorset_data->icm;
    d_vip_setChroma(&colorset_data->param);
    return D_OK;
}

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
vis_switch_init(D_S16 value, D_Visual *vis)
{
    if(value == 0)
    {
        d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
    }
    else if(value == 1)
    {
        d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
    }

    return D_OK;
}

static D_Result
set_colorset_set_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &colorset_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_ASE_BUTTON_1:
            vis = d_frame_get_control(frm, ID_ASE_LABEL_1);
            colorset_data->ase = (colorset_data->ase + 1) & 0x01;
            d_label_set_text(vis, d_gui_get_text((colorset_data->ase) ? atv_IDS_ON : atv_IDS_OFF));
            break;
        case ID_ASE_BUTTON_2:
            if(flag)
            {
                colorset_data->ase_weight = (colorset_data->ase_weight + 1) % 64;
            }
            else
            {
                colorset_data->ase_weight = (colorset_data->ase_weight + 64 - 1) % 64;
            }

            vis = d_frame_get_control(frm, ID_ASE_LABEL_2);
            {
                sprintf(colorset_data->ase_weight_buf, "%d", colorset_data->ase_weight);
                d_label_set_text(vis, colorset_data->ase_weight_buf);
            }
            break;
        case ID_ASE_BUTTON_3:
            vis = d_frame_get_control(frm, ID_ASE_LABEL_3);
            colorset_data->icm = (colorset_data->icm + 1) & 0x01;
            d_label_set_text(vis, d_gui_get_text((colorset_data->icm) ? atv_IDS_ON : atv_IDS_OFF));
            break;
        default:
            break;
    }
    set_param_of_colorset();
    return D_OK;
}


static D_Result
ase_weight_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &colorset_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_ASE_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_colorset_set_data(id, D_TRUE);
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
icm_on_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &colorset_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_ASE_LABEL_3);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_colorset_set_data(id, D_TRUE);
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
ase_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &colorset_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_ASE_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_colorset_set_data(id, D_TRUE);
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
colorset_vis_set(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &colorset_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_ASE_BUTTON_1);
    d_label_set_text(vis, "ASE");
    d_vis_set_handler(vis, ase_handler);

    vis = d_frame_get_control(frm, ID_ASE_LABEL_ASE);
    d_label_set_text(vis, "ColorSetting");

    vis = d_frame_get_control(frm, ID_ASE_BUTTON_2);
    d_label_set_text(vis, "Ase Weight");
    d_vis_set_handler(vis, ase_weight_handler);

    vis = d_frame_get_control(frm, ID_ASE_BUTTON_3);
    d_label_set_text(vis, "ICM");
    d_vis_set_handler(vis, icm_on_handler);

    vis = d_frame_get_control(frm, ID_ASE_LABEL_2);
    d_label_set_text(vis, colorset_data->ase_weight_buf);

    vis = d_frame_get_control(frm, ID_ASE_LABEL_3);
    vis_switch_init(colorset_data->icm, vis);

    vis = d_frame_get_control(frm, ID_ASE_LABEL_1);
    vis_switch_init(colorset_data->ase, vis);

    return D_OK;
}


static D_Result
colorset_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &colorset_window;
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
                    set_colorset_set_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_colorset_set_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            save_param_of_colorset();
            if(colorset_data)
            {
                PROJECT_FREE(colorset_data);
                colorset_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
colorset_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    colorset_data = (D_ColorsetDate*)PROJECT_ALLOC(sizeof(D_ColorsetDate));
    if(!colorset_data)
    {
        return D_ERR;
    }
    memset(colorset_data, 0, sizeof(D_ColorsetDate));
    colorset_data->input = p_conf_get_vid_input();
    if(colorset_data->input == D_VID_IUTPUT_AV1 || colorset_data->input == D_VID_IUTPUT_AV2 || colorset_data->input == D_VID_IUTPUT_TV)
    {
        colorset_data->hdflag = p_vip_get_ntscflag();
    }
    else
    {
        colorset_data->hdflag = p_vip_get_hdflag();
    }
    get_set_of_colorset();
    colorset_vis_set();

    vis = d_frame_get_control(frm, ID_ASE_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, colorset_window_handler);
    }

    return D_OK;
}

/** @brief ase菜单*/
D_Result
p_atv_colorset_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&colorset_window, D_TRUE);
}

