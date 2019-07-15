/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY_WIN7"
	update/create time:	2018-06-26 14:47:01

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-10-12 11:04:08.678

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
#define	ID_MENULANG_GROUP_BG	1
#define	ID_MENULANG_BUTTON_1	2
#define	ID_MENULANG_BUTTON_2	3
#define	ID_MENULANG_IMAGE_LEFT_ARROW	4
#define	ID_MENULANG_IMAGE_RIGHT_ARROW	5

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d76b9_0da4cad={-1, atv_IMG_ID_focus_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40dbf7d_0da506={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_ENGLISH, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40dbf7d_0da3608={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_ENGLISH, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae0f8e_34bb94={-1, atv_IMG_ID_left_arrow_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae1023_25158e2={-1, atv_IMG_ID_right_arrow_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b2a51f_0da29={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_CHINESE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b2a51f_0da4823={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_CHINESE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a36f2_2806cfc={-1, atv_IMG_ID_COMB_menu_button_normal_disable, atv_IDS_ENGLISH, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a3704_0ab53d={-1, atv_IMG_ID_COMB_menu_button_normal_disable, atv_IDS_CHINESE, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_MENULANG_GROUP_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{&GUID_c40d76b9_0da4cad, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_MENULANG_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40dbf7d_0da275f={{&GUID_c40dbf7d_0da506, &GUID_c40dbf7d_0da3608, &GUID_c20a36f2_2806cfc, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_MENULANG_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0eb3_0fa23e1={{&GUID_c4b2a51f_0da29, &GUID_c4b2a51f_0da4823, &GUID_c20a3704_0ab53d, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_IMAGE}	"ID_MENULANG_IMAGE_LEFT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ae0f8e_34b3e9b={{&GUID_c4ae0f8e_34bb94, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_IMAGE}	"ID_MENULANG_IMAGE_RIGHT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ae1023_2513423={{&GUID_c4ae1023_25158e2, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_menu_lang_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 176, 460, 0, 960, 58, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_MENULANG_GROUP_BG
	{D_CTRL_GROUP, 0, -1, 0, 20, 960, 58, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_MENULANG_BUTTON_1
	{D_CTRL_BUTTON, 1, 216, 13, 0, 120, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40dbf7d_0da275f, },
	// [3]ID_MENULANG_BUTTON_2
	{D_CTRL_BUTTON, 1, 531, 13, 0, 120, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0eb3_0fa23e1, },
	// [4]ID_MENULANG_IMAGE_LEFT_ARROW
	{D_CTRL_IMAGE, 1, 48, 6, 0, 26, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ae0f8e_34b3e9b, },
	// [5]ID_MENULANG_IMAGE_RIGHT_ARROW
	{D_CTRL_IMAGE, 1, 882, 6, 0, 26, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ae1023_2513423, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_menu_lang_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_menu_lang_window[6];
D_Frame atv_menu_lang_window = {
	run_ctrls_atv_menu_lang_window, 
	ctrl_description_of_atv_menu_lang_window, 
	atv_menu_lang_window_init, 
};

