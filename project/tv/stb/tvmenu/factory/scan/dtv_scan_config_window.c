/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2015-04-24 13:30:14

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
#define	ID_CONFIG_LABEL_CONFIG	1
#define	ID_CONFIG_GROUP	2
#define	ID_CONFIG_GROUP_1	3
#define	ID_CONFIG_GROUP_3	4
#define	ID_CONFIG_GROUP_4	5
#define	ID_CONFIG_GROUP_5	6
#define	ID_CONFIG_GROUP_7	7
#define	ID_CONFIG_GROUP_8	8
#define	ID_CONFIG_GROUP_9	9
#define	ID_CONFIG_GROUP_10	10
#define	ID_CONFIG_LABEL_SIGNAL	11
#define	ID_CONFIG_SELECT_SIGNAL	12
#define	ID_CONFIG_LABEL_FREQ	13
#define	ID_CONFIG_INPUT_FREQ	14
#define	ID_CONFIG_LABEL_MODULATION	15
#define	ID_CONFIG_SELECT_MODULATION	16
#define	ID_CONFIG_LABEL_SYMBOL_RATE	17
#define	ID_CONFIG_INPUT_SYMBOL_RATE	18
#define	ID_CONFIG_LABEL_WITH_ROLE	19
#define	ID_CONFIG_SELECT_WITH_ROLE	20
#define	ID_CONFIG_LABEL_START_FREQ	21
#define	ID_CONFIG_INPUT_START_FREQ	22
#define	ID_CONFIG_LABEL_END_FREQ	23
#define	ID_CONFIG_INPUT_END_FREQ	24
#define	ID_CONFIG_LABEL_BANDWIDTH	25
#define	ID_CONFIG_INPUT_BANDWIDTH	26

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, atv_IDS_DTV_SCAN_CONFIG, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda2ec1_38a531f={-1, atv_IMG_ID_box_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08b8c93_3a9780d={-1, -1, atv_IDS_AV_SIGNAL_SELECT, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08b8c93_3a91b10={-1, -1, atv_IDS_AV_SIGNAL_SELECT, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08b8d4f_0bb927={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08b8e0c_271555f={-1, -1, atv_IDS_FREQ, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08b8ef2_00f5ae3={-1, -1, atv_IDS_MODULATION, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08b9036_3995fa9={-1, -1, atv_IDS_SYMBOL_RATE, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08b91aa_31c1b29={-1, -1, atv_IDS_BY_ROLE, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08b9272_2ce5e25={-1, -1, atv_IDS_START_FREQ, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08b93a5_07d1f53={-1, -1, atv_IDS_END_FREQ, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08b9c35_2325f21={-1, -1, atv_IDS_BANDWIDTH, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08d89da_37a7c62={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_CONFIG_LABEL_CONFIG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_CONFIG_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda8768_3c81b4b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_CONFIG_GROUP_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96c42_0ab29={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_CONFIG_GROUP_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196952={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_CONFIG_GROUP_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e35_1d45af1={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_CONFIG_GROUP_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e7a_05dbb3={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_GROUP}	"ID_CONFIG_GROUP_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96f32_37a4d06={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_GROUP}	"ID_CONFIG_GROUP_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96f4e_32c39b3={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_GROUP}	"ID_CONFIG_GROUP_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96fb4_3a96443={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_GROUP}	"ID_CONFIG_GROUP_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed970cf_2bf701f={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_CONFIG_LABEL_SIGNAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c08b8c93_3a918aa={{&GUID_c08b8c93_3a9780d, &GUID_c08b8c93_3a91b10, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_SELECT}	"ID_CONFIG_SELECT_SIGNAL"
static PREFIXCONST D_TextID POSTCONST GUID_c08b9cb8_36b43a7[]={atv_IDS_DTMB, atv_IDS_DVBC, };
static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c08b8d4f_0bb14db={{&GUID_c08b8d4f_0bb927, &GUID_c08d89da_37a7c62, NULL, }, 1, 2, GUID_c08b9cb8_36b43a7, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_CONFIG_LABEL_FREQ"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c08b8e0c_2715464={{&GUID_c08b8e0c_271555f, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_INPUT}	"ID_CONFIG_INPUT_FREQ"
static char GUID_c08b8e7c_09c2535[3+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_c08b8e7c_09cbeb={{&GUID_c08b8d4f_0bb927, &GUID_c08d89da_37a7c62, NULL, }, 1, 0, 3, GUID_c08b8e7c_09c2535, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_LABEL}	"ID_CONFIG_LABEL_MODULATION"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c08b8ef2_00f1651={{&GUID_c08b8ef2_00f5ae3, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_SELECT}	"ID_CONFIG_SELECT_MODULATION"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c08b8f9d_38a2a5a={{&GUID_c08b8d4f_0bb927, &GUID_c08d89da_37a7c62, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_CONFIG_LABEL_SYMBOL_RATE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c08b9036_3998e={{&GUID_c08b9036_3995fa9, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_INPUT}	"ID_CONFIG_INPUT_SYMBOL_RATE"
static char GUID_c08b90e2_39955cb[4+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_c08b90e2_3994023={{&GUID_c08b8d4f_0bb927, &GUID_c08d89da_37a7c62, NULL, }, 1, 0, 4, GUID_c08b90e2_39955cb, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_LABEL}	"ID_CONFIG_LABEL_WITH_ROLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c08b91aa_31c5c75={{&GUID_c08b91aa_31c1b29, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_SELECT}	"ID_CONFIG_SELECT_WITH_ROLE"
static PREFIXCONST D_TextID POSTCONST GUID_c08b9cb8_36b19db[]={atv_IDS_NO, atv_IDS_YES, };
static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c08b920b_3b95293={{&GUID_c08b8d4f_0bb927, &GUID_c08d89da_37a7c62, NULL, }, 1, 2, GUID_c08b9cb8_36b19db, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_CONFIG_LABEL_START_FREQ"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c08b9272_2ce3ee4={{&GUID_c08b9272_2ce5e25, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_INPUT}	"ID_CONFIG_INPUT_START_FREQ"
static char GUID_c08b92db_3b926ec[3+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_c08b92db_3b94b1f={{&GUID_c08b8d4f_0bb927, &GUID_c08d89da_37a7c62, NULL, }, 1, 0, 3, GUID_c08b92db_3b926ec, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_LABEL}	"ID_CONFIG_LABEL_END_FREQ"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c08b93a5_07d23a6={{&GUID_c08b93a5_07d1f53, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_INPUT}	"ID_CONFIG_INPUT_END_FREQ"
static char GUID_c08b9be6_2de5543[3+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_c08b9be6_2de6046={{&GUID_c08b8d4f_0bb927, &GUID_c08d89da_37a7c62, NULL, }, 1, 0, 3, GUID_c08b9be6_2de5543, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_LABEL}	"ID_CONFIG_LABEL_BANDWIDTH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c08b9c35_23259b0={{&GUID_c08b9c35_2325f21, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_INPUT}	"ID_CONFIG_INPUT_BANDWIDTH"
static char GUID_c08d62c7_2fd390c[1+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_c08d62c7_2fdf3e={{&GUID_c08b8d4f_0bb927, &GUID_c08d89da_37a7c62, NULL, }, 1, 0, 1, GUID_c08d62c7_2fd390c, 1, '-', '*', };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_dtv_scan_config_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 485, 660, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_CONFIG_LABEL_CONFIG
	{D_CTRL_LABEL, 0, 111, 7, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_CONFIG_GROUP
	{D_CTRL_GROUP, 0, 0, 37, 20, 485, 621, 30, -1, (D_FrameCtrlDescr*)&GUID_beda8768_3c81b4b, },
	// [3]ID_CONFIG_GROUP_1
	{D_CTRL_GROUP, 2, 2, 6, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96c42_0ab29, },
	// [4]ID_CONFIG_GROUP_3
	{D_CTRL_GROUP, 2, 2, 74, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196952, },
	// [5]ID_CONFIG_GROUP_4
	{D_CTRL_GROUP, 2, 2, 108, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e35_1d45af1, },
	// [6]ID_CONFIG_GROUP_5
	{D_CTRL_GROUP, 2, 2, 142, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e7a_05dbb3, },
	// [7]ID_CONFIG_GROUP_7
	{D_CTRL_GROUP, 2, 2, 210, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96f32_37a4d06, },
	// [8]ID_CONFIG_GROUP_8
	{D_CTRL_GROUP, 2, 2, 244, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96f4e_32c39b3, },
	// [9]ID_CONFIG_GROUP_9
	{D_CTRL_GROUP, 2, 2, 278, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96fb4_3a96443, },
	// [10]ID_CONFIG_GROUP_10
	{D_CTRL_GROUP, 2, 2, 312, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed970cf_2bf701f, },
	// [11]ID_CONFIG_LABEL_SIGNAL
	{D_CTRL_LABEL, 3, 21, 2, -20, 223, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c08b8c93_3a918aa, },
	// [12]ID_CONFIG_SELECT_SIGNAL
	{D_CTRL_SELECT, 3, 309, 2, -20, 100, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_c08b8d4f_0bb14db, },
	// [13]ID_CONFIG_LABEL_FREQ
	{D_CTRL_LABEL, 4, 21, 2, -20, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c08b8e0c_2715464, },
	// [14]ID_CONFIG_INPUT_FREQ
	{D_CTRL_INPUT, 4, 309, 2, -20, 100, 26, 30, 4, (D_FrameCtrlDescr*)&GUID_c08b8e7c_09cbeb, },
	// [15]ID_CONFIG_LABEL_MODULATION
	{D_CTRL_LABEL, 5, 21, 2, -20, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c08b8ef2_00f1651, },
	// [16]ID_CONFIG_SELECT_MODULATION
	{D_CTRL_SELECT, 5, 309, 2, -20, 100, 26, 30, 5, (D_FrameCtrlDescr*)&GUID_c08b8f9d_38a2a5a, },
	// [17]ID_CONFIG_LABEL_SYMBOL_RATE
	{D_CTRL_LABEL, 6, 21, 2, -20, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c08b9036_3998e, },
	// [18]ID_CONFIG_INPUT_SYMBOL_RATE
	{D_CTRL_INPUT, 6, 309, 2, -20, 100, 26, 30, 6, (D_FrameCtrlDescr*)&GUID_c08b90e2_3994023, },
	// [19]ID_CONFIG_LABEL_WITH_ROLE
	{D_CTRL_LABEL, 7, 21, 2, -20, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c08b91aa_31c5c75, },
	// [20]ID_CONFIG_SELECT_WITH_ROLE
	{D_CTRL_SELECT, 7, 309, 2, -20, 100, 26, 30, 7, (D_FrameCtrlDescr*)&GUID_c08b920b_3b95293, },
	// [21]ID_CONFIG_LABEL_START_FREQ
	{D_CTRL_LABEL, 8, 21, 2, -20, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c08b9272_2ce3ee4, },
	// [22]ID_CONFIG_INPUT_START_FREQ
	{D_CTRL_INPUT, 8, 309, 2, -20, 100, 26, 30, 8, (D_FrameCtrlDescr*)&GUID_c08b92db_3b94b1f, },
	// [23]ID_CONFIG_LABEL_END_FREQ
	{D_CTRL_LABEL, 9, 21, 2, -20, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c08b93a5_07d23a6, },
	// [24]ID_CONFIG_INPUT_END_FREQ
	{D_CTRL_INPUT, 9, 309, 2, -20, 100, 26, 30, 9, (D_FrameCtrlDescr*)&GUID_c08b9be6_2de6046, },
	// [25]ID_CONFIG_LABEL_BANDWIDTH
	{D_CTRL_LABEL, 10, 21, 2, -20, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c08b9c35_23259b0, },
	// [26]ID_CONFIG_INPUT_BANDWIDTH
	{D_CTRL_INPUT, 10, 309, 2, -20, 100, 26, 30, 10, (D_FrameCtrlDescr*)&GUID_c08d62c7_2fdf3e, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	dtv_scan_config_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_dtv_scan_config_window[27];
D_Frame dtv_scan_config_window = {
	run_ctrls_dtv_scan_config_window, 
	ctrl_description_of_dtv_scan_config_window, 
	dtv_scan_config_window_init, 
};

