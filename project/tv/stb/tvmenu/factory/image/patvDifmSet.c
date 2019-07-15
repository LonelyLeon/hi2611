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
#include "difm_set_window.c"

#define BUF_LINE 4

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus={{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal={{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
	D_S16 focus, di_si_on, di_ti_on, di_fc_on, fm_rescsd_on, fm_resc22_on, fm_resc32_on, fm_loc22_on, 
		fm_loc32_on, fm_usest_on, fm_loctic_mode, fm_clip32, fm_clip22, scl_bicubic, ci_2d_gn, 
		ci_tgn, ci_mgn, ci_bgn, di_dbg, cs_idx,  fm_fld_tgn, fm_fld_zgn, fm_frm_tgn, fm_frm_zgn;
	D_VidInput input;
	D_U8 hdflag;
	D_DIFM_SET param;
	
	D_Char fm_loctic_mode_buf[BUF_LINE];
	D_Char fm_clip32_buf[BUF_LINE];
	D_Char fm_clip22_buf[BUF_LINE];

	D_Char ci_2d_gn_buf[BUF_LINE];
	D_Char ci_tgn_buf[BUF_LINE];
	D_Char ci_mgn_buf[BUF_LINE];
	D_Char ci_bgn_buf[BUF_LINE];
	D_Char di_dbg_buf[BUF_LINE];
	D_Char cs_idx_buf[BUF_LINE];
	
	D_Char fm_fld_tgn_buf[BUF_LINE];
	D_Char fm_fld_zgn_buf[BUF_LINE];
	D_Char fm_frm_tgn_buf[BUF_LINE];
	D_Char fm_frm_zgn_buf[BUF_LINE];
}D_DifmSetDate;

static D_DifmSetDate *difm_set_data;
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
set_gn_value(D_S16 value, D_Bool flag)
{
	
	if(flag)
	{
		if(value == 16)
			value = 0;
		else
			value ++;
			
	}
	else 
	{
		if(value == 0)
			value = 16;
		else 
			value --;
	}
	return value;
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
save_param_of_difm(void) D_FUNCPOSTFIT
{
 	if(difm_set_data->hdflag)
    {
		p_tvconf_set_hddifm_set_param(&difm_set_data->param, p_vip_get_dbinput(difm_set_data->input));
    }
    else
    {
		p_tvconf_set_difm_set_param(&difm_set_data->param, p_vip_get_dbinput(difm_set_data->input));
    }
	return D_OK;
}

static D_Result
set_param_of_difm(void) D_FUNCPOSTFIT
{
	difm_set_data->param.di_si_on= difm_set_data->di_si_on;
	difm_set_data->param.di_ti_on= difm_set_data->di_ti_on;
	difm_set_data->param.di_fc_on= difm_set_data->di_fc_on;

	difm_set_data->param.fm_rescsd_on = difm_set_data->fm_rescsd_on;
	difm_set_data->param.fm_resc22_on = difm_set_data->fm_resc22_on;
	difm_set_data->param.fm_resc32_on = difm_set_data->fm_resc32_on;
	difm_set_data->param.fm_loc22_on = difm_set_data->fm_loc22_on;
	difm_set_data->param.fm_loc32_on = difm_set_data->fm_loc32_on;
	difm_set_data->param.fm_usest_on = difm_set_data->fm_usest_on;
	difm_set_data->param.fm_clip32 = difm_set_data->fm_clip32;
	difm_set_data->param.fm_clip22 = difm_set_data->fm_clip22;
	difm_set_data->param.fm_loctic_mode = difm_set_data->fm_loctic_mode;
	difm_set_data->param.scl_bicubic= difm_set_data->scl_bicubic;

	difm_set_data->param.ci_2d_gn= difm_set_data->ci_2d_gn;
	difm_set_data->param.ci_tgn= difm_set_data->ci_tgn;
	difm_set_data->param.ci_mgn= difm_set_data->ci_mgn;
	difm_set_data->param.ci_bgn= difm_set_data->ci_bgn;
	difm_set_data->param.di_dbg= difm_set_data->di_dbg;
	difm_set_data->param.cs_idx= difm_set_data->cs_idx;
	difm_set_data->param.fm_fld_tgn= difm_set_data->fm_fld_tgn;
	difm_set_data->param.fm_fld_zgn= difm_set_data->fm_fld_zgn;
	difm_set_data->param.fm_frm_tgn= difm_set_data->fm_frm_tgn;
	difm_set_data->param.fm_frm_zgn= difm_set_data->fm_frm_zgn;

	d_vip_setDifm((D_U8*)&difm_set_data->param);
	
	return D_OK;
}


static D_Result
set_difm_set_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
	D_Frame *frm = &difm_set_window;
    D_Visual *vis;
	
	switch(id)
	{
		case ID_DIFM_BUTTON_1:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_1);
				difm_set_data->di_si_on = set_vis_switch(difm_set_data->di_si_on, vis);
			}
			else 
			{
				if(flag)
				{
					if(difm_set_data->fm_clip22 == 5)
						difm_set_data->fm_clip22 = 0;
					else 
						difm_set_data->fm_clip22 ++;
				}
				else
				{
					if(difm_set_data->fm_clip22 == 0)
						difm_set_data->fm_clip22 = 5;
					else 
						difm_set_data->fm_clip22 --;
				}

				vis = d_frame_get_control(frm, ID_DIFM_LABEL_1);
				if(vis)
				{
					sprintf(difm_set_data->fm_clip22_buf, "%d", difm_set_data->fm_clip22);
					d_label_set_text(vis, difm_set_data->fm_clip22_buf);
				}
			}
			break;
		case ID_DIFM_BUTTON_2:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_2);
				difm_set_data->di_ti_on = set_vis_switch(difm_set_data->di_ti_on, vis);
			}
			else
			{
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_2);
				difm_set_data->scl_bicubic= set_vis_switch(difm_set_data->scl_bicubic, vis);
			}
			break;
		case ID_DIFM_BUTTON_3:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_3);
				difm_set_data->di_fc_on = set_vis_switch(difm_set_data->di_fc_on, vis);
			}
			else
			{
				if(flag)
				{
					if(difm_set_data->cs_idx== 2)
						difm_set_data->cs_idx = 0;
					else 
						difm_set_data->cs_idx ++;
				}
				else
				{
					if(difm_set_data->cs_idx == 0)
						difm_set_data->cs_idx = 2;
					else 
						difm_set_data->cs_idx --;
				}
				sprintf(difm_set_data->cs_idx_buf, "%d", difm_set_data->cs_idx);
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_3);
				
				d_label_set_text(vis, difm_set_data->cs_idx_buf);
			}
			break;
		case ID_DIFM_BUTTON_4:
			if(first_flag)
			{
				difm_set_data->ci_2d_gn= set_gn_value(difm_set_data->ci_2d_gn, flag);
				
				sprintf(difm_set_data->ci_2d_gn_buf, "%d", difm_set_data->ci_2d_gn);
				
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_4);
				d_label_set_text(vis, difm_set_data->ci_2d_gn_buf);
			}
			else 
			{
				if(flag)
				{
					if(difm_set_data->fm_fld_tgn== 31)
						difm_set_data->fm_fld_tgn = 0;
					else 
						difm_set_data->fm_fld_tgn ++;
				}
				else
				{
					if(difm_set_data->fm_fld_tgn == 0)
						difm_set_data->fm_fld_tgn = 31;
					else 
						difm_set_data->fm_fld_tgn --;
				}
				
				sprintf(difm_set_data->fm_fld_tgn_buf, "%d", difm_set_data->fm_fld_tgn);
				
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_4);
				d_label_set_text(vis, difm_set_data->fm_fld_tgn_buf);
			}
			break;
		case ID_DIFM_BUTTON_5:
			if(first_flag)
			{
				difm_set_data->ci_tgn= set_gn_value(difm_set_data->ci_tgn, flag);
				
				sprintf(difm_set_data->ci_tgn_buf, "%d", difm_set_data->ci_tgn);
				
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_5);
				d_label_set_text(vis, difm_set_data->ci_tgn_buf);
			}
			else 
			{
				if(flag)
				{
					if(difm_set_data->fm_fld_zgn== 255)
						difm_set_data->fm_fld_zgn = 0;
					else 
						difm_set_data->fm_fld_zgn ++;
				}
				else
				{
					if(difm_set_data->fm_fld_zgn == 0)
						difm_set_data->fm_fld_zgn = 255;
					else 
						difm_set_data->fm_fld_zgn --;
				}
				
				sprintf(difm_set_data->fm_fld_zgn_buf, "%d", difm_set_data->fm_fld_zgn);
				
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_5);
				d_label_set_text(vis, difm_set_data->fm_fld_zgn_buf);
			}
			break;
		case ID_DIFM_BUTTON_6:
			if(first_flag)
			{
				difm_set_data->ci_mgn= set_gn_value(difm_set_data->ci_mgn, flag);
				
				sprintf(difm_set_data->ci_mgn_buf, "%d", difm_set_data->ci_mgn);
				
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_6);
				d_label_set_text(vis, difm_set_data->ci_mgn_buf);
			}
			else 
			{
				if(flag)
				{
					if(difm_set_data->fm_frm_tgn== 31)
						difm_set_data->fm_frm_tgn = 0;
					else 
						difm_set_data->fm_frm_tgn ++;
				}
				else
				{
					if(difm_set_data->fm_frm_tgn == 0)
						difm_set_data->fm_frm_tgn = 31;
					else 
						difm_set_data->fm_frm_tgn --;
				}
				
				sprintf(difm_set_data->fm_frm_tgn_buf, "%d", difm_set_data->fm_frm_tgn);
				
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_6);
				d_label_set_text(vis, difm_set_data->fm_frm_tgn_buf);
			}
			break;
		case ID_DIFM_BUTTON_7:
			if(first_flag)
			{
				difm_set_data->ci_bgn= set_gn_value(difm_set_data->ci_bgn, flag);
				
				sprintf(difm_set_data->ci_bgn_buf, "%d", difm_set_data->ci_bgn);
				
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_7);
				d_label_set_text(vis, difm_set_data->ci_bgn_buf);
			}
			else 
			{
				if(flag)
				{
					if(difm_set_data->fm_frm_zgn== 255)
						difm_set_data->fm_frm_zgn = 0;
					else 
						difm_set_data->fm_frm_zgn ++;
				}
				else
				{
					if(difm_set_data->fm_frm_zgn == 0)
						difm_set_data->fm_frm_zgn = 255;
					else 
						difm_set_data->fm_frm_zgn --;
				}
				
				sprintf(difm_set_data->fm_frm_zgn_buf, "%d", difm_set_data->fm_frm_zgn);
				
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_7);
				d_label_set_text(vis, difm_set_data->fm_frm_zgn_buf);
			}
			break;
		case ID_DIFM_BUTTON_8:
			if(first_flag)
			{
				if(flag)
				{
					if(difm_set_data->di_dbg== 15)
						difm_set_data->di_dbg = 0;
					else 
						difm_set_data->di_dbg ++;
				}
				else
				{
					if(difm_set_data->di_dbg == 0)
						difm_set_data->di_dbg = 15;
					else 
						difm_set_data->di_dbg --;
				}
				
				sprintf(difm_set_data->di_dbg_buf, "%d", difm_set_data->di_dbg);
				
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_8);
				d_label_set_text(vis, difm_set_data->di_dbg_buf);
			}
			break;
		case ID_DIFM_BUTTON_9:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_9);
				difm_set_data->fm_rescsd_on = set_vis_switch(difm_set_data->fm_rescsd_on, vis);
			}
			break;
		case ID_DIFM_BUTTON_10:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_10);
				difm_set_data->fm_resc22_on = set_vis_switch(difm_set_data->fm_resc22_on, vis);
			}
			break;
		case ID_DIFM_BUTTON_11:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_11);
				difm_set_data->fm_resc32_on = set_vis_switch(difm_set_data->fm_resc32_on, vis);
			}
			break;
		case ID_DIFM_BUTTON_12:
			if(first_flag)
			{
				if(flag)
				{
					if(difm_set_data->fm_loctic_mode == 3)
						difm_set_data->fm_loctic_mode = 0;
					else 
						difm_set_data->fm_loctic_mode ++;
				}
				else
				{
					if(difm_set_data->fm_loctic_mode == 0)
						difm_set_data->fm_loctic_mode = 3;
					else 
						difm_set_data->fm_loctic_mode --;
				}

				vis = d_frame_get_control(frm, ID_DIFM_LABEL_12);
				if(vis)
				{
					sprintf(difm_set_data->fm_loctic_mode_buf, "%d", difm_set_data->fm_loctic_mode);
					d_label_set_text(vis, difm_set_data->fm_loctic_mode_buf);
				}
			}
			break;
		case ID_DIFM_BUTTON_13:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_13);
				difm_set_data->fm_loc22_on = set_vis_switch(difm_set_data->fm_loc22_on, vis);
			}
			break;
		case ID_DIFM_BUTTON_14:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_14);
				difm_set_data->fm_loc32_on = set_vis_switch(difm_set_data->fm_loc32_on, vis);
			}
			break;
		case ID_DIFM_BUTTON_15:
			if(first_flag)
			{
				vis = d_frame_get_control(frm, ID_DIFM_LABEL_15);
				difm_set_data->fm_usest_on = set_vis_switch(difm_set_data->fm_usest_on, vis);
			}
			break;
		case ID_DIFM_BUTTON_16:
			if(first_flag)
			{
				if(flag)
				{
					if(difm_set_data->fm_clip32 == 5)
						difm_set_data->fm_clip32 = 0;
					else 
						difm_set_data->fm_clip32 ++;
				}
				else
				{
					if(difm_set_data->fm_clip32 == 0)
						difm_set_data->fm_clip32 = 5;
					else 
						difm_set_data->fm_clip32 --;
				}

				vis = d_frame_get_control(frm, ID_DIFM_LABEL_16);
				if(vis)
				{
					sprintf(difm_set_data->fm_clip32_buf, "%d", difm_set_data->fm_clip32);
					d_label_set_text(vis, difm_set_data->fm_clip32_buf);
				}
			}
			break;
		default:
			break;
	}
	set_param_of_difm();

	return D_OK;
}


static D_Result
button_1_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_1);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_2);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_3);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_4);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_5);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_6);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_7);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_8);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_9);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_10);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_11);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_12);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_13);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_14);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_15);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
	D_Frame *frm = &difm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DIFM_LABEL_16);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_difm_set_data(id, D_TRUE);
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
get_set_of_difm_set(void) D_FUNCPOSTFIT
{
	if(difm_set_data->hdflag)
    {
        p_tvconf_get_hddifm_set_param(&difm_set_data->param, p_vip_get_dbinput(difm_set_data->input));
    }
    else
    {
        p_tvconf_get_difm_set_param(&difm_set_data->param, p_vip_get_dbinput(difm_set_data->input));
    }
	
	difm_set_data->di_si_on= difm_set_data->param.di_si_on;
	difm_set_data->di_ti_on= difm_set_data->param.di_ti_on;
	difm_set_data->di_fc_on= difm_set_data->param.di_fc_on;
	difm_set_data->fm_rescsd_on= difm_set_data->param.fm_rescsd_on;
	difm_set_data->fm_resc22_on= difm_set_data->param.fm_resc22_on;
	difm_set_data->fm_resc32_on= difm_set_data->param.fm_resc32_on;
	difm_set_data->fm_loc22_on= difm_set_data->param.fm_loc22_on;

	difm_set_data->fm_loc32_on= difm_set_data->param.fm_loc32_on;
	difm_set_data->fm_usest_on= difm_set_data->param.fm_usest_on;
	difm_set_data->fm_clip32= difm_set_data->param.fm_clip32;
	difm_set_data->fm_clip22= difm_set_data->param.fm_clip22;
	difm_set_data->fm_loctic_mode= difm_set_data->param.fm_loctic_mode;
	difm_set_data->scl_bicubic= difm_set_data->param.scl_bicubic;

	difm_set_data->ci_2d_gn= difm_set_data->param.ci_2d_gn;
	difm_set_data->ci_tgn= difm_set_data->param.ci_tgn;
	difm_set_data->ci_mgn= difm_set_data->param.ci_mgn;
	difm_set_data->ci_bgn= difm_set_data->param.ci_bgn;
	difm_set_data->di_dbg= difm_set_data->param.di_dbg;
	difm_set_data->cs_idx= difm_set_data->param.cs_idx;

	difm_set_data->fm_fld_tgn= difm_set_data->param.fm_fld_tgn;
	difm_set_data->fm_fld_zgn= difm_set_data->param.fm_fld_zgn;
	difm_set_data->fm_frm_tgn= difm_set_data->param.fm_frm_tgn;
	difm_set_data->fm_frm_zgn= difm_set_data->param.fm_frm_zgn;
		

	sprintf(difm_set_data->fm_loctic_mode_buf, "%d", difm_set_data->fm_loctic_mode);
	sprintf(difm_set_data->fm_clip32_buf, "%d", difm_set_data->fm_clip32);
	sprintf(difm_set_data->fm_clip22_buf, "%d", difm_set_data->fm_clip22);
	sprintf(difm_set_data->ci_2d_gn_buf, "%d", difm_set_data->ci_2d_gn);
	sprintf(difm_set_data->ci_tgn_buf, "%d", difm_set_data->ci_tgn);
	sprintf(difm_set_data->ci_mgn_buf, "%d", difm_set_data->ci_mgn);
	sprintf(difm_set_data->ci_bgn_buf, "%d", difm_set_data->ci_bgn);
	sprintf(difm_set_data->di_dbg_buf, "%d", difm_set_data->di_dbg);
	sprintf(difm_set_data->cs_idx_buf, "%d", difm_set_data->cs_idx);

	sprintf(difm_set_data->fm_fld_tgn_buf, "%d", difm_set_data->fm_fld_tgn);
	sprintf(difm_set_data->fm_fld_zgn_buf, "%d", difm_set_data->fm_fld_zgn);
	sprintf(difm_set_data->fm_frm_tgn_buf, "%d", difm_set_data->fm_frm_tgn);
	sprintf(difm_set_data->fm_frm_zgn_buf, "%d", difm_set_data->fm_frm_zgn);
	
	return D_OK;
}

static D_Result
set_first_page_show(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &difm_set_window;
    D_Visual *vis;
	D_ID i;

	first_flag = D_TRUE;
	second_flag = D_FALSE;

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_DIFM);
	d_label_set_text(vis, "DI/FM");
	
	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_1);
	d_label_set_text(vis, "Di Si On");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_2);
	d_label_set_text(vis, "Di Ti On");
	
	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_3);
	d_label_set_text(vis, "Di Fc On");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_4);
	d_label_set_text(vis, "Ci 2d Gn");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_5);
	d_label_set_text(vis, "Ci Tgn");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_6);
	d_label_set_text(vis, "Ci Mgn");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_7);
	d_label_set_text(vis, "Ci Bgn");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_8);
	d_label_set_text(vis, "Di Dbg");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_9);
	d_label_set_text(vis, "Fm Rescsd On");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_10);
	d_label_set_text(vis, "Fm Resc22 On");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_11);
	d_label_set_text(vis, "Fm Resc32 On");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_12);
	d_label_set_text(vis, "Fm Loctic Mode");
	
	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_13);
	d_label_set_text(vis, "Fm Loc22 On");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_14);
	d_label_set_text(vis, "Fm Loc32 On");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_15);
	d_label_set_text(vis, "Fm Usest On");
	
	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_16);
	d_label_set_text(vis, "Fm Clip32");
	

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_1);
	vis_switch_init(difm_set_data->di_si_on,vis);
	
	vis = d_frame_get_control(frm, ID_DIFM_LABEL_2);
	vis_switch_init(difm_set_data->di_ti_on,vis);
	
	vis = d_frame_get_control(frm, ID_DIFM_LABEL_3);
	vis_switch_init(difm_set_data->di_fc_on,vis);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_4);
	d_label_set_text(vis, difm_set_data->ci_2d_gn_buf);
	
	vis = d_frame_get_control(frm, ID_DIFM_LABEL_5);
	d_label_set_text(vis, difm_set_data->ci_tgn_buf);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_6);
	d_label_set_text(vis, difm_set_data->ci_mgn_buf);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_7);
	d_label_set_text(vis, difm_set_data->ci_bgn_buf);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_8);
	d_label_set_text(vis, difm_set_data->di_dbg_buf);
	
	vis = d_frame_get_control(frm, ID_DIFM_LABEL_9);
	vis_switch_init(difm_set_data->fm_rescsd_on,vis);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_10);
	vis_switch_init(difm_set_data->fm_resc22_on,vis);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_11);
	vis_switch_init(difm_set_data->fm_resc32_on,vis);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_12);
	d_label_set_text(vis, difm_set_data->fm_loctic_mode_buf);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_13);
	vis_switch_init(difm_set_data->fm_loc22_on,vis);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_14);
	vis_switch_init(difm_set_data->fm_loc32_on,vis);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_15);
	vis_switch_init(difm_set_data->fm_usest_on,vis);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_16);
	d_label_set_text(vis, difm_set_data->fm_clip32_buf);


	for(i = ID_DIFM_GROUP_8; i <= ID_DIFM_GROUP_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_vis_enable(vis, D_TRUE);
	}

	for(i = ID_DIFM_BUTTON_8; i <= ID_DIFM_BUTTON_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_vis_set_focusable(vis, D_TRUE);
	}
	
	return D_OK;
}

static D_Result
set_second_page_show(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &difm_set_window;
    D_Visual *vis;
	D_ID i;

	second_flag = D_TRUE;
	first_flag = D_FALSE;

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_1);
	d_label_set_text(vis, "Fm Clip22");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_2);
	d_label_set_text(vis, "Scl Bicubic");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_3);
	d_label_set_text(vis, "Cs Idx");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_4);
	d_label_set_text(vis, "Fm Fld Tgn");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_5);
	d_label_set_text(vis, "Fm Fld Zgn");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_6);
	d_label_set_text(vis, "Fm Frm Tgn");

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_7);
	d_label_set_text(vis, "Fm Frm Zgn");

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_1);
	d_label_set_text(vis, difm_set_data->fm_clip22_buf);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_2);
	vis_switch_init(difm_set_data->scl_bicubic, vis);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_3);
	d_label_set_text(vis, difm_set_data->cs_idx_buf);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_4);
	d_label_set_text(vis, difm_set_data->fm_fld_tgn_buf);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_5);
	d_label_set_text(vis, difm_set_data->fm_fld_zgn_buf);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_6);
	d_label_set_text(vis, difm_set_data->fm_frm_tgn_buf);

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_7);
	d_label_set_text(vis, difm_set_data->fm_frm_zgn_buf);

	
	for(i = ID_DIFM_GROUP_8; i <= ID_DIFM_GROUP_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_vis_enable(vis, D_FALSE);
	}

	for(i = ID_DIFM_BUTTON_8; i <= ID_DIFM_BUTTON_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_label_set_text(vis, NULL);
		d_vis_set_focusable(vis, D_FALSE);
	}

	for(i = ID_DIFM_LABEL_8; i <= ID_DIFM_LABEL_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_label_set_text(vis, NULL);
	}
	
	return D_OK;
}

static D_Result
difm_set_vis_handler(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &difm_set_window;
    D_Visual *vis;

	vis = d_frame_get_control(frm, ID_DIFM_LABEL_DIFM);
	d_label_set_text(vis, "DIFM");
	
	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_1);
	d_vis_set_handler(vis, button_1_set_handler);

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_2);
	d_vis_set_handler(vis, button_2_set_handler);
	
	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_3);
	d_vis_set_handler(vis, button_3_set_handler);

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_4);
	d_vis_set_handler(vis, button_4_set_handler);

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_5);
	d_vis_set_handler(vis, button_5_set_handler);

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_6);
	d_vis_set_handler(vis, button_6_set_handler);

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_7);
	d_vis_set_handler(vis, button_7_set_handler);

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_8);
	d_vis_set_handler(vis, button_8_set_handler);

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_9);
	d_vis_set_handler(vis, button_9_set_handler);

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_10);
	d_vis_set_handler(vis, button_10_set_handler);

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_11);
	d_vis_set_handler(vis, button_11_set_handler);
	
	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_12);
	d_vis_set_handler(vis, button_12_set_handler);

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_13);
	d_vis_set_handler(vis, button_13_set_handler);
	
	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_14);
	d_vis_set_handler(vis, button_14_set_handler);

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_15);
	d_vis_set_handler(vis, button_15_set_handler);

	vis = d_frame_get_control(frm, ID_DIFM_BUTTON_16);
	d_vis_set_handler(vis, button_16_set_handler);

	return D_OK;
}

static D_Result
difm_set_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{	
	D_Visual *fv;
	D_Frame *frm = &difm_set_window;
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
					if(difm_set_data->focus == ID_DIFM_BUTTON_1 && first_flag)
					{
						set_second_page_show();
						difm_set_data->focus = ID_DIFM_BUTTON_7;
					}
					else if(difm_set_data->focus == ID_DIFM_BUTTON_1 && second_flag)
					{
						set_first_page_show();
						difm_set_data->focus = ID_DIFM_BUTTON_16;
					}
					else
					{
						difm_set_data->focus--;	
					}
					d_vis_set_focus(d_frame_get_control(frm, difm_set_data->focus));
					break;
				case D_KEY_DOWN:
				case D_KEY_PNL_D:
					if(difm_set_data->focus == ID_DIFM_BUTTON_7 && second_flag)
					{
						set_first_page_show();
						difm_set_data->focus = ID_DIFM_BUTTON_1;
					}
					else if(difm_set_data->focus == ID_DIFM_BUTTON_16 && first_flag)
					{
						difm_set_data->focus = ID_DIFM_BUTTON_1;
						set_second_page_show();
					}
					else 
					{
						difm_set_data->focus++;
					}
					d_vis_set_focus(d_frame_get_control(frm, difm_set_data->focus));
					break;
				case D_KEY_RIGHT:
				case D_KEY_PNL_R:
					set_difm_set_data(id, D_TRUE);
					break;
				case D_KEY_LEFT:
				case D_KEY_PNL_L:
					set_difm_set_data(id, D_FALSE);
					break;
				case D_KEY_MENU:
					return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
			save_param_of_difm();
			 if(difm_set_data)
            {
                PROJECT_FREE(difm_set_data);
                difm_set_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
difm_set_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

	difm_set_data = (D_DifmSetDate*)PROJECT_ALLOC(sizeof(D_DifmSetDate));
    if(!difm_set_data)
    {
        return D_ERR;
    }
	memset(difm_set_data, 0, sizeof(D_DifmSetDate));
	
	difm_set_data->input = p_conf_get_vid_input();
	if(difm_set_data->input == D_VID_IUTPUT_AV1 || difm_set_data->input == D_VID_IUTPUT_AV2|| difm_set_data->input == D_VID_IUTPUT_TV)
	{
		difm_set_data->hdflag = p_vip_get_ntscflag();
	}
	else
	{
		difm_set_data->hdflag = p_vip_get_hdflag();
	}
	get_set_of_difm_set();
	set_first_page_show();
	difm_set_vis_handler();
	
	difm_set_data->focus = ID_DIFM_BUTTON_1;
	
	vis = d_frame_get_control(frm, ID_DIFM_GROUP);
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
		d_vis_set_handler(vis, difm_set_window_handler);
	}

    return D_OK;
}

/** @brief 	DI/FM菜单*/
D_Result
p_atv_difm_set_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&difm_set_window, D_TRUE);
}
