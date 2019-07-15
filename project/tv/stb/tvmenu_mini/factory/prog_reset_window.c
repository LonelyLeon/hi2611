/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY"
	update/create time:	2015-08-25 15:04:46

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
#define	ID_CONFIG_LABEL_CONFIG	1
#define	ID_CONFIG_GROUP	2
#define	ID_CONFIG_GROUP_1	3
#define	ID_CONFIG_PROG_SEL	4
#define	ID_CONFIG_SELECT_PROG	5
#define	ID_CONFIG_LABEL_PROMPT	6

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed962b2_31c4823={atv_COLOR_ENUM_89, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bed96654_0bb6784={-1, -1, atv_IDS_INIT_FAC_CHANNEL, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beda2ec1_38a531f={-1, atv_IMG_ID_FS_FACTORY_YELLOW, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08b8c93_3a9780d={-1, -1, atv_IDS_INIT_FAC_CHANNEL, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08b8d4f_0bb927={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c08d89da_37a7c62={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4739a2d_1284823={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed962b2_31c29={{&GUID_bed962b2_31c4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_CONFIG_LABEL_CONFIG"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96654_0bb18be={{&GUID_bed96654_0bb6784, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_CONFIG_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beda8768_3c81b4b={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_GROUP}	"ID_CONFIG_GROUP_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bed96c42_0ab29={{NULL, &GUID_beda2ec1_38a531f, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_CONFIG_PROG_SEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c08b8c93_3a918aa={{&GUID_c08b8c93_3a9780d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_SELECT}	"ID_CONFIG_SELECT_PROG"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c08b8d4f_0bb14db={{&GUID_c08b8d4f_0bb927, &GUID_c08d89da_37a7c62, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_CONFIG_LABEL_PROMPT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4739a2d_12829={{&GUID_c4739a2d_1284823, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_prog_reset_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 485, 660, 0, -1, (D_FrameCtrlDescr*)&GUID_bed962b2_31c29, },
	// [1]ID_CONFIG_LABEL_CONFIG
	{D_CTRL_LABEL, 0, 111, 7, 20, 255, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96654_0bb18be, },
	// [2]ID_CONFIG_GROUP
	{D_CTRL_GROUP, 0, 0, 37, 20, 485, 621, 30, -1, (D_FrameCtrlDescr*)&GUID_beda8768_3c81b4b, },
	// [3]ID_CONFIG_GROUP_1
	{D_CTRL_GROUP, 2, 2, 33, 20, 480, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_bed96c42_0ab29, },
	// [4]ID_CONFIG_PROG_SEL
	{D_CTRL_LABEL, 3, 21, 1, 7, 223, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c08b8c93_3a918aa, },
	// [5]ID_CONFIG_SELECT_PROG
	{D_CTRL_SELECT, 3, 271, 1, 7, 180, 26, 30, 3, (D_FrameCtrlDescr*)&GUID_c08b8d4f_0bb14db, },
	// [6]ID_CONFIG_LABEL_PROMPT
	{D_CTRL_LABEL, 2, 77, 241, 0, 330, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4739a2d_12829, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	prog_reset_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_prog_reset_window[7];
D_Frame prog_reset_window = {
	run_ctrls_prog_reset_window, 
	ctrl_description_of_prog_reset_window, 
	prog_reset_window_init, 
};

