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
#include "icm_set_window.c"

#define BUF_LINE 8

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus={{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal={{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
	D_S16 focus,icm_on, 
		icm_rhr, icm_ghr, icm_bhr, icm_chr, icm_mhr, icm_yhr, icm_xhr, 
		icm_rhm, icm_ghm, icm_bhm, icm_chm, icm_mhm, icm_yhm, icm_xhm,
		icm_rhp, icm_ghp, icm_bhp, icm_chp, icm_mhp, icm_yhp, icm_xhp,
		icm_rsp, icm_gsp, icm_bsp, icm_csp, icm_msp, icm_ysp, icm_xsp;
	D_VidInput input;
	D_U8 hdflag;
	D_ICM_SET param;
	
	D_Char icm_rhr_buf[BUF_LINE];
	D_Char icm_ghr_buf[BUF_LINE];
	D_Char icm_bhr_buf[BUF_LINE];
	D_Char icm_chr_buf[BUF_LINE];
	D_Char icm_mhr_buf[BUF_LINE];
	D_Char icm_yhr_buf[BUF_LINE];
	D_Char icm_xhr_buf[BUF_LINE];

	D_Char icm_rhm_buf[BUF_LINE];
	D_Char icm_ghm_buf[BUF_LINE];
	D_Char icm_bhm_buf[BUF_LINE];
	D_Char icm_chm_buf[BUF_LINE];
	D_Char icm_mhm_buf[BUF_LINE];
	D_Char icm_yhm_buf[BUF_LINE];
	D_Char icm_xhm_buf[BUF_LINE];

	D_Char icm_rhp_buf[BUF_LINE];
	D_Char icm_ghp_buf[BUF_LINE];
	D_Char icm_bhp_buf[BUF_LINE];
	D_Char icm_chp_buf[BUF_LINE];
	D_Char icm_mhp_buf[BUF_LINE];
	D_Char icm_yhp_buf[BUF_LINE];
	D_Char icm_xhp_buf[BUF_LINE];

	D_Char icm_rsp_buf[BUF_LINE];
	D_Char icm_gsp_buf[BUF_LINE];
	D_Char icm_bsp_buf[BUF_LINE];
	D_Char icm_csp_buf[BUF_LINE];
	D_Char icm_msp_buf[BUF_LINE];
	D_Char icm_ysp_buf[BUF_LINE];
	D_Char icm_xsp_buf[BUF_LINE];
}D_IcmSetDate;

static D_IcmSetDate *icm_set_data;
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
save_param_of_icm(void) D_FUNCPOSTFIT
{
	if(icm_set_data->hdflag)
    {
		p_tvconf_set_hdicm_set_param(&icm_set_data->param, p_vip_get_dbinput(icm_set_data->input));
    }
    else
    {
		p_tvconf_set_icm_set_param(&icm_set_data->param, p_vip_get_dbinput(icm_set_data->input));
    }
	return D_OK;
}

static D_Result
set_param_of_icm(void) D_FUNCPOSTFIT
{	
	icm_set_data->param.icm_on= icm_set_data->icm_on; 
	icm_set_data->param.icm_rhr= icm_set_data->icm_rhr; 
	icm_set_data->param.icm_ghr= icm_set_data->icm_ghr; 
	icm_set_data->param.icm_bhr= icm_set_data->icm_bhr; 
	icm_set_data->param.icm_chr= icm_set_data->icm_chr; 
	icm_set_data->param.icm_xhr= icm_set_data->icm_xhr; 
	icm_set_data->param.icm_mhr= icm_set_data->icm_mhr; 
	icm_set_data->param.icm_yhr= icm_set_data->icm_yhr; 
	icm_set_data->param.icm_rhm= icm_set_data->icm_rhm; 
	icm_set_data->param.icm_ghm= icm_set_data->icm_ghm; 
	icm_set_data->param.icm_bhm= icm_set_data->icm_bhm; 
	icm_set_data->param.icm_chm= icm_set_data->icm_chm; 
	icm_set_data->param.icm_xhm= icm_set_data->icm_xhm; 
	icm_set_data->param.icm_mhm= icm_set_data->icm_mhm; 
	icm_set_data->param.icm_yhm= icm_set_data->icm_yhm; 
	icm_set_data->param.icm_rhp= icm_set_data->icm_rhp; 
	icm_set_data->param.icm_ghp= icm_set_data->icm_ghp; 
	icm_set_data->param.icm_bhp= icm_set_data->icm_bhp;
	icm_set_data->param.icm_chp= icm_set_data->icm_chp; 
	icm_set_data->param.icm_xhp= icm_set_data->icm_xhp; 
	icm_set_data->param.icm_mhp= icm_set_data->icm_mhp; 
	icm_set_data->param.icm_yhp= icm_set_data->icm_yhp; 
	icm_set_data->param.icm_rsp= icm_set_data->icm_rsp; 
	icm_set_data->param.icm_gsp= icm_set_data->icm_gsp; 
	icm_set_data->param.icm_bsp= icm_set_data->icm_bsp; 
	icm_set_data->param.icm_csp= icm_set_data->icm_csp; 
	icm_set_data->param.icm_xsp= icm_set_data->icm_xsp; 
	icm_set_data->param.icm_msp= icm_set_data->icm_msp; 
	icm_set_data->param.icm_ysp= icm_set_data->icm_ysp; 
	
	d_vip_setIcm((D_U8*)&icm_set_data->param);
	return D_OK;
}

static D_S16
set_icm_set_hr_value(D_S16 value, D_Bool flag)
{
	
	if(flag)
	{
		if(value == 7)
			value = 0;
		else 
			value ++;
	}
	else
	{
		if(value == 0)
			value = 7;
		else 
			value --;
	}

	return value;
}

static D_S16
set_icm_set_hm_value(D_S16 value, D_Bool flag)
{
	
	if(flag)
	{
		if(value == 359)
			value = 0;
		else 
			value ++;
	}
	else
	{
		if(value == 0)
			value = 359;
		else 
			value --;
	}

	return value;
}

static D_S16
set_icm_set_hp_value(D_S16 value, D_Bool flag)
{
	
	if(flag)
	{
		if(value == 63)
			value = 0;
		else 
			value ++;
	}
	else
	{
		if(value == 0)
			value = 63;
		else 
			value --;
	}

	return value;
}

static D_S16
set_icm_set_sp_value(D_S16 value, D_Bool flag)
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
set_icm_set_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
	D_Frame *frm = &icm_set_window;
    D_Visual *vis;
	
	switch(id)
	{
		case ID_ICM_BUTTON_1:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_1);
			if(first_flag)
			{
				if(icm_set_data->icm_on == 0)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
					icm_set_data->icm_on = 1;
				}
				else if(icm_set_data->icm_on == 1)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
					icm_set_data->icm_on = 0;
				}
			}
			else
			{
				icm_set_data->icm_csp = set_icm_set_sp_value(icm_set_data->icm_csp, flag);
				sprintf(icm_set_data->icm_csp_buf, "%d", icm_set_data->icm_csp);
				d_label_set_text(vis, icm_set_data->icm_csp_buf);
			}
			break;
		case ID_ICM_BUTTON_2:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_2);
			if(first_flag)
			{
				icm_set_data->icm_rhr = set_icm_set_hr_value(icm_set_data->icm_rhr, flag);
				sprintf(icm_set_data->icm_rhr_buf, "%d", icm_set_data->icm_rhr);
				d_label_set_text(vis, icm_set_data->icm_rhr_buf);
			}
			else
			{
				icm_set_data->icm_mhr = set_icm_set_hr_value(icm_set_data->icm_mhr, flag);
				sprintf(icm_set_data->icm_mhr_buf, "%d", icm_set_data->icm_mhr);
				d_label_set_text(vis, icm_set_data->icm_mhr_buf);
			}
			break;
		case ID_ICM_BUTTON_3:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_3);
			if(first_flag)
			{
				icm_set_data->icm_rhm = set_icm_set_hm_value(icm_set_data->icm_rhm, flag);
				sprintf(icm_set_data->icm_rhm_buf, "%d", icm_set_data->icm_rhm);
				d_label_set_text(vis, icm_set_data->icm_rhm_buf);
			}
			else
			{
				icm_set_data->icm_mhm = set_icm_set_hm_value(icm_set_data->icm_mhm, flag);
				sprintf(icm_set_data->icm_mhm_buf, "%d", icm_set_data->icm_mhm);
				d_label_set_text(vis, icm_set_data->icm_mhm_buf);
			}
			break;
		case ID_ICM_BUTTON_4:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_4);
			if(first_flag)
			{
				icm_set_data->icm_rhp = set_icm_set_hp_value(icm_set_data->icm_rhp, flag);
				sprintf(icm_set_data->icm_rhp_buf, "%d", icm_set_data->icm_rhp);
				d_label_set_text(vis, icm_set_data->icm_rhp_buf);
			}
			else
			{
				icm_set_data->icm_mhp = set_icm_set_hp_value(icm_set_data->icm_mhp, flag);
				sprintf(icm_set_data->icm_mhp_buf, "%d", icm_set_data->icm_mhp);
				d_label_set_text(vis, icm_set_data->icm_mhp_buf);
			}
			break;
		case ID_ICM_BUTTON_5:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_5);
			if(first_flag)
			{
				icm_set_data->icm_rsp = set_icm_set_sp_value(icm_set_data->icm_rsp, flag);
				sprintf(icm_set_data->icm_rsp_buf, "%d", icm_set_data->icm_rsp);
				d_label_set_text(vis, icm_set_data->icm_rsp_buf);
			}
			else
			{
				icm_set_data->icm_msp = set_icm_set_sp_value(icm_set_data->icm_msp, flag);
				sprintf(icm_set_data->icm_msp_buf, "%d", icm_set_data->icm_msp);
				d_label_set_text(vis, icm_set_data->icm_msp_buf);
			}
			break;
		case ID_ICM_BUTTON_6:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_6);
			if(first_flag)
			{
				icm_set_data->icm_ghr = set_icm_set_hr_value(icm_set_data->icm_ghr, flag);
				sprintf(icm_set_data->icm_ghr_buf, "%d", icm_set_data->icm_ghr);
				d_label_set_text(vis, icm_set_data->icm_ghr_buf);
			}
			else
			{
				icm_set_data->icm_yhr = set_icm_set_hr_value(icm_set_data->icm_yhr, flag);
				sprintf(icm_set_data->icm_yhr_buf, "%d", icm_set_data->icm_yhr);
				d_label_set_text(vis, icm_set_data->icm_yhr_buf);
			}
			break;
		case ID_ICM_BUTTON_7:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_7);
			if(first_flag)
			{
				icm_set_data->icm_ghm = set_icm_set_hm_value(icm_set_data->icm_ghm, flag);
				sprintf(icm_set_data->icm_ghm_buf, "%d", icm_set_data->icm_ghm);
				d_label_set_text(vis, icm_set_data->icm_ghm_buf);
			}
			else
			{
				icm_set_data->icm_yhm = set_icm_set_hm_value(icm_set_data->icm_yhm, flag);
				sprintf(icm_set_data->icm_yhm_buf, "%d", icm_set_data->icm_yhm);
				d_label_set_text(vis, icm_set_data->icm_yhm_buf);
			}
			break;
		case ID_ICM_BUTTON_8:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_8);
			if(first_flag)
			{
				icm_set_data->icm_ghp = set_icm_set_hp_value(icm_set_data->icm_ghp, flag);
				sprintf(icm_set_data->icm_ghp_buf, "%d", icm_set_data->icm_ghp);
				d_label_set_text(vis, icm_set_data->icm_ghp_buf);
			}
			else
			{
				icm_set_data->icm_yhp = set_icm_set_hp_value(icm_set_data->icm_yhp, flag);
				sprintf(icm_set_data->icm_yhp_buf, "%d", icm_set_data->icm_yhp);
				d_label_set_text(vis, icm_set_data->icm_yhp_buf);
			}
			break;
		case ID_ICM_BUTTON_9:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_9);
			if(first_flag)
			{
				icm_set_data->icm_gsp = set_icm_set_sp_value(icm_set_data->icm_gsp, flag);
				sprintf(icm_set_data->icm_gsp_buf, "%d", icm_set_data->icm_gsp);
				d_label_set_text(vis, icm_set_data->icm_gsp_buf);
			}
			else
			{
				icm_set_data->icm_ysp = set_icm_set_sp_value(icm_set_data->icm_ysp, flag);
				sprintf(icm_set_data->icm_ysp_buf, "%d", icm_set_data->icm_ysp);
				d_label_set_text(vis, icm_set_data->icm_ysp_buf);
			}
			break;
		case ID_ICM_BUTTON_10:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_10);
			if(first_flag)
			{
				icm_set_data->icm_bhr = set_icm_set_hr_value(icm_set_data->icm_bhr, flag);
				sprintf(icm_set_data->icm_bhr_buf, "%d", icm_set_data->icm_bhr);
				d_label_set_text(vis, icm_set_data->icm_bhr_buf);
			}
			else
			{
				icm_set_data->icm_xhr = set_icm_set_hr_value(icm_set_data->icm_xhr, flag);
				sprintf(icm_set_data->icm_xhr_buf, "%d", icm_set_data->icm_xhr);
				d_label_set_text(vis, icm_set_data->icm_xhr_buf);
			}
			break;
		case ID_ICM_BUTTON_11:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_11);
			if(first_flag)
			{
				icm_set_data->icm_bhm = set_icm_set_hm_value(icm_set_data->icm_bhm, flag);
				sprintf(icm_set_data->icm_bhm_buf, "%d", icm_set_data->icm_bhm);
				d_label_set_text(vis, icm_set_data->icm_bhm_buf);
			}
			else
			{
				icm_set_data->icm_xhm = set_icm_set_hm_value(icm_set_data->icm_xhm, flag);
				sprintf(icm_set_data->icm_xhm_buf, "%d", icm_set_data->icm_xhm);
				d_label_set_text(vis, icm_set_data->icm_xhm_buf);
			}
			break;
			break;
		case ID_ICM_BUTTON_12:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_12);
			if(first_flag)
			{
				icm_set_data->icm_bhp = set_icm_set_hp_value(icm_set_data->icm_bhp, flag);
				sprintf(icm_set_data->icm_bhp_buf, "%d", icm_set_data->icm_bhp);
				d_label_set_text(vis, icm_set_data->icm_bhp_buf);
			}
			else
			{
				icm_set_data->icm_xhp = set_icm_set_hp_value(icm_set_data->icm_xhp, flag);
				sprintf(icm_set_data->icm_xhp_buf, "%d", icm_set_data->icm_xhp);
				d_label_set_text(vis, icm_set_data->icm_xhp_buf);
			}
			break;
		case ID_ICM_BUTTON_13:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_13);
			if(first_flag)
			{
				icm_set_data->icm_bsp = set_icm_set_sp_value(icm_set_data->icm_bsp, flag);
				sprintf(icm_set_data->icm_bsp_buf, "%d", icm_set_data->icm_bsp);
				d_label_set_text(vis, icm_set_data->icm_bsp_buf);
			}
			else
			{
				icm_set_data->icm_xsp = set_icm_set_sp_value(icm_set_data->icm_xsp, flag);
				sprintf(icm_set_data->icm_xsp_buf, "%d", icm_set_data->icm_xsp);
				d_label_set_text(vis, icm_set_data->icm_xsp_buf);
			}
			break;
		case ID_ICM_BUTTON_14:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_14);
			if(first_flag)
			{
				icm_set_data->icm_chr = set_icm_set_hr_value(icm_set_data->icm_chr, flag);
				sprintf(icm_set_data->icm_chr_buf, "%d", icm_set_data->icm_chr);
				d_label_set_text(vis, icm_set_data->icm_chr_buf);
			}
			break;
		case ID_ICM_BUTTON_15:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_15);
			if(first_flag)
			{
				icm_set_data->icm_chm = set_icm_set_hm_value(icm_set_data->icm_chm, flag);
				sprintf(icm_set_data->icm_chm_buf, "%d", icm_set_data->icm_chm);
				d_label_set_text(vis, icm_set_data->icm_chm_buf);
			}
			break;
		case ID_ICM_BUTTON_16:
			vis = d_frame_get_control(frm, ID_ICM_LABEL_16);
			if(first_flag)
			{
				icm_set_data->icm_chp = set_icm_set_hp_value(icm_set_data->icm_chp, flag);
				sprintf(icm_set_data->icm_chp_buf, "%d", icm_set_data->icm_chp);
				d_label_set_text(vis, icm_set_data->icm_chp_buf);
			}
			break;
		default:
			break;
	}
	set_param_of_icm();
	return D_OK;
}

static D_Result
button_1_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_1);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_2);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_3);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_4);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_5);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_6);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_7);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_8);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_9);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_10);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_11);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_12);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_13);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_14);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_15);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
	D_Frame *frm = &icm_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_ICM_LABEL_16);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_icm_set_data(id, D_TRUE);
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
get_set_of_icm_set(void) D_FUNCPOSTFIT
{
	if(icm_set_data->hdflag)
    {
        p_tvconf_get_hdicm_set_param(&icm_set_data->param, p_vip_get_dbinput(icm_set_data->input));
    }
    else
    {
        p_tvconf_get_icm_set_param(&icm_set_data->param, p_vip_get_dbinput(icm_set_data->input));
    }
	icm_set_data->icm_on= icm_set_data->param.icm_on;
	icm_set_data->icm_rhr= icm_set_data->param.icm_rhr;
	icm_set_data->icm_ghr= icm_set_data->param.icm_ghr;
	icm_set_data->icm_bhr= icm_set_data->param.icm_bhr;
	icm_set_data->icm_chr= icm_set_data->param.icm_chr;
	icm_set_data->icm_xhr= icm_set_data->param.icm_xhr;
	icm_set_data->icm_mhr= icm_set_data->param.icm_mhr;
	icm_set_data->icm_yhr= icm_set_data->param.icm_yhr;
	icm_set_data->icm_rhm= icm_set_data->param.icm_rhm;
	icm_set_data->icm_ghm= icm_set_data->param.icm_ghm;
	icm_set_data->icm_bhm= icm_set_data->param.icm_bhm;
	icm_set_data->icm_chm= icm_set_data->param.icm_chm;
	icm_set_data->icm_xhm= icm_set_data->param.icm_xhm;
	icm_set_data->icm_mhm= icm_set_data->param.icm_mhm;
	icm_set_data->icm_yhm= icm_set_data->param.icm_yhm;
	icm_set_data->icm_rhp= icm_set_data->param.icm_rhp;
	icm_set_data->icm_ghp= icm_set_data->param.icm_ghp;
	icm_set_data->icm_bhp= icm_set_data->param.icm_bhp;
	icm_set_data->icm_chp= icm_set_data->param.icm_chp;
	icm_set_data->icm_xhp= icm_set_data->param.icm_xhp;
	icm_set_data->icm_mhp= icm_set_data->param.icm_mhp;
	icm_set_data->icm_yhp= icm_set_data->param.icm_yhp;
	icm_set_data->icm_rsp= icm_set_data->param.icm_rsp;
	icm_set_data->icm_gsp= icm_set_data->param.icm_gsp;
	icm_set_data->icm_bsp= icm_set_data->param.icm_bsp;
	icm_set_data->icm_csp= icm_set_data->param.icm_csp;
	icm_set_data->icm_xsp= icm_set_data->param.icm_xsp;
	icm_set_data->icm_msp= icm_set_data->param.icm_msp;
	icm_set_data->icm_ysp= icm_set_data->param.icm_ysp;
		
	sprintf(icm_set_data->icm_rhr_buf, "%d", icm_set_data->icm_rhr);
	sprintf(icm_set_data->icm_ghr_buf, "%d", icm_set_data->icm_ghr);
	sprintf(icm_set_data->icm_bhr_buf, "%d", icm_set_data->icm_bhr);
	sprintf(icm_set_data->icm_chr_buf, "%d", icm_set_data->icm_chr);
	sprintf(icm_set_data->icm_mhr_buf, "%d", icm_set_data->icm_mhr);
	sprintf(icm_set_data->icm_yhr_buf, "%d", icm_set_data->icm_yhr);
	sprintf(icm_set_data->icm_xhr_buf, "%d", icm_set_data->icm_xhr);
	
	sprintf(icm_set_data->icm_rhm_buf, "%d", icm_set_data->icm_rhm);
	sprintf(icm_set_data->icm_ghm_buf, "%d", icm_set_data->icm_ghm);
	sprintf(icm_set_data->icm_bhm_buf, "%d", icm_set_data->icm_bhm);
	sprintf(icm_set_data->icm_chm_buf, "%d", icm_set_data->icm_chm);
	sprintf(icm_set_data->icm_xhm_buf, "%d", icm_set_data->icm_xhm);
	sprintf(icm_set_data->icm_mhm_buf, "%d", icm_set_data->icm_mhm);
	sprintf(icm_set_data->icm_yhm_buf, "%d", icm_set_data->icm_yhm);

	sprintf(icm_set_data->icm_rhp_buf, "%d", icm_set_data->icm_rhp);
	sprintf(icm_set_data->icm_ghp_buf, "%d", icm_set_data->icm_ghp);
	sprintf(icm_set_data->icm_bhp_buf, "%d", icm_set_data->icm_bhp);
	sprintf(icm_set_data->icm_chp_buf, "%d", icm_set_data->icm_chp);
	sprintf(icm_set_data->icm_xhp_buf, "%d", icm_set_data->icm_xhp);
	sprintf(icm_set_data->icm_mhp_buf, "%d", icm_set_data->icm_mhp);
	sprintf(icm_set_data->icm_yhp_buf, "%d", icm_set_data->icm_yhp);

	sprintf(icm_set_data->icm_rsp_buf, "%d", icm_set_data->icm_rsp);
	sprintf(icm_set_data->icm_gsp_buf, "%d", icm_set_data->icm_gsp);
	sprintf(icm_set_data->icm_bsp_buf, "%d", icm_set_data->icm_bsp);
	sprintf(icm_set_data->icm_csp_buf, "%d", icm_set_data->icm_csp);
	sprintf(icm_set_data->icm_xsp_buf, "%d", icm_set_data->icm_xsp);
	sprintf(icm_set_data->icm_msp_buf, "%d", icm_set_data->icm_msp);
	sprintf(icm_set_data->icm_ysp_buf, "%d", icm_set_data->icm_ysp);
	
	return D_OK;
}

static D_Result
set_first_page_show(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &icm_set_window;
    D_Visual *vis;

	first_flag = D_TRUE;
	second_flag = D_FALSE;

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_1);
	d_label_set_text(vis, "Icm On");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_2);
	d_label_set_text(vis, "Icm Rhr");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_3);
	d_label_set_text(vis, "Icm Rhm");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_4);
	d_label_set_text(vis, "Icm Rhp");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_5);
	d_label_set_text(vis, "Icm Rsp");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_6);
	d_label_set_text(vis, "Icm Ghr");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_7);
	d_label_set_text(vis, "Icm Ghm");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_8);
	d_label_set_text(vis, "Icm Ghp");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_9);
	d_label_set_text(vis, "Icm Gsp");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_10);
	d_label_set_text(vis, "Icm Bhr");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_11);
	d_label_set_text(vis, "Icm Bhm");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_12);
	d_label_set_text(vis, "Icm Bhp");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_13);
	d_label_set_text(vis, "Icm Bsp");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_14);
	d_label_set_text(vis, "Icm Chr");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_15);
	d_label_set_text(vis, "Icm Chm");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_16);
	d_label_set_text(vis, "Icm Chp");

	vis = d_frame_get_control(frm, ID_ICM_LABEL_1);
	if(icm_set_data->icm_on == 0)
		d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
	else if(icm_set_data->icm_on == 1)
		d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
		
	vis = d_frame_get_control(frm, ID_ICM_LABEL_2);
	d_label_set_text(vis, icm_set_data->icm_rhr_buf);
	
	vis = d_frame_get_control(frm, ID_ICM_LABEL_3);
	d_label_set_text(vis, icm_set_data->icm_rhm_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_4);
	d_label_set_text(vis, icm_set_data->icm_rhp_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_5);
	d_label_set_text(vis, icm_set_data->icm_rsp_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_6);
	d_label_set_text(vis, icm_set_data->icm_ghr_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_7);
	d_label_set_text(vis, icm_set_data->icm_ghm_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_8);
	d_label_set_text(vis, icm_set_data->icm_ghp_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_9);
	d_label_set_text(vis, icm_set_data->icm_gsp_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_10);
	d_label_set_text(vis, icm_set_data->icm_bhr_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_11);
	d_label_set_text(vis, icm_set_data->icm_bhm_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_12);
	d_label_set_text(vis, icm_set_data->icm_bhp_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_13);
	d_label_set_text(vis, icm_set_data->icm_bsp_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_14);
	d_label_set_text(vis, icm_set_data->icm_chr_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_15);
	d_label_set_text(vis, icm_set_data->icm_chm_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_16);
	d_label_set_text(vis, icm_set_data->icm_chp_buf);

	vis = d_frame_get_control(frm, ID_ICM_GROUP_14);
	d_vis_enable(vis, D_TRUE);

	vis = d_frame_get_control(frm, ID_ICM_GROUP_15);
	d_vis_enable(vis, D_TRUE);

	vis = d_frame_get_control(frm, ID_ICM_GROUP_16);
	d_vis_enable(vis, D_TRUE);

	
	vis = d_frame_get_control(frm, ID_ICM_BUTTON_14);
	d_vis_set_focusable(vis, D_TRUE);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_15);
	d_vis_set_focusable(vis, D_TRUE);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_16);
	d_vis_set_focusable(vis, D_TRUE);
	
	return D_OK;
}

static D_Result
set_second_page_show(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &icm_set_window;
    D_Visual *vis;

	second_flag = D_TRUE;
	first_flag = D_FALSE;

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_1);
	d_label_set_text(vis, "Icm Csp");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_2);
	d_label_set_text(vis, "Icm Mhr");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_3);
	d_label_set_text(vis, "Icm Mhm");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_4);
	d_label_set_text(vis, "Icm Mhp");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_5);
	d_label_set_text(vis, "Icm Msp");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_6);
	d_label_set_text(vis, "Icm Yhr");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_7);
	d_label_set_text(vis, "Icm Yhm");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_8);
	d_label_set_text(vis, "Icm Yhp");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_9);
	d_label_set_text(vis, "Icm Ysp");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_10);
	d_label_set_text(vis, "Icm Xhr");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_11);
	d_label_set_text(vis, "Icm Xhm");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_12);
	d_label_set_text(vis, "Icm Xhp");

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_13);
	d_label_set_text(vis, "Icm Xsp");

	vis = d_frame_get_control(frm, ID_ICM_LABEL_1);
	d_label_set_text(vis, icm_set_data->icm_csp_buf);
	
	vis = d_frame_get_control(frm, ID_ICM_LABEL_2);
	d_label_set_text(vis, icm_set_data->icm_mhr_buf);
	
	vis = d_frame_get_control(frm, ID_ICM_LABEL_3);
	d_label_set_text(vis, icm_set_data->icm_mhm_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_4);
	d_label_set_text(vis, icm_set_data->icm_mhp_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_5);
	d_label_set_text(vis, icm_set_data->icm_msp_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_6);
	d_label_set_text(vis, icm_set_data->icm_yhr_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_7);
	d_label_set_text(vis, icm_set_data->icm_yhm_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_8);
	d_label_set_text(vis, icm_set_data->icm_yhp_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_9);
	d_label_set_text(vis, icm_set_data->icm_ysp_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_10);
	d_label_set_text(vis, icm_set_data->icm_xhr_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_11);
	d_label_set_text(vis, icm_set_data->icm_xhm_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_12);
	d_label_set_text(vis, icm_set_data->icm_xhp_buf);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_13);
	d_label_set_text(vis, icm_set_data->icm_xsp_buf);
	
	vis = d_frame_get_control(frm, ID_ICM_GROUP_14);
	d_vis_enable(vis, D_FALSE);

	vis = d_frame_get_control(frm, ID_ICM_GROUP_15);
	d_vis_enable(vis, D_FALSE);

	vis = d_frame_get_control(frm, ID_ICM_GROUP_16);
	d_vis_enable(vis, D_FALSE);

	
	vis = d_frame_get_control(frm, ID_ICM_BUTTON_14);
	d_vis_set_focusable(vis, D_FALSE);
	d_label_set_text(vis, NULL);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_15);
	d_vis_set_focusable(vis, D_FALSE);
	d_label_set_text(vis, NULL);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_16);
	d_vis_set_focusable(vis, D_FALSE);
	d_label_set_text(vis, NULL);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_14);
	d_label_set_text(vis, NULL);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_15);
	d_label_set_text(vis, NULL);

	vis = d_frame_get_control(frm, ID_ICM_LABEL_16);
	d_label_set_text(vis, NULL);
	
	return D_OK;
}

static D_Result
icm_set_vis_handler(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &icm_set_window;
    D_Visual *vis;

	vis = d_frame_get_control(frm, ID_ICM_LABEL_ICM);
	d_label_set_text(vis, "ICM");
	
	vis = d_frame_get_control(frm, ID_ICM_BUTTON_1);
	d_vis_set_handler(vis, button_1_set_handler);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_2);
	d_vis_set_handler(vis, button_2_set_handler);
	
	vis = d_frame_get_control(frm, ID_ICM_BUTTON_3);
	d_vis_set_handler(vis, button_3_set_handler);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_4);
	d_vis_set_handler(vis, button_4_set_handler);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_5);
	d_vis_set_handler(vis, button_5_set_handler);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_6);
	d_vis_set_handler(vis, button_6_set_handler);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_7);
	d_vis_set_handler(vis, button_7_set_handler);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_8);
	d_vis_set_handler(vis, button_8_set_handler);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_9);
	d_vis_set_handler(vis, button_9_set_handler);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_10);
	d_vis_set_handler(vis, button_10_set_handler);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_11);
	d_vis_set_handler(vis, button_11_set_handler);
	
	vis = d_frame_get_control(frm, ID_ICM_BUTTON_12);
	d_vis_set_handler(vis, button_12_set_handler);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_13);
	d_vis_set_handler(vis, button_13_set_handler);
	
	vis = d_frame_get_control(frm, ID_ICM_BUTTON_14);
	d_vis_set_handler(vis, button_14_set_handler);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_15);
	d_vis_set_handler(vis, button_15_set_handler);

	vis = d_frame_get_control(frm, ID_ICM_BUTTON_16);
	d_vis_set_handler(vis, button_16_set_handler);

	return D_OK;
}


static D_Result
icm_set_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{	
	D_Visual *fv;
	D_Frame *frm = &icm_set_window;
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
					if(icm_set_data->focus == ID_ICM_BUTTON_1 && first_flag)
					{
						set_second_page_show();
						icm_set_data->focus = ID_ICM_BUTTON_13;
					}
					else if(icm_set_data->focus == ID_ICM_BUTTON_1 && second_flag)
					{
						set_first_page_show();
						icm_set_data->focus = ID_ICM_BUTTON_16;
					}
					else
					{
						icm_set_data->focus--;	
					}
					d_vis_set_focus(d_frame_get_control(frm, icm_set_data->focus));
					break;
				case D_KEY_DOWN:
				case D_KEY_PNL_D:
					if(icm_set_data->focus == ID_ICM_BUTTON_13 && second_flag)
					{
						set_first_page_show();
						icm_set_data->focus = ID_ICM_BUTTON_1;
					}
					else if(icm_set_data->focus == ID_ICM_BUTTON_16 && first_flag)
					{
						icm_set_data->focus = ID_ICM_BUTTON_1;
						set_second_page_show();
					}
					else 
					{
						icm_set_data->focus++;
					}
					d_vis_set_focus(d_frame_get_control(frm, icm_set_data->focus));
					break;
				case D_KEY_RIGHT:
				case D_KEY_PNL_R:
					set_icm_set_data(id, D_TRUE);
					break;
				case D_KEY_LEFT:
				case D_KEY_PNL_L:
					set_icm_set_data(id, D_FALSE);
					break;
				case D_KEY_MENU:
					return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
			save_param_of_icm();
			 if(icm_set_data)
            {
                PROJECT_FREE(icm_set_data);
                icm_set_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
icm_set_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

	icm_set_data = (D_IcmSetDate*)PROJECT_ALLOC(sizeof(D_IcmSetDate));
    if(!icm_set_data)
    {
        return D_ERR;
    }
	memset(icm_set_data, 0, sizeof(D_IcmSetDate));
	icm_set_data->input = p_conf_get_vid_input();
	if(icm_set_data->input == D_VID_IUTPUT_AV1 || icm_set_data->input == D_VID_IUTPUT_AV2|| icm_set_data->input == D_VID_IUTPUT_TV)
	{
		icm_set_data->hdflag = p_vip_get_ntscflag();
	}
	else
	{
		icm_set_data->hdflag = p_vip_get_hdflag();
	}
	get_set_of_icm_set();
	icm_set_vis_handler();
	set_first_page_show();

	icm_set_data->focus = ID_ICM_BUTTON_1;

	vis = d_frame_get_control(frm, ID_ICM_GROUP);
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
		d_vis_set_handler(vis, icm_set_window_handler);
	}

    return D_OK;
}

/** @brief 	ICM菜单*/
D_Result
p_atv_icm_set_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&icm_set_window, D_TRUE);
}
