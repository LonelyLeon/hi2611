/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2015-07-10 09:48:13

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
#define	ID_CARRIER_FREQ_LSIT_TITLE	1
#define	ID_CARRIER_FREQ_DRAW_BACK	2
#define	ID_CARRIER_FREQ_INFO	3
#define	ID_CARRIER_FREQ_BUTTON_EXIT	4
#define	ID_CARRIER_FREQ_LABLE_EXIT	5
#define	ID_CARRIER_FREQ_L	6
#define	ID_CARRIER_FREQ_R	7
#define	ID_CARRIER_FREQ_OTHER_INFO_LABEL	8

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0bc240e_04ef33={atv_COLOR_ENUM_65, -1, atv_IDS_CARRIER_FREQ, &atv_fmt_left_middle_h15_v15_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0bc26f7_2514e3f={atv_COLOR_ENUM_13, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0bc29a2_1674e56={-1, atv_IMG_ID_hint_button, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0bc2a57_2eef6b={-1, -1, atv_IDS_BACK, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0bc2acf_1571b31={-1, atv_IMG_ID_program_info_direction_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0bc2b4c_15748d5={-1, atv_IMG_ID_program_info_direction_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0bc2c41_2716a37={-1, -1, atv_IDS_DEM_OTHER_INFO, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0bc23de_0fa29={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_CARRIER_FREQ_LSIT_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0bc240e_04e5fd4={{&GUID_c0bc240e_04ef33, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_DRAW_AREA}	"ID_CARRIER_FREQ_DRAW_BACK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0bc26f7_2514705={{&GUID_c0bc26f7_2514e3f, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_CARRIER_FREQ_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0bc2921_03e47ab={{&GUID_c0bc26f7_2514e3f, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_CARRIER_FREQ_BUTTON_EXIT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0bc29a2_16732ce={{&GUID_c0bc29a2_1674e56, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_CARRIER_FREQ_LABLE_EXIT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0bc2a57_2ee291b={{&GUID_c0bc2a57_2eef6b, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_CARRIER_FREQ_L"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0bc2acf_1573a7c={{&GUID_c0bc2acf_1571b31, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_CARRIER_FREQ_R"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0bc2b4c_157d3d={{&GUID_c0bc2b4c_15748d5, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_CARRIER_FREQ_OTHER_INFO_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0bc2c41_2716e={{&GUID_c0bc2c41_2716a37, NULL, NULL, }, 0, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_channel_carrier_freq_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 325, 102, 0, 644, 516, 0, -1, (D_FrameCtrlDescr*)&GUID_c0bc23de_0fa29, },
	// [1]ID_CARRIER_FREQ_LSIT_TITLE
	{D_CTRL_LABEL, 0, 0, 0, 122, 624, 68, 30, -1, (D_FrameCtrlDescr*)&GUID_c0bc240e_04e5fd4, },
	// [2]ID_CARRIER_FREQ_DRAW_BACK
	{D_CTRL_DRAW_AREA, 0, 27, 67, 90, 596, 359, 30, -1, (D_FrameCtrlDescr*)&GUID_c0bc26f7_2514705, },
	// [3]ID_CARRIER_FREQ_INFO
	{D_CTRL_LABEL, 0, 27, 425, 122, 596, 68, 30, -1, (D_FrameCtrlDescr*)&GUID_c0bc2921_03e47ab, },
	// [4]ID_CARRIER_FREQ_BUTTON_EXIT
	{D_CTRL_LABEL, 3, 62, 16, 23, 100, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_c0bc29a2_16732ce, },
	// [5]ID_CARRIER_FREQ_LABLE_EXIT
	{D_CTRL_LABEL, 3, 174, 16, 23, 62, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_c0bc2a57_2ee291b, },
	// [6]ID_CARRIER_FREQ_L
	{D_CTRL_LABEL, 3, 333, 16, 123, 20, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_c0bc2acf_1573a7c, },
	// [7]ID_CARRIER_FREQ_R
	{D_CTRL_LABEL, 3, 368, 16, 123, 20, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_c0bc2b4c_157d3d, },
	// [8]ID_CARRIER_FREQ_OTHER_INFO_LABEL
	{D_CTRL_LABEL, 3, 412, 16, 123, 112, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_c0bc2c41_2716e, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	channel_carrier_freq_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_channel_carrier_freq_window[9];
D_Frame channel_carrier_freq_window = {
	run_ctrls_channel_carrier_freq_window, 
	ctrl_description_of_channel_carrier_freq_window, 
	channel_carrier_freq_window_init, 
};

