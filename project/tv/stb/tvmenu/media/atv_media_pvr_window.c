/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY"
	update/create time:	2017-11-16 19:13:04

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-04-06 16:33:25.000

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
#define	ID_PVR_GROUP_ALL	1
#define	ID_MEDIA_LABEL_WINDOW	2
#define	ID_MEDIA_LABEL_SHOW	3
#define	ID_MEIDA_LABEL_NAME	4
#define	ID_MEDIA_PVR_GROUP	5
#define	ID_MEDIA_PVR_LIST	6
#define	ID_MEDIA_PVR_SCROOL	7
#define	ID_MEDIA_PVR_LABEL_BACK	8
#define	ID_MEDIA_PVR_LABEL_BACK_TITLE	9
#define	ID_MEDIA_PVR_LABEL_MOVE	10
#define	ID_MEDIA_PVR_LABEL_MOVE_TITLE	11
#define	ID_MEDIA_PVR_TITLE	12
#define	ID_PVR_DELETE_ICON	13
#define	ID_PVT_DELETE_INFO	14

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beffae8c_3994823={-1, atv_IMG_ID_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beffb07b_1e419bc={-1, atv_IMB_ID_COMB_small_window, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beffb19a_1a56e90={atv_COLOR_ENUM_0, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beffb221_1a56868={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beffb39f_2224f98={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beffb5bb_25129e8={-1, atv_IMG_ID_COMB_music_select, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beffb5bb_2515f7={-1, atv_IMG_ID_COMB_music_select_focus, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beffb664_27117bc={atv_COLOR_ENUM_2, -1, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beffb802_2ee133c={-1, atv_IMG_ID_FS_Move, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beffb875_23260b9={-1, -1, atv_IDS_MOVE, &atv_fmt_left_middle_h05_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beffb8cb_37a2a50={-1, atv_IMG_ID_hint_button, atv_IDS_OK, &atv_fmt_center_middle_h00_v00_single_grey, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_beffb96d_02e50bd={-1, -1, atv_IDS_OK, &atv_fmt_left_middle_h05_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf016e26_1d44778={-1, -1, -1, &atv_fmt_left_middle_h20_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf01871c_36b3412={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c475ff14_232281e={-1, atv_IMG_ID_Green, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c475ff6b_3c86777={-1, -1, atv_IDS_DELETE_PVR, &atv_fmt_left_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beffae8c_39929={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_PVR_GROUP_ALL"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cabaea42_000656c={{&GUID_beffae8c_3994823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_MEDIA_LABEL_WINDOW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beffb07b_1e47a1a={{&GUID_beffb07b_1e419bc, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_MEDIA_LABEL_SHOW"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beffb19a_1a57fa6={{&GUID_beffb19a_1a56e90, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_MEIDA_LABEL_NAME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beffb221_1a53434={{&GUID_beffb221_1a56868, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_MEDIA_PVR_GROUP"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beffb39f_22256bf={{&GUID_beffb39f_2224f98, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LIST}	"ID_MEDIA_PVR_LIST"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beffb405_06d6a34_GUID_beffb4e3_2fd6387={{&GUID_beffb5bb_25129e8, &GUID_beffb5bb_2515f7, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beffb405_06d6a34_GUID_bf016dd6_2222b7e={{&GUID_bf016e26_1d44778, NULL, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beffb405_06d6a34_GUID_bf016e27_2225fa2={{&GUID_bf01871c_36b3412, NULL, NULL, }, 1, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_beffb405_06d4267[]={
	&GUID_beffb405_06d6a34_GUID_beffb4e3_2fd6387, 
	&GUID_beffb405_06d6a34_GUID_beffb4e3_2fd6387, 
	&GUID_beffb405_06d6a34_GUID_beffb4e3_2fd6387, 
	&GUID_beffb405_06d6a34_GUID_beffb4e3_2fd6387, 
	&GUID_beffb405_06d6a34_GUID_beffb4e3_2fd6387, 
	&GUID_beffb405_06d6a34_GUID_beffb4e3_2fd6387, 
};

static PREFIXCONST D_Coord POSTCONST list_ctrl_GUID_beffb405_06d57cf[2]={80, 270, };
static PREFIXCONST D_FrameCtrlDescr* POSTCONST list_ctrl_GUID_beffb405_06d673f[6][2]=
{
	{&GUID_beffb405_06d6a34_GUID_bf016dd6_2222b7e, &GUID_beffb405_06d6a34_GUID_bf016e27_2225fa2, },
	{&GUID_beffb405_06d6a34_GUID_bf016dd6_2222b7e, &GUID_beffb405_06d6a34_GUID_bf016e27_2225fa2, },
	{&GUID_beffb405_06d6a34_GUID_bf016dd6_2222b7e, &GUID_beffb405_06d6a34_GUID_bf016e27_2225fa2, },
	{&GUID_beffb405_06d6a34_GUID_bf016dd6_2222b7e, &GUID_beffb405_06d6a34_GUID_bf016e27_2225fa2, },
	{&GUID_beffb405_06d6a34_GUID_bf016dd6_2222b7e, &GUID_beffb405_06d6a34_GUID_bf016e27_2225fa2, },
	{&GUID_beffb405_06d6a34_GUID_bf016dd6_2222b7e, &GUID_beffb405_06d6a34_GUID_bf016e27_2225fa2, },
};
static PREFIXCONST D_FrameListDescr POSTCONST GUID_beffb405_06d6a34={{NULL, NULL, NULL, }, 1, 6, 6, 6, 2, 40, list_ctrl_GUID_beffb405_06d57cf, 8, 0, D_LIST_FOCUS_TYPE_ROW, list_ctrl_GUID_beffb405_06d673f, list_ctrl_GUID_beffb405_06d4267, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_SCROLL}	"ID_MEDIA_PVR_SCROOL"
static PREFIXCONST D_FrameScrollBarDescr POSTCONST GUID_beffb664_271c25={{&GUID_beffb664_27117bc, NULL, NULL, }, 1, 100, 10, 1, {-1, -1, -1, atv_IMG_ID_scrool_one, }, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_MEDIA_PVR_LABEL_BACK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beffb802_2ee27c5={{&GUID_beffb802_2ee133c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_MEDIA_PVR_LABEL_BACK_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beffb875_232536b={{&GUID_beffb875_23260b9, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_MEDIA_PVR_LABEL_MOVE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beffb8cb_37a6896={{&GUID_beffb8cb_37a2a50, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_MEDIA_PVR_LABEL_MOVE_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_beffb96d_02e32e0={{&GUID_beffb96d_02e50bd, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_IMAGE}	"ID_MEDIA_PVR_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf009976_10970c0={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_PVR_DELETE_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c475ff14_23262ab={{&GUID_c475ff14_232281e, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_LABEL}	"ID_PVT_DELETE_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c475ff6b_3c822d1={{&GUID_c475ff6b_3c86777, NULL, NULL, }, 0, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_media_pvr_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 0, 0, 0, 1280, 720, 0, -1, (D_FrameCtrlDescr*)&GUID_beffae8c_39929, },
	// [1]ID_PVR_GROUP_ALL
	{D_CTRL_GROUP, 0, 0, 0, 20, 1280, 720, 30, -1, (D_FrameCtrlDescr*)&GUID_cabaea42_000656c, },
	// [2]ID_MEDIA_LABEL_WINDOW
	{D_CTRL_LABEL, 1, 138, 198, 20, 536, 324, 30, -1, (D_FrameCtrlDescr*)&GUID_beffb07b_1e47a1a, },
	// [3]ID_MEDIA_LABEL_SHOW
	{D_CTRL_LABEL, 2, 17, 8, 0, 502, 287, 30, -1, (D_FrameCtrlDescr*)&GUID_beffb19a_1a57fa6, },
	// [4]ID_MEIDA_LABEL_NAME
	{D_CTRL_LABEL, 1, 155, 523, 20, 508, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_beffb221_1a53434, },
	// [5]ID_MEDIA_PVR_GROUP
	{D_CTRL_GROUP, 1, 743, 198, 20, 407, 305, 30, -1, (D_FrameCtrlDescr*)&GUID_beffb39f_22256bf, },
	// [6]ID_MEDIA_PVR_LIST
	{D_CTRL_LIST, 5, 17, 12, 0, 350, 280, 30, 6, (D_FrameCtrlDescr*)&GUID_beffb405_06d6a34, },
	// [7]ID_MEDIA_PVR_SCROOL
	{D_CTRL_SCROLL, 5, 384, 22, 0, 5, 260, 30, -1, (D_FrameCtrlDescr*)&GUID_beffb664_271c25, },
	// [8]ID_MEDIA_PVR_LABEL_BACK
	{D_CTRL_LABEL, 1, 620, 658, 20, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_beffb802_2ee27c5, },
	// [9]ID_MEDIA_PVR_LABEL_BACK_TITLE
	{D_CTRL_LABEL, 1, 728, 664, 20, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_beffb875_232536b, },
	// [10]ID_MEDIA_PVR_LABEL_MOVE
	{D_CTRL_LABEL, 1, 836, 658, 20, 100, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_beffb8cb_37a6896, },
	// [11]ID_MEDIA_PVR_LABEL_MOVE_TITLE
	{D_CTRL_LABEL, 1, 944, 664, 20, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_beffb96d_02e32e0, },
	// [12]ID_MEDIA_PVR_TITLE
	{D_CTRL_IMAGE, 1, 34, 65, 20, 220, 60, 30, -1, (D_FrameCtrlDescr*)&GUID_bf009976_10970c0, },
	// [13]ID_PVR_DELETE_ICON
	{D_CTRL_LABEL, 1, 1056, 668, 20, 28, 19, 30, -1, (D_FrameCtrlDescr*)&GUID_c475ff14_23262ab, },
	// [14]ID_PVT_DELETE_INFO
	{D_CTRL_LABEL, 1, 1106, 658, 20, 100, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c475ff6b_3c822d1, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_media_pvr_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_media_pvr_window[15];
D_Frame atv_media_pvr_window = {
	run_ctrls_atv_media_pvr_window, 
	ctrl_description_of_atv_media_pvr_window, 
	atv_media_pvr_window_init, 
};

