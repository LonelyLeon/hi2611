/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2017-07-27 10:56:16

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
#define	ID_FULL_SCAN_LABEL_CHANNEL_SCAN	1
#define	ID_FULL_SCAN_LABEL_TV	2
#define	ID_FULL_SCAN_LABEL_RADIO	3
#define	ID_FULL_SCAN_LABEL_TV_NUM	4
#define	ID_FULL_SCAN_LABEL_RADIO_NUM	5
#define	ID_FULL_SCAN_LEBEL_FREQ	6
#define	ID_FULL_SCAN_LABEL_PROGRESS_SCAN	7
#define	ID_FULL_SCAN_LABEL_PROGRESS	8
#define	ID_FULL_SCAN_LABEL_TV_LABEL	9
#define	ID_FULL_SCAN_PROGRESS_SCAN	10
#define	ID_FULL_SCAN_LABEL_OK_ICON	11
#define	ID_FULL_SCAN_LABEL_OK	12
#define	ID_FULL_SCAN_LABEL_CANCEL_ICON	13
#define	ID_FULL_SCAN_LABEL_CANCEL	14

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a7308_23225df={-1, atv_IMG_ID_FS_WHITE_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a736f_35b62bb={-1, -1, atv_IDS_CHANNEL_SCAN, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a742e_1d44dd2={-1, -1, atv_IDS_DIGI_TV, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a78f8_34b1bb2={-1, -1, atv_IDS_DIGI_RADIO, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a795e_290263b={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a7dec_02e3cc2={-1, atv_IMG_ID_FS_BUTTON_GRAY, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a7edc_08c697e={-1, -1, atv_IDS_BACK, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a7f2f_1285cf7={-1, atv_IMG_ID_FS_BUTTON_GRAY, atv_IDS_MENU, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a7fe7_1576b29={-1, -1, atv_IDS_EXIT, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56b1019_37a1f5a={atv_COLOR_ENUM_18, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7308_2327e6c={{&GUID_c56a7308_23225df, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_FULL_SCAN_LABEL_CHANNEL_SCAN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a736f_35b7e2e={{&GUID_c56a736f_35b62bb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_FULL_SCAN_LABEL_TV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a742e_1d47393={{&GUID_c56a742e_1d44dd2, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_FULL_SCAN_LABEL_RADIO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a78f8_34b25d={{&GUID_c56a78f8_34b1bb2, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_FULL_SCAN_LABEL_TV_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a795e_2906132={{&GUID_c56a795e_290263b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_FULL_SCAN_LABEL_RADIO_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7a27_1484698={{&GUID_c56a795e_290263b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_FULL_SCAN_LEBEL_FREQ"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7af0_01f3306={{&GUID_c56a795e_290263b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_FULL_SCAN_LABEL_PROGRESS_SCAN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56b1019_37a5fb2={{&GUID_c56b1019_37a1f5a, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_FULL_SCAN_LABEL_PROGRESS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7b91_02e2141={{&GUID_c56a795e_290263b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_FULL_SCAN_LABEL_TV_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7c05_3c810e6={{&GUID_c56a742e_1d44dd2, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_PROGRESS}	"ID_FULL_SCAN_PROGRESS_SCAN"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_c56a7cdf_1e41f42={{NULL, NULL, NULL, }, 1, 100, 1, 0, atv_COLOR_ENUM_60,-1,  };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_FULL_SCAN_LABEL_OK_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7dec_02e226a={{&GUID_c56a7dec_02e3cc2, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_FULL_SCAN_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7edc_08cd74={{&GUID_c56a7edc_08c697e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_FULL_SCAN_LABEL_CANCEL_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7f2f_1282084={{&GUID_c56a7f2f_1285cf7, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_FULL_SCAN_LABEL_CANCEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7fe7_1574a4={{&GUID_c56a7fe7_1576b29, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_auto_search_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 180, 138, 0, 360, 300, 0, -1, (D_FrameCtrlDescr*)&GUID_c56a7308_2327e6c, },
	// [1]ID_FULL_SCAN_LABEL_CHANNEL_SCAN
	{D_CTRL_LABEL, 0, 103, 16, 20, 163, 24, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a736f_35b7e2e, },
	// [2]ID_FULL_SCAN_LABEL_TV
	{D_CTRL_LABEL, 0, 36, 53, 20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a742e_1d47393, },
	// [3]ID_FULL_SCAN_LABEL_RADIO
	{D_CTRL_LABEL, 0, 36, 83, 20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a78f8_34b25d, },
	// [4]ID_FULL_SCAN_LABEL_TV_NUM
	{D_CTRL_LABEL, 0, 226, 53, 20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a795e_2906132, },
	// [5]ID_FULL_SCAN_LABEL_RADIO_NUM
	{D_CTRL_LABEL, 0, 226, 83, 20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7a27_1484698, },
	// [6]ID_FULL_SCAN_LEBEL_FREQ
	{D_CTRL_LABEL, 0, 7, 176, 20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7af0_01f3306, },
	// [7]ID_FULL_SCAN_LABEL_PROGRESS_SCAN
	{D_CTRL_LABEL, 0, 13, 206, 20, 333, 16, 30, -1, (D_FrameCtrlDescr*)&GUID_c56b1019_37a5fb2, },
	// [8]ID_FULL_SCAN_LABEL_PROGRESS
	{D_CTRL_LABEL, 0, 196, 176, 20, 56, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7b91_02e2141, },
	// [9]ID_FULL_SCAN_LABEL_TV_LABEL
	{D_CTRL_LABEL, 0, 253, 176, 20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7c05_3c810e6, },
	// [10]ID_FULL_SCAN_PROGRESS_SCAN
	{D_CTRL_PROGRESS, 7, 0, 0, 0, 333, 16, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7cdf_1e41f42, },
	// [11]ID_FULL_SCAN_LABEL_OK_ICON
	{D_CTRL_LABEL, 0, 216, 249, 20, 74, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7dec_02e226a, },
	// [12]ID_FULL_SCAN_LABEL_OK
	{D_CTRL_LABEL, 0, 99, 250, 20, 50, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7edc_08cd74, },
	// [13]ID_FULL_SCAN_LABEL_CANCEL_ICON
	{D_CTRL_LABEL, 0, 20, 248, 20, 74, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7f2f_1282084, },
	// [14]ID_FULL_SCAN_LABEL_CANCEL
	{D_CTRL_LABEL, 0, 296, 251, 20, 50, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7fe7_1574a4, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_auto_search_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_auto_search_window[15];
D_Frame atv_auto_search_window = {
	run_ctrls_atv_auto_search_window, 
	ctrl_description_of_atv_auto_search_window, 
	atv_auto_search_window_init, 
};

