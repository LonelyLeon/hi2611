/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2016-01-11 19:50:15

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-11-30 18:45:54.727

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
#define	ID_LABEL_TITLE	1
#define	ID_GROUP	2
#define	ID_LABEL_STATE1	3
#define	ID_LABEL_STATE2	4
#define	ID_LABEL_STATE3	5
#define	ID_LABEL_STATE4	6
#define	ID_LABEL_STATE5	7
#define	ID_IMAGE_BOTTOM	8
#define	ID_HINT_ESC	9
#define	ID_LABEL_ESC	10

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee8087e_6c={atv_COLOR_ENUM_65, -1, atv_IDS_RECEIVE_SERIAL, &atv_fmt_left_middle_h15_v15_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee80985_90={atv_COLOR_ENUM_13, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee80eae_32={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee84ead_db={-1, atv_IMG_ID_FS_BUTTON_GRAY, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee852b4_3e={-1, -1, atv_IDS_BACK, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0e0f963_1386784={-1, -1, -1, &atv_fmt_left_middle_h10_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee67715_29={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_LABEL_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee8087e_e1={{&GUID_bee8087e_6c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee80985_52={{&GUID_bee80985_90, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_LABEL_STATE1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee80eae_8d={{&GUID_bee80eae_32, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_LABEL_STATE2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee812fb_a3={{&GUID_bee80eae_32, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_LABEL_STATE3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee82ecd_7f={{&GUID_bee80eae_32, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_LABEL_STATE4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee8330e_f5={{&GUID_bee80eae_32, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_LABEL_STATE5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee83680_9c={{&GUID_c0e0f963_1386784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_IMAGE}	"ID_IMAGE_BOTTOM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee83830_31={{&GUID_bee80985_90, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_HINT_ESC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee84ead_a6={{&GUID_bee84ead_db, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_LABEL_ESC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee852b4_0c={{&GUID_bee852b4_3e, NULL, NULL, }, 0, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_serial_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 45, 30, 0, 630, 516, 0, -1, (D_FrameCtrlDescr*)&GUID_bee67715_29, },
	// [1]ID_LABEL_TITLE
	{D_CTRL_LABEL, 0, 0, 0, 14, 610, 71, 30, -1, (D_FrameCtrlDescr*)&GUID_bee8087e_e1, },
	// [2]ID_GROUP
	{D_CTRL_GROUP, 0, 27, 68, 14, 583, 360, 30, -1, (D_FrameCtrlDescr*)&GUID_bee80985_52, },
	// [3]ID_LABEL_STATE1
	{D_CTRL_LABEL, 2, 31, 53, 64, 512, 43, 30, -1, (D_FrameCtrlDescr*)&GUID_bee80eae_8d, },
	// [4]ID_LABEL_STATE2
	{D_CTRL_LABEL, 2, 31, 101, 44, 513, 43, 30, -1, (D_FrameCtrlDescr*)&GUID_bee812fb_a3, },
	// [5]ID_LABEL_STATE3
	{D_CTRL_LABEL, 2, 31, 151, 26, 512, 43, 30, -1, (D_FrameCtrlDescr*)&GUID_bee82ecd_7f, },
	// [6]ID_LABEL_STATE4
	{D_CTRL_LABEL, 2, 31, 200, 12, 512, 43, 30, -1, (D_FrameCtrlDescr*)&GUID_bee8330e_f5, },
	// [7]ID_LABEL_STATE5
	{D_CTRL_LABEL, 2, 31, 250, -4, 512, 43, 30, -1, (D_FrameCtrlDescr*)&GUID_bee83680_9c, },
	// [8]ID_IMAGE_BOTTOM
	{D_CTRL_IMAGE, 0, 27, 426, 14, 583, 65, 30, -1, (D_FrameCtrlDescr*)&GUID_bee83830_31, },
	// [9]ID_HINT_ESC
	{D_CTRL_LABEL, 8, 337, 15, 17, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_bee84ead_a6, },
	// [10]ID_LABEL_ESC
	{D_CTRL_LABEL, 8, 452, 17, 17, 100, 33, 30, -1, (D_FrameCtrlDescr*)&GUID_bee852b4_0c, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_serial_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_serial_window[11];
D_Frame atv_serial_window = {
	run_ctrls_atv_serial_window, 
	ctrl_description_of_atv_serial_window, 
	atv_serial_window_init, 
};

