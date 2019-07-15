/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-03-04 10:03:19

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
#define	ID_LABEL_DRAW	1
#define	ID_TXT_DRAW_AREA	2
#define	ID_EBOOK_SCROLL	3

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c58de754_38a271c={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd8773e7_0eb4af5={atv_COLOR_ENUM_90, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd91b6d0_0547e87={atv_COLOR_ENUM_1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c58de6c3_20329={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_LABEL_DRAW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd8773e7_0eb7830={{&GUID_cd8773e7_0eb4af5, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_DRAW_AREA}	"ID_TXT_DRAW_AREA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c58de754_38a7849={{&GUID_c58de754_38a271c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_SCROLL}	"ID_EBOOK_SCROLL"
static PREFIXCONST D_FrameScrollBarDescr POSTCONST GUID_cd91b6d0_054153c={{&GUID_cd91b6d0_0547e87, NULL, NULL, }, 1, 100, 1, 1, {-1, -1, -1, atv_IMG_ID_v_roll, }, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_media_txt_full_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 960, 540, 0, -1, (D_FrameCtrlDescr*)&GUID_c58de6c3_20329, },
	// [1]ID_LABEL_DRAW
	{D_CTRL_LABEL, 0, 72, 78, 20, 816, 336, 30, -1, (D_FrameCtrlDescr*)&GUID_cd8773e7_0eb7830, },
	// [2]ID_TXT_DRAW_AREA
	{D_CTRL_DRAW_AREA, 1, 33, 17, -69, 739, 293, 30, -1, (D_FrameCtrlDescr*)&GUID_c58de754_38a7849, },
	// [3]ID_EBOOK_SCROLL
	{D_CTRL_SCROLL, 1, 805, 24, -1, 4, 285, 30, -1, (D_FrameCtrlDescr*)&GUID_cd91b6d0_054153c, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_media_txt_full_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_media_txt_full_window[4];
D_Frame atv_media_txt_full_window = {
	run_ctrls_atv_media_txt_full_window, 
	ctrl_description_of_atv_media_txt_full_window, 
	atv_media_txt_full_window_init, 
};

