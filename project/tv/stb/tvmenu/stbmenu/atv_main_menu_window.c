/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2015-05-18 11:06:31

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-05-13 17:11:10.881

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
#define	ID_MAINMENU_GROUP_ITEM_0	1
#define	ID_MAINMENU_GROUP_ITEM_1	2
#define	ID_MAINMENU_GROUP_ITEM_2	3
#define	ID_MAINMENU_GROUP_ITEM_3	4
#define	ID_MAINMENU_GROUP_ITEM_5	5
#define	ID_MAINMENU_GROUP_SUB_0	6
#define	ID_MAINMENU_GROUP_SUB_1	7
#define	ID_MAINMENU_GROUP_SUB_2	8
#define	ID_MAINMENU_GROUP_SUB_3	9
#define	ID_MAINMENU_IMAGE_ICON_0	10
#define	ID_MAINMENU_IMAGE_ICON_1	11
#define	ID_MAINMENU_IMAGE_ICON_2	12
#define	ID_MAINMENU_IMAGE_ICON_3	13
#define	ID_MAINMENU_LABEL_ITEM_TITLE_0	14
#define	ID_MAINMENU_LABEL_ITEM_TITLE_1	15
#define	ID_MAINMENU_LABEL_ITEM_TITLE_2	16
#define	ID_MAINMENU_LABEL_ITEM_TITLE_3	17
#define	ID_MAINMENU_LABEL_ITEM_CONTENT_0	18
#define	ID_MAINMENU_LABEL_ITEM_CONTENT_1	19
#define	ID_MAINMENU_LABEL_ITEM_CONTENT_2	20
#define	ID_MAINMENU_LABEL_ITEM_CONTENT_3	21
#define	ID_MAINMENU_LABEL_RETURN_IMAGE	22
#define	ID_MAINMENU_LABEL_RETURN	23
#define	ID_MAINMENU_LABEL_MOVE_IMAGE	24
#define	ID_MAINMENU_LABEL_MOVE	25
#define	ID_MAINMENU_LABEL_IMAGE_OK	26
#define	ID_MAINMENU_LABEL_OK	27

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40b72c4_03e4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40c55c8_2fd6eb4={-1, atv_IMG_ID_COMB_button_backgroud, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a023c3_29f6fb3={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a0266c_34b1d={-1, atv_IMG_ID_hint_button, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a031e5_2fdb97={-1, -1, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a03292_05d551b={-1, atv_IMG_ID_FS_Move, atv_IDS_MOVE, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a0334e_2423fd3={-1, -1, atv_IDS_MOVE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a033e6_37a20ab={-1, atv_IMG_ID_hint_button, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a03443_1861390={-1, -1, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4d07ba4_280553e={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_grey, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40b72c4_03e29={{&GUID_c40b72c4_03e4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_MAINMENU_GROUP_ITEM_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c3a1f_30d16a8={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_MAINMENU_GROUP_ITEM_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c749c_1577676={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_MAINMENU_GROUP_ITEM_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c9c08_3995e86={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_MAINMENU_GROUP_ITEM_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c9e21_1383b4={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_MAINMENU_GROUP_ITEM_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a67203_03e52b9={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_MAINMENU_GROUP_SUB_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c55c8_2fd5d82={{&GUID_c40c55c8_2fd6eb4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_GROUP}	"ID_MAINMENU_GROUP_SUB_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c9a81_33c3494={{&GUID_c40c55c8_2fd6eb4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_GROUP}	"ID_MAINMENU_GROUP_SUB_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c9cf4_186ce={{&GUID_c40c55c8_2fd6eb4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_GROUP}	"ID_MAINMENU_GROUP_SUB_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c9f2c_157675d={{&GUID_c40c55c8_2fd6eb4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_IMAGE}	"ID_MAINMENU_IMAGE_ICON_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c594f_31c10f2={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_IMAGE}	"ID_MAINMENU_IMAGE_ICON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c9afe_08c62bd={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_IMAGE}	"ID_MAINMENU_IMAGE_ICON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c9d44_29f17eb={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_IMAGE}	"ID_MAINMENU_IMAGE_ICON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c9fab_2322209={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_ITEM_TITLE_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c59ab_06d46b7={{&GUID_c4a023c3_29f6fb3, NULL, &GUID_c4d07ba4_280553e, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_ITEM_TITLE_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c9b6b_1a59fc={{&GUID_c4a023c3_29f6fb3, NULL, &GUID_c4d07ba4_280553e, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_ITEM_TITLE_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c9da2_119f23={{&GUID_c4a023c3_29f6fb3, NULL, &GUID_c4d07ba4_280553e, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_ITEM_TITLE_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40ca000_0fa359b={{&GUID_c4a023c3_29f6fb3, NULL, &GUID_c4d07ba4_280553e, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_ITEM_CONTENT_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c5ed9_05d3d2f={{&GUID_c40c55c8_2fd6eb4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_GROUP}	"ID_MAINMENU_LABEL_ITEM_CONTENT_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c9bb0_25144e1={{&GUID_c40c55c8_2fd6eb4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_GROUP}	"ID_MAINMENU_LABEL_ITEM_CONTENT_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40c9db7_2034ad3={{&GUID_c40c55c8_2fd6eb4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_ITEM_CONTENT_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40ca012_0fa41df={{&GUID_c40c55c8_2fd6eb4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_RETURN_IMAGE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a0266c_34b864={{&GUID_c4a0266c_34b1d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_RETURN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a031e5_2fd188b={{&GUID_c4a031e5_2fdb97, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_MOVE_IMAGE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a03292_05d6e85={{&GUID_c4a03292_05d551b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_MOVE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a0334e_24245b9={{&GUID_c4a0334e_2423fd3, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_IMAGE_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a033e6_37a4948={{&GUID_c4a033e6_37a20ab, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_LABEL}	"ID_MAINMENU_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a03443_18634fd={{&GUID_c4a03443_1861390, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_main_menu_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 50, 382, 0, 1180, 322, 0, -1, (D_FrameCtrlDescr*)&GUID_c40b72c4_03e29, },
	// [1]ID_MAINMENU_GROUP_ITEM_0
	{D_CTRL_GROUP, 0, 6, 111, 106, 1168, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c3a1f_30d16a8, },
	// [2]ID_MAINMENU_GROUP_ITEM_1
	{D_CTRL_GROUP, 0, 6, 151, 106, 1168, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c749c_1577676, },
	// [3]ID_MAINMENU_GROUP_ITEM_2
	{D_CTRL_GROUP, 0, 6, 191, 106, 1168, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c9c08_3995e86, },
	// [4]ID_MAINMENU_GROUP_ITEM_3
	{D_CTRL_GROUP, 0, 6, 231, 106, 1168, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c9e21_1383b4, },
	// [5]ID_MAINMENU_GROUP_ITEM_5
	{D_CTRL_GROUP, 0, 6, 6, 106, 1168, 100, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a67203_03e52b9, },
	// [6]ID_MAINMENU_GROUP_SUB_0
	{D_CTRL_GROUP, 1, 0, 0, -2, 204, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c55c8_2fd5d82, },
	// [7]ID_MAINMENU_GROUP_SUB_1
	{D_CTRL_GROUP, 2, 0, 0, -2, 204, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c9a81_33c3494, },
	// [8]ID_MAINMENU_GROUP_SUB_2
	{D_CTRL_GROUP, 3, 0, 0, -2, 204, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c9cf4_186ce, },
	// [9]ID_MAINMENU_GROUP_SUB_3
	{D_CTRL_GROUP, 4, 0, 0, -2, 204, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c9f2c_157675d, },
	// [10]ID_MAINMENU_IMAGE_ICON_0
	{D_CTRL_IMAGE, 6, 26, 2, 0, 32, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c594f_31c10f2, },
	// [11]ID_MAINMENU_IMAGE_ICON_1
	{D_CTRL_IMAGE, 7, 26, 2, 0, 32, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c9afe_08c62bd, },
	// [12]ID_MAINMENU_IMAGE_ICON_2
	{D_CTRL_IMAGE, 8, 26, 2, 0, 32, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c9d44_29f17eb, },
	// [13]ID_MAINMENU_IMAGE_ICON_3
	{D_CTRL_IMAGE, 9, 26, 2, 0, 32, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c9fab_2322209, },
	// [14]ID_MAINMENU_LABEL_ITEM_TITLE_0
	{D_CTRL_LABEL, 6, 86, 2, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c59ab_06d46b7, },
	// [15]ID_MAINMENU_LABEL_ITEM_TITLE_1
	{D_CTRL_LABEL, 7, 86, 3, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c9b6b_1a59fc, },
	// [16]ID_MAINMENU_LABEL_ITEM_TITLE_2
	{D_CTRL_LABEL, 8, 86, 3, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c9da2_119f23, },
	// [17]ID_MAINMENU_LABEL_ITEM_TITLE_3
	{D_CTRL_LABEL, 9, 86, 3, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c40ca000_0fa359b, },
	// [18]ID_MAINMENU_LABEL_ITEM_CONTENT_0
	{D_CTRL_LABEL, 1, 208, 0, -2, 960, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c5ed9_05d3d2f, },
	// [19]ID_MAINMENU_LABEL_ITEM_CONTENT_1
	{D_CTRL_GROUP, 2, 208, 0, -2, 960, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c9bb0_25144e1, },
	// [20]ID_MAINMENU_LABEL_ITEM_CONTENT_2
	{D_CTRL_GROUP, 3, 208, 0, -2, 960, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c40c9db7_2034ad3, },
	// [21]ID_MAINMENU_LABEL_ITEM_CONTENT_3
	{D_CTRL_LABEL, 4, 208, 0, -2, 960, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c40ca012_0fa41df, },
	// [22]ID_MAINMENU_LABEL_RETURN_IMAGE
	{D_CTRL_LABEL, 0, 280, 278, 106, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a0266c_34b864, },
	// [23]ID_MAINMENU_LABEL_RETURN
	{D_CTRL_LABEL, 0, 388, 286, 106, 68, 23, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a031e5_2fd188b, },
	// [24]ID_MAINMENU_LABEL_MOVE_IMAGE
	{D_CTRL_LABEL, 0, 510, 278, 106, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a03292_05d6e85, },
	// [25]ID_MAINMENU_LABEL_MOVE
	{D_CTRL_LABEL, 0, 618, 286, 106, 68, 23, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a0334e_24245b9, },
	// [26]ID_MAINMENU_LABEL_IMAGE_OK
	{D_CTRL_LABEL, 0, 742, 278, 106, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a033e6_37a4948, },
	// [27]ID_MAINMENU_LABEL_OK
	{D_CTRL_LABEL, 0, 850, 286, 106, 68, 23, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a03443_18634fd, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_main_menu_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_main_menu_window[28];
D_Frame atv_main_menu_window = {
	run_ctrls_atv_main_menu_window, 
	ctrl_description_of_atv_main_menu_window, 
	atv_main_menu_window_init, 
};

