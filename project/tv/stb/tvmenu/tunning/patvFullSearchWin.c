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
#include "atv_full_search_window.c"

#define MSG_BUFFER_LEN      (256)
#define SRV_NAME_MAX_LEN    D_DB_SERVICE_NAME_LEN
#define LABEL_BUFF_SIZE     (16)
#define D_SHOW_PROG_CNT     (4)

#define P_SHOW_TIME (5000)

/* @brief 菜单内部数据*/
typedef struct
{
    D_StbPlayer     *player;
    D_U32           menu_type;
    D_HFMan     hfman;
    D_HScan     hscan;                              /**< 搜索句柄*/
    D_FEndParam fendparam;                          /**< 频点信息*/
    D_FEndType   fendtype;                          /**< 前端类型*/
    D_Char      freq_lab[16];          /**< 频率标签显示数据*/

    D_Bool      scanning_flag;
    D_Bool      save_flag;
    D_Bool      got_srv_flag;
    D_Char      msg[MSG_BUFFER_LEN];                /**< 显示信息存储区*/

    D_U16       tv_cnt;
    D_U16       radio_cnt;
    D_U16       prog_cnt;
    D_Char      tv_buf[4];
    D_Char      radio_buf[4];
    D_Char      progress_val[10];


} D_ScanMenuData;


/** @brief 菜单内部数据指针*/
static D_ScanMenuData   *prog_data = NULL;
static D_U32   ScanMenuType = 0;
static D_ScanTaskConfig ScanConfig = {0};
static D_Ptr AutoScan_Op;
//static D_KeyCode filter_keys[] = {D_KEY_POWER, D_KEY_PNL_POWER, D_KEY_MENU, D_KEY_PNL_MENU, D_KEY_ESC, D_KEY_PNL_ESC, D_KEY_MUTE, D_KEY_VOLUME_PLUS, D_KEY_VOLUME_MINUS};
static D_Result scan_end (D_U32 save);

/*显示频率信息*/
static D_Result show_freq_info(D_FEndParam param)D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_full_search_window;
    D_Visual *vis;

    vis = d_frame_get_control (frm, ID_FULL_SCAN_LEBEL_FREQ);
    if(vis)
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

/** @brief 设置搜索进度*/
static D_Result set_progress (D_U16 prog) D_FUNCPOSTFIT
{
    D_Frame     *frm = &atv_full_search_window;
    D_Visual    *vis;

    /*设定进度条*/
    vis = d_frame_get_control (frm, ID_FULL_SCAN_PROGRESS_SCAN);
    if (vis)
    {
        d_progress_bar_set_val (vis, prog);
    }

    vis = d_frame_get_control (frm, ID_FULL_SCAN_LABEL_PROGRESS);
    if (vis)
    {
        sprintf(prog_data->progress_val, "%3d %%", prog);
        d_label_set_text(vis, prog_data->progress_val);
    }

    return D_OK;
}

static D_Result
stopScan_callback(D_Bool sel, D_U32 param)D_FUNCPOSTFIT
{
    if(sel)
    {
        scan_end(1);
        d_gui_upper_menu();
    }
    else
    {
        //p_fp_set_filter_keys(&filter_keys, sizeof(filter_keys)/sizeof(filter_keys[0]));
    }
    return D_OK;
}

/*开始节目自动搜索*/
static D_Result
start_scan(D_Visual *vis)D_FUNCPOSTFIT
{
    D_ScanTaskConfig config = ScanConfig;

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
    prog_data->hfman = config.hfman;
    if(p_conf_get_scan_config())
    {
        config.fend_type = D_FEND_DVBC;
        AutoScan_Op = (D_Ptr)(&DVBC_AutoScan_Op);
    }
    else
    {
        config.fend_type = D_FEND_DTMB;
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
    D_DBSrvInfo srv_info;
    D_DBTSID    db_ts_id;
    D_DBRecset rset_tv;
    D_DBID  ids_tv[1] = { -1};
    D_SIParam si_param;
    D_FEndParam mainparam;

    player = p_stb_get_player (0);
    if (! player)
        return D_ERR;

    player->play_radio = D_FALSE;
    player->tv_id = -1;
    player->tv_num = -1;
    player->prev_tv_id= -1;

    D_DUMP("pScanwin update prog num!\n");
    return D_OK;
}

/** @brief 结束搜索过程*/
static D_Result scan_end (D_U32 save)
{
    prog_data->scanning_flag = D_FALSE;
    prog_data->save_flag = save ? D_TRUE : D_FALSE;

    if (prog_data->hscan != D_INVALID_HANDLE)
    {
        d_auto_scan_destroy (prog_data->hscan, prog_data->save_flag);
        prog_data->hscan = D_INVALID_HANDLE;
    }

    if(prog_data->save_flag && prog_data->got_srv_flag)
    {
        /*搜索结束后默认播放第一个电视节目*/
        update_play_prog();
    }
    return D_OK;
}

/** @brief 显示搜索结果*/
static D_Result show_scan_result (D_Visual *vis, D_U16 tv_cnt, D_U16 radio_cnt)
{
    D_Result ret = D_ERR;
    D_Frame *frm = &atv_full_search_window;

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
        vis_prog = d_frame_get_control(frm, ID_FULL_SCAN_LABEL_RADIO_NUM);
        if(vis_prog)
        {
            sprintf(prog_data->radio_buf, "%03d", prog_data->radio_cnt);
            d_label_set_text(vis_prog, prog_data->radio_buf);
        }

        vis_prog = d_frame_get_control(frm, ID_FULL_SCAN_LABEL_TV_NUM);
        if(vis_prog)
        {
            sprintf(prog_data->tv_buf, "%03d", prog_data->tv_cnt);
            d_label_set_text(vis_prog, prog_data->tv_buf);
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
    D_Frame *frm = &atv_full_search_window;

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

    vis_prog = d_frame_get_control(frm, ID_FULL_SCAN_LABEL_RADIO_NUM);
    if(vis_prog)
    {
        sprintf(prog_data->radio_buf, "%03d", prog_data->radio_cnt);
        d_label_set_text(vis_prog, prog_data->radio_buf);
    }

    vis_prog = d_frame_get_control(frm, ID_FULL_SCAN_LABEL_TV_NUM);
    if(vis_prog)
    {
        sprintf(prog_data->tv_buf, "%03d", prog_data->tv_cnt);
        d_label_set_text(vis_prog, prog_data->tv_buf);
    }

    return D_OK;
}


/** @brief 事件处理*/
static D_Result
tv_scan_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &atv_full_search_window;

    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_MENU:
                case D_KEY_PNL_MENU:
                    //  0xfffff
                    //p_fp_set_filter_keys(&filter_keys, 0xfffff);
                    if(prog_data->hscan != D_INVALID_HANDLE)
                    {
                        d_atv_pop_select_center_show(4, D_GUI_LAYER_MESSAGE, NULL,
                            d_gui_get_text(atv_IDS_END_ALL_SCAN), P_SHOW_TIME, D_FALSE, stopScan_callback, 0) ;
                    }
                    else
                    {
                        d_gui_upper_menu();
                    }
                    break;
                case D_KEY_BACK:
                    if(prog_data->hscan != D_INVALID_HANDLE)
                    {
                        scan_end (1);
                    }
                    d_gui_upper_menu();
                    break;
                case D_KEY_MUTE:
                case D_KEY_VOLUME_PLUS:
                case D_KEY_VOLUME_MINUS:
                    return D_ERR;
                default:
                    return D_OK;
            }
            return D_OK;
        /*更新搜索进度*/
        case D_EVT_SCAN_PROGRESS:
            return set_progress (evt->scan.progress);
        /*搜索完毕*/
        case D_EVT_SCAN_FREQ:
            if (evt->scan.fendparam.freq != prog_data->fendparam.freq)
            {
                prog_data->fendparam = evt->scan.fendparam;
                show_freq_info(prog_data->fendparam);
            }
            return D_OK;
        case D_EVT_SCAN_OK:
            show_scan_result(vis, evt->scan.tv_cnt, evt->scan.radio_cnt);
            break;
        case D_EVT_SCAN_DATA:
            show_prog_number(vis, evt->scan.srvinfo.srv_type);
            return D_OK;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt (vis);
            //p_fp_set_filter_keys(&filter_keys, 0xfffff);
            if(prog_data)
            {
                if(prog_data->hscan != D_INVALID_HANDLE)
                {
                    scan_end(1);
                }
                d_fman_clear_status_req(prog_data->hfman, d_gui_get_queue ());
                p_stb_player_play_valid (0);
                /*恢复表监控*/
                d_tv_scan_si(prog_data->player->htv, D_TV_SCAN_ALL);
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
atv_full_search_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual        *vis;

    prog_data = (D_ScanMenuData*)PROJECT_ALLOC(sizeof(D_ScanMenuData));
    if(!prog_data)
    {
        return D_ERR;
    }

    memset(prog_data, 0x00, sizeof(D_ScanMenuData));

    prog_data->hscan = D_INVALID_HANDLE;
    prog_data->hfman = D_INVALID_HANDLE;
    prog_data->menu_type = ScanMenuType;
    prog_data->fendparam = ScanConfig.fend_param;
    prog_data->fendtype = ScanConfig.fend_type;
    prog_data->player = p_stb_get_player (0);

    if (! (prog_data->player))
    {
        PROJECT_FREE(prog_data);
        prog_data = NULL;
        return D_ERR;
    }

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

    /*停止表监控*/
    d_tv_scan_si(prog_data->player->htv, 0);

    vis = d_frame_get_control(frm, ID_FULL_SCAN_LABEL_TV_NUM);
    if(vis)
    {
        d_label_set_text(vis, "000");
    }
    vis = d_frame_get_control(frm, ID_FULL_SCAN_LABEL_RADIO_NUM);
    if(vis)
    {
        d_label_set_text(vis, "000");
    }

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK | D_EVT_AUDIO_KEY_MASK | D_EVT_PROGRAM_PLUS_MINUS_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, tv_scan_window_handler);
        start_scan(vis);
    }

    return D_OK;
}

/** @breif 显示搜索界面*/
D_Result
p_full_search_window_show (D_StbScanType type, D_ScanTaskConfig *scan_config) D_FUNCPOSTFIT
{

    if(type < STB_SCAN_TYPE_OTHERS)
    {
        ScanMenuType = (D_U32)type;
        if(scan_config)
        {
            ScanConfig = *scan_config;
        }

        return d_gui_enter_menu (&atv_full_search_window, D_TRUE);
    }

    return D_ERR;
}

/** @breif 显示搜索界面*/
D_Result
p_full_search_window_hide (void) D_FUNCPOSTFIT
{
    scan_end(1);
    return D_ERR;
}

