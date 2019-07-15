/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY"
	update/create time:	2017-11-16 18:46:50

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-04-06 16:33:25.000

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
#define	ID_MOVIE_GROUP_ALL	1
#define	ID_MOVIE_GROUP	2
#define	ID_MOVIE_BUTTON_0	3
#define	ID_MOVIE_BUTTON_1	4
#define	ID_MOVIE_BUTTON_2	5
#define	ID_MOVIE_BUTTON_3	6
#define	ID_MOVIE_BUTTON_4	7
#define	ID_MOVIE_BUTTON_5	8
#define	ID_MOVIE_BUTTON_6	9
#define	ID_MOVIE_IMG_LOGO	10
#define	ID_MOVIE_LABEL_0	11
#define	ID_MOVIE_LABEL_1	12
#define	ID_MOVIE_LABEL_2	13
#define	ID_MOVIE_LABEL_3	14
#define	ID_MOVIE_LABEL_4	15
#define	ID_MOVIE_LABEL_5	16
#define	ID_MOVIE_LABEL_6	17
#define	ID_MOVIE_PATH_LABEL	18
#define	ID_MOVIE_MING_LEFT	19
#define	ID_MOVIE_IMGE_RIGHT	20
#define	ID_MOVIE_LABEL_WIN	21
#define	ID_MOVIE_LANEL_PLAY_VIDEO	22
#define	ID_MOVIE_LABEL_NAME	23
#define	ID_MOVIE_LABEL_MOVE_BOTTON	24
#define	ID_MOVIE_LABEL_MOVE	25
#define	ID_MOVIE_LABEL_MOVE_TITLE	26
#define	ID_MOVIE_LABEL_OK_BOTTOM	27
#define	ID_MOVIE_LABEL_OK	28
#define	ID_MOVIE_LABEL_OK_TITLE	29
#define	ID_MOVIEW_PLAY_MODE	30
#define	ID_MOVIE_GREEN_SHOW	31
#define	ID_MOVIE_CONTROL_PLAY_MODE	32
#define	ID_MOVIE_IMAGE_PLAY_MODE	33

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c439aa_271c8b={-1, atv_IMG_ID_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ca5298_167786={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ca5298_17717c2={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_whilte_scroll_R2L, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cca42c_13841bb={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cca42c_381bb41={-1, -1, -1, &atv_fmt_left_top_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cca77c_31c10ac={-1, atv_IMB_ID_COMB_small_window, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cca96d_38a55eb={atv_COLOR_ENUM_0, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cd6fba_2af1a5f={-1, atv_IMG_ID_hint_button, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cd740b_29f1681={-1, atv_IMG_ID_hint_direction, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cd74bf_29015be={-1, -1, atv_IDS_MOVE, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cd86cf_30d659f={-1, -1, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cd8894_3a92471={-1, -1, atv_IDS_OK, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c474c38c_0cbfe6={-1, atv_IMG_ID_Green, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c474c3f9_2bf7ec7={-1, -1, atv_IDS_PLAY_MODE, &atv_fmt_left_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c439aa_271778d={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_MOVIE_GROUP_ALL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cabacee2_1771eb={{&GUID_c4c439aa_271c8b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_MOVIE_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c988a8_07d2895={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_MOVIE_BUTTON_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c98a24_0ab30f7={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_MOVIE_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c98b61_16762cb={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_MOVIE_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c98c25_09c9ca={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_BUTTON}	"ID_MOVIE_BUTTON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c98ce8_30d6c35={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_BUTTON}	"ID_MOVIE_BUTTON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c98d55_2512821={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_BUTTON}	"ID_MOVIE_BUTTON_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c98e1a_38a7b13={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_BUTTON}	"ID_MOVIE_BUTTON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c98e79_3b927cc={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_IMAGE}	"ID_MOVIE_IMG_LOGO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c9e28d_2fd6f24={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ca5298_1673af0={{&GUID_c4ca5298_167786, &GUID_c4ca5298_17717c2, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ca53bb_34bbd1={{&GUID_c4ca5298_167786, &GUID_c4ca5298_17717c2, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ca5439_1284a44={{&GUID_c4ca5298_167786, &GUID_c4ca5298_17717c2, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ca54e3_213559b={{&GUID_c4ca5298_167786, &GUID_c4ca5298_17717c2, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ca554e_34b37ae={{&GUID_c4ca5298_167786, &GUID_c4ca5298_17717c2, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ca5b27_00f3ca0={{&GUID_c4ca5298_167786, &GUID_c4ca5298_17717c2, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ca710d_0fa1649={{&GUID_c4ca5298_167786, &GUID_c4ca5298_17717c2, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_LABEL}	"ID_MOVIE_PATH_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cca42c_1385af1={{&GUID_c4cca42c_381bb41, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_IMAGE}	"ID_MOVIE_MING_LEFT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cca50a_1094cd9={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_IMAGE}	"ID_MOVIE_IMGE_RIGHT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cca5f7_03e4ef5={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_WIN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cca77c_31c1016={{&GUID_c4cca77c_31c10ac, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_LABEL}	"ID_MOVIE_LANEL_PLAY_VIDEO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cca96d_38a7ff6={{&GUID_c4cca96d_38a55eb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_NAME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cd6d76_1c55af1={{&GUID_c4ca5298_167786, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_MOVE_BOTTON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cd6fba_2af312a={{&GUID_c4cd6fba_2af1a5f, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_MOVE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cd740b_29fd34={{&GUID_c4cd740b_29f1681, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_MOVE_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cd74bf_2904844={{&GUID_c4cd74bf_29015be, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_OK_BOTTOM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cd76cf_07d44c={{&GUID_c4cd6fba_2af1a5f, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [28]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cd86cf_30d5ce3={{&GUID_c4cd86cf_30d659f, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [29]{D_CTRL_LABEL}	"ID_MOVIE_LABEL_OK_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cd8894_3a9196e={{&GUID_c4cd8894_3a92471, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [30]{D_CTRL_LABEL}	"ID_MOVIEW_PLAY_MODE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c474c256_3a9714a={{&GUID_c4cca42c_13841bb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [31]{D_CTRL_LABEL}	"ID_MOVIE_GREEN_SHOW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c474c38c_0cb432b={{&GUID_c474c38c_0cbfe6, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [32]{D_CTRL_LABEL}	"ID_MOVIE_CONTROL_PLAY_MODE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c474c3f9_2bf5a44={{&GUID_c474c3f9_2bf7ec7, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [33]{D_CTRL_IMAGE}	"ID_MOVIE_IMAGE_PLAY_MODE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c475b09d_2424357={{NULL, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_media_movie_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 1280, 720, 0, -1, (D_FrameCtrlDescr*)&GUID_c4c439aa_271778d, },
	// [1]ID_MOVIE_GROUP_ALL
	{D_CTRL_GROUP, 0, 0, 0, 20, 1280, 720, 30, -1, (D_FrameCtrlDescr*)&GUID_cabacee2_1771eb, },
	// [2]ID_MOVIE_GROUP
	{D_CTRL_GROUP, 1, 84, 452, 0, 1113, 155, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c988a8_07d2895, },
	// [3]ID_MOVIE_BUTTON_0
	{D_CTRL_BUTTON, 2, 0, 0, 0, 151, 112, 30, 11, (D_FrameCtrlDescr*)&GUID_c4c98a24_0ab30f7, },
	// [4]ID_MOVIE_BUTTON_1
	{D_CTRL_BUTTON, 2, 160, 0, 0, 152, 112, 30, 12, (D_FrameCtrlDescr*)&GUID_c4c98b61_16762cb, },
	// [5]ID_MOVIE_BUTTON_2
	{D_CTRL_BUTTON, 2, 320, 0, 0, 152, 113, 30, 13, (D_FrameCtrlDescr*)&GUID_c4c98c25_09c9ca, },
	// [6]ID_MOVIE_BUTTON_3
	{D_CTRL_BUTTON, 2, 480, 0, 0, 154, 113, 30, 14, (D_FrameCtrlDescr*)&GUID_c4c98ce8_30d6c35, },
	// [7]ID_MOVIE_BUTTON_4
	{D_CTRL_BUTTON, 2, 640, 0, 0, 153, 113, 30, 15, (D_FrameCtrlDescr*)&GUID_c4c98d55_2512821, },
	// [8]ID_MOVIE_BUTTON_5
	{D_CTRL_BUTTON, 2, 800, 0, 0, 153, 113, 30, 16, (D_FrameCtrlDescr*)&GUID_c4c98e1a_38a7b13, },
	// [9]ID_MOVIE_BUTTON_6
	{D_CTRL_BUTTON, 2, 960, 0, 0, 153, 113, 30, 17, (D_FrameCtrlDescr*)&GUID_c4c98e79_3b927cc, },
	// [10]ID_MOVIE_IMG_LOGO
	{D_CTRL_IMAGE, 1, 34, 59, 20, 236, 60, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c9e28d_2fd6f24, },
	// [11]ID_MOVIE_LABEL_0
	{D_CTRL_LABEL, 2, 0, 118, 0, 151, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ca5298_1673af0, },
	// [12]ID_MOVIE_LABEL_1
	{D_CTRL_LABEL, 2, 160, 118, 0, 151, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ca53bb_34bbd1, },
	// [13]ID_MOVIE_LABEL_2
	{D_CTRL_LABEL, 2, 320, 118, 0, 151, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ca5439_1284a44, },
	// [14]ID_MOVIE_LABEL_3
	{D_CTRL_LABEL, 2, 480, 118, 0, 154, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ca54e3_213559b, },
	// [15]ID_MOVIE_LABEL_4
	{D_CTRL_LABEL, 2, 640, 118, 0, 153, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ca554e_34b37ae, },
	// [16]ID_MOVIE_LABEL_5
	{D_CTRL_LABEL, 2, 800, 118, 0, 153, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ca5b27_00f3ca0, },
	// [17]ID_MOVIE_LABEL_6
	{D_CTRL_LABEL, 2, 960, 118, 0, 153, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ca710d_0fa1649, },
	// [18]ID_MOVIE_PATH_LABEL
	{D_CTRL_LABEL, 1, 84, 658, 20, 619, 60, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cca42c_1385af1, },
	// [19]ID_MOVIE_MING_LEFT
	{D_CTRL_IMAGE, 1, 51, 485, 20, 24, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cca50a_1094cd9, },
	// [20]ID_MOVIE_IMGE_RIGHT
	{D_CTRL_IMAGE, 1, 1204, 484, 20, 24, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cca5f7_03e4ef5, },
	// [21]ID_MOVIE_LABEL_WIN
	{D_CTRL_LABEL, 1, 376, 66, 20, 532, 337, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cca77c_31c1016, },
	// [22]ID_MOVIE_LANEL_PLAY_VIDEO
	{D_CTRL_LABEL, 21, 17, 9, 0, 498, 299, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cca96d_38a7ff6, },
	// [23]ID_MOVIE_LABEL_NAME
	{D_CTRL_LABEL, 1, 386, 406, 20, 510, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cd6d76_1c55af1, },
	// [24]ID_MOVIE_LABEL_MOVE_BOTTON
	{D_CTRL_LABEL, 1, 712, 655, 20, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cd6fba_2af312a, },
	// [25]ID_MOVIE_LABEL_MOVE
	{D_CTRL_LABEL, 24, 32, 3, 0, 30, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cd740b_29fd34, },
	// [26]ID_MOVIE_LABEL_MOVE_TITLE
	{D_CTRL_LABEL, 1, 818, 657, 20, 60, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cd74bf_2904844, },
	// [27]ID_MOVIE_LABEL_OK_BOTTOM
	{D_CTRL_LABEL, 1, 884, 655, 20, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cd76cf_07d44c, },
	// [28]ID_MOVIE_LABEL_OK
	{D_CTRL_LABEL, 27, 1, 3, 0, 97, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cd86cf_30d5ce3, },
	// [29]ID_MOVIE_LABEL_OK_TITLE
	{D_CTRL_LABEL, 1, 995, 657, 20, 61, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cd8894_3a9196e, },
	// [30]ID_MOVIEW_PLAY_MODE
	{D_CTRL_LABEL, 1, 81, 123, 20, 125, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c474c256_3a9714a, },
	// [31]ID_MOVIE_GREEN_SHOW
	{D_CTRL_LABEL, 1, 1071, 664, 20, 30, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c474c38c_0cb432b, },
	// [32]ID_MOVIE_CONTROL_PLAY_MODE
	{D_CTRL_LABEL, 1, 1118, 658, 20, 120, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c474c3f9_2bf5a44, },
	// [33]ID_MOVIE_IMAGE_PLAY_MODE
	{D_CTRL_IMAGE, 1, 34, 123, 20, 40, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c475b09d_2424357, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_media_movie_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_media_movie_window[34];
D_Frame atv_media_movie_window = {
	run_ctrls_atv_media_movie_window, 
	ctrl_description_of_atv_media_movie_window, 
	atv_media_movie_window_init, 
};

