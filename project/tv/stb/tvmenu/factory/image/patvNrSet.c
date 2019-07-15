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
#include "nr_set_window.c"

#define BUF_LINE 4

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus={{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal={{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
	D_S16 focus, snr_on, snr_uv_on, snr_prev_on, snr_adp_on, snr_gain, snr_uv_gain, tnr_on, tnr_uv_on, tnr_upper,
		tnr_gain, tnr_dynrnd, md_core, md_gain, md_con,  mnr_on, mnr_db_thr, mnr_dr_thr, mnr_db_coeff, tnr_adp_on, md_pflt_on;
	D_U16          value;
	D_VidInput input;
	D_U8 hdflag;
	D_NR_SET param;
	
	D_Char snr_gain_buf[BUF_LINE];
	D_Char snr_uv_gain_buf[BUF_LINE];
	D_Char tnr_upper_buf[BUF_LINE];
	D_Char tnr_gain_buf[BUF_LINE];
	D_Char tnr_dynrnd_buf[BUF_LINE];
	D_Char md_core_buf[BUF_LINE];
	D_Char md_gain_buf[BUF_LINE];

	D_Char mnr_db_thr_buf[BUF_LINE];
	D_Char mnr_dr_thr_buf[BUF_LINE];
	D_Char mnr_db_coeff_buf[BUF_LINE];
}D_NrSetDate;

static D_NrSetDate *nr_set_data;
static D_Bool first_flag = D_TRUE;
static D_Bool second_flag = D_FALSE;

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
save_param_of_nr(void) D_FUNCPOSTFIT
{
	if(nr_set_data->hdflag)
	{
		p_tvconf_set_hdnr_set_param(&nr_set_data->param, p_vip_get_dbinput(nr_set_data->input), nr_set_data->value);
	}
	else
	{
		p_tvconf_set_nr_set_param(&nr_set_data->param, p_vip_get_dbinput(nr_set_data->input), nr_set_data->value);
	}
	return D_OK;
}

static D_Result
set_param_of_nr(void) D_FUNCPOSTFIT
{
	nr_set_data->param.snr_on= nr_set_data->snr_on;
	nr_set_data->param.snr_uv_on= nr_set_data->snr_uv_on;
	nr_set_data->param.snr_prev_on= nr_set_data->snr_prev_on;
	nr_set_data->param.snr_adp_on = nr_set_data->snr_adp_on;
	nr_set_data->param.tnr_on = nr_set_data->tnr_on;
	nr_set_data->param.tnr_uv_on= nr_set_data->tnr_uv_on;
	
	nr_set_data->param.mnr_on = nr_set_data->mnr_on;
	nr_set_data->param.snr_gain = nr_set_data->snr_gain;
	nr_set_data->param.snr_uv_gain = nr_set_data->snr_uv_gain;
	nr_set_data->param.tnr_upper = nr_set_data->tnr_upper;
	nr_set_data->param.tnr_gain = nr_set_data->tnr_gain;
	nr_set_data->param.md_gain = nr_set_data->md_gain;
	nr_set_data->param.md_con = nr_set_data->md_con;
	nr_set_data->param.tnr_dynrnd = nr_set_data->tnr_dynrnd;
	nr_set_data->param.md_core = nr_set_data->md_core;
	nr_set_data->param.mnr_db_thr= nr_set_data->mnr_db_thr;
	nr_set_data->param.mnr_dr_thr= nr_set_data->mnr_dr_thr;
	nr_set_data->param.mnr_db_coeff= nr_set_data->mnr_db_coeff;
	nr_set_data->param.tnr_adp_on= nr_set_data->tnr_adp_on;
	nr_set_data->param.md_pflt_on= nr_set_data->md_pflt_on;

	d_vip_setNr((D_U8*)&nr_set_data->param);
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

static D_S16
set_nr_set_value1(D_S16 value, D_Bool flag)
{
	
	if(flag)
	{
		if(value == 31)
			value = 0;
		else 
			value ++;
	}
	else
	{
		if(value == 0)
			value = 31;
		else 
			value --;
	}

	return value;
}

static D_S16
set_nr_set_value2(D_S16 value, D_Bool flag)
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
set_nr_set_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis;
	
	switch(id)
	{
		case ID_NR_BUTTON_1:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_NR_LABEL_1);
				if(nr_set_data->snr_on == 0)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
					nr_set_data->snr_on = 1;
				}
				else if(nr_set_data->snr_on == 1)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
					nr_set_data->snr_on = 0;
				}
			}
			else 
			{
				if(flag)
				{
					if(nr_set_data->mnr_dr_thr== 63)
						nr_set_data->mnr_dr_thr = 0;
					else 
						nr_set_data->mnr_dr_thr ++;
				}
				else 
				{
					if(nr_set_data->mnr_dr_thr == 0)
						nr_set_data->mnr_dr_thr = 63;
					else 
						nr_set_data->mnr_dr_thr --;
				}

				vis = d_frame_get_control(frm, ID_NR_LABEL_1);
				{
					sprintf(nr_set_data->mnr_dr_thr_buf, "%d", nr_set_data->mnr_dr_thr);
					d_label_set_text(vis, nr_set_data->mnr_dr_thr_buf);
				}
			}
			break;
		case ID_NR_BUTTON_2:
			if(first_flag)
			{
			
				vis = d_frame_get_control(frm, ID_NR_LABEL_2);
				if(nr_set_data->snr_uv_on == 0)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
					nr_set_data->snr_uv_on = 1;
				}
				else if(nr_set_data->snr_uv_on == 1)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
					nr_set_data->snr_uv_on = 0;
				}
			}
			else
			{
				if(flag)
				{
					if(nr_set_data->mnr_db_coeff== 15)
						nr_set_data->mnr_db_coeff = 0;
					else 
						nr_set_data->mnr_db_coeff ++;
				}
				else 
				{
					if(nr_set_data->mnr_db_coeff == 0)
						nr_set_data->mnr_db_coeff = 15;
					else 
						nr_set_data->mnr_db_coeff --;
				}

				vis = d_frame_get_control(frm, ID_NR_LABEL_2);
				{
					sprintf(nr_set_data->mnr_db_coeff_buf, "%d", nr_set_data->mnr_db_coeff);
					d_label_set_text(vis, nr_set_data->mnr_db_coeff_buf);
				}
			}
			break;
		case ID_NR_BUTTON_3:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_NR_LABEL_3);
				if(nr_set_data->snr_prev_on == 0)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
					nr_set_data->snr_prev_on = 1;
				}
				else if(nr_set_data->snr_prev_on == 1)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
					nr_set_data->snr_prev_on = 0;
				}
			}
			else
			{
				vis = d_frame_get_control(frm, ID_NR_LABEL_3);
				if(nr_set_data->tnr_adp_on== 0)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
					nr_set_data->tnr_adp_on = 1;
				}
				else if(nr_set_data->tnr_adp_on == 1)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
					nr_set_data->tnr_adp_on = 0;
				}
			}
			break;
		case ID_NR_BUTTON_4:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_NR_LABEL_4);
				if(nr_set_data->snr_adp_on == 0)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
					nr_set_data->snr_adp_on = 1;
				}
				else if(nr_set_data->snr_adp_on == 1)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
					nr_set_data->snr_adp_on = 0;
				}
			}
			else
			{
				vis = d_frame_get_control(frm, ID_NR_LABEL_4);
				if(nr_set_data->md_pflt_on== 0)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
					nr_set_data->md_pflt_on = 1;
				}
				else if(nr_set_data->md_pflt_on == 1)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
					nr_set_data->md_pflt_on = 0;
				}
			}
			break;
		case ID_NR_BUTTON_5:
			if(first_flag)
			{
				if(flag)
				{
					if(nr_set_data->snr_gain == 15)
						nr_set_data->snr_gain = 0;
					else 
						nr_set_data->snr_gain ++;
				}
				else 
				{
					if(nr_set_data->snr_gain == 0)
						nr_set_data->snr_gain = 15;
					else 
						nr_set_data->snr_gain --;
				}

				vis = d_frame_get_control(frm, ID_NR_LABEL_5);
				{
					sprintf(nr_set_data->snr_gain_buf, "%d", nr_set_data->snr_gain);
					d_label_set_text(vis, nr_set_data->snr_gain_buf);
				}
			}
			break;
		case ID_NR_BUTTON_6:
			if(first_flag)
			{
				nr_set_data->snr_uv_gain = set_nr_set_value1(nr_set_data->snr_uv_gain, flag);

				vis = d_frame_get_control(frm, ID_NR_LABEL_6);
				{
					sprintf(nr_set_data->snr_uv_gain_buf, "%d", nr_set_data->snr_uv_gain);
					d_label_set_text(vis, nr_set_data->snr_uv_gain_buf);
				}
			}
			break;
		case ID_NR_BUTTON_7:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_NR_LABEL_7);
				if(nr_set_data->tnr_on== 0)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
					nr_set_data->tnr_on = 1;
				}
				else if(nr_set_data->tnr_on == 1)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
					nr_set_data->tnr_on = 0;
				}
			}
			break;
		case ID_NR_BUTTON_8:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_NR_LABEL_8);
				if(nr_set_data->tnr_uv_on== 0)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
					nr_set_data->tnr_uv_on = 1;
				}
				else if(nr_set_data->tnr_uv_on == 1)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
					nr_set_data->tnr_uv_on = 0;
				}
			}
			break;
		case ID_NR_BUTTON_9:
			if(first_flag)
			{
				nr_set_data->tnr_upper= set_nr_set_value1(nr_set_data->tnr_upper, flag);

				vis = d_frame_get_control(frm, ID_NR_LABEL_9);
				{
					sprintf(nr_set_data->tnr_upper_buf, "%d", nr_set_data->tnr_upper);
					d_label_set_text(vis, nr_set_data->tnr_upper_buf);
				}
			}
			break;
		case ID_NR_BUTTON_10:
			if(first_flag)
			{
				nr_set_data->tnr_gain = set_nr_set_value1(nr_set_data->tnr_gain, flag);

				vis = d_frame_get_control(frm, ID_NR_LABEL_10);
				{
					sprintf(nr_set_data->tnr_gain_buf, "%d", nr_set_data->tnr_gain);
					d_label_set_text(vis, nr_set_data->tnr_gain_buf);
				}
			}
			break;
		case ID_NR_BUTTON_11:
			if(first_flag)
			{
				if(flag)
				{
					if(nr_set_data->tnr_dynrnd == 3)
						nr_set_data->tnr_dynrnd = 0;
					else 
						nr_set_data->tnr_dynrnd ++;
				}
				else 
				{
					if(nr_set_data->tnr_dynrnd == 0)
						nr_set_data->tnr_dynrnd = 3;
					else 
						nr_set_data->tnr_dynrnd --;
				}

				vis = d_frame_get_control(frm, ID_NR_LABEL_11);
				{
					sprintf(nr_set_data->tnr_dynrnd_buf, "%d", nr_set_data->tnr_dynrnd);
					d_label_set_text(vis, nr_set_data->tnr_dynrnd_buf);
				}
			}
			break;
		case ID_NR_BUTTON_12:
			if(first_flag)
			{
				nr_set_data->md_core = set_nr_set_value2(nr_set_data->md_core, flag);

				vis = d_frame_get_control(frm, ID_NR_LABEL_12);
				{
					sprintf(nr_set_data->md_core_buf, "%d", nr_set_data->md_core);
					d_label_set_text(vis, nr_set_data->md_core_buf);
				}
			}
			break;
		case ID_NR_BUTTON_13:
			if(first_flag)
			{
				nr_set_data->md_gain = set_nr_set_value2(nr_set_data->md_gain, flag);

				vis = d_frame_get_control(frm, ID_NR_LABEL_13);
				{
					sprintf(nr_set_data->md_gain_buf, "%d", nr_set_data->md_gain);
					d_label_set_text(vis, nr_set_data->md_gain_buf);
				}
			}
			break;
		case ID_NR_BUTTON_14:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_NR_LABEL_14);
				if(nr_set_data->md_con== 0)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
					nr_set_data->md_con = 1;
				}
				else if(nr_set_data->md_con == 1)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
					nr_set_data->md_con = 0;
				}
			}
			break;
		case ID_NR_BUTTON_15:
			vis = d_frame_get_control(frm, ID_NR_LABEL_15);
			if(nr_set_data->mnr_on== 0)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
				nr_set_data->mnr_on = 1;
			}
			else if(nr_set_data->mnr_on == 1)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
				nr_set_data->mnr_on = 0;
			}
			break;
		case ID_NR_BUTTON_16:
			nr_set_data->mnr_db_thr= set_nr_set_value2(nr_set_data->mnr_db_thr, flag);

			vis = d_frame_get_control(frm, ID_NR_LABEL_16);
			{
				sprintf(nr_set_data->mnr_db_thr_buf, "%d", nr_set_data->mnr_db_thr);
				d_label_set_text(vis, nr_set_data->mnr_db_thr_buf);
			}
			break;
		default:
			break;
	}
	set_param_of_nr();

	return D_OK;
}

static D_Result
button_1_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_1);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
			break;
		case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
	d_gui_update();
    return D_OK;
}

static D_Result
button_2_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_2);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
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
button_3_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_3);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
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
button_4_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_4);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
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
button_5_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_5);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
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
button_6_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_6);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
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
button_7_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_7);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
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
button_8_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_8);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
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
button_9_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_9);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
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
button_10_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_10);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
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
button_11_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_11);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
			break;
		case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}static D_Result
button_12_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_12);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
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
button_13_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_13);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
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
button_14_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_14);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
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
button_15_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_15);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
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
button_16_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_NR_LABEL_16);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_nr_set_data(id, D_TRUE);
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
get_set_of_nr_set(void) D_FUNCPOSTFIT
{
	if(nr_set_data->hdflag)
    {
        p_tvconf_get_hdnr_set_param(&nr_set_data->param, p_vip_get_dbinput(nr_set_data->input), nr_set_data->value);
    }
    else
    {
        p_tvconf_get_nr_set_param(&nr_set_data->param, p_vip_get_dbinput(nr_set_data->input), nr_set_data->value);
    }

	nr_set_data->snr_on= nr_set_data->param.snr_on;
	nr_set_data->snr_uv_on= nr_set_data->param.snr_uv_on;
	nr_set_data->snr_prev_on= nr_set_data->param.snr_prev_on;
	nr_set_data->snr_adp_on = nr_set_data->param.snr_adp_on;
	nr_set_data->tnr_on = nr_set_data->param.tnr_on;
	nr_set_data->tnr_uv_on= nr_set_data->param.tnr_uv_on;

	nr_set_data->mnr_on = nr_set_data->param.mnr_on;
	nr_set_data->md_con = nr_set_data->param.md_con;
	nr_set_data->snr_gain = nr_set_data->param.snr_gain;
	nr_set_data->snr_uv_gain = nr_set_data->param.snr_uv_gain;
	nr_set_data->tnr_upper = nr_set_data->param.tnr_upper;
	nr_set_data->tnr_gain = nr_set_data->param.tnr_gain;
	nr_set_data->md_gain = nr_set_data->param.md_gain;
	nr_set_data->tnr_dynrnd = nr_set_data->param.tnr_dynrnd;
	nr_set_data->md_core = nr_set_data->param.md_core;
	nr_set_data->mnr_db_thr= nr_set_data->param.mnr_db_thr;
	nr_set_data->mnr_dr_thr= nr_set_data->param.mnr_dr_thr;
	nr_set_data->mnr_db_coeff= nr_set_data->param.mnr_db_coeff;	
	nr_set_data->tnr_adp_on= nr_set_data->param.tnr_adp_on;	
	nr_set_data->md_pflt_on= nr_set_data->param.md_pflt_on;	
	
	sprintf(nr_set_data->snr_gain_buf, "%d", nr_set_data->snr_gain);
	sprintf(nr_set_data->snr_uv_gain_buf, "%d", nr_set_data->snr_uv_gain);
	sprintf(nr_set_data->tnr_upper_buf, "%d", nr_set_data->tnr_upper);
	sprintf(nr_set_data->tnr_gain_buf, "%d", nr_set_data->tnr_gain);
	sprintf(nr_set_data->tnr_dynrnd_buf, "%d", nr_set_data->tnr_dynrnd);
	sprintf(nr_set_data->md_core_buf, "%d", nr_set_data->md_core);
	sprintf(nr_set_data->md_gain_buf, "%d", nr_set_data->md_gain);
	sprintf(nr_set_data->mnr_db_thr_buf, "%d", nr_set_data->mnr_db_thr);
	sprintf(nr_set_data->mnr_dr_thr_buf, "%d", nr_set_data->mnr_dr_thr);
	sprintf(nr_set_data->mnr_db_coeff_buf, "%d", nr_set_data->mnr_db_coeff);
	
	return D_OK;
}

static D_Result
set_first_page_show(void) D_FUNCPOSTFIT
{ 
	D_Frame *frm = &nr_set_window;
    D_Visual *vis;
	D_ID i;

	first_flag = D_TRUE;
	second_flag = D_FALSE;

		vis = d_frame_get_control(frm, ID_NR_LABEL_NR);
	d_label_set_text(vis, "NR");
	
	vis = d_frame_get_control(frm, ID_NR_BUTTON_1);
	d_label_set_text(vis, "Snr On");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_2);
	d_label_set_text(vis, "Snr Uv On");
	
	vis = d_frame_get_control(frm, ID_NR_BUTTON_3);
	d_label_set_text(vis, "Snr Prev On");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_4);
	d_label_set_text(vis, "Snr Adp On");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_5);
	d_label_set_text(vis, "Snr Gain");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_6);
	d_label_set_text(vis, "snr_uv_gain");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_7);
	d_label_set_text(vis, "Tnr On");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_8);
	d_label_set_text(vis, "Tnr Uv On");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_9);
	d_label_set_text(vis, "Tur Upper");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_10);
	d_label_set_text(vis, "Tur Gain");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_11);
	d_label_set_text(vis, "Tnr Dynrnd");
	
	vis = d_frame_get_control(frm, ID_NR_BUTTON_12);
	d_label_set_text(vis, "Md Core");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_13);
	d_label_set_text(vis, "Md Gain");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_14);
	d_label_set_text(vis, "Md Con");
	
	vis = d_frame_get_control(frm, ID_NR_BUTTON_15);
	d_label_set_text(vis, "Mnr On");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_16);
	d_label_set_text(vis, "Mnr Db Thr");

	vis = d_frame_get_control(frm, ID_NR_LABEL_1);
	vis_switch_init(nr_set_data->snr_on,vis);
	
	vis = d_frame_get_control(frm, ID_NR_LABEL_2);
	vis_switch_init(nr_set_data->snr_uv_on,vis);
	
	vis = d_frame_get_control(frm, ID_NR_LABEL_3);
	vis_switch_init(nr_set_data->snr_prev_on,vis);

	vis = d_frame_get_control(frm, ID_NR_LABEL_4);
	vis_switch_init(nr_set_data->snr_adp_on,vis);

	vis = d_frame_get_control(frm, ID_NR_LABEL_5);
	d_label_set_text(vis, nr_set_data->snr_gain_buf);

	vis = d_frame_get_control(frm, ID_NR_LABEL_6);
	d_label_set_text(vis, nr_set_data->snr_uv_gain_buf);

	vis = d_frame_get_control(frm, ID_NR_LABEL_7);
	vis_switch_init(nr_set_data->tnr_on,vis);

	vis = d_frame_get_control(frm, ID_NR_LABEL_8);
	vis_switch_init(nr_set_data->tnr_uv_on,vis);

	vis = d_frame_get_control(frm, ID_NR_LABEL_9);
	d_label_set_text(vis, nr_set_data->tnr_upper_buf);

	vis = d_frame_get_control(frm, ID_NR_LABEL_10);
	d_label_set_text(vis, nr_set_data->tnr_gain_buf);

	vis = d_frame_get_control(frm, ID_NR_LABEL_11);
	d_label_set_text(vis, nr_set_data->tnr_dynrnd_buf);

	vis = d_frame_get_control(frm, ID_NR_LABEL_12);
	d_label_set_text(vis, nr_set_data->md_core_buf);

	vis = d_frame_get_control(frm, ID_NR_LABEL_13);
	d_label_set_text(vis, nr_set_data->md_gain_buf);

	vis = d_frame_get_control(frm, ID_NR_LABEL_14);
	vis_switch_init(nr_set_data->md_con,vis);
	
	vis = d_frame_get_control(frm, ID_NR_LABEL_15);
	vis_switch_init(nr_set_data->mnr_on,vis);

	vis = d_frame_get_control(frm, ID_NR_LABEL_16);
	d_label_set_text(vis, nr_set_data->mnr_db_thr_buf);

	for(i = ID_NR_GROUP_5; i <= ID_NR_GROUP_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_vis_enable(vis, D_TRUE);
	}

	for(i = ID_NR_BUTTON_5; i <= ID_NR_BUTTON_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_vis_set_focusable(vis, D_TRUE);
	}
	
	return D_OK;
}

static D_Result
set_second_page_show(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis;
	D_ID i;

	second_flag = D_TRUE;
	first_flag = D_FALSE;

	vis = d_frame_get_control(frm, ID_NR_BUTTON_1);
	d_label_set_text(vis, "Mnr Dr Thr");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_2);
	d_label_set_text(vis, "Mnr Db Coeff");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_3);
	d_label_set_text(vis, "Tnr Adp On");

	vis = d_frame_get_control(frm, ID_NR_BUTTON_4);
	d_label_set_text(vis, "Md Pflt On");

	vis = d_frame_get_control(frm, ID_NR_LABEL_1);
	d_label_set_text(vis, nr_set_data->mnr_dr_thr_buf);
	
	vis = d_frame_get_control(frm, ID_NR_LABEL_2);
	d_label_set_text(vis, nr_set_data->mnr_db_coeff_buf);

	vis = d_frame_get_control(frm, ID_NR_LABEL_3);
	vis_switch_init(nr_set_data->tnr_adp_on,vis);
	
	vis = d_frame_get_control(frm, ID_NR_LABEL_4);
	vis_switch_init(nr_set_data->md_pflt_on,vis);

	for(i = ID_NR_GROUP_5; i <= ID_NR_GROUP_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_vis_enable(vis, D_FALSE);
	}

	for(i = ID_NR_BUTTON_5; i <= ID_NR_BUTTON_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_label_set_text(vis, NULL);
		d_vis_set_focusable(vis, D_FALSE);
	}

	for(i = ID_NR_LABEL_5; i <= ID_NR_LABEL_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_label_set_text(vis, NULL);
	}
	
	return D_OK;
}

static D_Result
nr_set_vis_handler(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &nr_set_window;
    D_Visual *vis;

	vis = d_frame_get_control(frm, ID_NR_LABEL_NR);
	d_label_set_text(vis, "NR");
	
	vis = d_frame_get_control(frm, ID_NR_BUTTON_1);
	d_vis_set_handler(vis, button_1_set_handler);

	vis = d_frame_get_control(frm, ID_NR_BUTTON_2);
	d_vis_set_handler(vis, button_2_set_handler);
	
	vis = d_frame_get_control(frm, ID_NR_BUTTON_3);
	d_vis_set_handler(vis, button_3_set_handler);

	vis = d_frame_get_control(frm, ID_NR_BUTTON_4);
	d_vis_set_handler(vis, button_4_set_handler);

	vis = d_frame_get_control(frm, ID_NR_BUTTON_5);
	d_vis_set_handler(vis, button_5_set_handler);

	vis = d_frame_get_control(frm, ID_NR_BUTTON_6);
	d_vis_set_handler(vis, button_6_set_handler);

	vis = d_frame_get_control(frm, ID_NR_BUTTON_7);
	d_vis_set_handler(vis, button_7_set_handler);

	vis = d_frame_get_control(frm, ID_NR_BUTTON_8);
	d_vis_set_handler(vis, button_8_set_handler);

	vis = d_frame_get_control(frm, ID_NR_BUTTON_9);
	d_vis_set_handler(vis, button_9_set_handler);

	vis = d_frame_get_control(frm, ID_NR_BUTTON_10);
	d_vis_set_handler(vis, button_10_set_handler);

	vis = d_frame_get_control(frm, ID_NR_BUTTON_11);
	d_vis_set_handler(vis, button_11_set_handler);
	
	vis = d_frame_get_control(frm, ID_NR_BUTTON_12);
	d_vis_set_handler(vis, button_12_set_handler);

	vis = d_frame_get_control(frm, ID_NR_BUTTON_13);
	d_vis_set_handler(vis, button_13_set_handler);
	
	vis = d_frame_get_control(frm, ID_NR_BUTTON_14);
	d_vis_set_handler(vis, button_14_set_handler);

	vis = d_frame_get_control(frm, ID_NR_BUTTON_15);
	d_vis_set_handler(vis, button_15_set_handler);

	vis = d_frame_get_control(frm, ID_NR_BUTTON_16);
	d_vis_set_handler(vis, button_16_set_handler);

	return D_OK;
}


static D_Result
nr_set_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{	
	D_Visual *fv;
	D_Frame *frm = &nr_set_window;
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
				case D_KEY_UP:
				case D_KEY_PNL_U:

					if(nr_set_data->focus == ID_NR_BUTTON_1 && first_flag)
					{
						set_second_page_show();
						nr_set_data->focus = ID_NR_BUTTON_4;
					}
					else if(nr_set_data->focus == ID_NR_BUTTON_1 && second_flag)
					{
						set_first_page_show();
						nr_set_data->focus = ID_NR_BUTTON_16;
					}
					else
					{
						nr_set_data->focus--;	
					}
					d_vis_set_focus(d_frame_get_control(frm, nr_set_data->focus));
					break;
				case D_KEY_DOWN:
				case D_KEY_PNL_D:
					if(nr_set_data->focus == ID_NR_BUTTON_4 && second_flag)
					{
						set_first_page_show();
						nr_set_data->focus = ID_NR_BUTTON_1;
					}
					else if(nr_set_data->focus == ID_NR_BUTTON_16 && first_flag)
					{
						nr_set_data->focus = ID_NR_BUTTON_1;
						set_second_page_show();
					}
					else 
					{
						nr_set_data->focus++;
					}
					d_vis_set_focus(d_frame_get_control(frm, nr_set_data->focus));
					break;
				case D_KEY_RIGHT:
				case D_KEY_PNL_R:
					set_nr_set_data(id, D_TRUE);
					break;
				case D_KEY_LEFT:
				case D_KEY_PNL_L:
					set_nr_set_data(id, D_FALSE);
					break;
				case D_KEY_MENU:
					return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
			save_param_of_nr();
            
			 if(nr_set_data)
            {
                PROJECT_FREE(nr_set_data);
                nr_set_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
nr_set_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;
 	D_U8 val;
	
	nr_set_data = (D_NrSetDate*)PROJECT_ALLOC(sizeof(D_NrSetDate));
    if(!nr_set_data)
    {
        return D_ERR;
    }
	memset(nr_set_data, 0, sizeof(D_NrSetDate));
	nr_set_data->input = p_conf_get_vid_input();
	if(p_tvconf_get_cur_nrmode  (&val, p_vip_get_dbinput(nr_set_data->input) ) == D_OK )
    {
        nr_set_data->value = val;
    }
	if(nr_set_data->input == D_VID_IUTPUT_AV1 || nr_set_data->input == D_VID_IUTPUT_AV2|| nr_set_data->input == D_VID_IUTPUT_TV)
	{
		nr_set_data->hdflag = p_vip_get_ntscflag();
	}
	else
	{
		nr_set_data->hdflag = p_vip_get_hdflag();
	}
	nr_set_data->focus = ID_NR_BUTTON_1;
	get_set_of_nr_set();
	set_first_page_show();
	nr_set_vis_handler();
	
	vis = d_frame_get_control(frm, ID_NR_GROUP);
	if(vis)
	{
		d_group_set_focus_loop(vis, D_TRUE);
		d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
		d_vis_unsubscribe_one_evt(vis, D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
	}

	vis = d_frame_get_control(frm, 0);
	if(vis)
	{
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
		d_vis_set_handler(vis, nr_set_window_handler);
	}

    return D_OK;
}

/** @brief 	NR菜单*/
D_Result
p_atv_nr_set_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&nr_set_window, D_TRUE);
}
