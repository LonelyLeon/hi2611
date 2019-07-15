/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-03-05 13:51:16

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2019-01-16 16:05:50.130

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
#define	ID_MOVIE_LIST_GROUP_ALL	1
#define	ID_MOVIE_LIST_GROUP_FILES	2
#define	ID_MOVIE_LIST_IMAGE_FILEICON_0	3
#define	ID_MOVIE_LIST_IMAGE_FILEICON_1	4
#define	ID_MOVIE_LIST_IMAGE_FILEICON_2	5
#define	ID_MOVIE_LIST_IMAGE_FILEICON_3	6
#define	ID_MOVIE_LIST_IMAGE_FILEICON_4	7
#define	ID_MOVIE_LIST_IMAGE_FILEICON_5	8
#define	ID_MOVIE_LIST_IMAGE_FILEICON_6	9
#define	ID_MOVIE_LIST_IMAGE_FILEICON_7	10
#define	ID_MOVIE_LIST_IMAGE_FILEICON_8	11
#define	ID_MOVIE_LIST_IMAGE_FILEICON_9	12
#define	ID_MOVIE_LIST_IMAGE_FILEICON_10	13
#define	ID_MOVIE_LIST_IMAGE_FILEICON_11	14
#define	ID_MOVIE_LIST_IMAGE_FILEICON_12	15
#define	ID_MOVIE_LIST_IMAGE_FILEICON_13	16
#define	ID_MOVIE_LIST_IMAGE_FILEICON_14	17
#define	ID_MOVIE_LIST_BUTTON_FILENAME_0	18
#define	ID_MOVIE_LIST_BUTTON_FILENAME_1	19
#define	ID_MOVIE_LIST_BUTTON_FILENAME_2	20
#define	ID_MOVIE_LIST_BUTTON_FILENAME_3	21
#define	ID_MOVIE_LIST_BUTTON_FILENAME_4	22
#define	ID_MOVIE_LIST_BUTTON_FILENAME_5	23
#define	ID_MOVIE_LIST_BUTTON_FILENAME_6	24
#define	ID_MOVIE_LIST_BUTTON_FILENAME_7	25
#define	ID_MOVIE_LIST_BUTTON_FILENAME_8	26
#define	ID_MOVIE_LIST_BUTTON_FILENAME_9	27
#define	ID_MOVIE_LIST_BUTTON_FILENAME_10	28
#define	ID_MOVIE_LIST_BUTTON_FILENAME_11	29
#define	ID_MOVIE_LIST_BUTTON_FILENAME_12	30
#define	ID_MOVIE_LIST_BUTTON_FILENAME_13	31
#define	ID_MOVIE_LIST_BUTTON_FILENAME_14	32
#define	ID_MOVIE_LIST_LABEL_FILENAME	33
#define	ID_MUSIC_GROUP_ALL	34
#define	ID_MUSIC_GROUP_PLAY	35
#define	ID_MUSIC_GROUP_CONTROL	36
#define	ID_MUSIC_LABEL_STATUS	37
#define	ID_MUSIC_GROUP_PROGRESS	38
#define	ID_MUSIC_PROGRESS	39
#define	ID_MUSIC_LABEL_TIME	40
#define	ID_MUSIC_IMG_PLAY_STATUS	41
#define	ID_MUSIC_LABEL_LYRIC	42
#define	ID_MUSIC_MODE_BOTTOM	43
#define	ID_MUSIC_PLAY_MODE_0	44
#define	ID_MUSIC_LABEL_SONG_NAME	45

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cae05a_2d9e661={-1, atv_IMG_ID_FS_WHITE_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7b2aa2b_3b925cd={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7b2aa2b_3b94d41={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_yellow, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7b7763a_1192307={-1, -1, -1, &atv_fmt_left_middle_h00_v00_signal_whilte_scroll_R2L, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c0735c_2421380={-1, atv_IMG_ID_FS_BUTTON_GRAY, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c037bf_29f1eb={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c07896_261174a={atv_COLOR_ENUM_101, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5883547_3c84236={-1, -1, -1, &atv_fmt_left_middle_h00_v00_signal_black_scroll_R2L, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c14ca046_0ea538={-1, atv_IMG_ID_atv_IMG_ID_BUTTON_Green, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a190fa_3d829={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_MOVIE_LIST_GROUP_ALL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b8848b_1674850={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_MOVIE_LIST_GROUP_FILES"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a2c1_0da12db={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3050={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3051={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3052={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3053={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3054={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3055={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3056={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3057={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3058={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3059={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3060={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3061={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3062={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_13"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3063={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_MOVIE_LIST_IMAGE_FILEICON_14"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2a977_08c3064={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b40={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b41={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b42={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b43={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b44={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b45={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b46={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b47={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b48={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b49={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [28]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b50={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [29]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b51={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [30]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b52={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [31]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_13"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b53={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [32]{D_CTRL_BUTTON}	"ID_MOVIE_LIST_BUTTON_FILENAME_14"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b2aa2b_3b95b54={{&GUID_c7b2aa2b_3b925cd, &GUID_c7b2aa2b_3b94d41, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [33]{D_CTRL_LABEL}	"ID_MOVIE_LIST_LABEL_FILENAME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b7763a_1197756={{&GUID_c7b7763a_1192307, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [34]{D_CTRL_GROUP}	"ID_MUSIC_GROUP_ALL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c84a08d2_15735={{&GUID_c4cae05a_2d9e661, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [35]{D_CTRL_GROUP}	"ID_MUSIC_GROUP_PLAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c05703_0ea1d82={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [36]{D_CTRL_GROUP}	"ID_MUSIC_GROUP_CONTROL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c0735c_2426972={{&GUID_c4c0735c_2421380, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [37]{D_CTRL_LABEL}	"ID_MUSIC_LABEL_STATUS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c0751a_1197874={{&GUID_c4c037bf_29f1eb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [38]{D_CTRL_GROUP}	"ID_MUSIC_GROUP_PROGRESS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c075e2_16779b3={{&GUID_c4c0735c_2421380, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [39]{D_CTRL_PROGRESS}	"ID_MUSIC_PROGRESS"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_c4c07896_2615cbf={{&GUID_c4c07896_261174a, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_106, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [40]{D_CTRL_LABEL}	"ID_MUSIC_LABEL_TIME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c07a89_157ba1={{&GUID_c4c037bf_29f1eb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [41]{D_CTRL_IMAGE}	"ID_MUSIC_IMG_PLAY_STATUS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c38aff_2034697={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [42]{D_CTRL_LABEL}	"ID_MUSIC_LABEL_LYRIC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5883547_3c835={{&GUID_c5883547_3c84236, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [43]{D_CTRL_LABEL}	"ID_MUSIC_MODE_BOTTOM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c14ca046_0ea1d6d={{&GUID_c14ca046_0ea538, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [44]{D_CTRL_LABEL}	"ID_MUSIC_PLAY_MODE_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c15284b7_31c3d6c={{&GUID_c4c037bf_29f1eb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [45]{D_CTRL_LABEL}	"ID_MUSIC_LABEL_SONG_NAME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c037bf_29f26e9={{&GUID_c4c037bf_29f1eb, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_music_list_menu_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 960, 540, 0, -1, (D_FrameCtrlDescr*)&GUID_c7a190fa_3d829, },
	// [1]ID_MOVIE_LIST_GROUP_ALL
	{D_CTRL_GROUP, 0, 0, 0, 20, 960, 414, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b8848b_1674850, },
	// [2]ID_MOVIE_LIST_GROUP_FILES
	{D_CTRL_GROUP, 1, 82, 81, 0, 796, 322, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a2c1_0da12db, },
	// [3]ID_MOVIE_LIST_IMAGE_FILEICON_0
	{D_CTRL_LABEL, 2, 48, 22, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3050, },
	// [4]ID_MOVIE_LIST_IMAGE_FILEICON_1
	{D_CTRL_LABEL, 2, 213, 22, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3051, },
	// [5]ID_MOVIE_LIST_IMAGE_FILEICON_2
	{D_CTRL_LABEL, 2, 377, 22, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3052, },
	// [6]ID_MOVIE_LIST_IMAGE_FILEICON_3
	{D_CTRL_LABEL, 2, 542, 22, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3053, },
	// [7]ID_MOVIE_LIST_IMAGE_FILEICON_4
	{D_CTRL_LABEL, 2, 707, 22, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3054, },
	// [8]ID_MOVIE_LIST_IMAGE_FILEICON_5
	{D_CTRL_LABEL, 2, 48, 124, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3055, },
	// [9]ID_MOVIE_LIST_IMAGE_FILEICON_6
	{D_CTRL_LABEL, 2, 213, 124, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3056, },
	// [10]ID_MOVIE_LIST_IMAGE_FILEICON_7
	{D_CTRL_LABEL, 2, 377, 124, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3057, },
	// [11]ID_MOVIE_LIST_IMAGE_FILEICON_8
	{D_CTRL_LABEL, 2, 542, 124, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3058, },
	// [12]ID_MOVIE_LIST_IMAGE_FILEICON_9
	{D_CTRL_LABEL, 2, 707, 124, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3059, },
	// [13]ID_MOVIE_LIST_IMAGE_FILEICON_10
	{D_CTRL_LABEL, 2, 48, 226, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3060, },
	// [14]ID_MOVIE_LIST_IMAGE_FILEICON_11
	{D_CTRL_LABEL, 2, 213, 226, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3061, },
	// [15]ID_MOVIE_LIST_IMAGE_FILEICON_12
	{D_CTRL_LABEL, 2, 377, 226, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3062, },
	// [16]ID_MOVIE_LIST_IMAGE_FILEICON_13
	{D_CTRL_LABEL, 2, 542, 226, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3063, },
	// [17]ID_MOVIE_LIST_IMAGE_FILEICON_14
	{D_CTRL_LABEL, 2, 707, 226, 30, 40, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b2a977_08c3064, },
	// [18]ID_MOVIE_LIST_BUTTON_FILENAME_0
	{D_CTRL_BUTTON, 2, 18, 74, 30, 100, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b40, },
	// [19]ID_MOVIE_LIST_BUTTON_FILENAME_1
	{D_CTRL_BUTTON, 2, 183, 74, 30, 100, 26, 30, 4, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b41, },
	// [20]ID_MOVIE_LIST_BUTTON_FILENAME_2
	{D_CTRL_BUTTON, 2, 347, 74, 30, 100, 26, 30, 5, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b42, },
	// [21]ID_MOVIE_LIST_BUTTON_FILENAME_3
	{D_CTRL_BUTTON, 2, 512, 74, 30, 100, 26, 30, 6, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b43, },
	// [22]ID_MOVIE_LIST_BUTTON_FILENAME_4
	{D_CTRL_BUTTON, 2, 677, 74, 30, 100, 26, 30, 7, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b44, },
	// [23]ID_MOVIE_LIST_BUTTON_FILENAME_5
	{D_CTRL_BUTTON, 2, 18, 176, 30, 100, 26, 30, 8, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b45, },
	// [24]ID_MOVIE_LIST_BUTTON_FILENAME_6
	{D_CTRL_BUTTON, 2, 183, 176, 30, 100, 26, 30, 9, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b46, },
	// [25]ID_MOVIE_LIST_BUTTON_FILENAME_7
	{D_CTRL_BUTTON, 2, 347, 176, 30, 100, 26, 30, 10, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b47, },
	// [26]ID_MOVIE_LIST_BUTTON_FILENAME_8
	{D_CTRL_BUTTON, 2, 512, 176, 30, 100, 26, 30, 11, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b48, },
	// [27]ID_MOVIE_LIST_BUTTON_FILENAME_9
	{D_CTRL_BUTTON, 2, 677, 176, 30, 100, 26, 30, 12, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b49, },
	// [28]ID_MOVIE_LIST_BUTTON_FILENAME_10
	{D_CTRL_BUTTON, 2, 18, 278, 30, 100, 26, 30, 13, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b50, },
	// [29]ID_MOVIE_LIST_BUTTON_FILENAME_11
	{D_CTRL_BUTTON, 2, 183, 278, 30, 100, 26, 30, 14, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b51, },
	// [30]ID_MOVIE_LIST_BUTTON_FILENAME_12
	{D_CTRL_BUTTON, 2, 347, 278, 30, 100, 26, 30, 15, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b52, },
	// [31]ID_MOVIE_LIST_BUTTON_FILENAME_13
	{D_CTRL_BUTTON, 2, 512, 278, 30, 100, 26, 30, 16, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b53, },
	// [32]ID_MOVIE_LIST_BUTTON_FILENAME_14
	{D_CTRL_BUTTON, 2, 677, 278, 30, 100, 26, 30, 17, (D_FrameCtrlDescr*)&GUID_c7b2aa2b_3b95b54, },
	// [33]ID_MOVIE_LIST_LABEL_FILENAME
	{D_CTRL_LABEL, 1, 84, 51, 0, 792, 24, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b7763a_1197756, },
	// [34]ID_MUSIC_GROUP_ALL
	{D_CTRL_GROUP, 0, 0, 413, 20, 960, 94, 30, -1, (D_FrameCtrlDescr*)&GUID_c84a08d2_15735, },
	// [35]ID_MUSIC_GROUP_PLAY
	{D_CTRL_GROUP, 34, 26, 6, 20, 907, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c05703_0ea1d82, },
	// [36]ID_MUSIC_GROUP_CONTROL
	{D_CTRL_GROUP, 35, 4, 0, -2, 133, 34, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c0735c_2426972, },
	// [37]ID_MUSIC_LABEL_STATUS
	{D_CTRL_LABEL, 36, 61, 4, -2, 67, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c0751a_1197874, },
	// [38]ID_MUSIC_GROUP_PROGRESS
	{D_CTRL_GROUP, 35, 154, 2, -2, 746, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c075e2_16779b3, },
	// [39]ID_MUSIC_PROGRESS
	{D_CTRL_PROGRESS, 38, 11, 12, 0, 540, 5, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c07896_2615cbf, },
	// [40]ID_MUSIC_LABEL_TIME
	{D_CTRL_LABEL, 38, 563, 2, 0, 175, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c07a89_157ba1, },
	// [41]ID_MUSIC_IMG_PLAY_STATUS
	{D_CTRL_IMAGE, 36, 10, 2, -2, 40, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c38aff_2034697, },
	// [42]ID_MUSIC_LABEL_LYRIC
	{D_CTRL_LABEL, 34, 179, 68, 20, 600, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c5883547_3c835, },
	// [43]ID_MUSIC_MODE_BOTTOM
	{D_CTRL_LABEL, 34, 745, 49, 20, 27, 12, 30, -1, (D_FrameCtrlDescr*)&GUID_c14ca046_0ea1d6d, },
	// [44]ID_MUSIC_PLAY_MODE_0
	{D_CTRL_LABEL, 34, 785, 42, 20, 133, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c15284b7_31c3d6c, },
	// [45]ID_MUSIC_LABEL_SONG_NAME
	{D_CTRL_LABEL, 34, 179, 42, 20, 550, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c037bf_29f26e9, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	music_list_menu_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_music_list_menu_window[46];
D_Frame music_list_menu_window = {
	run_ctrls_music_list_menu_window, 
	ctrl_description_of_music_list_menu_window, 
	music_list_menu_window_init, 
};

