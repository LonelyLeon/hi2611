/** @file
* @brief  时间计算
* @author 龚克
* @date 2005-10-26 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 代码整理
*/

#ifndef _D_TIME_H_
#define _D_TIME_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 时间偏移(分钟为单位)*/
extern D_S16 const g_local_time_offset[];

/** @brief 格林威治标准时区*/
extern D_U8	const g_gmt_zone_id;

/** @brief 北京所在东八区*/
extern D_U8	const g_bj_zone_id;

/** @brief 时间区域标志数目*/
extern D_U8	g_local_time_offset_cnt;

/** @brief 取本地时间
* @param[in] t	格林威治时间
* @param[in] off 时区偏移
* @reutrn 返回本地时间
*/
D_Time	d_time_local (D_Time t, D_S32 offset) D_FUNCPOSTFIT;

/** @brief 取格林威治时间
@param [in] t 当前时间
@param [in] off 时区偏移
@return utc 格林威治时间
*/
D_Time	d_time_utc (D_Time t, D_S32 offset) D_FUNCPOSTFIT;

/** @brief 取得当前时间
@return curr 当前时间
*/
D_Time d_time_get_time (void) D_FUNCPOSTFIT;

/** @brief 取得当前本地时间
@return time 本地时间
*/
D_Time d_time_get_local_time (void) D_FUNCPOSTFIT;

/** @brief 设置当前时间
@param[in] t 设置时间
@return D_OK 设置成功
*/
D_Result d_time_set_time (D_Time t) D_FUNCPOSTFIT;

/** @brief 设置当前(utc)时间, 当使用时间芯片的时候使用这个接口，
调用后d_time_set_time接口就无效了。
@param[in] t 设置时间
@return D_OK 设置成功
*/
D_Result
d_time_set_time_by_timechip (D_Time t) D_FUNCPOSTFIT;

/** @brief 判断是否已经设置当前时间
@return D_TRUE 已经设置过
*/
D_Bool
d_time_had_set_time (void) D_FUNCPOSTFIT;

/** @brief 取本地时间
@param [in] 格林威治时间
@return lt  本地时间
*/
D_Time d_time_local_time (D_Time t) D_FUNCPOSTFIT;


/** @brief 取格林威治时间
@param[in] t 当前时间
@return utc 格林威治时间
*/
D_Time d_time_utc_time (D_Time t) D_FUNCPOSTFIT;


/** @brief 取当前时区
@return time_offset 时间偏移
*/
D_S32 d_time_get_time_offset (void) D_FUNCPOSTFIT;

/** @brief 设置当前时区
@param[in] off 时间偏移
*/
void d_time_set_time_offset (D_S32 off) D_FUNCPOSTFIT;

/** @brief 24小时制转为12小时制
* @param[in] hour24	24小时时间
* @param[out] hour12	存放12小时时间的缓冲区
* @param[out] pm_am	存放上下午
* @return D_OK 正确，D_ERR错误
*/
D_Result d_hour24_to_hour12( D_U8 hour24,D_U8* pm_am, D_U8* hour12 )D_FUNCPOSTFIT;

/** @brief 12小时制转为24小时制
* @param[in] hour12	12小时时间
* @param[in] pm_am	0:上午，1:下午。
* @param[out] hour24	存放24小时时间的缓冲区
* @return 返回D_OK
*/
D_Result d_hour12_to_hour24( D_U8 hour12,D_U8 pm_am,D_U8* hour24 )D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
