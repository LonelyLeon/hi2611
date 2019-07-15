
/******************************************************************************
 * Copyright (c) 2008, 成都英集电子科技有限公司
 * All rights reserved.
 *
 * 文件名称： YJTypes.h
 * 
 * 概    要:  条件接受系统编程接口。
 *            
 * 
 * 当前版本： 	1.0.0
 *
 * 作    者： 		Matthew
 * 创建日期： 	2008年7月30日
 *
 ******************************************************************************/
#ifndef  _YJTYPES_H_
#define   _YJTYPES_H_ 
#ifdef  __cplusplus
extern "C" {
#endif


#define true           								1                                          
#define false          								0   


#ifndef		bool
#define		bool			unsigned  char 
#endif


#ifndef		NULL
#define		NULL								0
#endif


#define 		CVer
//#define 		DVBC
//#define		DVBS
#define		DMBT
#define		PUBLIVITY_AD								/*挂角广告*/
#define		SWITCH_PRO_AD								/*换台广告*/
#define		DATARADIATE
#define 		SUB_MAIN_CARD_AUTHENTICATION 				/*字母卡认证*/
//#define 		AREAVALIDATE			 					/*区域认证*/
#define 		ONECARDBYONESTB							/*机卡绑定*/
#define 		MAIL_MAX_CAPTIONLEN 				21		/*电子邮件头最大字节数20*/
#define 		MAIL_MAX_CONTENTLEN 				1024+1	/*电子邮件内容最大字节数1024*/
#define 		MAX_ROLLDATA_LEN					1024		/*滚动字幕内容最大字节数1024*/
#define 		STB_SERIAL_NUM_LEN				9			/*STB序列号长度9B*/
#define 		CARD_ID_LEN						10			/*Smart Card ID 10B*/
#define		USER_ID_LEN						8			/*用户号ID 8B*/
#define		MAX_VIDEOPID_NUM					255			/*滚动字幕节目控制的最大数目*/


/*警告信息的提示*/
#define		MESSAGE_CANCEL_TYPE				0x00		/*取消当前的显示*/
#define		MESSAGE_BADCARD_TYPE			0x01		/*无法识别卡，不能使用*/
#define		MESSAGE_EXPICARD_TYPE			0x02		/*智能卡已经过期，请更换新卡*/
#define		MESSAGE_INSERTCARD_TYPE			0x03		/*请插入智能卡*/
#define		MESSAGE_STOP_SERVICE				0x04		/*用户已停机*/
#define		MESSAGE_CONDITIONSTOP_TYPE		0x05		/*条件禁播*/
#define		MESSAGE_PAIRING_TYPE				0x06		/*机卡不匹配*/
#define		MESSAGE_NOENTITLE_TYPE			0x07		/*无有效授权*/
#define		MESSAGE_DECRYPTFAIL_TYPE			0x08		/*节目解密失败*/
#define     	        MESSAGE_ERRREGION_TYPE          		0x09		/*请勿跨区域使用机顶盒*/
#define		MESSAGE_INSERTMAIN_CARD			0x0A		/*请插入母卡认证*/
#define		MSSAGE_CARDINIT_SUCCE			0x0B		/*卡初始化成功*/
#define		MSSAGE_CARDINIT_FAIL				0x0C		/*卡初始化失败*/
#define		MSSAGE_CARD_AUTHENTICAT_FAIL	0x0D		/*字卡认证失败*/
#define		MSSAGE_CARD_AUTHENTICAT_SUCCE 	0x0E		/*子卡认证成功*/
#define		MSSAGE_CARD_SUB_INSERT			0x0F		/*请插入认证子卡*/
#define		MSSAGE_CARD_SUB_CANCEL			0x10		/*子卡取消成功*/
#define		MSSAGE_CARD_SUB_SETUP			0x11		/*子卡设置成功*/
#define		MSSAGE_CARD_MAIN_CONFIR_FAIL	0x12		/*母卡确认失败*/
#define		MSSAGE_CARD_MAIN_CONFIR_SUCCE	0x13		/*母卡确认成功*/
#define		MSSAGE_NOT_YJCA					0x14		/*非英集CA，不能解密节目*/
#define		MSSAGE_CARD_ERROR				0x15		/*卡类型与机顶盒类型不相符*/
#define		MSSAGE_STRING						0xFF

typedef unsigned long long 	UINT64;
//typedef unsigned int   		UINT32;
//typedef unsigned short 	UINT16;
//typedef unsigned char 		UINT8;


typedef long long 			INT64;
//typedef int   				INT32;
//typedef short 			INT16;
//typedef signed char		INT8;


typedef signed long long	__s64;
typedef signed int			__s32;
typedef signed short		__s16;


typedef int  				YJCA_Semaphore ;

#endif
