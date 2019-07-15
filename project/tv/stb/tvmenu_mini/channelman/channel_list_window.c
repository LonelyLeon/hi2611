/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2017-07-28 10:48:47

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-07-20 19:29:42.500

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
#define	ID_CHANNEL_LIST_LABEL_LIST	1
#define	ID_CHANNEL_LIST_LIST	2
#define	ID_CHANNEL_LIST_LABEL_RETURN_ICON	3
#define	ID_CHANNEL_LIST_LABEL_RETURN	4
#define	ID_CHANNEL_LIST_LABEL_OK_ICON	5
#define	ID_CHANNEL_LIST_LABEL_OK	6
#define	ID_CHANNEL_LIST_LEFT	7
#define	D_FRAMECONTROL_2	8
#define	ID_LIST_SCROLL	9

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a4ae5_3b91ebc={-1, atv_IMG_ID_FS_WHITE_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a4aef_232cb3={-1, -1, atv_IDS_CHANNEL_LIST, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a4e76_3a916c0={-1, atv_IMG_ID_FS_BUTTON_GRAY, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a5170_148622a={-1, -1, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a51c7_22267aa={-1, atv_IMG_ID_FS_BUTTON_GRAY, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a51f8_0ab5069={-1, -1, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c580983a_04e8bd={-1, atv_IMG_ID_sub_menu_direc_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5809953_38a101={-1, atv_IMG_ID_sub_menu_direc_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5847b54_3c872ae={atv_COLOR_ENUM_106, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c13a5f94_03e18be={atv_COLOR_ENUM_64, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c13b6cfd_177815={-1, atv_IMG_ID_FS_SCROL_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c142f024_0da66f5={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c142f024_0da6a24={-1, -1, -1, &atv_fmt_left_middle_h00_v00_signal_black_scroll_R2L, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a4ae5_3b91645={{&GUID_c56a4ae5_3b91ebc, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_CHANNEL_LIST_LABEL_LIST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a4aef_23223d7={{&GUID_c56a4aef_232cb3, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LIST}	"ID_CHANNEL_LIST_LIST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e={{NULL, &GUID_c5847b54_3c872ae, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6={{&GUID_c142f024_0da66f5, &GUID_c142f024_0da6a24, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c56a4b88_1e4761c[]={
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
};

static PREFIXCONST D_Coord POSTCONST list_ctrl_GUID_c56a4b88_1e41a4c[2]={50, 240, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c56a4b88_1e42b20[10][2]=
{
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
};
static PREFIXCONST D_FrameListDescr POSTCONST GUID_c56a4b88_1e46cf5={{&GUID_c13a5f94_03e18be, NULL, NULL, }, 1, 10, 10, 1, 2, 26, list_ctrl_GUID_c56a4b88_1e41a4c, 2, 0, D_LIST_FOCUS_TYPE_ROW, list_ctrl_GUID_c56a4b88_1e42b20, list_ctrl_GUID_c56a4b88_1e4761c, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_CHANNEL_LIST_LABEL_RETURN_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a4e76_3a91a87={{&GUID_c56a4e76_3a916c0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_CHANNEL_LIST_LABEL_RETURN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a5170_1481e92={{&GUID_c56a5170_148622a, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_CHANNEL_LIST_LABEL_OK_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a51c7_2222446={{&GUID_c56a51c7_22267aa, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_CHANNEL_LIST_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a51f8_0ab6597={{&GUID_c56a51f8_0ab5069, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_CHANNEL_LIST_LEFT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c580983a_04e4f5c={{&GUID_c580983a_04e8bd, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"D_FRAMECONTROL_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c5809953_38a30d4={{&GUID_c5809953_38a101, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_SCROLL}	"ID_LIST_SCROLL"
static PREFIXCONST D_FrameScrollBarDescr POSTCONST GUID_c13a6121_38a2358={{&GUID_c13b6cfd_177815, NULL, NULL, }, 1, 100, 10, 1, {-1, -1, -1, atv_IMG_ID_Scroll_Vernier, }, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_channel_list_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 195, 113, 0, 330, 350, 0, -1, (D_FrameCtrlDescr*)&GUID_c56a4ae5_3b91645, },
	// [1]ID_CHANNEL_LIST_LABEL_LIST
	{D_CTRL_LABEL, 0, 89, 6, 2, 179, 25, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a4aef_23223d7, },
	// [2]ID_CHANNEL_LIST_LIST
	{D_CTRL_LIST, 0, 15, 35, 2, 290, 278, 30, 9, (D_FrameCtrlDescr*)&GUID_c56a4b88_1e46cf5, },
	// [3]ID_CHANNEL_LIST_LABEL_RETURN_ICON
	{D_CTRL_LABEL, 0, 12, 318, 2, 75, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a4e76_3a91a87, },
	// [4]ID_CHANNEL_LIST_LABEL_RETURN
	{D_CTRL_LABEL, 0, 93, 318, 2, 60, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a5170_1481e92, },
	// [5]ID_CHANNEL_LIST_LABEL_OK_ICON
	{D_CTRL_LABEL, 0, 180, 318, 2, 75, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a51c7_2222446, },
	// [6]ID_CHANNEL_LIST_LABEL_OK
	{D_CTRL_LABEL, 0, 261, 318, 2, 60, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a51f8_0ab6597, },
	// [7]ID_CHANNEL_LIST_LEFT
	{D_CTRL_LABEL, 0, 64, 10, 2, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c580983a_04e4f5c, },
	// [8]D_FRAMECONTROL_2
	{D_CTRL_LABEL, 0, 280, 10, 2, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c5809953_38a30d4, },
	// [9]ID_LIST_SCROLL
	{D_CTRL_SCROLL, 0, 316, 35, 20, 4, 278, 30, -1, (D_FrameCtrlDescr*)&GUID_c13a6121_38a2358, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	channel_list_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_channel_list_window[10];
D_Frame channel_list_window = {
	run_ctrls_channel_list_window, 
	ctrl_description_of_channel_list_window, 
	channel_list_window_init, 
};

