#ifndef	__NVPART_DEF_AND_FUN_HEADER__
#define	__NVPART_DEF_AND_FUN_HEADER__
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dNVRam.h"

/** @brief NVRam设备数目*/
#define D_NV_DEV_CNT						(1)

/** @brief NVRam 分区ID*/
typedef enum {
	D_NV_PART_ALL			= 0,/**< 整个设备*/
	D_NV_PART_WRITABLE		= 1,/**< 设备可写区*/
	D_NV_PART_TABLE			= 2,/**< 分区表*/
	D_NV_PART_TABLE_BAK		= 3,/**< 分区表备份*/
	D_NV_PART_LOADER		= 4,/**< Loader分区*/
	D_NV_PART_SYSTEM 		= 5,/**< 操作系统分区*/
	D_NV_PART_CA1 			= 6,/**< CA分区*/
	D_NV_PART_APP           = 7,/**< 应用程序分区*/
	D_NV_PART_CA2   		= 8,/**< CA2分区*/
	D_NV_PART_CA3			= 9,/**< CA3分区*/
	D_NV_PART_PROG			= 10,/**< 节目分区*/
	D_NV_PART_PARAM			= 11,/**< 参数存储分区*/
	D_NV_PART_BAK			= 12,/**< 备份分区*/
	D_NV_PART_RSET          = 13,/**< 记录集分区*/
	D_NV_PART_MAIL			= 14,/**< 邮件分区*/
	D_NV_PART_DATA          = 15,/**< 用户数据区 */
	D_NV_PART_ADVERTISE     = 16,/**< 广告数据分区*/
	D_NV_PART_RESERVED      = 17,/**< 预留分区*/
	D_NV_PART_PROG2         = 18,/**< 第二个节目分区*/
	D_NV_PART_LOGO          = 19,/**< logo分区*/
	D_NV_PART_DB_DEFAULT    = 20,/**< 预置数据库分区*/
	D_NV_PART_LOGO_DEFAULT = 21,/**< 预置数据库分区*/
	D_NV_PART_FLASH_HEADER  = 22, /**< 直播星 Flash_header*/
	D_NV_PART_TDI		    = 23, /**< 直播星 TDI INFO*/
	D_NV_PART_TDI_BAK	    = 24, /**< 直播星 TDI BACKUP INFO*/
	D_NV_PART_OSDTEXT	    = 25, /**< 直播星 前端下发字符串分区*/
	D_NV_PART_RATINGS 	    = 26, /**< 直播星 收视率事件分区*/
	D_NV_PART_CA4   		= 27,/**< CA4分区*/
	D_NV_PART_CA5			= 28,/**< CA5分区*/
	D_NV_PART_CNT            /**<分区表类型个数*/
} D_NVPartID;

/** @brief NVRam分区数据类型*/
typedef enum {
	D_NV_PART_TYPE_DATA		= 1,
	D_NV_PART_TYPE_ZIP_DATA	= 2,
	D_NV_PART_TYPE_APP		= 3,
	D_NV_PART_TYPE_ZIP_APP= 4,
	D_NV_PART_TYPE_BLOCK	= 5
} D_NVPartType;

/** @brief 分区信息*/
typedef struct {
	D_U8					id;
	D_U8					parent_id;
	D_U8					need_backup;		// 原来为rfu，用来标志该区更新前需要备份以保护数据
	D_U8					type;
	D_U16					sec_start;
	D_U16					sec_cnt;
	/*2006-4-11 9:38*/
	D_U32 				nv_offset;
	D_U32         data_size;
	
	D_U32         nv_size;
} D_NVPartInfo;

typedef struct 
{
	D_U8 id;
	D_U8 parent_id;
	D_U8 need_backup;
	D_NVPartType type;
	D_U32 size;
}D_NVPartCfg;

/** @brief NVRam分区*/
typedef struct {
	D_Bool					used;
	D_NVPartInfo	  		info;
//	D_Size					nv_offset;
//	D_Size					nv_size;
	D_Size					data_size;
} D_NVPart;

/** @brief NVRam设备信息*/
typedef struct {
	D_ID					 id;
	D_HNVRam			 hnv;
	D_Size				 size;
	D_Size				 part_tab_start;
	D_Size				 part_tab_size;
	D_U16				 sector_cnt;
	const D_Size		 *sectors;
	D_NVPart			 parts[D_NV_PART_CNT];
	const D_NVRamGroup *sects;
	D_U16	sect_cnt;
} D_NVDev;

/** @brief 分区信息尾*/
typedef struct {
	D_U32					size;		/* 数据大小*/
	D_U8					id;			/* 分区标识D_NVPartID*/
	D_U8					rfu;			/* 保留	*/
	D_U8					type;		/* 类型D_NVPartType*/
	D_U8					flag;		/* 标识，固定为D_NV_PART_FLAG */
} D_NVPartTail;

/** @brief NVRam分区设备句柄*/
typedef D_Handle	D_HNVPart;


/** @brief 	取得指定的NVRam设备
* @param
		nv_id				分区设备标识
* @return
		NULL				失败
		有效指针		成功
*/
D_NVDev* get_nv (D_ID nv_id) D_FUNCPOSTFIT;

/**@brief 	检查分区表完整有效性，仅为提供测试用
@return
		D_OK			完整有效
		其他值		不完整
*/
D_Result _check_part(void) D_FUNCPOSTFIT;

/** @brief 	NVRam分区管理系统初始化
* @return
	D_OK		成功
	D_ERR		失败
*/
D_Result d_nvpart_open (void) D_FUNCPOSTFIT;

/** @brief 	分区管理系统退出
* @return
	D_OK		成功
	D_ERR		失败
*/
D_Result d_nvpart_close (void) D_FUNCPOSTFIT;

/** @brief 	在指定设备上增加一个分区
* @param
	nv_id		NVRam设备ID
	info			分区信息
* @return
	D_OK		成功
	D_ERR		失败
*/
D_Result d_nvpart_add (D_ID nv_id, D_NVPartInfo *info) D_FUNCPOSTFIT;

/** @brief 	在指定设备上删除一个分区
* @param 
	nv_id		NVRam设备ID
	part_id		要删除的分区ID
* @return
	D_OK		成功
	D_ERR		失败
*/
D_Result d_nvpart_remove (D_ID nv_id, D_ID part_id) D_FUNCPOSTFIT;

/** @brief 	存储一个设备的分区表
* @param 
	nv_id		NVRam设备ID
* @return
	D_OK		成功
	D_ERR		失败
*/
D_Result d_nvpart_store (D_ID nv_id) D_FUNCPOSTFIT;

/** @brief 	创建一个分区句柄
* @param 
	nv_id		NVRam设备ID
	id			 分区设备ID
* @return
	D_INVALID_HANDLE		失败
	其他值				成功
*/
D_HNVPart d_nvpart_create (D_ID nv_id, D_NVPartID id) D_FUNCPOSTFIT;

/** @brief 	销毁一个分区句柄
* @param
	hnvp		分区句柄
* @return
	D_OK		成功
	D_ERR		失败返回
*/
D_HNVPart d_nvpart_destroy (D_HNVPart hnvp) D_FUNCPOSTFIT;

/** @brief 	取得一个分区的信息
* @param
	hnvp		分区设备句柄
* @return
	D_OK		成功
	D_ERR		失败
*/
D_Result d_nvpart_get_info (D_HNVPart hnvp, D_NVPartInfo *info) D_FUNCPOSTFIT;

/** @brief 	读一个分区
* @param 
	hnvp		分区设备句柄
	offset		读起始位置偏移
	ptr			读数据缓冲区
	size			读数据大小
* @return
	非负数	成功，返回read的字节数
	负数		失败
*/
D_Size d_nvpart_read (D_HNVPart hnvp, D_Size offset, D_U8 *ptr, D_Size size) D_FUNCPOSTFIT;

/** @brief 	擦除一个分区
* @param
	hnvp		分区设备句柄
* @return
	D_OK		成功
	D_ERR		失败
	D_ERR_INVALID_HANDLE		无效句柄
	D_ERR_FAULT					参数错误
*/
D_Result d_nvpart_erase (D_HNVPart hnvp) D_FUNCPOSTFIT;

/** @brief 	擦除一个分区并同时进行事件处理
* @param 
	hnvp						分区设备句柄
	valid_data_len					?????????目前未使用
	callback						擦除过程中的事件处理接口
* @return
	D_OK						成功
	D_ERR_INVALIE_HANDLE		句柄无效
*/
D_Result d_nvpart_erase_with_hook (D_HNVPart hnvp,D_U32 valid_data_len,void(*callback)(D_U32 param)) D_FUNCPOSTFIT;

/** @brief 	写一个分区
* @param 
	hnvp			分区设备句柄
	offset 			写起始位置偏移
	ptr 				写数据缓冲区
	size 				写数据大小
* @return
	非负数		成功
	负数			失败
*/
D_Size d_nvpart_write (D_HNVPart hnvp, D_Size offset, const D_U8 *ptr, D_Size size) D_FUNCPOSTFIT;

/** @brief	写一个分区尾信息
* @param
	hnvp		分区设备句柄
 	id			尾信息的分区ID
* @return
	D_OK		成功
	D_ERR		失败
*/
D_Result d_nvpart_write_tail_ex (D_HNVPart hnvp, D_U8 id) D_FUNCPOSTFIT;

/** @brief	写一个分区尾信息
* @param
	hnvp		分区设备句柄
* @return
	D_OK		成功
	D_ERR		失败
*/
D_Result d_nvpart_write_tail (D_HNVPart hnvp) D_FUNCPOSTFIT;

/** @brief	检查一个分区内的数据是否有效
* @param
	hnvp		分区设备句柄
	size 			返回有效数据的字节数
	id	 		返回尾信息中的分区ID
* @return
	D_TRUE		成功
	D_FALSE		失败
*/
D_Bool d_nvpart_is_available (D_HNVPart hnvp, D_Size *size, D_U8 *id) D_FUNCPOSTFIT;

/** @brief 	直接读取flash，实现为线程安全的直接nvram操作
* @param 
	dev_id		设备标识
	offset		要访问的区域在设备中的偏移
	readbuf		存放要读取数据的缓冲区
	rbsize		缓冲区的容量
* @return
	非负数	成功
	D_ERR		失败
*/
D_Size d_nvpart_read_flash(D_ID dev_id, D_Size offset, void *readbuf, D_Size rbsize) D_FUNCPOSTFIT;

/** @brief 	直接写flash，实现为线程安全的直接nvram操作
* @param
	dev_id		设备标识
	offset		要访问的区域在设备中的偏移
	writebuf		存放要读取数据的缓冲区
	wbsize		缓冲区的容量
* @return
	非负数	成功
	D_ERR		失败
*/
D_Size d_nvpart_write_flash(D_ID dev_id, D_Size offset, const void *writebuf, D_Size wbsize) D_FUNCPOSTFIT;

/** @brief 	直接擦除flash，实现为线程安全的直接nvram操作
* @param
	dev_id		设备标识
	offset		要访问的区域在设备中的偏移
	rbsize		缓冲区的容量
* @return
	非负数	成功
	D_ERR		失败
*/
D_Size d_nvpart_erase_flash(D_ID dev_id, D_Size offset, D_Size wbsize) D_FUNCPOSTFIT;

/** @ brief 	对nvram指定地址进行加锁
@param
	hnvp		分区句柄
	offset		要加锁区间的结束地址，为分区中的偏移地址
* @return
	D_TRUE		成功
	D_FALSE		失败
*/
D_Bool d_nvpart_lock_part (D_HNVPart hnvp, D_Size offset) D_FUNCPOSTFIT;

/** @ brief 	对nvram指定地址进行解锁
@param
	hnvp		分区句柄
	offset		要解锁区间的结束地址，为分区中的偏移地址
* @return
	D_TRUE		成功
	D_FALSE		失败
*/
D_Bool d_nvpart_unlock_part (D_HNVPart hnvp, D_Size offset) D_FUNCPOSTFIT;

/** @ brief 	对nvram查询加锁状态
@param
	hnvp		分区句柄
	offset		要解锁区间的结束地址，为分区中的偏移地址
* @return
	D_TRUE		成功
	D_FALSE		失败
*/
D_Bool d_nvpart_check_lock_part (D_HNVPart hnvp, D_Size offset) D_FUNCPOSTFIT;

/** @ brief 	对nvram查询解锁状态
@param
	hnvp		分区句柄
 	offset		要解锁区间的结束地址，为分区中的偏移地址
* @return
	D_TRUE		成功
	D_FALSE		失败
*/
D_Bool d_nvpart_check_unlock_part(D_HNVPart hnvp, D_Size offset)D_FUNCPOSTFIT;


/** @ brief 	对nvram解锁
* @return
	D_TRUE		成功
	D_FALSE		失败
*/
D_Bool d_nvpart_lock (void) D_FUNCPOSTFIT;

/** @ brief 	对nvram查询加锁状态
* @return
	D_TRUE		成功
	D_FALSE		失败
*/
D_Bool d_nvpart_unlock (void) D_FUNCPOSTFIT;

/** @ brief 	对nvram查询解锁状态
* @return
	D_TRUE		成功
	D_FALSE		失败
*/
D_Bool d_nvpart_check_lock (void) D_FUNCPOSTFIT;

/** @ brief 	尝试锁定nvram
* @return
	D_TRUE		成功
	D_FALSE		失败
*/
D_Bool d_nvpart_check_unlock()D_FUNCPOSTFIT;

/** @brief 设置分区所需相关信息，包括分区表配置，分区表个数，以及loader所占用的空间大小
* @param
		config		分区表配置数据数组首地址，应当是一个全局有效的数组地址
		count		分区表数组元素个数
		loader_size	系统中，loader需要的nvram空间
* @return
		D_OK		成功
*/
D_Result d_nvpartcfg_set_config(const D_NVPartCfg *config, D_Int count, D_Size loader_size) D_FUNCPOSTFIT;

/** @brief 设置分区尾标志
* @param flag   分区尾标志
*/
void d_nvpart_set_tail_flag(D_U8 flag);

#ifdef  __cplusplus
}
#endif

#endif	//__NVPART_DEF_AND_FUN_HEADER__
