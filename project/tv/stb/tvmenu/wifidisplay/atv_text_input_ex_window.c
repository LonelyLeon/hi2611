/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY_WIN7"
	update/create time:	2017-12-07 15:13:02

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-10-12 11:04:08.678

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
#define	ID_TEXTINPUT_LABEL_TITLE	1
#define	ID_TEXTINPUT_LABEL_TEXT	2
#define	ID_TEXTINPUT_AREA	3
#define	ID_TEXTINPUT_IMAGE_RED	4
#define	ID_TEXTINPUT_LABEL_NUM0_9	5
#define	ID_TEXTINPUT_LABEL_NUMBER	6
#define	ID_TEXTINPUT_IMAGE_BLUE	7
#define	ID_TEXTINPUT_IMAGE_GREEN	8
#define	ID_TEXTINPUT_LABEL_DEL	9
#define	ID_TEXTINPUT_LABEL_CAPS	10
#define	ID_TEXTINPUT_LABEL_OK	11

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_attr_win={-1, atv_IMG_ID_FS_Wifi_password_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_attr_title={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_attr_txtbox={-1, atv_IMG_ID_FS_Wifi_pw_title, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cb6fc33d_08918be={-1, atv_IMG_ID_Red, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cb633dfc_8be0891={-1, atv_IMG_ID_Green, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_6fccb33d_018b89e={-1, atv_IMG_ID_Blue, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_67acb702_e26204={atv_COLOR_ENUM_84, -1, atv_IDS_NUMBER_0TO9, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_67acb702_620e20={-1, -1, atv_IDS_NUMBER, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_67acb702_620e21={-1, -1, atv_IDS_DELETE, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_67acb702_620e22={-1, -1, atv_IDS_CAPS, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_67acb702_620e23={-1, -1, atv_IDS_OK, &atv_fmt_left_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ctrldescr_win={{&GUID_attr_win, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_TEXTINPUT_LABEL_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ctrldescr_title={{&GUID_attr_title, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_TEXTINPUT_LABEL_TEXT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ctrldescr_txtbox={{&GUID_attr_txtbox, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_DRAW_AREA}	"ID_TEXTINPUT_AREA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_ctrldescr_area={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_IMAGE}	"ID_TEXTINPUT_IMAGE_RED"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cb6fc33d_0894823={{&GUID_cb6fc33d_08918be, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_LABEL}	"ID_TEXTINPUT_LABEL_NUM0_9"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cb70267a_2047941={{&GUID_67acb702_e26204, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_TEXTINPUT_LABEL_NUMBER"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cb702819_32b4030={{&GUID_67acb702_620e20, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_IMAGE}	"ID_TEXTINPUT_IMAGE_BLUE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cb6fc33d_0894824={{&GUID_6fccb33d_018b89e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_IMAGE}	"ID_TEXTINPUT_IMAGE_GREEN"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cb6fc33d_0894825={{&GUID_cb633dfc_8be0891, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_TEXTINPUT_LABEL_DEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cb702819_32b4031={{&GUID_67acb702_620e21, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_TEXTINPUT_LABEL_CAPS"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cb702819_32b4032={{&GUID_67acb702_620e22, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_TEXTINPUT_LABEL_OK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cb702819_32b4033={{&GUID_67acb702_620e23, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_text_input_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 375, 280, 0, 510, 370, 0, -1, (D_FrameCtrlDescr*)&GUID_ctrldescr_win, },
	// [1]ID_TEXTINPUT_LABEL_TITLE
	{D_CTRL_LABEL, 0, 30, 12, 0, 450, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_ctrldescr_title, },
	// [2]ID_TEXTINPUT_LABEL_TEXT
	{D_CTRL_LABEL, 0, 30, 53, 0, 450, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_ctrldescr_txtbox, },
	// [3]ID_TEXTINPUT_AREA
	{D_CTRL_DRAW_AREA, 0, 10, 100, 0, 490, 220, 30, -1, (D_FrameCtrlDescr*)&GUID_ctrldescr_area, },
	// [4]ID_TEXTINPUT_IMAGE_RED
	{D_CTRL_IMAGE, 0, 154, 334, 0, 26, 15, 30, -1, (D_FrameCtrlDescr*)&GUID_cb6fc33d_0894823, },
	// [5]ID_TEXTINPUT_LABEL_NUM0_9
	{D_CTRL_LABEL, 0, 30, 328, 40, 42, 24, 30, -1, (D_FrameCtrlDescr*)&GUID_cb70267a_2047941, },
	// [6]ID_TEXTINPUT_LABEL_NUMBER
	{D_CTRL_LABEL, 0, 76, 326, 40, 60, 28, 30, -1, (D_FrameCtrlDescr*)&GUID_cb702819_32b4030, },
	// [7]ID_TEXTINPUT_IMAGE_BLUE
	{D_CTRL_IMAGE, 0, 272, 334, 0, 26, 15, 30, -1, (D_FrameCtrlDescr*)&GUID_cb6fc33d_0894824, },
	// [8]ID_TEXTINPUT_IMAGE_GREEN
	{D_CTRL_IMAGE, 0, 395, 334, 0, 26, 15, 30, -1, (D_FrameCtrlDescr*)&GUID_cb6fc33d_0894825, },
	// [9]ID_TEXTINPUT_LABEL_DEL
	{D_CTRL_LABEL, 0, 185, 326, 40, 60, 28, 30, -1, (D_FrameCtrlDescr*)&GUID_cb702819_32b4031, },
	// [10]ID_TEXTINPUT_LABEL_CAPS
	{D_CTRL_LABEL, 0, 302, 326, 40, 80, 28, 30, -1, (D_FrameCtrlDescr*)&GUID_cb702819_32b4032, },
	// [11]ID_TEXTINPUT_LABEL_OK
	{D_CTRL_LABEL, 0, 426, 326, 40, 60, 28, 30, -1, (D_FrameCtrlDescr*)&GUID_cb702819_32b4033, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_text_input_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_text_input_window[12];
D_Frame atv_text_input_window = {
	run_ctrls_atv_text_input_window, 
	ctrl_description_of_atv_text_input_window, 
	atv_text_input_window_init, 
};

