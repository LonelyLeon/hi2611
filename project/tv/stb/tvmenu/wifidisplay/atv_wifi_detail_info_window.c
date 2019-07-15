/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY_WIN7"
	update/create time:	2017-11-24 19:01:07

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-10-12 11:04:08.678

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
#define	ID_WIFIINFO_LABEL_TITLE	1
#define	ID_WIFIINFO_GROUP	2
#define	ID_WIFIINFO_GROUP_MODE	3
#define	ID_WIFIINFO_GROUP_IPADDR	4
#define	ID_WIFIINFO_GROUP_MASK	5
#define	ID_WIFIINFO_GROUP_GATEWAY	6
#define	ID_WIFIINFO_GROUP_DNS	7
#define	ID_WIFIINFO_GROUP_MAC	8
#define	ID_WIFIINFO_LABEL_LEFT_MODE	9
#define	ID_WIFIINFO_LABEL_RIGHT_MODE	10
#define	ID_WIFIINFO_SELECT_MODE	11
#define	ID_WIFIINFO_INPUT_IPADDR	12
#define	ID_WIFIINFO_INPUT_MASK	13
#define	ID_WIFIINFO_INPUT_GATEWAY	14
#define	ID_WIFIINFO_INPUT_DNS	15
#define	ID_WIFIINFO_LABEL_MAC	16
#define	ID_WIFIINFO_LABEL_WARNING	17

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_attr_win={-1, atv_IMG_ID_FS_Wifi_password_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_attr_title={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_attr_disable={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e26e0={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_NET_MODE, &atv_fmt_left_middle_h20_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e26e1={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_NET_MODE, &atv_fmt_left_middle_h20_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e26e2={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_IPADDRESS, &atv_fmt_left_middle_h20_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e26e3={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_IPADDRESS, &atv_fmt_left_middle_h20_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e26e4={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_IPADDRESS, &atv_fmt_left_middle_h20_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e26e5={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_SUBNET_MASK, &atv_fmt_left_middle_h20_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e26e6={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_SUBNET_MASK, &atv_fmt_left_middle_h20_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e26e7={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_SUBNET_MASK, &atv_fmt_left_middle_h20_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e26e8={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_GATE_WAY, &atv_fmt_left_middle_h20_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e26e9={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_GATE_WAY, &atv_fmt_left_middle_h20_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e2610={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_GATE_WAY, &atv_fmt_left_middle_h20_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e2611={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_DNS, &atv_fmt_left_middle_h20_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e2612={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_DNS, &atv_fmt_left_middle_h20_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e2613={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_DNS, &atv_fmt_left_middle_h20_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cac47575_02e2614={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_MAC, &atv_fmt_left_middle_h20_v00_single_grey, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ctrldescr_win={{&GUID_attr_win, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_WIFIINFO_LABEL_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ctrldescr_title={{&GUID_attr_title, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_WIFIINFO_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cac472ac_61110={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_WIFIINFO_GROUP_MODE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cac472ac_6d340={{&GUID_cac47575_02e26e0, &GUID_cac47575_02e26e1, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_WIFIINFO_GROUP_IPADDR"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cac472ac_6d341={{&GUID_cac47575_02e26e2, &GUID_cac47575_02e26e3, &GUID_cac47575_02e26e4, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_WIFIINFO_GROUP_MASK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cac472ac_6d342={{&GUID_cac47575_02e26e5, &GUID_cac47575_02e26e6, &GUID_cac47575_02e26e7, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_WIFIINFO_GROUP_GATEWAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cac472ac_6d343={{&GUID_cac47575_02e26e8, &GUID_cac47575_02e26e9, &GUID_cac47575_02e2610, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_GROUP}	"ID_WIFIINFO_GROUP_DNS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cac472ac_6d344={{&GUID_cac47575_02e2611, &GUID_cac47575_02e2612, &GUID_cac47575_02e2613, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_GROUP}	"ID_WIFIINFO_GROUP_MAC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cac472ac_6d345={{&GUID_cac47575_02e2614, NULL, &GUID_cac47575_02e2614, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_WIFIINFO_LABEL_LEFT_MODE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cac472ac_34b29={{&GUID_attr_title, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_WIFIINFO_LABEL_RIGHT_MODE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cac472ac_84a27={{&GUID_attr_title, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_SELECT}	"ID_WIFIINFO_SELECT_MODE"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_cac4749c_222620e={{&GUID_attr_title, NULL, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_INPUT}	"ID_WIFIINFO_INPUT_IPADDR"
static char GUID_cac4793b_1486730[16+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_cac4793b_1486810={{&GUID_attr_title, NULL, &GUID_attr_disable, }, 1, 5, 16, GUID_cac4793b_1486730, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_INPUT}	"ID_WIFIINFO_INPUT_MASK"
static char GUID_cac4793b_1486731[16+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_cac4793b_1486811={{&GUID_attr_title, NULL, &GUID_attr_disable, }, 1, 5, 16, GUID_cac4793b_1486731, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_INPUT}	"ID_WIFIINFO_INPUT_GATEWAY"
static char GUID_cac4793b_1486732[16+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_cac4793b_1486812={{&GUID_attr_title, NULL, &GUID_attr_disable, }, 1, 5, 16, GUID_cac4793b_1486732, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_INPUT}	"ID_WIFIINFO_INPUT_DNS"
static char GUID_cac4793b_1486733[16+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_cac4793b_1486813={{&GUID_attr_title, NULL, &GUID_attr_disable, }, 1, 5, 16, GUID_cac4793b_1486733, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_WIFIINFO_LABEL_MAC"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cac49d5b_2adf903={{&GUID_attr_disable, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_WIFIINFO_LABEL_WARNING"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cac49d5b_2903adf={{&GUID_attr_title, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_wifi_detail_info_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 375, 300, 0, 510, 360, 0, -1, (D_FrameCtrlDescr*)&GUID_ctrldescr_win, },
	// [1]ID_WIFIINFO_LABEL_TITLE
	{D_CTRL_LABEL, 0, 30, 16, 20, 450, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_ctrldescr_title, },
	// [2]ID_WIFIINFO_GROUP
	{D_CTRL_GROUP, 0, 10, 55, 20, 490, 299, 30, -1, (D_FrameCtrlDescr*)&GUID_cac472ac_61110, },
	// [3]ID_WIFIINFO_GROUP_MODE
	{D_CTRL_GROUP, 2, 20, 8, 0, 450, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_cac472ac_6d340, },
	// [4]ID_WIFIINFO_GROUP_IPADDR
	{D_CTRL_GROUP, 2, 20, 48, 0, 450, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_cac472ac_6d341, },
	// [5]ID_WIFIINFO_GROUP_MASK
	{D_CTRL_GROUP, 2, 20, 88, 0, 450, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_cac472ac_6d342, },
	// [6]ID_WIFIINFO_GROUP_GATEWAY
	{D_CTRL_GROUP, 2, 20, 128, 0, 450, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_cac472ac_6d343, },
	// [7]ID_WIFIINFO_GROUP_DNS
	{D_CTRL_GROUP, 2, 20, 168, 0, 450, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_cac472ac_6d344, },
	// [8]ID_WIFIINFO_GROUP_MAC
	{D_CTRL_GROUP, 2, 20, 208, 0, 450, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_cac472ac_6d345, },
	// [9]ID_WIFIINFO_LABEL_LEFT_MODE
	{D_CTRL_LABEL, 3, 215, 1, 0, 20, 28, 30, -1, (D_FrameCtrlDescr*)&GUID_cac472ac_34b29, },
	// [10]ID_WIFIINFO_LABEL_RIGHT_MODE
	{D_CTRL_LABEL, 3, 415, 1, 0, 20, 28, 30, -1, (D_FrameCtrlDescr*)&GUID_cac472ac_84a27, },
	// [11]ID_WIFIINFO_SELECT_MODE
	{D_CTRL_SELECT, 3, 241, 0, 0, 168, 30, 30, 3, (D_FrameCtrlDescr*)&GUID_cac4749c_222620e, },
	// [12]ID_WIFIINFO_INPUT_IPADDR
	{D_CTRL_INPUT, 4, 241, 0, 0, 168, 30, 30, 4, (D_FrameCtrlDescr*)&GUID_cac4793b_1486810, },
	// [13]ID_WIFIINFO_INPUT_MASK
	{D_CTRL_INPUT, 5, 241, 0, 0, 168, 30, 30, 5, (D_FrameCtrlDescr*)&GUID_cac4793b_1486811, },
	// [14]ID_WIFIINFO_INPUT_GATEWAY
	{D_CTRL_INPUT, 6, 241, 0, 0, 168, 30, 30, 6, (D_FrameCtrlDescr*)&GUID_cac4793b_1486812, },
	// [15]ID_WIFIINFO_INPUT_DNS
	{D_CTRL_INPUT, 7, 241, 0, 0, 168, 30, 30, 7, (D_FrameCtrlDescr*)&GUID_cac4793b_1486813, },
	// [16]ID_WIFIINFO_LABEL_MAC
	{D_CTRL_LABEL, 8, 241, 0, 0, 168, 30, 30, 8, (D_FrameCtrlDescr*)&GUID_cac49d5b_2adf903, },
	// [17]ID_WIFIINFO_LABEL_WARNING
	{D_CTRL_LABEL, 2, 20, 254, 0, 450, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cac49d5b_2903adf, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_wifi_detail_info_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_wifi_detail_info_window[18];
D_Frame atv_wifi_detail_info_window = {
	run_ctrls_atv_wifi_detail_info_window, 
	ctrl_description_of_atv_wifi_detail_info_window, 
	atv_wifi_detail_info_window_init, 
};

