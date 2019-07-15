/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2018-08-24 17:21:05

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2018-03-02 10:21:44.000

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
#define	ID_LABEL_INFO	1

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1258a45_1d42c39={atv_COLOR_ENUM_2, -1, -1, -1, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1258a45_1d42119={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };


//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c12589f4_0bb18be={{&GUID_c1258a45_1d42c39, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_LABEL_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1258a45_1d45edb={{&GUID_c1258a45_1d42119, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_ratio_mode_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 800, 0, 0, 160, 100, 0, -1, (D_FrameCtrlDescr*)&GUID_c12589f4_0bb18be, },
	// [1]ID_LABEL_INFO
	{D_CTRL_LABEL, 0, 10, 35, 20, 150, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c1258a45_1d45edb, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	ratio_mode_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_ratio_mode_window[2];
D_Frame ratio_mode_window = {
	run_ctrls_ratio_mode_window, 
	ctrl_description_of_ratio_mode_window, 
	ratio_mode_window_init, 
};

