/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {liujh}
	on computer "PRLIUJH"
	update/create time:	2018-04-25 12:44:43

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2018-04-18 16:57:01.687

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
#define	ID_SCAN_LABEL_TITLE	1
#define	D_SCAN_LABEL_LINE_V	2
#define	D_SCAN_LABEL_LINE_H	3
#define	ID_SCAN_IMG_RED_LEFT	4
#define	ID_SCAN_LABEL_TV	5
#define	ID_SCAN_LABEL_TV_NUM	6
#define	ID_SCAN_IMG_RED_RIGHT	7
#define	ID_SCAN_LABEL_RADIO	8
#define	ID_SCAN_LABEL_RADIO_NUM	9
#define	ID_SCAN_LIST_TV	10
#define	ID_SCAN_LIST_RADIO	11
#define	ID_SCAN_LIST_RESULT	12
#define	ID_SCAN_IMG_ANTENNA	13
#define	ID_SCAN_IMG_WAVE	14
#define	ID_SCAN_IMG_SATELLITE	15
#define	ID_SCAN_PROGRESS	16
#define	ID_SCAN_LABEL_PROGRESS	17
#define	ID_SCAN_LING_H_UP	18

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1f69ada_1864823={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1fc9b32_09c3b66={-1, -1, atv_IDS_AUTO_TUNING, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1fc9c84_3a911b8={atv_COLOR_ENUM_64, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1fca268_177f07={-1, atv_IMG_ID_program_info_direction_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1fca391_1773ecf={-1, -1, atv_IDS_DIGI_TV, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1fca432_07d82e={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1fca5c5_23259e3={-1, -1, atv_IDS_DIGI_RADIO, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1fcae1e_07d3660={atv_COLOR_ENUM_14, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1fcd021_1c57bc={atv_COLOR_ENUM_19, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1f69ada_18629={{&GUID_c1f69ada_1864823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_SCAN_LABEL_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fc9b32_09c24e7={{&GUID_c1fc9b32_09c3b66, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"D_SCAN_LABEL_LINE_V"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fc9c84_3a9186d={{&GUID_c1fc9c84_3a911b8, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"D_SCAN_LABEL_LINE_H"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fc9e04_19642cc={{&GUID_c1fc9c84_3a911b8, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_IMAGE}	"ID_SCAN_IMG_RED_LEFT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fca268_17730b1={{&GUID_c1fca268_177f07, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_SCAN_LABEL_TV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fca391_1778a={{&GUID_c1fca391_1773ecf, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_SCAN_LABEL_TV_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fca432_07d7248={{&GUID_c1fca432_07d82e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_IMAGE}	"ID_SCAN_IMG_RED_RIGHT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fca55f_128221f={{&GUID_c1fca268_177f07, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_SCAN_LABEL_RADIO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fca5c5_232270f={{&GUID_c1fca5c5_23259e3, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_SCAN_LABEL_RADIO_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fca6a4_1963bd7={{&GUID_c1fca432_07d82e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LIST}	"ID_SCAN_LIST_TV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fca770_25116ba_GUID_c1fca893_37a4bba={{NULL, NULL, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fca770_25116ba_GUID_c1fca82a_06d3d4={{&GUID_c1fca432_07d82e, NULL, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c1fca770_2516b33[]={
	&GUID_c1fca770_25116ba_GUID_c1fca893_37a4bba, 
	&GUID_c1fca770_25116ba_GUID_c1fca893_37a4bba, 
	&GUID_c1fca770_25116ba_GUID_c1fca893_37a4bba, 
	&GUID_c1fca770_25116ba_GUID_c1fca893_37a4bba, 
	&GUID_c1fca770_25116ba_GUID_c1fca893_37a4bba, 
};

static PREFIXCONST D_Coord POSTCONST list_ctrl_GUID_c1fca770_2511035[2]={50, 300, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c1fca770_251161e[5][2]=
{
	{&GUID_c1fca770_25116ba_GUID_c1fca82a_06d3d4, &GUID_c1fca770_25116ba_GUID_c1fca82a_06d3d4, },
	{&GUID_c1fca770_25116ba_GUID_c1fca82a_06d3d4, &GUID_c1fca770_25116ba_GUID_c1fca82a_06d3d4, },
	{&GUID_c1fca770_25116ba_GUID_c1fca82a_06d3d4, &GUID_c1fca770_25116ba_GUID_c1fca82a_06d3d4, },
	{&GUID_c1fca770_25116ba_GUID_c1fca82a_06d3d4, &GUID_c1fca770_25116ba_GUID_c1fca82a_06d3d4, },
	{&GUID_c1fca770_25116ba_GUID_c1fca82a_06d3d4, &GUID_c1fca770_25116ba_GUID_c1fca82a_06d3d4, },
};
static PREFIXCONST D_FrameListDescr POSTCONST GUID_c1fca770_25116ba={{NULL, NULL, NULL, }, 1, 10, 5, 1, 2, 30, list_ctrl_GUID_c1fca770_2511035, 2, 0, D_LIST_FOCUS_TYPE_NO, list_ctrl_GUID_c1fca770_251161e, list_ctrl_GUID_c1fca770_2516b33, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LIST}	"ID_SCAN_LIST_RADIO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fca94e_1093602_GUID_c1fca970_1675b44={{NULL, NULL, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fca94e_1093602_GUID_c1fca966_1c52495={{&GUID_c1fca432_07d82e, NULL, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c1fca94e_1094be5[]={
	&GUID_c1fca94e_1093602_GUID_c1fca970_1675b44, 
	&GUID_c1fca94e_1093602_GUID_c1fca970_1675b44, 
	&GUID_c1fca94e_1093602_GUID_c1fca970_1675b44, 
	&GUID_c1fca94e_1093602_GUID_c1fca970_1675b44, 
	&GUID_c1fca94e_1093602_GUID_c1fca970_1675b44, 
};

static PREFIXCONST D_Coord POSTCONST list_ctrl_GUID_c1fca94e_10950f1[2]={50, 300, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c1fca94e_1097d7a[5][2]=
{
	{&GUID_c1fca94e_1093602_GUID_c1fca966_1c52495, &GUID_c1fca94e_1093602_GUID_c1fca966_1c52495, },
	{&GUID_c1fca94e_1093602_GUID_c1fca966_1c52495, &GUID_c1fca94e_1093602_GUID_c1fca966_1c52495, },
	{&GUID_c1fca94e_1093602_GUID_c1fca966_1c52495, &GUID_c1fca94e_1093602_GUID_c1fca966_1c52495, },
	{&GUID_c1fca94e_1093602_GUID_c1fca966_1c52495, &GUID_c1fca94e_1093602_GUID_c1fca966_1c52495, },
	{&GUID_c1fca94e_1093602_GUID_c1fca966_1c52495, &GUID_c1fca94e_1093602_GUID_c1fca966_1c52495, },
};
static PREFIXCONST D_FrameListDescr POSTCONST GUID_c1fca94e_1093602={{NULL, NULL, NULL, }, 1, 10, 5, 1, 2, 30, list_ctrl_GUID_c1fca94e_10950f1, 2, 0, D_LIST_FOCUS_TYPE_NO, list_ctrl_GUID_c1fca94e_1097d7a, list_ctrl_GUID_c1fca94e_1094be5, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LIST}	"ID_SCAN_LIST_RESULT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fcaa14_2af22cd_GUID_c1fcd63d_05d7a54={{NULL, NULL, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2={{&GUID_c1fca432_07d82e, NULL, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST GUID_c1fce656_02ec94[]={
	&GUID_c1fcaa14_2af22cd_GUID_c1fcd63d_05d7a54, 
	&GUID_c1fcaa14_2af22cd_GUID_c1fcd63d_05d7a54, 
	&GUID_c1fcaa14_2af22cd_GUID_c1fcd63d_05d7a54, 
	&GUID_c1fcaa14_2af22cd_GUID_c1fcd63d_05d7a54, 
	&GUID_c1fcaa14_2af22cd_GUID_c1fcd63d_05d7a54, 
};

static PREFIXCONST D_Coord POSTCONST list_ctrl_GUID_c1fcaa14_2af1e04[6]={70, 190, 100, 40, 100, 94, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c1fcaa14_2af361a[5][6]=
{
	{&GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, },
	{&GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, },
	{&GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, },
	{&GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, },
	{&GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, &GUID_c1fcaa14_2af22cd_GUID_c1fcaa37_0cb75c2, },
};
static PREFIXCONST D_FrameListDescr POSTCONST GUID_c1fcaa14_2af22cd={{NULL, NULL, NULL, }, 1, 10, 5, 5, 6, 32, list_ctrl_GUID_c1fcaa14_2af1e04, 2, 0, D_LIST_FOCUS_TYPE_NO, list_ctrl_GUID_c1fcaa14_2af361a, GUID_c1fce656_02ec94, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_IMAGE}	"ID_SCAN_IMG_ANTENNA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fcae1e_07d1cc8={{&GUID_c1fcae1e_07d3660, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_IMAGE}	"ID_SCAN_IMG_WAVE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c200d5fb_1382cd6={{&GUID_c1fcae1e_07d3660, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_IMAGE}	"ID_SCAN_IMG_SATELLITE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fcbf21_128102f={{&GUID_c1fcae1e_07d3660, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_PROGRESS}	"ID_SCAN_PROGRESS"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_c1fcd021_1c5d19={{&GUID_c1fcd021_1c57bc, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_54, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_SCAN_LABEL_PROGRESS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1fcd1f0_35b5372={{&GUID_c1fca432_07d82e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_LABEL}	"ID_SCAN_LING_H_UP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c75398d0_157f3e={{&GUID_c1fc9c84_3a911b8, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_scan_menu_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 265, 80, 0, 750, 550, 0, -1, (D_FrameCtrlDescr*)&GUID_c1f69ada_18629, },
	// [1]ID_SCAN_LABEL_TITLE
	{D_CTRL_LABEL, 0, 298, 12, 100, 215, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fc9b32_09c24e7, },
	// [2]D_SCAN_LABEL_LINE_V
	{D_CTRL_LABEL, 0, 372, 71, 100, 2, 235, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fc9c84_3a9186d, },
	// [3]D_SCAN_LABEL_LINE_H
	{D_CTRL_LABEL, 0, 2, 305, 100, 746, 2, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fc9e04_19642cc, },
	// [4]ID_SCAN_IMG_RED_LEFT
	{D_CTRL_IMAGE, 0, 51, 81, 100, 17, 34, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fca268_17730b1, },
	// [5]ID_SCAN_LABEL_TV
	{D_CTRL_LABEL, 0, 75, 82, 100, 176, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fca391_1778a, },
	// [6]ID_SCAN_LABEL_TV_NUM
	{D_CTRL_LABEL, 0, 270, 82, 100, 70, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fca432_07d7248, },
	// [7]ID_SCAN_IMG_RED_RIGHT
	{D_CTRL_IMAGE, 0, 428, 78, 100, 20, 34, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fca55f_128221f, },
	// [8]ID_SCAN_LABEL_RADIO
	{D_CTRL_LABEL, 0, 454, 80, 100, 176, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fca5c5_232270f, },
	// [9]ID_SCAN_LABEL_RADIO_NUM
	{D_CTRL_LABEL, 0, 650, 80, 100, 70, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fca6a4_1963bd7, },
	// [10]ID_SCAN_LIST_TV
	{D_CTRL_LIST, 0, 11, 125, 100, 350, 158, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fca770_25116ba, },
	// [11]ID_SCAN_LIST_RADIO
	{D_CTRL_LIST, 0, 387, 125, 100, 350, 158, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fca94e_1093602, },
	// [12]ID_SCAN_LIST_RESULT
	{D_CTRL_LIST, 0, 8, 321, 100, 594, 168, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fcaa14_2af22cd, },
	// [13]ID_SCAN_IMG_ANTENNA
	{D_CTRL_IMAGE, 0, 621, 424, 100, 36, 44, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fcae1e_07d1cc8, },
	// [14]ID_SCAN_IMG_WAVE
	{D_CTRL_IMAGE, 0, 616, 352, 100, 120, 47, 30, -1, (D_FrameCtrlDescr*)&GUID_c200d5fb_1382cd6, },
	// [15]ID_SCAN_IMG_SATELLITE
	{D_CTRL_IMAGE, 0, 616, 315, 100, 120, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fcbf21_128102f, },
	// [16]ID_SCAN_PROGRESS
	{D_CTRL_PROGRESS, 0, 13, 498, 100, 589, 17, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fcd021_1c5d19, },
	// [17]ID_SCAN_LABEL_PROGRESS
	{D_CTRL_LABEL, 0, 635, 494, 100, 86, 28, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fcd1f0_35b5372, },
	// [18]ID_SCAN_LING_H_UP
	{D_CTRL_LABEL, 0, 2, 68, 20, 746, 2, 30, -1, (D_FrameCtrlDescr*)&GUID_c75398d0_157f3e, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	scan_menu_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_scan_menu_window[19];
D_Frame scan_menu_window = {
	run_ctrls_scan_menu_window, 
	ctrl_description_of_scan_menu_window, 
	scan_menu_window_init, 
};

