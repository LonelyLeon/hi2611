/** @file
* @brief
* @author
* @date
*/
#include "dFP.h"
#include "dFrame.h"
#include "dControl.h"
#include "dGUI.h"
#include "show_osd_window.c"

/** @brief 事件处理*/
static D_Result
show_osd_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            break;
        default:
            break;
    }

    return D_ERR;
}
/** @brief 窗口初始化*/
D_Result
show_osd_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual           *vis;

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        //d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK ,D_INVALID_HANDLE);
        d_vis_set_handler (vis, show_osd_window_handler);
    }

    return D_OK;
}

/** @brief 画一个窗口*/
D_Result
p_show_osd_window (D_Bool show_en) D_FUNCPOSTFIT
{
    if(show_en)
    {
        if(!(show_osd_window.loaded))
        {
            d_gui_open_frame(&show_osd_window, D_GUI_LAYER_USER_2);
        }
    }
    else
    {
            d_gui_close_frame(&show_osd_window);
    }
    return D_OK;
}

