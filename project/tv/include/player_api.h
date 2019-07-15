#ifndef D_PLAYER_API_H
#define D_PLAYER_API_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

typedef enum {
	PLAYER_STATUS_PLAYING,
	PLAYER_STATUS_FINISHED,
	PLAYER_STATUS_STOP,
	PLAYER_STATUS_PAUSED,
	PLAYER_STATUS_SEEK,
	PLAYER_STATUS_DATA_BUFFER,
}PlayStatus;

typedef struct _player_status{
	PlayStatus state;
	int percent;
	int curTime;
	int totalTime;
}PlayerStatus;

typedef struct _player_control {
	void (* _player_play)(char * title, char * url);
	void (* _player_stop)(void);
	PlayerStatus * (* _player_get_status)(void);
	void (* _player_pause)(void);
	void (* _player_resume)(void);
	void (* _player_seek)(unsigned int sec);
	int (* _player_get_volume)(void);
	void (* _player_set_volume)(unsigned int volume);
	void (* _player_set_mute)(unsigned int mute); //1: mute 0: unmute
}PlayerControl;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* D_PLAYER_API_H */

