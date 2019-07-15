#ifndef _DVTSTCS_STBDataPublic_H_2004_12_31_
#define _DVTSTCS_STBDataPublic_H_2004_12_31_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef  __cplusplus
extern "C" {
#endif


#ifndef BYTE //8bit
#define BYTE unsigned char
#endif
#ifndef WORD //16bit
#define WORD unsigned short
#endif
#ifndef HRESULT
#define	HRESULT long
#endif
#ifndef DWORD
#define DWORD unsigned long
#endif
#ifndef bool //8bit
#define bool unsigned char
#endif
#ifndef NULL
#define NULL 0
#endif
#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif
	
//信号量定义
typedef long  DVTSTC_Semaphore ;

//线程函数地址类型
//typedef void (*pThreadFunc) (void);
	
/*----------------------------------------------------------------------*/
/*                       下面是长度值定义                               */
/*----------------------------------------------------------------------*/

#define DVTSTC_MAXLEN_PINCODE						8		//最长的PIN码长度
#define DVTSTC_LEN_SMARTCARD_SN					64		//最长只能卡序列号长度（外部卡号）

#define DVTSTC_MAXLEN_SERVICEPERECM				10		//每个ECM支持的最大Service数目

#define DVTSTC_MAXLEN_TVSNAME						21		//最长运营商名称长度+\0
#define DVTSTC_MAXLEN_MANUFACTURERNAME			21		//最长的STCS厂商名字长度+\0 
#define DVTSTC_MAXLEN_PRODUCT_NAME				21		//最长的产品名称,最多20个字符+\0
#define DVTSTC_MAXLEN_SERVICE_NAME				21		//最长的业务名称,最多20个字符+\0
#define DVTSTC_MAXLEN_EMAIL_SENDERNAME			11		//E-mail发送者姓名，最多10个字符+\0
#define DVTSTC_MAXLEN_EMAIL_CONTENT				1001	//E-mail最大长度，最多1000个字符+\0
#define DVTSTC_MAXLEN_EMAIL_SHORT_CONTENT		21		//E-mail标题长度，最多20个字符+\0
#define	DVTSTC_MAXNUMBER_TVSID					5		//支持的运营商最大个数

//请求收取私有数据的请求号
#define DVTSTC_STB_ECM_SLOT						1
#define DVTSTC_STB_EMM_Private_SLOT				2
#define DVTSTC_STB_EMM_Public_SLOT					3
#define DVTSTC_STB_EMM_Group_SLOT					4  //for Group Address 
//智能卡状态定义
#define DVTSTCS_SC_OUT								0		//智能卡不在读卡器中
#define DVTSTCS_SC_INIT								1		//智能卡在读卡器中，正在初始化
#define DVTSTCS_SC_IN								2		//智能卡在读卡器中，工作正常

//机卡配对状态定义
#define DVTSTCS_SC_PAIR_OK							0		//智能卡与当前机顶盒配对
#define DVTSTCS_SC_NO_Pairing						1		//智能卡没有与任何机顶盒配对
#define DVTSTCS_SC_PAIR_OTHER						2		//智能卡与当前机顶盒没有配对

//收看级别定义
#define DVTSTCS_Rating_3								3		//3岁
#define DVTSTCS_Rating_4								4		//4岁
#define DVTSTCS_Rating_5								5		//5岁
#define DVTSTCS_Rating_6								6		//6岁
#define DVTSTCS_Rating_7								7		//7岁
#define DVTSTCS_Rating_8								8		//8岁
#define DVTSTCS_Rating_9								9		//9岁
#define DVTSTCS_Rating_10							10		//10岁
#define DVTSTCS_Rating_11							11		//11岁
#define DVTSTCS_Rating_12							12		//12岁
#define DVTSTCS_Rating_13							13		//13岁
#define DVTSTCS_Rating_14							14		//14岁
#define DVTSTCS_Rating_15							15		//15岁
#define DVTSTCS_Rating_16							16		//16岁
#define DVTSTCS_Rating_17							17		//17岁
#define DVTSTCS_Rating_18							18		//18岁

//email 显示信息。
#define DVTSTCS_EMAIL_NEW							0		//新邮件通知
#define DVTSTCS_EMAIL_NEW_NO_ROOM				1		//有新邮件，但Email空间不够
#define DVTSTCS_EMAIL_NONE							0xFF	//隐藏标志

//email 状态。	
#define DVTSTCS_EMAIL_STATUS_INI					0		//初始值
#define DVTSTCS_EMAIL_STATUS_READ					2		//被读过了

//价格类型定义。
#define	TPP_TAP_PRICE								0		//不回传可录像
#define	TPP_NOTAP_PRICE							1		//不回传不可录像
#define	CPP_TAP_PRICE								2		//回传可录像
#define	CPP_NOTAP_PRICE							3		//回传不可录像


/*----------------------------------------------------------------------*/
/*                       下面是返回值定义                               */
/*----------------------------------------------------------------------*/

//机顶盒返回值基值定义
#define DVTSTCERR_BASE_STB						0xF1000000

//返回值定义
#define DVTSTC_OK								0 

#define DVTSTCERR_STB_POINTER_INVALID			(DVTSTCERR_BASE_STB + 1)		//输入的指针无效
#define DVTSTCERR_STB_DATA_LEN_ERROR				(DVTSTCERR_BASE_STB + 2)		//输入的数据长度不合法
#define DVTSTCERR_STB_TVS_NOT_FOUND				(DVTSTCERR_BASE_STB + 3)		//没有找到符合要求的运营商
#define DVTSTCERR_STB_EXCEED_MAX_COUNT			(DVTSTCERR_BASE_STB + 4)		//超过了允许的最大的个数
#define DVTSTCERR_STB_KEY_NOT_FOUND				(DVTSTCERR_BASE_STB + 5)		//没有找到解密密钥
#define DVTSTCERR_STB_PIN_INVALID				(DVTSTCERR_BASE_STB + 6)		//输入的PIN码无效
#define DVTSTCERR_STB_PIN_LOCKED					(DVTSTCERR_BASE_STB + 7)		//PIN码被锁定
#define DVTSTCERR_STB_CMD_INVALID				(DVTSTCERR_BASE_STB + 8)		//MAC校验错误
#define DVTSTCERR_STB_VER_EXPIRED				(DVTSTCERR_BASE_STB + 9)		//输入的版本没有IC卡中的大，即数据已经过期
#define DVTSTCERR_STB_EXCEED_MAX_LEN				(DVTSTCERR_BASE_STB + 10)	//运营商的名称超过最大的长度
#define DVTSTCERR_STB_NO_SPACE					(DVTSTCERR_BASE_STB + 11)	//已经没有空间
//#define DVTSTCERR_STB_IS_PAIRED					(DVTSTCERR_BASE_STB + 12)	//智能卡与当前机顶盒对应
#define DVTSTCERR_STB_NOT_PAIRED					(DVTSTCERR_BASE_STB + 13)	//智能卡与当前机顶盒没有对应
//#define DVTSTCERR_STB_COUNT_ISZERO				(DVTSTCERR_BASE_STB + 14)	//输入的Count为0. 
#define DVTSTCERR_STB_WORKTIME_INVALID			(DVTSTCERR_BASE_STB + 15)	//工作时段设置不合法，可能是时间不在00:00:00~23:59:59之间，或者开始时间大于结束时间。
//#define	DVTSTCERR_STB_OVERFLOW					(DVTSTCERR_BASE_STB + 16)	
#define	DVTSTCERR_STB_CARD_INVALID				(DVTSTCERR_BASE_STB + 17)	//智能卡无效
#define	DVTSTCERR_STB_Rating_LOW					(DVTSTCERR_BASE_STB + 18)	//智能卡设置的收看级别比当前收看的节目低
#define DVTSTCERR_STB_UNKNOWN					(DVTSTCERR_BASE_STB + 19)	//未知错误，STB不做任何提示，可通过卡复位恢复。

//#define	DVTSTCERR_STB_EMAILBOX_EMPTY				(DVTSTCERR_BASE_STB + 20)	//E-mail信箱为空
#define	DVTSTCERR_STB_NO_EMAIL					(DVTSTCERR_BASE_STB + 21)	//没有此E-mail
#define	DVTSTCERR_STB_EMAILBOX_FULL				(DVTSTCERR_BASE_STB + 22)	//E-mail信箱满
//#define	DVTSTCERR_STB_NO_SECTION					(DVTSTCERR_BASE_STB + 23)	//没有收到完整Section

#define DVTSTCERR_STB_MONEY_LACK					(DVTSTCERR_BASE_STB + 24)	//余额不多，只在预订时会返回该错误，需要提示用户"预订成功，但余额不多，请及时充值"。
#define DVTSTCERR_STB_PROD_NOT_FOUND				(DVTSTCERR_BASE_STB + 25)	//产品未找到
#define DVTSTCERR_STB_OPER_INVALID				(DVTSTCERR_BASE_STB + 26)	//产品已存在，不能操作
#define DVTSTCERR_STB_NEED_PIN_PASS				(DVTSTCERR_BASE_STB + 27)	//需要PIN验证通过
#define DVTSTCERR_STB_IC_COMMUNICATE				(DVTSTCERR_BASE_STB + 28)	//与IC卡通讯错误
#define DVTSTCERR_STB_SLOT_NOT_FOUND				(DVTSTCERR_BASE_STB + 29)	//运营商钱包没有发现
#define DVTSTCERR_STB_PRICE_INVALID				(DVTSTCERR_BASE_STB + 30)	//价格无效
#define DVTSTCERR_STB_PRODUCT_EXPIRED			(DVTSTCERR_BASE_STB + 31)	//产品已经过期

//xb:20050617 ++
#define DVTSTCERR_STB_EXPIRED					(DVTSTCERR_BASE_STB + 33)	//产品已经过期
#define DVTSTCERR_IPPREC_NOT_FOUND				(DVTSTCERR_BASE_STB + 34)	//IPP记录不存在
#define DVTSTCERR_TIME_INVALID					(DVTSTCERR_BASE_STB + 35)	//当前时间无效
#define DVTSTCERR_NOT_BOOKED						(DVTSTCERR_BASE_STB + 37)	//产品未预定
#define DVTSTCERR_CONFIRMED						(DVTSTCERR_BASE_STB + 38)	//产品已经确认
#define DVTSTCERR_UNCONFIRMED					(DVTSTCERR_BASE_STB + 39)	//产品已经取消确认
#define DVTSTCERR_INPUT_DATA_INVALID				(DVTSTCERR_BASE_STB + 40)	//输入的数据无效

#define DVTSTCERR_TERMINAL_NOT_ACTIVATE		(DVTSTCERR_BASE_STB + 51)	//终端未激活
#define DVTSTCERR_TERMINAL_NOT_SERVER			(DVTSTCERR_BASE_STB + 52)	//终端被禁用
#define DVTSTCERR_FREEPREVIEW_OVER				(DVTSTCERR_BASE_STB + 53)	//本次免费预览已结束
#define DVTSTCERR_FREEPREVIEW_ALLOVER			(DVTSTCERR_BASE_STB + 54)	//预览总次数已到
#define DVTSTCERR_AREA_RESTRICT					(DVTSTCERR_BASE_STB + 55)	//运营商限制区域观看
#define DVTSTCERR_NO_ENTITLE						(DVTSTCERR_BASE_STB + 56)	//没有购买此节目Program not paid

//----------------------------------------------
//机顶盒遥控器不能取消的显示信息列表
#define DVTSTC_RATING_TOO_LOW					0			//收看级别不够watching level not enough 
#define DVTSTC_NOT_IN_WATCH_TIME					1			//不在收看时段内Not in working period
#define DVTSTC_NO_ENTITLE						5			//没有购买此节目Program not paid
#define DVTSTC_PRODUCT_RESTRICT					6			//运营商限制观看该节目Program Restricted by Operator
#define DVTSTC_AREA_RESTRICT						7			//运营商限制区域观看Region Restricted by Operator
#define DVTSTC_FREE_PREVIEWING					22			//用户您好，此节目您尚未购买，正在免费预览中This program is not paid, free viewing
//wy:20071022－用户自定义数据类型
#define DVTSTC_BOUQUETID							254			//自定义数据类型-Bouquet_id

//+++++++++++++++++++++++++++++++++STCS新增
#define DVTSTC_TERMINAL_NOT_ACTIVATE			101			//终端未激活terminal is not activated
#define DVTSTC_TERMINAL_NOT_SERVER				102			//终端被禁用terminal is forbidden 
#define DVTSTC_FREEPREVIEW_OVER					103			//本次预览结束preview is over
#define DVTSTC_FREEPREVIEW_ALLOVER				104			//本节目今日预览次数已到today's preview of this program has been used up  
//----------------------------------------------

//kfd:2007-11-16---字符串语言类型
#define DVTSTC_LANG_CHN_SIM						1			//简体中文(默认)
#define DVTSTC_LANG_ENG							2			//英文

/*----------------------------------------------------------------------*/
/*                       下面是一些数据结构定义                         */
/*----------------------------------------------------------------------*/

typedef struct _SDVTSTCPin{
	BYTE	m_byLen;
	BYTE	m_byszPin[DVTSTC_MAXLEN_PINCODE];
}SDVTSTCPin;

typedef struct _SDVTSTCManuInfo{
	DWORD	m_dwCardID;											//卡内部ID
	DWORD	m_dwSTBSTCSVer;										//机顶盒STCS模块的版本号
	char	m_szSCSTCSManuName[DVTSTC_MAXLEN_MANUFACTURERNAME];	//STCS供应商的名称
}SDVTSTCManuInfo;

typedef struct _SDVTSTCTvsInfo{
	WORD	m_wTVSID; 											//运营商的外部编号
	char	m_szTVSName[DVTSTC_MAXLEN_TVSNAME];					//运营商名称
}SDVTSTCTvsInfo;

typedef struct _SDVTSTCServiceEntitle{
	WORD 	m_wProductID;										//产品ID
	DWORD	m_tEntitleTime;										//授权时间，time_t格式。
	DWORD	m_tStartTime;										//开始时间，time_t格式。
	DWORD	m_tEndTime;											//结束时间，time_t格式。
	char	m_szProductName[DVTSTC_MAXLEN_PRODUCT_NAME];			//产品名称
	bool	m_bTapingFlag;										//录像标识。
}SDVTSTCServiceEntitle;											//普通产品授权

typedef struct _SDVTSTCServiceInfo{
	WORD 	m_wEcmPid;											//加扰的ECMPID
	WORD 	m_wServiceID;										//所处频道的ServiceID
}SDVTSTCServiceInfo;

typedef struct _SDVTSTCEmailInfo{
	DWORD	m_dwVersion;										//发送时间
	char	m_szSenderName[DVTSTC_MAXLEN_EMAIL_SENDERNAME];		//发送者姓名
	BYTE	m_Status;											//邮件的状态，为DVTSTCS_EMAIL_STATUS_宏中的一种
	WORD	m_wEmailLength;										//邮件内容长度
	char	m_szTitle[DVTSTC_MAXLEN_EMAIL_SHORT_CONTENT];		//邮件短内容，厂家需要对该内容的编码格式进行校验
}SDVTSTCEmailInfo;

typedef struct _SDVTSTCEmailContent{
	DWORD	m_dwVersion;										//发送时间
	WORD	m_wEmailLength;										//邮件内容长度
	char	m_szEmail[DVTSTC_MAXLEN_EMAIL_CONTENT];				//邮件内容
}SDVTSTCEmailContent;

typedef struct _SDVTSTCIpp{
	WORD	m_wTVSID;					//运营商编号
	WORD	m_wProdID;					//产品ID
	BYTE	m_bySlotID;					//钱包ID
	char	m_szProdName[DVTSTC_MAXLEN_PRODUCT_NAME];	//产品名称
	DWORD	m_tStartTime;				//开始时间，time_t格式。
	DWORD	m_dwDuration;				//持续秒数
	char	m_szServiceName[DVTSTC_MAXLEN_SERVICE_NAME];	//业务名称
	WORD	m_wCurTppTapPrice;			//当前的不回传、能录像价格(分)，价格类型值为0
	WORD	m_wCurTppNoTapPrice;		//当前的不回传、不可录像价格(分)，价格类型值为1
	WORD	m_wCurCppTapPrice;			//当前的要回传、能录像价格(分)，价格类型值为2
	WORD	m_wCurCppNoTapPrice;		//当前的要回传、不可录像价格(分)，价格类型值为3
	WORD	m_wBookedPrice;			//已经预订的价格(分)
	BYTE	m_byBookedPriceType;		//已经预订的价格类型，取值范围0~3
	BYTE	m_byBookedInterval;		//预订收费间隔
	BYTE	m_byCurInterval;			//当前收费间隔
	BYTE	m_byIppStatus;				//Ipp产品状态
	BYTE	m_byUnit;					//收费间隔的单位0 -分钟1-小时2-天3-月4-年
	WORD	m_wIpptPeriod; 			//用户订购IPPT的观看周期数,for Philippines LongIPPT。
}SDVTSTCIpp;

typedef struct _SDVTSTCViewedIpp{
	WORD	m_wTVSID;											//运营商编号
	char	m_szProdName[DVTSTC_MAXLEN_PRODUCT_NAME];		//产品名称
	DWORD	m_tStartTime;						//开始时间，time_t格式。
	DWORD	m_dwDuration;						//持续秒数
	WORD	m_wBookedPrice;						//预订价格(分)
	BYTE	m_byBookedPriceType;					//预订价格类型：0:TppTap;1:TppNoTap;2:CppTap;3:CppNoTap;
	BYTE	m_byBookedInterval;					//预订收费间隔
	char   	m_szOtherInfo[44];					//ippv时为“此产品为ippv产品”，ippt时为“观看总时间：？分钟，扣钱总数：？分”
	BYTE	m_byUnit;						//收费单位，0 -分钟1-小时2-天3-月4-年
}SDVTSTCViewedIpp;

typedef struct _SDVTCAStationInfo{
	DWORD		m_dwCardArea;			//卡的区域码
	DWORD		m_tSetCardAreaTime;		//STCS中为0，设定区域时间。
	BYTE		m_byStartFlag;			//STCS中为0，启动标志。1:启动；0:没有。
	DWORD		m_tSetFlagTime;			//STCS中为0，设置标志时间。
	DWORD		m_tSetStreamTime;		//STCS中为0，设置特征码流的时间。(收到区域码流时间)
	DWORD		m_dwIntervalTime;		//STCS中为0，卡中当前时间减去特征码时间的最大值。
	DWORD		m_dwStreamMinArea;		//STCS中为0，码流的最小区域码
	DWORD		m_dwStreamMaxArea;		//STCS中为0，码流的最大区域码
}SDVTCAStationInfo;

typedef struct _SDVTSTCEmailMsg{
	DWORD		m_dwVersion;										//发送时间
	char		m_szSenderName[DVTSTC_MAXLEN_EMAIL_SENDERNAME];	//发送者姓名
	WORD		m_wEmailLength;									//邮件内容长度
	char		m_szEmail[DVTSTC_MAXLEN_EMAIL_CONTENT];			//邮件内容
}SDVTSTCEmailMsg;

typedef struct _SDVTSTCCharaterFingerMsg{
	bool    m_bVisionType;			//可视类型（0-Covert，1-Overt），covert时，duration不生效。
	BYTE	m_byszContent[8];		//指纹字符内容
	WORD	m_wDuration;			//指纹显示时间长度，-1代表始终显示。
	BYTE	m_byLocationFromTop;	//指纹左上角距离屏幕顶端位置(所占高度比例)。如果位置随机，值为-1；否则取值范围0-100。
	BYTE	m_byLocationFromLeft;	//指纹左上角距离屏幕左端位置（所占宽度比例）。如果位置随机，值为-1；否则取值范围0-100。
	BYTE	m_bySize;				//字符指纹宽度所占屏幕宽度比例；取值范围0-100。
	DWORD	m_dwFontARGB;			//字体透明度（1字节）+字体颜色，三基色
	DWORD	m_dwBackgroundARGB; 	//背景透明度（1字节）+背景颜色，三基色
	BYTE	m_byFontType;			//字体类型
}SDVTSTCCharaterFingerMsg;

typedef struct _SDVTSTCDotMatrixFingerMsg {
	bool    m_bVisionType;			//可视类型（0-Covert，1-Overt）.covert时，duration不生效。
	BYTE	m_byszContent[10];	//10个字节共80bit，前77个bit有效。
	WORD	m_wDuration;			//指纹显示时间长度，-1代表始终显示。
	BYTE	m_byLocationFromTop;	//指纹左上角距离屏幕顶端位置(所占高度比例)。如果位置随机，值为-1；否则取值范围0-100。
	BYTE	m_byLocationFromLeft;	//指纹左上角距离屏幕左端位置（所占宽度比例）。如果位置随机，值为-1；否则取值范围0-100。
	BYTE	m_bySize;				//点阵指纹面积所占屏幕比例；取值范围0-100。
	DWORD	m_dwFontARGB;			//点的透明度（1字节）+点的颜色，三基色
}SDVTSTCDotMatrixFingerMsg;
#ifdef  __cplusplus
}
#endif

#endif	
