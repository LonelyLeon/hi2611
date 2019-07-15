/** @file
* @brief 串口设备操作
* @author 龚克
* @date 2005-7-1 龚克: 建立文件
*/

#ifndef _D_SERIAL_H_
#define _D_SERIAL_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 串口设备句柄*/
typedef D_Handle	D_HSerial;

/** @brief 串口波特率*/
typedef D_U32	D_SerialBaud;

/** @brief 串口数据位数*/
typedef enum {
    D_SERIAL_7_DATABITS,
    D_SERIAL_8_DATABITS
} D_SerialDataBits;

/** @brief 串口停止位数目*/
typedef enum {
    D_SERIAL_1_STOPBITS,
    D_SERIAL_2_STOPBITS
} D_SerialStopBits;

/** @brief 串口校检方式*/
typedef enum {
    D_SERIAL_NO_PARITY,
    D_SERIAL_ODD_PARITY,
    D_SERIAL_EVEN_PARITY,
    D_SERIAL_SPACE_PARITY
} D_SerialParity;

/** @brief 串口工作模式*/
typedef struct {
	D_SerialBaud			baud;				/**< 波特率*/
	D_SerialDataBits	data_bits;	/**< 数据位*/
	D_SerialStopBits	stop_bits;	/**< 停止位*/
	D_SerialParity		parity;			/**< 校检方式*/
} D_SerialMode;

/** @brief 串口设备属性*/
typedef struct {
	D_ID							id;					/**< 设备ID*/
} D_SerialAttr;

/** @brief 按缺省属性初始化串口设备属性*/
#define D_SERIAL_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief 串口系统初始化
*
*	在调用串口操作函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result	d_serial_open (void) D_FUNCPOSTFIT;

/** @brief 串口系统中止
*
* 程序结束时，释放串口系统内的资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_serial_close (void) D_FUNCPOSTFIT;

/** @brief usb串口初始化
*
*	在调用usb串口操作函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result d_serial_open_usb(void) D_FUNCPOSTFIT;

/** @brief 创建一个串口设备
* @param attr	串口设备属性结构指针，为NULL时使用缺省值(id=0)
* @return 成功时返回串口设备句柄，失败返回D_INVALID_HANDLE
*/
D_HSerial	d_serial_create (D_SerialAttr *attr) D_FUNCPOSTFIT;

/** @brief 销毁一个串口设备
* @param hs	串口设备句柄
* @retval D_OK	释放成功
* @retval	D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_serial_destroy (D_HSerial hs) D_FUNCPOSTFIT;

/** @brief 设定串口工作模式
* @param hs		串口设备句柄
* @param mode	串口工作模式
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result 	d_serial_set_mode (D_HSerial hs, D_SerialMode *mode) D_FUNCPOSTFIT; 

/** @brief 向一个串口设备写数据
* @param hs	串口设备的句柄
* @param pd	写数据的缓冲区
* @param size	写入数据的字节数
* @return	返回实际写入的字节数,如果出错返回负数
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	data为NULL
* @retval D_ERR_FAULT	操作失败
*/
D_Size		d_serial_write (D_HSerial hs, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;

/** @brief 从一个串口设备读数据
* @param hs 		串口设备的句柄
* @param pd		存放读入数据的缓冲区
* @param size	数据缓冲区大小
* @return	返回实际读出的字节数,如果出错返回负数
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	data为NULL
* @retval D_ERR_FAULT	操作失败
*/
D_Size		d_serial_read (D_HSerial hs, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;
/** @brief 从一个串口设备读数据
* @param hs 		串口设备的句柄
* @param pd		存放读入数据的缓冲区
* @param size	数据缓冲区大小
* @param readtimeout	超时时间
* @return	返回实际读出的字节数,如果出错返回负数
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	data为NULL
* @retval D_ERR_FAULT	操作失败
*/
D_Size	d_serial_read_ex (D_HSerial hs, D_U8 *pd, D_Size size, D_U16 readtimeout) D_FUNCPOSTFIT;

D_Size		d_gprs_serial_read (D_HSerial hs, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;

/*清空串口buffer*/
D_Result d_serial_flush (D_HSerial hs) D_FUNCPOSTFIT;

/** @brief 打印字符到串口设备
* @param Format_p 遵循普通打印函数结构
*/
void d_serial_printf(char *Format_p, ...)D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif
