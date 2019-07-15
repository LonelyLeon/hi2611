/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {wenl}
	on computer "PRWENL"
	update/create time:	2019-01-30 14:13:31

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
#define	ID_CHANNEL_LIST_LABEL_LIST	1
#define	ID_CHANNEL_LIST_LIST	2
#define	ID_CHANNEL_LIST_LABEL_RETURN_ICON	3
#define	ID_CHANNEL_LIST_LABEL_RETURN	4
#define	ID_CHANNEL_LIST_LABEL_OK_ICON	5
#define	ID_CHANNEL_LIST_LABEL_OK	6
#define	ID_CHANNEL_LIST_LEFT	7
#define	D_FRAMECONTROL_2	8
#define	ID_LIST_SCROLL	9
#define	ID_CHANNEL_LIST_TYPE	10
#define	ID_CHANNEL_LIST_LABEL_TOTAL_TYPE	11
#define	ID_CHANNEL_LIST_LABEL_TOTAL_LIST	12

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a4ae5_3b91ebc={atv_COLOR_ENUM_110, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a4aef_232cb3={-1, -1, atv_IDS_CHANNEL_LIST, &atv_fmt_middle_h00_v00_single_orange, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a4e76_3a916c0={-1, atv_IMG_ID_hint_button, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a5170_148622a={-1, -1, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a51c7_22267aa={-1, atv_IMG_ID_hint_button, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a51f8_0ab5069={-1, -1, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c580983a_04e8bd={-1, atv_IMG_ID_search_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5809953_38a101={-1, atv_IMG_ID_search_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c13a5f94_03e18be={atv_COLOR_ENUM_111, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c13b6cfd_177815={-1, atv_IMG_ID_Scroll_Bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6f85638_1a574d={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6f85638_1a54dc8={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6f85640_04e66bb={-1, -1, -1, &atv_fmt_left_middle_h00_v00_signal_whilte_scroll_R2L, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6f85640_04e428b={-1, -1, -1, &atv_fmt_left_middle_h00_v00_signal_black_scroll_R2L, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6f85807_00f6ad6={-1, -1, atv_IDS_DIGITAL_TONE, &atv_fmt_right_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6f85896_01f368e={-1, -1, atv_IDS_SEARCH_AUTO, &atv_fmt_right_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6fb9034_157b8f={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6fb9034_157405e={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6fb99d7_2425753={atv_COLOR_ENUM_106, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c6fb99d7_2421ab1={atv_COLOR_ENUM_107, -1, -1, NULL, };

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
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e={{NULL, &GUID_c6fb99d7_2425753, &GUID_c6fb99d7_2421ab1, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6={{&GUID_c6f85638_1a574d, &GUID_c6f85638_1a54dc8, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a7={{&GUID_c6f85640_04e66bb, &GUID_c6f85640_04e428b, NULL, }, 1, };
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
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
};

static PREFIXCONST D_Coord POSTCONST list_ctrl_GUID_c56a4b88_1e41a4c[2]={61, 340, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c56a4b88_1e42b20[11][2]=
{
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a7, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a7, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a7, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a7, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a7, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a7, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a7, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a7, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a7, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a7, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, &GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a7, },
};
static PREFIXCONST D_FrameListDescr POSTCONST GUID_c56a4b88_1e46cf5={{&GUID_c13a5f94_03e18be, NULL, NULL, }, 1, 11, 11, 1, 2, 32, list_ctrl_GUID_c56a4b88_1e41a4c, 10, 0, D_LIST_FOCUS_TYPE_ROW, list_ctrl_GUID_c56a4b88_1e42b20, list_ctrl_GUID_c56a4b88_1e4761c, };

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
// definition of [10]{D_CTRL_LIST}	"ID_CHANNEL_LIST_TYPE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6f8395d_0ab6784_GUID_c6f85186_1285af1={{NULL, &GUID_c6fb99d7_2425753, &GUID_c6fb99d7_2421ab1, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6f8395d_0ab6784_GUID_c6f8579e_2fd4080={{&GUID_c6fb9034_157b8f, &GUID_c6fb9034_157405e, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c6f8395d_0ab18be[]={
	&GUID_c6f8395d_0ab6784_GUID_c6f85186_1285af1, 
	&GUID_c6f8395d_0ab6784_GUID_c6f85186_1285af1, 
	&GUID_c6f8395d_0ab6784_GUID_c6f85186_1285af1, 
	&GUID_c6f8395d_0ab6784_GUID_c6f85186_1285af1, 
	&GUID_c6f8395d_0ab6784_GUID_c6f85186_1285af1, 
	&GUID_c6f8395d_0ab6784_GUID_c6f85186_1285af1, 
	&GUID_c6f8395d_0ab6784_GUID_c6f85186_1285af1, 
	&GUID_c6f8395d_0ab6784_GUID_c6f85186_1285af1, 
	&GUID_c6f8395d_0ab6784_GUID_c6f85186_1285af1, 
	&GUID_c6f8395d_0ab6784_GUID_c6f85186_1285af1, 
	&GUID_c6f8395d_0ab6784_GUID_c6f85186_1285af1, 
};

static PREFIXCONST D_Coord POSTCONST list_ctrl_GUID_c6f8395d_0ab29[1]={348, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c6f8395d_0ab4823[11][1]=
{
	{&GUID_c6f8395d_0ab6784_GUID_c6f8579e_2fd4080, },
	{&GUID_c6f8395d_0ab6784_GUID_c6f8579e_2fd4080, },
	{&GUID_c6f8395d_0ab6784_GUID_c6f8579e_2fd4080, },
	{&GUID_c6f8395d_0ab6784_GUID_c6f8579e_2fd4080, },
	{&GUID_c6f8395d_0ab6784_GUID_c6f8579e_2fd4080, },
	{&GUID_c6f8395d_0ab6784_GUID_c6f8579e_2fd4080, },
	{&GUID_c6f8395d_0ab6784_GUID_c6f8579e_2fd4080, },
	{&GUID_c6f8395d_0ab6784_GUID_c6f8579e_2fd4080, },
	{&GUID_c6f8395d_0ab6784_GUID_c6f8579e_2fd4080, },
	{&GUID_c6f8395d_0ab6784_GUID_c6f8579e_2fd4080, },
	{&GUID_c6f8395d_0ab6784_GUID_c6f8579e_2fd4080, },
};
static PREFIXCONST D_FrameListDescr POSTCONST GUID_c6f8395d_0ab6784={{&GUID_c13a5f94_03e18be, NULL, NULL, }, 1, 11, 11, 1, 1, 32, list_ctrl_GUID_c6f8395d_0ab29, 10, 0, D_LIST_FOCUS_TYPE_ROW, list_ctrl_GUID_c6f8395d_0ab4823, list_ctrl_GUID_c6f8395d_0ab18be, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_CHANNEL_LIST_LABEL_TOTAL_TYPE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6f85807_00f2f14={{&GUID_c6f85807_00f6ad6, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_CHANNEL_LIST_LABEL_TOTAL_LIST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c6f85896_01f54dc={{&GUID_c6f85896_01f368e, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_iptv_list_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 20, 50, 0, 840, 580, 0, -1, (D_FrameCtrlDescr*)&GUID_c56a4ae5_3b91645, },
	// [1]ID_CHANNEL_LIST_LABEL_LIST
	{D_CTRL_LABEL, 0, 513, 11, 2, 179, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a4aef_23223d7, },
	// [2]ID_CHANNEL_LIST_LIST
	{D_CTRL_LIST, 0, 402, 73, 2, 401, 452, 30, 9, (D_FrameCtrlDescr*)&GUID_c56a4b88_1e46cf5, },
	// [3]ID_CHANNEL_LIST_LABEL_RETURN_ICON
	{D_CTRL_LABEL, 0, 150, 537, 2, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a4e76_3a91a87, },
	// [4]ID_CHANNEL_LIST_LABEL_RETURN
	{D_CTRL_LABEL, 0, 264, 546, 2, 63, 21, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a5170_1481e92, },
	// [5]ID_CHANNEL_LIST_LABEL_OK_ICON
	{D_CTRL_LABEL, 0, 545, 537, 2, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a51c7_2222446, },
	// [6]ID_CHANNEL_LIST_LABEL_OK
	{D_CTRL_LABEL, 0, 653, 545, 2, 55, 22, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a51f8_0ab6597, },
	// [7]ID_CHANNEL_LIST_LEFT
	{D_CTRL_LABEL, 0, 488, 20, 2, 12, 12, 30, -1, (D_FrameCtrlDescr*)&GUID_c580983a_04e4f5c, },
	// [8]D_FRAMECONTROL_2
	{D_CTRL_LABEL, 0, 704, 20, 2, 12, 12, 30, -1, (D_FrameCtrlDescr*)&GUID_c5809953_38a30d4, },
	// [9]ID_LIST_SCROLL
	{D_CTRL_SCROLL, 0, 815, 71, 20, 6, 450, 30, 2, (D_FrameCtrlDescr*)&GUID_c13a6121_38a2358, },
	// [10]ID_CHANNEL_LIST_TYPE
	{D_CTRL_LIST, 0, 33, 73, 20, 348, 452, 30, -1, (D_FrameCtrlDescr*)&GUID_c6f8395d_0ab6784, },
	// [11]ID_CHANNEL_LIST_LABEL_TOTAL_TYPE
	{D_CTRL_LABEL, 0, 170, 40, 20, 209, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c6f85807_00f2f14, },
	// [12]ID_CHANNEL_LIST_LABEL_TOTAL_LIST
	{D_CTRL_LABEL, 0, 597, 40, 20, 203, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c6f85896_01f54dc, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	iptv_list_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_iptv_list_window[13];
D_Frame iptv_list_window = {
	run_ctrls_iptv_list_window, 
	ctrl_description_of_iptv_list_window, 
	iptv_list_window_init, 
};

