/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-02-20 16:01:16

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
#define	ID_MEDIA_GROUP_SHOW	1
#define	ID_MEDIA_GROUP_INPUT	2
#define	ID_MEDIA_IMAGE	3
#define	ID_MEDIA_TIME_LABEL	4
#define	ID_MEDIA_INPUT	5
#define	ID_MEDIA_LABEL_PROMPT	6

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bfa7e2d8_30d3dd7={atv_COLOR_ENUM_1, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bfa7e40f_1961f2d={-1, atv_IMG_ID_atv_IMG_ID_BUTTON_Red, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bfa7e464_38a3b97={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bfa7e4c6_09c53e5={atv_COLOR_ENUM_106, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bfa7e603_11925e4={-1, -1, atv_IDS_RED_INPUT, &atv_fmt_left_middle_h00_v00_signal_whilte_scroll_R2L, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7ba7165_3e711b7={-1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bfa78db1_17729={{&GUID_c7ba7165_3e711b7, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_MEDIA_GROUP_SHOW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bfa7e2d8_30d6738={{&GUID_bfa7e2d8_30d3dd7, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_MEDIA_GROUP_INPUT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bfa7e3a1_04e7546={{&GUID_bfa7e2d8_30d3dd7, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_IMAGE}	"ID_MEDIA_IMAGE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bfa7e40f_1966e7d={{&GUID_bfa7e40f_1961f2d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_MEDIA_TIME_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bfa7e464_38a44eb={{&GUID_bfa7e464_38a3b97, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_INPUT}	"ID_MEDIA_INPUT"
static char GUID_bfa7e4c6_09c6508[8+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_bfa7e4c6_09c1477={{&GUID_bfa7e4c6_09c53e5, NULL, NULL, }, 1, 5, 8, GUID_bfa7e4c6_09c6508, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_MEDIA_LABEL_PROMPT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bfa7e603_1191ddb={{&GUID_bfa7e603_11925e4, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_media_pvr_record_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 960, 540, 0, -1, (D_FrameCtrlDescr*)&GUID_bfa78db1_17729, },
	// [1]ID_MEDIA_GROUP_SHOW
	{D_CTRL_GROUP, 0, 804, 18, 20, 135, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_bfa7e2d8_30d6738, },
	// [2]ID_MEDIA_GROUP_INPUT
	{D_CTRL_GROUP, 0, 804, 56, 20, 135, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_bfa7e3a1_04e7546, },
	// [3]ID_MEDIA_IMAGE
	{D_CTRL_IMAGE, 1, 8, 12, 0, 20, 12, 30, -1, (D_FrameCtrlDescr*)&GUID_bfa7e40f_1966e7d, },
	// [4]ID_MEDIA_TIME_LABEL
	{D_CTRL_LABEL, 1, 34, 3, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bfa7e464_38a44eb, },
	// [5]ID_MEDIA_INPUT
	{D_CTRL_INPUT, 2, 4, 2, 0, 128, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bfa7e4c6_09c1477, },
	// [6]ID_MEDIA_LABEL_PROMPT
	{D_CTRL_LABEL, 2, 4, 2, 0, 128, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bfa7e603_1191ddb, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_media_pvr_record_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_media_pvr_record_window[7];
D_Frame atv_media_pvr_record_window = {
	run_ctrls_atv_media_pvr_record_window, 
	ctrl_description_of_atv_media_pvr_record_window, 
	atv_media_pvr_record_window_init, 
};

