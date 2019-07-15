/*************************************************************************************************

File Name      :  hrca_config.h

Description    :  CA configure file

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hanjf

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012.1.13  	hanjf           created             ---

**************************************************************************************************/
#ifndef _HRCA_CONFIG_H_
#define _HRCA_CONFIG_H_

#include <stdint.h>
#include "dMMan.h"
#include "dMutex.h"
#include "dDemux.h"

/******************************************************************************/ 
/***********************************CA选择*************************************/ 
/******************************************************************************/

#define FREEACCESS			 0        // 0           without CA		不带CA
#define CDCA				(1 << 0)  // 1 	        novel-supertv		永新视博
#define DVTCA				(1 << 1)  // 2 	        sumavision		数码视讯
#define CTICA				(1 << 2)  // 4 	        cti			    算通
#define MGCA				(1 << 3)  // 8 	        shadt			    三洲迅驰
#define CHCA				(1 << 4)  // 16 	        changhong		    长虹
#define GYCA				(1 << 5)  // 32 	        geeya			    金亚
#define TRCA				(1 << 6)  // 64 	        trca               腾锐
#define WFCA				(1 << 7)  // 128 	    wfca              万发
#define QZCA				(1 << 8)  // 256 	    qz		         全智
#define XGCA				(1 << 9)  // 512 	    xg			    新光
#define DIVICA				(1 << 10) // 1024        divi			    数视通
#define DSCA				(1 << 11) // 2048        desaica            四川德赛
#define DVNCA               (1 << 12) // 4096        dvnca	              天柏
#define GOSCA               (1 << 13) // 8192        gospe              高斯贝尔
#define ABVCA               (1 << 14) // 16384       abvca			    北京联广视讯
#define UNITENDCA           (1 << 15) // 32768       unitendca	         北京数字太和
#define THTFCA              (1 << 16) // 65536       thtfca	             北京同方凌讯
#define LXDTCA              (1 << 17) // 131072       lxdtca	         力芯
#define YJCA				(1 << 18) // 262144      yjca		      成都英集
#define KVCA				(1 << 19) // 524288      kvca		      金网通
#define GTCA                (1 << 20) // 1048576    gtca                国通
#define XJCA                (1 << 21) // 2097152    xjca                西结
#define SCCA                (1 << 22) // 4194304    scca
#define COLABLECA			(1 << 23) // 8388608    colableca		
#define XSMCA			    (1 << 25) // 33554432  xsmca          杭州芯视猫	

#ifdef D_SYS_SUPPORT_CA_TYPE
#define EMBED_CA            (D_SYS_SUPPORT_CA_TYPE)  //编译的CA类型的定义在platform.cfg文件中
#else
#define EMBED_CA			(CDCA | CTICA | MGCA | DVTCA | WFCA | QZCA | GOSCA | ABVCA | DSCA | XGCA | DIVICA | DVNCA | TRCA | UNITENDCA | THTFCA | LXDTCA | YJCA | KVCA | GTCA | XJCA | SCCA | COLABLECA | XSMCA)
#endif

#define ADVANCED_HEC			  0 //1:带高级安全；0：不带高级安全
#define HR_CA_SCROLL_ON_OFF	      1 //滚动条开关: 1-on 0-off                                                     
#define HR_CA_DEBUG_TIME_RECORD   0  //1:打开换台计时打印 0:关闭换台计时打印 



/******************************************************************************/ 
/****************************各CA库同时使用变量********************************/ 
/******************************************************************************/
typedef void            VOID;  //算通和腾锐同时使用
typedef void*           PVOID; //算通和腾锐同时使用

typedef char	        INT8;   //德赛和数视通同时使用
typedef unsigned char	UINT8;  //德赛和数视通同时使用
typedef short	        INT16;  //德赛和数视通同时使用
typedef unsigned short	UINT16; //德赛和数视通同时使用
typedef int             INT32;  //德赛和数视通同时使用
typedef unsigned int    UINT32; //德赛和数视通同时使用
typedef unsigned int   	U32;     //腾锐和力芯同时使用
typedef unsigned short  U16;     //腾锐和力芯同时使用
typedef unsigned char   U8;      //腾锐和力芯同时使用

/**********************************END*****************************************/ 

#undef	CA_TRUE
#define CA_TRUE	    1

#undef	CA_FALSE
#define	CA_FALSE	0

/* LC添加 */
#undef  TRUE
#define TRUE		CA_TRUE

#undef  FALSE
#define FALSE		CA_FALSE

typedef unsigned char  	CA_BOOL;

/****************************通道定义********************************/ 

#define EMM_USED_FILTER_CNT	 8     //定义设置EMM过滤器的最大个数
#define DMUX_FORCALIB_CNT 	 8     //CA库自行创建使用的最大dumux个数
#define DATA_TEMP_BUF 	     1024  //存放收到的pmt cat空间大小

typedef struct
{
	/*可以将程序中用到的全局变量放在该结构中*/
	
	D_HMMan 	hmm; 		  /*CA内存管理器*/
	D_Int 		trace_level;  /*打印级别控制*/
	D_HMutex	lock;
	D_HQueue	hq; 	      /*CA APP消息队列句柄*/

	D_HDemux	hcatdemux; 	  /*cat demux句柄*/
	D_HDemux	hpmtdemux;    /*pmt demux句柄*/
	D_HDemux    hemmdemux[EMM_USED_FILTER_CNT];   /*emm demux句柄*/
	D_HDemux    hecmVdemux;   /*ecm video demux句柄*/
	D_HDemux    hecmAdemux;   /*ecm audio demux句柄*/
    D_HDemux    hnitdemux;    /*nit demux句柄*/

    D_U8        ecmVdemuxstart; /*ecm video demux start*/
    D_U8        ecmAdemuxstart; /*ecm Audio demux start*/        
    D_U32       ecmVdemuxtime;  /*ecm video demux start time*/
    D_U32       ecmAdemuxtime;  /*ecm Audio demux start time*/    
}D_CADev;

typedef struct
{
	D_HDemux 		hDemux;      //申请到的dmux设备
	D_DemuxFilter	hFilter;
    uint8_t         hFilterID;
    uint8_t         hUsed;       //0,此过滤器空闲；1，此过滤器已使用
}DemuxFilterFor_CA;

typedef struct
{
    uint8_t            cSlot;     //通道
    uint16_t           cSlotPid;  //通道pid
    uint8_t            cUsed;     //0,此通道空闲，1，此通道已使用
    uint8_t            cReceive;  //0 单次搜表，1，连续搜表
    uint8_t            cCrc;      //0 不校验， 1，校验
    DemuxFilterFor_CA  cDmuxAndFilter[EMM_USED_FILTER_CNT];//通道对应的过滤器
}DemuxFor_CA;

extern D_CADev  ca_dev;           //CA 任务使用的消息队列及demux句柄
extern uint32_t CurCAS;           //当前SMART卡所属的CA厂商

/******************************************************************************/ 
/*********当CA具有不同版本的库时，需要修改相应CA下的宏定义来进行区分***********/ 
/******************************************************************************/

#if ((EMBED_CA & DVTCA) == DVTCA)
//用来区分数码CA的不同版本，打开相应的宏即可
#define DVTCA_HUBEI_JINGZHOU  1       //1--为了湖北荆州项目，添加的特殊功能
#endif

#if ((EMBED_CA  & MGCA) == MGCA)
#ifndef MGCA_VERSION
//#define MGCA_VERSION
//#define MGCA_V312           7
//#define MGCA_V423           8
//#define MGCA_V              MGCA_V423  //三洲迅驰CA不同的CA库版本
#endif
#endif

#if ((EMBED_CA  & DSCA) == DSCA)
#define DSCA_VER4_6		    1
#define DSCA_VER5_1		    2
#define DSCA_VER        	DSCA_VER5_1	//德赛CA不同的CA库版本
#endif

#if ((EMBED_CA  & GOSCA) == GOSCA)
//#ifndef GOSCA_VERSION	
//#define GOSCA_VERSION
//#define GOSCA_V190                 15
//#define GOSCA_V208                 16
//#define GOSCA_V             GOSCA_V208 //高斯贝尔CA不同的CA库版本
//#endif
#define isSTB				1          //区分是机顶盒软件还是小电视软件， 1--STB software 0--TVPad software 
#endif


#if ((EMBED_CA & ABVCA) == ABVCA)
//#define ABVCA_GUANGSHUI           4//广水库
//#define ABVCA_XINYANG             5//信阳库
//#define ABVCA_INDIA               6//印度库
//#define ABVCA_VER        	ABVCA_XINYANG	//联广CA不同的CA库版本
#endif
/*********************************结束*****************************************/

/******************************************************************************/ 
/*******************************返回值定义*************************************/ 
/******************************************************************************/
//机顶盒返回值基值定义
#define CAERR_CDCA_BASE		0x0100
#define CAERR_DVTCA_BASE	0x0200
#define CAERR_CTICA_BASE	0x0300
#define CAERR_MGCA_BASE	    0x0400
#define CAERR_CHCA_BASE	    0x0500
#define CAERR_GYCA_BASE	    0x0600
#define CAERR_TRCA_BASE	    0x0700
#define CAERR_WFCA_BASE	    0x0800
#define CAERR_DVNCA_BASE	0x0900
#define CAERR_ABVCA_BASE	0x0a00
#define CAERR_THTFCA_BASE	0x0b00

//CDCA ERR
#define CA_POINTER_INVALID             (CAERR_CDCA_BASE + 2)   //空指针
#define CA_CARD_INVALID                (CAERR_CDCA_BASE + 3)   //卡无效
#define CA_CARD_PAIROTHER              (CAERR_CDCA_BASE + 4)   //已与其它机顶盒配对
#define CA_CARD_NOPAIR                 (CAERR_CDCA_BASE + 5)   //卡未配对
#define CA_CARD_NO_ROOM                (CAERR_CDCA_BASE + 6)   //卡空间不足
#define CA_CARD_STATUS_OUT             (CAERR_CDCA_BASE + 7)
#define CA_CARD_STATUS_NOT_READY       (CAERR_CDCA_BASE + 8)   //卡未准备好
#define CA_DATA_NOT_FIND 		       (CAERR_CDCA_BASE + 9)   //没有找到数据
#define CA_PIN_INVALID   		       (CAERR_CDCA_BASE + 10)  //pin码无效
#define CA_PIN_LEN_ERR 			       (CAERR_CDCA_BASE + 11)  //pin码长度错误
#define	CA_PIN_LOCKED     		       (CAERR_CDCA_BASE + 12)  //PIN码被锁
#define CA_WATCHRATING_INVALID 	       (CAERR_CDCA_BASE + 13)  //观看级别无效
#define CA_WORKTIME_INVALID 	       (CAERR_CDCA_BASE + 14)  //工作时段错误
#define CA_MONEY_LACK 			       (CAERR_CDCA_BASE + 15)  //钱不多，请充值
#define CA_PROG_STATUS_INVALID 	       (CAERR_CDCA_BASE + 16)
#define CA_FEEDTIME_NOT_ARRIVE         (CAERR_CDCA_BASE + 17)  //喂养时间未到，该子卡不能被喂养


//DVTCA ERR 
#define CA_BOOK_OK                     (CAERR_DVTCA_BASE + 1)   //订购成功
#define CA_UNBOOK_OK                   (CAERR_DVTCA_BASE + 2)   //退订成功
#define CA_ERR_UNBOOK_FAIL    	       (CAERR_DVTCA_BASE + 3)   //退订失败，请再次进入菜单重试
#define CA_ERR_MONEY_LACK              (CAERR_DVTCA_BASE + 4)   //订购成功，但余额不多，请及时充值
#define CA_ERR_NEED_PIN_PASS           (CAERR_DVTCA_BASE + 5)   // 需要通过PIN验证
#define CA_ERR_IC_COMMUNICATE          (CAERR_DVTCA_BASE + 6)   //与IC卡通讯参数错误
#define CA_ERR_TVS_NOT_FOUND           (CAERR_DVTCA_BASE + 7)   //运营商ID无效
#define CA_ERR_SLOT_NOT_FOUND          (CAERR_DVTCA_BASE + 8)   //钱包没有发现

#define CA_ERR_VER_EXPIRED             (CAERR_DVTCA_BASE + 9)   // 产品已经过期
#define CA_ERR_OPER_INVALID            (CAERR_DVTCA_BASE + 10)  // 产品已经存在，不能操作
#define CA_ERR_NO_SPACE                (CAERR_DVTCA_BASE + 11)  //没有空间
#define CA_ERR_PROD_NOT_FOUND          (CAERR_DVTCA_BASE + 12)  // 产品没有发现
#define CA_ERR_PRICE_INVALID           (CAERR_DVTCA_BASE + 13)  //价格无效
#define CA_ERR_PERIOD_INVLIAD          (CAERR_DVTCA_BASE + 14)  //周期数无效
#define CA_ERR_UNKNOWN                 (CAERR_DVTCA_BASE + 15)  //未知错误
#define	CA_ERR_DVT_PIN_LOCKED     	   (CAERR_DVTCA_BASE + 16)  //PIN码被锁


//CTICA ERR
#define CA_ERR_IPP_INVALID             (CAERR_CTICA_BASE + 1)  //ippv节目过期
#define CA_ERR_IPP_PLAY_NOT_SUPPORT    (CAERR_CTICA_BASE + 2)  //点播方式不支持
#define CA_ERR_WORKTIME_SET_TIME       (CAERR_CTICA_BASE + 3)  //准\禁播控制时间设置错误
#define CA_ERR_WORKTIME_SET_TIME_LONG  (CAERR_CTICA_BASE + 4)  //准\禁播控制时间超常
#define CA_ERR_WORKTIME_SET_SLOT       (CAERR_CTICA_BASE + 5)  //准\禁播控制通道设置错误
#define CA_ERR_WORKTIME_SET_MODE       (CAERR_CTICA_BASE + 6)  //准\禁播控制模式设置错误
#define CA_ERR_WORKTIME_SET            (CAERR_CTICA_BASE + 7)  //准\禁播控制模式设置错误

//GYCA ERR
#define	CA_CARD_PAIRCURRENTBOX         (CAERR_GYCA_BASE + 1)   //已配对当前机顶盒
#define CA_BOOK_FAILD		           (CAERR_GYCA_BASE + 2)   //订购失败（余额不足或卡错误）


//DVNCA ERR
#define CA_ERR_SC_COMMUNICATION        (CAERR_DVNCA_BASE + 1)  //机卡通讯错误
#define CA_ERR_SC_NOFUN                (CAERR_DVNCA_BASE + 2)  //智能卡不支持该功能
#define CA_ERR_SC_ERROR                (CAERR_DVNCA_BASE + 3)  //智能卡错误
#define CA_ERR_SC_CAK_STOP             (CAERR_DVNCA_BASE + 4)  //CAK stop
#define CA_ERR_SC_SEM_TIMEOUT          (CAERR_DVNCA_BASE + 5)  //信号量超时
#define CA_ERR_SC_PURSE_LACK           (CAERR_DVNCA_BASE + 6)  //余额不足
#define CA_ERR_SC_PIN_ERROR            (CAERR_DVNCA_BASE + 7)  //错误的PIN
#define CA_ERR_SC_OTHER_ERROR          (CAERR_DVNCA_BASE + 8)  //其他错误

#define CA_ERR_KP_SYSTEM_ERROR         (CAERR_DVNCA_BASE + 9)   //系统错误
#define CA_ERR_KP_PARAMETER_ERROR      (CAERR_DVNCA_BASE + 10)  //参数错误
#define CA_ERR_KP_PIN_LENGHT_INVALID   (CAERR_DVNCA_BASE + 11)  //PIN值长度错误
#define CA_ERR_KP_SAME_PIN             (CAERR_DVNCA_BASE + 12)  //新旧PIN值相同
#define CA_ERR_KP_PIN_ERROR            (CAERR_DVNCA_BASE + 13)  //PIN值错误

//ABVCA ERR
#define CA_PIN_NO_MATCH        		    (CAERR_ABVCA_BASE + 1)  //新密码不匹配
#define CA_OTHER_ERROR                  (CAERR_ABVCA_BASE + 2)  //其他错误
#define CA_CARD_LOCKED                  (CAERR_ABVCA_BASE + 3)  //智能卡锁定
#define CA_PIN_ERROR				    (CAERR_ABVCA_BASE + 4)	//密码错误
#define CA_NO_CARD					    (CAERR_ABVCA_BASE + 5)  //无卡或错误的智能卡
#define CA_BUY_IPPV_ERR			        (CAERR_ABVCA_BASE + 6)  //购买IPPV节目出错

//THTFCA ERR
#define CA_PIN_ERROR_1                  (CAERR_THTFCA_BASE + 1)  // PIN错误，剩余1次机会PIN将会被锁定
#define CA_PIN_ERROR_2                  (CAERR_THTFCA_BASE + 2)  // PIN错误，剩余2次机会PIN将会被锁定
#define CA_PIN_ERROR_3                  (CAERR_THTFCA_BASE + 3)  // PIN错误，剩余3次机会PIN将会被锁定
#define CA_TIME_ERROR                   (CAERR_THTFCA_BASE + 4)  // 时间数据错误
#define CA_TIME_SAME_ERROR              (CAERR_THTFCA_BASE + 5)  // 时间数据错误，开始时间不能与结束时间相同

/*********************************结束*****************************************/

/******************************************************************************/ 
/***************************CA库任务空间大小定义*******************************/ 
/******************************************************************************/

//#define STACK_SIZE_SAFE 			    0
//#define SMART_TASK_STK_SIZE 		    0x600
//#define ECM_STK_SIZE			        0x600//0x800
//#define EMM_STK_SIZE			        0x600//0x800
//#define TASK_URGENCYBROADCAST_STK_SIZE 0x600//4000	   

#if ((EMBED_CA & CDCA) == CDCA)

	//#define CDSM_MSG_STK_SIZE			0x900//0x1100
	//#define CDSM_ECM_STK_SIZE			0x900//0x1100
	//#define CDSM_EMM_STK_SIZE			0x900//0x1100
	//#define CDSM_EMM_REC_STK_SIZE		0x900//0x1100
#endif	

#if ((EMBED_CA & DVTCA) == DVTCA)
	#define DVTSM_ECM_STK_SIZE 		    0x1600
	#define DVTSM_EMM_REC_STK_SIZE 	    0x1200
	#define DVTSM_EMM_STK_SIZE 		    0x1600
	#define DVTSM_OSD_STK_SIZE 		    0x1600
	#define DVTSM_FINGER_STK_SIZE	    0x1000
#endif

#if ((EMBED_CA & CTICA) == CTICA)
	//#define CTICA1_STK_SIZE	        0x500
	//#define CTICA2_STK_SIZE	        0x500
	//#define CTICA3_STK_SIZE	        0x500
	//#define CTICA4_STK_SIZE	        0x500
	//#define CTICA5_STK_SIZE	        0x500
	//#define CTICA6_STK_SIZE	        0x500
	//#define CTICA7_STK_SIZE	        0x500
	//#define CTICA8_STK_SIZE	        0x500
#endif
	
#if ((EMBED_CA & TRCA) == TRCA)
    //#define TRCA1_STK_SIZE	        0x1000//0x1000
    //#define TRCA2_STK_SIZE	        0x1000//0x1000
    //#define TRCA3_STK_SIZE	        0x1800//0x2000
    //#define TRCA4_STK_SIZE	        0x1600//0x2000
#endif
			
#if ((EMBED_CA & MGCA) == MGCA)
	//#define SM_EMM_STK_SIZE			0x1100
	//#define SM_EMM_REC_STK_SIZE		0x1100
#endif
				
#if ((EMBED_CA & WFCA) == WFCA)
	//#define WFCA1_STK_SIZE			0x2000
#endif
					
#if ((EMBED_CA & GYCA) == GYCA)
	//#define SM_CAST_STK_SIZE		    0x3000//0x2000
	//#define SM_SMTT_STK_SIZE		    0x3000
#endif
						
#if ((EMBED_CA & DIVICA) == DIVICA)
	//#define CASC_STK_SIZE 			0x1000
	//#define CACORE_STK_SIZE			0x1000
	//#define CAOSD_STK_SIZE			0x1000
	//#define CAUSER_STK_SIZE			0x1000
#endif
							
#if ((EMBED_CA & DSCA) == DSCA)
	//#define SM_ECM_STK_SIZE	        0x800
	//#define SM_EMM_STK_SIZE           0x800
	//#define SM_SK_STK_SIZE            0x800
	//#define SM_MAIL_STK_SIZE		    0x800
	//#define SM_OSD_STK_SIZE		    0x600
	//#define SM_CONFIG_STK_SIZE		0x600
	//#define SM_OSDDISP_REC_STK_SIZE   0x600
	//#define SM_MONITOR_STK_SIZE	    0x600
#endif
								
#if ((EMBED_CA & DVNCA) == DVNCA)
	//#define CAk_STK_SIZE	0x2000
#endif
									
#if ((EMBED_CA & GOSCA) == GOSCA)
	//#define GOSSM_ECM_STK_SIZE			0x1100
	//#define GOSSM_EMM_STK_SIZE			0x1100
	//#define GOSSM_MONITOR_STK_SIZE		0x1000
	//#define GOSSM_TIMER_STK_SIZE		0x1000
#endif

#if ((EMBED_CA & SCCA) == SCCA)
    #define SCSM_STK_SIZE               0x8000
#endif
/*********************************结束*****************************************/
/******************************************************************************/ 
/******************CA库任务栈定义(for only 2019 or 2016)***********************/ 
/******************************************************************************/
#if 0
#if (EMBED_CA != FREEACCESS)
	extern OS_STK SmartTask_Stk[SMART_TASK_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK EcmTask_Stk[ECM_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK EmmTask_Stk[EMM_STK_SIZE + STACK_SIZE_SAFE];
#endif
										
#if ((EMBED_CA & CDCA) == CDCA)
	extern OS_STK CDCA_Stk4[CDSM_MSG_STK_SIZE + STACK_SIZE_SAFE];      //6k
	extern OS_STK CDCA_Stk1[CDSM_ECM_STK_SIZE + STACK_SIZE_SAFE];      //10k
	extern OS_STK CDCA_Stk3[CDSM_EMM_STK_SIZE + STACK_SIZE_SAFE];      //10k
	extern OS_STK CDCA_Stk5[CDSM_EMM_REC_STK_SIZE + STACK_SIZE_SAFE];  //6k
#endif

#if ((EMBED_CA & DVTCA) == DVTCA)
	extern OS_STK DVTCA_Stk1[DVTSM_ECM_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK DVTCA_Stk2[DVTSM_EMM_REC_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK DVTCA_Stk3[DVTSM_EMM_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK DVTCA_Stk4[DVTSM_OSD_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK DVTCA_Stk5[DVTSM_FINGER_STK_SIZE + STACK_SIZE_SAFE];
#endif
												
#if ((EMBED_CA & CTICA) == CTICA)
	extern OS_STK CTICA_Stk1[CTICA1_STK_SIZE];
	extern OS_STK CTICA_Stk2[CTICA2_STK_SIZE];
	extern OS_STK CTICA_Stk3[CTICA3_STK_SIZE];
	extern OS_STK CTICA_Stk4[CTICA4_STK_SIZE];
	extern OS_STK CTICA_Stk5[CTICA5_STK_SIZE];
	extern OS_STK CTICA_Stk6[CTICA6_STK_SIZE];
	extern OS_STK CTICA_Stk7[CTICA7_STK_SIZE];
	extern OS_STK CTICA_Stk8[CTICA8_STK_SIZE];

	extern void HRCASTB_SetNITData(uint8_t* NitBuffer, uint16_t u16Len);  
#endif
													
#if ((EMBED_CA & WFCA) == WFCA)
	extern OS_STK WFCA_Stk1[WFCA1_STK_SIZE];
#endif
													
#if ((EMBED_CA & TRCA) == TRCA)
	extern OS_STK TRCA_Stk1[TRCA1_STK_SIZE];
	extern OS_STK TRCA_Stk2[TRCA2_STK_SIZE];
	extern OS_STK TRCA_Stk3[TRCA2_STK_SIZE];
	extern OS_STK TRCA_Stk4[TRCA3_STK_SIZE];
#endif
														
#if ((EMBED_CA & GYCA) == GYCA)
	extern OS_STK GYCA_Stk1[SM_CAST_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK GYCA_Stk2[SM_SMTT_STK_SIZE + STACK_SIZE_SAFE];
#endif
															
#if ((EMBED_CA & DIVICA) == DIVICA)
	extern OS_STK CaScStk[CASC_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK CaCoreStk[CACORE_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK CaOsdStk[CAOSD_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK CaUserStk[CAUSER_STK_SIZE + STACK_SIZE_SAFE];
#endif
																
#if ((EMBED_CA & DSCA) == DSCA)
	extern OS_STK     DSCA_Stk1[SM_ECM_STK_SIZE + STACK_SIZE_SAFE];      
	extern OS_STK     DSCA_Stk2[SM_EMM_STK_SIZE + STACK_SIZE_SAFE];      
	extern OS_STK     DSCA_Stk3[SM_SK_STK_SIZE + STACK_SIZE_SAFE];      
	extern OS_STK     DSCA_Stk4[SM_MAIL_STK_SIZE + STACK_SIZE_SAFE];  
	extern OS_STK     DSCA_Stk5[SM_OSD_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK     DSCA_Stk6[SM_CONFIG_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK     DSCA_Stk7[SM_OSDDISP_REC_STK_SIZE + STACK_SIZE_SAFE]; 
 	extern OS_STK	  DSCA_Stk8[SM_MONITOR_STK_SIZE + STACK_SIZE_SAFE];
#endif
																	
#if ((EMBED_CA & DVNCA) == DVNCA)
	extern OS_STK CA_Stk_Cak[CAk_STK_SIZE + STACK_SIZE_SAFE];
#endif
																	
#if ((EMBED_CA & GOSCA) == GOSCA)
	extern OS_STK GOSCA_Stk1[CA_ECM_STK_SIZE + STACK_SIZE_SAFE];
	extern OS_STK GOSCA_Stk2[CA_EMM_STK_SIZE + STACK_SIZE_SAFE]; 
	extern OS_STK GOSCA_Stk3[CA_MONITOR_STK_SIZE + STACK_SIZE_SAFE]; 
	extern OS_STK GOSCA_Stk4[CA_TIMER_STK_SIZE + STACK_SIZE_SAFE];
#endif

#endif
/*********************************结束*****************************************/
//#if ((EMBED_CA & UNITENDCA) == UNITENDCA)
//#include "dca/unitendca_internal.h"
//#include "dca/unitendca_fun.h"
//#endif

/******************************************************************************/ 
/***************************CA数据表ID定义*************************************/ 
/******************************************************************************/

#define CAT_PID                   0x01
#define NIT_ACTUAL_NETWORK_TABLE_ID         0x40
#define NIT_OTHER_NETWORK_TABLE_ID          0x41
#define CAT_TABLE_ID              0x01
#define PMT_TABLE_ID              0x02
#define ECM_TABLE_ID0             0x80
#define ECM_TABLE_ID1             0x81
#define EMM_TABLE_ID2             0x82
#define EMM_TABLE_ID3             0x83
#define EMM_TABLE_ID4             0x84
#define EMM_TABLE_ID5             0x85
#define EMM_TABLE_ID6             0x86
#define EMM_TABLE_ID7             0x87
#define EMM_TABLE_ID8             0x88
#define EMM_TABLE_ID9             0x89
#define EMM_TABLE_IDA             0x8a
#define EMM_TABLE_IDB             0x8b
#define EMM_TABLE_IDC             0x8c
#define EMM_TABLE_IDD             0x8d
#define EMM_TABLE_IDE             0x8e
#define EMM_TABLE_IDF             0x8f
#define EMM_TABLE_ID90            0x90

/*********************************结束*****************************************/

/******************************************************************************/ 
/******************************视频编码定义************************************/ 
/******************************************************************************/

#define CA_MPEG1_VIDEO_STREAM        0x01
#define CA_MPEG2_VIDEO_STREAM        0x02
#define CA_MPEG1_AUDIO_STREAM        0x03
#define CA_MPEG2_AUDIO_STREAM        0x04
#define CA_PRIVATE_DATA_STREAM       0x06

#define CA_iso_iec_14496_10_AVC_VIDEO_STREAM                     0x1B  //h.264  mpeg4	视频
#define CA_iso_iec_14496_2_visual_VIDEO_STREAM                   0x10
#define CA_avs_VIDEO_STREAM                                      0x42  //AVS视频

#define CA_iso_iec_14496_3_audio_w_LATM_transp_AUDIO_STREAM      0x11  //ACC音频
#define CA_iso_iec_13818_7_audio_w_ADTS_transp_AUDIO_STREAM      0x0F  //ACC音频
#define CA_atsc_A_53B_Annex_B_AUDIO_STREAM                       0x81  //AC3音频
#define CA_avs_AUDIO_STREAM                                      0x43  //AVS音频

/*********************************结束*****************************************/

/*********************************其他*****************************************/
#define NO_OF_CRC_DATA_BYTES         4
#define CA_DESC                      0x09
#define MAX_PPID_NUM                 8
/*********************************结束*****************************************/

/******************************************************************************/ 
/******************************fun.c api***************************************/ 
/******************************************************************************/

#if EMBED_CA != FREEACCESS
	extern CA_BOOL HRCA_GetDateStrFromValC (uint16_t wInputDate, char* szOut);
	extern CA_BOOL HRCA_GetTimeStrFromValC (uint32_t nInputTime, char* szOut);
	extern CA_BOOL HRCA_GetTimeStrFromValC1(uint32_t nInputTime, char* szOut);
	extern CA_BOOL HRCA_EmailGetDateStrFromValC (uint16_t wInputDate, char* szOut);
	extern CA_BOOL HRCA_EmailGetTimeStrFromValC(uint32_t nInputTime, char* szOut);
	extern uint32_t HRCA_BCD2dec(uint32_t u32BCD);
    extern void HRTimer_Mjd2ymd(uint16_t MJD, uint32_t *Year, uint32_t *Month, uint32_t *Day);
    extern void HRTimer_dateToMJD(uint8_t mjd[2], uint32_t year, uint32_t month, uint32_t day);
    extern uint8_t* HexStringToBin(int8_t* name, uint32_t num);
    extern uint32_t hex2dec(uint8_t* hex);
  
    extern CA_BOOL  HRCA_FreeProg(void);
    extern CA_BOOL  HRCA_CurCAProg(void);
    extern int16_t HRCA_GetServiceID(void);
    extern int16_t HRCA_GetTSID(void);
    extern int16_t HRCA_GetOrgNetWorkID(void);
    extern uint16_t HRCA_GetNetWorkID(void);
 
#endif
/*********************************结束*****************************************/
#endif
