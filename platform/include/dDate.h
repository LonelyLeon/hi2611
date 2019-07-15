/** @file
* @brief 日期计算
* @author 龚克
* @date 2005-10-25 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 代码整理
*/

#ifndef _D_DATE_H_
#define _D_DATE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 日期*/
typedef struct {
	D_S16	year;	/**< 年(从1900算起)*/
	D_U8	mon;	/**< 月(0为1月...*/
	D_U16	yday;	/**< 一年中的第几天*/
	D_U8	mday;	/**< 每月的第几天*/
	D_U8	wday;	/**< 每周的第几天*/
	D_U8	hour;	/**< 小时*/
	D_U8	min;	/**< 分钟*/
	D_U8	sec;	/**< 秒*/
} D_Date;

typedef struct{
	D_U16	year;	/**< 年*/
	D_U8	mon;	/**< 月(1为1月...*/
	D_U8    day;      /** 日*/
	D_U8	hour;	/**< 小时*/
	D_U8	min;	/**< 分钟*/
	D_U8	sec;	/**< 秒*/
}D_Date_Ext;

/** @brief 将时间转化为日期
* @param[in] time	时间(从1970-1-1开始的秒数)
* @param[out] date 存放日期的缓冲区
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_date (D_Time time, D_Date *date) D_FUNCPOSTFIT;

/** @brief 将日期转化为时间(从1970-1-1开始的秒数)
* @param[in] date 存放日期的缓冲区
* @return 时间(从1970-1-1开始的秒数)
*/
D_Time d_date_anti (D_Date *date) D_FUNCPOSTFIT;

/** @brief 将日期时间的有效性
* @param[in] date 存放日期的缓冲区
* @return 是否有效
*/
D_Bool d_date_valid (D_Date *date) D_FUNCPOSTFIT;

/** @brief 将时间转化为日期
* @param[in] time	时间(从1970-1-1开始的秒数)
* @param[out] date_ext 存放日期的缓冲区
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_date_ext (D_Time time, D_Date_Ext *date_ext) D_FUNCPOSTFIT;

/** @brief 将日期转化为时间(从1970-1-1开始的秒数)
* @param[in] date_ext 存放日期的缓冲区
* @return 时间(从1970-1-1开始的秒数)
*/
D_Time d_date_anti_ext (D_Date_Ext*date_ext) D_FUNCPOSTFIT;

/** @brief 将日期时间的有效性
* @param[in] date_ext 存放日期的缓冲区
* @return 是否有效
*/
D_Bool d_date_valid_ext (D_Date_Ext*date_ext) D_FUNCPOSTFIT;

/** @brief 比较日期的先后
*@param [in] date1 日期
*@param [in] date2 日期
* @return date1>date2 返回1,date1<date2 返回1,date1==date2 返回0
*/
D_U8 d_compare_date(D_Date_Ext date1, D_Date_Ext date2) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
