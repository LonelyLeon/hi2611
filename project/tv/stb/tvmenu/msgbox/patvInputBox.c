/** @file
* @brief 用户密码输入窗口模块
* @author 覃宜
* @date 2013-7-3覃宜: 建立文件
* @date 2016-04-20刘军鸿: 从stbmenu移植至tv
*/
#include <stdio.h>
#include <string.h>
#include "dPop.h"
#include "dTimer.h"
#include "dDebug.h"
#include "pPopMsg.h"
#include "dControl.h"
#include "dGUI.h"
#include "dFrame.h"

#include "atv_input_box_window.c"


/*最大输入长度*/
#define D_MAX_INPUT_LEN	16


/** @brief 输入框数据*/
typedef struct {
	D_PopInputType type;
	const D_Char *str_title;
	const D_Char *msg;
	D_U16	input_len;
	D_Bool	user_hide;
	D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT;
	D_U32	param;
	D_Frame *frm;
} D_InputBoxData;

static D_InputBoxData	atv_inputbox_data[D_POP_PRIO_MAX];
static D_InputBoxData *curr_prio_inputbox;
static D_Char head_prompt[128];


static D_Result
clear_box (D_Char *input) D_FUNCPOSTFIT
{
	D_U32		 param;
	D_Char	 str[D_MAX_INPUT_LEN+1];
	D_Char	*ptr;
	
	D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT;
	
	param = curr_prio_inputbox->param;
	handler = curr_prio_inputbox->handler;
	
	if (input)
	{
		strcpy (str, input);
		ptr = str;
	}
	else
	{
		ptr = NULL;
	}
	
	d_atv_pop_input_hide (curr_prio_inputbox - atv_inputbox_data);
	
	if (handler)
		handler (ptr, param);
	
	return D_OK;
}

static D_Result
input_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	switch (evt->type) 
	{
		case D_EVT_DATA_CHANGED:
			break;
		default:
			break;
	}
	
	return D_ERR;
}

/** @brief 窗口事件处理函数*/
static D_Result
atv_input_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	D_Visual	*cv;

	switch (evt->type)
	{
		/*处理按键*/
		case D_EVT_FP:
			switch (evt->fp.key) 
			{
				case D_KEY_OK:
                case D_KEY_PNL_OK:
					cv = d_frame_get_control (curr_prio_inputbox->frm, ID_INPUT_PASSWD);
					if (cv)
					{
						clear_box (d_input_box_get_text (cv));
					}
					return D_OK; 
					break;
				case D_KEY_ESC:	
				case D_KEY_BACK:	
					if(curr_prio_inputbox->type != D_POP_INPUT_POWER_ON)
					{
						if (curr_prio_inputbox->user_hide)
						{
							d_atv_pop_input_hide (curr_prio_inputbox - atv_inputbox_data);
						}						
					}
                                    break;
				case D_KEY_UP:	
				case D_KEY_DOWN:
				case D_KEY_PGUP:
				case D_KEY_PGDOWN:
                case D_KEY_PNL_U:
                case D_KEY_PNL_D:    
					if(curr_prio_inputbox->type == D_POP_INPUT_PROG_LOCK)
					{
						d_atv_pop_input_hide (curr_prio_inputbox - atv_inputbox_data);
						return D_ERR;
					}
					break;					
				default:	
					if(curr_prio_inputbox->type == D_POP_INPUT_PROG_LOCK)
					{
						return D_ERR;
					}
					break;
			}
			return D_OK;
			break;
		/*释放资源*/
		case D_EVT_DESTROY:
			d_vis_unsubscribe_evt(vis);
			return D_OK;
		default:
			break;
	}

	return D_ERR;
}

/** @brief 消息窗口初始化*/
D_Result
atv_input_box_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
	D_Visual	*vis;
	D_U32	mask;
	
	/*设置显示信息*/
	vis = d_frame_get_control(frm, ID_LABEL_TITLE);
	if(vis && curr_prio_inputbox->str_title)
	{
		d_label_set_text(vis, (D_Char*)curr_prio_inputbox->str_title);
	}
	
	vis = d_frame_get_control(frm, ID_MSG_LABEL);
	if(vis)
	{
		snprintf(head_prompt, sizeof(head_prompt), curr_prio_inputbox->msg, curr_prio_inputbox->input_len);
		d_label_set_text(vis, head_prompt);
	}

	/*设定输入框*/
	vis = d_frame_get_control (frm, ID_INPUT_PASSWD);
	if (vis) {
		d_input_box_set_len (vis, curr_prio_inputbox->input_len);
		d_vis_set_handler (vis, input_handler);
	}
	
	/*根据消息类型设定窗口标题*/
	vis = d_frame_get_control (frm, 0);
	if (vis) 
	{
		mask = D_EVT_OK_KEY_MASK;
		
		if(curr_prio_inputbox->type == D_POP_INPUT_NORMAL)
		{				
			mask |= D_EVT_ALL_KEY_MASK;
		}
		else if(curr_prio_inputbox->type == D_POP_INPUT_POWER_ON)
		{
			mask |= D_EVT_ALL_KEY_MASK;
		}
		else if(curr_prio_inputbox->type == D_POP_INPUT_PROG_LOCK)
		{
			mask |= D_EVT_OK_KEY_MASK | D_EVT_ESC_KEY_MASK | D_EVT_PG_UP_DOWN_KEY_MASK |
				D_EVT_UP_DOWN_KEY_MASK |D_EVT_KEY_MASK;
			
		}
		
		d_vis_subscribe_evt (vis, mask, D_INVALID_HANDLE);
		
		/*设定窗口事件处理*/
		d_vis_set_handler (vis, atv_input_window_handler);
	}
	
	return D_OK;
}


static D_Result InputBoxShow(D_U16 prio, D_GUILayer layer, D_Frame *frm)
{
	curr_prio_inputbox = &atv_inputbox_data[prio];

	return D_OK;
}

/** @brief 显示输入窗口(有确认与退出提示)
* @param prio			消息框的优先级
* @param layer		显示所在的层
* @param type		输入框类型
* @param str_title			要显示的标题文本
* @param msg			要显示的信息
* @param len			输入字符长度
* @param user_hide	用户是否可以手动退出
* @param handler	选择处理回调函数指针
* @param param		传给用户回调的参数
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_atv_pop_input_show (D_U16 prio,
		D_GUILayer layer,
		D_PopInputType type,
		const D_Char *str_title,
		const D_Char *msg,
		D_U16 len, D_Bool user_hide,
		D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT,
		D_U32	param) D_FUNCPOSTFIT
{
	D_Result ret;
	D_InputBoxData	*pop;

	ret = d_pop_new (prio, layer, &atv_input_box_window, InputBoxShow);
	if(ret != D_OK)
	{
#ifdef D_DEBUG
		D_ERROR ("Cannot load the pop up input\n");
#endif
		return D_ERR;
	}
	
	pop = &atv_inputbox_data[prio];
	pop->type = type;
	pop->str_title = str_title;
	pop->msg = msg;
	pop->input_len = D_MIN (len, D_MAX_INPUT_LEN);
	pop->user_hide = user_hide;
	pop->handler = handler;
	pop->param = param;
	pop->frm = &atv_input_box_window;
	
	return d_pop_show (prio);
	
}

/** @brief 隐藏显示的用户选择窗口
* @param prio			消息框的优先级
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
d_atv_pop_input_hide (D_U16 prio) D_FUNCPOSTFIT
{
	return d_pop_free (prio);
}



/** @brief 消息窗口初始化*/
D_Result
atv_input_box_ex_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
	return atv_input_box_ex_window_init(frm);
}


/** @brief 显示输入窗口(下面只有确认提示)
* @param prio			消息框的优先级
* @param layer		显示所在的层
* @param type		输入框类型
* @param str_title			要显示的标题文本
* @param msg			要显示的信息
* @param len			输入字符长度
* @param user_hide	用户是否可以手动退出
* @param handler	选择处理回调函数指针
* @param param		传给用户回调的参数
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_atv_pop_input_show_ex (D_U16 prio,
		D_GUILayer layer,
		D_PopInputType type,
		const D_Char *str_title,
		const D_Char *msg,
		D_U16 len, D_Bool user_hide,
		D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT,
		D_U32	param) D_FUNCPOSTFIT
{
	D_Result ret;
	D_InputBoxData	*pop;

	ret = d_pop_new (prio, layer, &atv_input_box_ex_window, InputBoxShow);
	if(ret != D_OK)
	{
#ifdef D_DEBUG
		D_ERROR ("Cannot load the pop up input\n");
#endif
		return D_ERR;
	}
	
	pop = &atv_inputbox_data[prio];
	pop->type = type;
	pop->str_title = str_title;
	pop->msg = msg;
	pop->input_len = D_MIN (len, D_MAX_INPUT_LEN);
	pop->user_hide = user_hide;
	pop->handler = handler;
	pop->param = param;
	pop->frm = &atv_input_box_ex_window;
	
	return d_pop_show (prio);
	
}












