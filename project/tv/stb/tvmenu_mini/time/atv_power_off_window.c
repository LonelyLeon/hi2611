/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-05-10 16:07:50

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
#define	ID_POWEROFF_GROUP_BG	1
#define	ID_POWEROFF_BUTTON_SET	2
#define	ID_POWEROFF_LABLE_SHOWHOUR	3
#define	ID_POWEROFF_LABLE_SHOWDIAN	4
#define	ID_POWEROFF_LABLE_SHOWMINUTE	5
#define	ID_POWEROFF_LABLE_SWITCH	6

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4105d27_213c4d={-1, atv_IMG_ID_FS_OK_BUTTON_NORMAL, atv_IDS_ADJUST, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4105d27_21379dd={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, atv_IDS_ADJUST, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c49f9977_2904823={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c59c3798_04e372a={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08e322d_39914={-1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{&GUID_c08e322d_39914, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_POWEROFF_GROUP_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_POWEROFF_BUTTON_SET"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0eb3_0fa23e1={{&GUID_c4105d27_213c4d, &GUID_c4105d27_21379dd, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_POWEROFF_LABLE_SHOWHOUR"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c49f9977_29029={{&GUID_c49f9977_2904823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_POWEROFF_LABLE_SHOWDIAN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c59c3798_04e2dba={{&GUID_c59c3798_04e372a, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_POWEROFF_LABLE_SHOWMINUTE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c59c37bb_2904ad6={{&GUID_c59c3798_04e372a, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_POWEROFF_LABLE_SWITCH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a011ca_04e39a8={{&GUID_c49f9977_2904823, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_power_off_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 25, 445, 0, 900, 55, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_POWEROFF_GROUP_BG
	{D_CTRL_GROUP, 0, 0, 0, -41, 900, 55, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_POWEROFF_BUTTON_SET
	{D_CTRL_BUTTON, 1, 450, 15, 0, 120, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0eb3_0fa23e1, },
	// [3]ID_POWEROFF_LABLE_SHOWHOUR
	{D_CTRL_LABEL, 1, 172, 15, 0, 40, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c49f9977_29029, },
	// [4]ID_POWEROFF_LABLE_SHOWDIAN
	{D_CTRL_LABEL, 1, 213, 15, 0, 19, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c59c3798_04e2dba, },
	// [5]ID_POWEROFF_LABLE_SHOWMINUTE
	{D_CTRL_LABEL, 1, 235, 15, 0, 40, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c59c37bb_2904ad6, },
	// [6]ID_POWEROFF_LABLE_SWITCH
	{D_CTRL_LABEL, 1, 338, 15, 0, 35, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a011ca_04e39a8, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_power_off_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_power_off_window[7];
D_Frame atv_power_off_window = {
	run_ctrls_atv_power_off_window, 
	ctrl_description_of_atv_power_off_window, 
	atv_power_off_window_init, 
};

