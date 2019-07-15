/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2015-03-26 14:46:29

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
#define	ID_VOICESET_GROUP_BACKGROUND	1
#define	ID_VOICESET_BUTTON_LEFT_ARROW	2
#define	ID_VOICESET_PROGRESS_PUBLIC	3
#define	ID_VOICESET_LABLE_VAL	4
#define	ID_VOICESET_BUTTON_RIGHT_ARROW	5

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d76b9_0da4cad={-1, atv_IMG_ID_focus_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d8c87_04e366b={-1, atv_IMG_ID_left_arrow_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d8c87_04e66c4={-1, atv_IMG_ID_left_arrow_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d8e83_1c53ef6={-1, atv_IMG_ID_right_arrow_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d8e83_1c5822={-1, atv_IMG_ID_right_arrow_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d954f_3997bb9={-1, atv_IMG_ID_COMB_scroll_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a43097_2bf3d6c={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08e34f4_30d6390={-1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{&GUID_c08e34f4_30d6390, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_VOICESET_GROUP_BACKGROUND"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{&GUID_c40d76b9_0da4cad, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_VOICESET_BUTTON_LEFT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d8c87_04e1cd0={{&GUID_c40d8c87_04e366b, &GUID_c40d8c87_04e66c4, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_PROGRESS}	"ID_VOICESET_PROGRESS_PUBLIC"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_c40d954f_399902={{&GUID_c40d954f_3997bb9, NULL, NULL, }, 1, 100, 1, 0, -1, atv_IMG_ID_COMB_scroll_focus, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_VOICESET_LABLE_VAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a43097_2bf4ae1={{&GUID_c4a43097_2bf3d6c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_VOICESET_BUTTON_RIGHT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d8e83_1c55422={{&GUID_c40d8e83_1c53ef6, &GUID_c40d8e83_1c5822, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_voice_set_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 176, 460, 0, 960, 58, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_VOICESET_GROUP_BACKGROUND
	{D_CTRL_GROUP, 0, -1, 0, 20, 960, 58, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_VOICESET_BUTTON_LEFT_ARROW
	{D_CTRL_BUTTON, 1, 48, 6, 0, 27, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d8c87_04e1cd0, },
	// [3]ID_VOICESET_PROGRESS_PUBLIC
	{D_CTRL_PROGRESS, 1, 116, 13, 0, 718, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d954f_399902, },
	// [4]ID_VOICESET_LABLE_VAL
	{D_CTRL_LABEL, 3, 319, 1, 0, 83, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a43097_2bf4ae1, },
	// [5]ID_VOICESET_BUTTON_RIGHT_ARROW
	{D_CTRL_BUTTON, 1, 882, 6, 0, 27, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d8e83_1c55422, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_voice_set_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_voice_set_window[6];
D_Frame atv_voice_set_window = {
	run_ctrls_atv_voice_set_window, 
	ctrl_description_of_atv_voice_set_window, 
	atv_voice_set_window_init, 
};

