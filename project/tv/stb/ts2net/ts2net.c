#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <getopt.h>
#include "dMem.h"
#include "pStb.h"
#include "dMsg.h"
#include "dGUI.h"
#include "_helper.h"
#include "pTs2net.h"
//#include "pPvrRecord.h"
#include "pTs2NetRecord.h"
#include "dlna_init.h"
#include "dNetwork.h"

#define _TS2NET_AP_CFGFILE      "/tmp/rtl_hostapd_2G.conf"

static dlna_t * dms = NULL;

static D_HTask ts2net_task = D_INVALID_HANDLE;
static int ch_total = 0;
static unsigned int running_flag;

static char Ts2NetAPName[32] = "hi2611_ap";
static char Ts2NetAPPasswoed[32] = "12345678";
static char Ts2NetFriendlyName[48] = "haierDTV";
static char Ts2NetModelName[32] = "SumaDmsServer";

D_Result d_set_ap_name(char* dev_name)
{
    if(dev_name && (0 != strcmp(Ts2NetAPName, dev_name)))
    {
        snprintf(Ts2NetAPName, sizeof(Ts2NetAPName), "%s", dev_name);
        Ts2NetAPName[sizeof(Ts2NetAPName) - 1] = '\0';
        return D_OK;
    }
    return D_ERR;
}

D_Result d_get_ap_name(char* dev_name, char* password)
{
    if(dev_name && password)
    {
        sprintf(dev_name, "%s", Ts2NetAPName);
        sprintf(password, "%s", Ts2NetAPPasswoed);
        return D_OK;
    }
    return D_ERR;
}

D_Result d_make_ap_cfgfile(void)
{
    FILE * fp = NULL;
    char apbuf[64];

    if(access(_TS2NET_AP_CFGFILE, F_OK) == 0)
    {
        // 文件存在则删除此文件
        unlink(_TS2NET_AP_CFGFILE);
    }

    fp = fopen(_TS2NET_AP_CFGFILE, "w+");
    if(fp == NULL)
    {
        D_DUMP("Open file %s failed!\n", _TS2NET_AP_CFGFILE);
        return D_ERR;
    }
    fprintf(fp, "interface=wlan0\n"
            "driver=nl80211\n"
            "country_code=CN\n"
            "ctrl_interface=/var/run/hostapd\n"
            "ssid=%s\n"
            "channel=6\n"
            "hw_mode=g\n"
            "ieee80211n=1\n"
            "ht_capab=[HT40-][SHORT-GI-20][SHORT-GI-40]\n"
            "wpa=3\n"
            "wpa_pairwise=TKIP CCMP\n"
            "rsn_pairwise=TKIP CCMP\n"
            "wpa_passphrase=%s\n"
            "max_num_sta=255\n"
            "ap_isolate=1\n"
            "ieee80211d=1\n"
            "beacon_int=100\n"
            "dtim_period=2\n"
            "wmm_enabled=1\n",
            Ts2NetAPName, Ts2NetAPPasswoed);
    fclose(fp);
    return D_OK;
}

D_Size _ts2net_get_data (D_U32 dev_id, D_U8 *pbuf, D_Size dlen)
{
    SEE("%ld", dlen);
    return dlen;
}
