/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2016-01-18 14:29:41

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-11-30 18:45:54.727

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
#define	ID_UPGRADE_LABEL_UPGRADE	1
#define	ID_UPGRADE_GROUP_1	2
#define	ID_UPGRADE_GROUP_2	3
#define	ID_UPGRADE_BUTTON_1	4
#define	ID_UPGRADE_LABEL_1	5
#define	ID_UPGRADE_BUTTON_2	6
#define	ID_UPGRADE_LABEL_2	7
#define	ID_UPGRADE_PROGRESS	8
#define	ID_UPGRADE_LABEL_PROGRESS	9
#define	ID_SW_INFO_GROUP_1	10
#define	ID_SW_INFO_BUTTON_1	11
#define	ID_SW_INFO_LABEL_1	12
#define	ID_SW_INFO_GROUP_2	13
#define	ID_SW_INFO_BUTTON_2	14
#define	ID_SW_INFO_LABEL_2	15
#define	ID_SW_INFO_GROUP_3	16
#define	ID_SW_INFO_BUTTON_3	17
#define	ID_SW_INFO_LABEL_3	18
#define	ID_SW_INFO_GROUP_4	19
#define	ID_SW_INFO_BUTTON_4	20
#define	ID_SW_INFO_LABEL_4	21
#define	ID_SW_INFO_GROUP_6	22
#define	ID_SW_INFO_BUTTON_6	23
#define	ID_SW_INFO_LABEL_6	24
#define	ID_SW_INFO_GROUP_5	25
#define	ID_SW_INFO_BUTTON_5	26
#define	ID_SW_INFO_LABEL_5	27
#define	ID_SW_INFO_GROUP_7	28
#define	ID_SW_INFO_BUTTON_7	29
#define	ID_SW_INFO_LABEL_7	30

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, atv_IDS_NULL, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed9bb91_128645b={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda2ec1_38a531f={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c05f9741_07d2cd6={-1, -1, atv_IDS_NULL, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0638783_2222141={-1, atv_IMG_ID_box_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0638bdf_15727d0={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c064a4be_3a926e9={atv_COLOR_ENUM_33, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c47386a2_05d1649={-1, -1, atv_IDS_PRODUCECOMPANY, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c47386a2_05d6df1={-1, -1, atv_IDS_PRODUCECOMPANY, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4738987_1f4f3e={-1, -1, atv_IDS_HARDWAREEDITION, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4738c20_119b13={-1, -1, atv_IDS_SOFTWAREEDITION, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4738fa9_2de12bc={-1, -1, atv_IDS_SERIALNUMBER, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c47391aa_29f9f3={-1, -1, atv_IDS_COMPANYID, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c473e80f_00f5cd9={-1, -1, atv_IDS_BUILD_TIME, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c0ee2da5_1f41649={-1, -1, atv_IDS_CHIP_ID, &atv_fmt_left_middle_h00_v00_single_grey, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_UPGRADE_LABEL_UPGRADE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_UPGRADE_GROUP_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96c42_0ab29={{NULL, &GUID_c0638783_2222141, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_UPGRADE_GROUP_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96db6_02e4ae1={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_UPGRADE_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed9bb91_128666e={{&GUID_bed9bb91_128645b, &GUID_c05f9741_07d2cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_UPGRADE_LABEL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda2ec1_38a6275={{&GUID_beda2ec1_38a531f, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_BUTTON}	"ID_UPGRADE_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda323b_30d1d08={{&GUID_bed9bb91_128645b, &GUID_c05f9741_07d2cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_UPGRADE_LABEL_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bedb946e_0ab59e={{&GUID_c0638bdf_15727d0, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_PROGRESS}	"ID_UPGRADE_PROGRESS"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_c064a4be_3a941bb={{&GUID_c064a4be_3a926e9, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_66, -1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_UPGRADE_LABEL_PROGRESS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c06572d8_31c6784={{&GUID_c0638bdf_15727d0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_GROUP}	"ID_SW_INFO_GROUP_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4737646_03e3d6c={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_BUTTON}	"ID_SW_INFO_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c47386a2_05d5f90={{&GUID_c47386a2_05d1649, &GUID_c47386a2_05d6df1, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_SW_INFO_LABEL_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c473879d_05d41bb={{&GUID_c0638bdf_15727d0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_GROUP}	"ID_SW_INFO_GROUP_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4738920_30d2ea6={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_BUTTON}	"ID_SW_INFO_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4738987_1f4390c={{&GUID_c4738987_1f4f3e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_LABEL}	"ID_SW_INFO_LABEL_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4738a53_30d305e={{&GUID_c0638bdf_15727d0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_GROUP}	"ID_SW_INFO_GROUP_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4738b78_1094e6b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_BUTTON}	"ID_SW_INFO_BUTTON_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4738c20_1195169={{&GUID_c4738c20_119b13, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_LABEL}	"ID_SW_INFO_LABEL_3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4738e8a_3b97556={{&GUID_c0638bdf_15727d0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_GROUP}	"ID_SW_INFO_GROUP_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4738f43_0ab5ff2={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_BUTTON}	"ID_SW_INFO_BUTTON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4738fa9_2de3e5d={{&GUID_c4738fa9_2de12bc, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_SW_INFO_LABEL_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4739092_21316da={{&GUID_c0638bdf_15727d0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_GROUP}	"ID_SW_INFO_GROUP_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c473914a_0fa67d2={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_BUTTON}	"ID_SW_INFO_BUTTON_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c47391aa_29f381c={{&GUID_c47391aa_29f9f3, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_LABEL}	"ID_SW_INFO_LABEL_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4739221_2717c7b={{&GUID_c0638bdf_15727d0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_GROUP}	"ID_SW_INFO_GROUP_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c473e7e5_08c5cdd={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_BUTTON}	"ID_SW_INFO_BUTTON_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c473e80f_00f18fa={{&GUID_c473e80f_00f5cd9, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_LABEL}	"ID_SW_INFO_LABEL_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c473e8bb_08ccc0={{&GUID_c0638bdf_15727d0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [28]{D_CTRL_GROUP}	"ID_SW_INFO_GROUP_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0ee2a59_36b26e9={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [29]{D_CTRL_BUTTON}	"ID_SW_INFO_BUTTON_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0ee2ad6_32c12db={{&GUID_c0ee2da5_1f41649, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [30]{D_CTRL_LABEL}	"ID_SW_INFO_LABEL_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c0ee2b7a_167f3e={{&GUID_c0638bdf_15727d0, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_software_update_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 485, 660, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_UPGRADE_LABEL_UPGRADE
	{D_CTRL_LABEL, 0, 111, 7, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_UPGRADE_GROUP_1
	{D_CTRL_GROUP, 0, 2, 43, 40, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96c42_0ab29, },
	// [3]ID_UPGRADE_GROUP_2
	{D_CTRL_GROUP, 0, 2, 77, 40, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96db6_02e4ae1, },
	// [4]ID_UPGRADE_BUTTON_1
	{D_CTRL_BUTTON, 2, 21, 2, 0, 180, 26, 30, 2, (D_FrameCtrlDescr*)&GUID_bed9bb91_128666e, },
	// [5]ID_UPGRADE_LABEL_1
	{D_CTRL_LABEL, 2, 281, 2, 0, 187, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_beda2ec1_38a6275, },
	// [6]ID_UPGRADE_BUTTON_2
	{D_CTRL_BUTTON, 3, 21, 2, 0, 167, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_beda323b_30d1d08, },
	// [7]ID_UPGRADE_LABEL_2
	{D_CTRL_LABEL, 3, 281, 2, -20, 187, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bedb946e_0ab59e, },
	// [8]ID_UPGRADE_PROGRESS
	{D_CTRL_PROGRESS, 0, 2, 111, 20, 423, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c064a4be_3a941bb, },
	// [9]ID_UPGRADE_LABEL_PROGRESS
	{D_CTRL_LABEL, 0, 435, 111, 20, 44, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c06572d8_31c6784, },
	// [10]ID_SW_INFO_GROUP_1
	{D_CTRL_GROUP, 0, 2, 146, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4737646_03e3d6c, },
	// [11]ID_SW_INFO_BUTTON_1
	{D_CTRL_BUTTON, 10, 21, 2, 0, 180, 26, 30, 10, (D_FrameCtrlDescr*)&GUID_c47386a2_05d5f90, },
	// [12]ID_SW_INFO_LABEL_1
	{D_CTRL_LABEL, 10, 281, 2, 0, 187, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c473879d_05d41bb, },
	// [13]ID_SW_INFO_GROUP_2
	{D_CTRL_GROUP, 0, 2, 181, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4738920_30d2ea6, },
	// [14]ID_SW_INFO_BUTTON_2
	{D_CTRL_BUTTON, 13, 21, 2, 0, 167, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4738987_1f4390c, },
	// [15]ID_SW_INFO_LABEL_2
	{D_CTRL_LABEL, 13, 281, 2, 0, 187, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4738a53_30d305e, },
	// [16]ID_SW_INFO_GROUP_3
	{D_CTRL_GROUP, 0, 2, 216, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4738b78_1094e6b, },
	// [17]ID_SW_INFO_BUTTON_3
	{D_CTRL_BUTTON, 16, 21, 2, 0, 190, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4738c20_1195169, },
	// [18]ID_SW_INFO_LABEL_3
	{D_CTRL_LABEL, 16, 281, 2, 0, 187, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4738e8a_3b97556, },
	// [19]ID_SW_INFO_GROUP_4
	{D_CTRL_GROUP, 0, 2, 251, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4738f43_0ab5ff2, },
	// [20]ID_SW_INFO_BUTTON_4
	{D_CTRL_BUTTON, 19, 21, 2, 0, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4738fa9_2de3e5d, },
	// [21]ID_SW_INFO_LABEL_4
	{D_CTRL_LABEL, 19, 281, 2, 0, 187, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4739092_21316da, },
	// [22]ID_SW_INFO_GROUP_6
	{D_CTRL_GROUP, 0, 2, 285, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c473914a_0fa67d2, },
	// [23]ID_SW_INFO_BUTTON_6
	{D_CTRL_BUTTON, 22, 21, 2, 0, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c47391aa_29f381c, },
	// [24]ID_SW_INFO_LABEL_6
	{D_CTRL_LABEL, 22, 281, 2, 0, 187, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c4739221_2717c7b, },
	// [25]ID_SW_INFO_GROUP_5
	{D_CTRL_GROUP, 0, 2, 319, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c473e7e5_08c5cdd, },
	// [26]ID_SW_INFO_BUTTON_5
	{D_CTRL_BUTTON, 25, 21, 2, 0, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c473e80f_00f18fa, },
	// [27]ID_SW_INFO_LABEL_5
	{D_CTRL_LABEL, 25, 281, 2, 0, 187, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c473e8bb_08ccc0, },
	// [28]ID_SW_INFO_GROUP_7
	{D_CTRL_GROUP, 0, 2, 355, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c0ee2a59_36b26e9, },
	// [29]ID_SW_INFO_BUTTON_7
	{D_CTRL_BUTTON, 0, 23, 357, 20, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c0ee2ad6_32c12db, },
	// [30]ID_SW_INFO_LABEL_7
	{D_CTRL_LABEL, 0, 283, 352, 20, 180, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c0ee2b7a_167f3e, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	software_update_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_software_update_window[31];
D_Frame software_update_window = {
	run_ctrls_software_update_window, 
	ctrl_description_of_software_update_window, 
	software_update_window_init, 
};

