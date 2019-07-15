/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {zhangyp}
	on computer "PRZHANGYP"
	update/create time:	2017-07-19 15:47:15

	Tool info:
	{
		verion:	3.0.0.6
		build-date:	2017-07-18 16:19:49.390

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
enum {
    ID_SIGNAL_GROUP_BACKGROUD = 1,  
#if (defined(D_IUTPUT_SUPPORT_TV))
    ID_SIGNAL_BUTTON_TV          ,  
#endif
#if (defined(D_IUTPUT_SUPPORT_DTV))
    ID_SIGNAL_BUTTON_DTV         ,
#endif
#if (defined(D_IUTPUT_SUPPORT_AV1))
    ID_SIGNAL_BUTTON_AV1         ,
#endif
#if (defined(D_IUTPUT_SUPPORT_AV2))
    ID_SIGNAL_BUTTON_AV2         ,
#endif
#if (defined(D_IUTPUT_SUPPORT_HDMI1))
    ID_SIGNAL_BUTTON_HDMI1       ,
#endif 
#if (defined(D_IUTPUT_SUPPORT_HDMI2))
    ID_SIGNAL_BUTTON_HDMI2       ,
#endif 
#if (defined(D_IUTPUT_SUPPORT_USB))
    ID_SIGNAL_BUTTON_USB         ,
#endif
#ifdef D_TV_MIRACAST_SOURCE
    ID_SIGNAL_BUTTON_WIFIDISPLAY ,
#endif
#ifdef D_TV_LIULINK_SOURCE
    ID_SIGNAL_BUTTON_LIULINK     ,
#endif
   ID_SIGNAL_LABEL_TITLE        ,
    ID_SIGNAL_MAX                = ID_SIGNAL_LABEL_TITLE,
};

#define INPUT_ITEM_HEIGHT 50

#define INPUT_WINDOW_TOP 73

// exclude ID_SIGNAL_LABEL_TITLE and ID_SIGNAL_GROUP_BACKGROUD
#define INPUT_WINDOW_HEIGHT (INPUT_WINDOW_TOP + INPUT_ITEM_HEIGHT * (ID_SIGNAL_MAX - 2))

#define INPUT_ITEM_TOP(item) ((item - ID_SIGNAL_GROUP_BACKGROUD) * INPUT_ITEM_HEIGHT)



//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe021_37a1fc7={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_TV, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe032_29028ea={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE, atv_IDS_TV, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe023_37a3fc7={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_DTV, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe034_29048ea={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE, atv_IDS_DTV, &atv_fmt_center_middle_h00_v00_single_white, };

#if (defined(D_IUTPUT_SUPPORT_AV1)&&defined(D_IUTPUT_SUPPORT_AV2))
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe025_37a5fc7={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_AV1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe036_29068ea={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE, atv_IDS_AV1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe027_37a7fc7={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_AV2, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe038_29088ea={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE, atv_IDS_AV2, &atv_fmt_center_middle_h00_v00_single_white, };
#else
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe025_37a5fc7={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_AV, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe036_29068ea={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE, atv_IDS_AV, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe027_37a7fc7={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_AV, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe038_29088ea={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE, atv_IDS_AV, &atv_fmt_center_middle_h00_v00_single_white, };
#endif
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe029_37a9fc7={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_YPBPR, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe03a_290a8ea={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE, atv_IDS_YPBPR, &atv_fmt_center_middle_h00_v00_single_white, };

#if (defined(D_IUTPUT_SUPPORT_HDMI1)&&defined(D_IUTPUT_SUPPORT_HDMI2))
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe02b_37abfc7={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_HDMI1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe03c_290c8ea={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE, atv_IDS_HDMI1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe02d_37adfc7={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_HDMI2, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe03e_290e8ea={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE, atv_IDS_HDMI2, &atv_fmt_center_middle_h00_v00_single_white, };
#else
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe02b_37abfc7={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_HDMI, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe03c_290c8ea={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE, atv_IDS_HDMI, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe02d_37adfc7={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_HDMI, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe03e_290e8ea={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE, atv_IDS_HDMI, &atv_fmt_center_middle_h00_v00_single_white, };
#endif
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe07f_3a2ffc7={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_USB, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe911_281136a={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE, atv_IDS_USB, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe071_3a2ffc2={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_ZHILIAN_TV, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe912_281136b={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE, atv_IDS_ZHILIAN_TV, &atv_fmt_center_middle_h00_v00_single_white, };
#ifdef D_TV_LIULINK_SOURCE
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe071_3a2fdd2={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_NORMAL, atv_IDS_LIULINK, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe912_2811eeb={-1, atv_IMG_ID_FS_SIGNAL_BUTTON_FOCSE, atv_IDS_LIULINK, &atv_fmt_center_middle_h00_v00_single_white, };
#endif

static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c79fe047_296a8e2={-1, atv_IMG_ID_FS_SIGNAL_BACKGROUND, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c7a03495_1f426e9={-1, -1, atv_IDS_SOURCE, &atv_fmt_center_middle_h00_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c79f9679_17729={{NULL, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_GROUP}	"ID_SIGNAL_GROUP_BACKGROUD"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c79fbd1c_1194ae1={{&GUID_c79fe047_296a8e2, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_BUTTON}	"ID_SIGNAL_BUTTON_TV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c79fbd80_2716952={{&GUID_c79fe021_37a1fc7, &GUID_c79fe032_29028ea, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_SIGNAL_BUTTON_DTV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c79fbe24_3a95af1={{&GUID_c79fe023_37a3fc7, &GUID_c79fe034_29048ea, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_SIGNAL_BUTTON_AV1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c79fbe53_01fbb3={{&GUID_c79fe025_37a5fc7, &GUID_c79fe036_29068ea, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_SIGNAL_BUTTON_AV2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c79fbe94_37a7e87={{&GUID_c79fe027_37a7fc7, &GUID_c79fe038_29088ea, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_BUTTON}	"ID_SIGNAL_BUTTON_YPBPR"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c79fbead_1f4124={{&GUID_c79fe029_37a9fc7, &GUID_c79fe03a_290a8ea, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_BUTTON}	"ID_SIGNAL_BUTTON_HDMI1"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c79fbef7_1f44d06={{&GUID_c79fe02b_37abfc7, &GUID_c79fe03c_290c8ea, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_BUTTON}	"ID_SIGNAL_BUTTON_HDMI2"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c79fbf45_2af39b3={{&GUID_c79fe02d_37adfc7, &GUID_c79fe03e_290e8ea, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_BUTTON}	"ID_SIGNAL_BUTTON_USB"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c79fbf62_2716443={{&GUID_c79fe07f_3a2ffc7, &GUID_c79fe911_281136a, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_BUTTON}	"ID_SIGNAL_BUTTON_WIFIDISPLAY"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c71697f2_2bf6443={{&GUID_c79fe071_3a2ffc2, &GUID_c79fe912_281136b, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
#ifdef D_TV_LIULINK_SOURCE
// definition of [11]{D_CTRL_BUTTON}	"ID_SIGNAL_BUTTON_LIULINK"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c64497f2_2716bf3={{&GUID_c79fe071_3a2fdd2, &GUID_c79fe912_2811eeb, NULL, }, 1, };
#endif


//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_SIGNAL_LABEL_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c79fdf61_14853f={{&GUID_c7a03495_1f426e9, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_signal_select_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1,50, 50, 20, 190, INPUT_WINDOW_HEIGHT, 0, -1, (D_FrameCtrlDescr*)&GUID_c79f9679_17729, },
	// [1]ID_SIGNAL_GROUP_BACKGROUD
	{D_CTRL_GROUP,  0, 0, 0, 20,   190, INPUT_WINDOW_HEIGHT, 30, -1, (D_FrameCtrlDescr*)&GUID_c79fbd1c_1194ae1, },
#if (defined(D_IUTPUT_SUPPORT_TV))	
	// [2]ID_SIGNAL_BUTTON_TV
	{D_CTRL_BUTTON, 1, 0, INPUT_ITEM_TOP(ID_SIGNAL_BUTTON_TV),  -2, 190, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_c79fbd80_2716952, },
#endif
#if (defined(D_IUTPUT_SUPPORT_DTV))
	// [3]ID_SIGNAL_BUTTON_DTV
	{D_CTRL_BUTTON, 1, 0, INPUT_ITEM_TOP(ID_SIGNAL_BUTTON_DTV), -2, 190, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_c79fbe24_3a95af1, },
#endif
#if (defined(D_IUTPUT_SUPPORT_AV1))
	// [4]ID_SIGNAL_BUTTON_AV1
	{D_CTRL_BUTTON, 1, 0, INPUT_ITEM_TOP(ID_SIGNAL_BUTTON_AV1), -2, 190, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_c79fbe53_01fbb3, },
#endif
#if (defined(D_IUTPUT_SUPPORT_AV2))
	// [5]ID_SIGNAL_BUTTON_AV2
	{D_CTRL_BUTTON, 1, 0, INPUT_ITEM_TOP(ID_SIGNAL_BUTTON_AV2), -2, 190, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_c79fbe94_37a7e87, },
#endif
#if (defined(D_IUTPUT_SUPPORT_YPBPR))	
	// [6]ID_SIGNAL_BUTTON_YPBPR
	{D_CTRL_BUTTON, 1, 0, INPUT_ITEM_TOP(ID_SIGNAL_BUTTON_YPBPR), -2, 190, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_c79fbead_1f4124, },
#endif
#if (defined(D_IUTPUT_SUPPORT_HDMI1))
	// [7]ID_SIGNAL_BUTTON_HDMI1
	{D_CTRL_BUTTON, 1, 0, INPUT_ITEM_TOP(ID_SIGNAL_BUTTON_HDMI1), -2, 190, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_c79fbef7_1f44d06, },
#endif
#if (defined(D_IUTPUT_SUPPORT_HDMI2))
	// [8]ID_SIGNAL_BUTTON_HDMI2
	{D_CTRL_BUTTON, 1, 0, INPUT_ITEM_TOP(ID_SIGNAL_BUTTON_HDMI2), -2, 190, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_c79fbf45_2af39b3, },
#endif
#if (defined(D_IUTPUT_SUPPORT_USB))	
	// [9]ID_SIGNAL_BUTTON_USB
	{D_CTRL_BUTTON, 1, 0, INPUT_ITEM_TOP(ID_SIGNAL_BUTTON_USB), -2, 190, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_c79fbf62_2716443, },
#endif
#ifdef D_TV_MIRACAST_SOURCE
	// [10]ID_SIGNAL_BUTTON_WIFIDISPLAY
	{D_CTRL_BUTTON, 1, 0, INPUT_ITEM_TOP(ID_SIGNAL_BUTTON_WIFIDISPLAY), -2, 190, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_c71697f2_2bf6443, },
#endif
#ifdef D_TV_LIULINK_SOURCE
	// [11]ID_SIGNAL_BUTTON_LIULINK
	{D_CTRL_BUTTON, 1, 0, INPUT_ITEM_TOP(ID_SIGNAL_BUTTON_LIULINK), -2, 190, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_c64497f2_2716bf3, },
#endif

    
	// [13]ID_SIGNAL_LABEL_TITLE
	{D_CTRL_LABEL, 1, 0, 0, 20, 190, 48, 30, -1, (D_FrameCtrlDescr*)&GUID_c79fdf61_14853f, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	signal_select_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_tvsignal_select_window[13];
D_Frame signal_select_window = {
	run_ctrls_tvsignal_select_window, 
	ctrl_description_of_signal_select_window, 
	signal_select_window_init, 
};

