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
#include "atv_auto_analog_scan_window.c"
#include "pStbScan.h"
#include "dSys.h"

typedef struct
{
    D_HFMan hfman;
    D_HScan   hscan;
    D_Visual *vis_progress,*vis_progress_val, *vis_ch_num, *vis_freq, *vis_mhz;
    D_Float freq[20];
    D_Char  ch_num[20];
    D_Char  progress_val[20];
} D_AutoAnalogScanData;

static D_ScanTaskConfig ScanConfig = {0};
static D_Ptr AutoScan_Op = (D_Ptr)(&ATV_AutoScan_Op);

static D_AutoAnalogScanData *auto_analog_scan_data = NULL;

extern D_FEndFreq china_atv_freq_list[];
extern D_U32 china_atv_freq_cnt;
static D_AtvScanParam atv_scanparam = {0};
//static D_KeyCode filter_keys[] = {D_KEY_POWER, D_KEY_PNL_POWER, D_KEY_MENU, D_KEY_PNL_MENU, D_KEY_ESC, D_KEY_PNL_ESC, D_KEY_OK, D_KEY_MUTE, D_KEY_VOLUME_PLUS, D_KEY_VOLUME_MINUS};

/**开始自动模拟信号搜索*/
static D_Result start_atv_scan(D_Bool flag)D_FUNCPOSTFIT
{
    D_ScanTaskConfig config = ScanConfig;
	TIME_RECORD_START("ATV blind_scan START!");
    memset(&atv_scanparam, 0x00, sizeof(D_AtvScanParam));

    config.buf_size = 64 * 1024;
    config.hqueue = d_gui_get_queue();
    config.priority = D_AUTO_SCAN_TASK_PRIO;
    config.pScanOp = AutoScan_Op;

    config.fend_type = D_FEND_ANALOG;
    config.fend_param.atv.videoMode = D_VideoP;   
    config.fend_param.atv.audioMode = D_AudioDK;
    config.pReserved = (D_Ptr)&atv_scanparam;

#if 0
    /*用于配置搜索哪些类型的音视频*/
    atv_scanparam.audiomode[0] = D_AudioDK;
    atv_scanparam.audiomode[1] = D_AudioBG;
    atv_scanparam.videomode[0] = D_VideoP;
    atv_scanparam.videomode[1] = D_VideoN;
    /*cnt == 0 时，以config.fend_param里的为准*/
    atv_scanparam.audiomode_cnt = 2;
    atv_scanparam.videomode_cnt = 2;
#endif
#ifdef D_TV_IAMGE_SOURCE
    /**<盲扫>*/
    config.startfreq = 44250;//49750;
    config.endfreq = 869750;//386000;//
#else
#if 1
    /*按频率表搜索*/
    atv_scanparam.freq_cnt = china_atv_freq_cnt;
    atv_scanparam.freq_list = china_atv_freq_list;
    config.scan_type = D_ATV_SCAN_TYPE_AUTO;
    config.bandwitch = 7000; //正负2000
    config.stepfreq = 1000;  
#else
    /*全频段搜索*/
    config.scan_type = D_ATV_SCAN_TYPE_FULL;
    config.startfreq = 112250;
    config.endfreq = 869750;
    config.bandwitch = 8000;
    config.stepfreq = 250;
#endif
#endif

#ifdef D_TV_IAMGE_SOURCE
    auto_analog_scan_data->hscan = d_atv_blind_scan_create(config);
#else
    auto_analog_scan_data->hscan = d_atv_auto_scan_create(config);
#endif
    if (auto_analog_scan_data->hscan == D_INVALID_HANDLE)
    {
        return D_ERR;
    }

    D_DUMP("start_scan\n");
    return D_OK;
}

/*搜素默认播放第一个电视节目*/
static D_Result
update_play_atv_prog(void)D_FUNCPOSTFIT
{
    D_StbPlayer *player;

    player = p_stb_get_player (0);
    if (! player)
        return D_ERR;

    player->atv_id = -1;
    player->atv_num = -1;
    player->prev_atv_id = -1;

    return D_OK;
}

static D_Result
exit_search_callback(D_Bool sel, D_U32 param)D_FUNCPOSTFIT
{
	if(auto_analog_scan_data && sel)
	{
		return d_gui_clear_menu();
	}
}

/** @brief 事件处理*/
static D_Result
atv_auto_scan_analog_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_auto_scan_analog_window;

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                if (auto_analog_scan_data->hscan != D_INVALID_HANDLE)
                {
			d_atv_pop_select_show(D_POP_MSG_PRIO_MSG_1, D_GUI_LAYER_MESSAGE, NULL,
	                                  d_gui_get_text(atv_IDS_STOP_ATV_SCAN), 10000, D_FALSE, exit_search_callback, 0) ;
                }
                break;
					
	         case D_KEY_ESC:
                case D_KEY_PNL_ESC:		
                case D_KEY_BACK:
                {
                    return d_gui_upper_menu();
                }
                    break; 
                case D_KEY_MUTE:
                case D_KEY_VOLUME_PLUS:
                case D_KEY_VOLUME_MINUS:
                    return D_ERR;
                    break;   
                default:
                    break;
            }
        }
        return D_OK;
        break;

        /*更新搜索进度*/
        case D_EVT_SCAN_PROGRESS:
        {
            d_progress_bar_set_val(auto_analog_scan_data->vis_progress, evt->scan.progress);
            return D_OK;
        }
        break;

        case D_EVT_SCAN_FREQ:
        {
            sprintf(auto_analog_scan_data->freq, "%0.2f", (D_Float)evt->scan.fendparam.atv.freq / 1000);
            d_label_set_text(auto_analog_scan_data->vis_freq, auto_analog_scan_data->freq);
            d_progress_bar_set_val(auto_analog_scan_data->vis_progress, evt->scan.progress);
	     sprintf(auto_analog_scan_data->progress_val,"%d %%",evt->scan.progress);
	     d_label_set_text(auto_analog_scan_data->vis_progress_val,auto_analog_scan_data->progress_val);
            return D_OK;
        }
        break;

        case D_EVT_SCAN_DATA:
        {
            sprintf(auto_analog_scan_data->ch_num, "%d", evt->scan.prog_cnt);
            d_label_set_text(auto_analog_scan_data->vis_ch_num, auto_analog_scan_data->ch_num);
            sprintf(auto_analog_scan_data->freq, "%0.2f", (D_Float)evt->scan.fendparam.atv.freq / 1000);
            d_label_set_text(auto_analog_scan_data->vis_freq, auto_analog_scan_data->freq);
            return D_OK;
        }
        break;

        case D_EVT_SCAN_OK:
        {
            if (auto_analog_scan_data->hscan != D_INVALID_HANDLE)
            {
                d_atv_pop_select_hide(D_POP_MSG_PRIO_MSG_1);
                d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_1, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                   d_gui_get_text(atv_IDS_SAVE_PROGROM), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
                d_gui_update();
            #ifdef D_TV_IAMGE_SOURCE
				d_atv_blind_scan_destroy (auto_analog_scan_data->hscan, D_TRUE);
			#else
                d_atv_auto_scan_destroy (auto_analog_scan_data->hscan, D_TRUE);
			#endif
                d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_1);
                auto_analog_scan_data->hscan = D_INVALID_HANDLE;
                if (auto_analog_scan_data->hfman != D_INVALID_HANDLE)
                {
                    d_fman_set_suspend(auto_analog_scan_data->hfman, D_FALSE);
                }
            }
		TIME_RECORD_ONE("ATV blind_scan END!");

            return d_gui_clear_menu();
        }
        break;

        case D_EVT_DESTROY:
        {
            d_vis_unsubscribe_evt (vis);
            d_atv_pop_select_hide(D_POP_MSG_PRIO_MSG_1);
            //p_fp_set_filter_keys(&filter_keys, 0xfffff);
            if (auto_analog_scan_data->hscan != D_INVALID_HANDLE)
            {
            	d_atv_pop_msg_show(D_POP_MSG_PRIO_MSG_1, D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG, d_gui_get_text(atv_IDS_PROMPT_INFO), \
                                   d_gui_get_text(atv_IDS_SAVE_PROGROM), -1, D_POP_MSG_RESPONSE_NOT, D_FALSE, NULL, 0);
               d_gui_update(); 
            #ifdef D_TV_IAMGE_SOURCE
			    d_atv_blind_scan_destroy (auto_analog_scan_data->hscan, D_TRUE);
			#else
                d_atv_auto_scan_destroy (auto_analog_scan_data->hscan, D_TRUE);
			#endif
                d_atv_pop_msg_hide(D_POP_MSG_PRIO_MSG_1);
                auto_analog_scan_data->hscan = D_INVALID_HANDLE;
                if (auto_analog_scan_data->hfman != D_INVALID_HANDLE)
                {
                    d_fman_set_suspend(auto_analog_scan_data->hfman, D_FALSE);
                }
            }

            if(auto_analog_scan_data)
            {
                PROJECT_FREE(auto_analog_scan_data);
                auto_analog_scan_data = NULL;
            }
            /*ATV自动搜索之后播放第一个节目*/
            update_play_atv_prog();
            p_stb_player_play_valid (0);
        }
        break;

        default:
            break;
    }
    return D_ERR;
}

D_Result
atv_auto_scan_analog_window_init(D_Frame *frm)
{
    D_Visual *vis;

    auto_analog_scan_data = (D_AutoAnalogScanData*)PROJECT_ALLOC(sizeof(D_AutoAnalogScanData));
    if(!auto_analog_scan_data)
    {
        return D_ERR;
    }
    memset(auto_analog_scan_data, 0x00, sizeof(D_AutoAnalogScanData));
    auto_analog_scan_data->vis_ch_num = d_frame_get_control (frm, ID_AUTOANALOG_LABLE_CH_VAL);
    if(auto_analog_scan_data->vis_ch_num)
    {
        sprintf(auto_analog_scan_data->ch_num, "%d", 0);
        d_label_set_text(auto_analog_scan_data->vis_ch_num, auto_analog_scan_data->ch_num);
    }
    auto_analog_scan_data->vis_progress = d_frame_get_control (frm, ID_AUTOANALOG_PROGRESS_CH_BAR);
    auto_analog_scan_data->vis_progress_val = d_frame_get_control (frm, ID_AUTOANALOG_LABLE_PROGRESS_VAL);

    auto_analog_scan_data->vis_freq = d_frame_get_control (frm, ID_AUTOANALOG_LABLE_FREQ_VAL);
    auto_analog_scan_data->vis_mhz = d_frame_get_control (frm, ID_AUTOANALOG_LABLE_FREQ_MHZ);
    if(auto_analog_scan_data->vis_mhz)
    {
        d_label_set_text(auto_analog_scan_data->vis_mhz, "MHz");
    }


    /*设定界面响应的按键*/
    //p_fp_set_filter_keys(filter_keys, sizeof(filter_keys)/sizeof(filter_keys[0]));

    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK | D_EVT_AUDIO_KEY_MASK | D_EVT_PROGRAM_PLUS_MINUS_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_auto_scan_analog_window_handler);
        d_vis_subscribe_evt (vis, D_EVT_SCAN_MASK, D_INVALID_HANDLE);
    }

    d_stb_stop_play();
    auto_analog_scan_data->hfman = d_fman_get_handle_by_type(D_FEND_ANALOG, 0);
    d_fman_set_suspend(auto_analog_scan_data->hfman, D_TRUE);

    start_atv_scan(D_TRUE);

    return D_OK;
}

/** @brief 自动模拟信号搜索菜单*/
D_Result
patv_auto_scan_analog_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_auto_scan_analog_window, D_TRUE);
}

