#include "pUSBUpGrade.h"
#include "dNVPart.h"
#include "dMem.h"
#include "pConfig.h"
#include "dDBaseInternal.h"
#include "dApp.h"
#include "dMMan.h"
#include "dMem.h"
#include "pCustomConfig.h"

#define D_USB_UPGRADE_BUF_SIZE          (USB_FILE_BUFFER_SIZE+0x100)
#define SEND_MSG(_a,_b,_c)                    d_queue_try_send(_a,(D_U8*)(_b),_c)   /** 从一个消息队列中接收数据*/
#define TV_USB_FILE_NAME                "c:/tvusbupgrade.bin"

/** @brief 手动搜索内部数据*/
typedef struct
{
    D_HQueue        ms_hq;
    D_HQueue        hqueue;
    D_U8            *ms_buf;
    D_U8            process_busy;
    D_U8            upgrade;
} D_MSData;

static D_MSData tv_dmsdata;
static D_Usb_Upgrade_Data config;
static D_LoaderParam loaderparam;

/*将消息发送到gui，可用于显示*/
static D_Result ms_backcall(D_U8 event, D_U8 param)
{
    D_UserMsg smsg;
    if(event == 1)
    {
        smsg.type = D_MSG_USER;
        smsg.handle = d_app_self();
        smsg.param1 = D_MSG_USBUPGRADE_PROGRESS;
        smsg.param2 = param;
        SEND_MSG (tv_dmsdata.ms_hq, (D_U8*)&smsg, sizeof (smsg));
    }
    return D_OK;
}
/*将消息发送到gui，可用于显示*/
static D_Result ms_send_usb_end_msg(void)
{
    D_UserMsg smsg;

    smsg.type = D_MSG_USER;
    smsg.handle = d_app_self();
    smsg.param1 = D_MSG_USBUPGRADE_OK;
    SEND_MSG (tv_dmsdata.ms_hq, (D_U8*)&smsg, sizeof (smsg));

    return D_OK;
}
/*将消息发送到gui，可用于显示*/
static D_Result ms_send_usb_fail_msg(void)
{
    D_UserMsg smsg;

    smsg.type = D_MSG_USER;
    smsg.handle = d_app_self();
    smsg.param1 = D_MSG_USBUPGRADE_FAILED;
    SEND_MSG (tv_dmsdata.ms_hq, (D_U8*)&smsg, sizeof (smsg));

    return D_OK;
}
/*将消息发送到gui，可用于显示*/
static D_Size usb_upgrade_erase_flash_back(D_Handle handle, D_Size offset, D_Size size)
{
    D_Size ret;

    ret = d_nvpart_erase_flash(D_DB_NVRAM_ID, offset, size);

    handle = handle;

    return ret;
}
/*将消息发送到gui，可用于显示*/
static D_Size usb_upgrade_write_flash_back(D_Handle handle, D_Size offset, D_U8 *buff, D_Size size)
{
    D_Size ret;

    ret = d_nvpart_write_flash(D_DB_NVRAM_ID, offset, buff, size);

    handle = handle;
    return ret;
}

/** @brief usb升级消息回调函数
* @param[in] msg 消息
* @return 成功返回D_OK,失败返回D_ERR
*/
static D_Result usb_callback (D_Msg *msg)D_FUNCPOSTFIT
{
    D_UsbResultCode res;
    D_U32 sw_code;

    switch (msg->type)
    {
        case D_MSG_APP_CREATE:
            d_app_set_timeout(d_app_self (), 5);
            break;
        case D_MSG_APP_TIMEOUT:
            if(tv_dmsdata.upgrade == 0)
            {
                tv_dmsdata.upgrade = 1;
                tv_dmsdata.hqueue = d_app_get_queue (d_app_self ());
                config.mode = D_USB_VHW_UPDATE;
                res = start_usb_upgrade(config, &sw_code);
                if(res != USB_NO_ERROR)
                {
                    //升级失败，发送失败消息
                    ms_send_usb_fail_msg();
                    tv_dmsdata.process_busy =   0;
                }
                else
                {
                    if(sw_code != 0xffff8893)//0xffff8893为预留版本号，此时不更新软件版本号
                    {
                        //升级成功，需要更新版本号，发送升级成功消息
                        loaderparam.stb_param_copy.sw_major  = sw_code >> 24;
                        loaderparam.stb_param_copy.sw_minor = sw_code >> 16;
                        loaderparam.stb_param_copy.sw_build_num = sw_code;
                        p_conf_set_loader_param(&loaderparam);
                    }
                    ms_send_usb_end_msg();
                    tv_dmsdata.process_busy =   0;
                }
            }
            break;
        default:
            break;
    }

    return D_OK;
}

/** @brief 开始手动搜索,数据初始化*/
static D_Result ms_start (D_HQueue ms_hq, const char *full_path)
{
    D_U8            *buf;

    if(CUSTOM_CONFIG.sys.manu_id == (D_ManufactoryID) - 1)
        return D_ERR;

    buf = (D_U8*) d_mem_alloc (0, D_USB_UPGRADE_BUF_SIZE);

    if (!buf)
    {
        D_ERROR ("[tv_usb_upgrade] Cannot allocate memory\n");
        return D_ERR;
    }

    tv_dmsdata.ms_buf = buf;
    tv_dmsdata.ms_hq = ms_hq;
    if(p_conf_get_loader_param ((D_LoaderParam*)&loaderparam) != D_OK)  //读取loader参数失败
    {
        d_mem_free (buf);
        D_ERROR ("[tv_usb_upgrade] Cannot create memory manager\n");
        return D_ERR;
    }
    config.pbuff = tv_dmsdata.ms_buf;
    config.full_path = full_path;
    config.order = 0;
    config.hw_code = ((D_U32)CUSTOM_CONFIG.sys.hw_id << 24) \
                     | ((D_U32)CUSTOM_CONFIG.sys.hw_major << 16) \
                     | CUSTOM_CONFIG.sys.hw_minor;

    config.sw_code =  ((D_U32)loaderparam.stb_param_copy.sw_major << 24) \
                      | ((D_U32)loaderparam.stb_param_copy.sw_minor << 16) \
                      | loaderparam.stb_param_copy.sw_build_num;

    config.manu_id = (CUSTOM_CONFIG.sys.manu_id & 0xFFFF);

    config.flashhandle = 0; //flash模块
    config.flasherasefunc = usb_upgrade_erase_flash_back;
    config.flashwritefunc = usb_upgrade_write_flash_back;

    D_UsbSetEventCB((USBUPGRADEEVENTCALLBACK)ms_backcall);

    return D_OK;

}

/** @brief创建usb升级任务
* @param [in] ms_hq 上层消息
* @param[in]  full_path 升级文件全路径
* @param[in]  priority  任务优先级
* @return 成功返回搜索句柄, 失败返回D_INVALID_HANDLE
*/
D_Handle d_usb_upgrade_create(D_HQueue ms_hq, const char *full_path, D_S8 priority)D_FUNCPOSTFIT
{
    D_HApp      happ;

    D_INFO("[tv_usb_upgrade] create\n");
    if(full_path == NULL)
        full_path = TV_USB_FILE_NAME;
    if ((!full_path ) || (D_INVALID_HANDLE == ms_hq) || (tv_dmsdata.process_busy))
    {
        D_ERROR ("[tv_usb_upgrade] param error\n");
        return D_INVALID_HANDLE;
    }
    if(ms_start(ms_hq, full_path) == D_ERR)
    {
        D_ERROR ("[tv_usb_upgrade] ms_start error\n");
        return D_INVALID_HANDLE;
    }
    tv_dmsdata.upgrade = 0;
    happ = d_app_create ("tv_usb_upgrade", priority, D_USB_UPGRADE_TASK_STACK_SIZE, D_USBUPGRADE_QUEUE_SIZE, usb_callback, (D_Ptr)&tv_dmsdata);

    if (D_INVALID_HANDLE == happ)
    {
        D_ERROR ("Cannot create tv_usb_upgrade app\n");
        d_mem_free (tv_dmsdata.ms_buf);
        return happ;
    }
    tv_dmsdata.process_busy =   1;
    return happ;
}

/** @brief  结束USB升级
* @param[in] handle句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_usb_upgrade_destroy (D_Handle handle)D_FUNCPOSTFIT
{
    if (tv_dmsdata.ms_buf)
    {
        d_mem_free (tv_dmsdata.ms_buf);
    }
    d_app_destroy (handle);
    D_INFO("[tv_usb_upgrade] destroy\n");
    return D_OK;
}

