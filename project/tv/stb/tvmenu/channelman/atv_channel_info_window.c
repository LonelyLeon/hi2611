/* !!!!!!!!!!!!!DO NOT MODIFY THIS FILE!!!!!!!!!!!!! 
	This file is produced/modified by {qiny}
	on computer "PRQINY_WIN7"
	update/create time:	2018-05-27 15:59:47

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
#define	ID_CHANNEL_INFO_LABEL_INFO	1
#define	ID_CHANNEL_INFO_GROUP_AV	2
#define	ID_CHANNEL_INFO_LABEL_LEFT	3
#define	ID_CHANNEL_INFO_LABEL_RIGHT	4
#define	ID_CHANNEL_INFO_GROUP_INFO	5
#define	ID_LABEL_NOW_PROGRAM_TIME	6
#define	ID_LABEL_NOW_PRGRAM	7
#define	ID_LABEL_NEXT_PROGRAM_TIME	8
#define	ID_LABEL_NEXT_PROGRAM	9
#define	ID_CHANNEL_INFO_LABEL_INPUT	10
#define	ID_CHANNEL_INFO_LABEL_DATA	11
#define	ID_CHANNEL_INFO_LABEL_VIDEO	12
#define	ID_CHANNEL_INFO_LABEL_AUDIO	13
#define	ID_SELECT_VIDEO_TYPE	14
#define	ID_SELECT_AUDIO_TYPE	15
#define	ID_CHANNEL_INFO_LABEL_ICON	16
#define	ID_CHANNEL_INFO_LABEL_MULTIAUDIO	17
#define	ID_CHANNEL_INFO_LABEL_FREQ	18

//////////////////////////////////////////////////////////////////////////
// attributes
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56c53ed_02e7be={-1, atv_IMB_ID_COMB_white_background, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56c55c9_01f4465={-1, -1, -1, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56c5ad5_1281182={-1, atv_IMG_ID_FS_program_info_backplane, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56c5b59_06d6170={-1, atv_IMG_ID_program_info_direction_left, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56c5bfa_3992cb2={-1, atv_IMG_ID_program_info_direction_right, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56c5d1b_2036713={-1, atv_IMG_ID_FS_program_info_backplane, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c56c86b2_2bf587d={-1, -1, atv_IDS_DTV, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c33ee960_1963d6c={-1, -1, atv_IDS_VIDEO_FRMART, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c33ee9c2_2422cd6={-1, -1, atv_IDS_AUDIO_FRMART, &atv_fmt_center_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c33f8961_2036952={-1, atv_IMG_ID_Blue, -1, NULL, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c33f8a5f_2fd5af1={-1, -1, atv_IDS_MULTI_AUDIO, &atv_fmt_left_middle_h00_v00_single_black, };
static PREFIXCONST D_CtrlAttribute POSTCONST GUID_c8205f26_0af6952={-1, -1, atv_IDS_FREQ, &atv_fmt_left_middle_h05_v00_single_black, };

//////////////////////////////////////////////////////////////////////////
// sub-description of frame controls
//////////////////////////////////////////////////////////////////////////
// definition of [0]{D_CTRL_WINDOW}	"canvas"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c53ed_02e6c41={{&GUID_c56c53ed_02e7be, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [1]{D_CTRL_LABEL}	"ID_CHANNEL_INFO_LABEL_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c55c9_01f60ac={{&GUID_c56c55c9_01f4465, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [2]{D_CTRL_GROUP}	"ID_CHANNEL_INFO_GROUP_AV"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c5ad5_12819a3={{&GUID_c56c5ad5_1281182, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [3]{D_CTRL_LABEL}	"ID_CHANNEL_INFO_LABEL_LEFT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c5b59_06d63c2={{&GUID_c56c5b59_06d6170, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [4]{D_CTRL_LABEL}	"ID_CHANNEL_INFO_LABEL_RIGHT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c5bfa_3996e0b={{&GUID_c56c5bfa_3992cb2, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [5]{D_CTRL_GROUP}	"ID_CHANNEL_INFO_GROUP_INFO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c5d1b_2034a93={{&GUID_c56c5d1b_2036713, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [6]{D_CTRL_LABEL}	"ID_LABEL_NOW_PROGRAM_TIME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c5de8_06d4d0e={{&GUID_c56c55c9_01f4465, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [7]{D_CTRL_LABEL}	"ID_LABEL_NOW_PRGRAM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c5ecd_0ab51e3={{&GUID_c56c55c9_01f4465, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [8]{D_CTRL_LABEL}	"ID_LABEL_NEXT_PROGRAM_TIME"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c5f18_13869d={{&GUID_c56c55c9_01f4465, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [9]{D_CTRL_LABEL}	"ID_LABEL_NEXT_PROGRAM"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c731f_1f435bd={{&GUID_c56c55c9_01f4465, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [10]{D_CTRL_LABEL}	"ID_CHANNEL_INFO_LABEL_INPUT"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c56c86b2_2bf6ed0={{&GUID_c56c86b2_2bf587d, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [11]{D_CTRL_LABEL}	"ID_CHANNEL_INFO_LABEL_DATA"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c59e0dec_1861649={{&GUID_c56c55c9_01f4465, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [12]{D_CTRL_LABEL}	"ID_CHANNEL_INFO_LABEL_VIDEO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c33ed209_1195f90={{&GUID_c33ee960_1963d6c, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [13]{D_CTRL_LABEL}	"ID_CHANNEL_INFO_LABEL_AUDIO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c33ed381_3a92ea6={{&GUID_c33ee9c2_2422cd6, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [14]{D_CTRL_SELECT}	"ID_SELECT_VIDEO_TYPE"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c33ef9eb_08c2653={{&GUID_c56c55c9_01f4465, NULL, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [15]{D_CTRL_SELECT}	"ID_SELECT_AUDIO_TYPE"

static PREFIXCONST D_FrameSelectDescr POSTCONST GUID_c33efa34_05d3de0={{&GUID_c56c55c9_01f4465, NULL, NULL, }, 1, 0, NULL, };

//////////////////////////////////////////////////////////////////////////
// definition of [16]{D_CTRL_LABEL}	"ID_CHANNEL_INFO_LABEL_ICON"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c33f8961_20372ae={{&GUID_c33f8961_2036952, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [17]{D_CTRL_LABEL}	"ID_CHANNEL_INFO_LABEL_MULTIAUDIO"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c33f8a5f_2fd6df1={{&GUID_c33f8a5f_2fd5af1, NULL, NULL, }, 1, };

//////////////////////////////////////////////////////////////////////////
// definition of [18]{D_CTRL_LABEL}	"ID_CHANNEL_INFO_LABEL_FREQ"
static PREFIXCONST D_FrameCtrlDescr POSTCONST GUID_c8205f26_0af72ae={{&GUID_c8205f26_0af6952, NULL, NULL, }, 1, };


//////////////////////////////////////////////////////////////////////////
// frame control description arrays
static PREFIXCONST D_FrameControlDescr POSTCONST ctrl_description_of_atv_channel_info_window[]=
{
	// [0]canvas
	{D_CTRL_WINDOW, -1, 50, 514, 0, 1180, 184, 0, -1, (D_FrameCtrlDescr*)&GUID_c56c53ed_02e6c41, },
	// [1]ID_CHANNEL_INFO_LABEL_INFO
	{D_CTRL_LABEL, 0, 33, 11, 20, 416, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56c55c9_01f60ac, },
	// [2]ID_CHANNEL_INFO_GROUP_AV
	{D_CTRL_GROUP, 0, 30, 44, 20, 1100, 42, 30, -1, (D_FrameCtrlDescr*)&GUID_c56c5ad5_12819a3, },
	// [3]ID_CHANNEL_INFO_LABEL_LEFT
	{D_CTRL_LABEL, 2, 400, 4, 0, 20, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c56c5b59_06d63c2, },
	// [4]ID_CHANNEL_INFO_LABEL_RIGHT
	{D_CTRL_LABEL, 2, 700, 4, 0, 20, 36, 30, -1, (D_FrameCtrlDescr*)&GUID_c56c5bfa_3996e0b, },
	// [5]ID_CHANNEL_INFO_GROUP_INFO
	{D_CTRL_GROUP, 0, 30, 98, 20, 1100, 72, 30, -1, (D_FrameCtrlDescr*)&GUID_c56c5d1b_2034a93, },
	// [6]ID_LABEL_NOW_PROGRAM_TIME
	{D_CTRL_LABEL, 5, 24, 8, 0, 130, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56c5de8_06d4d0e, },
	// [7]ID_LABEL_NOW_PRGRAM
	{D_CTRL_LABEL, 5, 158, 8, 0, 935, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56c5ecd_0ab51e3, },
	// [8]ID_LABEL_NEXT_PROGRAM_TIME
	{D_CTRL_LABEL, 5, 24, 42, 0, 130, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56c5f18_13869d, },
	// [9]ID_LABEL_NEXT_PROGRAM
	{D_CTRL_LABEL, 5, 158, 42, 0, 935, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56c731f_1f435bd, },
	// [10]ID_CHANNEL_INFO_LABEL_INPUT
	{D_CTRL_LABEL, 2, 454, 10, 0, 206, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c56c86b2_2bf6ed0, },
	// [11]ID_CHANNEL_INFO_LABEL_DATA
	{D_CTRL_LABEL, 0, 908, 11, 20, 259, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c59e0dec_1861649, },
	// [12]ID_CHANNEL_INFO_LABEL_VIDEO
	{D_CTRL_LABEL, 0, 475, 11, 20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c33ed209_1195f90, },
	// [13]ID_CHANNEL_INFO_LABEL_AUDIO
	{D_CTRL_LABEL, 0, 685, 11, 20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c33ed381_3a92ea6, },
	// [14]ID_SELECT_VIDEO_TYPE
	{D_CTRL_SELECT, 0, 581, 11, 20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c33ef9eb_08c2653, },
	// [15]ID_SELECT_AUDIO_TYPE
	{D_CTRL_SELECT, 0, 790, 11, 20, 100, 26, 30, -1, (D_FrameCtrlDescr*)&GUID_c33efa34_05d3de0, },
	// [16]ID_CHANNEL_INFO_LABEL_ICON
	{D_CTRL_LABEL, 2, 890, 14, 0, 27, 18, 30, -1, (D_FrameCtrlDescr*)&GUID_c33f8961_20372ae, },
	// [17]ID_CHANNEL_INFO_LABEL_MULTIAUDIO
	{D_CTRL_LABEL, 2, 924, 7, 0, 141, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c33f8a5f_2fd6df1, },
	// [18]ID_CHANNEL_INFO_LABEL_FREQ
	{D_CTRL_LABEL, 2, 3, 6, 0, 300, 30, 30, -1, (D_FrameCtrlDescr*)&GUID_c8205f26_0af72ae, },
	{-1}
};

//////////////////////////////////////////////////////////////////////////
// definitions of FRAME entry
extern D_Result	atv_channel_info_window_init  (D_Frame *init) D_FUNCPOSTFIT;
static D_Visual* run_ctrls_atv_channel_info_window[19];
D_Frame atv_channel_info_window = {
	run_ctrls_atv_channel_info_window, 
	ctrl_description_of_atv_channel_info_window, 
	atv_channel_info_window_init, 
};

