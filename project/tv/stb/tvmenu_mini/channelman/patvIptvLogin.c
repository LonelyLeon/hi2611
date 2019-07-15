#ifdef D_TV_SUPPORT_IPTV  

#include <stdio.h>
#include <string.h>
#include "pMem.h"
#include "dDebug.h"
#include "dDate.h"
#include "dDBase.h"
#include "dFP.h"
#include "pConfig.h"
#include "dFrame.h"
#include "dGUI.h"
#include "pStbAtvMenus.h"
#include "dadporting.h"
#include "patvGuiResource.h"
#include "pPlayer.h"
#include "iptv_login_window.c"
#include "auth.h"

static activated_flag = 1; // 1: activated 0: unactivated 2: activated but unconnect

extern volatile int status_running;
extern D_TaskAttr	taskAttr;
extern D_HTask		iptvHandle;

extern void * iptv_run(void *d);

static void SetActivatedFlag( D_U8 flag )
{
	activated_flag = flag;
}

/** @breif 显示窗口*/
D_Result
p_atv_iptv_login_show (D_ID flag) D_FUNCPOSTFIT
{
	int count = 0;

	if(flag == 0) // if the activite is not success
	{
		SetActivatedFlag(0);
		d_gui_enter_menu (&iptv_login_window, D_TRUE);
		return D_OK;
	}
	// start the iptv failure
	if(flag == 1)
	{
		SetActivatedFlag(2);
		d_gui_enter_menu (&iptv_login_window, D_TRUE);
		return D_OK;
	}
	
	// show the iptvlist menu	
	SetActivatedFlag(1);
	p_atv_tv_iptv_list_show();
	
	return D_OK;
}

/** @brief 事件处理*/
static D_Result
iptv_login_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &iptv_login_window;
 	char * inputChar;
	Authenticator * auth;

    switch (evt->type)
    {
        case D_EVT_FP:
			D_ERROR ( "evt->fp.key is %d\n",  evt->fp.key);
			switch (evt->fp.key)
			{
				case D_KEY_OK:
				case D_KEY_PNL_OK:
					vis = d_frame_get_control (&iptv_login_window, D_FRAMECONTROL_INPUT);
					inputChar = d_input_box_get_text(vis);
					D_ERROR("the input char is %s\n",  inputChar);

					auth = OTT_get_default_auth();
					if(auth->status == REGISTER_SUCESS_READY_FOR_LOGIN)
					{
						OTT_start_login();
						
						if(iptvHandle != D_INVALID_HANDLE)
						{
							status_running = 0;
							d_task_wait(300);
							//d_task_kill(iptvHandle);
							d_task_join(iptvHandle);
							iptvHandle = D_INVALID_HANDLE;
						}
						status_running = 1;
						iptvHandle= d_task_create(&taskAttr, (D_TaskEntry)iptv_run, NULL);
					}
					else
					{
						OTT_start_register(inputChar);

						d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_3,
								D_GUI_LAYER_MESSAGE,
								D_POP_MSG_MSG,   "", "registering...",
								0, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);

						if(iptvHandle != D_INVALID_HANDLE)
						{
							status_running = 0;
							d_task_wait(300);
							//d_task_kill(iptvHandle);
							d_task_join(iptvHandle);
							iptvHandle = D_INVALID_HANDLE;
						}
						status_running = 1;
						iptvHandle= d_task_create(&taskAttr, (D_TaskEntry)iptv_run, NULL);
					}
					
					return D_OK;
					break;

				case D_KEY_HOME:
				case D_KEY_BACK:
					MSG("login in exit!\n");
					extern D_Result endIptv_callback(D_Bool sel, D_U32 param)D_FUNCPOSTFIT;
					endIptv_callback(1, 1);

					return D_OK;
				case D_KEY_SOURCE:
				case D_KEY_PNL_SOURCE:
	//				p_atv_signal_select_show();
					break;

				default:
					return D_OK;
					break;
			}
			break;
	      case D_EVT_USER:
			if( evt->user.param1 == USER_MSG_PARAM1_IPTV_LOGLABLE )
			{
				d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_3);
				iptv_register_info_show(&iptv_login_window, (D_Char*)(evt->user.param2));
			}
			break;		
		case D_EVT_DESTROY:
			d_vis_unsubscribe_evt (vis);
			break;
		
		default:
			break;
    }

    return D_ERR;
}

D_Result
iptv_register_info_show(D_Frame *frm, char * message) D_FUNCPOSTFIT
{
	D_Visual        *vis;
	
	vis = d_frame_get_control (frm, D_FRAMECONTROL_ACTIVE);
	
	MSG("message: %s\n", message);

	if(vis)
	{
		d_label_set_text(vis, message);
	}

	MSG("\n");	
	d_vis_update(vis, NULL);
	MSG("\n");	
}


D_Result
iptv_login_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
	D_Visual        *vis;
	vis = d_frame_get_control (frm, 0);
	if (vis)
	{
		/*设定窗口事件回调*/
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
		d_vis_subscribe_evt (vis, D_EVT_USER_MASK , D_INVALID_HANDLE);
		d_vis_set_handler (vis, iptv_login_window_handler);
	}
	
	vis = d_frame_get_control (frm, D_FRAMECONTROL_INPUT);
	if (vis)
	{
		d_vis_set_focus(vis);
		d_input_box_set_text(vis, "000000000000", 12);
	}
	
	vis = d_frame_get_control (frm, D_FRAMELABEL_TIP);
	if (vis)
	{
		d_label_set_text(vis, "Active Code:");
	}
	
	vis = d_frame_get_control (frm, D_FRAMECONTROL_ACTIVE);
	if (vis)
	{
		d_label_set_text(vis, "Activate");
	}
}

#endif
