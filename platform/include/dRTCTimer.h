/** @file
* @brief 高性能计数器
* @author 李臣
* @date 2013-11-01 李臣: 建立文件
*/
#ifndef __D_RTCTIMER_H
#define __D_RTCTIMER_H
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 高性能计数器初始化
* @return 成功D_OK, 错误D_ERR
*/
D_Result d_rtc_timer_open(void) D_FUNCPOSTFIT;

/** @brief 高性能计数器释放
* @return 成功D_OK, 错误D_ERR
*/
D_Result d_rtc_timer_close(void) D_FUNCPOSTFIT;

/** @brief 获得高性能计数器频率
* @return 高性能计数器频率(Hz)
*/
D_U64 d_rtc_timer_get_freq(void) D_FUNCPOSTFIT;

/** @brief 获得高性能计数器当前计数
* @return 高性能计数器当前计数值
*/
D_U64 d_rtc_timer_get_counter(void) D_FUNCPOSTFIT;

#define d_rtc_timer_wait_timeout_us(__usec) \
    D_MACRO_BEGIN\
        D_U64 __tick_time = __usec * d_rtc_timer_get_freq() / 1000000 + d_rtc_timer_get_counter();\
        while(d_rtc_timer_get_counter() < __tick_time);\
    D_MACRO_END

#ifdef  __cplusplus
}
#endif
#endif

