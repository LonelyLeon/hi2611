/** @file
* @brief 磁盘设备
* @author
* @date 
*/
#ifndef __D_DISK_H_
#define __D_DISK_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 磁盘设备属性*/
typedef struct {
	D_ID		id;				/**< 设备ID*/
} D_DiskAttr;

typedef enum {
    DEVICE_USB  = 1,
	DEVICE_USBX	= 1<<1,
	DEVICE_SD = 1<<2,
} D_Device_Type;

/** @brief 用缺省值初始化磁盘设备属性*/
#define D_DISK_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

typedef struct
{
    D_Char *name;
	D_Char type;
    D_U32 desc;
}D_DiskDescInfo;

typedef struct
{
    D_U32 bytes_per_sector;
    D_S64 total_sectors;
}D_DiskCapInfo;

typedef struct
{
    D_DiskDescInfo desc_info;
    D_DiskCapInfo cap_info;
}D_DiskInfo;

D_Result d_disk_open(void) D_FUNCPOSTFIT;
D_Result d_disk_close(void) D_FUNCPOSTFIT;
D_Result d_disk_check(D_ID *id, D_DiskInfo *info) D_FUNCPOSTFIT;
D_Handle d_disk_create(D_DiskAttr *attr) D_FUNCPOSTFIT;
D_Result d_disk_destroy(D_Handle handle) D_FUNCPOSTFIT;
D_Result d_disk_read_sector(D_Handle handle, D_U8 *buffer, D_U32 sector, D_U32 sector_num) D_FUNCPOSTFIT;
D_Result d_disk_write_sector(D_Handle handle, D_U8 *buffer, D_U32 sector, D_U32 sector_num) D_FUNCPOSTFIT;
D_Result d_disk_restart(D_ID id) D_FUNCPOSTFIT;
D_Result d_disk_start(D_U8 type) D_FUNCPOSTFIT;
D_Result d_disk_keeplivetime(D_ID id,D_U8 flag) D_FUNCPOSTFIT;
D_U8 d_disk_check_connect(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
