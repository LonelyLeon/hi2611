/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-02-25 10:18:42

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
#define	ID_LABEL_NO_SIGNAL	1

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1258a45_1d42c39={-1, atv_IMG_ID_FS_BLACK_BACKGROUND, atv_IDS_NO_SIGNAL, &atv_fmt_center_middle_h00_v00_multi_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c12589f4_0bb18be={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_LABEL_NO_SIGNAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1258a45_1d45edb={{&GUID_c1258a45_1d42c39, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_no_signal_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 960, 540, 0, -1, (D_FrameCtrlDescr*)&GUID_c12589f4_0bb18be, },
	// [1]ID_LABEL_NO_SIGNAL
	{D_CTRL_LABEL, 0, 400, 227, 20, 160, 84, 30, -1, (D_FrameCtrlDescr*)&GUID_c1258a45_1d45edb, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_no_signal_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_no_signal_window[2];
D_Frame atv_no_signal_window = {
	run_ctrls_atv_no_signal_window, 
	ctrl_description_of_atv_no_signal_window, 
	atv_no_signal_window_init, 
};

