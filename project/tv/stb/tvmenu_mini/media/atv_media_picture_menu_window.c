/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-03-05 13:54:16

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
#define	ID_PICFULL_GROUP_MENU	1
#define	ID_PICFULL_BUTTON_PLAY	2
#define	ID_PICFULL_LABLE_PLAY	3
#define	ID_PICFULL_BUTTON_LAST	4
#define	ID_PICFULL_LABLE_LAST	5
#define	ID_PICFULL_BUTTON_NEXT	6
#define	ID_PICFULL_LABLE_NEXT	7
#define	ID_PICFULL_BUTTON_LEFTROTATE	8
#define	ID_PICFULL_LABEL_LEFTROTATE	9
#define	ID_PICFULL_BUTTON_RIGHTROTATE	10
#define	ID_PICFULL_LABLE_RIGHTROTATE	11

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5662ab3_09c29={-1, atv_IMG_ID_FS_WHITE_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5667da1_0fa6d39={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5668237_280382a={-1, atv_IMG_ID_FS_Media_PictureMenu_Last, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5668237_28014ec={-1, atv_IMG_ID_FS_Media_PictureMenu_Last_Focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5668368_05d457={-1, -1, atv_IDS_LAST, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5669c16_2ce34f0={-1, atv_IMG_ID_FS_Media_PictureMenu_Next, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5669c16_2ce4a69={-1, atv_IMG_ID_FS_Media_PictureMenu_Next_Focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5669cc5_1093a20={-1, -1, atv_IDS_NEXT, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c566a10c_1194ba0={-1, atv_IMG_ID_FS_Media_PictureMenu_LeftRotate, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c566a10c_119582d={-1, atv_IMG_ID_FS_Media_PictureMenu_LeftRotate_Focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c566a1de_119792b={-1, -1, atv_IDS_ROTATE, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c566a376_0fa1f32={-1, atv_IMG_ID_FS_Media_PictureMenu_RightRotate, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c566a376_0fa7bd1={-1, atv_IMG_ID_FS_Media_PictureMenu_RightRotate_Focus, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5656e89_29029={{&GUID_c5662ab3_09c29, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_PICFULL_GROUP_MENU"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56776c7_2de4823={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_PICFULL_BUTTON_PLAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5667c2b_2af21e9={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_PICFULL_LABLE_PLAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5667da1_0fa2987={{&GUID_c5667da1_0fa6d39, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_PICFULL_BUTTON_LAST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5668237_280b3d={{&GUID_c5668237_280382a, &GUID_c5668237_28014ec, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_PICFULL_LABLE_LAST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5668368_05d4fe={{&GUID_c5668368_05d457, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_BUTTON}	"ID_PICFULL_BUTTON_NEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5669c16_2ce5547={{&GUID_c5669c16_2ce34f0, &GUID_c5669c16_2ce4a69, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_PICFULL_LABLE_NEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5669cc5_1095c90={{&GUID_c5669cc5_1093a20, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_BUTTON}	"ID_PICFULL_BUTTON_LEFTROTATE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c566a10c_11937ca={{&GUID_c566a10c_1194ba0, &GUID_c566a10c_119582d, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_PICFULL_LABEL_LEFTROTATE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c566a1de_1196ae8={{&GUID_c566a1de_119792b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_BUTTON}	"ID_PICFULL_BUTTON_RIGHTROTATE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c566a376_0fa149e={{&GUID_c566a376_0fa1f32, &GUID_c566a376_0fa7bd1, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_PICFULL_LABLE_RIGHTROTATE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c566a3f9_290f68={{&GUID_c566a1de_119792b, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_media_picture_menu_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 27, 422, 0, 907, 80, 0, -1, (D_FrameCtrlDescr*)&GUID_c5656e89_29029, },
	// [1]ID_PICFULL_GROUP_MENU
	{D_CTRL_GROUP, 0, 0, 0, -8, 907, 80, 30, -1, (D_FrameCtrlDescr*)&GUID_c56776c7_2de4823, },
	// [2]ID_PICFULL_BUTTON_PLAY
	{D_CTRL_BUTTON, 1, 106, 11, 1, 36, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c5667c2b_2af21e9, },
	// [3]ID_PICFULL_LABLE_PLAY
	{D_CTRL_LABEL, 0, 73, 48, -8, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c5667da1_0fa2987, },
	// [4]ID_PICFULL_BUTTON_LAST
	{D_CTRL_BUTTON, 1, 271, 11, 1, 36, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c5668237_280b3d, },
	// [5]ID_PICFULL_LABLE_LAST
	{D_CTRL_LABEL, 0, 238, 48, -8, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c5668368_05d4fe, },
	// [6]ID_PICFULL_BUTTON_NEXT
	{D_CTRL_BUTTON, 1, 436, 11, 1, 36, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c5669c16_2ce5547, },
	// [7]ID_PICFULL_LABLE_NEXT
	{D_CTRL_LABEL, 0, 403, 48, -8, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c5669cc5_1095c90, },
	// [8]ID_PICFULL_BUTTON_LEFTROTATE
	{D_CTRL_BUTTON, 1, 601, 11, 1, 36, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c566a10c_11937ca, },
	// [9]ID_PICFULL_LABEL_LEFTROTATE
	{D_CTRL_LABEL, 0, 568, 48, -8, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c566a1de_1196ae8, },
	// [10]ID_PICFULL_BUTTON_RIGHTROTATE
	{D_CTRL_BUTTON, 1, 766, 11, 1, 36, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c566a376_0fa149e, },
	// [11]ID_PICFULL_LABLE_RIGHTROTATE
	{D_CTRL_LABEL, 0, 733, 48, -8, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c566a3f9_290f68, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_media_picture_menu_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_media_picture_menu_window[12];
D_Frame atv_media_picture_menu_window = {
	run_ctrls_atv_media_picture_menu_window, 
	ctrl_description_of_atv_media_picture_menu_window, 
	atv_media_picture_menu_window_init, 
};

