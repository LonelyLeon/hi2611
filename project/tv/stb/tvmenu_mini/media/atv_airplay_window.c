/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2019-02-25 10:01:16

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2019-02-11  9:16:23.493

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
#define	ID_FULL_MOVIE_CONTROL_GROUP	1
#define	ID_FULL_MOVIE_BOTTOM	2
#define	ID_FULL_MOVIE_PLAY_CONTROL	3
#define	ID_FULL_MOVIE_PLAY_PROGRESS	4
#define	ID_MOVIE_SELECT_POS	5
#define	ID_FULL_MOVIE_PROGRESS	6
#define	ID_FULL_MOVIE_TOTAL_TIME	7
#define	ID_FULL_MOVIE_STATUS	8
#define	ID_FULL_MOVIE_STATUS_LABEL	9
#define	ID_FULL_MOVIE_INFO_GROUP	10
#define	ID_FULL_MOVIE_NAME_1	11
#define	ID_FULL_MOVIE_NAME	12
#define	ID_FULL_MOVIE_HW	13
#define	ID_FULL_MOVIE_HW_1	14
#define	ID_FULL_MOVIE_PROMPT_MSG	15
#define	ID_AIRPLAY_PROMPT_MSG	16

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cd9a3d_3a97e61={atv_COLOR_ENUM_0, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cd9a5a_2ee6061={atv_COLOR_ENUM_14, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cdafc6_33c7091={-1, -1, -1, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5904df1_04e722a={atv_COLOR_ENUM_21, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bef0f76a_2ee6947={-1, atv_IMG_ID_pos, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bda8d00f_04e18be={atv_COLOR_ENUM_107, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c522550c_32c18be={-1, -1, atv_IDS_Resolution, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c8bc5559_0794ad4={-1, -1, -1, &atv_fmt_left_top_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c8bc5bbd_1766784={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_ccae594f_3bc3d6c={-1, atv_IMG_ID_FS_Connect_pro, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_594fccae_d6c3bc3={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cd9a3d_3a9288={{&GUID_c4cd9a3d_3a97e61, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_FULL_MOVIE_CONTROL_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cd9a5a_2ee2898={{&GUID_c4cd9a5a_2ee6061, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_FULL_MOVIE_BOTTOM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5904df1_04e1ef3={{&GUID_c5904df1_04e722a, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_FULL_MOVIE_PLAY_CONTROL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cd9d6c_222288b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_FULL_MOVIE_PLAY_PROGRESS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cdaddd_2fd349f={{&GUID_c4cd9a5a_2ee6061, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_MOVIE_SELECT_POS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee99606_2de4823={{NULL, &GUID_bef0f76a_2ee6947, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_PROGRESS}	"ID_FULL_MOVIE_PROGRESS"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_c4cdae99_128b75={{&GUID_bda8d00f_04e18be, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_106, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_FULL_MOVIE_TOTAL_TIME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cdafc6_33c6172={{&GUID_c4cdafc6_33c7091, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_IMAGE}	"ID_FULL_MOVIE_STATUS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cdb03a_31c6dc3={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_FULL_MOVIE_STATUS_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cdb108_32c4c9e={{&GUID_c4cdafc6_33c7091, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_GROUP}	"ID_FULL_MOVIE_INFO_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c521dcb7_29f6784={{&GUID_ccae594f_3bc3d6c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_FULL_MOVIE_NAME_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c506360f_2806784={{&GUID_c4cdafc6_33c7091, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_FULL_MOVIE_NAME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c521ddda_33c284f={{&GUID_c8bc5559_0794ad4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_FULL_MOVIE_HW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c521df19_04e29d={{&GUID_c522550c_32c18be, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_FULL_MOVIE_HW_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c521df84_05d2e91={{&GUID_c8bc5bbd_1766784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_LABEL}	"ID_FULL_MOVIE_PROMPT_MSG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ccae594f_3bc4ae1={{&GUID_ccae594f_3bc3d6c, NULL, NULL, }, 1, };

// definition of [1]{D_CTRL_LABEL}	"ID_AIRPLAY_PROMPT_MSG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cc94fae5_34ae1bc={{&GUID_594fccae_d6c3bc3, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_airplay_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 960, 540, 0, -1, (D_FrameCtrlDescr*)&GUID_c4cd9a3d_3a9288, },
	// [1]ID_FULL_MOVIE_CONTROL_GROUP
	{D_CTRL_GROUP, 0, 44, 453, 20, 876, 62, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cd9a5a_2ee2898, },
	// [2]ID_FULL_MOVIE_BOTTOM
	{D_CTRL_GROUP, 1, 4, 4, 2, 868, 55, 30, -1, (D_FrameCtrlDescr*)&GUID_c5904df1_04e1ef3, },
	// [3]ID_FULL_MOVIE_PLAY_CONTROL
	{D_CTRL_GROUP, 2, 10, 2, 20, 146, 51, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cd9d6c_222288b, },
	// [4]ID_FULL_MOVIE_PLAY_PROGRESS
	{D_CTRL_GROUP, 2, 165, 8, 20, 697, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cdaddd_2fd349f, },
	// [5]ID_MOVIE_SELECT_POS
	{D_CTRL_BUTTON, 4, 6, 11, -20, 3, 14, 30, -1, (D_FrameCtrlDescr*)&GUID_bee99606_2de4823, },
	// [6]ID_FULL_MOVIE_PROGRESS
	{D_CTRL_PROGRESS, 4, 7, 16, 0, 520, 3, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cdae99_128b75, },
	// [7]ID_FULL_MOVIE_TOTAL_TIME
	{D_CTRL_LABEL, 4, 529, 5, 0, 167, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cdafc6_33c6172, },
	// [8]ID_FULL_MOVIE_STATUS
	{D_CTRL_IMAGE, 3, 17, 2, 0, 48, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cdb03a_31c6dc3, },
	// [9]ID_FULL_MOVIE_STATUS_LABEL
	{D_CTRL_LABEL, 3, 69, 11, 0, 62, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cdb108_32c4c9e, },
	// [10]ID_FULL_MOVIE_INFO_GROUP
	{D_CTRL_GROUP, 0, 150, 381, 20, 700, 71, 30, -1, (D_FrameCtrlDescr*)&GUID_c521dcb7_29f6784, },
	// [11]ID_FULL_MOVIE_NAME_1
	{D_CTRL_LABEL, 10, 10, 3, -1, 110, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c506360f_2806784, },
	// [12]ID_FULL_MOVIE_NAME
	{D_CTRL_LABEL, 10, 124, 3, -1, 570, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c521ddda_33c284f, },
	// [13]ID_FULL_MOVIE_HW
	{D_CTRL_LABEL, 10, 10, 37, -1, 110, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c521df19_04e29d, },
	// [14]ID_FULL_MOVIE_HW_1
	{D_CTRL_LABEL, 10, 124, 37, -1, 184, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c521df84_05d2e91, },
	// [15]ID_FULL_MOVIE_PROMPT_MSG
	{D_CTRL_LABEL, 0, 320, 235, 20, 320, 64, 30, -1, (D_FrameCtrlDescr*)&GUID_ccae594f_3bc4ae1, },
	// [16]ID_AIRPLAY_PROMPT_MSG
	{D_CTRL_LABEL, 0, 380, 240, 20, 200, 60, 30, -1, (D_FrameCtrlDescr*)&GUID_cc94fae5_34ae1bc, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_airplay_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_airplay_window[17];
D_Frame atv_airplay_window = {
	run_ctrls_atv_airplay_window, 
	ctrl_description_of_atv_airplay_window, 
	atv_airplay_window_init, 
};

