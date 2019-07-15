/** @file
* @brief 选择信息窗口模块
* @author 龚克
* @date 2005-9-13 龚克: 建立文件
*/
#include "dPop.h"
#include "dTimer.h"
#include "dDebug.h"
#include "pPopMsg.h"
#include "dControl.h"
#include "dGUI.h"
#include "pFp.h"
#include "dFrame.h"
#include <stdio.h>
#include <string.h>

#include "atv_select_box_center_window.c"

typedef struct {
	const D_Char *str_title;
	const D_Char *msg;
	D_MSec timeout;
	D_Bool def_sel;
	D_HTimer htimer;
	D_Bool prompt;
	D_HTimer prompt_htimer; /*2006-9-21 10:01*/
	D_Result (*handler) (D_Bool sel, D_U32 param) D_FUNCPOSTFIT;
	D_U32 param;
} D_SelBoxData;

static D_SelBoxData	selbox_data[D_POP_PRIO_MAX];
static D_SelBoxData *curr_prio_selbox;
static D_Char head_prompt[256];

static D_Result clear_box(D_Bool sel)
{
	D_U32 param;
	D_Result (*handler)(D_Bool sel, D_U32 param) D_FUNCPOSTFIT;
	
	param = curr_prio_selbox->param;
	handler = curr_prio_selbox->handler;
	
	d_atv_pop_select_hide((D_U16)(curr_prio_selbox - selbox_data));
	
	if(handler)
		handler(sel, param);
	
	return D_OK;
}

/*取得当前的选择项*/
static D_Bool get_curr_sel(D_Visual *vis)
{
	D_ID focus;
	D_Visual *fvis;
	D_Bool sel = D_FALSE;

	fvis = d_vis_get_focus(vis);
	if(fvis)
	{
		focus = d_frame_get_control_id(&atv_select_box_center_window, fvis);
		if(focus == ID_BUTTON_0)
		{
			sel = D_TRUE;
		}
	}	

	return sel;
}

/*设置默认的选择项*/
static D_Result set_default_sel(D_Bool def_sel)
{
	D_ID focus;
	D_Visual *vis;

	focus = (def_sel ? ID_BUTTON_0 : ID_BUTTON_1);
	vis = d_frame_get_control(&atv_select_box_center_window, focus);
	if(vis)
	{
		d_vis_set_focus(vis);
	}
	return D_OK;
}

/*切换焦点*/
static D_Result change_focus(D_Visual *vis)
{
	D_ID focus;
	D_Visual *fvis;

	fvis = d_vis_get_focus(vis);
	if(fvis)
	{
		focus = d_frame_get_control_id(&atv_select_box_center_window, fvis);
		if(focus == ID_BUTTON_0 || focus == ID_BUTTON_1)
		{
			focus = ((focus == ID_BUTTON_0) ? ID_BUTTON_1 : ID_BUTTON_0);
			fvis = d_frame_get_control(&atv_select_box_center_window, focus);
			if(fvis)
			{
				d_vis_set_focus(fvis);
			}
		}
	}
	
	return D_OK;
}


/** @brief 窗口事件处理*/
static D_Result window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	switch(evt->type)
	{
		case D_EVT_TIMER:
                    if(curr_prio_selbox->htimer == evt->timer.htimer)
                    {
			return clear_box(curr_prio_selbox->def_sel);
                    }
                    break;            
		case D_EVT_FP:
			switch(evt->fp.key)
			{
				case D_KEY_OK:					
                            case D_KEY_PNL_OK:
                case D_KEY_PNL_SOURCE:
					clear_box(get_curr_sel(vis));
					break;
				case D_KEY_BACK:
				case D_KEY_MENU:
				case D_KEY_PNL_MENU:
					clear_box(D_FALSE);
					break;	
				case D_KEY_ESC:
					clear_box(D_FALSE);
					//d_pop_select_hide((D_U16)(curr_prio_selbox - selbox_data));
					break;
				case D_KEY_LEFT:
                            case D_KEY_PNL_L:
				case D_KEY_RIGHT:
                            case D_KEY_PNL_R:                                
					change_focus(vis);
					break;
				default:
					break;
			}
			return D_OK;
		case D_EVT_DESTROY:
			/*销毁定时器*/
			if(curr_prio_selbox->htimer != D_INVALID_HANDLE)
			{
				d_timer_destroy(curr_prio_selbox->htimer);
			}
			
			if(curr_prio_selbox->prompt_htimer != D_INVALID_HANDLE)
			{
				d_timer_destroy(curr_prio_selbox->prompt_htimer);
			}
			
			d_vis_unsubscribe_evt(vis);
			break;
		default:
			break;
	}
	
	return D_ERR;
}

static D_Result prompt_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{

	switch(evt->type)
	{
		case D_EVT_TIMER:
			{
				D_Int sec = curr_prio_selbox->timeout / 1000;
				
				if(sec > 0)
				{
					snprintf(head_prompt, sizeof(head_prompt), curr_prio_selbox->msg, sec);
					curr_prio_selbox->timeout -= 1000;
					d_label_set_text(vis, head_prompt);
				}
			}
			break;
		default:
			break;	
	}
	
	return D_ERR;
}



/*选择窗口初始化*/
D_Result atv_select_box_center_window_init(D_Frame *init) D_FUNCPOSTFIT
{
	D_Visual *vis;

	curr_prio_selbox->htimer = D_INVALID_HANDLE;
	curr_prio_selbox->prompt_htimer = D_INVALID_HANDLE;
    
	vis = d_frame_get_control(init, 0);
	if(vis)
	{
		/*设置定时器*/
		if(curr_prio_selbox->timeout > 0)
		{
			curr_prio_selbox->htimer = d_timer_create(NULL, curr_prio_selbox->timeout, d_gui_get_queue());
			d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, curr_prio_selbox->htimer);
		}
		else
		{
			curr_prio_selbox->htimer = D_INVALID_HANDLE;
		}
			
		/*设定窗口回调*/
		d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
		d_vis_set_handler(vis, window_handler);
	}

	/*设置默认选项焦点*/
	set_default_sel(curr_prio_selbox->def_sel);
	
	vis = d_frame_get_control(init, ID_MSG_LABEL);
	if(vis)
	{
		if(curr_prio_selbox->prompt == D_TRUE)
		{
			/* 注册事件回调*/
			d_vis_set_handler(vis, prompt_handler);
			curr_prio_selbox->prompt_htimer = 
				d_timer_create(NULL, 1000, d_gui_get_queue());
			d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, curr_prio_selbox->prompt_htimer);
		}

		snprintf(head_prompt, sizeof(head_prompt), curr_prio_selbox->msg, curr_prio_selbox->timeout / 1000);
		d_label_set_text(vis, head_prompt);
	}

	
	return D_OK;
}

static D_Result SelBoxShow(D_U16 prio, D_GUILayer layer, D_Frame *frm)
{
	curr_prio_selbox = &selbox_data[prio];

	return D_OK;
}

/** @brief 显示机顶盒用户选择窗口,用户可以选择确认或取消
* @param prio			消息框的优先级
* @param layer			显示所在的层
* @param str_title			要显示的标题文本
* @param msg			要显示的信息
* @param timeout　		窗口在屏幕上滞留的时间，小于等于０表示永远显示,直道调用d_pop_select_hide
						或用户手动消除
* @param def			D_TRUE表示超时后和用户输入确认效果相同，D_FALSE表示超时后和用户输入取消
						效果相同
* @param handler		选择处理回调函数指针
* @param param			传给用户回调的参数
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_atv_pop_select_center_show (D_U16 prio,
		D_GUILayer layer,
		const D_Char *str_title,
		const D_Char *msg, D_MSec timeout, 
		D_Bool def, 
		D_Result (*handler) (D_Bool sel, D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT
{
	D_Result ret;
	D_SelBoxData *pop;
	
	ret = d_pop_new(prio, layer, &atv_select_box_center_window, SelBoxShow);
	if(ret != D_OK)
	{
#ifdef D_DEBUG
		D_ERROR ("Cannot load the pop up select\n");
#endif
		return D_ERR;
	}

	pop = &selbox_data[prio];

	pop->str_title = str_title;
	pop->msg = msg;
	pop->def_sel = def;
	pop->timeout = timeout;
	pop->htimer = D_INVALID_HANDLE;
	pop->handler = handler;
	pop->param = param;
	pop->prompt = D_FALSE;
	pop->prompt_htimer = D_INVALID_HANDLE;
	
	return d_pop_show (prio);
}

D_Result d_atv_pop_select_center_show_with_prompt (D_U16 prio,
		D_GUILayer layer,
		const D_Char *str_title,
		const D_Char *msg, D_MSec timeout, 
		D_Bool def, 
		D_Result (*handler) (D_Bool sel, D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT
{
	D_Result ret;
	D_SelBoxData *pop;
	
	ret = d_pop_new(prio, layer, &atv_select_box_center_window, SelBoxShow);
	if(ret != D_OK)
	{
#ifdef D_DEBUG
		D_ERROR ("Cannot load the pop up message\n");
#endif
		return D_ERR;
	}

	pop = &selbox_data[prio];
	
	pop->str_title = str_title;
	pop->msg = msg;
	pop->def_sel = def;
	pop->timeout = timeout;
	pop->htimer = D_INVALID_HANDLE;
	pop->handler = handler;
	pop->param = param;
	pop->prompt = D_TRUE;
	pop->prompt_htimer = D_INVALID_HANDLE;
	
	return d_pop_show (prio);
}


/** @brief 隐藏显示的用户选择窗口
* @param prio			消息框的优先级
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
d_atv_pop_select_center_hide (D_U16 prio) D_FUNCPOSTFIT
{
	return d_pop_free (prio);
}
/*EOF*/

