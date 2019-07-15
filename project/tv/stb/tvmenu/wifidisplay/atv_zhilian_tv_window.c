/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2019-01-05 16:53:28

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2018-06-01 11:01:56.252

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
#define	ID_ZHILIANTV_GROUP	1
#define	ID_ZHILIANTV_GROUP_INFO	2
#define	ID_ZHILIANTV_IMAGE_ICON	3
#define	ID_ZHILIANTV_LABEL_CONNECT	4
#define	ID_ZHILIANTV_LABEL_STATUS	5
#define	ID_ZHILIANTV_LABEL_DEVICE	6
#define	ID_ZHILIANTV_LABEL_INSTRUCTION	7
#define	ID_ZHILIANTV_LABEL_HINTINFO_1	8
#define	ID_ZHILIANTV_LABEL_HINTINFO_2	9
#define	ID_ZHILIANTV_LABEL_NOTICE	10
#define	ID_ZHILIANTV_IMAGE_RED	11
#define	ID_ZHILIANTV_LABEL_SET_WIFI	12
#define	ID_ZHILIANTV_HINT_OK	13
#define	ID_ZHILIANTV_LABEL_OK	14
#define	ID_ZHILIAN_IMAHE_FLAG	15
#define	ID_ZHILIAN_LABEL_FLAG	16

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd862b21_3bc4823={-1, atv_IMG_ID_main_zhilian_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c9245388_07d2ea6={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c9245f79_1b52d12={-1, -1, -1, &atv_fmt_left_middle_h00_v00_multi_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c9245f79_52112bd={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c80f36b0_03e3667={-1, atv_IMG_ID_Red, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c80f3850_09c5067={-1, -1, atv_IDS_WIFI_SETTING, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c81db92a_3993d6c={-1, atv_IMG_ID_hint_button, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c81dbd57_1095f90={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cd9bfc5e_28d45e1={atv_COLOR_ENUM_89, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c924511c_0ab18be={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_ZHILIANTV_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9b18241c_0a51be={{&GUID_cd862b21_3bc4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_IMAGE}	"ID_ZHILIANTV_GROUP_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c924517d_02e6952={{&GUID_cd9bfc5e_28d45e1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_IMAGE}	"ID_ZHILIANTV_IMAGE_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92452b8_2035af1={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_CONNECT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92454ab_2327e87={{&GUID_c9245f79_52112bd, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_STATUS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c8baee24_32c4ae1={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_DEVICE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92455be_399124={{&GUID_c9245388_07d2ea6, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_INSTRUCTION"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92460d0_29f6443={{&GUID_c9245f79_1b52d12, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_HINTINFO_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9245f79_1b539b3={{&GUID_c9245f79_1b52d12, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_HINTINFO_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9249c02_2038de={{&GUID_c9245f79_1b52d12, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_NOTICE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92471d4_29f701f={{&GUID_c9245f79_1b52d12, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_IMAGE}	"ID_ZHILIANTV_IMAGE_RED"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c80f36b0_03e5498={{&GUID_c80f36b0_03e3667, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_SET_WIFI"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c80f3850_09c50e={{&GUID_c80f3850_09c5067, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_ZHILIANTV_HINT_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c81db92a_3994ae1={{&GUID_c81db92a_3993d6c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c81dbd57_1096952={{&GUID_c81dbd57_1095f90, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_IMAGE}	"ID_ZHILIAN_IMAHE_FLAG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd9250ab_163445a={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_ZHILIAN_LABEL_FLAG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd9250f8_0ca71f6={{&GUID_c81dbd57_1095f90, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_zhilian_tv_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 1280, 720, 0, -1, (D_FrameCtrlDescr*)&GUID_c924511c_0ab18be, },
	// [1]ID_ZHILIANTV_GROUP
	{D_CTRL_GROUP, 0, 0, 0, 0, 1280, 720, 0, -1, (D_FrameCtrlDescr*)&GUID_c9b18241c_0a51be, },
	// [2]ID_ZHILIANTV_GROUP_INFO
	{D_CTRL_IMAGE, 1, 790, 0, 20, 490, 720, 30, -1, (D_FrameCtrlDescr*)&GUID_c924517d_02e6952, },
	// [3]ID_ZHILIANTV_IMAGE_ICON
	{D_CTRL_IMAGE, 1, 157, 155, 20, 567, 200, 30, -1, (D_FrameCtrlDescr*)&GUID_c92452b8_2035af1, },
	// [4]ID_ZHILIANTV_LABEL_CONNECT
	{D_CTRL_LABEL, 1, 95, 534, 20, 600, 50, 30, -1, (D_FrameCtrlDescr*)&GUID_c92454ab_2327e87, },
	// [5]ID_ZHILIANTV_LABEL_STATUS
	{D_CTRL_LABEL, 1, 95, 596, 20, 600, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c8baee24_32c4ae1, },
	// [6]ID_ZHILIANTV_LABEL_DEVICE
	{D_CTRL_LABEL, 1, 95, 492, 20, 600, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c92455be_399124, },
	// [7]ID_ZHILIANTV_LABEL_INSTRUCTION
	{D_CTRL_LABEL, 2, 15, 63, 20, 160, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c92460d0_29f6443, },
	// [8]ID_ZHILIANTV_LABEL_HINTINFO_1
	{D_CTRL_LABEL, 2, 15, 101, 20, 470, 60, 30, -1, (D_FrameCtrlDescr*)&GUID_c9245f79_1b539b3, },
	// [9]ID_ZHILIANTV_LABEL_HINTINFO_2
	{D_CTRL_LABEL, 2, 15, 161, 20, 470, 274, 30, -1, (D_FrameCtrlDescr*)&GUID_c9249c02_2038de, },
	// [10]ID_ZHILIANTV_LABEL_NOTICE
	{D_CTRL_LABEL, 2, 15, 507, 20, 470, 99, 30, -1, (D_FrameCtrlDescr*)&GUID_c92471d4_29f701f, },
	// [11]ID_ZHILIANTV_IMAGE_RED
	{D_CTRL_IMAGE, 2, 26, 628, 50, 26, 16, 30, -1, (D_FrameCtrlDescr*)&GUID_c80f36b0_03e5498, },
	// [12]ID_ZHILIANTV_LABEL_SET_WIFI
	{D_CTRL_LABEL, 2, 64, 614, 50, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c80f3850_09c50e, },
	// [13]ID_ZHILIANTV_HINT_OK
	{D_CTRL_LABEL, 2, 18, 661, 20, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c81db92a_3994ae1, },
	// [14]ID_ZHILIANTV_LABEL_OK
	{D_CTRL_LABEL, 2, 124, 663, 20, 300, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c81dbd57_1096952, },
	// [15]ID_ZHILIAN_IMAHE_FLAG
	{D_CTRL_IMAGE, 1, 50, 54, 20, 56, 44, 30, -1, (D_FrameCtrlDescr*)&GUID_cd9250ab_163445a, },
	// [16]ID_ZHILIAN_LABEL_FLAG
	{D_CTRL_LABEL, 1, 110, 62, 20, 160, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd9250f8_0ca71f6, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_zhilian_tv_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_zhilian_tv_window[17];
D_Frame atv_zhilian_tv_window = {
	run_ctrls_atv_zhilian_tv_window, 
	ctrl_description_of_atv_zhilian_tv_window, 
	atv_zhilian_tv_window_init, 
};

