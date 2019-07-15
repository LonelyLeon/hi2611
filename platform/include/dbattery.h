/** @file
* @brief _D_BATTERY_H_
*/

#ifndef _D_BATTERY_H_
#define _D_BATTERY_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/**@brief ������gpio ��ʼ��*/
D_Result d_battery_init(D_U16 min,D_U16 max)D_FUNCPOSTFIT;
/**@brief ������gpio �ر�*/
D_Result d_battery_uninit(void)D_FUNCPOSTFIT;
/**@brief ��ص������
*@return P_BATTERY_VOLUME ��ص��������*/
D_U8  d_battery_get_batleav(void)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
