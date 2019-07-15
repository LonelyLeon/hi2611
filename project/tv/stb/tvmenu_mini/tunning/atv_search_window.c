/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2017-07-27 13:24:49

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-07-18 16:19:49.390

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
#define	ID_SEARCH_LABLE_TITLE	1
#define	ID_SEARCH_GROUP_BG	2
#define	ID_SEARCH_BUTTON_FUN1	3
#define	ID_SEARCH_LABLE_MANUAL	4
#define	ID_SEARCH_LABLE_LEFT1	5
#define	ID_SEARCH_LABLE_MANUAL_TEXT	6
#define	ID_SEARCH_LABLE_MHZ1	7
#define	ID_SEARCH_LABLE_RIGHT1	8
#define	ID_SEARCH_BUTTON_FUN2	9
#define	ID_SEARCH_LABLE_TUNE	10
#define	ID_SEARCH_LABLE_LEFT2	11
#define	ID_SEARCH_LABLE_TUNE_TEXT2	12
#define	ID_SEARCH_LABLE_MHZ2	13
#define	ID_SEARCH_LABLE_RIGHT2	14
#define	ID_SEARCH_GROUP_FUN3	15
#define	ID_SEARCH_LABLE_NP	16
#define	ID_SEARCH_LABLE_LEFT3	17
#define	ID_SEARCH_SELECT_NP	18
#define	ID_SEARCH_LABLE_RIGHT3	19
#define	ID_SEARCH_GROUP_FUN4	20
#define	ID_SEARCH_LABLE_VOICE	21
#define	ID_SEARCH_LABLE_LEFT4	22
#define	ID_SEARCH_SECLECT_VOICE	23
#define	ID_SEARCH_LABLE_RIGHT4	24
#define	ID_SEARCH_GROUP_FUN5	25
#define	ID_SEARCH_LABLE_SKIP	26
#define	ID_SEARCH_LABLE_LEFT5	27
#define	ID_SEARCH_SELECT_ONOFF	28
#define	ID_SEARCH_LABLE_RIGHT5	29

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a176ab_2bf2b51={-1, -1, atv_IDS_PROGRAM_EDIT, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a18ed9_05d3771={-1, atv_IMG_ID_sub_menu_direc_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a1920b_07d6cde={-1, atv_IMG_ID_sub_menu_direc_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b628f2_29f2218={-1, -1, atv_IDS_MANUAL_SEARCH, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b64a5d_167298a={-1, atv_IMG_ID_FS_WHITE_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b64aec_33c46ad={-1, atv_IMG_ID_FS_BUTTON_GRAY, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b64aec_33c2402={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bc5431_1b57b6d={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bc5431_1b53dd9={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bc5431_1b55f81={-1, -1, atv_IDS_FINE_TUNE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bc5431_1b57625={-1, -1, atv_IDS_COLOR_SYSTEM, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bc5431_1b550a4={-1, -1, atv_IDS_SOUND_SYSTEM, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bc5431_1b512a3={-1, -1, atv_IDS_SKIP, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c594374e_2904ae1={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{&GUID_c4b64a5d_167298a, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a176ab_2bf43a5={{&GUID_c4a176ab_2bf2b51, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_SEARCH_GROUP_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a175f3_0fa6be={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_SEARCH_BUTTON_FUN1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b64aec_33c5e3={{&GUID_c4b64aec_33c46ad, &GUID_c4b64aec_33c2402, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_MANUAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a18c99_2af7d88={{&GUID_c4b628f2_29f2218, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_LEFT1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a18ed9_05d1733={{&GUID_c4a18ed9_05d3771, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_MANUAL_TEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b64f1f_35b7033={{&GUID_c4bc5431_1b57b6d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_MHZ1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a19143_177196f={{&GUID_c4bc5431_1b53dd9, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_RIGHT1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1920b_07d5c47={{&GUID_c4a1920b_07d6cde, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_BUTTON}	"ID_SEARCH_BUTTON_FUN2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b64b99_04e5dfc={{&GUID_c4b64aec_33c46ad, &GUID_c4b64aec_33c2402, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_TUNE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1986c_02e467f={{&GUID_c4bc5431_1b55f81, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_LEFT2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1b15d_1674e01={{&GUID_c4a18ed9_05d3771, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_TUNE_TEXT2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b6509f_1483393={{&GUID_c4bc5431_1b57b6d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_MHZ2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1b3a1_0ea7e59={{&GUID_c594374e_2904ae1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_RIGHT2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1b423_0cb54ab={{&GUID_c4a1920b_07d6cde, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_GROUP}	"ID_SEARCH_GROUP_FUN3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b64c0e_1d42a6d={{&GUID_c4b64aec_33c46ad, &GUID_c4b64aec_33c2402, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_NP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1bab7_242c0b={{&GUID_c4bc5431_1b57625, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_LEFT3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1bdc7_03e841={{&GUID_c4a18ed9_05d3771, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_SELECT}	"ID_SEARCH_SELECT_NP"
static PREFIXCONST D_TextID POSTCONST GUID_c58f8f70_16770ea[]={atv_IDS_SEARCH_PAL, atv_IDS_SEARCH_NTSC, };
static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c4a1bf17_36b75d0={{&GUID_c4bc5431_1b57b6d, NULL, NULL, }, 1, 2, GUID_c58f8f70_16770ea, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_RIGHT3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1c0fd_2ce2794={{&GUID_c4a1920b_07d6cde, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_GROUP}	"ID_SEARCH_GROUP_FUN4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b64c74_2425acc={{&GUID_c4b64aec_33c46ad, &GUID_c4b64aec_33c2402, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_VOICE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1c293_1672e99={{&GUID_c4bc5431_1b550a4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_LEFT4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a210e8_1a51f60={{&GUID_c4a18ed9_05d3771, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_SELECT}	"ID_SEARCH_SECLECT_VOICE"
static PREFIXCONST D_TextID POSTCONST GUID_c58f8f70_16722a3[]={atv_IDS_SEARCH_BG, atv_IDS_SEARCH_DK, atv_IDS_SEARCH_I, atv_IDS_SEARCH_M, };
static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c4a21247_1b51a28={{&GUID_c4bc5431_1b57b6d, NULL, NULL, }, 1, 4, GUID_c58f8f70_16722a3, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_RIGHT4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a222f6_261627e={{&GUID_c4a1920b_07d6cde, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_GROUP}	"ID_SEARCH_GROUP_FUN5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b64ce4_1576b75={{&GUID_c4b64aec_33c46ad, &GUID_c4b64aec_33c2402, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_SKIP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a2241a_1f45ea4={{&GUID_c4bc5431_1b512a3, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_LEFT5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a224f7_32c6b9c={{&GUID_c4a18ed9_05d3771, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [28]{D_CTRL_SELECT}	"ID_SEARCH_SELECT_ONOFF"
static PREFIXCONST D_TextID POSTCONST GUID_c4bc86a3_2321217[]={atv_IDS_OFF, atv_IDS_ON, };
static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c4a2255e_06d6d3f={{&GUID_c4bc5431_1b57b6d, NULL, NULL, }, 1, 2, GUID_c4bc86a3_2321217, };

//////////////////////////////////////////////////////////////////////////
// definition of [29]{D_CTRL_LABEL}	"ID_SEARCH_LABLE_RIGHT5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a226d6_07d51a7={{&GUID_c4a1920b_07d6cde, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_search_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 160, 168, 0, 400, 240, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_SEARCH_LABLE_TITLE
	{D_CTRL_LABEL, 0, 129, 11, 0, 143, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a176ab_2bf43a5, },
	// [2]ID_SEARCH_GROUP_BG
	{D_CTRL_GROUP, 0, 6, 59, 20, 388, 177, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a175f3_0fa6be, },
	// [3]ID_SEARCH_BUTTON_FUN1
	{D_CTRL_BUTTON, 2, 4, 5, 0, 384, 27, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b64aec_33c5e3, },
	// [4]ID_SEARCH_LABLE_MANUAL
	{D_CTRL_LABEL, 3, 7, 0, 0, 91, 27, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a18c99_2af7d88, },
	// [5]ID_SEARCH_LABLE_LEFT1
	{D_CTRL_LABEL, 3, 184, 5, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a18ed9_05d1733, },
	// [6]ID_SEARCH_LABLE_MANUAL_TEXT
	{D_CTRL_LABEL, 3, 223, 0, 0, 59, 27, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b64f1f_35b7033, },
	// [7]ID_SEARCH_LABLE_MHZ1
	{D_CTRL_LABEL, 3, 284, 0, 0, 41, 27, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a19143_177196f, },
	// [8]ID_SEARCH_LABLE_RIGHT1
	{D_CTRL_LABEL, 3, 353, 5, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1920b_07d5c47, },
	// [9]ID_SEARCH_BUTTON_FUN2
	{D_CTRL_BUTTON, 2, 4, 39, 0, 384, 27, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b64b99_04e5dfc, },
	// [10]ID_SEARCH_LABLE_TUNE
	{D_CTRL_LABEL, 9, 7, 0, 0, 91, 27, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1986c_02e467f, },
	// [11]ID_SEARCH_LABLE_LEFT2
	{D_CTRL_LABEL, 9, 184, 5, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1b15d_1674e01, },
	// [12]ID_SEARCH_LABLE_TUNE_TEXT2
	{D_CTRL_LABEL, 9, 223, 0, 0, 59, 27, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b6509f_1483393, },
	// [13]ID_SEARCH_LABLE_MHZ2
	{D_CTRL_LABEL, 9, 284, 0, 0, 41, 27, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1b3a1_0ea7e59, },
	// [14]ID_SEARCH_LABLE_RIGHT2
	{D_CTRL_LABEL, 9, 353, 5, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1b423_0cb54ab, },
	// [15]ID_SEARCH_GROUP_FUN3
	{D_CTRL_GROUP, 2, 4, 74, 0, 384, 27, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b64c0e_1d42a6d, },
	// [16]ID_SEARCH_LABLE_NP
	{D_CTRL_LABEL, 15, 7, 0, 0, 91, 27, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1bab7_242c0b, },
	// [17]ID_SEARCH_LABLE_LEFT3
	{D_CTRL_LABEL, 15, 184, 5, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1bdc7_03e841, },
	// [18]ID_SEARCH_SELECT_NP
	{D_CTRL_SELECT, 15, 223, 0, 0, 102, 27, 30, 15, (D_FrameCtrlDescr*)&GUID_c4a1bf17_36b75d0, },
	// [19]ID_SEARCH_LABLE_RIGHT3
	{D_CTRL_LABEL, 15, 353, 5, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1c0fd_2ce2794, },
	// [20]ID_SEARCH_GROUP_FUN4
	{D_CTRL_GROUP, 2, 4, 107, 0, 384, 27, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b64c74_2425acc, },
	// [21]ID_SEARCH_LABLE_VOICE
	{D_CTRL_LABEL, 20, 7, 0, 0, 91, 27, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1c293_1672e99, },
	// [22]ID_SEARCH_LABLE_LEFT4
	{D_CTRL_LABEL, 20, 184, 5, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a210e8_1a51f60, },
	// [23]ID_SEARCH_SECLECT_VOICE
	{D_CTRL_SELECT, 20, 223, 0, 20, 102, 27, 30, 20, (D_FrameCtrlDescr*)&GUID_c4a21247_1b51a28, },
	// [24]ID_SEARCH_LABLE_RIGHT4
	{D_CTRL_LABEL, 20, 353, 5, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a222f6_261627e, },
	// [25]ID_SEARCH_GROUP_FUN5
	{D_CTRL_GROUP, 2, 4, 141, 0, 384, 27, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b64ce4_1576b75, },
	// [26]ID_SEARCH_LABLE_SKIP
	{D_CTRL_LABEL, 25, 7, 0, 4, 91, 27, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a2241a_1f45ea4, },
	// [27]ID_SEARCH_LABLE_LEFT5
	{D_CTRL_LABEL, 25, 184, 5, 4, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a224f7_32c6b9c, },
	// [28]ID_SEARCH_SELECT_ONOFF
	{D_CTRL_SELECT, 25, 223, 0, 4, 102, 27, 30, 25, (D_FrameCtrlDescr*)&GUID_c4a2255e_06d6d3f, },
	// [29]ID_SEARCH_LABLE_RIGHT5
	{D_CTRL_LABEL, 25, 353, 5, 4, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a226d6_07d51a7, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_search_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_search_window[30];
D_Frame atv_search_window = {
	run_ctrls_atv_search_window, 
	ctrl_description_of_atv_search_window, 
	atv_search_window_init, 
};

