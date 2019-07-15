/** @file 
* @brief 鼠标设备
* @author 李臣
* @date 2014-07-10  李臣: 建立文件
*/
#ifndef __D_MOUSE_H
#define __D_MOUSE_H

#include "dTypes.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/** @brief 鼠标事件 */
typedef enum
{
	D_MOUSE_EVENT_LBUTTON_DOWN = 0,
	D_MOUSE_EVENT_LBUTTON_UP,
	D_MOUSE_EVENT_RBUTTON_DOWN,
	D_MOUSE_EVENT_RBUTTON_UP,
	D_MOUSE_EVENT_MBUTTON_DOWN,
	D_MOUSE_EVENT_MBUTTON_UP,
	D_MOUSE_EVENT_MOVE,
	D_MOUSE_EVENT_WHEEL,
}D_MouseEvent;

#define MOUSE_BUTTON_LEFT      0x0001
#define MOUSE_BUTTON_RIGHT     0x0002
#define MOUSE_BUTTON_MIDDLE    0x0004

/** @brief 鼠标设备初始化结构 */
typedef struct
{
    D_Coord xres;  /**< 水平分辨率 */
    D_Coord yres;  /**< 垂直分辨率 */
}D_MouseOpenParam;

/** @brief 鼠标查询数据 */
typedef struct
{
    D_MouseEvent evt;  /**< 鼠标事件 */
    D_U16 button;  /**< 鼠标按键(组合) */
    D_U16 x;  /**< 鼠标x坐标 */
    D_U16 y;  /**< 鼠标y坐标 */
    D_S16 z;  /**< 滑轮滑动位移 */
}D_MousePollData;

/** @brief 鼠标设备初始化
* @param[in]  初始化参数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result d_mouse_open(D_MouseOpenParam *param) D_FUNCPOSTFIT;

/** @brief 鼠标设备反初始化
* @retval D_OK	反初始化成功
* @retval D_ERR	反初始化失败
*/
D_Result d_mouse_close(void) D_FUNCPOSTFIT;

/** @brief 鼠标设备查询
* @param[out] poll_data 查询到的数据
* @retval D_OK	查询有数据
* @retval D_ERR	查询无数据
*/
D_Result d_mouse_poll(D_MousePollData *poll_data) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
