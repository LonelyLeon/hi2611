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
#include "ftc_set_window.c"

#define BUF_LINE 4

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus={{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal={{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
	D_S16 ftc_on, ftc_adj, ftd_htl, ftd_htu, ftd_hsl, ftd_hsu, ftd_ctl, ftd_ctu, 
		ftd_csl, ftd_csu, ftc_hgy, ftc_hgr, ftc_hcy, ftc_hcr;
	D_VidInput input;
	D_U8 hdflag;
	D_FTC_SET param;

	D_Char ftc_adj_buf[BUF_LINE];
	D_Char ftd_htl_buf[BUF_LINE];
	D_Char ftd_htu_buf[BUF_LINE];
	D_Char ftd_hsl_buf[BUF_LINE];
	D_Char ftd_hsu_buf[BUF_LINE];
	D_Char ftd_ctl_buf[BUF_LINE];
	D_Char ftd_ctu_buf[BUF_LINE];
	D_Char ftd_csl_buf[BUF_LINE];
	D_Char ftd_csu_buf[BUF_LINE];
	D_Char ftc_hgy_buf[BUF_LINE];
	D_Char ftc_hgr_buf[BUF_LINE];
	D_Char ftc_hcy_buf[BUF_LINE];
	D_Char ftc_hcr_buf[BUF_LINE];
}D_FtcSetDate;

static D_FtcSetDate *ftc_set_data;

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
save_param_of_ftc(void) D_FUNCPOSTFIT
{
	if(ftc_set_data->hdflag)
    {
		p_tvconf_set_hdftc_set_param(&ftc_set_data->param, p_vip_get_dbinput(ftc_set_data->input));
    }
    else
    {
		p_tvconf_set_ftc_set_param(&ftc_set_data->param, p_vip_get_dbinput(ftc_set_data->input));
    }
	return D_OK;
}

static D_Result
set_param_of_ftc(void) D_FUNCPOSTFIT
{
	ftc_set_data->param.ftc_adj = ftc_set_data->ftc_adj;
	ftc_set_data->param.ftd_htl = ftc_set_data->ftd_htl;
	ftc_set_data->param.ftd_htu = ftc_set_data->ftd_htu;
	ftc_set_data->param.ftd_hsl = ftc_set_data->ftd_hsl;
	ftc_set_data->param.ftd_hsu = ftc_set_data->ftd_hsu;
	ftc_set_data->param.ftd_ctl = ftc_set_data->ftd_ctl;
	ftc_set_data->param.ftd_ctu = ftc_set_data->ftd_ctu;
	ftc_set_data->param.ftd_csl = ftc_set_data->ftd_csl;
	ftc_set_data->param.ftd_csu = ftc_set_data->ftd_csu;
	ftc_set_data->param.ftc_hcy = ftc_set_data->ftc_hcy;
	ftc_set_data->param.ftc_hcr = ftc_set_data->ftc_hcr;
	ftc_set_data->param.ftc_hgy = ftc_set_data->ftc_hgy;
	ftc_set_data->param.ftc_hgr = ftc_set_data->ftc_hgr;
	ftc_set_data->param.ftc_on = ftc_set_data->ftc_on;

	d_vip_setFtc((D_U8*)&ftc_set_data->param);

	return D_OK;
}


static D_S16
set_ftc_set_value1(D_S16 value, D_Bool flag)
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
set_ftc_set_value2(D_S16 value, D_Bool flag)
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
set_ftc_set_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis;
	
	switch(id)
	{
		case ID_FTC_BUTTON_1:
			vis = d_frame_get_control(frm, ID_FTC_LABEL_1);
			if(ftc_set_data->ftc_on == 0)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_ON));
				ftc_set_data->ftc_on = 1;
			}
			else if(ftc_set_data->ftc_on == 1)
			{
				d_label_set_text(vis, d_gui_get_text(atv_IDS_OFF));
				ftc_set_data->ftc_on = 0;
			}
			break;
		case ID_FTC_BUTTON_2:
			ftc_set_data->ftc_adj = set_ftc_set_value1(ftc_set_data->ftc_adj, flag);
			
			vis = d_frame_get_control(frm, ID_FTC_LABEL_2);
			{
				sprintf(ftc_set_data->ftc_adj_buf, "%d", ftc_set_data->ftc_adj);
				d_label_set_text(vis, ftc_set_data->ftc_adj_buf);
			}
			break;
		case ID_FTC_BUTTON_3:
			ftc_set_data->ftd_htl = set_ftc_set_value2(ftc_set_data->ftd_htl, flag);
			
			vis = d_frame_get_control(frm, ID_FTC_LABEL_3);
			{
				sprintf(ftc_set_data->ftd_htl_buf, "%d", ftc_set_data->ftd_htl);
				d_label_set_text(vis, ftc_set_data->ftd_htl_buf);
			}
			break;
		case ID_FTC_BUTTON_4:
			ftc_set_data->ftd_htu = set_ftc_set_value2(ftc_set_data->ftd_htu, flag);
			
			vis = d_frame_get_control(frm, ID_FTC_LABEL_4);
			{
				sprintf(ftc_set_data->ftd_htu_buf, "%d", ftc_set_data->ftd_htu);
				d_label_set_text(vis, ftc_set_data->ftd_htu_buf);
			}
			break;
		case ID_FTC_BUTTON_5:
			ftc_set_data->ftd_hsl = set_ftc_set_value2(ftc_set_data->ftd_hsl, flag);

			vis = d_frame_get_control(frm, ID_FTC_LABEL_5);
			{
				sprintf(ftc_set_data->ftd_hsl_buf, "%d", ftc_set_data->ftd_hsl);
				d_label_set_text(vis, ftc_set_data->ftd_hsl_buf);
			}
			break;
		case ID_FTC_BUTTON_6:
			ftc_set_data->ftd_hsu = set_ftc_set_value2(ftc_set_data->ftd_hsu, flag);

			vis = d_frame_get_control(frm, ID_FTC_LABEL_6);
			{
				sprintf(ftc_set_data->ftd_hsu_buf, "%d", ftc_set_data->ftd_hsu);
				d_label_set_text(vis, ftc_set_data->ftd_hsu_buf);
			}
			break;
		case ID_FTC_BUTTON_7:
			ftc_set_data->ftd_ctl = set_ftc_set_value2(ftc_set_data->ftd_ctl, flag);

			vis = d_frame_get_control(frm, ID_FTC_LABEL_7);
			{
				sprintf(ftc_set_data->ftd_ctl_buf, "%d", ftc_set_data->ftd_ctl);
				d_label_set_text(vis, ftc_set_data->ftd_ctl_buf);
			}
			break;
		case ID_FTC_BUTTON_8:
			ftc_set_data->ftd_ctu = set_ftc_set_value2(ftc_set_data->ftd_ctu, flag);

			vis = d_frame_get_control(frm, ID_FTC_LABEL_8);
			{
				sprintf(ftc_set_data->ftd_ctu_buf, "%d", ftc_set_data->ftd_ctu);
				d_label_set_text(vis, ftc_set_data->ftd_ctu_buf);
			}
			break;
		case ID_FTC_BUTTON_9:
			ftc_set_data->ftd_csl= set_ftc_set_value2(ftc_set_data->ftd_csl, flag);

			vis = d_frame_get_control(frm, ID_FTC_LABEL_9);
			{
				sprintf(ftc_set_data->ftd_csl_buf, "%d", ftc_set_data->ftd_csl);
				d_label_set_text(vis, ftc_set_data->ftd_csl_buf);
			}
			break;
		case ID_FTC_BUTTON_10:
			ftc_set_data->ftd_csu = set_ftc_set_value2(ftc_set_data->ftd_csu, flag);

			vis = d_frame_get_control(frm, ID_FTC_LABEL_10);
			{
				sprintf(ftc_set_data->ftd_csu_buf, "%d", ftc_set_data->ftd_csu);
				d_label_set_text(vis, ftc_set_data->ftd_csu_buf);
			}
			break;
		case ID_FTC_BUTTON_13:
			ftc_set_data->ftc_hcy = set_ftc_set_value2(ftc_set_data->ftc_hcy, flag);

			vis = d_frame_get_control(frm, ID_FTC_LABEL_13);
			{
				sprintf(ftc_set_data->ftc_hcy_buf, "%d", ftc_set_data->ftc_hcy);
				d_label_set_text(vis, ftc_set_data->ftc_hcy_buf);
			}
			break;
		case ID_FTC_BUTTON_14:
			ftc_set_data->ftc_hcr = set_ftc_set_value2(ftc_set_data->ftc_hcr, flag);

			vis = d_frame_get_control(frm, ID_FTC_LABEL_14);
			{
				sprintf(ftc_set_data->ftc_hcr_buf, "%d", ftc_set_data->ftc_hcr);
				d_label_set_text(vis, ftc_set_data->ftc_hcr_buf);
			}
			break;
		case ID_FTC_BUTTON_11:
			ftc_set_data->ftc_hgy = set_ftc_set_value1(ftc_set_data->ftc_hgy, flag);

			vis = d_frame_get_control(frm, ID_FTC_LABEL_11);
			{
				sprintf(ftc_set_data->ftc_hgy_buf, "%d", ftc_set_data->ftc_hgy);
				d_label_set_text(vis, ftc_set_data->ftc_hgy_buf);
			}
			break;
		case ID_FTC_BUTTON_12:
			ftc_set_data->ftc_hgr = set_ftc_set_value1(ftc_set_data->ftc_hgr, flag);

			vis = d_frame_get_control(frm, ID_FTC_LABEL_12);
			{
				sprintf(ftc_set_data->ftc_hgr_buf, "%d", ftc_set_data->ftc_hgr);
				d_label_set_text(vis, ftc_set_data->ftc_hgr_buf);
			}
			break;
		default:
			break;
	}

	set_param_of_ftc();

	return D_OK;
}

static D_Result
ftc_on_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_FTC_LABEL_1);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ftc_set_data(id, D_TRUE);
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
ftc_adj_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_FTC_LABEL_2);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ftc_set_data(id, D_TRUE);
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
ftd_htl_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_FTC_LABEL_3);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ftc_set_data(id, D_TRUE);
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
ftd_htu_set_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_FTC_LABEL_4);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ftc_set_data(id, D_TRUE);
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
ftd_hsl_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_FTC_LABEL_5);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ftc_set_data(id, D_TRUE);
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
ftd_hsu_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_FTC_LABEL_6);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ftc_set_data(id, D_TRUE);
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
ftd_ctl_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_FTC_LABEL_7);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ftc_set_data(id, D_TRUE);
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
ftd_ctu_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_FTC_LABEL_8);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ftc_set_data(id, D_TRUE);
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
ftd_csl_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_FTC_LABEL_9);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ftc_set_data(id, D_TRUE);
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
ftd_csu_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_FTC_LABEL_10);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ftc_set_data(id, D_TRUE);
			break;
		case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}static D_Result
ftc_hcy_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_FTC_LABEL_13);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ftc_set_data(id, D_TRUE);
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
ftc_hcr_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_FTC_LABEL_14);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ftc_set_data(id, D_TRUE);
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
ftc_hgy_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_FTC_LABEL_11);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ftc_set_data(id, D_TRUE);
			break;
		case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}static D_Result
ftc_hgr_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_FTC_LABEL_12);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_PRESSED:
			set_ftc_set_data(id, D_TRUE);
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
get_set_of_ftc_set(void) D_FUNCPOSTFIT
{
	if(ftc_set_data->hdflag)
    {
        p_tvconf_get_hdftc_set_param(&ftc_set_data->param, p_vip_get_dbinput(ftc_set_data->input));
    }
    else
    {
        p_tvconf_get_ftc_set_param(&ftc_set_data->param, p_vip_get_dbinput(ftc_set_data->input));
    }
	ftc_set_data->ftc_adj= ftc_set_data->param.ftc_adj;
	ftc_set_data->ftd_htl= ftc_set_data->param.ftd_htl;
	ftc_set_data->ftd_htu= ftc_set_data->param.ftd_htu;
	ftc_set_data->ftd_hsl= ftc_set_data->param.ftd_hsl;
	ftc_set_data->ftd_hsu= ftc_set_data->param.ftd_hsu;
	ftc_set_data->ftd_ctl= ftc_set_data->param.ftd_ctl;
	ftc_set_data->ftd_ctu= ftc_set_data->param.ftd_ctu;
	ftc_set_data->ftd_csl= ftc_set_data->param.ftd_csl;
	ftc_set_data->ftd_csu= ftc_set_data->param.ftd_csu;
	ftc_set_data->ftc_hcy= ftc_set_data->param.ftc_hcy;
	ftc_set_data->ftc_hcr= ftc_set_data->param.ftc_hcr;
	ftc_set_data->ftc_hgy= ftc_set_data->param.ftc_hgy;
	ftc_set_data->ftc_hgr= ftc_set_data->param.ftc_hgr;
	ftc_set_data->ftc_on= ftc_set_data->param.ftc_on;
	
	
	sprintf(ftc_set_data->ftc_adj_buf, "%d", ftc_set_data->ftc_adj);
	sprintf(ftc_set_data->ftd_htl_buf, "%d", ftc_set_data->ftd_htl);
	sprintf(ftc_set_data->ftd_htu_buf, "%d", ftc_set_data->ftd_htu);
	sprintf(ftc_set_data->ftd_hsl_buf, "%d", ftc_set_data->ftd_hsl);
	sprintf(ftc_set_data->ftd_hsu_buf, "%d", ftc_set_data->ftd_hsu);
	sprintf(ftc_set_data->ftd_ctl_buf, "%d", ftc_set_data->ftd_ctl);
	sprintf(ftc_set_data->ftd_ctu_buf, "%d", ftc_set_data->ftd_ctu);
	sprintf(ftc_set_data->ftd_csl_buf, "%d", ftc_set_data->ftd_csl);
	sprintf(ftc_set_data->ftd_csu_buf, "%d", ftc_set_data->ftd_csu);
	sprintf(ftc_set_data->ftc_hgy_buf, "%d", ftc_set_data->ftc_hgy);
	sprintf(ftc_set_data->ftc_hgr_buf, "%d", ftc_set_data->ftc_hgr);
	sprintf(ftc_set_data->ftc_hcy_buf, "%d", ftc_set_data->ftc_hcy);
	sprintf(ftc_set_data->ftc_hcr_buf, "%d", ftc_set_data->ftc_hcr);
	
	return D_OK;
}

static D_Result
ftc_set_vis_set(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &ftc_set_window;
    D_Visual *vis;

	vis = d_frame_get_control(frm, ID_FTC_LABEL_FTC);
	d_label_set_text(vis, "FTC");
	
	vis = d_frame_get_control(frm, ID_FTC_BUTTON_1);
	d_label_set_text(vis, "Ftc On");
	d_vis_set_handler(vis, ftc_on_set_handler);
	
	vis = d_frame_get_control(frm, ID_FTC_BUTTON_2);
	d_label_set_text(vis, "Ftc Adj");
	d_vis_set_handler(vis, ftc_adj_set_handler);

	vis = d_frame_get_control(frm, ID_FTC_BUTTON_3);
	d_label_set_text(vis, "Ftc Htl");
	d_vis_set_handler(vis, ftd_htl_set_handler);
	
	vis = d_frame_get_control(frm, ID_FTC_BUTTON_4);
	d_label_set_text(vis, "Ftc Htu");
	d_vis_set_handler(vis, ftd_htu_set_handler);

	vis = d_frame_get_control(frm, ID_FTC_BUTTON_5);
	d_label_set_text(vis, "Ftc Hsl");
	d_vis_set_handler(vis, ftd_hsl_handler);

	vis = d_frame_get_control(frm, ID_FTC_BUTTON_6);
	d_label_set_text(vis, "Ftc Hsu");
	d_vis_set_handler(vis, ftd_hsu_handler);

	vis = d_frame_get_control(frm, ID_FTC_BUTTON_7);
	d_label_set_text(vis, "Ftc Ctl");
	d_vis_set_handler(vis, ftd_ctl_handler);

	vis = d_frame_get_control(frm, ID_FTC_BUTTON_8);
	d_label_set_text(vis, "Ftc Ctu");
	d_vis_set_handler(vis, ftd_ctu_handler);

	vis = d_frame_get_control(frm, ID_FTC_BUTTON_9);
	d_label_set_text(vis, "Ftc Csl");
	d_vis_set_handler(vis, ftd_csl_handler);

	vis = d_frame_get_control(frm, ID_FTC_BUTTON_10);
	d_label_set_text(vis, "Ftc Csu");
	d_vis_set_handler(vis, ftd_csu_handler);

	vis = d_frame_get_control(frm, ID_FTC_BUTTON_11);
	d_label_set_text(vis, "Ftc Hgy");
	d_vis_set_handler(vis, ftc_hgy_handler);
	
	vis = d_frame_get_control(frm, ID_FTC_BUTTON_12);
	d_label_set_text(vis, "Ftc Hgr");
	d_vis_set_handler(vis, ftc_hgr_handler);

	vis = d_frame_get_control(frm, ID_FTC_BUTTON_13);
	d_label_set_text(vis, "Ftc Hcy");
	d_vis_set_handler(vis, ftc_hcy_handler);
	
	vis = d_frame_get_control(frm, ID_FTC_BUTTON_14);
	d_label_set_text(vis, "Ftc Hcr");
	d_vis_set_handler(vis, ftc_hcr_handler);

	vis = d_frame_get_control(frm, ID_FTC_LABEL_1);
	vis_switch_init(ftc_set_data->ftc_on, vis);
	
	vis = d_frame_get_control(frm, ID_FTC_LABEL_2);
	d_label_set_text(vis, ftc_set_data->ftc_adj_buf);
	
	vis = d_frame_get_control(frm, ID_FTC_LABEL_3);
	d_label_set_text(vis, ftc_set_data->ftd_htl_buf);

	vis = d_frame_get_control(frm, ID_FTC_LABEL_4);
	d_label_set_text(vis, ftc_set_data->ftd_htu_buf);

	vis = d_frame_get_control(frm, ID_FTC_LABEL_5);
	d_label_set_text(vis, ftc_set_data->ftd_hsl_buf);

	vis = d_frame_get_control(frm, ID_FTC_LABEL_6);
	d_label_set_text(vis, ftc_set_data->ftd_hsu_buf);

	vis = d_frame_get_control(frm, ID_FTC_LABEL_7);
	d_label_set_text(vis, ftc_set_data->ftd_ctl_buf);

	vis = d_frame_get_control(frm, ID_FTC_LABEL_8);
	d_label_set_text(vis, ftc_set_data->ftd_ctu_buf);

	vis = d_frame_get_control(frm, ID_FTC_LABEL_9);
	d_label_set_text(vis, ftc_set_data->ftd_csl_buf);

	vis = d_frame_get_control(frm, ID_FTC_LABEL_10);
	d_label_set_text(vis, ftc_set_data->ftd_csu_buf);

	vis = d_frame_get_control(frm, ID_FTC_LABEL_11);
	d_label_set_text(vis, ftc_set_data->ftc_hgy_buf);

	vis = d_frame_get_control(frm, ID_FTC_LABEL_12);
	d_label_set_text(vis, ftc_set_data->ftc_hgr_buf);

	vis = d_frame_get_control(frm, ID_FTC_LABEL_13);
	d_label_set_text(vis, ftc_set_data->ftc_hcy_buf);

	vis = d_frame_get_control(frm, ID_FTC_LABEL_14);
	d_label_set_text(vis, ftc_set_data->ftc_hcr_buf);

	return D_OK;
}


static D_Result
ftc_set_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{	
	D_Visual *fv;
	D_Frame *frm = &ftc_set_window;
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
					set_ftc_set_data(id, D_TRUE);
					break;
				case D_KEY_LEFT:
				case D_KEY_PNL_L:
					set_ftc_set_data(id, D_FALSE);
					break;
				case D_KEY_MENU:
					return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
			save_param_of_ftc();
			 if(ftc_set_data)
            {
                PROJECT_FREE(ftc_set_data);
                ftc_set_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
ftc_set_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

	ftc_set_data = (D_FtcSetDate*)PROJECT_ALLOC(sizeof(D_FtcSetDate));
    if(!ftc_set_data)
    {
        return D_ERR;
    }
	memset(ftc_set_data, 0, sizeof(D_FtcSetDate));
	ftc_set_data->input = p_conf_get_vid_input();
	if(ftc_set_data->input == D_VID_IUTPUT_AV1 || ftc_set_data->input == D_VID_IUTPUT_AV2|| ftc_set_data->input == D_VID_IUTPUT_TV)
	{
		ftc_set_data->hdflag = p_vip_get_ntscflag();
	}
	else
	{
		ftc_set_data->hdflag = p_vip_get_hdflag();
	}
	get_set_of_ftc_set();
	ftc_set_vis_set();
	
	vis = d_frame_get_control(frm, ID_FTC_GROUP);
	if(vis)
	{
		d_group_set_focus_loop(vis, D_TRUE);
		d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
	}

	vis = d_frame_get_control(frm, 0);
	if(vis)
	{
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
		d_vis_set_handler(vis, ftc_set_window_handler);
	}

    return D_OK;
}

/** @brief 	FTC菜单*/
D_Result
p_atv_ftc_set_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&ftc_set_window, D_TRUE);
}
