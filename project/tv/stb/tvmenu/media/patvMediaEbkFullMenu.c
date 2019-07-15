#include "dFP.h"
#include "dFrame.h"
#include "dControl.h"
#include "dGUI.h"
#include "dFileSystem.h"
#include "pFile_Scan.h"
#include "dTV.h"
#include "pConfig.h"
#include "pSdk.h"
#include "pStbAtvMenus.h"


#include "atv_ebk_full_screen_window.c"

static D_Char media_ebk_buf_path[D_PATH_LENGTH];

/** @brief 事件处理*/
static D_Result
media_ebk_full_screen_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    d_media_ebk_stop();
                    d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
                    return D_OK;
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                case D_KEY_UP:
                case D_KEY_PNL_U:
                case D_KEY_DOWN:
                case D_KEY_PNL_D:
                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    d_media_ebk_set_key(evt->fp.key);
                    return D_OK;
                default:
                    break;
            }
        }
        break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            AtvMediaMenuStatus &= ~ATV_MEDIA_MENU_STATUS_EBOOK_FULLSCREEN;
            memset(media_ebk_buf_path, 0x00, D_PATH_LENGTH);
            break;
        default:
            break;
    }

    return D_ERR;
}



/** @brief 窗口初始化*/
D_Result
atv_ebk_full_screen_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual           *vis;
    D_VidFormat         fmt;
	D_U8 *payload;
	D_U16 len;

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, media_ebk_full_screen_window_handler);
    }
	
	payload = d_conf_file_search_tag(CUSTOM_CONFIG_TAG_PANEL_CONFIG, &len);
	if(payload)
	{
		D_U16 v_active_width,h_active_width;		
		h_active_width = ((D_U16)payload[2]<<8 )|payload[3];
		v_active_width = ((D_U16)payload[4]<<8 )|payload[5];
		d_media_ebk_play(media_ebk_buf_path, 0, 0, h_active_width, v_active_width);
	}
	else
	{
	    fmt = p_conf_get_vid_fmt();

	    switch (fmt)
	    {
	        case D_VID_FMT_NTSC:
	        case D_VID_FMT_480P_60:
	            d_media_ebk_play(media_ebk_buf_path, 0, 0, 720, 480);
	            break;

	        case D_VID_FMT_PAL:
	        case D_VID_FMT_576P_50:
	            d_media_ebk_play(media_ebk_buf_path, 0, 0, 720, 576);
	            break;

	        case D_VID_FMT_720P_50:
	        case D_VID_FMT_720P_60:
	            d_media_ebk_play(media_ebk_buf_path, 0, 0, 1280, 720);
	            break;

	        case D_VID_FMT_1080I_50:
	        case D_VID_FMT_1080I_60:
	        case D_VID_FMT_1080P_50:
	        case D_VID_FMT_1080P_60:
	            d_media_ebk_play(media_ebk_buf_path, 0, 0, 1920, 1080);
	            break;
	        case    D_VID_FMT_768P_50:
	        case    D_VID_FMT_768P_60:
	            d_media_ebk_play(media_ebk_buf_path, 0, 0, 1366, 768);
	            break;
	        case D_VID_FMT_1440_900:
	            d_media_ebk_play(media_ebk_buf_path, 0, 0, 1440, 900);
	            break;

	        default:
	            d_media_ebk_play(media_ebk_buf_path, 0, 0, 720, 576);
	            break;
	    }
	}
    /*设定服务声道和音量*/
    //d_av_set_aud_mute(0, D_FALSE);
    d_tv_set_aud_mute(g_htv, p_conf_get_aud_mute());
    d_tv_set_aud_track(g_htv, p_conf_get_aud_track());
    p_stb_player_set_vol(0, p_conf_get_volume());

    AtvMediaMenuStatus |= ATV_MEDIA_MENU_STATUS_EBOOK_FULLSCREEN;

    return D_OK;
}


D_Result
p_media_ebk_full_screen_window_show(D_Char* path_name) D_FUNCPOSTFIT
{
    memset(media_ebk_buf_path, 0x00, D_PATH_LENGTH);
    strncpy(media_ebk_buf_path, path_name, D_PATH_LENGTH);

    return d_gui_enter_menu_new (ATV_MEDIA_MENU_ID, &atv_ebk_full_screen_window, D_CLEAR_NONE);
}

D_Result
p_media_ebk_full_screen_window_hide(void) D_FUNCPOSTFIT
{
    if (d_frame_is_loaded (&atv_ebk_full_screen_window))
    {
        d_media_ebk_stop();
        d_gui_upper_menu_ext(ATV_MEDIA_MENU_ID);
    }

    return D_OK;
}

