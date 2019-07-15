/** @file
* @brief IIC设备操作
* @author 龚克
* @date 2005-5-16 龚克: 建立文件
*/

#ifndef _D_IIC_H_
#define _D_IIC_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dIO.h"

/** @brief IIC设备句柄*/
typedef D_Handle    D_HIIC;

/** @brief IIC地址模式*/
typedef enum {
    D_IIC_ADDR_7BITS,   /**< 7位地址*/
    D_IIC_ADDR_10BITS   /**< 10位地址*/
} D_IICAddrType;

/** @brief IIC设备属性*/
typedef struct {
    D_ID    id; /**<  IIC总线ID*/
} D_IICAttr;

/** @brief 用缺省参数初始化IIC设备属性*/
#define D_IIC_ATTR_INIT(_a)\
    D_MACRO_BEGIN\
        (_a)->id = 0;\
    D_MACRO_END

/** @brief i2c设备初始化结构 */
typedef struct
{
    D_GPIO_PortBit sda;
    D_GPIO_PortBit sdc;
}D_IICOpenParam;

/**  @brief 设置延时变量
*    @param time  延时长度
*/
void d_iic_set_time_delay (D_U8 time) D_FUNCPOSTFIT;

/** @brief IIC总线加锁
*
*   对IIC操作时加锁
* @param hiic   IIC设备句柄   
* @retval D_ERR_INVALID_HANDLE      设备句柄无效
*   
*/
D_Result d_iic_lock( D_HIIC hiic) D_FUNCPOSTFIT;

/** @brief IIC总线解锁
*
*   对IIC操作时解锁
* @param hiic   IIC设备句柄   
* @retval D_ERR_INVALID_HANDLE      设备句柄无效
*   
*/
D_Result d_iic_unlock(D_HIIC hiic) D_FUNCPOSTFIT;

/** @brief IIC系统初始化
*
*   在调用IIC操作函数时首先调用此函数
* @retval D_OK  初始化成功
* @retval D_ERR 初始化失败
*/
D_Result d_iic_open (D_IICOpenParam *param, D_Size cnt) D_FUNCPOSTFIT;

D_Result d_iic_open_ex(void) D_FUNCPOSTFIT;

/** @brief IIC系统中止
*
* 程序结束时，释放IIC系统内的资源
* @retval D_OK  操作成功
* @retval D_ERR 操作失败
*/
D_Result d_iic_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个IIC设备
* @param attr   IIC属性结构指针，为NULL时使用缺省值(iic_id=0)
* @return 成功时返回IIC设备句柄，失败返回D_INVALID_HANDLE
*/
D_HIIC d_iic_create (D_IICAttr *attr) D_FUNCPOSTFIT;

/** @brief 销毁一个IIC设备
* @param hiic   IIC设备句柄
* @retval D_OK  释放成功
* @retval   D_ERR_INVALID_HANDLE    句柄无效
*/
D_Result d_iic_destroy (D_HIIC hiic) D_FUNCPOSTFIT;

/** @brief 设定IIC地址
* @param hiic   IIC设备句柄
* @param at     地址类型(7/10位)
* @param addr   IIC地址
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE      设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT    参数无效
*/
D_Result d_iic_set_slave_addr (D_HIIC hiic, D_IICAddrType at, D_U16 addr) D_FUNCPOSTFIT;

/** @brief 设置IIC速度
* @param hiic   IIC设备句柄
* @param speed  IIC速度值(单位:kb/s)
* @retval D_OK  操作成功
* @retval D_ERR 操作失败
*/
D_Result d_iic_set_speed (D_HIIC hiic, D_U32 speed) D_FUNCPOSTFIT;

/** @brief  IIC读函数
* @param hiic   IIC设备句柄
* @param slave  slave设备地址
* @param addr   要读的寄存器的地址
* @param buffer 读数据缓冲区指针
* @param size   要读的字节数
* @param addrlen寄存器器地址的字节个数(0 - 2)
* @retval D_OK  操作成功
* @retval D_ERR 操作失败
*/
D_S32 d_iic_read(D_HIIC hiic, D_U8 slave, D_U8 *addr, D_U8 *buffer, D_U32 size, D_U8 addrlen) D_FUNCPOSTFIT;
D_S32 d_iic_read_stop(D_HIIC hiic, D_U8 slave, D_U8 *addr, D_U8 *buffer, D_U32 size, D_U8 addrlen) D_FUNCPOSTFIT;

/** @brief  IIC写函数
* @param hiic   IIC设备句柄
* @param slave  slave设备的地址
* @param addr   要写的寄存器的地址
* @param value  写数据的缓冲区指针
* @param size   要写入的字节数
* @param addrlen寄存器器地址的字节个数(0 - 2)
* @retval D_OK  操作成功
* @retval D_ERR 操作失败
*/
D_S32 d_iic_write(D_HIIC hiic, D_U8 slave, D_U8 *addr, D_U8 *value, D_U32 size, D_U8 addrlen) D_FUNCPOSTFIT;

/** @brief  IIC当前地址读函数
* @param hiic   IIC设备句柄
* @param slave  slave设备地址
* @param buffer 读数据缓冲区指针
* @param size   要读的字节数
* @retval D_OK  操作成功
* @retval D_ERR 操作失败
*/
D_S32 d_iic_cur_addr_read(D_HIIC hiic, D_U8 slave, D_U8 *buffer, D_U32 size)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif

