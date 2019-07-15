/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2019-02-21 16:12:21

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2019-02-21 11:45:23.159

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
#define	ID_ZHILIAN_MENU_GROUP	1
#define	ID_ZHILIAN_MENU_GROUP_INFO	2
#define	ID_ZHILIAN_MENU_IMAGE_TV	3
#define	ID_ZHILIAN_MENU_IMAGE_WIFI	4
#define	ID_ZHILIAN_MENU_IMAGE_PHONE	5
#define	ID_ZHILIAN_MENU_BUTTON_MIRA	6
#define	ID_ZHILIAN_MENU_IMAGE_MIRA	7
#define	ID_ZHILIAN_MENU_LABEL_MIRA	8
#define	ID_ZHILIAN_MENU_BUTTON_TSNET	9
#define	ID_ZHILIAN_MENU_IMAGE_TSNET	10
#define	ID_ZHILIAN_MENU_LABEL_TSNET	11
#define	ID_ZHILIAN_MENU_BUTTON_DLNA	12
#define	ID_ZHILIAN_MENU_IMAGE_DLNA	13
#define	ID_ZHILIAN_MENU_LABEL_DLNA	14
#define	ID_ZHILIAN_MENU_IMAGE_CHOOSE	15
#define	ID_ZHILIAN_MENU_LABEL_OK	16
#define	ID_ZHILIAN_MENU_IMAGE_FLAG	17
#define	ID_ZHILIAN_MENU_LABEL_TITLE	18
#define	ID_ZHILIAN_MENU_LABEL_INFO1	19
#define	ID_ZHILIAN_MENU_LABEL_INFO2	20
#define	ID_ZHILIAN_MENU_LABEL_INFO3	21


//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd5f94_0e14823={-1, atv_IMG_ID_main_zhilian_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd5ffb_19572ae={-1, atv_IMG_ID_zhilian_main_tv_pic, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd6059_0556df1={-1, atv_IMG_ID_zhilian_main_wifi_pic, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd60c2_3191eb={-1, atv_IMG_ID_zhilian_main_phone_pic, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd6222_198124={-1, atv_IMB_ID_COMB_zhilian_main_focse, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd631f_018491c={-1, atv_IMG_ID_FS_Zhilian_Mira, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd6397_14d54de={-1, -1, atv_IDS_WIFI_DISPLAY, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd65fc_0ee767d={-1, atv_IMG_ID_hint_button, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd66a5_3ac1e1f={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd631f_0184922={-1, atv_IMG_ID_FS_Zhilian_Tsnet, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd6397_14d5444={-1, -1, atv_IDS_DTV_SHAREING, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd631f_0184933={-1, atv_IMG_ID_FS_Zhilian_Dlna, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd6397_14d5455={-1, -1, atv_IDS_NETWORK_SHARING, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd6efe_1b05e76={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd6f9b_386344c={-1, -1, -1, &atv_fmt_left_middle_h00_v00_multi_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6d479b0_2bb4ae1={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6cd6efe_1b05e11={-1, atv_IMG_ID_main_zhilian_pic, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd5f94_0e129={{&GUID_c6cd5f94_0e14823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_ZHILIAN_MENU_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd5f9b_16218be={{&GUID_c6d479b0_2bb4ae1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_ZHILIAN_MENU_GROUP_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd6efe_1b019e8={{&GUID_c6cd6efe_1b05e76, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_IMAGE}	"ID_ZHILIAN_MENU_IMAGE_TV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd5ffb_1952cd6={{&GUID_c6cd5ffb_19572ae, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_IMAGE}	"ID_ZHILIAN_MENU_IMAGE_WIFI"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd6059_0551649={{&GUID_c6cd6059_0556df1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_IMAGE}	"ID_ZHILIAN_MENU_IMAGE_PHONE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd60c2_31926e9={{&GUID_c6cd60c2_3191eb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_BUTTON}	"ID_ZHILIAN_MENU_BUTTON_MIRA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd6222_198f3e={{NULL, &GUID_c6cd6222_198124, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_IMAGE}	"ID_ZHILIAN_MENU_IMAGE_MIRA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd631f_018440d={{&GUID_c6cd631f_018491c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_ZHILIAN_MENU_LABEL_MIRA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd6397_14d1547={{&GUID_c6cd6397_14d54de, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_BUTTON}	"ID_ZHILIAN_MENU_BUTTON_TSNET"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd6222_198f11={{NULL, &GUID_c6cd6222_198124, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_IMAGE}	"ID_ZHILIAN_MENU_IMAGE_TSNET"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd631f_0184411={{&GUID_c6cd631f_0184922, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_ZHILIAN_MENU_LABEL_TSNET"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd6397_14d1511={{&GUID_c6cd6397_14d5444, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_BUTTON}	"ID_ZHILIAN_MENU_BUTTON_DLNA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd6222_198f22={{NULL, &GUID_c6cd6222_198124, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_IMAGE}	"ID_ZHILIAN_MENU_IMAGE_DLNA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd631f_0184422={{&GUID_c6cd631f_0184933, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_ZHILIAN_MENU_LABEL_DLNA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd6397_14d1522={{&GUID_c6cd6397_14d5455, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_IMAGE}	"ID_ZHILIAN_MENU_IMAGE_CHOOSE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd65fc_0ee7a5a={{&GUID_c6cd65fc_0ee767d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_ZHILIAN_MENU_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd66a5_3ac3b25={{&GUID_c6cd66a5_3ac1e1f, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_IMAGE}	"ID_ZHILIAN_MENU_IMAGE_FLAG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6d485dd_0ea4ae1={{&GUID_c6cd6efe_1b05e11, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_LABEL}	"ID_ZHILIAN_MENU_LABEL_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd6f9b_3865b88={{&GUID_c6cd6f9b_386344c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_LABEL}	"ID_ZHILIAN_MENU_LABEL_INFO1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd6f9b_3865b99={{&GUID_c6cd6f9b_386344c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_LABEL}	"ID_ZHILIAN_MENU_LABEL_INFO2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd7063_05767c9={{&GUID_c6cd6f9b_386344c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_ZHILIAN_MENU_LABEL_INFO3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6cd7091_0b96871={{&GUID_c6cd6f9b_386344c, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_zhilian_menu_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 960, 540, 0, -1, (D_FrameCtrlDescr*)&GUID_c6cd5f94_0e129, },
	// [1]ID_ZHILIAN_MENU_GROUP
	{D_CTRL_GROUP, 0, 0, 0, 20, 960, 540, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd5f9b_16218be, },
	// [2]ID_ZHILIAN_MENU_GROUP_INFO
	{D_CTRL_GROUP, 1, 595, 0, 0, 365, 540, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd6efe_1b019e8, },
	// [3]ID_ZHILIAN_MENU_IMAGE_TV
	{D_CTRL_IMAGE, 1, 260, 132, 0, 234, 150, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd5ffb_1952cd6, },
	// [4]ID_ZHILIAN_MENU_IMAGE_WIFI
	{D_CTRL_IMAGE, 1, 197, 225, 0, 38, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd6059_0551649, },
	// [5]ID_ZHILIAN_MENU_IMAGE_PHONE
	{D_CTRL_IMAGE, 1, 86, 187, 0, 85, 95, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd60c2_31926e9, },
	// [6]ID_ZHILIAN_MENU_BUTTON_MIRA
	{D_CTRL_BUTTON, 1, 120, 326, 0, 158, 125, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd6222_198f3e, },
	// [7]ID_ZHILIAN_MENU_IMAGE_MIRA
	{D_CTRL_IMAGE, 6, 15, 15, 0, 128, 95, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd631f_018440d, },
	// [8]ID_ZHILIAN_MENU_LABEL_MIRA
	{D_CTRL_LABEL, 7, 5, 63, 0, 118, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd6397_14d1547, },
	// [9]ID_ZHILIAN_MENU_BUTTON_TSNET
	{D_CTRL_BUTTON, 1, 219, 326, 0, 158, 125, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd6222_198f11, },
	// [10]ID_ZHILIAN_MENU_IMAGE_TSNET
	{D_CTRL_IMAGE, 9, 15, 15, 0, 128, 95, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd631f_0184411, },
	// [11]ID_ZHILIAN_MENU_LABEL_TSNET
	{D_CTRL_LABEL, 10, 5, 63, 0, 118, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd6397_14d1511, },
	// [12]ID_ZHILIAN_MENU_BUTTON_DLNA
	{D_CTRL_BUTTON, 1, 317, 326, 0, 158, 125, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd6222_198f22, },
	// [13]ID_ZHILIAN_MENU_IMAGE_DLNA
	{D_CTRL_IMAGE, 12, 15, 15, 0, 128, 95, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd631f_0184422, },
	// [14]ID_ZHILIAN_MENU_LABEL_DLNA
	{D_CTRL_LABEL, 13, 5, 63, 0, 118, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd6397_14d1522, },
	// [15]ID_ZHILIAN_MENU_IMAGE_CHOOSE
	{D_CTRL_IMAGE, 1, 40, 494, 0, 80, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd65fc_0ee7a5a, },
	// [16]ID_ZHILIAN_MENU_LABEL_OK
	{D_CTRL_LABEL, 1, 125, 495, 0, 166, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd66a5_3ac3b25, },
	// [17]ID_ZHILIAN_MENU_IMAGE_FLAG
	{D_CTRL_IMAGE, 1, 37, 32, 0, 108, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_c6d485dd_0ea4ae1, },
	// [18]ID_ZHILIAN_MENU_LABEL_TITLE
	{D_CTRL_LABEL, 2, 15, 30, 20, 160, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd6f9b_3865b88, },
	// [19]ID_ZHILIAN_MENU_LABEL_INFO1
	{D_CTRL_LABEL, 2, 15, 69, 20, 340, 60, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd6f9b_3865b99, },
	// [20]ID_ZHILIAN_MENU_LABEL_INFO2
	{D_CTRL_LABEL, 2, 15, 129, 20, 340, 197, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd7063_05767c9, },
	// [21]ID_ZHILIAN_MENU_LABEL_INFO3
	{D_CTRL_LABEL, 2, 15, 314, 20, 340, 99, 30, -1, (D_FrameCtrlDescr*)&GUID_c6cd7091_0b96871, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	zhilian_menu_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_zhilian_menu_window[22];
D_Frame zhilian_menu_window = {
	run_ctrls_zhilian_menu_window, 
	ctrl_description_of_zhilian_menu_window, 
	zhilian_menu_window_init, 
};

