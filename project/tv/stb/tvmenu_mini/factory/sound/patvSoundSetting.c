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
#include "sound_setting_window.c"


static D_U8 drc_value = 0;
static D_Char drc_buf[8];


static D_Result
drc_change_value(D_Bool add) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_ID id;
    
    vis = d_vis_get_focus(d_frame_get_control(&sound_setting_window, 0));
    id = d_frame_get_control_id(&sound_setting_window, vis);

    if(id == ID_SOUND_BUTTON_12)
    {
        drc_value = (drc_value + 1) % 2;
        sprintf(drc_buf, "%d", drc_value);
        d_label_set_text(d_frame_get_control(&sound_setting_window, ID_SOUND_LABEL_VALUE12), drc_buf);
        d_av_avc_ctl_whole_en(0, drc_value);
        p_tvconf_set_avc_whole_en(drc_value);
    }

    return D_OK;
}


static D_Result
peq_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
            p_atv_peq_set_show();
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
avc_dac_ctl_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
        {
            D_ID vis_id = d_frame_get_control_id(&sound_setting_window, vis);

            if(vis_id == ID_SOUND_BUTTON_6)
            {
                p_atv_avc_dac_ctl_show(0);
            }
            else if(vis_id == ID_SOUND_BUTTON_12)
            {
                drc_change_value(D_TRUE);
            } 
        }
        break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
srs_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_PRESSED:
                p_atv_srs_show();
            break;
        default:
            break;
    }
    return D_OK;
}

static D_Result
sound_setting_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                    return d_gui_clear_menu();
                case D_KEY_MENU:
                    return d_gui_upper_menu();
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    drc_change_value(D_TRUE);
                    break;
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    drc_change_value(D_FALSE);
                    break;
                default:
                    break;
            }
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
        default:
            break;
    }
    return D_ERR;
}

D_Result
sound_setting_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;

    vis = d_frame_get_control(frm, ID_SOUND_BUTTON_4);
    if(vis)
    {
        d_button_set_text(vis, "PEQ");
        d_vis_set_handler(vis, peq_handler);
    }

    vis = d_frame_get_control(frm, ID_SOUND_BUTTON_6);
    if(vis)
    {
        d_button_set_text(vis, "AVC DAC CTL");
        d_vis_set_handler(vis, avc_dac_ctl_handler);
    }
    
    vis = d_frame_get_control(frm, ID_SOUND_BUTTON_12);
    if(vis)
    {
        d_button_set_text(vis, "DRC");
        d_vis_set_handler(vis, avc_dac_ctl_handler);
    }

    vis = d_frame_get_control(frm, ID_SOUND_BUTTON_13);
    if(vis)
    {
        d_button_set_text(vis, "SRS");
        d_vis_set_handler(vis, srs_handler);
    }

    drc_value = p_tvconf_get_avc_whole_en();
    drc_value = D_MIN(drc_value, 1);
    vis = d_frame_get_control(frm, ID_SOUND_LABEL_VALUE12);
    if(vis)
    {
        sprintf(drc_buf, "%d", drc_value);
        d_label_set_text(vis, drc_buf);
    }

    vis = d_frame_get_control(frm, ID_SOUND_GROUP);
    if(vis)
    {
        d_group_set_focus_loop(vis, D_TRUE);
        d_vis_unsubscribe_one_evt(vis, D_EVT_LEFT_RIGHT_KEY_MASK, D_INVALID_HANDLE);
    }

    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, sound_setting_window_handler);
    }

    return D_OK;
}

/** @brief …˘“Ù…Ë÷√≤Àµ•*/
D_Result
p_atv_sound_setting_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&sound_setting_window, D_TRUE);
}

