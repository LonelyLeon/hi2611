/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2014-12-17 16:30:34

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2014-12-15 16:03:25.890

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

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5801300_0ea4823={-1, atv_IMG_ID_Mute_Icon, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5801300_0ea29={{&GUID_c5801300_0ea4823, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_setmute_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 1180, 35, 0, 46, 46, 0, -1, (D_FrameCtrlDescr*)&GUID_c5801300_0ea29, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_setmute_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_setmute_window[1];
D_Frame atv_setmute_window = {
	run_ctrls_atv_setmute_window, 
	ctrl_description_of_atv_setmute_window, 
	atv_setmute_window_init, 
};

