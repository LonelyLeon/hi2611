/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2019-02-21 17:23:41

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2019-02-21 11:45:23.159

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
#define	ID_WIFISET_GROUP_LIST	1
#define	ID_WIFISET_LABEL_LISTHEAD	2
#define	ID_WIFISET_BUTTON_ON_OFF	3
#define	ID_WIFISET_LABEL_MSG	4
#define	ID_WIFISET_SCROLL_BAR	5
#define	ID_WIFISET_LIST_BUTTON_0	6
#define	ID_WIFISET_LIST_BUTTON_1	7
#define	ID_WIFISET_LIST_BUTTON_2	8
#define	ID_WIFISET_LIST_BUTTON_3	9
#define	ID_WIFISET_LIST_BUTTON_4	10
#define	ID_WIFISET_LIST_BUTTON_5	11
#define	ID_WIFISET_LIST_BUTTON_6	12
#define	ID_WIFISET_LABEL_INFO	13
#define	ID_WIFISET_IMAGE_GREEN	14
#define	ID_WIFISET_LABEL_RESCAN	15
#define	ID_WIFISET_IMAGE_BLUE	16

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c92423e1_09c68f8={-1, atv_IMG_ID_FS_Wifi_password_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c924255f_2de8be={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c927baa6_29f6af3={atv_COLOR_ENUM_101, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c927bcba_2226701={atv_COLOR_ENUM_64, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c927bcba_2226702={atv_COLOR_ENUM_60, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cad09cc5_3ca4671={-1, atv_IMG_ID_Green, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cad09d53_0b82076={-1, -1, atv_IDS_SCAN, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cad09e81_15a4510={-1, atv_IMG_ID_Blue, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cad09f27_0345431={-1, -1, atv_IDS_EPGINFO, &atv_fmt_left_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9240adc_1862cd6={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_WIFISET_GROUP_LIST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c92423e1_09c2cc0={{&GUID_c92423e1_09c68f8, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_WIFISET_LABEL_LISTHEAD"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c924255f_2de34ed={{&GUID_c924255f_2de8be, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_WIFISET_BUTTON_ON_OFF"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c927bcba_2221c2d={{&GUID_c927bcba_2226701, &GUID_c927bcba_2226702, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_WIFISET_LABEL_MSG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c927bd5b_2513cc1={{&GUID_c924255f_2de8be, &GUID_c927bcba_2226702, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_SCROLL}	"ID_WIFISET_SCROLL_BAR"
static PREFIXCONST D_FrameScrollBarDescr POSTCONST GUID_c927baa6_29f5a78={{&GUID_c927baa6_29f6af3, NULL, NULL, }, 1, 100, 10, 1, {-1, -1, -1, atv_IMG_ID_scrool_one, }, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_BUTTON}	"ID_WIFISET_LIST_BUTTON_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cabccfa7_11912d0={{&GUID_c927bcba_2226701, &GUID_c927bcba_2226702, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_BUTTON}	"ID_WIFISET_LIST_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cabccfa7_11912d1={{&GUID_c927bcba_2226701, &GUID_c927bcba_2226702, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_BUTTON}	"ID_WIFISET_LIST_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cabccfa7_11912d2={{&GUID_c927bcba_2226701, &GUID_c927bcba_2226702, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_BUTTON}	"ID_WIFISET_LIST_BUTTON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cabccfa7_11912d3={{&GUID_c927bcba_2226701, &GUID_c927bcba_2226702, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_BUTTON}	"ID_WIFISET_LIST_BUTTON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cabccfa7_11912d4={{&GUID_c927bcba_2226701, &GUID_c927bcba_2226702, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_BUTTON}	"ID_WIFISET_LIST_BUTTON_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cabccfa7_11912d5={{&GUID_c927bcba_2226701, &GUID_c927bcba_2226702, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_BUTTON}	"ID_WIFISET_LIST_BUTTON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cabccfa7_11912d6={{&GUID_c927bcba_2226701, &GUID_c927bcba_2226702, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_IMAGE}	"ID_WIFISET_LABEL_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cad09cc5_3ca5a25={{&GUID_cad09cc5_3ca4671, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_WIFISET_IMAGE_GREEN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cad09d53_0b84fad={{&GUID_cad09d53_0b82076, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_IMAGE}	"ID_WIFISET_LABEL_RESCAN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cad09e81_15a2d04={{&GUID_cad09e81_15a4510, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_WIFISET_IMAGE_BLUE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cad09f27_0346249={{&GUID_cad09f27_0345431, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_wifi_setting_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 960, 540, 0, -1, (D_FrameCtrlDescr*)&GUID_c9240adc_1862cd6, },
	// [1]ID_WIFISET_GROUP_LIST
	{D_CTRL_GROUP, 0, 120, 100, 20, 720, 410, 30, -1, (D_FrameCtrlDescr*)&GUID_c92423e1_09c2cc0, },
	// [2]ID_WIFISET_LABEL_LISTHEAD
	{D_CTRL_LABEL, 1, 22, 13, 0, 120, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_c924255f_2de34ed, },
	// [3]ID_WIFISET_BUTTON_ON_OFF
	{D_CTRL_BUTTON, 1, 160, 13, 0, 125, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_c927bcba_2221c2d, },
	// [4]ID_WIFISET_LABEL_MSG
	{D_CTRL_LABEL, 1, 263, 13, 0, 440, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_c927bd5b_2513cc1, },
	// [5]ID_WIFISET_SCROLL_BAR
	{D_CTRL_SCROLL, 1, 700, 59, 0, 5, 290, 30, -1, (D_FrameCtrlDescr*)&GUID_c927baa6_29f5a78, },
	// [6]ID_WIFISET_LIST_BUTTON_0
	{D_CTRL_BUTTON, 1, 21, 60, 0, 670, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_cabccfa7_11912d0, },
	// [7]ID_WIFISET_LIST_BUTTON_1
	{D_CTRL_BUTTON, 1, 21, 102, 0, 670, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_cabccfa7_11912d1, },
	// [8]ID_WIFISET_LIST_BUTTON_2
	{D_CTRL_BUTTON, 1, 21, 144, 0, 670, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_cabccfa7_11912d2, },
	// [9]ID_WIFISET_LIST_BUTTON_3
	{D_CTRL_BUTTON, 1, 21, 186, 0, 670, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_cabccfa7_11912d3, },
	// [10]ID_WIFISET_LIST_BUTTON_4
	{D_CTRL_BUTTON, 1, 21, 228, 0, 670, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_cabccfa7_11912d4, },
	// [11]ID_WIFISET_LIST_BUTTON_5
	{D_CTRL_BUTTON, 1, 21, 270, 0, 670, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_cabccfa7_11912d5, },
	// [12]ID_WIFISET_LIST_BUTTON_6
	{D_CTRL_BUTTON, 1, 21, 312, 0, 670, 35, 30, -1, (D_FrameCtrlDescr*)&GUID_cabccfa7_11912d6, },
	// [13]ID_WIFISET_LABEL_INFO
	{D_CTRL_IMAGE, 1, 60, 371, 0, 26, 15, 30, -1, (D_FrameCtrlDescr*)&GUID_cad09cc5_3ca5a25, },
	// [14]ID_WIFISET_IMAGE_GREEN
	{D_CTRL_LABEL, 1, 100, 365, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cad09d53_0b84fad, },
	// [15]ID_WIFISET_LABEL_RESCAN
	{D_CTRL_IMAGE, 1, 316, 371, 0, 26, 15, 30, -1, (D_FrameCtrlDescr*)&GUID_cad09e81_15a2d04, },
	// [16]ID_WIFISET_IMAGE_BLUE
	{D_CTRL_LABEL, 1, 353, 365, 0, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cad09f27_0346249, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_wifi_setting_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_wifi_setting_window[17];
D_Frame atv_wifi_setting_window = {
	run_ctrls_atv_wifi_setting_window, 
	ctrl_description_of_atv_wifi_setting_window, 
	atv_wifi_setting_window_init, 
};

