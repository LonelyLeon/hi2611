/**@defgroup MonitorTable 
*@{*/
/** @file
* @brief 开机检查(例如网络锁)
* @author qiny
* @date 2013-09-09 qiny: 建立文件
*/
#ifndef _D_POWERON_CHECK_H_
#define _D_POWERON_CHECK_H_

#ifdef  __cplusplus

extern "C"
{
#endif



/*开机检查结果*/
typedef struct
{
    D_Bool  network_match;
    D_U32   reserved;
}D_PowerOnCheck;




/** @brief 开机检查表监控初始化
*@return D_ERR 初始化失败 D_OK 初始化成功
*/
D_Result p_power_on_check_init(void)D_FUNCPOSTFIT;

/** @brief 开机检查表监控反初始化
*@return D_ERR 反初始化失败 D_OK 反初始化成功
*/
D_Result p_power_on_check_deinit(void)D_FUNCPOSTFIT;


/** @brief 启动开机检查表监控
*@return D_ERR 反初始化失败 D_OK 反初始化成功
*/
D_Result p_power_on_check_start(D_FEndType fendtype)D_FUNCPOSTFIT;


/** @brief 停止开机检查表监控
*@return D_ERR 反初始化失败 D_OK 反初始化成功
*/
D_Result p_power_on_check_stop(D_FEndType fendtype)D_FUNCPOSTFIT;


/** @brief 取得开机检查结果
*@return D_OK \D_ERR
*/
D_Bool p_power_on_check(D_PowerOnCheck *pow)D_FUNCPOSTFIT;



#ifdef  __cplusplus
}
#endif

#endif
/* @}*/

