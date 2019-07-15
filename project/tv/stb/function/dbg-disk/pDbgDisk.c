/** @file
* @brief  ��ӡ�����USB�ļ�
* @author ֣ΰ
* @date
*/
#include "dFileSystem.h"
#include "dResource.h"
#include "dDebug.h"
#include "dApp.h"
#include "dTask.h"
#include "dDisk.h"
#include "dMem.h"
#include "dMMan.h"
#include "dMsg.h"
#include "dTypes.h"

extern D_Int UartPutc(D_Int c);
extern D_Handle p_dbg_disk_destroy(D_Handle hscan);
extern D_Handle p_dbg_disk_create(D_S8 priority);

#define P_DBG_DISK_BUF_SIZE      0x8000//0x10000        /* ���buf�Ĵ�С64k */
#define P_DBG_DISK_MEM_SIZE      0x10000//0x20000        //�ڴ��С128k
#define P_DBG_DISK_READ_MIN      0              //ÿ�ν��ܵ���С��ֵ
#define P_DBG_DISK_READ_MAX      0x1000//0x4000         //��ȡ�������ֵ
#define P_DBG_DISK_WRTIE_TIME    100            /* ����ȴ�ʱ�� */
#define FILE_NAME                "c:/disk_dbg.txt"
#define FILE_DIR                 "c:"
#define abs(x)      ((x)>=0?(x):-(x))

typedef struct
{
    D_U8            *buf;            /**< �ڴ��ַ*/
    D_HMMan         hmm;             /**<�ڴ���������*/
    D_HApp          happ;            /**< Ӧ�þ��*/
    D_U8            *sec;            /**< pull���ݵ�BUF*/
    D_U8            *dbg_buf;        /**<push ���ݵĻ���BUF */
    D_U32           w_ptr;           /**<w_ptr ���ݵ����λ�� */
    D_U32           r_ptr;           /**<r_ptr ���ݵ����λ�� */
    D_Handle        file_handle;     /**<file_handle���ļ��ľ�� */

} P_DBG_DISK;

static P_DBG_DISK   *disk_dbg = NULL;                /**@brief< ��Դָ��*/
static D_S64 w_num = 0; /*д�Ĵ���*/
static D_S64 r_num = 0; /*���Ĵ���*/

/** @brief  �����ļ������������׼��ʹ��
* @param[in] void   ע��
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
* @note ע��
*/
D_Result dbg_disk_create_file(void) D_FUNCPOSTFIT
{
    D_Handle file_hand, file_handle;

    file_hand = d_fsm_find_file_dir(FILE_NAME);
    if( file_hand != D_OK )
    {
        /*
        D_Result ret = 0;
        ret = d_fsm_dir_create(FILE_DIR);  // ����Ŀ¼
        if( ret != D_OK )
        {
            return D_ERR;
        }*/

        file_handle = d_fs_create(FILE_NAME);
        if (file_handle == NULL)
        {
            return D_ERR;
        }
        else
        {
            d_fs_close(file_handle);
            return D_OK;
        }
    }
    return D_OK;
}
/** @brief  ɾ���ļ�
* @param[in] void   ע��
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
* @note ע��
*/
D_Result dbg_disk_destroy_file(void) D_FUNCPOSTFIT
{
    d_fsm_file_delete(FILE_NAME);
    return D_OK;
}

/** @brief  ����ʼ����׼��
* @param[in] void   ע��
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
* @note ע��
*/
static  P_DBG_DISK* dbg_disk_start (void) D_FUNCPOSTFIT
{
    D_U8        *buf;
    D_HMMan     hmm;

    buf = (D_U8*) d_mem_alloc(0, P_DBG_DISK_MEM_SIZE);
    if(! buf)
    {
        return NULL;
    }
    hmm = d_mman_create((D_Ptr)buf, (D_Size)P_DBG_DISK_MEM_SIZE, (D_MManType)D_MMAN_HEAP); //����һ���ڴ������
    if(D_INVALID_HANDLE == hmm)
    {
        d_mem_free (buf);
        return NULL;
    }
    disk_dbg = (P_DBG_DISK*) d_mman_alloc((D_HMMan)hmm, sizeof (P_DBG_DISK)); //ͨ���ڴ����������һ���ڴ�
    if(! disk_dbg)
    {
        d_mman_destroy (hmm);
        d_mem_free (buf);
        return NULL;
    }
    memset(disk_dbg, 0, sizeof (P_DBG_DISK));
    disk_dbg->sec = (D_U8*) d_mman_alloc((D_HMMan) hmm, P_DBG_DISK_BUF_SIZE / 2);//ͨ���ڴ����������һ���ڴ�
    if(! disk_dbg->sec)
    {
        d_mman_destroy (hmm);
        d_mem_free (buf);
        return NULL;
    }
    memset(disk_dbg->sec, 0, P_DBG_DISK_BUF_SIZE / 2);
    disk_dbg->dbg_buf = (D_U8*) d_mman_alloc((D_HMMan) hmm, (D_Size) P_DBG_DISK_BUF_SIZE);//ͨ���ڴ����������һ���ڴ�
    if(! disk_dbg->dbg_buf)
    {
        d_mman_destroy (hmm);
        return NULL;
    }
    memset(disk_dbg->dbg_buf, 0, P_DBG_DISK_BUF_SIZE);
    disk_dbg->hmm = hmm;
    disk_dbg->buf = buf;
    return disk_dbg;
}

/** @brief  ������������
* @param[in] void   ע��
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
* @note ע��
*/
static  D_Result dbg_disk_stop (void) D_FUNCPOSTFIT
{
    D_U8 *buf = disk_dbg->buf;

    if(D_INVALID_HANDLE  != disk_dbg->hmm)
    {
        d_mman_destroy (disk_dbg->hmm);                   /*�ͷ�һ���ڴ������*/
        disk_dbg->hmm = D_INVALID_HANDLE;
    }
    if(buf)
    {
        d_mem_free (buf);                           /*�ͷŷ�����ڴ�*/
    }
    d_fs_close(disk_dbg->file_handle);
    disk_dbg->file_handle = -1;
    return D_OK;
}

/** @brief  �ӻ���buf��ȡ������
* @param[in] void   ע��
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
* @note ע��
*/
static D_Result dbg_disk_pull(void) D_FUNCPOSTFIT  //���ڴ��ж�ȡ����
{
    D_U8 *r_buf;
    D_S32 length, r_length;
    D_S32 ret_sys;
    D_FsVolumeInfo VolumeInfo;

    if(!disk_dbg)
        return D_ERR;
    r_length = disk_dbg->w_ptr - disk_dbg->r_ptr;
//    length = (D_S32 )abs(disk_dbg->w_ptr - disk_dbg->r_ptr);
    if(r_length < 0)
    {
        length = 2 * P_DBG_DISK_BUF_SIZE - disk_dbg->r_ptr + disk_dbg->w_ptr;
    }
    else
        length = r_length;

    r_buf = disk_dbg->dbg_buf + (disk_dbg->r_ptr % P_DBG_DISK_BUF_SIZE);

    if(length > P_DBG_DISK_READ_MAX)
        length = P_DBG_DISK_READ_MAX;

    ret_sys = d_fsm_volume_get_info(FILE_DIR, &VolumeInfo);
    if( ret_sys != D_OK )
    {
        D_ERROR ("[Disk_dbg] NO USB DEVICE!\n");
        return D_ERR;
    }
    if(D_OK != dbg_disk_create_file())
    {
        D_DUMP("[Disk_dbg] Creat file failed!\n");
        return D_ERR;
    }

    if(length > P_DBG_DISK_READ_MIN)
    {
        D_S64 ret;

        disk_dbg->file_handle = d_fs_open(FILE_NAME , 0);
        /* ��ȡ�ļ���ǰ��С,,��Ҫ���һ����С�ж� */
        ret = d_fsm_get_file_size(FILE_NAME);
        /* ����дָ�뵽�ϴ�д��λ�� */
        d_fs_seek(disk_dbg->file_handle, ret);

        if(((disk_dbg->r_ptr % P_DBG_DISK_BUF_SIZE) + length) > P_DBG_DISK_BUF_SIZE)/* Ҫ�������ݸպ��ڷ�תλ�� */
        {
            D_U32 f_length = P_DBG_DISK_BUF_SIZE - (disk_dbg->r_ptr % P_DBG_DISK_BUF_SIZE);

            memcpy(disk_dbg->sec , r_buf, f_length);
            memcpy(disk_dbg->sec + f_length, disk_dbg->dbg_buf, (length - f_length));
        }
        else    /* ���ڷ�תλ��ʱ */
        {
            memcpy(disk_dbg->sec, r_buf, length);
        }

        d_fs_write(disk_dbg->file_handle, disk_dbg->sec, length);
        d_fs_close(disk_dbg->file_handle);
        r_num += 1;

        disk_dbg->r_ptr = (disk_dbg->r_ptr + length) % (2 * P_DBG_DISK_BUF_SIZE);
        return D_OK;
    }

    else
        return D_ERR;
}

/** @brief  ����ص�����
* @param[in] D_Msg * msg   ע��
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
* @note ע��
*/
static D_Result dbg_disk_callback(D_Msg * msg)
{
    P_DBG_DISK  *dbg;

    dbg = (P_DBG_DISK*) d_app_get_data ((D_HApp) d_app_self ());
    switch (msg->type)
    {
        case D_MSG_APP_CREATE:
        {
            dbg = msg->app.arg;
            d_app_set_data ((D_HApp) d_app_self (), (D_Ptr) dbg);

            d_app_set_timeout(d_app_self(), P_DBG_DISK_WRTIE_TIME);//����ʱʱ��
            break;
        }
        case D_MSG_APP_TIMEOUT:
        {
            dbg_disk_pull();
            break;
        }
        case D_MSG_APP_DESTROY:
        {
            dbg_disk_stop ();
            break;
        }
        default:
            break;
    }
    return D_OK;
}

/** @brief  ��ȡ��ӡ���ݣ�����ŵ�����buf��
* @param[in] D_Int s   ע��
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
* @note ע��
*/
static D_Int p_dbg_disk_push(D_Int s)
{
    D_Ptr base_p;
    D_U16 w_length, rest;

    if(!disk_dbg)
        return D_FALSE;
   // UartPutc(s);
    base_p = disk_dbg->dbg_buf + (disk_dbg->w_ptr % P_DBG_DISK_BUF_SIZE);
    w_length = sizeof(D_Char);

    rest = abs(disk_dbg->w_ptr - disk_dbg->r_ptr);
    if((P_DBG_DISK_BUF_SIZE - rest) >= w_length)//ʣ��Ŀռ��㹻д�����ݳ���
    {
        D_U16 length;
        length = disk_dbg->w_ptr % P_DBG_DISK_BUF_SIZE + w_length;
        /* Ҫд�����ݸպ��ڷ�תλ�� */
        if(length > P_DBG_DISK_BUF_SIZE)
        {
            memcpy(disk_dbg->dbg_buf, (&s), w_length);
            w_num += 1;
        }
        /* ���ڷ�תλ��ʱ */
        else
        {
            memcpy(base_p, &s, w_length);

            if((disk_dbg->w_ptr % P_DBG_DISK_BUF_SIZE) != (w_num % P_DBG_DISK_BUF_SIZE))
            {
                base_p = NULL;
            }
            w_num += 1;
        }
        disk_dbg->w_ptr = ( disk_dbg->w_ptr + w_length) % (2 * P_DBG_DISK_BUF_SIZE);
    }
    return D_OK;
}

/** @brief  ���񴴽����
* @param[in] D_S8 priority   ע��
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
* @note ע��
*/
D_Handle p_dbg_disk_create(D_S8 priority)D_FUNCPOSTFIT
{
    /*����ռ�*/
    disk_dbg = dbg_disk_start();

    d_dbg_set_io_func(NULL, p_dbg_disk_push);
    if(! disk_dbg)
    {
        return D_INVALID_HANDLE;
    }
    /*����*/
    disk_dbg->happ = d_app_create ("Disk_Dbg_test", priority, D_TEST_TASK_STACK_SIZE, D_TEST_QUEUE_SIZE, dbg_disk_callback, (D_Ptr)disk_dbg);

    if(D_INVALID_HANDLE == disk_dbg->happ)
    {
        dbg_disk_destroy_file ();
        return disk_dbg->happ;
    }
    /*ͬ�����ȴ��豸�������*/
    d_app_sync (disk_dbg->happ);
    return disk_dbg->happ;
}

/** @brief  ��������
* @param[in] D_Handle hscan   ע��
* @retval D_OK  �ɹ�
* @retval D_ERR  ʧ��
* @note ע��
*/
D_Handle p_dbg_disk_destroy(D_Handle hscan)D_FUNCPOSTFIT
{
    d_app_destroy (hscan);
    disk_dbg = NULL;

    return hscan;
}











