/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2017-07-26 15:05:09

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-07-18 16:19:49.390

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
#define	ID_PICTURE_OPTIMIZE_LABLE_TITLE	1
#define	ID_PICTURE_OPTIMIZE_GROUP_DNR	2
#define	ID_PICTURE_OPTIMIZE_LABLE_DNR	3
#define	ID_PICTURE_OPTIMIZE_LABLE_LEFT	4
#define	ID_PICTURE_OPTIMIZE_SELECT_SPEED	5
#define	ID_PICTURE_OPTIMIZE_LABLE_RIGHT	6

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a176ab_2bf2b51={-1, -1, atv_IDS_PICTURE_OPTIMIZE, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b64a5d_167298a={-1, atv_IMG_ID_FS_WHITE_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bc5431_1b57625={-1, -1, atv_IDS_DNR, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c564230b_1865eaa={-1, atv_IMG_ID_FS_BUTTON_GRAY, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c564230b_18624f3={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c564230b_1861d6a={-1, atv_IMG_ID_sub_menu_direc_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c564230b_1863bff={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c564230b_1864a80={-1, atv_IMG_ID_sub_menu_direc_right, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{&GUID_c4b64a5d_167298a, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_PICTURE_OPTIMIZE_LABLE_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a176ab_2bf43a5={{&GUID_c4a176ab_2bf2b51, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_PICTURE_OPTIMIZE_GROUP_DNR"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b64c0e_1d42a6d={{&GUID_c564230b_1865eaa, &GUID_c564230b_18624f3, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_PICTURE_OPTIMIZE_LABLE_DNR"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1bab7_242c0b={{&GUID_c4bc5431_1b57625, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_PICTURE_OPTIMIZE_LABLE_LEFT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1bdc7_03e841={{&GUID_c564230b_1861d6a, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_SELECT}	"ID_PICTURE_OPTIMIZE_SELECT_SPEED"
static PREFIXCONST D_TextID POSTCONST GUID_c5642ec7_2de2982[]={atv_IDS_HIGH, atv_IDS_MIDDLE, atv_IDS_LOW, atv_IDS_OFF, };
static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c4a1bf17_36b75d0={{&GUID_c564230b_1863bff, NULL, NULL, }, 1, 4, GUID_c5642ec7_2de2982, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_PICTURE_OPTIMIZE_LABLE_RIGHT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1c0fd_2ce2794={{&GUID_c564230b_1864a80, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_picture_optimize_setting_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 180, 178, 0, 360, 220, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_PICTURE_OPTIMIZE_LABLE_TITLE
	{D_CTRL_LABEL, 0, 117, 18, 0, 143, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a176ab_2bf43a5, },
	// [2]ID_PICTURE_OPTIMIZE_GROUP_DNR
	{D_CTRL_GROUP, 0, 10, 64, 20, 339, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b64c0e_1d42a6d, },
	// [3]ID_PICTURE_OPTIMIZE_LABLE_DNR
	{D_CTRL_LABEL, 2, 2, 0, -78, 115, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1bab7_242c0b, },
	// [4]ID_PICTURE_OPTIMIZE_LABLE_LEFT
	{D_CTRL_LABEL, 2, 162, 7, -78, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1bdc7_03e841, },
	// [5]ID_PICTURE_OPTIMIZE_SELECT_SPEED
	{D_CTRL_SELECT, 2, 200, 0, -78, 91, 32, 30, 2, (D_FrameCtrlDescr*)&GUID_c4a1bf17_36b75d0, },
	// [6]ID_PICTURE_OPTIMIZE_LABLE_RIGHT
	{D_CTRL_LABEL, 2, 317, 7, -78, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1c0fd_2ce2794, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	picture_optimize_setting_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_picture_optimize_setting_window[7];
D_Frame picture_optimize_setting_window = {
	run_ctrls_picture_optimize_setting_window, 
	ctrl_description_of_picture_optimize_setting_window, 
	picture_optimize_setting_window_init, 
};

