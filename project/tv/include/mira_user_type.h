#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __MIRA_USER_TYPE_H__
#define __MIRA_USER_TYPE_H__

typedef enum
{
    MIRA_PHONE_STATUS_NULL,
    MIRA_PHONE_STATUS_P2P_CONNECTING,
    MIRA_PHONE_STATUS_P2P_CONNECTED,
    MIRA_PHONE_STATUS_DHCPING,
    MIRA_PHONE_STATUS_DHCPED,
    MIRA_PHONE_STATUS_RTSPING,
    MIRA_PHONE_STATUS_CONNECTED,
    MIRA_PHONE_STATUS_END,
    MIRA_PHONE_STATUS_FAIL
}MiraPhoneStatus;

typedef void (*_user_media_init)(void);
typedef void (*_user_media_uninit)(void);
typedef void (*_user_media_handlePacket)(void* pData, unsigned int dataLeng);
typedef void (*_user_media_notify_state)(const char * name, const char * mac, int state);
#endif
