/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2015-07-10 09:48:58

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
#define	ID_DEMO_DETIAL_LSIT_TITLE	1
#define	ID_DEMO_DETIAL_INFO	2
#define	ID_DEMO_DETIAL_BUTTON_EXIT	3
#define	ID_DEMO_DETIAL_LABLE_EXIT	4
#define	ID_DEMO_DETIAL_L	5
#define	ID_DEMO_DETIAL_R	6
#define	ID_DEMO_DETIAL_OTHER_INFO_LABEL	7
#define	ID_DEMO_DETIAL_DRAW_BACK	8

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0b99d7b_0ea4900={atv_COLOR_ENUM_65, -1, atv_IDS_DEM_HN, &atv_fmt_left_middle_h15_v15_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0ba8769_3c83bce={atv_COLOR_ENUM_13, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0ba9835_1a53342={-1, atv_IMG_ID_hint_button, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0ba99d0_1e42cb6={-1, -1, atv_IDS_BACK, &atv_fmt_left_middle_h05_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0ba9a9c_271382e={-1, atv_IMG_ID_program_info_direction_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0ba9b51_1f44c0b={-1, atv_IMG_ID_program_info_direction_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0ba9bff_36b1497={-1, -1, atv_IDS_DEM_OTHER_INFO, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0b9992e_02e29={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_DEMO_DETIAL_LSIT_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0b99d7b_0ea7f6f={{&GUID_c0b99d7b_0ea4900, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_DEMO_DETIAL_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0ba8769_3c86ee8={{&GUID_c0ba8769_3c83bce, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_DEMO_DETIAL_BUTTON_EXIT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0ba9835_1a5607e={{&GUID_c0ba9835_1a53342, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_DEMO_DETIAL_LABLE_EXIT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0ba99d0_1e46b6e={{&GUID_c0ba99d0_1e42cb6, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_DEMO_DETIAL_L"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0ba9a9c_271666={{&GUID_c0ba9a9c_271382e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_DEMO_DETIAL_R"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0ba9b51_1f447a1={{&GUID_c0ba9b51_1f44c0b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_DEMO_DETIAL_OTHER_INFO_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0ba9bff_36b250b={{&GUID_c0ba9bff_36b1497, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_DRAW_AREA}	"ID_DEMO_DETIAL_DRAW_BACK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0ba9c90_09c7fa6={{&GUID_c0ba8769_3c83bce, NULL, NULL, }, 0, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_channel_demo_detial_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 325, 102, 0, 630, 516, 0, -1, (D_FrameCtrlDescr*)&GUID_c0b9992e_02e29, },
	// [1]ID_DEMO_DETIAL_LSIT_TITLE
	{D_CTRL_LABEL, 0, 0, 0, 122, 610, 68, 30, -1, (D_FrameCtrlDescr*)&GUID_c0b99d7b_0ea7f6f, },
	// [2]ID_DEMO_DETIAL_INFO
	{D_CTRL_LABEL, 0, 25, 425, 122, 584, 68, 30, -1, (D_FrameCtrlDescr*)&GUID_c0ba8769_3c86ee8, },
	// [3]ID_DEMO_DETIAL_BUTTON_EXIT
	{D_CTRL_LABEL, 2, 69, 16, -13, 100, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_c0ba9835_1a5607e, },
	// [4]ID_DEMO_DETIAL_LABLE_EXIT
	{D_CTRL_LABEL, 2, 169, 16, -13, 74, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_c0ba99d0_1e46b6e, },
	// [5]ID_DEMO_DETIAL_L
	{D_CTRL_LABEL, 2, 328, 16, 87, 20, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_c0ba9a9c_271666, },
	// [6]ID_DEMO_DETIAL_R
	{D_CTRL_LABEL, 2, 369, 16, 87, 20, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_c0ba9b51_1f447a1, },
	// [7]ID_DEMO_DETIAL_OTHER_INFO_LABEL
	{D_CTRL_LABEL, 2, 403, 16, 87, 112, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_c0ba9bff_36b250b, },
	// [8]ID_DEMO_DETIAL_DRAW_BACK
	{D_CTRL_DRAW_AREA, 0, 25, 67, 90, 584, 359, 30, -1, (D_FrameCtrlDescr*)&GUID_c0ba9c90_09c7fa6, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	channel_demo_detial_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_channel_demo_detial_window[9];
D_Frame channel_demo_detial_window = {
	run_ctrls_channel_demo_detial_window, 
	ctrl_description_of_channel_demo_detial_window, 
	channel_demo_detial_window_init, 
};

