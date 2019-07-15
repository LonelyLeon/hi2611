#ifndef __HCD_H
#define __HCD_H

#include "dTypes.h"
#include "dDisk.h"
#include "element.h"

#ifdef  __cplusplus
extern "C"
{
#endif

typedef struct
{
    D_ID id;
}D_UsbHcdAttr;

#define D_USBHCD_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

typedef enum
{
    D_UsbDeviceType_MassStorage = 0,
    D_UsbDeviceType_Mouse,
    D_UsbDeviceType_Wireless,
    D_UsbDeviceType_Ether,
    D_UsbDeviceType_SerialConverter,
    D_UsbDeviceType_HostDrv,
}D_UsbDevieType;

typedef struct
{
    D_UsbDevieType type;
    D_Ptr dev_ctx;
    union
    {
        D_DiskCapInfo disk;
    };
}D_UsbDeviceInfo;

typedef struct
{
    D_UsbDevieType type;
    D_Ptr dev_ctx;
}D_HostDeviceInfo;

D_Result d_usb_hcd_open(void) D_FUNCPOSTFIT;
D_Result d_usb_hcd_close(void) D_FUNCPOSTFIT;
D_Handle d_usb_hcd_create(D_UsbHcdAttr *attr) D_FUNCPOSTFIT;
D_Result d_usb_hcd_destroy(D_Handle hcd) D_FUNCPOSTFIT;

/* 以下是设备类驱动初始化 */
D_Result usb_stor_drv_init(void) D_FUNCPOSTFIT;  /* U盘驱动 */
D_Result usb_stor_drv_release(void) D_FUNCPOSTFIT;
D_Result rndis_host_drv_init(void) D_FUNCPOSTFIT; /* rndis_host USB网卡驱动 */
D_Result ftdi_drv_init(void) D_FUNCPOSTFIT;  /* FT232系列USB串口驱动 */
D_Result ftdi_drv_release(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

