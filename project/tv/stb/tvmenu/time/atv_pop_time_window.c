/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2014-11-17 10:46:37

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2014-11-11 13:50:18.265

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
#define	ID_POPTIME_GROUP_BG	1
#define	ID_POPTIME_INPUT_HOUR	2
#define	ID_POPTIME_LABLE_DIAN	3
#define	ID_POPTIME_INPUT_MINUTE	4

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c49fb278_11939bf={atv_COLOR_ENUM_84, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c49fb715_03e949={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4af8aa0_1484823={atv_COLOR_ENUM_106, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b22413_38a3906={-1, atv_IMG_ID_FS_pop_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bb98bb_2515854={-1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{&GUID_c4bb98bb_2515854, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_POPTIME_GROUP_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{&GUID_c4b22413_38a3906, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_INPUT}	"ID_POPTIME_INPUT_HOUR"
static char GUID_c49fb278_1195bb9[3+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_c49fb278_1195f0c={{&GUID_c49fb278_11939bf, &GUID_c4af8aa0_1484823, NULL, }, 1, 0, 3, GUID_c49fb278_1195bb9, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_POPTIME_LABLE_DIAN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c49fb715_03e3cc7={{&GUID_c49fb715_03e949, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_INPUT}	"ID_POPTIME_INPUT_MINUTE"
static char GUID_c49fb80d_38a15fc[2+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_c49fb80d_38a6176={{&GUID_c49fb278_11939bf, &GUID_c4af8aa0_1484823, NULL, }, 1, 0, 2, GUID_c49fb80d_38a15fc, 1, '-', '*', };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_pop_time_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 450, 500, 0, 323, 150, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_POPTIME_GROUP_BG
	{D_CTRL_GROUP, 0, 0, 0, 123, 323, 150, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_POPTIME_INPUT_HOUR
	{D_CTRL_INPUT, 1, 109, 51, -14, 36, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c49fb278_1195f0c, },
	// [3]ID_POPTIME_LABLE_DIAN
	{D_CTRL_LABEL, 1, 148, 51, -14, 26, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c49fb715_03e3cc7, },
	// [4]ID_POPTIME_INPUT_MINUTE
	{D_CTRL_INPUT, 1, 177, 51, -14, 36, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c49fb80d_38a6176, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_pop_time_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_pop_time_window[5];
D_Frame atv_pop_time_window = {
	run_ctrls_atv_pop_time_window, 
	ctrl_description_of_atv_pop_time_window, 
	atv_pop_time_window_init, 
};

