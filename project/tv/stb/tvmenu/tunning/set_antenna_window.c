/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY_WIN7"
	update/create time:	2018-05-26 14:32:46

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
#define	ID_FIXED_ANTENNA_TITLE	1
#define	ID_FIXED_ANTENNA_GROUP	2
#define	ID_SATELLITE_LABEL	3
#define	ID_LNB_FREQ_LABEL	4
#define	ID_TRANSPONDER_LIST_LABEL	5
#define	ID_22K_LABEL	6
#define	ID_SET_FIXED_ANTENNA_SELECT	7
#define	ID_LNB_FREQ_SELECT	8
#define	ID_TRANSPONDER_LIST_SELECT	9
#define	ID_22K_SELECT	10
#define	ID_SIGNAL_GROUP	11
#define	ID_TP_LABEL_INTESITY	12
#define	ID_TP_LABEL_QUALITY	13
#define	ID_TP_PROGRESS_S	14
#define	ID_TP_PROGRESS_Q	15
#define	ID_TP_LABEL_SVAL	16
#define	ID_TP_LABEL_QVAL	17
#define	ID_START_TP_SCAN	18
#define	ID_START_SATE_SCAN	19
#define	ID_IMAGE_RED	20
#define	ID_LABEL_ADD_TP	21
#define	ID_IMAGE_GREEN	22
#define	ID_LABEL_EDIT_TP	23

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20b3aad_1095af0={-1, -1, atv_IDS_SET_ANTENNA, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20b3bca_2bf371c={-1, -1, atv_IDS_SATELLITE, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20b3bca_2bf4c9f={atv_COLOR_ENUM_106, -1, atv_IDS_SATELLITE, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20b3c4e_2de81={-1, -1, atv_IDS_LNB_FREQ, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20b3d03_36b124c={-1, -1, atv_IDS_TRANSPONDER_LIST, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20b3e3b_2ee78b1={-1, -1, atv_IDS_22K, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20b3f14_36b2bc2={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20b3f14_36b7710={atv_COLOR_ENUM_106, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20c78ea_34b2882={-1, -1, atv_IDS_SIGNAL_INTENSITY, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20c7a04_1d43205={-1, -1, atv_IDS_SIGNAL_QUALITY, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c29b67c6_23229={atv_COLOR_ENUM_106, -1, atv_IDS_LNB_FREQ, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c29b67c6_2324823={atv_COLOR_ENUM_106, -1, atv_IDS_TRANSPONDER_LIST, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c29b67c6_2326784={atv_COLOR_ENUM_106, -1, atv_IDS_22K, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7516da3_3992982={-1, atv_IMG_ID_FS_select_focus_ex, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7516ee2_157166b={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7517536_3d843f0={-1, -1, atv_IDS_TP_SCAN, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c751753d_07d1c73={atv_COLOR_ENUM_106, -1, atv_IDS_TP_SCAN, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7517536_3d843f1={-1, -1, atv_IDS_SATE_SCAN, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c751753d_07d1c74={atv_COLOR_ENUM_106, -1, atv_IDS_SATE_SCAN, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c751927e_0ea4cad={atv_COLOR_ENUM_19, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c75194bd_128408b={-1, -1, -1, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c81e2c03_24b6df1={-1, atv_IMG_ID_Red, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c81e2df6_2bf1eb={-1, -1, atv_IDS_ADD_TP, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c81e2eab_23e6e65={-1, atv_IMG_ID_Green, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c81e2df6_1eb2bf={-1, -1, atv_IDS_EDIT_TP, &atv_fmt_left_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c20b3964_2515098={{&GUID_c7516ee2_157166b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_FIXED_ANTENNA_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c20b3aad_1097fda={{&GUID_c20b3aad_1095af0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_FIXED_ANTENNA_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c20b3b60_1863e91={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_SATELLITE_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c20b3bca_2bf5c67={{&GUID_c20b3bca_2bf371c, &GUID_c20b3bca_2bf4c9f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_LNB_FREQ_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c20b3c4e_2de6cbd={{&GUID_c20b3c4e_2de81, &GUID_c29b67c6_23229, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_TRANSPONDER_LIST_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c20b3d03_36b5e84={{&GUID_c20b3d03_36b124c, &GUID_c29b67c6_2324823, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_22K_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c20b3e3b_2ee23a1={{&GUID_c20b3e3b_2ee78b1, &GUID_c29b67c6_2326784, &GUID_c20b3e3b_2ee78b1, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_SELECT}	"ID_SET_FIXED_ANTENNA_SELECT"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c20b3f14_36b7cc1={{&GUID_c20b3f14_36b2bc2, &GUID_c20b3f14_36b7710, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_SELECT}	"ID_LNB_FREQ_SELECT"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c20b4109_280229={{&GUID_c20b3f14_36b2bc2, &GUID_c7516da3_3992982, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_SELECT}	"ID_TRANSPONDER_LIST_SELECT"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c20b41b9_2801efa={{&GUID_c20b3f14_36b2bc2, &GUID_c7516da3_3992982, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_SELECT}	"ID_22K_SELECT"
static PREFIXCONST D_TextID POSTCONST GUID_c7529ba2_32caaa[]={atv_IDS_OFF, atv_IDS_ON, atv_IDS_SEARCH_AUTO, };
static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c20b432c_29023f9={{&GUID_c20b3f14_36b2bc2, &GUID_c7516da3_3992982, &GUID_c75194bd_128408b, }, 1, 3, GUID_c7529ba2_32caaa, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_SIGNAL_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c20c74bc_2ce667b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_TP_LABEL_INTESITY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c20c78ea_34b794c={{&GUID_c20c78ea_34b2882, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_TP_LABEL_QUALITY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c20c7a04_1d470cd={{&GUID_c20c7a04_1d43205, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_PROGRESS}	"ID_TP_PROGRESS_S"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_c20c7ace_32c1010={{&GUID_c751927e_0ea4cad, NULL, NULL, }, 1, 100, 1, 0, -1, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_PROGRESS}	"ID_TP_PROGRESS_Q"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_c20c7c13_0fa4c82={{&GUID_c751927e_0ea4cad, NULL, NULL, }, 1, 100, 1, 0, -1, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_TP_LABEL_SVAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c2a632ec_31c6df1={{&GUID_c75194bd_128408b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_TP_LABEL_QVAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c2a6349d_2321eb={{&GUID_c75194bd_128408b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_BUTTON}	"ID_START_TP_SCAN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7516a27_34b6b2e={{&GUID_c7517536_3d843f0, &GUID_c751753d_07d1c73, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_BUTTON}	"ID_START_SATE_SCAN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7516a27_34b6b2f={{&GUID_c7517536_3d843f1, &GUID_c751753d_07d1c74, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_IMAGE}	"ID_IMAGE_RED"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c81e2c03_24b1649={{&GUID_c81e2c03_24b6df1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_LABEL_ADD_TP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c81e2df6_2bf26e9={{&GUID_c81e2df6_2bf1eb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_IMAGE}	"ID_IMAGE_GREEN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c81e2eab_23e417={{&GUID_c81e2eab_23e6e65, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_LABEL}	"ID_LABEL_EDIT_TP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c81e2f19_0954f22={{&GUID_c81e2df6_1eb2bf, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_set_antenna_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 370, 150, 0, 530, 380, 0, -1, (D_FrameCtrlDescr*)&GUID_c20b3964_2515098, },
	// [1]ID_FIXED_ANTENNA_TITLE
	{D_CTRL_LABEL, 0, 162, 11, 170, 200, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c20b3aad_1097fda, },
	// [2]ID_FIXED_ANTENNA_GROUP
	{D_CTRL_GROUP, 0, 14, 49, 170, 500, 286, 30, -1, (D_FrameCtrlDescr*)&GUID_c20b3b60_1863e91, },
	// [3]ID_SATELLITE_LABEL
	{D_CTRL_LABEL, 2, 5, 2, 0, 200, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c20b3bca_2bf5c67, },
	// [4]ID_LNB_FREQ_LABEL
	{D_CTRL_LABEL, 2, 5, 36, 0, 200, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c20b3c4e_2de6cbd, },
	// [5]ID_TRANSPONDER_LIST_LABEL
	{D_CTRL_LABEL, 2, 5, 70, 0, 200, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c20b3d03_36b5e84, },
	// [6]ID_22K_LABEL
	{D_CTRL_LABEL, 2, 5, 104, 0, 200, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c20b3e3b_2ee23a1, },
	// [7]ID_SET_FIXED_ANTENNA_SELECT
	{D_CTRL_SELECT, 2, 205, 2, 0, 290, 32, 30, 3, (D_FrameCtrlDescr*)&GUID_c20b3f14_36b7cc1, },
	// [8]ID_LNB_FREQ_SELECT
	{D_CTRL_SELECT, 2, 205, 36, 0, 290, 32, 30, 4, (D_FrameCtrlDescr*)&GUID_c20b4109_280229, },
	// [9]ID_TRANSPONDER_LIST_SELECT
	{D_CTRL_SELECT, 2, 205, 70, 0, 290, 32, 30, 5, (D_FrameCtrlDescr*)&GUID_c20b41b9_2801efa, },
	// [10]ID_22K_SELECT
	{D_CTRL_SELECT, 2, 205, 104, 0, 290, 32, 30, 6, (D_FrameCtrlDescr*)&GUID_c20b432c_29023f9, },
	// [11]ID_SIGNAL_GROUP
	{D_CTRL_LABEL, 2, 14, 206, 0, 475, 78, 30, -1, (D_FrameCtrlDescr*)&GUID_c20c74bc_2ce667b, },
	// [12]ID_TP_LABEL_INTESITY
	{D_CTRL_LABEL, 11, 5, 7, 91, 140, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c20c78ea_34b794c, },
	// [13]ID_TP_LABEL_QUALITY
	{D_CTRL_LABEL, 11, 5, 41, 91, 140, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c20c7a04_1d470cd, },
	// [14]ID_TP_PROGRESS_S
	{D_CTRL_PROGRESS, 11, 152, 12, 13, 260, 23, 30, -1, (D_FrameCtrlDescr*)&GUID_c20c7ace_32c1010, },
	// [15]ID_TP_PROGRESS_Q
	{D_CTRL_PROGRESS, 11, 152, 48, 93, 260, 23, 30, -1, (D_FrameCtrlDescr*)&GUID_c20c7c13_0fa4c82, },
	// [16]ID_TP_LABEL_SVAL
	{D_CTRL_LABEL, 11, 418, 8, 11, 54, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c2a632ec_31c6df1, },
	// [17]ID_TP_LABEL_QVAL
	{D_CTRL_LABEL, 11, 418, 40, 11, 54, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c2a6349d_2321eb, },
	// [18]ID_START_TP_SCAN
	{D_CTRL_BUTTON, 2, 5, 138, 0, 490, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c7516a27_34b6b2e, },
	// [19]ID_START_SATE_SCAN
	{D_CTRL_BUTTON, 2, 5, 170, 0, 490, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c7516a27_34b6b2f, },
	// [20]ID_IMAGE_RED
	{D_CTRL_IMAGE, 0, 47, 346, 20, 26, 15, 30, -1, (D_FrameCtrlDescr*)&GUID_c81e2c03_24b1649, },
	// [21]ID_LABEL_ADD_TP
	{D_CTRL_LABEL, 0, 79, 338, 20, 150, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c81e2df6_2bf26e9, },
	// [22]ID_IMAGE_GREEN
	{D_CTRL_IMAGE, 0, 302, 346, 20, 26, 15, 30, -1, (D_FrameCtrlDescr*)&GUID_c81e2eab_23e417, },
	// [23]ID_LABEL_EDIT_TP
	{D_CTRL_LABEL, 0, 333, 338, 20, 150, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c81e2f19_0954f22, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	set_antenna_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_set_antenna_window[24];
D_Frame set_antenna_window = {
	run_ctrls_set_antenna_window, 
	ctrl_description_of_set_antenna_window, 
	set_antenna_window_init, 
};

