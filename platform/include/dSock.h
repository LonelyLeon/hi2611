/** @file
* @brief 网络套接字定义
* @author 李臣
* @date 2014-05-05 李臣: 建立文件
*/
#ifndef __D_SOCK_H
#define __D_SOCK_H

#include "dTypes.h"

#ifdef  __cplusplus
extern "C"
{
#endif

typedef enum
{
    D_SockNetIf_Ether = 0,
    D_SockNetif_PPPoE,
    D_SockNetIf_Other,
}D_SockNetIfType;

typedef struct
{
    const D_Char *name; /**< 适配器接口名称, 4个字符 */
    union
    {
        D_ID netend_id;  /**< 物理网卡id */
        D_ID netif_index;  /**< PPPoE绑定适配器索引 */
    }medium;
    D_SockNetIfType type; /**< 适配器类型 */
    D_U32 ipaddr;  /**< 适配器ip */
    D_U32 mask;  /**< 适配器子网掩码 */
    D_U32 gateway;  /**< 适配器默认网关 */
    D_U8 mac[6];  /**< 适配器mac地址 */
    const D_Char *pppoe_user;  /**< PPPoE拨号用户名 */
    const D_Char *pppoe_password;  /**< PPPoE拨号密码 */
}D_SockNetIfAttr;

#define D_SNIC_GET_NAME         0x00000001
#define D_SNIC_GET_TYPE         0x00000002
#define D_SNIC_GET_IP           0x00000004
#define D_SNIC_GET_NETMASK      0x00000008
#define D_SNIC_GET_GATEWAY      0x00000010
#define D_SNIC_GET_STATUS       0x00000020
#define D_SNIC_GET_IF_HANDLE    0x00000040
#define D_SNIC_GET_MAC          0x00000080
#define D_SNIC_GET_ALL          (D_SNIC_GET_NAME | D_SNIC_GET_TYPE | D_SNIC_GET_IP | D_SNIC_GET_NETMASK \
    | D_SNIC_GET_GATEWAY | D_SNIC_GET_STATUS | D_SNIC_GET_IF_HANDLE | D_SNIC_GET_MAC)

#define D_SNIC_SET_IP           0x00010000
#define D_SNIC_SET_NETMASK      0x00020000
#define D_SNIC_SET_GATEWAY      0x00040000
#define D_SNIC_SET_STATUS       0x00080000
#define D_SNIC_SET_MAC          0x00100000
#define D_SNIC_SET_ALL          (D_SNIC_SET_IP | D_SNIC_SET_NETMASK | D_SNIC_SET_GATEWAY | D_SNIC_SET_STATUS \
    | D_SNIC_SET_MAC)

#define D_SNIC_ALL              (D_SNIC_GET_ALL | D_SNIC_SET_ALL)

#define D_SNIS_DOWN             0x00000000
#define D_SNIS_UP               0x00000001

typedef struct
{
    D_U32 cmd;  /**< 命令掩码, 可组合值 */
    const D_Char *name;
    D_SockNetIfType type;
    D_U32 ipaddr;
    D_U32 netmask;
    D_U32 gateway;
    D_U32 status;
    D_Handle if_handle;
    D_U8 mac[6];
}D_SockNetIfInfo;

D_Result d_sock_open(void) D_FUNCPOSTFIT;

D_Result d_sock_close(void) D_FUNCPOSTFIT;

D_ID d_sock_netif_create(D_SockNetIfAttr *attr) D_FUNCPOSTFIT;

D_Result d_sock_netif_destroy(D_ID netif_index) D_FUNCPOSTFIT;

D_Result d_sock_netif_cmd(D_ID netif_index, D_SockNetIfInfo *info) D_FUNCPOSTFIT;

D_Result d_sock_netif_dhcp_start(D_ID netif_index) D_FUNCPOSTFIT;

D_Result d_sock_netif_dhcp_stop(D_ID netif_index) D_FUNCPOSTFIT;

D_Result d_sock_set_dns(D_U32 dns1, D_U32 dns2) D_FUNCPOSTFIT;

D_Result d_sock_get_dns(D_U32 *dns1, D_U32 *dns2) D_FUNCPOSTFIT;

/* 套接字api按照BSD标准定义 */
#ifdef D_AUX_SUPPORT_LWIP
#   if !defined(D_SYSTEM_HROS) && !defined(D_SYSTEM_WIN32)
#       error "Target OS not support LWIP! Please select 'n'."
#   endif
#   ifndef __SOCKETS_DEF_INTERNAL
#       include "sock/sockets.h"
#   endif
#else
#   if defined(D_SYSTEM_WIN32)
#       include <windows.h>
#       include <winsock.h>
#   elif defined(D_SYSTEM_LINUX)
#       include <errno.h>
#       include <sys/types.h>
#       include <sys/socket.h>
#       include <netinet/in.h>
#       include <arpa/inet.h>
#       include <netdb.h>
#       define closesocket close
#       define ioctlsocket ioctl
#   endif
#endif

#ifdef  __cplusplus
}
#endif
#endif

