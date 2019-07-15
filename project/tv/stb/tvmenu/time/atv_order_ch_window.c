/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2015-03-26 14:37:43

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
#define	ID_ORDERCH_GROUP_BG	1
#define	ID_ORDERCH_IMAGE_LEFT	2
#define	ID_ORDERCH_BUTTON_CH	3
#define	ID_ORDERCH_IMAGE_RIGHT	4

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d76b9_0da4cad={-1, atv_IMG_ID_focus_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae54e7_1095a9d={-1, atv_IMG_ID_COMB_button_menu, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae54e7_109538f={-1, atv_IMG_ID_COMB_button_menu_focus, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae55b7_1b54b44={-1, atv_IMG_ID_left_arrow_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae567f_38a7dd8={-1, atv_IMG_ID_right_arrow_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08e317d_27155d2={-1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{&GUID_c08e317d_27155d2, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_ORDERCH_GROUP_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{&GUID_c40d76b9_0da4cad, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_IMAGE}	"ID_ORDERCH_IMAGE_LEFT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ae55b7_1b568a2={{&GUID_c4ae55b7_1b54b44, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_ORDERCH_BUTTON_CH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ae54e7_1091d43={{&GUID_c4ae54e7_1095a9d, &GUID_c4ae54e7_109538f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_IMAGE}	"ID_ORDERCH_IMAGE_RIGHT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ae567f_38a7ab5={{&GUID_c4ae567f_38a7dd8, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_order_ch_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 176, 460, 0, 960, 58, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_ORDERCH_GROUP_BG
	{D_CTRL_GROUP, 0, -1, 0, 20, 960, 58, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_ORDERCH_IMAGE_LEFT
	{D_CTRL_IMAGE, 1, 48, 6, 0, 26, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ae55b7_1b568a2, },
	// [3]ID_ORDERCH_BUTTON_CH
	{D_CTRL_BUTTON, 1, 416, 14, 0, 126, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ae54e7_1091d43, },
	// [4]ID_ORDERCH_IMAGE_RIGHT
	{D_CTRL_IMAGE, 1, 882, 6, 0, 26, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ae567f_38a7ab5, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_order_ch_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_order_ch_window[5];
D_Frame atv_order_ch_window = {
	run_ctrls_atv_order_ch_window, 
	ctrl_description_of_atv_order_ch_window, 
	atv_order_ch_window_init, 
};

