/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2015-04-24 13:31:29

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-04-16 14:04:23.640

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
#define	ID_SW_INFO_LABEL_SW_INFO	1
#define	ID_SW_INFO_GROUP_1	2
#define	ID_SW_INFO_GROUP_2	3
#define	ID_SW_INFO_GROUP_3	4
#define	ID_SW_INFO_GROUP_4	5
#define	ID_SW_INFO_GROUP_5	6
#define	ID_SW_INFO_BUTTON_1	7
#define	ID_SW_INFO_LABEL_1	8
#define	ID_SW_INFO_BUTTON_2	9
#define	ID_SW_INFO_BUTTON_3	10
#define	ID_SW_INFO_BUTTON_4	11
#define	ID_SW_INFO_BUTTON_5	12
#define	ID_SW_INFO_LABEL_2	13
#define	ID_SW_INFO_LABEL_3	14
#define	ID_SW_INFO_LABEL_4	15
#define	ID_SW_INFO_LABEL_5	16
#define	ID_SW_INFO_GROUP_6	17
#define	ID_SW_INFO_BUTTON_6	18
#define	ID_SW_INFO_LABEL_6	19

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, atv_IDS_SW_INFORMATION, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_128645b={-1, -1, atv_IDS_PRODUCECOMPANY, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda2ec1_38a531f={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c05f9741_07d3d6c={-1, -1, atv_IDS_HARDWAREEDITION, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c05f9741_07d2cd6={-1, -1, atv_IDS_HARDWAREEDITION, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c05f9741_07d72ae={-1, -1, atv_IDS_SOFTWAREEDITION, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c05f9741_07d6952={-1, -1, atv_IDS_SOFTWAREEDITION, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c05f9741_07d5f90={-1, -1, atv_IDS_SERIALNUMBER, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c05f9741_07d1649={-1, -1, atv_IDS_SERIALNUMBER, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c05f9741_07d6df1={-1, -1, atv_IDS_BUILD_TIME, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c05f9741_07d5af1={-1, -1, atv_IDS_BUILD_TIME, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c05fadc0_2802cd6={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0607f2c_00f26e9={-1, -1, atv_IDS_COMPANYID, &atv_fmt_left_middle_h00_v00_single_grey, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_SW_INFO_LABEL_SW_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_SW_INFO_GROUP_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96c42_0ab29={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_SW_INFO_GROUP_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96db6_02e4ae1={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_SW_INFO_GROUP_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196952={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_SW_INFO_GROUP_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e35_1d45af1={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_SW_INFO_GROUP_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e7a_05dbb3={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_BUTTON}	"ID_SW_INFO_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed9bb91_128666e={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_128645b, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_SW_INFO_LABEL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda2ec1_38a6275={{&GUID_beda2ec1_38a531f, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_BUTTON}	"ID_SW_INFO_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda323b_30d1d08={{&GUID_c05f9741_07d3d6c, &GUID_c05f9741_07d2cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_BUTTON}	"ID_SW_INFO_BUTTON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda3362_06d954={{&GUID_c05f9741_07d72ae, &GUID_c05f9741_07d6952, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_BUTTON}	"ID_SW_INFO_BUTTON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4df5={{&GUID_c05f9741_07d5f90, &GUID_c05f9741_07d1649, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_BUTTON}	"ID_SW_INFO_BUTTON_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda35d1_34b101a={{&GUID_c05f9741_07d6df1, &GUID_c05f9741_07d5af1, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_SW_INFO_LABEL_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb946e_0ab59e={{&GUID_beda2ec1_38a531f, &GUID_c05fadc0_2802cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_SW_INFO_LABEL_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9517_1865062={{&GUID_beda2ec1_38a531f, &GUID_c05fadc0_2802cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_LABEL}	"ID_SW_INFO_LABEL_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb957c_06df9e={{&GUID_beda2ec1_38a531f, &GUID_c05fadc0_2802cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_SW_INFO_LABEL_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb95a2_1199c5={{&GUID_beda2ec1_38a531f, &GUID_c05fadc0_2802cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_GROUP}	"ID_SW_INFO_GROUP_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0607ec6_2135f90={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_BUTTON}	"ID_SW_INFO_BUTTON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0607f2c_00f41bb={{&GUID_c0607f2c_00f26e9, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_LABEL}	"ID_SW_INFO_LABEL_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0607f8f_34b2ea6={{&GUID_beda2ec1_38a531f, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_sw_information_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 485, 660, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_SW_INFO_LABEL_SW_INFO
	{D_CTRL_LABEL, 0, 111, 7, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_SW_INFO_GROUP_1
	{D_CTRL_GROUP, 0, 2, 43, 40, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96c42_0ab29, },
	// [3]ID_SW_INFO_GROUP_2
	{D_CTRL_GROUP, 0, 2, 77, 40, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96db6_02e4ae1, },
	// [4]ID_SW_INFO_GROUP_3
	{D_CTRL_GROUP, 0, 2, 111, 40, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196952, },
	// [5]ID_SW_INFO_GROUP_4
	{D_CTRL_GROUP, 0, 2, 145, 40, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e35_1d45af1, },
	// [6]ID_SW_INFO_GROUP_5
	{D_CTRL_GROUP, 0, 2, 179, 40, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e7a_05dbb3, },
	// [7]ID_SW_INFO_BUTTON_1
	{D_CTRL_BUTTON, 2, 21, 2, 0, 180, 26, 30, 2, (D_FrameCtrlDescr*)&GUID_bed9bb91_128666e, },
	// [8]ID_SW_INFO_LABEL_1
	{D_CTRL_LABEL, 2, 281, 2, 0, 187, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda2ec1_38a6275, },
	// [9]ID_SW_INFO_BUTTON_2
	{D_CTRL_BUTTON, 3, 21, 2, 0, 167, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_beda323b_30d1d08, },
	// [10]ID_SW_INFO_BUTTON_3
	{D_CTRL_BUTTON, 4, 21, 2, 0, 190, 26, 30, 4, (D_FrameCtrlDescr*)&GUID_beda3362_06d954, },
	// [11]ID_SW_INFO_BUTTON_4
	{D_CTRL_BUTTON, 5, 21, 2, 0, 180, 26, 30, 5, (D_FrameCtrlDescr*)&GUID_beda356d_29f4df5, },
	// [12]ID_SW_INFO_BUTTON_5
	{D_CTRL_BUTTON, 6, 21, 2, 0, 180, 26, 30, 6, (D_FrameCtrlDescr*)&GUID_beda35d1_34b101a, },
	// [13]ID_SW_INFO_LABEL_2
	{D_CTRL_LABEL, 3, 281, 2, -20, 187, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb946e_0ab59e, },
	// [14]ID_SW_INFO_LABEL_3
	{D_CTRL_LABEL, 4, 281, 2, -20, 187, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9517_1865062, },
	// [15]ID_SW_INFO_LABEL_4
	{D_CTRL_LABEL, 5, 281, 2, -20, 187, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb957c_06df9e, },
	// [16]ID_SW_INFO_LABEL_5
	{D_CTRL_LABEL, 6, 281, 2, -20, 187, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb95a2_1199c5, },
	// [17]ID_SW_INFO_GROUP_6
	{D_CTRL_GROUP, 0, 2, 213, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c0607ec6_2135f90, },
	// [18]ID_SW_INFO_BUTTON_6
	{D_CTRL_BUTTON, 17, 21, 2, 0, 180, 26, 30, 18, (D_FrameCtrlDescr*)&GUID_c0607f2c_00f41bb, },
	// [19]ID_SW_INFO_LABEL_6
	{D_CTRL_LABEL, 17, 281, 2, 0, 187, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c0607f8f_34b2ea6, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	sw_information_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_sw_information_window[20];
D_Frame sw_information_window = {
	run_ctrls_sw_information_window, 
	ctrl_description_of_sw_information_window, 
	sw_information_window_init, 
};

