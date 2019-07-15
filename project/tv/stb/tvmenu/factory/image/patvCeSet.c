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
#include "ce_window.c"

#define BUF_LINE 4

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus={{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal={{&GUID_label_normal_attribute, NULL, NULL, }, 1, };


typedef struct
{
	D_S16 ce_on, bs_on, ws_on, cc_on, bbd_mode, ce_gain, histq_on, ropc_on;
	D_VidInput input;
	D_U8 hdflag;
	D_CE_SET param;

	D_Char ce_gain_buf[BUF_LINE];
}D_CeSetDate;

static D_Char* bbd_mode[3] = {"auto", "manual", "off"};
static D_CeSetDate *ce_set_data;

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
save_param_of_ce(void) D_FUNCPOSTFIT
{
	p_tvconf_set_ce_set_param(&ce_set_data->param, p_vip_get_dbinput(ce_set_data->input));
	if(ce_set_data->hdflag)
    {
		p_tvconf_set_hdce_set_param(&ce_set_data->param, p_vip_get_dbinput(ce_set_data->input));
    }
    else
    {
		p_tvconf_set_ce_set_param(&ce_set_data->param, p_vip_get_dbinput(ce_set_data->input));
    }
	return D_OK;
}

static D_Result
set_param_of_ce(void) D_FUNCPOSTFIT
{
	ce_set_data->param.ce_on= ce_set_data->ce_on;
	ce_set_data->param.bs_on= ce_set_data->bs_on;
	ce_set_data->param.ws_on= ce_set_data->ws_on;
	ce_set_data->param.cc_on= ce_set_data->cc_on;
	ce_set_data->param.bbd_mode= ce_set_data->bbd_mode;
	ce_set_data->param.ce_gain = ce_set_data->ce_gain;
	ce_set_data->param.histq_on = ce_set_data->histq_on;
	d_vip_setCe((D_U8*)&ce_set_data->param);

	return D_OK;
}


static D_S16
set_vis_switch(D_S16 value, D_Visual *vis)
{
	if(value == 0)
	{
		d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
		value = 1;
	}
	else if(value == 1)
	{
		d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
		value = 0;
	}

	return value;
}

static D_Result
set_ce_set_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
	D_Frame *frm = &ce_window;
    D_Visual *vis;
	
	switch(id)
	{
		case ID_CE_BUTTON_1:
			vis = d_frame_get_control(frm, ID_CE_LABEL_1);
			ce_set_data->ce_on = set_vis_switch(ce_set_data->ce_on, vis);
			break;
		case ID_CE_BUTTON_2:
			vis = d_frame_get_control(frm, ID_CE_LABEL_2);
			ce_set_data->bs_on = set_vis_switch(ce_set_data->bs_on, vis);
			break;
		case ID_CE_BUTTON_3:
			vis = d_frame_get_control(frm, ID_CE_LABEL_3);
			ce_set_data->ws_on = set_vis_switch(ce_set_data->ws_on, vis);
			break;
		case ID_CE_BUTTON_4:
			vis = d_frame_get_control(frm, ID_CE_LABEL_4);
			ce_set_data->cc_on = set_vis_switch(ce_set_data->cc_on, vis);
			break;
		case ID_CE_BUTTON_5:
			if(flag)
			{
				if(ce_set_data->ce_gain == 255)
					ce_set_data->ce_gain = 0;
				else 
					ce_set_data->ce_gain ++;
			}
			else
			{
				if(ce_set_data->ce_gain == 0)
					ce_set_data->ce_gain = 255;
				else 
					ce_set_data->ce_gain --;
			}

			vis = d_frame_get_control(frm, ID_CE_LABEL_5);
			if(vis)
			{
				sprintf(ce_set_data->ce_gain_buf, "%d", ce_set_data->ce_gain);
				d_label_set_text(vis, ce_set_data->ce_gain_buf);
			}
			break;
		case ID_CE_BUTTON_6:
			if(flag)
			{
				if(ce_set_data->bbd_mode == 2)
					ce_set_data->bbd_mode = 0;
				else 
					ce_set_data->bbd_mode ++;
			}
			else
			{
				if(ce_set_data->bbd_mode == 0)
					ce_set_data->bbd_mode = 2;
				else 
					ce_set_data->bbd_mode --;
			}
			vis = d_frame_get_control(frm, ID_CE_LABEL_6);
			{
				d_label_set_text(vis, bbd_mode[ce_set_data->bbd_mode]);
			}
			break;
		case ID_CE_BUTTON_7:
			vis = d_frame_get_control(frm, ID_CE_LABEL_7);
			ce_set_data->histq_on= set_vis_switch(ce_set_data->histq_on, vis);
			break;
		case ID_CE_BUTTON_8:
			vis = d_frame_get_control(frm, ID_CE_LABEL_8);
			ce_set_data->ropc_on = set_vis_switch(ce_set_data->ropc_on, vis);
			break;
		default:
			break;
	}
	set_param_of_ce();
	return D_OK;
}


static D_Result
ce_on_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ce_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CE_LABEL_1);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ce_set_data(id, D_TRUE);
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
bs_on_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ce_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CE_LABEL_2);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ce_set_data(id, D_TRUE);
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
ws_on_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ce_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CE_LABEL_3);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ce_set_data(id, D_TRUE);
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
cc_on_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ce_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CE_LABEL_4);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ce_set_data(id, D_TRUE);
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
bbd_mode_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ce_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CE_LABEL_6);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ce_set_data(id, D_TRUE);
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
ce_gain_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ce_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CE_LABEL_5);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ce_set_data(id, D_TRUE);
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
histq_on_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ce_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CE_LABEL_7);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ce_set_data(id, D_TRUE);
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
ropc_on_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ce_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CE_LABEL_8);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ce_set_data(id, D_TRUE);
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
get_set_of_ce_set(void) D_FUNCPOSTFIT
{
	if(ce_set_data->hdflag)
    {
        p_tvconf_get_hdce_set_param(&ce_set_data->param, p_vip_get_dbinput(ce_set_data->input));
    }
    else
    {
        p_tvconf_get_ce_set_param(&ce_set_data->param, p_vip_get_dbinput(ce_set_data->input));
    }
	ce_set_data->ce_on= ce_set_data->param.ce_on;
	ce_set_data->bs_on= ce_set_data->param.bs_on;
	ce_set_data->ws_on= ce_set_data->param.ws_on;
	ce_set_data->cc_on= ce_set_data->param.cc_on;
	ce_set_data->bbd_mode= ce_set_data->param.bbd_mode;
	ce_set_data->ce_gain = ce_set_data->param.ce_gain;
	ce_set_data->histq_on= ce_set_data->param.histq_on;
	ce_set_data->ropc_on= ce_set_data->param.ropc_on;
	
	sprintf(ce_set_data->ce_gain_buf, "%d", ce_set_data->ce_gain);
	
	return D_OK;
}

static D_Result
ce_set_vis_set(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &ce_window;
    D_Visual *vis;

	vis = d_frame_get_control(frm, ID_CE_LABEL_CE);
	d_label_set_text(vis, "CE");

	vis = d_frame_get_control(frm, ID_CE_BUTTON_1);
	d_label_set_text(vis, "Ce On");
	d_vis_set_handler(vis, ce_on_handler);
	
	vis = d_frame_get_control(frm, ID_CE_BUTTON_2);
	d_label_set_text(vis, "Bs On");
	d_vis_set_handler(vis, bs_on_handler);

	vis = d_frame_get_control(frm, ID_CE_BUTTON_3);
	d_label_set_text(vis, "Ws On");
	d_vis_set_handler(vis, ws_on_handler);

	vis = d_frame_get_control(frm, ID_CE_BUTTON_4);
	d_label_set_text(vis, "Cc On");
	d_vis_set_handler(vis, cc_on_handler);

	vis = d_frame_get_control(frm, ID_CE_BUTTON_6);
	d_label_set_text(vis, "Bbd Mode");
	d_vis_set_handler(vis, bbd_mode_handler);

	vis = d_frame_get_control(frm, ID_CE_BUTTON_5);
	d_label_set_text(vis, "Ce Gain");
	d_vis_set_handler(vis, ce_gain_handler);

	vis = d_frame_get_control(frm, ID_CE_BUTTON_7);
	d_label_set_text(vis, "Histq On");
	d_vis_set_handler(vis, histq_on_handler);

	vis = d_frame_get_control(frm, ID_CE_BUTTON_8);
	d_label_set_text(vis, "Ropc On");
	d_vis_set_handler(vis, ropc_on_handler);
	
	vis = d_frame_get_control(frm, ID_CE_LABEL_1);
	vis_switch_init(ce_set_data->ce_on, vis);

	vis = d_frame_get_control(frm, ID_CE_LABEL_2);
	vis_switch_init(ce_set_data->bs_on, vis);
	
	vis = d_frame_get_control(frm, ID_CE_LABEL_3);
	vis_switch_init(ce_set_data->ws_on, vis);

	vis = d_frame_get_control(frm, ID_CE_LABEL_4);
	vis_switch_init(ce_set_data->cc_on, vis);

	vis = d_frame_get_control(frm, ID_CE_LABEL_7);
	vis_switch_init(ce_set_data->histq_on, vis);

	vis = d_frame_get_control(frm, ID_CE_LABEL_5);
	d_label_set_text(vis, ce_set_data->ce_gain_buf);

	vis = d_frame_get_control(frm, ID_CE_LABEL_6);
	d_label_set_text(vis, bbd_mode[ce_set_data->bbd_mode]);

	vis = d_frame_get_control(frm, ID_CE_LABEL_8);
	vis_switch_init(ce_set_data->ropc_on, vis);
	return D_OK;
}


static D_Result
ce_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{	
	D_Visual *fv;
	D_Frame *frm = &ce_window;
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
					set_ce_set_data(id, D_TRUE);
					break;
				case D_KEY_LEFT:
				case D_KEY_PNL_L:
					set_ce_set_data(id, D_FALSE);
					break;
				case D_KEY_MENU:
					return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
			save_param_of_ce();
			 if(ce_set_data)
            {
                PROJECT_FREE(ce_set_data);
                ce_set_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
ce_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

	ce_set_data = (D_CeSetDate*)PROJECT_ALLOC(sizeof(D_CeSetDate));
    if(!ce_set_data)
    {
        return D_ERR;
    }
	memset(ce_set_data, 0, sizeof(D_CeSetDate));
	ce_set_data->input = p_conf_get_vid_input();
	if(ce_set_data->input == D_VID_IUTPUT_AV1 || ce_set_data->input == D_VID_IUTPUT_AV2|| ce_set_data->input == D_VID_IUTPUT_TV)
	{
		ce_set_data->hdflag = p_vip_get_ntscflag();
	}
	else
	{
		ce_set_data->hdflag = p_vip_get_hdflag();
	}
	get_set_of_ce_set();
	ce_set_vis_set();

	vis = d_frame_get_control(frm, ID_CE_GROUP);
	if(vis)
	{
		d_group_set_focus_loop(vis, D_TRUE);
		d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
	}

	vis = d_frame_get_control(frm, 0);
	if(vis)
	{
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
		d_vis_set_handler(vis, ce_window_handler);
	}

    return D_OK;
}

/** @brief ce菜单*/
D_Result
p_atv_ce_set_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&ce_window, D_TRUE);
}
