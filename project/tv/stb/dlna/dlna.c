#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <getopt.h>
#include "dDebug.h"
#include "pStb.h"
#include "dMsg.h"
#include "dGUI.h"
#include "_helper.h"
#include "pConfig.h"
#include "dlna_init.h"
#include "dEvent.h"
#include "dCBMan.h"

/**地址最大长度*/
#define DLNA_URL_MAX_LEN (1024)
#define DLNA_TITLE_MAX_LEN (256)

static dlna_t * dlna = NULL;
static D_HTask task = D_INVALID_HANDLE;

static PlayerStatus ps;
static int c_time = 0, total_time = 3600;
static unsigned int start_play_flag = 0;
static unsigned int check_end_counter = 0;
static D_U32 last_play_time = 0;
static char* dlna_last_url = NULL;
static char* dlan_title = NULL;
static D_HEvent hevent_stop = D_INVALID_HANDLE;
static D_Handle hcbman_gui = D_INVALID_HANDLE;

/**计算时间间隔*/
#define DLNA_CALC_TIME(_a, _b) ((_a <= _b) ? (_b - _a) : (0xFFFFFFFF - _a + _b))

/** @brief 设置回调函数
* @param parm   cb 回调函数
*/
static void dlna_gui_msg_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)
{
    D_UserMsg *msg = (D_UserMsg *)obj_data;
    if(msg->type == D_MSG_USER1 && msg->param1 == USER_MSG_PARAM1_DLNA_NO_CONNECT)
    {
        if(hevent_stop != D_INVALID_HANDLE)
        {
            d_event_signal(hevent_stop);
        }
    }
}

/**等待播放退出结束*/
static void wait_stop_end(D_U32 timeout)
{  
    int cnt = 15;

    if(ps.state != PLAYER_STATUS_STOP && ps.state != PLAYER_STATUS_FINISHED && hevent_stop != D_INVALID_HANDLE)
    {
        timeout = D_MIN(30000, timeout);
        cnt = (int)(timeout/500);
        while(cnt--)
        {
            if(D_OK == d_event_wait(hevent_stop, 500))
                break;   
            
            if(ps.state == PLAYER_STATUS_STOP || ps.state == PLAYER_STATUS_FINISHED)
                break;
        }
        d_task_wait(4);
    }
}

void my_player_stop(void)
{
    D_UserMsg msg;

    D_DUMP("%s\n", __FUNCTION__);

    if(hevent_stop != D_INVALID_HANDLE)
        d_event_clear(hevent_stop);
    
    c_time = 0;
    msg.type = D_MSG_USER1;
    msg.handle = D_INVALID_HANDLE;
    msg.param1 = USER_MSG_PARAM1_DLNA_NO_CONNECT;
    msg.param2 = 0;
    d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
    /** 等待播放结束，防止直接发给gui的播放消息处理出问题*/
    wait_stop_end(15000); 
    ps.state = PLAYER_STATUS_STOP;
     ps.curTime = 0;
    start_play_flag = 0;
    check_end_counter = 0;
    last_play_time = 0;
}

void my_player_play(char * title, char * url)
{
    D_UserMsg msg;
    D_U32 cur_time, dur_time;

    if((!title) || (!url))
        return;

    if(dlna_last_url == NULL)
    {
        dlna_last_url = d_mem_alloc(0, DLNA_URL_MAX_LEN);
        if(dlna_last_url == NULL)
        {
            D_DUMP("%s, dlna_last_url == NULL\n", __FUNCTION__);
            return ;
        }
        memset(dlna_last_url, 0x00, DLNA_URL_MAX_LEN);
    }

    if(dlan_title == NULL)
    {
        dlan_title = d_mem_alloc(0, DLNA_TITLE_MAX_LEN);
        if(dlan_title == NULL)
        {
            D_DUMP("%s, dlna_title == NULL\n", __FUNCTION__);
            return ;
        }
        memset(dlan_title, 0x00, DLNA_TITLE_MAX_LEN);
    }

    cur_time = d_sys_get_time();
    D_DUMP("%s, t %d\n", __FUNCTION__, cur_time);

    dur_time = DLNA_CALC_TIME(last_play_time, cur_time);
    if(dur_time < 10000 && (ps.state != PLAYER_STATUS_DATA_BUFFER && ps.state != PLAYER_STATUS_FINISHED) && 0 == strcmp(dlna_last_url, url))
    {
        last_play_time = cur_time;
        D_DUMP("%s url same, dur_time %d\n", __FUNCTION__, dur_time);
        return;
    }

    if(ps.state == PLAYER_STATUS_PLAYING || ps.state == PLAYER_STATUS_PAUSED || ps.state == PLAYER_STATUS_DATA_BUFFER)
    {
        my_player_stop();
    }

    c_time = 0;
    last_play_time = cur_time;
    snprintf(dlna_last_url, DLNA_URL_MAX_LEN, "%s", url);
    snprintf(dlan_title, DLNA_TITLE_MAX_LEN, "%s", title);

    msg.type = D_MSG_USER1;
    msg.handle = D_INVALID_HANDLE;
    msg.param1 = USER_MSG_PARAM1_DLNA_CONNECT;
    msg.param2 = (D_U32)dlna_last_url;
    msg.param3 = (D_U32)dlan_title;
    ps.state = PLAYER_STATUS_DATA_BUFFER; //PLAYER_STATUS_PLAYING; //
    start_play_flag = 1;
    check_end_counter = 0;
    d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
}
PlayerStatus * my_player_get_status(void)
{
    /* 避免异常情况播放界面未退出*/
    if(c_time >= (total_time + 1))
    {
        check_end_counter++;
        if(check_end_counter >= 5)
        {
            my_player_stop();
            ps.state = PLAYER_STATUS_FINISHED;
        }
    }
    else
    {
        check_end_counter = 0;
    }

    ps.percent = 0;
    ps.curTime = c_time;
    ps.totalTime = total_time;
    //ps.percent = (total_time > 0) ? (c_time *100 /total_time) : 0;

    //D_DUMP("my_player_get_status %d\n", ps.state);
    return &ps;
}
void my_player_pause(void)
{
    D_DUMP("my_player_pause\n");
    if(ps.state != PLAYER_STATUS_STOP && ps.state != PLAYER_STATUS_FINISHED)
    {
        D_UserMsg msg;
        msg.type = D_MSG_USER1;
        msg.handle = D_INVALID_HANDLE;
        msg.param1 = USER_MSG_PARAM1_DLNA_STATUS;
        msg.param2 = PLAYER_STATUS_PAUSED;

        ps.state = PLAYER_STATUS_PAUSED;

        d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
    }
}
void my_player_resume(void)
{
    D_DUMP("my_player_resume\n");
    if(ps.state != PLAYER_STATUS_STOP && ps.state != PLAYER_STATUS_FINISHED)
    {
        D_UserMsg msg;
        msg.type = D_MSG_USER1;
        msg.handle = D_INVALID_HANDLE;
        msg.param1 = USER_MSG_PARAM1_DLNA_STATUS;
        msg.param2 = PLAYER_STATUS_PLAYING;

        ps.state = PLAYER_STATUS_PLAYING;

        d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
    }
}
void my_player_seek(unsigned int sec)
{
    D_DUMP("my_player_seek sec %d\n", sec);
    if(ps.state != PLAYER_STATUS_STOP && ps.state != PLAYER_STATUS_FINISHED)
    {
        D_UserMsg msg;
        /* 刚开始播放，如果seek太靠近开头，则不操作*/
        if(start_play_flag)
        {
            start_play_flag = 0;
            if(c_time < 10 && D_ABS((c_time - (int)sec)) < 20)
            {
                return ;
            }
        }

        msg.type = D_MSG_USER1;
        msg.handle = D_INVALID_HANDLE;
        msg.param1 = USER_MSG_PARAM1_DLNA_SEEK;
        msg.param2 = sec;

        d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
        c_time = sec;
    }
}
int my_player_get_volume(void)
{
    int vol = 0;
    vol = p_conf_get_volume();
    /*转换为100级音量*/
    vol = vol * 100 / P_VOLUME_MAX;
    D_DUMP("my_player_get_volume %d\n", vol);
    return vol;

}
void my_player_set_volume(unsigned int volume)
{
    D_UserMsg msg;
    D_DUMP("my_player_set_volume %d\n", volume);
    /*转换为菜单音量*/
    volume = volume * P_VOLUME_MAX / 100;
    msg.type = D_MSG_USER1;
    msg.handle = D_INVALID_HANDLE;
    msg.param1 = USER_MSG_PARAM1_DLNA_VOLUME;
    msg.param2 = volume;
    d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
}

void my_player_set_mute(unsigned int mute)// 1: mute 0: unmute
{
    D_UserMsg msg;
    D_DUMP("my_player_set_mute %d\n", mute);
    msg.type = D_MSG_USER1;
    msg.handle = D_INVALID_HANDLE;
    msg.param1 = USER_MSG_PARAM1_DLNA_MUTE;
    msg.param2 = mute;
    d_queue_send(d_gui_get_queue(), (D_U8*)&msg, sizeof(D_UserMsg));
}

PlayerControl _pc =
{
    ._player_play = my_player_play,
    ._player_stop = my_player_stop,
    ._player_get_status = my_player_get_status,
    ._player_pause = my_player_pause,
    ._player_resume = my_player_resume,
    ._player_seek = my_player_seek,
    ._player_get_volume = my_player_get_volume,
    ._player_set_volume = my_player_set_volume,
    ._player_set_mute = my_player_set_mute,
};

static void _dlna_task(D_Ptr p)
{
    char * name = (char *)p;
    D_DUMP(" !!! DLNA open !!!\n");

    DLNA_Set_friendly_name(name);
    dlna = DLNA_Init(DMR_MODE, &_pc);
    if(dlna)
    {
        if(DLNA_ST_OK != DLNA_Run(dlna))
        {
            D_DUMP(" DLNA_Run error !!!\n");
        }
    }
}
void d_dlna_open(char * name)
{
    D_TaskAttr ta;

    memset(&ps, 0x00, sizeof(PlayerStatus));
    ps.state = PLAYER_STATUS_STOP;

    if(!dlna && (task == D_INVALID_HANDLE))
    {
        ta.id = 0;
        ta.stack_size = 8192;
        ta.name = "dlna";
        ta.priority = 4;
        task = d_task_create(&ta, _dlna_task, name);
        d_task_wait(50);
    }
    
    if(hevent_stop == D_INVALID_HANDLE)
    {
        hevent_stop = d_event_create(NULL);
    }

    if(hcbman_gui == D_INVALID_HANDLE)
    {
        hcbman_gui = d_cbman_subscribe(PL_GUI_DISP_MSG_RET, D_INVALID_HANDLE, dlna_gui_msg_cb, NULL);
    }
}
void d_dlna_close(void)
{
    if(!dlna)
        return;
    D_DUMP(" !!! DLNA close !!!\n");

    if(task != D_INVALID_HANDLE)
        d_task_join(task);
    task = D_INVALID_HANDLE;

    DLNA_Uninit(dlna);
    dlna = NULL;

    if(dlna_last_url)
    {
        d_mem_free(dlna_last_url);
        dlna_last_url = NULL;
    }
    
    if(dlan_title)
    {
        d_mem_free(dlan_title);
        dlan_title = NULL;
    }

    if(hevent_stop != D_INVALID_HANDLE)
    {
        d_event_destroy(hevent_stop);
        hevent_stop = D_INVALID_HANDLE;
    }

    if(hcbman_gui != D_INVALID_HANDLE)
    {
        d_cbman_unsubscribe(hcbman_gui);
        hcbman_gui = D_INVALID_HANDLE;
    }
}

void d_dlna_set_status(PlayStatus status)
{
    if(dlna && task != D_INVALID_HANDLE)
    {
        ps.state = status;
    }
}

void d_dlna_set_playtime(D_U32 playtime)
{
    if(dlna && task != D_INVALID_HANDLE)
    {
        if(((int)playtime) < 0 || ((int)playtime) >= 360000) // 100h
        {
            D_DUMP("DLNA playtime = %d !!!!!\n", ((int)playtime));
        }
        else
        {
            c_time = (int)playtime;
        }
    }
}

void d_dlna_set_totaltime(D_U32 totaltime)
{
    if(dlna && task != D_INVALID_HANDLE)
    {
        total_time = (int)totaltime;
    }
}

#if 0
int main (int argc, char * argv[])
{
    dlna_t * dlna = NULL;
    int c;

    ps.state = PLAYER_STATUS_STOP;
    dlna = DLNA_Init(&_pc);

    printf ("Hit 'q' or 'Q' + Enter to shutdown\n");
    while (1)
    {
        c = getchar ();
        if (c == 'q' || c == 'Q')
            break;
    }

    DLNA_Uninit(dlna);
    return 0;
}
#endif

