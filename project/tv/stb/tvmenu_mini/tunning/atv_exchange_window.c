/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2017-07-27 13:11:22

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
#define	ID_EXCHANGE_LABLE_TITLE	1
#define	ID_EXCHANGE_GROUP_FUN	2
#define	ID_EXCHANGE_BUTTON_FUN1	3
#define	ID_EXCHANGE_LABLE_CUR	4
#define	ID_EXCHANGE_LABLE_LEFT1	5
#define	ID_EXCHANGE_LABLE_CUR_TEXT	6
#define	ID_EXCHANGE_LABLE_RIGHT1	7
#define	ID_EXCHANGE_BUTTON_FUN2	8
#define	ID_EXCHANGE_LABLE_EXCHANGE	9
#define	ID_EXCHANGE_LABLE_LEFT2	10
#define	ID_EXCHANGE_LABLE_EXCHANGE_TEXT	11
#define	ID_EXCHANGE_LABLE_RIGHT2	12
#define	ID_EXCHANGE_BUTTON_FUN3	13
#define	ID_EXCHANGE_LABLE_OK	14
#define	ID_EXCHANGE_LABLE_OK1	15

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40db9f6_05d2fad={-1, atv_IMG_ID_FS_WHITE_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a176ab_2bf2b51={-1, -1, atv_IDS_EXCHANGE, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a23554_0cb7867={-1, atv_IMG_ID_sub_menu_direc_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a23554_0cb797b={-1, atv_IMG_ID_sub_menu_direc_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b5645c_08c29={-1, -1, atv_IDS_CURRENT_CHANNEL, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b5676a_30d385e={-1, atv_IMG_ID_FS_BUTTON_GRAY, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b5676a_30d6e88={-1, atv_IMG_ID_FS_OK_BUTTON_FOCSE, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bc56f5_00f29={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bc56f5_00f6784={-1, -1, atv_IDS_TO_CHANNEL, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bc56f5_00f5f90={-1, -1, atv_IDS_EXCHANGE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bc56f5_00f1649={-1, -1, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{&GUID_c40db9f6_05d2fad, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_EXCHANGE_LABLE_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a176ab_2bf43a5={{&GUID_c4a176ab_2bf2b51, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_EXCHANGE_GROUP_FUN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b58930_0da58b9={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_EXCHANGE_BUTTON_FUN1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b5676a_30d6526={{&GUID_c4b5676a_30d385e, &GUID_c4b5676a_30d6e88, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_EXCHANGE_LABLE_CUR"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1bab7_242c0b={{&GUID_c4b5645c_08c29, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_EXCHANGE_LABLE_LEFT1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1bdc7_03e841={{&GUID_c4a23554_0cb7867, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_EXCHANGE_LABLE_CUR_TEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b5b5a4_2615722={{&GUID_c4bc56f5_00f29, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_EXCHANGE_LABLE_RIGHT1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1c0fd_2ce2794={{&GUID_c4a23554_0cb797b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_BUTTON}	"ID_EXCHANGE_BUTTON_FUN2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b56af0_1861b60={{&GUID_c4b5676a_30d385e, &GUID_c4b5676a_30d6e88, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_EXCHANGE_LABLE_EXCHANGE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a1c293_1672e99={{&GUID_c4bc56f5_00f6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_EXCHANGE_LABLE_LEFT2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a210e8_1a51f60={{&GUID_c4a23554_0cb7867, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_EXCHANGE_LABLE_EXCHANGE_TEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b60bdd_39958da={{&GUID_c4bc56f5_00f29, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_EXCHANGE_LABLE_RIGHT2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a222f6_261627e={{&GUID_c4a23554_0cb797b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_BUTTON}	"ID_EXCHANGE_BUTTON_FUN3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b56c39_213337e={{&GUID_c4b5676a_30d385e, &GUID_c4b5676a_30d6e88, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_EXCHANGE_LABLE_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a2241a_1f45ea4={{&GUID_c4bc56f5_00f5f90, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_LABEL}	"ID_EXCHANGE_LABLE_OK1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b57159_02e3956={{&GUID_c4bc56f5_00f1649, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_exchange_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 160, 168, 0, 400, 240, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_EXCHANGE_LABLE_TITLE
	{D_CTRL_LABEL, 0, 123, 8, 20, 143, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a176ab_2bf43a5, },
	// [2]ID_EXCHANGE_GROUP_FUN
	{D_CTRL_GROUP, 0, 0, 89, 20, 398, 121, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b58930_0da58b9, },
	// [3]ID_EXCHANGE_BUTTON_FUN1
	{D_CTRL_BUTTON, 2, 10, 11, 0, 382, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b5676a_30d6526, },
	// [4]ID_EXCHANGE_LABLE_CUR
	{D_CTRL_LABEL, 3, 17, 0, 0, 95, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1bab7_242c0b, },
	// [5]ID_EXCHANGE_LABLE_LEFT1
	{D_CTRL_LABEL, 3, 200, 4, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1bdc7_03e841, },
	// [6]ID_EXCHANGE_LABLE_CUR_TEXT
	{D_CTRL_LABEL, 3, 236, 0, 0, 99, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b5b5a4_2615722, },
	// [7]ID_EXCHANGE_LABLE_RIGHT1
	{D_CTRL_LABEL, 3, 360, 4, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1c0fd_2ce2794, },
	// [8]ID_EXCHANGE_BUTTON_FUN2
	{D_CTRL_BUTTON, 2, 10, 48, 0, 382, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b56af0_1861b60, },
	// [9]ID_EXCHANGE_LABLE_EXCHANGE
	{D_CTRL_LABEL, 8, 17, 0, 0, 95, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a1c293_1672e99, },
	// [10]ID_EXCHANGE_LABLE_LEFT2
	{D_CTRL_LABEL, 8, 200, 4, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a210e8_1a51f60, },
	// [11]ID_EXCHANGE_LABLE_EXCHANGE_TEXT
	{D_CTRL_LABEL, 8, 236, 0, 0, 99, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b60bdd_39958da, },
	// [12]ID_EXCHANGE_LABLE_RIGHT2
	{D_CTRL_LABEL, 8, 360, 4, 0, 10, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a222f6_261627e, },
	// [13]ID_EXCHANGE_BUTTON_FUN3
	{D_CTRL_BUTTON, 2, 10, 85, 0, 382, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b56c39_213337e, },
	// [14]ID_EXCHANGE_LABLE_OK
	{D_CTRL_LABEL, 13, 17, 0, 4, 95, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a2241a_1f45ea4, },
	// [15]ID_EXCHANGE_LABLE_OK1
	{D_CTRL_LABEL, 13, 246, 0, 0, 76, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b57159_02e3956, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_exchange_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_exchange_window[16];
D_Frame atv_exchange_window = {
	run_ctrls_atv_exchange_window, 
	ctrl_description_of_atv_exchange_window, 
	atv_exchange_window_init, 
};

