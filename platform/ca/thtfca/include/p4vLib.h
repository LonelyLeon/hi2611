/******************************************************************************
 * p4vLib.h: ����LibP4V[�޿�]���ⲿ�ṩ�Ľӿ�
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

#ifndef P4V_LIB_H
#define P4V_LIB_H

#include "p4vLibConfigs.h"

#if defined __cplusplus || defined __cplusplus__
extern "C"
{
#endif

// ����CA����
ird_int32_t p4vInitialize(void);

// ֹͣCA����
ird_int32_t p4vShutdown(void);

// ��ȡ����汾
ird_int32_t p4vGetVersion(ird_uint8_t version[MAX_P4V_VERSION_LENGTH], ird_uint8_t * len);

// �����û�PIN
void p4vResetPINService(ird_uint8_t pinOldValue[PIN_LENGTH],
                        ird_uint8_t pinNewValue[PIN_LENGTH]);

// ʹ�û�ȡ��PIN
void p4vEnablePINService(ird_uint8_t pinValue[PIN_LENGTH],
                         ird_uint8_t enbaleOrNot);

// ���õ�ǰ�ĳ��˼���
void p4vResetCertificateService(ird_uint8_t pinValue[PIN_LENGTH],
                                ird_uint8_t newCertificate);
                    
// �տ����˼����Ŀ
void p4vCertificateConfirmService(ird_uint8_t pinValue[PIN_LENGTH]);

// ��ȡ�û�������Ϣ
void p4vRequestUserPrivacyService(void);

// ��ȡ��Ӫ����Ϣ
void p4vRequestOPListService(void);

// ��ȡ��Ȩ��Ϣ
void p4vRequestEntitlementListService(void);

// ��ȡECM PID
void p4vGetECMPID(ird_uint8_t * descriptors, ird_uint16_t length,
                  ird_uint16_t * pid);

// ��ȡEMM PID
void p4vGetEMMPIDList(ird_uint8_t * descriptors, ird_uint16_t length, emm_pid_list_t * pidList);

// ע��ECM����, ��Ϊע�Ὺʼ��ע��������ע��ȡ��
void p4vRegisterECMService(ird_uint16_t serviceID,
                           ird_uint8_t scrambleLevel,
                           ird_uint8_t processType);

// ��ECM��, ��Ϊ�󶨿�ʼ������������ȡ��
void p4vBindECMStream(ird_uint16_t serviceID, ird_uint16_t streamPID, ird_uint8_t streamType,
                      ird_uint16_t ecmPID,
                      ird_uint8_t processType);

// ��EMM��, ��Ϊ�󶨿�ʼ����ȡ��
void p4vBindEMMStream(ird_uint16_t emmPID, ird_uint8_t processType);

// �趨�����й���ʱ��
void p4vSetWorkingPeriodService(ird_uint8_t pinValue[PIN_LENGTH],
                                info_working_period_t newPeriod);

// ȡ������ʱ������
void p4vFreeWorkingPeriodService(ird_uint8_t pinValue[PIN_LENGTH]);

//��ȡ��ǰ�����õĹ���ʱ����Ϣ
void p4vGetWorkingPeriodInfoService(void);

//��ȡ���˼���������
void p4vGetCertificationLevelService(void);

// ��ȡPIN״̬
void p4vGetPinStateService(void);

//���������Զ�֪ͨ��Ϣ
void p4vSetOverdueInformInfoService(info_overdue_inform_t overdueInform);

//��ȡ�����Զ�֪ͨ������Ϣ
void p4vGetOverdueInformInfoService(void);

//��ȡ�û���Ȩ״̬��Ϣ
ird_int32_t p4vGetUserEntitlementState(ird_uint8_t currentDateTime[MJD_UTC_CODING_LENGTH]);

//��MJD���л����ȷ������
void p4vGetCalendarDateFromMJD(ird_uint8_t * mjd, ird_uint32_t * year, ird_uint32_t * month, ird_uint32_t * day);

#if defined __cplusplus || defined __cplusplus__
}
#endif

#endif  /* end_of_file */
