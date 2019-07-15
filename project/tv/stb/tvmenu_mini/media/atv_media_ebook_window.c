/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {lius}
	on computer "PRLIUS"
	update/create time:	2019-03-01 10:35:14

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2019-01-16 16:05:50.130

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

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c05639_1964823={atv_COLOR_ENUM_90, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c4c0581b_3c843f7={-1, -1, -1, &atv_fmt_left_middle_h00_v00_signal_whilte_scroll_R2L, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c5887323_3d818be={atv_COLOR_ENUM_1, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c85b8900_2035df7={-1, -1, -1, &atv_fmt_left_middle_h10_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c85b8900_203400a={-1, -1, -1, &atv_fmt_left_middle_h10_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c85b92e4_0f06784={-1, atv_IMG_ID_FS_Ebook_List_Select, -1, NULL, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c0347a_2fd29={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_EBOOK_GROUP_LIST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c05639_19629={{&GUID_c4c05639_1964823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_EBOOK_LABEL_PATH"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c0581b_3c84612={{&GUID_c4c0581b_3c843f7, NULL, NULL, }, 0, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LIST}	"ID_EBOOK_LIST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514={{NULL, &GUID_c85b92e4_0f06784, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c05d25_1576816_GUID_c4c25510_33c125e={{NULL, NULL, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080={{&GUID_c85b8900_2035df7, &GUID_c85b8900_203400a, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c4c05d25_1575a43[]={
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
	&GUID_c4c05d25_1576816_GUID_c4c05e6a_2fd514, 
};

static PREFIXCONST D_Coord POSTCONST list_ctrl_GUID_c4c05d25_1577c1e[4]={30, 60, 540, 156, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_c4c05d25_1571e9e[6][4]=
{
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
	{&GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25510_33c125e, &GUID_c4c05d25_1576816_GUID_c4c25246_2ee3080, NULL, },
};
static PREFIXCONST D_FrameListDescr POSTCONST GUID_c4c05d25_1576816={{NULL, NULL, NULL, }, 1, 6, 6, 10, 4, 41, list_ctrl_GUID_c4c05d25_1577c1e, 8, 0, D_LIST_FOCUS_TYPE_ROW, list_ctrl_GUID_c4c05d25_1571e9e, list_ctrl_GUID_c4c05d25_1575a43, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_SCROLL}	"ID_EBOOK_SCROLL"
static PREFIXCONST D_FrameScrollBarDescr POSTCONST GUID_c4c42754_17718be={{&GUID_c5887323_3d818be, NULL, NULL, }, 1, 100, 10, 1, {-1, -1, -1, atv_IMG_ID_v_roll, }, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_media_ebook_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 960, 540, 0, -1, (D_FrameCtrlDescr*)&GUID_c4c0347a_2fd29, },
	// [1]ID_EBOOK_GROUP_LIST
	{D_CTRL_GROUP, 0, 72, 78, 20, 816, 336, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c05639_19629, },
	// [2]ID_EBOOK_LABEL_PATH
	{D_CTRL_LABEL, 0, 84, 51, 20, 792, 24, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c0581b_3c84612, },
	// [3]ID_EBOOK_LIST
	{D_CTRL_LIST, 1, 11, 18, -16, 786, 286, 30, 4, (D_FrameCtrlDescr*)&GUID_c4c05d25_1576816, },
	// [4]ID_EBOOK_SCROLL
	{D_CTRL_SCROLL, 1, 805, 24, -1, 4, 285, 30, -1, (D_FrameCtrlDescr*)&GUID_c4c42754_17718be, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_media_ebook_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_media_ebook_window[5];
D_Frame atv_media_ebook_window = {
	run_ctrls_atv_media_ebook_window, 
	ctrl_description_of_atv_media_ebook_window, 
	atv_media_ebook_window_init, 
};

