/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2019-06-20 10:41:45

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
#define	ID_ZHILIAN_MAIN_GROUP_BUTTON	2
#define	ID_ZHILIAN_MAIN_BUTTON_MIRA	3
#define	ID_ZHILIAN_MAIN_IMAGE_MIRA	4
#define	ID_ZHILIAN_MAIN_LABEL_MIRTEXT	5
#define	ID_ZHILIAN_MAIN_BUTTON_DLNA	6
#define	ID_ZHILIAN_MAIN_IMAGE_DLNA	7
#define	ID_ZHILIAN_MAIN_LABEL_DLNATEXT	8
#define	ID_ZHILIAN_MAIN_BUTTON_AIRPLAY	9
#define	ID_ZHILIAN_MAIN_IMAGE_AIRPLAY	10
#define	ID_ZHILIAN_MAIN_LABEL_AIRPLAY	11
#define	ID_ZHILIAN_MAIN_BUTTON_SOURCE	12
#define	ID_ZHILIAN_MAIN_IMAGE_SOURCE	13
#define	ID_ZHILIAN_MAIN_LABEL_SOURCE	14
#define	ID_ZHILIAN_MAIN_BUTTON_MEDIA	15
#define	ID_ZHILIAN_MAIN_IMAGE_MEDIA	16
#define	ID_ZHILIAN_MAIN_LABEL_MEDIA	17
#define	ID_ZHILIAN_MAIN_BUTTON_IPTV	18
#define	ID_ZHILIAN_MAIN_IMAGE_IPTV	19
#define	ID_ZHILIAN_MAIN_LABEL_IPTV	20
#define	ID_ZHILIAN_MAIN_LABEL_IPTVTEXT	21
#define	ID_ZHILIAN_MAIN_BUTTON_SETTING	22
#define	ID_ZHILIAN_MAIN_IMAGE_SETTING	23
#define	ID_ZHILIAN_MAIN_LEBEL_SETTINGTEXT	24
#define	ID_ZHILIAN_MAIN_IMAGE_EXIT	25
#define	ID_ZHILIAN_MAIN_LABEL_EXIT	26
#define	ID_ZHILIAN_MAIN_LABEL_OK_ICON	27
#define	ID_ZHILIAN_MAIN_IMAGE_CHOOSE	28
#define	ID_ZHILIAN_MAIN_LABEL_CHOOSE	29
#define	ID_ZHILIAN_MAIN_WIFI_SHOW_GROUP	30
#define	ID_ZHILIAN_MAIN_LABEL_WIFI_INFO	31
#define	ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC	32
#define	ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC_BG	33
#define	ID_ZHILIAN_MAIN_LABEL_WIFI_NAME	34
#define	ID_ZHILIAN_MAIN_LABEL_WIFI_SIGNAL	35

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd862b21_3bc4823={-1, atv_IMG_ID_main_zhilian_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd862b7d_09a6784={-1, atv_IMG_ID_main_zhilian_pic, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd862c06_37b72ae={-1, -1, atv_IDS_SOURCE, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd863796_0fd6784={-1, atv_IMB_ID_COMB_zhilian_main_focse, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd863932_18f26e9={-1, -1, atv_IDS_ZHILIAN_IPTV, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd864aec_31cf3e={-1, atv_IMG_ID_FS_Mini_Zhilian_Source, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd864c1f_03c440d={-1, atv_IMG_ID_FS_Mini_Zhilian_Setting, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd864d98_01a1547={-1, atv_IMG_ID_FS_Mini_Zhilian_Mira, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd864ed9_0ec428b={-1, atv_IMG_ID_FS_Mini_Zhilian_Dlna, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd864fdf_3a47a5a={-1, atv_IMG_ID_FS_Mini_Zhilian_Iptv, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd8650a3_3b63b25={-1, atv_IMG_ID_hint_direction, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd865108_0f263cb={-1, -1, atv_IDS_CHOICE, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd865172_03b4e45={-1, atv_IMG_ID_hint_button, atv_IDS_EXIT, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd865194_0346b89={-1, -1, atv_IDS_EXIT, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b59f_1223626={-1, -1, atv_IDS_WIFI_DISPLAY, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b59f_1223628={-1, -1, atv_IDS_NETWORK_SHARING, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b59f_1223629={-1, -1, atv_IDS_ZHILIAN_IPTV_TEXT, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b54f_21d64ca={-1, -1, atv_IDS_SETTING, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd864fdf_3a47a12={-1, atv_IMG_ID_FS_Mini_Zhilian_Media, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b54f_21d6411={-1, -1, atv_IDS_USB, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd864fdf_3a47a13={-1, atv_IMG_ID_FS_Mini_Zhilian_Airplay, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b54f_21d6414={-1, -1, atv_IDS_AIRPLAY, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6d4776f_29372ae={-1, atv_IMG_ID_hint_button, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b54f_21d64cb={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd87b54f_21744cb={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd862b21_3bc29={{&GUID_cd862b21_3bc4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd862b7d_09a18be={{&GUID_cd862b7d_09a6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_ZHILIAN_MAIN_GROUP_BUTTON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd86a629_1ad5cd7={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_ZHILIAN_MAIN_BUTTON_MIRA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd863796_0fd4823={{NULL, &GUID_cd863796_0fd6784, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_MIRA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd864d98_01a4db7={{&GUID_cd864d98_01a1547, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_MIRTEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd9bdbea_3bdf3e={{&GUID_cd87b59f_1223626, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_BUTTON}	"ID_ZHILIAN_MAIN_BUTTON_DLNA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd86388c_0de5f90={{NULL, &GUID_cd863796_0fd6784, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_DLNA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd864ed9_0ec66bb={{&GUID_cd864ed9_0ec428b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_DLNATEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd9bde4c_2d51547={{&GUID_cd87b59f_1223628, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_BUTTON}	"ID_ZHILIAN_MAIN_BUTTON_AIRPLAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c623ebe0_3af1649={{NULL, &GUID_cd863796_0fd6784, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_AIRPLAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6da41ef_2ed26e9={{&GUID_cd864fdf_3a47a13, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_AIRPLAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6df651_04412db={{&GUID_cd87b54f_21d6414, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_BUTTON}	"ID_ZHILIAN_MAIN_BUTTON_SOURCE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd862d15_3261649={{NULL, &GUID_cd863796_0fd6784, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_SOURCE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd864aec_31c390c={{&GUID_cd864aec_31cf3e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_SOURCE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd862c06_37b2cd6={{&GUID_cd862c06_37b72ae, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_BUTTON}	"ID_ZHILIAN_MAIN_BUTTON_MEDIA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6d38be0_3af1649={{NULL, &GUID_cd863796_0fd6784, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_MEDIA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6d38cef_2ed26e9={{&GUID_cd864fdf_3a47a12, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_MEDIA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6d38d61_04412db={{&GUID_cd87b54f_21d6411, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_BUTTON}	"ID_ZHILIAN_MAIN_BUTTON_IPTV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd86399d_1322ea6={{NULL, &GUID_cd863796_0fd6784, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_IPTV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd864fdf_3a45d03={{&GUID_cd864fdf_3a47a5a, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_IPTV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd863932_18f41bb={{&GUID_cd863932_18f26e9, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_IPTVTEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd9bdeed_28374d={{&GUID_cd87b59f_1223629, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_BUTTON}	"ID_ZHILIAN_MAIN_BUTTON_SETTING"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd862d88_37926e9={{NULL, &GUID_cd863796_0fd6784, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_SETTING"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd864c1f_03c305e={{&GUID_cd864c1f_03c440d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LEBEL_SETTINGTEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd9bdb64_3b712db={{&GUID_cd87b54f_21d64ca, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_EXIT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd865172_03b7ff5={{&GUID_cd865172_03b4e45, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_EXIT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd865194_034260d={{&GUID_cd865194_0346b89, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_OK_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6d4776f_2932cd6={{&GUID_c6d4776f_29372ae, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [28]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_CHOOSE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd8650a3_3b61238={{&GUID_cd8650a3_3b63b25, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [29]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_CHOOSE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd865108_0f21ad4={{&GUID_cd865108_0f263cb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [30]{D_CTRL_GROUP}	"ID_ZHILIAN_MAIN_WIFI_SHOW_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd86a629_2ad5cd7={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [31]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_WIFI_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cacea8ae_1a01614={{&GUID_cd87b54f_21d64cb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [32]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cacea948_37b130={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [33]{D_CTRL_IMAGE}	"ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cacea948_37b132={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [34]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_WIFI_NAME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cacea978_31f55e0={{&GUID_cd87b54f_21744cb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [35]{D_CTRL_LABEL}	"ID_ZHILIAN_MAIN_LABEL_WIFI_SIGNAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cacea978_31f55e2={{&GUID_cd87b54f_21d64cb, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_zhilian_main_menu_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 960, 540, 0, -1, (D_FrameCtrlDescr*)&GUID_cd862b21_3bc29, },
	// [1]ID_ZHILIAN_MAIN_IMAGE
	{D_CTRL_IMAGE, 0, 31, 16, 20, 124, 41, 30, -1, (D_FrameCtrlDescr*)&GUID_cd862b7d_09a18be, },
	// [2]ID_ZHILIAN_MAIN_GROUP_BUTTON
	{D_CTRL_GROUP, 0, 0, 70, 20, 960, 418, 30, -1, (D_FrameCtrlDescr*)&GUID_cd86a629_1ad5cd7, },
	// [3]ID_ZHILIAN_MAIN_BUTTON_MIRA
	{D_CTRL_BUTTON, 2, 54, 1, 20, 285, 138, 30, -1, (D_FrameCtrlDescr*)&GUID_cd863796_0fd4823, },
	// [4]ID_ZHILIAN_MAIN_IMAGE_MIRA
	{D_CTRL_IMAGE, 3, 15, 15, 20, 255, 108, 30, -1, (D_FrameCtrlDescr*)&GUID_cd864d98_01a4db7, },
	// [5]ID_ZHILIAN_MAIN_LABEL_MIRTEXT
	{D_CTRL_LABEL, 4, 15, 10, 1, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd9bdbea_3bdf3e, },
	// [6]ID_ZHILIAN_MAIN_BUTTON_DLNA
	{D_CTRL_BUTTON, 2, 54, 140, 20, 285, 138, 30, -1, (D_FrameCtrlDescr*)&GUID_cd86388c_0de5f90, },
	// [7]ID_ZHILIAN_MAIN_IMAGE_DLNA
	{D_CTRL_IMAGE, 6, 15, 15, 20, 255, 108, 30, -1, (D_FrameCtrlDescr*)&GUID_cd864ed9_0ec66bb, },
	// [8]ID_ZHILIAN_MAIN_LABEL_DLNATEXT
	{D_CTRL_LABEL, 7, 15, 10, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd9bde4c_2d51547, },
	// [9]ID_ZHILIAN_MAIN_BUTTON_AIRPLAY
	{D_CTRL_BUTTON, 2, 54, 279, 20, 285, 138, 30, -1, (D_FrameCtrlDescr*)&GUID_c623ebe0_3af1649, },
	// [10]ID_ZHILIAN_MAIN_IMAGE_AIRPLAY
	{D_CTRL_IMAGE, 9, 15, 15, 20, 255, 108, 30, -1, (D_FrameCtrlDescr*)&GUID_c6da41ef_2ed26e9, },
	// [11]ID_ZHILIAN_MAIN_LABEL_AIRPLAY
	{D_CTRL_LABEL, 10, 15, 10, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c6df651_04412db, },
	// [12]ID_ZHILIAN_MAIN_BUTTON_SOURCE
	{D_CTRL_BUTTON, 2, 345, 210, 20, 278, 207, 30, -1, (D_FrameCtrlDescr*)&GUID_cd862d15_3261649, },
	// [13]ID_ZHILIAN_MAIN_IMAGE_SOURCE
	{D_CTRL_IMAGE, 12, 15, 15, 8, 248, 177, 30, -1, (D_FrameCtrlDescr*)&GUID_cd864aec_31c390c, },
	// [14]ID_ZHILIAN_MAIN_LABEL_SOURCE
	{D_CTRL_LABEL, 13, 15, 10, 20, 100, 29, 30, -1, (D_FrameCtrlDescr*)&GUID_cd862c06_37b2cd6, },
	// [15]ID_ZHILIAN_MAIN_BUTTON_MEDIA
	{D_CTRL_BUTTON, 2, 345, 1, 20, 278, 207, 30, -1, (D_FrameCtrlDescr*)&GUID_c6d38be0_3af1649, },
	// [16]ID_ZHILIAN_MAIN_IMAGE_MEDIA
	{D_CTRL_IMAGE, 15, 15, 15, 20, 248, 177, 30, -1, (D_FrameCtrlDescr*)&GUID_c6d38cef_2ed26e9, },
	// [17]ID_ZHILIAN_MAIN_LABEL_MEDIA
	{D_CTRL_LABEL, 16, 15, 10, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c6d38d61_04412db, },
	// [18]ID_ZHILIAN_MAIN_BUTTON_IPTV
	{D_CTRL_BUTTON, 2, 628, 1, 20, 278, 207, 30, -1, (D_FrameCtrlDescr*)&GUID_cd86399d_1322ea6, },
	// [19]ID_ZHILIAN_MAIN_IMAGE_IPTV
	{D_CTRL_IMAGE, 18, 15, 15, 20, 248, 177, 30, -1, (D_FrameCtrlDescr*)&GUID_cd864fdf_3a45d03, },
	// [20]ID_ZHILIAN_MAIN_LABEL_IPTV
	{D_CTRL_LABEL, 19, 15, 10, 0, 142, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd863932_18f41bb, },
	// [21]ID_ZHILIAN_MAIN_LABEL_IPTVTEXT
	{D_CTRL_LABEL, 19, 36, 142, 0, 200, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd9bdeed_28374d, },
	// [22]ID_ZHILIAN_MAIN_BUTTON_SETTING
	{D_CTRL_BUTTON, 2, 628, 210, 20, 278, 207, 30, -1, (D_FrameCtrlDescr*)&GUID_cd862d88_37926e9, },
	// [23]ID_ZHILIAN_MAIN_IMAGE_SETTING
	{D_CTRL_IMAGE, 22, 15, 15, 20, 248, 177, 30, -1, (D_FrameCtrlDescr*)&GUID_cd864c1f_03c305e, },
	// [24]ID_ZHILIAN_MAIN_LEBEL_SETTINGTEXT
	{D_CTRL_LABEL, 23, 15, 10, -5, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd9bdb64_3b712db, },
	// [25]ID_ZHILIAN_MAIN_IMAGE_EXIT
	{D_CTRL_IMAGE, 0, 742, 498, 20, 81, 34, 30, -1, (D_FrameCtrlDescr*)&GUID_cd865172_03b7ff5, },
	// [26]ID_ZHILIAN_MAIN_LABEL_EXIT
	{D_CTRL_LABEL, 0, 824, 498, 20, 80, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_cd865194_034260d, },
	// [27]ID_ZHILIAN_MAIN_LABEL_OK_ICON
	{D_CTRL_LABEL, 0, 551, 500, 20, 81, 31, 30, -1, (D_FrameCtrlDescr*)&GUID_c6d4776f_2932cd6, },
	// [28]ID_ZHILIAN_MAIN_IMAGE_CHOOSE
	{D_CTRL_IMAGE, 27, 26, 0, 0, 31, 29, 30, -1, (D_FrameCtrlDescr*)&GUID_cd8650a3_3b61238, },
	// [29]ID_ZHILIAN_MAIN_LABEL_CHOOSE
	{D_CTRL_LABEL, 0, 633, 500, 20, 80, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_cd865108_0f21ad4, },
	// [30]ID_ZHILIAN_MAIN_WIFI_SHOW_GROUP
	{D_CTRL_GROUP, 0, 590, 25, 20, 370, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd86a629_2ad5cd7, },
	// [31]ID_ZHILIAN_MAIN_LABEL_WIFI_INFO
	{D_CTRL_LABEL, 30, 230, 0, 20, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cacea8ae_1a01614, },
	// [32]ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC
	{D_CTRL_IMAGE, 30, 0, 0, 32, 30, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_cacea948_37b130, },
	// [33]ID_ZHILIAN_MAIN_IMAGE_WIFI_PIC_BG
	{D_CTRL_IMAGE, 30, 0, 0, 32, 30, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_cacea948_37b132, },
	// [34]ID_ZHILIAN_MAIN_LABEL_WIFI_NAME
	{D_CTRL_LABEL, 30, 80, 0, 20, 150, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cacea978_31f55e0, },
	// [35]ID_ZHILIAN_MAIN_LABEL_WIFI_SIGNAL
	{D_CTRL_LABEL, 30, 35, 0, 20, 45, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cacea978_31f55e2, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_zhilian_main_menu_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_zhilian_main_menu_window[36];
D_Frame atv_zhilian_main_menu_window = {
	run_ctrls_atv_zhilian_main_menu_window, 
	ctrl_description_of_atv_zhilian_main_menu_window, 
	atv_zhilian_main_menu_window_init, 
};

