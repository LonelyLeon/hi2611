/******************************************************************************
 * p4vInterfaces.h: ����IRD��ҪΪlibP4V[�޿�]ʵ�ֵ�ƽ̨�����ӿ�
 *-----------------------------------------------------------------------------
 *  ����ͬ����Ѷ�Ƽ����޹�˾
 *
 *  2009����Ȩ���У�����һ��Ȩ����
 *-----------------------------------------------------------------------------
 *
 * �޶���ʷ
 *     ��  ��   2009/04/06      �ĵ�������
 *
 ******************************************************************************/

#ifndef P4V_INTERFACES_H
#define P4V_INTERFACES_H

#include "p4vLibConfigs.h"

#if defined __cplusplus || defined __cplusplus__
extern "C"
{
#endif

int    irdDebugPrint(const char * format, ...);
void * irdAllocateBuffer(ird_int32_t size);
void   irdDeallocateBuffer(void * ptr);
void * irdCopyMemory(void * to, const void * from, ird_int32_t size);
void * irdClearMemory(void * block, ird_int32_t size);
void * irdFillMemory(void * block, ird_uint8_t c, ird_int32_t size);
ird_int32_t irdCompareMemory(void * lft, void * rht, ird_int32_t size);

typedef void(* task_service_t)(void *);

ird_int32_t irdCreateTask(ird_uint32_t * taskID,
                          task_service_t clbkTaskProcessor);
// �ر�˵���������߳�ʱ���������ȼ��Ͷ�ջ�ռ䣬������������Ϊ��ֲǿ��ָ�굥�����ĵ���˵����
ird_int32_t irdSuspendTask(ird_uint32_t taskID, ird_uint32_t time);
ird_int32_t irdTerminateTask(ird_uint32_t taskID);
ird_int32_t irdSuspendSelf(ird_uint32_t time);


ird_int32_t irdCreateSemaphore(ird_uint32_t * semID, ird_uint32_t count);
ird_int32_t irdWaitForSemaphore(ird_uint32_t semID);
ird_int32_t irdTryWaitSemaphore(ird_uint32_t semID);
ird_int32_t irdReleaseSemaphore(ird_uint32_t semID);


ird_int32_t irdCreateMutex(ird_uint32_t * muxID);
ird_int32_t irdLockMutex(ird_uint32_t muxID);
ird_int32_t irdUnlockMutex(ird_uint32_t muxID);


ird_int32_t irdCreateMessagePipe(ird_uint32_t * pipeID,
                                 ird_uint32_t   maxCapacity,
                                 ird_uint32_t   maxMsgSize);
ird_int32_t irdDeleteMessagePipe(ird_uint32_t pipeID);
ird_int32_t irdPushMessageIntoPipe(ird_uint32_t  pipeID,
                                   ird_uint8_t * msgData,
                                   ird_uint32_t  msgSize);
ird_int32_t irdPullMessageFromPipe(ird_uint32_t  pipeID,
                                   ird_uint8_t * msgData,
                                   ird_uint32_t * msgSize);
ird_int32_t irdClearPipe(ird_uint32_t pipeID);


typedef void(* demux_service_t)(ird_uint16_t ,   \
                                ird_uint8_t *,   \
                                ird_uint32_t,    \
                                ird_uint8_t);

ird_int32_t irdMaxFilterLengthPerDemuxChannel(ird_uint32_t * maxFilterLength);
ird_int32_t irdMaxFilterCountPerDemuxChannel(ird_uint32_t * maxFilterCount);
ird_int32_t irdRequestDemuxChannel(ird_uint32_t * channelID,
                                   ird_uint32_t maxSectionBufferSize);
ird_int32_t irdReleaseDemuxChannel(ird_uint32_t channelID);
ird_int32_t irdRequestDemuxChannelFilter(ird_uint32_t   channelID,
                                         ird_uint32_t * filterID);
ird_int32_t irdReleaseDemuxChannelFilter(ird_uint32_t   channelID,
                                         ird_uint32_t   filterID);
ird_int32_t irdSetDemuxChannelFilter(ird_uint32_t   channelID,
                                     ird_uint32_t   filterID,
                                     ird_uint8_t  * filterByte,
                                     ird_uint8_t  * maskByte,
                                     ird_uint32_t   filterLength);
ird_int32_t irdSetDemuxChannelPID(ird_uint32_t  channelID,
                                  ird_uint16_t  streamPID);
ird_int32_t irdSetDemuxChannelService(ird_uint32_t  channelID,
                                      demux_service_t clbkDemuxProcessor);
ird_int32_t irdEnableDemuxChannel(ird_uint32_t channelID);
ird_int32_t irdDisableDemuxChannel(ird_uint32_t channelID);

ird_int32_t irdOpenDescrambler();
ird_int32_t irdCloseDescrambler();
ird_int32_t irdMaxDescramblerChannelCount(ird_uint8_t * count);
ird_int32_t irdRequestDescramblerChannel(ird_uint32_t * channelID);
ird_int32_t irdReleaseDescramblerChannel(ird_uint32_t channelID);
ird_int32_t irdSetDescramblerChannelPID(ird_uint32_t channelID,
                                        ird_uint16_t streamPID,
                                        ird_uint8_t  scrambleLevel);
ird_int32_t irdSetDescramblerChannelCW(ird_uint32_t  channelID,
                                       ird_uint8_t   CWFlag,
                                       ird_uint8_t   oddCW[8],
                                       ird_uint8_t   evenCW[8],
                                       ird_uint8_t scrambleLevel);

ird_int32_t irdOpenFlash();
ird_int32_t irdCloseFlash();
ird_int32_t irdIsFlashOpen();
ird_int32_t irdReadFlash(ird_uint8_t * pd, ird_uint32_t size);
ird_int32_t irdWriteFlash(ird_uint8_t * pd, ird_uint32_t size);

// eeprom��д�ӿڣ�����ձ�׼Cʵ��
// �޸��� irdFileOpen ������������� level ��������ʾ�ļ���������������Ҫ���ȶ��Լ���
// �ȶ��Լ����壺Ŀǰ��Ϊ�������ֱ��Ǹ��ȶ������һ�㼶�𣬾���Ĳ���ֵ������˵��
// #define FILE_OPERATE_STABLITY_LEVEL_LOW             0x01        // һ�㼶��
// #define FILE_OPERATE_STABLITY_LEVEL_HIGH            0x02        // ���ȶ�����
ird_FILE_t * irdFileOpen(const ird_uint8_t * name, const ird_uint8_t * mode, const ird_uint8_t level);
ird_int32_t irdFileClose(ird_FILE_t * stream);
ird_int32_t irdFileRead(void * pd, ird_uint32_t size, ird_uint32_t count,
                   ird_FILE_t * stream);
ird_int32_t irdFileWrite(const void * pd, ird_uint32_t size, ird_uint32_t count,
                    ird_FILE_t * stream);

// OSD Notifier
ird_int32_t irdOSDNotifier(ird_uint8_t msgType,
                           ird_uint16_t msgLength,
                           ird_uint8_t * msgData,
                           ird_uint8_t operationResult);

// ��ȡHID
ird_int32_t irdGetHID(ird_uint8_t * length, ird_uint8_t ID[16]);
ird_int32_t irdGetUserID(ird_uint8_t * length, ird_uint8_t ID[16]);

// ��ȡ�ʼ���Ϣ
ird_int32_t irdGetMailBoxInformation(ird_uint32_t * flag, ird_uint32_t * maxcount);

#if defined __cplusplus || defined __cplusplus__
}
#endif

#endif  /* end_of_file */
