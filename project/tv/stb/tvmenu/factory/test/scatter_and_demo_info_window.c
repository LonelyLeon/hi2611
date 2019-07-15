/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2015-07-10 09:51:20

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
#define	ID_SCATTER_DEMO_PROGRAM_LSIT_TITLE	1
#define	ID_SCATTER_DEMO_INFO	2
#define	ID_SCATTER_DEMO_L	3
#define	ID_SCATTER_DEMO_R	4
#define	ID_SCATTER_DEMO_OTHER_INFO_LABEL	5
#define	ID_SCATTER_DEMO_BUTTON_EXIT	6
#define	ID_SCATTER_DEMO_LABLE_EXIT	7
#define	ID_SCATTER_DEMO_DRAW_BACK	8
#define	ID_SCATT_DRAW_PIC	9
#define	ID_SCATT_INFO	10

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130621092016_125452={atv_COLOR_ENUM_65, -1, atv_IDS_DEM_SCATTER, &atv_fmt_left_middle_h15_v15_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130621134659_303352={atv_COLOR_ENUM_0, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130625175946_89422={atv_COLOR_ENUM_13, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130626104011_223062={-1, atv_IMG_ID_program_info_direction_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130626104203_130752={-1, atv_IMG_ID_program_info_direction_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130626142215_273022={-1, -1, atv_IDS_DEM_OTHER_INFO, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c04ea57b_119439a2={-1, atv_IMG_ID_hint_button, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c04ea686_1d44202={-1, -1, atv_IDS_BACK, &atv_fmt_left_middle_h05_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c04f6a23_00f48232={atv_COLOR_ENUM_13, -1, atv_IDS_NULL, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130620084411_412={{NULL, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_SCATTER_DEMO_PROGRAM_LSIT_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130621092016_42842={{&PRSUNZY_sunzy_20130621092016_125452, &PRSUNZY_sunzy_20130621134659_303352, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_SCATTER_DEMO_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130625175946_128302={{&PRSUNZY_sunzy_20130625175946_89422, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_SCATTER_DEMO_L"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130626104011_11332={{&PRSUNZY_sunzy_20130626104011_223062, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_SCATTER_DEMO_R"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130626104203_268332={{&PRSUNZY_sunzy_20130626104203_130752, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_SCATTER_DEMO_OTHER_INFO_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130626142215_45452={{&PRSUNZY_sunzy_20130626142215_273022, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_SCATTER_DEMO_BUTTON_EXIT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c04ea57b_1191d3c2={{&GUID_c04ea57b_119439a2, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_SCATTER_DEMO_LABLE_EXIT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c04ea686_1d4326f2={{&GUID_c04ea686_1d44202, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_SCATTER_DEMO_DRAW_BACK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c04f6a23_00f292={{&GUID_c04f6a23_00f48232, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_DRAW_AREA}	"ID_SCATT_DRAW_PIC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0200e44_08c4ae1={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_DRAW_AREA}	"ID_SCATT_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c020a629_1a515fe={{NULL, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_scatter_and_demo_info_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 325, 102, 0, 630, 516, 0, -1, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130620084411_412, },
	// [1]ID_SCATTER_DEMO_PROGRAM_LSIT_TITLE
	{D_CTRL_LABEL, 0, 0, 0, 122, 610, 68, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130621092016_42842, },
	// [2]ID_SCATTER_DEMO_INFO
	{D_CTRL_LABEL, 0, 28, 425, 122, 582, 68, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130625175946_128302, },
	// [3]ID_SCATTER_DEMO_L
	{D_CTRL_LABEL, 2, 295, 15, 87, 20, 36, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130626104011_11332, },
	// [4]ID_SCATTER_DEMO_R
	{D_CTRL_LABEL, 2, 333, 15, 87, 20, 36, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130626104203_268332, },
	// [5]ID_SCATTER_DEMO_OTHER_INFO_LABEL
	{D_CTRL_LABEL, 2, 373, 17, 87, 120, 34, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130626142215_45452, },
	// [6]ID_SCATTER_DEMO_BUTTON_EXIT
	{D_CTRL_LABEL, 2, 80, 15, -13, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c04ea57b_1191d3c2, },
	// [7]ID_SCATTER_DEMO_LABLE_EXIT
	{D_CTRL_LABEL, 2, 185, 15, -13, 68, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_c04ea686_1d4326f2, },
	// [8]ID_SCATTER_DEMO_DRAW_BACK
	{D_CTRL_LABEL, 0, 28, 68, 42, 582, 357, 30, -1, (D_FrameCtrlDescr*)&GUID_c04f6a23_00f292, },
	// [9]ID_SCATT_DRAW_PIC
	{D_CTRL_DRAW_AREA, 8, -1, 1, 0, 255, 354, 30, -1, (D_FrameCtrlDescr*)&GUID_c0200e44_08c4ae1, },
	// [10]ID_SCATT_INFO
	{D_CTRL_DRAW_AREA, 8, 259, 1, 0, 320, 354, 30, -1, (D_FrameCtrlDescr*)&GUID_c020a629_1a515fe, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	scatter_and_demo_info_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_scatter_and_demo_info_window[11];
D_Frame scatter_and_demo_info_window = {
	run_ctrls_scatter_and_demo_info_window, 
	ctrl_description_of_scatter_and_demo_info_window, 
	scatter_and_demo_info_window_init, 
};

