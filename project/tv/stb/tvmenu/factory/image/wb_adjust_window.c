/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2015-04-24 13:30:04

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
#define	ID_WB_ADJUST_LABEL_WB_ADJUST	1
#define	ID_WB_ADJUST_GROUP	2
#define	ID_WB_ADJUST_GROUP_1	3
#define	ID_WB_ADJUST_GROUP_3	4
#define	ID_WB_ADJUST_GROUP_4	5
#define	ID_WB_ADJUST_GROUP_5	6
#define	ID_WB_ADJUST_GROUP_6	7
#define	ID_WB_ADJUST_GROUP_8	8
#define	ID_WB_ADJUST_GROUP_9	9
#define	ID_WB_ADJUST_GROUP_10	10
#define	ID_WB_ADJUST_GROUP_11	11
#define	ID_WB_ADJUST_GROUP_12	12
#define	ID_WB_ADJUST_BUTTON_1	13
#define	ID_WB_ADJUST_LABEL_1	14
#define	ID_WB_ADJUST_BUTTON_3	15
#define	ID_WB_ADJUST_BUTTON_4	16
#define	ID_WB_ADJUST_BUTTON_5	17
#define	ID_WB_ADJUST_BUTTON_6	18
#define	ID_WB_ADJUST_BUTTON_8	19
#define	ID_WB_ADJUST_BUTTON_9	20
#define	ID_WB_ADJUST_BUTTON_10	21
#define	ID_WB_ADJUST_LABEL_10	22
#define	ID_WB_ADJUST_BUTTON_11	23
#define	ID_WB_ADJUST_LABEL_11	24
#define	ID_WB_ADJUST_LABEL_3	25
#define	ID_WB_ADJUST_LABEL_4	26
#define	ID_WB_ADJUST_LABEL_5	27
#define	ID_WB_ADJUST_LABEL_6	28
#define	ID_WB_ADJUST_LABEL_8	29
#define	ID_WB_ADJUST_LABEL_9	30
#define	ID_WB_ADJUST_BUTTON_12	31
#define	ID_WB_ADJUST_LABEL_12	32

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, atv_IDS_WB_ADJUST, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_128645b={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_1282337={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda2ec1_38a531f={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedaa198_08c7e87={-1, atv_IMG_ID_box_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee176ca_34b6e5d={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_WB_ADJUST_LABEL_WB_ADJUST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_WB_ADJUST_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda8768_3c81b4b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_WB_ADJUST_GROUP_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96c42_0ab29={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_WB_ADJUST_GROUP_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196952={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_WB_ADJUST_GROUP_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e35_1d45af1={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_WB_ADJUST_GROUP_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e7a_05dbb3={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_GROUP}	"ID_WB_ADJUST_GROUP_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96ed6_1387e87={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_GROUP}	"ID_WB_ADJUST_GROUP_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96f4e_32c39b3={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_GROUP}	"ID_WB_ADJUST_GROUP_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96fb4_3a96443={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_GROUP}	"ID_WB_ADJUST_GROUP_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed970cf_2bf701f={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_GROUP}	"ID_WB_ADJUST_GROUP_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed97152_1e44509={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_GROUP}	"ID_WB_ADJUST_GROUP_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf024d8d_0ea6710={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_BUTTON}	"ID_WB_ADJUST_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed9bb91_128666e={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_WB_ADJUST_LABEL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda2ec1_38a6275={{&GUID_beda2ec1_38a531f, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_BUTTON}	"ID_WB_ADJUST_BUTTON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda3362_06d954={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_BUTTON}	"ID_WB_ADJUST_BUTTON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4df5={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_BUTTON}	"ID_WB_ADJUST_BUTTON_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda35d1_34b101a={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_BUTTON}	"ID_WB_ADJUST_BUTTON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4de4_07d2268={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_BUTTON}	"ID_WB_ADJUST_BUTTON_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4ec2_07db85={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_BUTTON}	"ID_WB_ADJUST_BUTTON_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4f20_2611fa5={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_BUTTON}	"ID_WB_ADJUST_BUTTON_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4fdd_290763c={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_LABEL}	"ID_WB_ADJUST_LABEL_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda5102_21348ee={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_BUTTON}	"ID_WB_ADJUST_BUTTON_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda522d_186323={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_LABEL}	"ID_WB_ADJUST_LABEL_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda52ef_27142b7={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_LABEL}	"ID_WB_ADJUST_LABEL_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9517_1865062={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_LABEL}	"ID_WB_ADJUST_LABEL_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb957c_06df9e={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_LABEL}	"ID_WB_ADJUST_LABEL_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb95a2_1199c5={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [28]{D_CTRL_LABEL}	"ID_WB_ADJUST_LABEL_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb95f1_2801033={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [29]{D_CTRL_LABEL}	"ID_WB_ADJUST_LABEL_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9793_1a5484d={{&GUID_bee176ca_34b6e5d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [30]{D_CTRL_LABEL}	"ID_WB_ADJUST_LABEL_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb97e2_3b92f2f={{&GUID_bee176ca_34b6e5d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [31]{D_CTRL_BUTTON}	"ID_WB_ADJUST_BUTTON_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf024de3_10947ae={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [32]{D_CTRL_LABEL}	"ID_WB_ADJUST_LABEL_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf024e09_33ceea={{&GUID_bee176ca_34b6e5d, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_wb_adjust_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 485, 660, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_WB_ADJUST_LABEL_WB_ADJUST
	{D_CTRL_LABEL, 0, 111, 7, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_WB_ADJUST_GROUP
	{D_CTRL_GROUP, 0, 0, 37, 20, 485, 621, 30, -1, (D_FrameCtrlDescr*)&GUID_beda8768_3c81b4b, },
	// [3]ID_WB_ADJUST_GROUP_1
	{D_CTRL_GROUP, 2, 2, 6, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96c42_0ab29, },
	// [4]ID_WB_ADJUST_GROUP_3
	{D_CTRL_GROUP, 2, 2, 74, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196952, },
	// [5]ID_WB_ADJUST_GROUP_4
	{D_CTRL_GROUP, 2, 2, 108, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e35_1d45af1, },
	// [6]ID_WB_ADJUST_GROUP_5
	{D_CTRL_GROUP, 2, 2, 142, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e7a_05dbb3, },
	// [7]ID_WB_ADJUST_GROUP_6
	{D_CTRL_GROUP, 2, 2, 176, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96ed6_1387e87, },
	// [8]ID_WB_ADJUST_GROUP_8
	{D_CTRL_GROUP, 2, 2, 244, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96f4e_32c39b3, },
	// [9]ID_WB_ADJUST_GROUP_9
	{D_CTRL_GROUP, 2, 2, 278, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96fb4_3a96443, },
	// [10]ID_WB_ADJUST_GROUP_10
	{D_CTRL_GROUP, 2, 2, 312, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed970cf_2bf701f, },
	// [11]ID_WB_ADJUST_GROUP_11
	{D_CTRL_GROUP, 2, 2, 346, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed97152_1e44509, },
	// [12]ID_WB_ADJUST_GROUP_12
	{D_CTRL_GROUP, 2, 2, 380, 0, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bf024d8d_0ea6710, },
	// [13]ID_WB_ADJUST_BUTTON_1
	{D_CTRL_BUTTON, 3, 21, 2, 0, 180, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_bed9bb91_128666e, },
	// [14]ID_WB_ADJUST_LABEL_1
	{D_CTRL_LABEL, 3, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda2ec1_38a6275, },
	// [15]ID_WB_ADJUST_BUTTON_3
	{D_CTRL_BUTTON, 4, 21, 2, 0, 201, 26, 30, 4, (D_FrameCtrlDescr*)&GUID_beda3362_06d954, },
	// [16]ID_WB_ADJUST_BUTTON_4
	{D_CTRL_BUTTON, 5, 21, 2, 0, 180, 26, 30, 5, (D_FrameCtrlDescr*)&GUID_beda356d_29f4df5, },
	// [17]ID_WB_ADJUST_BUTTON_5
	{D_CTRL_BUTTON, 6, 21, 2, 0, 180, 26, 30, 6, (D_FrameCtrlDescr*)&GUID_beda35d1_34b101a, },
	// [18]ID_WB_ADJUST_BUTTON_6
	{D_CTRL_BUTTON, 7, 21, 2, 0, 180, 26, 30, 7, (D_FrameCtrlDescr*)&GUID_beda4de4_07d2268, },
	// [19]ID_WB_ADJUST_BUTTON_8
	{D_CTRL_BUTTON, 8, 21, 2, 0, 180, 26, 30, 8, (D_FrameCtrlDescr*)&GUID_beda4ec2_07db85, },
	// [20]ID_WB_ADJUST_BUTTON_9
	{D_CTRL_BUTTON, 9, 21, 2, 0, 180, 26, 30, 9, (D_FrameCtrlDescr*)&GUID_beda4f20_2611fa5, },
	// [21]ID_WB_ADJUST_BUTTON_10
	{D_CTRL_BUTTON, 10, 21, 2, 0, 180, 26, 30, 10, (D_FrameCtrlDescr*)&GUID_beda4fdd_290763c, },
	// [22]ID_WB_ADJUST_LABEL_10
	{D_CTRL_LABEL, 10, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda5102_21348ee, },
	// [23]ID_WB_ADJUST_BUTTON_11
	{D_CTRL_BUTTON, 11, 21, 2, 0, 180, 26, 30, 11, (D_FrameCtrlDescr*)&GUID_beda522d_186323, },
	// [24]ID_WB_ADJUST_LABEL_11
	{D_CTRL_LABEL, 11, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda52ef_27142b7, },
	// [25]ID_WB_ADJUST_LABEL_3
	{D_CTRL_LABEL, 4, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9517_1865062, },
	// [26]ID_WB_ADJUST_LABEL_4
	{D_CTRL_LABEL, 5, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb957c_06df9e, },
	// [27]ID_WB_ADJUST_LABEL_5
	{D_CTRL_LABEL, 6, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb95a2_1199c5, },
	// [28]ID_WB_ADJUST_LABEL_6
	{D_CTRL_LABEL, 7, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb95f1_2801033, },
	// [29]ID_WB_ADJUST_LABEL_8
	{D_CTRL_LABEL, 8, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9793_1a5484d, },
	// [30]ID_WB_ADJUST_LABEL_9
	{D_CTRL_LABEL, 9, 309, 2, -20, 164, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb97e2_3b92f2f, },
	// [31]ID_WB_ADJUST_BUTTON_12
	{D_CTRL_BUTTON, 12, 21, 2, 0, 180, 26, 30, 12, (D_FrameCtrlDescr*)&GUID_bf024de3_10947ae, },
	// [32]ID_WB_ADJUST_LABEL_12
	{D_CTRL_LABEL, 12, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bf024e09_33ceea, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	wb_adjust_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_wb_adjust_window[33];
D_Frame wb_adjust_window = {
	run_ctrls_wb_adjust_window, 
	ctrl_description_of_wb_adjust_window, 
	wb_adjust_window_init, 
};

