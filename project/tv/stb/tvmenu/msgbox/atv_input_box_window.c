/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {liujh}
	on computer "PRLIUJH"
	update/create time:	2016-04-20 15:31:20

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2015-12-28 11:51:06.046

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
#define	ID_LABEL_TITLE	1
#define	ID_MSG_LABEL	2
#define	ID_INPUT_PASSWD	3
#define	ID_LABEL_OK	4
#define	ID_LABEL_CANCEL	5

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf82a754_38a4823={-1, atv_IMG_ID_FS_pop_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf82a768_2fd6784={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf82a8ef_26172ae={-1, -1, -1, &atv_fmt_center_middle_h00_v00_multi_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf82d40e_2804cb0={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf8797f5_0da3912={atv_COLOR_ENUM_1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c34a2fe1_27129={atv_COLOR_ENUM_1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c34a4bee_31c86f={-1, atv_IMG_ID_COMB_button_menu, atv_IDS_CANCEL, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf82a754_38a29={{&GUID_bf82a754_38a4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_LABEL_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf82a768_2fd18be={{&GUID_bf82a768_2fd6784, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_MSG_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf82a8ef_2612cd6={{&GUID_bf82a8ef_26172ae, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_INPUT}	"ID_INPUT_PASSWD"
static char GUID_bf8797f5_0da337d[16+1]={0};
static PREFIXCONST D_FrameInputBoxDescr POSTCONST GUID_bf8797f5_0da5fb2={{&GUID_bf8797f5_0da3912, &GUID_c34a2fe1_27129, NULL, }, 0, 3, 16, GUID_bf8797f5_0da337d, 1, '-', '*', };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf82d40e_2802b97={{&GUID_bf82d40e_2804cb0, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_LABEL_CANCEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf82d5c8_37a4f04={{&GUID_c34a4bee_31c86f, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_input_box_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 440, 206, 0, 404, 208, 0, -1, (D_FrameCtrlDescr*)&GUID_bf82a754_38a29, },
	// [1]ID_LABEL_TITLE
	{D_CTRL_LABEL, 0, 52, 8, 84, 309, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_bf82a768_2fd18be, },
	// [2]ID_MSG_LABEL
	{D_CTRL_LABEL, 0, 32, 47, 84, 341, 52, 30, -1, (D_FrameCtrlDescr*)&GUID_bf82a8ef_2612cd6, },
	// [3]ID_INPUT_PASSWD
	{D_CTRL_INPUT, 0, 105, 109, 76, 202, 33, 30, -1, (D_FrameCtrlDescr*)&GUID_bf8797f5_0da5fb2, },
	// [4]ID_LABEL_OK
	{D_CTRL_LABEL, 0, 86, 165, 76, 93, 33, 30, -1, (D_FrameCtrlDescr*)&GUID_bf82d40e_2802b97, },
	// [5]ID_LABEL_CANCEL
	{D_CTRL_LABEL, 0, 222, 165, 76, 93, 33, 30, -1, (D_FrameCtrlDescr*)&GUID_bf82d5c8_37a4f04, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_input_box_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_input_box_window[6];
D_Frame atv_input_box_window = {
	run_ctrls_atv_input_box_window, 
	ctrl_description_of_atv_input_box_window, 
	atv_input_box_window_init, 
};

 //////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_input_box_ex_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 440, 206, 0, 404, 308, 0, -1, (D_FrameCtrlDescr*)&GUID_bf82a754_38a29, },
	// [1]ID_LABEL_TITLE
	{D_CTRL_LABEL, 0, 52, 12, 84, 303, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf82a768_2fd18be, },
	// [2]ID_MSG_LABEL
	{D_CTRL_LABEL, 0, 32, 62, 84, 341, 67, 30, -1, (D_FrameCtrlDescr*)&GUID_bf82a8ef_2612cd6, },
	// [3]ID_INPUT_PASSWD
	{D_CTRL_INPUT, 0, 105, 150, 76, 202, 33, 30, -1, (D_FrameCtrlDescr*)&GUID_bf8797f5_0da5fb2, },
	// [4]ID_LABEL_OK
	{D_CTRL_LABEL, 0, 156, 165, 76, 93, 33, 30, -1, (D_FrameCtrlDescr*)&GUID_bf82d40e_2802b97, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_input_box_ex_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_input_box_ex_window[5];
D_Frame atv_input_box_ex_window = {
	run_ctrls_atv_input_box_ex_window, 
	ctrl_description_of_atv_input_box_ex_window, 
	atv_input_box_ex_window_init, 
};
