/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2015-05-23 15:47:49

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-05-21 10:13:28.484

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
#define	ID_LABLE_TITLE	1
#define	ID_LABLE_TIME	2
#define	D_FRAMECONTROL_1	3
#define	D_FRAMECONTROL_3	4
#define	ID_LIST_CHANNEL	5
#define	ID_LABLE_SELECT_DAY_LEFT	6
#define	ID_LABLE_SELECT_DAY	7
#define	ID_LABLE_SELECT_DAY_RIGHT	8
#define	ID_LIST_EVENT	9
#define	ID_IMG_OK	10
#define	ID_LABLE_OK	11
#define	ID_IMG_RED	12
#define	ID_LABLE_PROG_OR_EVENT	13
#define	ID_IMG_UP	14
#define	ID_IMG_DOWN	15
#define	ID_LABLE_UP_DOWN	16
#define	ID_IMG_DAY_LEFT	17
#define	ID_IMG_DAY_RIGHT	18
#define	ID_LABLE_DAY_TITLE	19
#define	ID_SCROLL_CHAN	20
#define	ID_SCROLL_EVENT	21

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c13485b9_2224823={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c134990e_2af7d92={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c134a3f3_2ce7341={-1, -1, -1, &atv_fmt_right_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c134a8a4_36b3246={-1, -1, -1, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c134ad52_05d1288={-1, atv_IMG_ID_search_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c134adff_24237dd={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c134ae71_20346dc={-1, atv_IMG_ID_search_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c135653b_1f4342a={atv_COLOR_ENUM_106, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c13567d9_01f1850={-1, atv_IMG_ID_hint_button, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_signal_black_scroll_R2L, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c13569c9_3d83014={-1, -1, atv_IDS_PLAY, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1356a82_32c62d5={-1, atv_IMG_ID_red_info_icon, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1356aeb_08c5c98={-1, -1, atv_IDS_SWITCH_USER_MODE, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1356bc7_2bf50ff={-1, atv_IMG_ID_program_info_direction_up, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1356c75_1c5424b={-1, atv_IMG_ID_program_info_direction_down, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1356ca4_31c6771={-1, -1, atv_IDS_CHOICE, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1356d3d_30d3870={-1, atv_IMG_ID_program_info_direction_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1356d6b_2fd14e1={-1, atv_IMG_ID_program_info_direction_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1356db6_39938d0={-1, -1, atv_IDS_EPG_HELP, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1359cad_3b959ea={atv_COLOR_ENUM_64, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c13b6db2_2de1e36={-1, atv_IMG_ID_Scroll_Bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c142eb5e_3997e87={-1, -1, -1, &atv_fmt_left_middle_h00_v00_signal_black_scroll_R2L, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c13485b9_22229={{&GUID_c13485b9_2224823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_LABLE_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c134990e_2af6346={{&GUID_c134990e_2af7d92, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_LABLE_TIME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c134a3f3_2ce1977={{&GUID_c134a3f3_2ce7341, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"D_FRAMECONTROL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1359cad_3b96d87={{&GUID_c1359cad_3b959ea, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"D_FRAMECONTROL_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1359d68_1b5695f={{&GUID_c1359cad_3b959ea, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LIST}	"ID_LIST_CHANNEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c134a8a4_36b64cf_GUID_c134aae0_1194401={{NULL, &GUID_c135653b_1f4342a, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c134a8a4_36b64cf_GUID_c134ab59_3a976ee={{&GUID_c134a8a4_36b3246, &GUID_c134a8a4_36b3246, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c134a8a4_36b64cf_GUID_c13598b2_1c519ff={{&GUID_c134990e_2af7d92, NULL, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c134a8a4_36b64cf_GUID_c13598bc_0bb26bf={{&GUID_c134990e_2af7d92, &GUID_c134990e_2af7d92, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c134a8a4_36b79cd[]={
	&GUID_c134a8a4_36b64cf_GUID_c134aae0_1194401, 
	&GUID_c134a8a4_36b64cf_GUID_c134aae0_1194401, 
	&GUID_c134a8a4_36b64cf_GUID_c134aae0_1194401, 
	&GUID_c134a8a4_36b64cf_GUID_c134aae0_1194401, 
	&GUID_c134a8a4_36b64cf_GUID_c134aae0_1194401, 
	&GUID_c134a8a4_36b64cf_GUID_c134aae0_1194401, 
};

static PREFIXCONST D_Coord POSTCONST list_ctrl_GUID_c134a8a4_36b22b6[3]={50, 411, 24, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c134a8a4_36b4556[6][3]=
{
	{&GUID_c134a8a4_36b64cf_GUID_c134ab59_3a976ee, &GUID_c134a8a4_36b64cf_GUID_c13598b2_1c519ff, &GUID_c134a8a4_36b64cf_GUID_c13598bc_0bb26bf, },
	{&GUID_c134a8a4_36b64cf_GUID_c134ab59_3a976ee, &GUID_c134a8a4_36b64cf_GUID_c13598b2_1c519ff, &GUID_c134a8a4_36b64cf_GUID_c13598bc_0bb26bf, },
	{&GUID_c134a8a4_36b64cf_GUID_c134ab59_3a976ee, &GUID_c134a8a4_36b64cf_GUID_c13598b2_1c519ff, &GUID_c134a8a4_36b64cf_GUID_c13598bc_0bb26bf, },
	{&GUID_c134a8a4_36b64cf_GUID_c134ab59_3a976ee, &GUID_c134a8a4_36b64cf_GUID_c13598b2_1c519ff, &GUID_c134a8a4_36b64cf_GUID_c13598bc_0bb26bf, },
	{&GUID_c134a8a4_36b64cf_GUID_c134ab59_3a976ee, &GUID_c134a8a4_36b64cf_GUID_c13598b2_1c519ff, &GUID_c134a8a4_36b64cf_GUID_c13598bc_0bb26bf, },
	{&GUID_c134a8a4_36b64cf_GUID_c134ab59_3a976ee, &GUID_c134a8a4_36b64cf_GUID_c13598b2_1c519ff, &GUID_c134a8a4_36b64cf_GUID_c13598bc_0bb26bf, },
};
static PREFIXCONST D_FrameListDescr POSTCONST GUID_c134a8a4_36b64cf={{&GUID_c134a8a4_36b3246, &GUID_c134a8a4_36b3246, NULL, }, 1, 10, 6, 6, 3, 32, list_ctrl_GUID_c134a8a4_36b22b6, 2, 0, D_LIST_FOCUS_TYPE_ROW, list_ctrl_GUID_c134a8a4_36b4556, list_ctrl_GUID_c134a8a4_36b79cd, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_LABLE_SELECT_DAY_LEFT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c134ad52_05d8cd={{&GUID_c134ad52_05d1288, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_LABLE_SELECT_DAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c134adff_2424f8c={{&GUID_c134adff_24237dd, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_LABLE_SELECT_DAY_RIGHT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c134ae71_2032172={{&GUID_c134ae71_20346dc, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LIST}	"ID_LIST_EVENT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c13564cb_1097a77_GUID_c1356530_34b432b={{NULL, &GUID_c135653b_1f4342a, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c13564cb_1097a77_GUID_c135978e_2bfaea={{&GUID_c134990e_2af7d92, &GUID_c134990e_2af7d92, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c13564cb_1097a77_GUID_c135986b_0da2ddc={{&GUID_c134990e_2af7d92, &GUID_c142eb5e_3997e87, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c13564cb_1091351[]={
	&GUID_c13564cb_1097a77_GUID_c1356530_34b432b, 
	&GUID_c13564cb_1097a77_GUID_c1356530_34b432b, 
	&GUID_c13564cb_1097a77_GUID_c1356530_34b432b, 
	&GUID_c13564cb_1097a77_GUID_c1356530_34b432b, 
	&GUID_c13564cb_1097a77_GUID_c1356530_34b432b, 
	&GUID_c13564cb_1097a77_GUID_c1356530_34b432b, 
};

static PREFIXCONST D_Coord POSTCONST list_ctrl_GUID_c13564cb_10950c6[3]={40, 115, 330, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c13564cb_1096cc8[6][3]=
{
	{&GUID_c13564cb_1097a77_GUID_c135978e_2bfaea, &GUID_c13564cb_1097a77_GUID_c135978e_2bfaea, &GUID_c13564cb_1097a77_GUID_c135986b_0da2ddc, },
	{&GUID_c13564cb_1097a77_GUID_c135978e_2bfaea, &GUID_c13564cb_1097a77_GUID_c135978e_2bfaea, &GUID_c13564cb_1097a77_GUID_c135986b_0da2ddc, },
	{&GUID_c13564cb_1097a77_GUID_c135978e_2bfaea, &GUID_c13564cb_1097a77_GUID_c135978e_2bfaea, &GUID_c13564cb_1097a77_GUID_c135986b_0da2ddc, },
	{&GUID_c13564cb_1097a77_GUID_c135978e_2bfaea, &GUID_c13564cb_1097a77_GUID_c135978e_2bfaea, &GUID_c13564cb_1097a77_GUID_c135986b_0da2ddc, },
	{&GUID_c13564cb_1097a77_GUID_c135978e_2bfaea, &GUID_c13564cb_1097a77_GUID_c135978e_2bfaea, &GUID_c13564cb_1097a77_GUID_c135986b_0da2ddc, },
	{&GUID_c13564cb_1097a77_GUID_c135978e_2bfaea, &GUID_c13564cb_1097a77_GUID_c135978e_2bfaea, &GUID_c13564cb_1097a77_GUID_c135986b_0da2ddc, },
};
static PREFIXCONST D_FrameListDescr POSTCONST GUID_c13564cb_1097a77={{&GUID_c134a8a4_36b3246, &GUID_c134a8a4_36b3246, NULL, }, 1, 10, 6, 6, 3, 32, list_ctrl_GUID_c13564cb_10950c6, 2, 0, D_LIST_FOCUS_TYPE_ROW, list_ctrl_GUID_c13564cb_1096cc8, list_ctrl_GUID_c13564cb_1091351, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_IMG_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c13567d9_01f41dd={{&GUID_c13567d9_01f1850, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_LABLE_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c13569c9_3d81dfa={{&GUID_c13569c9_3d83014, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_IMG_RED"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1356a82_32c2402={{&GUID_c1356a82_32c62d5, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_LABLE_PROG_OR_EVENT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1356aeb_08c7298={{&GUID_c1356aeb_08c5c98, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_IMG_UP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1356bc7_2bf6537={{&GUID_c1356bc7_2bf50ff, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_LABEL}	"ID_IMG_DOWN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1356c75_1c55ecd={{&GUID_c1356c75_1c5424b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_LABLE_UP_DOWN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1356ca4_31c265={{&GUID_c1356ca4_31c6771, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_IMG_DAY_LEFT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1356d3d_30d5f03={{&GUID_c1356d3d_30d3870, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_LABEL}	"ID_IMG_DAY_RIGHT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1356d6b_2fd12cf={{&GUID_c1356d6b_2fd14e1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_LABEL}	"ID_LABLE_DAY_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1356db6_3992976={{&GUID_c1356db6_39938d0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_SCROLL}	"ID_SCROLL_CHAN"
static PREFIXCONST D_FrameScrollBarDescr POSTCONST GUID_c13a725f_2421b11={{&GUID_c13b6db2_2de1e36, NULL, NULL, }, 1, 100, 10, 1, {-1, -1, -1, atv_IMG_ID_Scroll_Vernier, }, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_SCROLL}	"ID_SCROLL_EVENT"
static PREFIXCONST D_FrameScrollBarDescr POSTCONST GUID_c13a7379_3992559={{&GUID_c13b6db2_2de1e36, NULL, NULL, }, 1, 100, 10, 1, {-1, -1, -1, atv_IMG_ID_Scroll_Vernier, }, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_epg_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 700, 50, 0, 520, 590, 0, -1, (D_FrameCtrlDescr*)&GUID_c13485b9_22229, },
	// [1]ID_LABLE_TITLE
	{D_CTRL_LABEL, 0, 22, 13, 18, 165, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c134990e_2af6346, },
	// [2]ID_LABLE_TIME
	{D_CTRL_LABEL, 0, 198, 13, 18, 300, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c134a3f3_2ce1977, },
	// [3]D_FRAMECONTROL_1
	{D_CTRL_GROUP, 0, 8, 58, 18, 504, 220, 30, -1, (D_FrameCtrlDescr*)&GUID_c1359cad_3b96d87, },
	// [4]D_FRAMECONTROL_3
	{D_CTRL_GROUP, 0, 9, 325, 18, 504, 213, 30, -1, (D_FrameCtrlDescr*)&GUID_c1359d68_1b5695f, },
	// [5]ID_LIST_CHANNEL
	{D_CTRL_LIST, 3, 2, 10, 0, 485, 202, 30, 20, (D_FrameCtrlDescr*)&GUID_c134a8a4_36b64cf, },
	// [6]ID_LABLE_SELECT_DAY_LEFT
	{D_CTRL_LABEL, 0, 126, 297, 18, 12, 12, 30, -1, (D_FrameCtrlDescr*)&GUID_c134ad52_05d8cd, },
	// [7]ID_LABLE_SELECT_DAY
	{D_CTRL_LABEL, 0, 147, 288, 18, 223, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c134adff_2424f8c, },
	// [8]ID_LABLE_SELECT_DAY_RIGHT
	{D_CTRL_LABEL, 0, 378, 297, 18, 12, 12, 30, -1, (D_FrameCtrlDescr*)&GUID_c134ae71_2032172, },
	// [9]ID_LIST_EVENT
	{D_CTRL_LIST, 4, 1, 6, 0, 485, 202, 30, 21, (D_FrameCtrlDescr*)&GUID_c13564cb_1097a77, },
	// [10]ID_IMG_OK
	{D_CTRL_LABEL, 0, 10, 545, 18, 74, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c13567d9_01f41dd, },
	// [11]ID_LABLE_OK
	{D_CTRL_LABEL, 0, 92, 548, 18, 60, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c13569c9_3d81dfa, },
	// [12]ID_IMG_RED
	{D_CTRL_LABEL, 0, 152, 551, 18, 24, 24, 30, -1, (D_FrameCtrlDescr*)&GUID_c1356a82_32c2402, },
	// [13]ID_LABLE_PROG_OR_EVENT
	{D_CTRL_LABEL, 0, 184, 548, 18, 74, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c1356aeb_08c7298, },
	// [14]ID_IMG_UP
	{D_CTRL_LABEL, 0, 272, 547, 18, 36, 20, 30, -1, (D_FrameCtrlDescr*)&GUID_c1356bc7_2bf6537, },
	// [15]ID_IMG_DOWN
	{D_CTRL_LABEL, 0, 272, 564, 18, 36, 20, 30, -1, (D_FrameCtrlDescr*)&GUID_c1356c75_1c55ecd, },
	// [16]ID_LABLE_UP_DOWN
	{D_CTRL_LABEL, 0, 314, 548, 18, 81, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c1356ca4_31c265, },
	// [17]ID_IMG_DAY_LEFT
	{D_CTRL_LABEL, 0, 393, 545, 18, 20, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c1356d3d_30d5f03, },
	// [18]ID_IMG_DAY_RIGHT
	{D_CTRL_LABEL, 0, 412, 545, 18, 20, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c1356d6b_2fd12cf, },
	// [19]ID_LABLE_DAY_TITLE
	{D_CTRL_LABEL, 0, 446, 548, 18, 69, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c1356db6_3992976, },
	// [20]ID_SCROLL_CHAN
	{D_CTRL_SCROLL, 3, 494, 11, 2, 6, 200, 30, -1, (D_FrameCtrlDescr*)&GUID_c13a725f_2421b11, },
	// [21]ID_SCROLL_EVENT
	{D_CTRL_SCROLL, 4, 493, 6, 2, 6, 200, 30, -1, (D_FrameCtrlDescr*)&GUID_c13a7379_3992559, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_epg_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_epg_window[22];
D_Frame atv_epg_window = {
	run_ctrls_atv_epg_window, 
	ctrl_description_of_atv_epg_window, 
	atv_epg_window_init, 
};

