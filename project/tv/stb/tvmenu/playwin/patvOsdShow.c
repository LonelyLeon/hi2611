/** @file
* @brief
* @author
* @date
*/
#include    "dFrame.h"
#include    "atvFormat.h"
#include    "atvlanresource.h"
#include    "atvImageResource.h"
#include    "atvpalletes.h"

#include "dFP.h"
#include "dFrame.h"
#include "dControl.h"
#include "dGUI.h"


///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// predefined macros

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1022ddd_2fd4823 = { -1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW} "canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1022ddd_2fd29 = {{&GUID_c1022ddd_2fd4823, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_osd_show_window[] =
{
    // [0]canvas
    {D_CTRL_WINDOW, -1, 5, 5, 0, 20, 20, 0, -1, (D_FrameCtrlDescr*)&GUID_c1022ddd_2fd29, },
    { -1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result osd_show_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_osd_show_window[1];
D_Frame osd_show_window =
{
    run_ctrls_osd_show_window,
    ctrl_description_of_osd_show_window,
    osd_show_window_init,
};
static D_U32 Curhandle = 0;
/** @brief 事件处理*/
static D_Result
osd_show_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
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
osd_show_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual           *vis;

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        //d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK ,D_INVALID_HANDLE);
        d_vis_set_handler (vis, osd_show_window_handler);
    }

    return D_OK;
}

/** @brief 画一个窗口，为滚动条打开osd*/
D_Bool
p_osd_show (D_Bool show_en, D_U32 handle) D_FUNCPOSTFIT
{
    if(show_en)
    {
        Curhandle   = (Curhandle | (1 << handle));
        if(!(osd_show_window.loaded))
        {
            d_gui_open_frame(&osd_show_window, D_GUI_LAYER_USER_2);
        }
        return D_TRUE;
    }
    else
    {
        Curhandle   = (Curhandle & (~(1 << handle)));
        if(Curhandle <= 0)
        {
            d_gui_close_frame(&osd_show_window);
        }
        return D_FALSE;
    }
}

void p_osd_show_reset() D_FUNCPOSTFIT
{
  Curhandle   = 0;
}
