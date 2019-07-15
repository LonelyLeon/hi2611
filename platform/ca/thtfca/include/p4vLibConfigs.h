/******************************************************************************
 * p4vLibConfigs.h: ����IRD��Lib[�޿�]����ʹ�õ����ݽṹ�ͳ�������
 *-----------------------------------------------------------------------------
 *  ����ͬ����Ѷ�Ƽ����޹�˾
 *
 *  2009����Ȩ���У�����һ��Ȩ����
 *-----------------------------------------------------------------------------
 *
 * �޶���ʷ
 *     ��  ��   2009/04/06      �ĵ�������
 *     ̷�˻�   2009/05/07      �޸�info_user_entitlement_t�ṹ���壬����m_entitlements
                                �����鳤�ȸ�ΪMAX_PRODUCT_RECORD_COUNT + MAX_PACKAGE_RECORD_COUNT
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

//��������
#define SCRAMBLE_LEVEL_TS                           1
#define SCRAMBLE_LEVEL_PES                          2


// PSIҵ������
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

#define FILM_RATING_G                               0xC1        // ��ͨ��
#define FILM_RATING_PG                              0xC2        // 13�꼰���½�ֹ�ۿ�
#define FILM_RATING_PG13                            0xC3        // 13�꼰���¼ҳ���ͬ
#define FILM_RATING_R                               0xC4        // 15�꼰���½�ֹ�ۿ�
#define FILM_RATING_NC17                            0xC5        // 18�꼰���½�ֹ�ۿ�


///////////////////////////////////////////////////////////////////////////////
// NOTIFIER DEFINITION

// �ļ��ȶ�����
#define FILE_OPERATE_STABLITY_LEVEL_LOW             0x01        // һ�㼶��
#define FILE_OPERATE_STABLITY_LEVEL_HIGH            0x02        // ���ȶ�����
//�ļ���ȫ�Ա���
#define NO_SECURITY                                 0x03        //���ð�ȫ����
#define SECURITY                                    0x04        //��ȫ����


#define NOTIFIER_OPERATION_SUCCESS                  LIBP4V_BOOLEAN_TRUE
#define NOTIFIER_OPERATION_FAILURE                  LIBP4V_BOOLEAN_FALSE

#define NOTIFIER_ACT_USER_PRIVACY                   0xA0        // �����û�������Ϣ
#define NOTIFIER_ACT_OPS                            0xA1        // ��ȡ��Ӫ���б�
#define NOTIFIER_ACT_ENTITLEMENT_LIST               0xA2        // �����û���Ȩ�б�
#define NOTIFIER_ACT_RECOVER_PIN                    0xA3        // PIN���ѻָ�ΪĬ��ֵ000000
#define NOTIFIER_ACT_NEW_PIN_VALUE                  0xA4        // ���������µ��û�PIN
#define NOTIFIER_ACT_PIN_AVAILABILITY               0xA5        // ��������PIN��Ŀ�����
#define NOTIFIER_ACT_NEW_CERTIFICATE_VALUE          0xA6        // ����������Ҫ���Ʋ����Ľ�Ŀ���˼���
#define NOTIFIER_ACT_CERTIFICATE_CONFIRMING_RESULT  0xA7        // ��Ŀ��������趨�ۿ�����
#define NOTIFIER_ACT_EMERGENCY_BROADCASTING         0xA8        // ִ��Ӧ���㲥
#define NOTIFIER_ACT_WORKING_PERIOD                 0xA9        // ��������ʱ�����ý��
#define NOTIFIER_ACT_ATTRIBUTE_BLOCKING             0xAA        // �û��⵽���Զ������ԡ�����
#define NOTIFIER_ACT_OVERDUE_INFORM                 0xAB        // ���������Զ�֪ͨ���ý��

#define NOTIFIER_ACT_FREE_WORKING_PERIOD            0xE1        // ����ȡ������ʱ�����ý��
#define NOTIFIER_ACT_GET_WORKING_PERIOD             0xE2        // ������ȡ����ʱ�εľ�����Ϣ���
#define NOTIFIER_ACT_GET_CERTIFICATE_LEVEL          0xE3        // �������˼�����
#define NOTIFIER_ACT_GET_PIN_STATE                  0xE4        // ����PIN״̬
#define NOTIFIER_ACT_DISPLAY_USER_NUMBER            0xE5        // ��ʾ����
#define NOTIFIER_ACT_INACTIVE                       0xE6        // ϵͳ��δ����
#define NOTIFIER_ACT_ACTIVE_ERROR                   0xE7        // �������
#define NOTIFIER_ACT_GET_OVERDUE_INFORM             0xE8        // ������ȡ�����Զ�֪ͨ������Ϣ���

#define NOTIFIER_DAT_MAIL                           0xB0        // ��������Ϊ�����ʼ�
#define NOTIFIER_DAT_POPUP_MESSAGE                  0xB1        // ��������Ϊ������Ϣ
#define NOTIFIER_DAT_FILM_RATING                    0xB2        // ��������Ϊ��Ŀ�ּ�

#define NOTIFIER_POP_CLEAR_SCREEN                   0xD0        // ������
#define NOTIFIER_POP_UNSUPPORTED_FRONTEND           0xD2        // �Ǳ�ϵͳ���ܣ��޷��տ���
#define NOTIFIER_POP_GCA_BLOCKED                    0xD3        // �����������޷��տ��˽�Ŀ��
#define NOTIFIER_POP_BLACKLISTED                    0xD4        // ���������˺��������޷��տ��˽�Ŀ��
#define NOTIFIER_POP_USER_FROZEN                    0xD5        // ���û���ǰ�˽���
#define NOTIFIER_POP_USER_UNFROZEN                  0xD6        // ���û���ǰ�˽ⶳ
#define NOTIFIER_POP_NOT_IN_WORKING_PERIOD          0xD7        // ϵͳ���ڹ���ʱ����
#define NOTIFIER_POP_NO_SUCH_ENTITLEMENT            0xD8        // û����Ȩ���޷��տ��˽�Ŀ��

#define NOTIFIER_ACT_ACTIVE_EMERGENCY_BROADCASTING  0xD9        // Ӧ���㲥����
#define NOTIFIER_POP_ENTITLEMENT_OVERDUE            0xDA        // �û���Ȩ�ѹ���

// ��ע��  ��Ϣ��������ӵ�  0xE7
// ��ע��  ��Ϣ��������ӵ�  0xE8
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

#define ERROR_PIN_0                                 2           // PIN����PIN�Ѿ�����
#define ERROR_PIN_1                                 3           // PIN����ʣ��1�λ���PIN���ᱻ����
#define ERROR_PIN_2                                 4           // PIN����ʣ��2�λ���PIN���ᱻ����
#define ERROR_PIN_3                                 5           // PIN����ʣ��3�λ���PIN���ᱻ����
// zhaofan add
#define ERROR_INPUT_TIME                            6           // ʱ�����ݴ���
#define ERROR_INPUT_TIME_SAME                       7           // ʱ�����ݴ��󣬿�ʼʱ�䲻�������ʱ����ͬ

#define ERROR_NO_PROCESS                            8           // û�в���
#define ERROR_UNKNOW                                9           // ����ʧ��

//////////////////////////////////////////////////////////////////////////////
#define MAIL_TYPE_IMPORTANT                         1
#define MAIL_TYPE_COMMON                            2

//������Ϣ
#define ALLOCATE_MEMORY_FAILED                      -101
#define GET_FILE_FAILED                             -102

// ״̬��Ϣ
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
    ird_uint8_t     m_flag;                                     // 0����ʾ��1������
    ird_uint16_t    m_count;                                    // ��������
    ird_uint16_t    m_condition_list[MAX_CONDITION_COUNT];      // �����б�
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
    ird_uint8_t     m_programCertificate;                       // ��ǰ������Ŀ�ļ���
    ird_uint8_t     m_systemApprovalCertificate;                // ��ǰϵͳ��ɵļ���
};
typedef struct info_program_certificate     info_program_certificate_t;

// �û��鿴���ܿ�������Ϣʹ�õ����ݽṹ
struct info_user_privacy
{
    ird_uint8_t     m_version;                                  // ϵͳ�汾(CAϵͳ�汾)
    ird_uint8_t     m_serialNumber[SN_LENGTH];                  // ���ܿ�����
    ird_uint8_t     m_algorithmFamily;                          // ���ܿ���֧�ֵ��㷨�汾Ⱥ
    ird_uint32_t    m_superCASID;                               // ��ǰCAϵͳ��
    ird_uint8_t     m_pinAvailabilityFlag;                      // ������Ʊ�־
    ird_uint8_t     m_defaultPINFlag;                           // Ĭ��PIN���ʶλ:1ΪĬ��PIN��Ĭ��ֵ����0Ϊ���Զ��壩
    ird_uint8_t     m_systemApprovalCertificate;                // ϵͳ��ɳ��˼���
    ird_uint8_t     m_userState;                                // �û�״̬��1���ã���0���ã�
    ird_uint8_t     m_gcaNameLength;
    ird_uint8_t     m_gcaName[MAX_NAME_LENGTH];
    ird_uint8_t     m_casProviderNameLength;
    ird_uint8_t     m_casProviderName[MAX_NAME_LENGTH];
};
typedef struct info_user_privacy    info_user_privacy_t;

// �û��鿴��Ӫ����Ϣ�����ݽṹ
struct info_keyset
{
    ird_uint8_t     m_count;
    ird_uint16_t    m_ids[MAX_OP_KEYSET_COUNT];
};
typedef struct info_keyset  info_keyset_t;

struct info_op
{
    ird_uint8_t     m_serialNumber[SN_LENGTH];                  // �û�ID
    ird_uint32_t    m_subCASID;                                 // ��ǰCA��ϵͳ��
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


// �û��鿴��Ȩʹ�õ����ݽṹ
struct info_product
{
    ird_uint16_t    m_id;
    ird_uint8_t     m_type;
    ird_uint8_t     m_nameLength;
    ird_uint8_t     m_name[MAX_NAME_LENGTH];
    ird_uint8_t     m_expired[MJD_UTC_CODING_LENGTH];           // ��ƷʧЧ���ڣ�MJD_UTC
};
typedef struct info_product info_product_t;

struct info_user_entitlement
{
    ird_uint16_t     m_count;
    info_product_t  m_entitlements[MAX_PRODUCT_RECORD_COUNT + MAX_PACKAGE_RECORD_COUNT];
};
typedef struct info_user_entitlement    info_user_entitlement_t;


// �����й���ʱ����Ϣ�ṹ
struct info_working_period
{
    ird_uint8_t     m_state;                                    //����ʱ���Ƿ���ã�1Ϊ���ã�0Ϊ������
    ird_uint8_t     m_dailyBeginAt[UTC_CODING_LENGTH];
    ird_uint8_t     m_dailyEndAt[UTC_CODING_LENGTH];
};
typedef struct info_working_period info_working_period_t;

// Ӧ���㲥������
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
    desc_ca_linkage_t   m_caLinkageDesc;                        // ��ת������
    ird_uint8_t         m_expiredTime[MJD_UTC_CODING_LENGTH];   // �㲥��ֹʱ�� MJD + UTC
};
typedef struct info_emergency_broadcasting info_emergency_broadcasting_t;

struct info_operation_result
{
    ird_uint8_t     m_operation;                                // ��������
    ird_uint8_t     m_result;                                   // �������
    ird_uint32_t    m_value;                                    // �������ӷ���ֵ
};
typedef struct info_operation_result    info_operation_result_t;

struct emm_pid_list
{
    ird_uint8_t     m_count;                                    // EMM PID ����
    ird_uint16_t    m_pid[MAX_EMM_PID_COUNT];                   // EMM PID �б�
};
typedef struct emm_pid_list     emm_pid_list_t;

// �����Զ�֪ͨ���ݽṹ
struct info_overdue_inform
{
    ird_uint8_t     m_state;                                    //����֪ͨ�Ƿ���ã�1Ϊ���ã�0Ϊ������
    ird_uint8_t     m_aheadDays;                                     //����֪ͨ��ǰ������Ϊ5��15֮�䡣
};
typedef struct info_overdue_inform info_overdue_inform_t;

#if defined __cplusplus || defined __cplusplus__
}
#endif

#endif  /* end_of_file */
