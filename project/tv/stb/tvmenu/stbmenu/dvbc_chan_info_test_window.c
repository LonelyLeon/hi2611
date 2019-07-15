/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2016-12-23 14:14:55

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
#define	ID_GROUP_BAUD	6
#define	ID_LABEL_BAUD	7
#define	ID_INPUT_BAUD	8
#define	ID_GROUP_MODE	9
#define	ID_LABEL_MODE	10
#define	ID_SELECT_MODE	11
#define	ID_GROUP_VID_NUM	12
#define	ID_LABLE_VID_NUM	13
#define	ID_INPUT_VID_PID	14
#define	ID_SELECT_VIDEO_TYPE	15
#define	ID_GROUP_AUD_NUM	16
#define	ID_LABLE_AUD_NUM	17
#define	ID_INPUT_AUD_PID	18
#define	ID_SELECT_AUDIO_TYPE	19
#define	ID_GROUP_PCR_NUM	20
#define	ID_LABLE_PCR_NUM	21
#define	ID_INPUT_PCR_PID	22
#define	ID_GROUP_STRENGTH	23
#define	ID_LABEL_STRENGTH	24
#define	ID_PROGRESS_STRENGTH	25
#define	ID_GROUP_QUALITY	26
#define	ID_LABEL_QUALITY	27
#define	ID_PROGRESS_QUALYTY	28
#define	ID_IMAGE_BOTTOM	29
#define	ID_HINT_OK	30
#define	ID_LABEL_OK	31
#define	ID_HINT_ESC	32
#define	ID_LABEL_ESC	33

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee8087e_6c={-1, -1, atv_IDS_EPGINFO, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee80b0c_19={-1, atv_IMG_ID_COMB_music_select, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee80eae_32={-1, -1, atv_IDS_FREQUENCY, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee82ecd_13={-1, -1, atv_IDS_MODULATION, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee8330e_0c={-1, -1, atv_IDS_STRENGH_BAR, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee833b9_60={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee83680_7a={-1, -1, atv_IDS_QUALITY_BAR, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee84b1d_bb={-1, -1, atv_IDS_UPDATE_SYMBOL, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee84cdf_49={-1, atv_IMG_ID_hint_button, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee84dfe_e9={-1, -1, atv_IDS_OK, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee84ead_db={-1, atv_IMG_ID_hint_button, atv_IDS_EXIT, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee852b4_3e={-1, -1, atv_IDS_EXIT, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf89997b_2ce3b0a={-1, -1, atv_IDS_VIDEO_FRMART, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf899a52_02e1e35={-1, -1, atv_IDS_AUDIO_FRMART, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf899b08_1574ec5={-1, -1, atv_IDS_CLOCK, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf8a1120_3a93214={atv_COLOR_ENUM_84, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf8a388c_3d83739={atv_COLOR_ENUM_78, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c9796c8f_08c4ae1={atv_COLOR_ENUM_84, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c9796e23_07d404={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c98f9de0_167643a={atv_COLOR_ENUM_64, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee67715_29={{&GUID_c9796e23_07d404, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee80985_52={{&GUID_c98f9de0_167643a, NULL, NULL, }, 1, };

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
static char GUID_bf8a388c_3d84df1[3+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_bf8a1120_3a9217d={{&GUID_bf8a1120_3a93214, &GUID_bf8a388c_3d83739, NULL, }, 1, 0, 3, GUID_bf8a388c_3d84df1, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_GROUP_BAUD"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee81178_30={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_LABEL_BAUD"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee812fb_a3={{&GUID_bee84b1d_bb, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_INPUT}	"ID_INPUT_BAUD"
static char GUID_bf8a388c_3d89df1[4+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_bf8a3034_22277fc={{&GUID_bf8a1120_3a93214, &GUID_bf8a388c_3d83739, NULL, }, 1, 0, 4, GUID_bf8a388c_3d89df1, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_GROUP}	"ID_GROUP_MODE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee82e5c_c5={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_LABEL_MODE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee82ecd_7f={{&GUID_bee82ecd_13, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_SELECT}	"ID_SELECT_MODE"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_bf8a32ff_0bb6d1c={{&GUID_c9796c8f_08c4ae1, &GUID_bf8a388c_3d83739, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_GROUP}	"ID_GROUP_VID_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf898e9d_03e44e1={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_LABLE_VID_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf89997b_2ce453e={{&GUID_bf89997b_2ce3b0a, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_INPUT}	"ID_INPUT_VID_PID"
static char GUID_bf8a388c_3d84ef1[4+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_bf8a388c_3d87369={{&GUID_c9796c8f_08c4ae1, &GUID_bf8a388c_3d83739, NULL, }, 1, 0, 4, GUID_bf8a388c_3d84ef1, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_SELECT}	"ID_SELECT_VIDEO_TYPE"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_bfac4ba6_34b6333={{&GUID_c9796c8f_08c4ae1, &GUID_bf8a388c_3d83739, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_GROUP}	"ID_GROUP_AUD_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf898f0b_2901a18={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_LABLE_AUD_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf899a52_02e48a0={{&GUID_bf899a52_02e1e35, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_INPUT}	"ID_INPUT_AUD_PID"
static char GUID_bf8a4c1d_2ee67f8[4+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_bf8a4c1d_2ee6ebb={{&GUID_bf8a1120_3a93214, &GUID_bf8a388c_3d83739, NULL, }, 1, 0, 4, GUID_bf8a4c1d_2ee67f8, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_SELECT}	"ID_SELECT_AUDIO_TYPE"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_bfac4f68_2af52f4={{&GUID_bf8a1120_3a93214, &GUID_bf8a388c_3d83739, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_GROUP}	"ID_GROUP_PCR_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf898f5f_38a6097={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_LABLE_PCR_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf899b08_157583e={{&GUID_bf899b08_1574ec5, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_INPUT}	"ID_INPUT_PCR_PID"
static char GUID_bf8a50c5_1d46f1c[4+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_bf8a50c5_1d45e7f={{&GUID_c9796c8f_08c4ae1, &GUID_bf8a388c_3d83739, NULL, }, 1, 0, 4, GUID_bf8a50c5_1d46f1c, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_GROUP}	"ID_GROUP_STRENGTH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee831e7_6a={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_LABEL}	"ID_LABEL_STRENGTH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee8330e_f5={{&GUID_bee8330e_0c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_PROGRESS}	"ID_PROGRESS_STRENGTH"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_bee833b9_ad={{&GUID_bee833b9_60, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_97, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_GROUP}	"ID_GROUP_QUALITY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee834a2_4d={{&GUID_bee80b0c_19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_LABEL}	"ID_LABEL_QUALITY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee83680_9c={{&GUID_bee83680_7a, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [28]{D_CTRL_PROGRESS}	"ID_PROGRESS_QUALYTY"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_bee836e2_a5={{&GUID_bee833b9_60, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_97, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [29]{D_CTRL_IMAGE}	"ID_IMAGE_BOTTOM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee83830_31={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [30]{D_CTRL_LABEL}	"ID_HINT_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee84cdf_90={{&GUID_bee84cdf_49, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [31]{D_CTRL_LABEL}	"ID_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee84dfe_bb={{&GUID_bee84dfe_e9, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [32]{D_CTRL_LABEL}	"ID_HINT_ESC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee84ead_a6={{&GUID_bee84ead_db, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [33]{D_CTRL_LABEL}	"ID_LABEL_ESC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bee852b4_0c={{&GUID_bee852b4_3e, NULL, NULL, }, 0, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_dvbc_chan_info_test_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 325, 102, 0, 630, 536, 0, -1, (D_FrameCtrlDescr*)&GUID_bee67715_29, },
	// [1]ID_GROUP
	{D_CTRL_GROUP, 0, 27, 68, 2, 583, 373, 30, -1, (D_FrameCtrlDescr*)&GUID_bee80985_52, },
	// [2]ID_LABEL_TITLE
	{D_CTRL_LABEL, 0, 0, 0, 2, 630, 68, 30, -1, (D_FrameCtrlDescr*)&GUID_bee8087e_e1, },
	// [3]ID_GROUP_FREQ
	{D_CTRL_GROUP, 1, 33, 18, 21, 524, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee80b0c_c1, },
	// [4]ID_LABEL_FREQ
	{D_CTRL_LABEL, 3, 1, 1, 7, 150, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bee80eae_8d, },
	// [5]D_INPUT_FREQ
	{D_CTRL_INPUT, 3, 225, 1, -21, 275, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bf8a1120_3a9217d, },
	// [6]ID_GROUP_BAUD
	{D_CTRL_GROUP, 1, 33, 61, 21, 524, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee81178_30, },
	// [7]ID_LABEL_BAUD
	{D_CTRL_LABEL, 6, 1, 1, 4, 150, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bee812fb_a3, },
	// [8]ID_INPUT_BAUD
	{D_CTRL_INPUT, 6, 225, 1, -19, 275, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bf8a3034_22277fc, },
	// [9]ID_GROUP_MODE
	{D_CTRL_GROUP, 1, 33, 104, 21, 524, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee82e5c_c5, },
	// [10]ID_LABEL_MODE
	{D_CTRL_LABEL, 9, 1, 1, 0, 150, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bee82ecd_7f, },
	// [11]ID_SELECT_MODE
	{D_CTRL_SELECT, 9, 225, 1, -17, 275, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bf8a32ff_0bb6d1c, },
	// [12]ID_GROUP_VID_NUM
	{D_CTRL_GROUP, 1, 33, 147, 0, 524, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bf898e9d_03e44e1, },
	// [13]ID_LABLE_VID_NUM
	{D_CTRL_LABEL, 12, 1, 1, 4, 150, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf89997b_2ce453e, },
	// [14]ID_INPUT_VID_PID
	{D_CTRL_INPUT, 12, 225, 1, 6, 80, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bf8a388c_3d87369, },
	// [15]ID_SELECT_VIDEO_TYPE
	{D_CTRL_SELECT, 12, 307, 1, 66, 193, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bfac4ba6_34b6333, },
	// [16]ID_GROUP_AUD_NUM
	{D_CTRL_GROUP, 1, 33, 190, 0, 524, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bf898f0b_2901a18, },
	// [17]ID_LABLE_AUD_NUM
	{D_CTRL_LABEL, 16, 1, 1, 8, 145, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf899a52_02e48a0, },
	// [18]ID_INPUT_AUD_PID
	{D_CTRL_INPUT, 16, 225, 1, 8, 80, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bf8a4c1d_2ee6ebb, },
	// [19]ID_SELECT_AUDIO_TYPE
	{D_CTRL_SELECT, 16, 307, 1, 68, 193, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bfac4f68_2af52f4, },
	// [20]ID_GROUP_PCR_NUM
	{D_CTRL_GROUP, 1, 33, 233, 0, 524, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bf898f5f_38a6097, },
	// [21]ID_LABLE_PCR_NUM
	{D_CTRL_LABEL, 20, 1, 1, 10, 150, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf899b08_157583e, },
	// [22]ID_INPUT_PCR_PID
	{D_CTRL_INPUT, 20, 225, 1, 10, 275, 39, 30, -1, (D_FrameCtrlDescr*)&GUID_bf8a50c5_1d45e7f, },
	// [23]ID_GROUP_STRENGTH
	{D_CTRL_GROUP, 1, 33, 276, 21, 524, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee831e7_6a, },
	// [24]ID_LABEL_STRENGTH
	{D_CTRL_LABEL, 23, 1, 1, 100, 100, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bee8330e_f5, },
	// [25]ID_PROGRESS_STRENGTH
	{D_CTRL_PROGRESS, 23, 174, 1, 100, 324, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_bee833b9_ad, },
	// [26]ID_GROUP_QUALITY
	{D_CTRL_GROUP, 1, 33, 319, 21, 524, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee834a2_4d, },
	// [27]ID_LABEL_QUALITY
	{D_CTRL_LABEL, 26, 1, 1, 98, 109, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bee83680_9c, },
	// [28]ID_PROGRESS_QUALYTY
	{D_CTRL_PROGRESS, 26, 174, 1, 98, 324, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_bee836e2_a5, },
	// [29]ID_IMAGE_BOTTOM
	{D_CTRL_IMAGE, 0, 27, 451, 2, 583, 68, 30, -1, (D_FrameCtrlDescr*)&GUID_bee83830_31, },
	// [30]ID_HINT_OK
	{D_CTRL_LABEL, 29, 73, 13, 11, 101, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee84cdf_90, },
	// [31]ID_LABEL_OK
	{D_CTRL_LABEL, 29, 196, 14, 11, 84, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_bee84dfe_bb, },
	// [32]ID_HINT_ESC
	{D_CTRL_LABEL, 29, 307, 13, 11, 102, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_bee84ead_a6, },
	// [33]ID_LABEL_ESC
	{D_CTRL_LABEL, 29, 432, 14, 11, 78, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_bee852b4_0c, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	dvbc_chan_info_test_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_dvbc_chan_info_test_window[34];
D_Frame dvbc_chan_info_test_window = {
	run_ctrls_dvbc_chan_info_test_window, 
	ctrl_description_of_dvbc_chan_info_test_window, 
	dvbc_chan_info_test_window_init, 
};

