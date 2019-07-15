/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-05-07 15:21:49

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
#define	ID_ZHILIANTV_GROUP	1
#define	ID_ZHILIAN_IMAHE_FLAG	2
#define	ID_ZHILIAN_LABEL_FLAG	3
#define	ID_ZHILIANTV_IMAGE_ICON	4
#define	ID_ZHILIANTV_LABEL_DEVICE	5
#define	ID_ZHILIANTV_LABEL_CONNECT	6
#define	ID_ZHILIANTV_LABEL_STATUS	7
#define	ID_ZHILIANTV_IMAGE_SCREEN_ICON	8
#define	ID_ZHILIANTV_LABEL_HINTINFO_1	9
#define	ID_ZHILIANTV_LABEL_HINTINFO_2	10
#define	ID_ZHILIANTV_LABEL_NOTICE	11
#define	ID_ZHILIANTV_GROUP_INFO	12
#define	ID_ZHILIANTV_LABEL_INSTRUCTION	13
#define	ID_ZHILIANTV_HINT_OK	14
#define	ID_ZHILIANTV_LABEL_OK	15

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c9245388_07d2ea6={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c9245f79_1b52d12={-1, -1, -1, &atv_fmt_left_middle_h00_v00_multi_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c9245f79_52112bd={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c81db92a_3993d6c={-1, atv_IMG_ID_hint_button, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c81dbd57_1095f90={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7c852a2_0995944={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7c8610d_30c7c72={-1, atv_IMG_ID_main_zhilian_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7c885bd_1e26d92={-1, atv_IMG_ID_mini_screen_icon, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c924511c_0ab18be={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_ZHILIANTV_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7c8610d_30c47a={{&GUID_c7c8610d_30c7c72, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_IMAGE}	"ID_ZHILIAN_IMAHE_FLAG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd9250ab_163445a={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_ZHILIAN_LABEL_FLAG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cd9250f8_0ca71f6={{&GUID_c81dbd57_1095f90, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_IMAGE}	"ID_ZHILIANTV_IMAGE_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92452b8_2035af1={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_DEVICE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92455be_399124={{&GUID_c9245388_07d2ea6, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_CONNECT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92454ab_2327e87={{&GUID_c9245f79_52112bd, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_STATUS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c8baee24_32c4ae1={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_IMAGE}	"ID_ZHILIANTV_IMAGE_SCREEN_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7c885bd_1e292f={{&GUID_c7c885bd_1e26d92, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_HINTINFO_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9245f79_1b539b3={{&GUID_c9245f79_1b52d12, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_HINTINFO_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9249c02_2038de={{&GUID_c9245f79_1b52d12, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_NOTICE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92471d4_29f701f={{&GUID_c9245f79_1b52d12, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_GROUP}	"ID_ZHILIANTV_GROUP_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7c852a2_099480f={{&GUID_c7c852a2_0995944, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_INSTRUCTION"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92460d0_29f6443={{&GUID_c9245f79_1b52d12, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_ZHILIANTV_HINT_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c81db92a_3994ae1={{&GUID_c81db92a_3993d6c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_LABEL}	"ID_ZHILIANTV_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c81dbd57_1096952={{&GUID_c81dbd57_1095f90, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_zhilian_tv_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 960, 540, 0, -1, (D_FrameCtrlDescr*)&GUID_c924511c_0ab18be, },
	// [1]ID_ZHILIANTV_GROUP
	{D_CTRL_GROUP, 0, 0, 0, 20, 960, 540, 30, -1, (D_FrameCtrlDescr*)&GUID_c7c8610d_30c47a, },
	// [2]ID_ZHILIAN_IMAHE_FLAG
	{D_CTRL_IMAGE, 1, 39, 35, 0, 56, 44, 30, -1, (D_FrameCtrlDescr*)&GUID_cd9250ab_163445a, },
	// [3]ID_ZHILIAN_LABEL_FLAG
	{D_CTRL_LABEL, 1, 99, 43, 0, 160, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cd9250f8_0ca71f6, },
	// [4]ID_ZHILIANTV_IMAGE_ICON
	{D_CTRL_IMAGE, 1, 80, 132, 0, 416, 150, 30, -1, (D_FrameCtrlDescr*)&GUID_c92452b8_2035af1, },
	// [5]ID_ZHILIANTV_LABEL_DEVICE
	{D_CTRL_LABEL, 1, 30, 338, 0, 521, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c92455be_399124, },
	// [6]ID_ZHILIANTV_LABEL_CONNECT
	{D_CTRL_LABEL, 1, 30, 380, 0, 521, 50, 30, -1, (D_FrameCtrlDescr*)&GUID_c92454ab_2327e87, },
	// [7]ID_ZHILIANTV_LABEL_STATUS
	{D_CTRL_LABEL, 1, 30, 442, 0, 521, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c8baee24_32c4ae1, },
	// [8]ID_ZHILIANTV_IMAGE_SCREEN_ICON
	{D_CTRL_IMAGE, 1, 625, 237, 0, 295, 222, 30, -1, (D_FrameCtrlDescr*)&GUID_c7c885bd_1e292f, },
	// [9]ID_ZHILIANTV_LABEL_HINTINFO_1
	{D_CTRL_LABEL, 1, 595, 64, 20, 355, 55, 30, -1, (D_FrameCtrlDescr*)&GUID_c9245f79_1b539b3, },
	// [10]ID_ZHILIANTV_LABEL_HINTINFO_2
	{D_CTRL_LABEL, 1, 595, 119, 20, 355, 275, 30, -1, (D_FrameCtrlDescr*)&GUID_c9249c02_2038de, },
	// [11]ID_ZHILIANTV_LABEL_NOTICE
	{D_CTRL_LABEL, 1, 595, 395, 20, 355, 55, 30, -1, (D_FrameCtrlDescr*)&GUID_c92471d4_29f701f, },
	// [12]ID_ZHILIANTV_GROUP_INFO
	{D_CTRL_GROUP, 1, 580, 0, 0, 380, 540, 30, -1, (D_FrameCtrlDescr*)&GUID_c7c852a2_099480f, },
	// [13]ID_ZHILIANTV_LABEL_INSTRUCTION
	{D_CTRL_LABEL, 12, 15, 30, 20, 160, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c92460d0_29f6443, },
	// [14]ID_ZHILIANTV_HINT_OK
	{D_CTRL_LABEL, 12, 19, 497, 20, 80, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c81db92a_3994ae1, },
	// [15]ID_ZHILIANTV_LABEL_OK
	{D_CTRL_LABEL, 12, 104, 498, 20, 222, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c81dbd57_1096952, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_zhilian_tv_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_zhilian_tv_window[16];
D_Frame atv_zhilian_tv_window = {
	run_ctrls_atv_zhilian_tv_window, 
	ctrl_description_of_atv_zhilian_tv_window, 
	atv_zhilian_tv_window_init, 
};

