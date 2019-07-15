
/*频道预置菜单*/
#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dDBase.h"
#include "pConfig.h"
#include "dFEnd.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "prog_reset_window.c"


#define	USER_MSG_HANDLE_PROG	0xFEFDFCFB
#define	USER_MSG_PARAM1_PROG_RESET	0xFEFBFCFD

static D_Char *sel_content[] = {"boe", "ctv"};
static D_U32 cur_prog_sel_cnt = sizeof(sel_content)/sizeof(sel_content[0]);
static D_U32 cur_prog_sel = 0;
static D_Visual *vis_sel = NULL, *vis_prompt = NULL;

static D_Result
prog_reset_action(D_U32 param) D_FUNCPOSTFIT
{
    p_precast_program(param);
    return D_OK;
}

static D_Result
prog_reset_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_MENU:  
                case D_KEY_PNL_MENU: 
                    return d_gui_clear_menu();
					break;
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    cur_prog_sel = (cur_prog_sel + 1) % cur_prog_sel_cnt;
                    d_select_box_set_val(vis_sel, cur_prog_sel);
                    d_label_set_text(vis_prompt, "......");
                    d_gui_update();
                    prog_reset_action(cur_prog_sel);
                    d_label_set_text(vis_prompt, "OK");
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    cur_prog_sel = (cur_prog_sel + cur_prog_sel_cnt - 1) % cur_prog_sel_cnt;
                    d_select_box_set_val(vis_sel, cur_prog_sel);
                    d_label_set_text(vis_prompt, "......");
                    d_gui_update();
                    prog_reset_action(cur_prog_sel);
                    d_label_set_text(vis_prompt, "OK");
                    break;
                default:
                    break;
            }
            return D_OK;
        case D_EVT_USER:
            if(evt->user.param1 == USER_MSG_PARAM1_PROG_RESET)
            {
                d_vis_unsubscribe_one_evt(vis, D_EVT_USER_MASK, evt->user.handle);
                prog_reset_action(cur_prog_sel);
                d_label_set_text(vis_prompt, "OK");
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
        default:
            break;
    }
    return D_ERR;
}

D_Result
prog_reset_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;
	D_UserMsg msg;
    
    vis_sel = NULL;
    vis_prompt = NULL;
    
 	vis = d_frame_get_control(frm, ID_CONFIG_SELECT_PROG);
	if(vis)
	{
	    vis_sel = vis;
	    /* 选择框不响应按键，将由窗口响应*/
		d_vis_unsubscribe_one_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_select_box_set_content(vis, sel_content, cur_prog_sel_cnt);
        d_select_box_set_val(vis, cur_prog_sel);
	}

    vis = d_frame_get_control(&prog_reset_window, ID_CONFIG_LABEL_PROMPT);
    if(vis)
    {
        vis_prompt = vis;
        d_label_set_text(vis, "......");
    }
    
	vis = d_frame_get_control(frm, 0);
	if(vis)
	{
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
		d_vis_set_handler(vis, prog_reset_window_handler);

        /* 进入菜单后预置节目*/
        msg.type = D_MSG_USER;
        msg.handle = USER_MSG_HANDLE_PROG;
        msg.param1 = USER_MSG_PARAM1_PROG_RESET;

        d_vis_subscribe_evt(vis, D_EVT_USER_MASK, msg.handle);
        d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof (msg));
	}


    return D_OK;
}

/** @brief 频道预置菜单*/
D_Result
p_atv_program_reset_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&prog_reset_window, D_TRUE);
}

