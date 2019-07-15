/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2015-05-16 14:36:33

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
#define	ID_MDEIA_ZOOM_GROUP_BG	1
#define	ID_MDEIA_ZOOM_BUTTON_FULL_SCREEN	2
#define	ID_MDEIA_ZOOM_BUTTON_AUTO	3
#define	ID_MDEIA_ZOOM_IMAGE_LEFT_ARROW	4
#define	ID_MDEIA_ZOOM_IMAGE_RIGHT_ARROW	5

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d76b9_0da4cad={-1, atv_IMG_ID_focus_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40e54fa_3b929={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_FULL_SCREEN, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40e54fa_3b94823={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_FULL_SCREEN, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4adae22_0ea72ae={-1, atv_IMG_ID_left_arrow_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4adb03c_1b51eb={-1, atv_IMG_ID_right_arrow_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b05177_18629={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_SEARCH_AUTO, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b05516_23243a4={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_SEARCH_AUTO, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a2a52_06d29={-1, atv_IMG_ID_COMB_menu_button_normal_disable, atv_IDS_FULL_SCREEN, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a2a7c_1d44823={-1, atv_IMG_ID_COMB_menu_button_normal_disable, atv_IDS_SEARCH_AUTO, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_MDEIA_ZOOM_GROUP_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{&GUID_c40d76b9_0da4cad, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_MDEIA_ZOOM_BUTTON_FULL_SCREEN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0eb3_0fa23e1={{&GUID_c40e54fa_3b929, &GUID_c40e54fa_3b94823, &GUID_c20a2a52_06d29, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_MDEIA_ZOOM_BUTTON_AUTO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0f7c_1485bb2={{&GUID_c4b05177_18629, &GUID_c4b05516_23243a4, &GUID_c20a2a7c_1d44823, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_IMAGE}	"ID_MDEIA_ZOOM_IMAGE_LEFT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4adae22_0ea2cd6={{&GUID_c4adae22_0ea72ae, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_IMAGE}	"ID_MDEIA_ZOOM_IMAGE_RIGHT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4adb03c_1b526e9={{&GUID_c4adb03c_1b51eb, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_media_zoom_mode_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 176, 460, 0, 960, 58, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_MDEIA_ZOOM_GROUP_BG
	{D_CTRL_GROUP, 0, -1, 0, 20, 960, 58, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_MDEIA_ZOOM_BUTTON_FULL_SCREEN
	{D_CTRL_BUTTON, 1, 239, 13, 0, 120, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0eb3_0fa23e1, },
	// [3]ID_MDEIA_ZOOM_BUTTON_AUTO
	{D_CTRL_BUTTON, 1, 594, 13, 0, 120, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0f7c_1485bb2, },
	// [4]ID_MDEIA_ZOOM_IMAGE_LEFT_ARROW
	{D_CTRL_IMAGE, 1, 48, 6, 0, 26, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c4adae22_0ea2cd6, },
	// [5]ID_MDEIA_ZOOM_IMAGE_RIGHT_ARROW
	{D_CTRL_IMAGE, 1, 882, 6, 0, 26, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c4adb03c_1b526e9, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_media_zoom_mode_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_media_zoom_mode_window[6];
D_Frame atv_media_zoom_mode_window = {
	run_ctrls_atv_media_zoom_mode_window, 
	ctrl_description_of_atv_media_zoom_mode_window, 
	atv_media_zoom_mode_window_init, 
};

