#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dDate.h"
#include "dDBase.h"
#include "dFP.h"
#include "pConfig.h"
#include "dFrame.h"
#include "dGUI.h"
#include "dMem.h"
#include "dadporting.h"
#include "dControl.h"
#include "pGuiResource.h"
#include "pPopMsg.h"
#include "pStbMenus.h"
#include "pMem.h"
#include "pPlayer.h"
#include "atv_epg_window.c"


#define EPG_VIDEO_WINDOW_POS_X  358
#define EPG_VIDEO_WINDOW_POS_Y  112
#define EPG_VIDEO_WINDOW_W      274
#define EPG_VIDEO_WINDOW_H      188
#define BUFFER_LEN  64

/** @brief EPG��������*/
#define D_EPG_SEL_DATE          0           /**@briefѡ������*/
#define D_EPG_SEL_CHAN          1           /**@briefѡ��Ƶ��*/
#define D_EPG_SEL_SUB           2           /**@briefѡ��Ԥ����Ŀ*/
#define LIST_ROW_CNT_CHAN       (6)         /**@briefƵ���б������*/
#define LIST_ROW_CNT_EVENT      (6)         /**@brief�¼��б������*/
#define PERIOD_BUF_LEN          (32)        /**@brief�洢��ֹʱ��Ļ�������С*/
#define PROG_NAME_BUF_LEN       (64)        /**@brief�洢�¼����Ļ�������С*/
#define CHAN_NAME_BUF_LEN       (64)        /**@brief�洢Ƶ�����Ļ�������С*/
#define CHAN_NUM_BUF_LEN        (8)         /**@brief�洢Ƶ���ŵĻ�������С*/
#define TITLE_BUF_LEN           (128)       /**@brief�洢��ʾ��ǰʱ��Ļ�������С*/
#define SUBSCIBE_ANSWER         (256)       /**@brief���ԤԼ��ʾ��Ϣ�Ļ�������С*/
#define MAX_CHAN_CNT            (1000)      /**@briefƵ���б���������ֵ*/
#define MAX_PROG_CNT            (1000)      /**@brief�¼��б���������ֵ*/
#define REFRESH_CURR_TIME_PERIOD    (10000) /**@brief10����*/



/** @brief EPG�ڲ����ݽṹ*/
typedef struct
{
    D_S8            curr_date;                                          /**@brief< ��ǰ����*/
    D_ID            old_curr_chan;                                      /**@brief< ��һ��Ƶ����*/
    D_ID            curr_chan;                                          /**@brief< ��ǰƵ����*/
    D_DBRecset      chans;                                              /**@brief< Ƶ����¼��*/
    D_DBRecset      progs;                                              /**@brief< ��Ŀ�¼���¼��*/
    D_ID            chan_ids[MAX_CHAN_CNT];                             /**@brief< Ƶ��ID��Ż�����*/
    D_ID            prog_ids[MAX_PROG_CNT];                             /**@brief< ��ĿID��Ż�����*/
    D_Char          period[LIST_ROW_CNT_EVENT][PERIOD_BUF_LEN];         /**@brief<�¼���ʼ������ʱ��*/
    D_Char          prog_name[LIST_ROW_CNT_EVENT][PROG_NAME_BUF_LEN];
    D_Char          chan_name[LIST_ROW_CNT_CHAN][CHAN_NAME_BUF_LEN];
    D_Char          chan_num[LIST_ROW_CNT_CHAN][CHAN_NUM_BUF_LEN];
    D_U8            sub_mask[(MAX_PROG_CNT + 7) / 8];
    D_Char          week_lab[TITLE_BUF_LEN];                            /**@brief< ��ʾ��ǰ�£��ռ�����*/
    D_Char          curr_time[TITLE_BUF_LEN];                           /**@brief<��ʾ��ǰ��ϸʱ��*/
    D_Char          subscribe_answer[SUBSCIBE_ANSWER];                  /**@brief< EPGԤԼ��ʾ��Ϣ*/
    D_DBSrvType     srv_type;                                           /**@brief< EPG��������*/
    D_U8            epg_type;                                           /**@brief< EPG��������*/
    D_U8            menu_language;
    D_Char          chan_info[BUFFER_LEN];

} EPGData;


static   D_U8           day_of_week = 0;
static   EPGData        *epg_data;
static   D_Bool         chan_get_focus = D_TRUE;
static   D_Char         htimer = D_INVALID_HANDLE;
static   D_Visual       *update_time_vis = NULL;
static   D_ID           week_id[7] = {atv_IDS_SUNDAY, atv_IDS_MONDAY, atv_IDS_TUESDAY, atv_IDS_WENDSDAY, atv_IDS_THURSDAY, atv_IDS_FRIDAY, atv_IDS_SATURDAY};

/** @brief ����ʱ����ʾ
* @param[in] vis Ҫ�����Ŀؼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result update_time (D_Visual * vis) D_FUNCPOSTFIT
{
    D_Time  now;
    D_Date  date;

    if(!vis)
    {
        return D_ERR;
    }
    now = d_time_local_time (d_time_get_time ());
    d_date (now, &date);
    snprintf (epg_data->curr_time, sizeof(epg_data->curr_time), "%04d/%02d/%02d  %s  %02d:%02d",
    date.year + 1900, date.mon + 1, date.mday, d_gui_get_text(week_id[date.wday]), date.hour, date.min);
    d_label_set_text(vis, epg_data->curr_time);

    return D_OK;
}

/** @brief  �жϵ�ǰ���Ƿ�������
* @param[in] year Ҫ�жϵ����
* @return �ɹ�����D_TRUE,ʧ�ܷ���D_FALSE
*/
static D_Bool year_is_leap_year( D_U16 year )D_FUNCPOSTFIT
{
    if( (year % 4 == 0 && year % 100 != 0) || year % 400 == 0 )
    {
        return D_TRUE;
    }
    else
    {
        return D_FALSE;
    }
}

/** @brief  �õ���ǰ����
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result get_curr_day_of_week(void)D_FUNCPOSTFIT
{
    D_Time  now;
    D_Date  date;

    /*�趨��ǰʱ��*/
    now = d_time_local_time (d_time_get_time ());
    if(now > 0)
    {
        d_date (now, &date);
        day_of_week = date.wday;
    }
    return D_OK;
}

/** @brief �õ���ǰ�µ�����
* @param[in] year ��ǰ�����
* @param[in] month ��ǰ���·�
* @return �õ���ǰ�µ�����
*/
static D_S16 get_month_days(D_U16 year, D_U16 month)D_FUNCPOSTFIT
{
    D_S16 return_value = 0;

    switch(month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return_value = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            return_value = 30;
            break;
        case 2:
            if( year_is_leap_year(year) )
            {
                return_value = 29;
            }
            else
            {
                return_value = 28;
            }
            break;
        default:
            return_value = -1;
            break;
    }

    return return_value;
}



/** @brief �õ���ǰ�����Ժ�ĳ�������
* @param[in] curr_date ��ǰ����
* @param[in] off_set ƫ�Ƶ�����
* @param[out] output_date �õ���ǰ�����Ժ�ĳ�������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result get_later_date_by_offset(D_Date *curr_date, D_U8 off_set, D_Date *output_date)D_FUNCPOSTFIT
{
    D_S16 tmp_year;
    D_U8 tmp_month;
    D_U8 tmp_day;
    D_U16 curr_month_days;

    if(curr_date == NULL || output_date == NULL)
    {
        return D_ERR;
    }

    /*off_set:0-6*/
    if(off_set > 6)
    {
        return D_ERR;
    }

    memset(output_date, 0, sizeof(D_Date));

    tmp_year = curr_date->year + 1900;
    tmp_month = curr_date->mon + 1;
    tmp_day = curr_date->mday;

    tmp_day += off_set;
    curr_month_days = get_month_days((D_U16)tmp_year, (D_U16)tmp_month);

    if(tmp_day > curr_month_days)
    {
        tmp_day -= curr_month_days;
        tmp_month ++;
        if(tmp_month > 12)
        {
            tmp_month -= 12;
            tmp_year ++;
        }
    }

    output_date->year = tmp_year;
    output_date->mon = tmp_month;
    output_date->mday = tmp_day;

    return D_OK;
}


/** @brief ��ʾ���ӻ�㲥��Ŀ�б�����
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result
set_chan_list_title(void)D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_Char *title = NULL;

    switch(epg_data->srv_type)
    {
        case D_DB_SRV_TV:
            title = d_gui_get_text(atv_IDS_EPG_LIST);
            break;
        case D_DB_SRV_RADIO:
            title = d_gui_get_text(atv_IDS_EPG_LIST_RADIO);
            break;
        default:
            break;
    }

    /*��ʾ���ӻ�㲥��Ŀ�б����*/
    vis = d_frame_get_control(&atv_epg_window, ID_LABLE_TITLE);
    if(vis)
    {
        d_label_set_text(vis, title);
    }

    return D_OK;
}

/** @brief ��ʾ�¼��б�����
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result
set_evt_list_title(void)D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_Time  now;
    D_Date  date, later_date;

    now = d_time_local_time (d_time_get_time ());
    d_date (now, &date);
    get_later_date_by_offset(&date, epg_data->curr_date, &later_date);

    if(epg_data->menu_language == D_LANG_ENG)
    {
        snprintf (epg_data->week_lab, sizeof(epg_data->week_lab), "%02d - %02d  %s", later_date.mon, later_date.mday, d_gui_get_text(week_id[day_of_week]));
    }
    else
    {
        snprintf (epg_data->week_lab, sizeof(epg_data->week_lab), "%02d��%02d��%s", later_date.mon, later_date.mday, d_gui_get_text(week_id[day_of_week]));
    }

    vis = d_frame_get_control(&atv_epg_window, ID_LABLE_SELECT_DAY);
    if(vis)
    {
        d_label_set_text(vis, epg_data->week_lab);
    }

    return D_OK;
}


/** @brief ͬʱ���Ԥ������ʾ
* @param[in] sel �Ƿ�ȷ��ԤԼ
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result
subscribe_sametime(D_Bool sel)D_FUNCPOSTFIT
{
    D_DBEvtID   evt;
    D_ID    focus;
    D_Visual    *vis;
    D_Image     *img;
    D_Bool  sub = D_TRUE;


    img = d_gui_get_image(atv_IMG_ID_Clock);
    vis = d_frame_get_control (&atv_epg_window, ID_LIST_EVENT);
    if(vis)
    {
        focus = d_list_get_focus (vis, NULL, NULL);

        /*�����ݴ��ж�*/
        if((focus < 0) || (focus >= epg_data->progs.cnt))
        {
            return D_ERR;
        }

        evt = epg_data->prog_ids[focus];
        if(sel)
        {
            D_DBSubID       sub_id;
            D_DBEvtInfo info;

            /*ɾ����ǰ��Ԥ��*/
            if(d_dbase_get_evt_info (evt, &info) >= 0)
            {
                sub_id = d_dbase_get_subscribe_by_time(info.start, info.start + info.duration);
                if(sub_id != -1)
                {
                    d_dbase_delete_subscribe (sub_id);
                }
            }

            /*�û���ȷ����Ԥ����Ŀ*/
            if(epg_data->epg_type != D_EPG_SEL_SUB)
            {
                if(d_dbase_subscribe_evt (evt, sub) < 0)
                    return D_ERR;
            }

            D_SET_MASK (epg_data->sub_mask, focus);
            d_list_set_image (vis, focus, 0, img);
        }
        else
        {
            d_list_set_image (vis, focus, 0, NULL);
        }
    }
    else
    {
        return D_ERR;
    }
    return D_OK;

}


/** @brief Ԥ��һ����Ŀ
* @param[in] vis Ҫ�����Ŀؼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result
epg_subscribe (D_Visual *vis) D_FUNCPOSTFIT
{
    D_ID    focus;
    D_DBEvtID   evt;
    D_DBEvtInfo info;
    D_DBSrvInfo sinfo;
    D_DBSubID   sub_id;
    D_DBEvtInfo sub_info;
    D_Image *img;
    D_Time  time;
    D_Bool  sub = D_FALSE;

    focus = d_list_get_focus (vis, NULL, NULL);
    if((focus < 0) || (focus >= epg_data->progs.cnt))
    {
        return D_ERR;
    }

    evt = epg_data->prog_ids[focus];

    if(d_dbase_get_evt_info (evt, &info) >= 0)
    {
        sub = info.subscribe;
    }
    sub = ! sub;
    if(!sub)
    {
        /*ȡ��Ԥ��*/
        if(epg_data->epg_type != D_EPG_SEL_SUB)
        {
            if(d_dbase_subscribe_evt (evt, sub) < 0)
            {
                return D_ERR;
            }
        }
        D_CLEAR_MASK (epg_data->sub_mask, focus);
    }
    else
    {
        time = d_time_get_time ();
        if(time > info.start)
        {
            if(time >= (info.start + info.duration) )
            {
                return d_atv_pop_select_show(D_POP_MSG_PRIO_MSG_2,
                D_GUI_LAYER_MESSAGE, NULL, d_gui_get_text(atv_IDS_EVENT_OUT_OF_TIME),
                0, D_TRUE, NULL, 0);
            }
            else
            {
                return d_gui_clear_menu();
            }
        }

        /*����Ƿ���Ԥ��ʱ���ͻ*/
        sub_id = d_dbase_get_subscribe_by_time(info.start, info.start + info.duration);
        if(sub_id != -1)
        {
            D_Time start_time, end_time;
            D_Date start_date, end_date;

            d_dbase_get_subscribe_info (sub_id, &sub_info);
            d_dbase_get_srv_info (sub_info.db_srv_id, &sinfo);
            start_time = d_time_local_time (sub_info.start);
            d_date (start_time, &start_date);
            end_time = d_time_local_time (sub_info.start + sub_info.duration);
            d_date (end_time, &end_date);

            sprintf(epg_data->subscribe_answer, d_gui_get_text(atv_IDS_SUBSCRIBE_FAIL),
                    sinfo.name, sub_info.name, start_date.hour, start_date.min, end_date.hour, end_date.min);

            return d_atv_pop_select_show (D_POP_MSG_PRIO_MSG_2,
                                      D_GUI_LAYER_MESSAGE, NULL, epg_data->subscribe_answer, 0, D_TRUE, subscribe_sametime, (D_U32)vis);

        }

        if(d_dbase_subscribe_evt (evt, sub) < 0)
        {
            /*Ԥ����Ŀ������ʾ*/

            d_atv_pop_msg_show (D_POP_MSG_PRIO_MSG_2,
                            D_GUI_LAYER_MESSAGE,
                            D_POP_MSG_MSG,
                            NULL, d_gui_get_text(atv_IDS_REPEAT_TIME1),
                            0, D_POP_MSG_RESPONSE_ANY, D_FALSE, NULL, 0);

            return D_OK;
        }

    }

    /*������ʾ*/
    img = d_gui_get_image(atv_IMG_ID_Clock);
    d_list_set_image (vis, focus, 0, sub ? img : NULL);

    return D_OK;
}



/** @brief����Ƶ���б�
* @param[in] vis Ҫ�����Ŀؼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result
epg_chan_update_list (D_Visual *vis) D_FUNCPOSTFIT
{
    D_ID    start, i;
    D_DBSrvInfo info;

    /*����Ƶ���б���ʾ*/
    start = d_list_get_first_line_id (vis);

    for(i = start; i < start + LIST_ROW_CNT_CHAN; i++)
    {
        if(i >= epg_data->chans.cnt)
        {
            d_list_set_text (vis, i, 0, "");
            d_list_set_text (vis, i, 1, "");
            d_list_set_image (vis, i, 2, NULL);
        }
        else
        {
            if(d_dbase_get_srv_info (epg_data->chan_ids[i], &info) < 0)
            {
                d_list_set_text (vis, i, 0, "");
                d_list_set_text (vis, i, 1, "");
                d_list_set_image (vis, i, 2, NULL);
            }
            else
            {
                snprintf (epg_data->chan_num[i - start], sizeof(epg_data->chan_num[i - start]), "%03d", info.chan_num);

                /*��ʾƵ����*/
                d_list_set_text (vis, i, 0, epg_data->chan_num[i - start]);

                /*��ʾƵ����*/
                if(strlen (info.name))
                {
                    if(info.ca_flag)
                    {
                        sprintf(epg_data->chan_info, "%s  ($)", info.name);
                    }
                    else
                    {
                        sprintf(epg_data->chan_info, "%s", info.name);
                    }
                    strncpy (epg_data->chan_name[i - start], epg_data->chan_info, sizeof (epg_data->chan_name[i - start]) - 1);
                    d_list_set_text (vis, i, 1, epg_data->chan_name[i - start]);
                }
                else
                {

                    snprintf (epg_data->chan_name[i - start], sizeof(epg_data->chan_name[i - start]),
                              "%s%03d", d_gui_get_text(atv_IDS_PRO_NAME),
                              info.chan_num);
                    d_list_set_text (vis, i, 1, epg_data->chan_name[i - start]);

                }
            }
        }
    }

    return D_OK;
}


/** @brief����Ƶ������
* @param[in] vis Ҫ�����Ŀؼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result
epg_chan_update (D_Visual *vis) D_FUNCPOSTFIT
{
    D_ID            curr, i;
    D_DBSrvID   srv = -1;

    curr = epg_data->old_curr_chan;
    epg_data->old_curr_chan = epg_data->curr_chan;
    epg_data->curr_chan = curr;

    d_dbase_rset_empty (&epg_data->chans);
    d_dbase_get_srvs_by_type (&epg_data->chans, epg_data->srv_type, D_FALSE, 0);

    /*�趨��ǰƵ��*/
    if(curr == -1)
    {
        D_StbPlayer *player;

        player = p_stb_get_player (0);
        if(player)
        {
            srv = (epg_data->srv_type == D_DB_SRV_RADIO) ? player->radio_id : player->tv_id;

            for(i = 0; i < epg_data->chans.cnt; i++)
            {
                if(epg_data->chan_ids[i] == srv)
                {
                    epg_data->curr_chan = i;
                    break;
                }
            }
        }
    }


    d_list_set_max_row (vis, epg_data->chans.cnt);

    /*�����б�*/
    epg_chan_update_list (vis);

    return D_OK;
}

/** @brief�����¼�
* @param[in] vis Ҫ�����Ŀؼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result
epg_evt_update_list (D_Visual *vis) D_FUNCPOSTFIT
{
    D_ID    start, i;
    D_DBEvtInfo     info;
    D_Bool  sub;
    D_Char  * name, *period;
    D_Date  sdate, edate;
    D_Time  stime, endtime;
    D_Image * blueimg, *greenimg, *subimg;

    /*ȡ��Ԥ��ͼ��*/
    blueimg = d_gui_get_image(atv_IMG_ID_Blue);
    greenimg = d_gui_get_image(atv_IMG_ID_Green);
    subimg = d_gui_get_image(atv_IMG_ID_Clock);

    /*���·����б���ʾ*/
    start = d_list_get_first_line_id (vis);

    for(i = start; i < start + LIST_ROW_CNT_EVENT; i++)
    {
        d_list_set_image (vis, i, 0, NULL);
        d_list_set_text (vis, i, 1, "");
        d_list_set_text (vis, i, 2, "");
    }

    for(i = start; i < start + LIST_ROW_CNT_EVENT; i++)
    {
        name = NULL;
        period = NULL;
        sub = D_FALSE;
        if (i <  epg_data->progs.cnt)
        {

            /*ȡ�¼���Ϣ*/
            if(d_dbase_get_evt_info (epg_data->prog_ids[i], &info) >= 0)
            {
                strncpy (epg_data->prog_name[i - start], info.name,
                D_MIN(sizeof(info.name), sizeof(epg_data->prog_name[i - start])) - 1);
                name = epg_data->prog_name[i - start];

                sub = info.subscribe;

                stime = d_time_local_time (info.start);
                endtime = d_time_local_time (info.start + info.duration);
                d_date (stime, &sdate);
                d_date (endtime, &edate);
                snprintf (epg_data->period[i - start], sizeof (epg_data->period[i - start]),
                "%02d:%02d-%02d:%02d", sdate.hour, sdate.min, edate.hour, edate.min);

                /*������¼��ж������ڲ��Ż����ѹ���*/
                if(!epg_data->curr_date)
                {
                    /*�趨ͼ��*/
                    if(endtime < d_time_local_time(d_time_get_time()))
                    {
                        d_list_set_image (vis, i, 0, blueimg);
                    }
                    else if((endtime >= d_time_local_time(d_time_get_time())) && (stime <= d_time_local_time(d_time_get_time())))
                    {
                        d_list_set_image (vis, i, 0, greenimg);
                    }
                    else
                    {
                        d_list_set_image (vis, i, 0, NULL);
                    }

                }
                period = epg_data->period[i - start];

            }
        }

        if(sub)
        {
            d_list_set_image (vis, i, 0, subimg);
        }

        /*�趨ʱ��*/
        d_list_set_text (vis, i, 1, period);

        /*�趨�¼���*/
        d_list_set_text (vis, i, 2, name);

    }

    return D_OK;
}

/** @brief����EPG��Ŀ��Ϣ
* @param[in] vis Ҫ�����Ŀؼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result
epg_evt_update (D_Visual *vis) D_FUNCPOSTFIT
{
    D_Time  stime, etime;
    D_DBEvtInfo info;

    if(! epg_data)
        return D_ERR;

    d_dbase_rset_empty (&epg_data->progs);

    /*ȡ����*/
    switch (epg_data->epg_type)
    {
        case D_EPG_SEL_DATE:
        case D_EPG_SEL_CHAN:
        {
            D_DBSrvID   srv = -1;
            D_Time      begin, end;
            D_Time      today;

            /*ȡһ��Ľ�Ŀ*/
            if(epg_data->curr_chan < epg_data->chans.cnt)
            {
                srv = epg_data->chan_ids[epg_data->curr_chan];
                today  = d_time_local_time (d_time_get_time());
                begin = today + epg_data->curr_date * 3600 * 24;
                begin -= begin % (3600 * 24);
                end = begin + 3600 * 24;

                begin = d_time_utc_time (begin);
                end = d_time_utc_time (end);

                d_dbase_get_evts (srv, begin, end, &epg_data->progs);

            }
        }
        break;
        case D_EPG_SEL_SUB:
            break;
        default:
            return D_ERR;
    }

    if(!epg_data->curr_date)
    {
        if(epg_data->progs.cnt != 0)
        {
            D_ID focus_id;

            focus_id = d_list_get_focus (vis, NULL, NULL);
            if (focus_id >= epg_data->progs.cnt)
            {
                d_list_set_focus (vis, 0, 0);
            }
        }
    }

    d_list_set_max_row (vis, epg_data->progs.cnt);
    epg_evt_update_list (vis);

    return D_OK;
}


/** @brief Ƶ���б���¼��ص�
* @param[in] vis Ҫ�����Ŀؼ�
* @param[in] evt ��Ϣ�¼�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result
chan_list_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_DBSrvID      srv;
    D_Visual       * list, *vis_window;
    D_ID           curr;

    switch (evt->type)
    {
        case D_EVT_FP:
        {
            switch (evt->fp.key)
            {
                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    if(epg_data->curr_chan < epg_data->chans.cnt)
                    {
                        srv = epg_data->chan_ids[epg_data->curr_chan];
                        if(srv >= 0)
                        {
                            return d_gui_clear_menu();
                        }
                    }
                    return D_ERR;

                /*���¼�����Ӧ���¼�*/
                case D_KEY_PNL_U:
                case D_KEY_PNL_D:
                case D_KEY_UP:
                case D_KEY_DOWN:
                case D_KEY_PGDOWN:
                case D_KEY_PGUP:
                    return D_OK;

                default:
                    return D_ERR;
            }
        }
        case D_EVT_DATA_CHANGED:
            epg_chan_update_list (vis);
            return D_OK;
        case D_EVT_SELECTED:

            /* ��̨ʱ���ָ���ʾ����Ľ�Ŀ��Ϣ */
            list = d_frame_get_control (&atv_epg_window, ID_LIST_EVENT);
            if(list)
            {
                curr = d_list_get_focus (vis, NULL, NULL);
                if((curr < 0) || (curr >= epg_data->chans.cnt))
                {
                    return D_ERR;
                }

                srv = epg_data->chan_ids[curr];
                if(srv >= 0)
                {
                    p_stb_player_play_srv (0, srv);

                }
                epg_data->curr_chan = curr;

                /*��̨��ʾ����EPG*/
                epg_data->curr_date = 0;
                get_curr_day_of_week();
                set_evt_list_title();
                d_list_set_focus(list, 0, 0);
                epg_evt_update (list);
            }
            return D_OK;

        default:
            break;
    }

    return D_ERR;
}


/** @brief �¼��б���¼��ص�
* @param[in] vis Ҫ�����Ŀؼ�
* @param[in] evt ��Ϣ�¼�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result
epg_list_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                /*��ȡһ�ܵ�EPG��Ϣ*/
                case D_KEY_RIGHT:
                case D_KEY_PNL_R:
                    epg_data->curr_date++;
                    if(epg_data->curr_date > 6)
                    {
                        epg_data->curr_date = 0;
                    }
                    day_of_week++;
                    if(day_of_week > 6)
                    {
                        day_of_week = 0;
                    }
                    epg_evt_update (vis);
                    set_evt_list_title();
                    return D_OK;

                case D_KEY_LEFT:
                case D_KEY_PNL_L:
                    if(epg_data->curr_date == 0 )
                    {
                        epg_data->curr_date = 7;
                    }
                    epg_data->curr_date--;
                    if( day_of_week == 0 )
                    {
                        day_of_week = 7;
                    }
                    day_of_week--;
                    epg_evt_update (vis);
                    set_evt_list_title();
                    return D_OK;

                case D_KEY_OK:
                case D_KEY_PNL_OK:
                    epg_subscribe (vis);
                    return D_OK;
                    break;

                /*���¼�����Ӧ���¼�*/
                case D_KEY_PNL_U:
                case D_KEY_PNL_D:
                case D_KEY_UP:
                case D_KEY_DOWN:
                case D_KEY_PGDOWN:
                case D_KEY_PGUP:
                    return D_OK;
            }
            break;
        case D_EVT_DATA_CHANGED:
            epg_evt_update_list (vis);
            return D_OK;
        case D_EVT_SELECTED:
            break;
        default:
            break;
    }

    return D_ERR;
}



/** @brief EPG�����¼��ص�
* @param[in] vis Ҫ�����Ŀؼ�
* @param[in] evt ��Ϣ�¼�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
static D_Result
atv_epg_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Visual *rvis;
    D_StbPlayer *player;

    switch (evt->type)
    {
        case D_EVT_TIMER:
            vis = d_frame_get_control (&atv_epg_window, ID_LIST_EVENT);
            if (vis)
            {
                epg_evt_update (vis);
            }
            return update_time(update_time_vis);

        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_MENU:
                    d_gui_clear_menu ();
                    return D_OK;
                    break;
                case D_KEY_BACK:
                    return d_gui_upper_menu ();
                    break;
                case D_KEY_RED:
                    if(chan_get_focus)
                    {
                        chan_get_focus = D_FALSE;
                        d_vis_set_focus(d_frame_get_control(&atv_epg_window, ID_LIST_EVENT) );
                        rvis =  d_frame_get_control (&atv_epg_window, ID_LABLE_PROG_OR_EVENT);
                        if(rvis)
                        {
                            d_label_set_text(rvis, d_gui_get_text(atv_IDS_EVENT_NAME));
                        }

                    }
                    else
                    {
                        chan_get_focus = D_TRUE;
                        d_vis_set_focus(d_frame_get_control(&atv_epg_window, ID_LIST_CHANNEL) );
                        rvis =  d_frame_get_control (&atv_epg_window, ID_LABLE_PROG_OR_EVENT);
                        if(rvis)
                        {
                            d_label_set_text(rvis, d_gui_get_text(atv_IDS_EPGINFO));
                        }

                    }
                    return D_OK;
                    break;
                default:
                    break;
            }

            break;
        case D_EVT_DESTROY:
            p_ad_show_destroy(DAD_STB_EPG);
            d_vis_unsubscribe_evt (vis);

            if(htimer != D_INVALID_HANDLE)
            {
                d_timer_destroy(htimer);
                htimer = D_INVALID_HANDLE;
            }

            if(epg_data)
            {
                PROJECT_FREE(epg_data);
                epg_data = NULL;
            }
            p_set_signal_faint_msg_enable(D_FALSE, 2);
            break;
        default:
            break;
    }

    return D_ERR;
}


/** @brief EPG���ڳ�ʼ��
* @param[in] frm Ҫ��ʼ���Ĵ���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
atv_epg_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual        *vis;
    D_StbPlayer *player;
    D_Result ad_check = D_ERR;

    /*��ʼ�����ݽṹ*/
    epg_data = (EPGData*) PROJECT_ALLOC(sizeof (EPGData));
    if (! epg_data)
        return D_ERR;

    update_time_vis = NULL;
    epg_data->epg_type = D_EPG_SEL_CHAN;
    epg_data->curr_date = 0;
    epg_data->curr_chan = -1;
    epg_data->old_curr_chan = -1;
    epg_data->menu_language = p_conf_get_lang();

    chan_get_focus = D_TRUE;

    p_stb_player_get_curr_chan_num (0, &epg_data->srv_type);
    set_chan_list_title();

    /*ɾ������Ԥ��*/
    d_dbase_check_subscribe(D_TRUE, P_SUBSCRIBE_TIME, NULL);


    d_dbase_rset_init (&epg_data->chans, MAX_CHAN_CNT, epg_data->chan_ids);
    d_dbase_rset_init (&epg_data->progs, MAX_PROG_CNT, epg_data->prog_ids);

    /*�趨����*/
    vis = d_frame_get_control (frm, ID_LIST_CHANNEL);
    if(vis)
    {
        d_vis_set_focus (vis);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);

        /*���´�����ʾ*/
        epg_chan_update (vis);

        if(epg_data->curr_chan == -1)
        {
            epg_data->curr_chan = 0;
        }

        /*�趨�б��¼�����*/
        d_vis_set_handler (vis, chan_list_handler);

        /*�趨��ǰƵ��*/
        if(epg_data->curr_chan != -1)
        {
            d_list_set_focus (vis, epg_data->curr_chan, 0);
        }
    }

    /*�趨�¼��ص�*/
    vis = d_frame_get_control (frm, ID_LIST_EVENT);
    if(vis)
    {
        d_vis_set_handler (vis, epg_list_handler);
        d_vis_set_focusable(vis, D_FALSE);
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK, D_INVALID_HANDLE);

        /*�����¼���ʾ*/
        epg_evt_update (vis);
        d_list_set_focus(vis, 0, 0);
    }

    /*�趨��ƵС����*/
    if(0 == d_gui_get_menu_level())
    {
        player = p_stb_get_player(0);
        //      d_tv_set_vid_window (player->htv, EPG_VIDEO_WINDOW_POS_X, EPG_VIDEO_WINDOW_POS_Y,\
//              EPG_VIDEO_WINDOW_W, EPG_VIDEO_WINDOW_H);
    }

    /*�õ���ǰ����*/
    get_curr_day_of_week();

    set_evt_list_title();

    /*�趨�����¼�*/
    vis = d_frame_get_control (frm, 0);
    if(vis)
    {
        /*��ǰʱ��ˢ�¶�ʱ��*/
        htimer = d_timer_create (NULL, REFRESH_CURR_TIME_PERIOD, d_gui_get_queue());
        d_vis_subscribe_evt (vis, D_EVT_TIMER_MASK, htimer);

        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK & ~D_EVT_UP_DOWN_KEY_MASK, D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_epg_window_handler);
    }

    update_time_vis = d_frame_get_control (frm, ID_LABLE_TIME);
    if(update_time_vis)
    {
        update_time(update_time_vis);
    }

    p_set_signal_faint_msg_enable(D_TRUE, 1);
    d_pop_msg_reshow();

    return D_OK;
}
/** @breif ��ʾEPG����*/
D_Result
p_stb_atv_epg_window_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&atv_epg_window, D_TRUE);
}

