/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {songyw}
	on computer "PRSONGYW"
	update/create time:	2016-04-21 15:27:49

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2016-04-15 11:54:34.625

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
#define	ID_MULTIAUDIO_GROUP_INFO	1
#define	ID_MULTIAUDIO_LABEL_FILE_NAME	2
#define	ID_MULTIAUDIO_LABEL_AUDIO_TITLE	3
#define	ID_MULTIAUDIO_SELECT_AUDIO	4
#define	ID_MULTIAUDIO_BUTTON_ESC	5
#define	ID_MULTIAUDIO_LABEL_AUDIO_INFO	6

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0d45196_00f6df1={-1, atv_IMB_ID_COMB_white_background, atv_IDS_MULTI_AUDIO, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0d62427_2223820={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c69f9733_01f7ab7={-1, -1, atv_IDS_MULTI_AUDIO, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c69f9854_0da6310={-1, atv_IMG_ID_FS_Select_focus, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c69f9b0a_16769e5={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_OFF, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c69f9b0a_1672ef={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_OFF, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c3402545_1192ea6={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c3499384_33c4823={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0d45109_38a29={{&GUID_c0d62427_2223820, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_MULTIAUDIO_GROUP_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c69f8d58_2712bde={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_MULTIAUDIO_LABEL_FILE_NAME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0d45196_00f1649={{&GUID_c0d45196_00f6df1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_MULTIAUDIO_LABEL_AUDIO_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c69f92c9_03e293a={{&GUID_c69f9733_01f7ab7, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_SELECT}	"ID_MULTIAUDIO_SELECT_AUDIO"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c69f9854_0da6e1e={{&GUID_c3499384_33c4823, &GUID_c69f9854_0da6310, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_MULTIAUDIO_BUTTON_ESC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c69f9b0a_1677b0f={{&GUID_c69f9b0a_16769e5, &GUID_c69f9b0a_1672ef, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_MULTIAUDIO_LABEL_AUDIO_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c3402545_119bb3={{&GUID_c3402545_1192ea6, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_multi_audio_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 300, 200, 0, -1, (D_FrameCtrlDescr*)&GUID_c0d45109_38a29, },
	// [1]ID_MULTIAUDIO_GROUP_INFO
	{D_CTRL_GROUP, 0, 0, 0, 20, 300, 190, 30, -1, (D_FrameCtrlDescr*)&GUID_c69f8d58_2712bde, },
	// [2]ID_MULTIAUDIO_LABEL_FILE_NAME
	{D_CTRL_LABEL, 1, 0, 0, 0, 300, 52, 30, -1, (D_FrameCtrlDescr*)&GUID_c0d45196_00f1649, },
	// [3]ID_MULTIAUDIO_LABEL_AUDIO_TITLE
	{D_CTRL_LABEL, 1, 5, 74, 0, 120, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c69f92c9_03e293a, },
	// [4]ID_MULTIAUDIO_SELECT_AUDIO
	{D_CTRL_SELECT, 1, 136, 74, 0, 78, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c69f9854_0da6e1e, },
	// [5]ID_MULTIAUDIO_BUTTON_ESC
	{D_CTRL_BUTTON, 1, 109, 138, 0, 80, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c69f9b0a_1677b0f, },
	// [6]ID_MULTIAUDIO_LABEL_AUDIO_INFO
	{D_CTRL_LABEL, 0, 214, 74, 20, 79, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c3402545_119bb3, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_multi_audio_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_multi_audio_window[7];
D_Frame atv_multi_audio_window = {
	run_ctrls_atv_multi_audio_window, 
	ctrl_description_of_atv_multi_audio_window, 
	atv_multi_audio_window_init, 
};

