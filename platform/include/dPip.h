#ifndef _D_PIP_H_
#define _D_PIP_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
//接口定义由lc完成
D_Result d_pip_open(void);
D_Result d_pip_close(void);
D_Result d_pip_start(void);
D_Result d_pip_stop(void);
D_Result d_pip_destory(void);

#ifdef  __cplusplus
}
#endif
#endif
