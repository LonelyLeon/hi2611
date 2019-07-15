#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "pConfig.h"
#include "dFEnd.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "dtv_scan_config_window.c"

#define BUF_LINE 4
#define MSG_BUFFER_LEN		(256)
#define BUFFER_LEN 				(6)
#define MODE_MAX_CNT		 	(8)

#define MAX_SEARCH_FREQ	(874)
#define MIN_SEARCH_FREQ	(47)

#define LABEL_BUFF_SIZE		(16)

#define INIT_START_FREQ		(47)
#define INIT_END_FREQ		(874)
#define INIT_BAND			(8)

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus={{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal={{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
	
    D_FEndParam	fendparam;						/**< 频点信息*/
	D_FEndType	fendtype;						/**< 前端类型*/	
	
	D_Char		freq_value[BUFFER_LEN];			/**< 频率标签显示数据*/
	D_Char		freq_baud[BUFFER_LEN];		/**< 符号率显示数据*/
	D_Char		*mode_content[MODE_MAX_CNT];
	
	D_U8		strength;						/**< 信号强度*/
	D_U8		quanlity;							/**< 信号质量*/	
	D_U8		mode_cnt;

	D_Bool		standard_freq_list_flag;					/*是否按标准频率表*/

	D_FEndFreq	start_freq;
	D_Char		start_freq_lab[LABEL_BUFF_SIZE];			/**< 频率标签显示数据*/

	D_FEndFreq	end_freq;
	D_Char		end_freq_lab[LABEL_BUFF_SIZE];			/**< 频率标签显示数据*/
	
	D_FEndBandWitch bandwitch;
	D_Char		bandwitch_lab[LABEL_BUFF_SIZE];			/**< 带宽显示数据*/
	
	D_Char		msg[MSG_BUFFER_LEN];				/**< 显示信息存储区*/
	D_U8		signal_val;
	D_Bool 		flag;
}D_DtvScanConfigDate;

typedef struct
{
	D_FEndMod mode;
	D_Char strmode[BUFFER_LEN];	
}D_Mode;

static D_Mode fendMode[] =
{
//  {D_FEND_QAM16, "QAM16"},
//  {D_FEND_QAM32, "QAM32"},
    {D_FEND_QAM64, "QAM64"},
    {D_FEND_QAM128, "QAM128"},
    {D_FEND_QAM256, "QAM256"},
};


static D_DtvScanConfigDate *dtv_scan_config_data;


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
set_vis_enable(D_Bool flag) D_FUNCPOSTFIT
{
	D_Frame *frm = &dtv_scan_config_window;
	D_Visual	*vis;

	vis = d_frame_get_control (frm, ID_CONFIG_GROUP_5);
	if (vis) 
	{
		d_vis_enable(vis, flag);
	}
	vis = d_frame_get_control (frm, ID_CONFIG_GROUP_4);
	if (vis) 
	{
		d_vis_enable(vis, flag);
	}

	vis = d_frame_get_control (frm, ID_CONFIG_SELECT_MODULATION);
	if (vis) 
	{
		d_vis_show(vis, flag);
		d_vis_set_focusable(vis, flag);
	}

	vis = d_frame_get_control (frm, ID_CONFIG_LABEL_MODULATION);
	if (vis) 
	{
		d_vis_show(vis, flag);
		if(flag)
			d_label_set_text(vis, d_gui_get_text(atv_IDS_MODULATION));
	}

	vis = d_frame_get_control (frm, ID_CONFIG_INPUT_SYMBOL_RATE);
	if (vis) 
	{
		d_vis_show(vis, flag);
		d_vis_set_focusable(vis, flag);
	}

	vis = d_frame_get_control (frm, ID_CONFIG_LABEL_SYMBOL_RATE);
	if (vis) 
	{
		d_vis_show(vis, flag);
		if(flag)
			d_label_set_text(vis, d_gui_get_text(atv_IDS_SYMBOL_RATE));
	}
	
}

static D_Result
save_config_param(void)D_FUNCPOSTFIT
{
	D_Frame *frm = &dtv_scan_config_window;
	D_Visual	*vis;
	D_U32 val;
	D_SIParam si_param;
	
	vis = d_frame_get_control (frm, ID_CONFIG_INPUT_FREQ);
	if (vis) 
	{
		val = (D_U32)d_input_box_get_num(vis);
		dtv_scan_config_data->fendparam.freq = (D_FEndFreq)val;
	}
	vis = d_frame_get_control (frm, ID_CONFIG_INPUT_SYMBOL_RATE);
	if (vis) 
	{
		val = (D_U32)d_input_box_get_num(vis);
		dtv_scan_config_data->fendparam.dvbc.baud = (D_FEndBaud)val;
	}
	vis = d_frame_get_control (frm, ID_CONFIG_SELECT_MODULATION);
	if (vis) 
	{
		val = (D_U32)((D_U16)d_select_box_get_val(vis));
		dtv_scan_config_data->fendparam.dvbc.mod = fendMode[val].mode;
	}
	p_conf_get_si_param (&si_param);	
	si_param.main.freq=dtv_scan_config_data->fendparam.dvbc.freq;
	si_param.main.baud=dtv_scan_config_data->fendparam.dvbc.baud;
	si_param.main.mod=dtv_scan_config_data->fendparam.dvbc.mod;	
	p_conf_set_si_param(&si_param);

	return D_OK;
}

static D_Result
save_fullscan_config_param(void)D_FUNCPOSTFIT
{
	D_Frame *frm = &dtv_scan_config_window;
	D_Visual	*vis;
	D_U32 val;
	D_FULLSCAN_CONFIG fullscan_config;
	
	vis = d_frame_get_control (frm, ID_CONFIG_INPUT_START_FREQ);
	if (vis) 
	{
		val = (D_U32)d_input_box_get_num(vis);
		dtv_scan_config_data->start_freq = (D_FEndFreq)val;
	}
	vis = d_frame_get_control (frm, ID_CONFIG_INPUT_END_FREQ);
	if (vis) 
	{
		val = (D_U32)d_input_box_get_num(vis);
		dtv_scan_config_data->end_freq = (D_FEndBaud)val;
	}
	vis = d_frame_get_control (frm, ID_CONFIG_SELECT_WITH_ROLE);
	if (vis) 
	{
		val = d_select_box_get_val(vis);
		if(val == 1)
			dtv_scan_config_data->standard_freq_list_flag = D_TRUE;
		else
			dtv_scan_config_data->standard_freq_list_flag = D_FALSE;
			
	}

	vis = d_frame_get_control (frm, ID_CONFIG_INPUT_BANDWIDTH);
	if (vis) 
	{
		val = (D_U16)d_input_box_get_num(vis);
		dtv_scan_config_data->bandwitch = val;
	}
	
	p_tvconf_get_fullscan_config(&fullscan_config);
	fullscan_config.standard_freq_list_flag = dtv_scan_config_data->standard_freq_list_flag;
	fullscan_config.start_freq= dtv_scan_config_data->start_freq;
	fullscan_config.end_freq= dtv_scan_config_data->end_freq;
	fullscan_config.bandwitch= dtv_scan_config_data->bandwitch;
	p_tvconf_set_fullscan_config(&fullscan_config);

	return D_OK;
}



static D_Result
freq_info_init(void)
{
	D_Frame *frm = &dtv_scan_config_window;
	D_Visual	*vis;
	D_U16 val;
	D_SIParam si_param;
	D_U8 select_val;

	select_val = p_conf_get_scan_config();
	
	p_conf_get_si_param (&si_param);
	dtv_scan_config_data->fendparam.dvbc.freq=si_param.main.freq;
	dtv_scan_config_data->fendparam.dvbc.baud=si_param.main.baud;
	dtv_scan_config_data->fendparam.dvbc.mod=si_param.main.mod;

	vis = d_frame_get_control (frm, ID_CONFIG_INPUT_FREQ);
	if (vis) 
	{
		sprintf(dtv_scan_config_data->freq_value, "%03d", dtv_scan_config_data->fendparam.dvbc.freq);
		d_input_box_set_text(vis, dtv_scan_config_data->freq_value, strlen(dtv_scan_config_data->freq_value));
	}
	vis = d_frame_get_control (frm, ID_CONFIG_INPUT_SYMBOL_RATE);
	if (vis) 
	{
		sprintf(dtv_scan_config_data->freq_baud, "%04d", dtv_scan_config_data->fendparam.dvbc.baud);
		d_input_box_set_text(vis, dtv_scan_config_data->freq_baud, strlen(dtv_scan_config_data->freq_baud));
	}

	if(select_val == 1)
	{
		
		set_vis_enable(D_TRUE);
		vis = d_frame_get_control (frm, ID_CONFIG_SELECT_MODULATION);
		if (vis) 
		{
			for(val = 0; val < dtv_scan_config_data->mode_cnt; val++)
			{
				if(dtv_scan_config_data->fendparam.dvbc.mod == fendMode[val].mode)
				{
					d_select_box_set_val(vis, val);
					break;
				}
			}
		}
	}
	else
	{
		set_vis_enable(D_FALSE);
	}
	
	return D_OK;
}

static D_Result
signal_select_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &dtv_scan_config_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CONFIG_LABEL_SIGNAL);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		 case D_EVT_SELECTED:
            dtv_scan_config_data->signal_val = d_select_box_get_val(vis);
			p_conf_set_scan_config(dtv_scan_config_data->signal_val);
			freq_info_init();
		case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
freq_input_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &dtv_scan_config_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CONFIG_LABEL_FREQ);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break; 
		case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
		case D_EVT_DATA_CHANGED:
			save_config_param();
			break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
modulation_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &dtv_scan_config_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CONFIG_LABEL_MODULATION);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
			
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_SELECTED:
			save_config_param();
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
symbol_rate_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &dtv_scan_config_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CONFIG_LABEL_SYMBOL_RATE);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_DATA_CHANGED:
			save_config_param();
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
with_role_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &dtv_scan_config_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CONFIG_LABEL_WITH_ROLE);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
			dtv_scan_config_data->flag = D_TRUE;
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_SELECTED:
			if(dtv_scan_config_data->flag)
			{
				save_fullscan_config_param();
			}
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
start_freq_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &dtv_scan_config_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CONFIG_LABEL_START_FREQ);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
			dtv_scan_config_data->flag = D_TRUE;
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_DATA_CHANGED:
			if(dtv_scan_config_data->flag)
			{
				save_fullscan_config_param();
			}
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
end_freq_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &dtv_scan_config_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CONFIG_LABEL_END_FREQ);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
			dtv_scan_config_data->flag = D_TRUE;
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_DATA_CHANGED:
			if(dtv_scan_config_data->flag)
			{
				save_fullscan_config_param();
			}
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
bandwidth_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Frame *frm = &dtv_scan_config_window;
    D_Visual *vis_label;
	D_ID id;

	id = d_frame_get_control_id(frm,vis);
	vis_label = d_frame_get_control(frm, ID_CONFIG_LABEL_BANDWIDTH);
	
	switch (evt->type)
    {
        case D_EVT_ENTER:
			dtv_scan_config_data->flag = D_TRUE;
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
		case D_EVT_DATA_CHANGED:
			if(dtv_scan_config_data->flag)
			{
				save_fullscan_config_param();
			}
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
scan_config_vis_set(void) D_FUNCPOSTFIT
{
	D_Frame *frm = &dtv_scan_config_window;
    D_Visual *vis;

	vis = d_frame_get_control(frm, ID_CONFIG_SELECT_SIGNAL);
	d_vis_set_handler(vis, signal_select_handler);
	d_select_box_set_val(vis, dtv_scan_config_data->signal_val);

	vis = d_frame_get_control(frm, ID_CONFIG_INPUT_FREQ);
	d_vis_set_handler(vis, freq_input_handler);
	
	vis = d_frame_get_control(frm, ID_CONFIG_SELECT_MODULATION);
	d_vis_set_handler(vis, modulation_handler);
	d_select_box_set_content(vis, dtv_scan_config_data->mode_content, dtv_scan_config_data->mode_cnt);

	vis = d_frame_get_control(frm, ID_CONFIG_INPUT_SYMBOL_RATE);
	d_vis_set_handler(vis, symbol_rate_handler);
	vis = d_frame_get_control(frm, ID_CONFIG_SELECT_WITH_ROLE);
	d_vis_set_handler(vis, with_role_handler);
	vis = d_frame_get_control(frm, ID_CONFIG_INPUT_START_FREQ);
	d_vis_set_handler(vis, start_freq_handler);

	vis = d_frame_get_control(frm, ID_CONFIG_INPUT_END_FREQ);
	d_vis_set_handler(vis, end_freq_handler);
	vis = d_frame_get_control(frm, ID_CONFIG_INPUT_BANDWIDTH);
	d_vis_set_handler(vis, bandwidth_handler);

	vis = d_frame_get_control(frm, ID_CONFIG_LABEL_SIGNAL);
	d_label_set_text(vis, d_gui_get_text(atv_IDS_AV_SIGNAL_SELECT));
	vis = d_frame_get_control(frm, ID_CONFIG_LABEL_FREQ);
	d_label_set_text(vis, d_gui_get_text(atv_IDS_FREQ));
	vis = d_frame_get_control(frm, ID_CONFIG_LABEL_MODULATION);
	d_label_set_text(vis, d_gui_get_text(atv_IDS_MODULATION));

	vis = d_frame_get_control(frm, ID_CONFIG_LABEL_SYMBOL_RATE);
	d_label_set_text(vis, d_gui_get_text(atv_IDS_SYMBOL_RATE));
	vis = d_frame_get_control(frm, ID_CONFIG_LABEL_WITH_ROLE);
	d_label_set_text(vis, d_gui_get_text(atv_IDS_BY_ROLE));
	vis = d_frame_get_control(frm, ID_CONFIG_LABEL_START_FREQ);
	d_label_set_text(vis, d_gui_get_text(atv_IDS_START_FREQ));

	vis = d_frame_get_control(frm, ID_CONFIG_LABEL_END_FREQ);
	d_label_set_text(vis, d_gui_get_text(atv_IDS_END_FREQ));
	vis = d_frame_get_control(frm, ID_CONFIG_LABEL_BANDWIDTH);
	d_label_set_text(vis, d_gui_get_text(atv_IDS_BANDWIDTH));
	
	return D_OK;
}

static D_Result
dtv_scan_config_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &dtv_scan_config_window;
    D_ID id;

    id = get_focus_control_id(frm);

    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
					if(dtv_scan_config_data->bandwitch == 0 || dtv_scan_config_data->end_freq < dtv_scan_config_data->start_freq 
						|| dtv_scan_config_data->start_freq < INIT_START_FREQ || dtv_scan_config_data->end_freq > INIT_END_FREQ)
					{
						sprintf(dtv_scan_config_data->msg, d_gui_get_text(atv_IDS_CONFIG_ERROR), INIT_START_FREQ, INIT_END_FREQ);
						d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, 
										NULL, dtv_scan_config_data->msg, 4000, D_POP_MSG_RESPONSE_ANY, 
										D_FALSE, NULL, 0);
										
					}
					else
					{
						 return d_gui_clear_menu();
					}
					break;
                case D_KEY_RIGHT:

                case D_KEY_PNL_R:

               //     set_dtv_scan_config_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
               //     set_dtv_scan_config_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
					if(dtv_scan_config_data->bandwitch == 0 || dtv_scan_config_data->end_freq < dtv_scan_config_data->start_freq 
						|| dtv_scan_config_data->start_freq < INIT_START_FREQ || dtv_scan_config_data->end_freq > INIT_END_FREQ)
					{
						sprintf(dtv_scan_config_data->msg, d_gui_get_text(atv_IDS_CONFIG_ERROR), INIT_START_FREQ, INIT_END_FREQ);
						d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_2, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, 
										NULL, dtv_scan_config_data->msg, 4000, D_POP_MSG_RESPONSE_ANY, 
										D_FALSE, NULL, 0);
										
					}
					else
					{
						 return d_gui_clear_menu();
					}
					break;
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
        //    save_param_of_tv_scan_config();
            if(dtv_scan_config_data)
            {
                PROJECT_FREE(dtv_scan_config_data);
                dtv_scan_config_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
dtv_scan_config_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;
	D_U8 	idx;
	D_FULLSCAN_CONFIG fullscan_config;

	dtv_scan_config_data = (D_DtvScanConfigDate*)PROJECT_ALLOC(sizeof(D_DtvScanConfigDate));
    if(!dtv_scan_config_data)
    {
        return D_ERR;
    }
	memset(dtv_scan_config_data, 0, sizeof(D_DtvScanConfigDate));

	dtv_scan_config_data->flag = D_FALSE;
	dtv_scan_config_data->mode_cnt = sizeof(fendMode)/sizeof(fendMode[0]);
	for(idx = 0; idx < dtv_scan_config_data->mode_cnt; idx++)
	{
		dtv_scan_config_data->mode_content[idx] = fendMode[idx].strmode;
	}
	p_tvconf_get_fullscan_config(&fullscan_config);
	dtv_scan_config_data->standard_freq_list_flag = fullscan_config.standard_freq_list_flag;
	dtv_scan_config_data->start_freq = fullscan_config.start_freq;
	dtv_scan_config_data->end_freq = fullscan_config.end_freq;
	dtv_scan_config_data->bandwitch = fullscan_config.bandwitch;
	
	sprintf(dtv_scan_config_data->start_freq_lab, "%03d", dtv_scan_config_data->start_freq);
	sprintf(dtv_scan_config_data->end_freq_lab, "%03d", dtv_scan_config_data->end_freq);
	sprintf(dtv_scan_config_data->bandwitch_lab, "%d", dtv_scan_config_data->bandwitch);
	dtv_scan_config_data->signal_val = p_conf_get_scan_config();
	
	freq_info_init();
	scan_config_vis_set();

	vis = d_frame_get_control (frm, ID_CONFIG_SELECT_WITH_ROLE);
	if (vis) 
	{
		d_select_box_set_val(vis, (D_U16)dtv_scan_config_data->standard_freq_list_flag);
	}

	vis = d_frame_get_control (frm, ID_CONFIG_INPUT_START_FREQ);
	if(vis)
	{
		d_input_box_set_text(vis, dtv_scan_config_data->start_freq_lab, strlen(dtv_scan_config_data->start_freq_lab));
	}

	vis = d_frame_get_control (frm, ID_CONFIG_INPUT_END_FREQ);
	if(vis)
	{
		d_input_box_set_text(vis, dtv_scan_config_data->end_freq_lab, strlen(dtv_scan_config_data->end_freq_lab));
	}

	vis = d_frame_get_control (frm, ID_CONFIG_INPUT_BANDWIDTH);
	if(vis)
	{
		d_input_box_set_text(vis, dtv_scan_config_data->bandwitch_lab, strlen(dtv_scan_config_data->bandwitch_lab));
	}

	vis = d_frame_get_control(frm, ID_CONFIG_GROUP);
	if(vis)
	{
		d_group_set_focus_loop(vis, D_TRUE);
		d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
	}

	vis = d_frame_get_control(frm, 0);
	if(vis)
	{
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
		d_vis_set_handler(vis, dtv_scan_config_window_handler);
	}

    return D_OK;
}

/** @brief dtv搜索配置菜单*/
D_Result
p_atv_dtv_scan_config_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&dtv_scan_config_window, D_TRUE);
}
