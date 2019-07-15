#ifndef _D_LCD_H_
#define _D_LCD_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief :lcd��Ļ��ʼ��
*@param : ��
*@return: D_OK
*/
D_Result
d_lcd_init(void) D_FUNCPOSTFIT;

/** @brief :�򿪻�ر�lcd��Ļ��ʾ
*@param :on ���������
*@return: D_OK
*/
D_Result
d_lcd_on_off(D_Bool on) D_FUNCPOSTFIT;

/** @brief :����lcd��Ļ��ʾ����
*@param :val ����ֵ(0-255)
*@return: D_OK
*/
D_Result
d_lcd_set_bright(D_U8 val) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

