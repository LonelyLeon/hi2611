/** @file
* @brief _D_BATTERY_H_
*/

#ifndef _D_BATTERY_H_
#define _D_BATTERY_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/**@brief 电池相关gpio 初始化*/
D_Result d_battery_init(D_U16 min,D_U16 max)D_FUNCPOSTFIT;
/**@brief 电池相关gpio 关闭*/
D_Result d_battery_uninit(void)D_FUNCPOSTFIT;
/**@brief 电池电量检测
*@return P_BATTERY_VOLUME 电池电量检测结果*/
D_U8  d_battery_get_batleav(void)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
