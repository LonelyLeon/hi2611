/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2015-05-16 14:33:20

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
#define	ID_ZOOMMODE_GROUP_BACKGROUND	1
#define	ID_ZOOMMODE_BUTTON_FULLSCR	2
#define	ID_ZOOMMODE_BUTTON_43	3
#define	ID_ZOOMMODE_BUTTON_AMPLIFY	4
#define	ID_ZOOMMODE_BUTTON_FULLTRUE	5
#define	ID_ZOOMMODE_IMAGE_LEFT_ARROW	6
#define	ID_ZOOMMODE_IMAGE_RIGHT_ARROW	7

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d76b9_0da4cad={-1, atv_IMG_ID_focus_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40dbf7d_0da506={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_FULL_SCREEN, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40dbf7d_0da3608={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_FULL_SCREEN, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a76aff_30d72ae={-1, atv_IMG_ID_left_arrow_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a76c40_3c8a27={-1, atv_IMG_ID_right_arrow_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae5cb7_1b56938={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_4TO3, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae5cb7_1b52125={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_ZOOM, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae5cb7_1b57f58={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_PTP, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae748d_0bb7817={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_4TO3, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae748d_0bb26fc={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_ZOOM, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae748d_0bb76dc={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_PTP, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a2f22_03e29={-1, atv_IMG_ID_COMB_menu_button_normal_disable, atv_IDS_FULL_SCREEN, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a2f61_2034823={-1, atv_IMG_ID_COMB_menu_button_normal_disable, atv_IDS_4TO3, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a2f7e_1c518be={-1, atv_IMG_ID_COMB_menu_button_normal_disable, atv_IDS_ZOOM, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a2fd3_1a56784={-1, atv_IMG_ID_COMB_menu_button_normal_disable, atv_IDS_PTP, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_ZOOMMODE_GROUP_BACKGROUND"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{&GUID_c40d76b9_0da4cad, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_ZOOMMODE_BUTTON_FULLSCR"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40dbf7d_0da275f={{&GUID_c40dbf7d_0da506, &GUID_c40dbf7d_0da3608, &GUID_c20a2f22_03e29, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_ZOOMMODE_BUTTON_43"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0eb3_0fa23e1={{&GUID_c4ae5cb7_1b56938, &GUID_c4ae748d_0bb7817, &GUID_c20a2f61_2034823, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_ZOOMMODE_BUTTON_AMPLIFY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0f7c_1485bb2={{&GUID_c4ae5cb7_1b52125, &GUID_c4ae748d_0bb26fc, &GUID_c20a2f7e_1c518be, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_ZOOMMODE_BUTTON_FULLTRUE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0fe7_222289d={{&GUID_c4ae5cb7_1b57f58, &GUID_c4ae748d_0bb76dc, &GUID_c20a2fd3_1a56784, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_IMAGE}	"ID_ZOOMMODE_IMAGE_LEFT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a76aff_30d2cd6={{&GUID_c4a76aff_30d72ae, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_IMAGE}	"ID_ZOOMMODE_IMAGE_RIGHT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a76c40_3c85f6c={{&GUID_c4a76c40_3c8a27, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_zoom_mode_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 176, 460, 0, 960, 58, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_ZOOMMODE_GROUP_BACKGROUND
	{D_CTRL_GROUP, 0, -1, 0, 20, 960, 58, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_ZOOMMODE_BUTTON_FULLSCR
	{D_CTRL_BUTTON, 1, 133, 13, 0, 120, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40dbf7d_0da275f, },
	// [3]ID_ZOOMMODE_BUTTON_43
	{D_CTRL_BUTTON, 1, 325, 13, 0, 120, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0eb3_0fa23e1, },
	// [4]ID_ZOOMMODE_BUTTON_AMPLIFY
	{D_CTRL_BUTTON, 1, 517, 13, 0, 120, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0f7c_1485bb2, },
	// [5]ID_ZOOMMODE_BUTTON_FULLTRUE
	{D_CTRL_BUTTON, 1, 709, 13, 0, 120, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0fe7_222289d, },
	// [6]ID_ZOOMMODE_IMAGE_LEFT_ARROW
	{D_CTRL_IMAGE, 1, 48, 6, 0, 26, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a76aff_30d2cd6, },
	// [7]ID_ZOOMMODE_IMAGE_RIGHT_ARROW
	{D_CTRL_IMAGE, 1, 882, 6, 0, 26, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a76c40_3c85f6c, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_zoom_mode_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_zoom_mode_window[8];
D_Frame atv_zoom_mode_window = {
	run_ctrls_atv_zoom_mode_window, 
	ctrl_description_of_atv_zoom_mode_window, 
	atv_zoom_mode_window_init, 
};

