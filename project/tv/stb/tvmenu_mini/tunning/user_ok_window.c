/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2017-07-25 10:03:57

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
#define	ID_USER_OK_GROUP	1
#define	ID_USER_OK_BUTTON	2

//////////////////////////////////////////////////////////////////////////
// attributes

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4105d27_213c4d={-1, atv_IMG_ID_FS_OK_BUTTON_NORMAL, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4105d27_21379dd={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08e35b4_3993905={-1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7ab76b6_29f29={{&GUID_c08e35b4_3993905, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_USER_OK_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7ab86d8_23229={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_USER_OK_BUTTON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7ab8779_2bf4ae1={{&GUID_c4105d27_213c4d, &GUID_c4105d27_21379dd, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_user_ok_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 25, 486, 0, 672, 55, 0, -1, (D_FrameCtrlDescr*)&GUID_c7ab76b6_29f29, },
	// [1]ID_USER_OK_GROUP
	{D_CTRL_GROUP, 0, 0, 0, 20, 672, 55, 30, -1, (D_FrameCtrlDescr*)&GUID_c7ab86d8_23229, },
	// [2]ID_USER_OK_BUTTON
	{D_CTRL_BUTTON, 1, 286, 15, 0, 100, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c7ab8779_2bf4ae1, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	user_ok_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_user_ok_window[3];
D_Frame user_ok_window = {
	run_ctrls_user_ok_window, 
	ctrl_description_of_user_ok_window, 
	user_ok_window_init, 
};

