#include "pStb.h"
#include "dAV.h"
#include "pvr.h"
#include "mira.h"
#include "_helper.h"
#include "rbuf.h"
#include "dDebug.h"
#include "dMutex.h"

/* 2.4G是否自动扫描信道*/
#define D_AUTO_SCAN_CHANNEL (1)


static D_Bool  first_run_miracast = D_FALSE;
static D_Bool  mira_open_flag = D_FALSE;
static D_Bool  user_init_flag = D_FALSE;
static D_Bool  deal_data_flag = D_FALSE;
static D_HTask task = D_INVALID_HANDLE;
static D_Bool mira_run_flag = D_FALSE;
static D_HMutex hmutex_mira = D_INVALID_HANDLE;

#define __mira_lock() if(hmutex_mira != D_INVALID_HANDLE){d_mutex_lock(hmutex_mira);}
#define __mira_unlock() if(hmutex_mira != D_INVALID_HANDLE){d_mutex_unlock(hmutex_mira);}

static WIFI_25G_CH_FREQ wifiChannels[] =
{
    WIFI_25G_CH1_FREQ,
    WIFI_25G_CH2_FREQ,
    WIFI_25G_CH3_FREQ,
    WIFI_25G_CH4_FREQ,
    WIFI_25G_CH5_FREQ,
    WIFI_25G_CH6_FREQ,
    WIFI_25G_CH7_FREQ,
    WIFI_25G_CH8_FREQ,
    WIFI_25G_CH9_FREQ,
    WIFI_25G_CH10_FREQ,
    WIFI_25G_CH11_FREQ,
    WIFI_25G_CH12_FREQ,
    WIFI_25G_CH13_FREQ,
    WIFI_25G_CH14_FREQ,
};



#if 1
void pvr_user_init(void)
{
    MSG("\n");
    if(user_init_flag == D_FALSE)
    {
        //d_stb_stop_play();
        d_av_stop(0);
        d_av_set_vid_blank(0, D_TRUE); /*榛戝睆*/
        p_pvr_open();
        d_task_wait(50);
        d_av_set_video_frame_rate(D_VID_FRM_RAT_30);
        d_av_set_tv_ratio_mode(0, D_Overall_Screen);
        user_init_flag = D_TRUE;
        MSG("\n");
    }
    MSG("\n");
}
void pvr_user_uninit(void)
{
    MSG("\n");
    if(user_init_flag)
    {
        user_init_flag = D_FALSE;
        while(deal_data_flag)
        {
            d_task_wait(5);
        }
        p_pvr_close();
        d_task_wait(100);
        d_av_set_video_frame_rate(D_VID_FRM_RAT_RESERVED);
        d_av_set_vid_blank(0, D_TRUE);
        p_atv_zhilian_tv_window_show_status((D_U32)MIRA_PHONE_STATUS_END, NULL);
        p_atv_zhilian_tv_window_show_enable(1);
        MSG("\n");
    }
    MSG("\n");
}
void pvr_user_handlePacket(void* pData, unsigned int dataLen)
{
    PVRDATA * pvr_data = get_default_pvrdata();
    int space = 0, ret_len;

    if(user_init_flag && pvr_data && dataLen > 12)
    {
        deal_data_flag = D_TRUE;
        //D_DUMP("dataLen = %x\n", dataLen);
        space = hidrv_rbuf_space(&(pvr_data->rbuf)) & (~0x1f);
        if(space != 0)
        {
            dataLen -= 12;
            ret_len = hidrv_rbuf_write(&(pvr_data->rbuf), ((uint8_t*)pData) + 12, dataLen);
            if(ret_len != dataLen)
            {
                D_DUMP("ret_len != dataLen !!!  %x != %x\n", ret_len, dataLen);
            }
        }
        else
        {
            MSG("rbuf full !!!!!!!!!!!!!!!!!!!!\n");
        }
        d_pvr_fill_buf();
        deal_data_flag = D_FALSE;
    }
}

static void pvr_user_notify(const char * name, const char * mac, int state)
{
    __mira_lock();
    if(mira_open_flag == D_TRUE)
    {
        D_DUMP("Phone %s, mac: %s, state %d\n", name, mac, state);
        p_atv_zhilian_tv_window_show_status((D_U32)state, (D_Char*)name);
    }
    __mira_unlock();
}

static void _mira_task(D_Ptr p)
{
    mira_run_flag = D_TRUE;
    mira_run();
    D_DUMP("mira task done !!!\n");
}

#if D_AUTO_SCAN_CHANNEL
extern D_Result d_set_ap_name(char* dev_name);
extern D_Result d_make_ap_cfgfile(void);
#endif

D_Result p_mira_open(char * name)
{
    D_Result ret = D_OK;
    int cur_channel;

    if(hmutex_mira == D_INVALID_HANDLE)
    {
        hmutex_mira = d_mutex_create(NULL);
    }

    __mira_lock();
    if(mira_open_flag == D_FALSE)
    {
        D_TaskAttr ta;

        mira_run_flag = D_FALSE;

        srand(d_sys_get_time());
        cur_channel = (rand() % 3) * 5; /* default 1, 6, 11*/

        d_wireless_open(0);
        d_task_wait(50);
        if(d_wireless_check_device("wlan0") < 0)
        {
            D_DUMP("no wlan0 device\n");
            ret = D_ERR_NO_DEV;
        }
        else
        {
            d_wireless_disconnect("wlan0");
            d_task_wait(100);
            my_system("ifconfig wlan0 down");
            d_task_wait(20);
            my_system("ifconfig wlan0 up");
            d_task_wait(20);
#if D_AUTO_SCAN_CHANNEL
            if(first_run_miracast == D_FALSE)
            {
                MSG("\n");
                d_set_ap_name("ap_test");
                d_make_ap_cfgfile();
                d_task_wait(10);
                MSG("\n");
                my_system("/root/dvb/ap_start.sh start");
                d_task_wait(3000);
                if (access("/proc/net/rtl8188eu/wlan0/acs", 0) == 0)
                {
                    MSG("\n");
                    first_run_miracast = D_TRUE;
                    my_system("cp /proc/net/rtl8188eu/wlan0/acs /tmp/acs");
                }
                MSG("\n");
                my_system("/root/dvb/ap_start.sh stop");
                d_task_wait(50);
                d_wireless_close(1);
                d_task_wait(50);
                d_wireless_open(0);
                d_task_wait(50);
            }
#endif
            my_system("/root/dvb/mira.sh start");
            d_task_wait(50);
#if D_AUTO_SCAN_CHANNEL
            {
                int flag = 0, asc_channel = -1;
                char *cmd = NULL;
                FILE * file = NULL;
                char best_channel[8];

                if (access("/tmp/acs", 0) == 0)
                {
                    cmd = "cat /tmp/acs | grep \'Best 2.4G CH\' | awk -F \':\' \'{print $2}\'";
                    file = popen(cmd, "r");
                    if(!file)
                    {
                        MSG("cmd error\n");
                    }
                    else
                    {
                        flag = fread(best_channel, 1, 8, file);
                        if(flag <= 0)
                        {
                            pclose(file);
                        }
                        else
                        {
                            asc_channel = atoi(best_channel) - 1;
                        }
                    }
                    pclose(file);

                    if(asc_channel >= 0 && asc_channel < 11)
                    {
                        D_DUMP("###### acs mira channel: %d, freq: %d ######\n", asc_channel + 1, wifiChannels[asc_channel]);
                        cur_channel = asc_channel;
                    }
                }
            }
#endif

            D_DUMP("###### mira channel: %d, freq: %d ######\n", cur_channel + 1, wifiChannels[cur_channel]);
            mira_set_signal(BAND_25G, wifiChannels[cur_channel]);
            //mira_set_signal(BAND_5G, 5765);

            mira_set_video_format(0x00000000, 0, 0x100);
            mira_set_format_name(name);
            mira_init();
            mira_register_user_handle(pvr_user_init, pvr_user_uninit, pvr_user_handlePacket, pvr_user_notify);

            ta.id = 0;
            ta.stack_size = 8192;
            ta.name = "mira";
            ta.priority = 4;
            task = d_task_create(&ta, _mira_task, name);
            if(task == D_INVALID_HANDLE)
            {
                mira_run_flag = D_TRUE;
            }
            mira_open_flag = D_TRUE;
            ret = D_OK;
        }
    }
    __mira_unlock();
    return ret;
}

D_Result p_mira_close(void)
{
    __mira_lock();
    if(mira_open_flag == D_TRUE)
    {
        D_DUMP("mira_close !!!\n");
        /*等待调用了mira_run，才能mira_close，
        不然后面的d_task_join(task); 退不出来*/
        while(mira_run_flag == D_FALSE)
        {
            d_task_wait(50);
        }
        d_task_wait(40);
        pvr_user_uninit();
        d_task_wait(10);
        MSG("\n");
        mira_close();
        MSG("\n");
        if(task != D_INVALID_HANDLE)
            d_task_join(task);
        task = D_INVALID_HANDLE;
        MSG("\n");

#if D_AUTO_SCAN_CHANNEL
        if (access("/proc/net/rtl8188eu/wlan0/acs", 0) == 0)
        {
            MSG("\n");
            my_system("cp /proc/net/rtl8188eu/wlan0/acs /tmp/acs");
        }
#endif
        my_system("/root/dvb/mira.sh stop");
        d_task_wait(50);
        my_system("ifconfig wlan0 down");
        d_task_wait(20);
        //my_system("ifconfig wlan0 up");
        d_wireless_close(1);

        MSG("\n");
        //d_wireless_start_check(NULL);
        mira_open_flag = D_FALSE;
    }
    __mira_unlock();
    MSG("\n");
    return D_OK;
}
#else
#include <fcntl.h>
static int fd = 0;
static unsigned char * tmp_buf = NULL;
static int buf_len = 4 * 1024;
static running = D_TRUE;
static void _mira_task(D_Ptr p)
{
    PVRDATA * pvr_data = get_default_pvrdata();
    int read_bytes = 0;
    int space = 0;

    while(running)
    {
        read_bytes = 0;
        space = hidrv_rbuf_space(&(pvr_data->rbuf)) & ~0x1f;
        if(space != 0)
        {
            read_bytes = MIN(space, buf_len);
            if(read_bytes > 0)
            {
                read_bytes = read(fd, tmp_buf, read_bytes);
                hidrv_rbuf_write(&(pvr_data->rbuf), tmp_buf, read_bytes);
            }
            if(read_bytes == 0)
            {
                MSG("file read done !! lseek fd to 0, continue read\n");
                lseek(fd, 0, SEEK_SET);
            }
        }
        else
        {
            MSG("rbuf full !!! wait 1s\n");
            sleep(1);
        }
        d_pvr_fill_buf();
    }
    MSG("_mira_task exit !!! \n");
}
int p_mira_open(char * name)
{
    D_TaskAttr ta;

    d_stb_stop_play();
    d_av_set_vid_blank(0, D_TRUE); /*榛戝睆*/

    /*閲嶈闈欓煶/澹伴亾/闊抽噺*/
    d_av_set_aud_mute (0, 0);
    p_stb_player_set_vol(0, 10);

    d_av_set_vid_input (0, D_VID_IUTPUT_DTV);

    p_pvr_open();

    tmp_buf = malloc(buf_len);
    fd = open("/root/video/bian5.ts", O_RDWR);
    SEE("%d", fd);
    if(fd < 0)
    {
        MSG("file open error !\n");
        return -1;
    }

    running = D_TRUE;
    ta.id = 0;
    ta.stack_size = 8192;
    ta.name = "mira";
    ta.priority = 4;
    task = d_task_create(&ta, _mira_task, NULL);
    return 0;
}
void p_mira_close(void)
{
    printf("mira_close !!!\n");
    running = D_FALSE;
    if(task != D_INVALID_HANDLE)
        d_task_join(task);
    task = D_INVALID_HANDLE;
    free(tmp_buf);
    close(fd);
}
#endif
