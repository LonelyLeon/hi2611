//#include "hrchpll.h"
#include "dTypes.h"
#ifndef _D_CHPLL_H_
#define _D_CHPLL_H_

#ifdef  __cplusplus
extern "C"
{
#endif
typedef struct
{
	D_U16 freq;
	D_U8 sel;
}D_PllParam;
/** @brief
* @param */
D_Result d_pll_set_ddrfreq (D_U16 freq)D_FUNCPOSTFIT;
/** @brief
* @param */
D_U32 d_pll_get_freq (D_U8 sel)D_FUNCPOSTFIT;
/** @brief
* @param */
D_Result d_pll_set_freq (D_PllParam *param)D_FUNCPOSTFIT;
/** @brief
* @param */
D_Result d_pll_set_param_pll3(D_U16 fbdiv,D_U8 refdiv) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif

