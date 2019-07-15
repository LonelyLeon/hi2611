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
#include "ptvConfig.h"
#include "atv_power_off_msg_window.c"

#define CHANGE_TIME 1000

typedef struct 
{
	D_HTimer change_timer;
	D_Char msg[24];
	D_S16 value;
}D_AtvPowerOffMsg;

static D_AtvPowerOffMsg *msg = NULL;

/** @brief 事件处理*/
static D_Result
atv_power_off_msg_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_power_off_msg_window;

    switch (evt->type)
    {
        case D_EVT_FP:
            {
                D_Tv_Config_Poweron_Order   order;

                /* 任意键取消后，将定时关机设置成 off  @qiny 20150902*/
                p_tvconf_get_poweroff_order(&order);
                if(order.en)
                {
                    order.en = 0;
                    p_tvconf_set_poweroff_order(&order);
                }
			d_gui_close_frame(frm);
            }
        	return D_OK;
		case D_EVT_TIMER:
			msg->value --;
			if(msg->value == 0)
			{
#ifdef D_TV_SUPPORT_PVR
				p_atv_media_pvr_record_stop();
#endif
                d_gui_close_frame(frm);
				d_stb_stand_by();
                return D_OK;
			}
			vis = d_frame_get_control(frm, ID_MSG_LABEL_POWER_OFF);
			if(vis)
			{
				sprintf(msg->msg, "%d %s",msg->value, d_gui_get_text(atv_IDS_STAND_BY));
				d_label_set_text(vis, msg->msg);
			}
			if(msg->change_timer != D_INVALID_HANDLE)
            {
				d_timer_reset(msg->change_timer, CHANGE_TIME);
			}
			break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt(vis);
            if(msg)
            {
                if(msg->change_timer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(msg->change_timer);
					msg->change_timer = D_INVALID_HANDLE;
                }
                PROJECT_FREE(msg);
                msg = NULL;
            }				
        	break;
        default:
            break;
    }
    return D_ERR;
}


D_Result
atv_power_off_msg_window_init(D_Frame *frm)
{
    D_Visual *vis;

	msg = (D_AtvPowerOffMsg*)PROJECT_ALLOC(sizeof(D_AtvPowerOffMsg));
    if(!msg)
    {
        return D_ERR;
    }

    memset(msg, 0x00, sizeof(D_AtvPowerOffMsg));
	msg->value = 60;
	vis = d_frame_get_control(frm, ID_MSG_LABEL_POWER_OFF);
	if(vis)
	{
		sprintf(msg->msg, "%d %s",msg->value, d_gui_get_text(atv_IDS_STAND_BY));
		d_label_set_text(vis, msg->msg);
	}

	vis = d_frame_get_control(frm, D_FRAMECONTROL_2);
	if(vis)
	{
		d_label_set_text(vis, d_gui_get_text(atv_IDS_KEY_CANCEL));
	}

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
    	msg->change_timer = d_timer_create(NULL, CHANGE_TIME, d_gui_get_queue ());
		if(msg->change_timer != D_INVALID_HANDLE)
		{
			d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, msg->change_timer);
		}
		d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK | D_EVT_AUDIO_KEY_MASK | D_EVT_PROGRAM_PLUS_MINUS_KEY_MASK | D_EVT_POWER_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_power_off_msg_window_handler);
    }
    return D_OK;
}

/** @brief 显示待机提示菜单*/
D_Result
p_atv_power_off_msg_show (void) D_FUNCPOSTFIT
{
    return d_gui_open_frame(&atv_power_off_msg_window, D_GUI_LAYER_LOGO);
}

