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
#include "manual_scan_window.c"

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
    D_StbPlayer     *player;
    D_U32           menu_type;
    D_HFMan     hfman;
    D_HTimer    fend_timer;
    D_HScan     hscan;                              /**< 搜索句柄*/
    D_FEndParam fendparam;                          /**< 频点信息*/
    D_FEndType   fendtype;                          /**< 前端类型*/
    D_Bool      locked;                             /**< 是否锁住*/
//   D_U8        strength;                           /**< 信号强度*/
    D_U8        quanlity;                           /**< 信号质量*/
    D_Bool      scanning_flag;
    D_Bool      save_flag;
    D_Bool      got_srv_flag;
    D_Char      freq_lab[LABEL_BUFF_SIZE];          /**< 频率标签显示数据*/
    D_Char      freq_lab1[LABEL_BUFF_SIZE];          /**< 频率标签显示数据*/
    D_Char      vuhf[LABEL_BUFF_SIZE];
    D_Char      msg[MSG_BUFFER_LEN];                /**< 显示信息存储区*/

    D_U16       tv_cnt;
    D_U16       radio_cnt;
    D_Char      tv_buf[4];
    D_Char      radio_buf[4];

    D_Visual    *freq_index_vis;
    D_Visual    *freq_num_vis;
    D_Visual    *vuhf_vis;

} D_AtvManualScanData;

typedef struct
{
    D_U16   Show_key_val1; //个位
    D_U16   Show_key_val2;//十位
    D_U16   Show_key_val_ex;//扩展位
    D_U8    input_step1;
    D_U8    input_step2;
    D_U8    input_step3;
    D_U8    input_finished;
} Input_key;

typedef struct
{
    D_U8 major_num;
    D_U8 minor_num;
    D_U16 major_freq;
    D_U16 minor_freq;
    D_Char *ch_name;
} D_TvFreqWave;


/** @brief 菜单内部数据指针*/
static D_AtvManualScanData   *prog_data = NULL;
static D_ScanTaskConfig ScanConfig = {0};

static D_Ptr ManualScan_Op;
//static D_KeyCode filter_keys[] = {D_KEY_POWER, D_KEY_PNL_POWER, D_KEY_MENU, D_KEY_PNL_MENU, D_KEY_ESC, D_KEY_PNL_ESC, D_KEY_MUTE, D_KEY_VOLUME_PLUS, D_KEY_VOLUME_MINUS};

static D_S16    Freq_num_index = 0;
static Input_key g_input_key = {0};

D_TvFreqWave TvFreqWave[] =
{
    { 1, 0, 52,  5, "DS-1"},  { 2, 0, 60,  5, "DS-2"},  { 3, 0, 68,  5, "DS-3"},  { 4, 0, 80,  0, "DS-4"},  { 5, 0, 88,  0, "DS-5"},
    { 6, 0, 171, 0, "DS-6"},  { 7, 0, 179, 0, "DS-7"},  { 8, 0, 187, 0, "DS-8"},  { 9, 0, 195, 0, "DS-9"},  {10, 0, 203, 0, "DS-10"},
    {11, 0, 211, 0, "DS-11"}, {12, 0, 219, 0, "DS-12"}, {13, 0, 474, 0, "DS-13"}, {14, 0, 482, 0, "DS-14"}, {15, 0, 490, 0, "DS-15"},
    {16, 0, 498, 0, "DS-16"}, {17, 0, 506, 0, "DS-17"}, {18, 0, 514, 0, "DS-18"}, {19, 0, 522, 0, "DS-19"}, {20, 0, 530, 0, "DS-20"},
    {21, 0, 538, 0, "DS-21"}, {22, 0, 546, 0, "DS-22"}, {23, 0, 554, 0, "DS-23"}, {24, 0, 562, 0, "DS-24"}, {24, 1, 570, 0, "DS-24+1"},
    {24, 2, 578, 0, "DS-24+2"}, {24, 3, 586, 0, "DS-24+3"}, {24, 4, 594, 0, "DS-24+4"}, {24, 5, 602, 0, "DS-24+5"}, {25, 0, 610, 0, "DS-25"},
    {26, 0, 618, 0, "DS-26"}, {27, 0, 626, 0, "DS-27"}, {28, 0, 634, 0, "DS-28"}, {29, 0, 642, 0, "DS-29"}, {30, 0, 650, 0, "DS-30"},
    {31, 0, 658, 0, "DS-31"}, {32, 0, 666, 0, "DS-32"}, {33, 0, 674, 0, "DS-33"}, {34, 0, 682, 0, "DS-34"}, {35, 0, 690, 0, "DS-35"},
    {36, 0, 698, 0, "DS-36"}, {37, 0, 706, 0, "DS-37"}, {38, 0, 714, 0, "DS-38"}, {39, 0, 722, 0, "DS-39"}, {40, 0, 730, 0, "DS-40"},
    {41, 0, 738, 0, "DS-41"}, {42, 0, 746, 0, "DS-42"}, {43, 0, 754, 0, "DS-43"}, {44, 0, 762, 0, "DS-44"}, {45, 0, 770, 0, "DS-45"},
    {46, 0, 778, 0, "DS-46"}, {47, 0, 786, 0, "DS-47"}, {48, 0, 794, 0, "DS-48"}, {49, 0, 802, 0, "DS-49"}, {50, 0, 810, 0, "DS-50"},
    {51, 0, 818, 0, "DS-51"}, {52, 0, 826, 0, "DS-52"}, {53, 0, 834, 0, "DS-53"}, {54, 0, 842, 0, "DS-54"}, {55, 0, 850, 0, "DS-55"},
    {56, 0, 858, 0, "DS-56"}, {57, 0, 866, 0, "DS-57"},
};
#define VHF_MAX_FREQ (223)
#define FREQ_CNT (sizeof(TvFreqWave) / sizeof(TvFreqWave[0]))

static int
get_freq_idx_by_num(D_U8 major_num, D_U8 minor_num)
{
    int idx = -1, idx_main = -1, i;

    for(i = 0; i < FREQ_CNT; i++)
    {
        if(TvFreqWave[i].major_num == major_num)
        {
            if(idx_main == -1)
            {
                idx_main = i;
            }

            if(TvFreqWave[i].minor_num == minor_num)
            {
                idx = i;
                break;
            }
        }
    }

    return ((idx != -1) ? idx : idx_main);
}

/*显示频点信息*/
static D_Result
show_freq_info(int idx, D_Bool show_num)
{
    D_Frame *frm = &manual_scan_window;

    if(idx < 0 || idx >= FREQ_CNT)
    {
        return D_ERR;
    }

    prog_data->vuhf_vis = d_frame_get_control (frm, ID_MANUAL_SCAN_LABLE_VU);
    sprintf(prog_data->vuhf, (TvFreqWave[idx].major_freq < VHF_MAX_FREQ) ? "VHF" : "UHF");
    d_label_set_text(prog_data->vuhf_vis, prog_data->vuhf);

    if(show_num)
    {
        prog_data->freq_index_vis = d_frame_get_control (frm, ID_MANUAL_SCAN_LABLE_INDEX);
        if (prog_data->freq_index_vis)
        {
            if(TvFreqWave[idx].minor_num)
            {
                sprintf(prog_data->freq_lab, "DS-%d+%d", TvFreqWave[idx].major_num, TvFreqWave[idx].minor_num);
            }
            else
            {
                sprintf(prog_data->freq_lab, "DS-%d", TvFreqWave[idx].major_num);
            }
            d_label_set_text(prog_data->freq_index_vis, prog_data->freq_lab);
        }
    }

    prog_data->freq_num_vis = d_frame_get_control (frm, ID_MANUAL_SCAN_LABEL_FREQ_NUM);
    if (prog_data->freq_num_vis)
    {
        if(TvFreqWave[Freq_num_index].minor_freq)
        {
            sprintf(prog_data->freq_lab1, "%d.%d MHz", TvFreqWave[idx].major_freq, TvFreqWave[idx].minor_freq);
        }
        else
        {
            sprintf(prog_data->freq_lab1, "%d MHz", TvFreqWave[idx].major_freq);
        }
        d_label_set_text(prog_data->freq_num_vis, prog_data->freq_lab1);
    }
    return D_OK;
}

/*显示信号信息(强度与质量)*/
static D_Result
show_signal_status(D_Bool locked, D_U8 strength, D_U8 quality)
{
    D_Frame *frm = &manual_scan_window;
    D_Visual    *vis;

//    strength = D_MIN(strength, 100);
    quality = D_MIN(quality, 100);
    vis = d_frame_get_control (frm, ID_MANUAL_SCAN_PROGRESS_SCAN);
    if (vis)
    {
        d_progress_bar_set_val(vis, quality);
    }

    vis = d_frame_get_control (frm, ID_MANUAL_SCAN_LABEL_SIGNAL);
    if (vis)
    {
        if(prog_data->scanning_flag == D_FALSE)
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
        else
        {
            d_vis_show(vis, D_TRUE);
            d_label_set_text(vis, d_gui_get_text(atv_IDS_SCANNING));
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

    config.buf_size = 96 * 1024;
    config.hqueue = d_gui_get_queue();
    config.priority = D_MANUAL_SCAN_TASK_PRIO;
    config.scan_type = prog_data->menu_type;
    config.srv_name_en = D_FALSE;
    config.hfman = d_fman_get_handle_by_type(config.fend_type, 0);
    if(p_conf_get_scan_config())
    {
        config.fend_type = D_FEND_DVBC;
        ManualScan_Op = (D_Ptr)(&DVBC_ManualScan_Op);
    }
    else
    {
        config.fend_type = D_FEND_DTMB;
        ManualScan_Op = (D_Ptr)(&DVBT_ManualScan_Op);
    }
    config.pScanOp = ManualScan_Op;
    prog_data->hscan = d_manual_scan_create(config);
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

    db_ts_id = d_dbase_get_ts_by_param (0, ScanConfig.fend_type, &(ScanConfig.fend_param));
    if(db_ts_id >= 0)
    {
        d_dbase_rset_init (&rset_tv, 1, ids_tv);
        d_dbase_get_srvs_by_ts( &rset_tv, db_ts_id, D_DB_SRV_TV);
        if((rset_tv.ids[0] >= 0) && (d_dbase_get_srv_info(rset_tv.ids[0], &srv_info) >= 0))
        {
            player->tv_id = rset_tv.ids[0];
            player->tv_num = srv_info.chan_num;
        }
    }

    D_DUMP("pScanwin update prog num!\n");
    return D_OK;
}

/** @brief 结束搜索过程*/
static D_Result scan_end (D_U32 save)
{
    D_Frame *frm = &manual_scan_window;

    D_Visual *vis;
    prog_data->scanning_flag = D_FALSE;
    prog_data->save_flag = save ? D_TRUE : D_FALSE;
    prog_data->scanning_flag = D_FALSE;

    if (prog_data->hscan != D_INVALID_HANDLE)
    {
        d_manual_scan_destroy (prog_data->hscan, prog_data->save_flag);
        prog_data->hscan = D_INVALID_HANDLE;
    }

    vis = d_frame_get_control(frm, ID_MANUAL_SCAN_LABEL_SIGNAL);
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
    D_Frame *frm = &manual_scan_window;

    D_Visual *vis_prog;

    D_DUMP("scan_result : tv %d, radio %d\n", tv_cnt, radio_cnt);

    if (prog_data->hscan != D_INVALID_HANDLE)
    {
        d_vis_unsubscribe_one_evt(vis, D_EVT_SCAN_MASK, prog_data->hscan);
    }

    if((tv_cnt + radio_cnt) == 0)
    {
        scan_end(0);
    }
    else
    {
        prog_data->got_srv_flag = D_TRUE;
        vis_prog = d_frame_get_control(frm, ID_MANUAL_SCAN_LABEL_RADIO_NUM);
        if(vis_prog)
        {
            sprintf(prog_data->radio_buf, "%03d", radio_cnt);
            d_label_set_text(vis_prog, prog_data->radio_buf);
        }

        vis_prog = d_frame_get_control(frm, ID_MANUAL_SCAN_LABEL_TV_NUM);
        if(vis_prog)
        {
            sprintf(prog_data->tv_buf, "%03d", tv_cnt );
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
    D_Frame *frm = &manual_scan_window;

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

    vis_prog = d_frame_get_control(frm, ID_MANUAL_SCAN_LABEL_RADIO_NUM);
    if(vis_prog)
    {
        sprintf(prog_data->radio_buf, "%03d", prog_data->radio_cnt);
        d_label_set_text(vis_prog, prog_data->radio_buf);
    }

    vis_prog = d_frame_get_control(frm, ID_MANUAL_SCAN_LABEL_TV_NUM);
    if(vis_prog)
    {
        sprintf(prog_data->tv_buf, "%03d", prog_data->tv_cnt);
        d_label_set_text(vis_prog, prog_data->tv_buf);
    }

    return D_OK;
}

/*设置前端参数*/
static D_Result set_fend_param(D_Bool first)D_FUNCPOSTFIT
{
    D_Frame *frm = &manual_scan_window;
    D_FEndParam param = {0};
    D_Visual *vis;
    D_U32    val = 0;

    if(prog_data->fendtype == D_FEND_DVBC)
    {
        param = prog_data->fendparam;
    }

    if(Freq_num_index != -1)
    {
        param.freq = TvFreqWave[Freq_num_index].major_freq;
        if(prog_data->fendtype == D_FEND_DTMB)
        {
            param.dtmb.freq_k = TvFreqWave[Freq_num_index].minor_freq;
        }
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
vis_show_scan(D_Bool enable)
{
    D_Frame *frm = &manual_scan_window;
    D_Visual *vis;

    if(enable)
    {
        vis = d_frame_get_control (frm, ID_MANUAL_SCAN_GROUP_PROG_NUM);
        if (vis)
        {
            d_vis_show(vis, enable);
        }

        vis = d_frame_get_control(frm, ID_MANUAL_SCAN_LABEL_TV_NUM);
        if(vis)
        {
            d_label_set_text(vis, "000");
        }
        vis = d_frame_get_control(frm, ID_MANUAL_SCAN_LABEL_RADIO_NUM);
        if(vis)
        {
            d_label_set_text(vis, "000");
        }
    }
    else
    {
        vis = d_frame_get_control (frm, ID_MANUAL_SCAN_GROUP_PROG_NUM);
        if (vis)
        {
            d_vis_show(vis, enable);
        }
    }

    vis = d_frame_get_control(frm, ID_MANUAL_SCAN_LABEL_SIGNAL);
    if(vis)
    {
        d_vis_show(vis, D_TRUE);
        d_label_set_text(vis, d_gui_get_text(atv_IDS_SCANNING));
    }

    return D_ERR;
}

static D_Result
startscan_callback(D_Bool sel, D_U32 param)D_FUNCPOSTFIT
{
    D_Frame *frm = &manual_scan_window;
    D_Visual *vis;

    if(sel)
    {
        /*设定界面响应的按键*/
        //p_fp_set_filter_keys(filter_keys, sizeof(filter_keys) / sizeof(filter_keys[0]));
        vis_show_scan(D_TRUE);
        start_scan(d_frame_get_control(frm, 0));
    }
    else
    {
        d_gui_clear_menu ();
    }

    return D_OK;
}

int input_freq_info(D_U8 num)
{
    int ret = 0;
    D_FPKey rev_key;
    int idx = -1;

    rev_key = num;

    if(g_input_key.input_step1 == 0)
    {
        if(rev_key == 0)
            return 0;

        g_input_key.Show_key_val1 = rev_key;

        g_input_key.input_step1 = 1;
        g_input_key.input_step2 = 0;
        g_input_key.input_step3 = 0;
        sprintf(prog_data->freq_lab, "%d-", g_input_key.Show_key_val1);
        d_label_set_text(prog_data->freq_index_vis, prog_data->freq_lab);
        idx = get_freq_idx_by_num(g_input_key.Show_key_val1, 0);
        ret = 3;
    }
    else if(g_input_key.input_step2 == 0)
    {
        g_input_key.Show_key_val2 = g_input_key.Show_key_val1 * 10 + rev_key;

        if(g_input_key.Show_key_val2 > 57 )
        {
            g_input_key.Show_key_val2 = g_input_key.Show_key_val1;
        }

        if(g_input_key.Show_key_val2 != 24)
        {
            g_input_key.input_step1 = 0;
            g_input_key.input_step2 = 0;
            idx = get_freq_idx_by_num(g_input_key.Show_key_val2, 0);
            ret = 1;
        }
        else if(g_input_key.Show_key_val2 == 24)
        {
            g_input_key.input_step1 = 1;
            g_input_key.input_step2 = 1;
            sprintf(prog_data->freq_lab, "DS-%d+", g_input_key.Show_key_val2);
            d_label_set_text(prog_data->freq_index_vis, prog_data->freq_lab);
            idx = get_freq_idx_by_num(g_input_key.Show_key_val2, 0);
            ret = 2;
        }
    }
    else if(g_input_key.input_step3 == 0)
    {
        g_input_key.input_step1 = 0;
        g_input_key.input_step2 = 0;
        g_input_key.input_step3 = 0;
        g_input_key.Show_key_val_ex = rev_key;
        idx = get_freq_idx_by_num(g_input_key.Show_key_val2, g_input_key.Show_key_val_ex);
        ret = 1;
    }

    if(idx != -1)
    {
        Freq_num_index = idx;
    }

    return ret;
}

/** @brief 事件处理*/
static D_Result
manual_scan_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &manual_scan_window;

    ScanConfig.fend_type = prog_data->fendtype;
    ScanConfig.fend_param = prog_data->fendparam;

    switch (evt->type)
    {
        case D_EVT_FP:

            switch (evt->fp.key)
            {
                case D_KEY_BACK:
                    if(prog_data->hscan == D_INVALID_HANDLE)
                    {
                        p_stb_player_play_valid (0);
                        d_gui_upper_menu ();
                    }
                    break;
                case D_KEY_PNL_MENU:
                case D_KEY_MENU:
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                    if(prog_data->hscan == D_INVALID_HANDLE)
                    {
                        d_gui_clear_menu ();
                    }
                    break;

                case D_KEY_0:
                case D_KEY_1:
                case D_KEY_2:
                case D_KEY_3:
                case D_KEY_4:
                case D_KEY_5:
                case D_KEY_6:
                case D_KEY_7:
                case D_KEY_8:
                case D_KEY_9:
                    if(prog_data->hscan == D_INVALID_HANDLE)
                    {
                        int ret = input_freq_info((D_U8)(evt->fp.key - D_KEY_0));
                        if(ret)
                        {
                            if(ret == 1 || ret == 2)
                            {
                                show_freq_info(Freq_num_index, ((ret == 1) ? D_TRUE : D_FALSE));
                            }
                            if(ret != 3)
                            {
                                set_fend_param(D_FALSE);
                            }
                        }
                    }
                    break;

                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    if(prog_data->hscan == D_INVALID_HANDLE)
                    {
                        g_input_key.input_step1 = 0;
                        g_input_key.input_step2 = 0;
                        g_input_key.input_step3 = 0;
                        Freq_num_index = (Freq_num_index + FREQ_CNT - 1) % FREQ_CNT;
                        show_freq_info(Freq_num_index, D_TRUE);
                        set_fend_param(D_FALSE);
                    }
                    break;

                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    if(prog_data->hscan == D_INVALID_HANDLE)
                    {
                        Freq_num_index = (Freq_num_index + 1) % FREQ_CNT;
                        g_input_key.input_step1 = 0;
                        g_input_key.input_step2 = 0;
                        g_input_key.input_step3 = 0;
                        show_freq_info(Freq_num_index, D_TRUE);
                        set_fend_param(D_FALSE);
                    }
                    break;

                case D_KEY_OK:
                case D_KEY_PNL_SOURCE:
                    if(prog_data->hscan == D_INVALID_HANDLE)
                    {
                        if( g_input_key.input_step1 == 1 || g_input_key.input_step2 == 1 || g_input_key.input_step3 == 1)
                        {
                            show_freq_info(Freq_num_index, D_TRUE);
                            set_fend_param(D_FALSE);
                        }
                        else
                        {
                            d_atv_pop_select_center_show(D_POP_MSG_PRIO_MSG_1, D_GUI_LAYER_MESSAGE, NULL,
                                                         d_gui_get_text(atv_IDS_START_MANUAL_SCAN), 10000, D_FALSE, startscan_callback, 0) ;
                        }
                        g_input_key.Show_key_val1 = 0;
                        g_input_key.Show_key_val2 = 0;
                        g_input_key.Show_key_val_ex = 0;
                        g_input_key.input_step1 = 0;
                        g_input_key.input_step2 = 0;
                        g_input_key.input_step3 = 0;
                        g_input_key.input_finished = 0;
                    }
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
        /*搜索完毕*/
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
                if (prog_data->hscan != D_INVALID_HANDLE)
                {
                    d_manual_scan_destroy (prog_data->hscan, D_FALSE);
                    prog_data->hscan = D_INVALID_HANDLE;
                }

                d_fman_clear_status_req(prog_data->hfman, d_gui_get_queue ());

                if(prog_data->fend_timer != D_INVALID_HANDLE)
                {
                    d_timer_destroy(prog_data->fend_timer);
                    prog_data->fend_timer = D_INVALID_HANDLE;
                }

                d_tv_scan_si(prog_data->player->htv, D_TV_SCAN_ALL);

                d_tv_set_vid_window(prog_data->player->htv, 0, 0, -1, -1);
                p_stb_player_play_valid (0);
                PROJECT_FREE(prog_data);
                prog_data = NULL;
            }
            //p_fp_set_filter_keys(&filter_keys, 0xfffff);
            g_input_key.input_step1 = 0;
            g_input_key.input_step2 = 0;
            g_input_key.input_step3 = 0;
            break;
        default:
            break;
    }

    return D_ERR;
}


D_Result
manual_scan_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual        *vis;
    D_U8    idx;
    D_U8    mode_cnt;
    D_SIParam si_param;

    prog_data = (D_AtvManualScanData*)PROJECT_ALLOC(sizeof(D_AtvManualScanData));
    if(!prog_data)
    {
        return D_ERR;
    }

    p_conf_get_si_param(&si_param);
    memset(prog_data, 0x00, sizeof(D_AtvManualScanData));
    prog_data->fend_timer = D_INVALID_HANDLE;
    prog_data->hscan = D_INVALID_HANDLE;
    prog_data->fendparam.freq = si_param.main.freq;

    if(p_conf_get_scan_config())
    {
        prog_data->fendtype = D_FEND_DVBC;
        prog_data->fendparam.dvbc.baud = 6875;
        prog_data->fendparam.dvbc.mod = D_FEND_QAM64;
    }
    else
    {
        prog_data->fendtype = D_FEND_DTMB;
    }
    prog_data->menu_type = STB_SCAN_TYPE_MANUAL;
    prog_data->player = p_stb_get_player (0);

    prog_data->hfman = d_fman_get_handle_by_type(prog_data->fendtype, 0);

    /*因为有信号的锁定，要停播*/
    d_stb_stop_play();
    /*清除残留视频帧*/
    p_stb_player_clear_vid(0);

    vis_show_scan(D_FALSE);
    Freq_num_index = 0;
    show_freq_info(Freq_num_index, D_TRUE);
    show_signal_status(D_FALSE, 0, 0);

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK | D_EVT_AUDIO_KEY_MASK | D_EVT_PROGRAM_PLUS_MINUS_KEY_MASK | D_EVT_FEND_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, manual_scan_window_handler);

        /*创建前端定期检查定时器*/
        prog_data->fend_timer = d_timer_create (NULL, D_FEND_CHECK_TIME, d_gui_get_queue ());
        if(prog_data->fend_timer != D_INVALID_HANDLE)
        {
            d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, prog_data->fend_timer);
        }
    }

    set_fend_param(D_TRUE);

    return D_OK;
}

/** @breif 显示手动搜索界面*/
D_Result
p_atv_manual_scan_window_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&manual_scan_window, D_TRUE);
}
