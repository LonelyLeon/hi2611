/******************************************************************************
 * p4vLibConfigs.h: 定义IRD与Lib[无卡]交互使用的数据结构和常量定义
 *-----------------------------------------------------------------------------
 *  北京同方凌讯科技有限公司
 *
 *  2009，版权所有，保留一切权利。
 *-----------------------------------------------------------------------------
 *
 * 修订历史
 *     赵  凡   2009/04/06      文档创建。
 *     谭运华   2009/05/07      修改info_user_entitlement_t结构定义，其中m_entitlements
                                的数组长度改为MAX_PRODUCT_RECORD_COUNT + MAX_PACKAGE_RECORD_COUNT
 *
 ******************************************************************************/

#ifndef P4V_LIB_CONFIGS_H
#define P4V_LIB_CONFIGS_H

#include "p4vLocalTypes.h"

#if defined __cplusplus || defined __cplusplus__
extern "C"
{
#endif

#define MAX_P4V_VERSION_LENGTH                      100

#define PIPE_SIZE                                    256
#define PIPE_CAPACITY                                8

//加扰类型
#define SCRAMBLE_LEVEL_TS                           1
#define SCRAMBLE_LEVEL_PES                          2


// PSI业务类型
#ifndef PSI_DEFINITION
#define PSI_DEFINITION

#define PSI_STREAM_TYPE_VIDEO                       0x01
#define PSI_STREAM_TYPE_AUDIO                       0x02
#define PSI_STREAM_TYPE_OTHER                       0x03

#define PSI_ECM_SERVICE_ATTACH                      0x11
#define PSI_ECM_SERVICE_DETACH                      0x12
#define PSI_ECM_SERVICE_UPDATE                      0x13

#define PSI_ECM_STREAM_ATTACH                       0x21
#define PSI_ECM_STREAM_DETACH                       0x22
#define PSI_ECM_STREAM_UPDATE                       0x23

#define PSI_EMM_STREAM_ATTACH                       0x31
#define PSI_EMM_STREAM_DETACH                       0x32
#define PSI_EMM_STREAM_UPDATE                       0x33

#define PSI_INVALID_PID                             0x1FFF

#endif  /* end_of_psi_definition */


///////////////////////////////////////////////////////////////////////////////
// libca boolean definition

#ifndef LIBP4V_BOOLEAN_DEFINITION
#define LIBP4V_BOOLEAN_DEFINITION

#define LIBP4V_BOOLEAN_TRUE                         1
#define LIBP4V_BOOLEAN_FALSE                        0

#endif  /* end_of_boolean_definition */

#define PIN_ENABLE                                  LIBP4V_BOOLEAN_TRUE
#define PIN_DISABLE                                 LIBP4V_BOOLEAN_FALSE


///////////////////////////////////////////////////////////////////////////////
// user certificate (film rating)

#define FILM_RATING_G                               0xC1        // 普通级
#define FILM_RATING_PG                              0xC2        // 13岁及以下禁止观看
#define FILM_RATING_PG13                            0xC3        // 13岁及以下家长陪同
#define FILM_RATING_R                               0xC4        // 15岁及以下禁止观看
#define FILM_RATING_NC17                            0xC5        // 18岁及以下禁止观看


///////////////////////////////////////////////////////////////////////////////
// NOTIFIER DEFINITION

// 文件稳定级别
#define FILE_OPERATE_STABLITY_LEVEL_LOW             0x01        // 一般级别
#define FILE_OPERATE_STABLITY_LEVEL_HIGH            0x02        // 高稳定级别
//文件安全性保护
#define NO_SECURITY                                 0x03        //不用安全保护
#define SECURITY                                    0x04        //安全保护


#define NOTIFIER_OPERATION_SUCCESS                  LIBP4V_BOOLEAN_TRUE
#define NOTIFIER_OPERATION_FAILURE                  LIBP4V_BOOLEAN_FALSE

#define NOTIFIER_ACT_USER_PRIVACY                   0xA0        // 反馈用户基本信息
#define NOTIFIER_ACT_OPS                            0xA1        // 获取运营商列表
#define NOTIFIER_ACT_ENTITLEMENT_LIST               0xA2        // 反馈用户授权列表
#define NOTIFIER_ACT_RECOVER_PIN                    0xA3        // PIN码已恢复为默认值000000
#define NOTIFIER_ACT_NEW_PIN_VALUE                  0xA4        // 反馈设置新的用户PIN
#define NOTIFIER_ACT_PIN_AVAILABILITY               0xA5        // 反馈设置PIN码的可用性
#define NOTIFIER_ACT_NEW_CERTIFICATE_VALUE          0xA6        // 反馈设置需要限制播出的节目成人级别
#define NOTIFIER_ACT_CERTIFICATE_CONFIRMING_RESULT  0xA7        // 节目级别高于设定观看级别
#define NOTIFIER_ACT_EMERGENCY_BROADCASTING         0xA8        // 执行应急广播
#define NOTIFIER_ACT_WORKING_PERIOD                 0xA9        // 反馈工作时段设置结果
#define NOTIFIER_ACT_ATTRIBUTE_BLOCKING             0xAA        // 用户遭到“自定义属性”屏蔽
#define NOTIFIER_ACT_OVERDUE_INFORM                 0xAB        // 反馈续费自动通知设置结果

#define NOTIFIER_ACT_FREE_WORKING_PERIOD            0xE1        // 反馈取消工作时段设置结果
#define NOTIFIER_ACT_GET_WORKING_PERIOD             0xE2        // 反馈获取工作时段的具体信息结果
#define NOTIFIER_ACT_GET_CERTIFICATE_LEVEL          0xE3        // 反馈成人级级别
#define NOTIFIER_ACT_GET_PIN_STATE                  0xE4        // 反馈PIN状态
#define NOTIFIER_ACT_DISPLAY_USER_NUMBER            0xE5        // 显示卡号
#define NOTIFIER_ACT_INACTIVE                       0xE6        // 系统尚未激活
#define NOTIFIER_ACT_ACTIVE_ERROR                   0xE7        // 激活错误
#define NOTIFIER_ACT_GET_OVERDUE_INFORM             0xE8        // 反馈获取续费自动通知具体信息结果

#define NOTIFIER_DAT_MAIL                           0xB0        // 数据内容为电子邮件
#define NOTIFIER_DAT_POPUP_MESSAGE                  0xB1        // 数据内容为屏显消息
#define NOTIFIER_DAT_FILM_RATING                    0xB2        // 数据内容为节目分级

#define NOTIFIER_POP_CLEAR_SCREEN                   0xD0        // 清屏。
#define NOTIFIER_POP_UNSUPPORTED_FRONTEND           0xD2        // 非本系统加密，无法收看。
#define NOTIFIER_POP_GCA_BLOCKED                    0xD3        // 区域阻塞，无法收看此节目。
#define NOTIFIER_POP_BLACKLISTED                    0xD4        // 您被列入了黑名单，无法收看此节目。
#define NOTIFIER_POP_USER_FROZEN                    0xD5        // 该用户被前端禁用
#define NOTIFIER_POP_USER_UNFROZEN                  0xD6        // 该用户被前端解冻
#define NOTIFIER_POP_NOT_IN_WORKING_PERIOD          0xD7        // 系统不在工作时段内
#define NOTIFIER_POP_NO_SUCH_ENTITLEMENT            0xD8        // 没有授权，无法收看此节目。

#define NOTIFIER_ACT_ACTIVE_EMERGENCY_BROADCASTING  0xD9        // 应急广播启动
#define NOTIFIER_POP_ENTITLEMENT_OVERDUE            0xDA        // 用户授权已过期

// 请注意  消息类型已添加到  0xE7
// 请注意  消息类型已添加到  0xE8
///////////////////////////////////////////////////////////////////////////////
// MAX/MIN VALUE DEFINITION

#define MAX_NAME_LENGTH                             20
#define MAX_TITLE_LENGTH                            100//20
#define MAX_CONTENT_LENGTH                          1000
#define MAX_FILE_NAME_LENGTH                        20
#define MAX_FILE_COUNT                              20
#define MAX_CONDITION_COUNT                         50

#define MSG_SHOW_FLAG                               0
#define MSG_BLOCK_FLAG                              1

#define MAX_EMM_PID_COUNT                           4
#define MAX_OP_COUNT                                4
#define MAX_OP_KEYSET_COUNT                         2
#define MAX_KEYSET_COUNT                            8
//#define MAX_PRODUCT_RECORD_COUNT                    100
#define MAX_PRODUCT_RECORD_COUNT                    500
#define MAX_PACKAGE_RECORD_COUNT                    10

#define UTC_CODING_LENGTH                           3
#define MJD_UTC_CODING_LENGTH                       5
#define SN_LENGTH                                   16
#define PIN_LENGTH                                  6

///////////////////////////////////////////////////////////////////////////////
// ERROR

#define ERROR_PIN_0                                 2           // PIN错误，PIN已经锁定
#define ERROR_PIN_1                                 3           // PIN错误，剩余1次机会PIN将会被锁定
#define ERROR_PIN_2                                 4           // PIN错误，剩余2次机会PIN将会被锁定
#define ERROR_PIN_3                                 5           // PIN错误，剩余3次机会PIN将会被锁定
// zhaofan add
#define ERROR_INPUT_TIME                            6           // 时间数据错误
#define ERROR_INPUT_TIME_SAME                       7           // 时间数据错误，开始时间不能与结束时间相同

#define ERROR_NO_PROCESS                            8           // 没有操作
#define ERROR_UNKNOW                                9           // 操作失败

//////////////////////////////////////////////////////////////////////////////
#define MAIL_TYPE_IMPORTANT                         1
#define MAIL_TYPE_COMMON                            2

//故障信息
#define ALLOCATE_MEMORY_FAILED                      -101
#define GET_FILE_FAILED                             -102

// 状态信息
#define NO_ENTITY                                   101
#define ENTITY_OVERDUE                              102
#define ENTITY_AVAILABLE                            103


struct info_mail
{
    ird_uint8_t     m_deliveryTime[MJD_UTC_CODING_LENGTH];
    ird_uint8_t     m_titleLength;
    ird_uint8_t     m_title[MAX_TITLE_LENGTH];
    ird_uint16_t    m_contentLength;
    ird_uint8_t     m_content[MAX_CONTENT_LENGTH];
    ird_uint8_t     m_important_type;
};
typedef struct info_mail    info_mail_t;

// zhaofan add 2009-07-06
struct limit_list
{
    ird_uint8_t     m_flag;                                     // 0：显示；1：屏蔽
    ird_uint16_t    m_count;                                    // 条件个数
    ird_uint16_t    m_condition_list[MAX_CONDITION_COUNT];      // 条件列表
};
typedef struct limit_list limit_list_t;

// zhaofan modify 2009-07-06
struct info_popup_message
{
    ird_uint8_t     m_titleLength;
    ird_uint8_t     m_title[MAX_TITLE_LENGTH];
    ird_uint16_t    m_contentLength;
    ird_uint8_t     m_content[MAX_CONTENT_LENGTH];
    limit_list_t    m_condition;
    ird_uint8_t     m_display_type;
    ird_uint8_t     m_display_time;
};
typedef struct info_popup_message   info_popup_message_t;

struct info_program_certificate
{
    ird_uint16_t    m_serviceID;
    ird_uint8_t     m_programCertificate;                       // 当前播出节目的级别
    ird_uint8_t     m_systemApprovalCertificate;                // 当前系统许可的级别
};
typedef struct info_program_certificate     info_program_certificate_t;

// 用户查看智能卡基本信息使用的数据结构
struct info_user_privacy
{
    ird_uint8_t     m_version;                                  // 系统版本(CA系统版本)
    ird_uint8_t     m_serialNumber[SN_LENGTH];                  // 智能卡卡号
    ird_uint8_t     m_algorithmFamily;                          // 智能卡所支持的算法版本群
    ird_uint32_t    m_superCASID;                               // 当前CA系统号
    ird_uint8_t     m_pinAvailabilityFlag;                      // 密码控制标志
    ird_uint8_t     m_defaultPINFlag;                           // 默认PIN码标识位:1为默认PIN（默认值），0为（自定义）
    ird_uint8_t     m_systemApprovalCertificate;                // 系统许可成人级别
    ird_uint8_t     m_userState;                                // 用户状态（1禁用）（0启用）
    ird_uint8_t     m_gcaNameLength;
    ird_uint8_t     m_gcaName[MAX_NAME_LENGTH];
    ird_uint8_t     m_casProviderNameLength;
    ird_uint8_t     m_casProviderName[MAX_NAME_LENGTH];
};
typedef struct info_user_privacy    info_user_privacy_t;

// 用户查看运营商信息的数据结构
struct info_keyset
{
    ird_uint8_t     m_count;
    ird_uint16_t    m_ids[MAX_OP_KEYSET_COUNT];
};
typedef struct info_keyset  info_keyset_t;

struct info_op
{
    ird_uint8_t     m_serialNumber[SN_LENGTH];                  // 用户ID
    ird_uint32_t    m_subCASID;                                 // 当前CA子系统号
    ird_uint8_t     m_networkOperatorNameLength;
    ird_uint8_t     m_networkOperatorName[MAX_NAME_LENGTH];
    info_keyset_t   m_keyset;                                   // [MAX_OP_KEYSET_COUNT]
};
typedef struct info_op info_op_t;

struct info_op_list
{
    ird_uint8_t     m_count;
    info_op_t       m_ops[MAX_OP_COUNT];
};
typedef struct info_op_list info_op_list_t;


// 用户查看授权使用的数据结构
struct info_product
{
    ird_uint16_t    m_id;
    ird_uint8_t     m_type;
    ird_uint8_t     m_nameLength;
    ird_uint8_t     m_name[MAX_NAME_LENGTH];
    ird_uint8_t     m_expired[MJD_UTC_CODING_LENGTH];           // 产品失效日期，MJD_UTC
};
typedef struct info_product info_product_t;

struct info_user_entitlement
{
    ird_uint16_t     m_count;
    info_product_t  m_entitlements[MAX_PRODUCT_RECORD_COUNT + MAX_PACKAGE_RECORD_COUNT];
};
typedef struct info_user_entitlement    info_user_entitlement_t;


// 机顶盒工作时段信息结构
struct info_working_period
{
    ird_uint8_t     m_state;                                    //工作时段是否可用，1为可用，0为不可用
    ird_uint8_t     m_dailyBeginAt[UTC_CODING_LENGTH];
    ird_uint8_t     m_dailyEndAt[UTC_CODING_LENGTH];
};
typedef struct info_working_period info_working_period_t;

// 应急广播描述符
struct desc_ca_linkage
{
    ird_uint8_t     m_tag;
    ird_uint8_t     m_length;
    ird_uint16_t    m_transportStreamID;
    ird_uint16_t    m_originalNetworkID;
    ird_uint16_t    m_serviceID;
    ird_uint8_t     m_linkageType;

    ird_uint16_t    m_videoPID;
    ird_uint16_t    m_audioPID;
    ird_uint16_t    m_otherPID;
    ird_uint16_t    m_videoECMPID;
    ird_uint16_t    m_audioECMPID;
    ird_uint16_t    m_otherECMPID;
    ird_uint16_t    m_networkID;
    ird_uint16_t    m_symbolRate;
    ird_uint16_t    m_frequency;
};
typedef struct desc_ca_linkage  desc_ca_linkage_t;

struct info_emergency_broadcasting
{
    desc_ca_linkage_t   m_caLinkageDesc;                        // 跳转描述符
    ird_uint8_t         m_expiredTime[MJD_UTC_CODING_LENGTH];   // 广播截止时间 MJD + UTC
};
typedef struct info_emergency_broadcasting info_emergency_broadcasting_t;

struct info_operation_result
{
    ird_uint8_t     m_operation;                                // 操作代码
    ird_uint8_t     m_result;                                   // 操作结果
    ird_uint32_t    m_value;                                    // 操作附加返回值
};
typedef struct info_operation_result    info_operation_result_t;

struct emm_pid_list
{
    ird_uint8_t     m_count;                                    // EMM PID 数量
    ird_uint16_t    m_pid[MAX_EMM_PID_COUNT];                   // EMM PID 列表
};
typedef struct emm_pid_list     emm_pid_list_t;

// 续费自动通知数据结构
struct info_overdue_inform
{
    ird_uint8_t     m_state;                                    //续费通知是否可用，1为可用，0为不可用
    ird_uint8_t     m_aheadDays;                                     //续费通知提前天数，为5到15之间。
};
typedef struct info_overdue_inform info_overdue_inform_t;

#if defined __cplusplus || defined __cplusplus__
}
#endif

#endif  /* end_of_file */
