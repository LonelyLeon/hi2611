/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-02-20 16:00:34

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
#define	ID_MEDIA_TITLE	1
#define	ID_MEDIA_CONTENT	2

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c58e9c6c_30d4823={-1, atv_IMG_ID_FS_WHITE_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c58e9d96_06d23f0={-1, -1, atv_IDS_PROMPT_INFO, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5902940_18629={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c58e9c6c_30d29={{&GUID_c58e9c6c_30d4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_MEDIA_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c58e9d96_06d7c31={{&GUID_c58e9d96_06d23f0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_MEDIA_CONTENT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c58e9df3_0fa8f2={{&GUID_c5902940_18629, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_media_prompt_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 307, 218, 0, 347, 140, 0, -1, (D_FrameCtrlDescr*)&GUID_c58e9c6c_30d29, },
	// [1]ID_MEDIA_TITLE
	{D_CTRL_LABEL, 0, 98, 5, -10, 150, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c58e9d96_06d7c31, },
	// [2]ID_MEDIA_CONTENT
	{D_CTRL_LABEL, 0, 58, 40, -10, 230, 78, 30, -1, (D_FrameCtrlDescr*)&GUID_c58e9df3_0fa8f2, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_media_prompt_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_media_prompt_window[3];
D_Frame atv_media_prompt_window = {
	run_ctrls_atv_media_prompt_window, 
	ctrl_description_of_atv_media_prompt_window, 
	atv_media_prompt_window_init, 
};

