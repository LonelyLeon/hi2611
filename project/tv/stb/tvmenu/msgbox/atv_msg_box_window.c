/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2016-01-26 19:48:43

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-11-30 18:45:54.727

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
#define	ID_LABEL_TITLE	2

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a11d1_3d84823={-1, atv_IMG_ID_FS_pop_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a11de_00f7ae0={-1, -1, atv_IDS_NULL, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee2990c_06d3d6c={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a11d1_3d829={{&GUID_c56a11d1_3d84823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_MSG_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a11de_00f672f={{&GUID_c56a11de_00f7ae0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_LABEL_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee2990c_06d4ae1={{&GUID_bee2990c_06d3d6c, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_msg_box_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 440, 144, 0, 404, 208, 0, -1, (D_FrameCtrlDescr*)&GUID_c56a11d1_3d829, },
	// [1]ID_MSG_LABEL
	{D_CTRL_LABEL, 0, 50, 54, -242, 303, 135, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a11de_00f672f, },
	// [2]ID_LABEL_TITLE
	{D_CTRL_LABEL, 0, 96, 10, -242, 212, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bee2990c_06d4ae1, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_msg_box_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_msg_box_window[3];
D_Frame atv_msg_box_window = {
	run_ctrls_atv_msg_box_window, 
	ctrl_description_of_atv_msg_box_window, 
	atv_msg_box_window_init, 
};

