
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


#define  ROC_MAX_NET_DEVICE_NUM         8    /*!< 最大支持网卡的个数*/
#define  ROC_MAX_NET_DEVICE_NAME        32   /*!< 网卡名称最大长度*/
#define  ROC_MAX_NET_DEVICE_DESCRIBE    128  /*!< 网卡信息描述最大长度*/
#define  ROC_MAX_CM_HARDWAR_INFO        128  /*!< cable modem硬件信息最大长度*/
#define  ROC_MAX_PING_RESULT            256  /*!< ping最大返回内容长度*/
#define  ROC_MAX_NTP_SERVER             256  /*!< ntp服务器名称最大长度*/

#define  ROC_NET_RET_SUCCESS           (0)          /*!< 网络连接成功*/
#define  ROC_NET_RET_TIMEOUT           (-1)   /*!< 网络连接超时*/
#define  ROC_NET_RET_FAILED              (-2)   /*!< 网络连接失败*/
#define  ROC_NET_RET_PWDERR              (-3)   /*!< 密码错误*/

/*网络带宽及通信方式*/
#define ROC_SPEED_10    10
#define ROC_SPEED_100   100
#define ROC_SPEED_1000  1000
#define ROC_HALF_DUPLEX 0
#define ROC_FULL_DUPLEX 1

#define    ROC_SYSEVENT_TYPE                                   1001
#define    ROC_SYSEVENT_DHCP_SUCCESS                             10508     //DHCP功能启用成功，modifiers为网卡名，如"eth0"
#define    ROC_SYSEVENT_DHCP_TIMEOUT                                10509     //DHCP功能启用超时,    modifiers为网卡名，如"eth0"
                                                                         /* 预留 10510-10520 给LAN模式相关消息使用 */

#define    ROC_SYSEVENT_NTPTIME_SYNC_SUCC                      10521     // 网络NTP时间同步成功.modifiers为ntp同步utc时间,单位秒
#define    ROC_SYSEVENT_NTPTIME_SYNC_TIMEOUT                   10522     // 网络 NTP时间同步超时.
#define    ROC_SYSEVENT_PING_RESPONSE                          10523     // PING命令响应.
                                                                         // #modifiers ，字符串类型，"-1"：超时,服务器无响应;"0.7162ms"：表示响应的时间 
                                                                         /* 预留 10524-10530 给其他网络相关消息使用 */
#define    ROC_SYSEVENT_WRITE_FLASH_SUCC                       10601     // Flash写入成功
                                                                         /* 预留 10602-10700 给其它硬件相关消息使用 */

#define  ROC_MAX_ETH_NAME_LEN           16          // 设备名最大长度
#define  ROC_MAX_ETH_SUPPORT_NUM        6           // 支持网卡最大个数
#define  ROC_MAX_ESSID_LEN      32   /*!< ESSID最大长度*/
#define  ROC_MAX_PASSWORD_LEN   128  /*!< 密钥最大长度*/

/**
** @brief
**  网络连接的类型
*/
typedef enum _NET_CONNECT_TYPE
{
    _NET_CONNECT_TYPE_WIRED              = 0,    /*!< 有线连接，RJ45等普通接口上网*/
    _NET_CONNECT_TYPE_WIRELESS           = 1,    /*!< 无线连接，无线wifi上网*/
    _NET_CONNECT_TYPE_CABLE_MODEM        = 2,    /*!< 通过cable modem连接上网*/
    _NET_CONNECT_TYPE_MOBILE_BROADBAND   = 3,    /*!< 移动网络连接*/
    _NET_CONNECT_TYPE_UNKOWN             = 4,    /*!< 未知 */
    _NET_CONNECT_TYPE_RESERVE            = 5     /*!< 预留 */
}_NET_CONNECT_TYPE_e;

typedef _NET_CONNECT_TYPE_e _Connect_Type_e;

typedef struct Roc_IP_Config
{
    D_S32 index;                                  //index=0 真实ip，index =1、2、3对应虚拟ip  比如etn0:1
    D_Char devicename[ROC_MAX_ETH_NAME_LEN];
    D_Char method[8];
    D_Char ipaddr[16];
    D_Char mask[16];
    D_Char gateway[16];
    D_Char dns[16];
}Roc_IP_Config_t;

/**
** @brief
**  网络设备状态
*/
typedef enum _NET_DEVICE_STATUS
{
    _NET_DEVICE_STATUS_NOT_FOUND     = 0,    /*!< 设备不存在，不可访问*/
    _NET_DEVICE_STATUS_UNKOWN        = 1,    /*!< 设备存在，但无法获取状态*/

    /*针对有线方式*/
    _NET_DEVICE_STATUS_CONNECT       = 101,  /*!< 网线连接正常*/
    _NET_DEVICE_STATUS_DISCONNECT    = 102,  /*!< 网线连接异常*/

    /*针对cable modem方式*/
    _NET_DEVICE_STATUS_CM_USABLE     = 201,  /*!< cable modem网络连接正常*/
    _NET_DEVICE_STATUS_CM_UNUSABLE   = 202,  /*!< cable modem网络连接中断*/
    _NET_DEVICE_STATUS_CM_BADNESS    = 203,  /*!< cable modem网络状态不改变，但是不良*/
    
    _NET_DEVICE_STATUS_RESERVE       = 204   /*!< 预留*/
}_NET_DEVICE_STATUS_e;

/**
** @brief
**  ip协议的类型
*/
typedef enum Roc_IP_Type
{
    ROC_IP_TYPE_IPv4    = 0,    /*!< ipv4地址协议*/
    ROC_IP_TYPE_IPv6    = 1,    /*!< ipv6地址协议*/
    ROC_IP_TYPE_RESERVE = 2     /*!< 预留*/
}Roc_IP_Type_e;

/**
** @brief
**  IP地址，IPv4或IPv6类型
*/
typedef struct Roc_IP
{
    Roc_IP_Type_e type;         /*!< ip协议的类型*/
    union
    {
        D_U32   ipv4_add;    /*!< 仅在type=ROC_IP_TYPE_IPV4时有效*/
        D_U16   ipv6_add[8]; /*!< 仅在type=ROC_IP_TYPE_IPV6时有效*/
    }ip_add;
}Roc_IP_t;

/**
** @brief
**  ipv4网络地址配置信息
*/
typedef struct Roc_IPv4_Config
{
    D_U32    address;   /*!< ipv4地址*/
    D_U32    netmask;   /*!< 子网掩码，ipv4地址*/
    D_U32    gateway;   /*!< 默认网关，ipv4地址*/
    D_U32    dns[3];    /*!< 1-3个DNS服务地址，ipv4地址*/
}Roc_IPv4_Config_t;

/**
** @brief
**  ipv6网络地址配置信息
*/
typedef struct Roc_IPv6_Config
{
    D_U16    address[8]; /*!< ipv6地址*/
    D_U32    prefix_len; /*!< 子网前缀长度*/
    D_U16    gateway[8]; /*!< 默认网关，ipv6地址*/
    D_U16    dns[3][8]; /*!<  1-3个DNS服务地址，ipv6地址*/
}Roc_IPv6_Config_t;

/**
** @brief
**  PPPoE配置信息
*/
typedef struct Roc_PPPoE_Setup
{
    D_Char      usr_name[256];      /*!< 用户名*/
    D_Char      password[256];      /*!< 密码*/
    D_Bool    auto_dns;           /*!< 是否自动获取dns，此值为ROC_FALSE则dns_server有效*/
    D_S32     demand_value;       /*!< 空闲时自动断开时间，单位秒，-1代表永远不自动断开*/
}Roc_PPPoE_Setup_t;

/**
** @brief
**  网卡配置的基本信息
*/
typedef struct Roc_Net_Device_Cfg
{
    D_Char                  dev_name[ROC_MAX_NET_DEVICE_NAME];          /*!< 网卡名称，例如eth0*/
    D_Char                  description[ROC_MAX_NET_DEVICE_DESCRIBE];   /*!< 获取网卡描述信息，例如:"RealTek PCI GBE Family Controller"*/
    _NET_CONNECT_TYPE_e  connect_type;       /*!< 采用的网络连接类型*/
    D_U32                data_rate;          /*!< 网卡最大速率，单位为Kbps*/
    D_U8                 mac_addr[6];        /*!< 物理地址*/
    Roc_IP_Config_t         ip_cfg;             /*!< ip地址*/
}Roc_Net_Device_Cfg_t;

/*proxy模式*/
typedef enum _PROXY_Mode
{
    _PROXY_HTTP     = 0x00,   //使用http proxy
    _PROXY_HTTPS    = 0x01,   //使用https proxy
    _PROXY_FTP      = 0x02,   //使用ftp proxy
    _PROXY_NUM      = 0x03    //使用ftp proxy
}_PROXY_Mode_e;

//发送消息给webapp,type=1001为系统消息，type=1002为键盘，type=1003为鼠标，type=1004为通用遥控器，type=1005为 老人型遥控器，type=1006为儿童型遥控器，type值大于1006预留给扩展外设使用。
typedef struct SysNetworkEvent
{
    D_S32 msgtype;
    D_S32 msg;
    D_Char  modifiers[32];
}SysNetworkEvent_t;

typedef struct Roc_DHCPLeaseTime
{
    D_Char   leaseobtained[32];    //获取在DHCP模式下租用IP地址开始时间,yyyy-mm-dd hh:mm:ss
    D_Char   leaseexpires[32];     //获取在DHCP模式下IP地址的过期时间,yyyy-mm-dd hh:mm:ss
}Roc_DHCPLeaseTime_t;


typedef struct Roc_DHCP_Info
{
    D_Char   ipaddr[16];        //dhcp获取到的ip地址
    D_Char   mask[16];            //dhcp获取到的子网掩码
    D_Char   gateway[16];        //dhcp获取到的网管
    D_Char   dhcpserver[16];    //dhcp服务器的地址
    D_S16   dhcpport;          //dhcp服务器的端口号
    Roc_DHCPLeaseTime_t leasetime;
}Roc_DHCP_Info_t;

typedef struct Roc_Package_Info
{
    D_U32 sentpackages;         //获取网卡发送的数据包数量
    D_U32 receivedpackages;     //获取网卡接收到的数据包数量
}Roc_Package_Info_t;


/* proxy 服务器接入方式信息 */
typedef struct _PROXY_Config
{
    D_Char           devicename[ROC_MAX_ETH_NAME_LEN];
    D_U8          proxyenable;                //是否启用代理,数值型，取值如下：1表示当前代理立即生效，0表示当前代理无效，可读写
    _PROXY_Mode_e proxymode;                  //proxy类型
    D_Char           usrname[32];                //当前 proxy 服务器接入方式的用户名,取值为：0-30个字符，不可以是空格
    D_Char           password[32];               //当前 proxy 服务器接入方式的密码,取值为：0-30个字符，可以是空格
    D_Char           server[256];                //http代理服务器的 IP地址或者域名地址,不能超过 255 字节
    D_Char           unusedproxyurls[5][256];    //设置不使用代理的 URLs,不能超过 255 字节
    D_S32          port;                       //http代理服务的服务器端口号,取值为：0-5 个数字字符
}_PROXY_Config_t;

/*网卡配置的基本信息*/
typedef struct Roc_Device_Cfg
{
    D_Char                  devicename[ROC_MAX_ETH_NAME_LEN];          // 网卡名称,例如eth0
    D_Char                  description[128];        // 获取网卡描述信息，例如:"RealTek PCI GBE Family Controller
    _Connect_Type_e      connecttype;                // 采用的网络连接类型
    D_U32                datarate;                   // 网卡最大速率,单位为Kbps
    D_U8                 mac[6];                     // 物理地址
}Roc_Device_Cfg_t;

/*cable modem 联网状态*/
typedef enum Roc_Cable_Modem_Status
{
    _NET_CM_STATUS_OFFLINE       = 0,    // CABLE_MODEM离线
    _NET_CM_STATUS_ONLINE        = 1,    // CABLE_MODEM上线
    _NET_CM_STATUS_SCANNING      = 2     // CABLE_MODEM正在扫描频点
}Roc_Cable_Modem_Status_e;

/* CM信息*/
typedef struct Roc_Cable_Modem_Info
{
    D_Char                      hw_ver[128];    // 硬件版本
    D_Bool                    enable;         // 设备是否已经打开
    Roc_Cable_Modem_Status_e    state;             // CM状态
}Roc_Cable_Modem_Info_t;

/*无线网络连接状态*/
typedef enum _WIRELESS_STATUS
{
    _WIRELESS_STATUS_IDLE        = 0,    //设备空闲(未和任何AP连接)
    _WIRELESS_STATUS_CONNECTED   = 1,    // 连接成功
    _WIRELESS_STATUS_UNKOWN      = 2     // 未知状态
}_WIRELESS_STATUS_e;

/*IEEE 802.11标准*/
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

/*无线的工作模式*/
typedef enum _WIRELESS_MODE
{
    _WIRELESS_MODE_MANAGED       = 0,    // 控制模式
    _WIRELESS_MODE_AC_HOC        = 1,    // 对等模式
    _WIRELESS_MODE_REPEAT        = 2,    // 中继模式
    _WIRELESS_MODE_OTHER         = 3     // 其他模式
}_WIRELESS_MODE_e;

/* 无线认证方式*/
typedef enum Roc_Wireless_Auth_Alg
{
    _IW_AUTH_LEAP                = 0,    // 无认证
    _IW_AUTH_WEP_OPEN_SYSTEM     = 1,    // WEP开放系统身份验证
    _IW_AUTH_WEP_SHARED_KEY      = 2,    // WEP共享密钥身份验证
    _IW_AUTH_WPA_PSK             = 3,    // WPA预共用密钥模式，家庭及小型办公环境使用
    _IW_AUTH_WPA2_PSK            = 4,    // WPA2预共用密钥模式，家庭及小型办公环境使用
    _IW_AUTH_OTHER               = 5     // 其他认证方式
}Roc_Wireless_Auth_Alg_e;

/* 加密协议*/
typedef enum _WIRELESS_CIPHER
{
    _WIRELESS_CIPHER_NONE        = 0,    // 无加密协议
    _WIRELESS_CIPHER_WEP40       = 1,    // 64(40+24iv)位WEP加密协议
    _WIRELESS_CIPHER_WEP104      = 2,    // 128(104+24iv)位WEP加密协议
    _WIRELESS_CIPHER_WEP128      = 3,    // 152(128+24iv)位WEP加密协议
    _WIRELESS_CIPHER_TKIP        = 4,    // 暂时密钥集成协议,对应WPA/WPA2/WPA-PSK/WPA2-PSK使用
    _WIRELESS_CIPHER_AES         = 5,    // 高级加密标准,对应WPA/WPA2/WPA-PSK/WPA2-PSK使用
    _WIRELESS_CIPHER_OTHER       = 6     // 其他加密协议
}_WIRELESS_CIPHER_e;

/* WIFI连接参数*/
typedef struct _Wireless_Param
{
    D_Char                  essid[32];      //期望连接的AP的essid
    D_U8               bssid[6];// MAC地址
    D_S32                 key_len;       // 密钥长度,-1代表不需要密码连接
    D_S8                  key[128];      //密钥
    void                    *reserve;      // 预留，可扩展服务器验证参数
}_Wireless_Param_t;

/* WIFI AP信息*/
typedef struct _Wireless_AP_Info
{
    D_Char                          essid[32];                   // Extended Service Set Identifier 扩展服务单元标识符
    D_U8                         bssid[6];                   // Basic    Service Set Identifier,基本服务单元标识符,一般为MAC地址
    _WIRELESS_PROTOCOL_e         protocol;                   // 支持的ieee802.11协议
    _WIRELESS_MODE_e             wireless_mode;              // 工作模式
    D_U32                        bit_rate;                   // 网络速率,单位KHz
    D_U32                        freq;                       // 发射频率，以MHz为单位
    D_U8                         channel_num;                // 使用的连接通道值
    D_U8                         quality;                    //  link quality 信号质量,范围0到100
    D_U8                         signal;                     //  signal level (dBm) 信号强度 
    D_U8                         noise;                      //  noise  level (dBm) 干扰电平
    D_Bool                        privacy;                    // 是否为加密网络,privacy=ROC_TRUE为加密网络则wireless_alg,cipher有效
    D_Bool                        connected;              //
    Roc_Wireless_Auth_Alg_e         wireless_alg;               // 认证逻辑
    _WIRELESS_CIPHER_e           cipher;                     // 加密协议
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

/*DHCP模式*/
typedef enum DHCP_Mode
{
        ROC_STATIC     = 0x00,   /*中间件不使用DHCP*/
       ROC_DHCP   = 0x01,  /*中间件使用DHCP  */
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
    D_U8                         quality;                    //  link quality 信号质量,范围0到100
    D_U8                         signal;                     //  signal level (dBm) 信号强度 
    D_U8                         noise;                      //  noise  level (dBm) 干扰电平
}_net_cur_info_t;

/*--------------------------      函数定义     --------------------------*/


extern void my_system(char * cmd);

int d_timeserver_connect(void);

D_S32 d_get_wireless_password(D_Char* filename, D_Char *password);

/*******************************************************************************
功能说明: 
    网络监控回调函数格式, 回调函数要求立即返回。
   
参数说明:
    输入参数:
    [D_S32 type    ] 0
    [void *data      ] 消息的附加数据，类型为SysNetworkEvent_t，
                       SysNetworkEvent_t中的msg取消息的值
    [D_S32 data_len] 消息的长度
返回值:
    [D_S32] 0 成功；其他 错误码
*******************************************************************************/
typedef D_S32(*network_event_cbk)(D_S32 type, void* data, D_S32 data_len);

/*******************************************************************
功能：提供其他模块注册网络模块回调函数
输入参数：
    callback: 要注册的回调函数
输出参数：
    无
返回值：数值型，0  成功-1 失败
*/
D_S32 network_reg_cbk(network_event_cbk callback);

/*******************************************************************
功能：设置当前网络上提供网络时间服务器。可以是 IP 地址,也可以是域名。ntpserver 的作用是用来更新时间。
输入参数：
    ntpserver:字符串，不超过 255 字节
输出参数：
    无
返回值：数值型，0  成功-1 失败
备注：在调用 Network.save()后写 Flash
*/
D_S32 network_set_ntp_server(D_Char* ntpserver);

/*******************************************************************
功能：获取当前网络上提供网络时间服务器。可以是 IP 地址,也可以是域名。ntpserver 的作用是用来更新时间。
输入参数：
    bufflen :字符串最大长度
输出参数：
    ntpserver:字符串，不超过 255 字节
    bufflen :字符串实际长度
返回值：数值型，0  成功-1 失败
*/
D_S32 network_get_ntp_server(D_Char* ntpserver, D_U8* bufflen);

/*******************************************************************
功能：设置NTP同步间隔。
输入参数：
     interval:      NTP同步时间间隔，单位为秒
输出参数：
     无    
返回值：数值型， 0  成功-1 失败
*/
D_S32 network_set_ntp_interval(D_S32 interval);

/*******************************************************************
功能： 获取NTP同步间隔。
输入参数：
     无
输出参数：
     interval:      NTP同步时间间隔，单位为秒
返回值：数值型，0  成功-1 失败
*/
D_S32 network_get_ntp_interval(D_S32 *interval);

/*******************************************************************
功能： 设置NTP超时时间。
输入参数：
     timeout:       NTP时间同步超时时间，单位为秒
输出参数：
     无
返回值：数值型，0  成功-1 失败
*/
D_S32 network_set_ntp_timeout(D_S32 timeout);

/*******************************************************************
功能： 获取NTP超时时间。
输入参数：
     无
输出参数：
     timeout:       NTP时间同步超时时间，单位为秒
返回值：数值型，0  成功-1 失败
*/
D_S32 network_get_ntp_timeout(D_S32 *timeout);

/*******************************************************************
功能：同步 NTP 时间。 如果获取到消息 10521表示网络 NTP 时间同步成功；
获取到消息10522网络 NTP时间同步超时
输入参数：
    无
输出参数：
    无
返回值：数值型，0  成功-1 失败
备注：返回值只是表示程序是否开始执行 NTP 时间同步，并不表示实际的同步结果（实际的同步结果是由消息通知）。
    如返回 0，可能是因为没有设置NTPServer等
*/
D_S32 network_ntp_update();

/*******************************************************************
功能：设置网络对终端设备的一种识别字符串，即主机名
输入参数：
    hostname:字符串，不超过 255 字节，可读写
输出参数：
    无
返回值：数值型，0  成功-1 失败
备注：在调用 Network.save()后写 Flash
*/
D_S32 d_network_set_hostname(D_Char* hostname);

/*******************************************************************
功能：获取网络对终端设备的一种识别字符串，即主机名
输入参数：
    bufflen:字符串最大长度
输出参数：
    bufflen:字符串实际长度
    hostname:字符串，不超过 255 字节，可读写
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_get_hostname(D_Char* hostname, int bufflen);


/*******************************************************************
功能： 获取某个网卡的信息。
输入参数：
      devicename : 设备名称    
输出参数：
     devicecfg:       网卡配置信息。由中间件确保此值不为NULL。
返回值：数值型， 0  成功-1 失败
*/
D_S32 d_network_get_device_info(D_Char* devicename, Roc_Device_Cfg_t* devicecfg);

/*******************************************************************
功能：实现普通电脑上 ping 的功能。
输入参数：
        address：字符串，ping 的网络地址,IP 或者域名地址。 
        parameter：字符串，ping的参数，目前可只实现"-t"选项,其他值按无参数。 -t：连续地 ping 一个地址，直到手动停止.
        timeout:超时时间 ，单位ms
输出参数：
        无
返回值：数值型，0  成功-1 失败
备注：每个包响应或超时都返回消息，但不发最后的统计消息。
*/
D_S32 d_network_ping(D_Char* address, D_Char* parameter, D_S32 timeout);

/*******************************************************************
功能：收到 ROC_SYSEVENT_PING_RESPONSE 消息后获取 ping的响应字符串。
输入参数：
        bufflen：表示获取response分配内存长度
输出参数：
        pingresponsebuffer：字符串，用于获取ping的响应字符串
        bufflen:实际长度
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_get_ping_response(D_Char* pingresponsebuffer, D_U8* bufflen);

/*******************************************************************
功能：取消正在进行的 ping 操作。
输入参数：
    无
输入参数：
    无
返回值：数值型，0代表停止了正在执行的 ping 操作，-1代表当前 ping 操作已经结束或当前无 ping操作.
*/
D_S32 d_network_cancel_ping();

/*******************************************************************
功能：获取设备状态
输入参数：
        devicename：网卡名称；
输出参数：
    devicestate: 数值型，参考值如下:    
        0    设备不存在，不可访问
        1    设备存在，但无法获取状态
        101    网线连接
        102    网线脱落
        201    网络连接正常
        202    网络连接中断
        203    网络状态不改变，但是不良
        204    CableModem与STB通信中断
        205    CableModem与STB通信中断，重新上线
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_get_device_state(D_Char* devicename, D_S32* devicestate);

/*******************************************************************
功能：获取当前网络终端设备的IP对象，包括IP地址、子网掩码、网关。
输入参数：
        devicename：网卡名称；  
输出参数：
    ipinfo：请参考Roc_IP_Config_t具体定义。
返回值：数值型，0  成功-1 失败
说明: Roc_IP_Config_t的index传0，获取的是真实ip，支持3个虚拟ip，例如devicename是eth0，传1、2、3分别获取eth0:1,eth0:2,eth0:3
*/
D_S32 d_network_get_ip(D_Char* devicename, Roc_IP_Config_t* ipinfo);

/*******************************************************************
功能：设置当前网络终端设备的IP对象，包括IP地址、子网掩码、网关。
参数说明：
    devicename：网卡名称；
    ipinfo：请参考Roc_IP_Config_t具体定义。
输出参数：
    无
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_set_ip(D_Char* devicename, Roc_IP_Config_t* ipinfo);

/*******************************************************************
功能：获取网卡接收和发送包的信息
输入参数：
      devicename：设备名称，如eth0
输出参数:
    packages: 网卡发送和接收包的信息，详见Roc_Package_Info_t定义
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_get_packeages(D_Char* devicename, Roc_Package_Info_t *packages);

/*******************************************************************
功能：设置网卡的通信方式
输入参数：
       devicename：设备名称，如eth0 
    communicateway: 网卡的通信方式，可以是如下值"adapting"、"10M_fullDuplex"、"10M_halfDuplex"、"100M_fullDuplex"、"100M_halfDuplex"
输出参数:
    无
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_set_commute_way(D_Char* devicename, D_Char* communicateway);

/*******************************************************************
功能：获取网卡的通信方式
输入参数：
       devicename：设备名称，如eth0 
输出参数:
    communicateway: 网卡的通信方式，可以是如下值"adapting"、"10M_fullDuplex"、"10M_halfDuplex"、"100M_fullDuplex"、"100M_halfDuplex"
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_get_commute_way(D_Char* devicename, D_Char* communicateway);

/*******************************************************************
功能：获取当前的连接类型，取值范围："ethernet"、"ppp"或"pppoe"
输入参数：
    devicename：设备名称，如eth0
输出参数:
      connectiontype:字符串
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_get_connection_type(D_Char* devicename, D_Char* connectiontype);

/*******************************************************************
功能：设置DHCP模式是否自动获取DNS ，并不立即去执行获取DNS动作
输入参数：
    devicename：设备名称，如eth0
    autodns: 1表示自动获取DNS，0表示手动获取
输出参数:
       无
返回值：数值型，0  成功-1 失败
*/
D_S32 _set_dns_auto(D_Char* devicename, D_Bool autodns);

/*******************************************************************
功能：获取DHCP模式是否自动获取DNS 
输入参数：
    devicename：设备名称，如eth0    
输出参数:
       autodns: 1表示自动获取DNS，0表示手动获取
返回值：数值型，0  成功-1 失败
*/
D_S32 _get_dns_auto(D_Char* devicename, D_Bool *autodns);

/*******************************************************************
功能：设置DNS服务器信息
输入参数：
    devicename：设备名称，如eth0    
    index: DNS服务器索引，最多可设置三个DNS服务器
    dnsserver: DNS服务器地址     
输出参数:
       无
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_set_dnsserver(D_Char* devicename, D_Char *dnsserver);

/*******************************************************************
功能：获取DNS服务器信息
输入参数：
    devicename：设备名称，如eth0    
    index: DNS服务器索引，最多可设置三个DNS服务器
输出参数:
       dnsserver: DNS服务器地址     
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_get_dnsserver(D_Char* devicename, D_Char *dnsserver);

/**********************************************************************************
功能：
    设置底层网络的 DHCP 工作方式，dhcp 为网络的 DHCP 工作方式，0: 表示不采用 DHCP，1: 表示采用 DHCP， 其他值无效，直接返回0。
输入参数：
    devicename：设备名称，如eth0
    dhcpmode:  网络的 DHCP 工作方式代码
输出参数：
    无    
返回值：0  成功-1 失败
*/
D_S32 d_network_set_dhcp_mode(D_Char *devicename, Roc_DHCP_Mode_e dhcpmode,  D_Bool sync);

/**********************************************************************************
功能说明：
    获取当前网络的 DHCP 工作方式代码，0: 表示不采用 DHCP，1: 表示采用 DHCP。
输入参数：
    devicename：设备名称，如eth0
输出参数：
    dhcpmode : 是否启用DHCP
返回值：0  成功-1 失败
*/
D_S32 d_network_get_dhcp_status(D_Char *devicename, D_Bool *dhcp_status);

/**********************************
功能说明：
    获取DHCP动态分配的DHCP相关信息
输入参数：
    devicename 网卡名称
输出参数：
    dhcp的信息，详见Roc_DHCP_Info_t结构体   
返    回：数值型，0  成功-1 失败
**********************************/
D_S32 dg_network_get_dhcp_info(D_Char* devicename, Roc_DHCP_Info_t *pdhcpip);

/**********************************
@brief 取得设备的ip 地址、掩码、网关
* @param devicename   设备名
* @param ipinfo   信息结构
* @return 返回结果
**********************************/
D_S32 d_network_get_ip_gateway(D_Char* devicename, Roc_IP_Config_t* ipinfo);

/*******************************************************************
功能： 获取ethernet模式的连接状态
输入参数：
        devicename：设备名称，如eth0
输出参数:
        status: 1表示已经连接上，0表示没有连接上
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_get_lan_status(const D_Char *devicename, D_Bool *status);

/*******************************************************************
功能： 设置网卡是否禁用
输入参数：
        devicename：设备名称，如eth0
        enable: 1表示可用，0表示不可用
输出参数:
        无   
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_set_eth_enable(const D_Char *devicename, D_Bool enable);

/*******************************************************************
功能： 获取网卡是否禁用
输入参数：
        devicename：设备名称，如eth0  
输出参数:
        enable: 1表示可用，0表示不可用
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_get_eth_enable(const D_Char *devicename, D_Bool *enable);

/*******************************************************************
功能：将网卡设置的所有属性一次性设置给底层，所有属性包括 ethernet对象下的所有相关属性都可以进行设置。
    其功能类似 PC上网络设置的确认按钮的功能。
输入参数：
        devicename：网卡名称；
输出参数：
    无   
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_submit_parameters(D_Char* devicename);

/*******************************************************************

功能说明：
   获取Cable Modem的信息。
输入参数：
        无
输出参数：
        cminfo:          是否连接上。有中间件确保此指针不为NULL。    
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_cable_modem_info(Roc_Cable_Modem_Info_t *cminfo);

/*******************************************************************

功能说明：
  若启用了Cable Modem连接，查询Cable Modem的连接状态。
输入参数：
        无
输出参数：
        state: Cable Modem的状态。由中间件确保此指针不为NULL。
返回值：数值型，0  成功-1 失败
*/
D_S32 d_network_cable_modem_status(Roc_Cable_Modem_Status_e *state);

/*******************************************************************

功能说明：
     扫描无线网络，超时表示一个AP都没有搜到。
 输入参数：
        devicename     网卡名称。由中间件确保此指针不为NULL。
        timeout     超时时间,单位ms。
        num       ap_info的最大返回个数。由中间件确保此指针不为NULL。且ap_num为正值。
输出参数：
        apinfo      可以获取到的AP信息数组,内存由中间件分配。由中间件确保此指针不为NULL。
        num       获取到的AP信息数组的实际有效长度。由中间件确保此指针不为NULL。
返回值：ROC_NET_RET_SUCCESS   成功
             ROC_NET_RET_TIMEOUT   网络超时
             ROC_NET_RET_FAILED    网络失败
*/
D_S32 d_wireless_scan(D_Char* devicename, D_S32 timeout, _Wireless_AP_Info_t *apinfo, D_S32 *ap_num);

/*******************************************************************

功能说明：
    连接指定的AP,密码只支持16进制。
输入参数：
        devicename     网卡名称。由中间件确保此指针不为NULL。
        param         连接参数。
输出参数：
    无
返回值：ROC_NET_RET_SUCCESS   成功
             ROC_NET_RET_TIMEOUT   网络超时
             ROC_NET_RET_FAILED    网络失败
*/
D_S32 _wireless_scan( D_Char* devicename, D_S32 timeout, _Wireless_AP_Info_t *apinfo, D_S32 *ap_num);

/*******************************************************************
功能：断开与AP的连接
输入参数：
        devicename：网卡名称
输出参数：
        无
返回值：数值型，0  成功-1 失败
*/
D_S32 d_wireless_disconnect(D_Char* devicename);

/*******************************************************************
功能：获取当前连接的状态。
输入参数：
         devicename     网卡名称。由中间件确保此指针不为NULL。
输出参数：
         status :      当前连接状态。由中间件确保此指针不为NULL。
返回值：数值型，0  成功-1 失败
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

/** @brief 取得当前连接的wifi信号信息
* @param devicename   设备名
* @param info   信息结构
* @return 返回结果
*/
extern D_S32 d_network_get_curr_info(D_Char* devicename, _net_cur_info_t* info);

extern D_Bool d_wireless_is_connecting(void);

#ifdef __cplusplus
}
#endif

#endif

