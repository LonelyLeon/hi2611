/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2014-12-23 10:17:51

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2014-12-15 16:03:25.890

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
#define	ID_SETTING_IMAGE_SETTING	1
#define	ID_SETTING_LABEL_MOVE_ICON	2
#define	ID_SETTING_LABEL_MOVE	3
#define	ID_SETTING_LABEL_OK_ICON	4
#define	ID_SETTING_LABEL_OK	5
#define	ID_SETTING_GROUP_BACKGROUND	6
#define	ID_SETTING_GROUP_PICTURE_PLAY	7
#define	ID_SETTING_LABEL_PICTURE_PLAY	8
#define	ID_SETTING_IMAGE_LEFT	9
#define	ID_SETTING_IMAGE_RIGHT	10
#define	ID_SETTING_SELECT_SPEED	11

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c04a28_1b54823={-1, atv_IMG_ID_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c04f1d_08c81e={-1, atv_IMG_ID_title_setting, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c09c82_1a53016={-1, atv_IMG_ID_FS_Move, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c09cf5_2ce5071={-1, -1, atv_IDS_MOVE, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c09d4e_35b57ad={-1, atv_IMG_ID_hint_button, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c09df3_2033a34={-1, -1, atv_IDS_OK, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c21237_0ab1a80={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c222f9_1e45e42={-1, atv_IMG_ID_COMB_music_select, atv_IDS_NULL, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c222f9_1e4e32={-1, atv_IMG_ID_COMB_music_select_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c22504_1487e1c={-1, -1, atv_IDS_PICTURE_SPEED, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c226c8_14856a1={-1, atv_IMG_ID_search_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c227bd_03e317b={-1, atv_IMG_ID_search_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c2282a_09c4f17={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c2282a_09c61b1={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c04a28_1b529={{&GUID_c4c04a28_1b54823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_SETTING_IMAGE_SETTING"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c04f1d_08ccd3={{&GUID_c4c04f1d_08c81e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_SETTING_LABEL_MOVE_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c09c82_1a5211e={{&GUID_c4c09c82_1a53016, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_SETTING_LABEL_MOVE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c09cf5_2ce287a={{&GUID_c4c09cf5_2ce5071, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_SETTING_LABEL_OK_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c09d4e_35bae3={{&GUID_c4c09d4e_35b57ad, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_SETTING_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c09df3_203520e={{&GUID_c4c09df3_2033a34, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_SETTING_GROUP_BACKGROUND"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c21237_0ab2180={{&GUID_c4c21237_0ab1a80, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_GROUP}	"ID_SETTING_GROUP_PICTURE_PLAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c222f9_1e459dd={{&GUID_c4c222f9_1e45e42, &GUID_c4c222f9_1e4e32, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_SETTING_LABEL_PICTURE_PLAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c22504_1486124={{&GUID_c4c22504_1487e1c, &GUID_c4c22504_1487e1c, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_IMAGE}	"ID_SETTING_IMAGE_LEFT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c226c8_1485ea9={{&GUID_c4c226c8_14856a1, &GUID_c4c226c8_14856a1, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_IMAGE}	"ID_SETTING_IMAGE_RIGHT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c227bd_03e6f0d={{&GUID_c4c227bd_03e317b, &GUID_c4c227bd_03e317b, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_SELECT}	"ID_SETTING_SELECT_SPEED"
static PREFIXCONST D_TextID POSTCONST GUID_c4c2293e_1a51080[]={atv_IDS_LOW_SPEED, atv_IDS_MIDDLE_SPEED, atv_IDS_HIGH_SPEED, };
static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c4c2282a_09c5108={{&GUID_c4c2282a_09c4f17, &GUID_c4c2282a_09c61b1, NULL, }, 1, 3, GUID_c4c2293e_1a51080, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_media_setting_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 1280, 720, 0, -1, (D_FrameCtrlDescr*)&GUID_c4c04a28_1b529, },
	// [1]ID_SETTING_IMAGE_SETTING
	{D_CTRL_IMAGE, 0, 84, 70, 20, 280, 56, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c04f1d_08ccd3, },
	// [2]ID_SETTING_LABEL_MOVE_ICON
	{D_CTRL_LABEL, 0, 812, 660, 20, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c09c82_1a5211e, },
	// [3]ID_SETTING_LABEL_MOVE
	{D_CTRL_LABEL, 0, 920, 668, 20, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c09cf5_2ce287a, },
	// [4]ID_SETTING_LABEL_OK_ICON
	{D_CTRL_LABEL, 0, 1028, 660, 20, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c09d4e_35bae3, },
	// [5]ID_SETTING_LABEL_OK
	{D_CTRL_LABEL, 0, 1136, 668, 20, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c09df3_203520e, },
	// [6]ID_SETTING_GROUP_BACKGROUND
	{D_CTRL_GROUP, 0, 84, 136, 20, 1112, 474, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c21237_0ab2180, },
	// [7]ID_SETTING_GROUP_PICTURE_PLAY
	{D_CTRL_GROUP, 6, 40, 94, 0, 1016, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c222f9_1e459dd, },
	// [8]ID_SETTING_LABEL_PICTURE_PLAY
	{D_CTRL_LABEL, 7, 36, 5, 0, 208, 30, 30, 7, (D_FrameCtrlDescr*)&GUID_c4c22504_1486124, },
	// [9]ID_SETTING_IMAGE_LEFT
	{D_CTRL_IMAGE, 7, 616, 14, 0, 12, 12, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c226c8_1485ea9, },
	// [10]ID_SETTING_IMAGE_RIGHT
	{D_CTRL_IMAGE, 7, 956, 14, 0, 12, 12, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c227bd_03e6f0d, },
	// [11]ID_SETTING_SELECT_SPEED
	{D_CTRL_SELECT, 7, 693, 5, 0, 208, 30, 30, 7, (D_FrameCtrlDescr*)&GUID_c4c2282a_09c5108, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	media_setting_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_media_setting_window[12];
D_Frame media_setting_window = {
	run_ctrls_media_setting_window, 
	ctrl_description_of_media_setting_window, 
	media_setting_window_init, 
};

