#ifndef	__NVPART_DEF_AND_FUN_HEADER__
#define	__NVPART_DEF_AND_FUN_HEADER__
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dNVRam.h"

/** @brief NVRam�豸��Ŀ*/
#define D_NV_DEV_CNT						(1)

/** @brief NVRam ����ID*/
typedef enum {
	D_NV_PART_ALL			= 0,/**< �����豸*/
	D_NV_PART_WRITABLE		= 1,/**< �豸��д��*/
	D_NV_PART_TABLE			= 2,/**< ������*/
	D_NV_PART_TABLE_BAK		= 3,/**< ��������*/
	D_NV_PART_LOADER		= 4,/**< Loader����*/
	D_NV_PART_SYSTEM 		= 5,/**< ����ϵͳ����*/
	D_NV_PART_CA1 			= 6,/**< CA����*/
	D_NV_PART_APP           = 7,/**< Ӧ�ó������*/
	D_NV_PART_CA2   		= 8,/**< CA2����*/
	D_NV_PART_CA3			= 9,/**< CA3����*/
	D_NV_PART_PROG			= 10,/**< ��Ŀ����*/
	D_NV_PART_PARAM			= 11,/**< �����洢����*/
	D_NV_PART_BAK			= 12,/**< ���ݷ���*/
	D_NV_PART_RSET          = 13,/**< ��¼������*/
	D_NV_PART_MAIL			= 14,/**< �ʼ�����*/
	D_NV_PART_DATA          = 15,/**< �û������� */
	D_NV_PART_ADVERTISE     = 16,/**< ������ݷ���*/
	D_NV_PART_RESERVED      = 17,/**< Ԥ������*/
	D_NV_PART_PROG2         = 18,/**< �ڶ�����Ŀ����*/
	D_NV_PART_LOGO          = 19,/**< logo����*/
	D_NV_PART_DB_DEFAULT    = 20,/**< Ԥ�����ݿ����*/
	D_NV_PART_LOGO_DEFAULT = 21,/**< Ԥ�����ݿ����*/
	D_NV_PART_FLASH_HEADER  = 22, /**< ֱ���� Flash_header*/
	D_NV_PART_TDI		    = 23, /**< ֱ���� TDI INFO*/
	D_NV_PART_TDI_BAK	    = 24, /**< ֱ���� TDI BACKUP INFO*/
	D_NV_PART_OSDTEXT	    = 25, /**< ֱ���� ǰ���·��ַ�������*/
	D_NV_PART_RATINGS 	    = 26, /**< ֱ���� �������¼�����*/
	D_NV_PART_CA4   		= 27,/**< CA4����*/
	D_NV_PART_CA5			= 28,/**< CA5����*/
	D_NV_PART_CNT            /**<���������͸���*/
} D_NVPartID;

/** @brief NVRam������������*/
typedef enum {
	D_NV_PART_TYPE_DATA		= 1,
	D_NV_PART_TYPE_ZIP_DATA	= 2,
	D_NV_PART_TYPE_APP		= 3,
	D_NV_PART_TYPE_ZIP_APP= 4,
	D_NV_PART_TYPE_BLOCK	= 5
} D_NVPartType;

/** @brief ������Ϣ*/
typedef struct {
	D_U8					id;
	D_U8					parent_id;
	D_U8					need_backup;		// ԭ��Ϊrfu��������־��������ǰ��Ҫ�����Ա�������
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

/** @brief NVRam����*/
typedef struct {
	D_Bool					used;
	D_NVPartInfo	  		info;
//	D_Size					nv_offset;
//	D_Size					nv_size;
	D_Size					data_size;
} D_NVPart;

/** @brief NVRam�豸��Ϣ*/
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

/** @brief ������Ϣβ*/
typedef struct {
	D_U32					size;		/* ���ݴ�С*/
	D_U8					id;			/* ������ʶD_NVPartID*/
	D_U8					rfu;			/* ����	*/
	D_U8					type;		/* ����D_NVPartType*/
	D_U8					flag;		/* ��ʶ���̶�ΪD_NV_PART_FLAG */
} D_NVPartTail;

/** @brief NVRam�����豸���*/
typedef D_Handle	D_HNVPart;


/** @brief 	ȡ��ָ����NVRam�豸
* @param
		nv_id				�����豸��ʶ
* @return
		NULL				ʧ��
		��Чָ��		�ɹ�
*/
D_NVDev* get_nv (D_ID nv_id) D_FUNCPOSTFIT;

/**@brief 	��������������Ч�ԣ���Ϊ�ṩ������
@return
		D_OK			������Ч
		����ֵ		������
*/
D_Result _check_part(void) D_FUNCPOSTFIT;

/** @brief 	NVRam��������ϵͳ��ʼ��
* @return
	D_OK		�ɹ�
	D_ERR		ʧ��
*/
D_Result d_nvpart_open (void) D_FUNCPOSTFIT;

/** @brief 	��������ϵͳ�˳�
* @return
	D_OK		�ɹ�
	D_ERR		ʧ��
*/
D_Result d_nvpart_close (void) D_FUNCPOSTFIT;

/** @brief 	��ָ���豸������һ������
* @param
	nv_id		NVRam�豸ID
	info			������Ϣ
* @return
	D_OK		�ɹ�
	D_ERR		ʧ��
*/
D_Result d_nvpart_add (D_ID nv_id, D_NVPartInfo *info) D_FUNCPOSTFIT;

/** @brief 	��ָ���豸��ɾ��һ������
* @param 
	nv_id		NVRam�豸ID
	part_id		Ҫɾ���ķ���ID
* @return
	D_OK		�ɹ�
	D_ERR		ʧ��
*/
D_Result d_nvpart_remove (D_ID nv_id, D_ID part_id) D_FUNCPOSTFIT;

/** @brief 	�洢һ���豸�ķ�����
* @param 
	nv_id		NVRam�豸ID
* @return
	D_OK		�ɹ�
	D_ERR		ʧ��
*/
D_Result d_nvpart_store (D_ID nv_id) D_FUNCPOSTFIT;

/** @brief 	����һ���������
* @param 
	nv_id		NVRam�豸ID
	id			 �����豸ID
* @return
	D_INVALID_HANDLE		ʧ��
	����ֵ				�ɹ�
*/
D_HNVPart d_nvpart_create (D_ID nv_id, D_NVPartID id) D_FUNCPOSTFIT;

/** @brief 	����һ���������
* @param
	hnvp		�������
* @return
	D_OK		�ɹ�
	D_ERR		ʧ�ܷ���
*/
D_HNVPart d_nvpart_destroy (D_HNVPart hnvp) D_FUNCPOSTFIT;

/** @brief 	ȡ��һ����������Ϣ
* @param
	hnvp		�����豸���
* @return
	D_OK		�ɹ�
	D_ERR		ʧ��
*/
D_Result d_nvpart_get_info (D_HNVPart hnvp, D_NVPartInfo *info) D_FUNCPOSTFIT;

/** @brief 	��һ������
* @param 
	hnvp		�����豸���
	offset		����ʼλ��ƫ��
	ptr			�����ݻ�����
	size			�����ݴ�С
* @return
	�Ǹ���	�ɹ�������read���ֽ���
	����		ʧ��
*/
D_Size d_nvpart_read (D_HNVPart hnvp, D_Size offset, D_U8 *ptr, D_Size size) D_FUNCPOSTFIT;

/** @brief 	����һ������
* @param
	hnvp		�����豸���
* @return
	D_OK		�ɹ�
	D_ERR		ʧ��
	D_ERR_INVALID_HANDLE		��Ч���
	D_ERR_FAULT					��������
*/
D_Result d_nvpart_erase (D_HNVPart hnvp) D_FUNCPOSTFIT;

/** @brief 	����һ��������ͬʱ�����¼�����
* @param 
	hnvp						�����豸���
	valid_data_len					?????????Ŀǰδʹ��
	callback						���������е��¼�����ӿ�
* @return
	D_OK						�ɹ�
	D_ERR_INVALIE_HANDLE		�����Ч
*/
D_Result d_nvpart_erase_with_hook (D_HNVPart hnvp,D_U32 valid_data_len,void(*callback)(D_U32 param)) D_FUNCPOSTFIT;

/** @brief 	дһ������
* @param 
	hnvp			�����豸���
	offset 			д��ʼλ��ƫ��
	ptr 				д���ݻ�����
	size 				д���ݴ�С
* @return
	�Ǹ���		�ɹ�
	����			ʧ��
*/
D_Size d_nvpart_write (D_HNVPart hnvp, D_Size offset, const D_U8 *ptr, D_Size size) D_FUNCPOSTFIT;

/** @brief	дһ������β��Ϣ
* @param
	hnvp		�����豸���
 	id			β��Ϣ�ķ���ID
* @return
	D_OK		�ɹ�
	D_ERR		ʧ��
*/
D_Result d_nvpart_write_tail_ex (D_HNVPart hnvp, D_U8 id) D_FUNCPOSTFIT;

/** @brief	дһ������β��Ϣ
* @param
	hnvp		�����豸���
* @return
	D_OK		�ɹ�
	D_ERR		ʧ��
*/
D_Result d_nvpart_write_tail (D_HNVPart hnvp) D_FUNCPOSTFIT;

/** @brief	���һ�������ڵ������Ƿ���Ч
* @param
	hnvp		�����豸���
	size 			������Ч���ݵ��ֽ���
	id	 		����β��Ϣ�еķ���ID
* @return
	D_TRUE		�ɹ�
	D_FALSE		ʧ��
*/
D_Bool d_nvpart_is_available (D_HNVPart hnvp, D_Size *size, D_U8 *id) D_FUNCPOSTFIT;

/** @brief 	ֱ�Ӷ�ȡflash��ʵ��Ϊ�̰߳�ȫ��ֱ��nvram����
* @param 
	dev_id		�豸��ʶ
	offset		Ҫ���ʵ��������豸�е�ƫ��
	readbuf		���Ҫ��ȡ���ݵĻ�����
	rbsize		������������
* @return
	�Ǹ���	�ɹ�
	D_ERR		ʧ��
*/
D_Size d_nvpart_read_flash(D_ID dev_id, D_Size offset, void *readbuf, D_Size rbsize) D_FUNCPOSTFIT;

/** @brief 	ֱ��дflash��ʵ��Ϊ�̰߳�ȫ��ֱ��nvram����
* @param
	dev_id		�豸��ʶ
	offset		Ҫ���ʵ��������豸�е�ƫ��
	writebuf		���Ҫ��ȡ���ݵĻ�����
	wbsize		������������
* @return
	�Ǹ���	�ɹ�
	D_ERR		ʧ��
*/
D_Size d_nvpart_write_flash(D_ID dev_id, D_Size offset, const void *writebuf, D_Size wbsize) D_FUNCPOSTFIT;

/** @brief 	ֱ�Ӳ���flash��ʵ��Ϊ�̰߳�ȫ��ֱ��nvram����
* @param
	dev_id		�豸��ʶ
	offset		Ҫ���ʵ��������豸�е�ƫ��
	rbsize		������������
* @return
	�Ǹ���	�ɹ�
	D_ERR		ʧ��
*/
D_Size d_nvpart_erase_flash(D_ID dev_id, D_Size offset, D_Size wbsize) D_FUNCPOSTFIT;

/** @ brief 	��nvramָ����ַ���м���
@param
	hnvp		�������
	offset		Ҫ��������Ľ�����ַ��Ϊ�����е�ƫ�Ƶ�ַ
* @return
	D_TRUE		�ɹ�
	D_FALSE		ʧ��
*/
D_Bool d_nvpart_lock_part (D_HNVPart hnvp, D_Size offset) D_FUNCPOSTFIT;

/** @ brief 	��nvramָ����ַ���н���
@param
	hnvp		�������
	offset		Ҫ��������Ľ�����ַ��Ϊ�����е�ƫ�Ƶ�ַ
* @return
	D_TRUE		�ɹ�
	D_FALSE		ʧ��
*/
D_Bool d_nvpart_unlock_part (D_HNVPart hnvp, D_Size offset) D_FUNCPOSTFIT;

/** @ brief 	��nvram��ѯ����״̬
@param
	hnvp		�������
	offset		Ҫ��������Ľ�����ַ��Ϊ�����е�ƫ�Ƶ�ַ
* @return
	D_TRUE		�ɹ�
	D_FALSE		ʧ��
*/
D_Bool d_nvpart_check_lock_part (D_HNVPart hnvp, D_Size offset) D_FUNCPOSTFIT;

/** @ brief 	��nvram��ѯ����״̬
@param
	hnvp		�������
 	offset		Ҫ��������Ľ�����ַ��Ϊ�����е�ƫ�Ƶ�ַ
* @return
	D_TRUE		�ɹ�
	D_FALSE		ʧ��
*/
D_Bool d_nvpart_check_unlock_part(D_HNVPart hnvp, D_Size offset)D_FUNCPOSTFIT;


/** @ brief 	��nvram����
* @return
	D_TRUE		�ɹ�
	D_FALSE		ʧ��
*/
D_Bool d_nvpart_lock (void) D_FUNCPOSTFIT;

/** @ brief 	��nvram��ѯ����״̬
* @return
	D_TRUE		�ɹ�
	D_FALSE		ʧ��
*/
D_Bool d_nvpart_unlock (void) D_FUNCPOSTFIT;

/** @ brief 	��nvram��ѯ����״̬
* @return
	D_TRUE		�ɹ�
	D_FALSE		ʧ��
*/
D_Bool d_nvpart_check_lock (void) D_FUNCPOSTFIT;

/** @ brief 	��������nvram
* @return
	D_TRUE		�ɹ�
	D_FALSE		ʧ��
*/
D_Bool d_nvpart_check_unlock()D_FUNCPOSTFIT;

/** @brief ���÷������������Ϣ���������������ã�������������Լ�loader��ռ�õĿռ��С
* @param
		config		�������������������׵�ַ��Ӧ����һ��ȫ����Ч�������ַ
		count		����������Ԫ�ظ���
		loader_size	ϵͳ�У�loader��Ҫ��nvram�ռ�
* @return
		D_OK		�ɹ�
*/
D_Result d_nvpartcfg_set_config(const D_NVPartCfg *config, D_Int count, D_Size loader_size) D_FUNCPOSTFIT;

/** @brief ���÷���β��־
* @param flag   ����β��־
*/
void d_nvpart_set_tail_flag(D_U8 flag);

#ifdef  __cplusplus
}
#endif

#endif	//__NVPART_DEF_AND_FUN_HEADER__
