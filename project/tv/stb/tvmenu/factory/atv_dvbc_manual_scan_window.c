/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2015-07-10 09:37:12

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-07-09 12:05:15.417

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
#define	ID_LABEL_TITLE	1
#define	ID_GROUP	2
#define	ID_GROUP_FREQ	3
#define	ID_LABEL_FREQ	4
#define	ID_INPUT_FREQ	5
#define	ID_GROUP_BAUD	6
#define	ID_LABEL_BAUD	7
#define	ID_INPUT_BAUD	8
#define	ID_GROUP_MODE	9
#define	ID_LABEL_MODE	10
#define	ID_SELECT_MODE	11
#define	ID_GROUP_STRENGTH	12
#define	ID_LABEL_STRENGTH	13
#define	ID_PROGRESS_STRENGTH	14
#define	ID_GROUP_QUALITY	15
#define	ID_LABEL_QUALITY	16
#define	ID_PROGRESS_QUALYTY	17
#define	ID_IMAGE_BOTTOM	18
#define	ID_HINT_ESC	19
#define	ID_LABEL_ESC	20

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee8087e_6c={atv_COLOR_ENUM_65, -1, atv_IDS_SIGNAL_DETECT, &atv_fmt_left_middle_h15_v15_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee80985_90={atv_COLOR_ENUM_13, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee80b0c_19={atv_COLOR_ENUM_30, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee80eae_32={-1, -1, atv_IDS_FREQUENCY, &atv_fmt_left_middle_h10_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee8109e_e6={atv_COLOR_ENUM_87, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee8109e_22={atv_COLOR_ENUM_106, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee82ecd_13={-1, -1, atv_IDS_MODULATION, &atv_fmt_left_middle_h10_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee8330e_0c={-1, -1, atv_IDS_STRENGH_BAR, &atv_fmt_left_middle_h10_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee833b9_60={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee83680_7a={-1, -1, atv_IDS_QUALITY_BAR, &atv_fmt_left_middle_h10_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee84b1d_bb={-1, -1, atv_IDS_SYMBOL_RATE, &atv_fmt_left_middle_h10_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee84ead_db={-1, atv_IMG_ID_hint_button, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee852b4_3e={-1, -1, atv_IDS_BACK, &atv_fmt_left_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee67715_29={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_LABEL_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee8087e_e1={{&GUID_bee8087e_6c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee80985_52={{&GUID_bee80985_90, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_GROUP_FREQ"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee80b0c_c1={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_LABEL_FREQ"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee80eae_8d={{&GUID_bee80eae_32, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_INPUT}	"ID_INPUT_FREQ"
static char GUID_bee8109e_a1[3+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_bee8109e_d2={{&GUID_bee8109e_e6, &GUID_bee8109e_22, NULL, }, 1, 0, 3, GUID_bee8109e_a1, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_GROUP_BAUD"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee81178_30={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_LABEL_BAUD"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee812fb_a3={{&GUID_bee84b1d_bb, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_INPUT}	"ID_INPUT_BAUD"
static char GUID_bee82311_07[4+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_bee82311_19={{&GUID_bee8109e_e6, &GUID_bee8109e_22, NULL, }, 1, 0, 4, GUID_bee82311_07, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_GROUP}	"ID_GROUP_MODE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee82e5c_c5={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_LABEL_MODE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee82ecd_7f={{&GUID_bee82ecd_13, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_SELECT}	"ID_SELECT_MODE"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_bee82f65_8a={{&GUID_bee8109e_e6, &GUID_bee8109e_22, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_GROUP}	"ID_GROUP_STRENGTH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee831e7_6a={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_LABEL_STRENGTH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee8330e_f5={{&GUID_bee8330e_0c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_PROGRESS}	"ID_PROGRESS_STRENGTH"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_bee833b9_ad={{&GUID_bee833b9_60, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_104, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_GROUP}	"ID_GROUP_QUALITY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee834a2_4d={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_LABEL_QUALITY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee83680_9c={{&GUID_bee83680_7a, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_PROGRESS}	"ID_PROGRESS_QUALYTY"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_bee836e2_a5={{&GUID_bee833b9_60, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_104, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_IMAGE}	"ID_IMAGE_BOTTOM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee83830_31={{&GUID_bee80985_90, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_LABEL}	"ID_HINT_ESC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee84ead_a6={{&GUID_bee84ead_db, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_LABEL}	"ID_LABEL_ESC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee852b4_0c={{&GUID_bee852b4_3e, NULL, NULL, }, 0, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_dvbc_manual_scan_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 325, 102, 0, 630, 516, 0, -1, (D_FrameCtrlDescr*)&GUID_bee67715_29, },
	// [1]ID_LABEL_TITLE
	{D_CTRL_LABEL, 0, 0, 0, 14, 610, 71, 30, -1, (D_FrameCtrlDescr*)&GUID_bee8087e_e1, },
	// [2]ID_GROUP
	{D_CTRL_GROUP, 0, 27, 68, 14, 583, 360, 30, -1, (D_FrameCtrlDescr*)&GUID_bee80985_52, },
	// [3]ID_GROUP_FREQ
	{D_CTRL_GROUP, 2, 29, 51, 21, 516, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee80b0c_c1, },
	// [4]ID_LABEL_FREQ
	{D_CTRL_LABEL, 3, 12, 2, 43, 180, 43, 30, -1, (D_FrameCtrlDescr*)&GUID_bee80eae_8d, },
	// [5]ID_INPUT_FREQ
	{D_CTRL_INPUT, 3, 262, 1, 43, 254, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee8109e_d2, },
	// [6]ID_GROUP_BAUD
	{D_CTRL_GROUP, 2, 29, 101, 21, 516, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee81178_30, },
	// [7]ID_LABEL_BAUD
	{D_CTRL_LABEL, 6, 12, 0, 23, 180, 43, 30, -1, (D_FrameCtrlDescr*)&GUID_bee812fb_a3, },
	// [8]ID_INPUT_BAUD
	{D_CTRL_INPUT, 6, 262, -1, 23, 254, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee82311_19, },
	// [9]ID_GROUP_MODE
	{D_CTRL_GROUP, 2, 29, 151, 21, 516, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee82e5c_c5, },
	// [10]ID_LABEL_MODE
	{D_CTRL_LABEL, 9, 12, 0, 5, 180, 43, 30, -1, (D_FrameCtrlDescr*)&GUID_bee82ecd_7f, },
	// [11]ID_SELECT_MODE
	{D_CTRL_SELECT, 9, 262, -1, 5, 254, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee82f65_8a, },
	// [12]ID_GROUP_STRENGTH
	{D_CTRL_GROUP, 2, 29, 201, 21, 516, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee831e7_6a, },
	// [13]ID_LABEL_STRENGTH
	{D_CTRL_LABEL, 12, 12, -1, -9, 100, 43, 30, -1, (D_FrameCtrlDescr*)&GUID_bee8330e_f5, },
	// [14]ID_PROGRESS_STRENGTH
	{D_CTRL_PROGRESS, 12, 211, 1, -9, 301, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bee833b9_ad, },
	// [15]ID_GROUP_QUALITY
	{D_CTRL_GROUP, 2, 29, 251, 21, 516, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee834a2_4d, },
	// [16]ID_LABEL_QUALITY
	{D_CTRL_LABEL, 15, 12, -1, -25, 100, 43, 30, -1, (D_FrameCtrlDescr*)&GUID_bee83680_9c, },
	// [17]ID_PROGRESS_QUALYTY
	{D_CTRL_PROGRESS, 15, 211, 1, -25, 301, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bee836e2_a5, },
	// [18]ID_IMAGE_BOTTOM
	{D_CTRL_IMAGE, 0, 27, 426, 14, 583, 65, 30, -1, (D_FrameCtrlDescr*)&GUID_bee83830_31, },
	// [19]ID_HINT_ESC
	{D_CTRL_LABEL, 18, 337, 15, 17, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_bee84ead_a6, },
	// [20]ID_LABEL_ESC
	{D_CTRL_LABEL, 18, 452, 17, 17, 100, 33, 30, -1, (D_FrameCtrlDescr*)&GUID_bee852b4_0c, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_dvbc_manual_scan_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_dvbc_manual_scan_window[21];
D_Frame atv_dvbc_manual_scan_window = {
	run_ctrls_atv_dvbc_manual_scan_window, 
	ctrl_description_of_atv_dvbc_manual_scan_window, 
	atv_dvbc_manual_scan_window_init, 
};

