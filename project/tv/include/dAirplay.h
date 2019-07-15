/**
 * @file daurplay.h
 * external api header.
*/

#ifndef D_AIRPLAY_H
#define D_AIRPLAY_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dTypes.h"
#include "dSem.h"
#include "player_api.h"

/* 是否使用drm硬件解密*/
#define AIRPLAY_USE_DRM (1)

#define USER_MSG_PARAM1_AIRPLAY_VOLUME  0xeeda0001
#define USER_MSG_PARAM1_AIRPLAY_STATUS  0xeeda0002
#define USER_MSG_PARAM1_AIRPLAY_MOVIE_PLAY  0xeeda0003
#define USER_MSG_PARAM1_AIRPLAY_MOVIE_STOP  0xeeda0004
#define USER_MSG_PARAM1_AIRPLAY_MOVIE_SEEK  0xeeda0005
#define USER_MSG_PARAM1_AIRPLAY_MOVIE_STATUS     0xeeda0006


#define D_AIRPLAY_STATUS_START (0x8000)
#define D_AIRPLAY_STATUS_STOP   (0x8001)
#define D_AIRPLAY_STATUS_VID_OK (0x8002)

#if 0
typedef enum
{
    AIRPLAYER_STATUS_PLAYING,
    AIRPLAYER_STATUS_FINISHED,
    AIRPLAYER_STATUS_STOP,
    AIRPLAYER_STATUS_PAUSED,
    AIRPLAYER_STATUS_SEEK,
    AIRPLAYER_STATUS_DATA_BUFFER,
} D_AirPlayStatus;
#endif

typedef struct _mplayer_status
{
    PlayStatus state;
    //D_AirPlayStatus state;
    int percent;
    int curTime;
    int totalTime;
} D_MoivePlayerStatus;

typedef struct _mplayer_control
{
    int (* _movie_play)(int id, char *ip, char * url);
    void (* _movie_stop)(int id);
    void (* _movie_pause)(int id);
    void (* _movie_resume)(int id);
    void (* _movie_seek)(int id, unsigned int sec);
    D_MoivePlayerStatus * (* _get_status)(int id);
    int (* _get_volume)(int id);
    void (* _set_volume)(int id, unsigned int volume);
    void (* _set_mute)(int id, unsigned int mute);
} D_MoivePlayerControl;


extern D_MoivePlayerControl _airplay_mpc;

extern D_Result airplay_open(char * name);
extern D_Result airplay_close(void);

extern void airplay_push_video_sync(const D_Ptr data, D_Size size, D_S64 pts);
extern void airplay_set_audio_param(D_Int bits, D_Int channels, D_Int sample_rate);
extern void airplay_push_audio_sync(const D_Ptr data, D_Size size, D_S64 pts);
extern int airplay_notify_user_status(D_Int status, D_Int music);
extern void airplay_set_play_volume(D_Int volume);
/* airplay使用硬件drm进行解密*/
extern void airplay_drm_ctr128_decrypt(const unsigned char *in, unsigned char *out, size_t length,
                                       unsigned char key[16], unsigned char ivec[16], unsigned int *num);

extern void d_airplay_set_playtime(D_U32 playtime);
extern void d_airplay_set_totaltime(D_U32 totaltime);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* D_AIRPLAY_H */
