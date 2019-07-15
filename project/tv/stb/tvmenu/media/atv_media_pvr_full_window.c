/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2015-02-02 13:06:02

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2014-12-16 16:55:09.290

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
#define	ID_MEDIA_PVR_GROUP	1
#define	ID_MEDIA_PVR_CONTROL_GROUP	2
#define	ID_MEDIA_PVR_LAST	3
#define	ID_MEDIA_PVR_PLAY	4
#define	ID_MEDIA_PVR_NEXT	5
#define	ID_MEDIA_PVR_PROGRESS	6
#define	ID_MEDIA_PVR_CURR_TIME	7
#define	ID_MEDIA_PVR_TOTAL_TIME	8

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf08f737_2034823={atv_COLOR_ENUM_0, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf94315d_1b54823={-1, atv_IMG_ID_FS_picture_menu_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf943742_3b93a25={-1, atv_IMG_ID_media_pause, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf9438ee_2fd6ef0={-1, atv_IMG_ID_picture_menu_last, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf94398b_3a91a85={-1, atv_IMG_ID_picture_menu_next, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf944b9d_3b95c14={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf9456f6_2223511={-1, atv_IMG_ID_FS_Media_Stop_Focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf9457ba_2131e3a={-1, atv_IMG_ID_FS_Media_Last_Focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf94581f_2804101={-1, atv_IMG_ID_FS_Media_Next_focus, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf08f737_20329={{&GUID_bf08f737_2034823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_MEDIA_PVR_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf94315d_1b529={{&GUID_bf94315d_1b54823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_MEDIA_PVR_CONTROL_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf9436d9_1776853={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_MEDIA_PVR_LAST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf9438ee_2fd156e={{&GUID_bf9438ee_2fd6ef0, &GUID_bf9457ba_2131e3a, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_MEDIA_PVR_PLAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf943742_3b94ff1={{&GUID_bf943742_3b93a25, &GUID_bf9456f6_2223511, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_MEDIA_PVR_NEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf94398b_3a94a4c={{&GUID_bf94398b_3a91a85, &GUID_bf94581f_2804101, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_PROGRESS}	"ID_MEDIA_PVR_PROGRESS"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_bf943a18_1287fac={{NULL, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_105, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_MEDIA_PVR_CURR_TIME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf944b9d_3b937e5={{&GUID_bf944b9d_3b95c14, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_MEDIA_PVR_TOTAL_TIME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf944c54_2af3612={{&GUID_bf944b9d_3b95c14, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_media_pvr_full_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 1280, 720, 0, -1, (D_FrameCtrlDescr*)&GUID_bf08f737_20329, },
	// [1]ID_MEDIA_PVR_GROUP
	{D_CTRL_GROUP, 0, 295, 575, 20, 694, 108, 30, -1, (D_FrameCtrlDescr*)&GUID_bf94315d_1b529, },
	// [2]ID_MEDIA_PVR_CONTROL_GROUP
	{D_CTRL_GROUP, 1, 134, 52, 0, 425, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_bf9436d9_1776853, },
	// [3]ID_MEDIA_PVR_LAST
	{D_CTRL_BUTTON, 2, 12, 0, 0, 48, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_bf9438ee_2fd156e, },
	// [4]ID_MEDIA_PVR_PLAY
	{D_CTRL_BUTTON, 2, 187, 0, 0, 48, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_bf943742_3b94ff1, },
	// [5]ID_MEDIA_PVR_NEXT
	{D_CTRL_BUTTON, 2, 366, 0, 0, 48, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_bf94398b_3a94a4c, },
	// [6]ID_MEDIA_PVR_PROGRESS
	{D_CTRL_PROGRESS, 1, 22, 27, 0, 650, 1, 30, -1, (D_FrameCtrlDescr*)&GUID_bf943a18_1287fac, },
	// [7]ID_MEDIA_PVR_CURR_TIME
	{D_CTRL_LABEL, 1, 13, 32, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bf944b9d_3b937e5, },
	// [8]ID_MEDIA_PVR_TOTAL_TIME
	{D_CTRL_LABEL, 1, 584, 32, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bf944c54_2af3612, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_media_pvr_full_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_media_pvr_full_window[9];
D_Frame atv_media_pvr_full_window = {
	run_ctrls_atv_media_pvr_full_window, 
	ctrl_description_of_atv_media_pvr_full_window, 
	atv_media_pvr_full_window_init, 
};

