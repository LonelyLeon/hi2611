/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2015-05-18 13:50:12

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-05-13 17:11:10.881

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
#define	ID_MUSIC_LABEL_SONG_NAME	1
#define	ID_MUSIC_GROUP_LIST	2
#define	ID_MUSIC_GROUP_PLAY	3
#define	ID_LABEL_BOTTOM_0	4
#define	ID_MUSIC_LABEL_PATH	5
#define	ID_MUSIC_LIST	6
#define	ID_MUSIC_GROUP_CONTROL	7
#define	ID_MUSIC_LABEL_STATUS	8
#define	ID_MUSIC_GROUP_PROGRESS	9
#define	ID_MUSIC_PROGRESS	10
#define	ID_MUSIC_LABEL_TIME	11
#define	ID_MUSIC_IMG_PLAY_STATUS	12
#define	ID_MUSIC_SCROLL	13
#define	ID_MUSIC_IMG_LOGO	14
#define	ID_MUSIC_IMG_MUSIC_ICON	15
#define	ID_MUSIC_MOVE_BOTTOM	16
#define	ID_MUSIC_MOVE_ICON	17
#define	ID_MUSIC_MOVE_LABEL	18
#define	ID_MUSIC_OK_BOTTOM	19
#define	ID_MUSIC_OK_ICON	20
#define	ID_MUSIC_OK_0	21
#define	ID_MUSIC_LABEL_LYRIC	22
#define	ID_MUSIC_PLAY_MODE	23
#define	ID_MUSIC_MODE_BOTTOM	24
#define	ID_MUSIC_PLAY_MODE_0	25
#define	D_FRAMECONTROL_PLAY_MODE	26

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c0347a_2fd4823={-1, atv_IMG_ID_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c037bf_29f1eb={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cca42c_381bb41={-1, -1, -1, &atv_fmt_left_top_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c05639_1964823={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c05703_0eadc2={atv_COLOR_ENUM_14, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c0735c_2421380={-1, atv_IMG_ID_voice_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c075e2_1674804={-1, atv_IMG_ID_FS_White_Round_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c07896_261174a={atv_COLOR_ENUM_101, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c1bc28_37a2cd6={-1, atv_IMG_ID_COMB_music_select, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c1bc28_37a72ae={-1, atv_IMG_ID_COMB_music_select_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c25251_06d70f5={-1, -1, -1, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c25251_06d1477={-1, -1, -1, &atv_fmt_left_middle_h10_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cfb09f_1c54ae1={-1, atv_IMG_ID_hint_button, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cfb108_3b96952={-1, atv_IMG_ID_hint_direction, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cfb163_31c5af1={-1, -1, atv_IDS_MOVE, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cfb219_2517e87={-1, -1, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cfb276_167124={-1, -1, atv_IDS_OK, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5883547_3c84236={-1, -1, -1, &atv_fmt_center_middle_h00_v00_signal_black_scroll_R2L, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5903296_128764f={atv_COLOR_ENUM_21, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c14ca046_0ea538={-1, atv_IMG_ID_Green, atv_IDS_NULL, &atv_fmt_center_middle_h00_v00_multi_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c15394e8_2133d6c={-1, -1, atv_IDS_PLAY_MODE, &atv_fmt_left_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c0347a_2fd29={{&GUID_c4c0347a_2fd4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_MUSIC_LABEL_SONG_NAME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c037bf_29f26e9={{&GUID_c4c037bf_29f1eb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_MUSIC_GROUP_LIST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c05639_19629={{&GUID_c4c05639_1964823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_MUSIC_GROUP_PLAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c05703_0ea1d82={{&GUID_c4c05703_0eadc2, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_LABEL_BOTTOM_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5903296_1284ac2={{&GUID_c5903296_128764f, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_MUSIC_LABEL_PATH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c0581b_3c84612={{&GUID_c4cca42c_381bb41, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LIST}	"ID_MUSIC_LIST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514={{&GUID_c4c1bc28_37a2cd6, &GUID_c4c1bc28_37a72ae, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c05d25_1576816_GUID_c4c25510_33c125e={{NULL, NULL, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080={{&GUID_c4c25251_06d70f5, &GUID_c4c25251_06d1477, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c4c05d25_1575a43[]={
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
};

static PREFIXCONST D_Coord POSTCONST list_ctrl_GUID_c4c05d25_1577c1e[4]={30, 60, 630, 30, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c4c05d25_1571e9e[9][4]=
{
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
};
static PREFIXCONST D_FrameListDescr POSTCONST GUID_c4c05d25_1576816={{NULL, NULL, NULL, }, 1, 9, 9, 9, 4, 40, list_ctrl_GUID_c4c05d25_1577c1e, 8, 0, D_LIST_FOCUS_TYPE_ROW, list_ctrl_GUID_c4c05d25_1571e9e, list_ctrl_GUID_c4c05d25_1575a43, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_GROUP}	"ID_MUSIC_GROUP_CONTROL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c0735c_2426972={{&GUID_c4c0735c_2421380, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_MUSIC_LABEL_STATUS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c0751a_1197874={{&GUID_c4c037bf_29f1eb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_GROUP}	"ID_MUSIC_GROUP_PROGRESS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c075e2_16779b3={{&GUID_c4c075e2_1674804, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_PROGRESS}	"ID_MUSIC_PROGRESS"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_c4c07896_2615cbf={{&GUID_c4c07896_261174a, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_106, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_MUSIC_LABEL_TIME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c07a89_157ba1={{&GUID_c4c037bf_29f1eb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_IMAGE}	"ID_MUSIC_IMG_PLAY_STATUS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c38aff_2034697={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_SCROLL}	"ID_MUSIC_SCROLL"
static PREFIXCONST D_FrameScrollBarDescr POSTCONST GUID_c4c42754_17718be={{&GUID_c4c07896_261174a, NULL, NULL, }, 1, 100, 10, 1, {-1, -1, -1, atv_IMG_ID_scrool_one, }, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_IMAGE}	"ID_MUSIC_IMG_LOGO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c429f3_1f46c5c={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_IMAGE}	"ID_MUSIC_IMG_MUSIC_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cea17c_1e42e7e={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_MUSIC_MOVE_BOTTOM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cfb09f_1c56784={{&GUID_c4cfb09f_1c54ae1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_MUSIC_MOVE_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cfb108_3b972ae={{&GUID_c4cfb108_3b96952, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_LABEL}	"ID_MUSIC_MOVE_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cfb163_31c6df1={{&GUID_c4cfb163_31c5af1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_LABEL}	"ID_MUSIC_OK_BOTTOM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cfb1c4_0fa1eb={{&GUID_c4cfb09f_1c54ae1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_LABEL}	"ID_MUSIC_OK_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cfb219_251153c={{&GUID_c4cfb219_2517e87, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_MUSIC_OK_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cfb276_16799={{&GUID_c4cfb276_167124, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_LABEL}	"ID_MUSIC_LABEL_LYRIC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5883547_3c835={{&GUID_c5883547_3c84236, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_LABEL}	"ID_MUSIC_PLAY_MODE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c14c9d55_2ee41bb={{&GUID_c15394e8_2133d6c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_LABEL}	"ID_MUSIC_MODE_BOTTOM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c14ca046_0ea1d6d={{&GUID_c14ca046_0ea538, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_LABEL}	"ID_MUSIC_PLAY_MODE_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c15284b7_31c3d6c={{&GUID_c4c037bf_29f1eb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_IMAGE}	"D_FRAMECONTROL_PLAY_MODE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c20dc1a3_25144eb={{NULL, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_media_music_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 1280, 720, 0, -1, (D_FrameCtrlDescr*)&GUID_c4c0347a_2fd29, },
	// [1]ID_MUSIC_LABEL_SONG_NAME
	{D_CTRL_LABEL, 0, 574, 35, 20, 700, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c037bf_29f26e9, },
	// [2]ID_MUSIC_GROUP_LIST
	{D_CTRL_GROUP, 0, 230, 124, 20, 820, 456, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c05639_19629, },
	// [3]ID_MUSIC_GROUP_PLAY
	{D_CTRL_GROUP, 0, 50, 586, 20, 1180, 66, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c05703_0ea1d82, },
	// [4]ID_LABEL_BOTTOM_0
	{D_CTRL_LABEL, 3, 6, 5, 0, 1168, 55, 30, -1, (D_FrameCtrlDescr*)&GUID_c5903296_1284ac2, },
	// [5]ID_MUSIC_LABEL_PATH
	{D_CTRL_LABEL, 0, 88, 666, 20, 615, 60, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c0581b_3c84612, },
	// [6]ID_MUSIC_LIST
	{D_CTRL_LIST, 2, 27, 17, 0, 750, 424, 30, 13, (D_FrameCtrlDescr*)&GUID_c4c05d25_1576816, },
	// [7]ID_MUSIC_GROUP_CONTROL
	{D_CTRL_GROUP, 4, 27, 3, 0, 158, 52, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c0735c_2426972, },
	// [8]ID_MUSIC_LABEL_STATUS
	{D_CTRL_LABEL, 7, 84, 9, 0, 52, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c0751a_1197874, },
	// [9]ID_MUSIC_GROUP_PROGRESS
	{D_CTRL_GROUP, 4, 211, 7, 0, 933, 43, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c075e2_16779b3, },
	// [10]ID_MUSIC_PROGRESS
	{D_CTRL_PROGRESS, 9, 27, 16, 0, 715, 5, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c07896_2615cbf, },
	// [11]ID_MUSIC_LABEL_TIME
	{D_CTRL_LABEL, 9, 751, 6, 0, 174, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c07a89_157ba1, },
	// [12]ID_MUSIC_IMG_PLAY_STATUS
	{D_CTRL_IMAGE, 7, 25, 2, 0, 45, 45, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c38aff_2034697, },
	// [13]ID_MUSIC_SCROLL
	{D_CTRL_SCROLL, 2, 800, 16, 0, 5, 420, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c42754_17718be, },
	// [14]ID_MUSIC_IMG_LOGO
	{D_CTRL_IMAGE, 0, 14, 62, 20, 214, 57, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c429f3_1f46c5c, },
	// [15]ID_MUSIC_IMG_MUSIC_ICON
	{D_CTRL_IMAGE, 0, 522, 27, 20, 35, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cea17c_1e42e7e, },
	// [16]ID_MUSIC_MOVE_BOTTOM
	{D_CTRL_LABEL, 0, 712, 665, 20, 101, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cfb09f_1c56784, },
	// [17]ID_MUSIC_MOVE_ICON
	{D_CTRL_LABEL, 16, 32, 3, 0, 32, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cfb108_3b972ae, },
	// [18]ID_MUSIC_MOVE_LABEL
	{D_CTRL_LABEL, 0, 821, 669, 20, 64, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cfb163_31c6df1, },
	// [19]ID_MUSIC_OK_BOTTOM
	{D_CTRL_LABEL, 0, 897, 665, 20, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cfb1c4_0fa1eb, },
	// [20]ID_MUSIC_OK_ICON
	{D_CTRL_LABEL, 19, 2, 3, 0, 96, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cfb219_251153c, },
	// [21]ID_MUSIC_OK_0
	{D_CTRL_LABEL, 0, 1004, 669, 20, 59, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cfb276_16799, },
	// [22]ID_MUSIC_LABEL_LYRIC
	{D_CTRL_LABEL, 0, 304, 80, 20, 664, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c5883547_3c835, },
	// [23]ID_MUSIC_PLAY_MODE
	{D_CTRL_LABEL, 0, 1119, 672, 20, 120, 20, 30, -1, (D_FrameCtrlDescr*)&GUID_c14c9d55_2ee41bb, },
	// [24]ID_MUSIC_MODE_BOTTOM
	{D_CTRL_LABEL, 0, 1072, 675, 20, 35, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c14ca046_0ea1d6d, },
	// [25]ID_MUSIC_PLAY_MODE_0
	{D_CTRL_LABEL, 0, 81, 123, 20, 125, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c15284b7_31c3d6c, },
	// [26]D_FRAMECONTROL_PLAY_MODE
	{D_CTRL_IMAGE, 0, 33, 123, 20, 40, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c20dc1a3_25144eb, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_media_music_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_media_music_window[27];
D_Frame atv_media_music_window = {
	run_ctrls_atv_media_music_window, 
	ctrl_description_of_atv_media_music_window, 
	atv_media_music_window_init, 
};

