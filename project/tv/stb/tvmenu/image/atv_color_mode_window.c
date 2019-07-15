/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2015-05-16 14:25:17

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2014-12-15 18:43:38.888

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
#define	ID_COLORMODE_GROUP_BACKGROUND	1
#define	ID_COLORMODE_BUTTON_WARM	2
#define	ID_COLORMODE_BUTTON_STANDARD	3
#define	ID_COLORMODE_BUTTON_COOL	4
#define	ID_COLORMODE_IMAGE_LEFT_ARROW	5
#define	ID_COLORMODE_IMAGE_RIGHT_ARROW	6

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d76b9_0da4cad={-1, atv_IMG_ID_focus_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40dbf7d_0da506={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_WARM, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40dbf7d_0da3608={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_WARM, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a7bbd0_2427238={-1, atv_IMG_ID_left_arrow_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a7bc52_16748df={-1, atv_IMG_ID_right_arrow_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae5be9_10929={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_STANDARD, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae5be9_10918be={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_COOL, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae738b_08c29={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_STANDARD, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae738b_08c4823={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_COOL, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a2c0b_29029={-1, atv_IMG_ID_COMB_menu_button_normal_disable, atv_IDS_WARM, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a2c61_2bf4823={-1, atv_IMG_ID_COMB_menu_button_normal_disable, atv_IDS_STANDARD, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a2cb3_10918be={-1, atv_IMG_ID_COMB_menu_button_normal_disable, atv_IDS_COOL, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_COLORMODE_GROUP_BACKGROUND"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{&GUID_c40d76b9_0da4cad, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_COLORMODE_BUTTON_WARM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40dbf7d_0da275f={{&GUID_c40dbf7d_0da506, &GUID_c40dbf7d_0da3608, &GUID_c20a2c0b_29029, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_COLORMODE_BUTTON_STANDARD"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0eb3_0fa23e1={{&GUID_c4ae5be9_10929, &GUID_c4ae738b_08c29, &GUID_c20a2c61_2bf4823, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_COLORMODE_BUTTON_COOL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0f7c_1485bb2={{&GUID_c4ae5be9_10918be, &GUID_c4ae738b_08c4823, &GUID_c20a2cb3_10918be, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_IMAGE}	"ID_COLORMODE_IMAGE_LEFT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a7bbd0_24244eb={{&GUID_c4a7bbd0_2427238, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_IMAGE}	"ID_COLORMODE_IMAGE_RIGHT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a7bc52_1676473={{&GUID_c4a7bc52_16748df, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_color_mode_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 176, 460, 0, 960, 58, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_COLORMODE_GROUP_BACKGROUND
	{D_CTRL_GROUP, 0, -1, 0, 20, 960, 58, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_COLORMODE_BUTTON_WARM
	{D_CTRL_BUTTON, 1, 200, 13, 0, 120, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40dbf7d_0da275f, },
	// [3]ID_COLORMODE_BUTTON_STANDARD
	{D_CTRL_BUTTON, 1, 412, 13, 0, 120, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0eb3_0fa23e1, },
	// [4]ID_COLORMODE_BUTTON_COOL
	{D_CTRL_BUTTON, 1, 624, 13, 0, 120, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0f7c_1485bb2, },
	// [5]ID_COLORMODE_IMAGE_LEFT_ARROW
	{D_CTRL_IMAGE, 1, 48, 6, 0, 26, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a7bbd0_24244eb, },
	// [6]ID_COLORMODE_IMAGE_RIGHT_ARROW
	{D_CTRL_IMAGE, 1, 882, 6, 0, 26, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a7bc52_1676473, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_color_mode_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_color_mode_window[7];
D_Frame atv_color_mode_window = {
	run_ctrls_atv_color_mode_window, 
	ctrl_description_of_atv_color_mode_window, 
	atv_color_mode_window_init, 
};

