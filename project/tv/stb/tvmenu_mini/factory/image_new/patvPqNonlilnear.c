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
#include "pq_nonlilnear_window.c"

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus={{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal={{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

static D_Result
set_picture_mode(void) D_FUNCPOSTFIT;

typedef enum
{
	CONTRAST,
	BRIGHTNESS,
	SATURATION,
	SHARPNESS,
	HUE
}PICTURE;

typedef struct
{
	D_S16 mode;
	D_S16 video_mode;
    D_VidInput input;    
}D_PqNonlilnearDate;

static D_PqNonlilnearDate *pq_nonlilnear_data;

/** @brief 	判断焦点位置
* @param 	vis	控件指针
* @return	控件ID号
*/
static D_ID
get_focus_control_id(D_Frame *frm)
{
	D_Visual *vis;
	D_ID id;
	vis = d_vis_get_focus(d_frame_get_control(frm,0));
	id = d_frame_get_control_id(frm,vis);	
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
set_pqnonlilnear_param(void) D_FUNCPOSTFIT
{

	return D_OK;
}

static D_Result
save_pqnonlilnear_param(void) D_FUNCPOSTFIT
{

	return D_OK;
}

static D_Result
set_mode_show(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &pq_nonlilnear_window;
    D_Visual *vis;

	vis = d_frame_get_control(frm, ID_PQ_NONLILNEAR_LABEL_1);
	if(vis)
	{
		if(pq_nonlilnear_data->input== D_VID_IUTPUT_TV)
		{
			d_label_set_text(vis, d_gui_get_text(atv_IDS_TV));
			pq_nonlilnear_data->mode = 0;
		}
		else if(pq_nonlilnear_data->input == D_VID_IUTPUT_DTV)
		{
			d_label_set_text(vis, d_gui_get_text(atv_IDS_DTV));
			pq_nonlilnear_data->mode = 1;
		}
		else if((pq_nonlilnear_data->input == D_VID_IUTPUT_AV1)||(pq_nonlilnear_data->input == D_VID_IUTPUT_AV2))
		{
			d_label_set_text(vis, d_gui_get_text(atv_IDS_AV));
			pq_nonlilnear_data->mode = 2;
		}
		else if(pq_nonlilnear_data->input == D_VID_IUTPUT_YPBPR)
		{
			d_label_set_text(vis, d_gui_get_text(atv_IDS_YPBPR));
			pq_nonlilnear_data->mode = 3;
		}
		else if(pq_nonlilnear_data->input == D_VID_IUTPUT_HDMI1)
		{
			d_label_set_text(vis, d_gui_get_text(atv_IDS_HDMI1));
			pq_nonlilnear_data->mode = 4;
		}
		else if(pq_nonlilnear_data->input == D_VID_IUTPUT_USB1)
		{
			d_label_set_text(vis, d_gui_get_text(atv_IDS_USB));
			pq_nonlilnear_data->mode = 7;
		}
		else if(pq_nonlilnear_data->input == D_VID_IUTPUT_HDMI2)
		{
			d_label_set_text(vis, d_gui_get_text(atv_IDS_HDMI2));
			pq_nonlilnear_data->mode = 5;
		}
		else if(pq_nonlilnear_data->input == D_VID_IUTPUT_VGA)
		{
			d_label_set_text(vis, d_gui_get_text(atv_IDS_PC));
			pq_nonlilnear_data->mode = 6;
		}
	}

	
	return D_OK;
}

static D_Result
set_mode_vis_show(D_S16 flag) D_FUNCPOSTFIT
{
	D_Frame *frm = &pq_nonlilnear_window;
    D_Visual *vis;

	vis = d_frame_get_control(frm, ID_PQ_NONLILNEAR_LABEL_1);
	
    switch(flag)
    {
        case 0:
            pq_nonlilnear_data->input = D_VID_IUTPUT_TV;
			d_label_set_text(vis, d_gui_get_text(atv_IDS_TV));
            break;
        case 1:
            pq_nonlilnear_data->input = D_VID_IUTPUT_DTV;
			d_label_set_text(vis, d_gui_get_text(atv_IDS_DTV));
            break;
        case 2:
            pq_nonlilnear_data->input = D_VID_IUTPUT_AV1;
			d_label_set_text(vis, d_gui_get_text(atv_IDS_AV));
            break;
        case 3:
            pq_nonlilnear_data->input = D_VID_IUTPUT_YPBPR;
			d_label_set_text(vis, d_gui_get_text(atv_IDS_YPBPR));
            break;
        case 4:
            pq_nonlilnear_data->input = D_VID_IUTPUT_HDMI1;
			d_label_set_text(vis, d_gui_get_text(atv_IDS_HDMI1));
            break;
        case 5:
            pq_nonlilnear_data->input = D_VID_IUTPUT_HDMI2;
			d_label_set_text(vis, d_gui_get_text(atv_IDS_HDMI2));
            break;
        case 6:
            pq_nonlilnear_data->input = D_VID_IUTPUT_VGA;
			d_label_set_text(vis, d_gui_get_text(atv_IDS_PC));
            break;
        case 7:
            pq_nonlilnear_data->input = D_VID_IUTPUT_USB1;
			d_label_set_text(vis, d_gui_get_text(atv_IDS_USB));
            break;
        default:
            break;
    }
	p_tvconf_get_cur_imagemode(&pq_nonlilnear_data->video_mode, p_vip_get_dbinput(pq_nonlilnear_data->input));
	set_picture_mode();
	return D_OK;
}

static D_Result
set_picture_mode(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &pq_nonlilnear_window;
    D_Visual *vis;

	vis = d_frame_get_control(frm, ID_PQ_NONLILNEAR_LABEL_2);
	if(vis)
	{
		if(pq_nonlilnear_data->video_mode == 0)
		{
			d_label_set_text(vis, d_gui_get_text(atv_IDS_STANDARD));
		}
		else if(pq_nonlilnear_data->video_mode == 1)
		{
			d_label_set_text(vis, d_gui_get_text(atv_IDS_MILD));
		}
		else if(pq_nonlilnear_data->video_mode == 2)
		{
			d_label_set_text(vis, d_gui_get_text(atv_IDS_USER));
		}
		else if(pq_nonlilnear_data->video_mode == 3)
		{
			d_label_set_text(vis, d_gui_get_text(atv_IDS_LIGHT));
		}
	}
	
	return D_OK;
}


static D_Result
set_pq_nonlilnear_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
	
	switch(id)
	{
		case ID_PQ_NONLILNEAR_BUTTON_1:
			if(flag)
			{
				if(pq_nonlilnear_data->mode == 7)
					pq_nonlilnear_data->mode = 0;
				else
					pq_nonlilnear_data->mode++;
			}
			else
			{
				if(pq_nonlilnear_data->mode == 0)
					pq_nonlilnear_data->mode = 7;
				else 
					pq_nonlilnear_data->mode --;
			}
			set_mode_vis_show(pq_nonlilnear_data->mode);
			break;
		case ID_PQ_NONLILNEAR_BUTTON_2:
			if(flag)
			{
				if(pq_nonlilnear_data->video_mode == 3)
					pq_nonlilnear_data->video_mode = 0;
				else
					pq_nonlilnear_data->video_mode++;
			}
			else
			{
				if(pq_nonlilnear_data->video_mode == 0)
					pq_nonlilnear_data->video_mode = 3;
				else 
					pq_nonlilnear_data->video_mode --;
			}
			set_picture_mode();
			break;
		default:
			break;
	}

	set_pqnonlilnear_param();
	return D_OK;
}

static D_Result
mode_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &pq_nonlilnear_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_PQ_NONLILNEAR_LABEL_1);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_pq_nonlilnear_data(id, D_TRUE);
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
picture_mode_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &pq_nonlilnear_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);

	vis_label = d_frame_get_control(frm, ID_PQ_NONLILNEAR_LABEL_2);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_pq_nonlilnear_data(id,D_TRUE);
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
contrast_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	switch (evt->type)
    {
		case D_EVT_PRESSED:
			p_atv_setting_show(CONTRAST);
			break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
brightness_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	switch (evt->type)
	{
		case D_EVT_PRESSED:
			p_atv_setting_show(BRIGHTNESS);
			break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
saturation_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	switch (evt->type)
    {
		case D_EVT_PRESSED:
			p_atv_setting_show(SATURATION);
			break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
sharpness_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	switch (evt->type)
    {
		case D_EVT_PRESSED:
			p_atv_setting_show(SHARPNESS);
			break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
hue_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	switch (evt->type)
    {
		case D_EVT_PRESSED:
			p_atv_setting_show(HUE);
			break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
pq_nonlilnear_vis_handler(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &pq_nonlilnear_window;
    D_Visual *vis;

	vis = d_frame_get_control(frm, ID_PQ_NONLILNEAR_BUTTON_1);
	if(vis)
	{
		d_button_set_text(vis, "MODE");
		d_vis_set_handler(vis, mode_handler);
	}
	vis = d_frame_get_control(frm, ID_PQ_NONLILNEAR_BUTTON_2);
	if(vis)
	{
		d_button_set_text(vis, "PICTURE MODE");
		d_vis_set_handler(vis, picture_mode_handler);
	}

	vis = d_frame_get_control(frm, ID_PQ_NONLILNEAR_BUTTON_3);
	if(vis)
	{
		d_vis_set_handler(vis, contrast_set_handler);
	}

	vis = d_frame_get_control(frm, ID_PQ_NONLILNEAR_BUTTON_4);
	if(vis)
	{
		d_vis_set_handler(vis, brightness_set_handler);
	}

	vis = d_frame_get_control(frm, ID_PQ_NONLILNEAR_BUTTON_5);
	if(vis)
	{
		d_vis_set_handler(vis, saturation_set_handler);
	}

	vis = d_frame_get_control(frm, ID_PQ_NONLILNEAR_BUTTON_6);
	if(vis)
	{
		d_vis_set_handler(vis, sharpness_set_handler);
	}

	vis = d_frame_get_control(frm, ID_PQ_NONLILNEAR_BUTTON_7);
	if(vis)
	{
		d_vis_set_handler(vis, hue_set_handler);
	}
	
	return D_OK;
}

static D_Result
pq_nonlilnear_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{	
	D_Visual *fv;
	D_Frame *frm = &pq_nonlilnear_window;
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
				case D_KEY_SOURCE:
					set_pq_nonlilnear_data(id, D_TRUE);
					break;
				case D_KEY_LEFT:
				case D_KEY_PNL_L:
					set_pq_nonlilnear_data(id, D_FALSE);
					break;
				case D_KEY_MENU:
					return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
			save_pqnonlilnear_param();
			 if(pq_nonlilnear_data)
            {
                PROJECT_FREE(pq_nonlilnear_data);
                pq_nonlilnear_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
pq_nonlilnear_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

	pq_nonlilnear_data = (D_PqNonlilnearDate*)PROJECT_ALLOC(sizeof(D_PqNonlilnearDate));
    if(!pq_nonlilnear_data)
    {
        return D_ERR;
    }
	memset(pq_nonlilnear_data, 0, sizeof(D_PqNonlilnearDate));

	pq_nonlilnear_data->input = p_conf_get_vid_input();
    p_tvconf_get_cur_imagemode(&pq_nonlilnear_data->video_mode, p_vip_get_dbinput(pq_nonlilnear_data->input));

	set_mode_show();
	set_picture_mode();
	pq_nonlilnear_vis_handler();
	
	vis = d_frame_get_control(frm, ID_PQ_NONLILNEAR_GROUP);
	if(vis)
	{
		d_group_set_focus_loop(vis, D_TRUE);
		d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
	}

	vis = d_frame_get_control(frm, 0);
	if(vis)
	{
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
		d_vis_set_handler(vis, pq_nonlilnear_window_handler);
	}

    return D_OK;
}

/** @brief 效果菜单*/
D_Result
p_atv_pq_nonlilnear_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&pq_nonlilnear_window, D_TRUE);
}

