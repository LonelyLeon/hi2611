/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-05-08 17:04:44

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
#define	ID_ATV_GROUP_SUBBACK	1
#define	ID_ATV_GROUP_SUB1	2
#define	ID_ATV_BUTTOB_SUBINFO1	3
#define	ID_ATV_BUTTOB_SUBINFO2	4
#define	ID_ATV_BUTTOB_SUBINFO3	5
#define	ID_ATV_BUTTOB_SUBINFO4	6
#define	ID_ATV_BUTTOB_SUBINFO5	7
#define	ID_ATV_BUTTOB_SUBINFO6	8
#define	ID_ATV_BUTTOB_SUBINFO7	9
#define	ID_ATV_BUTTOB_SUBINFO8	10
#define	ID_ATV_IMAGE_SUBPIC	11
#define	ID_ATV_LABEL_UNDERLINE	12

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7a3ba51_00f22ce={-1, atv_IMG_ID_FS_SUBMENU_BUTTON_NORMAL, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c750f2a1_03ba2ce={-1, atv_IMG_ID_FS_SUBMENU_BUTTON_FOCSE, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c22cba51_07a30fe={-1, atv_IMG_ID_FS_SUBMENU_BUTTON_ENABLE, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c227a0fc1_0ba53e={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c9fa7d1d_3db61a6={atv_COLOR_ENUM_102, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a3b535_01f29={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_ATV_GROUP_SUBBACK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a3b64f_03e765a={{&GUID_c227a0fc1_0ba53e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_ATV_GROUP_SUB1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a3b915_1e47639={{&GUID_c7a3ba51_00f22ce, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_ATV_BUTTOB_SUBINFO1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a3ba51_00f429f={{&GUID_c7a3ba51_00f22ce, &GUID_c750f2a1_03ba2ce, &GUID_c22cba51_07a30fe, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_ATV_BUTTOB_SUBINFO2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a3bc53_280375a={{&GUID_c7a3ba51_00f22ce, &GUID_c750f2a1_03ba2ce, &GUID_c22cba51_07a30fe, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_ATV_BUTTOB_SUBINFO3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c70faa51_03b429f={{&GUID_c7a3ba51_00f22ce, &GUID_c750f2a1_03ba2ce, &GUID_c22cba51_07a30fe, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_BUTTON}	"ID_ATV_BUTTOB_SUBINFO4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a07533_2b5c8ca={{&GUID_c7a3ba51_00f22ce, &GUID_c750f2a1_03ba2ce, &GUID_c22cba51_07a30fe, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_BUTTON}	"ID_ATV_BUTTOB_SUBINFO5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a50f41_0a3b29f={{&GUID_c7a3ba51_00f22ce, &GUID_c750f2a1_03ba2ce, &GUID_c22cba51_07a30fe, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_BUTTON}	"ID_ATV_BUTTOB_SUBINFO6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a28c53_75013ba={{&GUID_c7a3ba51_00f22ce, &GUID_c750f2a1_03ba2ce, &GUID_c22cba51_07a30fe, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_BUTTON}	"ID_ATV_BUTTOB_SUBINFO7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c3b75c53_2872a0a={{&GUID_c7a3ba51_00f22ce, &GUID_c750f2a1_03ba2ce, &GUID_c22cba51_07a30fe, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_BUTTON}	"ID_ATV_BUTTOB_SUBINFO8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c32a5c53_2b7780a={{&GUID_c7a3ba51_00f22ce, &GUID_c750f2a1_03ba2ce, &GUID_c22cba51_07a30fe, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_IMAGE}	"ID_ATV_IMAGE_SUBPIC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a47cbb_1b56443={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_ATV_LABEL_UNDERLINE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9fa7d1d_3db4ddc={{&GUID_c9fa7d1d_3db61a6, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_sub_menu_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 400, 0, 960, 140, 0, -1, (D_FrameCtrlDescr*)&GUID_c7a3b535_01f29, },
	// [1]ID_ATV_GROUP_SUBBACK
	{D_CTRL_GROUP, 0, 0, 0, -28, 960, 140, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a3b64f_03e765a, },
	// [2]ID_ATV_GROUP_SUB1
	{D_CTRL_GROUP, 1, 0, 0, 0, 960, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a3b915_1e47639, },
	// [3]ID_ATV_BUTTOB_SUBINFO1
	{D_CTRL_BUTTON, 2, 0, 0, 0, 120, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a3ba51_00f429f, },
	// [4]ID_ATV_BUTTOB_SUBINFO2
	{D_CTRL_BUTTON, 2, 120, 0, 0, 120, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a3bc53_280375a, },
	// [5]ID_ATV_BUTTOB_SUBINFO3
	{D_CTRL_BUTTON, 2, 240, 0, 0, 120, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c70faa51_03b429f, },
	// [6]ID_ATV_BUTTOB_SUBINFO4
	{D_CTRL_BUTTON, 2, 360, 0, 0, 120, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a07533_2b5c8ca, },
	// [7]ID_ATV_BUTTOB_SUBINFO5
	{D_CTRL_BUTTON, 2, 480, 0, 0, 120, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a50f41_0a3b29f, },
	// [8]ID_ATV_BUTTOB_SUBINFO6
	{D_CTRL_BUTTON, 2, 600, 0, 0, 120, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a28c53_75013ba, },
	// [9]ID_ATV_BUTTOB_SUBINFO7
	{D_CTRL_BUTTON, 2, 720, 0, 0, 120, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c3b75c53_2872a0a, },
	// [10]ID_ATV_BUTTOB_SUBINFO8
	{D_CTRL_BUTTON, 2, 840, 0, 0, 120, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c32a5c53_2b7780a, },
	// [11]ID_ATV_IMAGE_SUBPIC
	{D_CTRL_IMAGE, 1, 32, 40, 0, 70, 60, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a47cbb_1b56443, },
	// [12]ID_ATV_LABEL_UNDERLINE
	{D_CTRL_LABEL, 1, 0, 103, 48, 960, 2, 30, -1, (D_FrameCtrlDescr*)&GUID_c9fa7d1d_3db4ddc, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_sub_menu_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_sub_menu_window[13];
D_Frame atv_sub_menu_window = {
	run_ctrls_atv_sub_menu_window, 
	ctrl_description_of_atv_sub_menu_window, 
	atv_sub_menu_window_init, 
};

