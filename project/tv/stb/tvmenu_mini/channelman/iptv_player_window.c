/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-03-07 11:47:48

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2019-02-20 18:00:19.367

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
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d9010_1674823={atv_COLOR_ENUM_0, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d9010_16729={{&GUID_c40d9010_1674823, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_iptv_player_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 960, 540, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d9010_16729, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	iptv_player_window_init  (void) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_iptv_player_window[1];
D_Frame iptv_player_window = {
	run_ctrls_iptv_player_window, 
	ctrl_description_of_iptv_player_window, 
	iptv_player_window_init, 
};
