/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY"
	update/create time:	2018-05-22 19:14:10

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-08-31 11:38:27.453

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
#define	ID_TS2NET_IMAGE	1
#define	ID_TS2NET_LABEL	2

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bfa78db1_1774823={atv_COLOR_ENUM_1, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bfa7e40f_1961f2d={-1, atv_IMG_ID_red_info_icon, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bfa7e464_38a3b97={-1, -1, atv_IDS_DTV_SHAREING, &atv_fmt_left_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bfa78db1_17729={{&GUID_bfa78db1_1774823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_IMAGE}	"ID_TS2NET_IMAGE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bfa7e40f_1966e7d={{&GUID_bfa7e40f_1961f2d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_TS2NET_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bfa7e464_38a44eb={{&GUID_bfa7e464_38a3b97, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_ts2net_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 500, 35, 0, -1, (D_FrameCtrlDescr*)&GUID_bfa78db1_17729, },
	// [1]ID_TS2NET_IMAGE
	{D_CTRL_IMAGE, 0, 5, 5, -26, 24, 24, 30, -1, (D_FrameCtrlDescr*)&GUID_bfa7e40f_1966e7d, },
	// [2]ID_TS2NET_LABEL
	{D_CTRL_LABEL, 0, 34, 2, -26, 460, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bfa7e464_38a44eb, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_ts2net_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_ts2net_window[3];
D_Frame atv_ts2net_window = {
	run_ctrls_atv_ts2net_window, 
	ctrl_description_of_atv_ts2net_window, 
	atv_ts2net_window_init, 
};

