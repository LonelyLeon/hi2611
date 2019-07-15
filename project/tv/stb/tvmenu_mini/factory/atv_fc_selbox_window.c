/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY"
	update/create time:	2015-10-19 18:24:48

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
#define	ID_GROUP_BUTTONS	1
#define	ID_BUTTON_YES	2
#define	ID_BUTTON_NO	3

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf82a754_38a4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5f899d2_36b6784={-1, -1, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5f899d2_36b4ae1={atv_COLOR_ENUM_106, -1, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5f89b98_06d6df1={-1, -1, atv_IDS_CANCEL, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5f89b98_06d5af1={atv_COLOR_ENUM_106, -1, atv_IDS_CANCEL, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf82a754_38a29={{&GUID_bf82a754_38a4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_GROUP_BUTTONS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5f89aa3_2132cd6={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_BUTTON_YES"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5f899d2_36b18be={{&GUID_c5f899d2_36b6784, &GUID_c5f899d2_36b4ae1, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_BUTTON_NO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5f89b98_06d1649={{&GUID_c5f89b98_06d6df1, &GUID_c5f89b98_06d5af1, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_fc_selbox_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 490, 200, 0, 160, 36, 0, -1, (D_FrameCtrlDescr*)&GUID_bf82a754_38a29, },
	// [1]ID_GROUP_BUTTONS
	{D_CTRL_GROUP, 0, 0, 0, 20, 160, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c5f89aa3_2132cd6, },
	// [2]ID_BUTTON_YES
	{D_CTRL_BUTTON, 1, 11, 4, 0, 56, 28, 30, -1, (D_FrameCtrlDescr*)&GUID_c5f899d2_36b18be, },
	// [3]ID_BUTTON_NO
	{D_CTRL_BUTTON, 1, 95, 4, 0, 56, 28, 30, -1, (D_FrameCtrlDescr*)&GUID_c5f89b98_06d1649, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_fc_selbox_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_fc_selbox_window[4];
D_Frame atv_fc_selbox_window = {
	run_ctrls_atv_fc_selbox_window, 
	ctrl_description_of_atv_fc_selbox_window, 
	atv_fc_selbox_window_init, 
};

