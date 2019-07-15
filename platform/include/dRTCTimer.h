/** @file
* @brief �����ܼ�����
* @author �
* @date 2013-11-01 �: �����ļ�
*/
#ifndef __D_RTCTIMER_H
#define __D_RTCTIMER_H
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief �����ܼ�������ʼ��
* @return �ɹ�D_OK, ����D_ERR
*/
D_Result d_rtc_timer_open(void) D_FUNCPOSTFIT;

/** @brief �����ܼ������ͷ�
* @return �ɹ�D_OK, ����D_ERR
*/
D_Result d_rtc_timer_close(void) D_FUNCPOSTFIT;

/** @brief ��ø����ܼ�����Ƶ��
* @return �����ܼ�����Ƶ��(Hz)
*/
D_U64 d_rtc_timer_get_freq(void) D_FUNCPOSTFIT;

/** @brief ��ø����ܼ�������ǰ����
* @return �����ܼ�������ǰ����ֵ
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

