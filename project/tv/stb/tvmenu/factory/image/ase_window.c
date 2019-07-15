/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2015-04-24 13:27:29

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
#define	ID_ASE_LABEL_ASE	1
#define	ID_ASE_GROUP	2
#define	ID_ASE_GROUP_1	3
#define	ID_ASE_GROUP_2	4
#define	ID_ASE_GROUP_3	5
#define	ID_ASE_GROUP_4	6
#define	ID_ASE_GROUP_5	7
#define	ID_ASE_GROUP_6	8
#define	ID_ASE_GROUP_7	9
#define	ID_ASE_BUTTON_1	10
#define	ID_ASE_LABEL_1	11
#define	ID_ASE_BUTTON_2	12
#define	ID_ASE_BUTTON_3	13
#define	ID_ASE_BUTTON_4	14
#define	ID_ASE_BUTTON_5	15
#define	ID_ASE_BUTTON_6	16
#define	ID_ASE_BUTTON_7	17
#define	ID_ASE_LABEL_2	18
#define	ID_ASE_LABEL_3	19
#define	ID_ASE_LABEL_4	20
#define	ID_ASE_LABEL_5	21
#define	ID_ASE_LABEL_6	22
#define	ID_ASE_LABEL_7	23

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, atv_IDS_NULL, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_128645b={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_1282337={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda2ec1_38a531f={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedaa198_08c7e87={-1, atv_IMG_ID_box_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1520670_1b5153c={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_ASE_LABEL_ASE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_ASE_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda8768_3c81b4b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_ASE_GROUP_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96c42_0ab29={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_ASE_GROUP_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96db6_02e4ae1={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_ASE_GROUP_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196952={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_ASE_GROUP_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e35_1d45af1={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_GROUP}	"ID_ASE_GROUP_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e7a_05dbb3={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_GROUP}	"ID_ASE_GROUP_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96ed6_1387e87={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_GROUP}	"ID_ASE_GROUP_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96f32_37a4d06={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_BUTTON}	"ID_ASE_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed9bb91_128666e={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_ASE_LABEL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda2ec1_38a6275={{&GUID_beda2ec1_38a531f, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_BUTTON}	"ID_ASE_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda323b_30d1d08={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_BUTTON}	"ID_ASE_BUTTON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda3362_06d954={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_BUTTON}	"ID_ASE_BUTTON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4df5={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_BUTTON}	"ID_ASE_BUTTON_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda35d1_34b101a={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_BUTTON}	"ID_ASE_BUTTON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4de4_07d2268={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_BUTTON}	"ID_ASE_BUTTON_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4e3e_2225585={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_LABEL}	"ID_ASE_LABEL_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb946e_0ab59e={{&GUID_c1520670_1b5153c, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_LABEL}	"ID_ASE_LABEL_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9517_1865062={{&GUID_c1520670_1b5153c, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_LABEL}	"ID_ASE_LABEL_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb957c_06df9e={{&GUID_c1520670_1b5153c, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_ASE_LABEL_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb95a2_1199c5={{&GUID_c1520670_1b5153c, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_LABEL}	"ID_ASE_LABEL_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb95f1_2801033={{&GUID_c1520670_1b5153c, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_LABEL}	"ID_ASE_LABEL_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9662_30d2cb6={{&GUID_c1520670_1b5153c, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_ase_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 485, 660, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_ASE_LABEL_ASE
	{D_CTRL_LABEL, 0, 111, 7, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_ASE_GROUP
	{D_CTRL_GROUP, 0, 0, 37, 20, 485, 621, 30, -1, (D_FrameCtrlDescr*)&GUID_beda8768_3c81b4b, },
	// [3]ID_ASE_GROUP_1
	{D_CTRL_GROUP, 2, 2, 6, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96c42_0ab29, },
	// [4]ID_ASE_GROUP_2
	{D_CTRL_GROUP, 2, 2, 40, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96db6_02e4ae1, },
	// [5]ID_ASE_GROUP_3
	{D_CTRL_GROUP, 2, 2, 74, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196952, },
	// [6]ID_ASE_GROUP_4
	{D_CTRL_GROUP, 2, 2, 108, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e35_1d45af1, },
	// [7]ID_ASE_GROUP_5
	{D_CTRL_GROUP, 2, 2, 142, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e7a_05dbb3, },
	// [8]ID_ASE_GROUP_6
	{D_CTRL_GROUP, 2, 2, 176, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96ed6_1387e87, },
	// [9]ID_ASE_GROUP_7
	{D_CTRL_GROUP, 2, 2, 210, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96f32_37a4d06, },
	// [10]ID_ASE_BUTTON_1
	{D_CTRL_BUTTON, 3, 21, 2, 0, 236, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_bed9bb91_128666e, },
	// [11]ID_ASE_LABEL_1
	{D_CTRL_LABEL, 3, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda2ec1_38a6275, },
	// [12]ID_ASE_BUTTON_2
	{D_CTRL_BUTTON, 4, 21, 2, 0, 180, 26, 30, 4, (D_FrameCtrlDescr*)&GUID_beda323b_30d1d08, },
	// [13]ID_ASE_BUTTON_3
	{D_CTRL_BUTTON, 5, 21, 2, 0, 201, 26, 30, 5, (D_FrameCtrlDescr*)&GUID_beda3362_06d954, },
	// [14]ID_ASE_BUTTON_4
	{D_CTRL_BUTTON, 6, 21, 2, 0, 180, 26, 30, 6, (D_FrameCtrlDescr*)&GUID_beda356d_29f4df5, },
	// [15]ID_ASE_BUTTON_5
	{D_CTRL_BUTTON, 7, 21, 2, 0, 180, 26, 30, 7, (D_FrameCtrlDescr*)&GUID_beda35d1_34b101a, },
	// [16]ID_ASE_BUTTON_6
	{D_CTRL_BUTTON, 8, 21, 2, 0, 180, 26, 30, 8, (D_FrameCtrlDescr*)&GUID_beda4de4_07d2268, },
	// [17]ID_ASE_BUTTON_7
	{D_CTRL_BUTTON, 9, 21, 2, 0, 180, 26, 30, 9, (D_FrameCtrlDescr*)&GUID_beda4e3e_2225585, },
	// [18]ID_ASE_LABEL_2
	{D_CTRL_LABEL, 4, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb946e_0ab59e, },
	// [19]ID_ASE_LABEL_3
	{D_CTRL_LABEL, 5, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9517_1865062, },
	// [20]ID_ASE_LABEL_4
	{D_CTRL_LABEL, 6, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb957c_06df9e, },
	// [21]ID_ASE_LABEL_5
	{D_CTRL_LABEL, 7, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb95a2_1199c5, },
	// [22]ID_ASE_LABEL_6
	{D_CTRL_LABEL, 8, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb95f1_2801033, },
	// [23]ID_ASE_LABEL_7
	{D_CTRL_LABEL, 9, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9662_30d2cb6, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	ase_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_ase_window[24];
D_Frame ase_window = {
	run_ctrls_ase_window, 
	ctrl_description_of_ase_window, 
	ase_window_init, 
};

