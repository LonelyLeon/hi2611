#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "pConfig.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "wb_adjust_window.c"

#define BUF_LINE 8

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_focus_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_focus = {{&GUID_label_focus_attribute, NULL, NULL, }, 1, };

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_label_normal_attribute = { -1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_label_normal = {{&GUID_label_normal_attribute, NULL, NULL, }, 1, };

typedef struct
{
    D_S16 temperature, roffset, goffset, boffset, power_ref, rgain, ggain, bgain;

    D_U8 hdflag;
    D_VidInput input;
    D_CTEMP_SET tparam;
    D_CSC_SET cscparam;
    D_Char roffset_buf[BUF_LINE];
    D_Char goffset_buf[BUF_LINE];
    D_Char boffset_buf[BUF_LINE];
    D_Char rgain_buf[BUF_LINE];
    D_Char ggain_buf[BUF_LINE];
    D_Char bgain_buf[BUF_LINE];
} D_WBAdjustDate;

static D_WBAdjustDate *wb_adjust_data;

static D_Result
save_of_wb_adjust(void) D_FUNCPOSTFIT
{
    p_tvconf_set_cur_colormode(&wb_adjust_data->temperature, p_vip_get_dbinput(wb_adjust_data->input));

    p_tvconf_set_ctemp_param(&wb_adjust_data->tparam, p_vip_get_dbinput(wb_adjust_data->input), wb_adjust_data->temperature);
    return D_OK;
}


static D_Result
get_set_of_wb_adjust(void) D_FUNCPOSTFIT
{
    p_tvconf_get_cur_colormode(&wb_adjust_data->temperature, p_vip_get_dbinput(wb_adjust_data->input));

    if(p_tvconf_get_ctemp_param(&wb_adjust_data->tparam, p_vip_get_dbinput(wb_adjust_data->input), wb_adjust_data->temperature) == D_OK)
    {
        wb_adjust_data->roffset = wb_adjust_data->tparam.roffset;
        wb_adjust_data->goffset= wb_adjust_data->tparam.goffset;
        wb_adjust_data->boffset= wb_adjust_data->tparam.boffset;
        wb_adjust_data->rgain = wb_adjust_data->tparam.rgain;
        wb_adjust_data->ggain = wb_adjust_data->tparam.ggain;
        wb_adjust_data->bgain = wb_adjust_data->tparam.bgain;
    }
    sprintf(wb_adjust_data->roffset_buf, "%d", wb_adjust_data->roffset);
    sprintf(wb_adjust_data->goffset_buf, "%d", wb_adjust_data->goffset);
    sprintf(wb_adjust_data->boffset_buf, "%d", wb_adjust_data->boffset);
    sprintf(wb_adjust_data->rgain_buf, "%d", wb_adjust_data->rgain);
    sprintf(wb_adjust_data->ggain_buf, "%d", wb_adjust_data->ggain);
    sprintf(wb_adjust_data->bgain_buf, "%d", wb_adjust_data->bgain);

    return D_OK;
}


static D_Result
set_of_wb_adjust(void) D_FUNCPOSTFIT
{
    wb_adjust_data->tparam.rgain = wb_adjust_data->rgain;
    wb_adjust_data->tparam.ggain = wb_adjust_data->ggain;
    wb_adjust_data->tparam.bgain = wb_adjust_data->bgain;
    wb_adjust_data->tparam.roffset= wb_adjust_data->roffset;
    wb_adjust_data->tparam.goffset= wb_adjust_data->goffset;
    wb_adjust_data->tparam.boffset= wb_adjust_data->boffset;
    d_vip_setTemperature( wb_adjust_data->input, (D_U8*)&wb_adjust_data->tparam, (D_U8*)&wb_adjust_data->cscparam);
    return D_OK;
}

/** @brief  判断焦点位置
* @param    vis 控件指针
* @return   控件ID号
*/
static D_ID
get_focus_control_id(D_Frame *frm)
{
    D_Visual *vis;
    D_ID id;
    vis = d_vis_get_focus(d_frame_get_control(frm, 0));
    id = d_frame_get_control_id(frm, vis);
    return id;
}

static D_Result
set_label_focus_attribute(D_Visual *vis, D_Bool flag) D_FUNCPOSTFIT
{
    D_Ptr pattr;

    if(flag)
    {
        pattr = (D_Ptr)&GUID_label_focus;
        d_vis_set_attribute(vis, pattr);
    }
    else
    {
        pattr = (D_Ptr)&GUID_label_normal;
        d_vis_set_attribute(vis, pattr);
    }

    return D_OK;
}


static D_Result
set_temperature_connected_show(D_S16 flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &wb_adjust_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_1);

    switch(flag)
    {
        case 0:
            d_label_set_text(vis, d_gui_get_text(atv_IDS_WARM));
            break;
        case 1:
            d_label_set_text(vis, d_gui_get_text(atv_IDS_STANDARD));
            break;
        case 2:
            d_label_set_text(vis, d_gui_get_text(atv_IDS_COOL));
            break;
        default:
            break;
    }

    //根据不同的模式取得不同的设置
    if(p_tvconf_get_ctemp_param(&wb_adjust_data->tparam, p_vip_get_dbinput(wb_adjust_data->input), wb_adjust_data->temperature) == D_OK)
    {
        wb_adjust_data->roffset= wb_adjust_data->tparam.roffset;
        wb_adjust_data->goffset= wb_adjust_data->tparam.goffset;
        wb_adjust_data->boffset= wb_adjust_data->tparam.boffset;
        wb_adjust_data->rgain = wb_adjust_data->tparam.rgain;
        wb_adjust_data->ggain = wb_adjust_data->tparam.ggain;
        wb_adjust_data->bgain = wb_adjust_data->tparam.bgain;
    }
    sprintf(wb_adjust_data->roffset_buf, "%d", wb_adjust_data->roffset);
    sprintf(wb_adjust_data->goffset_buf, "%d", wb_adjust_data->goffset);
    sprintf(wb_adjust_data->boffset_buf, "%d", wb_adjust_data->boffset);
    sprintf(wb_adjust_data->rgain_buf, "%d", wb_adjust_data->rgain);
    sprintf(wb_adjust_data->ggain_buf, "%d", wb_adjust_data->ggain);
    sprintf(wb_adjust_data->bgain_buf, "%d", wb_adjust_data->bgain);
    d_vip_setTemperature( wb_adjust_data->input, (D_U8*)&wb_adjust_data->tparam, (D_U8*)&wb_adjust_data->cscparam);

    vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_4);
    d_label_set_text(vis, wb_adjust_data->rgain_buf);

    vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_5);
    d_label_set_text(vis, wb_adjust_data->ggain_buf);

    vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_6);
    d_label_set_text(vis, wb_adjust_data->bgain_buf);

    vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_8);
    d_label_set_text(vis, wb_adjust_data->roffset_buf);

    vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_9);
    d_label_set_text(vis, wb_adjust_data->goffset_buf);

    vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_10);
    d_label_set_text(vis, wb_adjust_data->boffset_buf);

    return D_OK;
}

static D_Result
set_wb_adjust_data(D_ID id, D_Bool flag) D_FUNCPOSTFIT
{
    D_Frame *frm = &wb_adjust_window;
    D_Visual *vis;

    switch(id)
    {
        case ID_WB_ADJUST_BUTTON_1:
            p_tvconf_set_ctemp_param(&wb_adjust_data->tparam, p_vip_get_dbinput(wb_adjust_data->input), wb_adjust_data->temperature);
            if(flag)
            {
                wb_adjust_data->temperature = (wb_adjust_data->temperature + 1) % 3 ;
            }
            else
            {
                wb_adjust_data->temperature = (wb_adjust_data->temperature + 3 - 1) % 3 ;
            }
            set_temperature_connected_show(wb_adjust_data->temperature);
            break;
        case ID_WB_ADJUST_BUTTON_4:
            if(flag)
            {
                wb_adjust_data->rgain = (wb_adjust_data->rgain + 1) % 256;
            }
            else
            {
                wb_adjust_data->rgain = (wb_adjust_data->rgain + 256 - 1) % 256;
            }

            vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_4);
            {
                sprintf(wb_adjust_data->rgain_buf, "%d", wb_adjust_data->rgain);
                d_label_set_text(vis, wb_adjust_data->rgain_buf);
            }
            break;
        case ID_WB_ADJUST_BUTTON_5:
            if(flag)
            {
                wb_adjust_data->ggain = (wb_adjust_data->ggain + 1) % 256;
            }
            else
            {
                wb_adjust_data->ggain = (wb_adjust_data->ggain + 256 - 1) % 256;
            }

            vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_5);
            {
                sprintf(wb_adjust_data->ggain_buf, "%d", wb_adjust_data->ggain);
                d_label_set_text(vis, wb_adjust_data->ggain_buf);
            }

            break;

        case ID_WB_ADJUST_BUTTON_6:
            if(flag)
            {
                wb_adjust_data->bgain = (wb_adjust_data->bgain + 1) % 256;
            }
            else
            {
                wb_adjust_data->bgain = (wb_adjust_data->bgain + 256 - 1) % 256;
            }

            vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_6);
            {
                sprintf(wb_adjust_data->bgain_buf, "%d", wb_adjust_data->bgain);
                d_label_set_text(vis, wb_adjust_data->bgain_buf);
            }
            break;

        case ID_WB_ADJUST_BUTTON_8:
            if(flag)
            {
                wb_adjust_data->roffset= (wb_adjust_data->roffset+ 1) % 2048;
            }
            else
            {
                wb_adjust_data->roffset= (wb_adjust_data->roffset+ 2048 - 1) % 2048;
            }

            vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_8);
            {
                sprintf(wb_adjust_data->roffset_buf, "%d", wb_adjust_data->roffset);
                d_label_set_text(vis, wb_adjust_data->roffset_buf);
            }
            break;
        case ID_WB_ADJUST_BUTTON_9:
            if(flag)
            {
                wb_adjust_data->goffset= (wb_adjust_data->goffset + 1) % 2048;
            }
            else
            {
                wb_adjust_data->goffset = (wb_adjust_data->goffset + 2048 - 1) % 2048;
            }

            vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_9);
            {
                sprintf(wb_adjust_data->goffset_buf, "%d", wb_adjust_data->goffset);
                d_label_set_text(vis, wb_adjust_data->goffset_buf);
            }
            break;
        case ID_WB_ADJUST_BUTTON_10:
            if(flag)
            {
                wb_adjust_data->boffset= (wb_adjust_data->boffset + 1) % 2048;
            }
            else
            {
                wb_adjust_data->boffset = (wb_adjust_data->boffset + 2048 - 1) % 2048;
            }


            vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_10);
            {
                sprintf(wb_adjust_data->boffset_buf, "%d", wb_adjust_data->boffset);
                d_label_set_text(vis, wb_adjust_data->boffset_buf);
            }
            break;
        default:
            break;
    }
    set_of_wb_adjust();

    return D_OK;
}


static D_Result
tempearture_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &wb_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_1);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_wb_adjust_data(id, D_TRUE);
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
r_gain_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &wb_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_4);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_wb_adjust_data(id, D_TRUE);
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
g_gain_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &wb_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_5);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_wb_adjust_data(id, D_TRUE);
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
b_gain_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &wb_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_6);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_wb_adjust_data(id, D_TRUE);
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
r_offset_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &wb_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_8);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_wb_adjust_data(id, D_TRUE);
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
g_offset_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &wb_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_9);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_wb_adjust_data(id, D_TRUE);
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
b_offset_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &wb_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_10);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            set_wb_adjust_data(id, D_TRUE);
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
copy_all_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &wb_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_11);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
reset_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &wb_adjust_window;
    D_Visual *vis_label;
    D_ID id;

    id = d_frame_get_control_id(frm, vis);
    vis_label = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_12);

    switch (evt->type)
    {
        case D_EVT_ENTER:
            set_label_focus_attribute(vis_label, D_TRUE);
            break;
        case D_EVT_PRESSED:
            break;
        case D_EVT_LEAVE:
            set_label_focus_attribute(vis_label, D_FALSE);
            break;
        default:
            break;
    }
    return D_OK;
}



static D_Result
wb_adjust_label_show(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &wb_adjust_window;
    D_Visual *vis;

    set_temperature_connected_show(wb_adjust_data->temperature);

    vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_3);
    if(vis)
    {
        if(wb_adjust_data->input == D_VID_IUTPUT_TV)
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_TV));
        }
        else if(wb_adjust_data->input == D_VID_IUTPUT_DTV)
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_DTV));
        }
        else if((wb_adjust_data->input == D_VID_IUTPUT_AV1) || (wb_adjust_data->input == D_VID_IUTPUT_AV2))
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_AV));
        }
        else if(wb_adjust_data->input == D_VID_IUTPUT_YPBPR)
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_YPBPR));
        }
        else if(wb_adjust_data->input == D_VID_IUTPUT_HDMI1)
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_HDMI1));
        }
        else if(wb_adjust_data->input == D_VID_IUTPUT_USB1)
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_USB));
        }
        else if(wb_adjust_data->input == D_VID_IUTPUT_HDMI2)
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_HDMI2));
        }
        else if(wb_adjust_data->input == D_VID_IUTPUT_VGA)
        {
            d_label_set_text(vis, d_gui_get_text(atv_IDS_PC));
        }
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_4);
    if(vis)
    {
        d_label_set_text(vis, wb_adjust_data->rgain_buf);
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_5);
    if(vis)
    {
        d_label_set_text(vis, wb_adjust_data->ggain_buf);
    }
    vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_6);
    if(vis)
    {
        d_label_set_text(vis, wb_adjust_data->bgain_buf);
    }


    vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_8);
    if(vis)
    {
        d_label_set_text(vis, wb_adjust_data->roffset_buf);
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_9);
    if(vis)
    {
        d_label_set_text(vis, wb_adjust_data->goffset_buf);
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_LABEL_10);
    if(vis)
    {
        d_label_set_text(vis, wb_adjust_data->boffset_buf);
    }

    return D_OK;
}

static D_Result
wb_adjust_vis_handler(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &wb_adjust_window;
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_WB_ADJUST_BUTTON_1);
    if(vis)
    {
        d_button_set_text(vis, "TEMPERATURE");
        d_vis_set_handler(vis, tempearture_handler);
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_BUTTON_3);
    if(vis)
    {
        d_button_set_text(vis, "MODE");
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_BUTTON_4);
    if(vis)
    {
        d_button_set_text(vis, "R_GAIN");
        d_vis_set_handler(vis, r_gain_handler);
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_BUTTON_5);
    if(vis)
    {
        d_button_set_text(vis, "G_GAIN");
        d_vis_set_handler(vis, g_gain_handler);
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_BUTTON_6);
    if(vis)
    {
        d_button_set_text(vis, "B_GAIN");
        d_vis_set_handler(vis, b_gain_handler);
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_BUTTON_8);
    if(vis)
    {
        d_button_set_text(vis, "R_OFFSET");
        d_vis_set_handler(vis, r_offset_handler);
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_BUTTON_9);
    if(vis)
    {
        d_button_set_text(vis, "G_OFFSET");
        d_vis_set_handler(vis, g_offset_handler);
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_BUTTON_10);
    if(vis)
    {
        d_button_set_text(vis, "B_OFFSET");
        d_vis_set_handler(vis, b_offset_handler);
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_BUTTON_11);
    if(vis)
    {
        d_button_set_text(vis, "COPY ALL");
        d_vis_set_handler(vis, copy_all_handler);
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_BUTTON_12);
    if(vis)
    {
        d_button_set_text(vis, "Reset");
        d_vis_set_handler(vis, reset_handler);
    }

    return D_OK;
}

static D_Result
wb_adjust_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *fv;
    D_Frame *frm = &wb_adjust_window;
    D_ID id;

    id = get_focus_control_id(frm);

    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                    return d_gui_clear_menu();
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                case D_KEY_OK:
                    set_wb_adjust_data(id, D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    set_wb_adjust_data(id, D_FALSE);
                    break;
                case D_KEY_MENU:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            save_of_wb_adjust();
            if(wb_adjust_data)
            {
                PROJECT_FREE(wb_adjust_data);
                wb_adjust_data = NULL;
            }
        default:
            break;
    }
    return D_ERR;
}

D_Result
wb_adjust_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    wb_adjust_data = (D_WBAdjustDate*)PROJECT_ALLOC(sizeof(D_WBAdjustDate));
    if(!wb_adjust_data)
    {
        return D_ERR;
    }
    memset(wb_adjust_data, 0, sizeof(D_WBAdjustDate));

    wb_adjust_data->input = p_conf_get_vid_input();
    if(wb_adjust_data->input == D_VID_IUTPUT_AV1 || wb_adjust_data->input == D_VID_IUTPUT_AV2 || wb_adjust_data->input == D_VID_IUTPUT_TV)
    {
        wb_adjust_data->hdflag = p_vip_get_ntscflag();
    }
    else
    {
        wb_adjust_data->hdflag = p_vip_get_hdflag();
    }
    if(wb_adjust_data->hdflag)
    {
        p_tvconf_get_hdcsc_set_param(&wb_adjust_data->cscparam, p_vip_get_dbinput(wb_adjust_data->input));
    }
    else
    {
        p_tvconf_get_csc_set_param(&wb_adjust_data->cscparam, p_vip_get_dbinput(wb_adjust_data->input));
    }

    get_set_of_wb_adjust();
    wb_adjust_label_show();
    wb_adjust_vis_handler();

    vis = d_frame_get_control(frm, ID_WB_ADJUST_GROUP_3);
    if(vis)
    {
        d_vis_enable(vis, D_FALSE);
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_BUTTON_3);
    if(vis)
    {
        d_vis_set_focusable(vis, D_FALSE);
    }

    vis = d_frame_get_control(frm, ID_WB_ADJUST_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, wb_adjust_window_handler);
    }

    return D_OK;
}

/** @brief 白平衡调整菜单*/
D_Result
p_atv_wb_adjust_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&wb_adjust_window, D_TRUE);
}
