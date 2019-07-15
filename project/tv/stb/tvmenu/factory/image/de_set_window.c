/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2015-04-24 13:28:11

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
#define	ID_DE_LABEL_DE	1
#define	ID_DE_GROUP	2
#define	ID_DE_GROUP_1	3
#define	ID_DE_GROUP_2	4
#define	ID_DE_GROUP_3	5
#define	ID_DE_GROUP_4	6
#define	ID_DE_GROUP_5	7
#define	ID_DE_GROUP_6	8
#define	ID_DE_GROUP_7	9
#define	ID_DE_GROUP_8	10
#define	ID_DE_GROUP_9	11
#define	ID_DE_GROUP_10	12
#define	ID_DE_GROUP_11	13
#define	ID_DE_GROUP_12	14
#define	ID_DE_GROUP_13	15
#define	ID_DE_GROUP_14	16
#define	ID_DE_GROUP_15	17
#define	ID_DE_GROUP_16	18
#define	ID_DE_GROUP_17	19
#define	ID_DE_BUTTON_1	20
#define	ID_DE_LABEL_1	21
#define	ID_DE_BUTTON_2	22
#define	ID_DE_BUTTON_3	23
#define	ID_DE_BUTTON_4	24
#define	ID_DE_BUTTON_5	25
#define	ID_DE_BUTTON_6	26
#define	ID_DE_BUTTON_7	27
#define	ID_DE_BUTTON_8	28
#define	ID_DE_BUTTON_9	29
#define	ID_DE_BUTTON_10	30
#define	ID_DE_LABEL_10	31
#define	ID_DE_BUTTON_11	32
#define	ID_DE_LABEL_11	33
#define	ID_DE_BUTTON_12	34
#define	ID_DE_LABEL_12	35
#define	ID_DE_BUTTON_13	36
#define	ID_DE_LABEL_13	37
#define	ID_DE_BUTTON_14	38
#define	ID_DE_LABEL_2	39
#define	ID_DE_LABEL_3	40
#define	ID_DE_LABEL_4	41
#define	ID_DE_LABEL_5	42
#define	ID_DE_LABEL_6	43
#define	ID_DE_LABEL_7	44
#define	ID_DE_LABEL_8	45
#define	ID_DE_LABEL_9	46
#define	ID_DE_LABEL_14	47
#define	ID_DE_BUTTON_15	48
#define	ID_DE_BUTTON_16	49
#define	ID_DE_BUTTON_17	50
#define	ID_DE_LABEL_15	51
#define	ID_DE_LABEL_16	52
#define	ID_DE_LABEL_17	53

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, atv_IDS_NULL, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_128645b={-1, atv_IMG_ID_box_focus, atv_IDS_NULL, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_1282337={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda2ec1_38a531f={-1, atv_IMG_ID_box_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf0083d6_09c33bf={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf0575f9_16774d={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf05af4c_01f73a4={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_grey, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_DE_LABEL_DE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_DE_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda8768_3c81b4b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_DE_GROUP_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96c42_0ab29={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_DE_GROUP_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96db6_02e4ae1={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_DE_GROUP_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196952={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_DE_GROUP_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e35_1d45af1={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_GROUP}	"ID_DE_GROUP_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e7a_05dbb3={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_GROUP}	"ID_DE_GROUP_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96ed6_1387e87={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_GROUP}	"ID_DE_GROUP_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96f32_37a4d06={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_GROUP}	"ID_DE_GROUP_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96f4e_32c39b3={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_GROUP}	"ID_DE_GROUP_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96fb4_3a96443={{NULL, &GUID_bed9bb91_128645b, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_GROUP}	"ID_DE_GROUP_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed970cf_2bf701f={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_GROUP}	"ID_DE_GROUP_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed97152_1e44509={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_GROUP}	"ID_DE_GROUP_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed97222_2906e5d={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_GROUP}	"ID_DE_GROUP_13"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed9726c_1b57f96={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_GROUP}	"ID_DE_GROUP_14"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_befe5552_213516e={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_GROUP}	"ID_DE_GROUP_15"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf049acd_399d44={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_GROUP}	"ID_DE_GROUP_16"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf049af5_05d6108={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_GROUP}	"ID_DE_GROUP_17"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf049b99_33c54f6={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_BUTTON}	"ID_DE_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed9bb91_128666e={{&GUID_bf05af4c_01f73a4, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_DE_LABEL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda2ec1_38a6275={{&GUID_bf0083d6_09c33bf, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_BUTTON}	"ID_DE_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda323b_30d1d08={{&GUID_bf05af4c_01f73a4, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_BUTTON}	"ID_DE_BUTTON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda3362_06d954={{&GUID_bf05af4c_01f73a4, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_BUTTON}	"ID_DE_BUTTON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4df5={{&GUID_bf05af4c_01f73a4, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_BUTTON}	"ID_DE_BUTTON_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda35d1_34b101a={{&GUID_bf05af4c_01f73a4, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_BUTTON}	"ID_DE_BUTTON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4de4_07d2268={{&GUID_bf05af4c_01f73a4, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_BUTTON}	"ID_DE_BUTTON_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4e3e_2225585={{&GUID_bf05af4c_01f73a4, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [28]{D_CTRL_BUTTON}	"ID_DE_BUTTON_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4ec2_07db85={{&GUID_bf05af4c_01f73a4, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [29]{D_CTRL_BUTTON}	"ID_DE_BUTTON_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4f20_2611fa5={{&GUID_bf05af4c_01f73a4, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [30]{D_CTRL_BUTTON}	"ID_DE_BUTTON_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4fdd_290763c={{&GUID_bf05af4c_01f73a4, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [31]{D_CTRL_LABEL}	"ID_DE_LABEL_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda5102_21348ee={{&GUID_bf0575f9_16774d, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [32]{D_CTRL_BUTTON}	"ID_DE_BUTTON_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda522d_186323={{&GUID_bf05af4c_01f73a4, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [33]{D_CTRL_LABEL}	"ID_DE_LABEL_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda52ef_27142b7={{&GUID_bf0575f9_16774d, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [34]{D_CTRL_BUTTON}	"ID_DE_BUTTON_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda5506_0ab50f4={{&GUID_bf05af4c_01f73a4, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [35]{D_CTRL_LABEL}	"ID_DE_LABEL_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda5565_17727bd={{&GUID_bf0575f9_16774d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [36]{D_CTRL_BUTTON}	"ID_DE_BUTTON_13"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda5612_2bf570b={{&GUID_bf05af4c_01f73a4, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [37]{D_CTRL_LABEL}	"ID_DE_LABEL_13"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda56a5_03e5e9e={{&GUID_bf0575f9_16774d, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [38]{D_CTRL_BUTTON}	"ID_DE_BUTTON_14"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_befe55cd_3c86c1c={{&GUID_bf0575f9_16774d, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [39]{D_CTRL_LABEL}	"ID_DE_LABEL_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb946e_0ab59e={{&GUID_bf0575f9_16774d, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [40]{D_CTRL_LABEL}	"ID_DE_LABEL_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9517_1865062={{&GUID_bf0575f9_16774d, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [41]{D_CTRL_LABEL}	"ID_DE_LABEL_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb957c_06df9e={{&GUID_bf0575f9_16774d, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [42]{D_CTRL_LABEL}	"ID_DE_LABEL_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb95a2_1199c5={{&GUID_bf0575f9_16774d, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [43]{D_CTRL_LABEL}	"ID_DE_LABEL_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb95f1_2801033={{&GUID_bf0575f9_16774d, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [44]{D_CTRL_LABEL}	"ID_DE_LABEL_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9662_30d2cb6={{&GUID_bf0575f9_16774d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [45]{D_CTRL_LABEL}	"ID_DE_LABEL_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9793_1a5484d={{&GUID_bf0575f9_16774d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [46]{D_CTRL_LABEL}	"ID_DE_LABEL_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb97e2_3b92f2f={{&GUID_bf0575f9_16774d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [47]{D_CTRL_LABEL}	"ID_DE_LABEL_14"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_befe5773_35b2421={{&GUID_bf0575f9_16774d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [48]{D_CTRL_BUTTON}	"ID_DE_BUTTON_15"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf049c18_261359a={{&GUID_bf0575f9_16774d, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [49]{D_CTRL_BUTTON}	"ID_DE_BUTTON_16"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf049c6a_1a52bf4={{&GUID_bf0575f9_16774d, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [50]{D_CTRL_BUTTON}	"ID_DE_BUTTON_17"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf049c90_26161b={{&GUID_bf0575f9_16774d, &GUID_bf0083d6_09c33bf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [51]{D_CTRL_LABEL}	"ID_DE_LABEL_15"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf049cf3_1967325={{&GUID_bf0575f9_16774d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [52]{D_CTRL_LABEL}	"ID_DE_LABEL_16"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf049d33_222364b={{&GUID_bf0575f9_16774d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [53]{D_CTRL_LABEL}	"ID_DE_LABEL_17"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf049d47_2ee1549={{&GUID_bf0575f9_16774d, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_de_set_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 485, 660, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_DE_LABEL_DE
	{D_CTRL_LABEL, 0, 111, 7, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_DE_GROUP
	{D_CTRL_GROUP, 0, 0, 37, 20, 485, 621, 30, -1, (D_FrameCtrlDescr*)&GUID_beda8768_3c81b4b, },
	// [3]ID_DE_GROUP_1
	{D_CTRL_GROUP, 2, 2, 6, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96c42_0ab29, },
	// [4]ID_DE_GROUP_2
	{D_CTRL_GROUP, 2, 2, 40, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96db6_02e4ae1, },
	// [5]ID_DE_GROUP_3
	{D_CTRL_GROUP, 2, 2, 74, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196952, },
	// [6]ID_DE_GROUP_4
	{D_CTRL_GROUP, 2, 2, 108, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e35_1d45af1, },
	// [7]ID_DE_GROUP_5
	{D_CTRL_GROUP, 2, 2, 142, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e7a_05dbb3, },
	// [8]ID_DE_GROUP_6
	{D_CTRL_GROUP, 2, 2, 176, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96ed6_1387e87, },
	// [9]ID_DE_GROUP_7
	{D_CTRL_GROUP, 2, 2, 210, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96f32_37a4d06, },
	// [10]ID_DE_GROUP_8
	{D_CTRL_GROUP, 2, 2, 244, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96f4e_32c39b3, },
	// [11]ID_DE_GROUP_9
	{D_CTRL_GROUP, 2, 2, 278, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96fb4_3a96443, },
	// [12]ID_DE_GROUP_10
	{D_CTRL_GROUP, 2, 2, 312, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed970cf_2bf701f, },
	// [13]ID_DE_GROUP_11
	{D_CTRL_GROUP, 2, 2, 346, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed97152_1e44509, },
	// [14]ID_DE_GROUP_12
	{D_CTRL_GROUP, 2, 2, 380, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed97222_2906e5d, },
	// [15]ID_DE_GROUP_13
	{D_CTRL_GROUP, 2, 2, 414, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed9726c_1b57f96, },
	// [16]ID_DE_GROUP_14
	{D_CTRL_GROUP, 2, 2, 448, 0, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_befe5552_213516e, },
	// [17]ID_DE_GROUP_15
	{D_CTRL_GROUP, 2, 2, 482, 0, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bf049acd_399d44, },
	// [18]ID_DE_GROUP_16
	{D_CTRL_GROUP, 2, 2, 516, 0, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bf049af5_05d6108, },
	// [19]ID_DE_GROUP_17
	{D_CTRL_GROUP, 2, 2, 550, 0, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bf049b99_33c54f6, },
	// [20]ID_DE_BUTTON_1
	{D_CTRL_BUTTON, 3, 21, 2, 0, 180, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_bed9bb91_128666e, },
	// [21]ID_DE_LABEL_1
	{D_CTRL_LABEL, 3, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda2ec1_38a6275, },
	// [22]ID_DE_BUTTON_2
	{D_CTRL_BUTTON, 4, 21, 2, 0, 180, 26, 30, 4, (D_FrameCtrlDescr*)&GUID_beda323b_30d1d08, },
	// [23]ID_DE_BUTTON_3
	{D_CTRL_BUTTON, 5, 21, 2, 0, 180, 26, 30, 5, (D_FrameCtrlDescr*)&GUID_beda3362_06d954, },
	// [24]ID_DE_BUTTON_4
	{D_CTRL_BUTTON, 6, 21, 2, 0, 180, 26, 30, 6, (D_FrameCtrlDescr*)&GUID_beda356d_29f4df5, },
	// [25]ID_DE_BUTTON_5
	{D_CTRL_BUTTON, 7, 21, 2, 0, 180, 26, 30, 7, (D_FrameCtrlDescr*)&GUID_beda35d1_34b101a, },
	// [26]ID_DE_BUTTON_6
	{D_CTRL_BUTTON, 8, 21, 2, 0, 180, 26, 30, 8, (D_FrameCtrlDescr*)&GUID_beda4de4_07d2268, },
	// [27]ID_DE_BUTTON_7
	{D_CTRL_BUTTON, 9, 21, 2, 0, 180, 26, 30, 9, (D_FrameCtrlDescr*)&GUID_beda4e3e_2225585, },
	// [28]ID_DE_BUTTON_8
	{D_CTRL_BUTTON, 10, 21, 2, 0, 180, 26, 30, 10, (D_FrameCtrlDescr*)&GUID_beda4ec2_07db85, },
	// [29]ID_DE_BUTTON_9
	{D_CTRL_BUTTON, 11, 21, 2, 0, 180, 26, 30, 11, (D_FrameCtrlDescr*)&GUID_beda4f20_2611fa5, },
	// [30]ID_DE_BUTTON_10
	{D_CTRL_BUTTON, 12, 21, 2, 0, 180, 26, 30, 12, (D_FrameCtrlDescr*)&GUID_beda4fdd_290763c, },
	// [31]ID_DE_LABEL_10
	{D_CTRL_LABEL, 12, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda5102_21348ee, },
	// [32]ID_DE_BUTTON_11
	{D_CTRL_BUTTON, 13, 21, 2, 0, 180, 26, 30, 13, (D_FrameCtrlDescr*)&GUID_beda522d_186323, },
	// [33]ID_DE_LABEL_11
	{D_CTRL_LABEL, 13, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda52ef_27142b7, },
	// [34]ID_DE_BUTTON_12
	{D_CTRL_BUTTON, 14, 21, 2, 0, 180, 26, 30, 14, (D_FrameCtrlDescr*)&GUID_beda5506_0ab50f4, },
	// [35]ID_DE_LABEL_12
	{D_CTRL_LABEL, 14, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda5565_17727bd, },
	// [36]ID_DE_BUTTON_13
	{D_CTRL_BUTTON, 15, 21, 2, 0, 180, 26, 30, 15, (D_FrameCtrlDescr*)&GUID_beda5612_2bf570b, },
	// [37]ID_DE_LABEL_13
	{D_CTRL_LABEL, 15, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda56a5_03e5e9e, },
	// [38]ID_DE_BUTTON_14
	{D_CTRL_BUTTON, 16, 21, 2, 0, 180, 26, 30, 16, (D_FrameCtrlDescr*)&GUID_befe55cd_3c86c1c, },
	// [39]ID_DE_LABEL_2
	{D_CTRL_LABEL, 4, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb946e_0ab59e, },
	// [40]ID_DE_LABEL_3
	{D_CTRL_LABEL, 5, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9517_1865062, },
	// [41]ID_DE_LABEL_4
	{D_CTRL_LABEL, 6, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb957c_06df9e, },
	// [42]ID_DE_LABEL_5
	{D_CTRL_LABEL, 7, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb95a2_1199c5, },
	// [43]ID_DE_LABEL_6
	{D_CTRL_LABEL, 8, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb95f1_2801033, },
	// [44]ID_DE_LABEL_7
	{D_CTRL_LABEL, 9, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9662_30d2cb6, },
	// [45]ID_DE_LABEL_8
	{D_CTRL_LABEL, 10, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9793_1a5484d, },
	// [46]ID_DE_LABEL_9
	{D_CTRL_LABEL, 11, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb97e2_3b92f2f, },
	// [47]ID_DE_LABEL_14
	{D_CTRL_LABEL, 16, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_befe5773_35b2421, },
	// [48]ID_DE_BUTTON_15
	{D_CTRL_BUTTON, 17, 21, 2, 0, 180, 26, 30, 17, (D_FrameCtrlDescr*)&GUID_bf049c18_261359a, },
	// [49]ID_DE_BUTTON_16
	{D_CTRL_BUTTON, 18, 21, 2, 0, 180, 26, 30, 18, (D_FrameCtrlDescr*)&GUID_bf049c6a_1a52bf4, },
	// [50]ID_DE_BUTTON_17
	{D_CTRL_BUTTON, 19, 21, 2, 0, 180, 26, 30, 19, (D_FrameCtrlDescr*)&GUID_bf049c90_26161b, },
	// [51]ID_DE_LABEL_15
	{D_CTRL_LABEL, 17, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bf049cf3_1967325, },
	// [52]ID_DE_LABEL_16
	{D_CTRL_LABEL, 18, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bf049d33_222364b, },
	// [53]ID_DE_LABEL_17
	{D_CTRL_LABEL, 19, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bf049d47_2ee1549, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	de_set_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_de_set_window[54];
D_Frame de_set_window = {
	run_ctrls_de_set_window, 
	ctrl_description_of_de_set_window, 
	de_set_window_init, 
};

