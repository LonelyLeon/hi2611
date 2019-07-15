/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY"
	update/create time:	2015-09-15 10:44:57

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
#define	ID_LABEL_TITLE	1
#define	ID_INPUT_PASSWD	2

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf82a754_38a4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf82a768_2fd6784={-1, -1, -1, &atv_fmt_left_middle_h10_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf8797f5_0da3912={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf82a754_38a29={{&GUID_bf82a754_38a4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_LABEL_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf82a768_2fd18be={{&GUID_bf82a768_2fd6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_INPUT}	"ID_INPUT_PASSWD"
static char GUID_bf8797f5_0da337d[16+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_bf8797f5_0da5fb2={{&GUID_bf8797f5_0da3912, &GUID_bf8797f5_0da3912, NULL, }, 1, 3, 16, GUID_bf8797f5_0da337d, 1, '-', '*', };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_pwd_input_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 490, 200, 0, 160, 36, 0, -1, (D_FrameCtrlDescr*)&GUID_bf82a754_38a29, },
	// [1]ID_LABEL_TITLE
	{D_CTRL_LABEL, 0, 0, 3, 52, 84, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bf82a768_2fd18be, },
	// [2]ID_INPUT_PASSWD
	{D_CTRL_INPUT, 0, 84, 3, 44, 76, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bf8797f5_0da5fb2, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_pwd_input_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_pwd_input_window[3];
D_Frame atv_pwd_input_window = {
	run_ctrls_atv_pwd_input_window, 
	ctrl_description_of_atv_pwd_input_window, 
	atv_pwd_input_window_init, 
};

