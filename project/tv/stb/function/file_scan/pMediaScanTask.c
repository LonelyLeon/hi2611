/** @file
* @brief 多媒体扫描任务模块
* @author
* @date 2018.01.08: 建立文件
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


#define D_MEDIA_PATH_LEN  D_PATH_LENGTH /**文件路径最大长度*/

#define D_MEDIA_READ_DISK_TASK_PRIO     (1)             /**任务优先级*/
#define D_MEDIA_READ_DISK_TASK_STACK_SIZE  (16*1024)    /**任务堆栈大小*/

#define  MEDIA_PARTITION_MAX_CNT (24)

/**@brief dmj 多媒体扫描任务相关属性结构体定义*/
typedef struct
{
    D_TaskAttr tv_file_scan_taskattr;     /**任务属性*/
    D_HTask    tv_file_scan_task_handle; /**扫描任务handle*/
    D_U32 tv_file_scan_state;                 /** 扫描任务状态*/
    D_U32 tv_file_scan_exit_flag;           /**扫描任务退出标记，用户置为1，扫描将会退出*/
} TV_MEDIA_FILE_SCAN_TASK_ATTR;

typedef struct
{
    D_Char device[4];  /**欲扫描的磁盘盘符*/
    D_U32 vol_index; /**磁盘盘符*/
    D_Int   mediaTotalPartition;                           /**总的磁盘数**/
    D_U8    mediaVolIndexs[MEDIA_PARTITION_MAX_CNT];  /* 总共的盘符数**/
} MEDIA_SCAN_TASK;

typedef struct
{
    D_U8 hotplug_plug;
    D_U8 hotplug_arg;   
    D_U8  used;
}HOTPLUG_RSET;

/**任务属性结构体数组变量*/
static TV_MEDIA_FILE_SCAN_TASK_ATTR tv_media_filescan_task = {{0},D_INVALID_HANDLE,0,0};
static HOTPLUG_RSET hotplug_rset[24] = {{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},
                                                                {0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},
                                                                {0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},      
                                                                {0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0},{0xff,0xff,0}};

static  MEDIA_SCAN_TASK MediaScan_task_info;

static D_HSem sem_media_task;

extern D_Result p_tv_file_scan_get_files_by_type_ex(D_Char *path, D_S32 type, D_U32 *stop_ctrl)D_FUNCPOSTFIT;

/**@brief 多媒体扫描任务销毁，
其实当任务完成后会自行销毁，此处只是复位相关参数
*@param[in] task_attr 任务属性
*/
D_Result p_media_file_scan_task_destroy(void)D_FUNCPOSTFIT
{
    if(tv_media_filescan_task.tv_file_scan_task_handle == D_INVALID_HANDLE)
    {
        return D_ERR;
    }               //等待任务结束计数变量
    tv_media_filescan_task.tv_file_scan_exit_flag = 1; //设置标记停止扫描
    while(tv_media_filescan_task.tv_file_scan_state != 2) // 等待扫描退出后再删除扫描任务
    {
        d_task_wait(500);
    }
    tv_media_filescan_task.tv_file_scan_task_handle = D_INVALID_HANDLE;
    tv_media_filescan_task.tv_file_scan_state = 0;
    d_sem_destroy (sem_media_task);
    return D_OK;
}

/**@brief 文件扫描任务
*@param[in] arg文件扫描任务属性
*/
void media_file_scan_task(D_Ptr arg)D_FUNCPOSTFIT
{
    while(1)
    {
        D_Char *device = (D_Char*)arg ;
        tv_media_filescan_task.tv_file_scan_exit_flag = 0; /**退出标记0，表示持续深度扫描*/
        tv_media_filescan_task.tv_file_scan_state = 1;  /**开始扫描时将扫描状态位置1*/
        p_tv_file_scan_get_files_by_type_ex(device, (D_S32)MediaScan_task_info.vol_index, &tv_media_filescan_task.tv_file_scan_exit_flag); /***开始扫描*/
        tv_media_filescan_task.tv_file_scan_state = 2; /**扫描完成后任务状态置为2*/
        d_sem_wait (sem_media_task);
    }
    //d_task_exit();  /**任务退出*/
}

/**@brief 创建文件扫描任务
*param[in] task_attr 任务属性
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


/**brief USB 热插拔处理
*@param[in] evt 热插拔事件
*/
D_Result p_media_usb_plug_msg_process(D_U8 plug,D_U8 arg)
{
    //D_Ptr  arg;
    if(plug) 
    {
        D_U32 type;

        type = d_fsm_get_volume_type((D_U8)arg); /**获取磁盘类型*/
        if(type == D_ERR)
        {
            return D_ERR;
        }
        if(hotplug_rset[arg].used == 0)
        {
        if(DEVICE_USB == type || DEVICE_USBX == type)
        {
            p_tv_media_mman_open();    /**创建扫描文件记录集的内存管理器*/
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
    else   // 设备拔出
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


/**@brief 获取USB 或者SD 扫描任务的状态
*@param[in] usb_sd 磁盘类型
*@return 任务状态:0 表示任务未开始；1表示任务进行中；2表示任务结束
*/
D_U32 p_media_get_filescan_task_state(void)
{
    return tv_media_filescan_task.tv_file_scan_state;
}

