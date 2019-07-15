
#ifndef _D_USB_UPGRADE_H_
#define _D_USB_UPGRADE_H_

#include "dTypes.h"



#define	 UHDR_LENGTH 	sizeof(udf32_uhdr)

#define PHDR_MAX			256
#define REGULAR_EXPRESS_MOD		0
#define EXACT_MATCH_MOD			1
#define USB_FILE_BUFFER_SIZE			0x10000
/** @brief�°汾��־@qiny 2017.10.19*/
#define USB_HEADER_VER_NEW	0xFF5AA5FF

typedef D_Size (*USBUPGRADEFLASHERASE)(D_Handle handle, D_Size offset, D_Size size);
typedef D_Size (*USBUPGRADEFLASHWRITE)(D_Handle handle, D_Size offset,D_U8 *buff, D_Size size);

typedef enum
{
	D_USB_AUTO_UPDATE = 0,		/**<�ϸ���汾��Ϣ*/
	D_USB_MANUAL_UPDATE,			/**<���԰汾��Ϣ*/
	D_USB_VHW_UPDATE                /**<ֻ��鳧�Һ�Ӳ����Ϣ*/
}D_Usb_UpDate_Mode;

typedef	struct	
{ 	
	D_U32		p_paddr;
	D_U32		p_dsize;				//���ݶδ�С
	D_U32		p_dcrc32;			//���ݶ�У��
}udf32_phdr;

/** @brief �ɽṹ��u_phdrnum ��U8�ģ������255�������ֻ������16M - 64K���ļ�*/
typedef	struct
{ 	
	D_U32		u_hardver;
	D_U32		u_softver;	
	D_U16		u_mcode;
	D_U8		u_pcode;
	D_U8		u_phdrnum;
	D_U32		u_uhdrsize;
	udf32_phdr	u_phd[PHDR_MAX];
	D_U32		u_datacrc32;
	D_U32		u_reserved1;
	D_U32		u_reserved2;
	D_U32		u_headercrc32;
}udf32_uhdr_old;

/** @brief �½ṹ�������������С���ļ�@qiny 2017.10.19*/
typedef	struct
{ 	
	D_U32		u_hardver;
	D_U32		u_softver;	
	D_U16		u_mcode;
	D_U8		u_pcode;
	D_U8		u_reserved;
	D_U32		u_uhdrver;   /* ��Ӧ�ɽṹ���u_uhdrsize��ͨ����ֵ���ж��¾ɰ汾*/
	D_U32		u_phdrnum; /* U32�����ݴ���16M�����*/
	D_U32		u_uhdrsize;
	udf32_phdr	*u_phd;		/*��̬���䣬���ݴ���16M�����*/
	D_U32		u_datacrc32;
	D_U32		u_reserved1;
	D_U32		u_reserved2;
	D_U32		u_headercrc32;
}udf32_uhdr;

typedef struct
{
	const char *full_path;//�������ļ�ȫ·��
	D_U8 *pbuff;          //��������ʹ�õ�buff
	D_U8 order;           //����������ʹ�ã�Ŀǰ�Ĺ���Ϊ0
	D_U32 hw_code; //Ӳ���汾��
	D_U32 sw_code; //����汾��
	D_U16 manu_id; //���̺�    
	D_Handle flashhandle; //flashģ��
	USBUPGRADEFLASHERASE flasherasefunc;
	USBUPGRADEFLASHWRITE flashwritefunc;
	D_Usb_UpDate_Mode mode;//����ģʽ

}D_Usb_Upgrade_Data;

/** @brief Uart������붨��				
*/
typedef enum
{
	USB_NO_ERROR = 0,		
	USB_UNFINDDEV_ERROR,	//û���ҵ�usb�豸
	USB_CREATE_ERROR,	//����USB�豸����
	USB_CREATEFILE_ERROR,	//�����ļ�ϵͳ����		
	USB_OPENFILE_ERROR ,//���ļ�ʧ��	
	USB_HEAD_CRC_ERROR,//����ͷУ�����
	USB_MANU_ID_ERROR, //���̺Ŵ���
	USB_HWCODE_ERROR,  //Ӳ���汾�Ŵ���
	USB_SWHEAD_ERROR,  //����Ŵ���
	USB_SWCODE_ERROR,  //����汾�Ŵ���
	USB_UNKNOW_ERROR,  //��������	
	USB_BUFFLENGTH_ERROR,  //�ڴ����
	USB_READ_ERROR,  //��ȡ���ݴ���
	USB_ERASE_ERROR,  //��ȡ���ݴ���
	USB_WRITE_ERROR,  //��ȡ���ݴ���
	USB_DATA_CRC_ERROR,//����У�����
}D_UsbResultCode;



typedef void (*USBUPGRADEEVENTCALLBACK)(D_U8 event,D_U8 param);


void D_UsbSetEventCB(USBUPGRADEEVENTCALLBACK cb);
D_UsbResultCode start_usb_upgrade(D_Usb_Upgrade_Data config,D_U32 *sw_code)D_FUNCPOSTFIT;
void D_UsbSetEventCB_ex(USBUPGRADEEVENTCALLBACK cb);

#endif
