/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2015-03-26 14:40:54

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2014-12-24 14:48:49.406

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
#define	ID_SLEEP_GROUP_BG	1
#define	ID_SLEEP_IMAGE_LEFT_ARROW	2
#define	ID_SLEEP_BUTTON_OFF	3
#define	ID_SLEEP_BUTTON_MINUTE1	4
#define	ID_SLEEP_BUTTON_MINUTE2	5
#define	ID_SLEEP_BUTTON_MINUTE3	6
#define	ID_SLEEP_BUTTON_MINUTE4	7
#define	ID_SLEEP_BUTTON_MINUTE5	8
#define	ID_SLEEP_IMAGE_RIGHT_ARROW	9

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40d76b9_0da4cad={-1, atv_IMG_ID_focus_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40dbf7d_0da506={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_OFF, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c40dbf7d_0da3608={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_OFF, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae3285_128152c={-1, atv_IMG_ID_left_arrow_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4ae32e9_33c104d={-1, atv_IMG_ID_right_arrow_no_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b4c3a1_38a5709={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_15_MINUTE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b4c3a1_38a3ede={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_15_MINUTE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b4c3a1_38a7b72={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_30_MINUTE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b4c3a1_38a7fec={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_30_MINUTE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b4c3a1_38a4088={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_60_MINUTE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b4c3a1_38a5e88={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_60_MINUTE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b4c3a1_38a473e={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_120_MINUTE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b4c3a1_38a5e67={-1, atv_IMG_ID_COMB_button_menu_focus, atv_IDS_120_MINUTE, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08e32b4_1285f1b={-1, -1, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{&GUID_c08e32b4_1285f1b, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_SLEEP_GROUP_BG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d76b9_0daddc={{&GUID_c40d76b9_0da4cad, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_IMAGE}	"ID_SLEEP_IMAGE_LEFT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ae3285_1282685={{&GUID_c4ae3285_128152c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_SLEEP_BUTTON_OFF"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40dbf7d_0da275f={{&GUID_c40dbf7d_0da506, &GUID_c40dbf7d_0da3608, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_SLEEP_BUTTON_MINUTE1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0eb3_0fa23e1={{&GUID_c4b4c3a1_38a5709, &GUID_c4b4c3a1_38a3ede, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_SLEEP_BUTTON_MINUTE2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0f7c_1485bb2={{&GUID_c4b4c3a1_38a7b72, &GUID_c4b4c3a1_38a7fec, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_BUTTON}	"ID_SLEEP_BUTTON_MINUTE3"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e0fe7_222289d={{&GUID_c4b4c3a1_38a4088, &GUID_c4b4c3a1_38a5e88, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_BUTTON}	"ID_SLEEP_BUTTON_MINUTE4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e2b14_21318fa={{&GUID_c4b4c3a1_38a473e, &GUID_c4b4c3a1_38a5e67, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_BUTTON}	"ID_SLEEP_BUTTON_MINUTE5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40e2b7e_08c393c={{&GUID_c4b4c3a1_38a473e, &GUID_c4b4c3a1_38a5e67, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_IMAGE}	"ID_SLEEP_IMAGE_RIGHT_ARROW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4ae32e9_33c6bda={{&GUID_c4ae32e9_33c104d, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_sleep_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 176, 460, 0, 960, 58, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_SLEEP_GROUP_BG
	{D_CTRL_GROUP, 0, -1, 0, 20, 960, 58, 30, -1, (D_FrameCtrlDescr*)&GUID_c40d76b9_0daddc, },
	// [2]ID_SLEEP_IMAGE_LEFT_ARROW
	{D_CTRL_IMAGE, 1, 48, 6, 0, 26, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ae3285_1282685, },
	// [3]ID_SLEEP_BUTTON_OFF
	{D_CTRL_BUTTON, 1, 121, 13, 0, 100, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40dbf7d_0da275f, },
	// [4]ID_SLEEP_BUTTON_MINUTE1
	{D_CTRL_BUTTON, 1, 243, 13, 0, 100, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0eb3_0fa23e1, },
	// [5]ID_SLEEP_BUTTON_MINUTE2
	{D_CTRL_BUTTON, 1, 365, 13, 0, 100, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0f7c_1485bb2, },
	// [6]ID_SLEEP_BUTTON_MINUTE3
	{D_CTRL_BUTTON, 1, 487, 13, 0, 100, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e0fe7_222289d, },
	// [7]ID_SLEEP_BUTTON_MINUTE4
	{D_CTRL_BUTTON, 1, 609, 13, 0, 100, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e2b14_21318fa, },
	// [8]ID_SLEEP_BUTTON_MINUTE5
	{D_CTRL_BUTTON, 1, 731, 13, 0, 100, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c40e2b7e_08c393c, },
	// [9]ID_SLEEP_IMAGE_RIGHT_ARROW
	{D_CTRL_IMAGE, 1, 882, 6, 0, 26, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_c4ae32e9_33c6bda, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_sleep_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_sleep_window[10];
D_Frame atv_sleep_window = {
	run_ctrls_atv_sleep_window, 
	ctrl_description_of_atv_sleep_window, 
	atv_sleep_window_init, 
};

