
#ifndef _D_USB_UPGRADE_H_
#define _D_USB_UPGRADE_H_

#include "dTypes.h"



#define	 UHDR_LENGTH 	sizeof(udf32_uhdr)

#define PHDR_MAX			256
#define REGULAR_EXPRESS_MOD		0
#define EXACT_MATCH_MOD			1
#define USB_FILE_BUFFER_SIZE			0x10000
/** @brief新版本标志@qiny 2017.10.19*/
#define USB_HEADER_VER_NEW	0xFF5AA5FF

typedef D_Size (*USBUPGRADEFLASHERASE)(D_Handle handle, D_Size offset, D_Size size);
typedef D_Size (*USBUPGRADEFLASHWRITE)(D_Handle handle, D_Size offset,D_U8 *buff, D_Size size);

typedef enum
{
	D_USB_AUTO_UPDATE = 0,		/**<严格检查版本信息*/
	D_USB_MANUAL_UPDATE,			/**<忽略版本信息*/
	D_USB_VHW_UPDATE                /**<只检查厂家和硬件信息*/
}D_Usb_UpDate_Mode;

typedef	struct	
{ 	
	D_U32		p_paddr;
	D_U32		p_dsize;				//数据段大小
	D_U32		p_dcrc32;			//数据段校验
}udf32_phdr;

/** @brief 旧结构里u_phdrnum 是U8的，最大是255，即最多只能升级16M - 64K的文件*/
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

/** @brief 新结构可以升级任意大小的文件@qiny 2017.10.19*/
typedef	struct
{ 	
	D_U32		u_hardver;
	D_U32		u_softver;	
	D_U16		u_mcode;
	D_U8		u_pcode;
	D_U8		u_reserved;
	D_U32		u_uhdrver;   /* 对应旧结构里的u_uhdrsize，通过此值来判断新旧版本*/
	D_U32		u_phdrnum; /* U32，兼容大于16M的情况*/
	D_U32		u_uhdrsize;
	udf32_phdr	*u_phd;		/*动态分配，兼容大于16M的情况*/
	D_U32		u_datacrc32;
	D_U32		u_reserved1;
	D_U32		u_reserved2;
	D_U32		u_headercrc32;
}udf32_uhdr;

typedef struct
{
	const char *full_path;//升级的文件全路径
	D_U8 *pbuff;          //升级数据使用的buff
	D_U8 order;           //跟工具配套使用，目前的工具为0
	D_U32 hw_code; //硬件版本号
	D_U32 sw_code; //软件版本号
	D_U16 manu_id; //厂商号    
	D_Handle flashhandle; //flash模块
	USBUPGRADEFLASHERASE flasherasefunc;
	USBUPGRADEFLASHWRITE flashwritefunc;
	D_Usb_UpDate_Mode mode;//升级模式

}D_Usb_Upgrade_Data;

/** @brief Uart错误代码定义				
*/
typedef enum
{
	USB_NO_ERROR = 0,		
	USB_UNFINDDEV_ERROR,	//没有找到usb设备
	USB_CREATE_ERROR,	//创建USB设备出错
	USB_CREATEFILE_ERROR,	//创建文件系统出错		
	USB_OPENFILE_ERROR ,//打开文件失败	
	USB_HEAD_CRC_ERROR,//升级头校验错误
	USB_MANU_ID_ERROR, //厂商号错误
	USB_HWCODE_ERROR,  //硬件版本号错误
	USB_SWHEAD_ERROR,  //区域号错误
	USB_SWCODE_ERROR,  //软件版本号错误
	USB_UNKNOW_ERROR,  //其它错误	
	USB_BUFFLENGTH_ERROR,  //内存错误
	USB_READ_ERROR,  //读取数据错误
	USB_ERASE_ERROR,  //读取数据错误
	USB_WRITE_ERROR,  //读取数据错误
	USB_DATA_CRC_ERROR,//数据校验错误
}D_UsbResultCode;



typedef void (*USBUPGRADEEVENTCALLBACK)(D_U8 event,D_U8 param);


void D_UsbSetEventCB(USBUPGRADEEVENTCALLBACK cb);
D_UsbResultCode start_usb_upgrade(D_Usb_Upgrade_Data config,D_U32 *sw_code)D_FUNCPOSTFIT;
void D_UsbSetEventCB_ex(USBUPGRADEEVENTCALLBACK cb);

#endif
