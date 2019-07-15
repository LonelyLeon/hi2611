/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2014-12-22 14:33:37

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2014-12-16 16:55:09.290

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
#define	ID_TXT_DRAW_AREA	1
#define	ID_TXT_FILE_NAME	2

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c58de6c3_2034823={atv_COLOR_ENUM_80, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c58de754_38a271c={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c58de877_29f2321={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c58de6c3_20329={{&GUID_c58de6c3_2034823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_DRAW_AREA}	"ID_TXT_DRAW_AREA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c58de754_38a7849={{&GUID_c58de754_38a271c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_TXT_FILE_NAME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c58de877_29f4ab6={{&GUID_c58de877_29f2321, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_media_txt_full_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 1280, 720, 0, -1, (D_FrameCtrlDescr*)&GUID_c58de6c3_20329, },
	// [1]ID_TXT_DRAW_AREA
	{D_CTRL_DRAW_AREA, 0, 69, 77, 20, 1135, 589, 30, -1, (D_FrameCtrlDescr*)&GUID_c58de754_38a7849, },
	// [2]ID_TXT_FILE_NAME
	{D_CTRL_LABEL, 0, 135, 20, 20, 1002, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c58de877_29f4ab6, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_media_txt_full_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_media_txt_full_window[3];
D_Frame atv_media_txt_full_window = {
	run_ctrls_atv_media_txt_full_window, 
	ctrl_description_of_atv_media_txt_full_window, 
	atv_media_txt_full_window_init, 
};

