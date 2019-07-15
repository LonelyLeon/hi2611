/** @file
* @brief 语言设置菜单窗口模块
* @author 覃宜:
* @date 2013-10-18 覃宜: 建立文件
*/
#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "pConfig.h"
#include "pStbAtvMenus.h"

#include "atv_add_tp_window.c"


#define BUFF_LEN 16


typedef struct
{
    D_Result (*handler) (D_FEndParam *fparam, D_U32 param) D_FUNCPOSTFIT;
    D_U32 param;
    D_Bool    editflag;
    D_FEndParam fparam;
    D_Char    tp_fre[BUFF_LEN];
    D_Char    tp_sym[BUFF_LEN];
    D_FEndPol polarity;

} D_TpData;

static D_TpData    *tp_data = NULL;
static D_Char *d_polarity_buff[] = {"H", "V"};
static D_Char *d_polarity_buff_focus[] = {"<    H    >", "<    V    >"};


/** @brief 通知用户编辑结果*/
static D_Result
inform_user_edit_info(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_add_tp_window;
    D_Visual *vis;
    D_FEndParam fparam = {0};
    D_U32        param;
    D_Result (*handler) (D_FEndParam * fparam, D_U32 param) D_FUNCPOSTFIT;

    param = tp_data->param;
    handler = tp_data->handler;

    vis = d_frame_get_control(frm, ID_ADDTP_INPUT_FRE);
    if(vis)
    {
        fparam.freq = (D_FEndFreq)d_input_box_get_num(vis);
    }

    vis = d_frame_get_control(frm, ID_ADDTP_INPUT_SYM);
    if(vis)
    {
        fparam.dvbs.baud = (D_FEndBaud)d_input_box_get_num(vis);
    }

    vis = d_frame_get_control(frm, ID_ADDTP_SELECT_POLARITY);
    if(vis)
    {
        if(0 == d_select_box_get_val(vis))
        {
            fparam.dvbs.pol = D_FEND_HOR_POL;
        }
        else
        {
            fparam.dvbs.pol = D_FEND_VER_POL;
        }
    }

    if (handler)
    {
        handler (&fparam, param);
    }

    return D_OK;
}

/** @brief 事件处理*/
static D_Result
add_tp_pol_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_ENTER:
            d_select_box_set_content(vis, d_polarity_buff_focus, 2);
            break;
        case D_EVT_LEAVE:
            d_select_box_set_content(vis, d_polarity_buff, 2);
            break;
        default:
            break;
    }
    return D_ERR;
}

/** @brief 事件处理*/
static D_Result
add_tp_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
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
                case D_KEY_BACK:
                    d_gui_close_frame(&atv_add_tp_window);
                    break;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    inform_user_edit_info();
                    d_gui_close_frame(&atv_add_tp_window);
                default:
                    break;
            }
            return D_OK;
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(tp_data)
            {
                PROJECT_FREE(tp_data);
                tp_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}


/** @brief 窗口初始化*/
D_Result
atv_add_tp_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual        *vis;

    vis = d_frame_get_control(frm, ID_ADDTP_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    sprintf(tp_data->tp_fre, "%05d MHz", tp_data->fparam.freq);
    sprintf(tp_data->tp_sym, "%05d Ks/s", tp_data->fparam.dvbs.baud);
    tp_data->polarity = tp_data->fparam.dvbs.pol;

    vis = d_frame_get_control(frm,  ID_ADDTP_INPUT_FRE);
    if(vis)
    {
        d_input_box_set_text(vis, tp_data->tp_fre, strlen(tp_data->tp_fre));
    }

    vis = d_frame_get_control(frm, ID_ADDTP_INPUT_SYM);
    if(vis)
    {
        d_input_box_set_text(vis, tp_data->tp_sym, strlen(tp_data->tp_sym));
    }

    vis = d_frame_get_control(frm, ID_ADDTP_SELECT_POLARITY);
    if(vis)
    {
        d_select_box_set_content(vis, d_polarity_buff, 2);
        d_vis_set_handler(vis, add_tp_pol_handler);
        if(tp_data->polarity == D_FEND_HOR_POL)
        {
            d_select_box_set_val(vis, 0);
        }
        else
        {
            d_select_box_set_val(vis, 1);
        }
    }

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, add_tp_window_handler);
    }

    return D_OK;
}

/** @brief转发器编辑及增加弹出框窗口*/
D_Result
p_atv_add_edit_tp_menu_show(D_Bool edit, D_FEndParam *def_fparam,
                            D_Result (*handler) (D_FEndParam *fparam, D_U32 param) D_FUNCPOSTFIT,
                            D_U32 param)D_FUNCPOSTFIT
{

    if (D_FALSE == d_frame_is_loaded (&atv_add_tp_window))
    {
        tp_data = (D_TpData*)PROJECT_ALLOC(sizeof(D_TpData));
        if(!tp_data)
        {
            return D_ERR;
        }

        memset(tp_data, 0x00, sizeof(D_TpData));
        if(def_fparam)
        {
            tp_data->fparam = *def_fparam;
        }
        tp_data->editflag = edit;
        tp_data->handler = handler;
        tp_data->param = param;

        d_gui_open_frame(&atv_add_tp_window, D_GUI_LAYER_USER_2);
    }
    return D_OK;
}

/** @brief转发器编辑及增加弹出框窗口*/
D_Result
p_atv_add_edit_tp_menu_close(void)D_FUNCPOSTFIT
{
    if (D_TRUE == d_frame_is_loaded (&atv_add_tp_window))
    {
        d_gui_close_frame(&atv_add_tp_window);
    }
    return D_OK;
}

