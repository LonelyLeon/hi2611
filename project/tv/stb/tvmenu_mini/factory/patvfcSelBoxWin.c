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

#include "atv_fc_selbox_window.c"


static D_Result (*select_handler_cb) (D_Bool sel, D_U32 param) D_FUNCPOSTFIT;
static D_Bool default_select;
static D_U32 select_param;

static D_Result
clear_box (void) D_FUNCPOSTFIT
{
    D_U32        param;
    D_Bool     sel;
    D_Visual    *sv;
    D_ID  sid;

    sv = d_vis_get_focus(d_frame_get_control (&atv_fc_selbox_window, 0));
    sid = d_frame_get_control_id(&atv_fc_selbox_window, sv);
    sel = (sid == ID_BUTTON_YES) ? D_TRUE : D_FALSE;

    d_gui_close_frame(&atv_fc_selbox_window);

    if(select_handler_cb)
    {
        select_handler_cb(sel, select_param);
    }

    return D_OK;
}


/** @brief �����¼�������*/
static D_Result
atv_fc_selbox_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
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
                    clear_box ();
                    return D_OK;
                    break;
                case D_KEY_ESC:
                case D_KEY_BACK:
                    return d_gui_close_frame(&atv_fc_selbox_window);
                    break;
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                case D_KEY_UP:
                case D_KEY_DOWN:
                case D_KEY_PNL_U:
                case D_KEY_PNL_D:
                    return D_ERR;
                    break;
                default:
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
atv_fc_selbox_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual    *vis;

    vis = d_frame_get_control (frm, ID_GROUP_BUTTONS);
    if (vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
        d_group_set_focus_loop(vis, D_TRUE);
    }

    vis = d_frame_get_control (frm, ID_BUTTON_YES);
    if (vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_OK_KEY_MASK, D_INVALID_HANDLE);
        if(default_select)
        {
            d_vis_set_focus(vis);
        }
    }

    vis = d_frame_get_control (frm, ID_BUTTON_NO);
    if (vis)
    {
        d_vis_unsubscribe_one_evt (vis, D_EVT_OK_KEY_MASK, D_INVALID_HANDLE);
        if(!default_select)
        {
            d_vis_set_focus(vis);
        }
    }

    /*������Ϣ�����趨���ڱ���*/
    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & (~ D_EVT_UP_DOWN_KEY_MASK), D_INVALID_HANDLE);

        /*�趨�����¼�����*/
        d_vis_set_handler (vis, atv_fc_selbox_window_handler);
    }

    return D_OK;
}


/* ѡ���*/
D_Result    d_atv_fc_selbox_window_show (D_Bool def,
        D_Result (*handler) (D_Bool sel, D_U32 param) D_FUNCPOSTFIT,
        D_U32 param, D_Rect *rect) D_FUNCPOSTFIT
{
    D_Result ret;
    D_FrameControlDescr *descr;

    default_select = def;
    select_handler_cb = handler;
    select_param = param;

    descr = (D_FrameControlDescr *)(atv_fc_selbox_window.ctrl_descrs);
    descr[0].x = rect->x;
    descr[0].paly = rect->y;

    return d_gui_open_frame(&atv_fc_selbox_window, D_GUI_LAYER_LOGO);

}

D_Result
d_atv_fc_selbox_window_hide (void) D_FUNCPOSTFIT
{
    return d_gui_close_frame(&atv_fc_selbox_window);
}



