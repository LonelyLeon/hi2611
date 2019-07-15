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
#include "general_setting_window.c"

#define BUF_LINE 4

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_S16 lvds_map,wp_mode;
		D_U8  logo_mode, pm_mode;
    D_Char lvds_map_buf[BUF_LINE];
} D_GeneralSettingDate;

static D_Char* white_pattern[10] = {"Off", "White", "Red", "Green", "Blue", "Black", "Gyan", "Magenta", "Yellow", "50% Gray"};
static D_GeneralSettingDate *general_setting_data;

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
set_intelnal_pattern(D_S16 flag)
{
    return D_OK;
}

static D_Result
set_general_setting_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &general_setting_window;
    D_Visual *vis;
    D_LoaderParam loader_param;

    switch(id)
    {
        case ID_GENERAL_BUTTON_3:
            if(general_setting_data->logo_mode == 0)
            {
                vis = d_frame_get_control(frm, ID_GENERAL_LABEL_3);
                if(vis)
                {
                    d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
                }
                general_setting_data->logo_mode = 1;
								p_tvconf_set_logomode (&general_setting_data->logo_mode);
            }
            else if(general_setting_data->logo_mode == 1)
            {
                vis = d_frame_get_control(frm, ID_GENERAL_LABEL_3);
                if(vis)
                {
                    d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
                }
				
                general_setting_data->logo_mode = 0;
				p_tvconf_set_logomode (&general_setting_data->logo_mode);
            }						
            break;
        case ID_GENERAL_BUTTON_4:
            if(general_setting_data->pm_mode == 0)
            {
                vis = d_frame_get_control(frm, ID_GENERAL_LABEL_4);
                if(vis)
                {
                    d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
                }
                general_setting_data->pm_mode = 1;
			    if(p_conf_get_loader_param(&loader_param) == D_OK)
			    {
					loader_param.reserved2 = 1;
					p_conf_set_loader_param(&loader_param);
					
			    }
			}
            else if(general_setting_data->pm_mode == 1)
            {
                vis = d_frame_get_control(frm, ID_GENERAL_LABEL_4);
                if(vis)
                {
                    d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
                }
                general_setting_data->pm_mode = 0;
			    if(p_conf_get_loader_param(&loader_param) == D_OK)
			    {
					loader_param.reserved2 = 0;
					p_conf_set_loader_param(&loader_param);					
			    }
			}
            break;
        case ID_GENERAL_BUTTON_5:
            if(flag)
            {
                if(general_setting_data->wp_mode == 9)
                    general_setting_data->wp_mode = 0;
                else
                    general_setting_data->wp_mode++;
            }
            else
            {
                if(general_setting_data->wp_mode == 0)
                    general_setting_data->wp_mode = 9;
                else
                    general_setting_data->wp_mode--;
            }

            vis = d_frame_get_control(frm, ID_GENERAL_LABEL_5);
            {
                d_label_set_text(vis, white_pattern[general_setting_data->wp_mode]);
            }
            set_intelnal_pattern(general_setting_data->wp_mode);
            break;
        default:
            break;
    }

    return D_OK;
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
lvds_map_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &general_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_GENERAL_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_general_setting_data(id, D_TRUE);
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
logo_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &general_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_GENERAL_LABEL_3);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_general_setting_data(id, D_TRUE);
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
power_mode_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &general_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);

    vis_label = d_frame_get_control(frm, ID_GENERAL_LABEL_4);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_general_setting_data(id, D_TRUE);
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
white_pattern_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &general_setting_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_GENERAL_LABEL_5);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_general_setting_data(id, D_TRUE);
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
get_set_of_general_setting(void) D_FUNCPOSTFIT
{
    D_LoaderParam loader_param;

    p_conf_get_loader_param(&loader_param);
	if(loader_param.reserved2 == 1)
	{
		general_setting_data->pm_mode	= 1;		
	}
	else
	{
		general_setting_data->pm_mode	= 0;			
	}
    p_tvconf_get_logomode (&general_setting_data->logo_mode);

    //取得通用设置的数值
    general_setting_data->wp_mode = 0;
    sprintf(general_setting_data->lvds_map_buf, "%d", general_setting_data->lvds_map);

    return D_OK;
}

static D_Result
general_setting_label_show(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &general_setting_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_5);
    if(vis)
    {
        d_label_set_text(vis, "Intelnal Pattern");
		
    }

    vis = d_frame_get_control(frm, ID_GENERAL_LABEL_1);
    if(vis)
    {
        d_label_set_text(vis, general_setting_data->lvds_map_buf);
		d_vis_set_focusable(vis, D_FALSE);
    }

    vis = d_frame_get_control(frm, ID_GENERAL_LABEL_3);
    if(vis)
    {
        vis_switch_init(general_setting_data->logo_mode, vis);
    }

    vis = d_frame_get_control(frm, ID_GENERAL_LABEL_4);
    if(vis)
    {
			vis_switch_init(general_setting_data->pm_mode, vis);
    }

    vis = d_frame_get_control(frm, ID_GENERAL_LABEL_5);
    if(vis)
    {
        d_label_set_text(vis, white_pattern[general_setting_data->wp_mode]);
    }

    return D_OK;
}

static D_Result
general_setting_vis_handler(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &general_setting_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_3);
    if(vis)
    {
        d_vis_set_handler(vis, logo_handler);
    }

    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_4);
    if(vis)
    {
        d_vis_set_handler(vis, power_mode_handler);
    }

    vis = d_frame_get_control(frm, ID_GENERAL_BUTTON_5);
    if(vis)
    {
        d_vis_set_handler(vis, white_pattern_handler);
    }

    return D_OK;
}

static D_Result
general_setting_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &general_setting_window;
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
                case D_KEY_OK:
                    set_general_setting_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_general_setting_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                case D_KEY_BACK:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(general_setting_data)
            {
                PROJECT_FREE(general_setting_data);
                general_setting_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
general_setting_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    general_setting_data = (D_GeneralSettingDate*)PROJECT_ALLOC(sizeof(D_GeneralSettingDate));
    if(!general_setting_data)
    {
        return D_ERR;
    }
    memset(general_setting_data, 0, sizeof(D_GeneralSettingDate));

    get_set_of_general_setting();
    general_setting_label_show();
    general_setting_vis_handler();

    vis = d_frame_get_control(frm, ID_GENERAL_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, general_setting_window_handler);
    }

    return D_OK;
}

/** @brief 通用设置菜单*/
D_Result
p_atv_general_setting_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&general_setting_window, D_TRUE);
}

