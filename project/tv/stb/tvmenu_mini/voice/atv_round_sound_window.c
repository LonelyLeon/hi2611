/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-05-08 17:35:12

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
#define	ID_ROUND_GROUP_BG	1
#define	ID_ROUND_BUTTON_ON	2
#define	ID_ROUND_BUTTON_OFF	3
#define	ID_ROUND_IMAGE_LEFT_ARROW	4
#define	ID_ROUND_IMAGE_RIGHT_ARROW	5

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40e54fa_3b929={-1, atv_IMG_ID_FS_OK_BUTTON_NORMAL, atv_IDS_ON, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40e54fa_3b94823={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, atv_IDS_ON, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4adae22_0ea72ae={-1, atv_IMG_ID_sub_menu_direc_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4adb03c_1b51eb={-1, atv_IMG_ID_sub_menu_direc_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b05177_18629={-1, atv_IMG_ID_FS_OK_BUTTON_NORMAL, atv_IDS_OFF, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b05516_23243a4={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, atv_IDS_OFF, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a353c_251475a={-1, atv_IMG_ID_FS_OK_BUTTON_DISABLE, atv_IDS_ON, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a355c_2ce7781={-1, atv_IMG_ID_FS_OK_BUTTON_DISABLE, atv_IDS_OFF, &atv_fmt_center_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_ROUND_GROUP_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_ROUND_BUTTON_ON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0eb3_0fa23e1={{&GUID_c40e54fa_3b929, &GUID_c40e54fa_3b94823, &GUID_c20a353c_251475a, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_ROUND_BUTTON_OFF"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0f7c_1485bb2={{&GUID_c4b05177_18629, &GUID_c4b05516_23243a4, &GUID_c20a355c_2ce7781, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_IMAGE}	"ID_ROUND_IMAGE_LEFT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4adae22_0ea2cd6={{&GUID_c4adae22_0ea72ae, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_IMAGE}	"ID_ROUND_IMAGE_RIGHT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4adb03c_1b526e9={{&GUID_c4adb03c_1b51eb, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_round_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 25, 445, 0, 900, 55, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_ROUND_GROUP_BG
	{D_CTRL_GROUP, 0, 0, 0, -41, 900, 55, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_ROUND_BUTTON_ON
	{D_CTRL_BUTTON, 1, 229, 15, 0, 230, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0eb3_0fa23e1, },
	// [3]ID_ROUND_BUTTON_OFF
	{D_CTRL_BUTTON, 1, 533, 15, 0, 230, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0f7c_1485bb2, },
	// [4]ID_ROUND_IMAGE_LEFT_ARROW
	{D_CTRL_IMAGE, 1, 117, 18, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4adae22_0ea2cd6, },
	// [5]ID_ROUND_IMAGE_RIGHT_ARROW
	{D_CTRL_IMAGE, 1, 860, 18, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4adb03c_1b526e9, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_round_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_round_window[6];
D_Frame atv_round_window = {
	run_ctrls_atv_round_window, 
	ctrl_description_of_atv_round_window, 
	atv_round_window_init, 
};

