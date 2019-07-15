/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2018-01-30 16:18:26

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-04-19 13:59:09.343

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
#define	ID_SOUND_LABEL_SOUND_SETTING	1
#define	ID_SOUND_GROUP	2
#define	ID_SOUND_GROUP_4	3
#define	ID_SOUND_GROUP_6	4
#define	ID_SOUND_GROUP_12	5
#define	ID_SOUND_GROUP_13	6
#define	ID_SOUND_BUTTON_4	7
#define	ID_SOUND_BUTTON_6	8
#define	ID_SOUND_BUTTON_12	9
#define	ID_SOUND_BUTTON_13	10
#define	ID_SOUND_LABEL_VALUE12	11

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, atv_IDS_SOUND, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1402d9b_2321547={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1402e4f_26179dc={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c14e4de1_30d2475={-1, atv_IMG_ID_FS_FACTORY_YELLOW, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c480eff7_10941bb={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_grey, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_SOUND_LABEL_SOUND_SETTING"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_SOUND_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda8768_3c81b4b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_SOUND_GROUP_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e35_1d45af1={{NULL, &GUID_c14e4de1_30d2475, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_SOUND_GROUP_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1402d3b_0fa124={{NULL, &GUID_c14e4de1_30d2475, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_SOUND_GROUP_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1402d3b_3dfe589={{NULL, &GUID_c14e4de1_30d2475, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_SOUND_GROUP_13"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5065b8a_1862cd6={{NULL, &GUID_c14e4de1_30d2475, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_BUTTON}	"ID_SOUND_BUTTON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4df5={{&GUID_c1402e4f_26179dc, &GUID_c1402d9b_2321547, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_BUTTON}	"ID_SOUND_BUTTON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1402d9b_2324d06={{&GUID_c1402e4f_26179dc, &GUID_c1402d9b_2321547, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_BUTTON}	"ID_SOUND_BUTTON_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1402d9b_4fde9369={{&GUID_c1402e4f_26179dc, &GUID_c1402d9b_2321547, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_BUTTON}	"ID_SOUND_BUTTON_13"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5065ce1_1575af1={{&GUID_c1402e4f_26179dc, &GUID_c1402d9b_2321547, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_SOUND_LABEL_VALUE12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c480eff7_1095af1={{&GUID_c480eff7_10941bb, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_sound_setting_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 485, 660, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_SOUND_LABEL_SOUND_SETTING
	{D_CTRL_LABEL, 0, 111, 7, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_SOUND_GROUP
	{D_CTRL_GROUP, 0, 0, 37, 20, 485, 621, 30, -1, (D_FrameCtrlDescr*)&GUID_beda8768_3c81b4b, },
	// [3]ID_SOUND_GROUP_4
	{D_CTRL_GROUP, 2, 2, 6, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e35_1d45af1, },
	// [4]ID_SOUND_GROUP_6
	{D_CTRL_GROUP, 2, 2, 40, 0, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c1402d3b_0fa124, },
	// [5]ID_SOUND_GROUP_12
	{D_CTRL_GROUP, 2, 2, 74, 0, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c1402d3b_3dfe589, },
	// [6]ID_SOUND_GROUP_13
	{D_CTRL_GROUP, 2, 2, 108, 0, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c5065b8a_1862cd6, },
	// [7]ID_SOUND_BUTTON_4
	{D_CTRL_BUTTON, 3, 21, 2, 0, 220, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_beda356d_29f4df5, },
	// [8]ID_SOUND_BUTTON_6
	{D_CTRL_BUTTON, 4, 21, 2, 0, 220, 26, 30, 4, (D_FrameCtrlDescr*)&GUID_c1402d9b_2324d06, },
	// [9]ID_SOUND_BUTTON_12
	{D_CTRL_BUTTON, 5, 21, 2, 0, 220, 26, 30, 5, (D_FrameCtrlDescr*)&GUID_c1402d9b_4fde9369, },
	// [10]ID_SOUND_BUTTON_13
	{D_CTRL_BUTTON, 6, 21, 2, 0, 220, 26, 30, 6, (D_FrameCtrlDescr*)&GUID_c5065ce1_1575af1, },
	// [11]ID_SOUND_LABEL_VALUE12
	{D_CTRL_LABEL, 5, 314, 0, 0, 100, 28, 30, -1, (D_FrameCtrlDescr*)&GUID_c480eff7_1095af1, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	sound_setting_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_sound_setting_window[12];
D_Frame sound_setting_window = {
	run_ctrls_sound_setting_window, 
	ctrl_description_of_sound_setting_window, 
	sound_setting_window_init, 
};

