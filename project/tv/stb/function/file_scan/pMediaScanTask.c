/** @file
* @brief ��ý��ɨ������ģ��
* @author
* @date 2018.01.08: �����ļ�
*/
#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dTypes.h"
#include "pMem.h"
#include "dApp.h"
#include "dMsg.h"
#include "pMediaScanTask.h"
#include "dFileSystem.h"
#include "dDisk.h"

#define D_MEDIA_READ_DISK_DUMP      D_DUMP


#define D_MEDIA_PATH_LEN  D_PATH_LENGTH /**�ļ�·����󳤶�*/

#define D_MEDIA_READ_DISK_TASK_PRIO     (1)             /**�������ȼ�*/
#define D_MEDIA_READ_DISK_TASK_STACK_SIZE  (16*1024)    /**�����ջ��С*/

#define  MEDIA_PARTITION_MAX_CNT (24)

/**@brief dmj ��ý��ɨ������������Խṹ�嶨��*/
typedef struct
{
    D_TaskAttr tv_file_scan_taskattr;     /**��������*/
    D_HTask    tv_file_scan_task_handle; /**ɨ������handle*/
    D_U32 tv_file_scan_state;                 /** ɨ������״̬*/
    D_U32 tv_file_scan_exit_flag;           /**ɨ�������˳���ǣ��û���Ϊ1��ɨ�轫���˳�*/
} TV_MEDIA_FILE_SCAN_TASK_ATTR;

typedef struct
{
    D_Char device[4];  /**��ɨ��Ĵ����̷�*/
    D_U32 vol_index; /**�����̷�*/
    D_Int   mediaTotalPartition;                           /**�ܵĴ�����**/
    D_U8    mediaVolIndexs[MEDIA_PARTITION_MAX_CNT];  /* �ܹ����̷���**/
} MEDIA_SCAN_TASK;

typedef struct
{
    D_U8 hotplug_plug;
    D_U8 hotplug_arg;   
    D_U8  used;
}HOTPLUG_RSET;

/**�������Խṹ���������*/
static TV_MEDIA_FILE_SCAN_TASK_ATTR tv_media_filescan_task = {{0},D_INVALID_HANDLE,0,0};
static HOTPLUG_RSET hotplug_rset[24] = {{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},
                                                                {0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},
                                                                {0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},      
                                                                {0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0}};

static  MEDIA_SCAN_TASK MediaScan_task_info;

static D_HSem sem_media_task;

extern D_Result p_tv_file_scan_get_files_by_type_ex(D_Char *path, D_S32 type, D_U32 *stop_ctrl)D_FUNCPOSTFIT;

/**@brief ��ý��ɨ���������٣�
��ʵ��������ɺ���������٣��˴�ֻ�Ǹ�λ��ز���
*@param[in] task_attr ��������
*/
D_Result p_media_file_scan_task_destroy(void)D_FUNCPOSTFIT
{
    if(tv_media_filescan_task.tv_file_scan_task_handle == D_INVALID_HANDLE)
    {
        return D_ERR;
    }               //�ȴ����������������
    tv_media_filescan_task.tv_file_scan_exit_flag = 1; //���ñ��ֹͣɨ��
    while(tv_media_filescan_task.tv_file_scan_state != 2) // �ȴ�ɨ���˳�����ɾ��ɨ������
    {
        d_task_wait(500);
    }
    tv_media_filescan_task.tv_file_scan_task_handle = D_INVALID_HANDLE;
    tv_media_filescan_task.tv_file_scan_state = 0;
    d_sem_destroy (sem_media_task);
    return D_OK;
}

/**@brief �ļ�ɨ������
*@param[in] arg�ļ�ɨ����������
*/
void media_file_scan_task(D_Ptr arg)D_FUNCPOSTFIT
{
    while(1)
    {
        D_Char *device = (D_Char*)arg ;
        tv_media_filescan_task.tv_file_scan_exit_flag = 0; /**�˳����0����ʾ�������ɨ��*/
        tv_media_filescan_task.tv_file_scan_state = 1;  /**��ʼɨ��ʱ��ɨ��״̬λ��1*/
        p_tv_file_scan_get_files_by_type_ex(device, (D_S32)MediaScan_task_info.vol_index, &tv_media_filescan_task.tv_file_scan_exit_flag); /***��ʼɨ��*/
        tv_media_filescan_task.tv_file_scan_state = 2; /**ɨ����ɺ�����״̬��Ϊ2*/
        d_sem_wait (sem_media_task);
    }
    //d_task_exit();  /**�����˳�*/
}

/**@brief �����ļ�ɨ������
*param[in] task_attr ��������
*/
static D_Result media_file_scan_task_creat(void)D_FUNCPOSTFIT
{
    tv_media_filescan_task.tv_file_scan_taskattr.priority = D_MEDIA_READ_DISK_TASK_PRIO;
    tv_media_filescan_task.tv_file_scan_taskattr.stack_size = D_MEDIA_READ_DISK_TASK_STACK_SIZE;
    tv_media_filescan_task.tv_file_scan_taskattr.id = 0;
    tv_media_filescan_task.tv_file_scan_taskattr.name = "usbtask";
    tv_media_filescan_task.tv_file_scan_task_handle = d_task_create(&(tv_media_filescan_task.tv_file_scan_taskattr), media_file_scan_task, (D_Ptr)MediaScan_task_info.device);
    if(tv_media_filescan_task.tv_file_scan_task_handle == D_INVALID_HANDLE)
    {
        D_MEDIA_READ_DISK_DUMP("Cannot create media read disk applicatin!\n");
        return D_ERR;
    }
    sem_media_task = d_sem_create (NULL);
    return D_OK;
}


/**brief USB �Ȳ�δ���
*@param[in] evt �Ȳ���¼�
*/
D_Result p_media_usb_plug_msg_process(D_U8 plug,D_U8 arg)
{
    //D_Ptr  arg;
    if(plug) 
    {
        D_U32 type;

        type = d_fsm_get_volume_type((D_U8)arg); /**��ȡ��������*/
        if(type == D_ERR)
        {
            return D_ERR;
        }
        if(hotplug_rset[arg].used == 0)
        {
        if(DEVICE_USB == type || DEVICE_USBX == type)
        {
            p_tv_media_mman_open();    /**����ɨ���ļ���¼�����ڴ������*/
                hotplug_rset[arg].used =1;
            if(tv_media_filescan_task.tv_file_scan_task_handle == D_INVALID_HANDLE)
            {
                    MediaScan_task_info.device[0] = 'C' + (D_U8)arg;
                MediaScan_task_info.device[1] = ':';
                    MediaScan_task_info.vol_index = (D_U8)arg;
                if(media_file_scan_task_creat() == D_ERR)
                {
                    D_MEDIA_READ_DISK_DUMP("%s:%d--creat%d task fail\n", __FUNCTION__, __LINE__, type);
                    return D_ERR;
                }
            }
            else
            {
                while(tv_media_filescan_task.tv_file_scan_state != 2)
                {
                    d_task_wait(500);
                }  
                    MediaScan_task_info.device[0] = 'C' + (D_U8)arg;
                MediaScan_task_info.device[1] = ':';
                    MediaScan_task_info.vol_index = (D_U8)arg;
                d_sem_post (sem_media_task);
            }
            return D_OK;
        }
    }
    }
    else   // �豸�γ�
    {
        if(hotplug_rset[arg].used == 1)
        {
            hotplug_rset[arg].used = 0;
            p_tv_delete_volumes_data((D_U32)arg, (D_Bool)plug);
        d_fsm_get_volumes(MediaScan_task_info.mediaVolIndexs, &MediaScan_task_info.mediaTotalPartition);
        if(MediaScan_task_info.mediaTotalPartition == 0)
        {
                p_media_file_scan_task_destroy();
            p_tv_media_mman_close();
        }
    }
    }
    return D_OK;
}


D_Result p_media_hotplug_rset(D_U8 plug,D_U8 arg)
{
    hotplug_rset[arg].hotplug_arg = arg;
    hotplug_rset[arg].hotplug_plug = plug;
    return D_OK;
}


D_Result p_media_delete_all_rset(void)
{
    D_U8 i;

    for(i = 0;i < 24;i ++ )
    {
        if( hotplug_rset[i].used == 1)
        {
             p_tv_delete_volumes_data((D_U32)hotplug_rset[i].hotplug_arg, (D_Bool)hotplug_rset[i].hotplug_plug);
             hotplug_rset[i].used = 0;
        }
    } 
    p_media_file_scan_task_destroy();
    p_tv_media_mman_close();
    return D_OK;
}

D_Result p_media_begin_deal(void)
{
    D_U8 i;
    for(i = 0;i < 24;i ++ )
    {
        if( hotplug_rset[i].hotplug_plug)
        {
             p_media_usb_plug_msg_process(hotplug_rset[i].hotplug_plug,hotplug_rset[i].hotplug_arg);
        }
    } 
    return D_OK;
}


/**@brief ��ȡUSB ����SD ɨ�������״̬
*@param[in] usb_sd ��������
*@return ����״̬:0 ��ʾ����δ��ʼ��1��ʾ��������У�2��ʾ�������
*/
D_U32 p_media_get_filescan_task_state(void)
{
    return tv_media_filescan_task.tv_file_scan_state;
}

