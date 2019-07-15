/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {miaoyc}
	on computer "PRMIAOYC"
	update/create time:	2014-11-17 15:26:10

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2014-11-11 13:50:18.265

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
#define	ID_POSITION_LABLE_TITLE	1
#define	ID_POSITION_BUTTON_UP	2
#define	ID_POSITION_BUTTON_LEFT	3
#define	ID_POSITION_BUTTON_RIGHT	4
#define	ID_POSITION_BUTTON_DOWN	5
#define	ID_POSITION_LABLE_H	6
#define	ID_POSITION_LABLE_V	7
#define	ID_POSITION_LABLE_HVAL	8
#define	ID_POSITION_LABLE_VVAL	9

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c49fb150_0cb62b1={-1, atv_IMG_ID_FS_pop_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c49fb715_03e949={-1, -1, atv_IDS_ADJUST, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a07e5f_3b921fd={-1, atv_IMG_ID_position_up, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a07e5f_3b93a24={-1, atv_IMG_ID_position_up_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a07f88_2bf45e2={-1, atv_IMG_ID_position_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a07f88_2bf1cc3={-1, atv_IMG_ID_position_left_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a080ba_0ab2fa3={-1, atv_IMG_ID_position_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a080ba_0ab7770={-1, atv_IMG_ID_position_right_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a0812f_01f7c10={-1, atv_IMG_ID_position_down, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4a0812f_01f4608={-1, atv_IMG_ID_position_down_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b4236a_37a7fbf={-1, -1, -1, &atv_fmt_middle_h00_v00_single_orange, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4b4236a_37a5fcd={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bc531d_1c529={-1, -1, atv_IDS_HORIZONTAL_POS, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4bc53dd_3c829={-1, -1, atv_IDS_VERTICAL_POS, &atv_fmt_center_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c40d74e3_09c63cb={{&GUID_c49fb150_0cb62b1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_POSITION_LABLE_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c49fb715_03e3cc7={{&GUID_c49fb715_03e949, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_POSITION_BUTTON_UP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a07e5f_3b9524d={{&GUID_c4a07e5f_3b921fd, &GUID_c4a07e5f_3b93a24, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_POSITION_BUTTON_LEFT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a07f88_2bf1daa={{&GUID_c4a07f88_2bf45e2, &GUID_c4a07f88_2bf1cc3, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_POSITION_BUTTON_RIGHT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a080ba_0ab3d8f={{&GUID_c4a080ba_0ab2fa3, &GUID_c4a080ba_0ab7770, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_POSITION_BUTTON_DOWN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a0812f_01f5f3c={{&GUID_c4a0812f_01f7c10, &GUID_c4a0812f_01f4608, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_POSITION_LABLE_H"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a081ec_2af6729={{&GUID_c4bc531d_1c529, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_POSITION_LABLE_V"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4a09dbd_2715489={{&GUID_c4bc53dd_3c829, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_POSITION_LABLE_HVAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b4236a_37a3690={{&GUID_c4b4236a_37a7fbf, NULL, &GUID_c4b4236a_37a5fcd, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_POSITION_LABLE_VVAL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4b424a8_2426a6b={{&GUID_c4b4236a_37a7fbf, NULL, &GUID_c4b4236a_37a5fcd, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_pop_position_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 362, 312, 0, 552, 340, 0, -1, (D_FrameCtrlDescr*)&GUID_c40d74e3_09c63cb, },
	// [1]ID_POSITION_LABLE_TITLE
	{D_CTRL_LABEL, 0, 213, 15, -75, 125, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c49fb715_03e3cc7, },
	// [2]ID_POSITION_BUTTON_UP
	{D_CTRL_BUTTON, 0, 228, 58, 20, 96, 54, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a07e5f_3b9524d, },
	// [3]ID_POSITION_BUTTON_LEFT
	{D_CTRL_BUTTON, 0, 168, 120, 20, 54, 96, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a07f88_2bf1daa, },
	// [4]ID_POSITION_BUTTON_RIGHT
	{D_CTRL_BUTTON, 0, 332, 120, 20, 54, 96, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a080ba_0ab3d8f, },
	// [5]ID_POSITION_BUTTON_DOWN
	{D_CTRL_BUTTON, 0, 228, 222, 20, 96, 54, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a0812f_01f5f3c, },
	// [6]ID_POSITION_LABLE_H
	{D_CTRL_LABEL, 0, 62, 300, 20, 100, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a081ec_2af6729, },
	// [7]ID_POSITION_LABLE_V
	{D_CTRL_LABEL, 0, 310, 300, 20, 100, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c4a09dbd_2715489, },
	// [8]ID_POSITION_LABLE_HVAL
	{D_CTRL_LABEL, 0, 202, 300, 20, 55, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b4236a_37a3690, },
	// [9]ID_POSITION_LABLE_VVAL
	{D_CTRL_LABEL, 0, 448, 300, 20, 55, 32, 30, -1, (D_FrameCtrlDescr*)&GUID_c4b424a8_2426a6b, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_pop_position_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_pop_position_window[10];
D_Frame atv_pop_position_window = {
	run_ctrls_atv_pop_position_window, 
	ctrl_description_of_atv_pop_position_window, 
	atv_pop_position_window_init, 
};

