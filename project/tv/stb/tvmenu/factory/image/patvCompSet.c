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
#include "comp_set_window.c"

#define BUF_LINE 4

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus={{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal={{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
	D_S16 focus, comp_flip_clk, comp_i_adc, comp_gain_r,comp_gain_g,comp_gain_b,
		comp_offs_r, comp_offs_g, comp_offs_b, comp_iclamp_r, comp_iclamp_g, comp_iclamp_b, comp_imaxsel, comp_i_pga, comp_vclampimp, 
		comp_inbw_b, comp_inbw_g, comp_inbw_r, comp_pga_ref, comp_pwdb_lsb, comp_pwdb_msb, comp_test_adcref, comp_vclamplevel_b, comp_vclamplevel_g,
		comp_vclamplevel_r, comp_clampselect, comp_vcom1_sel;
	D_VidInput input;
	D_U8 hdflag;
	D_COMP_SET param;

	D_Char comp_gain_r_buf[BUF_LINE];
	D_Char comp_gain_g_buf[BUF_LINE];
	D_Char comp_gain_b_buf[BUF_LINE];
	
	D_Char comp_i_adc_buf[BUF_LINE];

	D_Char comp_offs_r_buf[BUF_LINE];
	D_Char comp_offs_g_buf[BUF_LINE];
	D_Char comp_offs_b_buf[BUF_LINE];
	D_Char comp_iclamp_r_buf[BUF_LINE];
	D_Char comp_iclamp_g_buf[BUF_LINE];
	D_Char comp_iclamp_b_buf[BUF_LINE];
	D_Char comp_imaxsel_buf[BUF_LINE];

	D_Char           comp_i_pga_buf[BUF_LINE];			
    D_Char           comp_vclampimp_buf[BUF_LINE];		
    D_Char           comp_inbw_b_buf[BUF_LINE];				
    D_Char           comp_inbw_g_buf[BUF_LINE];				
    D_Char           comp_inbw_r_buf[BUF_LINE];				
    D_Char           comp_pga_ref_buf[BUF_LINE];			
    D_Char           comp_pwdb_lsb_buf[BUF_LINE];			
    D_Char           comp_pwdb_msb_buf[BUF_LINE];			
    D_Char           comp_test_adcref_buf[BUF_LINE];	
    D_Char           comp_vclamplevel_b_buf[BUF_LINE];
    D_Char           comp_vclamplevel_g_buf[BUF_LINE];
    D_Char           comp_vclamplevel_r_buf[BUF_LINE];
    D_Char           comp_vcom1_sel_buf[BUF_LINE];		
}D_CompSetDate;

static D_CompSetDate *comp_set_data;
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
save_param_of_comp(id) D_FUNCPOSTFIT
{
	if(comp_set_data->hdflag)
    {
		p_tvconf_set_hdcomp_set_param(&comp_set_data->param, p_vip_get_dbinput(comp_set_data->input));
    }
    else
    {
		p_tvconf_set_comp_set_param(&comp_set_data->param, p_vip_get_dbinput(comp_set_data->input));
    }
	return D_OK;
}

static D_Result
set_param_of_comp(void) D_FUNCPOSTFIT
{
	comp_set_data->param.comp_flip_clk= comp_set_data->comp_flip_clk;
	comp_set_data->param.comp_i_adc = comp_set_data->comp_i_adc;
	
	comp_set_data->param.comp_gain_r = comp_set_data->comp_gain_r;
	comp_set_data->param.comp_gain_g = comp_set_data->comp_gain_g;
	comp_set_data->param.comp_gain_b = comp_set_data->comp_gain_b;
	
	comp_set_data->param.comp_offs_r = comp_set_data->comp_offs_r;
	comp_set_data->param.comp_offs_g = comp_set_data->comp_offs_g;
	comp_set_data->param.comp_offs_b = comp_set_data->comp_offs_b;
	comp_set_data->param.comp_iclamp_r = comp_set_data->comp_iclamp_r;
	comp_set_data->param.comp_iclamp_g = comp_set_data->comp_iclamp_g;
	comp_set_data->param.comp_iclamp_b = comp_set_data->comp_iclamp_b;
	comp_set_data->param.comp_imaxsel= comp_set_data->comp_imaxsel;

	comp_set_data->param.comp_i_pga= comp_set_data->comp_i_pga;
	comp_set_data->param.comp_vclampimp= comp_set_data->comp_vclampimp;
	comp_set_data->param.comp_inbw_b= comp_set_data->comp_inbw_b;
	comp_set_data->param.comp_inbw_g= comp_set_data->comp_inbw_g;
	comp_set_data->param.comp_inbw_r= comp_set_data->comp_inbw_r;
	
	comp_set_data->param.comp_pga_ref = comp_set_data->comp_pga_ref;
	comp_set_data->param.comp_pwdb_lsb = comp_set_data->comp_pwdb_lsb;
	comp_set_data->param.comp_pwdb_msb = comp_set_data->comp_pwdb_msb;
	comp_set_data->param.comp_test_adcref = comp_set_data->comp_test_adcref;
	comp_set_data->param.comp_vclamplevel_b = comp_set_data->comp_vclamplevel_b;
	comp_set_data->param.comp_vclamplevel_g = comp_set_data->comp_vclamplevel_g;
	comp_set_data->param.comp_vclamplevel_r= comp_set_data->comp_vclamplevel_r;
	
	comp_set_data->param.comp_clampselect = comp_set_data->comp_clampselect;
	comp_set_data->param.comp_vcom1_sel = comp_set_data->comp_vcom1_sel;
	d_vip_setComp((D_U8*)&comp_set_data->param);

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
set_comp_set_value1(D_S16 value, D_Bool flag)
{
	
	if(flag)
	{
		if(value == 511)
			value = 0;
		else 
			value ++;
	}
	else
	{
		if(value == 0)
			value = 511;
		else 
			value --;
	}

	return value;
}

static D_S16
set_comp_set_value2(D_S16 value, D_Bool flag)
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

static D_S16
set_comp_set_value3(D_S16 value, D_Bool flag)
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
set_comp_set_value4(D_S16 value, D_Bool flag)
{
	
	if(flag)
	{
		if(value == 15)
			value = 0;
		else 
			value ++;
	}
	else
	{
		if(value == 0)
			value = 15;
		else 
			value --;
	}

	return value;
}

static D_S16
set_comp_set_value5(D_S16 value, D_Bool flag)
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

static D_Result
set_comp_set_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
	D_Frame *frm = &comp_set_window;
    D_Visual *vis;
	
	switch(id)
	{
		case ID_COMP_BUTTON_1:
			vis = d_frame_get_control(frm, ID_COMP_LABEL_1);
			if(first_flag)
			{
				
				if(comp_set_data->comp_flip_clk == 0)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
					comp_set_data->comp_flip_clk = 1;
				}
				else if(comp_set_data->comp_flip_clk == 1)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
					comp_set_data->comp_flip_clk = 0;
				}
			}
			else if(second_flag)
			{
				comp_set_data->comp_iclamp_r = set_comp_set_value4(comp_set_data->comp_iclamp_r, flag);

				sprintf(comp_set_data->comp_iclamp_r_buf, "%d", comp_set_data->comp_iclamp_r);
				d_label_set_text(vis, comp_set_data->comp_iclamp_r_buf);
			}
			break;
		case ID_COMP_BUTTON_2:
			
			vis = d_frame_get_control(frm, ID_COMP_LABEL_2);
			if(first_flag)
			{
				comp_set_data->comp_gain_b= set_comp_set_value3(comp_set_data->comp_gain_b, flag);

				sprintf(comp_set_data->comp_gain_b_buf, "%d", comp_set_data->comp_gain_b);
				d_label_set_text(vis, comp_set_data->comp_gain_b_buf);

			}
			else if(second_flag)
			{
				comp_set_data->comp_imaxsel = set_comp_set_value4(comp_set_data->comp_imaxsel, flag);

				sprintf(comp_set_data->comp_imaxsel_buf, "%d", comp_set_data->comp_imaxsel);
				d_label_set_text(vis, comp_set_data->comp_imaxsel_buf);
			}
			break;
		case ID_COMP_BUTTON_3:
			
			vis = d_frame_get_control(frm, ID_COMP_LABEL_3);
			if(first_flag)
			{
				
				comp_set_data->comp_gain_g = set_comp_set_value3(comp_set_data->comp_gain_g, flag);

				sprintf(comp_set_data->comp_gain_g_buf, "%d", comp_set_data->comp_gain_g);
				d_label_set_text(vis, comp_set_data->comp_gain_g_buf);

			}
			else if(second_flag)
			{
				comp_set_data->comp_pwdb_lsb = set_comp_set_value4(comp_set_data->comp_pwdb_lsb, flag);

				sprintf(comp_set_data->comp_pwdb_lsb_buf, "%d", comp_set_data->comp_pwdb_lsb);
				d_label_set_text(vis, comp_set_data->comp_pwdb_lsb_buf);

			}
			break;
		case ID_COMP_BUTTON_4:
			
			vis = d_frame_get_control(frm, ID_COMP_LABEL_4);
			if(first_flag)
			{
				
				comp_set_data->comp_gain_r = set_comp_set_value3(comp_set_data->comp_gain_r, flag);

				sprintf(comp_set_data->comp_gain_r_buf, "%d", comp_set_data->comp_gain_r);
				d_label_set_text(vis, comp_set_data->comp_gain_r_buf);
			}
			else if(second_flag)
			{
				comp_set_data->comp_pwdb_msb = set_comp_set_value4(comp_set_data->comp_pwdb_msb, flag);

				sprintf(comp_set_data->comp_pwdb_msb_buf, "%d", comp_set_data->comp_pwdb_msb);
				d_label_set_text(vis, comp_set_data->comp_pwdb_msb_buf);
			}
			break;
		case ID_COMP_BUTTON_5:
			vis = d_frame_get_control(frm, ID_COMP_LABEL_5);
			if(first_flag)
			{
				comp_set_data->comp_i_adc = set_comp_set_value5(comp_set_data->comp_i_adc, flag);
				sprintf(comp_set_data->comp_i_adc_buf, "%d", comp_set_data->comp_i_adc);
				d_label_set_text(vis, comp_set_data->comp_i_adc_buf);

			}
			else 
			{
				comp_set_data->comp_test_adcref = set_comp_set_value5(comp_set_data->comp_test_adcref, flag);

				sprintf(comp_set_data->comp_test_adcref_buf, "%d", comp_set_data->comp_test_adcref);
				d_label_set_text(vis, comp_set_data->comp_test_adcref_buf);
			}
			break;
		case ID_COMP_BUTTON_6:
			vis = d_frame_get_control(frm, ID_COMP_LABEL_6);
			
			if(first_flag)
			{
				comp_set_data->comp_i_pga= set_comp_set_value5(comp_set_data->comp_i_pga, flag);
				sprintf(comp_set_data->comp_i_pga_buf, "%d", comp_set_data->comp_i_pga);
				d_label_set_text(vis, comp_set_data->comp_i_pga_buf);
			}
			else 
			{
				comp_set_data->comp_vclamplevel_b = set_comp_set_value3(comp_set_data->comp_vclamplevel_b, flag);

				sprintf(comp_set_data->comp_vclamplevel_b_buf, "%d", comp_set_data->comp_vclamplevel_b);
				d_label_set_text(vis, comp_set_data->comp_vclamplevel_b_buf);
			}
			break;
		case ID_COMP_BUTTON_7:
			vis = d_frame_get_control(frm, ID_COMP_LABEL_7);
			
			if(first_flag)
			{
				comp_set_data->comp_vclampimp = set_comp_set_value3(comp_set_data->comp_vclampimp, flag);

				sprintf(comp_set_data->comp_vclampimp_buf, "%d", comp_set_data->comp_vclampimp);
				d_label_set_text(vis, comp_set_data->comp_vclampimp_buf);

			}
			else 
			{
				comp_set_data->comp_vclamplevel_g = set_comp_set_value3(comp_set_data->comp_vclamplevel_g, flag);

				sprintf(comp_set_data->comp_vclamplevel_g_buf, "%d", comp_set_data->comp_vclamplevel_g);
				d_label_set_text(vis, comp_set_data->comp_vclamplevel_g_buf);
			}
			break;
		case ID_COMP_BUTTON_8:
			vis = d_frame_get_control(frm, ID_COMP_LABEL_8);
			
			if(first_flag)
			{
				comp_set_data->comp_inbw_b = set_comp_set_value3(comp_set_data->comp_inbw_b, flag);

				sprintf(comp_set_data->comp_inbw_b_buf, "%d", comp_set_data->comp_inbw_b);
				d_label_set_text(vis, comp_set_data->comp_inbw_b_buf);
			}
			else 
			{
				comp_set_data->comp_vclamplevel_r = set_comp_set_value3(comp_set_data->comp_vclamplevel_r, flag);

				sprintf(comp_set_data->comp_vclamplevel_r_buf, "%d", comp_set_data->comp_vclamplevel_r);
				d_label_set_text(vis, comp_set_data->comp_vclamplevel_r_buf);
			}
			break;
		case ID_COMP_BUTTON_9:
			vis = d_frame_get_control(frm, ID_COMP_LABEL_9);
			
			if(first_flag)
			{
				comp_set_data->comp_inbw_g = set_comp_set_value3(comp_set_data->comp_inbw_g, flag);

				sprintf(comp_set_data->comp_inbw_g_buf, "%d", comp_set_data->comp_inbw_g);
				d_label_set_text(vis, comp_set_data->comp_inbw_g_buf);

			}
			else
			{
				if(comp_set_data->comp_clampselect== 0)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
					comp_set_data->comp_clampselect = 1;
				}
				else if(comp_set_data->comp_clampselect == 1)
				{
					d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
					comp_set_data->comp_clampselect = 0;
				}

			}
			break;
		case ID_COMP_BUTTON_10:
			vis = d_frame_get_control(frm, ID_COMP_LABEL_10);
			if(first_flag)
			{
				
				comp_set_data->comp_inbw_r = set_comp_set_value3(comp_set_data->comp_inbw_r, flag);

				sprintf(comp_set_data->comp_inbw_r_buf, "%d", comp_set_data->comp_inbw_r);
				d_label_set_text(vis, comp_set_data->comp_inbw_r_buf);

			}
			else
			{
				comp_set_data->comp_vcom1_sel = set_comp_set_value5(comp_set_data->comp_vcom1_sel, flag);

				sprintf(comp_set_data->comp_vcom1_sel_buf, "%d", comp_set_data->comp_vcom1_sel);
				d_label_set_text(vis, comp_set_data->comp_vcom1_sel_buf);
			}
			break;
		case ID_COMP_BUTTON_11:
			vis = d_frame_get_control(frm, ID_COMP_LABEL_11);
			if(first_flag)
			{
				
				comp_set_data->comp_offs_b= set_comp_set_value2(comp_set_data->comp_offs_b, flag);

				sprintf(comp_set_data->comp_offs_b_buf, "%d", comp_set_data->comp_offs_b);
				d_label_set_text(vis, comp_set_data->comp_offs_b_buf);

			}
			break;
		case ID_COMP_BUTTON_12:
			vis = d_frame_get_control(frm, ID_COMP_LABEL_12);
			if(first_flag)
			{
				
				comp_set_data->comp_offs_g= set_comp_set_value2(comp_set_data->comp_offs_g, flag);

				sprintf(comp_set_data->comp_offs_g_buf, "%d", comp_set_data->comp_offs_g);
				d_label_set_text(vis, comp_set_data->comp_offs_g_buf);
			}
			break;
		case ID_COMP_BUTTON_13:
			vis = d_frame_get_control(frm, ID_COMP_LABEL_13);
			if(first_flag)
			{
				
				comp_set_data->comp_offs_r= set_comp_set_value2(comp_set_data->comp_offs_r, flag);

				sprintf(comp_set_data->comp_offs_r_buf, "%d", comp_set_data->comp_offs_r);
				d_label_set_text(vis, comp_set_data->comp_offs_r_buf);
			
			}
			break;
		case ID_COMP_BUTTON_14:
			vis = d_frame_get_control(frm, ID_COMP_LABEL_14);
			if(first_flag)
			{
				
				comp_set_data->comp_pga_ref = set_comp_set_value5(comp_set_data->comp_pga_ref, flag);

				sprintf(comp_set_data->comp_pga_ref_buf, "%d", comp_set_data->comp_pga_ref);
				d_label_set_text(vis, comp_set_data->comp_pga_ref_buf);
			}
			break;
		case ID_COMP_BUTTON_15:
			vis = d_frame_get_control(frm, ID_COMP_LABEL_15);
			if(first_flag)
			{
				
				comp_set_data->comp_iclamp_b = set_comp_set_value4(comp_set_data->comp_iclamp_b, flag);

				sprintf(comp_set_data->comp_iclamp_b_buf, "%d", comp_set_data->comp_iclamp_b);
				d_label_set_text(vis, comp_set_data->comp_iclamp_b_buf);

			}
			break;
		case ID_COMP_BUTTON_16:
			vis = d_frame_get_control(frm, ID_COMP_LABEL_16);
			if(first_flag)
			{
				
				comp_set_data->comp_iclamp_g = set_comp_set_value4(comp_set_data->comp_iclamp_g, flag);

				sprintf(comp_set_data->comp_iclamp_g_buf, "%d", comp_set_data->comp_iclamp_g);
				d_label_set_text(vis, comp_set_data->comp_iclamp_g_buf);
			}
			break;
		default:
			break;
	}
	set_param_of_comp();

	return D_OK;
}

static D_Result
button_1_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_1);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_3);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_4);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
button_2_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_2);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_5);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_6);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_7);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_8);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_9);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_10);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
			break;
		case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}static D_Result
button_13_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_13);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_14);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_11);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_12);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_15);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
	D_Frame *frm = &comp_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_COMP_LABEL_16);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_comp_set_data(id, D_TRUE);
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
get_set_of_comp_set(void) D_FUNCPOSTFIT
{
	if(comp_set_data->hdflag)
    {
        p_tvconf_get_hdcomp_set_param(&comp_set_data->param, p_vip_get_dbinput(comp_set_data->input));
    }
    else
    {
        p_tvconf_get_comp_set_param(&comp_set_data->param, p_vip_get_dbinput(comp_set_data->input));
    }
	comp_set_data->comp_flip_clk= comp_set_data->param.comp_flip_clk;
	comp_set_data->comp_i_adc = comp_set_data->param.comp_i_adc;

	comp_set_data->comp_gain_r = comp_set_data->param.comp_gain_r;
	comp_set_data->comp_gain_g = comp_set_data->param.comp_gain_g;
	comp_set_data->comp_gain_b = comp_set_data->param.comp_gain_b;	


	comp_set_data->comp_offs_r = comp_set_data->param.comp_offs_r;	
	comp_set_data->comp_offs_g = comp_set_data->param.comp_offs_g;	
	comp_set_data->comp_offs_b = comp_set_data->param.comp_offs_b;	
	comp_set_data->comp_iclamp_r = comp_set_data->param.comp_iclamp_r;	
	comp_set_data->comp_iclamp_g = comp_set_data->param.comp_iclamp_g;	
	comp_set_data->comp_iclamp_b = comp_set_data->param.comp_iclamp_b;	
	comp_set_data->comp_imaxsel = comp_set_data->param.comp_imaxsel;	


	comp_set_data->comp_i_pga= comp_set_data->param.comp_i_pga;
	comp_set_data->comp_vclampimp= comp_set_data->param.comp_vclampimp;
	comp_set_data->comp_inbw_b= comp_set_data->param.comp_inbw_b;
	comp_set_data->comp_inbw_g= comp_set_data->param.comp_inbw_g;
	comp_set_data->comp_inbw_r= comp_set_data->param.comp_inbw_r;

	comp_set_data->comp_pga_ref = comp_set_data->param.comp_pga_ref;
	comp_set_data->comp_pwdb_lsb = comp_set_data->param.comp_pwdb_lsb;
	comp_set_data->comp_pwdb_msb = comp_set_data->param.comp_pwdb_msb;
	comp_set_data->comp_test_adcref = comp_set_data->param.comp_test_adcref;
	comp_set_data->comp_vclamplevel_b = comp_set_data->param.comp_vclamplevel_b;
	comp_set_data->comp_vclamplevel_g = comp_set_data->param.comp_vclamplevel_g;
	comp_set_data->comp_vclamplevel_r= comp_set_data->param.comp_vclamplevel_r;

	comp_set_data->comp_clampselect = comp_set_data->param.comp_clampselect;
	comp_set_data->comp_vcom1_sel = comp_set_data->param.comp_vcom1_sel;
	
	sprintf(comp_set_data->comp_i_adc_buf, "%d", comp_set_data->comp_i_adc);

	sprintf(comp_set_data->comp_gain_r_buf, "%d", comp_set_data->comp_gain_r);
	sprintf(comp_set_data->comp_gain_g_buf, "%d", comp_set_data->comp_gain_g);
	sprintf(comp_set_data->comp_gain_b_buf, "%d", comp_set_data->comp_gain_b);

	sprintf(comp_set_data->comp_offs_r_buf, "%d", comp_set_data->comp_offs_r);
	sprintf(comp_set_data->comp_offs_g_buf, "%d", comp_set_data->comp_offs_g);
	sprintf(comp_set_data->comp_offs_b_buf, "%d", comp_set_data->comp_offs_b);
	sprintf(comp_set_data->comp_iclamp_r_buf, "%d", comp_set_data->comp_iclamp_r);
	sprintf(comp_set_data->comp_iclamp_g_buf, "%d", comp_set_data->comp_iclamp_g);
	sprintf(comp_set_data->comp_iclamp_b_buf, "%d", comp_set_data->comp_iclamp_b);
	sprintf(comp_set_data->comp_imaxsel_buf, "%d", comp_set_data->comp_imaxsel);
	
	sprintf(comp_set_data->comp_i_pga_buf, "%d", comp_set_data->comp_i_pga);
	sprintf(comp_set_data->comp_vclampimp_buf, "%d", comp_set_data->comp_vclampimp);
	sprintf(comp_set_data->comp_inbw_b_buf, "%d", comp_set_data->comp_inbw_b);
	sprintf(comp_set_data->comp_inbw_g_buf, "%d", comp_set_data->comp_inbw_g);

	sprintf(comp_set_data->comp_inbw_r_buf, "%d", comp_set_data->comp_inbw_r);
	sprintf(comp_set_data->comp_pga_ref_buf, "%d", comp_set_data->comp_pga_ref);
	sprintf(comp_set_data->comp_pwdb_lsb_buf, "%d", comp_set_data->comp_pwdb_lsb);

	sprintf(comp_set_data->comp_pwdb_msb_buf, "%d", comp_set_data->comp_pwdb_msb);
	sprintf(comp_set_data->comp_test_adcref_buf, "%d", comp_set_data->comp_test_adcref);
	sprintf(comp_set_data->comp_vclamplevel_b_buf, "%d", comp_set_data->comp_vclamplevel_b);
	sprintf(comp_set_data->comp_vclamplevel_g_buf, "%d", comp_set_data->comp_vclamplevel_g);
	sprintf(comp_set_data->comp_vclamplevel_r_buf, "%d", comp_set_data->comp_vclamplevel_r);
	sprintf(comp_set_data->comp_vcom1_sel_buf, "%d", comp_set_data->comp_vcom1_sel);

	return D_OK;
}

static D_Result
set_first_page_show(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &comp_set_window;
    D_Visual *vis;
	D_ID i;

	first_flag = D_TRUE;
	second_flag = D_FALSE;
	third_flag = D_FALSE;
	
	vis = d_frame_get_control(frm, ID_COMP_LABEL_COMP);
	d_label_set_text(vis, "COMP");
	
	vis = d_frame_get_control(frm, ID_COMP_BUTTON_1);
	d_label_set_text(vis, "Comp Flip Clk");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_2);
	d_label_set_text(vis, "Comp Gain B");
	
	vis = d_frame_get_control(frm, ID_COMP_BUTTON_3);
	d_label_set_text(vis, "Comp Gain G");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_4);
	d_label_set_text(vis, "Comp Gain R");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_5);
	d_label_set_text(vis, "Comp I Adc");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_6);
	d_label_set_text(vis, "Comp I Pga");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_7);
	d_label_set_text(vis, "Comp Vclampimp");
	vis = d_frame_get_control(frm, ID_COMP_BUTTON_8);
	d_label_set_text(vis, "Comp Inbw B");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_9);
	d_label_set_text(vis, "Comp Inbw G");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_10);
	d_label_set_text(vis, "Comp Inbw R");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_11);
	d_label_set_text(vis, "Comp Offs B");
	
	vis = d_frame_get_control(frm, ID_COMP_BUTTON_12);
	d_label_set_text(vis, "Comp Offs G");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_13);
	d_label_set_text(vis, "Comp Offs R");
	
	vis = d_frame_get_control(frm, ID_COMP_BUTTON_14);
	d_label_set_text(vis, "Comp Pga Ref");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_15);
	d_label_set_text(vis, "Comp Iclamp B");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_16);
	d_label_set_text(vis, "Comp Iclamp G");

	vis = d_frame_get_control(frm, ID_COMP_LABEL_1);
	vis_switch_init(comp_set_data->comp_flip_clk, vis);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_2);
	d_label_set_text(vis, comp_set_data->comp_gain_b_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_3);
	d_label_set_text(vis, comp_set_data->comp_gain_g_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_4);
	d_label_set_text(vis, comp_set_data->comp_gain_r_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_5);
	d_label_set_text(vis, comp_set_data->comp_i_adc_buf);
	
	vis = d_frame_get_control(frm, ID_COMP_LABEL_6);
	d_label_set_text(vis, comp_set_data->comp_i_pga_buf);
	
	vis = d_frame_get_control(frm, ID_COMP_LABEL_7);
	d_label_set_text(vis, comp_set_data->comp_vclampimp_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_8);
	d_label_set_text(vis, comp_set_data->comp_inbw_b_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_9);
	d_label_set_text(vis, comp_set_data->comp_inbw_g_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_10);
	d_label_set_text(vis, comp_set_data->comp_inbw_r_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_11);
	d_label_set_text(vis, comp_set_data->comp_offs_b_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_12);
	d_label_set_text(vis, comp_set_data->comp_offs_g_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_13);
	d_label_set_text(vis, comp_set_data->comp_offs_r_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_14);
	d_label_set_text(vis, comp_set_data->comp_pga_ref_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_15);
	d_label_set_text(vis, comp_set_data->comp_iclamp_b_buf); 

	vis = d_frame_get_control(frm, ID_COMP_LABEL_16);
	d_label_set_text(vis, comp_set_data->comp_iclamp_g_buf); 

	for(i = ID_COMP_GROUP_11; i <= ID_COMP_GROUP_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_vis_enable(vis, D_TRUE);
	}

	for(i = ID_COMP_BUTTON_11; i <= ID_COMP_BUTTON_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_vis_set_focusable(vis, D_TRUE);
	}
	
	return D_OK;
}

static D_Result
set_second_page_show(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &comp_set_window;
    D_Visual *vis;
	D_ID i;

	second_flag = D_TRUE;
	first_flag = D_FALSE;
	third_flag = D_FALSE;

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_1);
	d_label_set_text(vis, "Comp Iclamp R");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_2);
	d_label_set_text(vis, "Comp Imaxsel");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_3);
	d_label_set_text(vis, "Comp Pwdb Lsb");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_4);
	d_label_set_text(vis, "Comp Pwdb Msb");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_5);
	d_label_set_text(vis, "Comp Test Adcref");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_6);
	d_label_set_text(vis, "Comp Vclamplevel B");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_7);
	d_label_set_text(vis, "Comp Vclamplevel G");
	
	vis = d_frame_get_control(frm, ID_COMP_BUTTON_8);
	d_label_set_text(vis, "Comp Vclamplevel R");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_9);
	d_label_set_text(vis, "Comp Clampselect");

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_10);
	d_label_set_text(vis, "Comp Vcom1 Sel");
	


	vis = d_frame_get_control(frm, ID_COMP_LABEL_1);
	d_label_set_text(vis, comp_set_data->comp_iclamp_r_buf);
	
	vis = d_frame_get_control(frm, ID_COMP_LABEL_2);
	d_label_set_text(vis, comp_set_data->comp_imaxsel_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_3);
	d_label_set_text(vis, comp_set_data->comp_pwdb_lsb_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_4);
	d_label_set_text(vis, comp_set_data->comp_pwdb_msb_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_5);
	d_label_set_text(vis, comp_set_data->comp_test_adcref_buf);
	
	vis = d_frame_get_control(frm, ID_COMP_LABEL_6);
	d_label_set_text(vis, comp_set_data->comp_vclamplevel_b_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_7);
	d_label_set_text(vis, comp_set_data->comp_vclamplevel_g_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_8);
	d_label_set_text(vis, comp_set_data->comp_vclamplevel_r_buf);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_9);
	vis_switch_init(comp_set_data->comp_clampselect, vis);

	vis = d_frame_get_control(frm, ID_COMP_LABEL_10);
	d_label_set_text(vis, comp_set_data->comp_vcom1_sel_buf);


	for(i = ID_COMP_GROUP_11; i <= ID_COMP_GROUP_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_vis_enable(vis, D_FALSE);
	}

	for(i = ID_COMP_BUTTON_11; i <= ID_COMP_BUTTON_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_label_set_text(vis, NULL);
		d_vis_set_focusable(vis, D_FALSE);
	}

	for(i = ID_COMP_LABEL_11; i <= ID_COMP_LABEL_16; i++)
	{
		vis = d_frame_get_control(frm, i);
		d_label_set_text(vis, NULL);
	}

	return D_OK;
}


static D_Result
comp_set_vis_handler(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &comp_set_window;
    D_Visual *vis;
	
	vis = d_frame_get_control(frm, ID_COMP_BUTTON_1);
	d_vis_set_handler(vis, button_1_set_handler);

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_2);
	d_vis_set_handler(vis, button_2_set_handler);
	
	vis = d_frame_get_control(frm, ID_COMP_BUTTON_3);
	d_vis_set_handler(vis, button_3_set_handler);

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_4);
	d_vis_set_handler(vis, button_4_set_handler);

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_5);
	d_vis_set_handler(vis, button_5_set_handler);

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_6);
	d_vis_set_handler(vis, button_6_set_handler);

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_7);
	d_vis_set_handler(vis, button_7_set_handler);

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_8);
	d_vis_set_handler(vis, button_8_set_handler);

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_9);
	d_vis_set_handler(vis, button_9_set_handler);

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_10);
	d_vis_set_handler(vis, button_10_set_handler);

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_11);
	d_vis_set_handler(vis, button_11_set_handler);
	
	vis = d_frame_get_control(frm, ID_COMP_BUTTON_12);
	d_vis_set_handler(vis, button_12_set_handler);

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_13);
	d_vis_set_handler(vis, button_13_set_handler);
	
	vis = d_frame_get_control(frm, ID_COMP_BUTTON_14);
	d_vis_set_handler(vis, button_14_set_handler);

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_15);
	d_vis_set_handler(vis, button_15_set_handler);

	vis = d_frame_get_control(frm, ID_COMP_BUTTON_16);
	d_vis_set_handler(vis, button_16_set_handler);

	return D_OK;
}


static D_Result
comp_set_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{	
	D_Visual *fv;
	D_Frame *frm = &comp_set_window;
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
					if(comp_set_data->focus == ID_COMP_BUTTON_1 && first_flag)
					{
						set_second_page_show();
						comp_set_data->focus = ID_COMP_BUTTON_10;
					}
					else if(comp_set_data->focus == ID_COMP_BUTTON_1 && second_flag)
					{
						set_first_page_show();
						comp_set_data->focus = ID_COMP_BUTTON_16;
					}
					else
					{
						comp_set_data->focus--;	
					}
					d_vis_set_focus(d_frame_get_control(frm, comp_set_data->focus));
					break;
				case D_KEY_DOWN:
				case D_KEY_PNL_D:
					if(comp_set_data->focus == ID_COMP_BUTTON_10 && second_flag)
					{
						set_first_page_show();
						comp_set_data->focus = ID_COMP_BUTTON_1;
					}
					else if(comp_set_data->focus == ID_COMP_BUTTON_16 && first_flag)
					{
						comp_set_data->focus = ID_COMP_BUTTON_1;
						set_second_page_show();
					}
					else 
					{
						comp_set_data->focus++;
					}
					d_vis_set_focus(d_frame_get_control(frm, comp_set_data->focus));
					break;
				case D_KEY_RIGHT:
				case D_KEY_PNL_R:
					set_comp_set_data(id, D_TRUE);
					break;
				case D_KEY_LEFT:
				case D_KEY_PNL_L:
					set_comp_set_data(id, D_FALSE);
					break;
				case D_KEY_MENU:
					return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
			save_param_of_comp();
            
			 if(comp_set_data)
            {
                PROJECT_FREE(comp_set_data);
                comp_set_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
comp_set_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

	comp_set_data = (D_CompSetDate*)PROJECT_ALLOC(sizeof(D_CompSetDate));
    if(!comp_set_data)
    {
        return D_ERR;
    }
	memset(comp_set_data, 0, sizeof(D_CompSetDate));
	comp_set_data->input = p_conf_get_vid_input();
	if(comp_set_data->input == D_VID_IUTPUT_AV1 || comp_set_data->input == D_VID_IUTPUT_AV2|| comp_set_data->input == D_VID_IUTPUT_TV)
	{
		comp_set_data->hdflag = p_vip_get_ntscflag();
	}
	else
	{
		comp_set_data->hdflag = p_vip_get_hdflag();
	}
	comp_set_data->focus = ID_COMP_BUTTON_1;
	
	get_set_of_comp_set();
	comp_set_vis_handler();
	set_first_page_show();

	vis = d_frame_get_control(frm, ID_COMP_GROUP);
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
		d_vis_set_handler(vis, comp_set_window_handler);
	}

    return D_OK;
}

/** @brief 	COMP菜单*/
D_Result
p_atv_comp_set_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&comp_set_window, D_TRUE);
}

