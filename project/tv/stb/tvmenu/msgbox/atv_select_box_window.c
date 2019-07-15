/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2014-12-10 17:04:40

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2014-12-10 16:07:39.640

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
#define	ID_MSG_LABEL	1
#define	ID_BUTTON_0	2
#define	ID_BUTTON_1	3
#define	ID_COUNTDOWN_LABEL	4

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a11d1_3d84823={-1, atv_IMG_ID_FS_pop_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a11de_ae000f7={-1, -1, atv_IDS_NULL, &atv_fmt_right_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a11de_00f7ae0={-1, -1, atv_IDS_NULL, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a2421_05d3a4a={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a2421_05d1947={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a2539_1385c69={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_CANCEL, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a2539_1386f2b={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_CANCEL, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a11d1_3d829={{&GUID_c56a11d1_3d84823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_MSG_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a11de_00f672f={{&GUID_c56a11de_00f7ae0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_BUTTON_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a2421_05d4a44={{&GUID_c56a2421_05d3a4a, &GUID_c56a2421_05d1947, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a2539_138f8f={{&GUID_c56a2539_1385c69, &GUID_c56a2539_1386f2b, NULL, }, 1, };

// definition of [4]{D_CTRL_LABEL}	"ID_COUNTDOWN_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a11de_0f20f67={{&GUID_c56a11de_ae000f7, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_select_box_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 440, 406, 0, 404, 208, 0, -1, (D_FrameCtrlDescr*)&GUID_c56a11d1_3d829, },
	// [1]ID_MSG_LABEL
	{D_CTRL_LABEL, 0, 30, 32, 20, 344, 106, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a11de_00f672f, },
	// [2]ID_BUTTON_0
	{D_CTRL_BUTTON, 0, 44, 154, 20, 115, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a2421_05d4a44, },
	// [3]ID_BUTTON_1
	{D_CTRL_BUTTON, 0, 240, 154, 20, 115, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a2539_138f8f, },
	// [4]ID_COUNTDOWN_LABEL
	{D_CTRL_LABEL, 0, 336, 2, 20, 60, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a11de_0f20f67, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_select_box_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_select_box_window[5];
D_Frame atv_select_box_window = {
	run_ctrls_atv_select_box_window, 
	ctrl_description_of_atv_select_box_window, 
	atv_select_box_window_init, 
};

