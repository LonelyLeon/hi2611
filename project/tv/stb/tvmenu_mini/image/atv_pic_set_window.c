/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-05-08 17:52:38

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2019-02-14 16:39:05.650

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
#define	ID_ATV_GROUP_PICWIN	1
#define	ID_ATV_BUTTON_PICLEFT	2
#define	ID_ATV_BUTTON_PICRIGHT	3
#define	ID_ATV_PROGRESS_PIC	4
#define	ID_ATV_LABEL_PIC	5

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7aa35c3_06d4823={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7a523c3_06d4a38={-1, atv_IMG_ID_FS_PROGRESS_NORMAL, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7a383c3_06da524={-1, atv_IMG_ID_sub_menu_direc_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cca52643_0d7a383={-1, atv_IMG_ID_sub_menu_direc_right, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7aa309d_06d18be={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_ATV_GROUP_PICWIN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7aa3282_35b18be={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_ATV_BUTTON_PICLEFT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7aa3379_04e2cd6={{&GUID_c7a383c3_06da524, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_ATV_BUTTON_PICRIGHT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7aa3422_32c12db={{&GUID_cca52643_0d7a383, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_PROGRESS}	"ID_ATV_PROGRESS_PIC"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_c7aa347e_203f3e={{&GUID_c7a523c3_06d4a38, NULL, NULL, }, 1, 100, 1, 0, -1, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_ATV_LABEL_PIC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7aa35c3_06d29={{&GUID_c7aa35c3_06d4823, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_pic_set_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 25, 445, 0, 900, 55, 0, -1, (D_FrameCtrlDescr*)&GUID_c7aa309d_06d18be, },
	// [1]ID_ATV_GROUP_PICWIN
	{D_CTRL_GROUP, 0, 0, 0, -21, 900, 55, 30, -1, (D_FrameCtrlDescr*)&GUID_c7aa3282_35b18be, },
	// [2]ID_ATV_BUTTON_PICLEFT
	{D_CTRL_BUTTON, 1, 117, 17, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c7aa3379_04e2cd6, },
	// [3]ID_ATV_BUTTON_PICRIGHT
	{D_CTRL_BUTTON, 1, 860, 17, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c7aa3422_32c12db, },
	// [4]ID_ATV_PROGRESS_PIC
	{D_CTRL_PROGRESS, 1, 144, 17, 0, 700, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c7aa347e_203f3e, },
	// [5]ID_ATV_LABEL_PIC
	{D_CTRL_LABEL, 4, 310, 0, 0, 80, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c7aa35c3_06d29, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	pic_set_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_pic_set_window[6];
D_Frame pic_set_window = {
	run_ctrls_pic_set_window, 
	ctrl_description_of_pic_set_window, 
	pic_set_window_init, 
};

