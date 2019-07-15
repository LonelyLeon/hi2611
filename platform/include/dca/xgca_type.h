/***********************************************************************************************
File Name        : 

Description      :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  HMD_DVBC

Author(s)        :  lim

Notes              :  

History            :

Version    Date        	  Author(s)      Description         Referrence

1.0        2012-11-02      lim            created              ---
1.1		   2013-03-06	   lim			  modify               ---

*************************************************************************************************/

#ifndef XGCA_TYPE_H_
#define XGCA_TYPE_H_

/*类别码*/
#define CLA_GENERAL				0x00	  //通用命令
#define CLA_SPECIAL				0x80	  

/*指令码*/
//通用命令 指令
#define INS_GET_RESPONSE		0xc0	  //Get Response

//基本收视命令 指令
#define INS_TS_PACKAGE			0x33	  //发送TS数据包
#define INS_IPPV				0x35	  //是否收看IPPV

//基本信息命令 指令
#define INS_CAS_LIST			0x40	  //获得支持的CAS列表
#define INS_ECM_FILTER			0x41	  //获得ECM过滤参数
#define INS_EMM_FILTER			0x41	  //获得EMM过滤参数
#define INS_GET_CARD_INFO		0x56	  //获取卡信息
#define INS_GET_PPC				0x43	  //获得PPC授权情况列表
#define INS_ZONE_LIMI			0x45	  //获取卡区域限制情况
										  
//机卡配对命令 指令
#define INS_VERIFY_MATCH		0x8d	  //校验机卡配对
#define INS_BOUND				0x8d	  //请求绑定卡片
										  
//子母卡命令 指令
#define INS_GET_FEED_DATA		0x63	  //获取喂卡数据
#define INS_FEED_CARD			0x61	  //喂卡
#define INS_GET_MAIN_SUB_CARD	0x62	  //获取卡的子母卡信息


/*返回值（sw1 sw2）*/

//常规应答
#define SUCCESS_XGCA			0x9000	  //成功
#define INVALID_INSTRUCTION		0x6000	  //非法命令
#define GET_RESPONSE			0x61	  //(0x61是sw1的值)要求终端设备发送Get Response 命令以取得缓冲区数据. sw2的值是缓冲区数据长度。
#define WRONG_LENGTH			0x6700	  //域长度错误
#define CARD_FORMAT1_FAIL		0x6868	  //卡片未经格式化
#define CARD_FORMAT2_FAIL		0x68fc	  //卡片未完成应用格式化
#define WRONG_P1_P2				0x6a86	  //p1或p2参数错误
#define INVALID_NOT_SUPPORT		0x6a81	  //命令不支持
#define INS_WRONG_LENGTH		0x6c	  //(0x6c是sw1的值)命令数据体长度错误。应该为sw2的值。

//Get Response 命令
#define NO_DATA					0x6401	  //无数据可取

//发送TS数据包
#define TABLE_FORMAT_NOT_SUPP	0x6203	  //不支持的包格式版本
#define CA_NOT_SUPPORT			0x6204	  //不支持的CA版本
#define NET_NOT_SUPPORT			0x6205	  //不支持的网络系统
#define WRONG_FILTER			0x6206	  //错误的过滤规则
#define OPERATE_FAIL			0x6207	  //操作失败
#define START_SER_SUCCESS		0x6208	  //服务启用操作成功
#define STOP_SER_SUCCESS		0x6209	  //服务冻结操作成功
#define NEED_MATCH				0x620a	  //需要机卡配对
#define BALANCE_NOT_ENOUGH		0x620b	  //钱包余额不足
#define NEED_FEED_CARD			0x620c	  //子卡到期，需要喂卡
#define NIT_ZONE_FAIL			0x620d	  //NIT表区域验证失败
#define NEED_CORRECT_NIT		0x620e	  //卡未通过区域验证，需要正确的NIT
#define SER_STOPED				0x6244	  //服务被冻结
#define CARD_DELETED			0x62aa	  //卡被删除
#define FILE_SYS_WRONG			0x6884	  //文件系统出错
#define LEVEL_LIMITED			0x6885	  //不能收看的节目级别
#define DECRYPT_FAIL			0x6897	  //解密错误
#define NO_AUTHORIZATION		0x6899	  //无授权
#define TABLE_FORMAT_WRONG		0x6a82	  //错误的包格式

//收看IPPV
#define PAY_IPP_FAIL			0x689a	  //命令执行失败

//获得支持的CAS列表
#define P1_P2_NOT_ZERO			0x6a86	  //p1或p2不等于0
#define NO_VALID_INFO			0x6200	  //无可用的信息

//获得指定CAS的ECM\EMM过滤参数
#define CARD_INIT_FAIL			0x6200	  //卡片未完成应用初始化
#define INVALID_CAID			0x6204	  //未知的CAID

//获取卡片信息
#define CARD_NOT_INIT			0x6801	  //卡片未完成初始化

//获得PPC授权情况列表
/*
#define INVALID_CAID			0x6204	  //未知的CAID
#define FILE_SYS_WRONG			0x6884	  //文件系统出错
*/

//获取卡片区域限制情况
/*
#define CARD_NOT_INIT			0x6801	  //卡片未完成初始化
*/

//校验机卡配对
#define CARD_NOT_MATCH_STB		0x6301	  //卡未与任何STB配对
#define VERIFY_FAIL				0x6303	  //校验失败
#define VERIFY_UNEXPECTED_WRONG	0x6304	  //校验成功，但返回卡片特征码出现意外错误
#define CARD_NOT_REGISTER		0x6305	  //卡未注册

//请求绑定卡片
#define CARD_ALREADY_MATCH		0x6302	  //卡已经与某一STB配对
#define BOUND_FAIL				0x6303	  //绑定失败
#define BOUND_UNEXPECTED_WRONG	0x6304	  //绑定成功，但返回卡片特征码出现意外错误
/*
#define CARD_NOT_REGISTER		0x6305	  //卡未注册
*/

//获取喂卡数据
#define GET_FEED_FAIL			0x6280	  //卡为子卡，无法获取喂卡数据
#define UNKNOWN_TIME			0x6281	  //未知的当前时间，卡需要先获取ECM数据
/*
#define INVALID_CAID			0x6204	  //未知的CAID
*/

//喂卡
#define DONOT_NEED_FEED			0x6282	  //卡未母卡，不需要喂卡数据
#define WRONG_FEED_DATA			0x6285	  //错误的喂卡数据						

//获取卡片的子母卡信息
#define NO_EXPIRE_TIME			0x6286	  //卡是母卡，无子卡到期时间
/*
#define CARD_NOT_INIT			0x6801	  //卡片未完成初始化
*/

#endif //end XGCA_TYPE_H_
