/** @file
* @brief 窗口模块
* @author 覃宜
* @date 2013-7-1 覃宜: 建立文件
*/
#include <stdio.h>
#include <string.h>
#include "dMem.h"
#include "dDebug.h"
#include "dDate.h"
#include "dDBase.h"
#include "dFP.h"
#include "pConfig.h"
#include "dFrame.h"
#include "dControl.h"
#include "dGUI.h"
#include "dScan.h"
#include "pGuiResource.h"
#include "pStbMenus.h"
#include "pMem.h"
#include "pStb.h"
#include "atv_dvbc_manual_scan_window.c"

#define DEF_FEND_TYPE D_FEND_DVBC


/*前端定期检查定时器*/
#define D_FEND_CHECK_TIME   (500)


#define MSG_BUFFER_LEN      (256)
#define LABEL_BUFF_SIZE     (16)
#define MODE_MAX_CNT         (8)

#define MAX_SEARCH_FREQ (874)
#define MIN_SEARCH_FREQ (47)

typedef struct
{
    D_FEndMod mode;
    D_Char strmode[LABEL_BUFF_SIZE];
} D_Mode;


static D_Mode fendMode[] =
{
//  {D_FEND_QAM16, "QAM16"},
//  {D_FEND_QAM32, "QAM32"},
    {D_FEND_QAM64, "QAM64"},
    {D_FEND_QAM128, "QAM128"},
    {D_FEND_QAM256, "QAM256"},
};



/* @brief 菜单内部数据*/
typedef struct
{
    D_HFMan     hfman;
    D_HTimer    fend_timer;
    D_FEndParam fendparam;                          /**< 频点信息*/
    D_FEndType   fendtype;                          /**< 前端类型*/
    D_Bool      locked;                             /**< 是否锁住*/
    D_U8        strength;                           /**< 信号强度*/
    D_U8        quanlity;                           /**< 信号质量*/
    D_Char      freq_lab[LABEL_BUFF_SIZE];          /**< 频率标签显示数据*/
    D_Char      freq_baud[LABEL_BUFF_SIZE];         /**< 符号率显示数据*/
    D_Char      *mode_content[MODE_MAX_CNT];
    D_U8        mode_cnt;

    D_Char      msg[MSG_BUFFER_LEN];                /**< 显示信息存储区*/
} D_ScanMenuData;


/** @brief 菜单内部数据指针*/
static D_ScanMenuData   *prog_data = NULL;
static D_FEndParam  manual_fendparam = {0};

static D_Bool signal_detect_menu = D_FALSE;
static D_FEndParam  detect_fendparam = {0};




/*显示频点信息*/
static D_Result
show_freq_info(D_FEndParam param)
{
    D_Frame *frm = &atv_dvbc_manual_scan_window;
    D_Visual    *vis;
    D_U16 val;

    vis = d_frame_get_control (frm, ID_INPUT_FREQ);
    if (vis)
    {
        sprintf(prog_data->freq_lab, "%03d", param.freq);
        d_input_box_set_text(vis, prog_data->freq_lab, strlen(prog_data->freq_lab));
    }

		vis = d_frame_get_control (frm, ID_INPUT_BAUD);
	    if (vis)
	    {
	        sprintf(prog_data->freq_baud, "%04d", param.dvbc.baud);
	        d_input_box_set_text(vis, prog_data->freq_baud, strlen(prog_data->freq_baud));
	    }

	    vis = d_frame_get_control (frm, ID_SELECT_MODE);
	    if (vis)
	    {
	        for(val = 0; val < prog_data->mode_cnt; val++)
	        {
	            if(param.dvbc.mod == fendMode[val].mode)
	            {
	                d_select_box_set_val(vis, val);
	                break;
	            }
	        }
	    }
    return D_OK;
}

/*显示信号信息(强度与质量)*/
static D_Result
show_signal_status(D_Bool locked, D_U8 strength, D_U8 quality)
{
    D_Frame *frm = &atv_dvbc_manual_scan_window;
    D_Visual    *vis;
    D_U16   frontcolourid;

    strength = D_MIN(strength, 100);
    quality = D_MIN(quality, 100);
    frontcolourid = (locked) ? ((D_U16) - 1) : ID_COLOUR_RED;

    vis = d_frame_get_control (frm, ID_PROGRESS_STRENGTH);
    if (vis)
    {
        d_progress_bar_set_front_colour(vis, frontcolourid);
        d_progress_bar_set_val(vis, strength);
    }

    vis = d_frame_get_control (frm, ID_PROGRESS_QUALYTY);
    if (vis)
    {
        d_progress_bar_set_front_colour(vis, frontcolourid);
        d_progress_bar_set_val(vis, quality);
    }

    return D_OK;
}


/*设置前端参数*/
static D_Result set_fend_param(D_Bool first, D_Visual *cvis)D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_dvbc_manual_scan_window;
    D_FEndParam param = {0};
    D_Visual *vis;
    D_U32    val = 0;

    vis = d_frame_get_control (frm, ID_INPUT_FREQ);
    if (vis)
    {
        val = (D_U32)d_input_box_get_num(vis);
        param.freq = val;
    }
		vis = d_frame_get_control (frm, ID_INPUT_BAUD);
	    if (vis)
	    {
	        val = (D_U32)d_input_box_get_num(vis);
	        param.dvbc.baud = val;
	    }

	    vis = d_frame_get_control (frm, ID_SELECT_MODE);
	    if (vis)
	    {
	        val = (D_U32)((D_U16)d_select_box_get_val(vis));
	        param.dvbc.mod = fendMode[val].mode;
	    }
    if (first || (D_FALSE == d_fend_param_equal (prog_data->fendtype, &(prog_data->fendparam), &param)))
    {
        prog_data->fendparam = param;
        d_fman_set_param(prog_data->hfman, &prog_data->fendparam, D_FALSE, prog_data->fendtype, NULL, NULL);
        d_fman_get_status_req (prog_data->hfman, d_gui_get_queue ());
        d_timer_reset(prog_data->fend_timer, D_FEND_CHECK_TIME);
    }

    return D_OK;
}

static D_Result
param_change_handler(D_Visual *vis, D_Event *evt)
{
    switch (evt->type)
    {
        case D_EVT_SELECTED:
        case D_EVT_DATA_CHANGED:
            set_fend_param(D_FALSE, vis);
            return D_OK;
        default:
            break;
    }

    return D_ERR;
}

/** @brief 事件处理*/
static D_Result
atv_dvbc_manual_scan_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:

            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_MENU:
				case D_KEY_PNL_MENU:
                case D_KEY_BACK:
                    p_stb_player_play_valid (0);
                    d_gui_upper_menu ();
                    break;
                default:
                    break;
            }
            return D_OK;
            break;
        case D_EVT_TIMER:
            if(prog_data->hfman != D_INVALID_HANDLE)
            {
                d_fman_get_status_req (prog_data->hfman, d_gui_get_queue ());
            }
            return D_OK;
            break;
        case D_EVT_FEND_STATUS:
            if(prog_data->fendparam.freq > MAX_SEARCH_FREQ || prog_data->fendparam.freq < MIN_SEARCH_FREQ)
            {
                /*非法频点显示0 0 0*/
                return show_signal_status(0, 0, 0);
            }
            else
            {
                return show_signal_status(evt->fend.status.locked, evt->fend.status.strength, evt->fend.status.quanlity);
            }
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            d_fman_clear_status_req(prog_data->hfman, d_gui_get_queue ());
            if(signal_detect_menu == D_FALSE)
            {
                manual_fendparam = prog_data->fendparam;
            }
            else
            {
                detect_fendparam = prog_data->fendparam;
            }

            if(prog_data->fend_timer != D_INVALID_HANDLE)
            {
                d_timer_destroy(prog_data->fend_timer);
                prog_data->fend_timer = D_INVALID_HANDLE;
            }

            if(prog_data)
            {
                PROJECT_FREE(prog_data);
                prog_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}


/** @brief 窗口初始化*/
D_Result
atv_dvbc_manual_scan_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual        *vis;
    D_U8    idx;
    D_U8    mode_cnt;
    D_SIParam si_param;

    prog_data = (D_ScanMenuData*)PROJECT_ALLOC(sizeof(D_ScanMenuData));
    if(!prog_data)
    {
        return D_ERR;
    }

    memset(prog_data, 0x00, sizeof(D_ScanMenuData));
    prog_data->fend_timer = D_INVALID_HANDLE;
    prog_data->fendtype = DEF_FEND_TYPE;
    p_conf_get_si_param(&si_param);

    if(signal_detect_menu == D_FALSE && manual_fendparam.freq > 0)
    {
        prog_data->fendparam = manual_fendparam;
    }
    else if(signal_detect_menu == D_TRUE && detect_fendparam.freq > 0)
    {
        prog_data->fendparam = detect_fendparam;
    }
    else
    {
        if(si_param.main.freq > MAX_SEARCH_FREQ || si_param.main.freq < MIN_SEARCH_FREQ)
        {
            prog_data->fendparam.freq = 474;
            prog_data->fendparam.dvbc.baud = 6875;
            prog_data->fendparam.dvbc.mod = D_FEND_QAM64;
        }
        else
        {
            prog_data->fendparam.freq = si_param.main.freq;
            prog_data->fendparam.dvbc.baud = si_param.main.baud;
            prog_data->fendparam.dvbc.mod = si_param.main.mod;
        }
    }

    prog_data->mode_cnt = sizeof(fendMode) / sizeof(fendMode[0]);
    for(idx = 0; idx < prog_data->mode_cnt; idx++)
    {
        prog_data->mode_content[idx] = fendMode[idx].strmode;
    }

    prog_data->hfman = d_fman_get_handle_by_type(prog_data->fendtype, 0);

    /*因为有信号的锁定，要停播*/
    d_stb_stop_play();
    /*清除残留视频帧*/
    p_stb_player_clear_vid(0);

    vis = d_frame_get_control (frm, ID_INPUT_FREQ);
    if (vis)
    {
        d_vis_set_handler(vis, param_change_handler);
    }

		vis = d_frame_get_control (frm, ID_INPUT_BAUD);
	    if (vis)
	    {
	        d_vis_set_handler(vis, param_change_handler);
	    }

	    vis = d_frame_get_control (frm, ID_SELECT_MODE);
	    if (vis)
	    {
	        d_vis_set_handler(vis, param_change_handler);
	        d_select_box_set_content(vis, prog_data->mode_content, prog_data->mode_cnt);
	    }
	

    show_freq_info(prog_data->fendparam);
    show_signal_status(D_FALSE, 0, 0);

    set_fend_param(D_TRUE, NULL);

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK | D_EVT_FEND_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_dvbc_manual_scan_window_handler);

        /*创建前端定期检查定时器*/
        prog_data->fend_timer = d_timer_create (NULL, D_FEND_CHECK_TIME, d_gui_get_queue ());
        if(prog_data->fend_timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, prog_data->fend_timer);
        }
    }

    return D_OK;
}

/** @breif 显示信号检测窗口*/
D_Result
p_atv_dvbc_signal_detect_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_dvbc_manual_scan_window, D_TRUE);
}

