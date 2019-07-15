/** @file
* @brief NVRam设备操作
* @author 龚克
* @date 2005-5-16 龚克: 建立文件
*/

#ifndef _D_NVRAM_H_
#define _D_NVRAM_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/*支持的Flash型号*/
#define FLASH_ST_M29W640DT	0
#define FLASH_ST_M29W320ET	1
#define FLASH_EMU						2
#define FLASH_ST_M29W320EB  3
#define FLASH_ST_M28W320HT	4

/** @brief NVRAM设备句柄*/
typedef D_Handle	D_HNVRam;

typedef enum
{
	D_SECTOR_NONE,				/* 无效*/
	D_SECTOR_TYPE_4K=4096,		/* 4K字节的扇区*/
	D_SECTOR_TYPE_8K=8192,		/* 8K字节的扇区*/
	D_SECTOR_TYPE_16K=16384,		/* 16K字节的扇区*/
	D_SECTOR_TYPE_32K=32768,		/* 32K字节的扇区*/
	D_SECTOR_TYPE_64K=65536,		/* 64KB的扇区*/
}D_NVRamSectType;

typedef	D_U16 SECTOR_NO;
#define	INVALID_SECTOR_NO	((SECTOR_NO)-1)
typedef struct
{
	D_NVRamSectType type;			/* 分组的扇区大小*/
	SECTOR_NO start;				/* 分组第一个扇区的起始扇区号*/
	D_U16 sect_cnt;					/* 分组扇区个数*/
}D_NVRamGroup;

/** @brief NVRAM设备属性*/
typedef struct {
	D_ID						 id;				/**< 设备ID*/
	D_U32						 address;              /**<设备起始地址*/
	D_Size					 size;			/**< 设备大小*/
	D_NVRamGroup *sects;
	D_U16 sect_cnt;
} D_NVRamAttr;

typedef struct {
	D_U32					ManufactCode;              /*厂家号*/
	D_U32					DeviceCode;              /*设备号*/
	D_U32    				DeviceType;
} D_NVRamDevice;

/** @brief 用缺省值初始化NVRam属性*/
#define D_NVRAM_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
		(_a)->size = -1;\
	D_MACRO_END

/** @brief NVRAM系统初始化
*
*	在调用NVRam操作函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result	d_nvram_open (void) D_FUNCPOSTFIT;

/** @brief NVRAM系统中止
*
* 程序结束时，释放NVRAM系统内的资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_nvram_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个NVRAM块设备
* @param attr	NVRAM块设备属性结构指针，为NULL时使用缺省值(整个设备)
* @return 成功时返回NVRAM设备句柄，失败返回D_INVALID_HANDLE
*/
D_HNVRam	d_nvram_create (D_NVRamAttr *attr) D_FUNCPOSTFIT;

/** @brief 销毁一个NVRAM块设备
* @param hnvram NVRAM设备句柄
* @retval D_OK	释放成功
* @retval	D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_nvram_destroy (D_HNVRam hnvram) D_FUNCPOSTFIT;

/** @brief 取得一个NVRAM设备的属性
*
* 属性包括NVRAM设备的ID,字节为单位的大小
* @param hnvram	NVRAM设备的句柄
* @param attr	返回设备属性的缓冲区
* @retval D_OK	操作成功
* @retval D_ERR_INVALID_HANDLE	句柄无效
* @retval D_ERR_INVALID_ARGUMENT	attr为NULL
*/
D_Result	d_nvram_get_attr (D_HNVRam hnvram, D_NVRamAttr *attr) D_FUNCPOSTFIT;

/** @brief 向一个NVRAM设备写数据
* @param hnvram	NVRAM设备的句柄
* @param offset	写数据起始位置在块设备中的偏移量
* @param pd	写数据的缓冲区
* @param size	写入数据的字节数
* @return	返回实际读出的字节数,如果出错返回负数
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	data为NULL
* @retval D_ERR_OVERFLOW	起始偏移超过设备大小,或写数据量超过设备大小
*/
D_Size			d_nvram_write (D_HNVRam hnvram, D_Size offset, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;

/** @brief 从一个NVRAM设备读数据
* @param hnvram	NVRAM设备的句柄
* @param offset	读数据起始位置在块设备中的偏移量
* @param pd	存放读入数据的缓冲区
* @param size	数据缓冲区大小
* @return	返回实际读出的字节数,如果出错返回负数
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT	data为NULL
* @retval D_ERR_OVERFLOW	起始偏移超过设备大小,或读数据量超过设备大小
*/
D_Size			d_nvram_read (D_HNVRam hnvram, D_Size offset, D_U8 *pd, D_Size size) D_FUNCPOSTFIT;

/** @brief 擦除NVRam设备
* @param hnvram	NVRAM设备的句柄
* @param offset	擦除起始位置在块设备中的偏移量
* @param size	擦除区大小
* @return	返回实际擦除的字节数,如果出错返回负数
* @retval D_ERR_INVALID_HANDLE		设备句柄无效
* @retval D_ERR_OVERFLOW	起始偏移超过设备大小,或擦除量超过设备大小
*/
D_Size			d_nvram_erase (D_HNVRam hnvram, D_Size offset, D_Size size) D_FUNCPOSTFIT;

D_Size d_nvram_lockEnable (D_HNVRam hnvram);
D_Size d_nvram_lockstate (D_HNVRam hnvram, D_Size offset);
D_Size d_nvram_unlock (D_HNVRam hnvram, D_Size offset);
D_Size d_nvram_lock (D_HNVRam hnvram, D_Size offset);
D_Result d_nvram_get_device(D_NVRamDevice* NvDeviceInfo);

#ifdef  __cplusplus
}
#endif

#endif
