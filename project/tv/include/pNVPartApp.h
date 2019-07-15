#ifndef	__NVPART_UPPER_APP_HEADER__
#define	__NVPART_UPPER_APP_HEADER__

#include "dTypes.h"

typedef enum{
	D_LOGO_PART_TYPE_TABLE,
	D_LOGO_PART_TYPE_I,
	D_LOGO_PART_TYPE_GIF,
	D_LOGO_PART_TYPE_BMP	
}D_LogoPartType;

typedef enum{
	D_LOGO_PART_TABLE,
	D_LOGO_PART_LOGO,
	D_LOGO_PART_RADIO,
	D_LOGO_PART_EMERGENCY_BROADCAST,
    D_LOGO_PART_MAX
}D_LogoPartID;

typedef struct{
	D_LogoPartID		id;
	D_LogoPartType		type;
	D_U32			address;
	D_U32			size;
}D_LogoPartInfo;



//--------------����й�����-------------------

//����ļ�����
typedef enum{
	D_AD_FILE_TYPE_I,
	D_AD_FILE_TYPE_MPG,
	D_AD_FILE_TYPE_GIF,
	D_AD_FILE_TYPE_BMP,
	D_AD_FILE_TYPE_OTHER
}D_AdFileType;

//�������
typedef enum{
	D_AD_TYPE_BOOTLOGO,/*�������*/
	D_AD_TYPE_AUDIOBG,
	D_AD_TYPE_EPG,
	D_AD_TYPE_CHANNELLIST,
	D_AD_TYPE_SETTING,
	D_AD_TYPE_MAINMENU,
	D_AD_TYPE_PFBAR,
	D_AD_TYPE_VOLUMEBAR,	
	D_AD_TYPE_OTHER	
}D_AdType;

#define NUM_AD  16

typedef struct{
	D_U32              id;
	D_AdType        adtype;	
	D_AdFileType    filetype;
	D_U32    pos_x;
	D_U32    pos_y;
	D_U32    width;
	D_U32    heigth;
	D_U32    duration_time;
	
	D_U32	address;
	D_U32	size;
}D_ADPartInfo;


//----------------------------------------
/*˽�����ݷ������ݽṹ*/
typedef struct{
	D_Int reserved;
}D_PrivatePartInfo;
/** @brief �õ�ָ��logo  ��Ϣ
* @param logo_id ��Ҫ�õ���Ϣ��Logo ID
* @param logo_info �õ���Ϣ
* @return �ɹ�����D_OK��ʧ�ܷ���D_ERR
*/
D_Result d_nvpart_get_logo_info(D_ID logo_id, D_LogoPartInfo *logo_info);

D_Result app_nvpart_init(void) D_FUNCPOSTFIT;

#endif	//__NVPART_UPPER_APP_HEADER__
