/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2017-08-24 16:31:36

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-04-06 16:33:25.890

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
#define	ID_IMAGE_LABEL_IMAGE_SETTING	1
#define	ID_IMAGE_GROUP	2
#define	ID_IMAGE_GROUP_1	3
#define	ID_IMAGE_GROUP_2	4
#define	ID_IMAGE_GROUP_3	5
#define	ID_IMAGE_GROUP_4	6
#define	ID_IMAGE_GROUP_5	7
#define	ID_IMAGE_GROUP_6	8
#define	ID_IMAGE_GROUP_7	9
#define	ID_IMAGE_GROUP_8	10
#define	ID_IMAGE_GROUP_9	11
#define	ID_IMAGE_GROUP_10	12
#define	ID_IMAGE_GROUP_11	13
#define	ID_IMAGE_BUTTON_1	14
#define	ID_IMAGE_BUTTON_2	15
#define	ID_IMAGE_BUTTON_3	16
#define	ID_IMAGE_BUTTON_4	17
#define	ID_IMAGE_BUTTON_5	18
#define	ID_IMAGE_BUTTON_6	19
#define	ID_IMAGE_BUTTON_7	20
#define	ID_IMAGE_BUTTON_8	21
#define	ID_IMAGE_BUTTON_9	22
#define	ID_IMAGE_BUTTON_10	23
#define	ID_IMAGE_BUTTON_11	24
#define	ID_IMAGE_LABEL_1	25
#define	ID_IMAGE_LABEL_2	26
#define	ID_IMAGE_LABEL_3	27
#define	ID_IMAGE_LABEL_4	28
#define	ID_IMAGE_LABEL_5	29
#define	ID_IMAGE_LABEL_6	30
#define	ID_IMAGE_LABEL_7	31
#define	ID_IMAGE_LABEL_8	32
#define	ID_IMAGE_LABEL_9	33
#define	ID_IMAGE_LABEL_10	34
#define	ID_IMAGE_LABEL_11	35


//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, atv_IDS_PICTURE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_128645b={-1, -1, atv_IDS_SOUND_BACKLIGHT, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_1282337={-1, -1, atv_IDS_SOUND_BACKLIGHT, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda2ec1_38a531f={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedaa198_08c7e87={-1, atv_IMG_ID_FS_FACTORY_YELLOW, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc0f79_04e5596={-1, -1, atv_IDS_WB_ADJUST, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc0f79_04e7605={-1, -1, atv_IDS_WB_ADJUST, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc0f79_04e7826={-1, -1, atv_IDS_PQ_NONLINEAR, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc0f79_04e33a9={-1, -1, atv_IDS_PQ_NONLINEAR, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc0f79_04e36d8={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc0f79_04e59d4={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bee176ca_34b6e5d={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_IMAGE_LABEL_IMAGE_SETTING"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_IMAGE_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda8768_3c81b4b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_IMAGE_GROUP_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96c42_0ab29={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_IMAGE_GROUP_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96db6_02e4ae1={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_IMAGE_GROUP_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196952={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_IMAGE_GROUP_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e35_1d45af1={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_GROUP}	"ID_IMAGE_GROUP_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e7a_05dbb3={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_GROUP}	"ID_IMAGE_GROUP_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96ed6_1387e87={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_GROUP}	"ID_IMAGE_GROUP_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96f32_37a4d06={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_GROUP}	"ID_IMAGE_GROUP_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96f4e_32c39b3={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_GROUP}	"ID_IMAGE_GROUP_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96fb4_3a96443={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_GROUP}	"ID_IMAGE_GROUP_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed970cf_2bf701f={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_GROUP}	"ID_IMAGE_GROUP_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed97152_1e44509={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_BUTTON}	"ID_IMAGE_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4d01={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_BUTTON}	"ID_IMAGE_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4d02={{&GUID_bedc0f79_04e5596, &GUID_bedc0f79_04e7605, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_BUTTON}	"ID_IMAGE_BUTTON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4d03={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_BUTTON}	"ID_IMAGE_BUTTON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4d04={{&GUID_bedc0f79_04e36d8, &GUID_bedc0f79_04e59d4, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_BUTTON}	"ID_IMAGE_BUTTON_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4d05={{&GUID_bedc0f79_04e36d8, &GUID_bedc0f79_04e59d4, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_BUTTON}	"ID_IMAGE_BUTTON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4d06={{&GUID_bedc0f79_04e36d8, &GUID_bedc0f79_04e59d4, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_BUTTON}	"ID_IMAGE_BUTTON_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4d07={{&GUID_bedc0f79_04e36d8, &GUID_bedc0f79_04e59d4, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_BUTTON}	"ID_IMAGE_BUTTON_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4d08={{&GUID_bedc0f79_04e36d8, &GUID_bedc0f79_04e59d4, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_BUTTON}	"ID_IMAGE_BUTTON_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4d09={{&GUID_bedc0f79_04e36d8, &GUID_bedc0f79_04e59d4, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_BUTTON}	"ID_IMAGE_BUTTON_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4d10={{&GUID_bedc0f79_04e36d8, &GUID_bedc0f79_04e59d4, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_BUTTON}	"ID_IMAGE_BUTTON_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4d11={{&GUID_bedc0f79_04e36d8, &GUID_bedc0f79_04e59d4, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_LABEL}	"ID_IMAGE_LABEL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda2ec1_38a6275={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_LABEL}	"ID_IMAGE_LABEL_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb946e_0ab59e={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_LABEL}	"ID_IMAGE_LABEL_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9517_1865062={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [28]{D_CTRL_LABEL}	"ID_IMAGE_LABEL_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb957c_06df9e={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [29]{D_CTRL_LABEL}	"ID_IMAGE_LABEL_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb95a2_1199c5={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [30]{D_CTRL_LABEL}	"ID_IMAGE_LABEL_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb95f1_2801033={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [31]{D_CTRL_LABEL}	"ID_IMAGE_LABEL_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9662_30d2cb6={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [32]{D_CTRL_LABEL}	"ID_IMAGE_LABEL_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9793_1a5484d={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [33]{D_CTRL_LABEL}	"ID_IMAGE_LABEL_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb97e2_3b92f2f={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [34]{D_CTRL_LABEL}	"ID_IMAGE_LABEL_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda5102_21348ee={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [35]{D_CTRL_LABEL}	"ID_IMAGE_LABEL_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda52ef_27142b7={{&GUID_bee176ca_34b6e5d, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_image_setting_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 485, 660, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_IMAGE_LABEL_IMAGE_SETTING
	{D_CTRL_LABEL, 0, 111, 7, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_IMAGE_GROUP
	{D_CTRL_GROUP, 0, 0, 38, 20, 485, 520, 30, -1, (D_FrameCtrlDescr*)&GUID_beda8768_3c81b4b, },
	// [3]ID_IMAGE_GROUP_1
	{D_CTRL_GROUP, 2, 2, 5, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96c42_0ab29, },
	// [4]ID_IMAGE_GROUP_2
	{D_CTRL_GROUP, 2, 2, 39, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96db6_02e4ae1, },
	// [5]ID_IMAGE_GROUP_3
	{D_CTRL_GROUP, 2, 2, 73, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196952, },
	// [6]ID_IMAGE_GROUP_4
	{D_CTRL_GROUP, 2, 2, 107, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e35_1d45af1, },
	// [7]ID_IMAGE_GROUP_5
	{D_CTRL_GROUP, 2, 2, 141, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e7a_05dbb3, },
	// [8]ID_IMAGE_GROUP_6
	{D_CTRL_GROUP, 2, 2, 175, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96ed6_1387e87, },
	// [9]ID_IMAGE_GROUP_7
	{D_CTRL_GROUP, 2, 2, 209, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96f32_37a4d06, },
	// [10]ID_IMAGE_GROUP_8
	{D_CTRL_GROUP, 2, 2, 243, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96f4e_32c39b3, },
	// [11]ID_IMAGE_GROUP_9
	{D_CTRL_GROUP, 2, 2, 277, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96fb4_3a96443, },
	// [12]ID_IMAGE_GROUP_10
	{D_CTRL_GROUP, 2, 2, 311, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed970cf_2bf701f, },
	// [13]ID_IMAGE_GROUP_11
	{D_CTRL_GROUP, 2, 2, 345, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed97152_1e44509, },
	// [14]ID_IMAGE_BUTTON_1
	{D_CTRL_BUTTON, 3, 21, 2, 0, 180, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_beda356d_29f4d01, },
	// [15]ID_IMAGE_BUTTON_2
	{D_CTRL_BUTTON, 4, 21, 2, 0, 180, 26, 30, 4, (D_FrameCtrlDescr*)&GUID_beda356d_29f4d02, },
	// [16]ID_IMAGE_BUTTON_3
	{D_CTRL_BUTTON, 5, 21, 2, 0, 180, 26, 30, 5, (D_FrameCtrlDescr*)&GUID_beda356d_29f4d03, },
	// [17]ID_IMAGE_BUTTON_4
	{D_CTRL_BUTTON, 6, 21, 2, 0, 180, 26, 30, 6, (D_FrameCtrlDescr*)&GUID_beda356d_29f4d04, },
	// [18]ID_IMAGE_BUTTON_5
	{D_CTRL_BUTTON, 7, 21, 2, 0, 180, 26, 30, 7, (D_FrameCtrlDescr*)&GUID_beda356d_29f4d05, },
	// [19]ID_IMAGE_BUTTON_6
	{D_CTRL_BUTTON, 8, 21, 2, 0, 180, 26, 30, 8, (D_FrameCtrlDescr*)&GUID_beda356d_29f4d06, },
	// [20]ID_IMAGE_BUTTON_7
	{D_CTRL_BUTTON, 9, 21, 2, 0, 180, 26, 30, 9, (D_FrameCtrlDescr*)&GUID_beda356d_29f4d07, },
	// [21]ID_IMAGE_BUTTON_8
	{D_CTRL_BUTTON, 10, 21, 2, 0, 100, 26, 30, 10, (D_FrameCtrlDescr*)&GUID_beda356d_29f4d08, },
	// [22]ID_IMAGE_BUTTON_9
	{D_CTRL_BUTTON, 11, 21, 2, -20, 100, 26, 30, 11, (D_FrameCtrlDescr*)&GUID_beda356d_29f4d09, },
	// [23]ID_IMAGE_BUTTON_10
	{D_CTRL_BUTTON, 12, 21, 2, -20, 100, 26, 30, 12, (D_FrameCtrlDescr*)&GUID_beda356d_29f4d10, },
	// [24]ID_IMAGE_BUTTON_11
	{D_CTRL_BUTTON, 13, 21, 2, -20, 100, 26, 30, 13, (D_FrameCtrlDescr*)&GUID_beda356d_29f4d11, },
	// [25]ID_IMAGE_LABEL_1
	{D_CTRL_LABEL, 3, 309, 2, -20, 164, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb97e2_3b92f2f, },
	// [26]ID_IMAGE_LABEL_2
	{D_CTRL_LABEL, 4, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda5102_21348ee, },
	// [27]ID_IMAGE_LABEL_3
	{D_CTRL_LABEL, 5, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda52ef_27142b7, },
	// [28]ID_IMAGE_LABEL_4
	{D_CTRL_LABEL, 6, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb957c_06df9e, },
	// [29]ID_IMAGE_LABEL_5
	{D_CTRL_LABEL, 7, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb95a2_1199c5, },
	// [30]ID_IMAGE_LABEL_6
	{D_CTRL_LABEL, 8, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb95f1_2801033, },
	// [31]ID_IMAGE_LABEL_7
	{D_CTRL_LABEL, 9, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9662_30d2cb6, },
	// [32]ID_IMAGE_LABEL_8
	{D_CTRL_LABEL, 10, 309, 2, -20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9793_1a5484d, },
	// [33]ID_IMAGE_LABEL_9
	{D_CTRL_LABEL, 11, 309, 2, -20, 164, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb97e2_3b92f2f, },
	// [34]ID_IMAGE_LABEL_10
	{D_CTRL_LABEL, 12, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda5102_21348ee, },
	// [35]ID_IMAGE_LABEL_11
	{D_CTRL_LABEL, 13, 309, 2, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda52ef_27142b7, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	image_setting_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_image_setting_window[36];
D_Frame image_setting_window = {
	run_ctrls_image_setting_window, 
	ctrl_description_of_image_setting_window, 
	image_setting_window_init, 
};

