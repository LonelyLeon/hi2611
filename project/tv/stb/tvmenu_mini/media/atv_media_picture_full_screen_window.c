/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-02-20 15:45:09

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
#define	ID_FULL_LOADING_IMAGE	1

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c439aa_271c8b={atv_COLOR_ENUM_0, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c439aa_271778d={{&GUID_c4c439aa_271c8b, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_IMAGE}	"ID_FULL_LOADING_IMAGE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c51e2431_2af5a54={{NULL, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_media_picture_full_screen_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 960, 540, 0, -1, (D_FrameCtrlDescr*)&GUID_c4c439aa_271778d, },
	// [1]ID_FULL_LOADING_IMAGE
	{D_CTRL_IMAGE, 0, 435, 239, 20, 87, 61, 30, -1, (D_FrameCtrlDescr*)&GUID_c51e2431_2af5a54, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_media_picture_full_screen_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_media_picture_full_screen_window[2];
D_Frame atv_media_picture_full_screen_window = {
	run_ctrls_atv_media_picture_full_screen_window, 
	ctrl_description_of_atv_media_picture_full_screen_window, 
	atv_media_picture_full_screen_window_init, 
};

