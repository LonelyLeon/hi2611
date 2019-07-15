/** @file 
* @brief 触摸屏设备
* @author 李臣
* @date 2015-07-10  朱小磊: 建立文件
*/
#ifndef __D_TOUCH_SCREEN_H
#define __D_TOUCH_SCREEN_H

#include "dTypes.h"
#include "dIO.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/** @brief 触摸屏型号*/
typedef enum
{
    touchscreen_FT5x06,
    touchscreen_max,
}D_TouchScreenType_t;

/** @brief 触摸屏事件 */
typedef enum
{
	D_TOUCH_SCREEN_EVENT_DOWN = 0,
	D_TOUCH_SCREEN_EVENT_UP,
	D_TOUCH_SCREEN_EVENT_MOVE,
}D_TouchScreenEvent;

/** @brief 触摸屏查询数据 */
typedef struct
{
    D_TouchScreenEvent evt;  /**< 触摸屏事件 */
    D_U16 x;  /**< 触摸屏x坐标 */
    D_U16 y;  /**< 触摸屏y坐标 */
}D_TouchScreenPollData;


/** @brief 触摸屏open参数*/
typedef struct
{
    D_Coord             xres;   /**< 水平分辨率 */
    D_Coord             yres;   /**< 垂直分辨率 */
    D_S8                prio;   /* 任务优先级*/
    D_TouchScreenType_t type;   /* 触摸屏型号*/
    D_GPIO_PortBit      reset;  /* 复位所用io*/
    D_GPIO_PortBit      interrupt;  /* 中断所用io*/
}D_TouchScreenOpenParam;


/** @brief 触摸屏操作接口*/
typedef struct 
{
	D_Result (*init)(D_TouchScreenOpenParam *ts)D_FUNCPOSTFIT;
	D_Result (*deinit)(void)D_FUNCPOSTFIT;
	D_Result (*reset)(void)D_FUNCPOSTFIT;
    D_Result (*poll)(D_TouchScreenPollData *poll_data)D_FUNCPOSTFIT;
}D_TouchScreenOp;


/** @brief 触摸屏设备注册
* @retval D_OK	注册成功
* @retval D_ERR	注册失败
*/
D_Result d_touchscreen_register_ops(D_TouchScreenType_t type, D_TouchScreenOp *op) D_FUNCPOSTFIT;

/** @brief 触摸屏设备初始化
* @param[in]  初始化参数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result d_touchscreen_open(D_TouchScreenOpenParam *ts) D_FUNCPOSTFIT;

/** @brief 触摸屏设备反初始化
* @retval D_OK	反初始化成功
* @retval D_ERR	反初始化失败
*/
D_Result d_touchscreen_close(void) D_FUNCPOSTFIT;

/** @brief 触摸屏设备查询
* @param[out] poll_data 查询到的数据
* @retval D_OK	查询有数据
* @retval D_ERR	查询无数据
*/
D_Result d_touchscreen_poll(D_TouchScreenPollData *poll_data) D_FUNCPOSTFIT;

/** @brief 触摸屏任务创建*/
D_Result d_touchscreen_init(void) D_FUNCPOSTFIT;


D_Result d_touchscreen_register_FT5x06(void) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif
#endif

