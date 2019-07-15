/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-05-10 15:04:36

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2019-02-14 16:39:05.650

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
#define	ID_ATV_GROUP_MAINMENU	1
#define	ID_ATV_BUTTON_1	2
#define	ID_ATV_BUTTON_2	3
#define	ID_ATV_BUTTON_4	4
#define	ID_ATV_BUTTON_5	5
#define	ID_ATV_IMAGE_1	6
#define	ID_ATV_IMAGE_2	7
#define	ID_ATV_IMAGE_4	8
#define	ID_ATV_IMAGE_5	9
#define	ID_ATV_IMAGE_6	10
#define	ID_ATV_IMAGE_7	11

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7a1e0ad_2715599={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, -1, &atv_fmt_center_middle_h00_v100_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c70ada1e_2791559={-1, atv_IMG_ID_FS_MAIN_MENU_BUTTON_FOCSE, -1, &atv_fmt_center_middle_h00_v100_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c709155e_27ada19={-1, atv_IMG_ID_FS_SIGNAL_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7a15951_279e0ad={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7a79e01_21595ad={atv_COLOR_ENUM_1, -1, -1, &atv_fmt_center_middle_h00_v62_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a190fa_3d829={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_ATV_GROUP_MAINMENU"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a19579_33c786d={{&GUID_c709155e_27ada19, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_ATV_BUTTON_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a19111_00043a1={{&GUID_c7a1e0ad_2715599, &GUID_c70ada1e_2791559, &GUID_c7a79e01_21595ad, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_ATV_BUTTON_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a19113_31c1262={{&GUID_c7a1e0ad_2715599, &GUID_c70ada1e_2791559, &GUID_c7a79e01_21595ad, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_ATV_BUTTON_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a19114_00043a4={{&GUID_c7a1e0ad_2715599, &GUID_c70ada1e_2791559, &GUID_c7a79e01_21595ad, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_ATV_BUTTON_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9fdb932_191491c={{&GUID_c7a1e0ad_2715599, &GUID_c70ada1e_2791559, &GUID_c7a79e01_21595ad, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_IMAGE}	"ID_ATV_IMAGE_1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a1db6d_0da29={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_IMAGE}	"ID_ATV_IMAGE_2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a1dddf_30d4ae1={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_IMAGE}	"ID_ATV_IMAGE_4"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a1df50_29f5af1={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_IMAGE}	"ID_ATV_IMAGE_5"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c9fdbcab_103e60={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_IMAGE}	"ID_ATV_IMAGE_6"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a1e58d_3d8b14={{&GUID_c7a15951_279e0ad, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_IMAGE}	"ID_ATV_IMAGE_7"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c7a1e619_1862d32={{&GUID_c7a15951_279e0ad, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_main_menu_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 400, 0, 960, 140, 0, -1, (D_FrameCtrlDescr*)&GUID_c7a190fa_3d829, },
	// [1]ID_ATV_GROUP_MAINMENU
	{D_CTRL_GROUP, 0, 0, 0, 420, 960, 140, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a19579_33c786d, },
	// [2]ID_ATV_BUTTON_1
	{D_CTRL_BUTTON, 1, 56, 0, -445, 210, 140, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a19111_00043a1, },
	// [3]ID_ATV_BUTTON_2
	{D_CTRL_BUTTON, 1, 268, 0, -448, 210, 140, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a19113_31c1262, },
	// [4]ID_ATV_BUTTON_4
	{D_CTRL_BUTTON, 1, 480, 0, -448, 210, 140, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a19114_00043a4, },
	// [5]ID_ATV_BUTTON_5
	{D_CTRL_BUTTON, 1, 692, 0, -400, 210, 140, 30, -1, (D_FrameCtrlDescr*)&GUID_c9fdb932_191491c, },
	// [6]ID_ATV_IMAGE_1
	{D_CTRL_IMAGE, 2, 69, 23, 0, 70, 70, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a1db6d_0da29, },
	// [7]ID_ATV_IMAGE_2
	{D_CTRL_IMAGE, 3, 69, 23, 0, 70, 70, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a1dddf_30d4ae1, },
	// [8]ID_ATV_IMAGE_4
	{D_CTRL_IMAGE, 4, 69, 23, 0, 70, 70, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a1df50_29f5af1, },
	// [9]ID_ATV_IMAGE_5
	{D_CTRL_IMAGE, 5, 70, 23, -48, 70, 70, 30, -1, (D_FrameCtrlDescr*)&GUID_c9fdbcab_103e60, },
	// [10]ID_ATV_IMAGE_6
	{D_CTRL_IMAGE, 1, 0, 0, -448, 54, 140, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a1e58d_3d8b14, },
	// [11]ID_ATV_IMAGE_7
	{D_CTRL_IMAGE, 1, 904, 0, -448, 54, 140, 30, -1, (D_FrameCtrlDescr*)&GUID_c7a1e619_1862d32, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_main_menu_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_main_menu_window[12];
D_Frame atv_main_menu_window = {
	run_ctrls_atv_main_menu_window, 
	ctrl_description_of_atv_main_menu_window, 
	atv_main_menu_window_init, 
};

