/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-05-10 16:18:23

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
#define	ID_POPON_BUTTON_ON	1
#define	ID_POPON_BUTTON_OFF	2
#define	ID_POPON_GROUP_TIME	3
#define	ID_POPON_INPUT_HOUR	4
#define	ID_POPON_LABLE_DIAN	5
#define	ID_POPON_INPUT_MINUTE	6

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c49fb278_11939bf={atv_COLOR_ENUM_84, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c49fb715_03e949={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a027ab_04e19bf={-1, atv_IMG_ID_FS_BUTTON_GRAY, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a027ab_04e6d4b={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b2604d_2901b95={-1, atv_IMG_ID_FS_WHITE_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b27262_3a9643={atv_COLOR_ENUM_106, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{&GUID_c4b2604d_2901b95, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_BUTTON}	"ID_POPON_BUTTON_ON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a027ab_04e67ee={{&GUID_c4a027ab_04e19bf, &GUID_c4a027ab_04e6d4b, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_POPON_BUTTON_OFF"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a0288c_1e471ab={{&GUID_c4a027ab_04e19bf, &GUID_c4a027ab_04e6d4b, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_POPON_GROUP_TIME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a02c60_167dac={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_INPUT}	"ID_POPON_INPUT_HOUR"
static char GUID_c49fb278_1195bb9[3+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_c49fb278_1195f0c={{&GUID_c49fb278_11939bf, &GUID_c4b27262_3a9643, NULL, }, 1, 0, 3, GUID_c49fb278_1195bb9, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_POPON_LABLE_DIAN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c49fb715_03e3cc7={{&GUID_c49fb715_03e949, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_INPUT}	"ID_POPON_INPUT_MINUTE"
static char GUID_c49fb80d_38a15fc[2+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_c49fb80d_38a6176={{&GUID_c49fb278_11939bf, &GUID_c4b27262_3a9643, NULL, }, 1, 0, 2, GUID_c49fb80d_38a15fc, 1, '-', '*', };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_pop_power_on_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 230, 400, 0, 260, 140, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_POPON_BUTTON_ON
	{D_CTRL_BUTTON, 0, 14, 30, 295, 90, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a027ab_04e67ee, },
	// [2]ID_POPON_BUTTON_OFF
	{D_CTRL_BUTTON, 0, 14, 78, 295, 90, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a0288c_1e471ab, },
	// [3]ID_POPON_GROUP_TIME
	{D_CTRL_GROUP, 0, 126, 51, 295, 122, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a02c60_167dac, },
	// [4]ID_POPON_INPUT_HOUR
	{D_CTRL_INPUT, 0, 135, 53, 295, 36, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c49fb278_1195f0c, },
	// [5]ID_POPON_LABLE_DIAN
	{D_CTRL_LABEL, 0, 174, 53, 295, 26, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c49fb715_03e3cc7, },
	// [6]ID_POPON_INPUT_MINUTE
	{D_CTRL_INPUT, 0, 203, 53, 295, 36, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c49fb80d_38a6176, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_pop_power_on_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_pop_power_on_window[7];
D_Frame atv_pop_power_on_window = {
	run_ctrls_atv_pop_power_on_window, 
	ctrl_description_of_atv_pop_power_on_window, 
	atv_pop_power_on_window_init, 
};

