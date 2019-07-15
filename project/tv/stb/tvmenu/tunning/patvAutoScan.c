#include "pConfig.h"
#include "dFrame.h"
#include "dControl.h"
#include "dGUI.h"
#include "dScan.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "pPlayer.h"
#include "dDBase.h"
#include "dTV.h"
#include "pStbScan.h"
#include "auto_scan_window.c"

/*前端定期检查定时器*/
#define D_FEND_CHECK_TIME   (500)

#define MSG_BUFFER_LEN      (256)
#define LABEL_BUFF_SIZE     (16)
#define MODE_MAX_CNT         (8)

#define MAX_SEARCH_FREQ (874)
#define MIN_SEARCH_FREQ (47)


/* @brief 菜单内部数据*/
typedef struct
{
    D_StbPlayer		*player; 
	D_U32   		menu_type;
	D_HFMan     hfman;
    D_HTimer    fend_timer;
	D_HScan		hscan;								/**< 搜索句柄*/	
    D_FEndParam fendparam;                          /**< 频点信息*/
    D_FEndType   fendtype;                          /**< 前端类型*/
    D_Bool      locked;                             /**< 是否锁住*/
    D_U8        quanlity;                           /**< 信号质量*/
	D_Bool		scanning_flag;
	D_Bool		save_flag;
	D_Bool		got_srv_flag;
    D_Char      freq_lab[LABEL_BUFF_SIZE];          /**< 频率标签显示数据*/

    D_Char      msg[MSG_BUFFER_LEN];                /**< 显示信息存储区*/

	D_U16 		tv_cnt;
	D_U16 		radio_cnt;
	D_Char 		tv_buf[4];
	D_Char 		radio_buf[4];
} D_AtvaAutoScanData;


/** @brief 菜单内部数据指针*/
static D_AtvaAutoScanData   *prog_data = NULL;
static D_ScanTaskConfig ScanConfig = {0};

static D_Ptr AutoScan_Op;
//static D_KeyCode filter_keys[] = {D_KEY_POWER,D_KEY_PNL_POWER, D_KEY_MENU,D_KEY_PNL_MENU,D_KEY_ESC,D_KEY_PNL_ESC, D_KEY_MUTE, D_KEY_VOLUME_PLUS, D_KEY_VOLUME_MINUS};

/*显示频点信息*/
static D_Result
show_freq_info(D_FEndParam param)
{
    D_Frame *frm = &auto_scan_window;
    D_Visual    *vis;
    D_U16 val;

    vis = d_frame_get_control (frm, ID_AUTO_SCAN_LABEL_FREQ_NUM);
    if (vis)
    {
	        if(ScanConfig.fend_type = D_FEND_DTMB && param.dtmb.freq_k)
	        {
	            sprintf(prog_data->freq_lab, "%d.%d MHz", param.freq, param.dtmb.freq_k);
	        }
	        else
	        {
	            sprintf(prog_data->freq_lab, "%d MHz", param.freq);
	        }
		d_label_set_text(vis, prog_data->freq_lab);
    }
    return D_OK;
}

/*显示信号信息(强度与质量)*/
static D_Result
show_signal_status(D_Bool locked, D_U8 strength, D_U8 quality)
{
    D_Frame *frm = &auto_scan_window;
    D_Visual    *vis;

    quality = D_MIN(quality, 100);
	
    vis = d_frame_get_control (frm, ID_AUTO_SCAN_PROGRESS_SCAN);
    if (vis)
    {
        d_progress_bar_set_val(vis, quality);
    }

	vis = d_frame_get_control (frm, ID_AUTO_SCAN_LABEL_SIGNAL);
    if (vis)
    {
        if(locked)
        {
			d_vis_show(vis, D_FALSE);
		}
		else
		{
			d_vis_show(vis, D_TRUE);
			d_label_set_text(vis, d_gui_get_text(atv_IDS_NO_SIGNAL));
		}
    }

    return D_OK;
}

/*开始节目自动搜索*/
static D_Result
start_scan(D_Visual *vis)D_FUNCPOSTFIT
{
	D_ScanTaskConfig config = ScanConfig;

	/*停止表监控*/
    d_tv_scan_si(prog_data->player->htv, 0);
	
	prog_data->scanning_flag = D_FALSE;
	prog_data->tv_cnt = 0;
	prog_data->radio_cnt = 0;
	prog_data->save_flag = D_FALSE;
	prog_data->got_srv_flag = D_FALSE;

	config.db_sat_id = -1;
	config.sdt_srv_type_en = D_TRUE;

	config.buf_size = 512 * 1024;
    config.hqueue = d_gui_get_queue();
    config.parse_mode = D_SCAN_PARSE_TP;
    config.priority = D_AUTO_SCAN_TASK_PRIO;
    config.scan_type = prog_data->menu_type;
    config.srv_name_en = D_TRUE;
    config.hfman = d_fman_get_handle_by_type(config.fend_type, 0);
	if(p_conf_get_scan_config())
	{
		AutoScan_Op = (D_Ptr)(&DVBC_AutoScan_Op);
	}
	else
	{
		AutoScan_Op = (D_Ptr)(&DVBT_AutoScan_Op);
	}
	config.pScanOp = AutoScan_Op;
	prog_data->hscan = d_auto_scan_create(config);	
	if (prog_data->hscan != D_INVALID_HANDLE)
	{
		d_vis_subscribe_evt (vis, D_EVT_SCAN_MASK, prog_data->hscan);
		prog_data->scanning_flag = D_TRUE;
	}	

	D_DUMP("start_scan\n");
	return D_OK;
}


/*搜素默认播放第一个电视节目*/
static D_Result
update_play_prog(void)D_FUNCPOSTFIT
{
	D_StbPlayer *player;
	D_DBSrvInfo	srv_info;
	D_DBTSID	db_ts_id;
	D_DBRecset rset_tv;
	D_DBID	ids_tv[1] = {-1};
    D_SIParam si_param;
    D_FEndParam mainparam;
	
	player = p_stb_get_player (0);
	if (! player)
		return D_ERR;
	
	player->play_radio = D_FALSE;
	player->tv_id = -1;	
	player->tv_num = -1;
	
	
	D_DUMP("pScanwin update prog num!\n");
	return D_OK;
}

/** @brief 结束搜索过程*/
static D_Result scan_end (D_U32 save)
{	
	D_Frame *frm = &auto_scan_window;
	D_Visual *vis;
	
	prog_data->scanning_flag = D_FALSE;
	prog_data->save_flag = save ? D_TRUE : D_FALSE;
    prog_data->scanning_flag = D_FALSE;

	/*保存搜索的节目*/
    if (prog_data->hscan != D_INVALID_HANDLE)
    {
        d_auto_scan_destroy (prog_data->hscan, prog_data->save_flag);
        prog_data->hscan = D_INVALID_HANDLE;
    }

	vis = d_frame_get_control(frm, ID_AUTO_SCAN_LABEL_SIGNAL);
	if(vis)
	{
		d_vis_show(vis, D_FALSE);
	}

    if(prog_data->save_flag && prog_data->got_srv_flag)
    {
        /*搜索结束后默认播放第一个电视节目*/
        update_play_prog();
    }
	
	return D_OK;
}


/** @brief 显示搜索结果*/
static D_Result show_scan_result (D_Visual *vis, D_U16 prog_cnt, D_U16 tv_cnt, D_U16 radio_cnt)
{
	D_Result ret = D_ERR;
	D_Frame *frm = &auto_scan_window;

	D_Visual *vis_prog;

	D_DUMP("scan_result : tv %d, radio %d\n", tv_cnt, radio_cnt);
	
	if (prog_data->hscan != D_INVALID_HANDLE) 
	{
		d_vis_unsubscribe_one_evt(vis, D_EVT_SCAN_MASK, prog_data->hscan);
	}

	if((tv_cnt + radio_cnt) == 0)
	{
		scan_end(1);
	}
	else  
	{
		prog_data->got_srv_flag = D_TRUE;
		vis_prog = d_frame_get_control(frm, ID_AUTO_SCAN_LABEL_RADIO_NUM);
		if(vis_prog)
		{
			sprintf(prog_data->radio_buf, "%03d", prog_data->radio_cnt);
			d_label_set_text(vis_prog, prog_data->radio_buf);
		}
		
		vis_prog = d_frame_get_control(frm, ID_AUTO_SCAN_LABEL_TV_NUM);
		if(vis_prog)
		{	
			sprintf(prog_data->tv_buf, "%03d", prog_data->tv_cnt);
			d_label_set_text(vis_prog,prog_data->tv_buf);
		} 

		d_gui_update(); 
		scan_end(1);
	}
	d_gui_clear_menu();
	
	return D_OK;
}

/**@brief 显示搜索到的节目个数*/
static D_Result show_prog_number (D_Visual *vis, D_U32 type)
{
	D_Frame *frm = &auto_scan_window;

	D_Visual *vis_prog;

	if(type != D_DB_SRV_TV && type != D_DB_SRV_RADIO)
		return D_OK;

	if(type == D_DB_SRV_TV)
	{
		prog_data->tv_cnt ++;
	}
	if(type == D_DB_SRV_RADIO)
	{
		prog_data->radio_cnt ++;
	}

	vis_prog = d_frame_get_control(frm, ID_AUTO_SCAN_LABEL_RADIO_NUM);
	if(vis_prog)
	{
		sprintf(prog_data->radio_buf, "%03d", prog_data->radio_cnt);
		d_label_set_text(vis_prog, prog_data->radio_buf);
	}
	
	vis_prog = d_frame_get_control(frm, ID_AUTO_SCAN_LABEL_TV_NUM);
	if(vis_prog)
	{	
		sprintf(prog_data->tv_buf, "%03d", prog_data->tv_cnt);
		d_label_set_text(vis_prog,prog_data->tv_buf);
	} 
	
	return D_OK;
}

/** @brief 事件处理*/
static D_Result
auto_scan_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
   D_Frame *frm = &auto_scan_window;
   
   switch (evt->type)
    {
        case D_EVT_FP:

            switch (evt->fp.key)
            {
				case D_KEY_ESC:
				case D_KEY_PNL_ESC:
                case D_KEY_PNL_MENU:
				case D_KEY_MENU:
                    d_gui_clear_menu ();
                    break;
                case D_KEY_BACK:
                    p_stb_player_play_valid (0);
                    d_gui_upper_menu ();
                    break;
                case D_KEY_MUTE:
                case D_KEY_VOLUME_PLUS:
                case D_KEY_VOLUME_MINUS:
                    return D_ERR;
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
        case D_EVT_SCAN_FEND_STATUS:
            return show_signal_status(evt->scan.fendstatus.locked, evt->scan.fendstatus.strength, evt->scan.fendstatus.quanlity);
            break;
		/*搜索完毕*/
		 case D_EVT_SCAN_FREQ:
            if (evt->scan.fendparam.freq != prog_data->fendparam.freq)
            {
                prog_data->fendparam = evt->scan.fendparam;
                show_freq_info(prog_data->fendparam);
            }
            return D_OK;
		case D_EVT_SCAN_OK:	
			show_scan_result(vis, evt->scan.prog_cnt, evt->scan.tv_cnt, evt->scan.radio_cnt);
			break;
		case D_EVT_SCAN_DATA:
			show_prog_number(vis, evt->scan.srvinfo.srv_type);
			return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            if(prog_data)
            {  
                if(prog_data->hscan != D_INVALID_HANDLE)
                {
                    scan_end(1);
                }
                
                d_fman_clear_status_req(prog_data->hfman, d_gui_get_queue ());
    			//p_fp_set_filter_keys(&filter_keys, 0xfffff);
                if(prog_data->fend_timer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(prog_data->fend_timer);
                    prog_data->fend_timer = D_INVALID_HANDLE;
                }

            	d_tv_scan_si(prog_data->player->htv, D_TV_SCAN_ALL);  

    			d_tv_set_vid_window(prog_data->player->htv,0,0, -1, -1);
    			p_stb_player_play_valid (0);           
                PROJECT_FREE(prog_data);
                prog_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;
}


D_Result
auto_scan_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
	D_Visual        *vis;
    D_U8    idx;
    D_U8    mode_cnt;
    D_SIParam si_param;

    prog_data = (D_AtvaAutoScanData*)PROJECT_ALLOC(sizeof(D_AtvaAutoScanData));
    if(!prog_data)
    {
        return D_ERR;
    }
	p_conf_get_si_param(&si_param);
    memset(prog_data, 0x00, sizeof(D_AtvaAutoScanData));
    prog_data->fend_timer = D_INVALID_HANDLE;

	prog_data->fendparam.freq = si_param.main.freq;
	
	if(p_conf_get_scan_config())
    {
		prog_data->fendtype = D_FEND_DVBC;
	    prog_data->fendparam.dvbc.baud = si_param.main.baud;
	    prog_data->fendparam.dvbc.mod = si_param.main.mod;        
    }
    else
    {
		prog_data->fendtype = D_FEND_DTMB;
    }
	prog_data->menu_type = STB_SCAN_TYPE_AUTO;
	prog_data->player = p_stb_get_player (0);

    prog_data->hfman = d_fman_get_handle_by_type(prog_data->fendtype, 0);

	ScanConfig.fend_type = prog_data->fendtype;
   	ScanConfig.fend_param = prog_data->fendparam;

#ifdef D_TV_SUPPORT_TS2NET
    ts2net_check_enable = D_FALSE;
    d_ts2net_close();
#endif

    /*因为有信号的锁定，要停播*/
    d_stb_stop_play();
    /*清除残留视频帧*/
    p_stb_player_clear_vid(0);
	/*设定界面响应的按键*/
	//p_fp_set_filter_keys(&filter_keys, sizeof(filter_keys)/sizeof(filter_keys[0]));

    show_freq_info(prog_data->fendparam);
    show_signal_status(D_FALSE, 0, 0);

	vis = d_frame_get_control(frm, ID_AUTO_SCAN_LABEL_TV_NUM);
	if(vis)
	{
		d_label_set_text(vis, "000");
	}
	vis = d_frame_get_control(frm, ID_AUTO_SCAN_LABEL_RADIO_NUM);
	if(vis)
	{
		d_label_set_text(vis, "000");
	}	

	vis = d_frame_get_control(frm, ID_AUTO_SCAN_LABEL_SIGNAL);
	if(vis)
	{
		d_label_set_text(vis, d_gui_get_text(atv_IDS_SCANNING));
	}
		
    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK | D_EVT_AUDIO_KEY_MASK | D_EVT_PROGRAM_PLUS_MINUS_KEY_MASK | D_EVT_FEND_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, auto_scan_window_handler);

        /*创建前端定期检查定时器*/
        prog_data->fend_timer = d_timer_create (NULL, D_FEND_CHECK_TIME, d_gui_get_queue ());
        if(prog_data->fend_timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, prog_data->fend_timer);
        }
		start_scan(vis);

    }

    return D_OK;
}

/** @breif 显示手动搜索界面*/
D_Result
p_atv_auto_scan_window_show (void) D_FUNCPOSTFIT
{
	return d_gui_enter_menu (&auto_scan_window, D_TRUE);
}
