/** @file
* @brief Ӧ�����õ���һЩ���ýӿں���
* @author ����
* @date 2014-06-20 ����: �����ļ�
*/
#include <stdlib.h>
#include <string.h>
#include "pStbFunctions.h"
#include "pPlayer.h"
#include "pConfig.h"
#include "pPopMsg.h"
#include "pStbMenus.h"
#include "pStbAtvMenus.h"
#include "pTs2net.h"

D_Bool  SYS_TVOUT_FLAG = D_FALSE;


extern D_Result d_fman_release_dev(D_HFMan fm) D_FUNCPOSTFIT;

/** @brief �������ݿ��������趨�����������������*/
D_Result
p_stb_reset_mute_track_volume( void )D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_Bool mute;
    D_AudTrack track;
    D_U8 vol;

    player = p_stb_get_player (0);
    if (! player)
    {
        return D_ERR;
    }

    mute = p_conf_get_aud_mute();
    d_tv_set_aud_mute (player->htv, mute);

    track = p_conf_get_aud_track();
    p_stb_player_set_track(0, track);

    vol = p_conf_get_volume();
    p_stb_player_set_vol(0, vol);

    return D_OK;
}

void p_set_ratio_mode(D_U8 mode)D_FUNCPOSTFIT
{
    switch(mode)
    {
        case 0:
        {
            d_av_set_tv_ratio_mode(0, D_Full_Screen);
            break;
        }
        case 1:
        {
            d_av_set_tv_ratio_mode(0, D_NATURAL_RATIO);
            break;
        }
        case 2:
        {
            d_av_set_tv_ratio_mode(0, D_4_to_3);
            break;
        }
        case 3:
        {
            d_av_set_tv_ratio_mode(0, D_ZOOM_1X);
            break;
        }
        case 4:
        {
            d_av_set_tv_ratio_mode(0, D_Overall_Screen);
            break;
        }
        default:
        {
            d_av_set_tv_ratio_mode(0, D_Full_Screen);
            break;
        }
    }
}

/** @brief �������ݿ������趨����״̬*/
D_Result
p_stb_reset_mute_status( void )D_FUNCPOSTFIT
{
    D_StbPlayer *player;
    D_Bool mute;

    player = p_stb_get_player (0);
    if (! player)
    {
        return D_ERR;
    }

    mute = p_conf_get_aud_mute();
    d_tv_set_aud_mute (player->htv, mute);

    return D_OK;
}

/**@brief ���ռ��С����Ϊ�ַ���*/
D_Result p_unit_converter( D_Double orisize, D_Char * output )D_FUNCPOSTFIT
{
    D_U8 i;
    D_Float display_size;
    const char * unit[] = {"Byte", "KB", "MB", "GB", "TB", "PB"};

    for(i = 0; i < 6; i++)
    {
        if(orisize < 1024)
        {
            display_size = (D_Float)orisize;
            sprintf(output, "%.2f %s", display_size, unit[i]);
            return D_OK;
        }
        else
        {
            orisize = orisize / 1024;
        }
    }

    return D_OK;
}


/** @brief ��ʾ��������Ϣ����
* @param prio           ��Ϣ������ȼ�
* @param layer          ��ʾ���ڵĲ�
* @param type           ��Ϣ������
* @param str_title          Ҫ��ʾ�ı����ı�
* @param msg            Ҫ��ʾ����Ϣid
* @param timeout��      ��������Ļ��������ʱ�䣬С�ڵ��ڣ���ʾ��Զ��ʾ,ֱ������d_pop_msg_hide
                        ���û��ֶ�����
* @param pop_msg_resp_type  ��Ӧ����
* @param video_win_show ��С��Ƶ�������Ƿ���ʾ
* @param handler        �û�ȷ�Ϻ���õĺ���ָ��
* @param param          �����û��ص��Ĳ���
* @return ��ʾ�ɹ�����D_OK,��ʾʧ�ܷ���D_ERR
*/
D_Result d_pop_msg_show (D_U16 prio,
                         D_GUILayer layer,
                         D_PopMsgType type, const D_Char *str_title, const D_Char *msg,
                         D_MSec timeout, D_PopMsgResponseType pop_msg_resp_type,
                         D_Bool video_win_show,
                         D_Result (*handler) (D_U32 param) D_FUNCPOSTFIT,
                         D_U32 param) D_FUNCPOSTFIT
{
    D_VidInput input;

    input = p_conf_get_vid_input ();
    switch(input)
    {
        case D_VID_IUTPUT_DTV:
        {
#if (defined(HI_P_TV_TYPE_TV_STB))
            return d_stb_pop_msg_show( prio, layer, type, str_title, msg, timeout, pop_msg_resp_type,
                                       video_win_show, handler, param);
#else
            return d_atv_pop_msg_show( prio, layer, type, str_title, msg, timeout, pop_msg_resp_type,
                                       video_win_show, handler, param);
#endif
        }
        default:
            break;
    }
    return D_OK;

}

/** @brief ��˸��ʾ��������Ϣ����
* @param prio           ��Ϣ������ȼ�
* @param layer          ��ʾ���ڵĲ�
* @param type           ��Ϣ������
* @param str_title          Ҫ��ʾ�ı����ı�
* @param msg            Ҫ��ʾ����Ϣ�ı�
* @param flash_times        ��˸����
* @param show_time��    ��˸ʱ��ʾʱ��
* @param hide_time      ��˸ʱ����ʱ��
* @param pop_msg_resp_type  ��Ӧ����
* @param video_win_show ��С��Ƶ�������Ƿ���ʾ
* @param handler        �û�ȷ�Ϻ���õĺ���ָ��
* @param param          �����û��ص��Ĳ���
* @return ��ʾ�ɹ�����D_OK,��ʾʧ�ܷ���D_ERR
*/
D_Result d_pop_msg_flash_show (D_U16 prio, D_GUILayer layer,
                               D_PopMsgType type, const D_Char *str_title, const D_Char *msg,
                               D_U16 flash_times, D_MSec show_time, D_MSec hide_time,
                               D_PopMsgResponseType pop_msg_resp_type, D_Bool video_win_show,
                               D_Result (*handler) (D_U32 param) D_FUNCPOSTFIT,
                               D_U32 param) D_FUNCPOSTFIT
{
    D_VidInput input;

    input = p_conf_get_vid_input ();
    switch(input)
    {
        case D_VID_IUTPUT_DTV:
        {
#if (defined(HI_P_TV_TYPE_TV_STB))
            return d_stb_pop_msg_flash_show(prio, layer,
                                            type, str_title, msg,
                                            flash_times,  show_time,  hide_time,
                                            pop_msg_resp_type,  video_win_show,
                                            handler,
                                            param);
#else
            return d_atv_pop_msg_flash_show(prio, layer,
                                            type, str_title, msg,
                                            flash_times,  show_time,  hide_time,
                                            pop_msg_resp_type,  video_win_show,
                                            handler,
                                            param);
#endif
        }
        default:
            break;
    }
    return D_OK;

}

/** @brief ������ʾ����Ϣ����
* @param prio           ��Ϣ������ȼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_pop_msg_hide (D_U16 prio) D_FUNCPOSTFIT
{
    D_VidInput input;

    input = p_conf_get_vid_input ();
    switch(input)
    {
        case D_VID_IUTPUT_DTV:
        {
#if (defined(HI_P_TV_TYPE_TV_STB))
            return d_stb_pop_msg_hide(prio);
#else
            return d_atv_pop_msg_hide(prio);
#endif
        }
        default:
            break;
    }
    return D_OK;

}

/** @brief ��ʾ�������û�ѡ�񴰿�,�û�����ѡ��ȷ�ϻ�ȡ��
* @param prio           ��Ϣ������ȼ�
* @param layer          ��ʾ���ڵĲ�
* @param str_title          Ҫ��ʾ�ı����ı�
* @param msg            Ҫ��ʾ����Ϣ
* @param timeout��      ��������Ļ��������ʱ�䣬С�ڵ��ڣ���ʾ��Զ��ʾ,ֱ������d_pop_select_hide
                        ���û��ֶ�����
* @param def            D_TRUE��ʾ��ʱ����û�����ȷ��Ч����ͬ��D_FALSE��ʾ��ʱ����û�����ȡ��
                        Ч����ͬ
* @param handler        ѡ����ص�����ָ��
* @param param          �����û��ص��Ĳ���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_pop_select_show (D_U16 prio,
                            D_GUILayer layer,
                            const D_Char *str_title,
                            const D_Char *msg, D_MSec timeout,
                            D_Bool def,
                            D_Result (*handler) (D_Bool sel, D_U32 param) D_FUNCPOSTFIT,
                            D_U32 param) D_FUNCPOSTFIT
{
    D_VidInput input;

    input = p_conf_get_vid_input ();
    switch(input)
    {
        case D_VID_IUTPUT_DTV:
        {
#if (defined(HI_P_TV_TYPE_TV_STB))
            return d_stb_pop_select_show(prio, layer, str_title, msg, timeout, def, handler, param);
#else
            return d_atv_pop_select_show(prio, layer, str_title, msg, timeout, def, handler, param);
#endif
        }
        default:
            break;
    }
    return D_OK;

}

/** @brief ������ʾ���û�ѡ�񴰿�
* @param prio           ��Ϣ������ȼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result    d_pop_select_hide (D_U16 prio) D_FUNCPOSTFIT
{
    D_VidInput input;

    input = p_conf_get_vid_input ();
    switch(input)
    {
        case D_VID_IUTPUT_DTV:
        {
#if (defined(HI_P_TV_TYPE_TV_STB))
            return d_stb_pop_select_hide(prio);
#else
            return d_atv_pop_select_hide(prio);
#endif
        }
        default:
            break;
    }
    return D_OK;

}



/** @brief ��ʾ���봰��(��ȷ�����˳���ʾ)
* @param prio           ��Ϣ������ȼ�
* @param layer      ��ʾ���ڵĲ�
* @param type       ���������
* @param str_title          Ҫ��ʾ�ı����ı�
* @param msg            Ҫ��ʾ����Ϣ
* @param len            �����ַ�����
* @param user_hide  �û��Ƿ�����ֶ��˳�
* @param handler    ѡ����ص�����ָ��
* @param param      �����û��ص��Ĳ���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result    d_pop_input_show (D_U16 prio,
                              D_GUILayer layer,
                              D_PopInputType type,
                              const D_Char *str_title,
                              const D_Char *msg,
                              D_U16 len, D_Bool user_hide,
                              D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT,
                              D_U32   param) D_FUNCPOSTFIT
{
    D_VidInput input;

    input = p_conf_get_vid_input ();
    switch(input)
    {
        case D_VID_IUTPUT_DTV:
        {
#if (defined(HI_P_TV_TYPE_TV_STB))
            return d_stb_pop_input_show( prio, layer, type, str_title, msg, len, user_hide, handler, param);
#else
            return d_atv_pop_input_show( prio, layer, type, str_title, msg, len, user_hide, handler, param);
#endif
        }
        default:
            break;
    }
    return D_OK;

}

/** @brief ��ʾ���봰��(����ֻ��ȷ����ʾ)
* @param prio           ��Ϣ������ȼ�
* @param layer      ��ʾ���ڵĲ�
* @param type       ���������
* @param str_title          Ҫ��ʾ�ı����ı�
* @param msg            Ҫ��ʾ����Ϣ
* @param len            �����ַ�����
* @param user_hide  �û��Ƿ�����ֶ��˳�
* @param handler    ѡ����ص�����ָ��
* @param param      �����û��ص��Ĳ���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result    d_pop_input_show_ex (D_U16 prio,
                                 D_GUILayer layer,
                                 D_PopInputType type,
                                 const D_Char *str_title,
                                 const D_Char *msg,
                                 D_U16 len, D_Bool user_hide,
                                 D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT,
                                 D_U32   param) D_FUNCPOSTFIT
{
    D_VidInput input;

    input = p_conf_get_vid_input ();
    switch(input)
    {
        case D_VID_IUTPUT_DTV:
        {
#if (defined(HI_P_TV_TYPE_TV_STB))
            return d_stb_pop_input_show_ex(prio, layer, type, str_title, msg, len, user_hide, handler, param);
#else
            return d_atv_pop_input_show_ex(prio, layer, type, str_title, msg, len, user_hide, handler, param);
#endif
        }
        default:
            break;
    }
    return D_OK;

}
/** @brief ������ʾ���û�ѡ�񴰿�
* @param prio           ��Ϣ������ȼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result    d_pop_input_hide (D_U16 prio) D_FUNCPOSTFIT
{
    D_VidInput input;

    input = p_conf_get_vid_input ();
    switch(input)
    {
        case D_VID_IUTPUT_DTV:
        {
#if (defined(HI_P_TV_TYPE_TV_STB))
            return d_stb_pop_input_hide(prio);
#else
            return d_atv_pop_input_hide(prio);
#endif
        }
        default:
            break;
    }
    return D_OK;
}


/** @brief ȡ�����洰�ڶ�Ӧ�Ŀؼ�*/
D_Visual*
p_desktop_get_control (void) D_FUNCPOSTFIT
{
    D_VidInput input;

    input = p_conf_get_vid_input ();
    switch(input)
    {
        case D_VID_IUTPUT_TV:
        {
#if (defined(HI_P_TV_TYPE_TV_STB))
            return p_stb_get_player_window();
#else
            return p_atv_get_player_window ();
#endif
        }
        default:
            return p_atv_get_player_window ();
    }
}

/** @brief ����ca�˵�*/
D_Result
p_stb_set_ca_menu(D_GUIMenu *camenu) D_FUNCPOSTFIT
{
#if (defined(HI_P_TV_TYPE_TV_STB))
#if   D_CA_SUPPORT_DEF
    return p_stb_set_ca_menu_ex(camenu);
#endif
#endif
#if (defined(HI_P_TV_TYPE_TV))
#if   D_CA_SUPPORT_DEF
    return p_stb_set_atv_ca_menu(camenu);
#endif
#endif


    return D_OK;
}

/** @brief ȡ���û����õı���ɫ*/
D_U32 p_sys_get_user_background_color(void) D_FUNCPOSTFIT
{
    D_U8 flag;
    p_tvconf_get_blue_screen(&flag);
    return (D_U32)((flag == 0) ?  D_VID_BackGround_Blue : D_VID_BackGround_BLack);
}


/** @brief �����л�Դ*/
D_Result p_sys_set_input_mode(D_VidInput lastinput, D_VidInput input) D_FUNCPOSTFIT
{
    D_DBSrvID           srv;
    D_HFMan hfman;
    D_StbPlayer *player;
    D_FEndParam fendparam;
    D_U8 ratio_mode;

    if(lastinput == input)
        return D_OK;

    d_stb_stop_play();
#if defined( D_TV_MIRACAST_SOURCE) || defined(D_TV_DLNA_SOURCE) || defined(D_TV_SUPPORT_TS2NET)
    p_atv_zhilian_main_menu_window_hide();
#endif
    p_atv_player_window_clear_osd(0);

    if(lastinput == D_VID_IUTPUT_USB1)
    {
        d_gui_clear_menu_ext(ATV_MEDIA_MENU_ID);
        AtvMediaMenuStatus = 0;
        p_gui_atv_media_resource_deinit();
    }
#if defined( D_TV_MIRACAST_SOURCE) || defined(D_TV_DLNA_SOURCE) || defined(D_TV_SUPPORT_TS2NET)
    if(lastinput == D_VID_IUTPUT_WIFIDISPLAY)
    {
        d_gui_clear_menu_ext(ATV_MEDIA_MENU_ID);
        p_gui_atv_zhilian_resource_deinit();
    }
#endif
#ifdef D_TV_LIULINK_SOURCE
    if(lastinput == D_VID_IUTPUT_LIULINK)
    {
        D_ERROR("         EXIT LIULINK\n");
        extern int Liulinkclient_exit(void);
        Liulinkclient_exit();
    }
#endif

    if(lastinput == D_VID_IUTPUT_TEST)
    {
        aging_Ctrl_close();
        p_fp_set_filter_keys(NULL, 0XFFFF);
    }
    if(lastinput == D_VID_IUTPUT_TV)
    {
        p_vip_set_panel_param(0);//lvdsʱ���л�������
        gui_set_ddr_freq(1066);//ddrʱ���л�������
    }
    if(input != D_VID_IUTPUT_DTV)
    {
        gui_set_ddr_freq(1066);//ddrʱ���л�������
        hfman = d_fman_get_handle_by_type(D_FEND_DTMB, 0);
        d_fman_set_suspend(hfman, D_TRUE);
        d_fman_release_dev(hfman);
        hfman = d_fman_get_handle_by_type(D_FEND_DVBC, 0);
        d_fman_set_suspend(hfman, D_TRUE);
        d_fman_release_dev(hfman);
        hfman = d_fman_get_handle_by_type(D_FEND_DVBS, 0);
        d_fman_set_suspend(hfman, D_TRUE);
        d_fman_release_dev(hfman);

        p_monitor_close();
    }
#ifdef D_TV_IAMGE_SOURCE
    hfman = d_fman_get_handle_by_type(D_FEND_CVBS, 0);
    d_fman_set_suspend(hfman, D_TRUE);
    d_fman_release_dev(hfman);
#endif
    if(input != D_VID_IUTPUT_TV)
    {
        hfman = d_fman_get_handle_by_type(D_FEND_ANALOG, 0);
        d_fman_set_suspend(hfman, D_TRUE);
        d_fman_release_dev(hfman);
    }
    if((input == D_VID_IUTPUT_USB1)\
       || (input == D_VID_IUTPUT_USB2) || (input == D_VID_IUTPUT_USB3)
#ifdef D_TV_LIULINK_SOURCE
       || (input == D_VID_IUTPUT_LIULINK)
#endif
      )
    {
        p_av_set_vid_background(0, D_VID_BackGround_BLack, D_FALSE);
#ifdef D_DDR_SIZE_64M
        d_av_noise_bypass_en(1);
#endif
        p_gui_atv_media_resource_init();
    }
    else
    {
        p_av_set_vid_background(0, p_sys_get_user_background_color(), D_FALSE);
#ifdef D_DDR_SIZE_64M
        d_av_noise_bypass_en(0);
#endif
    }

    if(lastinput == D_VID_IUTPUT_DTV)
    {
        /*�ͷ�epgռ����Դ*/
        p_auxi_free_varstring();

#ifdef D_TV_SUPPORT_TS2NET
        if(ts2net_func_running && input != D_VID_IUTPUT_WIFIDISPLAY)
        {
            d_ts2net_close();
            ts2net_func_running = D_FALSE;
            ts2net_check_enable = D_FALSE;
            p_atv_ts2net_window_hide();
        }
#endif
    }
    if(input == D_VID_IUTPUT_DTV)
    {
        /*���·���epg��Դ*/
        p_auxi_reopen_varstring();
#if  D_CA_SUPPORT_DEF
        {
            //��DTV�е�DTV������CA��ʾ��Ϣ���ʼ�Сͼ��ȵ��������
            p_Ca_BuyMsg_bak(); //����CA��ʾ��Ϣ
            p_Ca_osd_window_bak(); //�����ʼ�Сͼ������(��DTV�»�ȡ���ʼ�Сͼ������ݵ�δ��ʾ������DTVʱ������ʾ)
            p_osd_show_reset();
            p_Ca_window_reshow();
        }
#endif
    }

#if defined( D_TV_MIRACAST_SOURCE) || defined(D_TV_DLNA_SOURCE) || defined(D_TV_SUPPORT_TS2NET)
    if(input == D_VID_IUTPUT_WIFIDISPLAY)
    {
        p_gui_atv_zhilian_resource_init();
    }
#endif

    p_vip_changeinput(lastinput, input);
    backlight_monitor_reset();
    d_av_set_vid_blank(0, D_TRUE);
    d_tv_set_vid_input (g_htv, input);
    p_tvconf_get_cur_zoommode(&ratio_mode, p_vip_get_dbinput(input));

    d_tv_sync(g_htv);
    d_av_set_vid_window(0, 0, 0, -1, -1);
    p_set_ratio_mode (ratio_mode);
    /*���農��/����/����*/
    p_stb_reset_mute_track_volume();
    atv_reset_screen();

#if  D_CA_SUPPORT_DEF
    if(input != D_VID_IUTPUT_DTV) //DTV�е���DTV
    {
        p_Ca_BuyMsg_bak(); //����CA��ʾ��Ϣ
        p_Ca_osd_window_bak(); //�����ʼ�Сͼ������

        d_atv_pop_msg_hide(D_POP_MSG_PRIO_VIDEO_MSG_2); //���CA��ʾ��Ϣ
        p_Ca_osd_window_hide(); //����ʼ�Сͼ��

        d_ca_system_stop();  //ֹͣca��������
        d_gui_clear_layer(D_GUI_LAYER_USER_2);
        p_stb_ca_scroll_show(0);
        p_osd_show_reset();
        p_Ca_window_hide();
    }
#endif

    if(input == D_VID_IUTPUT_DTV)
    {
        if(!p_conf_get_channel_change_mode())
        {
            d_tv_set_chan_change_blank(g_htv, D_TRUE);
        }
        else
        {
            d_tv_set_chan_change_blank(g_htv, D_FALSE);
        }
        d_tv_clear_vid(g_htv);
        d_tv_sync(g_htv);


        p_vip_init(input, 0, 0, 0);
        player = p_stb_get_player(0);
        player->play_atv = D_FALSE;

        d_gui_clear_menu();
        d_gui_clear_layer(D_GUI_LAYER_VIDEO_MESSAGE);
        d_atv_pop_msg_hide(D_POP_MSG_PRIO_VIDEO_MSG_3);
        d_atv_pop_msg_hide(D_POP_MSG_PRIO_VIDEO_MSG_4);
        /*���Ƶ������ʾ*/
        d_gui_clear_layer(D_GUI_LAYER_IME);
        /*��ֹ��ʾ�ź��ж�*/
        p_set_signal_faint_msg_enable(D_FALSE, 0);

#if (defined(HI_P_TV_TYPE_TV_STB))
        p_atv_menu_deinit();
        p_stb_menu_init();
        p_stb_player_win_show (0);
#endif
        hfman = d_fman_get_handle_by_type(D_FEND_DTMB, 0);
        d_fman_set_suspend(hfman, D_FALSE);

        hfman = d_fman_get_handle_by_type(D_FEND_DVBC, 0);
        d_fman_set_suspend(hfman, D_FALSE);

        hfman = d_fman_get_handle_by_type(D_FEND_DVBS, 0);
        d_fman_set_suspend(hfman, D_FALSE);

        p_stb_player_stop(0);
        p_set_signal_faint_msg_enable(D_TRUE, 2);

        srv = p_stb_player_get_curr_srv(0);
        if(srv == -1)
        {
            D_DBSrvInfo info;
            srv = p_conf_get_curr_srv();
            if(D_OK == d_dbase_get_srv_info(srv, &info))
            {
                if(info.srv_type == D_DB_SRV_RADIO)
                {
                    player->play_radio = D_TRUE;
                    player->radio_id = srv;
                    player->radio_num = info.chan_num;
                }
                else if(info.srv_type == D_DB_SRV_TV)
                {
                    player->play_radio = D_FALSE;
                    player->tv_id = srv;
                    player->tv_num = info.chan_num;
                }
            }
        }
#if  D_CA_SUPPORT_DEF
        {
            //DTV��������ʾCA��ʾ��Ϣ,�ʼ�Сͼ���
            p_Ca_BuyMsg_reshow();
            p_Ca_osd_window_show(D_CA_EVT_SC_USER, NULL); //�ʼ�Сͼ��ȵ���ʾ����ʹ��֮ǰ���ݵ�����

            p_stb_ca_scroll_show(1);
            d_ca_system_run(); //����ʾ���������ٻָ�ca����

        }
#endif

        /*���Բ��Ÿ��ֿ��ܵĽ�Ŀ*/
        if (p_stb_player_play_valid (0) >= 0)
        {
            d_av_set_vid_blank(0, D_FALSE);
        }
        else
        {
            /*û�д洢��Ŀ����ʼ�Զ���̨*/
            D_DUMP ("Cannot get any tv program\n");
            p_no_prog_msg(D_TRUE);
            p_atv_channel_info_window_show(0);
        }
        p_monitor_restart();
    }
    else if(input == D_VID_IUTPUT_TV)
    {
        d_tv_set_chan_change_blank(g_htv, D_TRUE);
        d_tv_clear_vid(g_htv);
        d_tv_sync(g_htv);
        p_vip_init(input, 0, 0, 0);
        player = p_stb_get_player(0);
        player->play_atv = D_TRUE;

        d_gui_clear_menu();
        d_gui_clear_layer(D_GUI_LAYER_VIDEO_MESSAGE);
        d_atv_pop_msg_hide(D_POP_MSG_PRIO_VIDEO_MSG_3);
        d_atv_pop_msg_hide(D_POP_MSG_PRIO_VIDEO_MSG_4);
        /*���Ƶ������ʾ*/
        d_gui_clear_layer(D_GUI_LAYER_IME);
        /*��ֹ��ʾ�ź��ж�*/
        p_set_signal_faint_msg_enable(D_FALSE, 0);

        /*����DVB���ź�SI���*/
        hfman = d_fman_get_handle_by_type(D_FEND_ANALOG, 0);
        d_fman_set_suspend(hfman, D_FALSE);

#if (defined(HI_P_TV_TYPE_TV_STB))
        p_stb_menu_deinit();
        p_atv_menu_init();
        p_atv_player_win_show (0);
#else
        d_gdev_set_enable(p_gui_get_hgdev(), D_TRUE);
#endif
        p_stb_player_stop(0);
        p_set_signal_faint_msg_enable(D_TRUE, 2);

        srv = p_stb_player_get_curr_srv(0);
        if(srv == -1)
        {
            D_S16 chan_num;

            p_tvconf_get_boot_chan(&chan_num);

            if(chan_num > 0)
            {
                srv = d_dbase_get_srv_by_num(chan_num, D_DB_SRV_ATV);
            }

            if(srv < 0)
            {
                /*ȡ�ϴβ��ŵĽ�Ŀ*/
                srv = p_conf_get_curr_atv_srv();
            }

            player->atv_id = srv;
        }

        /*���Բ��Ÿ��ֿ��ܵĽ�Ŀ*/
        if (p_stb_player_play_valid (0) >= 0)
        {
            d_av_set_vid_blank(0, D_FALSE);
        }
        else
        {
            /*û�д洢��Ŀ����ʼ�Զ���̨*/
            D_DUMP ("Cannot get any tv program\n");
            p_no_prog_msg(D_TRUE);
            p_atv_tv_chan_info_window_show(0);
        }
    }
    else if(input == D_VID_IUTPUT_TEST)
    {
        D_KeyCode tfilter_keys[] = {D_KEY_POWER, D_KEY_PNL_POWER, D_KEY_EXITOLDMODE};
        d_tv_set_chan_change_blank(g_htv, D_TRUE);
        d_tv_clear_vid(g_htv);
        d_tv_sync(g_htv);

        p_set_ratio_mode (ratio_mode );
        p_vip_init(input, 0, 0, 1);
        player = p_stb_get_player(0);
        player->play_atv = D_FALSE;
        /*�ͷ�epgռ����Դ*/
        p_auxi_free_varstring();
        d_av_stop(0);//Ϊ�˺���ľ���Ч��
        d_gui_clear_menu();
        p_fp_set_filter_keys(&tfilter_keys, sizeof(tfilter_keys) / sizeof(tfilter_keys[0]));
        d_gdev_set_enable(p_gui_get_hgdev(), D_FALSE);

        p_signal_faint_msg(D_FALSE);
        p_set_signal_faint_msg_enable(D_FALSE, 0);

        p_atv_timer_set_show();
    }
    else
    {
        d_tv_set_chan_change_blank(g_htv, D_TRUE);
        d_tv_clear_vid(g_htv);
        d_tv_sync(g_htv);
        p_vip_init(input, 0, 0, 0);
        player = p_stb_get_player(0);
        player->play_atv = D_FALSE ;

        d_gui_clear_menu();
        d_gui_clear_layer(D_GUI_LAYER_VIDEO_MESSAGE);
        d_atv_pop_msg_hide(D_POP_MSG_PRIO_VIDEO_MSG_3);
        d_atv_pop_msg_hide(D_POP_MSG_PRIO_VIDEO_MSG_4);
        /*���Ƶ������ʾ*/
        d_gui_clear_layer(D_GUI_LAYER_IME);
        /*��ֹ��ʾ�ź��ж�*/
		if (input != D_VID_IUTPUT_WIFIDISPLAY)
       	 	p_atv_signal_input_show(input, NULL, NULL);
        p_signal_faint_msg(D_FALSE);
        p_set_signal_faint_msg_enable(D_FALSE, 0);
        d_fman_get_locked_req(player->hfman, D_INVALID_HANDLE);

#if (defined(HI_P_TV_TYPE_TV_STB))
        p_stb_menu_deinit();
        p_atv_menu_init();
        p_atv_player_win_show (0);
#else
        d_gdev_set_enable(p_gui_get_hgdev(), D_TRUE);
#endif
    }

    if((input == D_VID_IUTPUT_AV1) || (input == D_VID_IUTPUT_AV2) || (input == D_VID_IUTPUT_S)\
       || (input == D_VID_IUTPUT_YPBPR) || (input == D_VID_IUTPUT_VGA)\
       || (input == D_VID_IUTPUT_HDMI1) || (input == D_VID_IUTPUT_HDMI2)\
       || (input == D_VID_IUTPUT_HDMI3))
    {
#ifdef D_TV_IAMGE_SOURCE
        if((input == D_VID_IUTPUT_AV1) || (input == D_VID_IUTPUT_AV2))
        {
            hfman = d_fman_get_handle_by_type(D_FEND_CVBS, 0);
            d_fman_set_suspend(hfman, D_FALSE);
            if((input == D_VID_IUTPUT_AV2))
                fendparam.freq = 1;
            else
                fendparam.freq = 0;

            d_fman_set_param (hfman, &fendparam, D_TRUE, (D_FEndType)D_FEND_CVBS, NULL, NULL);
        }
#endif
        d_av_set_vid_blank(0, D_FALSE);
        p_signal_faint_start(1);
        p_set_signal_faint_msg_enable(D_TRUE, 2);
    }
    else if((input == D_VID_IUTPUT_TV) || (input == D_VID_IUTPUT_DTV))
    {
        /* ATV,DTV,������������źţ���ʱ���¼�� 0*/
        p_signal_faint_start(2);
        p_set_signal_faint_msg_enable(D_TRUE, 2);
    }
    else if((input == D_VID_IUTPUT_USB1) || (input == D_VID_IUTPUT_USB2) || (input == D_VID_IUTPUT_USB3) || (input == D_VID_IUTPUT_TEST))
    {
        /* ��ý����,������������źţ���ʱ���¼�� 0*/
        p_signal_faint_start(2);
    }
#ifdef D_TV_LIULINK_SOURCE
    else if ((input == D_VID_IUTPUT_LIULINK))
    {
        p_signal_faint_start(2);
    }
#endif
#if defined( D_TV_MIRACAST_SOURCE) || defined(D_TV_DLNA_SOURCE) || defined(D_TV_SUPPORT_TS2NET)
    else if (input == D_VID_IUTPUT_WIFIDISPLAY)
    {
        p_signal_faint_start(2);
        p_atv_zhilian_main_menu_window_show();
    }
#endif


    return D_OK;
}


