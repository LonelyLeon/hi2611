#ifndef _MCU_HAL_INCLUDES_H_
#define _MCU_HAL_INCLUDES_H_

#if defined(_KEIL_COMPILER_)
    #include <intrins.h>
    #include <stdio.h>  
    #include <math.h>
    #include <string.h>
    //  
    #include "i8051\N76E003\Include\N76E003.h"
    #include "i8051\N76E003\Include\SFR_Macro.h"
	#include "i8051\N76E003\Include\Function_Define.h"
	#include "i8051\N76E003\Include\Common.h"
	#include "mcu_hal_typedef.h"
    #include "mcu_hal_gpio.h"
	#include "keil_proj_config.h"
	

#elif defined(_GNU_COMPILER_)
	#include <stdlib.h>
	#include "mcu_hal_typedef.h"
#else	
	#include <stdlib.h>
	#include "stm8s.h"
	#include "mcu_hal_typedef.h"
	#include "stm8s\stm8s_lib.h"

	#include "stm8s_proj_config.h"  /* For STM8S project only */
	#include "stm8s\stm8s_it.h"
	
#endif 

#include "mcu_hal_timer.h"
#include "mcu_hal_i2c.h"

#ifdef _INCLUDE_LIB_UART_
    #include "mcu_hal_uart.h"
#endif 

#ifdef _INCLUDE_LIB_KEYBOARD_
    #include "mcu_hal_key.h"
#endif

#endif
