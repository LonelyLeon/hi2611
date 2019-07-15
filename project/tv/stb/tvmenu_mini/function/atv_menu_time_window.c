/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-05-08 17:47:32

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2019-02-14 16:39:05.650

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
#define	ID_MENUTIME_GROUP_BG	1
#define	ID_MENUTIME_BUTTON_1	2
#define	ID_MENUTIME_BUTTON_2	3
#define	ID_MENUTIME_BUTTON_3	4
#define	ID_MENUTIME_IMAGE_LEFT_ARROW	5
#define	ID_MENUTIME_IMAGE_RIGHT_ARROW	6

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40dbf7d_0da506={-1, atv_IMG_ID_FS_OK_BUTTON_NORMAL, atv_IDS_5_S, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40dbf7d_0da3608={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, atv_IDS_5_S, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae0f8e_34bb94={-1, atv_IMG_ID_sub_menu_direc_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae1023_25158e2={-1, atv_IMG_ID_sub_menu_direc_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b2a51f_0da29={-1, atv_IMG_ID_FS_OK_BUTTON_NORMAL, atv_IDS_10_S, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b2a51f_0da4823={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, atv_IDS_10_S, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b2a51f_0da18be={-1, atv_IMG_ID_FS_OK_BUTTON_NORMAL, atv_IDS_15_S, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b2a51f_0da6784={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, atv_IDS_15_S, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a36f2_2806cfc={-1, atv_IMG_ID_FS_OK_BUTTON_DISABLE, atv_IDS_5_S, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a3704_0ab53d={-1, atv_IMG_ID_FS_OK_BUTTON_DISABLE, atv_IDS_10_S, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a3748_1d4144b={-1, atv_IMG_ID_FS_OK_BUTTON_DISABLE, atv_IDS_15_S, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c9faa950_11c606d={-1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{&GUID_c9faa950_11c606d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_MENUTIME_GROUP_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_MENUTIME_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40dbf7d_0da275f={{&GUID_c40dbf7d_0da506, &GUID_c40dbf7d_0da3608, &GUID_c20a36f2_2806cfc, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_MENUTIME_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0eb3_0fa23e1={{&GUID_c4b2a51f_0da29, &GUID_c4b2a51f_0da4823, &GUID_c20a3704_0ab53d, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_MENUTIME_BUTTON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0f7c_1485bb2={{&GUID_c4b2a51f_0da18be, &GUID_c4b2a51f_0da6784, &GUID_c20a3748_1d4144b, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_IMAGE}	"ID_MENUTIME_IMAGE_LEFT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ae0f8e_34b3e9b={{&GUID_c4ae0f8e_34bb94, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_IMAGE}	"ID_MENUTIME_IMAGE_RIGHT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ae1023_2513423={{&GUID_c4ae1023_25158e2, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_menu_time_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 25, 445, 0, 900, 55, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_MENUTIME_GROUP_BG
	{D_CTRL_GROUP, 0, 0, 0, -41, 900, 55, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_MENUTIME_BUTTON_1
	{D_CTRL_BUTTON, 1, 141, 15, 0, 200, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c40dbf7d_0da275f, },
	// [3]ID_MENUTIME_BUTTON_2
	{D_CTRL_BUTTON, 1, 395, 15, 0, 200, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0eb3_0fa23e1, },
	// [4]ID_MENUTIME_BUTTON_3
	{D_CTRL_BUTTON, 1, 646, 15, 0, 200, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0f7c_1485bb2, },
	// [5]ID_MENUTIME_IMAGE_LEFT_ARROW
	{D_CTRL_IMAGE, 1, 117, 18, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ae0f8e_34b3e9b, },
	// [6]ID_MENUTIME_IMAGE_RIGHT_ARROW
	{D_CTRL_IMAGE, 1, 860, 18, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ae1023_2513423, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_menu_time_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_menu_time_window[7];
D_Frame atv_menu_time_window = {
	run_ctrls_atv_menu_time_window, 
	ctrl_description_of_atv_menu_time_window, 
	atv_menu_time_window_init, 
};

