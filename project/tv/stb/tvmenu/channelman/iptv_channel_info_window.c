/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {wenl}
	on computer "PRWENL"
	update/create time:	2019-04-09 11:17:54

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2019-03-06 17:00:02.265

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
#define	ID_CHANNEL_INFO_LABEL_INFO	1

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56c53ed_02e7be={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56c55c9_01f4465={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c53ed_02e6c41={{&GUID_c56c53ed_02e7be, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_CHANNEL_INFO_LABEL_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c55c9_01f60ac={{&GUID_c56c55c9_01f4465, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_iptv_channel_info_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 140, 620, 0, 1000, 80, 0, -1, (D_FrameCtrlDescr*)&GUID_c56c53ed_02e6c41, },
	// [1]ID_CHANNEL_INFO_LABEL_INFO
	{D_CTRL_LABEL, 0, 63, 24, 86, 925, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c56c55c9_01f60ac, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	iptv_channel_info_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_iptv_channel_info_window[2];
D_Frame iptv_channel_info_window = {
	run_ctrls_iptv_channel_info_window, 
	ctrl_description_of_iptv_channel_info_window, 
	iptv_channel_info_window_init, 
};

