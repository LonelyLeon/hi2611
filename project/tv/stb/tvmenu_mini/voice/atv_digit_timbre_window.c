/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-05-08 17:34:56

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
#define	ID_DIGIT_TIMBRE_GROUP_BG	1
#define	ID_DIGIT_TIMBRE_BUTTON_STANDARD	2
#define	ID_DIGIT_TIMBRE_BUTTON_USER	3
#define	ID_DIGIT_TIMBRE_BUTTON_MUSIC	4
#define	ID_DIGIT_TIMBRE_BUTTON_MOVIE	5
#define	ID_DIGIT_TIMBRE_IMAGE_LEFT_ARROW	6
#define	ID_DIGIT_TIMBRE_IMAGE_RIGHT_ARROW	7

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40dbf7d_0da506={-1, atv_IMG_ID_FS_OK_BUTTON_NORMAL, atv_IDS_STANDARD, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40dbf7d_0da3608={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, atv_IDS_STANDARD, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a76aff_30d72ae={-1, atv_IMG_ID_sub_menu_direc_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a76c40_3c8a27={-1, atv_IMG_ID_sub_menu_direc_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae5cb7_1b56938={-1, atv_IMG_ID_FS_OK_BUTTON_NORMAL, atv_IDS_THEATRE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae5cb7_1b52125={-1, atv_IMG_ID_FS_OK_BUTTON_NORMAL, atv_IDS_MUSIC, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae5cb7_1b57f58={-1, atv_IMG_ID_FS_OK_BUTTON_NORMAL, atv_IDS_MOVIE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae748d_0bb7817={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, atv_IDS_THEATRE, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae748d_0bb26fc={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, atv_IDS_MUSIC, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae748d_0bb76dc={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, atv_IDS_MOVIE, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a3186_14829={-1, atv_IMG_ID_FS_OK_BUTTON_DISABLE, atv_IDS_STANDARD, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a31bf_01f4823={-1, atv_IMG_ID_FS_OK_BUTTON_DISABLE, atv_IDS_THEATRE, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a31e2_38a18be={-1, atv_IMG_ID_FS_OK_BUTTON_DISABLE, atv_IDS_MUSIC, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20a3220_0bb6784={-1, atv_IMG_ID_FS_OK_BUTTON_DISABLE, atv_IDS_MOVIE, &atv_fmt_center_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_DIGIT_TIMBRE_GROUP_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_DIGIT_TIMBRE_BUTTON_STANDARD"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40dbf7d_0da275f={{&GUID_c40dbf7d_0da506, &GUID_c40dbf7d_0da3608, &GUID_c20a3186_14829, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_DIGIT_TIMBRE_BUTTON_USER"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0eb3_0fa23e1={{&GUID_c4ae5cb7_1b56938, &GUID_c4ae748d_0bb7817, &GUID_c20a31bf_01f4823, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_DIGIT_TIMBRE_BUTTON_MUSIC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0f7c_1485bb2={{&GUID_c4ae5cb7_1b52125, &GUID_c4ae748d_0bb26fc, &GUID_c20a31e2_38a18be, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_DIGIT_TIMBRE_BUTTON_MOVIE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0fe7_222289d={{&GUID_c4ae5cb7_1b57f58, &GUID_c4ae748d_0bb76dc, &GUID_c20a3220_0bb6784, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_IMAGE}	"ID_DIGIT_TIMBRE_IMAGE_LEFT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a76aff_30d2cd6={{&GUID_c4a76aff_30d72ae, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_IMAGE}	"ID_DIGIT_TIMBRE_IMAGE_RIGHT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a76c40_3c85f6c={{&GUID_c4a76c40_3c8a27, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_digit_timbre_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 25, 445, 0, 900, 55, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_DIGIT_TIMBRE_GROUP_BG
	{D_CTRL_GROUP, 0, 0, 0, -41, 900, 55, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_DIGIT_TIMBRE_BUTTON_STANDARD
	{D_CTRL_BUTTON, 1, 142, 15, 0, 150, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c40dbf7d_0da275f, },
	// [3]ID_DIGIT_TIMBRE_BUTTON_USER
	{D_CTRL_BUTTON, 1, 328, 15, 0, 150, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0eb3_0fa23e1, },
	// [4]ID_DIGIT_TIMBRE_BUTTON_MUSIC
	{D_CTRL_BUTTON, 1, 512, 15, 0, 150, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0f7c_1485bb2, },
	// [5]ID_DIGIT_TIMBRE_BUTTON_MOVIE
	{D_CTRL_BUTTON, 1, 696, 15, 0, 150, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0fe7_222289d, },
	// [6]ID_DIGIT_TIMBRE_IMAGE_LEFT_ARROW
	{D_CTRL_IMAGE, 1, 117, 18, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a76aff_30d2cd6, },
	// [7]ID_DIGIT_TIMBRE_IMAGE_RIGHT_ARROW
	{D_CTRL_IMAGE, 1, 860, 18, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a76c40_3c85f6c, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_digit_timbre_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_digit_timbre_window[8];
D_Frame atv_digit_timbre_window = {
	run_ctrls_atv_digit_timbre_window, 
	ctrl_description_of_atv_digit_timbre_window, 
	atv_digit_timbre_window_init, 
};

