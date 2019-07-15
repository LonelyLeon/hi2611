#ifndef _UTI_DRIVER_SYSTEM_API_H_
#define _UTI_DRIVER_SYSTEM_API_H_

#include "unitend.h"
#include "uti_udrm_type.h"
//#include "UTIType.h"

typedef UTI_SINT32 (*DRM_DEMUX_CALLBACK)(UTI_UINT16 tsInputId, UTI_UINT16 pid, UTI_UINT8 *section);

// driver needed api
extern UTI_SINT32 UTIAppSendDataToDriver(UTI_UINT8 *data, UTI_UINT32 len);

// add for udrm driver
extern UTI_SINT32 UDRMDeviceInit(void);

/*------start flash API-------------------------------*/
extern UTI_SINT32 UDRMFlashRead(UTI_UINT32 offset, UTI_UINT8 *mem, UTI_UINT32 len);
extern UTI_SINT32 UDRMFlashWrite (UTI_UINT32 offset, const UTI_UINT8 *mem, UTI_UINT32 len);
/*------end flash API--------------------------------*/

/*------start demux API-------------------------------*/
extern UTI_SINT32 UDRMDemuxStartSectionFilter(UTI_UINT16 tunerID, UTI_UINT16 pid, const UTI_UINT8 *data, const UTI_UINT8 *mask, DRM_DEMUX_CALLBACK callbackFun);
extern UTI_SINT32 UDRMDemuxStopSectionFilter(UTI_UINT16 tunerID, UTI_UINT16 pid);
/*------end demux API--------------------------------*/

// user define
extern UTI_SINT32 UDRMNotify(UDRM_NOTIFY udrmNotifyStruct);
/*------start tuner API---------------------*/
extern UTI_SINT32 UDRMTunerGetLockStatus(UTI_UINT8 *lockStatus);
/*------end tuner API---------------------*/


extern UTI_SINT32 DemuxRead(UTI_UINT8 *data, UTI_UINT32 *len);

// descrambler
extern UTI_SINT32 UDRMDescramblerOpen(UTI_UINT32 *id);
extern UTI_SINT32 UDRMDescramblerClose(UTI_UINT32 id);
extern UTI_SINT32 UDRMDescramblerSetStreamPid(UTI_UINT32 id, UTI_UINT32 pidListLen, UTI_UINT16 *pidList);
extern UTI_SINT32 UDRMDescramblerSetCW(UTI_UINT32 id, UTI_UINT8 *evenCW, UTI_UINT8 *oddCW);


// user define
extern UTI_SINT32 UDRMNotify(UDRM_NOTIFY udrmNotifyStruct);

//CA移植库通过此接口实现移植库和SCPU里cos库之间的交互，海尔负责将Cmd传递给SCPU,并将SCPU端无卡COSLIB反馈的信息及状态通过pbRxData给CA移植库
extern UTI_SINT32 UTIDRV_SCARD_AdpuCommand(UTI_UINT16 CmdL,UTI_UINT8 *cmd,UTI_SINT32 RespL,UTI_UINT8 *pbRxData, UTI_SINT32 *Resp);
//mode 解密算法0:3des 1:aes ,key:被rootkey 加密的SGK ,为16字节
extern UTI_SINT32 UDRMSGKSet (UTI_UINT32 mode, UTI_UINT8 *key);

//mode 解密算法0:3des 1:aes ,key:被SGK 加密的PK,为16字节
extern UTI_SINT32 UDRMPKSet (UTI_UINT32 mode, UTI_UINT8 *key);

//mode 解密算法0:3des 1:aes ,cw是被PK 加密的控制字,为16字节,前8个字节偶cw,后8字节为奇cw
extern UTI_SINT32 UDRMCWSet (UTI_UINT32 mode, UTI_UINT8 *cw);
#endif
