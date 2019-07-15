/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {wenl}
	on computer "PRWENL"
	update/create time:	2019-02-27 17:23:02

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2018-09-29 16:14:31.286

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
#define	D_FRAMEGROUP	1
#define	D_FRAMELABEL_TIP	2
#define	D_FRAMECONTROL_INPUT	3
#define	D_FRAMECONTROL_ACTIVE	4

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7ae4e4a_02e48f6={-1, -1, atv_IDS_LOGO, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7aec914_2714011={atv_COLOR_ENUM_110, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7aec978_33c23f2={-1, -1, atv_IDS_COLOR, &atv_fmt_center_middle_h00_v00_multi_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7b009e3_31c19e9={atv_COLOR_ENUM_111, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7b09aee_01f2cc1={-1, atv_IMG_ID_FS_no_signal_backgroud, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5638e24_12829={{NULL, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"D_FRAMEGROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7b09aee_01f78aa={{&GUID_c7b09aee_01f2cc1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"D_FRAMELABEL_TIP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7ae4e4a_02e111={{&GUID_c7ae4e4a_02e48f6, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_INPUT}	"D_FRAMECONTROL_INPUT"
static char GUID_c7aec914_27163da[12+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_c7aec914_271234f={{&GUID_c7aec914_2714011, &GUID_c7b009e3_31c19e9, NULL, }, 1, 0, 12, GUID_c7aec914_27163da, 2, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"D_FRAMECONTROL_ACTIVE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7aec978_33c4a7c={{&GUID_c7aec978_33c23f2, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_iptv_login_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 1280, 720, 0, -1, (D_FrameCtrlDescr*)&GUID_c5638e24_12829, },
	// [1]D_FRAMEGROUP
	{D_CTRL_GROUP, 0, 535, 217, 20, 164, 117, 30, -1, (D_FrameCtrlDescr*)&GUID_c7b09aee_01f78aa, },
	// [2]D_FRAMELABEL_TIP
	{D_CTRL_LABEL, 1, 5, 1, -210, 150, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c7ae4e4a_02e111, },
	// [3]D_FRAMECONTROL_INPUT
	{D_CTRL_INPUT, 1, 4, 37, 0, 157, 29, 30, -1, (D_FrameCtrlDescr*)&GUID_c7aec914_271234f, },
	// [4]D_FRAMECONTROL_ACTIVE
	{D_CTRL_LABEL, 1, 7, 79, 0, 147, 33, 30, -1, (D_FrameCtrlDescr*)&GUID_c7aec978_33c4a7c, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	iptv_login_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_iptv_login_window[5];
D_Frame iptv_login_window = {
	run_ctrls_iptv_login_window, 
	ctrl_description_of_iptv_login_window, 
	iptv_login_window_init, 
};

