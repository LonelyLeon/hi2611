/** @file
* @brief EEPRom设备操作
* @author 龚克
* @date 2005-5-17 龚克: 建立文件
*/

#ifndef _D_EEPROM_H_
#define _D_EEPROM_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief EEPRom设备句柄*/
typedef D_Handle	D_HEEPRom;

/** @brief EEPRom设备属性*/
typedef struct {
	D_ID							id;					/**< 设备ID*/
	D_Size						size;				/**< 块大小*/
} D_EEPRomAttr;

/** @brief 按缺省属性初始化EEPRom设备属性*/
#define D_EEPROM_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
		(_a)->size = -1;\
	D_MACRO_END

/** @brief EEProm设备类型 */
typedef enum
{
    D_EEProm_Real = 0,  /**< EEProm设备 */
    D_EEProm_Fake,      /**< 虚拟设备 */
}D_EEPromType;

/** @brief EEProm设备参数 */
typedef struct
{
    D_U8 iic_bus_no;    /**< i2c总线号 */
    D_U8 page_size;     /**< 页大小 */
}D_EEPromRealParam;

/** @brief EEProm虚拟设备参数 */
typedef struct
{
    D_U32 nvram_offset_1;   /**< 虚拟EEProm设备在flash里存放位置块1 */
    D_U32 nvram_offset_2;   /**< 虚拟EEProm设备在flash里存放位置块2 */
    D_U32 nvram_block_size; /**< flash块大小 */
}D_EEPromFakeParam;

/** @brief EEProm设备初始化结构 */
typedef struct
{
    D_EEPromType type;  /**< EEProm设备类型 */
    D_Size size;        /**< EEProm设备大小 */
    union
    {
        D_EEPromRealParam real;
        D_EEPromFakeParam fake;
    }u;
}D_EEPRomOpenParam;

/** @brief EEPRom系统初始化
*
*	在调用EEPRom操作函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result d_eeprom_open (D_EEPRomOpenParam *param) D_FUNCPOSTFIT;

/** @brief EEPRom系统中止
*
* 程序结束时，释放EEPRom系统内的资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result d_eeprom_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个EEPRom设备
* @param attr	EEProm设备属性结构指针，为NULL时使用缺省值(id=0)
* @return 成功时返回EEPRom设备句柄，失败返回D_INVALID_HANDLE
*/
D_HEEPRom d_eeprom_create (D_EEPRomAttr *attr) D_FUNCPOSTFIT;

/** @brief 销毁一个EEPRom设备
* @param heeprom EEProm设备句柄
* @retval D_OK	释放成功
* @retval	D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result d_eeprom_destroy (D_HEEPRom heeprom) D_FUNCPOSTFIT;

/** @brief 取得一个EEPRom设备的属性
*
* 属性包括EEPRom设备的ID,字节为单位的大小
* @param heeprom	EEPRom设备的句柄
* @param attr	返回设备属性的缓冲区
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE	句柄无效
* @retval D_ERR_INVALID_ARGUMENT	attr为NULL
*/
D_Result d_eeprom_get_attr (D_HEEPRom heeprom, D_EEPRomAttr *attr) D_FUNCPOSTFIT;

/** @brief 向一个EEPRom设备写数据
* @param heeprom	EEProm设备的句柄
* @param offset	写数据起始位置在块设备中的偏移量
* @param pd	写数据的缓冲区
* @param size	写入数据的字节数
* @return	返回实际写入的字节数,如果出错返回负数
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	data为NULL
* @retval D_ERR_OVERFLOW	起始偏移超过设备大小,或写数据量超过设备大小
*/
D_Size	d_eeprom_write (D_HEEPRom heeprom, D_Size offset, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;

/** @brief 从一个EEPRom设备读数据
* @param heeprom EEPRom设备的句柄
* @param offset	读数据起始位置在块设备中的偏移量
* @param pd	存放读入数据的缓冲区
* @param size	数据缓冲区大小
* @return	返回实际读出的字节数,如果出错返回负数
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	data为NULL
* @retval D_ERR_OVERFLOW	起始偏移超过设备大小,或读数据量超过设备大小
*/
D_Size	d_eeprom_read (D_HEEPRom heeprom, D_Size offset, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;


/** @brief 清除一个EEPRom设备数据
* @param heeprom EEPRom设备的句柄
* @return	成功返回D_OK, 失败返回D_ERR
*/
D_Result  d_eeprom_clear_all(D_HEEPRom heeprom) D_FUNCPOSTFIT;

/** @brief 清除EEPRom里的部分数据
* @param heeprom EEPRom设备的句柄
* @return	成功返回D_OK, 失败返回D_ERR
*/
D_Result  d_eeprom_clear_part(D_HEEPRom heeprom,D_Size offset, D_Size clearsize)D_FUNCPOSTFIT;

/** @brief eeprom读写测试*/
void EEP_RW_TEST(D_HEEPRom heeprom) D_FUNCPOSTFIT;

/** @brief eeprom疲劳测试*/
void EEP_FATIGUE_TEST(D_HEEPRom heeprom) D_FUNCPOSTFIT;

/** @brief eeprom寿命测试*/
void EEP_LIFETIME_TEST(D_HEEPRom heeprom) D_FUNCPOSTFIT;

/** @brief eeprom总体测试*/
void EEPROM_TEST(D_HEEPRom heeprom) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
