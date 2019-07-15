/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY"
	update/create time:	2018-05-26 13:22:46

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-08-31 11:38:27.453

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
#define	ID_ADDTP_GROUP	1
#define	ID_ADDTP_LABEL0	2
#define	ID_ADDTP_INPUT_FRE	3
#define	ID_ADDTP_LABEL1	4
#define	ID_ADDTP_INPUT_SYM	5
#define	ID_ADDTP_LABEL2	6
#define	ID_ADDTP_SELECT_POLARITY	7

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1f7c19c_30df3e={-1, -1, atv_IDS_POLARITY, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1f7c19c_30df5e={-1, -1, atv_IDS_FREQUENCY, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1f7c19c_30df6e={-1, -1, atv_IDS_SYMBOL_RATE, &atv_fmt_left_middle_h05_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c1f8f776_34b4823={atv_COLOR_ENUM_106, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c20b7283_1b529={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c81ddd08_3991967={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1f7b99f_05d29={{&GUID_c81ddd08_3991967, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_ADDTP_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c20ca188_1f4615a={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_ADDTP_LABEL0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1f7c105_10931={{&GUID_c1f7c19c_30df5e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_INPUT}	"ID_ADDTP_INPUT_FRE"
static char GUID_c1ffc410_0006df1[10+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_c1ffc410_0005af1={{&GUID_c20b7283_1b529, &GUID_c1f8f776_34b4823, NULL, }, 1, 5, 10, GUID_c1ffc410_0006df1, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_ADDTP_LABEL1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1f7c105_10941={{&GUID_c1f7c19c_30df6e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_INPUT}	"ID_ADDTP_INPUT_SYM"
static char GUID_c1fe4ac1_09c6496[10+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_c1fe4ac1_09c3d16={{&GUID_c20b7283_1b529, &GUID_c1f8f776_34b4823, NULL, }, 1, 5, 10, GUID_c1fe4ac1_09c6496, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_ADDTP_LABEL2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c1f7c105_10911={{&GUID_c1f7c19c_30df3e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_SELECT}	"ID_ADDTP_SELECT_POLARITY"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c1f7c105_10912={{&GUID_c20b7283_1b529, &GUID_c1f8f776_34b4823, NULL, }, 1, 0, NULL, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_add_tp_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 910, 260, 0, 310, 124, 0, -1, (D_FrameCtrlDescr*)&GUID_c1f7b99f_05d29, },
	// [1]ID_ADDTP_GROUP
	{D_CTRL_GROUP, 0, 7, 6, -140, 296, 110, 30, -1, (D_FrameCtrlDescr*)&GUID_c20ca188_1f4615a, },
	// [2]ID_ADDTP_LABEL0
	{D_CTRL_LABEL, 1, 5, 3, 135, 130, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c1f7c105_10931, },
	// [3]ID_ADDTP_INPUT_FRE
	{D_CTRL_INPUT, 1, 140, 3, 85, 150, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c1ffc410_0005af1, },
	// [4]ID_ADDTP_LABEL1
	{D_CTRL_LABEL, 1, 5, 39, 135, 130, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c1f7c105_10941, },
	// [5]ID_ADDTP_INPUT_SYM
	{D_CTRL_INPUT, 1, 140, 39, 115, 150, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c1fe4ac1_09c3d16, },
	// [6]ID_ADDTP_LABEL2
	{D_CTRL_LABEL, 1, 5, 75, 135, 130, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c1f7c105_10911, },
	// [7]ID_ADDTP_SELECT_POLARITY
	{D_CTRL_SELECT, 1, 140, 75, 135, 150, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c1f7c105_10912, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_add_tp_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_add_tp_window[8];
D_Frame atv_add_tp_window = {
	run_ctrls_atv_add_tp_window, 
	ctrl_description_of_atv_add_tp_window, 
	atv_add_tp_window_init, 
};

