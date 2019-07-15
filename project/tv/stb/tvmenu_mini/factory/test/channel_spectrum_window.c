/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2015-07-10 09:50:19

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
#define	ID_SPECTRUM_PROGRAM_LSIT_TITLE	1
#define	ID_SPECTRUM_INFO	2
#define	ID_SPECTRUM_L	3
#define	ID_SPECTRUM_R	4
#define	ID_SPECTRUM_OTHER_INFO_LABEL	5
#define	ID_SPECTRUM_BUTTON_EXIT	6
#define	ID_SPECTRUM_LABLE_EXIT	7
#define	ID_SPECTRUM_DRAW_BACK	8

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130621092016_12545={atv_COLOR_ENUM_65, -1, atv_IDS_DEM_SP, &atv_fmt_left_middle_h15_v15_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130621134659_30335={atv_COLOR_ENUM_0, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130625175946_8942={atv_COLOR_ENUM_13, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130626104011_22306={-1, atv_IMG_ID_sub_menu_direc_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130626104203_13075={-1, atv_IMG_ID_sub_menu_direc_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST PRSUNZY_sunzy_20130626142215_27302={-1, -1, atv_IDS_DEM_OTHER_INFO, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c04ea57b_119439a={-1, atv_IMG_ID_FS_BUTTON_GRAY, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c04ea686_1d4420={-1, -1, atv_IDS_BACK, &atv_fmt_left_middle_h05_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c04f6a23_00f4823={atv_COLOR_ENUM_13, -1, atv_IDS_NULL, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130620084411_41={{NULL, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_SPECTRUM_PROGRAM_LSIT_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130621092016_4284={{&PRSUNZY_sunzy_20130621092016_12545, &PRSUNZY_sunzy_20130621134659_30335, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_SPECTRUM_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130625175946_12830={{&PRSUNZY_sunzy_20130625175946_8942, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_SPECTRUM_L"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130626104011_1133={{&PRSUNZY_sunzy_20130626104011_22306, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_SPECTRUM_R"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130626104203_26833={{&PRSUNZY_sunzy_20130626104203_13075, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_SPECTRUM_OTHER_INFO_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST PRSUNZY_sunzy_20130626142215_4545={{&PRSUNZY_sunzy_20130626142215_27302, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_SPECTRUM_BUTTON_EXIT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c04ea57b_1191d3c={{&GUID_c04ea57b_119439a, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_SPECTRUM_LABLE_EXIT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c04ea686_1d4326f={{&GUID_c04ea686_1d4420, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_DRAW_AREA}	"ID_SPECTRUM_DRAW_BACK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c04f6a23_00f29={{&GUID_c04f6a23_00f4823, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_channel_spectrum_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 45, 30, 0, 630, 516, 0, -1, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130620084411_41, },
	// [1]ID_SPECTRUM_PROGRAM_LSIT_TITLE
	{D_CTRL_LABEL, 0, 0, 0, 122, 610, 68, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130621092016_4284, },
	// [2]ID_SPECTRUM_INFO
	{D_CTRL_LABEL, 0, 27, 427, 122, 582, 68, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130625175946_12830, },
	// [3]ID_SPECTRUM_L
	{D_CTRL_LABEL, 2, 322, 25, 20, 10, 18, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130626104011_1133, },
	// [4]ID_SPECTRUM_R
	{D_CTRL_LABEL, 2, 358, 25, 20, 10, 18, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130626104203_26833, },
	// [5]ID_SPECTRUM_OTHER_INFO_LABEL
	{D_CTRL_LABEL, 2, 385, 16, 20, 112, 37, 30, 0, (D_FrameCtrlDescr*)&PRSUNZY_sunzy_20130626142215_4545, },
	// [6]ID_SPECTRUM_BUTTON_EXIT
	{D_CTRL_LABEL, 2, 58, 16, -80, 100, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c04ea57b_1191d3c, },
	// [7]ID_SPECTRUM_LABLE_EXIT
	{D_CTRL_LABEL, 2, 162, 16, -80, 73, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c04ea686_1d4326f, },
	// [8]ID_SPECTRUM_DRAW_BACK
	{D_CTRL_DRAW_AREA, 0, 27, 68, 42, 582, 359, 30, -1, (D_FrameCtrlDescr*)&GUID_c04f6a23_00f29, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	channel_spectrum_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_channel_spectrum_window[9];
D_Frame channel_spectrum_window = {
	run_ctrls_channel_spectrum_window, 
	ctrl_description_of_channel_spectrum_window, 
	channel_spectrum_window_init, 
};

