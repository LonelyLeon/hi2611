/** @file
* @brief ѡ����Ϣ����ģ��
* @author ����
* @date 2005-9-13 ����: �����ļ�
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

/*ȡ�õ�ǰ��ѡ����*/
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

/*����Ĭ�ϵ�ѡ����*/
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

/*�л�����*/
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


/** @brief �����¼�����*/
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
			/*���ٶ�ʱ��*/
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



/*ѡ�񴰿ڳ�ʼ��*/
D_Result atv_select_box_center_window_init(D_Frame *init) D_FUNCPOSTFIT
{
	D_Visual *vis;

	curr_prio_selbox->htimer = D_INVALID_HANDLE;
	curr_prio_selbox->prompt_htimer = D_INVALID_HANDLE;
    
	vis = d_frame_get_control(init, 0);
	if(vis)
	{
		/*���ö�ʱ��*/
		if(curr_prio_selbox->timeout > 0)
		{
			curr_prio_selbox->htimer = d_timer_create(NULL, curr_prio_selbox->timeout, d_gui_get_queue());
			d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, curr_prio_selbox->htimer);
		}
		else
		{
			curr_prio_selbox->htimer = D_INVALID_HANDLE;
		}
			
		/*�趨���ڻص�*/
		d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
		d_vis_set_handler(vis, window_handler);
	}

	/*����Ĭ��ѡ���*/
	set_default_sel(curr_prio_selbox->def_sel);
	
	vis = d_frame_get_control(init, ID_MSG_LABEL);
	if(vis)
	{
		if(curr_prio_selbox->prompt == D_TRUE)
		{
			/* ע���¼��ص�*/
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

/** @brief ��ʾ�������û�ѡ�񴰿�,�û�����ѡ��ȷ�ϻ�ȡ��
* @param prio			��Ϣ������ȼ�
* @param layer			��ʾ���ڵĲ�
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣ
* @param timeout��		��������Ļ��������ʱ�䣬С�ڵ��ڣ���ʾ��Զ��ʾ,ֱ������d_pop_select_hide
						���û��ֶ�����
* @param def			D_TRUE��ʾ��ʱ����û�����ȷ��Ч����ͬ��D_FALSE��ʾ��ʱ����û�����ȡ��
						Ч����ͬ
* @param handler		ѡ����ص�����ָ��
* @param param			�����û��ص��Ĳ���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
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


/** @brief ������ʾ���û�ѡ�񴰿�
* @param prio			��Ϣ������ȼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_atv_pop_select_center_hide (D_U16 prio) D_FUNCPOSTFIT
{
	return d_pop_free (prio);
}
/*EOF*/

