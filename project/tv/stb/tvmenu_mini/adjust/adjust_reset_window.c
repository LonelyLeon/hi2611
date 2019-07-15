/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2015-03-26 14:29:10

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2014-12-24 14:48:49.406

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
#define	ID_RESET_GROUP_BG	1
#define	ID_RESET_BUTTON_RESET	2

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d76b9_0da4cad={-1, atv_IMG_ID_focus_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4105d27_213c4d={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4105d27_21379dd={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bbb10b_37a29={-1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{&GUID_c4bbb10b_37a29, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_RESET_GROUP_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{&GUID_c40d76b9_0da4cad, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_RESET_BUTTON_RESET"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0eb3_0fa23e1={{&GUID_c4105d27_213c4d, &GUID_c4105d27_21379dd, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_adjust_reset_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 176, 460, 0, 960, 58, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_RESET_GROUP_BG
	{D_CTRL_GROUP, 0, -1, 0, 20, 960, 58, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_RESET_BUTTON_RESET
	{D_CTRL_BUTTON, 1, 412, 13, 0, 120, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0eb3_0fa23e1, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	adjust_reset_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_adjust_reset_window[3];
D_Frame adjust_reset_window = {
	run_ctrls_adjust_reset_window, 
	ctrl_description_of_adjust_reset_window, 
	adjust_reset_window_init, 
};

