/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY"
	update/create time:	2015-11-03 11:02:54

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-08-20 10:37:14.250

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
#define	ID_MOVIEINFO_GROUP_INFO	1
#define	ID_MOVIEINFO_LABEL_FILE_NAME	2
#define	ID_MOVIEINFO_LABEL_SIZE_TITLE	3
#define	ID_MOVIEINFO_LABEL_SIZE	4
#define	ID_MOVIEINFO_LABEL_WH_TITLE	5
#define	ID_MOVIEINFO_LABEL_WH	6
#define	ID_MOVIEINFO_LABEL_AUDIO_TITLE	7
#define	ID_MOVIEINFO_LABEL_PROG_TITLE	8
#define	ID_MOVIEINFO_SELECT_AUDIO	9
#define	ID_MOVIEINFO_SELECT_PROG	10
#define	ID_MOVIEINFO_BUTTON_ESC	11

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0d45196_00f6df1={-1, atv_IMB_ID_COMB_white_background, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0d62427_2223820={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c69f92c9_03e1511={-1, -1, atv_IDS_FILE_SIZE, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c69f93bb_21310ec={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c69f9733_01f3153={-1, -1, atv_IDS_Resolution, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c69f9733_01f7ab7={-1, -1, atv_IDS_MULTI_AUDIO, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c69f9733_01f1c97={-1, -1, atv_IDS_EVENT_NAME, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c69f9854_0da6310={-1, atv_IMG_ID_FS_Select_focus, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c69f9b0a_16769e5={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_OFF, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c69f9b0a_1672ef={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_OFF, &atv_fmt_center_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0d45109_38a29={{&GUID_c0d62427_2223820, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_MOVIEINFO_GROUP_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c69f8d58_2712bde={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_MOVIEINFO_LABEL_FILE_NAME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0d45196_00f1649={{&GUID_c0d45196_00f6df1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_MOVIEINFO_LABEL_SIZE_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c69f92c9_03e2938={{&GUID_c69f92c9_03e1511, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_MOVIEINFO_LABEL_SIZE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c69f93bb_2136b55={{&GUID_c69f93bb_21310ec, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_MOVIEINFO_LABEL_WH_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c69f92c9_03e2939={{&GUID_c69f9733_01f3153, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_MOVIEINFO_LABEL_WH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c69f93bb_2136b56={{&GUID_c69f93bb_21310ec, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_MOVIEINFO_LABEL_AUDIO_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c69f92c9_03e293a={{&GUID_c69f9733_01f7ab7, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_MOVIEINFO_LABEL_PROG_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c69f92c9_03e293b={{&GUID_c69f9733_01f1c97, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_SELECT}	"ID_MOVIEINFO_SELECT_AUDIO"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c69f9854_0da6e1e={{&GUID_c69f93bb_21310ec, &GUID_c69f9854_0da6310, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_SELECT}	"ID_MOVIEINFO_SELECT_PROG"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c69f9854_0da6e1d={{&GUID_c69f93bb_21310ec, &GUID_c69f9854_0da6310, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_BUTTON}	"ID_MOVIEINFO_BUTTON_ESC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c69f9b0a_1677b0f={{&GUID_c69f9b0a_16769e5, &GUID_c69f9b0a_1672ef, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_media_movie_info_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 300, 260, 0, -1, (D_FrameCtrlDescr*)&GUID_c0d45109_38a29, },
	// [1]ID_MOVIEINFO_GROUP_INFO
	{D_CTRL_GROUP, 0, 0, 0, 20, 300, 260, 30, -1, (D_FrameCtrlDescr*)&GUID_c69f8d58_2712bde, },
	// [2]ID_MOVIEINFO_LABEL_FILE_NAME
	{D_CTRL_LABEL, 1, 0, 0, 0, 300, 52, 30, -1, (D_FrameCtrlDescr*)&GUID_c0d45196_00f1649, },
	// [3]ID_MOVIEINFO_LABEL_SIZE_TITLE
	{D_CTRL_LABEL, 1, 5, 62, 0, 120, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c69f92c9_03e2938, },
	// [4]ID_MOVIEINFO_LABEL_SIZE
	{D_CTRL_LABEL, 1, 146, 62, 0, 140, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c69f93bb_2136b55, },
	// [5]ID_MOVIEINFO_LABEL_WH_TITLE
	{D_CTRL_LABEL, 1, 5, 94, 0, 120, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c69f92c9_03e2939, },
	// [6]ID_MOVIEINFO_LABEL_WH
	{D_CTRL_LABEL, 1, 146, 94, 0, 140, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c69f93bb_2136b56, },
	// [7]ID_MOVIEINFO_LABEL_AUDIO_TITLE
	{D_CTRL_LABEL, 1, 5, 126, 0, 120, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c69f92c9_03e293a, },
	// [8]ID_MOVIEINFO_LABEL_PROG_TITLE
	{D_CTRL_LABEL, 1, 5, 158, 0, 120, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c69f92c9_03e293b, },
	// [9]ID_MOVIEINFO_SELECT_AUDIO
	{D_CTRL_SELECT, 1, 146, 126, 0, 140, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c69f9854_0da6e1e, },
	// [10]ID_MOVIEINFO_SELECT_PROG
	{D_CTRL_SELECT, 1, 146, 158, 0, 140, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c69f9854_0da6e1d, },
	// [11]ID_MOVIEINFO_BUTTON_ESC
	{D_CTRL_BUTTON, 1, 110, 213, 0, 80, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c69f9b0a_1677b0f, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_media_movie_info_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_media_movie_info_window[12];
D_Frame atv_media_movie_info_window = {
	run_ctrls_atv_media_movie_info_window, 
	ctrl_description_of_atv_media_movie_info_window, 
	atv_media_movie_info_window_init, 
};

