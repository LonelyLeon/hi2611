/** @file
* @brief 网络套接字定义
* @author 李臣
* @date 2014-05-10 李臣: 建立文件
*/
#ifndef __SOCK_INET_H__
#define __SOCK_INET_H__

#include "dTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 255.255.255.255 */
#define INADDR_NONE         ((D_U32)0xffffffffUL)
/** 127.0.0.1 */
#define INADDR_LOOPBACK     ((D_U32)0x7f000001UL)
/** 0.0.0.0 */
#define INADDR_ANY          ((D_U32)0x00000000UL)
/** 255.255.255.255 */
#define INADDR_BROADCAST    ((D_U32)0xffffffffUL)

D_U32 inet_addr(const D_Char *cp);
int inet_aton(const D_Char *cp, struct in_addr *addr);
D_Char* inet_ntoa(struct in_addr addr);
D_Char* inet_ntoa_r(struct in_addr addr, D_Char *buf, int buflen);

struct hostent {
    char  *h_name;      /* Official name of the host. */
    char **h_aliases;   /* A pointer to an array of pointers to alternative host names,
                           terminated by a null pointer. */
    int    h_addrtype;  /* Address type. */
    int    h_length;    /* The length, in bytes, of the address. */
    char **h_addr_list; /* A pointer to an array of pointers to network addresses (in
                           network byte order) for the host, terminated by a null pointer. */
#define h_addr h_addr_list[0] /* for backward compatibility */
};

struct addrinfo {
    int               ai_flags;      /* Input flags. */
    int               ai_family;     /* Address family of socket. */
    int               ai_socktype;   /* Socket type. */
    int               ai_protocol;   /* Protocol of socket. */
    socklen_t         ai_addrlen;    /* Length of socket address. */
    struct sockaddr  *ai_addr;       /* Socket address of socket. */
    char             *ai_canonname;  /* Canonical name of service location. */
    struct addrinfo  *ai_next;       /* Pointer to next in list. */
};

struct hostent *gethostbyname(const char *name);
int gethostbyname_r(const char *name, struct hostent *ret, char *buf,
                size_t buflen, struct hostent **result, int *h_errnop);
int getaddrinfo(const char *nodename,
       const char *servname,
       const struct addrinfo *hints,
       struct addrinfo **res);
void freeaddrinfo(struct addrinfo *ai);

#define htons   d_htons
#define ntohs   d_htons
#define htonl   d_htonl
#define ntohl   d_htonl

#ifdef __cplusplus
}
#endif
#endif

