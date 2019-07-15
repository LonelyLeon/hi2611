/** @file
* @brief �û��������봰��ģ��
* @author ����
* @date 2013-7-3����: �����ļ�
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

#include "atv_pwd_input_window.c"


/*������볤��*/
#define D_MAX_INPUT_LEN 16


/** @brief ���������*/
typedef struct
{
    D_PopInputType type;
    const D_Char *str_title;
    const D_Char *msg;
    D_U16   input_len;
    D_Bool  user_hide;
    D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT;
    D_U32   param;
    D_Frame *frm;
    D_Rect  rect;   /*��¼���ڵ�����*/
} D_InputBoxData;

static D_InputBoxData   inputbox_data[D_POP_PRIO_MAX];
static D_InputBoxData *curr_prio_inputbox;
//static D_Char head_prompt[128];
/*��¼���ڵ�Ĭ������*/
static D_Rect  default_rect = {-1, -1, -1, -1};

static D_Result
clear_box (D_Char *input) D_FUNCPOSTFIT
{
    D_U32        param;
    D_Char   str[D_MAX_INPUT_LEN + 1];
    D_Char  *ptr;

    D_Result (*handler) (D_Char * input, D_U32 param) D_FUNCPOSTFIT;

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

    d_pop_free (curr_prio_inputbox - inputbox_data);

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
            if(vis->element.input.val == vis->element.input.cnt)
            {
                clear_box (d_input_box_get_text (vis));
            }
            break;
        default:
            break;
    }

    return D_ERR;
}

/** @brief �����¼�������*/
static D_Result
input_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual    *cv;

    switch (evt->type)
    {
        /*������*/
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
                            d_pop_input_hide (curr_prio_inputbox - inputbox_data);
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
                        d_pop_input_hide (curr_prio_inputbox - inputbox_data);
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
        /*�ͷ���Դ*/
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt(vis);
            return D_OK;
        default:
            break;
    }

    return D_ERR;
}

/** @brief ��Ϣ���ڳ�ʼ��*/
D_Result
atv_pwd_input_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual    *vis;
    D_U32   mask;

    /*������ʾ��Ϣ*/
    vis = d_frame_get_control(frm, ID_LABEL_TITLE);
    if(vis && curr_prio_inputbox->str_title)
    {
        d_label_set_text(vis, (D_Char*)curr_prio_inputbox->str_title);
    }

    /*�趨�����*/
    vis = d_frame_get_control (frm, ID_INPUT_PASSWD);
    if (vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_COLOR_KEY_MASK, D_INVALID_HANDLE);
        d_input_box_set_len (vis, curr_prio_inputbox->input_len);
        d_vis_set_handler (vis, input_handler);
    }

    /*������Ϣ�����趨���ڱ���*/
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
                    D_EVT_UP_DOWN_KEY_MASK | D_EVT_KEY_MASK;

        }

        d_vis_subscribe_evt (vis, mask, D_INVALID_HANDLE);

        /*�趨�����¼�����*/
        d_vis_set_handler (vis, input_window_handler);
    }

    return D_OK;
}


static D_Result InputBoxShow(D_U16 prio, D_GUILayer layer, D_Frame *frm)
{
    D_FrameControlDescr *descr;
    
    curr_prio_inputbox = &inputbox_data[prio];

    descr = (D_FrameControlDescr *)(curr_prio_inputbox->frm->ctrl_descrs);
    
    descr[0].x = curr_prio_inputbox->rect.x;
    descr[0].paly = curr_prio_inputbox->rect.y;
    
    return D_OK;
}

/** @brief ��ʾ�������봰��
* @param prio           ��Ϣ������ȼ�
* @param layer      ��ʾ���ڵĲ�
* @param type       ���������
* @param str_title          Ҫ��ʾ�ı����ı�
* @param msg            Ҫ��ʾ����Ϣ
* @param len            �����ַ�����
* @param user_hide  �û��Ƿ�����ֶ��˳�
* @param handler    ѡ����ص�����ָ��
* @param param      �����û��ص��Ĳ���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result    d_atv_pwd_input_window_show (D_U16 prio,
                              D_GUILayer layer,
                              D_PopInputType type,
                              const D_Char *str_title,
                              const D_Char *msg,
                              D_U16 len, D_Bool user_hide,
                              D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT,
                              D_U32   param, D_Rect *rect) D_FUNCPOSTFIT
{
    D_Result ret;
    D_InputBoxData  *pop;
    D_FrameControlDescr *descr;

    ret = d_pop_new (prio, layer, &atv_pwd_input_window, InputBoxShow);
    if(ret != D_OK)
    {
#ifdef D_DEBUG
        D_ERROR ("Cannot load the pop up input\n");
#endif
        return D_ERR;
    }

    pop = &inputbox_data[prio];
    pop->type = type;
    pop->str_title = str_title;
    pop->msg = msg;
    pop->input_len = D_MIN (len, D_MAX_INPUT_LEN);
    pop->user_hide = user_hide;
    pop->handler = handler;
    pop->param = param;

    if(default_rect.x == -1 && default_rect.y == -1)
    {
        descr = (D_FrameControlDescr *)(atv_pwd_input_window.ctrl_descrs);
        default_rect.x = descr[0].x;
        default_rect.y = descr[0].paly;
    }
    
    if(rect)
    {
        pop->rect = *rect;
    }
    else
    {
        pop->rect = default_rect;
    }

    pop->frm = &atv_pwd_input_window;

    return d_pop_show (prio);

}

/** @brief ������ʾ���û����봰��
* @param prio           ��Ϣ������ȼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_atv_pwd_input_window_hide (D_U16 prio) D_FUNCPOSTFIT
{
    return d_pop_free (prio);
}



