#ifndef __PVR_H
#define __PVR_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

#include "dTypes.h"
#include "rbuf.h"
#include "dPvrPorting.h"
#include "dAV.h"
#include "dPvrReplay.h"
#include "dSys.h"
#include "dMem.h"
#include "dSem.h"
#include "dTask.h"
#include "dResource.h"
#include "dCBMan.h"
#include "dDebug.h"

#ifdef  __cplusplus
extern "C"
{
#endif

typedef struct
{
	D_ID dev_id;
	D_U8 *rep_buf_nc;
	D_U8 *rep_buf;
	D_U8 *rep_buf_phys;
	D_Bool running;
	D_HSem notify;
	D_PvrIntMask PvrReplayIntStatus;
	D_PvrRepTsParm ts_parm;
	D_PvrHandle hPvr;
	HidrvRbuf rbuf;
}PVRDATA;

D_Result p_pvr_open(void) D_FUNCPOSTFIT;

D_Result p_pvr_close(void) D_FUNCPOSTFIT;

void d_pvr_fill_buf(void);
PVRDATA * get_default_pvrdata(void);

#ifdef  __cplusplus
}
#endif
#endif
