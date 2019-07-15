/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2014-12-23 15:08:31

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2014-12-16 16:55:09.290

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
#define	ID_VOICE_LABLE_BG	1
#define	ID_VOICE_LABLE_BG2	2
#define	ID_VOICE_GROUP_BG	3
#define	ID_VOICE_LABLE_ICON	4
#define	ID_VOICE_LABLE_VAL	5
#define	ID_VOICE_PROGRESS_BAR	6

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a251c9_1b552fe={-1, atv_IMG_ID_FS_White_Round_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a252c2_38a7bbe={-1, atv_IMG_ID_voice_icon, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a25c0c_09c66d0={atv_COLOR_ENUM_21, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a25f29_0ea159e={-1, atv_IMG_ID_voice_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a260a9_2ee5744={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a273e1_1a52ed8={atv_COLOR_ENUM_2, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bb6843_22229={atv_COLOR_ENUM_14, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{&GUID_c4bb6843_22229, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_VOICE_LABLE_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a25c0c_09c4c8e={{&GUID_c4a25c0c_09c66d0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_VOICE_LABLE_BG2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a25f29_0ea454f={{&GUID_c4a25f29_0ea159e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_VOICE_GROUP_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a251c9_1b552a5={{&GUID_c4a251c9_1b552fe, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_VOICE_LABLE_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a252c2_38aa45={{&GUID_c4a252c2_38a7bbe, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_VOICE_LABLE_VAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a260a9_2ee799a={{&GUID_c4a260a9_2ee5744, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_PROGRESS}	"ID_VOICE_PROGRESS_BAR"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_c4a271fe_05d1e47={{&GUID_c4a273e1_1a52ed8, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_60, -1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_voicebar_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 50, 586, 0, 1180, 66, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_VOICE_LABLE_BG
	{D_CTRL_LABEL, 0, 6, 5, 30, 1168, 55, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a25c0c_09c4c8e, },
	// [2]ID_VOICE_LABLE_BG2
	{D_CTRL_LABEL, 1, 25, 3, 0, 156, 50, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a25f29_0ea454f, },
	// [3]ID_VOICE_GROUP_BG
	{D_CTRL_GROUP, 1, 211, 7, 0, 934, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a251c9_1b552a5, },
	// [4]ID_VOICE_LABLE_ICON
	{D_CTRL_LABEL, 2, 37, 1, 133, 48, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a252c2_38aa45, },
	// [5]ID_VOICE_LABLE_VAL
	{D_CTRL_LABEL, 2, 89, 4, 0, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a260a9_2ee799a, },
	// [6]ID_VOICE_PROGRESS_BAR
	{D_CTRL_PROGRESS, 3, 29, 19, 0, 877, 6, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a271fe_05d1e47, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_voicebar_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_voicebar_window[7];
D_Frame atv_voicebar_window = {
	run_ctrls_atv_voicebar_window, 
	ctrl_description_of_atv_voicebar_window, 
	atv_voicebar_window_init, 
};

