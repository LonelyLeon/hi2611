/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-04-08 11:05:03

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
#define	ID_DRC_LABEL_DRC	1
#define	ID_DRC_GROUP	2
#define	ID_DRC_GROUP_1	3
#define	ID_DRC_GROUP_2	4
#define	ID_DRC_GROUP_3	5
#define	ID_DRC_BUTTON_1	6
#define	ID_DRC_BUTTON_2	7
#define	ID_DRC_BUTTON_3	8
#define	ID_DRC_LABEL_1	9
#define	ID_DRC_LABEL_2	10
#define	ID_DRC_LABEL_3	11

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_128645b={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_1282337={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda2ec1_38a531f={-1, atv_IMG_ID_box_focus, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_DRC_LABEL_DRC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_DRC_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda8768_3c81b4b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_DRC_GROUP_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96c42_0ab29={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_DRC_GROUP_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96db6_02e4ae1={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_DRC_GROUP_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c93175e6_0a4432b={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_BUTTON}	"ID_DRC_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed9bb91_128666e={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_BUTTON}	"ID_DRC_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda323b_30d1d08={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_BUTTON}	"ID_DRC_BUTTON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c93176a6_1d74aa1={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_DRC_LABEL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda2ec1_38a6275={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_DRC_LABEL_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb946e_0ab59e={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_DRC_LABEL_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9318731_2182ee4={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_drc_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 415, 525, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_DRC_LABEL_DRC
	{D_CTRL_LABEL, 0, 80, 7, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_DRC_GROUP
	{D_CTRL_GROUP, 0, 0, 37, 20, 415, 488, 30, -1, (D_FrameCtrlDescr*)&GUID_beda8768_3c81b4b, },
	// [3]ID_DRC_GROUP_1
	{D_CTRL_GROUP, 2, 2, 6, 20, 410, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96c42_0ab29, },
	// [4]ID_DRC_GROUP_2
	{D_CTRL_GROUP, 2, 2, 38, 20, 410, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96db6_02e4ae1, },
	// [5]ID_DRC_GROUP_3
	{D_CTRL_GROUP, 2, 2, 70, 0, 410, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c93175e6_0a4432b, },
	// [6]ID_DRC_BUTTON_1
	{D_CTRL_BUTTON, 3, 21, 2, 0, 180, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_bed9bb91_128666e, },
	// [7]ID_DRC_BUTTON_2
	{D_CTRL_BUTTON, 4, 21, 2, 0, 180, 26, 30, 4, (D_FrameCtrlDescr*)&GUID_beda323b_30d1d08, },
	// [8]ID_DRC_BUTTON_3
	{D_CTRL_BUTTON, 5, 21, 2, 20, 180, 26, 30, 5, (D_FrameCtrlDescr*)&GUID_c93176a6_1d74aa1, },
	// [9]ID_DRC_LABEL_1
	{D_CTRL_LABEL, 3, 280, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda2ec1_38a6275, },
	// [10]ID_DRC_LABEL_2
	{D_CTRL_LABEL, 4, 280, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb946e_0ab59e, },
	// [11]ID_DRC_LABEL_3
	{D_CTRL_LABEL, 5, 280, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c9318731_2182ee4, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	drc_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_drc_window[12];
D_Frame drc_window = {
	run_ctrls_drc_window, 
	ctrl_description_of_drc_window, 
	drc_window_init, 
};

