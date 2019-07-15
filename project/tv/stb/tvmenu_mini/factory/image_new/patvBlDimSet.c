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
#include "bl_dim_window.c"

#define BUF_LINE 4

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_S16 backlight, bl_min, bl_max;
    D_VidInput input;
    D_BLDIM_SET param;
    D_Char backlight_buf[BUF_LINE];
    D_Char bl_min_buf[BUF_LINE];
    D_Char bl_max_buf[BUF_LINE];
} D_BlDimDate;

static D_BlDimDate *bl_dim_data;

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
save_param_of_bl_dim(void) D_FUNCPOSTFIT
{
    p_tvconf_set_bldim_set_param(&bl_dim_data->param, p_vip_get_dbinput(bl_dim_data->input));
 	p_tvconf_set_bldim_backlight(&(bl_dim_data->backlight),p_vip_get_dbinput(bl_dim_data->input));
    return D_OK;
}

static D_Result
set_param_of_bl_dim(void) D_FUNCPOSTFIT
{
    bl_dim_data->param.bl_min = bl_dim_data->bl_min;
    bl_dim_data->param.bl_max = bl_dim_data->bl_max;

    d_vip_setBldim((D_U8*)&bl_dim_data->param,bl_dim_data->backlight);
    return D_OK;
}

static D_Result
get_set_of_bl_dim(void) D_FUNCPOSTFIT
{
    if(p_tvconf_get_bldim_set_param(&bl_dim_data->param, p_vip_get_dbinput(bl_dim_data->input)) == D_OK)
    {
        bl_dim_data->bl_min = bl_dim_data->param.bl_min;
        bl_dim_data->bl_max = bl_dim_data->param.bl_max;
    }
	p_tvconf_get_bldim_backlight(&(bl_dim_data->backlight),p_vip_get_dbinput(bl_dim_data->input));			
	
    sprintf(bl_dim_data->backlight_buf, "%d", bl_dim_data->backlight);
    sprintf(bl_dim_data->bl_min_buf, "%d", bl_dim_data->bl_min);
    sprintf(bl_dim_data->bl_max_buf, "%d", bl_dim_data->bl_max);
    return D_OK;
}


static D_S16
set_bl_dim_value(D_S16 value, D_Bool flag)
{

    if(flag)
    {
        if(value == 255)
            value = 0;
        else
            value ++;
    }
    else
    {
        if(value == 0)
            value = 255;
        else
            value --;
    }

    return value;
}


static D_Result
set_bl_dim_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &bl_dim_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_BL_DIM_BUTTON_1:
            if(flag)
            {
                if(bl_dim_data->backlight == 100)
                    bl_dim_data->backlight = 0;
                else
                    bl_dim_data->backlight ++;
            }
            else
            {
                if(bl_dim_data->backlight == 0)
                    bl_dim_data->backlight = 100;
                else
                    bl_dim_data->backlight --;
            }

            vis = d_frame_get_control(frm, ID_BL_DIM_LABEL_1);
            {
                sprintf(bl_dim_data->backlight_buf, "%d", bl_dim_data->backlight);
                d_label_set_text(vis, bl_dim_data->backlight_buf);
            }
            break;
        case ID_BL_DIM_BUTTON_2:
            bl_dim_data->bl_min = set_bl_dim_value(bl_dim_data->bl_min, flag);

            vis = d_frame_get_control(frm, ID_BL_DIM_LABEL_2);
            {
                sprintf(bl_dim_data->bl_min_buf, "%d", bl_dim_data->bl_min);
                d_label_set_text(vis, bl_dim_data->bl_min_buf);
            }
            break;
        case ID_BL_DIM_BUTTON_3:
            bl_dim_data->bl_max = set_bl_dim_value(bl_dim_data->bl_max, flag);

            vis = d_frame_get_control(frm, ID_BL_DIM_LABEL_3);
            {
                sprintf(bl_dim_data->bl_max_buf, "%d", bl_dim_data->bl_max);
                d_label_set_text(vis, bl_dim_data->bl_max_buf);
            }
            break;			
        default:
            break;
    }

    set_param_of_bl_dim();
    return D_OK;
}


static D_Result
backlight_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &bl_dim_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_BL_DIM_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_bl_dim_data(id, D_TRUE);
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
bl_min_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &bl_dim_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_BL_DIM_LABEL_2);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_bl_dim_data(id, D_TRUE);
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
bl_max_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &bl_dim_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_BL_DIM_LABEL_3);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_bl_dim_data(id, D_TRUE);
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
bl_dim_vis_set(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &bl_dim_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_BL_DIM_LABEL_BL_DIM);
    d_label_set_text(vis, "BL DIM");

    vis = d_frame_get_control(frm, ID_BL_DIM_BUTTON_1);
    d_button_set_text(vis, "BackLight");
    d_vis_set_handler(vis, backlight_handler);

    vis = d_frame_get_control(frm, ID_BL_DIM_BUTTON_2);
    d_button_set_text(vis, "Bl Min");
    d_vis_set_handler(vis, bl_min_handler);

    vis = d_frame_get_control(frm, ID_BL_DIM_BUTTON_3);
    d_button_set_text(vis, "Bl Max");
    d_vis_set_handler(vis, bl_max_handler);

    vis = d_frame_get_control(frm, ID_BL_DIM_LABEL_1);
    d_label_set_text(vis, bl_dim_data->backlight_buf);

    vis = d_frame_get_control(frm, ID_BL_DIM_LABEL_2);
    d_label_set_text(vis, bl_dim_data->bl_min_buf);

    vis = d_frame_get_control(frm, ID_BL_DIM_LABEL_3);
    d_label_set_text(vis, bl_dim_data->bl_max_buf);

    return D_OK;
}


static D_Result
bl_dim_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &bl_dim_window;
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

                    set_bl_dim_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_bl_dim_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            save_param_of_bl_dim();
            if(bl_dim_data)
            {
                PROJECT_FREE(bl_dim_data);
                bl_dim_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
bl_dim_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    bl_dim_data = (D_BlDimDate*)PROJECT_ALLOC(sizeof(D_BlDimDate));
    if(!bl_dim_data)
    {
        return D_ERR;
    }
    memset(bl_dim_data, 0, sizeof(D_BlDimDate));
    bl_dim_data->input = p_conf_get_vid_input();

    get_set_of_bl_dim();
    bl_dim_vis_set();

    vis = d_frame_get_control(frm, ID_BL_DIM_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, bl_dim_window_handler);
    }

    return D_OK;
}

/** @brief bl dim菜单*/
D_Result
p_atv_bl_dim_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&bl_dim_window, D_TRUE);
}

