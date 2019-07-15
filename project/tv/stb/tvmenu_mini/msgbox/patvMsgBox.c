/** @file
* @brief ��Ϣ����ģ��
* @author ����
* @date 2005-9-13 ����: �����ļ�
*/

#include "dPop.h"
#include "dTimer.h"
#include "dDebug.h"
#include "pPopMsg.h"
#include "dControl.h"
#include "dGUI.h"
#include "dFrame.h"
#include "pFp.h"

#include "atv_msg_box_window.c"


/** @brief �Ƿ�����ڴ濽���ı�*/
#define COPY_MSG_ENABLE (1)

#define P_TITLE_MAX_LEN (36)
#define P_MSG_MAX_LEN (128)


/** @brief ��Ϣ������*/
typedef struct {
    D_U16 pop_type;
    D_GUILayer layer;
    D_U16 type;
#if COPY_MSG_ENABLE
    D_Char str_title[P_TITLE_MAX_LEN];
    D_Char msg[P_MSG_MAX_LEN];
#else
    const D_Char *str_title;
    const D_Char *msg;
#endif
    D_MSec timeout;
    D_PopMsgResponseType pop_msg_resp_type;
    D_Bool video_win_show;	
    D_HTimer htimer;
    D_Result (*handler) (D_U32 param) D_FUNCPOSTFIT;
    D_U32 param;
    
    D_MSec flash_hide_time; //����ʱ��
    D_U16   flash_cnt;  //��˸�ܴ���
    D_U16   flash_times;//����˸����
    D_Bool show_status;//��ʾ״̬
} D_MsgBoxData;

static D_MsgBoxData	msgbox_data[D_POP_PRIO_MAX];
static D_MsgBoxData *curr_prio_msgbox;


/** @brief ���ҵ�ǰ��Ҫ��С�Ӵ�����ʾ����ʾ��Ϣ
��С��������ʾ�ı�����MENU��֮�µ���ʾ��Ϣ*/
static D_Result 
video_win_msg_show(D_Bool show)
{
	/*������Ϣ��С����*/	
	if(curr_prio_msgbox->video_win_show && curr_prio_msgbox->layer < D_GUI_LAYER_MENU)
	{
		if (show)
		{
			d_gui_set_video_window_msg(D_TRUE, (D_Char*)(curr_prio_msgbox->msg));
		}
		else
		{
			d_gui_set_video_window_msg(D_FALSE, NULL);
		}
	}
	
	return D_OK;
}



static D_Result clear_box(void) D_FUNCPOSTFIT
{
	D_U32 param;
	D_Result (*handler)(D_U32 param) D_FUNCPOSTFIT;
	
	param = curr_prio_msgbox->param;
	handler = curr_prio_msgbox->handler;
	
	d_atv_pop_msg_hide((D_U16)(curr_prio_msgbox - msgbox_data));
	
	if(handler)
		handler(param);
	
	return D_OK;
}

static D_Result show_box(D_Bool show) D_FUNCPOSTFIT
{
	D_Visual *vis;
    
	vis = d_frame_get_control(&atv_msg_box_window, 0);
	if(vis)
	{    
            d_vis_show(vis, show);
            video_win_msg_show(show);
       }
	return D_OK;
}


/** @brief �����¼�������*/
static D_Result
msg_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
	switch(evt->type)
	{
		/*������*/
		case D_EVT_FP:
			if(curr_prio_msgbox->pop_msg_resp_type == D_POP_MSG_RESPONSE_ALL_NOT)
			{
				return D_OK;
			}
			else if(curr_prio_msgbox->pop_msg_resp_type == D_POP_MSG_RESPONSE_ANY)
			{
				clear_box();
				return D_OK;
			}
			else if(curr_prio_msgbox->pop_msg_resp_type == D_POP_MSG_RESPONSE_OK)
			{
				if(evt->fp.key == D_KEY_OK || evt->fp.key == D_KEY_PNL_OK || evt->fp.key == D_KEY_PNL_SOURCE)
				{
					clear_box();
					return D_OK;
				}
			}
			else
			{
				return D_ERR;
			}
			break;
		/*����ʱ*/
		case D_EVT_TIMER:
                    if(curr_prio_msgbox->htimer == evt->timer.htimer)
                    {
                        if(curr_prio_msgbox->show_status)
                        {
                            curr_prio_msgbox->flash_times++;                            
                            if(curr_prio_msgbox->flash_times >= curr_prio_msgbox->flash_cnt)
                            {
                                return clear_box();
                            }
                            else
                            {
                                show_box(D_FALSE);
                                curr_prio_msgbox->show_status = D_FALSE;                                
                                d_timer_reset(curr_prio_msgbox->htimer, curr_prio_msgbox->flash_hide_time);
                            }
                        }
                        else
                        {
                            show_box(D_TRUE);
                            curr_prio_msgbox->show_status = D_TRUE;                                
                            d_timer_reset(curr_prio_msgbox->htimer, curr_prio_msgbox->timeout);
                        }
                    }
                    break;
		/*�ͷ���Դ*/
		case D_EVT_DESTROY:

			/*����С���������ʾ��Ϣ*/
			video_win_msg_show(D_FALSE);
			
			if(curr_prio_msgbox->htimer != D_INVALID_HANDLE)
			{
				d_timer_destroy(curr_prio_msgbox->htimer);
				curr_prio_msgbox->htimer = D_INVALID_HANDLE;
			}
			
			d_vis_unsubscribe_evt(vis);
			return D_OK;
		default:
			break;
	}
	
	return D_OK;
}

/** @brief ��Ϣ���ڳ�ʼ��*/
D_Result atv_msg_box_window_init  (D_Frame *init) D_FUNCPOSTFIT
{
	D_Visual *vis;
	D_Char *str = NULL;

        curr_prio_msgbox->htimer = D_INVALID_HANDLE;
        curr_prio_msgbox->show_status = D_TRUE;

	vis = d_frame_get_control(init, ID_LABEL_TITLE);
	if(vis && curr_prio_msgbox->str_title)
	{
		d_label_set_text(vis, (D_Char*)curr_prio_msgbox->str_title);
	}
	
	vis = d_frame_get_control(init, ID_MSG_LABEL);
	if(vis)
	{
		d_label_set_text(vis, (D_Char*)curr_prio_msgbox->msg);
	}
	
	/*������Ϣ�����趨���ڱ���*/
	vis = d_frame_get_control(init, 0);
	if(vis)
	{
		/*���ó�ʱ*/
		if(curr_prio_msgbox->timeout > 0 && curr_prio_msgbox->timeout != ((D_MSec)-1)) {
			curr_prio_msgbox->htimer = d_timer_create(NULL, curr_prio_msgbox->timeout, d_gui_get_queue());
			d_vis_subscribe_evt(vis, D_EVT_TIMER_MASK, curr_prio_msgbox->htimer);	
		}
		
		/*�û������ٴ���*/
		if((curr_prio_msgbox->pop_msg_resp_type == D_POP_MSG_RESPONSE_ANY) \
			|| (curr_prio_msgbox->pop_msg_resp_type == D_POP_MSG_RESPONSE_OK))
		{
			d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
		}
              else if(curr_prio_msgbox->pop_msg_resp_type == D_POP_MSG_RESPONSE_ALL_NOT)
		{
			d_vis_subscribe_evt(vis, D_EVT_ALL_KEY_MASK | D_EVT_POWER_KEY_MASK | D_EVT_PROGRAM_PLUS_MINUS_KEY_MASK, D_INVALID_HANDLE);
		}                
		/*�趨�����¼�����*/
		d_vis_set_handler(vis, msg_window_handler);
	}
	
	return D_OK;
}

static D_Result MsgBoxShow(D_U16 prio, D_GUILayer layer, D_Frame *frm)
{
	curr_prio_msgbox = &msgbox_data[prio];
	
	/*��ʾС���������ʾ��Ϣ*/
	video_win_msg_show(D_TRUE);
	return D_OK;
}

/** @brief ��ʾ��������Ϣ����
* @param prio			��Ϣ������ȼ�
* @param layer			��ʾ���ڵĲ�
* @param type			��Ϣ������
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣ�ı�
* @param timeout��		��������Ļ��������ʱ�䣬С�ڵ��ڣ���ʾ��Զ��ʾ,ֱ������d_pop_msg_hide
						���û��ֶ�����
* @param pop_msg_resp_type	��Ӧ����
* @param video_win_show	��С��Ƶ�������Ƿ���ʾ
* @param handler		�û�ȷ�Ϻ���õĺ���ָ��
* @param param			�����û��ص��Ĳ���
* @return ��ʾ�ɹ�����D_OK,��ʾʧ�ܷ���D_ERR
*/
D_Result d_atv_pop_msg_show (D_U16 prio,
		D_GUILayer layer,
		D_PopMsgType type, const D_Char *str_title, const D_Char *msg, 
		D_MSec timeout, D_PopMsgResponseType pop_msg_resp_type, 
		D_Bool video_win_show,
		D_Result (*handler) (D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT
{
	D_Result ret;
	D_MsgBoxData *pop;
	
	ret = d_pop_new (prio, layer, &atv_msg_box_window, MsgBoxShow);
	if(ret != D_OK)
	{
#ifdef D_DEBUG
		D_ERROR ("Cannot load the pop up message\n");
#endif
		return D_ERR;
	}

	pop = &msgbox_data[prio];

	pop->layer = layer;
	pop->type = type;
#if COPY_MSG_ENABLE        
    snprintf(pop->str_title, P_TITLE_MAX_LEN, "%s", (str_title) ? str_title : "");
    snprintf(pop->msg, P_MSG_MAX_LEN, "%s", (msg) ? msg : "");
#else    
	pop->str_title = str_title;
	pop->msg = msg;
#endif
	pop->pop_msg_resp_type = pop_msg_resp_type;
	pop->video_win_show = video_win_show;
	pop->timeout = timeout;
	pop->htimer = D_INVALID_HANDLE;
	pop->handler = handler;
	pop->param = param;
	pop->flash_times = 0;
	pop->flash_cnt = 0; 
	pop->flash_hide_time = 0;    
	return d_pop_show (prio);
}

/** @brief ��˸��ʾ��������Ϣ����
* @param prio			��Ϣ������ȼ�
* @param layer			��ʾ���ڵĲ�
* @param type			��Ϣ������
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣ�ı�
* @param flash_times        ��˸����
* @param show_time��	��˸ʱ��ʾʱ��
* @param hide_time		��˸ʱ����ʱ��
* @param pop_msg_resp_type	��Ӧ����
* @param video_win_show	��С��Ƶ�������Ƿ���ʾ
* @param handler		�û�ȷ�Ϻ���õĺ���ָ��
* @param param			�����û��ص��Ĳ���
* @return ��ʾ�ɹ�����D_OK,��ʾʧ�ܷ���D_ERR
*/
D_Result d_atv_pop_msg_flash_show (D_U16 prio, D_GUILayer layer,
		D_PopMsgType type, const D_Char *str_title, const D_Char *msg, 
		D_U16 flash_times, D_MSec show_time, D_MSec hide_time, 
		D_PopMsgResponseType pop_msg_resp_type, D_Bool video_win_show,
		D_Result (*handler) (D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT
{
	D_Result ret;
	D_MsgBoxData *pop;
	
	ret = d_pop_new (prio, layer, &atv_msg_box_window, MsgBoxShow);
	if(ret != D_OK)
	{
#ifdef D_DEBUG
		D_ERROR ("Cannot load the pop up message\n");
#endif
		return D_ERR;
	}

	pop = &msgbox_data[prio];

	pop->layer = layer;
	pop->type = type;
#if COPY_MSG_ENABLE        
    snprintf(pop->str_title, P_TITLE_MAX_LEN, "%s", (str_title) ? str_title : "");
    snprintf(pop->msg, P_MSG_MAX_LEN, "%s", (msg) ? msg : "");
#else    
	pop->str_title = str_title;
	pop->msg = msg;
#endif
	pop->pop_msg_resp_type = pop_msg_resp_type;
	pop->video_win_show = video_win_show;
	pop->timeout = show_time;
	pop->flash_hide_time = hide_time; 
	pop->flash_cnt = flash_times;     
	pop->htimer = D_INVALID_HANDLE;
	pop->handler = handler;
	pop->param = param;
	pop->flash_times = 0;

       if(flash_times == 0)
       {
            pop->timeout = 0;
            pop->flash_hide_time = 0;
       }
 
	return d_pop_show (prio);
}

/** @brief ������ʾ����Ϣ����
* @param prio			��Ϣ������ȼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_atv_pop_msg_hide (D_U16 prio) D_FUNCPOSTFIT
{
	return d_pop_free (prio);
}
/*EOF*/

