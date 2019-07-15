#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "pConfig.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pBurnSerialNumber.h"
#include "pStbCaMenus.h"
#include "atv_serial_window.c"

static D_Result
serial_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_serial_window;
    D_Visual *tvis;

    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_BACK:
                case D_KEY_PNL_MENU:
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_MENU:
#if D_CA_SUPPORT_DEF
                    HRCA_HideOsdMessage(0); //清除屏幕顶部的滚动条
#endif
                    return d_gui_clear_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_CA:
            /*CA事件*/
        {
#if   D_CA_SUPPORT_DEF
            if((D_CAEventType)evt->ca.param1 == D_CA_EVT_ABV_SERIALIZE_STATUS)
            {
                D_U32 current_Cas = 0;

                current_Cas = d_ca_get_curcas();
                if(current_Cas == (1 << 14))//abvca
                {
#ifdef D_CA_SUPPORT_ABVCA
                    D_U8 *pserialstatus = ((D_U8 *)evt->ca.param2);

                    //D_CRIT("\n##### D_CA_EVT_ABV_SERIALIZE_STATUS-->%d\n", *pserialstatus);
                    if(*pserialstatus == 1) //配置成功
                    {
                        tvis = d_frame_get_control(frm, ID_LABEL_STATE3);
                        if(tvis)
                        {
                            d_label_set_text(tvis, "序列化成功，请退出");
                        }
                    }
                    else if(*pserialstatus == 0) //配置失败
                    {
                        tvis = d_frame_get_control(frm, ID_LABEL_STATE3);
                        if(tvis)
                        {
                            d_label_set_text(tvis, "序列化操作失败，请重新进行序列化");
                        }
                    }
#endif
                }
            }
#endif
        }
        return D_OK;
        case D_EVT_DESTROY:
        {
#ifdef D_BURN_SN_MODE_B
            if(p_serial_monitor_get_task_hdl() != D_INVALID_HANDLE)
            {
                p_serial_monitor_destroy();
            }
#ifdef D_COLOUR_SERIAL_EN
            p_serial_monitor_create(1, p_tv_bur_sn_handle, 0xffffffff, D_TRUE);
#endif
#endif
            //重新播放节目
            d_vis_unsubscribe_evt (vis);
            /*尝试播放各种可能的节目*/
            if (p_stb_player_play_valid (0) >= 0)
            {
            }
        }
        default:
            break;
    }
    return D_ERR;
}



D_Result
atv_serial_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
#if   D_CA_SUPPORT_DEF
    D_Visual *vis;

    /*停止所有播放*/
    d_stb_stop_play ();

    vis = d_frame_get_control(frm, ID_LABEL_STATE3);
    if(vis)
    {
        d_label_set_text(vis, "正在序列化，请勿进行其它操作");
    }
    vis = d_frame_get_control(frm, 0);
    if(vis)
    {
#ifdef D_BURN_SN_MODE_B
        if(p_serial_monitor_get_task_hdl() != D_INVALID_HANDLE)
        {
            p_serial_monitor_destroy();
        }
#ifdef D_JIANGSU_BURNER_SERIAL_NUM //jiangsu项目不使用联广的烧号方式
        //p_serial_monitor_create(1, p_bur_sn_handle, 0xffffffff, D_TRUE);
#else
        p_stb_ca_burn_serial_number();
#endif
#endif

        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK | D_EVT_CA_MASK, D_INVALID_HANDLE);
        d_vis_set_handler(vis, serial_window_handler);
    }

    return D_OK;
#else
    return D_OK;
#endif
}

/** @brief 序列化菜单*/
D_Result
p_atv_serial_show (void) D_FUNCPOSTFIT
{
    D_VidInput      input;
    D_U32   current_Cas = 0;

    input = p_conf_get_vid_input ();
    if(input != D_VID_IUTPUT_DTV)
    {
        return D_ERR;
    }

#if   D_CA_SUPPORT_DEF
    current_Cas = p_conf_get_curr_ca();

    if(current_Cas == (1 << 9) || current_Cas == (1 << 14))
    {
    }
    else
    {
        return D_ERR;
    }
#else
    return D_ERR;
#endif
    return d_gui_enter_menu (&atv_serial_window, D_TRUE);
}
