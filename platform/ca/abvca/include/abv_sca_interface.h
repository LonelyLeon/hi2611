
#ifndef __ABV_SCA_INTERFACE_H__
#define __ABV_SCA_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif
#include  "abv_ca_types.h"


ABV_Boolean ABV_SCA_Sys_Init(void);

 ABV_Boolean ABV_SAC_CryptEcm(ABV_UInt8* ecm, ABV_UInt8*CW);

/*********************************************************************/
#ifdef __cplusplus
}
#endif
#endif 
