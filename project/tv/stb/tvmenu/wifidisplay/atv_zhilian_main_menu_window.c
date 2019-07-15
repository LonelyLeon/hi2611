/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2019-06-14 17:45:14

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2019-06-10 11:41:27.793

	}
*/
#include	"dFrame.h"
#include	"atvFormat.h"
#include	"atvlanresource.h"
#include	"atvImageResource.h"
#include	"atvpalletes.h"


///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// predefined macros 
#define	ID_ZHILIAN_MAIN_IMAGE	1
#define	ID_ZHILIAN_MAIN_IMAGE_MEDIA	2
#define	ID_ZHILIAN_MAIN_LABEL_MEDIA	3
#define	ID_ZHILIAN_MAIN_BUTTON_MEDIA	4
#define	ID_ZHILIAN_MAIN_GROUP_BUTTON	5
#define	ID_ZHILIAN_MAIN_LABEL_SOURCE	6
#define	ID_ZHILIAN_MAIN_BUTTON_SOURCE	7
#define	ID_ZHILIAN_MAIN_LABEL_SOURCE_NAME	8
#define	ID_ZHILIAN_MAIN_IMAGE_CUR_SOURCE	9
#define	ID_ZHILIAN_MAIN_IMAGE_SOURCE	10
#define	ID_ZHILIAN_MAIN_BUTTON_SETTING	11
#define	ID_ZHILIAN_MAIN_IMAGE_SETTING	12
#define	ID_ZHILIAN_MAIN_LEBEL_SETTINGTEXT	13
#define	ID_ZHILIAN_MAIN_LABEL_ZHILIAN	14
#define	ID_ZHILIAN_MAIN_BUTTON_MIRA	15
#define	ID_ZHILIAN_MAIN_IMAGE_MIRA	16
#define	ID_ZHILIAN_MAIN_LABEL_MIRTEXT	17
#define	ID_ZHILIAN_MAIN_BUTTON_TVWEB	18
#define	ID_ZHILIAN_MAIN_IMAGE_TVWEB	19
#define	ID_ZHILIAN_MAIN_LABEL_TVWEBTEXT	20
#define	ID_ZHILIAN_MAIN_BUTTON_DLNA	21
#define	ID_ZHILIAN_MAIN_IMAGE_DLNA	22
#define	ID_ZHILIAN_MAIN_LABEL_DLNATEXT	23
#define	ID_ZHILIAN_MAIN_IMAGE_TV	24
#define	ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC	25
#define	ID_ZHILIAN_MAIN_IMAGE_TV_PIC	26
#define	ID_ZHILIAN_MAIN_IMAGE_ZHILIAN	27
#define	ID_ZHILIAN_MAIN_LABEL_IPTV	28
#define	ID_ZHILIAN_MAIN_BUTTON_IPTV	29
#define	ID_ZHILIAN_MAIN_IMAGE_IPTV	30
#define	ID_ZHILIAN_MAIN_LABEL_IPTVTEXT	31
#define	ID_ZHILIAN_MAIN_IMAGE_CHOOSE	32
#define	ID_ZHILIAN_MAIN_LABEL_CHOOSE	33
#define	ID_ZHILIAN_MAIN_LABEL_TIME	34
#define	ID_ZHILIAN_MAIN_LABEL_OK_ICON	35
#define	ID_ZHILIAN_MAIN_WIFI_SHOW_GROUP	36
#define	ID_ZHILIAN_MAIN_LABEL_WIFI_INFO	37
#define	ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC	38
#define	ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC_BG	39
#define	ID_ZHILIAN_MAIN_LABEL_WIFI_NAME	40
#define	ID_ZHILIAN_MAIN_LABEL_WIFI_SIGNAL  41
//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd862b21_3bc4823={-1, atv_IMG_ID_main_zhilian_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd862b7d_09a6784={-1, atv_IMG_ID_main_zhilian_pic, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd862df5_2cd153c={-1, -1, atv_IDS_ZHILIAN_MAIN_TV, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd863796_0fd6784={-1, atv_IMB_ID_COMB_zhilian_main_focse, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd864aec_31cf3e={-1, atv_IMG_ID_FS_Zhilian_Source, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd864c1f_03c440d={-1, atv_IMG_ID_FS_Zhilian_Setting, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd864d98_01a1547={-1, atv_IMG_ID_FS_Zhilian_Mira, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd864e52_37874d={-1, atv_IMG_ID_FS_Zhilian_Tsnet, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd864ed9_0ec428b={-1, atv_IMG_ID_FS_Zhilian_Dlna, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd864fdf_3a47a5a={-1, atv_IMG_ID_FS_Zhilian_tv, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd8650a3_3b63b25={-1, atv_IMG_ID_hint_direction, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd865108_0f263cb={-1, -1, atv_IDS_CHOICE, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd86ef5e_25f6143={-1, atv_IMG_ID_FS_main_zhilian_mode_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b54f_21d64cb={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b54f_21744cb={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b59f_1223625={-1, -1, atv_IDS_TV, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b59f_1223626={-1, -1, atv_IDS_WIFI_DISPLAY, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b59f_1223627={-1, -1, atv_IDS_DTV_SHAREING, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b59f_1223628={-1, -1, atv_IDS_NETWORK_SHARING, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b54f_21d64ca={-1, -1, atv_IDS_SETTING, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd864fdf_3a47a12={-1, atv_IMG_ID_FS_Zhilian_Media, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b54f_21d6411={-1, -1, atv_IDS_USB, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6d4573f_35672ae={-1, atv_IMG_ID_zhilian_main_phone_pic, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6d457bc_1e56df1={-1, atv_IMG_ID_zhilian_main_wifi_pic, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6d45816_1281eb={-1, atv_IMG_ID_zhilian_main_tv_pic, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6d4776f_29372ae={-1, atv_IMG_ID_hint_button, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6d4776f_23272ae={-1, atv_IMG_ID_main_zhilian_source_dtv, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd862b21_3bc29={{&GUID_cd862b21_3bc4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd862b7d_09a18be={{&GUID_cd862b7d_09a6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_MEDIA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6d38cef_2ed26e9={{&GUID_cd864fdf_3a47a12, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_MEDIA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6d38d61_04412db={{&GUID_cd87b54f_21d6411, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_ZHILIAN_MAIN_BUTTON_MEDIA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6d38be0_3af1649={{NULL, &GUID_cd863796_0fd6784, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_ZHILIAN_MAIN_GROUP_BUTTON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd86a629_1ad5cd7={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_SOURCE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd862c06_37b2cd6={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_BUTTON}	"ID_ZHILIAN_MAIN_BUTTON_SOURCE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd862d15_3261649={{NULL, &GUID_cd863796_0fd6784, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_SOURCE_NAME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd87b59f_1222eb0={{&GUID_cd87b59f_1223625, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_CUR_SOURCE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd86523a_12155a9={{&GUID_c6d4776f_23272ae, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_SOURCE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd864aec_31c390c={{&GUID_cd864aec_31cf3e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_BUTTON}	"ID_ZHILIAN_MAIN_BUTTON_SETTING"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd862d88_37926e9={{NULL, &GUID_cd863796_0fd6784, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_SETTING"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd864c1f_03c305e={{&GUID_cd864c1f_03c440d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LEBEL_SETTINGTEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd9bdb64_3b712db={{&GUID_cd87b54f_21d64ca, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_ZHILIAN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd862df5_2cd12db={{&GUID_cd862df5_2cd153c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_BUTTON}	"ID_ZHILIAN_MAIN_BUTTON_MIRA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd863796_0fd4823={{NULL, &GUID_cd863796_0fd6784, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_MIRA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd864d98_01a4db7={{&GUID_cd864d98_01a1547, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_MIRTEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd9bdbea_3bdf3e={{&GUID_cd87b59f_1223626, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_BUTTON}	"ID_ZHILIAN_MAIN_BUTTON_TVWEB"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd863828_0923d6c={{NULL, &GUID_cd863796_0fd6784, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_TVWEB"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd864e52_3782d12={{&GUID_cd864e52_37874d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_TVWEBTEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd9bdcf7_119440d={{&GUID_cd87b59f_1223627, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_BUTTON}	"ID_ZHILIAN_MAIN_BUTTON_DLNA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd86388c_0de5f90={{NULL, &GUID_cd863796_0fd6784, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_DLNA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd864ed9_0ec66bb={{&GUID_cd864ed9_0ec428b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_DLNATEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd9bde4c_2d51547={{&GUID_cd87b59f_1223628, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_TV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6d4573f_3562cd6={{&GUID_c6d4573f_35672ae, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6d457bc_1e51649={{&GUID_c6d457bc_1e56df1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_TV_PIC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6d45816_12826e9={{&GUID_c6d45816_1281eb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_ZHILIAN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd86ef5e_25f55c7={{&GUID_cd86ef5e_25f6143, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [28]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_IPTV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd863932_18f41bb={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [29]{D_CTRL_BUTTON}	"ID_ZHILIAN_MAIN_BUTTON_IPTV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd86399d_1322ea6={{NULL, &GUID_cd863796_0fd6784, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [30]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_IPTV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd864fdf_3a45d03={{&GUID_cd864fdf_3a47a5a, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [31]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_IPTVTEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd9bdeed_28374d={{&GUID_cd87b59f_1223625, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [32]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_CHOOSE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd8650a3_3b61238={{&GUID_cd8650a3_3b63b25, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [33]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_CHOOSE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd865108_0f21ad4={{&GUID_cd865108_0f263cb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [34]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_TIME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd87b54f_21d36e9={{&GUID_cd87b54f_21d64cb, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [35]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_OK_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6d4776f_2932cd6={{&GUID_c6d4776f_29372ae, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_ZHILIAN_MAIN_GROUP_BUTTON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd86a629_2ad5cd7={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [36]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_WIFI_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cacea8ae_1a01614={{&GUID_cd87b54f_21d64cb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [37]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cacea948_37b130={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [38]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cacea948_37b132={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [39]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_WIFI_NAME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cacea978_31f55e0={{&GUID_cd87b54f_21744cb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [40]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_WIFI_SIGNAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cacea978_31f55e2={{&GUID_cd87b54f_21d64cb, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_zhilian_main_menu_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 1280, 720, 0, -1, (D_FrameCtrlDescr*)&GUID_cd862b21_3bc29, },
	// [1]ID_ZHILIAN_MAIN_IMAGE
	{D_CTRL_IMAGE, 0, 59, 43, 20, 36, 41, 30, -1, (D_FrameCtrlDescr*)&GUID_cd862b7d_09a18be, },
	// [2]ID_ZHILIAN_MAIN_IMAGE_MEDIA
	{D_CTRL_IMAGE, 0, 937, 441, 20, 290, 123, 30, -1, (D_FrameCtrlDescr*)&GUID_c6d38cef_2ed26e9, },
	// [3]ID_ZHILIAN_MAIN_LABEL_MEDIA
	{D_CTRL_LABEL, 2, 10, 10, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c6d38d61_04412db, },
	// [4]ID_ZHILIAN_MAIN_BUTTON_MEDIA
	{D_CTRL_BUTTON, 0, 922, 426, 20, 320, 153, 30, -1, (D_FrameCtrlDescr*)&GUID_c6d38be0_3af1649, },
	// [5]ID_ZHILIAN_MAIN_GROUP_BUTTON
	{D_CTRL_GROUP, 0, 0, 80, 20, 1280, 555, 30, -1, (D_FrameCtrlDescr*)&GUID_cd86a629_1ad5cd7, },
	// [6]ID_ZHILIAN_MAIN_LABEL_SOURCE
	{D_CTRL_LABEL, 5, 59, 17, 0, 100, 29, 30, -1, (D_FrameCtrlDescr*)&GUID_cd862c06_37b2cd6, },
	// [7]ID_ZHILIAN_MAIN_BUTTON_SOURCE
	{D_CTRL_BUTTON, 5, 45, 52, 20, 320, 294, 30, -1, (D_FrameCtrlDescr*)&GUID_cd862d15_3261649, },
	// [8]ID_ZHILIAN_MAIN_LABEL_SOURCE_NAME
	{D_CTRL_LABEL, 7, 96, 150, -20, 128, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd87b59f_1222eb0, },
	// [9]ID_ZHILIAN_MAIN_IMAGE_CUR_SOURCE
	{D_CTRL_IMAGE, 7, 110, 68, 10, 100, 78, 30, -1, (D_FrameCtrlDescr*)&GUID_cd86523a_12155a9, },
	// [10]ID_ZHILIAN_MAIN_IMAGE_SOURCE
	{D_CTRL_IMAGE, 7, 15, 15, 10, 290, 264, 30, -1, (D_FrameCtrlDescr*)&GUID_cd864aec_31c390c, },
	// [11]ID_ZHILIAN_MAIN_BUTTON_SETTING
	{D_CTRL_BUTTON, 5, 45, 346, 0, 320, 153, 30, -1, (D_FrameCtrlDescr*)&GUID_cd862d88_37926e9, },
	// [12]ID_ZHILIAN_MAIN_IMAGE_SETTING
	{D_CTRL_IMAGE, 11, 15, 15, 0, 290, 123, 30, -1, (D_FrameCtrlDescr*)&GUID_cd864c1f_03c305e, },
	// [13]ID_ZHILIAN_MAIN_LEBEL_SETTINGTEXT
	{D_CTRL_LABEL, 12, 16, 10, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd9bdb64_3b712db, },
	// [14]ID_ZHILIAN_MAIN_LABEL_ZHILIAN
	{D_CTRL_LABEL, 0, 109, 50, 20, 147, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd862df5_2cd12db, },
	// [15]ID_ZHILIAN_MAIN_BUTTON_MIRA
	{D_CTRL_BUTTON, 5, 366, 344, 0, 197, 153, 30, -1, (D_FrameCtrlDescr*)&GUID_cd863796_0fd4823, },
	// [16]ID_ZHILIAN_MAIN_IMAGE_MIRA
	{D_CTRL_IMAGE, 15, 15, 15, 0, 167, 123, 30, -1, (D_FrameCtrlDescr*)&GUID_cd864d98_01a4db7, },
	// [17]ID_ZHILIAN_MAIN_LABEL_MIRTEXT
	{D_CTRL_LABEL, 16, 33, 83, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd9bdbea_3bdf3e, },
	// [18]ID_ZHILIAN_MAIN_BUTTON_TVWEB
	{D_CTRL_BUTTON, 5, 546, 344, 0, 197, 153, 30, -1, (D_FrameCtrlDescr*)&GUID_cd863828_0923d6c, },
	// [19]ID_ZHILIAN_MAIN_IMAGE_TVWEB
	{D_CTRL_IMAGE, 18, 15, 15, 0, 167, 123, 30, -1, (D_FrameCtrlDescr*)&GUID_cd864e52_3782d12, },
	// [20]ID_ZHILIAN_MAIN_LABEL_TVWEBTEXT
	{D_CTRL_LABEL, 19, 33, 83, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd9bdcf7_119440d, },
	// [21]ID_ZHILIAN_MAIN_BUTTON_DLNA
	{D_CTRL_BUTTON, 5, 725, 344, 0, 197, 153, 30, -1, (D_FrameCtrlDescr*)&GUID_cd86388c_0de5f90, },
	// [22]ID_ZHILIAN_MAIN_IMAGE_DLNA
	{D_CTRL_IMAGE, 21, 15, 15, 0, 167, 123, 30, -1, (D_FrameCtrlDescr*)&GUID_cd864ed9_0ec66bb, },
	// [23]ID_ZHILIAN_MAIN_LABEL_DLNATEXT
	{D_CTRL_LABEL, 22, 33, 85, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd9bde4c_2d51547, },
	// [24]ID_ZHILIAN_MAIN_IMAGE_TV
	{D_CTRL_IMAGE, 5, 408, 187, 0, 113, 125, 30, -1, (D_FrameCtrlDescr*)&GUID_c6d4573f_3562cd6, },
	// [25]ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC
	{D_CTRL_IMAGE, 5, 528, 224, 0, 38, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c6d457bc_1e51649, },
	// [26]ID_ZHILIAN_MAIN_IMAGE_TV_PIC
	{D_CTRL_IMAGE, 5, 574, 112, 0, 312, 200, 30, -1, (D_FrameCtrlDescr*)&GUID_c6d45816_12826e9, },
	// [27]ID_ZHILIAN_MAIN_IMAGE_ZHILIAN
	{D_CTRL_IMAGE, 5, 380, 64, 0, 529, 417, 30, -1, (D_FrameCtrlDescr*)&GUID_cd86ef5e_25f55c7, },
	// [28]ID_ZHILIAN_MAIN_LABEL_IPTV
	{D_CTRL_LABEL, 5, 933, 17, 0, 142, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd863932_18f41bb, },
	// [29]ID_ZHILIAN_MAIN_BUTTON_IPTV
	{D_CTRL_BUTTON, 5, 922, 52, 0, 320, 294, 30, -1, (D_FrameCtrlDescr*)&GUID_cd86399d_1322ea6, },
	// [30]ID_ZHILIAN_MAIN_IMAGE_IPTV
	{D_CTRL_IMAGE, 29, 15, 15, 0, 290, 264, 30, -1, (D_FrameCtrlDescr*)&GUID_cd864fdf_3a45d03, },
	// [31]ID_ZHILIAN_MAIN_LABEL_IPTVTEXT
	{D_CTRL_LABEL, 30, 45, 199, 0, 200, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd9bdeed_28374d, },
	// [32]ID_ZHILIAN_MAIN_IMAGE_CHOOSE
	{D_CTRL_IMAGE, 0, 1074, 648, 20, 31, 29, 30, -1, (D_FrameCtrlDescr*)&GUID_cd8650a3_3b61238, },
	// [33]ID_ZHILIAN_MAIN_LABEL_CHOOSE
	{D_CTRL_LABEL, 0, 1146, 648, 20, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd865108_0f21ad4, },
	// [34]ID_ZHILIAN_MAIN_LABEL_TIME
	{D_CTRL_LABEL, 0, 344, 28, 20, 379, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd87b54f_21d36e9, },
	// [35]ID_ZHILIAN_MAIN_LABEL_OK_ICON
	{D_CTRL_LABEL, 0, 1040, 644, 20, 102, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_c6d4776f_2932cd6, },
	// [5]ID_ZHILIAN_MAIN_GROUP_BUTTON
	{D_CTRL_GROUP, 0, 900, 45, 20, 370, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd86a629_2ad5cd7, },
	// [36]ID_ZHILIAN_MAIN_LABEL_WIFI_INFO
	{D_CTRL_LABEL, 36,250, 0, 20, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cacea8ae_1a01614, },
	// [37]ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC
	{D_CTRL_IMAGE, 36, 0, 0, 32, 30, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_cacea948_37b130, },
	// [38]ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC_BG
	{D_CTRL_IMAGE, 36, 0, 0, 32, 30, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_cacea948_37b132, },
	// [39]ID_ZHILIAN_MAIN_LABEL_WIFI_NAME
	{D_CTRL_LABEL, 36, 80, 0, 20, 170, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cacea978_31f55e0, },
	// [40]ID_ZHILIAN_MAIN_LABEL_WIFI_SIGNAL
	{D_CTRL_LABEL, 36, 35, 0, 20, 45, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cacea978_31f55e2, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_zhilian_main_menu_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_zhilian_main_menu_window[42];
D_Frame atv_zhilian_main_menu_window = {
	run_ctrls_atv_zhilian_main_menu_window, 
	ctrl_description_of_atv_zhilian_main_menu_window, 
	atv_zhilian_main_menu_window_init, 
};

