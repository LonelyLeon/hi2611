/*
   Copyright (C), SUMAVISION SOFTWARE TECHNOLOGIES CO.,LTD.
   -------------------------------------------------------------------------------
File Name     : network.c
Version       : 1.0
Author        : SMSX-Dept-10&12
Created       : 2012-05-21
History       :
 * Version   Date         Author      Description
 * 1         2012-10-15   dsm         Create this file.
 -------------------------------------------------------------------------------
 */

#ifndef __NETWORK_C__
#define __NETWORK_C__

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <linux/if.h>
#include <linux/route.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <net/if_arp.h>
#include <netinet/ether.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
//#include <glib.h>
#include <asm/types.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <unistd.h>
#include <resolv.h>
#include <math.h>
#include <string.h>
#include <ifaddrs.h>
#include <linux/wireless.h>

//#include "osp.h"
//#include "base.h"
//#include "setting.h"
//#include <service/service.h>
#include <pthread.h>
#include <sys/syscall.h>

#include "dNetwork.h"
#include "dDebug.h"
#include "dMutex.h"
#include "dMem.h"
#include "dSem.h"
#include "dEvent.h"
#include "dTask.h"
#include "dSys.h"
#include "_helper.h"

#define _INFO_ "[network]info: "
#define _ERRO_ "[network]error: "
#define _WARN_ "[network]warn: "


#define hi_eprintf D_DUMP
#define porting_print(_i_,_x_) { D_DUMP(_i_); D_DUMP _x_ ;}
#define net_sleep_ms d_task_wait
#define NET_MEMALLOC(_s) d_mem_alloc(0, _s)
#define NET_MEMREALLOC(_p,_s) d_mem_realloc(0, _p, _s)
#define NET_MEMFREE(_p) if(_p){d_mem_free (_p); _p = NULL;}

/* 根据flash规划，如果WIFI_CFG  NETWORK_SETTING_FILE 是临时文件系统里时，断电不保存
 此时将这些信息保存在数据库里，开机后再生成临时文件*/
#define  SAVE_CONFIG_IN_SYS_DBASE (1)
#if SAVE_CONFIG_IN_SYS_DBASE
#include "ptvConfig.h"
#endif

#define WIFI_8188EU			0
#define WIFI_8188FU			1

#define ENABLE_WIFI_TYPE		WIFI_8188FU//WIFI_8188EU//

#define USE_SHELL_CMD

#ifdef USE_SHELL_CMD
#define ETHERNET_TMP_DIR "/tmp/"
#define WIFI_CFG "/tmp/network/wifi_cfg"
#define WPA_TMP_FILE "/tmp/wpa_tmp"
#define NETWORK_SETTING_FILE "/tmp/network/setting"
#define SOCKET_WPA "/var/run/wpa_supplicant"
#endif

extern int net_state;
//extern gboolean _check_state_cb(gpointer data);
char wifi_dev[8] = {0};

//char * if_indextoname(unsigned int ifindex, char * ifname); //此函数声明在<net/if.h>中，但是如果包含此头文件会和<linux/if.h>冲突

//wifi插入标识
//extern int g_wifi_flag;
int g_wifi_flag = 0;

/*------------------------     宏\枚举\结构体定义     ------------------------*/
//开启此宏，确保ip不会改变，解决nfs挂载调试时ip改变导致连接中断
//#define _NET_INVALID__          0


//#define _NET_DEVICE_NUM         2
#define _NET_DEVICE_MAX_NUM        5     // 2  (2太小，usb网卡调试时有时找不到设备)
D_S32 _NET_DEVICE_NUM = 0;

#define _NET_RESOLV_CFG         "/etc/resolv.conf"
#define _NET_ROUTE_PATH         "/proc/net/route"
#define _NET_DEV_PATH           "/proc/net/dev"
#define _NET_DHCP_INFO_CFG      "/tmp/dhcp_info.cfg"
#define _NET_HOST_NAME      "/etc/hostname"


#define _DEF_NET0_NAME          "eth0"
#define _DEF_NET0_DESC          "RealTek-rtl8201cp"
#define _DEF_NET0_RATE          100*1024

#define _WIF_NET0_NAME          "wlan0"
#define _WIF_NET0_DESC          "Ralink-rt2870"
#define _WIF_NET0_RATE          54*1024

#define _PPP_NET0_NAME          "ppp0"

#define NETWORK_LOCK()      do{if(D_INVALID_HANDLE!=s_net_mtx)d_mutex_lock(s_net_mtx);}while(0);
#define NETWORK_UNLOCK()    do{if(D_INVALID_HANDLE!=s_net_mtx)d_mutex_unlock(s_net_mtx);}while(0);

#if 0
typedef struct service_interface
{
    GHashTable *services;
    _net_cfg_t  *net_setting_last;
} service_interface_t;
#endif
struct route_info
{
    u_int dstAddr;
    u_int srcAddr;
    u_int gateWay;
//    char ifName[IF_NAMESIZE];
    char ifName[64];
};
/*---------------------------  Private Variable   ---------------------------*/
//static UINT32_T         s_net_mtx   = 0;
static D_HMutex s_net_mtx   = D_INVALID_HANDLE;
static D_HSem hsem_test_net = D_INVALID_HANDLE;
static _net_manage_t    *s_net_man  = NULL;
static _net_cfg_t  *net_setting_last = NULL;
static _net_cfg_t  *net_setting_file_info = NULL;
static D_HTask htask_net_start = D_INVALID_HANDLE;
static D_Bool   connect_task_break_flag = D_FALSE;
//static unsigned int     s_dns[3];
static D_Char *     s_dns[3];
static D_Char cur_wifiname[32] = {0};
static D_Bool   wifi_connect_ing = D_FALSE;
/***************ping*************/
//static D_MUTEX_T         ping_list_lock;
pthread_t tid_net_timeserver = 0;

#define BUFSIZE 8192

static void _network_test_communicate_sync(void);

unsigned char HexChar2Hex(char hexch)
{
    unsigned char ch = 0;

    if('a' <= hexch && hexch <= 'F') ch = 0x0a + (hexch - 'a');
    else if('A' <= hexch && hexch <= 'F') ch = 0x0a + (hexch - 'A');
    else if('0' <= hexch && hexch <= '9') ch = 0x00 + (hexch - '0');
    return ch;
}

int convert_hexstr_to_bytestr(char* hexstr, int hexlen, char* bytestr, int byte_len)
{
    int i = 0, idx = 0, off;
    int ch;

    bytestr[0] = '\0';
    while(i < hexlen)
    {
        ch = 0xFFFF;
        if(hexstr[i] == '\\')
        {
            off = 1;
            if((i + 1) < hexlen && hexstr[i+1] == 'x')
            {
                off = 2;
                if((i + 2) < hexlen)
                {
                    ch = HexChar2Hex(hexstr[i+2]);
                    off = 3;
                }
                if((i + 3) < hexlen)
                {
                    ch = (ch << 4) + HexChar2Hex(hexstr[i+3]);
                    off = 4;
                }
            }
            i += off;
        }
        else
        {
            ch = hexstr[i];
            i += 1;
        }

        if(idx < byte_len && ch != 0xFFFF)
            bytestr[idx++] = (char)ch;
    }
 
    return idx;
}


//#define MAKE_WIFI_FILENAME(_filename, _essid, _bssid) {sprintf(_filename, "%s_%02X%02X%02X%02X%02X%02X", (_essid[0] ? _essid : "NULL"), _bssid[0], _bssid[1], _bssid[2], _bssid[3], _bssid[4], _bssid[5]);}
void MAKE_WIFI_FILENAME(char*_filename, char* _essid, unsigned char *_bssid)
{
    int i, idx = 0;
    char name[66] = {0}, ch;

    for(i = 0; i < 32; i++)
    {
        if(_essid[i] == '\0')
        {
            break;
        }
        
        if(_essid[i] == '_' || _essid[i] == '-' || isdigit(_essid[i]) || isalpha(_essid[i]))
        {
            name[idx++] = _essid[i];
        }
        else
        {
            ch = 0x0f & (_essid[i]  >> 4);
            ch = (ch >= 0x0a) ? ('A' + (ch - 0x0a)) : ('0' + ch);
            name[idx++] = ch;
            ch = 0x0f & _essid[i] ;
            ch = (ch >= 0x0a) ? ('A' + (ch - 0x0a)) : ('0' + ch);
            name[idx++] = ch;
        }
    }

    sprintf(_filename, "%s_%02X%02X%02X%02X%02X%02X", (idx ? name : "NULL"), _bssid[0], _bssid[1], _bssid[2], _bssid[3], _bssid[4], _bssid[5]);
}

/**
* 函数 my_system
* my_system 函数代替系统函数 system，关闭除标准输入、标准输出、标准错误以外的所有文件描述符，解决tunner初始化错误
* 参数 cmd 要执行的命令
*/
void my_system(char * cmd)
{
    pid_t pid = vfork();
    if (pid < 0)
    {
        printf("fork error %d\n", pid);
        return;
    }
    else if (pid == 0)
    {
#if 0  // vfork 时用if 0
        int i = 0;
        for (i = 0; i < sysconf(_SC_OPEN_MAX); i++)
        {
            if (i != STDIN_FILENO && i != STDOUT_FILENO && i != STDERR_FILENO)
                close(i);
        }
#endif
        execl("/bin/sh", "/bin/sh", "-c", cmd, NULL);
        _exit(127); //子进程正常执行则不会执行此语句
    }
    else
    {
        int status = 0;
        pid_t wpid = wait(&status);
        printf("recvie child signal: [%d]\n", wpid);
    }
}

/** @brief 粗略使用str的长度判断要设置的IP地址是否是有效
  */
D_Bool d_ipv4_addr_check(char * str)
{
    D_Bool ret = D_FALSE;
    struct in_addr dest;

    if(strlen(str))
    {
        if (inet_pton(AF_INET, str, &dest) > 0)
        {
            ret = D_TRUE;
        }
    }
    return ret;
}

/** @brief  查找网络设备序号*/
static  int __inline__ _find_deviece_id(char *devicename)
{
    int i;

    if(devicename)
    {
        for(i = 0; i < _NET_DEVICE_NUM; i++)
        {
            if( 0 == strcmp(s_net_man[i].name, devicename) )
            {
                return i;
            }
        }
    }
    return -1;
}

/* 判断进程是否在运行*/
static int _check_process_running(D_Char * process_name)
{
    int ret = 0;
    FILE * pfile = NULL;
    char cmd_buf[128] = {0,};
    char read_buf[1024];

    sprintf(cmd_buf, "ps ax | grep \"%s\" | grep -v grep", process_name);
    pfile = popen(cmd_buf, "r");
    if(pfile != NULL)
    {
        while(fgets(read_buf, sizeof(read_buf), pfile) != NULL)
        {
            //printf("%s\n", read_buf);
            if(strstr(read_buf, process_name) != NULL)
            {
                ret = 1;
            }
        }
        pclose(pfile);
    }

    return ret;
}

/**
* 函数 _get_ifi_info
*
* 通过读取文件/proc/net/dev获取网络设备
* 返回值 正确返回 0; 错误返回 -1
*/
static int _get_all_devices_info(void)
{
    char line[256];
    FILE *fd;
    char *str;
    int i = 0, j = 0;
    int error = 0;
    int sockfd = -1, flags;
    struct ifreq  ifr;

    NETWORK_LOCK();

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    fd = fopen(_NET_DEV_PATH, "r");
    if( NULL == fd )
    {
        printf("not found %s \n", _NET_DEV_PATH);
        error = -1;
    }
    else
    {
        while(fgets(line, sizeof(line), fd) != NULL)
        {
            memset(s_net_man[i].name, 0, sizeof(s_net_man[i].name));
            if((str = strstr(line, "eth")) != NULL)
            {
                strcpy(s_net_man[i].name, "eth");
                j = 3;
                str += 3;
            }
            else if((str = strstr(line, "wlan")) != NULL)
            {
                strcpy(s_net_man[i].name, "wlan");
                j = 4;
                str += 4;
            }
            else
            {
                continue;
            }

            while(*str != ':')
            {
                s_net_man[i].name[j] = *str;
                str++;
                j++;
            }

            if(strncmp(s_net_man[i].name, "wlan", 4) == 0)
            {
                memset(wifi_dev, 0, sizeof(wifi_dev));
                strcpy(wifi_dev, s_net_man[i].name);
                //  MSG("wifi_dev:%s\n", wifi_dev);
            }

            s_net_man[i].support    = 1;
            s_net_man[i].dhcp_flag  = 0;
            s_net_man[i].data_rate  = _DEF_NET0_RATE;

            memset(&ifr, 0, sizeof(ifr));
            strcpy(ifr.ifr_name, s_net_man[i].name);
            ioctl(sockfd, SIOCGIFFLAGS, &ifr);
            flags = ifr.ifr_flags;
            if((flags & IFF_UP) == 0)
                s_net_man[i].enable = 0;
            else
                s_net_man[i].enable = 1;

            hi_eprintf("------net name=%s enable=%d --------\n", s_net_man[i].name, s_net_man[i].enable);
            if(++i >= _NET_DEVICE_MAX_NUM)
            {
                break;
            }
        }
    }

    _NET_DEVICE_NUM = i;
    if(NULL != fd )
    fclose(fd);
    if(sockfd >= 0)
        close(sockfd);

    NETWORK_UNLOCK();

    return error;
}

static D_S32 _parsing_network_setting(void)
{
    D_Char line[256];
    FILE *fd;
    int i = 0;
    D_S32 error = -1;
    D_Char *token;

    fd = fopen(NETWORK_SETTING_FILE, "r");
    if( NULL == fd )
    {
        printf("fopen %s failed \n", NETWORK_SETTING_FILE);
        error = -1;
        return -1;
    }

    while(fgets(line, sizeof(line), fd) != NULL)
    {
        token = strchr(line, ':');
        if(token)
        {
            while(*token  == ':')
                token++;
            D_S32 len;
            len = strlen(token);
            if(token[len - 1] == '\n')
                token[len - 1] = '\0';
            switch(i)
            {
                case 0:
                    net_setting_last->type = atoi(token);
                    break;
                case 1:
                    strcpy(net_setting_last->devicename, token);
                    break;
                case 2:
                    net_setting_last->connected = atoi(token);
                    break;
                case 3:
                    net_setting_last->method = atoi(token);
                    break;
                case 4:
                    strcpy(net_setting_last->name, token);
                    break;
                case 5:
                    for(i = 0; i < 6; ++i)
                    {
                        net_setting_last->bssid[i] = strtoul(token, NULL, 16);
                        token += 3;
                    }
                    break;
                case 6:
                    strcpy(net_setting_last->ip, token);
                    break;
                case 7:
                    strcpy(net_setting_last->gateway, token);
                    break;
                case 8:
                    strcpy(net_setting_last->mask, token);
                    break;
                case 9:
                    strcpy(net_setting_last->dns, token);
                    error = 0;
                    return error;
                default:
                    break;
            }
            i++;
        }
        else
        {
            error = -1;
        }
    }
    fclose(fd);
    return error;
}

/**
* 函数 _set_network_attribute
* 向网络的配置文件中写入信息
*/
static void _set_network_attribute(D_U32 reget_ip_num, D_Bool force_save)
{
    Roc_IP_Config_t ipinfo;
    FILE *fp = NULL;
    int error = 0;
    int save_flag = D_FALSE;
    char cmd_buf[1024] = {0,};
    char bssid[24] = {0,};

    if(reget_ip_num)
    {
        while(reget_ip_num > 0)
        {
            memset(&ipinfo, 0, sizeof(ipinfo));
            if(0 == d_network_get_ip_gateway(net_setting_last->devicename, &ipinfo))
            {
                break;
            }
            net_sleep_ms(200);
            reget_ip_num--;
        }
        d_network_get_dnsserver(net_setting_last->devicename, ipinfo.dns);
        strcpy(net_setting_last->ip, ipinfo.ipaddr);
        strcpy(net_setting_last->mask, ipinfo.mask);
        strcpy(net_setting_last->gateway, ipinfo.gateway);
        strcpy(net_setting_last->dns, ipinfo.dns);
    }

    if(force_save)
    {
        save_flag = D_TRUE;
    }
    else
    {
        if(net_setting_last->type != net_setting_file_info->type \
           || net_setting_last->connected != net_setting_file_info->connected \
           || net_setting_last->method != net_setting_file_info->method \
           || (strcmp(net_setting_last->devicename, net_setting_file_info->devicename) != 0) \
           || (strcmp(net_setting_last->name, net_setting_file_info->name) != 0) \
           || (memcmp(net_setting_last->bssid, net_setting_file_info->bssid, sizeof(net_setting_last->bssid)) != 0) \
           || (strcmp(net_setting_last->ip, net_setting_file_info->ip) != 0) \
           || (strcmp(net_setting_last->mask, net_setting_file_info->mask) != 0) \
           || (strcmp(net_setting_last->gateway, net_setting_file_info->gateway) != 0) \
           || (strcmp(net_setting_last->dns, net_setting_file_info->dns) != 0) )
        {
            save_flag = D_TRUE;
        }
    }

    /* 有变化才保存*/
    if(save_flag == D_TRUE)
    {
        fp = fopen(NETWORK_SETTING_FILE, "w+");
        if(fp == NULL)
        {
            hi_eprintf("Open file %s failed!\n", NETWORK_SETTING_FILE);
            error = -1;
            return ;
        }
        if(net_setting_last->type == _NET_CONNECT_TYPE_WIRED)
            strcpy(net_setting_last->name, "NONE");
        memset(cmd_buf, 0, sizeof(cmd_buf));
        sprintf(bssid, "%02X:%02X:%02X:%02X:%02X:%02X", net_setting_last->bssid[0], net_setting_last->bssid[1], net_setting_last->bssid[2], net_setting_last->bssid[3], net_setting_last->bssid[4], net_setting_last->bssid[5]);
        sprintf(cmd_buf, "type:%d\ndevicename:%s\nconnected:%d\nmethod:%d\nname:%s\nbssid:%s\nip:%s\ngateway:%s\nmask:%s\ndns:%s\n",
                net_setting_last->type, net_setting_last->devicename,
                net_setting_last->connected, net_setting_last->method,
                net_setting_last->name, bssid, net_setting_last->ip,
                net_setting_last->gateway, net_setting_last->mask,
                net_setting_last->dns);
        //printf("********%s******:\n%s\n", NETWORK_SETTING_FILE, cmd_buf);
        fprintf(fp, "%s", cmd_buf);
        fclose(fp);
        fp = NULL;
#if SAVE_CONFIG_IN_SYS_DBASE
        {
            D_NetWorkSettingDat set_param;

            memset(&set_param, 0x00, sizeof(set_param));
            set_param.type = (D_U8)net_setting_last->type;
            //set_param.connected = (D_U8)net_setting_last->connected;
            set_param.method = (D_U8)net_setting_last->method;
            if(net_setting_last->method == ROC_STATIC)
            {
                set_param.ipaddr = (D_U32)inet_addr(net_setting_last->ip);
                set_param.mask = (D_U32)inet_addr(net_setting_last->mask);
                set_param.gateway = (D_U32)inet_addr(net_setting_last->gateway);
                set_param.dns = (D_U32)inet_addr(net_setting_last->dns);
            }
            sprintf(set_param.devicename, "%s", net_setting_last->devicename);
            sprintf(set_param.name, "%s", net_setting_last->name);
            memcpy(set_param.bssid, net_setting_last->bssid, sizeof(set_param.bssid));
            p_tvconf_set_network_setting_param(&set_param);
        }
#endif
    }
    memcpy(net_setting_file_info, net_setting_last, sizeof(_net_cfg_t));
}

/**
* 函数 _get_network_attribute
* 读取网络的配置文件
*/
static void _get_network_attribute(void)
{
    FILE *fp = NULL;
    int error = 0;
    char cmd_buf[1024] = {0,};

    if(access(NETWORK_SETTING_FILE, F_OK) != 0)
    {
        fp = fopen(NETWORK_SETTING_FILE, "w+");
        if(fp == NULL)
        {
            hi_eprintf("Open file %s failed!\n", NETWORK_SETTING_FILE);
            error = -1;
            return ;
        }
        memset(cmd_buf, 0, sizeof(cmd_buf));
        fprintf(fp, "type:%d\ndevicename:%s\nconnected:%d\nmethod:%d\nname:%s\nbssid:00:00:00:00:00:00\nip:%s\ngateway:%s\nmask:%s\ndns:%s\n", _NET_CONNECT_TYPE_WIRELESS, "wlan0", 0, ROC_DHCP, "NONE", "0.0.0.0", "0.0.0.0", "255.255.255.0", "192.168.1.1");
        fclose(fp);
        net_setting_last->type = _NET_CONNECT_TYPE_WIRELESS;
        strcpy(net_setting_last->devicename, _WIF_NET0_NAME);
        net_setting_last->connected = 0;
        net_setting_last->method = ROC_DHCP;
        memset(net_setting_last->bssid, 0x00, sizeof(net_setting_last->bssid));
        strcpy(net_setting_last->name, "NONE");
        strcpy(net_setting_last->ip, "0.0.0.0");
        strcpy(net_setting_last->gateway, "0.0.0.0");
        strcpy(net_setting_last->mask, "255.255.255.0");
        strcpy(net_setting_last->dns, "192.168.1.1");
    }
    else
    {
        _parsing_network_setting();
    }
    memcpy(net_setting_file_info, net_setting_last, sizeof(_net_cfg_t));
}

D_S32 d_get_wireless_password(D_Char* filename, D_Char *password)
{
    D_Char line[256];
    D_Char path[256];
    FILE *fd;
    D_S32 error = -1;
    D_Char *token;
    D_S32 len;

    sprintf(path, "%s/%s", WIFI_CFG, ((filename[0] != '\0') ? filename : "NULL"));

    fd = fopen(path, "r");
    if( NULL == fd )
    {
        //printf("fopen %s failed \n", path);
        error = -1;
        return -1;
    }

    while(fgets(line, sizeof(line), fd) != NULL)
    {
        token = strstr(line, "psk=\"");
        if(token)
        {
            while(*token  != '\"')
                token++;
            token++;

            strcpy(password, token);
            len = strlen(password);
            if(password[len - 1] == '\n' && password[len - 2] == '\"')
                password[len - 2] = '\0';
            error = 0;
            break;
        }
        else
        {
            error = -1;
        }
    }
    fclose(fd);
    return error;
}

#if 0
static int _readNlSock(int sockFd, char *bufPtr, int seqNum, int pId)
{
    struct nlmsghdr *nlHdr;
    int readLen = 0, msgLen = 0;

    do
    {
        /* Recieve response from the kernel */
        if((readLen = recv(sockFd, bufPtr, BUFSIZE - msgLen, 0)) < 0)
        {
            perror("SOCK READ: ");
            return -1;
        }

        nlHdr = (struct nlmsghdr *)bufPtr;

        /* Check if the header is valid */
        if((NLMSG_OK(nlHdr, readLen) == 0) || (nlHdr->nlmsg_type == NLMSG_ERROR))
        {
            perror("Error in recieved packet");
            return -1;
        }

        /* Check if the its the last message */
        if(nlHdr->nlmsg_type == NLMSG_DONE)
        {
            break;
        }
        else
        {
            /* Else move the pointer to buffer appropriately */
            bufPtr += readLen;
            msgLen += readLen;
        }

        /* Check if its a multi part message */
        if((nlHdr->nlmsg_flags & NLM_F_MULTI) == 0)
        {
            /* return if its not */
            break;
        }
    }
    while((nlHdr->nlmsg_seq != seqNum) || (nlHdr->nlmsg_pid != pId));
    return msgLen;
}
#if 0
/* For printing the routes. */
static void _printRoute(struct route_info *rtInfo)
{
    char tempBuf[512];

    /* Print Interface Name*/
    fprintf(stdout, "%s\n", rtInfo->ifName);

    /* Print Destination address */
    if(rtInfo->dstAddr != 0)
        sprintf(tempBuf, "%d.%d.%d.%d",  (0xFF & (rtInfo->dstAddr >> 24)), (0xFF & (rtInfo->dstAddr >> 16)), (0xFF & (rtInfo->dstAddr >> 8)), (0xFF & (rtInfo->dstAddr)) );
    else
        sprintf(tempBuf, "*.*.*.*");
    fprintf(stdout, "dstaddr %s\n", tempBuf);

    /* Print Gateway address */
    if(rtInfo->gateWay != 0)
        sprintf(tempBuf, "%d.%d.%d.%d",  (0xFF & (rtInfo->gateWay >> 24)), (0xFF & (rtInfo->gateWay >> 16)), (0xFF & (rtInfo->gateWay >> 8)), (0xFF & (rtInfo->gateWay)) );
    else
        sprintf(tempBuf, "*.*.*.*");
    fprintf(stdout, "gateway %s\n", tempBuf);

    /* Print Source address */
    if(rtInfo->srcAddr != 0)
        sprintf(tempBuf, "%d.%d.%d.%d",  (0xFF & (rtInfo->srcAddr >> 24)), (0xFF & (rtInfo->srcAddr >> 16)), (0xFF & (rtInfo->srcAddr >> 8)), (0xFF & (rtInfo->srcAddr)) );
    else
        sprintf(tempBuf, "*.*.*.*");
    fprintf(stdout, "srcaddr %s\n", tempBuf);
}
#endif
/* For parsing the route info returned */
static void _parseRoutes(struct nlmsghdr *nlHdr, struct route_info *rtInfo, char *gateway)
{
    struct rtmsg *rtMsg;
    struct rtattr *rtAttr;
    int rtLen;
    char *tempBuf = NULL;

    rtMsg = (struct rtmsg *)NLMSG_DATA(nlHdr);

    /* If the route is not for AF_INET or does not belong to main routing table
       then return. */
    if((rtMsg->rtm_family != AF_INET) || (rtMsg->rtm_table != RT_TABLE_MAIN))
        return;

    tempBuf = (char *)NET_MEMALLOC(100);

    /* get the rtattr field */
    rtAttr = (struct rtattr *)RTM_RTA(rtMsg);
    rtLen = RTM_PAYLOAD(nlHdr);
    for(; RTA_OK(rtAttr, rtLen); rtAttr = RTA_NEXT(rtAttr, rtLen))
    {
        switch(rtAttr->rta_type)
        {
            case RTA_OIF:
                if_indextoname(*(int *)RTA_DATA(rtAttr), rtInfo->ifName);
                break;
            case RTA_GATEWAY:
                rtInfo->gateWay = *(u_int *)RTA_DATA(rtAttr);
                break;
            case RTA_PREFSRC:
                rtInfo->srcAddr = *(u_int *)RTA_DATA(rtAttr);
                break;
            case RTA_DST:
                rtInfo->dstAddr = *(u_int *)RTA_DATA(rtAttr);
                break;
        }
    }
    //printf("%s\n", (char *)inet_ntoa(rtInfo->dstAddr));

    // ADDED BY BOB - ALSO COMMENTED printRoute
//    if (strstr((char *)inet_ntoa((struct in_addr)rtInfo->dstAddr), "0.0.0.0"))
//        sprintf(gateway, "%s", (char *)inet_ntoa((struct in_addr)rtInfo->gateWay));
    struct in_addr addr;
    addr.s_addr =  rtInfo->dstAddr;
    if (strstr((char *)inet_ntoa(addr), "0.0.0.0"))
    {
        addr.s_addr =  rtInfo->gateWay;
        sprintf(gateway, "%s", (char *)inet_ntoa(addr));
    }
    //_printRoute(rtInfo);

    NET_MEMFREE(tempBuf);
    return;
}

int _get_gateway(char *gateway)
{
    struct nlmsghdr *nlMsg;
    struct rtmsg *rtMsg;
    struct route_info *rtInfo;
    char msgBuf[BUFSIZE];

    int sock, len, msgSeq = 0;

    /* Create Socket */
    if((sock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE)) < 0)
        perror("Socket Creation: ");

    /* Initialize the buffer */
    memset(msgBuf, 0, BUFSIZE);

    /* point the header and the msg structure pointers into the buffer */
    nlMsg = (struct nlmsghdr *)msgBuf;
    rtMsg = (struct rtmsg *)NLMSG_DATA(nlMsg);

    /* Fill in the nlmsg header*/
    nlMsg->nlmsg_len = NLMSG_LENGTH(sizeof(struct rtmsg)); // Length of message.
    nlMsg->nlmsg_type = RTM_GETROUTE; // Get the routes from kernel routing table .
    nlMsg->nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST; // The message is a request for dump.
    nlMsg->nlmsg_seq = msgSeq++; // Sequence of the message packet.
    nlMsg->nlmsg_pid = getpid(); // PID of process sending the request.

    /* Send the request */
    if(send(sock, nlMsg, nlMsg->nlmsg_len, 0) < 0)
    {
        hi_eprintf("Write To Socket Failed...\n");
        return -1;
    }

    /* Read the response */
    if((len = _readNlSock(sock, msgBuf, msgSeq, getpid())) < 0)
    {
        hi_eprintf("Read From Socket Failed...\n");
        return -1;
    }
    /* Parse and print the response */
    rtInfo = (struct route_info *)NET_MEMALLOC(sizeof(struct route_info));
    // ADDED BY BOB

    /* THIS IS THE NETTSTAT -RL code I commented out the printing here and in parse routes */
    //fprintf(stdout, "Destination\tGateway\tInterface\tSource\n");

    for(; NLMSG_OK(nlMsg, len); nlMsg = NLMSG_NEXT(nlMsg, len))
    {
        memset(rtInfo, 0, sizeof(struct route_info));
        _parseRoutes(nlMsg, rtInfo, gateway);
    }
    NET_MEMFREE(rtInfo);
    close(sock);

    return 0;
}
#endif
static void * _network_ntp_update(void* p)
{
    D_Char cmd[64];

    sprintf(cmd, "rdate -s time.nist.gov ");
    hi_eprintf("cmd:%s \n", cmd);
    my_system(cmd);
    return (void *)1;
}

int d_timeserver_connect(void)
{
    int err;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    err = pthread_create(&tid_net_timeserver, &attr, _network_ntp_update, NULL);
    pthread_attr_destroy(&attr);
    if (err != 0)
    {
        printf("can't create thread: %s\n", strerror(err));
        return FALSE;
    }
    return TRUE;
}
/** @brief 设置主机名*/
D_S32 d_network_set_hostname(D_Char* hostname)
{
#if 0
    FILE *fd = NULL;
    D_Char buff[256] = {0,};
    D_S32 len;

    fd = fopen(_NET_HOST_NAME, "w+");
    if( NULL == fd )
    {
        printf("fopen %s failed \n", _NET_HOST_NAME);
        return -1;
    }
    strcpy(buff, hostname);
    len = strlen(buff);
    buff[len] = '\n';
    fwrite(buff, len + 1, 1, fd);
    fclose(fd);
#else
    sethostname(hostname, strlen(hostname));
#endif
    return 0;
}

/** @brief 取得主机名*/
D_S32 d_network_get_hostname(D_Char* hostname, int bufflen)
{
    D_Char buff[256] = {0,};
    D_S32 size;
#if 0
    FILE *fd = NULL;
    fd = fopen(_NET_HOST_NAME, "r");
    if( NULL == fd )
    {
        printf("fopen %s failed \n", _NET_HOST_NAME);
        return -1;
    }
    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    size = fread(buff, 1, size, fd);
    fclose(fd);
    if(buff[size - 1] == '\n')
    {
        buff[size - 1] = 0;
        size--;
    }
#else
    gethostname(buff, sizeof(buff));
    size = strlen(buff);
#endif

    size = size > bufflen ? bufflen : size;
    strncpy(hostname, buff, size);
    hostname[size] = 0;
    bufflen = size;

    return 0;
}

#if 0
D_S32 d_network_get_device_info(D_Char* devicename, Roc_Device_Cfg_t* devicecfg)
{
    int error = 0;

    if( NULL == devicename )
    {
        porting_print(_ERRO_, (" devicename == NULL \n"));
        return -1;
    }

    if( NULL == device_num )
    {
        porting_print(_ERRO_, (" devicename == NULL \n"));
        return -1;
    }

    NETWORK_LOCK();

    switch(connect_type)
    {
        case _NET_CONNECT_TYPE_WIRED:
        {
            strcpy(devicename[0], _DEF_NET0_NAME);
            *device_num = 1;
        }
        break;
        case _NET_CONNECT_TYPE_WIRELESS:
        {
            if( 1 == g_wifi_flag )
            {
                strcpy(devicename[0], _WIF_NET0_NAME);
                *device_num = 1;
            }
            else
            {
                *device_num = 0;
            }
        }
        break;
        case _NET_CONNECT_TYPE_CABLE_MODEM:
        case _NET_CONNECT_TYPE_MOBILE_BROADBAND:
        default:
        {
            *device_num = 0;
        }
        break;
    }

    NETWORK_UNLOCK();

    return error;
}
#endif
/** @brief 取得网络设备的相关信息*/
D_S32 d_network_get_device_info(D_Char* devicename, Roc_Device_Cfg_t* devicecfg)
{
    int i      = 0;
    int error  = 0;
    int sockfd = -1;
    struct ifreq ifr;

    if( NULL == devicecfg )
    {
        porting_print(_ERRO_, (" devicecfg == NULL \n"));
        return -1;
    }

    NETWORK_LOCK();

    i = _find_deviece_id(devicename);
    if(i == -1)
    {
        porting_print(_ERRO_, ("not found device - %s \n", (devicename) ? devicename : "NULL"));
        error = -1;
        goto exit;
    }
    else
    {
        /*获取网络的属性*/
        strcpy(devicecfg->devicename, s_net_man[i].name);
        strcpy(devicecfg->description, s_net_man[i].desc);
        devicecfg->connecttype = s_net_man[i].type;
        devicecfg->datarate    = s_net_man[i].data_rate;

        /*建立socket连接*/
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if( sockfd < 0 )
        {
            porting_print(_ERRO_, ("socket(AF_INET, SOCK_DGRAM, 0) failed \n"));
            error = -1;
            goto exit;
        }

        /*获取mac*/
        memset(&ifr, 0, sizeof(struct ifreq));
        strcpy(ifr.ifr_name, s_net_man[i].name);
        if (ioctl(sockfd, SIOCGIFHWADDR, &ifr) < 0)
        {
            porting_print(_ERRO_, ("ioctl(sockfd, SIOCGIFHWADDR, &ifr) failed \n"));
        }
        else
        {
            memcpy(devicecfg->mac, ifr.ifr_hwaddr.sa_data, 6);
        }

#if 0
        /*获取ip*/
        memset(&ifr, 0, sizeof(struct ifreq));
        strcpy(ifr.ifr_name, s_net_man[i].name);
        sin = (struct sockaddr_in *)&ifr.ifr_addr;
        sin->sin_family = AF_INET;
        if (ioctl(sockfd, SIOCGIFADDR, &ifr) < 0)
        {
            porting_print(_WARN_, ("ioctl(sockfd, SIOCGIFADDR, &ifr) failed \n"));
            devicecfg->ip_cfg.ipv4.address = 0;
        }
        else
        {
            devicecfg->ip_cfg.ipv4.address = sin->sin_addr.s_addr;
        }

        /*获取mask*/
        memset(&ifr, 0, sizeof(struct ifreq));
        strcpy(ifr.ifr_name, s_net_man[i].name);
        sin = (struct sockaddr_in *)&ifr.ifr_netmask;
        sin->sin_family = AF_INET;
        if (ioctl(sockfd, SIOCGIFNETMASK, &ifr) < 0)
        {
            porting_print(_WARN_, ("ioctl(sockfd, SIOCGIFNETMASK, &ifr) failed \n"));
            devicecfg->ip_cfg.ipv4.netmask = 0;
        }
        else
        {
            devicecfg->ip_cfg.ipv4.netmask = sin->sin_addr.s_addr;
        }

        close(sockfd);
        sockfd = -1;

        /*获取网关*/
        fd = fopen(_NET_ROUTE_PATH, "r");
        if( NULL == fd )
        {
            porting_print(_ERRO_, ("parse route failed \n"));
        }
        else
        {
            memset(line, 0, sizeof(line));
            while(fgets(line, sizeof(line), fd) != NULL)
            {

                token = strtok(line, "\t ");
                if( !strcmp(token, s_net_man[i].name) )
                {
                    token = strtok(NULL, "\t ");
                    if(!strcmp(token, "00000000"))
                    {
                        token = strtok(NULL, "\t ");
                        break;
                    }
                }

                token = NULL;
            }
            if(token == NULL)
            {
                devicecfg->ip_cfg.ipv4.gateway = 0x00000000;
            }
            else
            {
                sscanf(token, "%x", &(devicecfg->ip_cfg.ipv4.gateway));
            }
            fclose(fd);
        }

        /*获取dns*/
        _res.nscount = 3;
        res_init();
        devicecfg->ip_cfg.ipv4.dns[0] = (UINT32_T)(_res.nsaddr_list[0].sin_addr.s_addr);
        devicecfg->ip_cfg.ipv4.dns[1] = (UINT32_T)(_res.nsaddr_list[1].sin_addr.s_addr);
        devicecfg->ip_cfg.ipv4.dns[2] = (UINT32_T)(_res.nsaddr_list[2].sin_addr.s_addr);
#endif
        /*现在不支持ipv6，未来再支持*/
        {
            //        devicecfg->ip_cfg.is_ipv6_support = ROC_FALSE;
        }

        if(sockfd >= 0)
        {
            close(sockfd);
            sockfd = -1;
        }
    }

exit:
    NETWORK_UNLOCK();

    return error;
}

/** @brief 设置网络设备使用与禁用*/
D_S32 d_network_set_device_enable(const D_Char *devicename, D_Bool enable)
{
#ifdef _NET_INVALID__
    porting_print(_WARN_, ("net invalid \n"));
    return 0;
#else
    int i      = 0;
    int error  = 0;
    int sockfd = 0;
    struct ifreq ifr;

    NETWORK_LOCK();

    i = _find_deviece_id(devicename);
    if(i == -1)
    {
        porting_print(_ERRO_, ("not found device - %s \n", (devicename) ? devicename : "NULL"));
        error = -1;
        goto exit;
    }
    else
    {
        if(1 == s_net_man[i].dhcp_flag)
        {
            my_system("killall udhcpc");
            //  my_system("rm -rf /mnt/dhcp_print.conf");
            net_sleep_ms(100);
            s_net_man[i].dhcp_flag = 0;
        }

        memset(&ifr, 0, sizeof(struct ifreq));
        strcpy(ifr.ifr_name, s_net_man[i].name);

        sockfd  =  socket(AF_INET, SOCK_DGRAM, 0);
        if( sockfd < 0 )
        {
            porting_print(_ERRO_, ("socket(AF_INET, SOCK_DGRAM, 0) failed \n"));
            error = -1;
            goto exit;
        }

        if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0)
        {
            close(sockfd);
            porting_print(_ERRO_, ("ioctl(sockfd, SIOCGIFFLAGS, &ifr) failed \n"));
            error = -1;
            goto exit;
        }

        if( ROC_TRUE == enable )
        {
            ifr.ifr_flags |= (IFF_UP | IFF_RUNNING);

            if( strncmp(s_net_man[i].name, _WIF_NET0_NAME, strlen(_WIF_NET0_NAME)) == 0)
                g_wifi_flag = 1;
        }
        else
        {
            ifr.ifr_flags &= ~IFF_UP;

            if( strncmp(s_net_man[i].name, _WIF_NET0_NAME, strlen(_WIF_NET0_NAME)) == 0)
                g_wifi_flag = 0;
        }

        if (ioctl(sockfd, SIOCSIFFLAGS, &ifr) < 0)
        {
            close(sockfd);
            porting_print(_ERRO_, ("ioctl(sockfd, SIOCSIFFLAGS, &ifr) failed \n"));
            error = -1;
            goto exit;
        }
        else
        {
            porting_print(_INFO_, (" %s state = %d g_wifi_flag = %d  OK \n", devicename, enable, g_wifi_flag ));
        }

        close(sockfd);
    }

exit:
    NETWORK_UNLOCK();

    return error;
#endif
}

/** @brief 取得网络设备使用与禁用*/
D_S32 d_network_get_device_enable(const D_Char *devicename, D_Bool *enable)
{
#ifdef _NET_INVALID__
    porting_print(_WARN_, ("net invalid \n"));
    return 0;
#else
    int i      = 0;
    int error  = 0;
    int sockfd = 0;
    struct ifreq ifr;

    NETWORK_LOCK();

    i = _find_deviece_id(devicename);
    if(i == -1)
    {
        porting_print(_ERRO_, ("not found device - %s \n", (devicename) ? devicename : "NULL"));
        error = -1;
        goto exit;
    }
    else
    {
        memset(&ifr, 0, sizeof(struct ifreq));
        strcpy(ifr.ifr_name, s_net_man[i].name);

        sockfd  =  socket(AF_INET, SOCK_DGRAM, 0);
        if( sockfd < 0 )
        {
            porting_print(_ERRO_, ("socket(AF_INET, SOCK_DGRAM, 0) failed \n"));
            error = -1;
            goto exit;
        }

        if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0)
        {
            close(sockfd);
            porting_print(_ERRO_, ("ioctl(sockfd, SIOCGIFFLAGS, &ifr) failed \n"));
            error = -1;
            goto exit;
        }

        if(ifr.ifr_flags & IFF_UP)
        {
            *enable = 1;
        }
        else
        {
            *enable = 0;
        }

        close(sockfd);
    }

exit:
    NETWORK_UNLOCK();

    return error;
#endif
}

/** @brief 设置网络的dhcp 模式
* @param devicename   设备名
* @param dhcpmode   模式
* @param sync   同步还是异步方式
* @return 返回结果
*/
D_S32 d_network_set_dhcp_mode(D_Char *devicename, Roc_DHCP_Mode_e dhcpmode,  D_Bool sync)
{
#ifdef _NET_INVALID__
    porting_print(_WARN_, ("net invalid \n"));
    return 0;
#else
    int error = 0;
    int i = 0;
    char command[256];

    porting_print(_WARN_, ("devicename=%s dhcpmode=%d \n", devicename, dhcpmode));

    NETWORK_LOCK();

    i = _find_deviece_id(devicename);
    if(i == -1)
    {
        porting_print(_ERRO_, ("not found device - %s \n", (devicename) ? devicename : "NULL"));
        error = -1;
        goto exit;
    }
    else
    {
        if( ROC_DHCP == dhcpmode )
        {
            char hostname[32] = {0,};

            if(_check_process_running("udhcpc"))
            {
                my_system("killall udhcpc");
                net_sleep_ms(100);
            }

            snprintf(command, sizeof(command), "rm -rf %s", _NET_DHCP_INFO_CFG);
            my_system(command);
            net_sleep_ms(10);
            s_net_man[i].dhcp_flag = 0;

            d_network_get_hostname(hostname, 32);
            MSG("hostname:%s\n", hostname);

            memset(command, 0, sizeof(command));
            if(ROC_FALSE == s_net_man[i].dns_auto )
            {
                /*不自动获取dns*/
                snprintf(command, sizeof(command), "udhcpc -b -R -x hostname:%s -s /usr/share/udhcpc/default.script -i %s &>%s &", hostname, s_net_man[i].name, _NET_DHCP_INFO_CFG);
            }
            else
            {
                /*自动获取dns*/
                snprintf(command, sizeof(command), "udhcpc -b -R -x hostname:%s -i %s &>%s &", hostname, s_net_man[i].name, _NET_DHCP_INFO_CFG);
                //snprintf(command, sizeof(command), "udhcpc -b -R -x hostname:%s -i %s &", hostname, s_net_man[i].name);
            }

            hi_eprintf("command=%s\n", command);
            porting_print(_INFO_, (" %s start dhcp ... \n", devicename));
            my_system(command);
            net_sleep_ms(100);
            s_net_man[i].dhcp_flag = 1;

            if(sync) /*同步方式检查结果*/
            {
                int j = 0, timeout = 5000;
                FILE * pfile = NULL;
                char read_buf[1024];

                for(j = 0; j < timeout; j++)
                {
                    if(connect_task_break_flag)
                    {
                        break;
                    }
                    if(access(_NET_DHCP_INFO_CFG, F_OK) == 0)
                    {
                        pfile = fopen(_NET_DHCP_INFO_CFG, "r");
                        while((pfile != NULL) && (NULL != fgets(read_buf, sizeof(read_buf), pfile)))
                        {
                            /* 判断是否成功链接 */
                            if((strstr(read_buf, "Lease of") != NULL) && (strstr(read_buf, "obtained,") != NULL) &&  (strstr(read_buf, "lease time ") != NULL))
                            {
                                //printf("wait dhcp ok time %dms\n", j);
                                j = timeout;
                                break;
                            }
                            else if(strstr(read_buf, "No lease") != NULL)
                            {
                                //printf("wait dhcp err time %dms\n", j);
                                j = timeout;
                                break;
                            }
                            if(connect_task_break_flag)
                            {
                                break;
                            }
                        }

                        if(pfile)
                        {
                            fclose(pfile);
                            pfile = NULL;
                        }
                    }

                    if(j < timeout)
                    {
                        net_sleep_ms(250);
                        j += 250;
                    }
                }
                net_sleep_ms(200);
            }
        }
        else
        {
            if(_check_process_running("udhcpc"))
            {
                my_system("killall udhcpc");
                net_sleep_ms(100);
            }
            snprintf(command, sizeof(command), "rm -rf %s", _NET_DHCP_INFO_CFG);
            porting_print(_INFO_, (" %s stop dhcp ... \n", devicename));
            s_net_man[i].dhcp_flag = 0;
        }
    }
exit:

    NETWORK_UNLOCK();

    return error;
#endif
}

D_S32 _set_dns_auto(D_Char* devicename, D_Bool autodns)
{
    int error = 0;
    int i = 0;

    NETWORK_LOCK();

    i = _find_deviece_id(devicename);
    if(i == -1)
    {
        porting_print(_ERRO_, ("not found device - %s \n", (devicename) ? devicename : "NULL"));
        error = -1;
    }
    else
    {
        s_net_man[i].dns_auto = autodns;
    }

    NETWORK_UNLOCK();

    return error;
}

D_S32 _get_dns_auto(D_Char* devicename, D_Bool *autodns)
{
    int i = 0;
    int error = 0;

    NETWORK_LOCK();
    i = _find_deviece_id(devicename);
    if(i == -1)
    {
        porting_print(_ERRO_, ("not found device - %s \n", (devicename) ? devicename : "NULL"));
        error = -1;
    }
    else
    {
        *autodns = s_net_man[i].dns_auto;
    }
    NETWORK_UNLOCK();
    return error;
}

/** @brief 取得是否运行dhcp的记录*/
D_S32 d_network_get_dhcp_status(D_Char *devicename, D_Bool *dhcp_status)
{
    int i = 0;
    int error = 0;

    NETWORK_LOCK();
    i = _find_deviece_id(devicename);
    if(i == -1)
    {
        porting_print(_ERRO_, ("not found device - %s \n", (devicename) ? devicename : "NULL"));
        error =  -1;
    }
    else
    {
        *dhcp_status = s_net_man[i].dhcp_flag;
    }
    NETWORK_UNLOCK();
    return error;
}

/** @brief 取得dhcp的相关信息*/
D_S32 d_network_get_dhcp_info(D_Char *devicename, Roc_DHCP_Info_t *pdhcpif)
{
    int error = -1;
    int i = 0;
    FILE *fd;
    D_Char line[256];
    D_Char *ptr, *token;

    if( NULL == pdhcpif )
    {
        porting_print(_ERRO_, (" pdhcpip == NULL \n"));
        return -1;
    }

    i = _find_deviece_id(devicename);
    if(i == -1)
    {
        porting_print(_ERRO_, ("not found device - %s \n", (devicename) ? devicename : "NULL"));
    }
#if 1
    NETWORK_LOCK();

    memset(pdhcpif, 0, sizeof(Roc_DHCP_Info_t));
    pdhcpif->dhcpport = 68;

    /*目前无法获取的dhcp server的ip*/
    //pdhcpip->ip.ip_add.ipv4_add = 0x0A0A0A0A;//假的
    strcpy(pdhcpif->dhcpserver, "10.0.0.1");

    /*  get ip */
    Roc_IP_Config_t ipinfo;
    memset(&ipinfo, 0, sizeof(ipinfo));
    if(d_network_get_ip_gateway(devicename, &ipinfo) != 0)
    {
        error = -1;
        goto exit;
    }
    strcpy(pdhcpif->ipaddr, ipinfo.ipaddr);
    strcpy(pdhcpif->mask, ipinfo.mask);
    strcpy(pdhcpif->gateway, ipinfo.gateway);

    fd = fopen(_NET_DHCP_INFO_CFG, "r");
    if( NULL == fd )
    {
        porting_print(_ERRO_, ("fopen %s failed \n", _NET_DHCP_INFO_CFG));
        error = -1;
        goto exit;
    }
    else
    {
        memset(line, 0, sizeof(line));
        while(fgets(line, sizeof(line), fd) != NULL)
        {
            ptr = strstr(line, "lease time ");
            if( NULL != ptr )
            {
                token = ptr + strlen("lease time ");
                if(token == NULL)
                {
                    error = 0;
                }
                else
                {
                    time_t timep;
                    struct tm *p;
                    D_S32 leasetime;

                    sscanf(token, "%d", &leasetime);
                    if(leasetime)
                    {
                        time(&timep);
                        p = localtime(&timep);
                        sprintf(pdhcpif->leasetime.leaseobtained, "%d-%d-%d %d:%d:%d",
                                1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday,
                                p->tm_hour, p->tm_min, p->tm_sec);
                        timep += leasetime;
                        p = localtime(&timep);
                        sprintf(pdhcpif->leasetime.leaseexpires, "%d-%d-%d %d:%d:%d",
                                1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday,
                                p->tm_hour, p->tm_min, p->tm_sec);
                    }
                    error = 0;
                }
            }
        }
        fclose(fd);
    }

exit:
    NETWORK_UNLOCK();
#endif
    return error;
}

/** @brief 取得设备的ip 地址、掩码、网关
* @param devicename   设备名
* @param ipinfo   信息结构
* @return 返回结果
*/
D_S32 d_network_get_ip_gateway(D_Char* devicename, Roc_IP_Config_t* ipinfo)
{
    int error = -1;
    FILE *pfile;
    char buf[512];
    char cmd[128];
    char *tmp;
    int d;

    strcpy(cmd, "ip route");
    pfile = popen(cmd, "r");
    if(NULL == pfile)
    {
        perror("popen error");
    }
    else
    {
        sprintf(cmd, "dev %s", devicename);
        while(fgets(buf, sizeof(buf), pfile) != NULL)
        {
            tmp = buf;
            while(*tmp && isspace(*tmp))
            {
                tmp++;
            }
            //printf("%s\n", tmp);
            if(strstr(tmp, cmd))
            {
                if(strncmp(tmp, "default", strlen("default")) == 0 )
                {
                    sscanf(buf, "%*s%*s%s", ipinfo->gateway);
                    printf("gateway: '%s'\n", ipinfo->gateway);
                }
                else
                {
                    tmp = strstr(tmp, "/");
                    if(tmp)
                    {
                        tmp++;
                        d = 0;
                        sscanf(tmp, "%d", &d);
                        d = ((0xFFFFFFFF >> (32 - d)) << (32 - d));
                        sprintf(ipinfo->mask, "%d.%d.%d.%d", (0xFF & (d >> 24)), (0xFF & (d >> 16)), (0xFF & (d >> 8)), (0xFF & d));
                        printf("mask: '%s'\n", ipinfo->mask);

                        tmp = strstr(tmp, "src");
                        if(tmp)
                        {
                            sscanf(tmp, "%*s%s", ipinfo->ipaddr);
                            printf("ipaddr: '%s'\n", ipinfo->ipaddr);
                            error = 0;
                        }
                    }
                }
            }
        }
        pclose(pfile);
    }

    return error;
}

/** @brief 设置ip 与net mask*/
D_S32 d_network_set_ip(D_Char* devicename, Roc_IP_Config_t* ipinfo)
{
#ifdef _NET_INVALID__
    porting_print(_WARN_, ("net invalid \n"));
    return 0;
#else
    int error = 0;
    int i = 0;

    porting_print(_ERRO_, (" ====devicename:%s ipaddr:%s===== \n", devicename, ipinfo->ipaddr));

    NETWORK_LOCK();

    i = _find_deviece_id(devicename);
    if(i == -1)
    {
        porting_print(_ERRO_, ("not found device - %s \n", (devicename) ? devicename : "NULL"));
        error = -1;
        goto exit;
    }
    else
    {
        //switch(address.type)
        {
            //case ROC_IP_TYPE_IPv4:
            {
                int sockfd = 0;
                struct ifreq ifr;

                struct sockaddr_in *sin = NULL;

                sockfd = socket(AF_INET, SOCK_DGRAM, 0);
                if (sockfd < 0)
                {
                    porting_print(_ERRO_, ("socket(AF_INET, SOCK_DGRAM, 0) failed \n"));
                    error = -1;
                    goto exit;
                }
                else
                {
                    memset(&ifr, 0, sizeof(struct ifreq));
                    strcpy(ifr.ifr_name, devicename);
                    sin = (struct sockaddr_in *)&ifr.ifr_addr;
                    sin->sin_family = AF_INET;

                    if(inet_pton(AF_INET, ipinfo->ipaddr, &sin->sin_addr) <= 0)
                    {
                        porting_print(_ERRO_, ("inet_pton() ipaddr failed \n"));
                        error = -1;
                        close(sockfd);
                        goto exit;
                    }

                    if (ioctl(sockfd, SIOCSIFADDR, &ifr) < 0)
                    {
                        porting_print(_ERRO_, ("ioctl(sockfd, SIOCSIFADDR, &ifr) failed \n"));
                        error = -1;
                    }
                    else
                    {
                        porting_print(_INFO_, ("%s change ip to %s \n", devicename, ipinfo->ipaddr));
                    }

                    if(inet_pton(AF_INET, ipinfo->mask, &sin->sin_addr) <= 0)
                    {
                        porting_print(_ERRO_, ("inet_pton() maks failed \n"));
                        error = -1;
                        close(sockfd);
                        goto exit;
                    }

                    if (ioctl(sockfd, SIOCSIFNETMASK, &ifr) < 0)
                    {
                        porting_print(_ERRO_, ("ioctl(sockfd, SIOCSIFNETMASK, &ifr) failed \n"));
                        error = -1;
                    }
                    else
                    {
                        porting_print(_INFO_, ("%s change mask to %s \n", devicename, ipinfo->mask));
                    }

                    close(sockfd);
                }
            }
#if 0
            //    break;
        case ROC_IP_TYPE_IPv6:
            {
                porting_print(_ERRO_, ("not support ipv6 \n"));
                error = -1;
                goto exit;
            }
            break;
        default:
            break;
#endif
        }
    }

exit:
    NETWORK_UNLOCK();

    return error;
#endif
}


#if 0
D_S32 _network_get_ip(D_Char* devicename, Roc_IP_Config_t* ipinfo)
{
#ifdef _NET_INVALID__
    porting_print(_WARN_, ("net invalid \n"));
    return 0;
#else
    int error = 0;
    int i  = 0;

    NETWORK_LOCK();

    i = _find_deviece_id(devicename);
    if(i == -1)
    {
        porting_print(_ERRO_, ("not found device - %s \n", (devicename) ? devicename : "NULL"));
        error = -1;
        goto exit;
    }
    else
    {
        int sockfd = 0;
        struct ifreq ifr;
        struct sockaddr_in *sin = NULL;

        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0)
        {
            porting_print(_ERRO_, ("socket(AF_INET, SOCK_DGRAM, 0) failed \n"));
            error = -1;
            goto exit;
        }
        else
        {
            memset(&ifr, 0, sizeof(struct ifreq));
            printf("F:%s L:%d\n", __func__, __LINE__);
            strcpy(ifr.ifr_name, s_net_man[i].name);
            sin = (struct sockaddr_in *)&ifr.ifr_addr;
            sin->sin_family = AF_INET;

            if (ioctl(sockfd, SIOCGIFADDR, &ifr) < 0)
            {
                porting_print(_ERRO_, ("ioctl(sockfd, SIOCSIFADDR, &ifr) failed \n"));
                perror(" SIOCGIFADDR");
                error = -1;
            }
            else
            {
                sin = (struct sockaddr_in *)&ifr.ifr_addr;
                strcpy(ipinfo->ipaddr, inet_ntoa(sin->sin_addr));
                //    memcpy(ipinfo->ipaddr, sin->sin_addr.s_addr, sizeof(ipinfo->ipaddr));
                hi_eprintf("ipaddr=%s \n", ipinfo->ipaddr);
            }

            if (ioctl(sockfd, SIOCGIFNETMASK, &ifr) < 0)
            {
                porting_print(_ERRO_, ("ioctl(sockfd, SIOCSIFADDR, &ifr) failed \n"));
                perror(" SIOCGIFADDR");
                error = -1;
            }
            else
            {
                sin = (struct sockaddr_in *)&ifr.ifr_addr;
                strcpy(ipinfo->mask, inet_ntoa(sin->sin_addr));
                //    memcpy(ipinfo->ipaddr, sin->sin_addr.s_addr, sizeof(ipinfo->ipaddr));
                hi_eprintf("mask=%s \n", ipinfo->mask);
            }
            close(sockfd);
        }

        error = _get_gateway(ipinfo->gateway);
        hi_eprintf("gateway=%s \n", ipinfo->gateway);
    }

exit:
    NETWORK_UNLOCK();

    return error;
#endif
}

int _network_set_ipv4_mask(char * devicename, char * address)
{
#ifdef _NET_INVALID__
    porting_print(_WARN_, ("net invalid \n"));
    return 0;
#else
    int error = 0;
    int i     = 0;

    NETWORK_LOCK();

    i = _find_deviece_id(devicename);
    if(i == -1)
    {
        porting_print(_ERRO_, ("not found device - %s \n", (devicename) ? devicename : "NULL"));
        error = -1;
        goto exit;
    }
    else
    {
        int sockfd = 0;
        struct ifreq ifr;
        struct sockaddr_in *sin = NULL;

        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0)
        {
            porting_print(_ERRO_, ("socket(AF_INET, SOCK_DGRAM, 0) failed \n"));
            error = -1;
            goto exit;
        }
        else
        {
            memset(&ifr, 0, sizeof(struct ifreq));
            strcpy(ifr.ifr_name, s_net_man[i].name);
            sin = (struct sockaddr_in *) & (ifr.ifr_netmask);
            sin->sin_family = AF_INET;
            sin->sin_addr.s_addr = inet_addr(address);

            if (ioctl(sockfd, SIOCSIFNETMASK, &ifr) < 0)
            {
                porting_print(_ERRO_, ("ioctl(sockfd, SIOCSIFNETMASK, &ifr) failed \n"));
                printf("strerror:%s\n", strerror(errno));
                error = -1;
            }
            else
            {
                struct in_addr in;
                memset(&in, 0, sizeof(struct in_addr));
                in.s_addr = (unsigned int)address;
                porting_print(_INFO_, ("%s change mask to %s \n", devicename, address));
            }
            close(sockfd);
        }
    }

exit:
    NETWORK_UNLOCK();

    return error;
#endif
}
#endif
/** @brief 取得设备的网关
* @param devicename   设备名
* @param gateway   网关名缓存
* @return 返回结果
*/
D_S32 d_network_get_gateway(D_Char* devicename, D_Char* gateway)
{
    int error = -1;
    FILE *pfile;
    char buf[512];
    char cmd[128];
    char *tmp;
    int d;

    strcpy(cmd, "ip route");
    pfile = popen(cmd, "r");
    if(NULL == pfile)
    {
        perror("popen error");
    }
    else
    {
        sprintf(cmd, "dev %s", devicename);
        while(fgets(buf, sizeof(buf), pfile) != NULL)
        {
            tmp = buf;
            while(*tmp && isspace(*tmp))
            {
                tmp++;
            }

            if(strstr(tmp, cmd))
            {
                if(strncmp(tmp, "default", strlen("default")) == 0 )
                {
                    sscanf(buf, "%*s%*s%s", gateway);
                    printf("gateway: '%s'\n", gateway);
                    error = 0;
                    break;
                }
            }
        }
        pclose(pfile);
    }

    return error;
}

#if 0
D_S32 _network_set_gatway(D_Char *devicename, Roc_IP_t address)
{
#ifdef _NET_INVALID__
    porting_print(_WARN_, ("net invalid \n"));
    return 0;
#else
    int error = 0;
    int i = 0;

    NETWORK_LOCK();

    i = _find_deviece_id(devicename);
    if(i == -1)
    {
        porting_print(_ERRO_, ("not found device - %s \n", (devicename) ? devicename : "NULL"));
        error = -1;
        goto exit;
    }
    else
    {
        switch(address.type)
        {
            case ROC_IP_TYPE_IPv4:
            {
                int sockfd = 0;
                struct rtentry re;

                sockfd = socket(AF_INET, SOCK_DGRAM, 0);
                if (sockfd < 0)
                {
                    porting_print(_ERRO_, ("socket(AF_INET, SOCK_DGRAM, 0) failed \n"));
                    error = -1;
                    goto exit;
                }
                else
                {
                    memset(&re, 0, sizeof(struct rtentry));
                    re.rt_flags = RTF_UP | RTF_GATEWAY;
                    ((struct sockaddr_in*)&re.rt_dst)->sin_family     = AF_INET;
                    ((struct sockaddr_in*)&re.rt_genmask)->sin_family = AF_INET;
                    ((struct sockaddr_in*)&re.rt_gateway)->sin_family = AF_INET;
                    ((struct sockaddr_in*)&re.rt_gateway)->sin_addr.s_addr = address.ip_add.ipv4_add;
                    if (ioctl(sockfd, SIOCADDRT, &re) < 0)
                    {
                        if (errno == ENETUNREACH)
                        {
                            porting_print(_WARN_, ("gateway %d unreachable \n", address.ip_add.ipv4_add));
                        }
                        else if (errno == EEXIST)
                        {
                            porting_print(_WARN_, ("gateway %d has been added \n", address.ip_add.ipv4_add));
                        }
                        else
                        {
                            porting_print(_ERRO_, ("ioctl(sockfd, SIOCADDRT, &re) failed \n"));
                            error = -1;
                        }
                    }
                    else
                    {
                        struct in_addr in;
                        memset(&in, 0, sizeof(struct in_addr));
                        in.s_addr = address.ip_add.ipv4_add;
                        porting_print(_INFO_, ("%s change gateway to %s \n", devicename, inet_ntoa( in )));
                    }
                    close(sockfd);
                }
            }
            break;
            case ROC_IP_TYPE_IPv6:
            {
                porting_print(_ERRO_, ("not support ipv6 \n"));
                error = -1;
                goto exit;
            }
            break;
            default:
                break;
        }
    }

exit:
    NETWORK_UNLOCK();

    return error;
#endif
}
#endif
D_S32 d_network_set_gateway(D_Char *devicename, D_Char* gateway)
{
    D_Char cmd[64];
    memset(cmd, 0, sizeof(cmd));
    sprintf(cmd, "route del default");
    my_system(cmd);
    memset(cmd, 0, sizeof(cmd));
    sprintf(cmd, "route add default gw %s", gateway);
    my_system(cmd);
    return 0;
}

D_S32 d_network_set_dnsserver(D_Char* devicename,  D_Char *dnsserver)
{
    D_S32 error = 0;
    D_S32 i = 0;
    FILE *fd = NULL;
    D_Char data[128];

    NETWORK_LOCK();

    i = _find_deviece_id(devicename);
    if(i == -1)
    {
        porting_print(_ERRO_, ("not found device - %s \n", (devicename) ? devicename : "NULL"));
        error = -1;
        goto exit;
    }
    else
    {
        fd = fopen(_NET_RESOLV_CFG, "w+");
        if( NULL == fd )
        {
            porting_print(_ERRO_, ("fopen %s failed \n", _NET_RESOLV_CFG));
            error = -1;
            goto exit;
        }
        else
        {
            memset(data, 0, sizeof(data));
            snprintf( data, sizeof(data), "nameserver %s\n", dnsserver);

            fwrite(data, strlen(data), 1, fd);
            fclose(fd);
            porting_print(_INFO_, ("%s change dns to %s \n", devicename, dnsserver));
        }
    }
exit:
    NETWORK_UNLOCK();

    return error;
}

D_S32 d_network_get_dnsserver(D_Char* devicename, D_Char *dnsserver)
{
    D_Char line[256];
    FILE *fd;
    D_S32 error = -1;
    D_Char *token;

    if( NULL == devicename )
    {
        porting_print(_ERRO_, (" devicename == NULL \n"));
        return -1;
    }

    NETWORK_LOCK();

    fd = fopen(_NET_RESOLV_CFG, "r");
    if( NULL == fd )
    {
        porting_print(_ERRO_, ("fopen %s failed \n", _NET_RESOLV_CFG));
        error = -1;
        goto exit;
    }

    while(fgets(line, sizeof(line), fd) != NULL)
    {
        token = strstr(line, "nameserver");
        if(token)
        {
            while(*token  != ' ')
                token++;
            while(*token  == ' ')
                token++;
            D_S32 len;
            strcpy(dnsserver, token);
            len = strlen(dnsserver);
            if(dnsserver[len - 1] == '\n')
                dnsserver[len - 1] = 0;
            error = 0;
            break;
        }
        else
        {
            error = -1;
        }

    }
    fclose(fd);

    NETWORK_UNLOCK();

exit:

    printf("dnsserver='%s'\n",  dnsserver);
    return error;
}

D_S32 d_network_get_device_state(D_Char* devicename, D_S32* devicestate)
{
    int error = 0;
    int i = 0;

    porting_print(_ERRO_, (" ====%s===== \n", __FUNCTION__));

    NETWORK_LOCK();
    i = _find_deviece_id(devicename);
    if(i == -1)
    {
        porting_print(_ERRO_, ("not found device - %s \n", (devicename) ? devicename : "NULL"));
        //*devicestate = _NET_DEVICE_STATUS_NOT_FOUND;
        *devicestate = 0;
    }
    else
    {
        int sockfd = 0;
        struct ifreq ifr;
        struct ethtool_value edata;

        memset(&ifr, 0, sizeof(ifr));
        memset(&edata, 0, sizeof(edata));
        edata.cmd = ETHTOOL_GLINK;
        edata.data = 0;
        strcpy(ifr.ifr_name, s_net_man[i].name);
        ifr.ifr_data = (char *)&edata;

        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0)
        {
            porting_print(_ERRO_, ("socket(AF_INET, SOCK_DGRAM, 0) failed \n"));
            perror("socket");
            //*devicestate = _NET_DEVICE_STATUS_UNKOWN;
            *devicestate = 0;
        }
        else
        {
            if(strcmp(s_net_man[i].name, _DEF_NET0_NAME))
            {
                *devicestate = 201;
            }
            else
            {
                if (ioctl(sockfd, SIOCETHTOOL, &ifr) == -1)
                {
                    perror("SIOCETHTOOL");
                    //*devicestate = _NET_DEVICE_STATUS_DISCONNECT;
                    //*devicestate = 102; //zhangmc
                    *devicestate = 201; //zhangmc
                }
                else
                {
                    if ( 0 < edata.data )
                    {
                        *devicestate = 201;
                        //*devicestate = _NET_DEVICE_STATUS_CONNECT;
                    }
                    else
                    {
                        *devicestate = 202;
                        //*devicestate = _NET_DEVICE_STATUS_DISCONNECT;
                    }
                }
            }

            close(sockfd);
        }
    }

    NETWORK_UNLOCK();

    return error;
}
/*
static unsigned short checksum(unsigned short *buffer, int size)
{
    unsigned long cksum=0;
    while(size >1)
    {
        cksum+=*buffer++;
        size -=sizeof(unsigned short);
    }

    if(size )
    {
        cksum += *(unsigned short *)buffer;
    }

    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >>16);
    return (unsigned short)(~cksum);
}
*/

/*wireless part ...*/

#define ENABLE_PARSE_ESSID        (1 << 1)
#define ENABLE_PARSE_PROTOCOL (1 << 2)
#define ENABLE_PARSE_MODE         (1 << 3)
#define ENABLE_PARSE_FREQ         (1 << 4)
#define ENABLE_PARSE_ENC_KEY  (1 << 5)
#define ENABLE_PARSE_BIT_RATE (1 << 6)
#define ENABLE_PARSE_QUALITY  (1 << 7)
#define ENABLE_PARSE_CIPHER       (1 << 8)

#define USER_IW_MAX_AP IW_MAX_AP
static _Wireless_AP_Info_t s_ap_rec[USER_IW_MAX_AP];

#ifdef USE_SHELL_CMD
static int _get_num_and_mac(_Wireless_AP_Info_t * apinfo, char * buf)
{
    char * p;
    int i = 0;
    int num = -1;
    p = buf;
    p = strstr(p, "Cell");
    if(p)
    {
        p += 4;
        num = atoi(p);
    }
    p = strstr(p, "Address");
    p = strstr(p, ":");
    p += 2;
    for(i = 0; i < 6; ++i)
    {
        apinfo->bssid[i] = strtoul(p, NULL, 16);
        p += 3;
    }
//  hi_eprintf("MAC: %lu\n", apinfo->bssid);
    return num;
}

static void _get_essid(_Wireless_AP_Info_t * apinfo, char * buf)
{
    char name_utf8[96] = {0};
    char * p;
    char *pp;
    int len;

    apinfo->essid[0] = '\0';
    p = buf;
    p = strstr(p, "ESSID");
    if(p)
    {
        p = strchr(p, '"');
        p++;
        pp = strchr(p, '"');
        len = pp - p;
        if(len > sizeof(name_utf8))
        {
            len = sizeof(name_utf8);
        }
        // "\xE6\x88\x91OPPO"   ->  utf8:   "我OPPO"
        strncpy(name_utf8, p, len);
        memset(apinfo->essid, 0x00, sizeof(apinfo->essid));
        convert_hexstr_to_bytestr(name_utf8, len, apinfo->essid, sizeof(apinfo->essid));
        apinfo->essid[sizeof(apinfo->essid) - 1] = '\0';
        //hi_eprintf("essid: '%s'\n", apinfo->essid);
    }
}

static void _get_protocol(_Wireless_AP_Info_t * apinfo, char * buf)
{
    char * p = buf;
    p = strstr(p, "Protocol");
    if(p)
    {
        p = strchr(p, ':');
        p += 6;
        if(!strcmp(p, "802.11"))
        {
            apinfo->protocol = _WIRELESS_PROTOCOL_80211;
        }
        else if(!strcmp(p, "802.11a"))
        {
            apinfo->protocol = _WIRELESS_PROTOCOL_80211a;
        }
        else if(!strcmp(p, "802.11b"))
        {
            apinfo->protocol = _WIRELESS_PROTOCOL_80211b;
        }
        else if(!strcmp(p, "802.11g"))
        {
            apinfo->protocol = _WIRELESS_PROTOCOL_80211g;
        }
        else if(!strcmp(p, "802.11i"))
        {
            apinfo->protocol = _WIRELESS_PROTOCOL_80211i;
        }
        else if(!strcmp(p, "802.11n"))
        {
            apinfo->protocol = _WIRELESS_PROTOCOL_80211n;
        }
        else if(!strcmp(p, "802.11bg"))
        {
            apinfo->protocol = _WIRELESS_PROTOCOL_80211bg;
        }
        else if(!strcmp(p, "802.11bgn"))
        {
            apinfo->protocol = _WIRELESS_PROTOCOL_80211bgn;
        }
        else
        {
            apinfo->protocol = _WIRELESS_PROTOCOL_OTHER;
        }
    }
}

static void _get_freq(_Wireless_AP_Info_t * apinfo, char * buf)
{
    char * p = buf;
    int freq = 0;
    p = strstr(p, "Frequency");
    if(p)
    {
        p = strchr(p, ':');
        p++;
        freq = atoi(p) * 1000;
        p += 2;
        freq += atoi(p);

        p = strchr(p, ' ');
        p++;
        if(!strncmp(p, "G", 1))
        {
            freq *= 1000;
        }

//        hi_eprintf("freq: %d MHz\n", freq);
        apinfo->freq = freq;
    }
    p = strstr(p, "Channel");
    if(p)
    {
        p += 8;
        apinfo->channel_num = atoi(p);
//        hi_eprintf("channel: %d\n", apinfo->channel_num);
    }
}
static void _get_encryption(_Wireless_AP_Info_t * apinfo, char * buf)
{
    char * p = buf;
    p = strstr(p, "Encryption key");
    if(p)
    {
        p = strchr(p, ':');
        p++;
        if(!strncmp(p, "on", 2))
        {
            apinfo->privacy = 1;
        }
        else
        {
            apinfo->privacy = 0;
        }
    }
}

static void _get_bitrate(_Wireless_AP_Info_t * apinfo, char * buf)
{
    char * p = buf;
    int bit = 0;
    p = strstr(p, "Bit Rates");
    if(p)
    {
        p = strchr(p, ':');
        p++;
        bit = atoi(p);
        p = strchr(p, ' ');
        p++;
        if(!strncmp(p, "M", 1))
        {
            bit *= 1000;
        }
        apinfo->bit_rate = bit;
//        hi_eprintf("bit rate: %d KHz\n", bit);
    }
}

static void _get_quality(_Wireless_AP_Info_t * apinfo, char * buf)
{
    char * p = buf;
    int quality = 0;
    int signal = 0;

    //  Quality=86/100  Signal level=31/100
    p = strstr(p, "Quality");
    if(p)
    {
        p = strchr(p, '=');
        p++;
        quality = atoi(p);
        apinfo->quality = quality;
//        hi_eprintf("quality: %d\n", quality);
    }
    p = strstr(p, "Signal level");
    if(p)
    {
        p = strchr(p, '=');
        p += 1;
        signal = atoi(p);
        apinfo->signal = signal;
//        hi_eprintf("signal: %d\n", signal);
    }
}
#endif

static int _analyse_ap_info(D_Char* devicename, FILE * pfile, _Wireless_AP_Info_t * apinfos)
{
    _Wireless_AP_Info_t * apinfo = apinfos;
    char read_buf[4096] = {0,};
    char * p = NULL;
    int num = 0, cnt, i;
    unsigned int enable_flag;

    printf("%s, %d\n", __FUNCTION__, __LINE__);
    enable_flag = 0xFFFFFFFF;
    while(fgets(read_buf, sizeof(read_buf), pfile) != NULL)
    {
        //  printf("%s, %d, read_buf:%s\n", __FUNCTION__, __LINE__, read_buf);
        read_buf[sizeof(read_buf) - 1] = '\0';
        if (read_buf[strlen(read_buf) - 1] == '\n')
        {
            read_buf[strlen(read_buf) - 1] = '\0'; //去除换行符
        }
        //hi_eprintf("'%s'\n", read_buf);
        p = read_buf;
        if(strncmp(read_buf, devicename, strlen(devicename)) == 0)
        {
            if(strstr(p, "Scan completed"))
            {
                continue;
            }
            else//No scan results
                break;
        }
        if(strstr(p, "Cell"))
        {
            enable_flag = 0xFFFFFFFF;
            if(num >= USER_IW_MAX_AP) // 满了
            {
                break;
            }

            if(num != 0)
            {
                apinfo++;
            }
            _get_num_and_mac(apinfo, read_buf);
            num++;
            continue;
        }
        else if((enable_flag & ENABLE_PARSE_ESSID) && strstr(p, "ESSID"))
        {
            enable_flag &= ~ENABLE_PARSE_ESSID;
            _get_essid(apinfo, read_buf);
        }
        else if((enable_flag & ENABLE_PARSE_PROTOCOL) && strstr(p, "Protocol"))
        {
            enable_flag &= ~ENABLE_PARSE_PROTOCOL;
            _get_protocol(apinfo, read_buf);
        }
        else if((enable_flag & ENABLE_PARSE_MODE) && strstr(p, "Mode"))
        {
            enable_flag &= ~ENABLE_PARSE_MODE;
            if(strstr(p, "Master"))
            {
                apinfo->wireless_mode = _WIRELESS_MODE_OTHER;
            }
            else if(strstr(p, "Ad-Hoc"))
            {
                apinfo->wireless_mode = _WIRELESS_MODE_AC_HOC;
            }
            else if(strstr(p, "Managed"))
            {
                apinfo->wireless_mode = _WIRELESS_MODE_MANAGED;
            }
            else if(strstr(p, "Repeater"))
            {
                apinfo->wireless_mode = _WIRELESS_MODE_REPEAT;
            }
            else
            {
            }
        }
        else if((enable_flag & ENABLE_PARSE_FREQ) && strstr(p, "Frequency"))
        {
            enable_flag &= ~ENABLE_PARSE_FREQ;
            _get_freq(apinfo, read_buf);
        }
        else if((enable_flag & ENABLE_PARSE_ENC_KEY) && strstr(p, "Encryption key"))
        {
            enable_flag &= ~ENABLE_PARSE_ENC_KEY;
            _get_encryption(apinfo, read_buf);
        }
        else if((enable_flag & ENABLE_PARSE_BIT_RATE) && strstr(p, "Bit Rates"))
        {
            enable_flag &= ~ENABLE_PARSE_BIT_RATE;
            _get_bitrate(apinfo, read_buf);
        }
        else if((enable_flag & ENABLE_PARSE_QUALITY) && strstr(p, "Quality"))
        {
            enable_flag &= ~ENABLE_PARSE_QUALITY;
            _get_quality(apinfo, read_buf);
        }
        else if(strstr(p, "IE"))
        {
            if(strstr(p, "WPA2"))
            {
                apinfo->wireless_alg = _IW_AUTH_WPA2_PSK; //
            }
            else if(strstr(p, "WPA"))
            {
                apinfo->wireless_alg = _IW_AUTH_WPA_PSK; //
            }
            else
                apinfo->wireless_alg = _IW_AUTH_OTHER;
        }
        else if((enable_flag & ENABLE_PARSE_CIPHER) && strstr(p, "Group Cipher"))
        {
            enable_flag &= ~ENABLE_PARSE_CIPHER;
            if(strstr(p, "TKIP"))
            {
                apinfo->cipher = _WIRELESS_CIPHER_TKIP;
            }
            else if(strstr(p, "CCMP"))
            {
                apinfo->cipher = _WIRELESS_CIPHER_AES;
            }
            else
                apinfo->cipher = _WIRELESS_CIPHER_OTHER;
        }
        strncpy(apinfo->password, "NULL", sizeof("NULL"));
    }

    /* 去掉没有名字的ap*/
    i = 0;
    cnt = 0;
    while(i < num)
    {
        if(apinfos[i].essid[0] != 0)
        {
            if(cnt != i)
            {
                memcpy(&apinfos[cnt], &apinfos[i], sizeof(_Wireless_AP_Info_t));
            }
            cnt++;
        }
#if 0        
        else
        {
            _Wireless_AP_Info_t * ap = &apinfos[i];
            D_DUMP("ignore ap: p %-2x wm %-2d br %-8d freq %-8d ch %-2d q %-3d  s %-2d n %-2d privacy %-2d alg %-2d c %-2d %02X%02X%02X%02X%02X%02X %s\n", \
                   ap->protocol, ap->wireless_mode, ap->bit_rate, ap->freq, ap->channel_num, ap->quality, ap->signal, ap->noise, ap->privacy, ap->wireless_alg, ap->cipher, \
                   ap->bssid[0], ap->bssid[1], ap->bssid[2], ap->bssid[3], ap->bssid[4], ap->bssid[5], ap->essid);
        }
#endif
        i++;
    }

    return cnt;
}



static int _check_wlan_up(D_Char * devicename)
{
    FILE * pfile = NULL;
    char cmd_buf[128] = {0,};
    char read_buf[2048];

    sprintf(cmd_buf, "ifconfig | grep \"%s\" | grep -v grep", devicename);
    pfile = popen(cmd_buf, "r");
    if(pfile != NULL)
    {
        if(fgets(read_buf, sizeof(read_buf), pfile) == NULL)
        {
            memset(cmd_buf, 0, sizeof(cmd_buf));
            sprintf(cmd_buf, "ifconfig %s  up", devicename);
            my_system(cmd_buf);
        }
        pclose(pfile);
    }

    return 0;
}

/** @brief 创建目录，可多级创建
* @param dirname        目录名
* @return 成功返回D_TRUE,  失败返回D_FALSE
*/
D_Bool  d_create_dir(const char *dirname)
{
    D_Bool ret = D_TRUE;
    char dir_name[512];
    int i, len;

    strcpy(dir_name, dirname);
    len = strlen(dir_name);

    if(dir_name[len - 1] != '/')
        strcat(dir_name, "/");

    len = strlen(dir_name);

    for(i = 1; i < len; i++)
    {
        if(dir_name[i] == '/')
        {
            dir_name[i] = '\0';
            if(access(dir_name, F_OK) != 0)
            {
                if(mkdir(dir_name, 0755) == -1)
                {
                    /*将错误输出到stderr*/
                    perror("d_create_dir error");
                    ret = D_FALSE;
                    break;
                }
            }
            dir_name[i] = '/';
        }
    }

    return ret;
}
static int _make_wifi_cfgfile(char*essid, unsigned char*bssid, char* key, int key_len, int savedbase)
{
    FILE * fp = NULL;
    D_Char filename[64];
    char wifi_cfg_path[256];

#if SAVE_CONFIG_IN_SYS_DBASE
    if(savedbase > 0)
    {
        D_WifiApConfig param;
        memset(&param, 0, sizeof(D_WifiApConfig));
        sprintf(param.essid, "%s", essid);
        memcpy(param.bssid, bssid, sizeof(param.bssid));
        param.key_len = (key_len > 0) ? ((D_S16) key_len) : 0;
        if(param.key_len > 0)
        {
            snprintf(param.key, sizeof(param.key), "%s", key);
        }
        p_tvconf_set_wifiap_param  (&param);
    }
#endif

    MAKE_WIFI_FILENAME(filename, essid, bssid);
    sprintf(wifi_cfg_path, "%s/%s", WIFI_CFG, filename);

    fp = fopen(wifi_cfg_path, "w+");
    if(fp == NULL)
    {
        hi_eprintf("Open file %s failed!\n", wifi_cfg_path);
        return -1;
    }

    fprintf(fp, "ctrl_interface="SOCKET_WPA"\nnetwork={\nssid=\"%s\"\nbssid=%02X:%02X:%02X:%02X:%02X:%02X\n", \
            ((essid[0] != '\0') ? essid : "NULL"), bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);

    if(key_len <= 0)
    {
        fprintf(fp, "key_mgmt=NONE\n}\n");
    }
    else
    {
        fprintf(fp, "proto=WPA WPA2\nkey_mgmt=WPA-PSK\npairwise=CCMP TKIP\ngroup=CCMP TKIP\n"
                "psk=\"%s\"\n"
                "priority=2\n"
                "}\n",
                key);
    }
    fclose(fp);

    return 0;
}

/** @brief 连接无线网络线程函数
* @param
* @return 返回连接结果
*/
int _wireless_connect(D_Char* devicename, _Wireless_Param_t *param)
{
    int error = ROC_NET_RET_SUCCESS;
#ifdef USE_SHELL_CMD
    FILE * pfile = NULL;
    char cmd_buf[1024];
    char wifi_cfg_path[256];
    D_Char filename[64];
    int connect_flag = 0;
    int i = 0;

    /*  检查创建存储信息目录*/
    if(access(ETHERNET_TMP_DIR, F_OK) != 0)
    {
        d_create_dir(ETHERNET_TMP_DIR);
    }

    /*  删除可能残留的配置文件 */
    if(access(WPA_TMP_FILE, F_OK) == 0)
    {
        unlink(WPA_TMP_FILE);
    }
    strncpy(cur_wifiname, param->essid, sizeof(param->essid));
    porting_print(_INFO_, ("start connect essid: '%s' ,  key: '%s'\n", param->essid, param->key));

    /*  删除已有链接 */
    net_setting_last->connected = 0;
    _network_test_communicate_sync(); /*等待测试线程同步*/

    if(_check_process_running("wpa_supplicant"))
    {
        memset(cmd_buf, 0, sizeof(cmd_buf));
        sprintf(cmd_buf, "killall wpa_supplicant");
        my_system(cmd_buf);
        net_sleep_ms(1000);
    }

    memset(cmd_buf, 0, sizeof(cmd_buf));
    sprintf(cmd_buf, "rm -fr %s", SOCKET_WPA);
    my_system(cmd_buf);

    /*  生成wpa配置文件 */
    MAKE_WIFI_FILENAME(filename, param->essid, param->bssid);
    sprintf(wifi_cfg_path, "%s/%s", WIFI_CFG, filename);
    i = access(wifi_cfg_path, F_OK);
    hi_eprintf("access(wifi_cfg_path, F_OK)=  %d\n", i);
    if(i == 0)
    {
        char old_key[128] = {0,};
        if(param->key_len <= 0)
        {
            memset(param->key, 0, sizeof(param->key));
        }
        d_get_wireless_password(filename, old_key);
        if(strcmp(old_key, param->key) != 0) /* 密码变化*/
        {
            i = 0x05aa5aa5;
        }
    }

    if(i != 0) /* 文件不存在或密码变化都重新写配置文件*/
    {
        if(_make_wifi_cfgfile(param->essid, param->bssid, param->key, param->key_len, 1) < 0)
        {
            error = ROC_NET_RET_FAILED;
            goto _exit;
        }
    }

    /* 开始链接 */
    memset(cmd_buf, 0, sizeof(cmd_buf));
    sprintf(cmd_buf, "wpa_supplicant -i %s -t -f %s -Dnl80211 -c %s -B &", devicename, WPA_TMP_FILE, wifi_cfg_path);
    hi_eprintf("cmd: '%s'\n", cmd_buf);
    my_system(cmd_buf);

    memset(cmd_buf, 0, sizeof(cmd_buf));
    sleep(1);
    error = ROC_NET_RET_TIMEOUT;
    pfile = NULL;
    for(i = 0; i < 10; ++i)
    {
        if(connect_task_break_flag)
        {
            break;
        }

        if(access(WPA_TMP_FILE, F_OK) != 0)
        {
            sleep(1);
            continue;
        }

        pfile = fopen(WPA_TMP_FILE, "r");
        while((pfile != NULL) && (NULL != fgets(cmd_buf, sizeof(cmd_buf), pfile)))
        {
            /* 判断是否密码错误 */
            if((strstr(cmd_buf, "pre-shared key may be incorrect") != NULL) || (strstr(cmd_buf, "failed to parse psk") != NULL))
            {
                hi_eprintf("%s\n", cmd_buf);
                hi_eprintf("Passwd error!\n");
                connect_flag = 0;
                error = ROC_NET_RET_PWDERR;
                break;
            }
            /* 判断是否成功链接 */
            if(strstr(cmd_buf, "CTRL-EVENT-CONNECTED") != NULL)
            {
                if(strstr(cmd_buf, "completed") != NULL)
                {
                    connect_flag = 1;
                    error = ROC_NET_RET_SUCCESS;
                    break;
                }
            }

            if(connect_task_break_flag)
            {
                break;
            }
        }

        if(pfile)
        {
            fclose(pfile);
            pfile = NULL;
        }

        if((error == ROC_NET_RET_SUCCESS) || (error == ROC_NET_RET_PWDERR))
        {
            break;
        }
        sleep(1);
    }

    /*  如果链接失败，kill wpa_supplicant */
    if(connect_flag == 0)
    {
        memset(cmd_buf, 0, sizeof(cmd_buf));
        sprintf(cmd_buf, "killall wpa_supplicant");
        my_system(cmd_buf);
        memset(cmd_buf, 0, sizeof(cmd_buf));
        sprintf(cmd_buf, "rm -fr %s", SOCKET_WPA);
        my_system(cmd_buf);
        hi_eprintf("Connect Failed!(err=%d)%s\n", error,  ((error == ROC_NET_RET_TIMEOUT) ? "timeout" : ""));
        net_setting_last->connected = 0;

        /*  删除配置文件 */
        if((error == ROC_NET_RET_PWDERR) && (access(wifi_cfg_path, F_OK) == 0))
        {
            //unlink(wifi_cfg_path);
        }
    }
    else
    {
        hi_eprintf("Connect Successful!\n");
        net_setting_last->connected = TRUE;
        strcpy(net_setting_last->name, ((param->essid[0] != '\0') ? param->essid : "NONE"));
        memcpy(net_setting_last->bssid, param->bssid, sizeof(param->bssid));
        if(net_setting_last->method == ROC_DHCP)
        {
            /*  DHCP方式，自动分配IP等 */
            _set_dns_auto(devicename, ROC_TRUE);
            d_network_set_dhcp_mode(devicename, ROC_DHCP, ROC_TRUE);
        }
        else
        {
            if(d_ipv4_addr_check(net_setting_last->ip) && d_ipv4_addr_check(net_setting_last->mask) \
               && d_ipv4_addr_check(net_setting_last->gateway) && d_ipv4_addr_check(net_setting_last->dns))
            {
                Roc_IP_Config_t ip_conf;
                memset(&ip_conf, 0, sizeof(Roc_IP_Config_t));
                strncpy(ip_conf.ipaddr, net_setting_last->ip, strlen(net_setting_last->ip));
                strncpy(ip_conf.gateway, net_setting_last->gateway, strlen(net_setting_last->gateway));
                strncpy(ip_conf.mask, net_setting_last->mask, strlen(net_setting_last->mask));
                strncpy(ip_conf.dns, net_setting_last->dns, strlen(net_setting_last->dns));
                net_setting_last->method = ROC_STATIC;
                d_network_set_ip(devicename, &ip_conf);
                d_network_set_gateway(devicename, ip_conf.gateway);
                d_network_set_dnsserver(devicename, ip_conf.dns);
            }
            else
            {
                net_setting_last->method = ROC_DHCP;
                d_network_set_dhcp_mode(devicename, ROC_DHCP, ROC_TRUE);
            }
        }

        strcpy(net_setting_last->devicename, devicename);
        net_sleep_ms(50);
        _set_network_attribute(3, D_TRUE);
        net_sleep_ms(20);
        d_sem_post(hsem_test_net);
    }

_exit:
    if(access(WPA_TMP_FILE, F_OK) == 0)
    {
        unlink(WPA_TMP_FILE);
    }

    return error;
#endif
    return error;
}

D_S32 _wireless_scan( D_Char* devicename, D_S32 timeout, _Wireless_AP_Info_t *apinfo, D_S32 *ap_num)
{
    int error = ROC_NET_RET_SUCCESS;
#ifdef USE_SHELL_CMD
    FILE * pfile = NULL;
    char *cmd_buf[128] = {0,};
    int num = 0;

    memset(s_ap_rec, 0, sizeof(s_ap_rec));

    /* 检测device 是否 up */
    _check_wlan_up(devicename);

    memset(cmd_buf, 0, sizeof(cmd_buf));
    sprintf(cmd_buf, "iwlist %s scan", devicename);
    pfile = popen(cmd_buf, "r");
    if(!pfile)
    {
        printf("popen failed \n");
        error = ROC_NET_RET_FAILED;
        *ap_num = 0;
    }
    else
    {
        num = _analyse_ap_info(devicename, pfile, s_ap_rec);
        pclose(pfile);
        pfile = NULL;
        hi_eprintf("scan num : %d\n", num);
        num = (num > (*ap_num)) ? (*ap_num) : num;
        memcpy(apinfo, s_ap_rec, num * sizeof(_Wireless_AP_Info_t));
        *ap_num = num;
    }

#endif
    return error;
}

static void _wireless_init(void)
{
    memset(s_ap_rec, 0, sizeof(s_ap_rec));
#if SAVE_CONFIG_IN_SYS_DBASE
    {
        FILE *fp = NULL;
        int i;
        D_WifiApConfig param;
        D_NetWorkSettingDat set_param = {0,};

        if(D_OK == p_tvconf_get_network_setting_param(&set_param))
        {
            D_Char ip[16] = {0,};
            D_Char mask[16] = {0,};
            D_Char gateway[16] = {0,};
            D_Char dns[16] = {0,};
            D_Char bssid[24] = {0,};
            struct in_addr tmpaddr;

            fp = fopen(NETWORK_SETTING_FILE, "w+");
            if(fp != NULL)
            {
                set_param.devicename[sizeof(set_param.devicename) - 1] = 0;
                set_param.name[sizeof(set_param.name) - 1] = 0;
                tmpaddr.s_addr = set_param.ipaddr;
                sprintf(ip, "%s", (char *)inet_ntoa(tmpaddr));
                tmpaddr.s_addr = set_param.mask;
                sprintf(mask, "%s", (char *)inet_ntoa(tmpaddr));
                tmpaddr.s_addr = set_param.gateway;
                sprintf(gateway, "%s", (char *)inet_ntoa(tmpaddr));
                tmpaddr.s_addr = set_param.dns;
                sprintf(dns, "%s", (char *)inet_ntoa(tmpaddr));
                sprintf(bssid, "%02X:%02X:%02X:%02X:%02X:%02X", set_param.bssid[0], set_param.bssid[1], set_param.bssid[2], set_param.bssid[3], set_param.bssid[4], set_param.bssid[5]);
                fprintf(fp, "type:%d\ndevicename:%s\nconnected:%d\nmethod:%d\nname:%s\nbssid:%s\nip:%s\ngateway:%s\nmask:%s\ndns:%s\n",
                        (int)set_param.type, set_param.devicename,
                        (int)set_param.connected, (int)set_param.method,
                        set_param.name, bssid, ip, gateway, mask, dns);
                fclose(fp);
                fp = NULL;
            }
        }

        for(i = 0; i < D_TV_WIFI_AP_CNT; i++)
        {
            memset(&param, 0, sizeof(D_WifiApConfig));
            if(D_OK == p_tvconf_get_wifiap_param(&param, i))
            {
                _make_wifi_cfgfile(param.essid, param.bssid, param.key, param.key_len, 0);
            }
        }
    }
#endif
}

D_S32 d_wireless_get_status(D_Char* devicename, _WIRELESS_STATUS_e *status)
{
    int error = ROC_NET_RET_SUCCESS;
#ifdef USE_SHELL_CMD
    char cmd_buf[1024];
    char read_buf[2048];
    FILE * pfile;

    sprintf(cmd_buf, "iwconfig %s | grep \"Encryption key:off\"", devicename);
    pfile = popen(cmd_buf, "r");
    if(fgets(read_buf, sizeof(read_buf), pfile) != NULL)
    {
        *status = _WIRELESS_STATUS_IDLE;
    }
    else
    {
        *status = _WIRELESS_STATUS_CONNECTED;
    }
    if(pfile)
    {
        pclose(pfile);
    }
    return error;
#endif
    return error;
}

D_S32 d_wireless_reload_ko()
{
	char t[64] = {0};
	sprintf(t, "ifconfig wlan0 down");
	my_system(t);
	d_task_wait(50);
	#if ENABLE_WIFI_TYPE	== WIFI_8188EU
	sprintf(t, "rmmod 8188eu.ko");
	#else
	sprintf(t, "rmmod 8188fu.ko");
	#endif
	my_system(t);
	d_task_wait(50);
	#if ENABLE_WIFI_TYPE	== WIFI_8188EU
    	sprintf(t, "insmod ./8188eu.ko rtw_acs_auto_scan=1 rtw_acs_mode=1");
	#else
	sprintf(t, "insmod ./8188fu.ko rtw_acs_auto_scan=1 rtw_acs_mode=1");
	#endif
	my_system(t);
	d_task_wait(50);
	sprintf(t, "ifconfig wlan0 up");
	my_system(t);
	d_task_wait(50);
}

static int wireless_open_flag = 0;
/** @brief 无线网络open，即加载驱动*/
D_S32 d_wireless_open(D_U32 action)
{
    if(wireless_open_flag == 0 || action == 1)
    {
        char t[64] = {0};

        wireless_open_flag = 1;
        //sprintf(t, "insmod ./8188eu.ko");
        #if ENABLE_WIFI_TYPE	== WIFI_8188EU
        sprintf(t, "insmod ./8188eu.ko rtw_acs_auto_scan=1 rtw_acs_mode=1");
	#else
	 sprintf(t, "insmod ./8188fu.ko rtw_acs_auto_scan=1 rtw_acs_mode=1");
	#endif
        my_system(t);
        d_task_wait(50);
        sprintf(t, "ifconfig wlan0 up");
        my_system(t);
        d_task_wait(50);
    }
    return 0;
}

/** @brief 无线网络close，即卸载驱动*/
D_S32 d_wireless_close(D_U32 action)
{
    if(wireless_open_flag == 1 || action)
    {
        char t[32] = {0};
        wireless_open_flag = 0;
        sprintf(t, "ifconfig wlan0 down");
        my_system(t);
        d_task_wait(50);
	#if ENABLE_WIFI_TYPE	== WIFI_8188EU
        sprintf(t, "rmmod 8188eu.ko");
	#else
	sprintf(t, "rmmod 8188fu.ko");
	#endif
        my_system(t);
        d_task_wait(50);
    }
    return 0;
}

/** @brief 无线模组软复位*/
D_S32 d_wireless_sreset(void)
{
    D_S32 err = -1;
    
    if(wireless_open_flag == 1)
    {
        FILE* fp = NULL;
        #if ENABLE_WIFI_TYPE	== WIFI_8188EU
        if(access("/proc/net/rtl8188eu/wlan0/sreset", F_OK) == 0)
        {
            	fp = fopen("/proc/net/rtl8188eu/wlan0/sreset", "wb");
        }
	#else
	 if(access("/proc/net/rtl8188fu/wlan0/sreset", F_OK) == 0)
        {
		fp = fopen("/proc/net/rtl8188fu/wlan0/sreset", "wb");
        }
	#endif
        if(fp)
        {
            char *v = "1";
            fwrite(v, sizeof(char), strlen(v), fp);
            fclose(fp);
            err = 0;
        }
    }
    return err;
}

/** @brief 检查设备是否存在*/
D_S32 d_wireless_check_device(D_Char* devicename)
{
    D_S32 ret = -1;
    FILE * pfile = NULL;
    char cmd_buf[128] = {0,};
    char read_buf[2048];

    sprintf(cmd_buf, "ifconfig %s up", devicename);
    my_system(cmd_buf);
    d_task_wait(50);

    sprintf(cmd_buf, "ifconfig | grep \"%s\" | grep -v grep", devicename);
    pfile = popen(cmd_buf, "r");
    if(pfile != NULL)
    {
        if(fgets(read_buf, sizeof(read_buf), pfile) != NULL)
        {
            ret = 1;
        }
        pclose(pfile);
    }

    return ret;
}

/** @brief 无线网络断开连接*/
D_S32 d_wireless_disconnect(D_Char* devicename)
{
    int i = 0;
    int error = ROC_NET_RET_SUCCESS;

    connect_task_break_flag = D_TRUE;
    if(htask_net_start != D_INVALID_HANDLE)
    {
        d_task_join(htask_net_start);
        htask_net_start = D_INVALID_HANDLE;
    }
    if(net_setting_last)
    {
        net_setting_last->connected = 0;
        //net_setting_last->method = _NET_CONNECT_TYPE_WIRELESS;
    }
    _network_test_communicate_sync(); /*等待测试线程同步*/
    connect_task_break_flag = D_FALSE;
#ifdef USE_SHELL_CMD
    char cmd_buf[128];
    my_system("killall wpa_supplicant");
    my_system("killall udhcpc");
    my_system("route del default");
    d_task_wait(10);
    memset(cmd_buf, 0, sizeof(cmd_buf));
    sprintf(cmd_buf, "ifconfig %s down", devicename);
    my_system(cmd_buf);
    d_task_wait(20);
    memset(cmd_buf, 0, sizeof(cmd_buf));
    sprintf(cmd_buf, "ifconfig %s up", devicename);
    my_system(cmd_buf);


#endif
    return error;
}

/** @brief 网络初始化*/
D_S32 d_network_init(void)
{
//  char command[128];
    porting_print(_INFO_, ("network_init \n"));

    /* 目录不存在就创建*/
    d_create_dir(WIFI_CFG);

    if(D_INVALID_HANDLE == s_net_mtx)
    {
        s_net_mtx = d_mutex_create(NULL);
    }

    if( NULL == s_net_man )
    {
        if(access(_NET_DHCP_INFO_CFG, F_OK) == 0)
        {
            // 文件存在则删除此文件
            unlink(_NET_DHCP_INFO_CFG);
        }

        res_init();
        s_dns[0] = (D_Char *)(_res.nsaddr_list[0].sin_addr.s_addr);
        s_dns[1] = (D_Char *)(_res.nsaddr_list[1].sin_addr.s_addr);
        s_dns[2] = (D_Char *)(_res.nsaddr_list[2].sin_addr.s_addr);

        s_net_man = (_net_manage_t *)NET_MEMALLOC(_NET_DEVICE_MAX_NUM * sizeof(_net_manage_t));
        if( NULL == s_net_man )
        {
            porting_print(_ERRO_, (" malloc %x failed \n", (_NET_DEVICE_MAX_NUM * sizeof(_net_manage_t))));
            return -1;
        }
        else
        {
#if 0
            /*支持普通有线网络*/
            s_net_man[0].type       = _NET_CONNECT_TYPE_WIRED;
            strcpy(s_net_man[0].name, _DEF_NET0_NAME);
            strcpy(s_net_man[0].desc, _DEF_NET0_DESC);
            s_net_man[0].support    = 1;
            s_net_man[0].enable     = 1;
            s_net_man[0].dhcp_flag  = 0;
            s_net_man[0].data_rate  = _DEF_NET0_RATE;
            /*支持无线网络*/
            s_net_man[1].type       = _NET_CONNECT_TYPE_WIRELESS;
            strcpy(s_net_man[1].name, _WIF_NET0_NAME);
            strcpy(s_net_man[1].desc, _WIF_NET0_DESC);
            s_net_man[1].support    = 1;
            s_net_man[1].enable     = 0;
            s_net_man[1].dhcp_flag  = 0;
            s_net_man[1].data_rate  = _WIF_NET0_RATE;
#if 0
            /*目前不支持cable猫*/
            s_net_man[2].type       = _NET_CONNECT_TYPE_CABLE_MODEM;
            s_net_man[2].support    = 0;
            s_net_man[2].enable     = 0;
            s_net_man[2].dhcp_flag  = 0;
            /*目前不支持移动网络*/
            s_net_man[3].type       = _NET_CONNECT_TYPE_MOBILE_BROADBAND;
            s_net_man[3].support    = 0;
            s_net_man[3].enable     = 0;
            s_net_man[3].dhcp_flag  = 0;
#endif
#else
            d_wireless_open(0);
            _get_all_devices_info();
#endif
        }

        _wireless_init();

    }

    if(net_setting_last == NULL)
    {
        net_setting_file_info = (_net_cfg_t *)NET_MEMALLOC(sizeof(_net_cfg_t));
        net_setting_last = (_net_cfg_t *)NET_MEMALLOC(sizeof(_net_cfg_t));
        if( NULL == net_setting_last || NULL == net_setting_file_info)
        {
            porting_print(_ERRO_, (" malloc %x failed \n", (sizeof(_net_cfg_t))));
            if(net_setting_last)
            {
                NET_MEMFREE(net_setting_last);
                net_setting_last = NULL;
            }
            if(net_setting_file_info)
            {
                NET_MEMFREE(net_setting_file_info);
                net_setting_file_info = NULL;
            }
            return -1;
        }
        else
        {
            memset(net_setting_last, 0x00, (sizeof(_net_cfg_t)));
            memset(net_setting_file_info, 0x00, (sizeof(_net_cfg_t)));
            _get_network_attribute();
            net_setting_last->connected = 0;
        }
    }

    return 0;
}

/** @brief 网络反初始化*/
void d_network_uninit(void)
{
    if(s_net_man)
    {
        NET_MEMFREE(s_net_man);
        s_net_man = NULL;
    }
    if(net_setting_last)
    {
        NET_MEMFREE(net_setting_last);
        net_setting_last = NULL;
    }
    if(net_setting_file_info)
    {
        NET_MEMFREE(net_setting_file_info);
        net_setting_file_info = NULL;
    }
    if(D_INVALID_HANDLE != s_net_mtx)
    {
        d_mutex_destroy(s_net_mtx);
        s_net_mtx = D_INVALID_HANDLE;
    }
}

/** @brief 扫描无线网络
* @param devicename 设备名
* @param timeout 超时时间 ms
* @param apinfo   wifi ap信息
* @param ap_num   传入最大数目，返回取得数目
* @return 返回结果
*/
D_S32 d_wireless_scan(D_Char* devicename, D_S32 timeout, _Wireless_AP_Info_t *apinfo, D_S32 *ap_num)
{
    int i, j, cnt = 0, error = 0;
    D_Char passwd[64];
    D_Char filename[64];

    if(htask_net_start != D_INVALID_HANDLE)
    {
        d_task_join(htask_net_start);
        htask_net_start = D_INVALID_HANDLE;
    }

    error = _wireless_scan(devicename, timeout, apinfo, ap_num);
    if(error == ROC_NET_RET_SUCCESS && (*ap_num) > 0)
    {
        /*找到当前正在连接的记录*/
        for(i = 0; i < (*ap_num); i++)
        {
            /* 相同网卡的判断*/
            for(j = 0; j < cnt; j++)
            {
                if(0 == memcmp(apinfo[i].bssid, apinfo[j].bssid, sizeof(apinfo[i].bssid)))
                {
                    D_DUMP("apinfo[%d] %s == apinfo[%d] %s",  i, apinfo[i].essid, j, apinfo[j].essid);
                    break;
                }
            }

            if(j >= cnt)  /* 没有相同网卡时才保存*/
            {
                if(cnt != i)
                {
                    memcpy(&apinfo[cnt], &apinfo[i], sizeof(_Wireless_AP_Info_t));
                }
                memset(passwd, 0x00, sizeof(passwd));
                MAKE_WIFI_FILENAME(filename, apinfo[cnt].essid, apinfo[cnt].bssid);
                if(0 ==  d_get_wireless_password(filename, passwd))
                {
                    memcpy(apinfo[cnt].password, passwd, D_MIN(sizeof(passwd), sizeof(apinfo[cnt].password)));
                }

                if(net_setting_last->connected && (0 == strcmp(apinfo[cnt].essid, net_setting_last->name) && 0 == memcmp(apinfo[cnt].bssid, net_setting_last->bssid, sizeof(net_setting_last->bssid)) ))
                {
                    apinfo[cnt].connected = net_setting_last->connected;
                }
                cnt++;
            }
        }
    }
    *ap_num = cnt;

    return error;
}

/** @brief 连接无线网络
* @param devicename 设备名
* @param param   连接参数
* @return 返回连接结果
*/
D_S32 d_wireless_connect(D_Char *devicename, _Wireless_Param_t *param)
{
    int ret;
    wifi_connect_ing = D_TRUE;
    if(htask_net_start != D_INVALID_HANDLE)
    {
        d_task_join(htask_net_start);
        htask_net_start = D_INVALID_HANDLE;
    }

    if(strcmp(net_setting_last->devicename, devicename) == 0)
    {
        if(strcmp(net_setting_last->name, param->essid) != 0)
        {
            net_setting_last->method = ROC_DHCP;
        }
    }

    ret = _wireless_connect(devicename, param);
    if(ret == ROC_NET_RET_SUCCESS)
    {
        d_task_wait(100);
    }

    wifi_connect_ing = D_FALSE;
    return ret;
}

/** @brief 当已连接后获取网络信息
* @param devicename   设备名
* @param info   信息结构
* @return 返回
*/
D_S32 d_wireless_get_info(D_Char *devicename, _net_cfg_t *info)
{
    if(net_setting_last->connected && (strcmp(net_setting_last->devicename, devicename) == 0))
    {
        Roc_IP_Config_t ipinfo;
        memset(&ipinfo, 0, sizeof(ipinfo));
        strcpy(info->devicename, net_setting_last->devicename);
        d_network_get_ip_gateway(devicename, &ipinfo);
        d_network_get_dnsserver(devicename, ipinfo.dns);
        strcpy(info->ip, ipinfo.ipaddr);
        strcpy(info->mask, ipinfo.mask);
        strcpy(info->gateway, ipinfo.gateway);
        strcpy(info->dns, ipinfo.dns);
        info->method = net_setting_last->method;
        strcpy(info->name, net_setting_last->name);

        strcpy(net_setting_last->ip, ipinfo.ipaddr);
        strcpy(net_setting_last->mask, ipinfo.mask);
        strcpy(net_setting_last->gateway, ipinfo.gateway);
        strcpy(net_setting_last->dns, ipinfo.dns);
        _set_network_attribute(0, D_FALSE);
    }
    return  0;
}

/** @brief 当已连接后设置网络信息
* @param devicename   设备名
* @param info   信息结构
* @return 返回
*/
D_S32 d_wireless_set_info(D_Char *devicename, _net_cfg_t *info)
{
    if(info->method == ROC_DHCP)
    {
        _set_dns_auto(devicename, ROC_TRUE);
        d_network_set_dhcp_mode(devicename, ROC_DHCP, ROC_FALSE);
        net_setting_last->method = info->method;
    }
    else
    {
        Roc_IP_Config_t ipinfo;
        memset(&ipinfo, 0, sizeof(ipinfo));
        strcpy(ipinfo.ipaddr, info->ip);
        strcpy(ipinfo.mask, info->mask);
        strcpy(ipinfo.gateway, info->gateway);
        strcpy(ipinfo.dns, info->dns);
        strcpy(ipinfo.devicename, devicename);

        _set_dns_auto(devicename, ROC_FALSE);
        if(info->method != net_setting_last->method)
        {
            d_network_set_dhcp_mode(devicename, ROC_STATIC, ROC_FALSE);
        }
        d_network_set_ip(devicename, &ipinfo);
        d_network_set_gateway(devicename, ipinfo.gateway);
        d_network_set_dnsserver(devicename, ipinfo.dns);
        net_setting_last->method = info->method;
        strcpy(net_setting_last->ip, info->ip);
        strcpy(net_setting_last->gateway, info->mask);
        strcpy(net_setting_last->mask, info->gateway);
        strcpy(net_setting_last->dns, info->dns);
    }

    _set_network_attribute(1, D_FALSE);

    return  0;
}

/** @brief 当前连接的wifi名称
* @param devicename   设备名
* @param wifi_name   wifi名
* @return 返回
*/
D_S32 d_wireless_get_curr_wifi(D_Char *devicename, D_Char *wifi_name, D_Bool *connected)
{
    if(devicename && wifi_name && net_setting_last && (strcmp(net_setting_last->devicename, devicename) == 0))
    {
        //strcpy(wifi_name, net_setting_last->name);
        strcpy(wifi_name, cur_wifiname);
        if(connected)
        *connected = net_setting_last->connected;
    }
    return  0;
}

/** @brief 当前是否正属于wifi连接过程中
* @param wifi_name   wifi名
* @return 返回
*/
D_Bool d_wireless_is_connecting(void)
{
    return  wifi_connect_ing;
}

static void _wireless_connect_proc(void *p)
{
    _Wireless_Param_t param;
    D_Char filename[64];
    int error;
    wifi_connect_ing = D_TRUE;
    memset(&param, 0x00, sizeof(_Wireless_Param_t));
    if((net_setting_last->name[0] != '\0') && (strcmp(net_setting_last->name, "NONE") != 0))
    {
        strcpy(param.essid, net_setting_last->name);
    }
    memcpy(param.bssid, net_setting_last->bssid, sizeof(param.bssid));
    MAKE_WIFI_FILENAME(filename, param.essid, net_setting_last->bssid);
    if(0 == d_get_wireless_password(filename, param.key))
    {
        param.key_len = strlen(param.key);
    }
    error =  _wireless_connect(net_setting_last->devicename, &param);
    if((error != ROC_NET_RET_SUCCESS) && (error != ROC_NET_RET_PWDERR))
    {
        d_task_wait(1000);
        error = _wireless_connect(net_setting_last->devicename, &param);
    }
    
    if(p)
    {
        *((D_S32*)p) = error;
    }

    if(error == ROC_NET_RET_SUCCESS)
    {
        d_task_wait(100);
    }
    wifi_connect_ing = D_FALSE;
}

/** @brief 开机时，d_network_init后，检查并自动连接上一次的wifi*/
D_S32 d_wireless_start_check(D_S32 *error_check)
{
    D_S32 ret = -1;

    wifi_connect_ing = D_TRUE;
    if(htask_net_start != D_INVALID_HANDLE)
    {
        d_task_join(htask_net_start);
        htask_net_start = D_INVALID_HANDLE;
    }
    wifi_connect_ing = D_TRUE;
    if(net_setting_last)
    {
        D_TaskAttr TaskAttr;
        char name[32], wifi_cfg_path[256];
        D_Char filename[64];

        memset(name, 0x00, sizeof(name));
        memset(wifi_cfg_path, 0x00, sizeof(wifi_cfg_path));
        ret = 0;
        if((net_setting_last->name[0] == '\0') || (strcmp(net_setting_last->name, "NONE") == 0))
        {
            printf("[Network]no last ap !\n");
            ret = -1;
            goto __start_check_end;
        }

        strcpy(name, net_setting_last->name);
        MAKE_WIFI_FILENAME(filename, name, net_setting_last->bssid);
        sprintf(wifi_cfg_path, "%s/%s", WIFI_CFG, filename);
        if(access(wifi_cfg_path, F_OK) != 0)
        {
            printf("[Network]no cfg file: %s !\n", wifi_cfg_path);
            ret = -1;
            goto __start_check_end;
        }

        if(htask_net_start == D_INVALID_HANDLE)
        {
            D_TASK_ATTR_INIT(&TaskAttr);
            TaskAttr.name = "WifiConnect";
            TaskAttr.priority = 2;
            TaskAttr.stack_size = 16 * 1024;
            htask_net_start = d_task_create(&TaskAttr, _wireless_connect_proc, (void*)error_check);
            if (htask_net_start == D_INVALID_HANDLE)
            {
                printf("can't create WifiConnect task !\n");
                ret = -1;
                goto __start_check_end;
            }
            return ret;
        }
    }
__start_check_end:
    wifi_connect_ing = D_FALSE;
    return ret;
}

static D_U32 NetworkCommunicateStatus = 0;
static D_U32 NetworkConectStatus = 0;
static D_HEvent hevet_test_sync = D_INVALID_HANDLE;
static void _network_test_communicate_sync(void)
{
    if(hevet_test_sync != D_INVALID_HANDLE)
    {
        d_event_clear(hevet_test_sync);
        d_sem_post(hsem_test_net);
        d_event_wait(hevet_test_sync, (D_MSec) - 1);
    }    
}

static void _network_test_communicate_proc(void *p)
{
    D_U32 ok_flag, connect_flag;
    D_Time timeout = (D_Time) - 1;
    char hostname[32], cmd_buf[128], read_buf[1024];
    FILE * pfile = NULL;

    sprintf(hostname, "%s", "www.baidu.com");

    while(1)
    {
        d_sem_wait_timeout(hsem_test_net, timeout);
        ok_flag = 0;
        connect_flag = 0;
        if(net_setting_last && net_setting_last->connected)
        {
            connect_flag = 1;
            NetworkConectStatus = connect_flag;
            timeout = 5000;
#if 0
            sprintf(cmd_buf, "ping -c 1 -w 10 %s", hostname);
            //my_system(cmd_buf);
            pfile = popen(cmd_buf, "r");
            if(pfile)
            {
                while(NULL != fgets(read_buf, sizeof(read_buf), pfile))
                {
                    /* 判断是否错误 */
                    //hi_eprintf("%s\n", read_buf);
                    if((strstr(read_buf, "unreachable") != NULL) || (strstr(read_buf, "bad address") != NULL))
                    {
                        hi_eprintf("%s\n", read_buf);
                        break;
                    }
                    /* 判断是否成功链接 */
                    if(strstr(read_buf, "packets received,") != NULL)
                    {
                        int num_recv = 0;
                        char *ptr;

                        ptr = strstr(read_buf, "packets transmitted, ");
                        if(ptr != NULL)
                        {
                            ptr += strlen("packets transmitted, ");
                            sscanf(ptr, "%d", &num_recv);
                            //hi_eprintf("num_recv = %d\n", num_recv);
                            if(num_recv > 0)
                            {
                                ok_flag = 1;
                            }
                            else
                            {
                                hi_eprintf("%s\n", read_buf);
                            }
                        }
                        break;
                    }
                }
                pclose(pfile);
                pfile = NULL;
            }
#else
            ok_flag = 1;
#endif            
        }
        else
        {
            timeout = (D_Time) - 1;
        }
        NetworkCommunicateStatus = ok_flag;
        NetworkConectStatus = connect_flag;
        d_event_broadcast(hevet_test_sync);
    }
}
/** @brief 建立线程，检测网络连接状态*/
D_U32 d_network_test_communicate(void)
{
    D_TaskAttr TaskAttr;
    static D_HTask htask_net_test = D_INVALID_HANDLE;

    if(hsem_test_net == D_INVALID_HANDLE)
    {
        hsem_test_net = d_sem_create(NULL);
    }
    if(hevet_test_sync == D_INVALID_HANDLE)
    {
        hevet_test_sync = d_event_create(NULL);
    }
    if(htask_net_test == D_INVALID_HANDLE)
    {
        D_TASK_ATTR_INIT(&TaskAttr);
        TaskAttr.name = "WifiComTest";
        TaskAttr.priority = 2;
        TaskAttr.stack_size = 8 * 1024;
        htask_net_test = d_task_create(&TaskAttr, _network_test_communicate_proc, NULL);
        if (htask_net_test == D_INVALID_HANDLE)
        {
            printf("can't create WifiComTest task !\n");
            return -1;
        }
    }
    return 0;
}

/** @brief 取得当前网络连接状态*/
D_U32 d_network_get_connect_status(void)
{
    return NetworkConectStatus;
}

/** @brief 取得当前网络通信状态*/
D_U32 d_network_get_communicate_status(void)
{
    return NetworkCommunicateStatus;
}

/** @brief 取得当前连接的wifi信号信息
* @param devicename   设备名
* @param info   信息结构
* @return 返回结果
*/
D_S32 d_network_get_curr_info(D_Char* devicename, _net_cur_info_t* info)
{
    int error = -1;
    int valid = 0;

    struct iwreq iwr;
    int sockfd;

    info->quality = 0;
    info->signal = 0;
    info->noise = 0;  
  
    memset(&iwr, 0, sizeof(iwr));
    strcpy(iwr.ifr_name, devicename);
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    memset(info->name, 0, sizeof(info->name));
    iwr.u.essid.pointer = (caddr_t)(info->name);
    iwr.u.essid.length = sizeof(info->name);

    /* 取得essid，说明连接上了*/
    if(ioctl(sockfd, SIOCGIWESSID, &iwr) >= 0)
    {
        valid = 1;
        error = 0;
    }
    else
    {
        D_DUMP("ioctl SIOCGIWESSID err !\n");
    }

    if(valid)
    {
        struct iw_statistics stainfo; 

         /* 取得bssid, 即mac */
        if(ioctl(sockfd, SIOCGIWAP, &iwr) >= 0)
        {
            memcpy(info->bssid, iwr.u.ap_addr.sa_data, sizeof(info->bssid));
        }
        else
        {
            D_DUMP("ioctl SIOCGIWAP err !\n");
        }

        /* 信号强度质量信息*/
        memset(&stainfo, 0, sizeof(stainfo));
        iwr.u.data.pointer = (caddr_t)&stainfo;
        iwr.u.data.length = sizeof(stainfo);
        iwr.u.data.flags = 1;
        
        if(ioctl(sockfd, SIOCGIWSTATS, &iwr) >= 0)
        {
            info->quality = stainfo.qual.qual;
            info->signal = stainfo.qual.level;
            info->noise = stainfo.qual.noise;
        }
        else
        {
            D_DUMP("ioctl SIOCGIWSTATS err !\n");
        }
    }
    
    info->connected = (D_Bool)valid;
    
    close(sockfd);
    
#if 0
        D_DUMP("\"%s\", %02X%02X%02X%02X%02X%02X, %d, %d\n", info->name, info->bssid[0], info->bssid[1], info->bssid[2], \
               info->bssid[3], info->bssid[4], info->bssid[5], info->quality, info->signal);
#endif
    return error;
}

#endif
