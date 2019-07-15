#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mira_user_type.h"

typedef enum {
	BAND_25G,
	BAND_5G
}WIFI_BAND;

typedef enum {
	WIFI_25G_CH1_FREQ = 2412,
	WIFI_25G_CH2_FREQ = 2417,
	WIFI_25G_CH3_FREQ = 2422,
	WIFI_25G_CH4_FREQ = 2427,
	WIFI_25G_CH5_FREQ = 2432,
	WIFI_25G_CH6_FREQ = 2437,
	WIFI_25G_CH7_FREQ = 2442,
	WIFI_25G_CH8_FREQ = 2447,
	WIFI_25G_CH9_FREQ = 2452,
	WIFI_25G_CH10_FREQ = 2457,
	WIFI_25G_CH11_FREQ = 2462,
	WIFI_25G_CH12_FREQ = 2467,
	WIFI_25G_CH13_FREQ = 2472,
	WIFI_25G_CH14_FREQ = 2484,
}WIFI_25G_CH_FREQ;

typedef enum {
	/* 40MHz */
	WIFI_5G_CH42_FREQ = 5210,
	WIFI_5G_CH50_FREQ = 5250,
	WIFI_5G_CH58_FREQ = 5290,
	WIFI_5G_CH152_FREQ = 5760,
	WIFI_5G_CH160_FREQ = 5800,

	/* 20MHz */
	WIFI_5G_CH36_FREQ = 5180,
	WIFI_5G_CH40_FREQ = 5200,
	WIFI_5G_CH44_FREQ = 5220,
	WIFI_5G_CH48_FREQ = 5240,
	WIFI_5G_CH52_FREQ = 5260,
	WIFI_5G_CH56_FREQ = 5290,
	WIFI_5G_CH60_FREQ = 5300,
	WIFI_5G_CH64_FREQ = 5320,

	WIFI_5G_CH149_FREQ = 5745,
	WIFI_5G_CH153_FREQ = 5765,
	WIFI_5G_CH157_FREQ = 5785,
	WIFI_5G_CH161_FREQ = 5805,
	WIFI_5G_CH165_FREQ = 5825,
}WIFI_5G_CH_FREQ;

extern int mira_init(void);
extern void mira_run(void);
extern void mira_close(void);
extern void mira_set_signal(int band, int freq);
extern void mira_set_video_format(int cea, int vesa, int hh);
extern void mira_set_format_name(char * name);
extern void mira_register_user_handle(_user_media_init _fn_init, _user_media_uninit _fn_uninit, _user_media_handlePacket _fn_handle, _user_media_notify_state _fn_notify);
