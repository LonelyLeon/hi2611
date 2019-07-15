/** @file
* @brief �����
* @author majy
* @date 2013-11-07 majy: �����ļ�
*/

#ifndef _D_POWEROFF_H_
#define _D_POWEROFF_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dPowerOff.h"

typedef struct
{
    D_U8  guid_code;
    D_U16 machine_code;
    D_U16 key;
}P_POWERKEY;

typedef struct
{
    D_U8  fd650_clk;
    D_U8 fd650_data;
    D_U8 key;
    D_U8	key_io;
}P_LEDKEYSET;

typedef struct
{
    P_POWERKEY key[4];
    D_U8 remote_num;
    D_U8 wakeup_time;
    D_Ptr prog;
    D_Size prog_size;
}HRPOWERDOWN_KERNEL_DATA;

/** @brief ��ȡ�����ļ������������Ҫ����������
* �������оƬ����power����ֵ֮ǰ����Ҫ�ȵ��øú���
* @param[in]  ��
* @retval 0	��ʼ���ɹ� 
* @retval -1	��ʼ��ʧ�� 
*/
D_Result d_PowerOff_open(void);

/** @brief    ����ң������POWERKEY��ʹ������ʵ��Ӳ�����������
* @param[in]  power_keyң�����������������Ϣ(�������ͣ��û��룬��ֵ)
* @param[in]  remote_num ���ÿ����������ң��������
* @param[in]  wakeup_time   ������������ʱ��(��λ10s)
* @param[in]  type �����ѡ��������ķ�ʽ: 0��Ӳ��оƬ�����������ʵ�����������
* @retval 0   ��
*/
void d_remote_power_off(P_POWERKEY* power_key,D_U8 remote_num,D_U16 wakeup_time,D_U8 type)D_FUNCPOSTFIT;
void d_multiple_remote_power_off(P_POWERKEY* power_key, D_U8 remote_num, D_U16 wakeup_time, D_U8 type , D_U32* mask)D_FUNCPOSTFIT;
/** @brief    ����ң������POWERKEY��ʹ������ʵ������������������
* @param[in]  power_keyң�����������������Ϣ(�������ͣ��û��룬��ֵ)
* @param[in]  remote_num ���ÿ����������ң��������
* @param[in]  wakeup_time   ������������ʱ��(��λ10s)
* @retval 0   ��
*/
void hrpowerstandby(P_POWERKEY* power_key,D_U8 remote_num,D_U8 wakeup_time,P_LEDKEYSET *led_set);
void d_remote_power_timewake(D_U16 wakeup_time);
D_U8 d_check_start(void);
D_U8 d_fp_power_off(void);
void d_power_off(void);
D_U8 d_get_power_ctr_int(void);
D_U8 d_get_power_ctr_intstate(void);
void d_set_power_ctr_int_clear(void);
void d_set_power_ctr_int_enable(void);
#ifdef  __cplusplus
}
#endif

#endif

