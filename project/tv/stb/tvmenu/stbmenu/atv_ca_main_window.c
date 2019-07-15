/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {songyw}
	on computer "PRSONGYW"
	update/create time:	2016-04-22 09:12:08

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2016-04-15 11:54:34.625

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
#define	ID_CA_LABEL_TITLE	1
#define	ID_CA_LIST	2
#define	ID_CA_LABEL_RETURN_ICON	3
#define	ID_CA_LABEL_RETURN	4
#define	ID_CA_LABEL_OK_ICON	5
#define	ID_CA_LABEL_OK	6
#define	ID_CA_LABEL_LINE	7

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a4ae5_3b91ebc={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a4aef_232cb3={-1, -1, atv_IDS_RECEIVE_CHOISE, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a4e76_3a916c0={-1, atv_IMG_ID_hint_button, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a5170_148622a={-1, -1, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a51c7_22267aa={-1, atv_IMG_ID_hint_button, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a51f8_0ab5069={-1, -1, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79bc3bc_1e41bcf={atv_COLOR_ENUM_106, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79bdfcc_2618bb={-1, -1, -1, &atv_fmt_left_middle_h20_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79c2b80_07d18be={atv_COLOR_ENUM_1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a4ae5_3b91645={{&GUID_c56a4ae5_3b91ebc, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_CA_LABEL_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a4aef_23223d7={{&GUID_c56a4aef_232cb3, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LIST}	"ID_CA_LIST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e={{NULL, &GUID_c79bc3bc_1e41bcf, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6={{&GUID_c79bdfcc_2618bb, &GUID_c79bdfcc_2618bb, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c56a4b88_1e4761c[]={
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
	&GUID_c56a4b88_1e46cf5_GUID_c56a4df9_01f130e, 
};

static PREFIXCONST D_Coord POSTCONST list_ctrl_GUID_c56a4b88_1e41a4c[1]={352, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c56a4b88_1e42b20[6][1]=
{
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
	{&GUID_c56a4b88_1e46cf5_GUID_c56a4e4c_13852a6, },
};
static PREFIXCONST D_FrameListDescr POSTCONST GUID_c56a4b88_1e46cf5={{NULL, NULL, NULL, }, 1, 6, 6, 1, 1, 32, list_ctrl_GUID_c56a4b88_1e41a4c, 10, 0, D_LIST_FOCUS_TYPE_ROW, list_ctrl_GUID_c56a4b88_1e42b20, list_ctrl_GUID_c56a4b88_1e4761c, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_CA_LABEL_RETURN_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a4e76_3a91a87={{&GUID_c56a4e76_3a916c0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_CA_LABEL_RETURN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a5170_1481e92={{&GUID_c56a5170_148622a, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_CA_LABEL_OK_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a51c7_2222446={{&GUID_c56a51c7_22267aa, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_CA_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a51f8_0ab6597={{&GUID_c56a51f8_0ab5069, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_CA_LABEL_LINE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c79c2b80_07d4823={{&GUID_c79c2b80_07d18be, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_ca_main_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 430, 100, 0, 420, 400, 0, -1, (D_FrameCtrlDescr*)&GUID_c56a4ae5_3b91645, },
	// [1]ID_CA_LABEL_TITLE
	{D_CTRL_LABEL, 0, 16, 11, 52, 386, 31, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a4aef_23223d7, },
	// [2]ID_CA_LIST
	{D_CTRL_LIST, 0, 34, 71, 52, 352, 242, 30, 9, (D_FrameCtrlDescr*)&GUID_c56a4b88_1e46cf5, },
	// [3]ID_CA_LABEL_RETURN_ICON
	{D_CTRL_LABEL, 0, 58, 349, 52, 56, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a4e76_3a91a87, },
	// [4]ID_CA_LABEL_RETURN
	{D_CTRL_LABEL, 0, 120, 357, 52, 63, 21, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a5170_1481e92, },
	// [5]ID_CA_LABEL_OK_ICON
	{D_CTRL_LABEL, 0, 226, 349, 52, 52, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a51c7_2222446, },
	// [6]ID_CA_LABEL_OK
	{D_CTRL_LABEL, 0, 285, 356, 52, 58, 22, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a51f8_0ab6597, },
	// [7]ID_CA_LABEL_LINE
	{D_CTRL_LABEL, 0, 32, 49, 50, 360, 2, 30, -1, (D_FrameCtrlDescr*)&GUID_c79c2b80_07d4823, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_ca_main_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_ca_main_window[8];
D_Frame atv_ca_main_window = {
	run_ctrls_atv_ca_main_window, 
	ctrl_description_of_atv_ca_main_window, 
	atv_ca_main_window_init, 
};

