/** @file
* @brief 文件系统
* @author
* @date 
*/
#ifndef __D_FILESYSTEM_H
#define __D_FILESYSTEM_H
#ifdef __cplusplus
extern "C"{
#endif

#include "dTypes.h"

#define MAX_PATH                256	//128 //wangyq  20140113  17:53
#define FILE_TYPE_NUM          32
#define FILE_OPEN_MODE_READ     0x00000000
#define FILE_OPEN_MODE_WRITE    0x00000001

/**@brief 查找文件功能交换数据的结构*/
typedef struct
{
	D_Char *full_path; /**< 文件所在全路径*/
	D_Char *filename; /**< 文件名称，不包括路径*/
	D_U32 attribute; /**< 文件属性 */
	D_S64 file_size; /**< 搜索到的文件的大小，文件夹时无意义 */
}D_FileFindData;

typedef struct
{
	D_U8  flag;
	D_U8  step;
	D_U8  device_idx;
	D_U32 start_clust;
	D_U32 filetype[FILE_TYPE_NUM];   /*匹配项数组*/
    D_U8  num;       /*数组元素数量*/
}D_FileFindPara;
typedef struct
{
    const D_Char *name;
    D_Char  formatno;
    D_Char  format[8];
    D_S64 free_size;
    D_S64 total_size;
}D_FsVolumeInfo;

typedef struct
{
    D_Bool plug;
    D_Int logic_drv_no;
}D_FsHotPlugNotifyInfo;

typedef D_Bool (*D_ReadDirProcCB)(D_FileFindData *fd, D_Ptr arg) D_FUNCPOSTFIT;
typedef D_Bool (*D_ReadDirProcCB_ext)(D_FileFindData *fd, D_Ptr arg,D_Ptr find_para) D_FUNCPOSTFIT;

typedef enum
{
    D_Seek_Begin = 0,
    D_Seek_Current,
    D_Seek_End,
}D_FsSeekWhence;

typedef enum
{
    FAT_12 = 1,
    FAT_16,
    FAT_32,
    NTFS,
}D_FsFormat;


D_Result d_file_system_open(void) D_FUNCPOSTFIT;

D_Result d_file_system_close(void) D_FUNCPOSTFIT;

D_Result d_fsm_readdir(const D_Char *full_path, D_ReadDirProcCB readdir_proc, D_Ptr arg) D_FUNCPOSTFIT;
D_Result d_fsm_readdir_ext(const D_Char *full_path, D_ReadDirProcCB_ext readdir_proc, D_Ptr arg,D_Ptr find_para) D_FUNCPOSTFIT;

/**@brief 创建文件
* @param full_path		欲创建的文件的全路径
* @param fast_access	快速文件访问，非零则后续通过fs_create返回的句柄访问文件时，将以快速模式访问。
* @return	0，创建失败；其他值，创建成功，返回值为与此文件对应的句柄
*/
D_Handle d_fs_create(const D_Char *full_path) D_FUNCPOSTFIT;

/**@brief 打开已存在文件，获得访问文件的句柄
* @param full_path		欲访问的文件的全路径
* @param open_mode	文件访问方式，可设置两个位信息指明模式
						bit0		1	可写文件
						bit1		1	快速访问
* @return		0，打开文件失败；其他值，打开文件成功，返回值为与此文件对应的句柄
*/
D_Handle d_fs_open(const D_Char *full_path, D_Int open_mode) D_FUNCPOSTFIT;

/**@brief 关闭文件句柄
* @param fs_handle		文件句柄，由fs_create或者fs_open返回
* @return				无
*/
void d_fs_close(D_Handle fs_handle) D_FUNCPOSTFIT;

/**@brief 读取文件数据
* @param fs_handle		文件句柄，由fs_create或者fs_open返回
* @param read_buf[out]	放置读取结果的缓冲区
* @param read_size		欲读取的数据大小
* @return				<0，读取失败；其他值，成功读取的字节数
*/
D_Size d_fs_read(D_Handle fs_handle, D_U8 *read_buf, D_Size read_size) D_FUNCPOSTFIT;

/**@brief 写入文件数据
* @param fs_handle		文件句柄，由fs_create或者fs_open返回
* @param write_buf		欲写入数据的缓冲区
* @param write_size		欲写入的数据大小
* @return				<0，写入失败；其他值，成功写入的字节数
*/
D_Size d_fs_write(D_Handle fs_handle, D_U8 *write_buf, D_Size write_size) D_FUNCPOSTFIT;

/**@brief 设定文件当前方位位置
* @param fs_handle		文件句柄，由fs_create或者fs_open返回
* @param whence         偏移起始位置
* @param offset			偏移字节数
* @return				<0，失败；其他值，成功
*/
D_S64 d_fs_seek_ex(D_Handle fs_handle, D_FsSeekWhence whence, D_S64 offset) D_FUNCPOSTFIT;

/**@brief 设定文件读写位置
* @param fs_handle		文件句柄
* @param offset			相对欲文件起始的偏移字节数
* @return				-1，失败；其他值，成功
*/
#define d_fs_seek(__f, __offset)       d_fs_seek_ex((__f), D_Seek_Begin, (__offset))

/**@brief 获取文件当前方位位置
* @param fs_handle		文件句柄，由fs_create或者fs_open返回
* @return				-1，失败；其他值，成功
*/
D_S64 d_fs_tell(D_Handle fs_handle) D_FUNCPOSTFIT;

/**@brief 设定文件当前方位位置到文件起始位置
* @param fs_handle		文件句柄，由fs_create或者fs_open返回
* @return				-1，失败；0，成功
*/
D_Result d_fs_rewind(D_Handle fs_handle) D_FUNCPOSTFIT;

/**@brief 设定已存在文件大小，若欲设置的文件比当前的小，则不修改大小而直接返回
* @param fs_handle		文件句柄，由fs_create或者fs_open返回
* @param size			欲设置的文件大小
* @return					-1，失败；其他值，文件大小
*/
D_S64 d_fs_set_size(D_Handle fs_handle, D_S64 size) D_FUNCPOSTFIT;

/**@brief 取得文件大小
* @param fs_handle      文件句柄，由fs_create或者fs_open返回
* @return                   -1，失败；其他值，文件大小
*/
D_S64 d_fs_get_size(D_Handle fs_handle) D_FUNCPOSTFIT;

D_Result d_fs_fsync(D_Handle fs_handle) D_FUNCPOSTFIT;

/**@brief 获得已存在文件的大小
* @param full_path			文件全路径
* @return 					-1，失败；其他值，文件大小
*/
D_S64 d_fsm_get_file_size(const D_Char *full_path) D_FUNCPOSTFIT;

/**@brief 修改文件名称
* @param old_full_name	原文件全路径
* @param new_file_name	新文件名称，将要替换全路径old_full_name的最后文件名称部分
* @return					0，成功；<0，失败
*/
D_Result d_fsm_file_rename(const D_Char *old_full_name, const D_Char *new_file_name) D_FUNCPOSTFIT;

/**@brief 删除文件
* @param full_path			欲删除文件的全路径
* @return					0，成功；<0，失败
*/
D_Result d_fsm_file_delete(const D_Char *full_path) D_FUNCPOSTFIT;

/**@brief 拷贝文件
* @param src_full_name	源文件全路径
* @param dest_full_name	目标文件全路径
* @param overwrite_if_target_exist		当目标文件存在时，0则结束，非零值则覆盖
* @return				0，成功；<0，失败
*/
D_Result d_fsm_file_copy(const D_Char *src_full_name, const D_Char *dest_full_name, D_Bool overwrite_if_target_exist) D_FUNCPOSTFIT;

/**@brief 创建文件夹
* @param full_path		文件夹全路径
* @return				0，成功；<0，失败
*/
D_Result d_fsm_dir_create(const D_Char *full_path) D_FUNCPOSTFIT;

/**@brief 删除文件夹
* @param full_path		文件夹全路径
* @param delete_full	非零则删除该文件夹及其子文件夹和其中的文件。目前未实现该选项
* @return				0，成功；<0，失败
*/
D_Result d_fsm_dir_delete(const D_Char *full_path) D_FUNCPOSTFIT;

/**@brief 获取当前盘符数量与索引值
* @param vol_index 记录索引值数组
* @param count      记录数量
* @return D_OK，成功；其它，失败
*/
D_Result d_fsm_get_volumes(D_U8 vol_index[], D_Int *count) D_FUNCPOSTFIT;

/**@brief 获取盘符信息(格式、空间信息等)
* @param root_path 盘符路径名
* @param info      记录信息
* @return D_OK，成功；其它，失败
*/
D_Result d_fsm_volume_get_info(const D_Char *root_path, D_FsVolumeInfo *info) D_FUNCPOSTFIT;

/**@brief 查询盘符的类型(usb / sd)
* @param vol_index 盘符索引值
* @return 0: usb, 1: sd, 其他值，失败
*/
D_S32 d_fsm_get_volume_type(D_U8 vol_index) D_FUNCPOSTFIT;

/**@brief 查询盘符的类型(usb / sd)与no
* @param[in] vol_index 盘符索引值
* @param[out] type  usb / usbx / sd
* @param[out] type_no  0,1,2...
* @return <0失败 
*/
D_S32 d_fsm_get_volume_type_and_no(D_U8 vol_index, D_S32 *type, D_S32 *type_no) D_FUNCPOSTFIT;

/**@brief 查询盘符的类型(usb / sd)
* @param root_path 盘符路径名
* @return 0: usb, 1: sd, 其他值，失败
*/
D_S32 d_fsm_device_type(const D_Char *root_path) D_FUNCPOSTFIT;

/**@brief 查询盘符的类型(usb / sd)
* @param[in] root_path 盘符路径名
* @param[out] type  usb / usbx / sd
* @param[out] type_no  0,1,2...
* @return <0失败 
*/
D_S32 d_fsm_device_type_and_no(const D_Char *root_path, D_S32 *type, D_S32 *type_no) D_FUNCPOSTFIT;

/**@brief 查询文件名或文件夹是否存在
* @param full_path		文件或文件夹全路径
* @return			0，成功；其他值，失败
*/
D_Result d_fsm_find_file_dir(const D_Char *full_path) D_FUNCPOSTFIT;

/**@brief逻辑路径转换为物理路径*/
D_Result d_fs_path_logic_to_physical(const D_Char *logic_path, const D_Char *phys_path);

/**@brief物理路径转换为逻辑路径*/
D_Result d_fs_path_physical_to_logic(const D_Char *phys_path, const D_Char *logic_path) ;

#if defined(D_SYSTEM_WIN32)
D_Result d_fs_win32_open(void) D_FUNCPOSTFIT;
#elif defined(D_SYSTEM_LINUX)
D_Result d_fs_linux_open(void) D_FUNCPOSTFIT;
#else
D_Result d_fs_fat_open(void) D_FUNCPOSTFIT;
D_Result d_fs_ntfs_open(void) D_FUNCPOSTFIT;
#endif

D_Result d_file_system_suspend (void) D_FUNCPOSTFIT;
D_Result d_file_system_resume(void) D_FUNCPOSTFIT;



#ifdef __cplusplus
}
#endif
#endif
