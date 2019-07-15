/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2015-03-26 14:38:23

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
#define	ID_ORDER_GROUP_BG	1
#define	ID_ORDER_BUTTON_SET	2
#define	ID_ORDER_LABLE_SHOWHOUR	3
#define	ID_ORDER_LABLE_SHOWDIAN	4
#define	ID_ORDER_LABLE_SHOWMINUTE	5
#define	ID_ORDER_LABLE_SWITCH	6

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d76b9_0da4cad={-1, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4105d27_213c4d={-1, atv_IMG_ID_FS_OK_BUTTON_NORMAL, atv_IDS_ADJUST, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4105d27_21379dd={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, atv_IDS_ADJUST, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c49f9977_2904823={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c59c5487_0bb537={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08e31cd_0da76f9={-1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{&GUID_c08e31cd_0da76f9, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_ORDER_GROUP_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{&GUID_c40d76b9_0da4cad, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_ORDER_BUTTON_SET"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0eb3_0fa23e1={{&GUID_c4105d27_213c4d, &GUID_c4105d27_21379dd, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_ORDER_LABLE_SHOWHOUR"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c49f9977_29029={{&GUID_c49f9977_2904823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_ORDER_LABLE_SHOWDIAN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c59c5487_0bb6af0={{&GUID_c59c5487_0bb537, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_ORDER_LABLE_SHOWMINUTE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c59c54a1_2514586={{&GUID_c59c5487_0bb537, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_ORDER_LABLE_SWITCH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a011ca_04e39a8={{&GUID_c49f9977_2904823, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_order_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 25, 486, 0, 672, 55, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_ORDER_GROUP_BG
	{D_CTRL_GROUP, 0, 0, 0, 0, 672, 55, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_ORDER_BUTTON_SET
	{D_CTRL_BUTTON, 1, 450, 15, 0, 120, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0eb3_0fa23e1, },
	// [3]ID_ORDER_LABLE_SHOWHOUR
	{D_CTRL_LABEL, 1, 172, 15, 0, 40, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c49f9977_29029, },
	// [4]ID_ORDER_LABLE_SHOWDIAN
	{D_CTRL_LABEL, 1, 213, 15, 0, 19, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c59c5487_0bb6af0, },
	// [5]ID_ORDER_LABLE_SHOWMINUTE
	{D_CTRL_LABEL, 1, 235, 15, 0, 40, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c59c54a1_2514586, },
	// [6]ID_ORDER_LABLE_SWITCH
	{D_CTRL_LABEL, 1, 338, 15, 0, 35, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a011ca_04e39a8, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_order_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_order_window[7];
D_Frame atv_order_window = {
	run_ctrls_atv_order_window, 
	ctrl_description_of_atv_order_window, 
	atv_order_window_init, 
};

