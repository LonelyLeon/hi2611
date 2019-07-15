/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2015-11-16 14:38:45

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-10-02 13:11:52.082

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
#define	ID_FACTORY_LABEL_FACTORY_SETTING	1
#define	ID_FACTORY_GROUP	2
#define	ID_FACTORY_GROUP_0	3
#define	ID_FACTORY_GROUP_1	4
#define	ID_FACTORY_GROUP_2	5
#define	ID_FACTORY_GROUP_3	6
#define	ID_FACTORY_GROUP_4	7
#define	ID_FACTORY_GROUP_5	8
#define	ID_FACTORY_GROUP_6	9
#define	ID_FACTORY_GROUP_7	10
#define	ID_FACTORY_GROUP_9	11
#define	ID_FACTORY_GROUP_10	12
#define	ID_FACTORY_GROUP_11	13
#define	ID_FACTORY_GROUP_12	14
#define	ID_FACTORY_GROUP_13	15
#define	ID_FACTORY_BUTTON_0	16
#define	ID_FACTORY_BUTTON_1	17
#define	ID_FACTORY_BUTTON_2	18
#define	ID_FACTORY_BUTTON_3	19
#define	ID_FACTORY_BUTTON_4	20
#define	ID_FACTORY_BUTTON_5	21
#define	ID_FACTORY_BUTTON_6	22
#define	ID_FACTORY_BUTTON_7	23
#define	ID_FACTORY_BUTTON_9	24
#define	ID_FACTORY_BUTTON_10	25
#define	ID_FACTORY_BUTTON_11	26
#define	ID_FACTORY_BUTTON_12	27
#define	ID_FACTORY_BUTTON_13	28
#define	ID_FACTORY_BUTTON_VERSION	29
#define	ID_FACTORY_BUTTON_TIME	30
#define	ID_FACTORY_BUTTON_SVN	31
#define	ID_FACTORY_BUTTON_BOARD	32
#define	ID_FACTORY_LABEL_0	33
#define	ID_FACTORY_LABEL_1	34
#define	ID_FACTORY_LABEL_5	35
#define	ID_FACTORY_LABEL_10	36
#define	ID_FACTORY_LABEL_11	37
#define	ID_FACTORY_LABEL_12	38
#define	ID_FACTORY_LABEL_13	39
#define	ID_FACTORY_LABEL_VERSION	40
#define	ID_FACTORY_LABLE_TIME	41
#define	ID_FACTORY_LABLE_SVN	42
#define	ID_FACTORY_LABEL_BOARD	43

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, atv_IDS_FACTORY_SETTING, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_128645b={-1, -1, atv_IDS_INIT_TV, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_1282337={-1, -1, atv_IDS_INIT_TV, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda2ec1_38a531f={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda323b_30daae={-1, -1, atv_IDS_GENERAL_SETTING, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda323b_30d5c5c={-1, -1, atv_IDS_GENERAL_SETTING, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda3362_06d77ef={-1, -1, atv_IDS_PICTURE, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda3362_06d18ac={-1, -1, atv_IDS_PICTURE, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda356d_29f4688={-1, -1, atv_IDS_SOUND, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda356d_29f2aac={-1, -1, atv_IDS_SOUND, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda35d1_34b6446={-1, -1, atv_IDS_DEBUG, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda35d1_34b7c2d={-1, -1, atv_IDS_DEBUG, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda4f20_261c81={-1, -1, atv_IDS_SOFTWARE_UPDATE, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda4f20_2613e5={-1, -1, atv_IDS_SOFTWARE_UPDATE, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda4fdd_290750e={-1, -1, atv_IDS_INIT_FAC_CHANNEL, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda4fdd_2903088={-1, -1, atv_IDS_INIT_FAC_CHANNEL, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda522d_1861400={-1, -1, atv_IDS_BURN_MODE, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda522d_186253f={-1, -1, atv_IDS_BURN_MODE, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda5565_1771de4={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_red, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedaa198_08c7e87={-1, atv_IMG_ID_box_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc2755_232aae={-1, -1, atv_IDS_ADC_ADJUST, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc2755_2325d73={-1, -1, atv_IDS_ADC_ADJUST, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc2755_232611c={-1, -1, atv_IDS_EMC_SETTING, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc2755_232e8={-1, -1, atv_IDS_EMC_SETTING, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc2755_232753d={-1, -1, atv_IDS_VERSION, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc2755_2321ec6={-1, -1, atv_IDS_VERSION, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc5116_08c6df1={-1, -1, atv_IDS_BUILD_TIME, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08a2801_1861859={-1, -1, atv_IDS_SCAN_CONFIG, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08a2801_1866a8a={-1, -1, atv_IDS_SCAN_CONFIG, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c38cc7e9_1f44521={-1, -1, atv_IDS_SIGNAL_DETECT, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c38cc7e9_1f4db5={-1, -1, atv_IDS_SIGNAL_DETECT, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4655e45_0ea41bb={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c465897d_0005af1={-1, -1, atv_IDS_SVN_VERSION, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c465897d_00041bb={-1, -1, atv_IDS_BOARD_VER, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4728180_2ee5f32={-1, -1, atv_IDS_FACTORY_RESET, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4728180_2ee3bf6={-1, -1, atv_IDS_FACTORY_RESET, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedca55_23272ae={-1, -1, atv_IDS_ADC_ADJUST, &atv_fmt_left_middle_h00_v00_single_black, };
//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_FACTORY_LABEL_FACTORY_SETTING"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_FACTORY_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda8768_3c81b4b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_FACTORY_GROUP_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96c42_0ab29={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_FACTORY_GROUP_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4727f8d_1e45878={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_FACTORY_GROUP_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96db6_02e4ae1={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_FACTORY_GROUP_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196952={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_GROUP}	"ID_FACTORY_GROUP_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e35_1d45af1={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_GROUP}	"ID_FACTORY_GROUP_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e7a_05dbb3={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_GROUP}	"ID_FACTORY_GROUP_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96ed6_1387e87={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_GROUP}	"ID_FACTORY_GROUP_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96f32_37a4d06={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_GROUP}	"ID_FACTORY_GROUP_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96fb4_3a96443={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_GROUP}	"ID_FACTORY_GROUP_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed970cf_2bf701f={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_GROUP}	"ID_FACTORY_GROUP_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed97152_1e44509={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_GROUP}	"ID_FACTORY_GROUP_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c08a2686_2af460b={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_GROUP}	"ID_FACTORY_GROUP_13"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c38cc781_2131dc5={{NULL, &GUID_bedaa198_08c7e87, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4728180_2ee1a49={{&GUID_c4728180_2ee5f32, &GUID_c4728180_2ee3bf6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed9bb91_128666e={{&GUID_bed9bb91_128645b, &GUID_bed9bb91_1282337, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda323b_30d1d08={{&GUID_beda323b_30daae, &GUID_beda323b_30d5c5c, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda3362_06d954={{&GUID_beda3362_06d77ef, &GUID_beda3362_06d18ac, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4df5={{&GUID_beda356d_29f4688, &GUID_beda356d_29f2aac, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda35d1_34b101a={{&GUID_beda35d1_34b6446, &GUID_beda35d1_34b7c2d, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4de4_07d2268={{&GUID_bedc2755_232aae, &GUID_bedc2755_2325d73, &GUID_bedca55_23272ae, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4e3e_2225585={{&GUID_bedc2755_232611c, &GUID_bedc2755_232e8, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4f20_2611fa5={{&GUID_beda4f20_261c81, &GUID_beda4f20_2613e5, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda4fdd_290763c={{&GUID_beda4fdd_290750e, &GUID_beda4fdd_2903088, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda522d_186323={{&GUID_beda522d_1861400, &GUID_beda522d_186253f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c08a2801_1866733={{&GUID_c08a2801_1861859, &GUID_c08a2801_1866a8a, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [28]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_13"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c38cc7e9_1f4550e={{&GUID_c38cc7e9_1f44521, &GUID_c38cc7e9_1f4db5, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [29]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_VERSION"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda5506_0ab50f4={{&GUID_bedc2755_232753d, &GUID_bedc2755_2321ec6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [30]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_TIME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4653f58_2bf68f8={{&GUID_bedc5116_08c6df1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [31]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_SVN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c465407c_1774e78={{&GUID_c465897d_0005af1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [32]{D_CTRL_BUTTON}	"ID_FACTORY_BUTTON_BOARD"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda586e_30d777e={{&GUID_c465897d_00041bb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [33]{D_CTRL_LABEL}	"ID_FACTORY_LABEL_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4728258_1a5797d={{&GUID_c4655e45_0ea41bb, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [34]{D_CTRL_LABEL}	"ID_FACTORY_LABEL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda2ec1_38a6275={{&GUID_beda2ec1_38a531f, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [35]{D_CTRL_LABEL}	"ID_FACTORY_LABEL_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda5102_53d13f4={{&GUID_c4655e45_0ea41bb, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [36]{D_CTRL_LABEL}	"ID_FACTORY_LABEL_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda5102_21348ee={{&GUID_c4655e45_0ea41bb, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [37]{D_CTRL_LABEL}	"ID_FACTORY_LABEL_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda52ef_27142b7={{&GUID_c4655e45_0ea41bb, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [38]{D_CTRL_LABEL}	"ID_FACTORY_LABEL_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c08a2925_1f45c2c={{&GUID_c4655e45_0ea41bb, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [39]{D_CTRL_LABEL}	"ID_FACTORY_LABEL_13"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c38cc851_31c1b3={{&GUID_c4655e45_0ea41bb, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [40]{D_CTRL_LABEL}	"ID_FACTORY_LABEL_VERSION"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda5565_17727bd={{&GUID_beda5565_1771de4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [41]{D_CTRL_LABEL}	"ID_FACTORY_LABLE_TIME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c464731a_23271ce={{&GUID_beda5565_1771de4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [42]{D_CTRL_LABEL}	"ID_FACTORY_LABLE_SVN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c465415e_07d4ba6={{&GUID_beda5565_1771de4, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [43]{D_CTRL_LABEL}	"ID_FACTORY_LABEL_BOARD"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c06374c7_07df3e={{&GUID_c4655e45_0ea41bb, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_factory_setting_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 485, 660, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_FACTORY_LABEL_FACTORY_SETTING
	{D_CTRL_LABEL, 0, 116, 8, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_FACTORY_GROUP
	{D_CTRL_GROUP, 0, 0, 39, 20, 485, 621, 30, -1, (D_FrameCtrlDescr*)&GUID_beda8768_3c81b4b, },
	// [3]ID_FACTORY_GROUP_0
	{D_CTRL_GROUP, 2, 2, 5, 0, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96c42_0ab29, },
	// [4]ID_FACTORY_GROUP_1
	{D_CTRL_GROUP, 2, 2, 39, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4727f8d_1e45878, },
	// [5]ID_FACTORY_GROUP_2
	{D_CTRL_GROUP, 2, 2, 73, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96db6_02e4ae1, },
	// [6]ID_FACTORY_GROUP_3
	{D_CTRL_GROUP, 2, 2, 107, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196952, },
	// [7]ID_FACTORY_GROUP_4
	{D_CTRL_GROUP, 2, 2, 141, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e35_1d45af1, },
	// [8]ID_FACTORY_GROUP_5
	{D_CTRL_GROUP, 2, 2, 175, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e7a_05dbb3, },
	// [9]ID_FACTORY_GROUP_6
	{D_CTRL_GROUP, 2, 2, 209, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96ed6_1387e87, },
	// [10]ID_FACTORY_GROUP_7
	{D_CTRL_GROUP, 2, 2, 243, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96f32_37a4d06, },
	// [11]ID_FACTORY_GROUP_9
	{D_CTRL_GROUP, 2, 2, 278, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96fb4_3a96443, },
	// [12]ID_FACTORY_GROUP_10
	{D_CTRL_GROUP, 2, 2, 312, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed970cf_2bf701f, },
	// [13]ID_FACTORY_GROUP_11
	{D_CTRL_GROUP, 2, 2, 346, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed97152_1e44509, },
	// [14]ID_FACTORY_GROUP_12
	{D_CTRL_GROUP, 2, 2, 380, 0, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c08a2686_2af460b, },
	// [15]ID_FACTORY_GROUP_13
	{D_CTRL_GROUP, 2, 2, 414, 0, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c38cc781_2131dc5, },
	// [16]ID_FACTORY_BUTTON_0
	{D_CTRL_BUTTON, 3, 21, 2, -34, 150, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_c4728180_2ee1a49, },
	// [17]ID_FACTORY_BUTTON_1
	{D_CTRL_BUTTON, 4, 21, 2, 34, 125, 26, 30, 4, (D_FrameCtrlDescr*)&GUID_bed9bb91_128666e, },
	// [18]ID_FACTORY_BUTTON_2
	{D_CTRL_BUTTON, 5, 21, 2, 0, 238, 26, 30, 5, (D_FrameCtrlDescr*)&GUID_beda323b_30d1d08, },
	// [19]ID_FACTORY_BUTTON_3
	{D_CTRL_BUTTON, 6, 21, 2, 0, 100, 26, 30, 6, (D_FrameCtrlDescr*)&GUID_beda3362_06d954, },
	// [20]ID_FACTORY_BUTTON_4
	{D_CTRL_BUTTON, 7, 21, 2, 0, 100, 26, 30, 7, (D_FrameCtrlDescr*)&GUID_beda356d_29f4df5, },
	// [21]ID_FACTORY_BUTTON_5
	{D_CTRL_BUTTON, 8, 21, 2, 0, 100, 26, 30, 8, (D_FrameCtrlDescr*)&GUID_beda35d1_34b101a, },
	// [22]ID_FACTORY_BUTTON_6
	{D_CTRL_BUTTON, 9, 21, 2, 0, 239, 26, 30, 9, (D_FrameCtrlDescr*)&GUID_beda4de4_07d2268, },
	// [23]ID_FACTORY_BUTTON_7
	{D_CTRL_BUTTON, 10, 21, 2, 0, 245, 26, 30, 10, (D_FrameCtrlDescr*)&GUID_beda4e3e_2225585, },
	// [24]ID_FACTORY_BUTTON_9
	{D_CTRL_BUTTON, 11, 21, 2, 0, 260, 26, 30, 11, (D_FrameCtrlDescr*)&GUID_beda4f20_2611fa5, },
	// [25]ID_FACTORY_BUTTON_10
	{D_CTRL_BUTTON, 12, 21, 2, 0, 223, 26, 30, 12, (D_FrameCtrlDescr*)&GUID_beda4fdd_290763c, },
	// [26]ID_FACTORY_BUTTON_11
	{D_CTRL_BUTTON, 13, 21, 2, 0, 189, 26, 30, 13, (D_FrameCtrlDescr*)&GUID_beda522d_186323, },
	// [27]ID_FACTORY_BUTTON_12
	{D_CTRL_BUTTON, 14, 21, 2, 0, 189, 26, 30, 14, (D_FrameCtrlDescr*)&GUID_c08a2801_1866733, },
	// [28]ID_FACTORY_BUTTON_13
	{D_CTRL_BUTTON, 15, 21, 2, 0, 189, 26, 30, 15, (D_FrameCtrlDescr*)&GUID_c38cc7e9_1f4550e, },
	// [29]ID_FACTORY_BUTTON_VERSION
	{D_CTRL_BUTTON, 0, 23, 521, 40, 130, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda5506_0ab50f4, },
	// [30]ID_FACTORY_BUTTON_TIME
	{D_CTRL_BUTTON, 0, 23, 555, 20, 130, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4653f58_2bf68f8, },
	// [31]ID_FACTORY_BUTTON_SVN
	{D_CTRL_BUTTON, 0, 23, 590, 21, 130, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c465407c_1774e78, },
	// [32]ID_FACTORY_BUTTON_BOARD
	{D_CTRL_BUTTON, 0, 23, 625, 40, 130, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda586e_30d777e, },
	// [33]ID_FACTORY_LABEL_0
	{D_CTRL_LABEL, 3, 309, 1, -34, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4728258_1a5797d, },
	// [34]ID_FACTORY_LABEL_1
	{D_CTRL_LABEL, 4, 309, 1, 34, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda2ec1_38a6275, },
	// [35]ID_FACTORY_LABEL_5
	{D_CTRL_LABEL, 8, 309, 1, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda5102_53d13f4, },
	// [36]ID_FACTORY_LABEL_10
	{D_CTRL_LABEL, 12, 309, 1, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda5102_21348ee, },
	// [37]ID_FACTORY_LABEL_11
	{D_CTRL_LABEL, 13, 309, 1, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda52ef_27142b7, },
	// [38]ID_FACTORY_LABEL_12
	{D_CTRL_LABEL, 14, 309, 1, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c08a2925_1f45c2c, },
	// [39]ID_FACTORY_LABEL_13
	{D_CTRL_LABEL, 15, 309, 1, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c38cc851_31c1b3, },
	// [40]ID_FACTORY_LABEL_VERSION
	{D_CTRL_LABEL, 0, 168, 521, 40, 313, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda5565_17727bd, },
	// [41]ID_FACTORY_LABLE_TIME
	{D_CTRL_LABEL, 0, 168, 555, 20, 313, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c464731a_23271ce, },
	// [42]ID_FACTORY_LABLE_SVN
	{D_CTRL_LABEL, 0, 168, 590, 21, 313, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c465415e_07d4ba6, },
	// [43]ID_FACTORY_LABEL_BOARD
	{D_CTRL_LABEL, 0, 168, 625, 20, 313, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c06374c7_07df3e, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	factory_setting_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_factory_setting_window[44];
D_Frame factory_setting_window = {
	run_ctrls_factory_setting_window, 
	ctrl_description_of_factory_setting_window, 
	factory_setting_window_init, 
};

