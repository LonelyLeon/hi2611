/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY"
	update/create time:	2015-09-06 16:03:04

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-08-20 10:37:14.250

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
#define	ID_MANUAL_SCAN_LABEL_CHANNEL_SCAN	1
#define	ID_MANUAL_SCAN_GROUP_FREQ	2
#define	ID_MANUAL_SCAN_LABLE_VU	3
#define	ID_MANUAL_SCAN_LABLE_INDEX	4
#define	ID_MANUAL_SCAN_FREQ_LEFT	5
#define	ID_MANUAL_SCAN_FREQ_RIGHT	6
#define	ID_MANUAL_SCAN_GROUP_PROG_NUM	7
#define	ID_MANUAL_SCAN_LABEL_TV	8
#define	ID_MANUAL_SCAN_LABEL_RADIO	9
#define	ID_MANUAL_SCAN_LABEL_TV_NUM	10
#define	ID_MANUAL_SCAN_LABEL_RADIO_NUM	11
#define	ID_MANUAL_SCAN_LEBEL_FREQ	12
#define	ID_MANUAL_SCAN_LABEL_TV_LABEL	13
#define	ID_MANUAL_SCAN_LABEL_PROGRESS	14
#define	ID_MANUAL_SCAN_PROGRESS_SCAN	15
#define	ID_MANUAL_SCAN_LABEL_OK_ICON	16
#define	ID_MANUAL_SCAN_LABEL_OK	17
#define	ID_MANUAL_SCAN_LABEL_CANCEL_ICON	18
#define	ID_MANUAL_SCAN_LABEL_CANCEL	19
#define	ID_MANUAL_SCAN_LABEL_SIGNAL	20
#define	ID_MANUAL_SCAN_LABEL_FREQ	21
#define	ID_MANUAL_SCAN_LABEL_FREQ_NUM	22

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a7308_23225df={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a736f_35b62bb={-1, -1, atv_IDS_TV_MANUAL_SCAN, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a742e_1d44dd2={-1, -1, atv_IDS_DIGI_TV, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a78f8_34b1bb2={-1, -1, atv_IDS_DIGI_RADIO, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a795e_290263b={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a7dec_02e3cc2={-1, atv_IMG_ID_hint_button, atv_IDS_BACK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a7edc_08c697e={-1, -1, atv_IDS_EXIT, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a7f2f_1285cf7={-1, atv_IMG_ID_hint_button, atv_IDS_MENU, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a7fe7_1576b29={-1, -1, atv_IDS_BACK, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a80cb_08c48a9={-1, -1, atv_IDS_BAD, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a80cb_08c5586={-1, -1, atv_IDS_GOOD, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a84b1_10965e2={-1, -1, atv_IDS_NO_SIGNAL, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a8553_1b568d8={-1, -1, atv_IDS_FREQ, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a8624_1485d76={atv_COLOR_ENUM_106, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a87bd_2de675d={-1, atv_IMG_ID_search_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56a98d9_2517a6c={-1, atv_IMG_ID_search_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56c32ec_0cb2b28={-1, atv_IMG_ID_signal_progress_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c46b9143_1196784={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7308_2327e6c={{&GUID_c56a7308_23225df, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABEL_CHANNEL_SCAN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a736f_35b7e2e={{&GUID_c56a736f_35b62bb, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_MANUAL_SCAN_GROUP_FREQ"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a8624_1484453={{&GUID_c56a8624_1485d76, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABLE_VU"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c46e0fc3_00f18be={{&GUID_c46b9143_1196784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABLE_INDEX"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c46b98fe_3996952={{&GUID_c46b9143_1196784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_FREQ_LEFT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a87bd_2de456a={{&GUID_c56a87bd_2de675d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_FREQ_RIGHT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a98d9_251676a={{&GUID_c56a98d9_2517a6c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_GROUP}	"ID_MANUAL_SCAN_GROUP_PROG_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56e39f3_05d5f90={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABEL_TV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a742e_1d47393={{&GUID_c56a742e_1d44dd2, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABEL_RADIO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a78f8_34b25d={{&GUID_c56a78f8_34b1bb2, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABEL_TV_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a795e_2906132={{&GUID_c56a795e_290263b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABEL_RADIO_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7a27_1484698={{&GUID_c56a795e_290263b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LEBEL_FREQ"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7af0_01f3306={{&GUID_c56a80cb_08c48a9, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABEL_TV_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7c05_3c810e6={{&GUID_c56a80cb_08c5586, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABEL_PROGRESS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c32ec_0cb3075={{&GUID_c56c32ec_0cb2b28, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_PROGRESS}	"ID_MANUAL_SCAN_PROGRESS_SCAN"
static PREFIXCONST D_FrameProgressBarDescr POSTCONST GUID_c56a7cdf_1e41f42={{NULL, NULL, NULL, }, 1, 100, 1, 0, -1, atv_IMG_ID_signal_progress, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABEL_OK_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7dec_02e226a={{&GUID_c56a7dec_02e3cc2, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7edc_08cd74={{&GUID_c56a7edc_08c697e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABEL_CANCEL_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7f2f_1282084={{&GUID_c56a7f2f_1285cf7, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABEL_CANCEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a7fe7_1574a4={{&GUID_c56a7fe7_1576b29, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABEL_SIGNAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a84b1_1094010={{&GUID_c56a84b1_10965e2, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABEL_FREQ"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a8553_1b5752f={{&GUID_c56a8553_1b568d8, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_LABEL}	"ID_MANUAL_SCAN_LABEL_FREQ_NUM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56a8587_2514b91={{&GUID_c46b9143_1196784, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_manual_scan_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 380, 144, 0, 520, 432, 0, -1, (D_FrameCtrlDescr*)&GUID_c56a7308_2327e6c, },
	// [1]ID_MANUAL_SCAN_LABEL_CHANNEL_SCAN
	{D_CTRL_LABEL, 0, 140, 16, 20, 231, 24, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a736f_35b7e2e, },
	// [2]ID_MANUAL_SCAN_GROUP_FREQ
	{D_CTRL_GROUP, 0, 10, 64, 20, 500, 40, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a8624_1484453, },
	// [3]ID_MANUAL_SCAN_LABLE_VU
	{D_CTRL_LABEL, 2, 168, 9, 0, 40, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c46e0fc3_00f18be, },
	// [4]ID_MANUAL_SCAN_LABLE_INDEX
	{D_CTRL_LABEL, 2, 209, 9, 0, 115, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c46b98fe_3996952, },
	// [5]ID_MANUAL_SCAN_FREQ_LEFT
	{D_CTRL_LABEL, 2, 108, 14, 0, 12, 12, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a87bd_2de456a, },
	// [6]ID_MANUAL_SCAN_FREQ_RIGHT
	{D_CTRL_LABEL, 2, 369, 14, 0, 12, 12, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a98d9_251676a, },
	// [7]ID_MANUAL_SCAN_GROUP_PROG_NUM
	{D_CTRL_GROUP, 0, 42, 109, 20, 440, 78, 30, -1, (D_FrameCtrlDescr*)&GUID_c56e39f3_05d5f90, },
	// [8]ID_MANUAL_SCAN_LABEL_TV
	{D_CTRL_LABEL, 7, 38, 3, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a742e_1d47393, },
	// [9]ID_MANUAL_SCAN_LABEL_RADIO
	{D_CTRL_LABEL, 7, 38, 33, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a78f8_34b25d, },
	// [10]ID_MANUAL_SCAN_LABEL_TV_NUM
	{D_CTRL_LABEL, 7, 312, 3, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a795e_2906132, },
	// [11]ID_MANUAL_SCAN_LABEL_RADIO_NUM
	{D_CTRL_LABEL, 7, 312, 33, 0, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7a27_1484698, },
	// [12]ID_MANUAL_SCAN_LEBEL_FREQ
	{D_CTRL_LABEL, 0, 34, 314, 20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7af0_01f3306, },
	// [13]ID_MANUAL_SCAN_LABEL_TV_LABEL
	{D_CTRL_LABEL, 0, 452, 314, 20, 54, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7c05_3c810e6, },
	// [14]ID_MANUAL_SCAN_LABEL_PROGRESS
	{D_CTRL_LABEL, 0, 34, 344, 20, 453, 16, 30, -1, (D_FrameCtrlDescr*)&GUID_c56c32ec_0cb3075, },
	// [15]ID_MANUAL_SCAN_PROGRESS_SCAN
	{D_CTRL_PROGRESS, 14, 0, 0, 0, 453, 16, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7cdf_1e41f42, },
	// [16]ID_MANUAL_SCAN_LABEL_OK_ICON
	{D_CTRL_LABEL, 0, 290, 376, 20, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7dec_02e226a, },
	// [17]ID_MANUAL_SCAN_LABEL_OK
	{D_CTRL_LABEL, 0, 162, 379, 20, 73, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7edc_08cd74, },
	// [18]ID_MANUAL_SCAN_LABEL_CANCEL_ICON
	{D_CTRL_LABEL, 0, 57, 376, 20, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7f2f_1282084, },
	// [19]ID_MANUAL_SCAN_LABEL_CANCEL
	{D_CTRL_LABEL, 0, 397, 379, 20, 74, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a7fe7_1574a4, },
	// [20]ID_MANUAL_SCAN_LABEL_SIGNAL
	{D_CTRL_LABEL, 0, 104, 252, 20, 331, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a84b1_1094010, },
	// [21]ID_MANUAL_SCAN_LABEL_FREQ
	{D_CTRL_LABEL, 0, 131, 283, 20, 69, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a8553_1b5752f, },
	// [22]ID_MANUAL_SCAN_LABEL_FREQ_NUM
	{D_CTRL_LABEL, 0, 208, 283, 20, 122, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56a8587_2514b91, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	manual_scan_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_manual_scan_window[23];
D_Frame manual_scan_window = {
	run_ctrls_manual_scan_window, 
	ctrl_description_of_manual_scan_window, 
	manual_scan_window_init, 
};

