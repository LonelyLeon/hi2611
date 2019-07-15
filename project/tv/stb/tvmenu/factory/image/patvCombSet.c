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
#include "comb_set_window.c"

#define BUF_LINE 4

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus={{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal={{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
	D_S16 focus,comb_2d_on, 
		comb_3d_on, comb_thr_f_c, comb_td_org_thr, comb_coef_pb, comb_coef_nb, comb_y_level_msb, comb_u_gain_msb, 
		comb_thr_curr_y, comb_thr_ff_y, comb_td_mflt_thr, comb_coef_pl1, comb_coef_nl1, comb_y_level_lsb, comb_u_gain_lsb,
		comb_thr_curr_c, comb_thr_ff_c, comb_md_core, comb_coef_pl2, comb_coef_nl2, comb_y_gain_msb, comb_v_gain_msb,
		comb_thr_f_y, comb_td_flt_thr, comb_md_gain, comb_coef_pl3, comb_coef_nl3, comb_y_gain_lsb, comb_v_gain_lsb,
		wavePos_msb, wavePos_lsb, comb_agc_c0, comb_agc_c1, comb_agc_c2;
	D_VidInput input;
	D_U8 hdflag;
	D_COMB_SET param;
	
	D_Char wavePos_msb_buf[BUF_LINE];
	D_Char wavePos_lsb_buf[BUF_LINE];
	D_Char comb_thr_f_c_buf[BUF_LINE];
	D_Char comb_td_org_thr_buf[BUF_LINE];
	D_Char comb_coef_pb_buf[BUF_LINE];
	D_Char comb_coef_nb_buf[BUF_LINE];
	D_Char comb_y_level_msb_buf[BUF_LINE];
	D_Char comb_u_gain_msb_buf[BUF_LINE];

	D_Char comb_thr_curr_y_buf[BUF_LINE];
	D_Char comb_thr_ff_y_buf[BUF_LINE];
	D_Char comb_td_mflt_thr_buf[BUF_LINE];
	D_Char comb_coef_pl1_buf[BUF_LINE];
	D_Char comb_coef_nl1_buf[BUF_LINE];
	D_Char comb_y_level_lsb_buf[BUF_LINE];
	D_Char comb_u_gain_lsb_buf[BUF_LINE];

	D_Char comb_thr_curr_c_buf[BUF_LINE];
	D_Char comb_thr_ff_c_buf[BUF_LINE];
	D_Char comb_md_core_buf[BUF_LINE];
	D_Char comb_coef_pl2_buf[BUF_LINE];
	D_Char comb_coef_nl2_buf[BUF_LINE];
	D_Char comb_y_gain_msb_buf[BUF_LINE];
	D_Char comb_v_gain_msb_buf[BUF_LINE];

	D_Char comb_thr_f_y_buf[BUF_LINE];
	D_Char comb_td_flt_thr_buf[BUF_LINE];
	D_Char comb_md_gain_buf[BUF_LINE];
	D_Char comb_coef_pl3_buf[BUF_LINE];
	D_Char comb_coef_nl3_buf[BUF_LINE];
	D_Char comb_y_gain_lsb_buf[BUF_LINE];
	D_Char comb_v_gain_lsb_buf[BUF_LINE];

	D_Char comb_agc_c0_buf[BUF_LINE];
	D_Char comb_agc_c1_buf[BUF_LINE];
	D_Char comb_agc_c2_buf[BUF_LINE];
}D_CombSetDate;

static D_CombSetDate *comb_set_data;
static D_Bool first_flag = D_TRUE;
static D_Bool second_flag = D_FALSE;
static D_Bool third_flag = D_FALSE;
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
save_param_of_comb(void) D_FUNCPOSTFIT
{
	if(comb_set_data->hdflag)
    {
		p_tvconf_set_hdcomb_set_param(&comb_set_data->param, p_vip_get_dbinput(comb_set_data->input));
    }
    else
    {
		p_tvconf_set_comb_set_param(&comb_set_data->param, p_vip_get_dbinput(comb_set_data->input));
    }
	return D_OK;
}

static D_Result
set_param_of_comb(void) D_FUNCPOSTFIT
{
	comb_set_data->param.comb_2d_on= comb_set_data->comb_2d_on; 	
	comb_set_data->param.comb_3d_on = comb_set_data->comb_3d_on;
	comb_set_data->param.comb_thr_f_c = comb_set_data->comb_thr_f_c;
	comb_set_data->param.comb_td_org_thr = comb_set_data->comb_td_org_thr;
	comb_set_data->param.comb_coef_pb = comb_set_data->comb_coef_pb;
	comb_set_data->param.comb_u_gain_msb = comb_set_data->comb_u_gain_msb;
	comb_set_data->param.comb_coef_nb = comb_set_data->comb_coef_nb;
	comb_set_data->param.comb_y_level_msb = comb_set_data->comb_y_level_msb;
	
	comb_set_data->param.comb_thr_curr_y= comb_set_data->comb_thr_curr_y;
	comb_set_data->param.comb_thr_ff_y= comb_set_data->comb_thr_ff_y;
	comb_set_data->param.comb_td_mflt_thr= comb_set_data->comb_td_mflt_thr;
	comb_set_data->param.comb_coef_pl1= comb_set_data->comb_coef_pl1;
	comb_set_data->param.comb_u_gain_lsb= comb_set_data->comb_u_gain_lsb;
	comb_set_data->param.comb_coef_nl1= comb_set_data->comb_coef_nl1;
	comb_set_data->param.comb_y_level_lsb= comb_set_data->comb_y_level_lsb;
	
	comb_set_data->param.comb_thr_curr_c= comb_set_data->comb_thr_curr_c;
	comb_set_data->param.comb_thr_ff_c= comb_set_data->comb_thr_ff_c;
	comb_set_data->param.comb_md_core= comb_set_data->comb_md_core;
	comb_set_data->param.comb_coef_pl2= comb_set_data->comb_coef_pl2;
	comb_set_data->param.comb_v_gain_msb= comb_set_data->comb_v_gain_msb;
	comb_set_data->param.comb_coef_nl2= comb_set_data->comb_coef_nl2;
	comb_set_data->param.comb_y_gain_msb= comb_set_data->comb_y_gain_msb;
	
	comb_set_data->param.comb_thr_f_y= comb_set_data->comb_thr_f_y;
	comb_set_data->param.comb_td_flt_thr= comb_set_data->comb_td_flt_thr;
	comb_set_data->param.comb_md_gain= comb_set_data->comb_md_gain;
	comb_set_data->param.comb_coef_pl3= comb_set_data->comb_coef_pl3;
	comb_set_data->param.comb_v_gain_lsb= comb_set_data->comb_v_gain_lsb;
	comb_set_data->param.comb_coef_nl3= comb_set_data->comb_coef_nl3;
	comb_set_data->param.comb_y_gain_lsb= comb_set_data->comb_y_gain_lsb;
	comb_set_data->param.wavePos_lsb= comb_set_data->wavePos_lsb;
	comb_set_data->param.wavePos_msb= comb_set_data->wavePos_msb;
	comb_set_data->param.comb_agc_c0= comb_set_data->comb_agc_c0;
	comb_set_data->param.comb_agc_c1= comb_set_data->comb_agc_c1;
	comb_set_data->param.comb_agc_c2= comb_set_data->comb_agc_c2;
	d_vip_setComb((D_U8*)&comb_set_data->param);
	
	return D_OK;
}


static D_S16
set_comb_set_value1(D_S16 value, D_Bool flag)
{
	
	if(flag)
	{
		if(value == 3)
			value = 0;
		else 
			value ++;
	}
	else
	{
		if(value == 0)
			value = 3;
		else 
			value --;
	}

	return value;
}

static D_S16
set_comb_set_value2(D_S16 value, D_Bool flag)
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
set_comb_set_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
	D_Frame *frm = &comb_set_window;
    D_Visual *vis;
	
	switch(id)
	{
		case ID_COMB_BUTTON_1:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_1);
			if(first_flag)
			{
				if(comb_set_data->comb_2d_on == 0)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
					comb_set_data->comb_2d_on = 1;
				}
				else if(comb_set_data->comb_2d_on == 1)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
					comb_set_data->comb_2d_on = 0;
				}
			}
			else if(second_flag)
			{
				comb_set_data->comb_coef_pl3 = set_comb_set_value1(comb_set_data->comb_coef_pl3, flag);
				sprintf(comb_set_data->comb_coef_pl3_buf, "%d", comb_set_data->comb_coef_pl3);
				d_label_set_text(vis, comb_set_data->comb_coef_pl3_buf);
			}
			else 
			{	
				if(flag)
				{
					if(comb_set_data->comb_agc_c1 == 63)
						comb_set_data->comb_agc_c1 = 0;
					else 
						comb_set_data->comb_agc_c1 ++;
				}
				else
				{
					if(comb_set_data->comb_agc_c1 == 0)
						comb_set_data->comb_agc_c1 = 63;
					else 
						comb_set_data->comb_agc_c1 --;
				}
				sprintf(comb_set_data->comb_agc_c1_buf, "%d", comb_set_data->comb_agc_c1);
				d_label_set_text(vis, comb_set_data->comb_agc_c1_buf);
			}
			break;
		case ID_COMB_BUTTON_2:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_2);
			if(first_flag)
			{
				if(comb_set_data->comb_3d_on == 0)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
					comb_set_data->comb_3d_on = 1;
				}
				else if(comb_set_data->comb_3d_on == 1)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
					comb_set_data->comb_3d_on = 0;
				}
			}
			else if(second_flag)
			{
				comb_set_data->comb_coef_nb = set_comb_set_value1(comb_set_data->comb_coef_nb, flag);
				sprintf(comb_set_data->comb_coef_nb_buf, "%d", comb_set_data->comb_coef_nb);
				d_label_set_text(vis, comb_set_data->comb_coef_nb_buf);
			}
			else 
			{
				comb_set_data->comb_agc_c2= set_comb_set_value2(comb_set_data->comb_agc_c2, flag);
				sprintf(comb_set_data->comb_agc_c2_buf, "%d", comb_set_data->comb_agc_c2);
				d_label_set_text(vis, comb_set_data->comb_agc_c2_buf);
			}
			break;
		case ID_COMB_BUTTON_3:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_3);
			if(first_flag)
			{
				comb_set_data->comb_thr_curr_y = set_comb_set_value2(comb_set_data->comb_thr_curr_y, flag);
				sprintf(comb_set_data->comb_thr_curr_y_buf, "%d", comb_set_data->comb_thr_curr_y);
				d_label_set_text(vis, comb_set_data->comb_thr_curr_y_buf);
			}
			else if(second_flag)
			{
				comb_set_data->comb_coef_nl1 = set_comb_set_value1(comb_set_data->comb_coef_nl1, flag);
				sprintf(comb_set_data->comb_coef_nl1_buf, "%d", comb_set_data->comb_coef_nl1);
				d_label_set_text(vis, comb_set_data->comb_coef_nl1_buf);
			}
			
			break;
		case ID_COMB_BUTTON_4:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_4);
			if(first_flag)
			{
				comb_set_data->comb_thr_curr_c = set_comb_set_value2(comb_set_data->comb_thr_curr_c, flag);
				sprintf(comb_set_data->comb_thr_curr_c_buf, "%d", comb_set_data->comb_thr_curr_c);
				d_label_set_text(vis, comb_set_data->comb_thr_curr_c_buf);
			}
			else if(second_flag)
			{
				comb_set_data->comb_coef_nl2 = set_comb_set_value1(comb_set_data->comb_coef_nl2, flag);
				sprintf(comb_set_data->comb_coef_nl2_buf, "%d", comb_set_data->comb_coef_nl2);
				d_label_set_text(vis, comb_set_data->comb_coef_nl2_buf);
			}
			break;
		case ID_COMB_BUTTON_5:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_5);
			if(first_flag)
			{
				comb_set_data->comb_thr_f_y = set_comb_set_value2(comb_set_data->comb_thr_f_y, flag);
				sprintf(comb_set_data->comb_thr_f_y_buf, "%d", comb_set_data->comb_thr_f_y);
				d_label_set_text(vis, comb_set_data->comb_thr_f_y_buf);
			}
			else if(second_flag)
			{
				comb_set_data->comb_coef_nl3 = set_comb_set_value1(comb_set_data->comb_coef_nl3, flag);
				sprintf(comb_set_data->comb_coef_nl3_buf, "%d", comb_set_data->comb_coef_nl3);
				d_label_set_text(vis, comb_set_data->comb_coef_nl3_buf);
			}
			break;
		case ID_COMB_BUTTON_6:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_6);
			if(first_flag)
			{
				comb_set_data->comb_thr_f_c = set_comb_set_value2(comb_set_data->comb_thr_f_c, flag);
				sprintf(comb_set_data->comb_thr_f_c_buf, "%d", comb_set_data->comb_thr_f_c);
				d_label_set_text(vis, comb_set_data->comb_thr_f_c_buf);
			}
			else if(second_flag)
			{
				comb_set_data->comb_y_level_msb = set_comb_set_value2(comb_set_data->comb_y_level_msb, flag);
				sprintf(comb_set_data->comb_y_level_msb_buf, "%d", comb_set_data->comb_y_level_msb);
				d_label_set_text(vis, comb_set_data->comb_y_level_msb_buf);
			}
			break;
		case ID_COMB_BUTTON_7:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_7);
			if(first_flag)
			{
				comb_set_data->comb_thr_ff_y = set_comb_set_value2(comb_set_data->comb_thr_ff_y, flag);
				sprintf(comb_set_data->comb_thr_ff_y_buf, "%d", comb_set_data->comb_thr_ff_y);
				d_label_set_text(vis, comb_set_data->comb_thr_ff_y_buf);
			}
			else if(second_flag)
			{
				comb_set_data->comb_y_level_lsb = set_comb_set_value2(comb_set_data->comb_y_level_lsb, flag);
				sprintf(comb_set_data->comb_y_level_lsb_buf, "%d", comb_set_data->comb_y_level_lsb);
				d_label_set_text(vis, comb_set_data->comb_y_level_lsb_buf);
			}
			break;
		case ID_COMB_BUTTON_8:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_8);
			if(first_flag)
			{
				comb_set_data->comb_thr_ff_c = set_comb_set_value2(comb_set_data->comb_thr_ff_c, flag);
				sprintf(comb_set_data->comb_thr_ff_c_buf, "%d", comb_set_data->comb_thr_ff_c);
				d_label_set_text(vis, comb_set_data->comb_thr_ff_c_buf);
			}
			else if(second_flag)
			{
				comb_set_data->comb_y_gain_msb = set_comb_set_value2(comb_set_data->comb_y_gain_msb, flag);
				sprintf(comb_set_data->comb_y_gain_msb_buf, "%d", comb_set_data->comb_y_gain_msb);
				d_label_set_text(vis, comb_set_data->comb_y_gain_msb_buf);
			}
			break;
		case ID_COMB_BUTTON_9:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_9);
			if(first_flag)
			{
				comb_set_data->comb_td_flt_thr = set_comb_set_value2(comb_set_data->comb_td_flt_thr, flag);
				sprintf(comb_set_data->comb_td_flt_thr_buf, "%d", comb_set_data->comb_td_flt_thr);
				d_label_set_text(vis, comb_set_data->comb_td_flt_thr_buf);
			}
			else if(second_flag)
			{
				comb_set_data->comb_y_gain_lsb = set_comb_set_value2(comb_set_data->comb_y_gain_lsb, flag);
				sprintf(comb_set_data->comb_y_gain_lsb_buf, "%d", comb_set_data->comb_y_gain_lsb);
				d_label_set_text(vis, comb_set_data->comb_y_gain_lsb_buf);
			}
			break;
		case ID_COMB_BUTTON_10:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_10);
			if(first_flag)
			{
				comb_set_data->comb_td_org_thr = set_comb_set_value2(comb_set_data->comb_td_org_thr, flag);
				sprintf(comb_set_data->comb_td_org_thr_buf, "%d", comb_set_data->comb_td_org_thr);
				d_label_set_text(vis, comb_set_data->comb_td_org_thr_buf);
			}
			else if(second_flag)
			{
				comb_set_data->comb_u_gain_msb = set_comb_set_value2(comb_set_data->comb_u_gain_msb, flag);
				sprintf(comb_set_data->comb_u_gain_msb_buf, "%d", comb_set_data->comb_u_gain_msb);
				d_label_set_text(vis, comb_set_data->comb_u_gain_msb_buf);
			}
			break;
		case ID_COMB_BUTTON_11:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_11);
			if(first_flag)
			{
				comb_set_data->comb_td_mflt_thr = set_comb_set_value2(comb_set_data->comb_td_mflt_thr, flag);
				sprintf(comb_set_data->comb_td_mflt_thr_buf, "%d", comb_set_data->comb_td_mflt_thr);
				d_label_set_text(vis, comb_set_data->comb_td_mflt_thr_buf);
			}
			else if(second_flag)
			{
				comb_set_data->comb_u_gain_lsb = set_comb_set_value2(comb_set_data->comb_u_gain_lsb, flag);
				sprintf(comb_set_data->comb_u_gain_lsb_buf, "%d", comb_set_data->comb_u_gain_lsb);
				d_label_set_text(vis, comb_set_data->comb_u_gain_lsb_buf);
			}
			break;
			break;
		case ID_COMB_BUTTON_12:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_12);
			if(first_flag)
			{
				comb_set_data->comb_md_core = set_comb_set_value2(comb_set_data->comb_md_core, flag);
				sprintf(comb_set_data->comb_md_core_buf, "%d", comb_set_data->comb_md_core);
				d_label_set_text(vis, comb_set_data->comb_md_core_buf);
			}
			else if(second_flag)
			{
				comb_set_data->comb_v_gain_msb = set_comb_set_value2(comb_set_data->comb_v_gain_msb, flag);
				sprintf(comb_set_data->comb_v_gain_msb_buf, "%d", comb_set_data->comb_v_gain_msb);
				d_label_set_text(vis, comb_set_data->comb_v_gain_msb_buf);
			}
			break;
		case ID_COMB_BUTTON_13:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_13);
			if(first_flag)
			{
				comb_set_data->comb_md_gain = set_comb_set_value2(comb_set_data->comb_md_gain, flag);
				sprintf(comb_set_data->comb_md_gain_buf, "%d", comb_set_data->comb_md_gain);
				d_label_set_text(vis, comb_set_data->comb_md_gain_buf);
			}
			else if(second_flag)
			{
				comb_set_data->comb_v_gain_lsb = set_comb_set_value2(comb_set_data->comb_v_gain_lsb, flag);
				sprintf(comb_set_data->comb_v_gain_lsb_buf, "%d", comb_set_data->comb_v_gain_lsb);
				d_label_set_text(vis, comb_set_data->comb_v_gain_lsb_buf);
			}
			break;
		case ID_COMB_BUTTON_14:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_14);
			if(first_flag)
			{
				comb_set_data->comb_coef_pb = set_comb_set_value1(comb_set_data->comb_coef_pb, flag);
				sprintf(comb_set_data->comb_coef_pb_buf, "%d", comb_set_data->comb_coef_pb);
				d_label_set_text(vis, comb_set_data->comb_coef_pb_buf);
			}
			else if(second_flag)
			{
				comb_set_data->wavePos_msb= set_comb_set_value2(comb_set_data->wavePos_msb, flag);
				sprintf(comb_set_data->wavePos_msb_buf, "%d", comb_set_data->wavePos_msb);
				d_label_set_text(vis, comb_set_data->wavePos_msb_buf);
			}
			break;
		case ID_COMB_BUTTON_15:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_15);
			if(first_flag)
			{
				comb_set_data->comb_coef_pl1 = set_comb_set_value1(comb_set_data->comb_coef_pl1, flag);
				sprintf(comb_set_data->comb_coef_pl1_buf, "%d", comb_set_data->comb_coef_pl1);
				d_label_set_text(vis, comb_set_data->comb_coef_pl1_buf);
			}
			else if(second_flag)
			{
				comb_set_data->wavePos_lsb= set_comb_set_value2(comb_set_data->wavePos_lsb, flag);
				sprintf(comb_set_data->wavePos_lsb_buf, "%d", comb_set_data->wavePos_lsb);
				d_label_set_text(vis, comb_set_data->wavePos_lsb_buf);
			}
			break;
		case ID_COMB_BUTTON_16:
			vis = d_frame_get_control(frm, ID_COMB_LABEL_16);
			if(first_flag)
			{
				comb_set_data->comb_coef_pl2 = set_comb_set_value1(comb_set_data->comb_coef_pl2, flag);
				sprintf(comb_set_data->comb_coef_pl2_buf, "%d", comb_set_data->comb_coef_pl2);
				d_label_set_text(vis, comb_set_data->comb_coef_pl2_buf);
			}
			else if(second_flag)
			{
				comb_set_data->comb_agc_c0= set_comb_set_value2(comb_set_data->comb_agc_c0, flag);
				sprintf(comb_set_data->comb_agc_c0_buf, "%d", comb_set_data->comb_agc_c0);
				d_label_set_text(vis, comb_set_data->comb_agc_c0_buf);
			}
			break;
		default:
			break;
	}
	set_param_of_comb();
	return D_OK;
}

static D_Result
button_1_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_1);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_2);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_3);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_4);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_5);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_6);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_7);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_8);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_9);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_10);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_11);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_12);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_13);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_14);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_15);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
	D_Frame *frm = &comb_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMB_LABEL_16);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comb_set_data(id, D_TRUE);
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
get_set_of_comb_set(void) D_FUNCPOSTFIT
{
	if(comb_set_data->hdflag)
    {
        p_tvconf_get_hdcomb_set_param(&comb_set_data->param, p_vip_get_dbinput(comb_set_data->input));
    }
    else
    {
        p_tvconf_get_comb_set_param(&comb_set_data->param, p_vip_get_dbinput(comb_set_data->input));
    }
	comb_set_data->comb_2d_on= comb_set_data->param.comb_2d_on;		
	comb_set_data->comb_3d_on = comb_set_data->param.comb_3d_on;
	comb_set_data->comb_thr_f_c = comb_set_data->param.comb_thr_f_c;
	comb_set_data->comb_td_org_thr = comb_set_data->param.comb_td_org_thr;
	comb_set_data->comb_coef_pb = comb_set_data->param.comb_coef_pb;
	comb_set_data->comb_u_gain_msb = comb_set_data->param.comb_u_gain_msb;
	comb_set_data->comb_coef_nb = comb_set_data->param.comb_coef_nb;
	comb_set_data->comb_y_level_msb = comb_set_data->param.comb_y_level_msb;
	
	comb_set_data->comb_thr_curr_y= comb_set_data->param.comb_thr_curr_y;
	comb_set_data->comb_thr_ff_y= comb_set_data->param.comb_thr_ff_y;
	comb_set_data->comb_td_mflt_thr= comb_set_data->param.comb_td_mflt_thr;
	comb_set_data->comb_coef_pl1= comb_set_data->param.comb_coef_pl1;
	comb_set_data->comb_u_gain_lsb= comb_set_data->param.comb_u_gain_lsb;
	comb_set_data->comb_coef_nl1= comb_set_data->param.comb_coef_nl1;
	comb_set_data->comb_y_level_lsb= comb_set_data->param.comb_y_level_lsb;
	
	comb_set_data->comb_thr_curr_c= comb_set_data->param.comb_thr_curr_c;
	comb_set_data->comb_thr_ff_c= comb_set_data->param.comb_thr_ff_c;
	comb_set_data->comb_md_core= comb_set_data->param.comb_md_core;
	comb_set_data->comb_coef_pl2= comb_set_data->param.comb_coef_pl2;
	comb_set_data->comb_v_gain_msb= comb_set_data->param.comb_v_gain_msb;
	comb_set_data->comb_coef_nl2= comb_set_data->param.comb_coef_nl2;
	comb_set_data->comb_y_gain_msb= comb_set_data->param.comb_y_gain_msb;
	
	comb_set_data->comb_thr_f_y= comb_set_data->param.comb_thr_f_y;
	comb_set_data->comb_td_flt_thr= comb_set_data->param.comb_td_flt_thr;
	comb_set_data->comb_md_gain= comb_set_data->param.comb_md_gain;
	comb_set_data->comb_coef_pl3= comb_set_data->param.comb_coef_pl3;
	comb_set_data->comb_v_gain_lsb= comb_set_data->param.comb_v_gain_lsb;
	comb_set_data->comb_coef_nl3= comb_set_data->param.comb_coef_nl3;
	comb_set_data->comb_y_gain_lsb= comb_set_data->param.comb_y_gain_lsb;
	comb_set_data->wavePos_lsb= comb_set_data->param.wavePos_lsb;
	comb_set_data->wavePos_msb= comb_set_data->param.wavePos_msb;
	comb_set_data->comb_agc_c0= comb_set_data->param.comb_agc_c0;
	comb_set_data->comb_agc_c1= comb_set_data->param.comb_agc_c1;
	comb_set_data->comb_agc_c2= comb_set_data->param.comb_agc_c2;
	
	sprintf(comb_set_data->wavePos_lsb_buf, "%d", comb_set_data->wavePos_lsb);
	sprintf(comb_set_data->wavePos_msb_buf, "%d", comb_set_data->wavePos_msb);

	sprintf(comb_set_data->comb_thr_f_c_buf, "%d", comb_set_data->comb_thr_f_c);
	sprintf(comb_set_data->comb_td_org_thr_buf, "%d", comb_set_data->comb_td_org_thr);
	sprintf(comb_set_data->comb_coef_pb_buf, "%d", comb_set_data->comb_coef_pb);
	sprintf(comb_set_data->comb_coef_nb_buf, "%d", comb_set_data->comb_coef_nb);
	sprintf(comb_set_data->comb_y_level_msb_buf, "%d", comb_set_data->comb_y_level_msb);
	sprintf(comb_set_data->comb_u_gain_msb_buf, "%d", comb_set_data->comb_u_gain_msb);
	
	sprintf(comb_set_data->comb_thr_curr_y_buf, "%d", comb_set_data->comb_thr_curr_y);
	sprintf(comb_set_data->comb_thr_ff_y_buf, "%d", comb_set_data->comb_thr_ff_y);
	sprintf(comb_set_data->comb_td_mflt_thr_buf, "%d", comb_set_data->comb_td_mflt_thr);
	sprintf(comb_set_data->comb_coef_pl1_buf, "%d", comb_set_data->comb_coef_pl1);
	sprintf(comb_set_data->comb_u_gain_lsb_buf, "%d", comb_set_data->comb_u_gain_lsb);
	sprintf(comb_set_data->comb_coef_nl1_buf, "%d", comb_set_data->comb_coef_nl1);
	sprintf(comb_set_data->comb_y_level_lsb_buf, "%d", comb_set_data->comb_y_level_lsb);

	sprintf(comb_set_data->comb_thr_curr_c_buf, "%d", comb_set_data->comb_thr_curr_c);
	sprintf(comb_set_data->comb_thr_ff_c_buf, "%d", comb_set_data->comb_thr_ff_c);
	sprintf(comb_set_data->comb_md_core_buf, "%d", comb_set_data->comb_md_core);
	sprintf(comb_set_data->comb_coef_pl2_buf, "%d", comb_set_data->comb_coef_pl2);
	sprintf(comb_set_data->comb_v_gain_msb_buf, "%d", comb_set_data->comb_v_gain_msb);
	sprintf(comb_set_data->comb_coef_nl2_buf, "%d", comb_set_data->comb_coef_nl2);
	sprintf(comb_set_data->comb_y_gain_msb_buf, "%d", comb_set_data->comb_y_gain_msb);

	sprintf(comb_set_data->comb_thr_f_y_buf, "%d", comb_set_data->comb_thr_f_y);
	sprintf(comb_set_data->comb_td_flt_thr_buf, "%d", comb_set_data->comb_td_flt_thr);
	sprintf(comb_set_data->comb_md_gain_buf, "%d", comb_set_data->comb_md_gain);
	sprintf(comb_set_data->comb_coef_pl3_buf, "%d", comb_set_data->comb_coef_pl3);
	sprintf(comb_set_data->comb_v_gain_lsb_buf, "%d", comb_set_data->comb_v_gain_lsb);
	sprintf(comb_set_data->comb_coef_nl3_buf, "%d", comb_set_data->comb_coef_nl3);
	sprintf(comb_set_data->comb_y_gain_lsb_buf, "%d", comb_set_data->comb_y_gain_lsb);
	sprintf(comb_set_data->comb_agc_c0_buf, "%d", comb_set_data->comb_agc_c0);
	sprintf(comb_set_data->comb_agc_c1_buf, "%d", comb_set_data->comb_agc_c1);
	sprintf(comb_set_data->comb_agc_c2_buf, "%d", comb_set_data->comb_agc_c2);
	
	return D_OK;
}

static D_Result
set_first_page_show(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &comb_set_window;
    D_Visual *vis;
	D_ID i;

	first_flag = D_TRUE;
	second_flag = D_FALSE;
	third_flag = D_FALSE;

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_1);
	d_label_set_text(vis, "Comb 2d On");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_2);
	d_label_set_text(vis, "Comb 3d On");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_3);
	d_label_set_text(vis, "Comb Thr Curr Y");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_4);
	d_label_set_text(vis, "Comb Thr Curr C");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_5);
	d_label_set_text(vis, "Comb Thr F Y");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_6);
	d_label_set_text(vis, "Comb Thr F C");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_7);
	d_label_set_text(vis, "Comb Thr Ff Y");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_8);
	d_label_set_text(vis, "Comb Thr Ff C");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_9);
	d_label_set_text(vis, "Comb Td Flt Thr");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_10);
	d_label_set_text(vis, "Comb Td Org Thr");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_11);
	d_label_set_text(vis, "Comb Td Mflt Thr");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_12);
	d_label_set_text(vis, "Comb Md Core");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_13);
	d_label_set_text(vis, "Comb Md Gain");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_14);
	d_label_set_text(vis, "Comb Coef Pb");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_15);
	d_label_set_text(vis, "Comb Coef Pl1");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_16);
	d_label_set_text(vis, "Comb Coef Pl2");

	vis = d_frame_get_control(frm, ID_COMB_LABEL_1);
	vis_switch_init(comb_set_data->comb_2d_on, vis);
	
	vis = d_frame_get_control(frm, ID_COMB_LABEL_2);
	vis_switch_init(comb_set_data->comb_3d_on, vis);
	 
	vis = d_frame_get_control(frm, ID_COMB_LABEL_3);
	d_label_set_text(vis, comb_set_data->comb_thr_curr_y_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_4);
	d_label_set_text(vis, comb_set_data->comb_thr_curr_c_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_5);
	d_label_set_text(vis, comb_set_data->comb_thr_f_y_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_6);
	d_label_set_text(vis, comb_set_data->comb_thr_f_c_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_7);
	d_label_set_text(vis, comb_set_data->comb_thr_ff_y_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_8);
	d_label_set_text(vis, comb_set_data->comb_thr_ff_c_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_9);
	d_label_set_text(vis, comb_set_data->comb_td_flt_thr_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_10);
	d_label_set_text(vis, comb_set_data->comb_td_org_thr_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_11);
	d_label_set_text(vis, comb_set_data->comb_td_mflt_thr_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_12);
	d_label_set_text(vis, comb_set_data->comb_md_core_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_13);
	d_label_set_text(vis, comb_set_data->comb_md_gain_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_14);
	d_label_set_text(vis, comb_set_data->comb_coef_pb_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_15);
	d_label_set_text(vis, comb_set_data->comb_coef_pl1_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_16);
	d_label_set_text(vis, comb_set_data->comb_coef_pl2_buf);

	vis = d_frame_get_control(frm, ID_COMB_GROUP_16);
	d_vis_enable(vis, D_TRUE);

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_16);
	d_vis_set_focusable(vis, D_TRUE);

	for(i = ID_COMB_GROUP_3; i <= ID_COMB_GROUP_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_vis_enable(vis, D_TRUE);
	}

	for(i = ID_COMB_BUTTON_3; i <= ID_COMB_BUTTON_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_vis_set_focusable(vis, D_TRUE);
	}
	
	return D_OK;
}

static D_Result
set_second_page_show(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &comb_set_window;
    D_Visual *vis;
	D_ID i;
	
	second_flag = D_TRUE;
	first_flag = D_FALSE;
	third_flag = D_FALSE;

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_1);
	d_label_set_text(vis, "Comb Coef Pl3");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_2);
	d_label_set_text(vis, "Comb Coef Nb");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_3);
	d_label_set_text(vis, "Comb Coef Nl1");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_4);
	d_label_set_text(vis, "Comb Coef Nl2");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_5);
	d_label_set_text(vis, "Comb Coef Nl3");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_6);
	d_label_set_text(vis, "Comb Y Level Msb");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_7);
	d_label_set_text(vis, "Comb Y Level Lsb");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_8);
	d_label_set_text(vis, "Comb Y Gain Msb");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_9);
	d_label_set_text(vis, "Comb Y Gain Lsb");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_10);
	d_label_set_text(vis, "Comb U Gain Msb");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_11);
	d_label_set_text(vis, "Comb U Gain Lsb");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_12);
	d_label_set_text(vis, "Comb V Gain Msb");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_13);
	d_label_set_text(vis, "Comb V Gain Lsb");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_14);
	d_label_set_text(vis, "WavePos Msb");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_15);
	d_label_set_text(vis, "WavePos Lsb");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_16);
	d_label_set_text(vis, "Comb Agc C0");

	vis = d_frame_get_control(frm, ID_COMB_LABEL_1);
	d_label_set_text(vis, comb_set_data->comb_coef_pl3_buf);
	
	vis = d_frame_get_control(frm, ID_COMB_LABEL_2);
	d_label_set_text(vis, comb_set_data->comb_coef_nb_buf);
	
	vis = d_frame_get_control(frm, ID_COMB_LABEL_3);
	d_label_set_text(vis, comb_set_data->comb_coef_nl1_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_4);
	d_label_set_text(vis, comb_set_data->comb_coef_nl2_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_5);
	d_label_set_text(vis, comb_set_data->comb_coef_nl3_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_6);
	d_label_set_text(vis, comb_set_data->comb_y_level_msb_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_7);
	d_label_set_text(vis, comb_set_data->comb_y_level_lsb_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_8);
	d_label_set_text(vis, comb_set_data->comb_y_gain_msb_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_9);
	d_label_set_text(vis, comb_set_data->comb_y_gain_lsb_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_10);
	d_label_set_text(vis, comb_set_data->comb_u_gain_msb_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_11);
	d_label_set_text(vis, comb_set_data->comb_u_gain_lsb_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_12);
	d_label_set_text(vis, comb_set_data->comb_v_gain_msb_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_13);
	d_label_set_text(vis, comb_set_data->comb_v_gain_lsb_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_14);
	d_label_set_text(vis, comb_set_data->wavePos_msb_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_15);
	d_label_set_text(vis, comb_set_data->wavePos_lsb_buf);

	vis = d_frame_get_control(frm, ID_COMB_LABEL_16);
	d_label_set_text(vis, comb_set_data->comb_agc_c0_buf);

	for(i = ID_COMB_GROUP_3; i <= ID_COMB_GROUP_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_vis_enable(vis, D_TRUE);
	}

	for(i = ID_COMB_BUTTON_3; i <= ID_COMB_BUTTON_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_vis_set_focusable(vis, D_TRUE);
	}
	
	return D_OK;
}

static D_Result
set_third_page_show(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &comb_set_window;
    D_Visual *vis;
	D_ID i;

	second_flag = D_FALSE;
	first_flag = D_FALSE;
	third_flag = D_TRUE;

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_1);
	d_label_set_text(vis, "Comb Agc C1");

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_2);
	d_label_set_text(vis, "Comb Agc C2");


	vis = d_frame_get_control(frm, ID_COMB_LABEL_1);
	d_label_set_text(vis, comb_set_data->comb_agc_c1_buf);
	
	vis = d_frame_get_control(frm, ID_COMB_LABEL_2);
	d_label_set_text(vis, comb_set_data->comb_agc_c2_buf);
	
	for(i = ID_COMB_GROUP_3; i <= ID_COMB_GROUP_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_vis_enable(vis, D_FALSE);
	}

	for(i = ID_COMB_BUTTON_3; i <= ID_COMB_BUTTON_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_label_set_text(vis, NULL);
		d_vis_set_focusable(vis, D_FALSE);
	}

	for(i = ID_COMB_LABEL_3; i <= ID_COMB_LABEL_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_label_set_text(vis, NULL);
	}
	
	return D_OK;
}


static D_Result
comb_set_vis_handler(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &comb_set_window;
    D_Visual *vis;

	vis = d_frame_get_control(frm, ID_COMB_LABEL_COMB);
	d_label_set_text(vis, "COMB");
	
	vis = d_frame_get_control(frm, ID_COMB_BUTTON_1);
	d_vis_set_handler(vis, button_1_set_handler);

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_2);
	d_vis_set_handler(vis, button_2_set_handler);
	
	vis = d_frame_get_control(frm, ID_COMB_BUTTON_3);
	d_vis_set_handler(vis, button_3_set_handler);

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_4);
	d_vis_set_handler(vis, button_4_set_handler);

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_5);
	d_vis_set_handler(vis, button_5_set_handler);

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_6);
	d_vis_set_handler(vis, button_6_set_handler);

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_7);
	d_vis_set_handler(vis, button_7_set_handler);

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_8);
	d_vis_set_handler(vis, button_8_set_handler);

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_9);
	d_vis_set_handler(vis, button_9_set_handler);

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_10);
	d_vis_set_handler(vis, button_10_set_handler);

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_11);
	d_vis_set_handler(vis, button_11_set_handler);
	
	vis = d_frame_get_control(frm, ID_COMB_BUTTON_12);
	d_vis_set_handler(vis, button_12_set_handler);

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_13);
	d_vis_set_handler(vis, button_13_set_handler);
	
	vis = d_frame_get_control(frm, ID_COMB_BUTTON_14);
	d_vis_set_handler(vis, button_14_set_handler);

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_15);
	d_vis_set_handler(vis, button_15_set_handler);

	vis = d_frame_get_control(frm, ID_COMB_BUTTON_16);
	d_vis_set_handler(vis, button_16_set_handler);

	return D_OK;
}


static D_Result
comb_set_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{	
	D_Visual *fv;
	D_Frame *frm = &comb_set_window;
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
					if(comb_set_data->focus == ID_COMB_BUTTON_1)
					{
						if(first_flag)
						{
							set_third_page_show();
							comb_set_data->focus = ID_COMB_BUTTON_2;
						}
						else if(second_flag)
						{
							set_first_page_show();
							comb_set_data->focus = ID_COMB_BUTTON_16;
						}
						else if(third_flag)
						{
							set_second_page_show();
							comb_set_data->focus = ID_COMB_BUTTON_16;
						}
					}
					else
					{
						comb_set_data->focus--;	
					}
					d_vis_set_focus(d_frame_get_control(frm, comb_set_data->focus));
					break;
				case D_KEY_DOWN:
				case D_KEY_PNL_D:
					if(comb_set_data->focus == ID_COMB_BUTTON_16)
					{
						if(first_flag)
						{
							comb_set_data->focus = ID_COMB_BUTTON_1;
							set_second_page_show();
						}
						else if(second_flag)
						{
							set_third_page_show();
							comb_set_data->focus = ID_COMB_BUTTON_1;
						}
					}
					else if(comb_set_data->focus == ID_COMB_BUTTON_2 && third_flag)
					{
						comb_set_data->focus = ID_COMB_BUTTON_1;
						set_first_page_show();
					}
					else 
					{
						comb_set_data->focus++;
					}
					d_vis_set_focus(d_frame_get_control(frm, comb_set_data->focus));
					break;
				case D_KEY_RIGHT:
				case D_KEY_PNL_R:
					set_comb_set_data(id, D_TRUE);
					break;
				case D_KEY_LEFT:
				case D_KEY_PNL_L:
					set_comb_set_data(id, D_FALSE);
					break;
				case D_KEY_MENU:
					return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
			save_param_of_comb();
			 if(comb_set_data)
            {
                PROJECT_FREE(comb_set_data);
                comb_set_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
comb_set_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

	comb_set_data = (D_CombSetDate*)PROJECT_ALLOC(sizeof(D_CombSetDate));
    if(!comb_set_data)
    {
        return D_ERR;
    }
	memset(comb_set_data, 0, sizeof(D_CombSetDate));
	comb_set_data->input = p_conf_get_vid_input();
	if(comb_set_data->input == D_VID_IUTPUT_AV1 || comb_set_data->input == D_VID_IUTPUT_AV2|| comb_set_data->input == D_VID_IUTPUT_TV)
	{
		comb_set_data->hdflag = p_vip_get_ntscflag();
	}
	else
	{
		comb_set_data->hdflag = p_vip_get_hdflag();
	}
	get_set_of_comb_set();
	comb_set_vis_handler();
	set_first_page_show();

	comb_set_data->focus = ID_COMB_BUTTON_1;
	
	vis = d_frame_get_control(frm, ID_COMB_GROUP);
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
		d_vis_set_handler(vis, comb_set_window_handler);
	}

    return D_OK;
}

/** @brief 	COMB菜单*/
D_Result
p_atv_comb_set_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&comb_set_window, D_TRUE);
}

