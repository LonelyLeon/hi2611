#ifndef ___atv_LANGUAGE_SOURCE_IDS_DEFINE_FILE__
#define	___atv_LANGUAGE_SOURCE_IDS_DEFINE_FILE__

#include "dTypes.h"


#define	atv_LAN_ENUM_START	0x4000
enum {
	atv_IDS_NULL=atv_LAN_ENUM_START,
	atv_IDS_CONTRAST,	/* 0x0001 */
	atv_IDS_BRIGHTNESS,	/* 0x0002 */
	atv_IDS_COLOR,	/* 0x0003 */
	atv_IDS_SHARPNESS,	/* 0x0004 */
	atv_IDS_PICTURE_MODE,	/* 0x0005 */
	atv_IDS_ASPECT_RATIO,	/* 0x0006 */
	atv_IDS_COLOR_TEMP,	/* 0x0007 */
	atv_IDS_PICTURE,	/* 0x0008 */
	atv_IDS_SOUND,	/* 0x0009 */
	atv_IDS_CHANNEL,	/* 0x000a */
	atv_IDS_FUNCTION,	/* 0x000b */
	atv_IDS_ADJUST,	/* 0x000c */
	atv_IDS_TIME,	/* 0x000d */
	atv_IDS_BACK,	/* 0x000e */
	atv_IDS_MOVE,	/* 0x000f */
	atv_IDS_OK,	/* 0x0010 */
	atv_IDS_TINT,	/* 0x0011 */
	atv_IDS_VOLUME,	/* 0x0012 */
	atv_IDS_BALANCE,	/* 0x0013 */
	atv_IDS_DIGITAL_TONE,	/* 0x0014 */
	atv_IDS_SRS,	/* 0x0015 */
	atv_IDS_AVL,	/* 0x0016 */
	atv_IDS_PROGRAM_EDIT,	/* 0x0017 */
	atv_IDS_AUTO_TUNING,	/* 0x0018 */
	atv_IDS_EXCHANGE,	/* 0x0019 */
	atv_IDS_OSD_LANGUAGE,	/* 0x001a */
	atv_IDS_MENU_TIMEOUT,	/* 0x001b */
	atv_IDS_DNR,	/* 0x001c */
	atv_IDS_BULE_SCREEN,	/* 0x001d */
	atv_IDS_BACKLIGHT,	/* 0x001e */
	atv_IDS_RESET,	/* 0x001f */
	atv_IDS_IMAGE_POSITION,	/* 0x0020 */
	atv_IDS_HORIZONTAL_AMPLITUDE,	/* 0x0021 */
	atv_IDS_VERTICAL_AMPLITUDE,	/* 0x0022 */
	atv_IDS_AUTO_ADJUST,	/* 0x0023 */
	atv_IDS_CLOCK,	/* 0x0024 */
	atv_IDS_PHASE,	/* 0x0025 */
	atv_IDS_CURRENT_TIME,	/* 0x0026 */
	atv_IDS_OFF_TIME,	/* 0x0027 */
	atv_IDS_ON_TIME,	/* 0x0028 */
	atv_IDS_ON_CHANNEL,	/* 0x0029 */
	atv_IDS_REMIND_TIME,	/* 0x002a */
	atv_IDS_REMIND_CHANNEL,	/* 0x002b */
	atv_IDS_SLEEP_TIMER,	/* 0x002c */
	atv_IDS_TV,	/* 0x002d */
	atv_IDS_DTV,	/* 0x002e */
	atv_IDS_AV,	/* 0x002f */
	atv_IDS_AV1,	/* 0x0030 */
	atv_IDS_AV2,	/* 0x0031 */
	atv_IDS_YPBPR,	/* 0x0032 */
	atv_IDS_HDMI,	/* 0x0033 */
	atv_IDS_HDMI1,	/* 0x0034 */
	atv_IDS_HDMI2,	/* 0x0035 */
	atv_IDS_PC,	/* 0x0036 */
	atv_IDS_USB,	/* 0x0037 */
	atv_IDS_SOURCE,	/* 0x0038 */
	atv_IDS_STANDARD,	/* 0x0039 */
	atv_IDS_MILD,	/* 0x003a */
	atv_IDS_USER,	/* 0x003b */
	atv_IDS_LIGHT,	/* 0x003c */
	atv_IDS_FULL_SCREEN,	/* 0x003d */
	atv_IDS_4TO3,	/* 0x003e */
	atv_IDS_ZOOM,	/* 0x003f */
	atv_IDS_PANORAMA,	/* 0x0040 */
	atv_IDS_WARM,	/* 0x0041 */
	atv_IDS_COOL,	/* 0x0042 */
	atv_IDS_ON,	/* 0x0043 */
	atv_IDS_OFF,	/* 0x0044 */
	atv_IDS_PROGRAM_MANAGE,	/* 0x0045 */
	atv_IDS_MANUAL_SEARCH,	/* 0x0046 */
	atv_IDS_FINE_TUNE,	/* 0x0047 */
	atv_IDS_COLOR_SYSTEM,	/* 0x0048 */
	atv_IDS_SOUND_SYSTEM,	/* 0x0049 */
	atv_IDS_SKIP,	/* 0x004a */
	atv_IDS_CANCEL,	/* 0x004b */
	atv_IDS_START_AUTO_SCAN,	/* 0x004c */
	atv_IDS_ENGLISH,	/* 0x004d */
	atv_IDS_CHINESE,	/* 0x004e */
	atv_IDS_HORIZONTAL_POS,	/* 0x004f */
	atv_IDS_VERTICAL_POS,	/* 0x0050 */
	atv_IDS_15_MINUTE,	/* 0x0051 */
	atv_IDS_30_MINUTE,	/* 0x0052 */
	atv_IDS_60_MINUTE,	/* 0x0053 */
	atv_IDS_120_MINUTE,	/* 0x0054 */
	atv_IDS_240_MINUTE,	/* 0x0055 */
	atv_IDS_PTP,	/* 0x0056 */
	atv_IDS_5_S,	/* 0x0057 */
	atv_IDS_10_S,	/* 0x0058 */
	atv_IDS_15_S,	/* 0x0059 */
	atv_IDS_CURRENT_CHANNEL,	/* 0x005a */
	atv_IDS_TO_CHANNEL,	/* 0x005b */
	atv_IDS_MENU,	/* 0x005c */
	atv_IDS_MOVIE,	/* 0x005d */
	atv_IDS_MUSIC,	/* 0x005e */
	atv_IDS_SETTING,	/* 0x005f */
	atv_IDS_PLAY,	/* 0x0060 */
	atv_IDS_PAUSE,	/* 0x0061 */
	atv_IDS_PICTURE_SPEED,	/* 0x0062 */
	atv_IDS_UP_LEVEL,	/* 0x0063 */
	atv_IDS_HIGH_SPEED,	/* 0x0064 */
	atv_IDS_LOW_SPEED,	/* 0x0065 */
	atv_IDS_MIDDLE_SPEED,	/* 0x0066 */
	atv_IDS_PICTURE_OPTIMIZE,	/* 0x0067 */
	atv_IDS_HIGH,	/* 0x0068 */
	atv_IDS_LOW,	/* 0x0069 */
	atv_IDS_MIDDLE,	/* 0x006a */
	atv_IDS_LAST,	/* 0x006b */
	atv_IDS_NEXT,	/* 0x006c */
	atv_IDS_ROTATE,	/* 0x006d */
	atv_IDS_STOP_AUTO_SCAN,	/* 0x006e */
	atv_IDS_CHANNEL_LIST,	/* 0x006f */
	atv_IDS_TV_MANUAL_SCAN,	/* 0x0070 */
	atv_IDS_CHANNEL_SCAN,	/* 0x0071 */
	atv_IDS_NO_SIGNAL,	/* 0x0072 */
	atv_IDS_BAD,	/* 0x0073 */
	atv_IDS_GOOD,	/* 0x0074 */
	atv_IDS_FREQ,	/* 0x0075 */
	atv_IDS_DIGI_TV,	/* 0x0076 */
	atv_IDS_DIGI_RADIO,	/* 0x0077 */
	atv_IDS_QUIT,	/* 0x0078 */
	atv_IDS_CH_ID,	/* 0x0079 */
	atv_IDS_EBOOK,	/* 0x007a */
	atv_IDS_STOP,	/* 0x007b */
	atv_IDS_AV_SIGNAL_SELECT,	/* 0x007c */
	atv_IDS_AV_SIGNAL,	/* 0x007d */
	atv_IDS_DVBC,	/* 0x007e */
	atv_IDS_DTMB,	/* 0x007f */
	atv_IDS_NO_USB,	/* 0x0080 */
	atv_IDS_USB_CONNECT,	/* 0x0081 */
	atv_IDS_USB_DIS_CONNECT,	/* 0x0082 */
	atv_IDS_SEARCH_AUTO,	/* 0x0083 */
	atv_IDS_SEARCH_PAL,	/* 0x0084 */
	atv_IDS_SEARCH_SECAM,	/* 0x0085 */
	atv_IDS_SEARCH_NTSC,	/* 0x0086 */
	atv_IDS_SEARCH_DK,	/* 0x0087 */
	atv_IDS_SEARCH_BG,	/* 0x0088 */
	atv_IDS_SEARCH_I,	/* 0x0089 */
	atv_IDS_SEARCH_M,	/* 0x008a */
	atv_IDS_DEFAULT_SET,	/* 0x008b */
	atv_IDS_RESTORE_OK,	/* 0x008c */
	atv_IDS_PROMPT_INFO,	/* 0x008d */
	atv_IDS_PLAY_FAILED,	/* 0x008e */
	atv_IDS_FREQ_SEARCH,	/* 0x008f */
	atv_IDS_TV_AUTO_SCAN,	/* 0x0090 */
	atv_IDS_START_ALL_SCAN,	/* 0x0091 */
	atv_IDS_END_ALL_SCAN,	/* 0x0092 */
	atv_IDS_SCANNING,	/* 0x0093 */
	atv_IDS_MONDAY,	/* 0x0094 */
	atv_IDS_TUESDAY,	/* 0x0095 */
	atv_IDS_WENDSDAY,	/* 0x0096 */
	atv_IDS_THURSDAY,	/* 0x0097 */
	atv_IDS_FRIDAY,	/* 0x0098 */
	atv_IDS_SATURDAY,	/* 0x0099 */
	atv_IDS_SUNDAY,	/* 0x009a */
	atv_IDS_INIT_TV,	/* 0x009b */
	atv_IDS_GENERAL_SETTING,	/* 0x009c */
	atv_IDS_DEBUG,	/* 0x009d */
	atv_IDS_SW_INFORMATION,	/* 0x009e */
	atv_IDS_SOFTWARE_UPDATE,	/* 0x009f */
	atv_IDS_INIT_FAC_CHANNEL,	/* 0x00a0 */
	atv_IDS_BURN_MODE,	/* 0x00a1 */
	atv_IDS_INIT_ALL_FOR_BOE,	/* 0x00a2 */
	atv_IDS_HOTEL_MODE,	/* 0x00a3 */
	atv_IDS_SOURCE_LOCK,	/* 0x00a4 */
	atv_IDS_CHANNEL_LOCK,	/* 0x00a5 */
	atv_IDS_DEFAULT_SOURCE,	/* 0x00a6 */
	atv_IDS_DEFAULT_PROG,	/* 0x00a7 */
	atv_IDS_MAX_VOLUME,	/* 0x00a8 */
	atv_IDS_DEFAULT_VOLUME,	/* 0x00a9 */
	atv_IDS_POWER_DOWN_RESET,	/* 0x00aa */
	atv_IDS_RESET_HOTEL,	/* 0x00ab */
	atv_IDS_EXPORT_SETTINGS,	/* 0x00ac */
	atv_IDS_IMPORT_SETTINGS,	/* 0x00ad */
	atv_IDS_KEY_LOCK,	/* 0x00ae */
	atv_IDS_CAPTURE_LOGO,	/* 0x00af */
	atv_IDS_LOGO,	/* 0x00b0 */
	atv_IDS_DEFAULT,	/* 0x00b1 */
	atv_IDS_ADC_ADJUST,	/* 0x00b2 */
	atv_IDS_EMC_SETTING,	/* 0x00b3 */
	atv_IDS_BUILD_TIME,	/* 0x00b4 */
	atv_IDS_VERSION,	/* 0x00b5 */
	atv_IDS_LVDS_MAP,	/* 0x00b6 */
	atv_IDS_POWER_MODE,	/* 0x00b7 */
	atv_IDS_WHITE_PATTERN,	/* 0x00b8 */
	atv_IDS_PWM,	/* 0x00b9 */
	atv_IDS_POWER_REF,	/* 0x00ba */
	atv_IDS_POWER_DIM,	/* 0x00bb */
	atv_IDS_BACKLIGHT_MAX,	/* 0x00bc */
	atv_IDS_BACKLIGHT_LEVEL,	/* 0x00bd */
	atv_IDS_BACKLIGHT_STEP,	/* 0x00be */
	atv_IDS_STEP_TIME,	/* 0x00bf */
	atv_IDS_FACTORY_SETTING,	/* 0x00c0 */
	atv_IDS_NO_PROGRAM,	/* 0x00c1 */
	atv_IDS_SOUND_BACKLIGHT,	/* 0x00c2 */
	atv_IDS_WB_ADJUST,	/* 0x00c3 */
	atv_IDS_PQ_NONLINEAR,	/* 0x00c4 */
	atv_IDS_SOUND_MODE,	/* 0x00c5 */
	atv_IDS_VOLUME_CURVE,	/* 0x00c6 */
	atv_IDS_SATURATION,	/* 0x00c7 */
	atv_IDS_PVR,	/* 0x00c8 */
	atv_IDS_STOP_RECORD,	/* 0x00c9 */
	atv_IDS_ENTER_RECORD,	/* 0x00ca */
	atv_IDS_RECORD_FAILED,	/* 0x00cb */
	atv_IDS_RECORD_TIME_OUT,	/* 0x00cc */
	atv_IDS_NO_SPACE,	/* 0x00cd */
	atv_IDS_REICORD_FILE_LARGE,	/* 0x00ce */
	atv_IDS_BAD_SIGNAL_SAVING,	/* 0x00cf */
	atv_IDS_DEVICE_REMOVED,	/* 0x00d0 */
	atv_IDS_RECORD_NOT_CHANGE_CHANNEL,	/* 0x00d1 */
	atv_IDS_NO_FIND_DISK,	/* 0x00d2 */
	atv_IDS_RED_INPUT,	/* 0x00d3 */
	atv_IDS_BOXINFORMATION,	/* 0x00d4 */
	atv_IDS_PRODUCECOMPANY,	/* 0x00d5 */
	atv_IDS_HARDWAREEDITION,	/* 0x00d6 */
	atv_IDS_SOFTWAREEDITION,	/* 0x00d7 */
	atv_IDS_SERIALNUMBER,	/* 0x00d8 */
	atv_IDS_COMPANYID,	/* 0x00d9 */
	atv_IDS_UPGRADE_FAIL,	/* 0x00da */
	atv_IDS_UPGRADE_SUC,	/* 0x00db */
	atv_IDS_INVALID_FILE,	/* 0x00dc */
	atv_IDS_THEATRE,	/* 0x00dd */
	atv_IDS_SCAN_CONFIG,	/* 0x00de */
	atv_IDS_TV_SCAN_CONFIG,	/* 0x00df */
	atv_IDS_DTV_SCAN_CONFIG,	/* 0x00e0 */
	atv_IDS_START_FREQ,	/* 0x00e1 */
	atv_IDS_END_FREQ,	/* 0x00e2 */
	atv_IDS_BANDWIDTH,	/* 0x00e3 */
	atv_IDS_BY_ROLE,	/* 0x00e4 */
	atv_IDS_MODULATION,	/* 0x00e5 */
	atv_IDS_SYMBOL_RATE,	/* 0x00e6 */
	atv_IDS_FREQUENCY,	/* 0x00e7 */
	atv_IDS_YES,	/* 0x00e8 */
	atv_IDS_NO,	/* 0x00e9 */
	atv_IDS_CONFIG_ERROR,	/* 0x00ea */
	atv_IDS_START_MANUAL_SCAN,	/* 0x00eb */
	atv_IDS_END_MANUAL_SCAN,	/* 0x00ec */
	atv_IDS_END_AUTO_SCAN,	/* 0x00ed */
	atv_IDS_SUB_START,	/* 0x00ee */
	atv_IDS_SUB_START_CHAN,	/* 0x00ef */
	atv_IDS_EVENT_OUT_OF_TIME,	/* 0x00f0 */
	atv_IDS_SUBSCRIBE_FAIL,	/* 0x00f1 */
	atv_IDS_SWITCH_USER_MODE,	/* 0x00f2 */
	atv_IDS_EPG_HELP,	/* 0x00f3 */
	atv_IDS_CHOICE,	/* 0x00f4 */
	atv_IDS_EPG_LIST,	/* 0x00f5 */
	atv_IDS_EPG_LIST_RADIO,	/* 0x00f6 */
	atv_IDS_REPEAT_TIME1,	/* 0x00f7 */
	atv_IDS_REPEAT_TIME,	/* 0x00f8 */
	atv_IDS_PRO_NAME,	/* 0x00f9 */
	atv_IDS_EVENT_NAME,	/* 0x00fa */
	atv_IDS_EVENT_SYNOPSIS,	/* 0x00fb */
	atv_IDS_EPGINFO,	/* 0x00fc */
	atv_IDS_LIST_LOOP,	/* 0x00fd */
	atv_IDS_SINGNAL_LOOP,	/* 0x00fe */
	atv_IDS_RANDOM_LOOP,	/* 0x00ff */
	atv_IDS_LIST_PLAY,	/* 0x0100 */
	atv_IDS_PLAY_MODE,	/* 0x0101 */
	atv_IDS_CARRIER_FREQ,	/* 0x0102 */
	atv_IDS_DEM_OTHER_INFO,	/* 0x0103 */
	atv_IDS_DEMO_DETIAL,	/* 0x0104 */
	atv_IDS_DEM_SCATTER,	/* 0x0105 */
	atv_IDS_DEM_HN,	/* 0x0106 */
	atv_IDS_DEM_SP,	/* 0x0107 */
	atv_IDS_SIGNAL_DETECT,	/* 0x0108 */
	atv_IDS_STRENGH_BAR,	/* 0x0109 */
	atv_IDS_QUALITY_BAR,	/* 0x010a */
	atv_IDS_UPDATE_SYMBOL,	/* 0x010b */
	atv_IDS_NET_SEARCH,	/* 0x010c */
	atv_IDS_START_NET_SCAN,	/* 0x010d */
	atv_IDS_TV_NET_SCAN,	/* 0x010e */
	atv_IDS_END_NET_SCAN,	/* 0x010f */
	atv_IDS_EARPHONE_IN,	/* 0x0110 */
	atv_IDS_EARPHONE_OUT,	/* 0x0111 */
	atv_IDS_SCRAMBLED_PROG,	/* 0x0112 */
	atv_IDS_SVN_VERSION,	/* 0x0113 */
	atv_IDS_BOARD_VER,	/* 0x0114 */
	atv_IDS_NOT_SUPPORT_PIC_SIZE,	/* 0x0115 */
	atv_IDS_NOT_SUPPORT_FILE,	/* 0x0116 */
	atv_IDS_FACTORY_RESET,	/* 0x0117 */
	atv_IDS_DELETE_PVR,	/* 0x0118 */
	atv_IDS_DELETE_PVR_FILE,	/* 0x0119 */
	atv_IDS_EXIT,	/* 0x011a */
	atv_IDS_DVI1,	/* 0x011b */
	atv_IDS_DVI2,	/* 0x011c */
	atv_IDS_UNKNOW_FORMAT,	/* 0x011d */
	atv_IDS_INPUT_TIME_ERROR,	/* 0x011e */
	atv_IDS_FILE_SIZE,	/* 0x011f */
	atv_IDS_BPS,	/* 0x0120 */
	atv_IDS_Bitrate_Excess,	/* 0x0121 */
	atv_IDS_Resolution,	/* 0x0122 */
	atv_IDS_MULTI_AUDIO,	/* 0x0123 */
	atv_IDS_LEFT,	/* 0x0124 */
	atv_IDS_RIGHT,	/* 0x0125 */
	atv_IDS_STEREO,	/* 0x0126 */
	atv_IDS_NONE,	/* 0x0127 */
	atv_IDS_ACTION_INVALID,	/* 0x0128 */
	atv_IDS_DEVICE_BITRATE_BAD,	/* 0x0129 */
	atv_IDS_RECEIVE_CHOISE,	/* 0x012a */
	atv_IDS_RECEIVE_SERIAL,	/* 0x012b */
	atv_IDS_CHIP_ID,	/* 0x012c */
	atv_IDS_VIDEO_FRMART,	/* 0x012d */
	atv_IDS_AUDIO_FRMART,	/* 0x012e */
	atv_IDS_NEW_SOFTWARE,	/* 0x012f */
	atv_IDS_SW_UPDATE,	/* 0x0130 */
	atv_IDS_SW_UPDATE_MUST,	/* 0x0131 */
	atv_IDS_SAVE_PROGROM,
	atv_IDS_STAND_BY,
	atv_IDS_KEY_CANCEL,
	atv_IDS_BLUE_SCREEN,
	atv_IDS_BLACK_SCREEN,	
#if 1//ndef D_TV_UI_STYLE_MINI
	atv_IDS_DVBS_SEARCH,
	atv_IDS_SET_ANTENNA,	/* 0x0131 */
	atv_IDS_SATELLITE,	/* 0x0132 */
	atv_IDS_LNB_FREQ,	/* 0x0133 */
	atv_IDS_TRANSPONDER_LIST,	/* 0x0134 */
	atv_IDS_22K,	/* 0x0135 */
	atv_IDS_POLARITY,		/* 0x0136 */
	atv_IDS_SIGNAL_INTENSITY,	/* 0x0137 */
	atv_IDS_SIGNAL_QUALITY,	/* 0x0138 */
	atv_IDS_TP_SCAN,	/* 0x0139 */
	atv_IDS_SATE_SCAN,		/* 0x013a */
	atv_IDS_ADD_TP,
	atv_IDS_EDIT_TP,
	atv_IDS_WIFI_SETTING,
	atv_IDS_WIFI_DISPLAY,
	atv_IDS_DEVICE_NAME,
	atv_IDS_NET_MODE,
	atv_IDS_IPADDRESS,
	atv_IDS_SUBNET_MASK,
	atv_IDS_GATE_WAY,
	atv_IDS_DNS,
	atv_IDS_MAC,
	atv_IDS_SCAN,
	atv_IDS_DELETE,
	atv_IDS_CAPS,
	atv_IDS_NUMBER,
	atv_IDS_NUMBER_0TO9,
	atv_IDS_ZHILIAN_TV,
	atv_IDS_NETWORK_SHARING,
	atv_IDS_DTV_SHAREING,
	atv_IDS_AIRPLAY,
	atv_IDS_LIULINK,
	IDS_GET_NET_TIME,	/* 0x020e */
	IDS_THEREIS_NOPROG,	/* 0x020f */
	IDS_CONNECTING_NET,	/* 0x0210 */
	IDS_WIFI_FAILED,	/* 0x0211 */
	IDS_SET_WIFI,	/* 0x0212 */
	atv_IDS_JANUARY,		// IDS_JANUARY
	atv_IDS_FEBRUARY,		// IDS_FEBRUARY
	atv_IDS_MARCH,		// IDS_MARCH
	atv_IDS_APRIL,		// IDS_APRIL
	atv_IDS_MAY,		// IDS_MAY
	atv_IDS_JUNE,		// IDS_JUNE
	atv_IDS_JULY,		// IDS_JULY
	atv_IDS_AUGUST,		// IDS_AUGUST
	atv_IDS_SEPTEMBER,		// IDS_SEPTEMBER
	atv_IDS_OCTOBER,		// IDS_OCTOBER
	atv_IDS_NOVEMBER,		// IDS_NOVEMBER
	atv_IDS_DECEMBER,		// IDS_DECEMBER
	atv_IDS_ZHILIAN_MAIN_TV,
	atv_IDS_ZHILIAN_IPTV,
	atv_IDS_ZHILIAN_IPTV_TEXT,
	atv_IDS_WIFI_CONNECT,
        atv_IDS_WIFI_NO_CONNECT,
        atv_IDS_WIFI_CONNECTED,
	atv_IDS_SEC,
	atv_IDS_GOTO_LAST_TIME,
	atv_IDS_STOP_ATV_SCAN,
#else
        atv_IDS_NO_SUCH_FILE,
#endif
	atv_IDS_ENUM_MAX,	/* 0x4000+0x131*/
};

#define	atv_LANCOUNTRY_English	0
#define	atv_LANCOUNTRY_Chinese	1
PREFIXCONST char* POSTCONST atv_LoadIdsRes(int ids, int lanid);

#endif	//___LANGUAGE_SOURCE_IDS_DEFINE_FILE__
