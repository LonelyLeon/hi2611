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
#include "de_set_window.c"

#define BUF_LINE 4

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus={{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal={{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
	D_S16 lti_on, cti_on, peak_on, de_core, de_nl_en, lti_gain, cti_gain, pk_core, pk_up,
		pk_beta, pk_gain, pk_cfg, pk_negain, lti_f_idx, cti_f_idx, pk_f_idx, sts_on;
	D_VidInput input;
	D_U8 hdflag;
	D_DE_SET param;

	D_Char de_core_buf[BUF_LINE];
	D_Char lti_gain_buf[BUF_LINE];
	D_Char cti_gain_buf[BUF_LINE];
	D_Char pk_core_buf[BUF_LINE];
	D_Char pk_up_buf[8];
	D_Char pk_beta_buf[BUF_LINE];
	D_Char pk_gain_buf[BUF_LINE];
	D_Char pk_negain_buf[BUF_LINE];
	D_Char cti_f_idx_buf[BUF_LINE];
	D_Char lti_f_idx_buf[BUF_LINE];
	D_Char pk_f_idx_buf[BUF_LINE];
	
}D_DeSetDate;

static D_DeSetDate *de_set_data;

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
save_param_of_de(void) D_FUNCPOSTFIT
{
	
 	if(de_set_data->hdflag)
    {
        p_tvconf_set_hdde_set_param(&de_set_data->param, p_vip_get_dbinput(de_set_data->input));
    }
    else
    {
        p_tvconf_set_de_set_param(&de_set_data->param, p_vip_get_dbinput(de_set_data->input));
    }

	return D_OK;
}

static D_Result
set_param_of_de(void) D_FUNCPOSTFIT
{
	de_set_data->param.lti_on= de_set_data->lti_on;
	de_set_data->param.cti_on= de_set_data->cti_on;
	de_set_data->param.peak_on= de_set_data->peak_on;
	de_set_data->param.pk_cfg = de_set_data->pk_cfg;
	de_set_data->param.de_nl_en = de_set_data->de_nl_en;
	de_set_data->param.sts_on= de_set_data->sts_on;
	
	de_set_data->param.de_core = de_set_data->de_core;
	de_set_data->param.cti_gain = de_set_data->cti_gain;
	de_set_data->param.lti_gain = de_set_data->lti_gain;
	de_set_data->param.pk_core = de_set_data->pk_core;
	de_set_data->param.pk_up = de_set_data->pk_up;
	de_set_data->param.pk_beta = de_set_data->pk_beta;
	de_set_data->param.pk_negain = de_set_data->pk_negain;
	de_set_data->param.pk_gain = de_set_data->pk_gain;
	de_set_data->param.lti_f_idx= de_set_data->lti_f_idx;
	de_set_data->param.cti_f_idx= de_set_data->cti_f_idx;
	de_set_data->param.pk_f_idx= de_set_data->pk_f_idx; 
	d_vip_setDe((D_U8*)&de_set_data->param);

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
set_de_set_value(D_S16 value, D_Bool flag)
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
set_de_set_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis;
	
	switch(id)
	{
		case ID_DE_BUTTON_1:
			vis = d_frame_get_control(frm, ID_DE_LABEL_1);
			if(de_set_data->lti_on == 0)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
				de_set_data->lti_on = 1;
			}
			else if(de_set_data->lti_on == 1)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
				de_set_data->lti_on = 0;
			}
			break;
		case ID_DE_BUTTON_2:
			vis = d_frame_get_control(frm, ID_DE_LABEL_2);
			if(de_set_data->cti_on == 0)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
				de_set_data->cti_on = 1;
			}
			else if(de_set_data->cti_on == 1)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
				de_set_data->cti_on = 0;
			}
			break;
		case ID_DE_BUTTON_3:
			vis = d_frame_get_control(frm, ID_DE_LABEL_3);
			if(de_set_data->peak_on == 0)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
				de_set_data->peak_on = 1;
			}
			else if(de_set_data->peak_on == 1)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
				de_set_data->peak_on = 0;
			}
			break;
		case ID_DE_BUTTON_4:
			de_set_data->de_core = set_de_set_value(de_set_data->de_core, flag);

			vis = d_frame_get_control(frm, ID_DE_LABEL_4);
			{
				sprintf(de_set_data->de_core_buf, "%d", de_set_data->de_core);
				d_label_set_text(vis, de_set_data->de_core_buf);
			}
			break;
		case ID_DE_BUTTON_5:
			vis = d_frame_get_control(frm, ID_DE_LABEL_5);
			if(de_set_data->de_nl_en == 0)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
				de_set_data->de_nl_en = 1;
			}
			else if(de_set_data->de_nl_en == 1)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
				de_set_data->de_nl_en = 0;
			}
			break;
		case ID_DE_BUTTON_6:
			de_set_data->lti_gain = set_de_set_value(de_set_data->lti_gain, flag);

			vis = d_frame_get_control(frm, ID_DE_LABEL_6);
			{
				sprintf(de_set_data->lti_gain_buf, "%d", de_set_data->lti_gain);
				d_label_set_text(vis, de_set_data->lti_gain_buf);
			}
			break;
		case ID_DE_BUTTON_7:
			de_set_data->cti_gain = set_de_set_value(de_set_data->cti_gain, flag);

			vis = d_frame_get_control(frm, ID_DE_LABEL_7);
			{
				sprintf(de_set_data->cti_gain_buf, "%d", de_set_data->cti_gain);
				d_label_set_text(vis, de_set_data->cti_gain_buf);
			}
			break;
		case ID_DE_BUTTON_8:
			de_set_data->pk_core = set_de_set_value(de_set_data->pk_core, flag);

			vis = d_frame_get_control(frm, ID_DE_LABEL_8);
			{
				sprintf(de_set_data->pk_core_buf, "%d", de_set_data->pk_core);
				d_label_set_text(vis, de_set_data->pk_core_buf);
			}
			break;
			break;
		case ID_DE_BUTTON_9:
			if(flag)
			{
				if(de_set_data->pk_up >= 1023)
					de_set_data->pk_up = 0;
				else 
					de_set_data->pk_up = de_set_data->pk_up + 4;
			}
			else
			{
				if(de_set_data->pk_up <=  0)
					de_set_data->pk_up = 1023;
				else 
					de_set_data->pk_up = de_set_data->pk_up - 4;
			}

			vis = d_frame_get_control(frm, ID_DE_LABEL_9);
			{
				sprintf(de_set_data->pk_up_buf, "%d", de_set_data->pk_up);
				d_label_set_text(vis, de_set_data->pk_up_buf);
			}
			break;
		case ID_DE_BUTTON_10:
			if(flag)
			{
				if(de_set_data->pk_beta == 63)
					de_set_data->pk_beta = 0;
				else 
					de_set_data->pk_beta++;
			}
			else
			{
				if(de_set_data->pk_beta == 0)
					de_set_data->pk_beta = 63;
				else 
					de_set_data->pk_beta--;
			}

			vis = d_frame_get_control(frm, ID_DE_LABEL_10);
			{
				sprintf(de_set_data->pk_beta_buf, "%d", de_set_data->pk_beta);
				d_label_set_text(vis, de_set_data->pk_beta_buf);
			}
			break;
		case ID_DE_BUTTON_11:
			de_set_data->pk_gain = set_de_set_value(de_set_data->pk_gain, flag);

			vis = d_frame_get_control(frm, ID_DE_LABEL_11);
			{
				sprintf(de_set_data->pk_gain_buf, "%d", de_set_data->pk_gain);
				d_label_set_text(vis, de_set_data->pk_gain_buf);
			}
			break;
		case ID_DE_BUTTON_12:
			vis = d_frame_get_control(frm, ID_DE_LABEL_12);
			if(de_set_data->pk_cfg == 0)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
				de_set_data->pk_cfg = 1;
			}
			else if(de_set_data->pk_cfg == 1)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
				de_set_data->pk_cfg = 0;
			}
			break;
		case ID_DE_BUTTON_13:
			de_set_data->pk_negain = set_de_set_value(de_set_data->pk_negain, flag);

			vis = d_frame_get_control(frm, ID_DE_LABEL_13);
			{
				sprintf(de_set_data->pk_negain_buf, "%d", de_set_data->pk_negain);
				d_label_set_text(vis, de_set_data->pk_negain_buf);
			}
			break;
		case ID_DE_BUTTON_14:
			if(flag)
			{
				if(de_set_data->lti_f_idx == 3)
					de_set_data->lti_f_idx = 0;
				else 
					de_set_data->lti_f_idx++;
			}
			else
			{
				if(de_set_data->lti_f_idx == 0)
					de_set_data->lti_f_idx = 3;
				else 
					de_set_data->lti_f_idx--;
			}

			vis = d_frame_get_control(frm, ID_DE_LABEL_14);
			{
				sprintf(de_set_data->lti_f_idx_buf, "%d", de_set_data->lti_f_idx);
				d_label_set_text(vis, de_set_data->lti_f_idx_buf);
			}
			break;
		case ID_DE_BUTTON_15:
			if(flag)
			{
				if(de_set_data->cti_f_idx == 3)
					de_set_data->cti_f_idx = 0;
				else 
					de_set_data->cti_f_idx++;
			}
			else
			{
				if(de_set_data->cti_f_idx == 0)
					de_set_data->cti_f_idx = 3;
				else 
					de_set_data->cti_f_idx--;
			}

			vis = d_frame_get_control(frm, ID_DE_LABEL_15);
			{
				sprintf(de_set_data->cti_f_idx_buf, "%d", de_set_data->cti_f_idx);
				d_label_set_text(vis, de_set_data->cti_f_idx_buf);
			}
			break;
		case ID_DE_BUTTON_16:
			if(flag)
			{
				if(de_set_data->pk_f_idx== 3)
					de_set_data->pk_f_idx = 0;
				else 
					de_set_data->pk_f_idx ++;
			}
			else 
			{
				if(de_set_data->pk_f_idx == 0)
					de_set_data->pk_f_idx = 3;
				else 
					de_set_data->pk_f_idx --;
			}

			vis = d_frame_get_control(frm, ID_DE_LABEL_16);
			{
				sprintf(de_set_data->pk_f_idx_buf, "%d", de_set_data->pk_f_idx);
				d_label_set_text(vis, de_set_data->pk_f_idx_buf);
			}
			break;
		case ID_DE_BUTTON_17:
			vis = d_frame_get_control(frm, ID_DE_LABEL_17);
			if(de_set_data->sts_on== 0)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
				de_set_data->sts_on = 1;
			}
			else if(de_set_data->sts_on == 1)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
				de_set_data->sts_on = 0;
			}
			break;
		default:
			break;
	}
	set_param_of_de();

	return D_OK;
}

static D_Result
lti_on_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_1);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
peak_on_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_3);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
de_core_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_4);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
cti_on_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_2);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
de_nl_en_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_5);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
lti_gain_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_6);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
cti_gain_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_7);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
pk_core_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_8);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
pk_up_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_9);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
pk_beta_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_10);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
			break;
		case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}static D_Result
pk_negain_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_13);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
lti_f_idx_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_14);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
pk_gain_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_11);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
			break;
		case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}static D_Result
pk_cfg_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_12);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
cti_f_idx_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_15);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
pk_f_idx_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_16);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
sts_on_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_DE_LABEL_17);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_de_set_data(id, D_TRUE);
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
get_set_of_de_set(void) D_FUNCPOSTFIT
{
	if(de_set_data->hdflag)
    {
        p_tvconf_get_hdde_set_param(&de_set_data->param, p_vip_get_dbinput(de_set_data->input));
    }
    else
    {
        p_tvconf_get_de_set_param(&de_set_data->param, p_vip_get_dbinput(de_set_data->input));
    }
	de_set_data->lti_on= de_set_data->param.lti_on;
	de_set_data->cti_on= de_set_data->param.cti_on;
	de_set_data->peak_on= de_set_data->param.peak_on;
	de_set_data->pk_cfg = de_set_data->param.pk_cfg;
	de_set_data->de_nl_en = de_set_data->param.de_nl_en;
	de_set_data->sts_on= de_set_data->param.sts_on;

	de_set_data->de_core = de_set_data->param.de_core;
	de_set_data->cti_gain = de_set_data->param.cti_gain;
	de_set_data->lti_gain = de_set_data->param.lti_gain;
	de_set_data->pk_core = de_set_data->param.pk_core;
	de_set_data->pk_up = de_set_data->param.pk_up;
	de_set_data->pk_beta = de_set_data->param.pk_beta;
	de_set_data->pk_negain = de_set_data->param.pk_negain;
	de_set_data->pk_gain = de_set_data->param.pk_gain;
	de_set_data->lti_f_idx= de_set_data->param.lti_f_idx;
	de_set_data->cti_f_idx= de_set_data->param.cti_f_idx;
	de_set_data->pk_f_idx= de_set_data->param.pk_f_idx;	
	
	sprintf(de_set_data->de_core_buf, "%d", de_set_data->de_core);
	sprintf(de_set_data->lti_gain_buf, "%d", de_set_data->lti_gain);
	sprintf(de_set_data->cti_gain_buf, "%d", de_set_data->cti_gain);
	sprintf(de_set_data->pk_core_buf, "%d", de_set_data->pk_core);
	sprintf(de_set_data->pk_up_buf, "%d", de_set_data->pk_up);
	sprintf(de_set_data->pk_beta_buf, "%d", de_set_data->pk_beta);
	sprintf(de_set_data->pk_gain_buf, "%d", de_set_data->pk_gain);
	sprintf(de_set_data->pk_negain_buf, "%d", de_set_data->pk_negain);
	sprintf(de_set_data->cti_f_idx_buf, "%d", de_set_data->cti_f_idx);
	sprintf(de_set_data->lti_f_idx_buf, "%d", de_set_data->lti_f_idx);
	sprintf(de_set_data->pk_f_idx_buf, "%d", de_set_data->pk_f_idx);
	
	return D_OK;
}


static D_Result
de_set_vis_set(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &de_set_window;
    D_Visual *vis;

	vis = d_frame_get_control(frm, ID_DE_LABEL_DE);
	d_label_set_text(vis, "DE");
	
	vis = d_frame_get_control(frm, ID_DE_BUTTON_1);
	d_label_set_text(vis, "Lti On");
	d_vis_set_handler(vis, lti_on_set_handler);

	vis = d_frame_get_control(frm, ID_DE_BUTTON_2);
	d_label_set_text(vis, "Cti On");
	d_vis_set_handler(vis, cti_on_handler);
	
	vis = d_frame_get_control(frm, ID_DE_BUTTON_3);
	d_label_set_text(vis, "Peak On");
	d_vis_set_handler(vis, peak_on_handler);

	vis = d_frame_get_control(frm, ID_DE_BUTTON_4);
	d_label_set_text(vis, "De Core");
	d_vis_set_handler(vis, de_core_handler);

	vis = d_frame_get_control(frm, ID_DE_BUTTON_5);
	d_label_set_text(vis, "De Nl En");
	d_vis_set_handler(vis, de_nl_en_handler);

	vis = d_frame_get_control(frm, ID_DE_BUTTON_6);
	d_label_set_text(vis, "Lti Gain");
	d_vis_set_handler(vis, lti_gain_handler);

	vis = d_frame_get_control(frm, ID_DE_BUTTON_7);
	d_label_set_text(vis, "Cti Gain");
	d_vis_set_handler(vis, cti_gain_handler);

	vis = d_frame_get_control(frm, ID_DE_BUTTON_8);
	d_label_set_text(vis, "Pk Core");
	d_vis_set_handler(vis, pk_core_handler);

	vis = d_frame_get_control(frm, ID_DE_BUTTON_9);
	d_label_set_text(vis, "Pk Up");
	d_vis_set_handler(vis, pk_up_handler);

	vis = d_frame_get_control(frm, ID_DE_BUTTON_10);
	d_label_set_text(vis, "Pk Beta");
	d_vis_set_handler(vis, pk_beta_handler);

	vis = d_frame_get_control(frm, ID_DE_BUTTON_11);
	d_label_set_text(vis, "Pk Gain");
	d_vis_set_handler(vis, pk_gain_handler);
	
	vis = d_frame_get_control(frm, ID_DE_BUTTON_12);
	d_label_set_text(vis, "Pk Cfg");
	d_vis_set_handler(vis, pk_cfg_handler);

	vis = d_frame_get_control(frm, ID_DE_BUTTON_13);
	d_label_set_text(vis, "Pk Negain");
	d_vis_set_handler(vis, pk_negain_handler);
	
	vis = d_frame_get_control(frm, ID_DE_BUTTON_14);
	d_label_set_text(vis, "Lti F Idx");
	d_vis_set_handler(vis, lti_f_idx_handler);

	vis = d_frame_get_control(frm, ID_DE_BUTTON_15);
	d_label_set_text(vis, "Cti F Idx");
	d_vis_set_handler(vis, cti_f_idx_handler);

	vis = d_frame_get_control(frm, ID_DE_BUTTON_16);
	d_label_set_text(vis, "Pk F Idx");
	d_vis_set_handler(vis, pk_f_idx_handler);

	vis = d_frame_get_control(frm, ID_DE_BUTTON_17);
	d_label_set_text(vis, "Sts On");
	d_vis_set_handler(vis, sts_on_handler);
	
	vis = d_frame_get_control(frm, ID_DE_LABEL_1);
	vis_switch_init(de_set_data->lti_on, vis);
	
	vis = d_frame_get_control(frm, ID_DE_LABEL_2);
	vis_switch_init(de_set_data->cti_on, vis);
	
	vis = d_frame_get_control(frm, ID_DE_LABEL_3);
	vis_switch_init(de_set_data->peak_on, vis);

	vis = d_frame_get_control(frm, ID_DE_LABEL_4);
	d_label_set_text(vis, de_set_data->de_core_buf);

	vis = d_frame_get_control(frm, ID_DE_LABEL_5);
	vis_switch_init(de_set_data->de_nl_en, vis);

	vis = d_frame_get_control(frm, ID_DE_LABEL_6);
	d_label_set_text(vis, de_set_data->lti_gain_buf);

	vis = d_frame_get_control(frm, ID_DE_LABEL_7);
	d_label_set_text(vis, de_set_data->cti_gain_buf);

	vis = d_frame_get_control(frm, ID_DE_LABEL_8);
	d_label_set_text(vis, de_set_data->pk_core_buf);

	vis = d_frame_get_control(frm, ID_DE_LABEL_9);
	d_label_set_text(vis, de_set_data->pk_up_buf);

	vis = d_frame_get_control(frm, ID_DE_LABEL_10);
	d_label_set_text(vis, de_set_data->pk_beta_buf);

	vis = d_frame_get_control(frm, ID_DE_LABEL_11);
	d_label_set_text(vis, de_set_data->pk_gain_buf);

	vis = d_frame_get_control(frm, ID_DE_LABEL_12);
	vis_switch_init(de_set_data->pk_cfg, vis);

	vis = d_frame_get_control(frm, ID_DE_LABEL_13);
	d_label_set_text(vis, de_set_data->pk_negain_buf);

	vis = d_frame_get_control(frm, ID_DE_LABEL_14);
	d_label_set_text(vis, de_set_data->lti_f_idx_buf);

	vis = d_frame_get_control(frm, ID_DE_LABEL_15);
	d_label_set_text(vis, de_set_data->cti_f_idx_buf);

	vis = d_frame_get_control(frm, ID_DE_LABEL_16);
	d_label_set_text(vis, de_set_data->pk_f_idx_buf);

	vis = d_frame_get_control(frm, ID_DE_LABEL_17);
	vis_switch_init(de_set_data->sts_on, vis);
	
	return D_OK;
}


static D_Result
de_set_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{	
	D_Visual *fv;
	D_Frame *frm = &de_set_window;
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
					set_de_set_data(id, D_TRUE);
					break;
				case D_KEY_LEFT:
				case D_KEY_PNL_L:
					set_de_set_data(id, D_FALSE);
					break;
				case D_KEY_MENU:
					return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
			save_param_of_de();
			 if(de_set_data)
            {
                PROJECT_FREE(de_set_data);
                de_set_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
de_set_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

	de_set_data = (D_DeSetDate*)PROJECT_ALLOC(sizeof(D_DeSetDate));
    if(!de_set_data)
    {
        return D_ERR;
    }
	memset(de_set_data, 0, sizeof(D_DeSetDate));
	de_set_data->input = p_conf_get_vid_input();
	if(de_set_data->input == D_VID_IUTPUT_AV1 || de_set_data->input == D_VID_IUTPUT_AV2|| de_set_data->input == D_VID_IUTPUT_TV)
	{
		de_set_data->hdflag = p_vip_get_ntscflag();
	}
	else
	{
		de_set_data->hdflag = p_vip_get_hdflag();
	}
	get_set_of_de_set();
	de_set_vis_set();
	
	vis = d_frame_get_control(frm, ID_DE_GROUP);
	if(vis)
	{
		d_group_set_focus_loop(vis, D_TRUE);
		d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
	}

	vis = d_frame_get_control(frm, 0);
	if(vis)
	{
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
		d_vis_set_handler(vis, de_set_window_handler);
	}

    return D_OK;
}

/** @brief 	DE菜单*/
D_Result
p_atv_de_set_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&de_set_window, D_TRUE);
}
