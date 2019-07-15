#ifndef _TX_GLOBAL_H_
#define _TX_GLOBAL_H_

#include "mcu_hal_comm.h"

/*========================================
 * Enums and structures
 *=======================================*/
#ifndef TX_API
    #define TX_API  
#endif

#ifndef TX_HAL_API
    #define TX_HAL_API  
#endif

#ifndef TX_HAL_EXTERN
    #define TX_HAL_EXTERN   extern
#endif

typedef enum _E_TX_ERR_CODE
{
    ATXERR_OK           = 0x00,
    ATXERR_SIGNAL_LOST  = 0xF0,
    ATXERR_NOT_PRESENT  = 0xF1,    
    ATXERR_EDID_FAIL    = 0xF2,      
    ATXERR_FATAL        = 0xF3,        
    ATXERR_UNKNOWN      = 0xFF     
} ATX_ERR;

/*========================================
 * Global definitions
 *=======================================*/
#define TX_NUM_OF_DEVICES           (1)

#ifndef TX_NUM_OF_INSTANCES
#define TX_NUM_OF_INSTANCES         TX_NUM_OF_DEVICES
#endif

#define TX_DEV_NAME                 ("AQUARIUS")
#define UNKNOWN_MODE                (0xFF)

#endif
