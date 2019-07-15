/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY"
	update/create time:	2017-11-15 14:12:10

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
#define	ID_TEXTINPUT_LABEL_TITLE	1
#define	ID_TEXTINPUT_LABEL_TEXT	2
#define	ID_TEXTINPUT_BUTTON_00	3
#define	ID_TEXTINPUT_BUTTON_01	4
#define	ID_TEXTINPUT_BUTTON_02	5
#define	ID_TEXTINPUT_BUTTON_03	6
#define	ID_TEXTINPUT_BUTTON_04	7
#define	ID_TEXTINPUT_BUTTON_05	8
#define	ID_TEXTINPUT_BUTTON_06	9
#define	ID_TEXTINPUT_BUTTON_07	10
#define	ID_TEXTINPUT_BUTTON_08	11
#define	ID_TEXTINPUT_BUTTON_09	12
#define	ID_TEXTINPUT_BUTTON_10	13
#define	ID_TEXTINPUT_BUTTON_11	14
#define	ID_TEXTINPUT_BUTTON_12	15
#define	ID_TEXTINPUT_BUTTON_13	16
#define	ID_TEXTINPUT_BUTTON_14	17
#define	ID_TEXTINPUT_BUTTON_15	18
#define	ID_TEXTINPUT_BUTTON_16	19
#define	ID_TEXTINPUT_BUTTON_17	20
#define	ID_TEXTINPUT_BUTTON_18	21
#define	ID_TEXTINPUT_BUTTON_19	22
#define	ID_TEXTINPUT_BUTTON_20	23
#define	ID_TEXTINPUT_BUTTON_21	24
#define	ID_TEXTINPUT_BUTTON_22	25
#define	ID_TEXTINPUT_BUTTON_23	26
#define	ID_TEXTINPUT_BUTTON_24	27
#define	ID_TEXTINPUT_BUTTON_25	28
#define	ID_TEXTINPUT_BUTTON_26	29
#define	ID_TEXTINPUT_BUTTON_27	30
#define	ID_TEXTINPUT_BUTTON_28	31
#define	ID_TEXTINPUT_BUTTON_29	32
#define	ID_TEXTINPUT_BUTTON_30	33
#define	ID_TEXTINPUT_BUTTON_31	34
#define	ID_TEXTINPUT_BUTTON_32	35
#define	ID_TEXTINPUT_BUTTON_33	36
#define	ID_TEXTINPUT_BUTTON_34	37
#define	ID_TEXTINPUT_BUTTON_35	38
#define	ID_TEXTINPUT_BUTTON_36	39
#define	ID_TEXTINPUT_BUTTON_37	40
#define	ID_TEXTINPUT_BUTTON_38	41
#define	ID_TEXTINPUT_BUTTON_39	42
#define	ID_TEXTINPUT_BUTTON_40	43
#define	ID_TEXTINPUT_BUTTON_41	44
#define	ID_TEXTINPUT_BUTTON_42	45
#define	ID_TEXTINPUT_BUTTON_43	46
#define	ID_TEXTINPUT_BUTTON_44	47
#define	ID_TEXTINPUT_BUTTON_45	48
#define	ID_TEXTINPUT_BUTTON_46	49
#define	ID_TEXTINPUT_BUTTON_47	50
#define	ID_TEXTINPUT_BUTTON_48	51
#define	ID_TEXTINPUT_BUTTON_49	52
#define	ID_TEXTINPUT_BUTTON_50	53
#define	ID_TEXTINPUT_BUTTON_51	54
#define	ID_TEXTINPUT_BUTTON_52	55
#define	ID_TEXTINPUT_BUTTON_53	56
#define	ID_TEXTINPUT_BUTTON_54	57

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf41b2e4_0ea4823={-1, atv_IMG_ID_FS_Wifi_password_bg, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf41b811_0fa4823={-1, atv_IMG_ID_FS_Wifi_pw_title, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf41b995_0003d6c={-1, atv_IMG_ID_FS_Wifi_pwkey_normal, -1, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_bf41b995_0002cd6={-1, atv_IMG_ID_FS_Wifi_pwkey_focse, -1, &atv_fmt_center_middle_h00_v00_single_white, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_cab7be93_3b93607={-1, -1, -1, &atv_fmt_center_middle_h00_v00_single_white, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b2e4_0ea29={{&GUID_bf41b2e4_0ea4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_TEXTINPUT_LABEL_TITLE"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_cab7be93_3b948c9={{&GUID_cab7be93_3b93607, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_LABEL}	"ID_TEXTINPUT_LABEL_NAME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b811_0fa29={{&GUID_bf41b811_0fa4823, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_00"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a00={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_01"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a01={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_02"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a02={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_03"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a03={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_04"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a04={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_05"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a05={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_06"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a06={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_07"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a07={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_08"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a08={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_09"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a09={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_10"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a10={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_11"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a11={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_12"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a12={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_13"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a13={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_14"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a14={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_15"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a15={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [19]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_16"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a16={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [20]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_17"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a17={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [21]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_18"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a18={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [22]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_19"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a19={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [23]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_20"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a20={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [24]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_21"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a21={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [25]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_22"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a22={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [26]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_23"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a23={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [27]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_24"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a24={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [28]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_25"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a25={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [29]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_26"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a26={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [30]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_27"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a27={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [31]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_28"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a28={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [32]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_29"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a29={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [33]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_30"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a30={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [34]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_31"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a31={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [35]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_32"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a32={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [36]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_33"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a33={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [37]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_34"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a34={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [38]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_35"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a35={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [39]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_36"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a36={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [40]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_37"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a37={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [41]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_38"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a38={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [42]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_39"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a39={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [43]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_40"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a40={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [44]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_41"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a41={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [45]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_42"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a42={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [46]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_43"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a43={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [47]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_44"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a44={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [48]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_45"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a45={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [49]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_46"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a46={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [50]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_47"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a47={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [51]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_48"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a48={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [52]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_49"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a49={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [53]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_50"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a50={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [54]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_51"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a51={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [55]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_52"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a52={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [56]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_53"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a53={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [57]{D_CTRL_BUTTON}	"ID_TEXTINPUT_BUTTON_54"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_bf41b995_0004a54={{&GUID_bf41b995_0003d6c, &GUID_bf41b995_0002cd6, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_text_input_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 225, 113, 0, 510, 370, 0, -1, (D_FrameCtrlDescr*)&GUID_bf41b2e4_0ea29, },
	// [1]ID_TEXTINPUT_LABEL_TITLE
	{D_CTRL_LABEL, 0, 30, 16, 20, 450, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_cab7be93_3b948c9, },
	// [2]ID_TEXTINPUT_LABEL_NAME
	{D_CTRL_LABEL, 0, 30, 61, 20, 450, 46, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b811_0fa29, },
	// [3]ID_TEXTINPUT_BUTTON_00
	{D_CTRL_BUTTON, 0, 30, 121, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a00, },
	// [4]ID_TEXTINPUT_BUTTON_01
	{D_CTRL_BUTTON, 0, 69, 121, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a01, },
	// [5]ID_TEXTINPUT_BUTTON_02
	{D_CTRL_BUTTON, 0, 108, 121, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a02, },
	// [6]ID_TEXTINPUT_BUTTON_03
	{D_CTRL_BUTTON, 0, 147, 121, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a03, },
	// [7]ID_TEXTINPUT_BUTTON_04
	{D_CTRL_BUTTON, 0, 186, 121, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a04, },
	// [8]ID_TEXTINPUT_BUTTON_05
	{D_CTRL_BUTTON, 0, 225, 121, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a05, },
	// [9]ID_TEXTINPUT_BUTTON_06
	{D_CTRL_BUTTON, 0, 264, 121, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a06, },
	// [10]ID_TEXTINPUT_BUTTON_07
	{D_CTRL_BUTTON, 0, 303, 121, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a07, },
	// [11]ID_TEXTINPUT_BUTTON_08
	{D_CTRL_BUTTON, 0, 342, 121, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a08, },
	// [12]ID_TEXTINPUT_BUTTON_09
	{D_CTRL_BUTTON, 0, 381, 121, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a09, },
	// [13]ID_TEXTINPUT_BUTTON_10
	{D_CTRL_BUTTON, 0, 420, 121, 20, 60, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a10, },
	// [14]ID_TEXTINPUT_BUTTON_11
	{D_CTRL_BUTTON, 0, 30, 167, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a11, },
	// [15]ID_TEXTINPUT_BUTTON_12
	{D_CTRL_BUTTON, 0, 69, 167, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a12, },
	// [16]ID_TEXTINPUT_BUTTON_13
	{D_CTRL_BUTTON, 0, 108, 167, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a13, },
	// [17]ID_TEXTINPUT_BUTTON_14
	{D_CTRL_BUTTON, 0, 147, 167, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a14, },
	// [18]ID_TEXTINPUT_BUTTON_15
	{D_CTRL_BUTTON, 0, 186, 167, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a15, },
	// [19]ID_TEXTINPUT_BUTTON_16
	{D_CTRL_BUTTON, 0, 225, 167, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a16, },
	// [20]ID_TEXTINPUT_BUTTON_17
	{D_CTRL_BUTTON, 0, 264, 167, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a17, },
	// [21]ID_TEXTINPUT_BUTTON_18
	{D_CTRL_BUTTON, 0, 303, 167, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a18, },
	// [22]ID_TEXTINPUT_BUTTON_19
	{D_CTRL_BUTTON, 0, 342, 167, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a19, },
	// [23]ID_TEXTINPUT_BUTTON_20
	{D_CTRL_BUTTON, 0, 381, 167, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a20, },
	// [24]ID_TEXTINPUT_BUTTON_21
	{D_CTRL_BUTTON, 0, 420, 167, 20, 60, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a21, },
	// [25]ID_TEXTINPUT_BUTTON_22
	{D_CTRL_BUTTON, 0, 30, 213, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a22, },
	// [26]ID_TEXTINPUT_BUTTON_23
	{D_CTRL_BUTTON, 0, 69, 213, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a23, },
	// [27]ID_TEXTINPUT_BUTTON_24
	{D_CTRL_BUTTON, 0, 108, 213, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a24, },
	// [28]ID_TEXTINPUT_BUTTON_25
	{D_CTRL_BUTTON, 0, 147, 213, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a25, },
	// [29]ID_TEXTINPUT_BUTTON_26
	{D_CTRL_BUTTON, 0, 186, 213, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a26, },
	// [30]ID_TEXTINPUT_BUTTON_27
	{D_CTRL_BUTTON, 0, 225, 213, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a27, },
	// [31]ID_TEXTINPUT_BUTTON_28
	{D_CTRL_BUTTON, 0, 264, 213, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a28, },
	// [32]ID_TEXTINPUT_BUTTON_29
	{D_CTRL_BUTTON, 0, 303, 213, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a29, },
	// [33]ID_TEXTINPUT_BUTTON_30
	{D_CTRL_BUTTON, 0, 342, 213, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a30, },
	// [34]ID_TEXTINPUT_BUTTON_31
	{D_CTRL_BUTTON, 0, 381, 213, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a31, },
	// [35]ID_TEXTINPUT_BUTTON_32
	{D_CTRL_BUTTON, 0, 420, 213, 20, 60, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a32, },
	// [36]ID_TEXTINPUT_BUTTON_33
	{D_CTRL_BUTTON, 0, 30, 259, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a33, },
	// [37]ID_TEXTINPUT_BUTTON_34
	{D_CTRL_BUTTON, 0, 69, 259, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a34, },
	// [38]ID_TEXTINPUT_BUTTON_35
	{D_CTRL_BUTTON, 0, 108, 259, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a35, },
	// [39]ID_TEXTINPUT_BUTTON_36
	{D_CTRL_BUTTON, 0, 147, 259, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a36, },
	// [40]ID_TEXTINPUT_BUTTON_37
	{D_CTRL_BUTTON, 0, 186, 259, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a37, },
	// [41]ID_TEXTINPUT_BUTTON_38
	{D_CTRL_BUTTON, 0, 225, 259, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a38, },
	// [42]ID_TEXTINPUT_BUTTON_39
	{D_CTRL_BUTTON, 0, 264, 259, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a39, },
	// [43]ID_TEXTINPUT_BUTTON_40
	{D_CTRL_BUTTON, 0, 303, 259, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a40, },
	// [44]ID_TEXTINPUT_BUTTON_41
	{D_CTRL_BUTTON, 0, 342, 259, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a41, },
	// [45]ID_TEXTINPUT_BUTTON_42
	{D_CTRL_BUTTON, 0, 381, 259, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a42, },
	// [46]ID_TEXTINPUT_BUTTON_43
	{D_CTRL_BUTTON, 0, 420, 259, 20, 60, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a43, },
	// [47]ID_TEXTINPUT_BUTTON_44
	{D_CTRL_BUTTON, 0, 30, 305, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a44, },
	// [48]ID_TEXTINPUT_BUTTON_45
	{D_CTRL_BUTTON, 0, 69, 305, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a45, },
	// [49]ID_TEXTINPUT_BUTTON_46
	{D_CTRL_BUTTON, 0, 108, 305, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a46, },
	// [50]ID_TEXTINPUT_BUTTON_47
	{D_CTRL_BUTTON, 0, 147, 305, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a47, },
	// [51]ID_TEXTINPUT_BUTTON_48
	{D_CTRL_BUTTON, 0, 186, 305, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a48, },
	// [52]ID_TEXTINPUT_BUTTON_49
	{D_CTRL_BUTTON, 0, 225, 305, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a49, },
	// [53]ID_TEXTINPUT_BUTTON_50
	{D_CTRL_BUTTON, 0, 264, 305, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a50, },
	// [54]ID_TEXTINPUT_BUTTON_51
	{D_CTRL_BUTTON, 0, 303, 305, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a51, },
	// [55]ID_TEXTINPUT_BUTTON_52
	{D_CTRL_BUTTON, 0, 342, 305, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a52, },
	// [56]ID_TEXTINPUT_BUTTON_53
	{D_CTRL_BUTTON, 0, 381, 305, 20, 32, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a53, },
	// [57]ID_TEXTINPUT_BUTTON_54
	{D_CTRL_BUTTON, 0, 420, 305, 20, 60, 38, 30, -1, (D_FrameCtrlDescr*)&GUID_bf41b995_0004a54, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_text_input_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_text_input_window[58];
D_Frame atv_text_input_window = {
	run_ctrls_atv_text_input_window, 
	ctrl_description_of_atv_text_input_window, 
	atv_text_input_window_init, 
};

