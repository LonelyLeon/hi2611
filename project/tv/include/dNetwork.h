
/*******************************************************************************
File name   : network.h

Author        : XXX            

Description : .
              
Copyright (C) BeiJing SUMAVision, Inc., 2011 .All rights reserved.

History        :
                2011.01.12        Created                         
*******************************************************************************/
#ifndef __WORK_H_
#define __WORK_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ROC_TRUE
#define ROC_TRUE 1
#endif

#ifndef ROC_FALSE
#define ROC_FALSE 0
#endif

//#include "base.h"
//#include "product.h"
#include "dTypes.h"

typedef D_Char gchar;

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


#define  ROC_MAX_NET_DEVICE_NUM         8    /*!< ���֧�������ĸ���*/
#define  ROC_MAX_NET_DEVICE_NAME        32   /*!< ����������󳤶�*/
#define  ROC_MAX_NET_DEVICE_DESCRIBE    128  /*!< ������Ϣ������󳤶�*/
#define  ROC_MAX_CM_HARDWAR_INFO        128  /*!< cable modemӲ����Ϣ��󳤶�*/
#define  ROC_MAX_PING_RESULT            256  /*!< ping��󷵻����ݳ���*/
#define  ROC_MAX_NTP_SERVER             256  /*!< ntp������������󳤶�*/

#define  ROC_NET_RET_SUCCESS           (0)          /*!< �������ӳɹ�*/
#define  ROC_NET_RET_TIMEOUT           (-1)   /*!< �������ӳ�ʱ*/
#define  ROC_NET_RET_FAILED              (-2)   /*!< ��������ʧ��*/
#define  ROC_NET_RET_PWDERR              (-3)   /*!< �������*/

/*�������ͨ�ŷ�ʽ*/
#define ROC_SPEED_10    10
#define ROC_SPEED_100   100
#define ROC_SPEED_1000  1000
#define ROC_HALF_DUPLEX 0
#define ROC_FULL_DUPLEX 1

#define    ROC_SYSEVENT_TYPE                                   1001
#define    ROC_SYSEVENT_DHCP_SUCCESS                             10508     //DHCP�������óɹ���modifiersΪ����������"eth0"
#define    ROC_SYSEVENT_DHCP_TIMEOUT                                10509     //DHCP�������ó�ʱ,    modifiersΪ����������"eth0"
                                                                         /* Ԥ�� 10510-10520 ��LANģʽ�����Ϣʹ�� */

#define    ROC_SYSEVENT_NTPTIME_SYNC_SUCC                      10521     // ����NTPʱ��ͬ���ɹ�.modifiersΪntpͬ��utcʱ��,��λ��
#define    ROC_SYSEVENT_NTPTIME_SYNC_TIMEOUT                   10522     // ���� NTPʱ��ͬ����ʱ.
#define    ROC_SYSEVENT_PING_RESPONSE                          10523     // PING������Ӧ.
                                                                         // #modifiers ���ַ������ͣ�"-1"����ʱ,����������Ӧ;"0.7162ms"����ʾ��Ӧ��ʱ�� 
                                                                         /* Ԥ�� 10524-10530 ���������������Ϣʹ�� */
#define    ROC_SYSEVENT_WRITE_FLASH_SUCC                       10601     // Flashд��ɹ�
                                                                         /* Ԥ�� 10602-10700 ������Ӳ�������Ϣʹ�� */

#define  ROC_MAX_ETH_NAME_LEN           16          // �豸����󳤶�
#define  ROC_MAX_ETH_SUPPORT_NUM        6           // ֧������������
#define  ROC_MAX_ESSID_LEN      32   /*!< ESSID��󳤶�*/
#define  ROC_MAX_PASSWORD_LEN   128  /*!< ��Կ��󳤶�*/

/**
** @brief
**  �������ӵ�����
*/
typedef enum _NET_CONNECT_TYPE
{
    _NET_CONNECT_TYPE_WIRED              = 0,    /*!< �������ӣ�RJ45����ͨ�ӿ�����*/
    _NET_CONNECT_TYPE_WIRELESS           = 1,    /*!< �������ӣ�����wifi����*/
    _NET_CONNECT_TYPE_CABLE_MODEM        = 2,    /*!< ͨ��cable modem��������*/
    _NET_CONNECT_TYPE_MOBILE_BROADBAND   = 3,    /*!< �ƶ���������*/
    _NET_CONNECT_TYPE_UNKOWN             = 4,    /*!< δ֪ */
    _NET_CONNECT_TYPE_RESERVE            = 5     /*!< Ԥ�� */
}_NET_CONNECT_TYPE_e;

typedef _NET_CONNECT_TYPE_e _Connect_Type_e;

typedef struct Roc_IP_Config
{
    D_S32 index;                                  //index=0 ��ʵip��index =1��2��3��Ӧ����ip  ����etn0:1
    D_Char devicename[ROC_MAX_ETH_NAME_LEN];
    D_Char method[8];
    D_Char ipaddr[16];
    D_Char mask[16];
    D_Char gateway[16];
    D_Char dns[16];
}Roc_IP_Config_t;

/**
** @brief
**  �����豸״̬
*/
typedef enum _NET_DEVICE_STATUS
{
    _NET_DEVICE_STATUS_NOT_FOUND     = 0,    /*!< �豸�����ڣ����ɷ���*/
    _NET_DEVICE_STATUS_UNKOWN        = 1,    /*!< �豸���ڣ����޷���ȡ״̬*/

    /*������߷�ʽ*/
    _NET_DEVICE_STATUS_CONNECT       = 101,  /*!< ������������*/
    _NET_DEVICE_STATUS_DISCONNECT    = 102,  /*!< ���������쳣*/

    /*���cable modem��ʽ*/
    _NET_DEVICE_STATUS_CM_USABLE     = 201,  /*!< cable modem������������*/
    _NET_DEVICE_STATUS_CM_UNUSABLE   = 202,  /*!< cable modem���������ж�*/
    _NET_DEVICE_STATUS_CM_BADNESS    = 203,  /*!< cable modem����״̬���ı䣬���ǲ���*/
    
    _NET_DEVICE_STATUS_RESERVE       = 204   /*!< Ԥ��*/
}_NET_DEVICE_STATUS_e;

/**
** @brief
**  ipЭ�������
*/
typedef enum Roc_IP_Type
{
    ROC_IP_TYPE_IPv4    = 0,    /*!< ipv4��ַЭ��*/
    ROC_IP_TYPE_IPv6    = 1,    /*!< ipv6��ַЭ��*/
    ROC_IP_TYPE_RESERVE = 2     /*!< Ԥ��*/
}Roc_IP_Type_e;

/**
** @brief
**  IP��ַ��IPv4��IPv6����
*/
typedef struct Roc_IP
{
    Roc_IP_Type_e type;         /*!< ipЭ�������*/
    union
    {
        D_U32   ipv4_add;    /*!< ����type=ROC_IP_TYPE_IPV4ʱ��Ч*/
        D_U16   ipv6_add[8]; /*!< ����type=ROC_IP_TYPE_IPV6ʱ��Ч*/
    }ip_add;
}Roc_IP_t;

/**
** @brief
**  ipv4�����ַ������Ϣ
*/
typedef struct Roc_IPv4_Config
{
    D_U32    address;   /*!< ipv4��ַ*/
    D_U32    netmask;   /*!< �������룬ipv4��ַ*/
    D_U32    gateway;   /*!< Ĭ�����أ�ipv4��ַ*/
    D_U32    dns[3];    /*!< 1-3��DNS�����ַ��ipv4��ַ*/
}Roc_IPv4_Config_t;

/**
** @brief
**  ipv6�����ַ������Ϣ
*/
typedef struct Roc_IPv6_Config
{
    D_U16    address[8]; /*!< ipv6��ַ*/
    D_U32    prefix_len; /*!< ����ǰ׺����*/
    D_U16    gateway[8]; /*!< Ĭ�����أ�ipv6��ַ*/
    D_U16    dns[3][8]; /*!<  1-3��DNS�����ַ��ipv6��ַ*/
}Roc_IPv6_Config_t;

/**
** @brief
**  PPPoE������Ϣ
*/
typedef struct Roc_PPPoE_Setup
{
    D_Char      usr_name[256];      /*!< �û���*/
    D_Char      password[256];      /*!< ����*/
    D_Bool    auto_dns;           /*!< �Ƿ��Զ���ȡdns����ֵΪROC_FALSE��dns_server��Ч*/
    D_S32     demand_value;       /*!< ����ʱ�Զ��Ͽ�ʱ�䣬��λ�룬-1������Զ���Զ��Ͽ�*/
}Roc_PPPoE_Setup_t;

/**
** @brief
**  �������õĻ�����Ϣ
*/
typedef struct Roc_Net_Device_Cfg
{
    D_Char                  dev_name[ROC_MAX_NET_DEVICE_NAME];          /*!< �������ƣ�����eth0*/
    D_Char                  description[ROC_MAX_NET_DEVICE_DESCRIBE];   /*!< ��ȡ����������Ϣ������:"RealTek PCI GBE Family Controller"*/
    _NET_CONNECT_TYPE_e  connect_type;       /*!< ���õ�������������*/
    D_U32                data_rate;          /*!< ����������ʣ���λΪKbps*/
    D_U8                 mac_addr[6];        /*!< �����ַ*/
    Roc_IP_Config_t         ip_cfg;             /*!< ip��ַ*/
}Roc_Net_Device_Cfg_t;

/*proxyģʽ*/
typedef enum _PROXY_Mode
{
    _PROXY_HTTP     = 0x00,   //ʹ��http proxy
    _PROXY_HTTPS    = 0x01,   //ʹ��https proxy
    _PROXY_FTP      = 0x02,   //ʹ��ftp proxy
    _PROXY_NUM      = 0x03    //ʹ��ftp proxy
}_PROXY_Mode_e;

//������Ϣ��webapp,type=1001Ϊϵͳ��Ϣ��type=1002Ϊ���̣�type=1003Ϊ��꣬type=1004Ϊͨ��ң������type=1005Ϊ ������ң������type=1006Ϊ��ͯ��ң������typeֵ����1006Ԥ������չ����ʹ�á�
typedef struct SysNetworkEvent
{
    D_S32 msgtype;
    D_S32 msg;
    D_Char  modifiers[32];
}SysNetworkEvent_t;

typedef struct Roc_DHCPLeaseTime
{
    D_Char   leaseobtained[32];    //��ȡ��DHCPģʽ������IP��ַ��ʼʱ��,yyyy-mm-dd hh:mm:ss
    D_Char   leaseexpires[32];     //��ȡ��DHCPģʽ��IP��ַ�Ĺ���ʱ��,yyyy-mm-dd hh:mm:ss
}Roc_DHCPLeaseTime_t;


typedef struct Roc_DHCP_Info
{
    D_Char   ipaddr[16];        //dhcp��ȡ����ip��ַ
    D_Char   mask[16];            //dhcp��ȡ������������
    D_Char   gateway[16];        //dhcp��ȡ��������
    D_Char   dhcpserver[16];    //dhcp�������ĵ�ַ
    D_S16   dhcpport;          //dhcp�������Ķ˿ں�
    Roc_DHCPLeaseTime_t leasetime;
}Roc_DHCP_Info_t;

typedef struct Roc_Package_Info
{
    D_U32 sentpackages;         //��ȡ�������͵����ݰ�����
    D_U32 receivedpackages;     //��ȡ�������յ������ݰ�����
}Roc_Package_Info_t;


/* proxy ���������뷽ʽ��Ϣ */
typedef struct _PROXY_Config
{
    D_Char           devicename[ROC_MAX_ETH_NAME_LEN];
    D_U8          proxyenable;                //�Ƿ����ô���,��ֵ�ͣ�ȡֵ���£�1��ʾ��ǰ����������Ч��0��ʾ��ǰ������Ч���ɶ�д
    _PROXY_Mode_e proxymode;                  //proxy����
    D_Char           usrname[32];                //��ǰ proxy ���������뷽ʽ���û���,ȡֵΪ��0-30���ַ����������ǿո�
    D_Char           password[32];               //��ǰ proxy ���������뷽ʽ������,ȡֵΪ��0-30���ַ��������ǿո�
    D_Char           server[256];                //http����������� IP��ַ����������ַ,���ܳ��� 255 �ֽ�
    D_Char           unusedproxyurls[5][256];    //���ò�ʹ�ô���� URLs,���ܳ��� 255 �ֽ�
    D_S32          port;                       //http�������ķ������˿ں�,ȡֵΪ��0-5 �������ַ�
}_PROXY_Config_t;

/*�������õĻ�����Ϣ*/
typedef struct Roc_Device_Cfg
{
    D_Char                  devicename[ROC_MAX_ETH_NAME_LEN];          // ��������,����eth0
    D_Char                  description[128];        // ��ȡ����������Ϣ������:"RealTek PCI GBE Family Controller
    _Connect_Type_e      connecttype;                // ���õ�������������
    D_U32                datarate;                   // �����������,��λΪKbps
    D_U8                 mac[6];                     // �����ַ
}Roc_Device_Cfg_t;

/*cable modem ����״̬*/
typedef enum Roc_Cable_Modem_Status
{
    _NET_CM_STATUS_OFFLINE       = 0,    // CABLE_MODEM����
    _NET_CM_STATUS_ONLINE        = 1,    // CABLE_MODEM����
    _NET_CM_STATUS_SCANNING      = 2     // CABLE_MODEM����ɨ��Ƶ��
}Roc_Cable_Modem_Status_e;

/* CM��Ϣ*/
typedef struct Roc_Cable_Modem_Info
{
    D_Char                      hw_ver[128];    // Ӳ���汾
    D_Bool                    enable;         // �豸�Ƿ��Ѿ���
    Roc_Cable_Modem_Status_e    state;             // CM״̬
}Roc_Cable_Modem_Info_t;

/*������������״̬*/
typedef enum _WIRELESS_STATUS
{
    _WIRELESS_STATUS_IDLE        = 0,    //�豸����(δ���κ�AP����)
    _WIRELESS_STATUS_CONNECTED   = 1,    // ���ӳɹ�
    _WIRELESS_STATUS_UNKOWN      = 2     // δ֪״̬
}_WIRELESS_STATUS_e;

/*IEEE 802.11��׼*/
typedef enum _WIRELESS_PROTOCOL
{
    _WIRELESS_PROTOCOL_80211     = 0x0001,
    _WIRELESS_PROTOCOL_80211a    = 0x0002,
    _WIRELESS_PROTOCOL_80211b    = 0x0004,
    _WIRELESS_PROTOCOL_80211g    = 0x0008,
    _WIRELESS_PROTOCOL_80211i    = 0x0010,
    _WIRELESS_PROTOCOL_80211n    = 0x0020,
    _WIRELESS_PROTOCOL_80211bg   = 0x0040,
    _WIRELESS_PROTOCOL_80211bgn  = 0x0080,
    _WIRELESS_PROTOCOL_OTHER     = 0x0000
}_WIRELESS_PROTOCOL_e;

/*���ߵĹ���ģʽ*/
typedef enum _WIRELESS_MODE
{
    _WIRELESS_MODE_MANAGED       = 0,    // ����ģʽ
    _WIRELESS_MODE_AC_HOC        = 1,    // �Ե�ģʽ
    _WIRELESS_MODE_REPEAT        = 2,    // �м�ģʽ
    _WIRELESS_MODE_OTHER         = 3     // ����ģʽ
}_WIRELESS_MODE_e;

/* ������֤��ʽ*/
typedef enum Roc_Wireless_Auth_Alg
{
    _IW_AUTH_LEAP                = 0,    // ����֤
    _IW_AUTH_WEP_OPEN_SYSTEM     = 1,    // WEP����ϵͳ�����֤
    _IW_AUTH_WEP_SHARED_KEY      = 2,    // WEP������Կ�����֤
    _IW_AUTH_WPA_PSK             = 3,    // WPAԤ������Կģʽ����ͥ��С�Ͱ칫����ʹ��
    _IW_AUTH_WPA2_PSK            = 4,    // WPA2Ԥ������Կģʽ����ͥ��С�Ͱ칫����ʹ��
    _IW_AUTH_OTHER               = 5     // ������֤��ʽ
}Roc_Wireless_Auth_Alg_e;

/* ����Э��*/
typedef enum _WIRELESS_CIPHER
{
    _WIRELESS_CIPHER_NONE        = 0,    // �޼���Э��
    _WIRELESS_CIPHER_WEP40       = 1,    // 64(40+24iv)λWEP����Э��
    _WIRELESS_CIPHER_WEP104      = 2,    // 128(104+24iv)λWEP����Э��
    _WIRELESS_CIPHER_WEP128      = 3,    // 152(128+24iv)λWEP����Э��
    _WIRELESS_CIPHER_TKIP        = 4,    // ��ʱ��Կ����Э��,��ӦWPA/WPA2/WPA-PSK/WPA2-PSKʹ��
    _WIRELESS_CIPHER_AES         = 5,    // �߼����ܱ�׼,��ӦWPA/WPA2/WPA-PSK/WPA2-PSKʹ��
    _WIRELESS_CIPHER_OTHER       = 6     // ��������Э��
}_WIRELESS_CIPHER_e;

/* WIFI���Ӳ���*/
typedef struct _Wireless_Param
{
    D_Char                  essid[32];      //�������ӵ�AP��essid
    D_U8               bssid[6];// MAC��ַ
    D_S32                 key_len;       // ��Կ����,-1������Ҫ��������
    D_S8                  key[128];      //��Կ
    void                    *reserve;      // Ԥ��������չ��������֤����
}_Wireless_Param_t;

/* WIFI AP��Ϣ*/
typedef struct _Wireless_AP_Info
{
    D_Char                          essid[32];                   // Extended Service Set Identifier ��չ����Ԫ��ʶ��
    D_U8                         bssid[6];                   // Basic    Service Set Identifier,��������Ԫ��ʶ��,һ��ΪMAC��ַ
    _WIRELESS_PROTOCOL_e         protocol;                   // ֧�ֵ�ieee802.11Э��
    _WIRELESS_MODE_e             wireless_mode;              // ����ģʽ
    D_U32                        bit_rate;                   // ��������,��λKHz
    D_U32                        freq;                       // ����Ƶ�ʣ���MHzΪ��λ
    D_U8                         channel_num;                // ʹ�õ�����ͨ��ֵ
    D_U8                         quality;                    //  link quality �ź�����,��Χ0��100
    D_U8                         signal;                     //  signal level (dBm) �ź�ǿ�� 
    D_U8                         noise;                      //  noise  level (dBm) ���ŵ�ƽ
    D_Bool                        privacy;                    // �Ƿ�Ϊ��������,privacy=ROC_TRUEΪ����������wireless_alg,cipher��Ч
    D_Bool                        connected;              //
    Roc_Wireless_Auth_Alg_e         wireless_alg;               // ��֤�߼�
    _WIRELESS_CIPHER_e           cipher;                     // ����Э��
    D_Char                          password[32]; 
}_Wireless_AP_Info_t;

typedef struct _net_manage
{
    _Connect_Type_e        type;
    char                    name[32];
    char                    desc[64];
    char                    ip[16];
    int                     support;
    int                     enable;
    int                     dhcp_flag;
    unsigned int            data_rate; 
    int                        dns_auto;
}_net_manage_t;

/*DHCPģʽ*/
typedef enum DHCP_Mode
{
        ROC_STATIC     = 0x00,   /*�м����ʹ��DHCP*/
       ROC_DHCP   = 0x01,  /*�м��ʹ��DHCP  */
}DHCP_Mode;

typedef DHCP_Mode Roc_DHCP_Mode_e;


typedef struct _net_cfg
{
    _Connect_Type_e        type;
    char devicename[8];
    D_Bool       connected;
   DHCP_Mode        method;
    char                    name[32];
    unsigned char      bssid[6];
    char                    ip[16];
    char                    gateway[16];
    char                    mask[16];
    char                    dns[16];
}_net_cfg_t;

typedef struct  arg_pthread
{
    char *devicename;
    _Wireless_Param_t *param;
}ARG_PTHREAD;

typedef struct _net_cur_info
{
    D_Bool       connected;
    char                    name[32];
    unsigned char      bssid[6];
    D_U8                         quality;                    //  link quality �ź�����,��Χ0��100
    D_U8                         signal;                     //  signal level (dBm) �ź�ǿ�� 
    D_U8                         noise;                      //  noise  level (dBm) ���ŵ�ƽ
}_net_cur_info_t;

/*--------------------------      ��������     --------------------------*/


extern void my_system(char * cmd);

int d_timeserver_connect(void);

D_S32 d_get_wireless_password(D_Char* filename, D_Char *password);

/*******************************************************************************
����˵��: 
    �����ػص�������ʽ, �ص�����Ҫ���������ء�
   
����˵��:
    �������:
    [D_S32 type    ] 0
    [void *data      ] ��Ϣ�ĸ������ݣ�����ΪSysNetworkEvent_t��
                       SysNetworkEvent_t�е�msgȡ��Ϣ��ֵ
    [D_S32 data_len] ��Ϣ�ĳ���
����ֵ:
    [D_S32] 0 �ɹ������� ������
*******************************************************************************/
typedef D_S32(*network_event_cbk)(D_S32 type, void* data, D_S32 data_len);

/*******************************************************************
���ܣ��ṩ����ģ��ע������ģ��ص�����
���������
    callback: Ҫע��Ļص�����
���������
    ��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 network_reg_cbk(network_event_cbk callback);

/*******************************************************************
���ܣ����õ�ǰ�������ṩ����ʱ��������������� IP ��ַ,Ҳ������������ntpserver ����������������ʱ�䡣
���������
    ntpserver:�ַ����������� 255 �ֽ�
���������
    ��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
��ע���ڵ��� Network.save()��д Flash
*/
D_S32 network_set_ntp_server(D_Char* ntpserver);

/*******************************************************************
���ܣ���ȡ��ǰ�������ṩ����ʱ��������������� IP ��ַ,Ҳ������������ntpserver ����������������ʱ�䡣
���������
    bufflen :�ַ�����󳤶�
���������
    ntpserver:�ַ����������� 255 �ֽ�
    bufflen :�ַ���ʵ�ʳ���
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 network_get_ntp_server(D_Char* ntpserver, D_U8* bufflen);

/*******************************************************************
���ܣ�����NTPͬ�������
���������
     interval:      NTPͬ��ʱ��������λΪ��
���������
     ��    
����ֵ����ֵ�ͣ� 0  �ɹ�-1 ʧ��
*/
D_S32 network_set_ntp_interval(D_S32 interval);

/*******************************************************************
���ܣ� ��ȡNTPͬ�������
���������
     ��
���������
     interval:      NTPͬ��ʱ��������λΪ��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 network_get_ntp_interval(D_S32 *interval);

/*******************************************************************
���ܣ� ����NTP��ʱʱ�䡣
���������
     timeout:       NTPʱ��ͬ����ʱʱ�䣬��λΪ��
���������
     ��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 network_set_ntp_timeout(D_S32 timeout);

/*******************************************************************
���ܣ� ��ȡNTP��ʱʱ�䡣
���������
     ��
���������
     timeout:       NTPʱ��ͬ����ʱʱ�䣬��λΪ��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 network_get_ntp_timeout(D_S32 *timeout);

/*******************************************************************
���ܣ�ͬ�� NTP ʱ�䡣 �����ȡ����Ϣ 10521��ʾ���� NTP ʱ��ͬ���ɹ���
��ȡ����Ϣ10522���� NTPʱ��ͬ����ʱ
���������
    ��
���������
    ��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
��ע������ֵֻ�Ǳ�ʾ�����Ƿ�ʼִ�� NTP ʱ��ͬ����������ʾʵ�ʵ�ͬ�������ʵ�ʵ�ͬ�����������Ϣ֪ͨ����
    �緵�� 0����������Ϊû������NTPServer��
*/
D_S32 network_ntp_update();

/*******************************************************************
���ܣ�����������ն��豸��һ��ʶ���ַ�������������
���������
    hostname:�ַ����������� 255 �ֽڣ��ɶ�д
���������
    ��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
��ע���ڵ��� Network.save()��д Flash
*/
D_S32 d_network_set_hostname(D_Char* hostname);

/*******************************************************************
���ܣ���ȡ������ն��豸��һ��ʶ���ַ�������������
���������
    bufflen:�ַ�����󳤶�
���������
    bufflen:�ַ���ʵ�ʳ���
    hostname:�ַ����������� 255 �ֽڣ��ɶ�д
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_get_hostname(D_Char* hostname, int bufflen);


/*******************************************************************
���ܣ� ��ȡĳ����������Ϣ��
���������
      devicename : �豸����    
���������
     devicecfg:       ����������Ϣ�����м��ȷ����ֵ��ΪNULL��
����ֵ����ֵ�ͣ� 0  �ɹ�-1 ʧ��
*/
D_S32 d_network_get_device_info(D_Char* devicename, Roc_Device_Cfg_t* devicecfg);

/*******************************************************************
���ܣ�ʵ����ͨ������ ping �Ĺ��ܡ�
���������
        address���ַ�����ping �������ַ,IP ����������ַ�� 
        parameter���ַ�����ping�Ĳ�����Ŀǰ��ֻʵ��"-t"ѡ��,����ֵ���޲����� -t�������� ping һ����ַ��ֱ���ֶ�ֹͣ.
        timeout:��ʱʱ�� ����λms
���������
        ��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
��ע��ÿ������Ӧ��ʱ��������Ϣ������������ͳ����Ϣ��
*/
D_S32 d_network_ping(D_Char* address, D_Char* parameter, D_S32 timeout);

/*******************************************************************
���ܣ��յ� ROC_SYSEVENT_PING_RESPONSE ��Ϣ���ȡ ping����Ӧ�ַ�����
���������
        bufflen����ʾ��ȡresponse�����ڴ泤��
���������
        pingresponsebuffer���ַ��������ڻ�ȡping����Ӧ�ַ���
        bufflen:ʵ�ʳ���
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_get_ping_response(D_Char* pingresponsebuffer, D_U8* bufflen);

/*******************************************************************
���ܣ�ȡ�����ڽ��е� ping ������
���������
    ��
���������
    ��
����ֵ����ֵ�ͣ�0����ֹͣ������ִ�е� ping ������-1����ǰ ping �����Ѿ�������ǰ�� ping����.
*/
D_S32 d_network_cancel_ping();

/*******************************************************************
���ܣ���ȡ�豸״̬
���������
        devicename���������ƣ�
���������
    devicestate: ��ֵ�ͣ��ο�ֵ����:    
        0    �豸�����ڣ����ɷ���
        1    �豸���ڣ����޷���ȡ״̬
        101    ��������
        102    ��������
        201    ������������
        202    ���������ж�
        203    ����״̬���ı䣬���ǲ���
        204    CableModem��STBͨ���ж�
        205    CableModem��STBͨ���жϣ���������
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_get_device_state(D_Char* devicename, D_S32* devicestate);

/*******************************************************************
���ܣ���ȡ��ǰ�����ն��豸��IP���󣬰���IP��ַ���������롢���ء�
���������
        devicename���������ƣ�  
���������
    ipinfo����ο�Roc_IP_Config_t���嶨�塣
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
˵��: Roc_IP_Config_t��index��0����ȡ������ʵip��֧��3������ip������devicename��eth0����1��2��3�ֱ��ȡeth0:1,eth0:2,eth0:3
*/
D_S32 d_network_get_ip(D_Char* devicename, Roc_IP_Config_t* ipinfo);

/*******************************************************************
���ܣ����õ�ǰ�����ն��豸��IP���󣬰���IP��ַ���������롢���ء�
����˵����
    devicename���������ƣ�
    ipinfo����ο�Roc_IP_Config_t���嶨�塣
���������
    ��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_set_ip(D_Char* devicename, Roc_IP_Config_t* ipinfo);

/*******************************************************************
���ܣ���ȡ�������պͷ��Ͱ�����Ϣ
���������
      devicename���豸���ƣ���eth0
�������:
    packages: �������ͺͽ��հ�����Ϣ�����Roc_Package_Info_t����
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_get_packeages(D_Char* devicename, Roc_Package_Info_t *packages);

/*******************************************************************
���ܣ�����������ͨ�ŷ�ʽ
���������
       devicename���豸���ƣ���eth0 
    communicateway: ������ͨ�ŷ�ʽ������������ֵ"adapting"��"10M_fullDuplex"��"10M_halfDuplex"��"100M_fullDuplex"��"100M_halfDuplex"
�������:
    ��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_set_commute_way(D_Char* devicename, D_Char* communicateway);

/*******************************************************************
���ܣ���ȡ������ͨ�ŷ�ʽ
���������
       devicename���豸���ƣ���eth0 
�������:
    communicateway: ������ͨ�ŷ�ʽ������������ֵ"adapting"��"10M_fullDuplex"��"10M_halfDuplex"��"100M_fullDuplex"��"100M_halfDuplex"
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_get_commute_way(D_Char* devicename, D_Char* communicateway);

/*******************************************************************
���ܣ���ȡ��ǰ���������ͣ�ȡֵ��Χ��"ethernet"��"ppp"��"pppoe"
���������
    devicename���豸���ƣ���eth0
�������:
      connectiontype:�ַ���
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_get_connection_type(D_Char* devicename, D_Char* connectiontype);

/*******************************************************************
���ܣ�����DHCPģʽ�Ƿ��Զ���ȡDNS ����������ȥִ�л�ȡDNS����
���������
    devicename���豸���ƣ���eth0
    autodns: 1��ʾ�Զ���ȡDNS��0��ʾ�ֶ���ȡ
�������:
       ��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 _set_dns_auto(D_Char* devicename, D_Bool autodns);

/*******************************************************************
���ܣ���ȡDHCPģʽ�Ƿ��Զ���ȡDNS 
���������
    devicename���豸���ƣ���eth0    
�������:
       autodns: 1��ʾ�Զ���ȡDNS��0��ʾ�ֶ���ȡ
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 _get_dns_auto(D_Char* devicename, D_Bool *autodns);

/*******************************************************************
���ܣ�����DNS��������Ϣ
���������
    devicename���豸���ƣ���eth0    
    index: DNS������������������������DNS������
    dnsserver: DNS��������ַ     
�������:
       ��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_set_dnsserver(D_Char* devicename, D_Char *dnsserver);

/*******************************************************************
���ܣ���ȡDNS��������Ϣ
���������
    devicename���豸���ƣ���eth0    
    index: DNS������������������������DNS������
�������:
       dnsserver: DNS��������ַ     
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_get_dnsserver(D_Char* devicename, D_Char *dnsserver);

/**********************************************************************************
���ܣ�
    ���õײ������ DHCP ������ʽ��dhcp Ϊ����� DHCP ������ʽ��0: ��ʾ������ DHCP��1: ��ʾ���� DHCP�� ����ֵ��Ч��ֱ�ӷ���0��
���������
    devicename���豸���ƣ���eth0
    dhcpmode:  ����� DHCP ������ʽ����
���������
    ��    
����ֵ��0  �ɹ�-1 ʧ��
*/
D_S32 d_network_set_dhcp_mode(D_Char *devicename, Roc_DHCP_Mode_e dhcpmode,  D_Bool sync);

/**********************************************************************************
����˵����
    ��ȡ��ǰ����� DHCP ������ʽ���룬0: ��ʾ������ DHCP��1: ��ʾ���� DHCP��
���������
    devicename���豸���ƣ���eth0
���������
    dhcpmode : �Ƿ�����DHCP
����ֵ��0  �ɹ�-1 ʧ��
*/
D_S32 d_network_get_dhcp_status(D_Char *devicename, D_Bool *dhcp_status);

/**********************************
����˵����
    ��ȡDHCP��̬�����DHCP�����Ϣ
���������
    devicename ��������
���������
    dhcp����Ϣ�����Roc_DHCP_Info_t�ṹ��   
��    �أ���ֵ�ͣ�0  �ɹ�-1 ʧ��
**********************************/
D_S32 dg_network_get_dhcp_info(D_Char* devicename, Roc_DHCP_Info_t *pdhcpip);

/**********************************
@brief ȡ���豸��ip ��ַ�����롢����
* @param devicename   �豸��
* @param ipinfo   ��Ϣ�ṹ
* @return ���ؽ��
**********************************/
D_S32 d_network_get_ip_gateway(D_Char* devicename, Roc_IP_Config_t* ipinfo);

/*******************************************************************
���ܣ� ��ȡethernetģʽ������״̬
���������
        devicename���豸���ƣ���eth0
�������:
        status: 1��ʾ�Ѿ������ϣ�0��ʾû��������
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_get_lan_status(const D_Char *devicename, D_Bool *status);

/*******************************************************************
���ܣ� ���������Ƿ����
���������
        devicename���豸���ƣ���eth0
        enable: 1��ʾ���ã�0��ʾ������
�������:
        ��   
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_set_eth_enable(const D_Char *devicename, D_Bool enable);

/*******************************************************************
���ܣ� ��ȡ�����Ƿ����
���������
        devicename���豸���ƣ���eth0  
�������:
        enable: 1��ʾ���ã�0��ʾ������
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_get_eth_enable(const D_Char *devicename, D_Bool *enable);

/*******************************************************************
���ܣ����������õ���������һ�������ø��ײ㣬�������԰��� ethernet�����µ�����������Զ����Խ������á�
    �书������ PC���������õ�ȷ�ϰ�ť�Ĺ��ܡ�
���������
        devicename���������ƣ�
���������
    ��   
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_submit_parameters(D_Char* devicename);

/*******************************************************************

����˵����
   ��ȡCable Modem����Ϣ��
���������
        ��
���������
        cminfo:          �Ƿ������ϡ����м��ȷ����ָ�벻ΪNULL��    
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_cable_modem_info(Roc_Cable_Modem_Info_t *cminfo);

/*******************************************************************

����˵����
  ��������Cable Modem���ӣ���ѯCable Modem������״̬��
���������
        ��
���������
        state: Cable Modem��״̬�����м��ȷ����ָ�벻ΪNULL��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_network_cable_modem_status(Roc_Cable_Modem_Status_e *state);

/*******************************************************************

����˵����
     ɨ���������磬��ʱ��ʾһ��AP��û���ѵ���
 ���������
        devicename     �������ơ����м��ȷ����ָ�벻ΪNULL��
        timeout     ��ʱʱ��,��λms��
        num       ap_info����󷵻ظ��������м��ȷ����ָ�벻ΪNULL����ap_numΪ��ֵ��
���������
        apinfo      ���Ի�ȡ����AP��Ϣ����,�ڴ����м�����䡣���м��ȷ����ָ�벻ΪNULL��
        num       ��ȡ����AP��Ϣ�����ʵ����Ч���ȡ����м��ȷ����ָ�벻ΪNULL��
����ֵ��ROC_NET_RET_SUCCESS   �ɹ�
             ROC_NET_RET_TIMEOUT   ���糬ʱ
             ROC_NET_RET_FAILED    ����ʧ��
*/
D_S32 d_wireless_scan(D_Char* devicename, D_S32 timeout, _Wireless_AP_Info_t *apinfo, D_S32 *ap_num);

/*******************************************************************

����˵����
    ����ָ����AP,����ֻ֧��16���ơ�
���������
        devicename     �������ơ����м��ȷ����ָ�벻ΪNULL��
        param         ���Ӳ�����
���������
    ��
����ֵ��ROC_NET_RET_SUCCESS   �ɹ�
             ROC_NET_RET_TIMEOUT   ���糬ʱ
             ROC_NET_RET_FAILED    ����ʧ��
*/
D_S32 _wireless_scan( D_Char* devicename, D_S32 timeout, _Wireless_AP_Info_t *apinfo, D_S32 *ap_num);

/*******************************************************************
���ܣ��Ͽ���AP������
���������
        devicename����������
���������
        ��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 d_wireless_disconnect(D_Char* devicename);

/*******************************************************************
���ܣ���ȡ��ǰ���ӵ�״̬��
���������
         devicename     �������ơ����м��ȷ����ָ�벻ΪNULL��
���������
         status :      ��ǰ����״̬�����м��ȷ����ָ�벻ΪNULL��
����ֵ����ֵ�ͣ�0  �ɹ�-1 ʧ��
*/
D_S32 rocme_porting_wireless_status(D_Char* devicename, _WIRELESS_STATUS_e *status);

extern int d_network_init(void);
extern void d_network_uninit(void);
extern D_S32 d_wireless_open(D_U32 action);
extern D_S32 d_wireless_close(D_U32 action);
extern D_S32 d_wireless_check_device(D_Char* devicename);
extern D_S32 d_wireless_connect(char *devicename, _Wireless_Param_t *param);
extern D_S32 d_wireless_get_info(char *name, _net_cfg_t *info);
extern D_S32 d_wireless_set_info(char *name, _net_cfg_t *info);
extern D_S32 d_wireless_get_curr_wifi(D_Char *devicename, D_Char *wifi_name, D_Bool *connected);
extern D_S32 d_wireless_start_check(D_S32 *error_check);
extern D_U32 d_network_test_communicate(void);
extern D_U32 d_network_get_connect_status(void);
extern D_U32 d_network_get_communicate_status(void);

extern D_S32 d_wireless_sreset(void);
extern D_S32 d_wireless_reload_ko();

/** @brief ȡ�õ�ǰ���ӵ�wifi�ź���Ϣ
* @param devicename   �豸��
* @param info   ��Ϣ�ṹ
* @return ���ؽ��
*/
extern D_S32 d_network_get_curr_info(D_Char* devicename, _net_cur_info_t* info);

extern D_Bool d_wireless_is_connecting(void);

#ifdef __cplusplus
}
#endif

#endif

