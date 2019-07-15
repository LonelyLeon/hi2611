/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2018-09-18 17:26:05

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2018-08-24 14:48:36.658

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
#define	ID_GENERAL_LABEL_GENERAL_SETTING	1
#define	ID_GENERAL_GROUP	2
#define	ID_GENERAL_LABEL_SHOW	3
#define	ID_GENERAL_LABEL_1	4
#define	ID_GENERAL_GROUP_3	5
#define	ID_GENERAL_GROUP_4	6
#define	ID_GENERAL_GROUP_5	7
#define	ID_GENERAL_GROUP_6	8
#define	ID_GENERAL_BUTTON_3	9
#define	ID_GENERAL_BUTTON_4	10
#define	ID_GENERAL_BUTTON_5	11
#define	ID_GENERAL_BUTTON_6	12
#define	ID_GENERAL_LABEL_3	13
#define	ID_GENERAL_LABEL_4	14
#define	ID_GENERAL_LABEL_5	15
#define	ID_GENERAL_LABEL_6	16

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, atv_IDS_GENERAL_SETTING, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc0f79_04e7826={-1, -1, atv_IDS_LOGO, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc0f79_04e33a9={-1, -1, atv_IDS_LOGO, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc0f79_04e36d8={-1, -1, atv_IDS_POWER_MODE, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc0f79_04e59d4={-1, -1, atv_IDS_POWER_MODE, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc0f79_04e4237={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc0f79_04e503f={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08988cd_2de5af1={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c14e5676_06d6ccf={-1, atv_IMG_ID_box_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c14e5676_06d736f={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c14e5b9d_1d47290={-1, -1, atv_IDS_LVDS_MAP, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c98b95ff_07d428b={-1, -1, atv_IDS_LVDS_MAP, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c98b976e_33c985={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_GENERAL_SETTING"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_GENERAL_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda8768_3c81b4b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_SHOW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c14e5b9d_1d43134={{&GUID_c14e5b9d_1d47290, NULL, &GUID_c98b95ff_07d428b, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda2ec1_38a6275={{&GUID_c08988cd_2de5af1, &GUID_c14e5676_06d736f, &GUID_c98b976e_33c985, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_GENERAL_GROUP_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196952={{NULL, &GUID_c14e5676_06d6ccf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_GENERAL_GROUP_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e35_1d45af1={{NULL, &GUID_c14e5676_06d6ccf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_GROUP}	"ID_GENERAL_GROUP_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e7a_05dbb3={{NULL, &GUID_c14e5676_06d6ccf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_GROUP}	"ID_GENERAL_GROUP_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cb2e5384_0506952={{NULL, &GUID_c14e5676_06d6ccf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_BUTTON}	"ID_GENERAL_BUTTON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda3362_06d954={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_BUTTON}	"ID_GENERAL_BUTTON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4df5={{&GUID_bedc0f79_04e36d8, &GUID_bedc0f79_04e59d4, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_BUTTON}	"ID_GENERAL_BUTTON_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda35d1_34b101a={{&GUID_bedc0f79_04e4237, &GUID_bedc0f79_04e503f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_BUTTON}	"ID_GENERAL_BUTTON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cb2e549b_1282ea6={{&GUID_c08988cd_2de5af1, &GUID_c14e5676_06d736f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9517_1865062={{&GUID_c08988cd_2de5af1, &GUID_c14e5676_06d736f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb957c_06df9e={{&GUID_c08988cd_2de5af1, &GUID_c14e5676_06d736f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb95a2_1199c5={{&GUID_c08988cd_2de5af1, &GUID_c14e5676_06d736f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cb2e5f1b_394161d={{&GUID_c08988cd_2de5af1, &GUID_c14e5676_06d736f, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_general_setting_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 485, 660, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_GENERAL_LABEL_GENERAL_SETTING
	{D_CTRL_LABEL, 0, 111, 7, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_GENERAL_GROUP
	{D_CTRL_GROUP, 0, 0, 37, 20, 485, 621, 30, -1, (D_FrameCtrlDescr*)&GUID_beda8768_3c81b4b, },
	// [3]ID_GENERAL_LABEL_SHOW
	{D_CTRL_LABEL, 2, 23, 8, 0, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c14e5b9d_1d43134, },
	// [4]ID_GENERAL_LABEL_1
	{D_CTRL_LABEL, 2, 311, 8, 20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda2ec1_38a6275, },
	// [5]ID_GENERAL_GROUP_3
	{D_CTRL_GROUP, 2, 2, 40, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196952, },
	// [6]ID_GENERAL_GROUP_4
	{D_CTRL_GROUP, 2, 2, 74, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e35_1d45af1, },
	// [7]ID_GENERAL_GROUP_5
	{D_CTRL_GROUP, 2, 2, 108, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e7a_05dbb3, },
	// [8]ID_GENERAL_GROUP_6
	{D_CTRL_GROUP, 2, 2, 142, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cb2e5384_0506952, },
	// [9]ID_GENERAL_BUTTON_3
	{D_CTRL_BUTTON, 5, 21, 2, 0, 180, 26, 30, 5, (D_FrameCtrlDescr*)&GUID_beda3362_06d954, },
	// [10]ID_GENERAL_BUTTON_4
	{D_CTRL_BUTTON, 6, 21, 2, 0, 180, 26, 30, 6, (D_FrameCtrlDescr*)&GUID_beda356d_29f4df5, },
	// [11]ID_GENERAL_BUTTON_5
	{D_CTRL_BUTTON, 7, 21, 2, 0, 180, 26, 30, 7, (D_FrameCtrlDescr*)&GUID_beda35d1_34b101a, },
	// [12]ID_GENERAL_BUTTON_6
	{D_CTRL_BUTTON, 8, 21, 2, 0, 180, 26, 30, 8, (D_FrameCtrlDescr*)&GUID_cb2e549b_1282ea6, },
	// [13]ID_GENERAL_LABEL_3
	{D_CTRL_LABEL, 5, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9517_1865062, },
	// [14]ID_GENERAL_LABEL_4
	{D_CTRL_LABEL, 6, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb957c_06df9e, },
	// [15]ID_GENERAL_LABEL_5
	{D_CTRL_LABEL, 7, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb95a2_1199c5, },
	// [16]ID_GENERAL_LABEL_6
	{D_CTRL_LABEL, 8, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_cb2e5f1b_394161d, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	general_setting_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_general_setting_window[17];
D_Frame general_setting_window = {
	run_ctrls_general_setting_window, 
	ctrl_description_of_general_setting_window, 
	general_setting_window_init, 
};

