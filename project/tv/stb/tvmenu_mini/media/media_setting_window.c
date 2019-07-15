/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-02-19 15:13:23

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2018-11-19 14:07:05.183

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
#define	ID_SETTING_GROUP_BACKGROUND	1
#define	ID_SETTING_GROUP_PICTURE_PLAY	2
#define	ID_SETTING_LABEL_PICTURE_PLAY	3
#define	ID_SETTING_IMAGE_LEFT	4
#define	ID_SETTING_IMAGE_RIGHT	5
#define	ID_SETTING_SELECT_SPEED	6
#define	ID_SETTING_LABEL_SET	7

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c222f9_1e45e42={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_NULL, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c22504_1487e1c={-1, -1, atv_IDS_PICTURE_SPEED, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c226c8_14856a1={-1, atv_IMG_ID_sub_menu_direc_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c227bd_03e317b={-1, atv_IMG_ID_sub_menu_direc_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c2c612_09b82a1={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c2282a_09c61b1={-1, atv_IMG_ID_FS_BUTTON_YELLOW, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c845644e_01f61ca={-1, -1, atv_IDS_SETTING, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7b84d14_0a218f8={-1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c04a28_1b529={{&GUID_c7b84d14_0a218f8, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_SETTING_GROUP_BACKGROUND"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c21237_0ab2180={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_SETTING_GROUP_PICTURE_PLAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c222f9_1e459dd={{&GUID_c4c222f9_1e45e42, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_SETTING_LABEL_PICTURE_PLAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c22504_1486124={{&GUID_c4c22504_1487e1c, &GUID_c4c22504_1487e1c, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_IMAGE}	"ID_SETTING_IMAGE_LEFT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c226c8_1485ea9={{&GUID_c4c226c8_14856a1, &GUID_c4c226c8_14856a1, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_IMAGE}	"ID_SETTING_IMAGE_RIGHT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c227bd_03e6f0d={{&GUID_c4c227bd_03e317b, &GUID_c4c227bd_03e317b, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_SELECT}	"ID_SETTING_SELECT_SPEED"
static PREFIXCONST D_TextID POSTCONST GUID_c4c2293e_1a51080[]={atv_IDS_LOW_SPEED, atv_IDS_MIDDLE_SPEED, atv_IDS_HIGH_SPEED, };
static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c4c2282a_09c5108={{&GUID_c4c2c612_09b82a1, &GUID_c4c2282a_09c61b1, NULL, }, 1, 3, GUID_c4c2293e_1a51080, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_SETTING_LABEL_SET"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c845644e_01f7d8a={{&GUID_c845644e_01f61ca, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_media_setting_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 960, 420, 0, -1, (D_FrameCtrlDescr*)&GUID_c4c04a28_1b529, },
	// [1]ID_SETTING_GROUP_BACKGROUND
	{D_CTRL_GROUP, 0, 72, 79, 20, 816, 336, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c21237_0ab2180, },
	// [2]ID_SETTING_GROUP_PICTURE_PLAY
	{D_CTRL_GROUP, 1, 23, 23, -57, 750, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c222f9_1e459dd, },
	// [3]ID_SETTING_LABEL_PICTURE_PLAY
	{D_CTRL_LABEL, 2, 30, 2, 0, 159, 26, 30, 7, (D_FrameCtrlDescr*)&GUID_c4c22504_1486124, },
	// [4]ID_SETTING_IMAGE_LEFT
	{D_CTRL_IMAGE, 2, 394, 6, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c226c8_1485ea9, },
	// [5]ID_SETTING_IMAGE_RIGHT
	{D_CTRL_IMAGE, 2, 635, 6, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c227bd_03e6f0d, },
	// [6]ID_SETTING_SELECT_SPEED
	{D_CTRL_SELECT, 2, 380, 0, 0, 281, 30, 30, 7, (D_FrameCtrlDescr*)&GUID_c4c2282a_09c5108, },
	// [7]ID_SETTING_LABEL_SET
	{D_CTRL_LABEL, 0, 74, 51, 20, 812, 24, 30, -1, (D_FrameCtrlDescr*)&GUID_c845644e_01f7d8a, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	media_setting_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_media_setting_window[8];
D_Frame media_setting_window = {
	run_ctrls_media_setting_window, 
	ctrl_description_of_media_setting_window, 
	media_setting_window_init, 
};

