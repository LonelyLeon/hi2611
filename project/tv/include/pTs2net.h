#ifndef __P_TS2NET_H
#define __P_TS2NET_H

#include "dTypes.h"

#ifdef  __cplusplus
extern "C"
{
#endif

extern D_Result d_ts2net_open(D_Char *dev_name);

extern D_Result d_ts2net_close(void);

#ifdef  __cplusplus
}
#endif
#endif

