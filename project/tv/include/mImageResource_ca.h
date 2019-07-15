#ifndef	__ca_IMG_RESOURCE_HEADER_FILE_PRODUCED_AUTOMATICALLY_BY_GUI_TOOL
#define	__ca_IMG_RESOURCE_HEADER_FILE_PRODUCED_AUTOMATICALLY_BY_GUI_TOOL
#include	"dGuitooldraw.h"
#ifdef	__cplusplus
extern "C" {
#endif//__cplusplus
#define	ca_IMG_ID_START	0x2000
enum{
	//////////////////////////////////////////////////////////////////////////
	// single image resource
	ca_IMG_ID_Yellow=ca_IMG_ID_START,
	ca_IMG_ID_Blue,	//=0x0001,
	ca_IMG_ID_Green,	//=0x0002,
	ca_IMG_ID_Hint_Down,	//=0x0003,
	ca_IMG_ID_Hint_Left,	//=0x0004,
	ca_IMG_ID_Hint_Right,	//=0x0005,
	ca_IMG_ID_Hint_Up,	//=0x0006,
	ca_IMG_ID_Mail,	//=0x0007,
	ca_IMG_ID_Red,	//=0x0008,
	ca_IMG_ID_Preview,	//=0x0009,
	ca_IMG_ID_ENUM_MAX,	//=0x2010,

	//////////////////////////////////////////////////////////////////////////
	// combine image resource
	ca_COMB_ID_ENUM_MAX,

	//////////////////////////////////////////////////////////////////////////
	// userdefine image resource
	ca_IMG_ID_FS_Group_Bg,	//=0x0000,
	ca_IMG_ID_FS_ENUM_MAX,

};

//////////////////////////////////////////////////////////////////////////
// single image resource


PREFIXCONST unsigned char *POSTCONST ca_LoadImageData(int ids, int lanid, int *size);

//////////////////////////////////////////////////////////////////////////
// combine image resource
#define	ca_IMG_ID_COMB_START ca_COMB_ID_ENUM_MAX
typedef enum{
	ca_IID_HOR=0,
	ca_IID_VER=1,
	ca_IID_MAT=2,
	ca_IID_USER=3,
}ca_COMBINE_IMG_TYPE;

const short* ca_LoadCombineImageData(int ids);

//////////////////////////////////////////////////////////////////////////
// userdefine image resource
#define	ca_IMG_ID_FS_START	ca_IMG_ID_FS_Group_Bg

fGuiTool ca_LoadFreeShape(int id, int lanid);

#ifdef	__cplusplus
}
#endif//__cplusplus
#endif//	__ca_IMG_RESOURCE_HEADER_FILE_PRODUCED_AUTOMATICALLY_BY_GUI_TOOL
