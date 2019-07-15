/** @file
* @brief 播放器模块
* @author 田青
* @date 田青2009-7-3: 建立文件
*/
#include "stdio.h"
#include <string.h>
#include "dTypes.h"
#include "pPlayer.h"
#include "pConfig.h"
#include "pStbMenus.h"
#include "dDebug.h"
#include "pNVPartApp.h"
#include "pCustomConfig.h"
#include "pEpgControl.h"
#include "dSys.h"
#include "dadporting.h"
#include "pStbFunctions.h"
#include "pStbAtvMenus.h"
#include "pTs2NetRecord.h"

/*系统实际的音量最大值，取决于驱动*/
#define SYS_REAL_VOLUME_MAX d_av_get_max_volume()

#define D_STB_PLAYER_CNT 1


static D_StbPlayer stb_player[D_STB_PLAYER_CNT];



/** @brief 返回指定ID的播放器*/
D_StbPlayer*
p_stb_get_player (D_ID player_id) D_FUNCPOSTFIT
{
    if(player_id < D_STB_PLAYER_CNT)
    {
        return &stb_player[player_id];
    }

    return NULL;
}



/** @brief 取播放器当前正在播放的服务ID*/
static D_DBSrvID
player_get_srv (D_StbPlayer *player) D_FUNCPOSTFIT
{
    if (player->play_srv)
    {
        return player->srv_id;
    }
    else if(player->play_atv)
    {
        return player->atv_id;
    }
    else if (player->play_radio)
    {
        return player->radio_id;
    }
    else
    {
        return player->tv_id;
    }
}

/** @brief 得到播放器中记录的服务ID*/
D_DBSrvID
p_stb_player_get_rec_srv (D_ID player_id, D_DBSrvType type) D_FUNCPOSTFIT
{
    D_DBSrvID   srv = -1;
    D_StbPlayer *player;

    player = p_stb_get_player (player_id);
    if (player)
    {
        if (type == D_DB_SRV_TV)
        {
            srv = player->tv_id;
        }
        else if (type == D_DB_SRV_RADIO)
        {
            srv = player->radio_id;
        }
        else if(D_DB_SRV_ATV)
        {
            srv = player->atv_id;
        }
    }

    return srv;
}



/** @brief 初始化一个播放器
* @param player_id      播放器ID
* @param hfman  前端设备句柄
* @param htv    TV设备句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
p_stb_player_init (D_ID player_id, D_HFMan hfman, D_HTV htv) D_FUNCPOSTFIT
{
    D_StbPlayer *player;

    if (! (player = p_stb_get_player (player_id)))
    {
        return D_ERR;
    }

    player->hfman = hfman;
    player->htv = htv;
    player->play_radio = D_FALSE;
    player->play_srv = D_FALSE;
    player->play_emc_flag = D_FALSE;
    player->tv_id = -1;
    player->tv_num = -1;
    player->prev_tv_id = -1;
    player->radio_id = -1;
    player->radio_num = -1;
    player->prev_radio_id = -1;
    player->srv_id = -1;
    player->unlock_srv_id = -1;
    player->status = D_STB_PLAYER_STATUS_STOPPED;
    player->urgency_timer = D_INVALID_HANDLE;
    player->urgency_prev_srv_id = -1;
    player->playflags = 0;
    player->play_atv = D_FALSE;
    player->atv_id = -1;
    player->atv_num = -1;
    player->prev_atv_id = -1;

	return D_OK;
}

/** @brief 重新设置播放器内部数据
* @param player_id      播放器ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
p_stb_player_reset (D_ID player_id) D_FUNCPOSTFIT
{
    D_StbPlayer *player;

    if (! (player = p_stb_get_player (player_id)))
    {
        return D_ERR;
    }

    player->play_radio = D_FALSE;
    player->play_srv = D_FALSE;
    player->play_emc_flag = D_FALSE;
    player->tv_id = -1;
    player->tv_num = -1;
    player->prev_tv_id = -1;
    player->radio_id = -1;
    player->radio_num = -1;
    player->prev_radio_id = -1;
    player->srv_id = -1;
    player->unlock_srv_id = -1;
    player->status = D_STB_PLAYER_STATUS_STOPPED;
    player->playflags = 0;
    player->play_atv = D_FALSE;
    player->atv_id = -1;
    player->atv_num = -1;
    player->prev_atv_id = -1;

    return D_OK;
}

/** @brief 播放I帧*/
D_Result
p_stb_player_display_pic_I (D_ID player_id, D_ID pic, D_ID no) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    d_ad_pict_info imginfo;
    D_U8 count;
    D_Result ret = D_ERR;

    if (! (player = p_stb_get_player (player_id)))
    {
        return D_ERR;
    }

    if (pic == -1)
    {
        d_tv_display_pic_I (player->htv, -1, NULL, 0);
        ret = D_OK;
    }
    else
    {
        count =  d_ad_get_img_count (pic);
        if(count > no)
        {
            if(d_ad_load_img_data(pic, no, &imginfo) != D_OK)
            {
                return D_ERR;
            }
            if(imginfo.imgType == D_IMAGE_MPEG2_FRAME_I)
            {
                d_tv_display_pic_I (player->htv, imginfo.id, (D_U8*)imginfo.buffer, imginfo.img_size);
                ret = D_OK;
            }
            d_ad_release_img_data(&imginfo );
        }
    }

    return ret;
}

/** @brief 设置音量，将音量值转换为驱动所需音量值*/
D_Result
p_stb_player_set_vol (D_ID player_id, D_U8 vol) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_U8 set_vol;

    if (! (player = p_stb_get_player (player_id)))
    {
        return D_ERR;
    }

    set_vol = (D_U8)((((D_U16)vol) * SYS_REAL_VOLUME_MAX) / P_VOLUME_MAX);
    d_tv_set_volume (player->htv, (D_U8)set_vol);

    return D_OK;
}

/** @brief 设置声道*/
D_Result
p_stb_player_set_track (D_ID player_id, D_AudTrack track) D_FUNCPOSTFIT
{
    D_StbPlayer *player;

    if (! (player = p_stb_get_player (player_id)))
    {
        return D_ERR;
    }

    d_tv_set_aud_track (player->htv, track);

    return D_OK;
}

/** @brief 尝试进行音视频播放并设置CA*/
D_Result
p_stb_player_try_play (D_ID player_id) D_FUNCPOSTFIT
{
    D_DBSrvInfo  info;
    D_StbPlayer *player;
    D_ID    srv;
    D_S8 vol , adapt_vol = 0, set_vol;

    if (! (player = p_stb_get_player (player_id)))
    {
        return D_ERR;
    }

    /*取当前播放服务*/
    srv = player_get_srv (player);

    if (d_dbase_get_srv_info (srv, &info) < 0)
    {
        return D_ERR;
    }

    D_DUMP("player try play: srv %d,  srvid 0x%04x, vpid(%d) 0x%04x, apid1(%d) 0x%04x, apid2(%d) 0x%04x\n",
    srv, info.srv_id, info.vid_codec, info.vid_pid, info.aud1_codec, info.aud1_pid, info.aud2_codec, info.aud2_pid);

    d_tv_play_srv (player->htv, srv);

    /*是否使用音量补偿功能*/
    if(g_custom_config.sys_setup.vol_compensate)
    {
        vol = p_conf_get_volume();
        adapt_vol = info.volume;

        /*防止补偿音量过小或过大*/
        adapt_vol = (adapt_vol < 0) ? D_MAX(adapt_vol, (0 - P_VOLUME_MAX)) : D_MIN(adapt_vol, P_VOLUME_MAX);

        if(vol <= 0)
        {
            set_vol = 0;
        }
        else
        {
            /*音量值不为零时，补偿后的最小值为1*/
            set_vol = vol + adapt_vol;
            set_vol = D_MAX(set_vol, 1);
        }

        set_vol = (set_vol < 0) ? D_MAX(set_vol, 0) : D_MIN(set_vol, P_VOLUME_MAX);
    }
    else
    {
        if(D_DB_SRV_ATV ==info.srv_type)
        {
            set_vol = p_conf_get_volume();
        }		
#if 0
        /*原来机顶盒上的智能音量(每个频道单独存储音量)的方式不再使用*/
        else if(p_conf_get_smart_voice_en())
        {
            set_vol = info.volume;
        }
#endif
        else
        {
            set_vol = p_conf_get_volume();
        }
    }

    /*设定服务声道和音量*/
    d_tv_set_aud_track (player->htv, info.aud_track);
    p_stb_player_set_vol (player_id, (D_U8)set_vol);

    if(D_DB_SRV_ATV != info.srv_type)
    {
        /* 启动后台epg搜索 */
      p_epg_start(0);
    }

    return D_OK;
}

/** @brief 停止播放
* @param    player_id   播放器ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
p_stb_player_stop (D_ID player_id) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    //D_DBSrvID      srv;

    if (! (player = p_stb_get_player (player_id)))
    {
        return D_ERR;
    }

    //srv = player_get_srv (player);

    if (player->status == D_STB_PLAYER_STATUS_PLAYING)
    {
        d_tv_stop_srv (player->htv);
        player->status = D_STB_PLAYER_STATUS_STOPPED;
    }
    p_atv_radio_icon_win_hide();
    return D_OK;
}


/** @brief 尝试播放一个服务
* @param    player_id   播放器ID
* @param    srv 节目记录ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
p_stb_player_play_srv (D_ID player_id, D_DBSrvID srv) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_DBTSInfo tsinfo;
    D_DBSrvInfo info;
    D_Char  led[5];
    D_DBSrvID   osrv;
    D_Bool  already_done = D_FALSE;
    D_Bool  show_radio = D_FALSE;
    D_Bool  hide_radio = D_FALSE;
    D_Bool  prog_lock_enable;

    TIME_RECORD_START("[MENU]");

    if (! (player = p_stb_get_player (player_id)))
        return D_ERR;

    /*取服务相关信息*/
    if (d_dbase_get_srv_info (srv, &info) < 0)
    {
        return D_ERR;
    }
    if(d_dbase_get_ts_info(info.db_ts_id, &tsinfo) < 0)
    {
        return D_ERR;
    }

    if (player->status == D_STB_PLAYER_STATUS_PLAYING)
    {
        /*是否已经是当前节目*/
        osrv = player_get_srv (player);
        if (osrv == srv)
            already_done = D_TRUE;
    }

    if (already_done)
    {
        D_DUMP ("The channel already played\n");    
        if(info.srv_type == D_DB_SRV_TV)
        {
            player->tv_num = info.chan_num;
            snprintf (led, sizeof(led), "C%03d", info.chan_num);
        }
        else if(info.srv_type == D_DB_SRV_RADIO)
        {
            player->radio_num = info.chan_num;
            if(g_stb->status == D_STB_ST_PLAYING)
            {
                p_atv_radio_icon_win_show(srv);
                snprintf (led, sizeof(led), "A%03d", info.chan_num);
            }
        }
        else if(info.srv_type == D_DB_SRV_ATV)
        {
            player->atv_num = info.chan_num;
            snprintf (led, sizeof(led), "A%03d", info.chan_num);
        }
#if (defined(HI_P_TV_TYPE_TV_STB))        
        /*LED显示*/
        d_fp_set_led (0, led);
#endif
        return D_OK;
    }

    /*停止播放*/
    p_stb_player_stop (player_id);

    player->fendtype = (D_FEndType)tsinfo.tuner_type;

    switch (info.srv_type)
    {
        case D_DB_SRV_TV:
            if (player->play_srv)
            {
                player->play_srv = D_FALSE;
            }
            if (player->play_radio)
            {
                hide_radio = D_TRUE;
            }
            /*Added by licc 2006-07-07*/
            if(player->tv_id < 0)
            {
                player->prev_tv_id = srv;
            }
            else if(player->prev_tv_id != player->tv_id)
            {
                player->prev_tv_id = player->tv_id;
            }
            /*END 2006-07-07*/
            player->play_atv = D_FALSE;
            player->play_radio = D_FALSE;
            player->tv_id = srv;
            player->tv_num = info.chan_num;
            player->play_emc_flag = D_FALSE;

            /*记录播放节目ID*/
            p_conf_set_curr_srv (srv);

            snprintf (led, sizeof(led), "C%03d", info.chan_num);
            break;
        case D_DB_SRV_RADIO:
            if (player->play_srv)
            {
                player->play_srv = D_FALSE;
            }
            if (! player->play_radio)
            {
                show_radio = D_TRUE;
            }
            player->play_atv = D_FALSE;
            player->play_radio = D_TRUE;
            /*Added by licc 2006-07-07*/
            if(player->radio_id < 0)
            {
                player->prev_radio_id = srv;
            }
            else if(player->prev_radio_id != player->radio_id)
            {
                player->prev_radio_id = player->radio_id;
            }
            /*END 2006-07-07*/
            player->radio_id = srv;
            player->radio_num = info.chan_num;

            /*记录播放节目ID*/
            p_conf_set_curr_srv (srv);//不记录广播节目，开机需播放电视节目

            snprintf (led, sizeof(led), "A%03d", info.chan_num);
            break;
        case D_DB_SRV_ATV:
            player->play_srv = D_FALSE;
            if (player->play_radio)
            {
                hide_radio = D_TRUE;
            }
            //player->play_radio = D_FALSE;
            player->play_atv = D_TRUE;
            /*Added by licc 2006-07-07*/
            if(player->atv_id < 0)
            {
                player->prev_atv_id = srv;
            }
            else if(player->prev_atv_id != player->atv_id)
            {
                player->prev_atv_id = player->atv_id;
            }
            /*END 2006-07-07*/
            player->atv_id = srv;
            player->atv_num = info.chan_num;

            /*记录播放节目ID*/
            p_conf_set_curr_atv_srv (srv);//不记录广播节目，开机需播放电视节目

            snprintf (led, sizeof(led), "A%03d", info.chan_num);
            break;

        default:
            D_DUMP ("Unknown service type 0x%x\n", info.srv_type);
            return D_ERR;
    }

    /*信号不好时不播放背景画面*/
    if (show_radio || (player->play_radio == D_TRUE))
    {
        /*显示广播背景*/
        if(D_ERR == p_stb_player_display_pic_I (player_id, DAD_STB_RadioBackGround, 0))
        {
            p_stb_player_clear_vid(player_id);
        }
    }

    if (hide_radio)
    {
        /*停止显示广播背景*/
        //d_tv_clear_pic_I(player->htv);//comment by Wansb
    }

#if (defined(HI_P_TV_TYPE_TV_STB))
    /*显示频道信息窗口*/
    if ( g_stb->status == D_STB_ST_PLAYING)
    {
        if(player->play_atv)
        {
            p_atv_tv_chan_info_window_show(player_id);
        }
        else
        {
            p_atv_channel_info_window_show (player_id);
        }
    }

    /*清除界面上的无节目提示*/
    p_no_prog_msg(D_FALSE);

    /*LED显示*/
    d_fp_set_led (0, led);

    prog_lock_enable = p_conf_get_prog_passwd_en();

    if(info.lock && (player->unlock_srv_id != srv) && prog_lock_enable)
    {
        p_show_prog_password_window((D_U32)srv);
    }
    else
    {
        if(prog_lock_enable)
        {
            p_clear_prog_password_window();
        }

        /*清除无法播放osd*/
        p_no_es_stream_show(D_FALSE, D_FALSE);
        p_not_play_msg_show(D_FALSE);
		
        /*设定播放器状态*/
        player->status = D_STB_PLAYER_STATUS_PLAYING;
        player->unlock_srv_id = srv;
        /*开始播放节目*/
        p_stb_player_try_play (player_id);
    }
#else
    /*显示频道信息窗口*/
    if ( g_stb->status == D_STB_ST_PLAYING)
    {
        if(player->play_atv)
        {
            p_atv_tv_chan_info_window_show(player_id);
        }
        else
        {
            p_atv_channel_info_window_show (player_id);
            if(player->play_radio)
            {
                p_atv_radio_icon_win_show(srv);
            }
        }
    }

#ifdef D_TV_SUPPORT_TS2NET
    if(info.srv_type == D_DB_SRV_TV || info.srv_type == D_DB_SRV_RADIO)
    {
        p_ts2net_record_swich_channel(srv);
    }
#endif

    /*清除无法播放osd*/
    p_no_es_stream_show(D_FALSE, D_FALSE);
    p_not_play_msg_show(D_FALSE);
    
    /*设定播放器状态*/
    player->status = D_STB_PLAYER_STATUS_PLAYING;
    player->unlock_srv_id = srv;
    /*开始播放节目*/
    p_stb_player_try_play (player_id);
#endif

    return D_OK;
}

/** @brief 尝试播放一个频道
* @param    player_id   播放器ID
* @param    num 节目频道号
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
p_stb_player_play (D_ID player_id, D_U16 num) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_ID        srv;
    D_DBSrvType type = D_DB_SRV_ATV;

    if (! (player = p_stb_get_player (player_id)))
        return D_ERR;

    if(!player->play_atv)
    {
        type = (player->play_radio) ? D_DB_SRV_RADIO : D_DB_SRV_TV;
    }

    srv = d_dbase_get_srv_by_num (num, type);
    if (srv != -1)
    {
        return p_stb_player_play_srv (player_id, srv);
    }

    return D_ERR;
}

/** @brief 播放下一个频道(频道号++查寻)
* @param    player_id   播放器ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
p_stb_player_channel_up (D_ID player_id) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_S16       num;
    D_DBSrvType type;

    if (! (player = p_stb_get_player (player_id)))
        return D_ERR;

    /*取当前频道号*/
    if (player->play_atv)
    {
        num = player->atv_num;
        type = D_DB_SRV_ATV;
    }
    else if (! player->play_radio)
    {
        num = player->tv_num;
        type = D_DB_SRV_TV;
    }
    else
    {
        num = player->radio_num;
        type = D_DB_SRV_RADIO;
    }

    /*取下一频道号*/
    num = d_dbase_get_next_chan_num (num, type, D_TRUE, D_FALSE);
    if (num < 0)
    {
        D_DUMP ("Cannot get next program\n");
        return D_ERR;
    }

    return p_stb_player_play (player_id, num);
}

/** @brief 播放上一个频道(频道号--查寻)
* @param    player_id   播放器ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
p_stb_player_channel_down (D_ID player_id) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_S16       num;
    D_DBSrvType type;

    if (! (player = p_stb_get_player (player_id)))
        return D_ERR;

    /*取当前频道号*/
    if (player->play_atv)
    {
        num = player->atv_num;
        type = D_DB_SRV_ATV;
    }
    else if (! player->play_radio)
    {
        num = player->tv_num;
        type = D_DB_SRV_TV;
    }
    else
    {
        num = player->radio_num;
        type = D_DB_SRV_RADIO;
    }

    /*取下一频道号*/
    num = d_dbase_get_next_chan_num (num, type, D_FALSE, D_FALSE);
    if (num < 0)
    {
        D_DUMP ("Cannot get previous program\n");
        return D_ERR;
    }

    return p_stb_player_play (player_id, num);
}

/** @brief 切换电视和广播播放模式
* @param    player_id   播放器ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
p_stb_player_switch_tv_radio (D_ID player_id, D_Bool play_tv) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_DBSrvType srvtype;
    D_DBSrvID    srv;
    D_S16        num;
    D_DBSrvInfo srvinfo;
    D_Bool  show_radio = D_FALSE;
    D_Bool  hide_radio = D_FALSE;
    D_Result ret;

    if (! (player = p_stb_get_player (player_id)))
        return D_ERR;

    /*取得要播放的服务*/
    if ((player->play_radio && (!play_tv)) || (!(player->play_radio) && play_tv))
    {
        /*不再重新播放相同类型的节目*/
        return D_ERR;
    }

    if(player->play_radio)
    {
        srv = player->tv_id;
        num = player->tv_num;
        srvtype = D_DB_SRV_TV;
    }
    else
    {
        if(d_dbase_get_srvs_cnt(D_FALSE, D_DB_SRV_RADIO) == 0)/*如果电广键没有广播则不切换只弹框提示*/
            return D_ERR;
        else
        {
            srv = player->radio_id;
            num = player->radio_num;
            srvtype = D_DB_SRV_RADIO;
        }
    }

    /*检查db_srv_id有效性 */
    if(srv >= 0)
    {
        ret = d_dbase_get_srv_info(srv, &srvinfo);
        if((ret != D_OK) || (srvinfo.srv_type != srvtype))
        {
            srv = -1;
        }
    }

    if ((srv < 0) && (num >= 0))
    {
        srv = d_dbase_get_srv_by_num (num, srvtype);
        /*检查db_srv_id有效性 */
        if((srv >= 0) && (d_dbase_get_srv_info(srv, &srvinfo) != D_OK))
        {
            srv = -1;
        }
    }

    if (srv < 0)
    {
        num = d_dbase_get_next_chan_num (-1, srvtype, D_TRUE, D_FALSE);
        srv = d_dbase_get_srv_by_num (num, srvtype);
        /*检查db_srv_id有效性 */
        if(srv >= 0)
        {
            ret = d_dbase_get_srv_info(srv, &srvinfo);
            if((ret != D_OK) || (srvinfo.srv_type != srvtype))
            {
                srv = -1;
            }
        }
    }

    if (srv < 0)
    {
        D_DUMP ("No program found");
        /*停止播放*/
        p_stb_player_stop (player_id);

        if(player->play_radio)
        {
            hide_radio = D_TRUE;
            if(player->tv_id < 0)
            {
                player->prev_tv_id = srv;
            }
            else
            {
                player->prev_tv_id = player->tv_id;
            }
            /*END 2006-07-07*/
            player->play_srv = D_FALSE;
            player->play_radio = D_FALSE;
            player->tv_id = srv;
            player->tv_num = 0;
            player->play_emc_flag = D_FALSE;
        }
        else
        {
            show_radio = D_TRUE;
            /*Added by licc 2006-07-07*/
            if(player->radio_id < 0)
            {
                player->prev_radio_id = srv;
            }
            else
            {
                player->prev_radio_id = player->radio_id;
            }
            /*END 2006-07-07*/
            player->play_srv = D_FALSE;
            player->play_radio = D_TRUE;
            player->radio_id = srv;
            player->radio_num = 0;
            player->play_emc_flag = D_FALSE;
        }

        /*信号不好时播放背景画面*/
        if (show_radio || (player->play_radio == D_TRUE))
        {
            /*显示广播背景*/
            p_stb_player_display_pic_I (player_id, DAD_STB_RadioBackGround, 0); //add by Wansb
        }

        if (hide_radio)
        {
            /*停止显示广播背景*/
            //d_tv_clear_pic_I(player->htv);
        }

        /*显示频道信息窗口*/
        if ( g_stb->status == D_STB_ST_PLAYING)
        {
            if(player->play_atv)
            {
                p_atv_tv_chan_info_window_show(player_id);
            }
            else
            {
                p_atv_channel_info_window_show (player_id);
            }
        }

        /*LED显示*/
        d_fp_set_led (0, "0000");

        return D_ERR;
    }


    return p_stb_player_play_srv (player_id, srv);
}


/** @brief 尝试播放各种可能的节目
* @param    player_id   播放器ID
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
p_stb_player_play_valid (D_ID player_id) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_DBSrvType srvtype;
    D_S16       num;
    D_DBSrvID   osrv;

    D_DBSrvID   srv = -1;
    D_DBSrvInfo  srvinfo;
    D_Result ret;

    if (! (player = p_stb_get_player (player_id)))
        return D_ERR;

    if(player->play_atv)
    {
        osrv = player->atv_id;
        num = player->atv_num;
        srvtype = D_DB_SRV_ATV;
    }
    else if(player->play_radio)
    {
        osrv = player->radio_id;
        num = player->radio_num;
        srvtype = D_DB_SRV_RADIO;
    }
    else
    {
        osrv = player->tv_id;
        num = player->tv_num;
        srvtype = D_DB_SRV_TV;
    }

    if (osrv >= 0)
    {
        if((d_dbase_get_srv_info(osrv, &srvinfo) >= 0) && (srvinfo.srv_type == srvtype))
        {
            srv = osrv;
        }
    }

    if ((srv < 0) && (num >= 0))
    {
        srv = d_dbase_get_srv_by_num (num, srvtype);
        /*检查db_srv_id有效性 */
        if(srv >= 0)
        {
            ret = d_dbase_get_srv_info(srv, &srvinfo);
            if((ret != D_OK) || (srvinfo.srv_type != srvtype))
            {
                srv = -1;
            }
        }
    }

    if (srv < 0)
    {
        num = d_dbase_get_next_chan_num (-1, srvtype, D_TRUE, D_FALSE);
        srv = d_dbase_get_srv_by_num (num, srvtype);
        /*检查db_srv_id有效性 */
        if(srv >= 0)
        {
            ret = d_dbase_get_srv_info(srv, &srvinfo);
            if((ret != D_OK) || (srvinfo.srv_type != srvtype))
            {
                srv = -1;
            }
        }
    }

    if (srv >= 0)
    {
        p_stb_player_play_srv (player_id, srv);
        return D_OK;
    }

    return D_ERR;
}

#if 0
D_Result
p_stb_player_play_valid (D_ID player_id) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_S16       num = -1;
    D_DBSrvID   srv = -1;
    D_U8        try_time;
    D_DBSrvInfo  srvinfo;

    if (! (player = p_stb_get_player (player_id)))
        return D_ERR;

    for (try_time = 0; try_time < 2; try_time ++)
    {
        /*尝试播放电视节目*/
        if ((! player->play_radio) != try_time)
        {
            if (player->tv_id >= 0 || player->tv_num >= 0)
            {
                if(d_dbase_get_srv_info(player->tv_id, &srvinfo) >= 0)
                {
                    srv = player->tv_id;
                }
                else
                {
                    srv = d_dbase_get_srv_by_num (player->tv_num, D_DB_SRV_TV);
                }
            }

            if ((srv == -1) && d_dbase_has_any_srv (D_DB_SRV_TV))
            {
                num = d_dbase_get_next_chan_num (-1, D_DB_SRV_TV, D_TRUE, D_FALSE);
                if (num >= 0)
                {
                    srv = d_dbase_get_srv_by_num (num, D_DB_SRV_TV);
                }
            }

            if (srv != -1)
            {
                p_stb_player_play_srv (player_id, srv);
                return D_OK;
            }
        }

        /*尝试播放广播节目*/
        if ((player->play_radio) != try_time)
        {
            if (player->radio_id >= 0 || player->radio_num >= 0)
            {
                if(d_dbase_get_srv_info(player->radio_id, &srvinfo) >= 0)
                {
                    srv = player->radio_id;
                }
                else
                {
                    srv = d_dbase_get_srv_by_num (player->radio_num, D_DB_SRV_RADIO);
                }
            }

            if ((srv == -1) && d_dbase_has_any_srv (D_DB_SRV_RADIO))
            {
                num = d_dbase_get_next_chan_num (-1, D_DB_SRV_RADIO, D_TRUE, D_FALSE);
                if (num >= 0)
                {
                    srv = d_dbase_get_srv_by_num (num, D_DB_SRV_RADIO);
                }
            }

            if (srv != -1)
            {
                p_stb_player_play_srv (player_id, srv);
                return D_OK;
            }
        }
    }

    return D_ERR;
}
#endif

/** @brief 取得当前播放的服务ID*/
D_DBSrvID
p_stb_player_get_curr_srv (D_ID player_id) D_FUNCPOSTFIT
{
    D_DBSrvID           srv = -1;
    D_StbPlayer  *player;

    player = p_stb_get_player (player_id);
    if (! player)
    {
        return srv;
    }

    if (player->play_srv)
    {
        srv = player->srv_id;
    }
    else if (player->play_atv)
    {
        srv = player->atv_id;
    }
    else if (! player->play_radio)
    {
        srv = player->tv_id;
    }
    else
    {
        srv = player->radio_id;
    }

    return srv;
}

/** @brief 取得当前播放的频道号和服务类型*/
D_S16
p_stb_player_get_curr_chan_num (D_ID player_id, D_DBSrvType *type) D_FUNCPOSTFIT
{
    D_S16   num = -1;
    D_StbPlayer  *player;
    D_DBSrvType srvtype;

    player = p_stb_get_player (player_id);
    if (! player)
        return num;

    /*正在播放固定服务*/
    if (player->play_srv)
        return -1;

    srvtype = D_DB_SRV_TV;
    if (player->play_atv)
    {
        num = player->atv_num;
        srvtype = D_DB_SRV_ATV;
    }
    else if (! player->play_radio)
    {
        num = player->tv_num;
        srvtype = D_DB_SRV_TV;
    }
    else
    {
        num = player->radio_num;
        srvtype = D_DB_SRV_RADIO;
    }

    if (type)
    {
        *type = srvtype;
    }

    return num;
}

/** @brief 设定播放器播放标志
* @param player_id 播放器ID
* @param flags  播放器标志
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
p_stb_player_set_flags (D_ID player_id, D_U32 flags) D_FUNCPOSTFIT
{
    D_StbPlayer  *player;

    player = p_stb_get_player (player_id);
    if (! player)
        return D_ERR;

    player->playflags = flags;
    return D_OK;
}

/** @brief 取得播放器播放标志
* @param player_id 播放器ID
* @return 返回当前的播放状态
*/
D_U32
p_stb_player_get_flags (D_ID player_id) D_FUNCPOSTFIT
{
    D_StbPlayer  *player;

    player = p_stb_get_player (player_id);
    if (! player)
    {
        return 0;
    }

    return player->playflags;
}

/** @brief 进行应急广播
* @param[in] player_id  播放器ID
* @param[in] srv    节目记录ID
* @param[in] ms 应急广播延迟时间(毫秒)，<= 0表示一直播放
* @retval D_OK 正确, D_ERR失败
*/
D_Result
p_stb_player_play_urgency_srv (D_ID player_id, D_DBSrvID srv, D_MSec ms) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_U32                oflag;
    D_Visual        *win;

    player = p_stb_get_player (player_id);
    if (! player)
        return D_ERR;

    oflag = p_stb_player_get_flags (player_id);
    if (!(oflag & D_PLAYER_FLAGS_URGENCY))
    {
        /*如果没有进入应急广播,记录正在播放的节目*/
        player->urgency_prev_srv_id = p_stb_player_get_curr_srv (player_id);
    }

    /*设定应急播放状态*/
    p_stb_player_set_flags (player_id, oflag | D_PLAYER_FLAGS_URGENCY);

    /*开始播放节目*/
    p_stb_player_play_srv (player_id, srv);

    /*设定定时器*/
    if (ms > 0)
    {
        if (player->urgency_timer == D_INVALID_HANDLE)
        {
            player->urgency_timer = d_timer_create (NULL, ms, d_gui_get_queue ());
            win = p_desktop_get_control ();
            if (win)
            {
                d_vis_subscribe_evt (win, D_EVT_TIMER_MASK, player->urgency_timer);
            }
        }
        else
        {
            d_timer_reset (player->urgency_timer, ms);
        }
    }
    else
    {
        if (player->urgency_timer != D_INVALID_HANDLE)
        {
            d_timer_destroy (player->urgency_timer);
            win = p_desktop_get_control ();
            if (win)
            {
                d_vis_unsubscribe_one_evt (win, D_EVT_TIMER_MASK, player->urgency_timer);
            }
            player->urgency_timer = D_INVALID_HANDLE;
        }
    }

    return D_OK;
}

/** @brief 停止应急广播
* @param[in] player_id  播放器ID
* @param[in] play_prev 是否返回播放之前的节目
* @retval D_OK 正确, D_ERR失败
*/
D_Result
p_stb_player_stop_urgency_srv (D_ID player_id, D_Bool play_prev) D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_U32                oflag;
    D_Visual        *win;

    player = p_stb_get_player (player_id);
    if (! player)
        return D_ERR;

    oflag = p_stb_player_get_flags (player_id);
    if (!(oflag & D_PLAYER_FLAGS_URGENCY))
    {
        /*如果没有进入应急广播,记录正在播放的节目*/
        return D_OK;
    }

    /*退出应急广播*/
    if (player->urgency_timer != D_INVALID_HANDLE)
    {
        d_timer_destroy (player->urgency_timer);
        win = p_desktop_get_control ();
        if (win)
        {
            d_vis_unsubscribe_one_evt (win, D_EVT_TIMER_MASK, player->urgency_timer);
        }
        player->urgency_timer = D_INVALID_HANDLE;
    }

    p_stb_player_set_flags (player_id, oflag & ~D_PLAYER_FLAGS_URGENCY);

    /*播放上一节目*/
    if(play_prev)
    {
        p_stb_player_play_srv (player_id, player->urgency_prev_srv_id);
    }

    return D_OK;
}

/**@brief 交替节目显示*/
D_Result p_stb_player_alt_srv(D_ID player_id) D_FUNCPOSTFIT
{
    D_StbPlayer *player;

    player = p_stb_get_player (player_id);
    if (! player)
    {
        return D_ERR;
    }

    if(player->play_atv)
    {
        p_stb_player_play_srv(player_id, player->prev_atv_id);
    }
    else if (player->play_radio)
    {
        p_stb_player_play_srv(player_id, player->prev_radio_id);
    }
    else
    {
        p_stb_player_play_srv(player_id, player->prev_tv_id);
    }

    return D_OK;
}

/*清除残留视频 帧(黑屏操作)，stop之后调用*/
D_Result p_stb_player_clear_vid(D_ID player_id)  D_FUNCPOSTFIT
{
    D_StbPlayer *player;

    player = p_stb_get_player (player_id);
    if (! player)
    {
        return D_ERR;
    }

    d_tv_clear_vid (player->htv);

    return D_OK;
}
