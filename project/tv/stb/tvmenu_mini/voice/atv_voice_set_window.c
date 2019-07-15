/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-05-08 17:36:22

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
#define	ID_VOICESET_GROUP_BACKGROUND	1
#define	ID_VOICESET_BUTTON_LEFT_ARROW	2
#define	ID_VOICESET_PROGRESS_PUBLIC	3
#define	ID_VOICESET_LABLE_VAL	4
#define	ID_VOICESET_BUTTON_RIGHT_ARROW	5

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d8c87_04e366b={-1, atv_IMG_ID_sub_menu_direc_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d8e83_1c53ef6={-1, atv_IMG_ID_sub_menu_direc_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d954f_3997bb9={-1, atv_IMG_ID_FS_PROGRESS_NORMAL, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a43097_2bf3d6c={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_VOICESET_GROUP_BACKGROUND"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_VOICESET_BUTTON_LEFT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d8c87_04e1cd0={{&GUID_c40d8c87_04e366b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_PROGRESS}	"ID_VOICESET_PROGRESS_PUBLIC"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_c40d954f_399902={{&GUID_c40d954f_3997bb9, NULL, NULL, }, 1, 100, 1, 0, -1, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_VOICESET_LABLE_VAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a43097_2bf4ae1={{&GUID_c4a43097_2bf3d6c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_VOICESET_BUTTON_RIGHT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d8e83_1c55422={{&GUID_c40d8e83_1c53ef6, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_voice_set_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 25, 445, 0, 900, 55, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_VOICESET_GROUP_BACKGROUND
	{D_CTRL_GROUP, 0, 0, 0, -21, 900, 55, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_VOICESET_BUTTON_LEFT_ARROW
	{D_CTRL_BUTTON, 1, 117, 17, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d8c87_04e1cd0, },
	// [3]ID_VOICESET_PROGRESS_PUBLIC
	{D_CTRL_PROGRESS, 1, 144, 17, 0, 700, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d954f_399902, },
	// [4]ID_VOICESET_LABLE_VAL
	{D_CTRL_LABEL, 3, 310, 0, 0, 80, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a43097_2bf4ae1, },
	// [5]ID_VOICESET_BUTTON_RIGHT_ARROW
	{D_CTRL_BUTTON, 1, 860, 17, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d8e83_1c55422, },
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

