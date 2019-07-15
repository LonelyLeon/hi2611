/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2015-07-10 09:49:08

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
#define	ID_IMPULSE_PROGRAM_LSIT_TITLE	1
#define	ID_IMPULSE_INFO	2
#define	ID_IMPULSE_L	3
#define	ID_IMPULSE_R	4
#define	ID_IMPULSE_OTHER_INFO_LABEL	5
#define	ID_IMPULSE_BUTTON_EXIT	6
#define	ID_IMPULSE_LABLE_EXIT	7
#define	ID_IMPULSE_DRAW_BACK	8

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130621092016_125451={atv_COLOR_ENUM_65, -1, atv_IDS_DEM_HN, &atv_fmt_left_middle_h15_v15_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130621134659_303351={atv_COLOR_ENUM_0, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130625175946_89421={atv_COLOR_ENUM_13, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130626104011_223061={-1, atv_IMG_ID_program_info_direction_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130626104203_130751={-1, atv_IMG_ID_program_info_direction_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130626142215_273021={-1, -1, atv_IDS_DEM_OTHER_INFO, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c04ea57b_119439a1={-1, atv_IMG_ID_hint_button, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c04ea686_1d44201={-1, -1, atv_IDS_BACK, &atv_fmt_left_middle_h05_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c04f6a23_00f48231={atv_COLOR_ENUM_13, -1, atv_IDS_NULL, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130620084411_411={{NULL, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_IMPULSE_PROGRAM_LSIT_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130621092016_42841={{&PRSUNZY_sunzy_20130621092016_125451, &PRSUNZY_sunzy_20130621134659_303351, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_IMPULSE_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130625175946_128301={{&PRSUNZY_sunzy_20130625175946_89421, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_IMPULSE_L"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130626104011_11331={{&PRSUNZY_sunzy_20130626104011_223061, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_IMPULSE_R"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130626104203_268331={{&PRSUNZY_sunzy_20130626104203_130751, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_IMPULSE_OTHER_INFO_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130626142215_45451={{&PRSUNZY_sunzy_20130626142215_273021, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_IMPULSE_BUTTON_EXIT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c04ea57b_1191d3c1={{&GUID_c04ea57b_119439a1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_IMPULSE_LABLE_EXIT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c04ea686_1d4326f1={{&GUID_c04ea686_1d44201, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_DRAW_AREA}	"ID_IMPULSE_DRAW_BACK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c04f6a23_00f291={{&GUID_c04f6a23_00f48231, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_channel_impulse_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 325, 102, 0, 630, 516, 0, -1, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130620084411_411, },
	// [1]ID_IMPULSE_PROGRAM_LSIT_TITLE
	{D_CTRL_LABEL, 0, 0, 0, 122, 610, 68, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130621092016_42841, },
	// [2]ID_IMPULSE_INFO
	{D_CTRL_LABEL, 0, 27, 427, 122, 583, 68, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130625175946_128301, },
	// [3]ID_IMPULSE_L
	{D_CTRL_LABEL, 2, 320, 15, 20, 20, 35, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130626104011_11331, },
	// [4]ID_IMPULSE_R
	{D_CTRL_LABEL, 2, 362, 15, 20, 20, 35, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130626104203_268331, },
	// [5]ID_IMPULSE_OTHER_INFO_LABEL
	{D_CTRL_LABEL, 2, 400, 15, 20, 112, 35, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130626142215_45451, },
	// [6]ID_IMPULSE_BUTTON_EXIT
	{D_CTRL_LABEL, 2, 78, 15, -80, 100, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_c04ea57b_1191d3c1, },
	// [7]ID_IMPULSE_LABLE_EXIT
	{D_CTRL_LABEL, 2, 183, 15, -80, 77, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_c04ea686_1d4326f1, },
	// [8]ID_IMPULSE_DRAW_BACK
	{D_CTRL_DRAW_AREA, 0, 27, 68, 42, 583, 359, 30, -1, (D_FrameCtrlDescr*)&GUID_c04f6a23_00f291, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	channel_impulse_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_channel_impulse_window[9];
D_Frame channel_impulse_window = {
	run_ctrls_channel_impulse_window, 
	ctrl_description_of_channel_impulse_window, 
	channel_impulse_window_init, 
};

