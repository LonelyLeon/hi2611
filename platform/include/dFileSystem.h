/** @file
* @brief �ļ�ϵͳ
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

/**@brief �����ļ����ܽ������ݵĽṹ*/
typedef struct
{
	D_Char *full_path; /**< �ļ�����ȫ·��*/
	D_Char *filename; /**< �ļ����ƣ�������·��*/
	D_U32 attribute; /**< �ļ����� */
	D_S64 file_size; /**< ���������ļ��Ĵ�С���ļ���ʱ������ */
}D_FileFindData;

typedef struct
{
	D_U8  flag;
	D_U8  step;
	D_U8  device_idx;
	D_U32 start_clust;
	D_U32 filetype[FILE_TYPE_NUM];   /*ƥ��������*/
    D_U8  num;       /*����Ԫ������*/
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

/**@brief �����ļ�
* @param full_path		���������ļ���ȫ·��
* @param fast_access	�����ļ����ʣ����������ͨ��fs_create���صľ�������ļ�ʱ�����Կ���ģʽ���ʡ�
* @return	0������ʧ�ܣ�����ֵ�������ɹ�������ֵΪ����ļ���Ӧ�ľ��
*/
D_Handle d_fs_create(const D_Char *full_path) D_FUNCPOSTFIT;

/**@brief ���Ѵ����ļ�����÷����ļ��ľ��
* @param full_path		�����ʵ��ļ���ȫ·��
* @param open_mode	�ļ����ʷ�ʽ������������λ��Ϣָ��ģʽ
						bit0		1	��д�ļ�
						bit1		1	���ٷ���
* @return		0�����ļ�ʧ�ܣ�����ֵ�����ļ��ɹ�������ֵΪ����ļ���Ӧ�ľ��
*/
D_Handle d_fs_open(const D_Char *full_path, D_Int open_mode) D_FUNCPOSTFIT;

/**@brief �ر��ļ����
* @param fs_handle		�ļ��������fs_create����fs_open����
* @return				��
*/
void d_fs_close(D_Handle fs_handle) D_FUNCPOSTFIT;

/**@brief ��ȡ�ļ�����
* @param fs_handle		�ļ��������fs_create����fs_open����
* @param read_buf[out]	���ö�ȡ����Ļ�����
* @param read_size		����ȡ�����ݴ�С
* @return				<0����ȡʧ�ܣ�����ֵ���ɹ���ȡ���ֽ���
*/
D_Size d_fs_read(D_Handle fs_handle, D_U8 *read_buf, D_Size read_size) D_FUNCPOSTFIT;

/**@brief д���ļ�����
* @param fs_handle		�ļ��������fs_create����fs_open����
* @param write_buf		��д�����ݵĻ�����
* @param write_size		��д������ݴ�С
* @return				<0��д��ʧ�ܣ�����ֵ���ɹ�д����ֽ���
*/
D_Size d_fs_write(D_Handle fs_handle, D_U8 *write_buf, D_Size write_size) D_FUNCPOSTFIT;

/**@brief �趨�ļ���ǰ��λλ��
* @param fs_handle		�ļ��������fs_create����fs_open����
* @param whence         ƫ����ʼλ��
* @param offset			ƫ���ֽ���
* @return				<0��ʧ�ܣ�����ֵ���ɹ�
*/
D_S64 d_fs_seek_ex(D_Handle fs_handle, D_FsSeekWhence whence, D_S64 offset) D_FUNCPOSTFIT;

/**@brief �趨�ļ���дλ��
* @param fs_handle		�ļ����
* @param offset			������ļ���ʼ��ƫ���ֽ���
* @return				-1��ʧ�ܣ�����ֵ���ɹ�
*/
#define d_fs_seek(__f, __offset)       d_fs_seek_ex((__f), D_Seek_Begin, (__offset))

/**@brief ��ȡ�ļ���ǰ��λλ��
* @param fs_handle		�ļ��������fs_create����fs_open����
* @return				-1��ʧ�ܣ�����ֵ���ɹ�
*/
D_S64 d_fs_tell(D_Handle fs_handle) D_FUNCPOSTFIT;

/**@brief �趨�ļ���ǰ��λλ�õ��ļ���ʼλ��
* @param fs_handle		�ļ��������fs_create����fs_open����
* @return				-1��ʧ�ܣ�0���ɹ�
*/
D_Result d_fs_rewind(D_Handle fs_handle) D_FUNCPOSTFIT;

/**@brief �趨�Ѵ����ļ���С���������õ��ļ��ȵ�ǰ��С�����޸Ĵ�С��ֱ�ӷ���
* @param fs_handle		�ļ��������fs_create����fs_open����
* @param size			�����õ��ļ���С
* @return					-1��ʧ�ܣ�����ֵ���ļ���С
*/
D_S64 d_fs_set_size(D_Handle fs_handle, D_S64 size) D_FUNCPOSTFIT;

/**@brief ȡ���ļ���С
* @param fs_handle      �ļ��������fs_create����fs_open����
* @return                   -1��ʧ�ܣ�����ֵ���ļ���С
*/
D_S64 d_fs_get_size(D_Handle fs_handle) D_FUNCPOSTFIT;

D_Result d_fs_fsync(D_Handle fs_handle) D_FUNCPOSTFIT;

/**@brief ����Ѵ����ļ��Ĵ�С
* @param full_path			�ļ�ȫ·��
* @return 					-1��ʧ�ܣ�����ֵ���ļ���С
*/
D_S64 d_fsm_get_file_size(const D_Char *full_path) D_FUNCPOSTFIT;

/**@brief �޸��ļ�����
* @param old_full_name	ԭ�ļ�ȫ·��
* @param new_file_name	���ļ����ƣ���Ҫ�滻ȫ·��old_full_name������ļ����Ʋ���
* @return					0���ɹ���<0��ʧ��
*/
D_Result d_fsm_file_rename(const D_Char *old_full_name, const D_Char *new_file_name) D_FUNCPOSTFIT;

/**@brief ɾ���ļ�
* @param full_path			��ɾ���ļ���ȫ·��
* @return					0���ɹ���<0��ʧ��
*/
D_Result d_fsm_file_delete(const D_Char *full_path) D_FUNCPOSTFIT;

/**@brief �����ļ�
* @param src_full_name	Դ�ļ�ȫ·��
* @param dest_full_name	Ŀ���ļ�ȫ·��
* @param overwrite_if_target_exist		��Ŀ���ļ�����ʱ��0�����������ֵ�򸲸�
* @return				0���ɹ���<0��ʧ��
*/
D_Result d_fsm_file_copy(const D_Char *src_full_name, const D_Char *dest_full_name, D_Bool overwrite_if_target_exist) D_FUNCPOSTFIT;

/**@brief �����ļ���
* @param full_path		�ļ���ȫ·��
* @return				0���ɹ���<0��ʧ��
*/
D_Result d_fsm_dir_create(const D_Char *full_path) D_FUNCPOSTFIT;

/**@brief ɾ���ļ���
* @param full_path		�ļ���ȫ·��
* @param delete_full	������ɾ�����ļ��м������ļ��к����е��ļ���Ŀǰδʵ�ָ�ѡ��
* @return				0���ɹ���<0��ʧ��
*/
D_Result d_fsm_dir_delete(const D_Char *full_path) D_FUNCPOSTFIT;

/**@brief ��ȡ��ǰ�̷�����������ֵ
* @param vol_index ��¼����ֵ����
* @param count      ��¼����
* @return D_OK���ɹ���������ʧ��
*/
D_Result d_fsm_get_volumes(D_U8 vol_index[], D_Int *count) D_FUNCPOSTFIT;

/**@brief ��ȡ�̷���Ϣ(��ʽ���ռ���Ϣ��)
* @param root_path �̷�·����
* @param info      ��¼��Ϣ
* @return D_OK���ɹ���������ʧ��
*/
D_Result d_fsm_volume_get_info(const D_Char *root_path, D_FsVolumeInfo *info) D_FUNCPOSTFIT;

/**@brief ��ѯ�̷�������(usb / sd)
* @param vol_index �̷�����ֵ
* @return 0: usb, 1: sd, ����ֵ��ʧ��
*/
D_S32 d_fsm_get_volume_type(D_U8 vol_index) D_FUNCPOSTFIT;

/**@brief ��ѯ�̷�������(usb / sd)��no
* @param[in] vol_index �̷�����ֵ
* @param[out] type  usb / usbx / sd
* @param[out] type_no  0,1,2...
* @return <0ʧ�� 
*/
D_S32 d_fsm_get_volume_type_and_no(D_U8 vol_index, D_S32 *type, D_S32 *type_no) D_FUNCPOSTFIT;

/**@brief ��ѯ�̷�������(usb / sd)
* @param root_path �̷�·����
* @return 0: usb, 1: sd, ����ֵ��ʧ��
*/
D_S32 d_fsm_device_type(const D_Char *root_path) D_FUNCPOSTFIT;

/**@brief ��ѯ�̷�������(usb / sd)
* @param[in] root_path �̷�·����
* @param[out] type  usb / usbx / sd
* @param[out] type_no  0,1,2...
* @return <0ʧ�� 
*/
D_S32 d_fsm_device_type_and_no(const D_Char *root_path, D_S32 *type, D_S32 *type_no) D_FUNCPOSTFIT;

/**@brief ��ѯ�ļ������ļ����Ƿ����
* @param full_path		�ļ����ļ���ȫ·��
* @return			0���ɹ�������ֵ��ʧ��
*/
D_Result d_fsm_find_file_dir(const D_Char *full_path) D_FUNCPOSTFIT;

/**@brief�߼�·��ת��Ϊ����·��*/
D_Result d_fs_path_logic_to_physical(const D_Char *logic_path, const D_Char *phys_path);

/**@brief����·��ת��Ϊ�߼�·��*/
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
