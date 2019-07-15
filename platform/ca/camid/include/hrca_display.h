/*************************************************************************************************

File Name      :  hrca_display.h

Description    :  External dmux definitions for ca module

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hourn

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-02-02     hourn          created              ---

**************************************************************************************************/
#ifndef _HRCA_DISPLAY_H_
#define _HRCA_DISPLAY_H_

#include <stdint.h>
#include "dCA.h"
#include "dScroll.h"
#include "hrca_config.h"
#if EMBED_CA != FREEACCESS

/************************************************************************************************/
/*************************************Static  Variable  for  CA *******************************************/
/*************************************各平台CA显示部分全局变量声明*******************************************/
/************************************************************************************************/
						
#if ((EMBED_CA & CDCA) == CDCA) 
    #include "../../cdca/include/CDCASS.h"
    #include "dca/cdca_fun.h"
    #include "dca/cdca_internal.h"
    extern D_CAFingerInfo CdcaFinger;
    extern D_CaOSDPreDefined cdca_pre_defined_osds[];
#endif
								
#if ((EMBED_CA & DVTCA) == DVTCA)
    #include "dca/dvtca_fun.h"
    #include "dca/dvtca_internal.h"
    extern D_CaOSDPreDefined dvtca_pre_defined_osds[];
#endif

#if ((EMBED_CA & CTICA) == CTICA)
    #include "../../ctica/include/ctiapi.h"
    #include "dca/ctica_fun.h"
	#include "dca/ctica_internal.h"
	extern D_CaOSDPreDefined ctica_pre_defined_osds[];
	extern D_CAOrdinaryFinger CticaFinger;
#endif
											
#if ((EMBED_CA & MGCA) == MGCA)
	#include "dca/mgca_fun.h"
   	#include "dca/mgca_internal.h"
	extern D_CaOSDPreDefined mgca_pre_defined_osds[];
#endif

#if ((EMBED_CA & GYCA) == GYCA)
	#include "../gyca/include/gyca_fun.h"
	#include "../gyca/include/gyca_internal.h"
#endif

#if ((EMBED_CA & TRCA) == TRCA) 
    #include "../../trca/include/Tr_Cas.h"
    #include "dca/trca_fun.h"
	#include "dca/trca_internal.h"
    extern D_CaOSDPreDefined trca_pre_defined_osds[];
#endif	

#if ((EMBED_CA & WFCA) == WFCA)
	#include "dca/wfca_fun.h"
	extern D_CaOSDPreDefined wfca_pre_defined_osds[];
#endif
													
#if ((EMBED_CA & QZCA) == QZCA)
	#include "dca/qzca_fun.h"
	extern D_CaOSDPreDefined qzca_pre_defined_osds[];
#endif
															
#if ((EMBED_CA & XGCA) == XGCA) 
	#include "dca/xgca_fun.h"
	extern D_CaOSDPreDefined xgca_pre_defined_osds[];
#endif
																
#if ((EMBED_CA & DIVICA) == DIVICA)
    #include "dca/divica_fun.h"
	#include "dca/divica_internal.h"
	extern D_CaOSDPreDefined divica_pre_defined_osds[];

#endif
																	
#if ((EMBED_CA & DSCA) == DSCA)
    #include "dca/dsca_fun.h"
    #include "dca/dsca_internal.h"	
    extern D_CaOSDPreDefined dsca_pre_defined_osds[];
#endif
																		
#if ((EMBED_CA & DVNCA) == DVNCA)
    #include "dca/dvnca_fun.h"
	#include "dca/dvnca_internal.h"
    extern D_CaOSDPreDefined dvnca_pre_defined_osds[];
    extern D_CaOSDPreDefined dvnca_smpair_defined_osds[];
#endif
																			
#if ((EMBED_CA & GOSCA) == GOSCA)
	#include "dca/gosca_internal.h"
    #include "dca/gosca_fun.h"    
    #include "../../gosca/include/GOSCAS_STBDataPublic.h"
	#include "../../gosca/include/GOSCAS_STBInf.h"
	extern D_CaOSDPreDefined gosca_pre_defined_osds[];
#endif

#if ((EMBED_CA & ABVCA) == ABVCA)
    #include "dca/abvca_fun.h"
	#include "dca/abvca_internal.h"
	extern D_CaOSDPreDefined abvca_pre_defined_osds[];
#endif

#if ((EMBED_CA & UNITENDCA) == UNITENDCA)
    #include "dca/unitendca_fun.h"
	#include "dca/unitendca_internal.h"
    #include "../../unitendca/include/udrm.h"
    extern D_CaOSDPreDefined unitendca_pre_defined_osds[];
#endif

#if ((EMBED_CA & THTFCA) == THTFCA)
    #include "dca/thtfca_fun.h"
	#include "dca/thtfca_internal.h"
    extern D_CaOSDPreDefined thtfca_pre_defined_osds[];
#endif

#if ((EMBED_CA & LXDTCA) == LXDTCA)
    #include "dca/lxdtca_fun.h"
	#include "dca/lxdtca_internal.h"
    #include "../../lxdtca/include/LxDtCa_Usr.h"
    extern D_CaOSDPreDefined lxdtca_pre_defined_osds[];
#endif

#if ((EMBED_CA & YJCA) == YJCA)
    #include "dca/yjca_fun.h"
	#include "dca/yjca_internal.h"
    extern D_CaOSDPreDefined yjca_pre_defined_osds[];
#endif

#if ((EMBED_CA & SCCA) == SCCA)
    #include "dca/scca_fun.h"
    #include "dca/scca_internal.h"
    extern D_CaOSDPreDefined scca_pre_defined_osds[];
#endif

#if ((EMBED_CA & COLABLECA) == COLABLECA)
	#include "dca/colableca_fun.h"
	#include "dca/colableca_internal.h"
    extern D_CaOSDPreDefined hcnca_pre_defined_osds[];
	extern uint8_t  feeInfo[100];
#endif

#if ((EMBED_CA & XSMCA) == XSMCA)
	#include "dca/xsmca_fun.h"
	#include "dca/xsmca_internal.h"
    extern D_CaOSDPreDefined xsmca_pre_defined_osds[];
#endif


typedef    enum
{
	CA_EMAIL_NEW_DISP,				// 新邮件提示
	CA_EMAIL_HIDE_DISP,				// 隐藏新邮件提示
	CA_EMAIL_FULL_DISP,				// 邮箱已满
	CA_EMAIL_OSD_DISP
}hrca_ca_email_e;

typedef    enum
{
#if ((EMBED_CA & CDCA) == CDCA)
	CDCA_PROMPT_CLEAR = 0x00,		//0x00 取消当前的显示 
	CA_PROMPT_BADCARD,				//0x01 无法识别的卡 
	CA_PROMPT_EXPICARD,				//0x02 智能卡过期，请更换新卡
	CA_PROMPT_NOT_INSERTCARD,		//0x03 加扰节目，请插入智能卡 
	CA_PROMPT_NOOPER,				//0x04 卡中不存在节目运营商 
	CA_PROMPT_BLACKOUT,				//0x05 条件禁播   
	CA_PROMPT_OUTWORKTIME,			//0x06 当前时段被设定为不能观看 
	CA_PROMPT_WATCHLEVEL,			//0x07 节目级别高于设定的观看级别 
	CA_PROMPT_PAIRING,				//0x08 智能卡与本机顶盒不对应 
	CA_PROMPT_NOENTITLE,			//0x09 没有授权  
	CA_PROMPT_DECRYPTFAIL,			//0x0A 节目解密失败 
	CA_PROMPT_NOMONEY,				//0x0B 卡内金额不足 
	CA_PROMPT_ERRREGION,			//0x0C 区域不正确 
	CA_PROMPT_NEEDFEED,				//0x0D 子卡需要和母卡对应，请插入母卡 
	CA_PROMPT_ERRCARD,				//0x0E 智能卡校验失败，请联系运营商 
	CA_PROMPT_UPDATE,				//0x0F 智能卡升级，请不要拔卡或者关机 
	CA_PROMPT_LOWCARDVER,			//0x10 请升级智能卡 
    CA_PROMPT_VIEWLOCK,				//0x11 请勿频繁切换频道
	CA_PROMPT_MAXRESTART,			//0x12 智能卡暂时休眠，请5分钟后重新开机 
	CA_PROMPT_FREEZE,				//0x13 智能卡已冻结，请联系运营商 
	CA_PROMPT_CALLBACK,				//0x14 智能卡已暂停，请回传收视记录给运营商 
	CA_PROMPT_CURTAIN,				//0x15 高级预览节目，该阶段不能免费观看
	CA_PROMPT_CARDTESTSTART,		//0x16 升级测试卡测试中...
	CA_PROMPT_CARDTESTFAILD,		//0x17 升级测试卡测试失败，请检查机卡通讯模块
	CA_PROMPT_CARDTESTSUCC,			//0x18 升级测试卡测试成功
   	CA_PROMPT_NOCALIBOPER,			//0x19 卡中不存在移植库定制运营商
	CA_PROMPT_STBLOCKED,			//0x1A 请重启机顶盒 
   	CA_PROMPT_STBFREEZE,			//0x1B 机顶盒被冻结
   	CA_FEEDING_NOTE,				//0x1C 母卡数据读取成功，请插子卡
	CA_FEEDFAIL_NOTE,				//0x1D 母卡数据读取失败
	CA_NOT_XXCA,					//0x1E 非同方CA
    
	CDCA_SHOW_FINGER_PRINTING,		//0x1F 显示指纹
	CDCA_HIDE_FINGER_PRINTING,		//0x20 隐藏指纹
	CDCA_SHOW_OSD_MESSAGE,			//0x21 显示osd
	CA_HIDE_OSD_MESSAGE,			//0x22 隐藏osd
	CDCA_NEW_EMAIL_NOTE,			//0x23新邮件提示
	CDCA_HIDE_EMAIL_NOTE,			//0x24 隐藏新邮件提示
	CDCA_EMAIL_FULL_NOTE,			//0x25 邮箱已满
	CA_PROMPT_IPPVSTART,			//0x26 显示ippv
	CA_PROMPT_IPPVHIDE,				//0x27 隐藏ippv
	CA_NEW_DETITLE_NOTE,			//0x28 新的反授权提示
	CA_HIDE_DETITLE_NOTE,			//0x29 隐藏反授权
	CA_DETITLE_FULL_NOTE,			//0x2A 反授权信息已满
	CA_FEED_HIDE,					//0x2B 隐藏子卡喂养提示
	CA_PROMPT_NOTP,					//0x2C
	CDCA_SHOW_URGENCY_BROADCAST,	//0x2D //正在紧急广播
	CDCA_HIDE_URGENCY_BROADCAST,	//0x2E
	CA_SHOW_SUPERLOOK_NOTE,			//0x2F
	CA_HIDE_SUPERLOOK_NOTE,    		//0x30
#endif

#if ((EMBED_CA & DVTCA) == DVTCA)
	CA_PROMPT_RATING_TOO_LOW = 0x00,		//0x00//收看级别不够
	CA_PROMPT_NOT_IN_WATCH_TIME,			//0x01//不在收看时段内
	CA_PROMPT_NOT_PAIRED,					//0x02//没有机卡对应
	CA_PROMPT_IS_PAIRED_OTHER,				//0x03//IC卡与其它机顶盒对应
	CA_PROMPT_PLEASE_INSERT_CARD,			//0x04//请插卡	
	CA_PROMPT_NO_ENTITLE,					//0x05//没有购买此节目
	CA_PROMPT_PRODUCT_RESTRICT,				//0x06//运营商限制观看该节目
	CA_PROMPT_AREA_RESTRICT,				//0x07//运营商限制区域观看
	CA_PROMPT_MOTHER_RESTRICT,				//0x08//此卡为子卡，已经被限制收看，请与母卡配对
	CA_PROMPT_NO_MONEY,						//0x09//余额不足，不能观看此节目，请及时充值
	CA_PROMPT_IPPV_NO_CONFIRM,				//0x0A//此节目为IPPV节目，请到IPPV节目确认/取消购买菜单下确认购买此节目
	CA_PROMPT_IPPV_NO_BOOK,					//0x0B//此节目为IPPV节目，您没有预订和确认购买，不能观看此节目
	CA_PROMPT_IPPT_NO_CONFIRM,				//0x0C//此节目为IPPT节目，请到IPPT节目确认/取消购买菜单下确认购买此节目
	CA_PROMPT_IPPT_NO_BOOK,					//0x0D//此节目为IPPT节目，您没有预订和确认购买，不能观看此节目
	CA_PROMPT_IPPV_NO_MONEY,				//0x0E//此节目为IPPV节目，余额不足，不能观看，请及时充值
	CA_PROMPT_IPPT_NO_MONEY,				//0x0F//此节目为IPPT节目，余额不足，不能观看，请及时充值
   	CA_PROMPT_DATA_INVALID,					//0x10//数据无效，STB不做任何提示。卡密钥问题。
	CA_PROMPT_SLOT_NOT_FOUND,				//0x11//钱包不存在
	CA_PROMPT_SC_NOT_SERVER, 				//0x12//IC卡被禁止服务
	CA_PROMPT_TVS_NOT_FOUND,				//0x13//运营商不存在
	CA_PROMPT_KEY_NOT_FOUND, //20			//0x14//此卡未被激活，请联系运营商
	CA_PROMPT_IPPNEED_CALLBACK,				//0x15//请联系运营商回传IPP节目信息
	CA_PROMPT_FREE_PREVIEWING,              //0X16用户您好，此节目您尚未购买，正在免费预览中
	CA_PROMPT_TERMINAL_NOT_ACTIVATE,	    //0x17终端未激活terminal is not activated
    CA_PROMPT_TERMINAL_NOT_SERVER,			//0x18终端被禁用terminal is forbidden 
    CA_PROMPT_FREEPREVIEW_OVER,			    //0x19本次预览结束preview is over
    CA_PROMPT_FREEPREVIEW_ALLOVER,		    //0x1A本节目今日预览次数已到today's preview of this program has been used up  

	DVTCA_PROMPT_CLEAR,  				    //0X1E

	DVTCA_SHOW_FINGER_PRINTING, 			//0x1F
	DVTCA_HIDE_FINGER_PRINTING,  			//0x20
	CA_SHOW_OSD_MESSAGE,
	DVTCA_SHOW_URGENCY_BROADCAST,			//正在紧急广播
	DVTCA_HIDE_URGENCY_BROADCAST,
	CA_SHOW_INQUIRE_IPP,
	DVTCA_NEW_EMAIL_NOTE,
	DVTCA_HIDE_EMAIL_NOTE,					//
	DVTCA_EMAIL_FULL_NOTE,					//   
	CA_SINGLE_AREA_LOCK,
	CA_UNKNOWN_ERR,

	CA_DECRYPT_FAILURE,
	DVTCA_HIDE_FREE_PREVIEWING,             //清除免费预览
	DVTCA_ANNO_SHOW,
	DVTCA_ANNO_HIDE,
#endif

#if ((EMBED_CA & CTICA) == CTICA)
	CTICA_PROMPT_CLEAR = 0x00,             //0x00 清除提示信息
	CA_PROMPT_SC_OUT,                      //0x01 请插入智能卡
	CA_PROMPT_SC_UNKNOWN,                  //0x02 无法识别智能卡
	CA_PROMPT_SC_CHECK,                    //0x03 正在校验智能卡
	CA_PROMPT_STB_NOT_MATCH,               //0x04  机卡不对应

	CA_PROMPT_LOW_PARENTAL_RATING,         //0x05 父母锁级别太低
	CA_PROMPT_UNKNOWN_ENCRYPT_PROGRAMME,   //0x06 无法识别的加密节目
	CA_PROMPT_NOT_ENTITLE,                 //0x07 没有解密授权
	STATUS_CA_DESCRAMBLE_SUCCESS,          //0x08 
	STATUS_CA_IPPV_PROGRAMME,              //0x09

	STATUS_CA_SC_IN,                       //0x0a
	STATUS_SUBTITLE_GOT,                   //0x0b 
	STATUS_NEW_MAIL_GOT,                   //0x0c
	STATUS_IPPV_PIN_ERROR,                 //0x0d
	STATUS_IPPV_NO_ENOUGH_CREDIT,          //0x0e

	CA_PROMPT_IPPV_NOTIFY,                 //0x0f  IPPV节目	弹出框
	STATUS_NO_SIGNAL,                      //0x10
	STATUS_SERVICE_UNKNOWN,                //0x11
	STATUS_PPID_CALL,                      //0x12
	STATUS_PIN_CORRECT,                    //0x13

	STATUS_PIN_INCORRECT,                  //0x14
	STATUS_IPPV_BUY,                       //0x15
	STATUS_IPPV_OK,                        //0x16
	STATUS_IPPV_FAIL,                      //0x17
	STATUS_IPPVP_PIN_ERROR,                //0x18

	STATUS_IPPV_NO_MONEY,                  //0x19
	STATUS_IPPVP_UNSUPPORT_MODE,           //0x1a  
	STATUS_PPV_LIST_INFO_NOTIFY_OK,        //0x1b   
	STATUS_IPPV_LIST_INFO_NOTIFY_OK,       //0x1c
	STATUS_PIN_CHANGE,                     //0x1d

	STATUS_PIN_FAIL,                       //0X1e
	STATUS_RAT_CHANGE,                     //0X1f
	STATUS_RAT_FAIL,                       //0X20
	STATUS_RAT_PINERR,                     //0x21
	STATUS_OLDPIN_ERROR,                   //0x22

	CTICA_SHOW_FINGER_PRINTING,            //0x23
	CTICA_HIDE_FINGER_PRINTING,            //0x24
	STATUS_ENTITLE_PWSUCCESS,              //0x25
	STATUS_ENTITLE_PWFAIL,                 //0x26
	CA_PROMPT_ECM_FILTER_ERROR,            //0x27 分配ECM通道失败

	CA_PROMPT_OPEN_DES_FAILED,             //0x28 解扰通道分配失败
	CA_PROMPT_SC_DES,                      //0x29 解扰时智能卡错误
	CA_PROMPT_CW_ERROR,                    //0x2a 控制字出错
	CA_PROMPT_IPPV_EXPIRED,                //0x2b IPPV节目过期
	STATUS_ANTI_OK,                        //0x2c

	STATUS_ANIT_NOT,                       //0x2d
	STATUS_MAIL_NO_ENOUGH_SPACE,           //0x2e
	CA_PROMPT_NOT_CTICA,                   //0x2f  非CTICA
	CA_PROMPT_FORCE_CHANGE_CHANNEL,        //0x30 强制切换频道
	STATUS_REQ_CHANGE_CHANNEL,             //0x31

	CA_PROMPT_AF_PLAY_SET_OK,              //0x32 用户准禁播设置成功
	CA_PROMPT_AF_PLAY_READ_OK,             //0x33 用户准禁播数据读取成功
	CA_PROMPT_AF_PLAY_SET_TIME_ERROR,      //0x34 用户准禁播设置时间错误
	CA_PROMPT_AF_PLAY_SET_TIME_LONG_ERROR, //0x35 用户准禁播控制时间超长
	CA_PROMPT_AF_PLAY_SET_SLOT_ERROR,      //0x36 用户准禁播设置通道错误

	CA_PROMPT_AF_PLAY_SET_MODE_ERROR,      //0x37 用户准禁播设置模式错误
	CA_PROMPT_AF_PLAY_SET_PIN_ERROR,       //0x38 用户准禁播设置PIN码错误
	CA_PROMPT_AF_PLAY_SET_ERROR,           //0x39 用户准禁播设置失败
	CA_PROMPT_CHILD_CARD_VERIFY_OK,        //0x3a 子卡认证成功
	CA_PROMPT_CARD_OK,                     //0x3b 智能卡OK

	CA_PROMPT_CHILD_CARD_VERIFY_ERROR,     //0x3c 子卡认证失败
	CA_PROMPT_MOTHER_CARD_VERIFY_ERROR,    //0x3d 母卡验证失败
	CA_PROMPT_CHILD_CARD_EXPIRED_ERROR,    //0x3e 子卡认证过期
	CA_PROMPT_STB_REGION_ERROR,            //0x3f 区域码不正确
	CA_PROMPT_USER_AF_PLAY_CTRL,           //0x40 用户准禁播控制

	CA_PROMPT_REGION_AF_PLAY_CTRL,         //0x41 区域准禁播控制
	STATUS_PROG_SKIP_CANCEL,               //0x42

	CTICA_NEW_EMAIL_NOTE,				   //新邮件
	CTICA_HIDE_EMAIL_NOTE,				   //擦除邮件标志
	CTICA_EMAIL_FULL_NOTE,				   //邮件已满
	//CTICA_SHOW_URGENCY_BROADCAST,		   //紧急广播
	CA_CHOOSE_URGENCY,					   //选择是否跳到紧急广播的对话框,对话框里要显示紧急广播的内容

#endif

#if ((EMBED_CA & MGCA) == MGCA)

	MGCA_ERR_SCARD_NOT_ACT = 0x00,	   	   //请激活子卡
	MGCA_ERR_SCARD_DISABLED,         //请激活子卡/*the leavetimelength<0 in the son card 20071218 eileen*/
	MGCA_ERR_ZONE_CODE,              //智能卡区域码错误    /*the zone code is not compatible with networkid in NIT 20080328 eileen*/
	MGCA_ERR_NO_MONEY,		   	   //智能卡余额不足
	MGCA_ERR_NOT_AUTHORED,		   //节目未授权
	MGCA_ERR_CARD_LOCKED,			   //智能卡锁定
	MGCA_ERR_APP_LOCKED,			   //服务锁定
	MGCA_ERR_PIN_AUTHEN,			   //机卡配对错误
	MGCA_ERR_PINERR_STB_PAIRED,	   //机卡配对错误：智能卡未配对，机顶盒已配对
	MGCA_ERR_PINERR_CARD_PAIRED,	   //机卡配对错误：智能卡已配对，机顶盒未配对
	MGCA_ERR_EXTER_AUTHEN,		   //智能卡认证失败
	MGCA_ERR_GET_CARD_DATA,		   //智能卡数据错误
	MGCA_ERR_ILLEGAL_CARD,		   //智能卡通信错误
	MGCA_ERR_DONOT_TELEVIEW_PPV,	   //PPV收费节目
	MGCA_ERR_CARD_NOTFOUND,		   //请插入智能卡
	MGCA_ERR_CARD_NOTMATCH, 		   //智能卡不匹配  /* v3.1.2 added, hanjf */
	MGCA_ERR_UPDATE_GK, 			   //智能卡升级失败   /* v3.1.2 added, hanjf */

	MGCA_EMM_APP_STOP,			   //智能卡暂停服务
	MGCA_EMM_APP_RESUME,			   //智能卡恢复服务
	MGCA_EMM_PROG_UNAUTH,			   //取消节目订购
	MGCA_EMM_PROG_AUTH ,			   //增加节目订购
	MGCA_EMM_EN_PARTNER,			   //启用机卡配对
	MGCA_EMM_DIS_PARTNER,			   //取消机卡配对
	MGCA_EMM_UPDATE_GNO,			   //智能卡组号更新
	MGCA_EMM_UPDATE_GK,			   //智能卡升级请重启机顶盒
	MGCA_EMM_SONCARD,				   //设置子母卡
	MGCA_EMM_URGENT_SERVICE, 		   //（切换到目标频道）紧急服务
	MGCA_EMM_MODIFY_ZONECODE,		   //智能卡区域码更新
	MGCA_EMM_UPDATE_CRT,			   //授权更新
	MGCA_EMM_MODIFY_CTRLCODE,		   //智能卡限播码更新
	MGCA_ERR_CONTROL_PLAY,		   //本节目条件限播
	MGCA_ERR_AUTH_CLOSED,			   //本节目授权关闭
	MGCA_ERR_AUTH_OVERDUE,		   //智能卡授权过期
	MGCA_ERR_AUTH_UPDATE,			   //授权刷新，请稍候
	MGCA_ERR_ILLEGAL_AUTH,		   //智能卡授权错误
	MGCA_ERR_CARD_STATUS_RENEW,	   //智能卡状态更新，请重启机顶盒
	MGCA_ERR_CARD_OPERATE,		   //智能卡操作失败
    MGCA_ERR_CARDOUT_PLEASEIN,	   //请插入智能卡
    MGCA_NOT_MGCA,				   //非MGCAS (0x26)


	MGCA_SUCCESS,				       //清屏！！！
	MGCA_ERR_PINERR_SC_NOTMATCH,	   //机卡配对错误：机卡再插入X次后将被锁定//-------2012.06.11--------------------
	MGCA_EMM_EMAIL,				   //显示新邮件图标
	MGCA_EMM_CHARGE,				   //电子钱包充值成功，充值金额X点
	MGCA_ECM_PPV_UPD,				   //“PPV”图标（类似于邮件，是IPPV购买前出现，提示这是ppv节目）！！！
	MGCA_ECM_PreAuth_UPD,			   //"预授权"图标（类似于邮件，是IPPV购买前出现，提示这是预授权的节目）
	MGCA_PreAuth_UPD_VANISH,		   //清除"预授权"图标
	MGCA_HIDE_EMAIL_NOTE,			   //邮件
	MGCA_ERR_QUESTION_TELEVIEW_PPV,  //PPV节目请购买					
	MGCA_ERR_AUTHNEARBOOT_REMIND,	   //节目授权剩余X天，请及时续费
	MGCA_ERR_AUTHNEARTIME_REMIND,	   //节目授权剩余X天，请及时续费
	MGCA_ERR_AUTHEXPIRE_REMIND,	   //节目授权已过期，请及时续费

	MGCA_HIDE_IPPV_ICON,
	MGCA_SHOW_URGENCY_ICON,
	MGCA_HIDE_URGENCY_ICON,
	MGCA_HIDE_AUTH_REMAIN_DLG,
	MGCA_HIDE_PURSE_DLG,
	MGCA_HIDE_EXPIR_DLG,

#endif

#if ((EMBED_CA & GYCA) == GYCA)
//---以下为库提示--
	CA_NO_CASH = 0x00, 						//智能卡内无金额
	CA_NOT_ENOUGH_CASH,						//智能卡金额不足
	CA_ENTITLEMENT_EXPIRED,					//您的费用已到期
	CA_LOGOUT,								//智能卡已注销
	CA_NOT_ENTITLED_USER, 					//加密频道, 用户无授权
	CA_SMARTCARD_DISABLED, 				  	//智能卡未激活
	CA_UPGADING_PLEASE_WAIT, 				//正在升级算法,请稍候...
	CA_DECRYPT_ERROR,  					    //智能卡解码异常
	CA_CALL_FOR_STOP, 					    //智能卡已报停
	CA_READING_SMARTCARD, 			   		//正在读取智能卡, 请稍候
	CA_CHECK_SMARTCARD, 					//加密频道, 请检查智能卡
	CA_CHECK_CARD_DIRECTION, 				//无法识别卡, 请检查插卡方向
	CA_UNKNOWN_SMART_CONTACT_SUPPLIERS, 	//智能卡版本错, 请联系供应商
	CA_READSMART_ERR_PLEASE_CHECK,   		//读卡出错, 请检查智能卡
	CA_WRITESMART_ERR_PLEASE_CHECK,  		//写卡出错, 请检查智能卡
	CA_INSERT_SMART_PLEASE, 				//请插入智能卡
	CA_UNKNOWN_SMART_PLEASE_CHECK,  		//不能识别该卡, 请检查智能卡
	CA_SMART_BOX_NOT_MATCHED, 			    //机卡不匹配
	CA_PIN_ERR, 							//PIN码出错
	CA_SMART_LEVEL_NOT_ENOUGH,  			//智能卡级别不够
	CA_UNKNOWN_BOX_TYPE, 					//机顶盒型号不支持
	CA_INSERT_PARENT_CARD,    				//请先插入主卡
	CA_SON_CARDERR_INSERT_PARENT, 			//子卡操作超时, 请插入主卡
	CA_UNCORRECT_SUBSCRIBER, 				//子卡用户名不匹配
	CA_CARD_AREA_ERR,						//用户区域不正确
	CA_STB_AREA_ERR, 						//其他地区机顶盒
	CA_CONDITIONAL_LIMITED,					//条件禁播
	CA_DEBUG_VERSION, 						//调试版, 禁止解密
	CA_UNKNOWN_ERR = 28,					//未知信息
	CA_NEED_ADD_ENUM,                       //没有找到和库提示一致的枚举类型，可能需要添加枚举定义！
//-----------------

	CA_NOTICE_SHOW,         // 显示节目不能播放的提示信息--
	CA_NOTICE_ERASE,		// 擦除提示信息					 --
	CA_OSD_ERASE,			// 擦除OSD信息					 --
	CA_RESTART_CHAN,		// 请求应用程序重新播放当前节目
	CA_OSD_INFO,			// 有EMM,PEMM OSD信息通知
	CA_MAIL_INFO,			// 有EMM,PEMM Mail信息通知
	CA_EXECUTE_OP_INFO,	    // 要求机顶盒执行具体的机顶盒操作
	CA_SW_UPDATE_INFO,		// 有EMM,PEMM 软件更新信息通知
	CA_TRANSPARENT_INFO,	// CA 透传给机顶盒的私有信息
	CA_FINGER_SHOW,		    // 要求显示指纹信息
	CA_FINGER_ERASE,		// 要求擦除指纹信息
	CA_IPPV_INFO,			// IPPV 信息
	GYCA_NEW_EMAIL_NOTE,		// 新邮件(图标)
	GYCA_HIDE_EMAIL_NOTE,
	GYCA_EMAIL_FULL_NOTE,
	CA_SWITCH_CHANNEL,
	CA_SEARCH_CHANNEL,
	CA_NOT_XXCA,
	CA_CARD_NOTFOUND,		//请插入智能卡
	GYCA_PROMPT_CLEAR,		//非加扰台清屏

#endif

#if ((EMBED_CA & TRCA) == TRCA)
    CA_PROMPT_E00 = 0x00,  // 0x00  E00 当前节目没加密(清除提示信息)
    CA_PROMPT_E01,  // 0x01  E01 请插入CA模块
    CA_PROMPT_E02,  // 0x02  E02 CA模块EEPROM失败
    CA_PROMPT_E03,  // 0x03  E03 CA模块失败
    CA_PROMPT_E04,  // 0x04  E04 请插入智能卡
    CA_PROMPT_E05,  // 0x05  E05 系统不识别此卡
    CA_PROMPT_E06,  // 0x06  E06 智能卡失败
    CA_PROMPT_E07,  // 0x07  E07 正在检测智能卡
    CA_PROMPT_E08,  // 0x08  E08 CA模块失败
    CA_PROMPT_E09,  // 0x09  E09 智能卡EEPROM失败
    CA_PROMPT_E10,  // 0x0A  E10 PMT格式错误
    CA_PROMPT_E11,  // 0x0B  E11 机卡不匹配
    CA_PROMPT_E12,  // 0x0C  E12 请与母机同步
    CA_PROMPT_E13,  // 0x0D  E13 没有有效的节目
    CA_PROMPT_E14,  // 0x0E  E14 节目没有授权
    CA_PROMPT_E15,  // 0x0F  E15 接收到授权
    CA_PROMPT_E16,  // 0x10  E16 当前节目已加密
    CA_PROMPT_E17,  // 0x11  E17 当前节目已加密
    CA_PROMPT_E18,  // 0x12  E18
    CA_PROMPT_E19,  // 0x13  E19
    CA_PROMPT_E20,  // 0x14  E20 无运营商授权
    CA_PROMPT_E21,  // 0x15  E21
    CA_PROMPT_E22,  // 0x16  E22
    CA_PROMPT_E23,  // 0x17  E23 当前节目正在解密
    CA_PROMPT_E24,  // 0x18  E24 无本区域授权
    CA_PROMPT_E25,  // 0x19  E25 智能卡不兼容
    CA_PROMPT_E26,  // 0x1A  E26 系统不认识当前节目
    CA_PROMPT_E27,  // 0x1B  E27 当前节目不在运行
    CA_PROMPT_E28,  // 0x1C  E28 锁定智能卡
    CA_PROMPT_E29,  // 0x1D  E29
    CA_PROMPT_E30,  // 0x1E  E30 当前节目无效
    CA_PROMPT_E31,  // 0x1F  E31 父母控制锁定
    CA_PROMPT_E32,  // 0x20  E32 国家代码没有授权
    CA_PROMPT_E33,  // 0x21  E33 没有授权数据
    CA_PROMPT_E34,  // 0x22  E34 非授权机顶盒
    CA_PROMPT_E35,  // 0x23  E35 没有信号
    CA_PROMPT_E36,

    CA_NOTICE_SHOW = 37,    // 显示节目不能播放的提示信息
	CA_NOTICE_ERASE,		// 擦除提示信息
	CA_OSD_ERASE,			// 擦除OSD信息
	CA_OSD_INFO,			// 有EMM,PEMM OSD信息通知
	CA_MAIL_INFO,			// 有EMM,PEMM Mail信息通知
	CA_EXECUTE_OP_INFO,	    // 要求机顶盒执行具体的机顶盒操作
	CA_SW_UPDATE_INFO,		// 有EMM,PEMM 软件更新信息通知
	CA_TRANSPARENT_INFO,	// CA 透传给机顶盒的私有信息
	CA_FINGER_SHOW,		    // 要求显示指纹信息
	CA_FINGER_ERASE,		// 要求擦除指纹信息
	CA_IPPV_INFO,			// IPPV 信息
	CA_IPPT_INFO,           // IPPT 信息
    CA_HIDE_IPP,            // 擦除 IPP图标
	CA_IPP_BUY,				//IPP购买弹出框
	CA_ANNO_INFO,			//公告显示
	CA_ANNO_HIDE,           //公告掩藏
	CA_PARENTALCTRL_HIDE,   //父母锁掩藏
#endif

#if ((EMBED_CA & WFCA) == WFCA)
	WFCA_WFERR_COMMON_NO	= 0x00	    		,/* 没有错误 */
	WFCA_WFERR_COMMON_PARAMETER 				,/* 函数的参数非法 */
	WFCA_WFERR_COMMON_MEMALLOC				,/* 分配存储器失败 */
	WFCA_WFERR_COMMON_MEMFREE					,/* 释放存储器失败 */
	WFCA_WFERR_COMMON_ILLEAGAL				,/* 非法的操作 */
	WFCA_WFERR_COMMON_VERIFY					,/* 校验失败 */
	WFCA_WFERR_COMMON_MEMEXEC					,/* 内存异常 */

	WFCA_WFERR_SMART_SW1SW2  					, /* 执行命令时状态字不等于0x9000,低16位为状态字SW1SW2 */
	WFCA_WFERR_SMART_RWSIZE					, /* 实际响应字节数比要求的少 */
	WFCA_WFERR_SMART_ABSENT					, /* 没有插入智能卡 */
	WFCA_WFERR_SMART_INVALID					, /* 非法的智能卡 */
	WFCA_WFERR_SMART_DRIVER					, /* 智能卡驱动程序错误从这里开始编号，且小于WFERR_FILE_FORMAT */

	WFCA_WFERR_FILE_FORMAT					, /* 文件格式错误 */
	WFCA_WFERR_FILE_CONFLICT					,/* 插入冲突 */
	WFCA_WFERR_FILE_FULL						,/* 文件已满 */
	WFCA_WFERR_FILE_EMPTY						,/* 文件已空 */
	WFCA_WFERR_FILE_QUERY						,/* 未能查询到记录 */
    WFCA_WFERR_FILE_ABNORMAL                    ,/*文件内容异常*/

	WFCA_WFERR_CAS_ABSENT						, /* CAS尚未初始化 */
	WFCA_WFERR_CAS_PRESENT					,/* CAS已经初始化 */
	WFCA_WFERR_CAS_INVALIDSTB					,/* 非法的机顶盒,或者机卡不匹配 */
	WFCA_WFERR_CAS_UNLICENSED					,/* 节目未经授权 */
	WFCA_WFERR_CAS_OUTOFPERIOD				,/* 节目不在授权的期间内 */
	WFCA_WFERR_CAS_FORBIDDEN					,/* 禁止解扰 */
	WFCA_WFERR_CAS_COMMAND					,/* 非法的前端命令 */
	WFCA_WFERR_CAS_LENGTH						,/* 命令的参数长度不正确 */
	WFCA_WFERR_CAS_ADDRESS					,/* 前端寻址没有寻到本机 */
	WFCA_WFERR_CAS_BALANCE					,/* 余额不足 */
	WFCA_WFERR_CAS_UNMATCHED					,/* 子机与母机不匹配 */
	WFCA_WFERR_CAS_EXPIRATION					,/* 过期的子机授权 */
	WFCA_WFERR_CAS_ZONE						,/* 错误的区域 */
	WFCA_WFERR_CAS_PROTOCOL					,/* CMT协议不正确 *///30

	WFCA_EMM_MESSAGE_DISPLAY ,		   		//ca Message存于全局变量WFSTB_EMMMessage中，用于显示
    WFCA_EMAIL_NOTE			,
    WFCA_EMAIL_CLEAR			,
	WFCA_PPT_NOTE			,
   	WFCA_PPT_CLEAR			,
	WFCA_OSDMSG_NOTE			,
	WFCA_DBC_SUBMIT			,
	WFCA_SHOW_URGENCY_BROADCAST ,
	WFCA_ENTITLEMENT		,              //该节目收视权限还剩%u天
    WFCA_AUTHNEARBOOT_REMIND,
    WFCA_HIDE_AUTH_REMAIN_DLG,

#endif

#if ((EMBED_CA & QZCA) == QZCA)
	CA_OK	= 0x00			,  /*0x00 状态正确,取消显示*/
	CA_NO_SW1SW2		,  /*没有状态字*/
	CA_MEMORY_ERROR		,  /*智能卡内存出错*/
	CA_WRONG_LC_LENGTH	,  /*APDU命令长度(lc)错误*/
	CA_WRONG_DATA		,  /*数据错误， 通常是CRC错误*/
	CA_WRONG_PARA		,  /*APDU参数错误*/
	CA_WRONG_LE_LENGTH	,  /*APDU 返回字节长度（le）错误*/
	CA_INS_NOT_SUPPORT	,  /*APDU命令不支持*/
	CA_CLA_NOT_SUPPORT	,  /*APDU 类型码不支持*/
	CA_GENERAL_ERROR	,  /*未知类型错误，一般是通讯错误*/
	CA_EXPIRED			,  /*授权过期*/

	CA_STB_NOT_MATCH	,  /*机卡不配对*/
	CA_CARD_NOT_INIT	,  /*智能卡未初始化*/
	CA_WRONG_SUPER_CASID,  /*错误的SUPER_CAS_ID*/
	CA_WRONG_SC_ID		,  /*错误的智能卡号， 过滤的数据不是这张卡的*/
	CA_PPV_EXCEED		,  /*PPV过期*/
	CA_NOT_PAIRED		,  /*智能卡没有设置为机卡配对*/
	CA_ECM_NOT_AUTH		,  /*频道未授权*/
	CA_LIMIT_AREA		,  /*区域限播*/
	CA_LIMIT_CARD		,  /*卡限播*/
	CA_NOT_CHILD_MODE	,  /*智能卡没有设置为子卡模式*/
	CA_NO_CHILD_AUTH	,  /*没有子卡授权*/
	CA_CHILD_NOT_AUTH	,  /*子卡未授权*/
	CA_CHILD_AUTH_TIMEOUT, /*设置子卡授权超时*/
	CA_CHILD_AUTH_EXPIRED, /*0x18子卡授权过期*/

   	CA_ERR_CRC			,  /*CRC错误*/
	CA_ERR_NOT_INT		,  /*未初始化*/
	CA_CARD_NO_FOUND	,  /*请插入智能卡*/
	CA_CARD_ERROR		,  /*错误的智能卡*/
	CA_CARD_ERR_COMM    ,  /*通讯错误*/
	CA_WRONG_DATA_PACK  ,  /*数据包错误*/
	CA_NOT_AUTH_OR_EXPIRED,/*授权未开始或已过期*/

	CA_NEW_EMAIL		,
	CA_HIDE_EMAIL		,
	CA_FULL_EMAIL		,
	CA_SHORT_MSG		,  /*滚动条*/

#endif

#if ((EMBED_CA & XGCA) == XGCA)
	
	/*常规应答错误*/	
	CA_XG_SUCCESS = 0x00	        , 	//成功
	CA_XG_INVALID_INSTRUCTION		, 	//非法命令
	CA_XG_WRONG_LENGTH				, 	//域长度错误
	CA_XG_CARD_FORMAT1_FAIL			, 	//卡片未经格式化
	CA_XG_CARD_FORMAT2_FAIL			, 	//卡片未完成应用格式化
	CA_XG_WRONG_P1_P2				, 	//p1或p2参数错误
	CA_XG_INVALID_NOT_SUPPORT		, 	//命令不支持
	CA_XG_NO_DATA					, 	//无数据可取
	/*应答错误*/
	CA_XG_TABLE_FORMAT_NOT_SUPP		,	  //不支持的包格式版本	 0x08
	CA_XG_CA_NOT_SUPPORT			,	  //不支持的CA版本
	CA_XG_NET_NOT_SUPPORT			,	  //不支持的网络系统
	CA_XG_WRONG_FILTER				,	  //错误的过滤规则
	CA_XG_OPERATE_FAIL				,	  //操作失败
	CA_XG_START_SER_SUCCESS			,	  //服务启用操作成功
	CA_XG_STOP_SER_SUCCESS			,	  //服务冻结操作成功
	CA_XG_NEED_MATCH				,	  //需要机卡配对
	CA_XG_BALANCE_NOT_ENOUGH		,	  //钱包余额不足
	CA_XG_CARD_EXPIRE				,	  //子卡将到期
	CA_XG_NIT_ZONE_FAIL				,	  //NIT表区域验证失败
	CA_XG_NEED_CORRECT_NIT			,	  //卡未通过区域验证，需要正确的NIT
	CA_XG_SER_STOPED				,	  //服务被冻结//20
	CA_XG_CARD_DELETED				,	  //卡被删除
	CA_XG_FILE_SYS_WRONG			,	  //文件系统出错
	CA_XG_LEVEL_LIMITED				,	  //不能收看的节目级别
	CA_XG_DECRYPT_FAIL				,	  //解密错误
	CA_XG_NO_AUTHORIZATION			,	  //无授权
	CA_XG_TABLE_FORMAT_WRONG		,	  //错误的包格式
	CA_XG_PAY_IPP_FAIL				,	  //购买IPPV失败
	CA_XG_NO_VALID_INFO				,	  //无可用的信息
	CA_XG_CARD_INIT_FAIL			,	  //卡片未完成应用初始化
	CA_XG_INVALID_CAID				,	  //未知的CAID //30
	CA_XG_CARD_NOT_INIT				,	  //卡片未完成初始化
	CA_XG_CARD_NOT_MATCH_STB		,	  //卡未与任何STB配对	
	CA_XG_CARD_ALREADY_MATCH		,	  //卡已经与某一STB配对	
	CA_XG_BOUND_FAIL				,	  //机卡绑定失败
	CA_XG_VERIFY_FAIL				,	  //机卡配对校验失败
	CA_XG_BOUND_UNEXPECTED_WRONG	,	  //绑定成功，但返回卡片特征码出现意外错误
	CA_XG_VERIFY_UNEXPECTED_WRONG	,	  //校验成功，但返回卡片特征码出现意外错误
	CA_XG_CARD_NOT_REGISTER			,	  //卡未注册
 	CA_XG_PLEASE_INSERT_CARD		,	  //请插卡	
	CA_XG_PPC						,	  //授权将到期,请及时续费//40
	CA_XG_CARD_INI_SUCCESS			,     //卡初始化成功
	CA_XG_CARD_INI_FAIL				,	  //卡初始化失败
	CA_XG_MATCH_STB_SUCCESS			,	  //机卡配对成功
	CA_XG_MATCH_STB_ALREADY			,	  //机卡已经配对
	CA_XG_NIT_MODIFYING				,	  //正在进行区域验证，请稍等。。。
	CA_XG_UNKNOWN_ERROR				,	  //未知错误
	CA_XG_FORCE_SHUTDOWN            ,     //强制关断
    CA_XG_FEED_MACHINE             ,     //子机授权即将到期，请到母机获取授权码
    CA_XG_FEED_MACHINE_SUCCESS      ,     //喂养成功
    CA_XG_FEED_MACHINE_FAIL         ,       //喂养失败//50
    CA_XG_CASYS_NOT_INIT             ,       //CA系统未出始化
    CA_XG_CASYS_UNKNOWN             ,       //无法识别的CA系统
    CA_XG_DECRYPT_ERROR             ,       //解密校验失败


	/*提示框、邮件、指纹、OSD*/
	CA_XG_PLEASE_CONFIRM			,	  //请按’确认‘开始配对子母卡	
	CA_XG_PLEASE_INSERT_MAINCARD	,	  //请插入母卡，并按’确认‘获取喂卡数据
	CA_XG_GET_FEED_FAIL				,	  //卡为子卡，无法获取喂卡数据，请插入母卡，并按’确认‘
	CA_XG_UNKNOWN_TIME				,	  //未知的当前时间，卡需要先获取ECM数据
	CA_XG_UNKNOWN_CAID				,	  //未知的CA-ID
	CA_XG_PLEASE_INSERT_SUBCARD		,	  //读母卡数据成功，请插入子卡，按’确认‘
	CA_XG_NO_SUBCARD				,	  //卡槽中无卡，请插入子卡，并按‘确认’
	CA_XG_DONOT_NEED_FEED			,	  //卡为母卡，不需要喂卡数据，请插入子卡并按’确认‘
	CA_XG_WRONG_FEED_DATA			,	  //错误的喂卡数据						
	CA_XG_FEED_SUCCESS				,	  //喂卡成功
	CA_XG_NEED_FEED_CARD			,	  //子卡到期，需要喂卡，请插入母卡获取喂卡数据	 
	CA_XG_NEW_EMAIL					,
	CA_XG_HIDE_EMAIL				,     //
	CA_XG_FULL_EMAIL				,     
	CA_XG_FINGER					,
	CA_XG_FINGER_HIDE               ,
	CA_XG_SHORT_MSG					, 	  //滚动条
	CA_XG_SHOW_IPPV					,
	CA_XG_HIDE_IPPV					,
	CA_XG_PPV_NOTE					,	 


#endif

#if ((EMBED_CA & DIVICA) == DIVICA)
	CA_DIVI_PROMT_CLEAR = 0x00, 	//0x00 销毁提示区域
	CA_DIVI_NO_ENTITLE , 	        //0x01 节目未授权
	CA_DIVI_BLACKOUT   , 			//0x02 条件限播
	CA_DIVI_INITIAL_CARD, 		    //0x03 初始化安装，卡不可使用
	CA_DIVI_WAIT_CARD  , 			//0x04 正在安装，卡等待激活
	CA_DIVI_OUTOF_SERVICE,  		//0x05 欠费停用
	CA_DIVI_PAIR_SERVICE,   		//0x06 维修停用
	CA_DIVI_APPLY_SERVICE,  		//0x07 申请报停停用
	CA_DIVI_LOGOUT		,   		//0x08 注销状态
	CA_DIVI_NOT_IN_WORKTIME,	    //0x09不在工作
	CA_DIVI_RATE_TOO_LOW,   		//0x0a 级别低于
	CA_DIVI_MONEY_NOT_ENOUGH,	    //0x0b 卡内金额?
	CA_DIVI_TEMP_LIVE,			    //0x0c 子卡可临
	CA_DIVI_TIMEOUT,				//0x0d 子卡过期
	CA_DIVI_NOT_PAIRED,			    //0x0e 机卡配对
	CA_DIVI_INVALID_CARD,		    //0x0f 无效卡
	CA_DIVI_INSERT_CARD,			//0X10 请插卡
	CA_DIVI_UNKNOW_ERR,			    //0X11 未知错误
    CA_DIVI_ENTITLE_EXPIRERDAYS,    //0X12 开机提醒
#endif
																													
#if ((EMBED_CA & DSCA) == DSCA)
	DSCA_CANCEL_TYPE		= 0x00,           
	DSCA_BADCARD_TYPE		= 0x01,		/*无法识别卡，不能使用*/
	DSCA_EXPICARD_TYPE		= 0x02,		/*智能卡已经过期，请更换新卡*/
	DSCA_CARD_INIT_TYPE		= 0x03,		/*智能卡正在初始化*/
	DSCA_INSERTCARD_TYPE	= 0x04,		/*加密节目，请插入智能卡*/
	DSCA_CARD_INIT_ERR_TYPE	= 0x05,		/*智能卡初始化失败*/
	DSCA_STB_NO_CARD_TYPE	= 0x06,		/*机顶盒中不存在智能卡*/

	DSCA_NOOPER_TYPE		= 0x10,		/*卡中不存在节目运营商*/
	DSCA_CARDSTOP_TYPE		= 0x11,		/*智能卡已停用*/
	DSCA_OUTWORKTIME_TYPE	= 0x12,		/*不在工作时段内*/
	DSCA_WATCHLEVEL_TYPE	= 0x13,		/*节目级别高于设定观看级别*/
	DSCA_PAIRING_TYPE		= 0x14,		/*机卡没有对应*/

	DSCA_NOENTITLE_TYPE		= 0x20,		/*您没有购买该节目*/
	DSCA_DECRYPTFAIL_TYPE	= 0x21,		/*节目解密失败*/
	DSCA_NOMONEY_TYPE		= 0x22,		/*卡内金额不足*/
	DSCA_ERRREGION_TYPE		= 0x23,		/*区域不正确*/
	//DSCA_FINGER_SHOW		= 0x24,		/*指纹显示*/

	//DSCA_FINGER_DISAPPEAR	= 0x30,		/*指纹隐藏*/
	DSCA_CARDNOTACTIVE_TYPE	= 0x31,		/*智能卡未激活*/
	DSCA_CARDLOGOUT_TYPE	= 0x32,		/*智能卡已注销*/
	DSCA_CONDITION_CTL_TYPE	= 0x33,		/*该产品被限播*/
	DSCA_DESCRA_NOENTITLE_TYPE	= 0x34,	/*授权已到期，请联系运营商*/
	DSCA_ENTITLE_UPDATE_TYPE    = 0x35,	/*授权更新中，请稍等！*/
	DSCA_CARD_UNWONTED_TYPE		= 0x36,	/*智能卡内部异常*/
	DSCA_CHANGEPRO_TOO_FAST_TYPE= 0x37,	/*请不要频繁切台*/
#if (defined(DSCA_56) || defined(DSCA_COS) || defined(DSCA_56_OVERSEAS))
	DSCA_SYSTEM_DATA_ERR_TYPE   = 0x38,	/*系统异常，无法更新*/
#else
	DSCA_STB_NEED_UPDATE_TYPE   = 0x38,	/*机顶盒需要升级，请稍等*/
#endif
	DSCA_CARD_IN_BLACKLIST_TYPE = 0x39,	/*您的卡已被列入黑名单！*/
#if defined(DSCA_56_OVERSEAS)	
	DSCA_STB_NEED_UPDATE_TYPE   = 0x3A,	/*机顶盒需要升级，请稍等*/
#endif	
   	DSCA_ZBCardPAIRING_OK	= 0x40,		/* 子母卡配对成功 */
   	DSCA_ZBCardPAIRING_Err	= 0x41,		/* 子母卡配对失败,请重新插入正确的母卡 */
   	DSCA_ZCardPAIRING_REQ	= 0x42,		/* 子卡需重新和母卡配对 */
	DSCA_CARD_MATCH_OK		= 0x43,		/*机卡配对成功*/
	DSCA_REMATCH_TYPE		= 0x44,		/*重新机卡配对*/
	DSCA_CANCEL_MATCH_TYPE	= 0x45,		/*取消机卡配对*/

	DSCA_SHOWNEWEMAIL		= 0x50,		/* 显示新邮件图标 */  
	DSCA_SHOWOVEREMAIL		= 0x51,		/* 显示邮件存满 */
	DSCA_HIDENEWEMAIL		= 0x52,		/* 隐藏新邮件图标*/
	DSCA_EXIGENT_PROGRAM	= 0x53,		/*紧急广播*/
	DSCA_STOP_EXIGENT_PROGRAM	= 0x54,	/*隐藏紧急广播字样*/
	DSCA_CARD_UNLOCK_OK			= 0x55,	/*智能卡密码解锁成功*/
	DSCA_CARD_PURSER_UPDATE_OK	= 0x56,	/*电子钱包更新*/
	DSCA_NET_ERR_LOCK_TYPE		= 0x57,	/*网络异常，卡被锁定*/
	DSCA_SYSTEM_ERR_LOCK_TYPE	= 0x58,	/*系统异常，卡被锁定*/
	DSCA_NET_ERR_UNLOCK_TYPE	= 0x59,	/*网络异常解锁*/
	DSCA_SYSTEM_ERR_UNLOCK_TYPE	= 0x60,	/*系统异常解锁*/

	/*智能卡更新.显示进度条，进度，和失败错误码*/
	DSCA_CARD_UPDATE_BEGIN_TYPE		= 0x65,		/*智能卡开始更新，显示进度条,此时进度为0*/
	DSCA_CARD_UPDATE_PROGRESS_TYPE	= 0x66,		/*更新进度*/
	DSCA_CARD_UPDATE_ERR_TYPE		= 0x67,		/*更新出错，错误代码*/
	DSCA_CARD_UPDATE_END_TYPE		= 0x68,		/*更新成功，进度条消失*/
	DSCA_CARD_NEED_UPDATE_TYPE		= 0x69,		/*智能卡需要更新，请稍后*/


	/*提示对话框*/
	DSCA_CARDISDUE_TYPE		= 0x70,		/*智能卡处于欠费催缴(带‘确定’按钮的对话框)*/
	DSCA_IPPVBUY			= 0x71,		/*Ippv购买提示框 */
	DSCA_IPPV_OUT_TIME		= 0x72,		/*Ippv节目过期*/
	DSCA_HIDE_IPPVBUY		= 0x73,		/*隐藏 Ippv购买提示框 */
	DSCA_ReqPAIRING_TYPE	= 0x74,		/*请求节目配对入网测试*/
#endif
																						
#if ((EMBED_CA & DVNCA) == DVNCA)
/* 为了使DVNCA_SHOW_PAIR以后枚举类型的值，在有卡和无卡的情况下相同
    无卡和有卡的PROMPT提示信息的总数需要相同。
*/
	DVNCA_PROMPT_CLEAR = 0x00,    //0x00 关闭所有提示(不需提示)
#if (!defined(DVNCA_COS))	
	DVNCA_PROMPT_SCNOTPAIR,       //0x01 机卡未配对
	DVNCA_PROMPT_NGTTOKEN,        //0x02 金额不正确
	DVNCA_PROMPT_NOTENGHTOKEN,    //0x03 钱包余额不足
	DVNCA_PROMPT_PAIRFAIL,        //0x04 配对未完成
	DVNCA_PROMPT_INSERT_CARD,     //0x05 请插入智能卡
	DVNCA_PROMPT_ANOTMACH,        //0x06 区域不匹配
	DVNCA_PROMPT_ECMBACKOUT,      //0x07 条件禁播
	DVNCA_PROMPT_SUBEXP,          //0x08 节目已过期
	DVNCA_PROMPT_SUBMOVED,        //0x09 节目未授权
	DVNCA_PROMPT_STBLOCK,         //0x0A 机顶盒被锁定
	DVNCA_PROMPT_SUBNOTSTART,     //0x0B 授权未开始
	DVNCA_PROMPT_SCEXP,           //0x0C 智能卡过期
	DVNCA_PROMPT_ECMDATAERR,      //0x0D ECM数据错误
	DVNCA_PROMPT_SECURITYERR,     //0x0E 安全通道错误
	DVNCA_PROMPT_LOWRATING,       //0x0F 观看级别不够
	DVNCA_PROMPT_CHECKSUMERR,     //0x10 节目校验错误
	DVNCA_PROMPT_ECMERR,          //0x11 ECM 解密错误
	DVNCA_PROMPT_NOTIDENTIFYSC,   //0x12 不能识别智能卡
	DVNCA_PROMPT_LIB_EXPIRED,     //0x13 CAK lib过期  
	DVNCA_PROMPT_SCCOM_ERR,       //0x14 机卡通讯错误太多
	DVNCA_PROMPT_UNSUPPORT_ECM,   //0x15 不支持ECM协议版本
    DVNCA_PROMPT_NOT_INWORKTIME,   //0x16 不在工作时段内
#else //无卡CA
    DVNCA_KP_PROMPT_NO_MATCH,       //0x01      //0x1 CA 库版本与前端不匹配
    DVNCA_KP_PROMPT_NO_ACTIVE,      //0x02     //0x2 CA 未激活, 请与运营商联系
    DVNCA_KP_PROMPT_AREA_NOT_MATCH, //0x03     //0x3  区域码不匹配
    DVNCA_KP_PROMPT_ERROR_PRODUCT,  //0x04     //0x7 产品ID 错误, 网络里面没有该产品
    DVNCA_KP_PROMPT_ERROR_PROVIDER, //0x05     //0x8  运营商ID 错误, 网络里面没有该运营商
    DVNCA_KP_PROMPT_NO_ENTITLE,     //0x06     //0x9 节目没有授权
    DVNCA_KP_PROMPT_ENTITLE_EXPIRED,//0x07     //0xa 节目授权已过期
    DVNCA_KP_PROMPT_ENTITLE_NOSTART,//0x08     //0xb  节目授权未开始
    DVNCA_KP_PROMPT_PRODUCT_CLASH,  //0x09     //0xc  产品ID 冲突
    DVNCA_KP_PROMPT_SERVICE_FORCE,  //0x0A     //0xd  条件禁播
    DVNCA_KP_PROMPT_OUT_RATING,     //0x0B     //0x11 观看等级不够
    DVNCA_KP_PROMPT_OUT_WORKTIME,   //0x0C     //0x12  不在工作时段内
    DVNCA_KP_PROMPT_RESET_PIN,      //0x0D     //0x13  PIN 已重置
    DVNCA_KP_PROMPT_GROUP_FORCE,    //0x0E     //0x14 分组禁播
    DVNCA_KP_PROMPT_EMERGENCY,      //0x0F     // 0x15  紧急事件
    DVNCA_KP_PROMPT_PRODUCT_UPDATE, //0x10     //0x1A  产品信息已更新
    DVNCA_KP_PROMPT_FREEZE,         //0x11     //0x20  CA 已过期
    DVNCA_KP_PROMPT_RESERVED1,      //0x12     
    DVNCA_KP_PROMPT_RESERVED2,      //0x13     
    DVNCA_KP_PROMPT_RESERVED3,      //0x14   
    DVNCA_KP_PROMPT_RESERVED4,      //0x15     
    DVNCA_KP_PROMPT_RESERVED5,      //0x16     
#endif

    DVNCA_SHOW_PAIR,              //0x17显示机卡配对
    DVNCA_HIDE_PAIR,              //0x18掩藏机卡配对
    DVNCA_SHOW_OSD,               //0x19显示滚屏OSD
    DVNCA_HIDE_OSD,               //0x1A掩藏滚屏OSD
    DVNCA_SHOW_URGENCY_ICON,      //0x1B显示"紧急事件"图标
    DVNCA_HIDE_URGENCY_ICON,      //0x1C隐藏"紧急事件"图标
#endif

#if ((EMBED_CA & GOSCA) == GOSCA)
	CA_PROMPT_CLEAR = 0x00,					//0x00清屏
	CA_PROMPT_SMART_STOP,					//0x01智能卡被禁用
	CA_PROMPT_SMART_AREA_NOPAIR, 			//0x02智能卡区域不匹配
	CA_PROMPT_SMART_IPPT_SWITCH,            //0x03无    /*暂时没用*/	
	CA_PROMPT_SMART_STB_NOPAIR,			 	//0x04机卡不配对
	CA_PROMPT_SMART_PROG_NOENTITLE,		 	//0x05节目未授权
	CA_PROMPT_SMART_PROG_NOENTITLE_IPPT,    //0x06无 /*暂时没用*/
	CA_PROMPT_SMART_MOTHER_SON_PAIR,		//0x07子母卡需重新配对
	CA_PROMPT_SMART_MOTHER_SON_TIMEOUT, 	//0x08子母卡配对超时
	CA_PROMPT_SMART_PAIR_OK,            	//0x09无 /*暂时没用*/
	CA_PROMPT_SMART_AREA_LOCK,				//0x0a智能卡区域锁定
	CA_PROMPT_SMART_CARD_LOCK, 				//0x0b智能卡被锁定
	CA_PROMPT_SMART_LIMIT_WATCH, 			//0x0c卡限制收看
	CA_PROMPT_SMART_NO_WORK_TIME, 			//0x0d卡不在工作时段

    /*0x0e~0x12是V2.08功能*/
	CA_PROMPT_SMART_AREA_CONTROL_ERROR,     //0x0e卡没有工作在正确的分区内
	CA_PROMPT_BIND_INFO_ERROR,              //0x0f机卡绑定错误+错误ID
	CA_PROMPT_SMART_IDRUN_ERROR,            //0x10卡号在网络中无效错误
	CA_PROMPT_SMART_LEVEL_ERROR,	        //0x11卡的观看级别低于节目级别
	CA_PROMPT_PVR_ENTITLE_TIMEOUT,          //0x12PVR 授权文件过期
    
	CA_PROMPT_SMART_OUT,				    //0x13节目加扰，请插卡

    /*0x14~0x17是V2.08功能*/
	CA_PROMPT_SMART_INVALID,                //0x14所插入卡非高斯贝尔CA卡
	CA_PROMPT_SMART_STB_NOBIND,             //0x15机卡未绑定时提示
	CA_PROMPT_CASID_BIND_ERROR,             //0x16机顶盒运营商ID和运营商ID绑定错误
    CA_PROMPT_CASID_SOL_ERROR,              //0x17 开机控制SOL信息接收错误

	CA_PROMPT_SMART_UNKNOWN_ERROR, 			//0x18未知错误

	CA_PROMPT_SMART_LAST_DAY, 				//0x19离截止日期剩余天数
	CA_PROMPT_SMART_IPPT, 					//0x1A无

	CA_SHOW_FINGER_PRINTING = 31, 			//0x1F
	CA_HIDE_FINGER_PRINTING = 32,  			//0x20
	GOSCA_SHOW_OSD_MESSAGE = 33,
	CA_SHOW_URGENCY_BROADCAST = 34,			//正在紧急广播
	CA_HIDE_URGENCY_BROADCAST = 35,
	GOSCA_SHOW_INQUIRE_IPP = 36,
	GOSCA_NEW_EMAIL_NOTE = 37,
	GOSCA_HIDE_EMAIL_NOTE = 38,						
	GOSCA_EMAIL_FULL_NOTE = 39,
	GOSCA_HIDE_SMART_LAST_DAY,             //隐藏剩余授权天数提示弹出框
#endif						   
#if ((EMBED_CA & ABVCA) == ABVCA)
	//调试使用，不强制用户显
   ABVCA_PROMPT_CLEAR = 0x00,			//正确   0
   ABVCA_STB_GET_ENTITLE,         	//智能卡获得新授权
   ABVCA_UPDATE_ECM_EMM,			//用于通知用户收到新的ECM和EMM数据
/*与节目不相关的需要显示信息*/
   ABVCA_STB_SC_NO_PAIRED,     		/*机卡不匹配*/
   ABVCA_SC_ERROR,			/* 错误的智能卡*/
   ABVCA_NO_SC,                		/*请插入智能卡  5*/
   ABVCA_CARD_IN_BEGIN,			/* 卡开始初始化*/
   ABVCA_CARD_IN_END_SUCCESS,		/* 卡初始化成功*/
   ABVCA_CARD_IN_END_FAIL,		/* 卡初始化失败*/
   ABVCA_READ_WRITER_ERR,			/*卡交互失败*/
   ABVCA_SC_PIN_RESET,			/*密码重置成功   10*/
   ABVCA_STB_SC_PAIRED,			/*机卡配对成功*/
   ABVCA_STB_SC_FREE_PAIRED,		/*解除机卡配对成功*/
   ABVCA_STB_SC_PAIRED_FAILED,		/*机卡配对失败*/
  // ABVCA_STB_MODIFY_WATCH_TIME_SUC,	/*修改观看时间成功*/
   //ABVCA_STB_MODIFY_WATCH_TIME_FAILED,	/*修改观看时间失败  15*/
   ABVCA_NOT_IN_WATCH_TIME,		/*不在设置的节目观看时间之内*/
/*与节目相关需要显示的信息   */
   ABVCA_OUT_OF_DATE,			/*智能卡过期*/
   ABVCA_NO_ENTITLE,           		/*没有授权*/
   ABVCA_IPPV_PRO_NO_ENOUGH_TOKEN,	/*IPPV节目,余额不足*/   
   ABVCA_STB_AREA_RESTRECT,		/*区域阻塞*/
   ABVCA_CA_NO_PAIRED,			/*需要机卡配对   30*/
   ABVCA_ECM_UNKNOWEN_ERROR,		/*错误的节目信息*/
   
   ABVCA_WAIT_ENTITLE,				 /*等待接收授权*/
   ABVCA_STBID_NULL,			/*STBID 为空，需要先烧写stbid*/
   ABVCA_ALREADY_PAIRED,		/*卡已绑定，此命令无效*/
   ABVCA_CHIP_NOT_MATCH,		/*flash 主芯片不匹配*/
   ABVCA_NOT_CONTACT_MASTER,	/*没有母卡*/
   ABVCA_CLEAR_IPPV_SHOW,
   ABVCA_CHANNEL_EMM_FP,
   ABVCA_STB_EXTEND,
   ABVCA_FORBID_PVR,
   
   ABVCA_MAIL_FULL,			/*邮件已满*/
   ABVCA_GET_MAIL,			/*邮箱中有未读邮件*/
   ABVCA_GET_SUB ,			/*有新的屏显*/
   ABVCA_GET_OTA,				/*有新的OTA信息*/ 
   ABVCA_EMM_FINGERPRINT,			/*User Fingerprint   20*/
   ABVCA_MATURE_PRO,           		/*成人级节目*/
   ABVCA_IPPV_PRO,           		/*IPPV节目    25*/  
   ABVCA_STB_FINGERPRINT,			/* 显示fingerprint*/
   ABVCA_STB_CLEAR_FINGERPRINT,		/*擦除fingerprint的显示*/
   ABVCA_CLEAR_EMM_FP,				/*擦除正在显示的EMM 指纹*/
   ABVCA_CLEAR_CHANNEL_EMM_FP,		/*擦除正在显示的对Channel 的EMM 指纹*/
   									/*收到此消息，擦除EMM指纹，STB不再定时显示EMM指纹*/
#endif	
#if ((EMBED_CA & UNITENDCA) == UNITENDCA)
    UNITENDCA_PROMPT_INFO_00 = 0x00,    //非加扰节目
    UNITENDCA_PROMPT_INFO_01,           //uti安全芯片错误
    UNITENDCA_PROMPT_INFO_02,           //uti安全芯片无效
    UNITENDCA_PROMPT_INFO_03,           //终端没有此运营商
    UNITENDCA_PROMPT_INFO_04,           //nvram错误
    UNITENDCA_PROMPT_INFO_05,           //没有信号
    UNITENDCA_PROMPT_INFO_06,           //节目异常，请联系运营商
    UNITENDCA_PROMPT_INFO_07,           //节目没有授权
    UNITENDCA_PROMPT_INFO_08,           //节目解扰成功
    UNITENDCA_PROMPT_INFO_09,           //节目区域限制播出
    UNITENDCA_PROMPT_INFO_10,           //节目成人级别限制
    UNITENDCA_PROMPT_INFO_11,           //指纹显示
    UNITENDCA_PROMPT_INFO_12,           //购买信用受限
    UNITENDCA_PROMPT_INFO_13,           //节目预览
    UNITENDCA_PROMPT_INFO_14,           //产品已经购买
    UNITENDCA_PROMPT_INFO_15,           //授权记录达到最大数
    UNITENDCA_PROMPT_INFO_16,           //未开户
    UNITENDCA_PROMPT_INFO_17,           //条件禁播
    UNITENDCA_PROMPT_INFO_18,           //密码已重置
    UNITENDCA_PROMPT_INFO_19,           //链接服务器失败
    UNITENDCA_PROMPT_INFO_20,           //本节目受drm保护
    UNITENDCA_PROMPT_INFO_21,           //uti安全芯片锁定
    UNITENDCA_PROMPT_INFO_22,           //uti安全芯片解除锁定
    UNITENDCA_PROMPT_INFO_23,           //重要邮件显示
    UNITENDCA_PROMPT_INFO_24,           //重要邮件掩藏
    UNITENDCA_PROMPT_INFO_10_HIDE,      //成人级别设置掩藏
#endif

#if ((EMBED_CA & THTFCA) == THTFCA)
    THTFCA_CLEAR_SCREEN =  0x00,         // 清屏。
    THTFCA_UNSUPPORTED_FRONTEND,         // 非本系统加密，无法收看。
    THTFCA_GCA_BLOCKED,                  // 区域阻塞，无法收看此节目。
    THTFCA_BLACKLISTED,                  // 您被列入了黑名单，无法收看此节目。
    THTFCA_USER_FROZEN,                  // 该用户被前端禁用
    THTFCA_USER_UNFROZEN,                // 该用户被前端解冻
    THTFCA_NOT_IN_WORKING_PERIOD,        // 系统不在工作时段内
    THTFCA_NO_SUCH_ENTITLEMENT,          // 没有授权，无法收看此节目。
    THTFCA_EMERGENCY_BROADCASTING,       //应急广播
    THTFCA_ENTITLEMENT_OVERDUE,          // 用户授权已过期
    THTFCA_INACTIVE,                     // 系统尚未激活
    THTFCA_ACTIVE_ERROR,                 // 激活错误
    THTFCA_RECOVER_PIN,                  // PIN码已恢复为默认值000000
    THTFCA_ATTRIBUTE_BLOCKING,           // 用户遭到“自定义属性”屏蔽
#endif

#if ((EMBED_CA & LXDTCA) == LXDTCA)
    LXDTCA_MESSAGE_CANCEL_TYPE = 0x00,  /*清除CAMESSAGE显示*/
    LXDTCA_MESSAGE_BADCARD_TYPE,	    /*无法识别卡*/
    LXDTCA_MESSAGE_EXPICARD_TYPE,		/*智能卡已经过期，请更换新卡*/
    LXDTCA_MESSAGE_INSERTCARD_TYPE,     /*加扰节目，请插入智能卡*/
    LXDTCA_MESSAGE_NOOPER_TYPE,			/*卡中不存在节目运营商*/
    LXDTCA_MESSAGE_BLACKOUT_TYPE,		/*条件禁播*/
    LXDTCA_MESSAGE_WATCHLEVEL_TYPE,		/*节目级别高于设定观看级别*/
    LXDTCA_MESSAGE_PAIRING_TYPE,		/*节目要求机卡对应*/
    LXDTCA_MESSAGE_NOENTITLE_TYPE,		/*没有授权*/
    LXDTCA_MESSAGE_NOMONEY_TYPE,		/*卡内金额不足*/
    LXDTCA_MESSAGE_ERRREGION_TYPE,      /*区域不正确*/
    LXDTCA_MESSAGE_STOP_SERVICE,		/*用户已停机*/
    LXDTCA_MESSAGE_STB_CARD_NOMARCH,	/*机卡不匹配*/
    LXDTCA_MESSAGE_INSERT_PARENTCARD,   /*请插入母卡认证*/
    LXDTCA_MSSAGE_CARDINIT_FAIL,		/*卡初始化失败*/
    LXDTCA_MSSAGE_CHILDCARD_AUTHE_FAIL,	/*子卡认证失败*/
    LXDTCA_MSSAGE_CHILDCARD_AUTHE_SUCCE,/*子卡认证成功*/
    LXDTCA_MSSAGE_CHILDCARD_INSERT,		/*请插入认证子卡*/
    LXDTCA_MSSAGE_CHILDCARD_CANCELOK,	/*子卡取消成功*/
    LXDTCA_MSSAGE_CHILDCARD_SETUPOK,	/*子卡设置成功*/
    LXDTCA_MSSAGE_PARENT_CONFIRM_FAIL,	/*母卡确认失败*/
    LXDTCA_MSSAGE_PARENT_CONFIRM_SUCCE,	/*母卡确认成功*/
#endif

#if ((EMBED_CA & YJCA) == YJCA)
    YJCA_CANCEL_TYPE = 0x00,					/*取消当前的显示  0*/
    YJCA_BADCARD_TYPE,			 		        /*无法识别卡，不能使用*/
	YJCA_EXPICARD_TYPE,			 		        /*智能卡已经过期，请更换新卡*/
    YJCA_INSERTCARD_TYPE,			 		    /*请插入智能卡*/
    YJCA_STOP_SERVICE,				 		    /*用户已停机*/
    YJCA_CONDITIONSTOP_TYPE,		    		/*条件禁播          5*/
    YJCA_PAIRING_TYPE,				 		    /*机卡不匹配*/
    YJCA_NOENTITLE_TYPE,			 		    /*无有效授权*/
    YJCA_DECRYPTFAIL_TYPE,			 		    /*节目解密失败*/
    YJCA_ERRREGION_TYPE,          		 	    /*请勿跨区域使用机顶盒*/
    YJCA_INSERTMAIN_CARD,					    /*请插入母卡认证  10*/
    YJCA_CARDINIT_SUCCE,			 		    /*卡初始化成功*/
    YJCA_CARDINIT_FAIL,				 		    /*卡初始化失败*/
    YJCA_CARD_AUTHENTICAT_FAIL,	 		        /*字卡认证失败*/
    YJCA_CARD_AUTHENTICAT_SUCCE, 	     		/*子卡认证成功*/
    YJCA_CARD_SUB_INSERT,			    		/*请插入认证子卡    15*/
    YJCA_CARD_SUB_CANCEL,			    		/*子卡取消成功*/
    YJCA_CARD_SUB_SETUP,			    		/*子卡设置成功*/
    YJCA_CARD_MAIN_CONFIR_FAIL,	    		    /*母卡确认失败*/
    YJCA_CARD_MAIN_CONFIR_SUCCE,	    		/*母卡确认成功*/
    YJCA_NOT_YJCA,				    		    /*非英集CA，不能解密节目  20*/
    YJCA_CARD_ERROR,				    		/*卡类型与机顶盒类型不相符*/ 
    YJCA_STRING,
#endif

#if ((EMBED_CA & SCCA) == SCCA)
    SCCA_MESSAGE_CANCEL_TYPE = 0x00,                /*清除*/
    SCCA_MESSAGE_BADCARD_TYPE,						/*无法识别卡，不能使用*/
    SCCA_MESSAGE_EXPICARD_TYPE,						/*智能卡已经过期，请更换新卡*/
    SCCA_MESSAGE_CARD_INIT_TYPE,						/*智能卡正在初始化*/
    SCCA_MESSAGE_INSERTCARD_TYPE,					/*加密节目，请插入智能卡*/
    SCCA_MESSAGE_CARD_INIT_ERR_TYPE,					/*智能卡初始化失败*/
    SCCA_MESSAGE_STB_NO_CARD_TYPE,				/*机顶盒中不存在智能卡*/
    SCCA_MESSAGE_CARD_INIT_OK_TYPE,				/*智能卡初始化完成*/
    SCCA_MESSAGE_NOOPER_TYPE,						/*卡中不存在节目运营商*/
    SCCA_MESSAGE_CARDSTOP_TYPE,						/*智能卡已停用*/
    SCCA_MESSAGE_OUTWORKTIME_TYPE,					/*不在工作时段内*/
    SCCA_MESSAGE_WATCHLEVEL_TYPE,					/*节目级别高于设定观看级别*/
    SCCA_MESSAGE_PAIRING_TYPE,						/*机卡没有对应*/
    SCCA_MESSAGE_NOENTITLE_TYPE,						/*您没有购买该节目*/
    SCCA_MESSAGE_DECRYPTFAIL_TYPE,					/*节目解密失败*/
    SCCA_MESSAGE_NOMONEY_TYPE,						/*卡内金额不足*/
    SCCA_MESSAGE_ERRREGION_TYPE,						/*区域不正确*/
      SCCA_MESSAGE_FINGER_SHOW_TYPE,					/*指纹显示*/
      SCCA_MESSAGE_FINGER_DISAPPEAR_TYPE,				/*指纹隐藏*/
    SCCA_MESSAGE_CARDNOTACTIVE_TYPE,					/*智能卡未激活*/
    SCCA_MESSAGE_CARDLOGOUT_TYPE,					/*智能卡已注销*/
    SCCA_MESSAGE_CONDITION_CTL_TYPE,					/*该产品被限播*/
    SCCA_MESSAGE_DESCRA_NOENTITLE_TYPE,				/*授权已到期，请联系运营商*/
    SCCA_MESSAGE_ENTITLE_UPDATE_TYPE,				/*授权更新中，请稍等！*/
    SCCA_MESSAGE_CARD_UNWONTED_TYPE,					/*智能卡内部异常*/
    SCCA_MESSAGE_CHANGEPRO_TOO_FAST_TYPE,			/*请不要频繁切台*/
    SCCA_MESSAGE_MS_PAIR_OK_TYPE,		    		/* 子母卡配对成功 */
    SCCA_MESSAGE_MS_PAIR_FAILED_TYPE,				/* 子母卡配对失败,请重新插入正确的母卡 */
    SCCA_MESSAGE_MS_REPAIR_TYPE,						/* 子卡需重新和母卡配对 */
    SCCA_MESSAGE_CARD_MATCH_OK_TYPE,					/*机卡配对成功*/
    SCCA_MESSAGE_CARD_REMATCH_TYPE,					/*重新机卡配对*/
    SCCA_MESSAGE_CANCEL_MATCH_TYPE,					/*取消机卡配对*/

    SCCA_MESSAGE_NEWEMAIL_TYPE,						/* 显示新邮件图标 */
    SCCA_MESSAGE_OVEREMAIL_TYPE,						/* 显示邮件存满 */
    SCCA_MESSAGE_HIDE_NEWEMAIL_TYPE,					/* 隐藏新邮件图标*/
    SCCA_MESSAGE_EXIGENT_PROG_TYPE,					/*紧急广播*/
    SCCA_MESSAGE_EXIGENT_PROG_STOP_TYPE,				/*停止紧急广播*/
    SCCA_MESSAGE_CARD_UNLOCK_OK_TYPE,				/*智能卡密码解锁成功*/
    SCCA_MESSAGE_PURSER_UPDATE_TYPE,					/*电子钱包更新*/
    SCCA_MESSAGE_NET_ERR_LOCK_TYPE,					/*网络异常，卡被锁定*/
    SCCA_MESSAGE_SYSTEM_ERR_LOCK_TYPE,				/*系统异常，卡被锁定*/
    SCCA_MESSAGE_NET_ERR_UNLOCK_TYPE,				/*网络异常解锁*/
    SCCA_MESSAGE_SYSTEM_ERR_UNLOCK_TYPE,				/*系统异常解锁*/

    /*OSD消息*/
    SCCA_MESSAGE_SHOWOSD_TYPE,						/*显示OSD消息*/
    SCCA_MESSAGE_HIDEOSD_TYPE,						/*隐藏OSD消息*/

    /*提示对话框*/
    SCCA_MESSAGE_CARDISDUE_TYPE,						/*智能卡处于欠费催缴*/
    SCCA_MESSAGE_IPPVBUY_TYPE,						/*IPPV购买提示框 */
    SCCA_MESSAGE_IPPV_OUTTIME_TYPE,					/*IPPV节目过期*/
    SCCA_MESSAGE_HIDE_IPPVBUY_TYPE,					/*隐藏 IPPV购买提示框 */
    SCCA_MESSAGE_CONDITION_SEARCH_TYPE,				/*条件NIT表搜索节目*/
#endif

#if ((EMBED_CA & COLABLECA) == COLABLECA)

	HCN_NO_MSG = 0,		//无CA信息
	HCN_PLS_INSERT_SMC,	//请插卡
	HCN_SMC_INSERT,		//智能卡插入
	HCN_SMC_REMOVED,		//智能卡取出
	HCN_SMC_INIT_SUCCEES,	//智能卡初始化成功
	HCN_SMC_INIT_FAIL, 	//智能卡初始化失败
	HCN_SMC_READ_ERROR,	//读卡出错
	HCN_CARD_NOMATCH,		//机卡不配对
	HCN_MATCH_SUCCESS, 	//配对成功
	HCN_MATCH_FAIL,		//配对失败
	HCN_NO_RIGHT,			//无节目权限010
	HCN_TIMEEXPIRED,		//有效期已过
	HCN_INSTANCE_CLOSE,	//即时关断
	HCN_OUT_WORKTIME,		//不在工作时段
	HCN_MASK_LIMITED,		//区域限播
	HCN_OUT_LEVEL, 		//不满足收看级别
	HCN_TYPE_LIMIT,		//录像控制限制
	HCN_PPV,				//ppv节目
	HCN_PPC,				//ppc节目
	HCN_PPV_AWARD_SUCCESS, //ppv节目授权成功
	HCN_PPV_AWARD_FAIL,	//ppv节目授权失败20
	HCN_PPC_AWARD_SUCCESS, //ppc节目授权成功
	HCN_PPC_AWARD_FAIL,	//ppc节目授权失败
	HCN_REMAIN_DAY,		//收看有效期还有 9天，请续费
//////////////////////
	HCN_CANCEL_MATCH,		//已取消配对
	HCN_CANCEL_MATCHFAIL,	//取消配对失败
	HCN_SMC_NOTOPEN,//26		//智能卡未启用
	HCN_CREDIT_CONUT_FULL, //点数已满
	HCN_UNRECOGNISED_CARD, //无法识别智能卡
	HCN_ERRORVERSION_CARD, //智能卡版本错误
	HCN_ippv_eventzreo,	//ippv事件号为零
 /////////////////////////		
	//命令通知
	HCN_MAIL_NOTIFY = 0x62,//邮件
	HCN_SUBTITLE_NOTIFY, //字幕
	HCN_DISPALY_FINGER_NOTIFY,//显示指纹
	HCN_STOP_FINGER_NOTIFY,	//停止指纹	
	HCN_DISPLAY_URGE_FEE_NOTIFY,//display upge_fee
	HCN_STOP_URGE_FEE_NOTIFY,//stop display	upge_fee	
	HCN_IPPV_SHOW,		//IPPV show
	HCN_IPPV_CLOSE,		//IPPV close
	HCN_REFILT_PMT,		//重新处理PMT，如果符合条件则重新启动CA

#endif

#if ((EMBED_CA & XSMCA) == XSMCA)
    XSMCA_SC_NORMAL = 0x00,                 // 0  正常状态
    XSMCA_SC_NO_CARD,   			        // 1   未插卡 
    XSMCA_SC_NO_PPV_RIGHT,  		        // 2  没有PPV授权 
    XSMCA_SC_NO_PPC_RIGHT,  		        // 3  没有PPC授权 
    XSMCA_SC_PARENT_CTRL,  	                // 4  家长控制 
    XSMCA_SC_NO_CONDITION,  	            // 5  条件限播 
    XSMCA_SC_INVALID_CARD,                  // 6  无效卡 
    XSMCA_SC_TYPEERROR,		                // 7   子母卡喂养失败,插入智能卡类型错误 
    XSMCA_SC_NEEDFEED,		                // 8   子卡需要与母卡对应,请喂养子卡 
    XSMCA_SC_ZONEERROR,                     // 9   区域错误 
    XSMCA_SC_FEEDTIMEERROR,                 // 10  喂养时间错误 
    XSMCA_SC_FEEDDATEERROR,                 // 11  喂养日期错误 
    XSMCA_SC_FEEDSYSTEMTIMEERROR,           // 12  系统时间没有正确获取,喂养失败 
    XSMCA_SC_ACSEVICEIDEERROR,              // 13 加扰机AC 错误 
    XSMCA_SC_CARDSTBNOTPAIR,                // 14  加扰机AC 错误 
    XSMCA_SC_CARDENTITLEREMAINTDAY,         // 15  授权剩余天数 
    XSMCA_SC_UPDATAINT,                     //16   智能卡数据更新，请勿断电! 
    XSMCA_SC_EXIRATION_REMINDER,            // 17  到期提醒! 
    XSMCA_SC_HIDE_AUTH_REMAINDAY,           //18  擦除授权剩余天数 提示
#endif
	CA_OSD_NONE,
} hrca_ca2us_state_t;

/*---------- -----------------进度条提示信息------------------------ ---------*/

#define CA_SCALE_DATA		    1     /* 升级数据接收中 */
#define CA_SCALE_SCUPDATE       2     /* 智能卡升级中 */


//升级成功状态
extern uint8_t g_cur_updata_time_flag;

/*----------------------------反授权信息----------------------------------------*/

//反授权信息总数
extern uint8_t d_DetitleCount;

//反授权
#if ((EMBED_CA & CDCA) == CDCA)
//extern hrcdca_detitleInfo_t  d_DetitleInfo_cdca[10];
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_detitleInfo_t   d_DetitleInfo_dvtca[10];
#endif


/*-----------------------------节目信息-------------------------------------------*/

//购买的节目总数
extern uint8_t d_ServiceCount;

//购买的节目信息
#if ((EMBED_CA & CDCA) == CDCA)
//extern hrcdca_serviceEntitles_t *d_ServiceEntitles_cdca; //[ENTITLE_COUNT_CDCA];
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_serviceEntitles_t d_ServiceEntitles_dvtca[ENTITLE_COUNT_DVTCA];
#endif



/*------------------------------子母卡信息----------------------------------------*/

//子母卡配对信息
#if ((EMBED_CA & CDCA) == CDCA)
extern hrcdca_scAddedInfo_t d_ScAddedInfo_cdca[OPERATOR_COUNT_CDCA]; 
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_scAddedInfo_t d_ScAddedInfo_dvtca[OPERATOR_COUNT_DVTCA]; 
#endif


/*------------------------------IPP信息-----------------------------------------------*/

//IPPV节目总数
extern uint16_t d_IPPVProNum;

//ippv ecm pid
extern uint16_t IppvECMPID;

//ippv类型
extern uint8_t IppvType;

//查看ipp 个数
extern uint16_t viewIppCount;  

//ipp订购个数
extern uint16_t bookIppCount;

//弹出框购买ipp节目
#if ((EMBED_CA & CDCA) == CDCA)
extern hrcdca_ippBuyInfo_t d_IppBuyInfo_cdca;
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_ippBuyInfo_t d_IppBuyInfo_dvtca;
#endif
#if ((EMBED_CA & CTICA) == CTICA)
extern hrctica_ippBuyInfo_t d_IppBuyInfo_ctica;
#endif
#if ((EMBED_CA & MGCA) == MGCA)
extern hrmgca_ippBuyInfo_t d_IppBuyInfo_mgca;
#endif
#if ((EMBED_CA & DSCA) == DSCA)
extern hrdsca_ippBuyInfo_t d_IppBuyInfo_dsca;
#endif
#if ((EMBED_CA & GOSCA) == GOSCA)
extern hrgosca_ippBuyInfo_t d_IppBuyInfo_gosca;
#endif
#if ((EMBED_CA & ABVCA) == ABVCA)
extern hrabvca_ippBuyInfo_t d_IppBuyInfo_abvca[2];
#endif
#if ((EMBED_CA & XGCA) == XGCA)
extern hrxgca_ippBuyInfo_t d_IppBuyInfo_xgca;
#endif
#if ((EMBED_CA & LXDTCA) == LXDTCA)
extern hrlxdtca_ippBuyInfo_t d_IppBuyInfo_lxdtca;
#endif
#if ((EMBED_CA & DVNCA) == DVNCA)
extern hrdvnca_ippBuyInfo_t d_IppBuyInfo_dvnca;
#endif

//IPPV节目信息
#if ((EMBED_CA & CDCA) == CDCA)
//extern hrcdca_viewedIpp_t d_ViewedIPPV_cdca[300];
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_viewedIpp_t d_ViewedIPPV_dvtca[300];
#endif
#if ((EMBED_CA & SCCA) == SCCA)
extern hrscca_ippBuyInfo_t d_IppBuyInfo_scca;
#endif
#if ((EMBED_CA & COLABLECA) == COLABLECA)
extern hcn_ipptv_t d_IppBuyInfo_hcnca;
#endif
/*--------------------------------钱包信息-----------------------------------------*/

//钱包总数
extern uint8_t d_SlotCount;

//钱包ID
extern uint8_t d_SlotID[20];

//充值金额
extern uint32_t ChargeValue;

//钱包信息
#if ((EMBED_CA & CDCA) == CDCA)
//extern hrcdca_slotInfo_t  d_SlotInfo_cdca[20];
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_slotInfo_t  d_SlotInfo_dvtca[20];
#endif
/*-------------------------------运营商信息--------------------------------------*/

//运营商编号
extern uint16_t d_TVSId[5];

//运营商总数
extern uint8_t d_OperatorCount;


//运营商信息
#if ((EMBED_CA & CDCA) == CDCA)
//extern hrcdca_operatorInfo_t d_OperatorInfo_cdca[OPERATOR_COUNT_CDCA];
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_operatorInfo_t d_OperatorInfo_dvtca[OPERATOR_COUNT_DVTCA]; 
#endif

/*-------------------------------邮件信息-----------------------------------------*/

//邮件总数
extern uint16_t d_EmailCount;

//未读邮件个数
extern uint16_t d_NewEmailCount;

//剩余邮件个数
extern uint16_t d_EmptyEmailCount;

//邮件头
#if ((EMBED_CA & CDCA) == CDCA)
extern hrcdca_emailInfo_t d_EmailInfo_cdca[EMAIL_COUNT_CDCA];
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_emailInfo_t d_EmailInfo_dvtca[EMAIL_COUNT_DVTCA];
#endif


//邮件内容
#if ((EMBED_CA & CDCA) == CDCA)
//extern hrcdca_emailContent_t d_EmailContent_cdca;
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_emailContent_t d_EmailContent_dvtca;
#endif

/*------------------------------智能卡信息-------------------------------------*/

//观看级别
extern uint8_t d_ViewRating;

//智能卡工作起始时间
extern uint8_t d_StartHour, d_StartMinute, d_StartSecond;

//智能卡工作结束时间
extern uint8_t d_EndHour, d_EndMinute, d_EndSecond;

//智能卡基本信息
#if ((EMBED_CA & CDCA) == CDCA)
extern hrcdca_scBasicInfo_t d_ScBasicInfo_cdca;
extern hrcdca_scmInfo_t d_ScmInfo_cdca;
#endif
#if ((EMBED_CA & DVTCA) == DVTCA)
extern hrdvtca_scBasicInfo_t d_ScBasicInfo_dvtca;
#endif
#if ((EMBED_CA & CTICA) == CTICA)
extern hrctica_replyFalg_t caCoreReply;
#endif
#if ((EMBED_CA & MGCA) == MGCA)
extern hrmgca_scBasicInfo_t d_ScBasicInfo_mgca;
#endif
#if ((EMBED_CA & XGCA) == XGCA)
extern hrxgca_scBasicInfo_t d_ScBasicInfo_xgca;
#endif

/*------------------------------机卡对应--------------------------------------*/

//机卡对应总数
extern uint8_t  d_pNumber;

//机卡对应列表
extern uint8_t d_pSTBIdList[5][13];

//机卡对应状态
extern int32_t d_pairedStatue;


/*-------------------------------应急广播---------------------------------*/

//获取当前节目的频道号
extern uint16_t g_ChNO; 

//是否禁止切台操作,TRUE:不允许切台;FALSE:允许切台
extern uint8_t forbidSwitchChannel;

//记录应急广播的持续时间长度
extern uint16_t broadcastDuration;    

//记录是否有应急广播了,TRUE:有;FALSE:无
extern uint8_t g_bUrgency; 

 //记录是否第一次有应急广播
extern uint8_t g_First_Urgency;

 //应急广播时间
extern uint32_t g_wDuration;       

			  
/*-------------------------------其他---------------------------------------*/

//剩余插拔卡次数
extern uint8_t TryTimes;

//机顶盒id
extern uint8_t d_StbId[12];    //机顶盒id

//是否是自动配对(only for DVNCA)
extern CA_BOOL g_bAutoPair;   

/*0： 当前播放的节目为电视节目 1：当前播放的节目为广播节目*/
extern uint8_t ChangeFlag;

/*0： 强制换台时没有进行电视广播的转换 1：强制换台时进行了电视广播的转换*/
extern uint8_t ToChange;

//升级成功状态
extern uint8_t g_cur_updata_time_flag;

extern uint8_t cwctrl;

extern uint8_t cwctrl_t;

extern uint16_t d_NearDay;//授权剩余天数


/***********************************End of Static Variables for CA**************************************/

/************************************************************************************************/
/**********************************Function for CA******************************************************/
/**********************************各平台CA显示部分函数声明******************************************************/
/************************************************************************************************/
extern void HRCA_ShowAnnouncement(char * data, hrca_ca2us_state_t u8MessageType);
extern void HRCA_ShowEmailNotifyMessage(hrca_ca_email_e byShow);
extern void HRCA_ShowSuperLookPic(uint8_t picFlag,CA_BOOL* state);
extern void HRCA_AutoChargeMessage(void* ChargeInfo);
extern void HRCA_ShowPromptMessage(uint32_t u32EcmPID, hrca_ca2us_state_t MessageType);
extern void HRCA_TimerShowPromptMessage(uint32_t u32EcmPID, hrca_ca2us_state_t u8MessageType,uint32_t time);
extern void HRCA_FlashShowPromptMessage(uint32_t u32EcmPID, hrca_ca2us_state_t u8MessageType,uint32_t time, uint32_t show_time, uint32_t hide_time);
extern void HRCA_ShowOperateMsg(uint8_t bMessage);
extern void HRCA_ShowLogoIcon(hrca_ca2us_state_t bLogoType, uint16_t keep_seconds);
extern void HRCA_SaveOsdInit(uint8_t OSDMaxNum);
extern CA_BOOL HRCA_SaveOsdMessage(char* u8OsdData);
extern char* HRCA_GetOsdMessage(void);
extern void HRCA_SaveOsdExit(void);
extern void HRCA_ShowOsdMessage(uint8_t u8Style, char* u8OsdData, uint8_t u8Prio,uint32_t time, uint32_t judge_value);
extern void HRCA_ShowOsdMessageWithColor(uint8_t u8Style, char* u8OsdData, uint8_t u8Prio,uint16_t u16Time, uint8_t u8JudgeValue, uint8_t *u8bgColor, uint8_t *u8fontColor, uint8_t u8FontSize);
extern void HRCA_HideOsdMessage(uint8_t u8Style);
extern void HRCA_ShowIntervalOsdMessage(uint8_t u8Style, char* u8OsdData,uint32_t u32IntervalTime,uint8_t u8JudgeValue);
extern void HRCA_HideIntervalOsdMessage(uint8_t u8Style);
extern uint8_t HRCA_GetOSDStatus(uint8_t u8Style);
extern void HRCA_ShowFinger(uint32_t u32EcmPID, char *CardIDarray, uint32_t u32Duration, uint8_t ShowOrHide);
extern void HRCA_ShowEmmFinger(char *CardIDarray, uint32_t u32Duration, uint8_t ShowOrHide);
extern void HRCA_ShowSuperFinger(uint32_t u32EcmPID, char *CardIDarray, uint32_t u32Duration, uint8_t ShowOrHide);
extern void HRCA_StartIppvBuyDlg(uint32_t u32EcmPID, uint32_t u32Ippv, void *ippvBuyInfo); //hanjf
extern int32_t HRCA_IppvBuy(uint8_t* u8Pin,uint8_t buyIppType, void *ippvBuyInfo);
extern void HRCA_HideppvBuyDlg(uint32_t ecmPid, uint32_t IppType);
extern void HRCA_ForceSwitchChannel(void *ChannelInfo, uint8_t Type);
extern void HRCA_CancelForceSwitchChannel(void *cType);
extern void HRCA_GetCurentEpgTime(uint8_t *pu8Time);
extern uint8_t	HRCA_SendStringToCom(uint8_t *u8String, uint16_t u16StrLen);
extern void HRCA_ShowProgressStrip(uint8_t u8Progress, uint8_t u8Type);
extern void HRCA_HideProgressStrip(void);
extern void HRCA_RefreshShowMenu(void);
extern void HRCA_ShowSuperOSD(void *oType,uint8_t ShowOrHide);
extern void HRCA_ShowFeedStatus(uint32_t *FeedStatus);
extern void HRCA_STBShowDialog(hrca_ca2us_state_t u8MessageType, uint32_t value);
extern void HRCA_STBHideDialog(hrca_ca2us_state_t u8MessageType, uint32_t value);
extern uint8_t HRCA_Startplay(void);
extern uint8_t HRCA_Stopplay(void);
extern void HRCA_LanChange(uint8_t lanType);
extern void HRCA_RemoteLock(uint8_t LockOrUnlock);		


/*************************************Static  Variable  for  2019 *******************************************/
/***********************************   2309CA显示部分全局变量声明 ******************************************/
/************************************************************************************************/

/***********************************End of Static Variables for 2019**************************************/

/************************************************************************************************/
/**********************************Function for 2019******************************************************/
/********************************2309CA显示部分函数声明*************************************************/
/************************************************************************************************/
#if HR_CA_SCROLL_ON_OFF
extern D_HScroll HRCA_Text_Scroll_Create(void);
extern D_Result HRCA_Text_Scroll_Destroy(D_HScroll hscroll);
extern D_Result HRCA_Text_Scroll_Stop(D_HScroll hscroll);
extern D_Result HRCA_Text_Scroll_Start(
    D_HScroll hscroll, 
    D_U32 position, 
    D_Char* text, 
    D_U32 bg_color, 
    D_U32 text_color, 
    D_U8  font_size, 
    D_U32 scroll_speed, 
    D_U32 repeat_times, 
    D_U32 duration, 
    D_Bool immediate, 
    D_ScrollCallback callback);
extern D_ScrollState HRCA_Text_Scroll_GetState(D_HScroll hscroll);

extern int  HRCA_Scroll_Create(void);
extern D_Result HRCA_TopScroll_Start(D_HScroll handle, char *text, uint32_t repeat, uint32_t duration);
extern D_Result HRCA_BottomScroll_Start(D_HScroll handle, char *text, uint32_t repeat, uint32_t duration);
extern CA_BOOL HRCA_DeleteEnterFlags(char* OsdMessageContent, uint32_t len);
#endif
/**************************************end of function for CA********************************************************/


#endif

#endif

