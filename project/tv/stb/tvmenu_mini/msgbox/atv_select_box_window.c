/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2017-07-27 11:38:04

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-07-18 16:19:49.390

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
#define	ID_MSG_LABEL	1
#define	ID_BUTTON_0	2
#define	ID_BUTTON_1	3

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a11d1_3d84823={-1, atv_IMG_ID_FS_WHITE_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a11de_00f7ae0={-1, -1, atv_IDS_NULL, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a2421_05d3a4a={-1, atv_IMG_ID_FS_BUTTON_GRAY, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a2421_05d1947={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a2539_1385c69={-1, atv_IMG_ID_FS_BUTTON_GRAY, atv_IDS_CANCEL, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a2539_1386f2b={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, atv_IDS_CANCEL, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a11d1_3d829={{&GUID_c56a11d1_3d84823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_MSG_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a11de_00f672f={{&GUID_c56a11de_00f7ae0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_BUTTON_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a2421_05d4a44={{&GUID_c56a2421_05d3a4a, &GUID_c56a2421_05d1947, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a2539_138f8f={{&GUID_c56a2539_1385c69, &GUID_c56a2539_1386f2b, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_select_box_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 350, 218, 0, 260, 140, 0, -1, (D_FrameCtrlDescr*)&GUID_c56a11d1_3d829, },
	// [1]ID_MSG_LABEL
	{D_CTRL_LABEL, 0, 11, 5, -180, 239, 91, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a11de_00f672f, },
	// [2]ID_BUTTON_0
	{D_CTRL_BUTTON, 0, 28, 104, -180, 72, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a2421_05d4a44, },
	// [3]ID_BUTTON_1
	{D_CTRL_BUTTON, 0, 160, 104, -180, 72, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a2539_138f8f, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_select_box_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_select_box_window[4];
D_Frame atv_select_box_window = {
	run_ctrls_atv_select_box_window, 
	ctrl_description_of_atv_select_box_window, 
	atv_select_box_window_init, 
};

