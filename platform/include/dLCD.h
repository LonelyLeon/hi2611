#ifndef _D_LCD_H_
#define _D_LCD_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief :lcd屏幕初始化
*@param : 无
*@return: D_OK
*/
D_Result
d_lcd_init(void) D_FUNCPOSTFIT;

/** @brief :打开或关闭lcd屏幕显示
*@param :on 开或关命令
*@return: D_OK
*/
D_Result
d_lcd_on_off(D_Bool on) D_FUNCPOSTFIT;

/** @brief :设置lcd屏幕显示亮度
*@param :val 亮度值(0-255)
*@return: D_OK
*/
D_Result
d_lcd_set_bright(D_U8 val) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

