/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2015-05-06 15:22:18

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-04-16 14:04:23.640

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
#define	ID_TV_CHAN_INFO_LABEL_VIDEO	1
#define	ID_TV_CHAN_INFO_LABEL_AUDIO	2
#define	ID_TV_CHAN_INFO_LABEL_NUM	3
#define	ID_TV_CHAN_INFO_CH	4

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c584a2cc_0da4823={atv_COLOR_ENUM_2, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c584a757_04e3e08={-1, -1, atv_IDS_NULL, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5879359_0ea1ee0={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1f64ac7_3b97b4={-1, -1, atv_IDS_NULL, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1f64ec4_39968af={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c584a2cc_0da29={{&GUID_c584a2cc_0da4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_TV_CHAN_INFO_LABEL_VIDEO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c584a757_04e965={{&GUID_c584a757_04e3e08, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_TV_CHAN_INFO_LABEL_AUDIO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c584a7d1_32c1a4d={{&GUID_c1f64ac7_3b97b4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_TV_CHAN_INFO_LABEL_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5879359_0ea5e47={{&GUID_c5879359_0ea1ee0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_TV_CHAN_INFO_CH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5879a58_1864823={{&GUID_c1f64ec4_39968af, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_tv_chan_info_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 580, 20, 0, 120, 90, 0, -1, (D_FrameCtrlDescr*)&GUID_c584a2cc_0da29, },
	// [1]ID_TV_CHAN_INFO_LABEL_VIDEO
	{D_CTRL_LABEL, 0, 0, 56, -16, 60, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c584a757_04e965, },
	// [2]ID_TV_CHAN_INFO_LABEL_AUDIO
	{D_CTRL_LABEL, 0, 60, 56, -16, 60, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c584a7d1_32c1a4d, },
	// [3]ID_TV_CHAN_INFO_LABEL_NUM
	{D_CTRL_LABEL, 0, 60, 10, 20, 32, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c5879359_0ea5e47, },
	// [4]ID_TV_CHAN_INFO_CH
	{D_CTRL_LABEL, 0, 28, 10, 20, 32, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c5879a58_1864823, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	tv_chan_info_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_tv_chan_info_window[5];
D_Frame tv_chan_info_window = {
	run_ctrls_tv_chan_info_window, 
	ctrl_description_of_tv_chan_info_window, 
	tv_chan_info_window_init, 
};

