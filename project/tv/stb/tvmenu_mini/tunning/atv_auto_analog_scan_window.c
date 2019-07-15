/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2017-07-27 11:06:53

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-07-18 16:19:49.390

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
#define	ID_AUTOANALOG_LABLE_CH_NUM	1
#define	ID_AUTOANALOG_LABLE_CH_VAL	2
#define	ID_AUTOANALOG_LABLE_FREQ	3
#define	ID_AUTOANALOG_LABLE_FREQ_VAL	4
#define	ID_AUTOANALOG_GROUP_PROGRESS	5
#define	ID_AUTOANALOG_PROGRESS_CH_BAR	6
#define	D_FRAMECONTROL_BACK_ICON	7
#define	D_FRAMECONTROL_BACK	8
#define	D_FRAMECONTROL_MENU_ICON	9
#define	D_FRAMECONTROL_4	10

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a11d1_3d84823={-1, atv_IMG_ID_FS_WHITE_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a11de_00f7ae0={-1, -1, atv_IDS_CH_ID, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56bba65_232391d={-1, -1, atv_IDS_FREQ, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56bbe36_3997a0b={atv_COLOR_ENUM_2, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56bbf75_31c1455={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c52000f6_3c84db7={-1, atv_IMG_ID_FS_BUTTON_GRAY, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c520026e_2422d12={-1, -1, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c52002d9_37a66bb={-1, atv_IMG_ID_FS_BUTTON_GRAY, atv_IDS_MENU, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c52003ea_04e1d9d={-1, -1, atv_IDS_EXIT, &atv_fmt_center_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a11d1_3d829={{&GUID_c56a11d1_3d84823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_AUTOANALOG_LABLE_CH_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a11de_00f672f={{&GUID_c56a11de_00f7ae0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_AUTOANALOG_LABLE_CH_VAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56bbf75_31c7d85={{&GUID_c56bbf75_31c1455, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_AUTOANALOG_LABLE_FREQ"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56bba65_2324579={{&GUID_c56bba65_232391d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_AUTOANALOG_LABLE_FREQ_VAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56bbfc0_29064e0={{&GUID_c56bbf75_31c1455, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_AUTOANALOG_GROUP_PROGRESS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c0dcc_28056d5={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_PROGRESS}	"ID_AUTOANALOG_PROGRESS_CH_BAR"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_c56bbe36_3994665={{&GUID_c56bbe36_3997a0b, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_106, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"D_FRAMECONTROL_BACK_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c52000f6_3c84d06={{&GUID_c52000f6_3c84db7, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"D_FRAMECONTROL_BACK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c520026e_24239b3={{&GUID_c520026e_2422d12, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"D_FRAMECONTROL_MENU_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c52002d9_37a6443={{&GUID_c52002d9_37a66bb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"D_FRAMECONTROL_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c52003ea_04e7f79={{&GUID_c52003ea_04e1d9d, NULL, NULL, }, 0, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_auto_scan_analog_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 180, 188, 0, 360, 200, 0, -1, (D_FrameCtrlDescr*)&GUID_c56a11d1_3d829, },
	// [1]ID_AUTOANALOG_LABLE_CH_NUM
	{D_CTRL_LABEL, 0, 17, 8, -206, 188, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a11de_00f672f, },
	// [2]ID_AUTOANALOG_LABLE_CH_VAL
	{D_CTRL_LABEL, 0, 246, 11, -206, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56bbf75_31c7d85, },
	// [3]ID_AUTOANALOG_LABLE_FREQ
	{D_CTRL_LABEL, 0, 17, 43, -206, 188, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c56bba65_2324579, },
	// [4]ID_AUTOANALOG_LABLE_FREQ_VAL
	{D_CTRL_LABEL, 0, 246, 46, -206, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56bbfc0_29064e0, },
	// [5]ID_AUTOANALOG_GROUP_PROGRESS
	{D_CTRL_GROUP, 0, 7, 111, -206, 349, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c56c0dcc_28056d5, },
	// [6]ID_AUTOANALOG_PROGRESS_CH_BAR
	{D_CTRL_PROGRESS, 5, 6, 6, 0, 336, 20, 30, -1, (D_FrameCtrlDescr*)&GUID_c56bbe36_3994665, },
	// [7]D_FRAMECONTROL_BACK_ICON
	{D_CTRL_LABEL, 0, 25, 159, 0, 65, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c52000f6_3c84d06, },
	// [8]D_FRAMECONTROL_BACK
	{D_CTRL_LABEL, 0, 98, 160, 0, 50, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c520026e_24239b3, },
	// [9]D_FRAMECONTROL_MENU_ICON
	{D_CTRL_LABEL, 0, 217, 159, 0, 65, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c52002d9_37a6443, },
	// [10]D_FRAMECONTROL_4
	{D_CTRL_LABEL, 0, 288, 160, 0, 50, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c52003ea_04e7f79, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_auto_scan_analog_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_auto_scan_analog_window[11];
D_Frame atv_auto_scan_analog_window = {
	run_ctrls_atv_auto_scan_analog_window, 
	ctrl_description_of_atv_auto_scan_analog_window, 
	atv_auto_scan_analog_window_init, 
};

