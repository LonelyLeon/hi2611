/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-05-30 17:07:33

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2019-05-14 14:18:09.300

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
#define	ID_PANEL_LABEL_PANEL_SETTING	1
#define	ID_GENERAL_GROUP	2
#define	ID_GENERAL_GROUP_1	3
#define	ID_GENERAL_GROUP_2	4
#define	ID_GENERAL_GROUP_3	5
#define	ID_GENERAL_GROUP_4	6
#define	ID_GENERAL_GROUP_5	7
#define	ID_GENERAL_GROUP_6	8
#define	ID_GENERAL_GROUP_7	9
#define	ID_GENERAL_GROUP_8	10
#define	ID_GENERAL_GROUP_9	11
#define	ID_GENERAL_BUTTON_1	12
#define	ID_GENERAL_BUTTON_2	13
#define	ID_GENERAL_BUTTON_3	14
#define	ID_GENERAL_BUTTON_4	15
#define	ID_GENERAL_BUTTON_5	16
#define	ID_GENERAL_BUTTON_6	17
#define	ID_GENERAL_BUTTON_7	18
#define	ID_GENERAL_BUTTON_8	19
#define	ID_GENERAL_BUTTON_9	20
#define	ID_GENERAL_LABEL_1	21
#define	ID_GENERAL_LABEL_2	22
#define	ID_GENERAL_LABEL_3	23
#define	ID_GENERAL_LABEL_4	24
#define	ID_GENERAL_LABEL_5	25
#define	ID_GENERAL_LABEL_6	26
#define	ID_GENERAL_LABEL_7	27
#define	ID_GENERAL_LABEL_8	28
#define	ID_GENERAL_LABEL_9	29

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc0f79_04e7826={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bedc0f79_04e33a9={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c14e5676_06d6ccf={-1, atv_IMG_ID_box_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_ca26989b_3b243eb={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_PANEL_LABEL_PANEL_SETTING"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_GENERAL_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda8768_3c81b4b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_GENERAL_GROUP_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196952={{NULL, &GUID_c14e5676_06d6ccf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_GROUP}	"ID_GENERAL_GROUP_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e35_1d45af1={{NULL, &GUID_c14e5676_06d6ccf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_GENERAL_GROUP_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196953={{NULL, &GUID_c14e5676_06d6ccf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_GROUP}	"ID_GENERAL_GROUP_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196954={{NULL, &GUID_c14e5676_06d6ccf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_GROUP}	"ID_GENERAL_GROUP_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196955={{NULL, &GUID_c14e5676_06d6ccf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_GROUP}	"ID_GENERAL_GROUP_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196956={{NULL, &GUID_c14e5676_06d6ccf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_GROUP}	"ID_GENERAL_GROUP_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196957={{NULL, &GUID_c14e5676_06d6ccf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_GROUP}	"ID_GENERAL_GROUP_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ca268056_02a75b9={{NULL, &GUID_c14e5676_06d6ccf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_GROUP}	"ID_GENERAL_GROUP_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96e18_1196958={{NULL, &GUID_c14e5676_06d6ccf, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_BUTTON}	"ID_GENERAL_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda3362_06d954={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, &GUID_ca26989b_3b243eb, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_BUTTON}	"ID_GENERAL_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda356d_29f4df5={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, &GUID_ca26989b_3b243eb, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_BUTTON}	"ID_GENERAL_BUTTON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda3362_06d955={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_BUTTON}	"ID_GENERAL_BUTTON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda3362_06d956={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, &GUID_ca26989b_3b243eb, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_BUTTON}	"ID_GENERAL_BUTTON_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda3362_06d957={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_BUTTON}	"ID_GENERAL_BUTTON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda3362_06d958={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_BUTTON}	"ID_GENERAL_BUTTON_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda3362_06d959={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_BUTTON}	"ID_GENERAL_BUTTON_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ca26812b_2256049={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_BUTTON}	"ID_GENERAL_BUTTON_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda3362_06d960={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9517_1865062={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, &GUID_ca26989b_3b243eb, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb957c_06df9e={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, &GUID_ca26989b_3b243eb, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9517_1865063={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9517_1865064={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, &GUID_ca26989b_3b243eb, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9517_1865065={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9517_1865066={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9517_1865067={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [28]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_8"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ca2681dc_1e82935={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [29]{D_CTRL_LABEL}	"ID_GENERAL_LABEL_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb9517_1865068={{&GUID_bedc0f79_04e7826, &GUID_bedc0f79_04e33a9, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_panel_setting_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 485, 660, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_PANEL_LABEL_PANEL_SETTING
	{D_CTRL_LABEL, 0, 111, 7, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_GENERAL_GROUP
	{D_CTRL_GROUP, 0, 0, 37, 20, 485, 621, 30, -1, (D_FrameCtrlDescr*)&GUID_beda8768_3c81b4b, },
	// [3]ID_GENERAL_GROUP_1
	{D_CTRL_GROUP, 2, 2, 6, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196952, },
	// [4]ID_GENERAL_GROUP_2
	{D_CTRL_GROUP, 2, 2, 40, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e35_1d45af1, },
	// [5]ID_GENERAL_GROUP_3
	{D_CTRL_GROUP, 2, 2, 74, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196953, },
	// [6]ID_GENERAL_GROUP_4
	{D_CTRL_GROUP, 2, 2, 108, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196954, },
	// [7]ID_GENERAL_GROUP_5
	{D_CTRL_GROUP, 2, 2, 142, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196955, },
	// [8]ID_GENERAL_GROUP_6
	{D_CTRL_GROUP, 2, 2, 176, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196956, },
	// [9]ID_GENERAL_GROUP_7
	{D_CTRL_GROUP, 2, 2, 210, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196957, },
	// [10]ID_GENERAL_GROUP_8
	{D_CTRL_GROUP, 2, 1, 244, 0, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_ca268056_02a75b9, },
	// [11]ID_GENERAL_GROUP_9
	{D_CTRL_GROUP, 2, 2, 278, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96e18_1196958, },
	// [12]ID_GENERAL_BUTTON_1
	{D_CTRL_BUTTON, 3, 21, 2, 0, 180, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_beda3362_06d954, },
	// [13]ID_GENERAL_BUTTON_2
	{D_CTRL_BUTTON, 4, 21, 2, 0, 180, 26, 30, 4, (D_FrameCtrlDescr*)&GUID_beda356d_29f4df5, },
	// [14]ID_GENERAL_BUTTON_3
	{D_CTRL_BUTTON, 5, 21, 2, 0, 180, 26, 30, 5, (D_FrameCtrlDescr*)&GUID_beda3362_06d955, },
	// [15]ID_GENERAL_BUTTON_4
	{D_CTRL_BUTTON, 6, 21, 2, 0, 180, 26, 30, 6, (D_FrameCtrlDescr*)&GUID_beda3362_06d956, },
	// [16]ID_GENERAL_BUTTON_5
	{D_CTRL_BUTTON, 7, 21, 2, 0, 180, 26, 30, 7, (D_FrameCtrlDescr*)&GUID_beda3362_06d957, },
	// [17]ID_GENERAL_BUTTON_6
	{D_CTRL_BUTTON, 8, 21, 2, 0, 180, 26, 30, 8, (D_FrameCtrlDescr*)&GUID_beda3362_06d958, },
	// [18]ID_GENERAL_BUTTON_7
	{D_CTRL_BUTTON, 9, 21, 2, 0, 180, 26, 30, 9, (D_FrameCtrlDescr*)&GUID_beda3362_06d959, },
	// [19]ID_GENERAL_BUTTON_8
	{D_CTRL_BUTTON, 10, 22, 1, 20, 180, 26, 30, 10, (D_FrameCtrlDescr*)&GUID_ca26812b_2256049, },
	// [20]ID_GENERAL_BUTTON_9
	{D_CTRL_BUTTON, 11, 21, 2, 0, 180, 26, 30, 11, (D_FrameCtrlDescr*)&GUID_beda3362_06d960, },
	// [21]ID_GENERAL_LABEL_1
	{D_CTRL_LABEL, 3, 249, 2, -20, 210, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9517_1865062, },
	// [22]ID_GENERAL_LABEL_2
	{D_CTRL_LABEL, 4, 249, 2, -20, 210, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb957c_06df9e, },
	// [23]ID_GENERAL_LABEL_3
	{D_CTRL_LABEL, 5, 249, 2, -20, 210, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9517_1865063, },
	// [24]ID_GENERAL_LABEL_4
	{D_CTRL_LABEL, 6, 249, 2, -20, 210, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9517_1865064, },
	// [25]ID_GENERAL_LABEL_5
	{D_CTRL_LABEL, 7, 249, 2, -20, 210, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9517_1865065, },
	// [26]ID_GENERAL_LABEL_6
	{D_CTRL_LABEL, 8, 249, 2, -20, 210, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9517_1865066, },
	// [27]ID_GENERAL_LABEL_7
	{D_CTRL_LABEL, 9, 249, 2, -20, 210, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9517_1865067, },
	// [28]ID_GENERAL_LABEL_8
	{D_CTRL_LABEL, 10, 250, 2, 0, 210, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_ca2681dc_1e82935, },
	// [29]ID_GENERAL_LABEL_9
	{D_CTRL_LABEL, 11, 249, 2, -20, 210, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb9517_1865068, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	panel_setting_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_panel_setting_window[30];
D_Frame panel_setting_window = {
	run_ctrls_panel_setting_window, 
	ctrl_description_of_panel_setting_window, 
	panel_setting_window_init, 
};

