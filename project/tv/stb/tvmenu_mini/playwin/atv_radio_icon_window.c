/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY"
	update/create time:	2015-08-31 15:07:04

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-08-20 10:37:14.250

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
#define	ID_LABEL_RADIO_TITLE	1
#define	ID_LABEL_RADIO_NAME	2

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1258a45_1d42c39={-1, -1, atv_IDS_DIGI_RADIO, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c480127d_2de3d6c={-1, atv_IMG_ID_FS_BLACK_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c480261f_0cb72ae={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c12589f4_0bb18be={{&GUID_c480127d_2de3d6c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_LABEL_RADIO_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1258a45_1d45edb={{&GUID_c1258a45_1d42c39, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_LABEL_RADIO_NAME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c480261f_0cb2cd6={{&GUID_c480261f_0cb72ae, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_radio_icon_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 451, 266, 0, 184, 120, 0, -1, (D_FrameCtrlDescr*)&GUID_c12589f4_0bb18be, },
	// [1]ID_LABEL_RADIO_TITLE
	{D_CTRL_LABEL, 0, 8, 10, 286, 168, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c1258a45_1d45edb, },
	// [2]ID_LABEL_RADIO_NAME
	{D_CTRL_LABEL, 0, 4, 54, 20, 176, 60, 30, -1, (D_FrameCtrlDescr*)&GUID_c480261f_0cb2cd6, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_radio_icon_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_radio_icon_window[3];
D_Frame atv_radio_icon_window = {
	run_ctrls_atv_radio_icon_window, 
	ctrl_description_of_atv_radio_icon_window, 
	atv_radio_icon_window_init, 
};

