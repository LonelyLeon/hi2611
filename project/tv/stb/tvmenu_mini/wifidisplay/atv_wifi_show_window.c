/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2017-09-15 14:36:19

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-04-06 16:33:25.890

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
#define	ID_WIFISHOW_HINT	1
#define	ID_WIFISHOW_GROUP_ALL	2
#define	ID_WIFISHOW_IMAGE_ICON	3
#define	ID_WIFISHOW_LABEL	4
#define	ID_WIFISHOW_LABLE_CONNECT	5
#define	ID_WIFISHOW_LABLE_INFO	6
#define	ID_WIFISHOW_LABLE_INFO2	7
#define	ID_WIFISHOW_BUTTON	8
#define	ID_WIFISHOW_LABLE_HINTINFO	9
#define	ID_WIFISHOW_LABLE_INSTRUCTION	10
#define	ID_WIFISHOW_LABLE_2	11
#define	ID_WIFISHOW_LABLE_NOTICE	12

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c924511c_0ab6784={atv_COLOR_ENUM_108, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c924517d_02e5f90={atv_COLOR_ENUM_25, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c92452b8_20341bb={-1, atv_IMG_ID_wifi_show_icon, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c9245388_07d2ea6={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c9245d41_35b4db7={-1, atv_IMG_ID_COMB_music_select_focus, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c9245f79_1b52d12={-1, -1, -1, &atv_fmt_left_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c924cbd4_232d8a={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c924511c_0ab18be={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_WIFISHOW_HINT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9b18241c_0a51be={{&GUID_c924511c_0ab6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_IMAGE}	"ID_WIFISHOW_GROUP_ALL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c924517d_02e6952={{&GUID_c924517d_02e5f90, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_IMAGE}	"ID_WIFISHOW_IMAGE_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92452b8_2035af1={{&GUID_c92452b8_20341bb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_WIFISHOW_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9245388_07dbb3={{&GUID_c9245388_07d2ea6, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_WIFISHOW_LABLE_CONNECT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92454ab_2327e87={{&GUID_c9245388_07d2ea6, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_WIFISHOW_LABLE_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92455be_399124={{&GUID_c9245388_07d2ea6, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_WIFISHOW_LABLE_INFO2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c924c836_1b51356={{&GUID_c924cbd4_232d8a, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_BUTTON}	"ID_WIFISHOW_BUTTON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9245d41_35b4d06={{&GUID_c9245d41_35b4db7, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_WIFISHOW_LABLE_HINTINFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9245f79_1b539b3={{&GUID_c9245f79_1b52d12, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_WIFISHOW_LABLE_INSTRUCTION"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92460d0_29f6443={{&GUID_c9245f79_1b52d12, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_WIFISHOW_LABLE_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9249c02_2038de={{&GUID_c9245f79_1b52d12, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_WIFISHOW_LABLE_NOTICE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92471d4_29f701f={{&GUID_c9245f79_1b52d12, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_wifi_show_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 1280, 720, 0, -1, (D_FrameCtrlDescr*)&GUID_c924511c_0ab18be, },
	// [1]ID_WIFISHOW_HINT
	{D_CTRL_GROUP, 0, 0, 0, 0, 1280, 720, 0, -1, (D_FrameCtrlDescr*)&GUID_c9b18241c_0a51be, },
	// [2]ID_WIFISHOW_GROUP_ALL
	{D_CTRL_IMAGE, 1, 832, 0, 20, 448, 720, 30, -1, (D_FrameCtrlDescr*)&GUID_c924517d_02e6952, },
	// [3]ID_WIFISHOW_IMAGE_ICON
	{D_CTRL_IMAGE, 1, 359, 135, 20, 114, 92, 30, -1, (D_FrameCtrlDescr*)&GUID_c92452b8_2035af1, },
	// [4]ID_WIFISHOW_LABEL
	{D_CTRL_LABEL, 1, 344, 230, 20, 142, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c9245388_07dbb3, },
	// [5]ID_WIFISHOW_LABLE_CONNECT
	{D_CTRL_LABEL, 1, 316, 318, 20, 200, 50, 30, -1, (D_FrameCtrlDescr*)&GUID_c92454ab_2327e87, },
	// [6]ID_WIFISHOW_LABLE_INFO
	{D_CTRL_LABEL, 1, 100, 590, 20, 120, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c92455be_399124, },
	// [7]ID_WIFISHOW_LABLE_INFO2
	{D_CTRL_LABEL, 1, 220, 590, 0, 200, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c924c836_1b51356, },
	// [8]ID_WIFISHOW_BUTTON
	{D_CTRL_BUTTON, 1, 590, 585, 20, 100, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c9245d41_35b4d06, },
	// [9]ID_WIFISHOW_LABLE_HINTINFO
	{D_CTRL_LABEL, 2, 26, 140, 0, 400, 60, 30, -1, (D_FrameCtrlDescr*)&GUID_c9245f79_1b539b3, },
	// [10]ID_WIFISHOW_LABLE_INSTRUCTION
	{D_CTRL_LABEL, 2, 28, 72, 0, 155, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c92460d0_29f6443, },
	// [11]ID_WIFISHOW_LABLE_2
	{D_CTRL_LABEL, 2, 26, 210, 0, 400, 230, 30, -1, (D_FrameCtrlDescr*)&GUID_c9249c02_2038de, },
	// [12]ID_WIFISHOW_LABLE_NOTICE
	{D_CTRL_LABEL, 2, 26, 566, 0, 400, 60, 30, -1, (D_FrameCtrlDescr*)&GUID_c92471d4_29f701f, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_wifi_show_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_wifi_show_window[13];
D_Frame atv_wifi_show_window = {
	run_ctrls_atv_wifi_show_window, 
	ctrl_description_of_atv_wifi_show_window, 
	atv_wifi_show_window_init, 
};

