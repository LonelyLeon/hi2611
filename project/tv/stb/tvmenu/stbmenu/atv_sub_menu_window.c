/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2019-05-14 11:56:54

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2019-03-11  9:04:05.382

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
#define	ID_SUBMENU_IMAGE_ICON	1
#define	ID_SUBMENU_LABEL_TITLE	2
#define	ID_SUBMENU_BUTTON_ICON_0	3
#define	ID_SUBMENU_BUTTON_ICON_1	4
#define	ID_SUBMENU_BUTTON_ICON_2	5
#define	ID_SUBMENU_BUTTON_ICON_3	6
#define	ID_SUBMENU_BUTTON_ICON_4	7
#define	ID_SUBMENU_BUTTON_ICON_5	8
#define	ID_SUBMENU_BUTTON_ICON_6	9
#define	ID_SUBMENU_BUTTON_ICON_7	10
#define	ID_SUBMENU_LABEL_ITEM_0	11
#define	ID_SUBMENU_LABEL_ITEM_1	12
#define	ID_SUBMENU_LABEL_ITEM_2	13
#define	ID_SUBMENU_LABEL_ITEM_3	14
#define	ID_SUBMENU_LABEL_ITEM_4	15
#define	ID_SUBMENU_LABEL_ITEM_5	16
#define	ID_SUBMENU_LABEL_ITEM_6	17
#define	ID_SUBMENU_LABEL_ITEM_7	18

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40b72c4_03e4823={-1, atv_IMG_ID_menu_backgroud_blue, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40c3428_1f43d6c={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40c3428_1f42cd6={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a2981f_0cb99={-1, -1, atv_IDS_NULL, &atv_fmt_center_middle_h00_v00_multi_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_ca056d45_0d12f14={-1, atv_IMG_ID_title_backgroud, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_ca05953c_05272ae={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40b72c4_03e29={{&GUID_c40b72c4_03e4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_IMAGE}	"ID_SUBMENU_IMAGE_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40b92d2_2617a89={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_SUBMENU_LABEL_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40b95a1_0003f89={{&GUID_c40c3428_1f43d6c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_SUBMENU_BUTTON_ICON_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ca056d45_0d13cd0={{NULL, &GUID_ca056d45_0d12f14, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_SUBMENU_BUTTON_ICON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ca056d45_0d13cd1={{NULL, &GUID_ca056d45_0d12f14, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_SUBMENU_BUTTON_ICON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ca056d45_0d13cd2={{NULL, &GUID_ca056d45_0d12f14, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_BUTTON}	"ID_SUBMENU_BUTTON_ICON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ca056d45_0d13cd3={{NULL, &GUID_ca056d45_0d12f14, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_BUTTON}	"ID_SUBMENU_BUTTON_ICON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ca056d45_0d13cd4={{NULL, &GUID_ca056d45_0d12f14, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_BUTTON}	"ID_SUBMENU_BUTTON_ICON_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ca056d45_0d13cd5={{NULL, &GUID_ca056d45_0d12f14, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_BUTTON}	"ID_SUBMENU_BUTTON_ICON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ca056d45_0d13cd6={{NULL, &GUID_ca056d45_0d12f14, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_BUTTON}	"ID_SUBMENU_BUTTON_ICON_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ca056d45_0d13cd7={{NULL, &GUID_ca056d45_0d12f14, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_SUBMENU_LABEL_ITEM_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c3428_1f44ae1={{&GUID_ca05953c_05272ae, &GUID_c40c3428_1f42cd6, &GUID_c4a2981f_0cb99, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_SUBMENU_LABEL_ITEM_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c34a6_2de6952={{&GUID_ca05953c_05272ae, &GUID_c40c3428_1f42cd6, &GUID_c4a2981f_0cb99, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_SUBMENU_LABEL_ITEM_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c3508_1e45af1={{&GUID_ca05953c_05272ae, &GUID_c40c3428_1f42cd6, &GUID_c4a2981f_0cb99, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_SUBMENU_LABEL_ITEM_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c362a_1b5bb3={{&GUID_ca05953c_05272ae, &GUID_c40c3428_1f42cd6, &GUID_c4a2981f_0cb99, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_LABEL}	"ID_SUBMENU_LABEL_ITEM_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c368d_1d47e87={{&GUID_ca05953c_05272ae, &GUID_c40c3428_1f42cd6, &GUID_c4a2981f_0cb99, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_SUBMENU_LABEL_ITEM_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c36ed_38a124={{&GUID_ca05953c_05272ae, &GUID_c40c3428_1f42cd6, &GUID_c4a2981f_0cb99, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_SUBMENU_LABEL_ITEM_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c3741_1f44d06={{&GUID_ca05953c_05272ae, &GUID_c40c3428_1f42cd6, &GUID_c4a2981f_0cb99, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_LABEL}	"ID_SUBMENU_LABEL_ITEM_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c3871_196174d={{&GUID_ca05953c_05272ae, &GUID_c40c3428_1f42cd6, &GUID_c4a2981f_0cb99, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_sub_menu_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 56, 296, 0, 1168, 100, 0, -1, (D_FrameCtrlDescr*)&GUID_c40b72c4_03e29, },
	// [1]ID_SUBMENU_IMAGE_ICON
	{D_CTRL_IMAGE, 0, 44, 4, 20, 64, 64, 30, -1, (D_FrameCtrlDescr*)&GUID_c40b92d2_2617a89, },
	// [2]ID_SUBMENU_LABEL_TITLE
	{D_CTRL_LABEL, 0, 26, 73, 20, 100, 24, 30, -1, (D_FrameCtrlDescr*)&GUID_c40b95a1_0003f89, },
	// [3]ID_SUBMENU_BUTTON_ICON_0
	{D_CTRL_BUTTON, 0, 208, 2, 20, 120, 40, 30, 11, (D_FrameCtrlDescr*)&GUID_ca056d45_0d13cd0, },
	// [4]ID_SUBMENU_BUTTON_ICON_1
	{D_CTRL_BUTTON, 0, 328, 2, 20, 120, 40, 30, 12, (D_FrameCtrlDescr*)&GUID_ca056d45_0d13cd1, },
	// [5]ID_SUBMENU_BUTTON_ICON_2
	{D_CTRL_BUTTON, 0, 448, 2, 20, 120, 40, 30, 13, (D_FrameCtrlDescr*)&GUID_ca056d45_0d13cd2, },
	// [6]ID_SUBMENU_BUTTON_ICON_3
	{D_CTRL_BUTTON, 0, 568, 2, 20, 120, 40, 30, 14, (D_FrameCtrlDescr*)&GUID_ca056d45_0d13cd3, },
	// [7]ID_SUBMENU_BUTTON_ICON_4
	{D_CTRL_BUTTON, 0, 688, 2, 20, 120, 40, 30, 15, (D_FrameCtrlDescr*)&GUID_ca056d45_0d13cd4, },
	// [8]ID_SUBMENU_BUTTON_ICON_5
	{D_CTRL_BUTTON, 0, 808, 2, 20, 120, 40, 30, 16, (D_FrameCtrlDescr*)&GUID_ca056d45_0d13cd5, },
	// [9]ID_SUBMENU_BUTTON_ICON_6
	{D_CTRL_BUTTON, 0, 928, 2, 20, 120, 40, 30, 17, (D_FrameCtrlDescr*)&GUID_ca056d45_0d13cd6, },
	// [10]ID_SUBMENU_BUTTON_ICON_7
	{D_CTRL_BUTTON, 0, 1048, 2, 20, 120, 40, 30, 18, (D_FrameCtrlDescr*)&GUID_ca056d45_0d13cd7, },
	// [11]ID_SUBMENU_LABEL_ITEM_0
	{D_CTRL_LABEL, 3, 5, 0, 20, 110, 40, 30, 3, (D_FrameCtrlDescr*)&GUID_c40c3428_1f44ae1, },
	// [12]ID_SUBMENU_LABEL_ITEM_1
	{D_CTRL_LABEL, 4, 5, 0, 20, 110, 40, 30, 4, (D_FrameCtrlDescr*)&GUID_c40c34a6_2de6952, },
	// [13]ID_SUBMENU_LABEL_ITEM_2
	{D_CTRL_LABEL, 5, 5, 0, 20, 110, 40, 30, 5, (D_FrameCtrlDescr*)&GUID_c40c3508_1e45af1, },
	// [14]ID_SUBMENU_LABEL_ITEM_3
	{D_CTRL_LABEL, 6, 5, 0, 20, 110, 40, 30, 6, (D_FrameCtrlDescr*)&GUID_c40c362a_1b5bb3, },
	// [15]ID_SUBMENU_LABEL_ITEM_4
	{D_CTRL_LABEL, 7, 5, 0, 20, 110, 40, 30, 7, (D_FrameCtrlDescr*)&GUID_c40c368d_1d47e87, },
	// [16]ID_SUBMENU_LABEL_ITEM_5
	{D_CTRL_LABEL, 8, 5, 0, 20, 110, 40, 30, 8, (D_FrameCtrlDescr*)&GUID_c40c36ed_38a124, },
	// [17]ID_SUBMENU_LABEL_ITEM_6
	{D_CTRL_LABEL, 9, 5, 0, 20, 110, 40, 30, 9, (D_FrameCtrlDescr*)&GUID_c40c3741_1f44d06, },
	// [18]ID_SUBMENU_LABEL_ITEM_7
	{D_CTRL_LABEL, 10, 5, 0, 20, 110, 40, 30, 10, (D_FrameCtrlDescr*)&GUID_c40c3871_196174d, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_sub_menu_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_sub_menu_window[19];
D_Frame atv_sub_menu_window = {
	run_ctrls_atv_sub_menu_window, 
	ctrl_description_of_atv_sub_menu_window, 
	atv_sub_menu_window_init, 
};

