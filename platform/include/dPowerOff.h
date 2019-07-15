/** @file
* @brief 真待机
* @author majy
* @date 2013-11-07 majy: 建立文件
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

/** @brief 读取配置文件中真待机所需要的配置数据
* 在向待机芯片发送power键键值之前，需要先调用该函数
* @param[in]  无
* @retval 0	初始化成功 
* @retval -1	初始化失败 
*/
D_Result d_PowerOff_open(void);

/** @brief    接收遥控器的POWERKEY后使机顶盒实现硬件真待机功能
* @param[in]  power_key遥控器待机键的相关信息(编码类型，用户码，键值)
* @param[in]  remote_num 配置可以真待机的遥控器个数
* @param[in]  wakeup_time   待机后重启的时间(单位10s)
* @param[in]  type 软件中选择真待机的方式: 0是硬件芯片，其他是软件实现真待机功能
* @retval 0   无
*/
void d_remote_power_off(P_POWERKEY* power_key,D_U8 remote_num,D_U16 wakeup_time,D_U8 type)D_FUNCPOSTFIT;
void d_multiple_remote_power_off(P_POWERKEY* power_key, D_U8 remote_num, D_U16 wakeup_time, D_U8 type , D_U32* mask)D_FUNCPOSTFIT;
/** @brief    接收遥控器的POWERKEY后使机顶盒实现软件真待机待机功能
* @param[in]  power_key遥控器待机键的相关信息(编码类型，用户码，键值)
* @param[in]  remote_num 配置可以真待机的遥控器个数
* @param[in]  wakeup_time   待机后重启的时间(单位10s)
* @retval 0   无
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

