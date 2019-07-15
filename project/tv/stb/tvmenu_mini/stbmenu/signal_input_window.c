/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-02-25 10:45:19

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
#define	ID_LABEL_INPUT	1
#define	ID_SIGNAL_INPUT_LABEL_VIDEO	2
#define	ID_SIGNAL_INPUT_LABEL_AUDIO	3

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5638e24_1284823={atv_COLOR_ENUM_2, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c57f8f5e_2af18be={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5816721_1c5148a={-1, -1, atv_IDS_NULL, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5638e24_12829={{&GUID_c5638e24_1284823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_LABEL_INPUT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c57f8f5e_2af4823={{&GUID_c57f8f5e_2af18be, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_SIGNAL_INPUT_LABEL_VIDEO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5816721_1c53c54={{&GUID_c5816721_1c5148a, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_SIGNAL_INPUT_LABEL_AUDIO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5816891_0da1097={{&GUID_c57f8f5e_2af18be, NULL, NULL, }, 0, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_signal_input_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 775, 20, 0, 160, 90, 0, -1, (D_FrameCtrlDescr*)&GUID_c5638e24_12829, },
	// [1]ID_LABEL_INPUT
	{D_CTRL_LABEL, 0, 14, 4, -16, 133, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c57f8f5e_2af4823, },
	// [2]ID_SIGNAL_INPUT_LABEL_VIDEO
	{D_CTRL_LABEL, 0, 14, 34, -16, 133, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c5816721_1c53c54, },
	// [3]ID_SIGNAL_INPUT_LABEL_AUDIO
	{D_CTRL_LABEL, 0, 14, 64, -16, 133, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c5816891_0da1097, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	signal_input_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_signal_input_window[4];
D_Frame signal_input_window = {
	run_ctrls_signal_input_window, 
	ctrl_description_of_signal_input_window, 
	signal_input_window_init, 
};

