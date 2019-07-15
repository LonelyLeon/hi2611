/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2015-03-24 17:18:26

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2014-12-24 14:48:49.406

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
#define	ID_SCAN_CONFIG_LABEL_SCAN_CONFIG	1
#define	ID_SCAN_CONFIG_GROUP	2
#define	ID_SCAN_CONFIG_GROUP_1	3
#define	ID_SCAN_CONFIG_GROUP_2	4
#define	ID_SCAN_CONFIG_BUTTON_1	5
#define	ID_SCAN_CONFIG_LABEL_1	6
#define	ID_SCAN_CONFIG_BUTTON_2	7
#define	ID_SCAN_CONFIG_LABEL_2	8

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, atv_IDS_TV_SCAN_CONFIG, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_128645b={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_1282337={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedaa198_08c7e87={-1, atv_IMG_ID_box_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf0098de_1672cd8={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08a818a_1861eb={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_SCAN_CONFIG_LABEL_SCAN_CONFIG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_SCAN_CONFIG_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda8768_3c81b4b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_SCAN_CONFIG_GROUP_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96c42_0ab29={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_SCAN_CONFIG_GROUP_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96db6_02e4ae1={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_SCAN_CONFIG_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed9bb91_128666e={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_SCAN_CONFIG_LABEL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda2ec1_38a6275={{&GUID_bf0098de_1672cd8, &GUID_bf0098de_1672cd8, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_BUTTON}	"ID_SCAN_CONFIG_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda323b_30d1d08={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_SCAN_CONFIG_LABEL_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb946e_0ab59e={{&GUID_c08a818a_1861eb, &GUID_bf0098de_1672cd8, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_tv_scan_config_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 485, 660, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_SCAN_CONFIG_LABEL_SCAN_CONFIG
	{D_CTRL_LABEL, 0, 111, 7, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_SCAN_CONFIG_GROUP
	{D_CTRL_GROUP, 0, 0, 37, 20, 485, 621, 30, -1, (D_FrameCtrlDescr*)&GUID_beda8768_3c81b4b, },
	// [3]ID_SCAN_CONFIG_GROUP_1
	{D_CTRL_GROUP, 2, 2, 6, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96c42_0ab29, },
	// [4]ID_SCAN_CONFIG_GROUP_2
	{D_CTRL_GROUP, 2, 2, 40, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96db6_02e4ae1, },
	// [5]ID_SCAN_CONFIG_BUTTON_1
	{D_CTRL_BUTTON, 3, 21, 2, 0, 180, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_bed9bb91_128666e, },
	// [6]ID_SCAN_CONFIG_LABEL_1
	{D_CTRL_LABEL, 3, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda2ec1_38a6275, },
	// [7]ID_SCAN_CONFIG_BUTTON_2
	{D_CTRL_BUTTON, 4, 21, 2, 0, 180, 26, 30, 4, (D_FrameCtrlDescr*)&GUID_beda323b_30d1d08, },
	// [8]ID_SCAN_CONFIG_LABEL_2
	{D_CTRL_LABEL, 4, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb946e_0ab59e, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	tv_scan_config_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_tv_scan_config_window[9];
D_Frame tv_scan_config_window = {
	run_ctrls_tv_scan_config_window, 
	ctrl_description_of_tv_scan_config_window, 
	tv_scan_config_window_init, 
};

