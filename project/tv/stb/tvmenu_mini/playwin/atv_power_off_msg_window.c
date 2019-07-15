/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-02-25 10:21:07

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
#define	ID_MSG_LABEL_POWER_OFF	1
#define	D_FRAMECONTROL_2	2

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c13050b8_2714823={-1, atv_IMG_ID_FS_BLACK_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1305eac_2af6d6e={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c13050b8_27129={{&GUID_c13050b8_2714823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_MSG_LABEL_POWER_OFF"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1305313_36b6e4={{&GUID_c1305eac_2af6d6e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"D_FRAMECONTROL_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1307493_08c3cf2={{&GUID_c1305eac_2af6d6e, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_power_off_msg_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 380, 223, 0, 200, 94, 0, -1, (D_FrameCtrlDescr*)&GUID_c13050b8_27129, },
	// [1]ID_MSG_LABEL_POWER_OFF
	{D_CTRL_LABEL, 0, 25, 19, 55, 150, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c1305313_36b6e4, },
	// [2]D_FRAMECONTROL_2
	{D_CTRL_LABEL, 0, 25, 49, 55, 150, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c1307493_08c3cf2, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_power_off_msg_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_power_off_msg_window[3];
D_Frame atv_power_off_msg_window = {
	run_ctrls_atv_power_off_msg_window, 
	ctrl_description_of_atv_power_off_msg_window, 
	atv_power_off_msg_window_init, 
};

