/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2014-12-09 17:43:58

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2014-12-09 17:35:22.625

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
#define	ID_IMG_NUM_100	1
#define	ID_IMG_NUM_10	2
#define	ID_IMG_NUM_1	3

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c574a6bf_0fa4823={-1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c574a6bf_0fa29={{&GUID_c574a6bf_0fa4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_IMAGE}	"ID_IMG_NUM_100"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c574a7eb_08c178c={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_IMAGE}	"ID_IMG_NUM_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c574a8a5_399617c={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_IMAGE}	"ID_IMG_NUM_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c574a8f9_03e7d15={{NULL, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_chan_input_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 550, 25, 0, 132, 56, 0, -1, (D_FrameCtrlDescr*)&GUID_c574a6bf_0fa29, },
	// [1]ID_IMG_NUM_100
	{D_CTRL_IMAGE, 0, 0, 0, 20, 44, 56, 30, -1, (D_FrameCtrlDescr*)&GUID_c574a7eb_08c178c, },
	// [2]ID_IMG_NUM_10
	{D_CTRL_IMAGE, 0, 44, 0, 20, 44, 56, 30, -1, (D_FrameCtrlDescr*)&GUID_c574a8a5_399617c, },
	// [3]ID_IMG_NUM_1
	{D_CTRL_IMAGE, 0, 88, 0, 20, 44, 56, 30, -1, (D_FrameCtrlDescr*)&GUID_c574a8f9_03e7d15, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_chan_input_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_chan_input_window[4];
D_Frame atv_chan_input_window = {
	run_ctrls_atv_chan_input_window, 
	ctrl_description_of_atv_chan_input_window, 
	atv_chan_input_window_init, 
};

