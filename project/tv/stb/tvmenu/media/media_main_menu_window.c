/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-07-01 14:02:27

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2019-05-14 14:18:09.300

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
#define	ID_MAIN_MENU_IMAGE_MEDIA	1
#define	ID_MAINMENU_BUTTON_MOVIE	2
#define	ID_MAINMENU_BUTTON_MUSIC	3
#define	ID_MAINMENU_BUTTON_PICTURE	4
#define	ID_MAINMENU_BUTTON_PVR	5
#define	ID_MAINMENU_LABEL_MOVIE	6
#define	ID_MAINMENU_LABEL_MUSIC	7
#define	ID_MAINMENU_LABEL_PICTURE	8
#define	ID_MAINMENU_LABEL_PVR	9
#define	ID_MAINMENU_LABEL_USB_ICON	10
#define	ID_MAINMENU_LABEL_USB	11
#define	ID_MAINMENU_LABEL_MOVE_ICON	12
#define	ID_MAINMENU_LABEL_MOVE	13
#define	ID_MAINMENU_LABEL_OK_ICON	14
#define	ID_MAINMENU_LABEL_OK	15

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c04a28_1b54823={-1, atv_IMG_ID_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c04f1d_08c81e={-1, atv_IMG_ID_title_usb, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c085de_0fa7d82={-1, atv_IMG_ID_FS_Media_movie, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c085de_0fa29dc={-1, atv_IMG_ID_FS_Media_Movie_Focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c0864e_29f693d={-1, atv_IMG_ID_FS_Media_Music, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c0864e_29f2260={-1, atv_IMG_ID_FS_Media_Music_Focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c086e9_2bf4e4f={-1, atv_IMG_ID_FS_Media_Picture, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c086e9_2bf58b2={-1, atv_IMG_ID_FS_Media_Picture_Focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c09944_000105b={-1, -1, atv_IDS_MOVIE, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c09a1b_1c54f2d={-1, -1, atv_IDS_MUSIC, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c09ade_0cbb2b={-1, -1, atv_IDS_PICTURE, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c09bbb_2ee5725={-1, atv_IMG_ID_usb_small, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c09c24_3b91d8b={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c09c82_1a53016={-1, atv_IMG_ID_FS_Move, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c09cf5_2ce5071={-1, -1, atv_IDS_MOVE, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c09d4e_35b57ad={-1, atv_IMG_ID_hint_button, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c09df3_2033a34={-1, -1, atv_IDS_OK, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf0060a8_2de4823={-1, atv_IMG_ID_FS_Media_Normal, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf0060a8_2de18be={-1, atv_IMG_ID_FS_Media_PVR_FOCUS, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf0071ca_05d3d6c={-1, -1, atv_IDS_PVR, &atv_fmt_center_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c04a28_1b529={{&GUID_c4c04a28_1b54823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_IMAGE}	"ID_MAIN_MENU_IMAGE_MEDIA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c04f1d_08ccd3={{&GUID_c4c04f1d_08c81e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_MAINMENU_BUTTON_MOVIE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c085de_0fa61f5={{&GUID_c4c085de_0fa7d82, &GUID_c4c085de_0fa29dc, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_MAINMENU_BUTTON_MUSIC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c0864e_29f4371={{&GUID_c4c0864e_29f693d, &GUID_c4c0864e_29f2260, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_MAINMENU_BUTTON_PICTURE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c086e9_2bf1d9c={{&GUID_c4c086e9_2bf4e4f, &GUID_c4c086e9_2bf58b2, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_MAINMENU_BUTTON_PVR"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf0060a8_2de29={{&GUID_bf0060a8_2de4823, &GUID_bf0060a8_2de18be, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_MOVIE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c09944_00011f={{&GUID_c4c09944_000105b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_MUSIC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c09a1b_1c5613a={{&GUID_c4c09a1b_1c54f2d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_PICTURE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c09ade_0cb5cd2={{&GUID_c4c09ade_0cbb2b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_PVR"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf0071ca_05d4ae1={{&GUID_bf0071ca_05d3d6c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_USB_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c09bbb_2eebe={{&GUID_c4c09bbb_2ee5725, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_USB"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c09c24_3b964e={{&GUID_c4c09c24_3b91d8b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_MOVE_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c09c82_1a5211e={{&GUID_c4c09c82_1a53016, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_MOVE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c09cf5_2ce287a={{&GUID_c4c09cf5_2ce5071, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_OK_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c09d4e_35bae3={{&GUID_c4c09d4e_35b57ad, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c09df3_203520e={{&GUID_c4c09df3_2033a34, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_media_main_menu_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 1280, 720, 0, -1, (D_FrameCtrlDescr*)&GUID_c4c04a28_1b529, },
	// [1]ID_MAIN_MENU_IMAGE_MEDIA
	{D_CTRL_IMAGE, 0, 84, 70, 20, 180, 56, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c04f1d_08ccd3, },
	// [2]ID_MAINMENU_BUTTON_MOVIE
	{D_CTRL_BUTTON, 0, 212, 441, 20, 152, 112, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c085de_0fa61f5, },
	// [3]ID_MAINMENU_BUTTON_MUSIC
	{D_CTRL_BUTTON, 0, 446, 442, 20, 152, 112, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c0864e_29f4371, },
	// [4]ID_MAINMENU_BUTTON_PICTURE
	{D_CTRL_BUTTON, 0, 680, 442, 20, 152, 112, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c086e9_2bf1d9c, },
	// [5]ID_MAINMENU_BUTTON_PVR
	{D_CTRL_BUTTON, 0, 914, 442, 20, 152, 112, 30, -1, (D_FrameCtrlDescr*)&GUID_bf0060a8_2de29, },
	// [6]ID_MAINMENU_LABEL_MOVIE
	{D_CTRL_LABEL, 0, 252, 568, 20, 72, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c09944_00011f, },
	// [7]ID_MAINMENU_LABEL_MUSIC
	{D_CTRL_LABEL, 0, 486, 568, 20, 72, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c09a1b_1c5613a, },
	// [8]ID_MAINMENU_LABEL_PICTURE
	{D_CTRL_LABEL, 0, 720, 568, 20, 72, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c09ade_0cb5cd2, },
	// [9]ID_MAINMENU_LABEL_PVR
	{D_CTRL_LABEL, 0, 940, 568, 20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bf0071ca_05d4ae1, },
	// [10]ID_MAINMENU_LABEL_USB_ICON
	{D_CTRL_LABEL, 0, 84, 668, 20, 74, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c09bbb_2eebe, },
	// [11]ID_MAINMENU_LABEL_USB
	{D_CTRL_LABEL, 0, 166, 668, 20, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c09c24_3b964e, },
	// [12]ID_MAINMENU_LABEL_MOVE_ICON
	{D_CTRL_LABEL, 0, 802, 660, 20, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c09c82_1a5211e, },
	// [13]ID_MAINMENU_LABEL_MOVE
	{D_CTRL_LABEL, 0, 910, 663, 20, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c09cf5_2ce287a, },
	// [14]ID_MAINMENU_LABEL_OK_ICON
	{D_CTRL_LABEL, 0, 1018, 660, 20, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c09d4e_35bae3, },
	// [15]ID_MAINMENU_LABEL_OK
	{D_CTRL_LABEL, 0, 1126, 663, 20, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c09df3_203520e, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	media_main_menu_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_media_main_menu_window[16];
D_Frame media_main_menu_window = {
	run_ctrls_media_main_menu_window, 
	ctrl_description_of_media_main_menu_window, 
	media_main_menu_window_init, 
};

