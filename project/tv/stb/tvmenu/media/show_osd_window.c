/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {liujh}
	on computer "PRLIUJH"
	update/create time:	2016-04-22 14:57:20

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2016-04-20 17:29:23.093

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
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c34e31d8_0fa4ae1={-1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c34e31d8_0fa6784={{&GUID_c34e31d8_0fa4ae1, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_show_osd_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 1000, 0, 0, 30, 30, 0, -1, (D_FrameCtrlDescr*)&GUID_c34e31d8_0fa6784, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	show_osd_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_show_osd_window[1];
D_Frame show_osd_window = {
	run_ctrls_show_osd_window, 
	ctrl_description_of_show_osd_window, 
	show_osd_window_init, 
};

