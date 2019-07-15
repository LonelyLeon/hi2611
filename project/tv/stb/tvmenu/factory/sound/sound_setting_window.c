/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-04-08 10:48:55

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2018-10-23 11:43:09.109

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
#define	ID_SOUND_GROUP_14	7
#define	ID_SOUND_BUTTON_4	8
#define	ID_SOUND_BUTTON_6	9
#define	ID_SOUND_BUTTON_12	10
#define	ID_SOUND_BUTTON_13	11
#define	ID_SOUND_BUTTON_14	12
#define	ID_SOUND_LABEL_VALUE12	13

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, atv_IDS_SOUND, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1402d9b_2321547={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1402e4f_26179dc={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c14e4de1_30d2475={-1, atv_IMG_ID_box_focus, -1, NULL, };
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
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c50595a6_2426443={{NULL, &GUID_c14e4de1_30d2475, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_GROUP}	"ID_SOUND_GROUP_14"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c93170d4_06d39b3={{NULL, &GUID_c14e4de1_30d2475, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_BUTTON}	"ID_SOUND_BUTTON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4df5={{&GUID_c1402e4f_26179dc, &GUID_c1402d9b_2321547, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_BUTTON}	"ID_SOUND_BUTTON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1402d9b_2324d06={{&GUID_c1402e4f_26179dc, &GUID_c1402d9b_2321547, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_BUTTON}	"ID_SOUND_BUTTON_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1402d9b_4fde9369={{&GUID_c1402e4f_26179dc, &GUID_c1402d9b_2321547, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_BUTTON}	"ID_SOUND_BUTTON_13"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c50596ce_04e701f={{&GUID_c1402e4f_26179dc, &GUID_c1402d9b_2321547, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_BUTTON}	"ID_SOUND_BUTTON_14"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9317150_3cf3602={{&GUID_c1402e4f_26179dc, &GUID_c1402d9b_2321547, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_SOUND_LABEL_VALUE12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c480eff7_1095af1={{&GUID_c480eff7_10941bb, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_sound_setting_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 415, 525, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_SOUND_LABEL_SOUND_SETTING
	{D_CTRL_LABEL, 0, 80, 7, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_SOUND_GROUP
	{D_CTRL_GROUP, 0, 0, 37, 20, 415, 488, 30, -1, (D_FrameCtrlDescr*)&GUID_beda8768_3c81b4b, },
	// [3]ID_SOUND_GROUP_4
	{D_CTRL_GROUP, 2, 2, 6, 20, 410, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e35_1d45af1, },
	// [4]ID_SOUND_GROUP_6
	{D_CTRL_GROUP, 2, 2, 38, 0, 410, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c1402d3b_0fa124, },
	// [5]ID_SOUND_GROUP_12
	{D_CTRL_GROUP, 2, 2, 70, 0, 410, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c1402d3b_3dfe589, },
	// [6]ID_SOUND_GROUP_13
	{D_CTRL_GROUP, 2, 2, 102, 0, 410, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c50595a6_2426443, },
	// [7]ID_SOUND_GROUP_14
	{D_CTRL_GROUP, 2, 2, 134, 0, 410, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c93170d4_06d39b3, },
	// [8]ID_SOUND_BUTTON_4
	{D_CTRL_BUTTON, 3, 21, 2, 0, 220, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_beda356d_29f4df5, },
	// [9]ID_SOUND_BUTTON_6
	{D_CTRL_BUTTON, 4, 21, 2, 0, 220, 26, 30, 4, (D_FrameCtrlDescr*)&GUID_c1402d9b_2324d06, },
	// [10]ID_SOUND_BUTTON_12
	{D_CTRL_BUTTON, 5, 21, 2, 0, 220, 26, 30, 5, (D_FrameCtrlDescr*)&GUID_c1402d9b_4fde9369, },
	// [11]ID_SOUND_BUTTON_13
	{D_CTRL_BUTTON, 6, 21, 2, 0, 220, 26, 30, 6, (D_FrameCtrlDescr*)&GUID_c50596ce_04e701f, },
	// [12]ID_SOUND_BUTTON_14
	{D_CTRL_BUTTON, 7, 21, 2, 0, 220, 26, 30, 7, (D_FrameCtrlDescr*)&GUID_c9317150_3cf3602, },
	// [13]ID_SOUND_LABEL_VALUE12
	{D_CTRL_LABEL, 5, 280, 0, 0, 100, 28, 30, -1, (D_FrameCtrlDescr*)&GUID_c480eff7_1095af1, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	sound_setting_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_sound_setting_window[14];
D_Frame sound_setting_window = {
	run_ctrls_sound_setting_window, 
	ctrl_description_of_sound_setting_window, 
	sound_setting_window_init, 
};

