/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2016-12-23 14:15:19

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2016-12-23  9:24:26.406

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
#define	ID_GROUP	1
#define	ID_LABEL_TITLE	2
#define	ID_GROUP_FREQ	3
#define	ID_LABEL_FREQ	4
#define	D_INPUT_FREQ	5
#define	ID_GROUP_MODE	6
#define	ID_LABEL_MODE	7
#define	ID_SELECT_MODE	8
#define	ID_GROUP_VID_NUM	9
#define	ID_LABLE_VID_NUM	10
#define	ID_INPUT_VID_PID	11
#define	ID_SELECT_VIDEO_TYPE	12
#define	ID_GROUP_AUD_NUM	13
#define	ID_LABLE_AUD_NUM	14
#define	ID_INPUT_AUD_PID	15
#define	ID_SELECT_AUDIO_TYPE	16
#define	ID_GROUP_PCR_NUM	17
#define	ID_LABLE_PCR_NUM	18
#define	ID_INPUT_PCR_PID	19
#define	ID_GROUP_STRENGTH	20
#define	ID_LABEL_STRENGTH	21
#define	ID_PROGRESS_STRENGTH	22
#define	ID_GROUP_QUALITY	23
#define	ID_LABEL_QUALITY	24
#define	ID_PROGRESS_QUALYTY	25
#define	ID_IMAGE_BOTTOM	26
#define	ID_HINT_OK	27
#define	ID_LABEL_OK	28
#define	ID_HINT_ESC	29
#define	ID_LABEL_ESC	30

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee8087e_6c={-1, -1, atv_IDS_EPGINFO, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee80b0c_19={-1, atv_IMG_ID_COMB_music_select, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee80eae_32={-1, -1, atv_IDS_FREQUENCY, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee82ecd_13={-1, -1, atv_IDS_MODULATION, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee8330e_0c={-1, -1, atv_IDS_STRENGH_BAR, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee833b9_60={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee83680_7a={-1, -1, atv_IDS_QUALITY_BAR, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee84cdf_49={-1, atv_IMG_ID_hint_button, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_signal_black_scroll_R2L, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee84dfe_e9={-1, -1, atv_IDS_OK, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee84ead_db={-1, atv_IMG_ID_hint_button, atv_IDS_QUIT, &atv_fmt_center_middle_h00_v00_signal_black_scroll_R2L, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee852b4_3e={-1, -1, atv_IDS_QUIT, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf89997b_2ce3b0a={-1, -1, atv_IDS_VIDEO_FRMART, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf899a52_02e1e35={-1, -1, atv_IDS_AUDIO_FRMART, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf899b08_1574ec5={-1, -1, atv_IDS_CLOCK, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf8a1120_3a93214={atv_COLOR_ENUM_84, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf8a388c_3d83739={atv_COLOR_ENUM_94, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c9739c40_21327bd={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c98f8ca5_09c17e4={atv_COLOR_ENUM_64, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee67715_29={{&GUID_c9739c40_21327bd, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee80985_52={{&GUID_c98f8ca5_09c17e4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_LABEL_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee8087e_e1={{&GUID_bee8087e_6c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_GROUP_FREQ"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee80b0c_c1={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_LABEL_FREQ"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee80eae_8d={{&GUID_bee80eae_32, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_INPUT}	"D_INPUT_FREQ"
static char GUID_bf8a388c_3d84df1[5+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_bf8a1120_3a9217d={{&GUID_bf8a1120_3a93214, &GUID_bf8a388c_3d83739, NULL, }, 1, 5, 5, GUID_bf8a388c_3d84df1, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_GROUP_MODE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee82e5c_c5={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_LABEL_MODE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee82ecd_7f={{&GUID_bee82ecd_13, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_SELECT}	"ID_SELECT_MODE"
static PREFIXCONST D_TextID POSTCONST GUID_c9740f8f_33c1361[]={atv_IDS_SEARCH_AUTO, };
static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_bf8a32ff_0bb6d1c={{&GUID_bf8a1120_3a93214, &GUID_bf8a388c_3d83739, NULL, }, 1, 1, GUID_c9740f8f_33c1361, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_GROUP}	"ID_GROUP_VID_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf898e9d_03e44e1={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_LABLE_VID_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf89997b_2ce453e={{&GUID_bf89997b_2ce3b0a, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_INPUT}	"ID_INPUT_VID_PID"
static char GUID_bf8a388c_3d84ef1[4+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_bf8a388c_3d87369={{&GUID_bf8a1120_3a93214, &GUID_bf8a388c_3d83739, NULL, }, 1, 0, 4, GUID_bf8a388c_3d84ef1, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_SELECT}	"ID_SELECT_VIDEO_TYPE"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_bfac4ba6_34b6333={{&GUID_bf8a1120_3a93214, &GUID_bf8a388c_3d83739, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_GROUP}	"ID_GROUP_AUD_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf898f0b_2901a18={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_LABLE_AUD_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf899a52_02e48a0={{&GUID_bf899a52_02e1e35, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_INPUT}	"ID_INPUT_AUD_PID"
static char GUID_bf8a4c1d_2ee67f8[4+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_bf8a4c1d_2ee6ebb={{&GUID_bf8a1120_3a93214, &GUID_bf8a388c_3d83739, NULL, }, 1, 0, 4, GUID_bf8a4c1d_2ee67f8, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_SELECT}	"ID_SELECT_AUDIO_TYPE"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_bfac4f68_2af52f4={{&GUID_bf8a1120_3a93214, &GUID_bf8a388c_3d83739, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_GROUP}	"ID_GROUP_PCR_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf898f5f_38a6097={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_LABEL}	"ID_LABLE_PCR_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf899b08_157583e={{&GUID_bf899b08_1574ec5, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_INPUT}	"ID_INPUT_PCR_PID"
static char GUID_bf8a50c5_1d46f1c[4+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_bf8a50c5_1d45e7f={{&GUID_bf8a1120_3a93214, &GUID_bf8a388c_3d83739, NULL, }, 1, 0, 4, GUID_bf8a50c5_1d46f1c, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_GROUP}	"ID_GROUP_STRENGTH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee831e7_6a={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_LABEL_STRENGTH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee8330e_f5={{&GUID_bee8330e_0c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_PROGRESS}	"ID_PROGRESS_STRENGTH"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_bee833b9_ad={{&GUID_bee833b9_60, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_105, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_GROUP}	"ID_GROUP_QUALITY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee834a2_4d={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_LABEL}	"ID_LABEL_QUALITY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee83680_9c={{&GUID_bee83680_7a, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_PROGRESS}	"ID_PROGRESS_QUALYTY"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_bee836e2_a5={{&GUID_bee833b9_60, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_105, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_IMAGE}	"ID_IMAGE_BOTTOM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee83830_31={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_LABEL}	"ID_HINT_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee84cdf_90={{&GUID_bee84cdf_49, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [28]{D_CTRL_LABEL}	"ID_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee84dfe_bb={{&GUID_bee84dfe_e9, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [29]{D_CTRL_LABEL}	"ID_HINT_ESC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee84ead_a6={{&GUID_bee84ead_db, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [30]{D_CTRL_LABEL}	"ID_LABEL_ESC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee852b4_0c={{&GUID_bee852b4_3e, NULL, NULL, }, 0, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_chan_info_test_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 325, 102, 0, 630, 516, 0, -1, (D_FrameCtrlDescr*)&GUID_bee67715_29, },
	// [1]ID_GROUP
	{D_CTRL_GROUP, 0, 27, 67, 2, 583, 359, 30, -1, (D_FrameCtrlDescr*)&GUID_bee80985_52, },
	// [2]ID_LABEL_TITLE
	{D_CTRL_LABEL, 0, 0, 0, 2, 630, 68, 30, -1, (D_FrameCtrlDescr*)&GUID_bee8087e_e1, },
	// [3]ID_GROUP_FREQ
	{D_CTRL_GROUP, 1, 29, 12, 21, 529, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee80b0c_c1, },
	// [4]ID_LABEL_FREQ
	{D_CTRL_LABEL, 3, 1, 1, 9, 133, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bee80eae_8d, },
	// [5]D_INPUT_FREQ
	{D_CTRL_INPUT, 3, 167, 1, -19, 344, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bf8a1120_3a9217d, },
	// [6]ID_GROUP_MODE
	{D_CTRL_GROUP, 1, 29, 55, 21, 529, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee82e5c_c5, },
	// [7]ID_LABEL_MODE
	{D_CTRL_LABEL, 6, 1, 1, -4, 136, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bee82ecd_7f, },
	// [8]ID_SELECT_MODE
	{D_CTRL_SELECT, 6, 167, 1, -21, 344, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bf8a32ff_0bb6d1c, },
	// [9]ID_GROUP_VID_NUM
	{D_CTRL_GROUP, 1, 29, 98, 0, 529, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bf898e9d_03e44e1, },
	// [10]ID_LABLE_VID_NUM
	{D_CTRL_LABEL, 9, 1, 1, -2, 127, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf89997b_2ce453e, },
	// [11]ID_INPUT_VID_PID
	{D_CTRL_INPUT, 9, 167, 1, 0, 120, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bf8a388c_3d87369, },
	// [12]ID_SELECT_VIDEO_TYPE
	{D_CTRL_SELECT, 9, 289, 1, 60, 221, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bfac4ba6_34b6333, },
	// [13]ID_GROUP_AUD_NUM
	{D_CTRL_GROUP, 1, 29, 141, 0, 529, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bf898f0b_2901a18, },
	// [14]ID_LABLE_AUD_NUM
	{D_CTRL_LABEL, 13, 1, 1, 0, 136, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_bf899a52_02e48a0, },
	// [15]ID_INPUT_AUD_PID
	{D_CTRL_INPUT, 13, 167, 1, 0, 120, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bf8a4c1d_2ee6ebb, },
	// [16]ID_SELECT_AUDIO_TYPE
	{D_CTRL_SELECT, 13, 289, 1, 60, 221, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bfac4f68_2af52f4, },
	// [17]ID_GROUP_PCR_NUM
	{D_CTRL_GROUP, 1, 29, 184, 0, 529, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bf898f5f_38a6097, },
	// [18]ID_LABLE_PCR_NUM
	{D_CTRL_LABEL, 17, 1, 0, 0, 136, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bf899b08_157583e, },
	// [19]ID_INPUT_PCR_PID
	{D_CTRL_INPUT, 17, 167, 1, 0, 344, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bf8a50c5_1d45e7f, },
	// [20]ID_GROUP_STRENGTH
	{D_CTRL_GROUP, 1, 29, 227, 21, 529, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee831e7_6a, },
	// [21]ID_LABEL_STRENGTH
	{D_CTRL_LABEL, 20, 1, 0, 129, 117, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bee8330e_f5, },
	// [22]ID_PROGRESS_STRENGTH
	{D_CTRL_PROGRESS, 20, 169, 1, 129, 341, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bee833b9_ad, },
	// [23]ID_GROUP_QUALITY
	{D_CTRL_GROUP, 1, 29, 270, 21, 529, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee834a2_4d, },
	// [24]ID_LABEL_QUALITY
	{D_CTRL_LABEL, 23, 0, 1, 125, 120, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_bee83680_9c, },
	// [25]ID_PROGRESS_QUALYTY
	{D_CTRL_PROGRESS, 23, 169, 1, 125, 342, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bee836e2_a5, },
	// [26]ID_IMAGE_BOTTOM
	{D_CTRL_IMAGE, 0, 27, 436, 2, 583, 68, 30, -1, (D_FrameCtrlDescr*)&GUID_bee83830_31, },
	// [27]ID_HINT_OK
	{D_CTRL_LABEL, 26, 97, 10, 11, 101, 41, 30, -1, (D_FrameCtrlDescr*)&GUID_bee84cdf_90, },
	// [28]ID_LABEL_OK
	{D_CTRL_LABEL, 26, 210, 12, 11, 84, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_bee84dfe_bb, },
	// [29]ID_HINT_ESC
	{D_CTRL_LABEL, 26, 302, 10, 11, 101, 41, 30, -1, (D_FrameCtrlDescr*)&GUID_bee84ead_a6, },
	// [30]ID_LABEL_ESC
	{D_CTRL_LABEL, 26, 419, 12, 11, 78, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_bee852b4_0c, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	chan_info_test_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_chan_info_test_window[31];
D_Frame chan_info_test_window = {
	run_ctrls_chan_info_test_window, 
	ctrl_description_of_chan_info_test_window, 
	chan_info_test_window_init, 
};

