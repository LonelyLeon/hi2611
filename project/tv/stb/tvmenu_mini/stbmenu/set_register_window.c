/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX_NOTE"
	update/create time:	2015-08-27 23:53:04

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-08-05 15:45:47.015

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
#define	ID_REGISTER_LABEL_REGISTER	1
#define	ID_REGISTER_GROUP	2
#define	ID_REGISTER_GROUP_1	3
#define	ID_REGISTER_GROUP_2	4
#define	ID_REGISTER_GROUP_3	5
#define	ID_REGISTER_LABEL_1	6
#define	ID_REGISTER_LABEL_2	7
#define	ID_REGISTER_LABEL_3	8
#define	ID_REGISTER_LABEL_SHOW_VALUE	9
#define	ID_REGISTER_INPUT_1	10
#define	ID_REGISTER_INPUT_3	11

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={-1, atv_IMG_ID_FS_WHITE_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, atv_IDS_NULL, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf0083d6_09c33bf={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0645bb9_2033e75={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c200af49_38a29={-1, atv_IMG_ID_FS_FACTORY_YELLOW, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c200af49_38a6952={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c21168c7_3d84551={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c21168c7_3d82ee0={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c2119915_3d843ac={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_grey, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_REGISTER_LABEL_REGISTER"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_REGISTER_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda8768_3c81b4b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_REGISTER_GROUP_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96db6_02e4ae1={{NULL, &GUID_c200af49_38a29, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_REGISTER_GROUP_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196952={{NULL, &GUID_c200af49_38a29, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_REGISTER_GROUP_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e35_1d45af1={{NULL, &GUID_c200af49_38a29, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_REGISTER_LABEL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda323b_30d1d08={{&GUID_c200af49_38a6952, &GUID_c200af49_38a6952, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_REGISTER_LABEL_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda3362_06d954={{&GUID_c2119915_3d843ac, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_REGISTER_LABEL_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4df5={{&GUID_c2119915_3d843ac, &GUID_c200af49_38a6952, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_REGISTER_LABEL_SHOW_VALUE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9517_1865062={{&GUID_c0645bb9_2033e75, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_INPUT}	"ID_REGISTER_INPUT_1"
static char GUID_c21168c7_3d87127[3+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_c21168c7_3d82934={{&GUID_c21168c7_3d84551, &GUID_c21168c7_3d82ee0, NULL, }, 1, 0, 3, GUID_c21168c7_3d87127, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_INPUT}	"ID_REGISTER_INPUT_3"
static char GUID_c2116972_3a9945[4+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_c2116972_3a9dab={{&GUID_c0645bb9_2033e75, &GUID_c21168c7_3d82ee0, NULL, }, 1, 0, 4, GUID_c2116972_3a9945, 1, '-', '*', };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_set_register_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 117, 188, 0, 485, 200, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_REGISTER_LABEL_REGISTER
	{D_CTRL_LABEL, 0, 111, 7, 426, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_REGISTER_GROUP
	{D_CTRL_GROUP, 0, 0, 37, 426, 485, 138, 30, -1, (D_FrameCtrlDescr*)&GUID_beda8768_3c81b4b, },
	// [3]ID_REGISTER_GROUP_1
	{D_CTRL_GROUP, 2, 2, 6, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96db6_02e4ae1, },
	// [4]ID_REGISTER_GROUP_2
	{D_CTRL_GROUP, 2, 2, 40, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196952, },
	// [5]ID_REGISTER_GROUP_3
	{D_CTRL_GROUP, 2, 2, 74, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e35_1d45af1, },
	// [6]ID_REGISTER_LABEL_1
	{D_CTRL_LABEL, 3, 21, 2, 0, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda323b_30d1d08, },
	// [7]ID_REGISTER_LABEL_2
	{D_CTRL_LABEL, 4, 21, 2, 0, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda3362_06d954, },
	// [8]ID_REGISTER_LABEL_3
	{D_CTRL_LABEL, 5, 21, 2, 0, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda356d_29f4df5, },
	// [9]ID_REGISTER_LABEL_SHOW_VALUE
	{D_CTRL_LABEL, 4, 281, 2, -20, 189, 26, 30, 4, (D_FrameCtrlDescr*)&GUID_bedb9517_1865062, },
	// [10]ID_REGISTER_INPUT_1
	{D_CTRL_INPUT, 3, 309, 2, -20, 100, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_c21168c7_3d82934, },
	// [11]ID_REGISTER_INPUT_3
	{D_CTRL_INPUT, 5, 309, 2, -20, 100, 26, 30, 5, (D_FrameCtrlDescr*)&GUID_c2116972_3a9dab, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	set_register_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_set_register_window[12];
D_Frame set_register_window = {
	run_ctrls_set_register_window, 
	ctrl_description_of_set_register_window, 
	set_register_window_init, 
};

