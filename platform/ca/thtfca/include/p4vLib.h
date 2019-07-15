/******************************************************************************
 * p4vLib.h: 定义LibP4V[无卡]对外部提供的接口
 *-----------------------------------------------------------------------------
 *  北京同方凌讯科技有限公司
 *
 *  2009，版权所有，保留一切权利。
 *-----------------------------------------------------------------------------
 *
 * 修订历史
 *     赵  凡   2009/04/06      文档创建。
 *
 ******************************************************************************/

#ifndef P4V_LIB_H
#define P4V_LIB_H

#include "p4vLibConfigs.h"

#if defined __cplusplus || defined __cplusplus__
extern "C"
{
#endif

// 启动CA服务
ird_int32_t p4vInitialize(void);

// 停止CA服务
ird_int32_t p4vShutdown(void);

// 获取软件版本
ird_int32_t p4vGetVersion(ird_uint8_t version[MAX_P4V_VERSION_LENGTH], ird_uint8_t * len);

// 设置用户PIN
void p4vResetPINService(ird_uint8_t pinOldValue[PIN_LENGTH],
                        ird_uint8_t pinNewValue[PIN_LENGTH]);

// 使用或取消PIN
void p4vEnablePINService(ird_uint8_t pinValue[PIN_LENGTH],
                         ird_uint8_t enbaleOrNot);

// 设置当前的成人级别
void p4vResetCertificateService(ird_uint8_t pinValue[PIN_LENGTH],
                                ird_uint8_t newCertificate);
                    
// 收看成人级别节目
void p4vCertificateConfirmService(ird_uint8_t pinValue[PIN_LENGTH]);

// 获取用户基本信息
void p4vRequestUserPrivacyService(void);

// 获取运营商信息
void p4vRequestOPListService(void);

// 获取授权信息
void p4vRequestEntitlementListService(void);

// 获取ECM PID
void p4vGetECMPID(ird_uint8_t * descriptors, ird_uint16_t length,
                  ird_uint16_t * pid);

// 获取EMM PID
void p4vGetEMMPIDList(ird_uint8_t * descriptors, ird_uint16_t length, emm_pid_list_t * pidList);

// 注册ECM服务, 分为注册开始，注册升级，注册取消
void p4vRegisterECMService(ird_uint16_t serviceID,
                           ird_uint8_t scrambleLevel,
                           ird_uint8_t processType);

// 绑定ECM流, 分为绑定开始，绑定升级，绑定取消
void p4vBindECMStream(ird_uint16_t serviceID, ird_uint16_t streamPID, ird_uint8_t streamType,
                      ird_uint16_t ecmPID,
                      ird_uint8_t processType);

// 绑定EMM流, 分为绑定开始，绑定取消
void p4vBindEMMStream(ird_uint16_t emmPID, ird_uint8_t processType);

// 设定机顶盒工作时段
void p4vSetWorkingPeriodService(ird_uint8_t pinValue[PIN_LENGTH],
                                info_working_period_t newPeriod);

// 取消工作时段设置
void p4vFreeWorkingPeriodService(ird_uint8_t pinValue[PIN_LENGTH]);

//获取当前所设置的工作时段信息
void p4vGetWorkingPeriodInfoService(void);

//获取成人级级别设置
void p4vGetCertificationLevelService(void);

// 获取PIN状态
void p4vGetPinStateService(void);

//设置续费自动通知信息
void p4vSetOverdueInformInfoService(info_overdue_inform_t overdueInform);

//获取续费自动通知具体信息
void p4vGetOverdueInformInfoService(void);

//获取用户授权状态信息
ird_int32_t p4vGetUserEntitlementState(ird_uint8_t currentDateTime[MJD_UTC_CODING_LENGTH]);

//从MJD码中获得正确的日期
void p4vGetCalendarDateFromMJD(ird_uint8_t * mjd, ird_uint32_t * year, ird_uint32_t * month, ird_uint32_t * day);

#if defined __cplusplus || defined __cplusplus__
}
#endif

#endif  /* end_of_file */
