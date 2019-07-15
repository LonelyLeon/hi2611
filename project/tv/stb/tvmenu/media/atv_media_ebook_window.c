/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {hegx}
	on computer "PRHEGX"
	update/create time:	2014-12-23 15:21:14

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2014-12-16 16:55:09.290

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
#define	ID_EBOOK_GROUP_LIST	1
#define	ID_EBOOK_LABEL_PATH	2
#define	ID_EBOOK_LIST	3
#define	ID_EBOOK_SCROLL	4
#define	ID_EBOOK_IMG_LOGO	5
#define	ID_EBOOK_MOVE_BOTTOM	6
#define	ID_EBOOK_MOVE_ICON	7
#define	ID_EBOOK_MOVE_LABEL	8
#define	ID_EBOOK_OK_BOTTOM	9
#define	ID_EBOOK_OK_ICON	10
#define	ID_EBOOK_OK_0	11

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c0347a_2fd4823={-1, atv_IMG_ID_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c05639_1964823={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c0581b_3c843f7={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c1bc28_37a2cd6={-1, atv_IMG_ID_COMB_music_select, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c1bc28_37a72ae={-1, atv_IMG_ID_COMB_music_select_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c25251_06d70f5={-1, -1, -1, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c25251_06d1477={-1, -1, -1, &atv_fmt_left_middle_h10_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cfb09f_1c54ae1={-1, atv_IMG_ID_hint_button, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cfb108_3b96952={-1, atv_IMG_ID_hint_direction, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cfb163_31c5af1={-1, -1, atv_IDS_MOVE, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cfb219_2517e87={-1, -1, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cfb276_167124={-1, -1, atv_IDS_OK, &atv_fmt_left_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5887323_3d818be={atv_COLOR_ENUM_101, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4cca42c_381bb41={-1, -1, -1, &atv_fmt_left_top_h00_v00_multi_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c0347a_2fd29={{&GUID_c4c0347a_2fd4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_EBOOK_GROUP_LIST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c05639_19629={{&GUID_c4c05639_1964823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_EBOOK_LABEL_PATH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c0581b_3c84612={{&GUID_c4cca42c_381bb41, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LIST}	"ID_EBOOK_LIST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514={{&GUID_c4c1bc28_37a2cd6, &GUID_c4c1bc28_37a72ae, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c05d25_1576816_GUID_c4c25510_33c125e={{NULL, NULL, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080={{&GUID_c4c25251_06d70f5, &GUID_c4c25251_06d1477, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c4c05d25_1575a43[]={
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
};

static PREFIXCONST D_Coord POSTCONST list_ctrl_GUID_c4c05d25_1577c1e[4]={30, 60, 540, 120, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c4c05d25_1571e9e[10][4]=
{
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
};
static PREFIXCONST D_FrameListDescr POSTCONST GUID_c4c05d25_1576816={{NULL, NULL, NULL, }, 1, 10, 10, 10, 4, 40, list_ctrl_GUID_c4c05d25_1577c1e, 8, 0, D_LIST_FOCUS_TYPE_ROW, list_ctrl_GUID_c4c05d25_1571e9e, list_ctrl_GUID_c4c05d25_1575a43, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_SCROLL}	"ID_EBOOK_SCROLL"
static PREFIXCONST D_FrameScrollBarDescr POSTCONST GUID_c4c42754_17718be={{&GUID_c5887323_3d818be, NULL, NULL, }, 1, 100, 10, 1, {-1, -1, -1, atv_IMG_ID_scrool_one, }, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_IMAGE}	"ID_EBOOK_IMG_LOGO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c429f3_1f46c5c={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_EBOOK_MOVE_BOTTOM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cfb09f_1c56784={{&GUID_c4cfb09f_1c54ae1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_EBOOK_MOVE_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cfb108_3b972ae={{&GUID_c4cfb108_3b96952, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_EBOOK_MOVE_LABEL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cfb163_31c6df1={{&GUID_c4cfb163_31c5af1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_EBOOK_OK_BOTTOM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cfb1c4_0fa1eb={{&GUID_c4cfb09f_1c54ae1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_EBOOK_OK_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cfb219_251153c={{&GUID_c4cfb219_2517e87, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_EBOOK_OK_0"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4cfb276_16799={{&GUID_c4cfb276_167124, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_media_ebook_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 1280, 720, 0, -1, (D_FrameCtrlDescr*)&GUID_c4c0347a_2fd29, },
	// [1]ID_EBOOK_GROUP_LIST
	{D_CTRL_GROUP, 0, 230, 134, 20, 820, 505, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c05639_19629, },
	// [2]ID_EBOOK_LABEL_PATH
	{D_CTRL_LABEL, 0, 90, 665, 20, 615, 60, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c0581b_3c84612, },
	// [3]ID_EBOOK_LIST
	{D_CTRL_LIST, 1, 26, 16, 0, 750, 472, 30, 4, (D_FrameCtrlDescr*)&GUID_c4c05d25_1576816, },
	// [4]ID_EBOOK_SCROLL
	{D_CTRL_SCROLL, 1, 800, 16, 0, 5, 470, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c42754_17718be, },
	// [5]ID_EBOOK_IMG_LOGO
	{D_CTRL_IMAGE, 0, 30, 65, 20, 199, 57, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c429f3_1f46c5c, },
	// [6]ID_EBOOK_MOVE_BOTTOM
	{D_CTRL_LABEL, 0, 820, 665, 20, 101, 37, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cfb09f_1c56784, },
	// [7]ID_EBOOK_MOVE_ICON
	{D_CTRL_LABEL, 6, 32, 3, 0, 32, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cfb108_3b972ae, },
	// [8]ID_EBOOK_MOVE_LABEL
	{D_CTRL_LABEL, 0, 929, 669, 20, 64, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cfb163_31c6df1, },
	// [9]ID_EBOOK_OK_BOTTOM
	{D_CTRL_LABEL, 0, 1049, 665, 20, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cfb1c4_0fa1eb, },
	// [10]ID_EBOOK_OK_ICON
	{D_CTRL_LABEL, 9, 2, 3, 0, 96, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cfb219_251153c, },
	// [11]ID_EBOOK_OK_0
	{D_CTRL_LABEL, 0, 1156, 669, 20, 59, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c4cfb276_16799, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_media_ebook_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_media_ebook_window[12];
D_Frame atv_media_ebook_window = {
	run_ctrls_atv_media_ebook_window, 
	ctrl_description_of_atv_media_ebook_window, 
	atv_media_ebook_window_init, 
};

