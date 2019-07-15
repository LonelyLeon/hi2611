#ifndef _D_IO_H_
#define _D_IO_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

typedef enum
{
	D_PIO_BIT_INPUT = 0x00,
	D_PIO_BIT_OUTPUT,
	D_PIO_BIT_OPEN_DRAIN,
	D_PIO_BIT_2ND_FUNCTION,
	D_PIO_BIT_INT_LOW_PULSE,
	D_PIO_BIT_INT_UP_PULSE,
} D_GPIO_BitConfig;

typedef enum
{
    D_GPIO_PORT0_BIT0 = 0x00,
    D_GPIO_PORT0_BIT1,
    D_GPIO_PORT0_BIT2,
    D_GPIO_PORT0_BIT3,
    D_GPIO_PORT0_BIT4,
    D_GPIO_PORT0_BIT5,
    D_GPIO_PORT0_BIT6,
    D_GPIO_PORT0_BIT7,
    D_GPIO_PORT1_BIT0,//10
    D_GPIO_PORT1_BIT1,
    D_GPIO_PORT1_BIT2,
    D_GPIO_PORT1_BIT3,
    D_GPIO_PORT1_BIT4,
    D_GPIO_PORT1_BIT5,
    D_GPIO_PORT1_BIT6,
    D_GPIO_PORT1_BIT7,
    D_GPIO_PORT2_BIT0,//20
    D_GPIO_PORT2_BIT1,
    D_GPIO_PORT2_BIT2,
    D_GPIO_PORT2_BIT3,
    D_GPIO_PORT2_BIT4,
    D_GPIO_PORT2_BIT5,
    D_GPIO_PORT2_BIT6,
    D_GPIO_PORT2_BIT7,
    D_GPIO_PORT3_BIT0,//30
    D_GPIO_PORT3_BIT1,
    D_GPIO_PORT3_BIT2,
    D_GPIO_PORT3_BIT3,
    D_GPIO_PORT3_BIT4,
    D_GPIO_PORT3_BIT5,
    D_GPIO_PORT3_BIT6,
    D_GPIO_PORT3_BIT7,
    D_GPIO_PORT4_BIT0,//40
    D_GPIO_PORT4_BIT1,
    D_GPIO_PORT4_BIT2,
    D_GPIO_PORT4_BIT3,
    D_GPIO_PORT4_BIT4,
    D_GPIO_PORT4_BIT5,
    D_GPIO_PORT4_BIT6,
    D_GPIO_PORT4_BIT7,
    D_GPIO_PORT5_BIT0,//50
    D_GPIO_PORT5_BIT1,
    D_GPIO_PORT5_BIT2,
    D_GPIO_PORT5_BIT3,
    D_GPIO_PORT5_BIT4,
    D_GPIO_PORT5_BIT5,
    D_GPIO_PORT5_BIT6,
    D_GPIO_PORT5_BIT7,
    D_GPIO_PORT6_BIT0,//60
    D_GPIO_PORT6_BIT1,
    D_GPIO_PORT6_BIT2,
    D_GPIO_PORT6_BIT3,
    D_GPIO_PORT6_BIT4,
    D_GPIO_PORT6_BIT5,
    D_GPIO_PORT6_BIT6,
    D_GPIO_PORT6_BIT7,
    D_GPIO_PORT7_BIT0,//70
    D_GPIO_PORT7_BIT1,
    D_GPIO_PORT7_BIT2,
    D_GPIO_PORT7_BIT3,
    D_GPIO_PORT7_BIT4,
    D_GPIO_PORT7_BIT5,
    D_GPIO_PORT7_BIT6,
    D_GPIO_PORT7_BIT7,  
	D_GPIO_PORT8_BIT0,//80
    D_GPIO_PORT8_BIT1,
    D_GPIO_PORT8_BIT2,
	D_GPIO_PORT8_BIT3,
	D_GPIO_PORT8_BIT4,
	D_GPIO_PORT8_BIT5,
	D_GPIO_PORT8_BIT6,
	D_GPIO_PORT8_BIT7,
	D_GPIO_PORT9_BIT0,//90
	D_GPIO_PORT9_BIT1,
	D_GPIO_PORT9_BIT2,
	D_GPIO_PORT9_BIT3,
	D_GPIO_PORT9_BIT4,
	D_GPIO_PORT9_BIT5,
	D_GPIO_PORT9_BIT6,
	D_GPIO_PORT9_BIT7,
	D_GPIO_PORT10_BIT0,//10.0
    D_GPIO_PORT10_BIT1,
	D_GPIO_PORT10_BIT2,
	D_GPIO_PORT10_BIT3,
    D_GPIO_PORT10_BIT4,
	D_GPIO_PORT10_BIT5,
	D_GPIO_PORT10_BIT6,
	D_GPIO_PORT10_BIT7,
	D_GPIO_PORT11_BIT0,//11.0
    D_GPIO_PORT11_BIT1,
	D_GPIO_PORT11_BIT2,
	D_GPIO_PORT11_BIT3,
	D_GPIO_PORT11_BIT4,
	D_GPIO_PORT11_BIT5,
    D_GPIO_PORT11_BIT6,
    D_GPIO_PORT11_BIT7,
	D_GPIO_PORT12_BIT0,//12.0
    D_GPIO_PORT12_BIT1,
	D_GPIO_PORT12_BIT2,
	D_GPIO_PORT12_BIT3,
	D_GPIO_PORT12_BIT4,
    D_GPIO_PORT12_BIT5,
	D_GPIO_PORT12_BIT6,
	D_GPIO_PORT12_BIT7,
	D_GPIO_PORT13_BIT0,//13.0
	D_GPIO_PORT13_BIT1,
	D_GPIO_PORT13_BIT2,
	D_GPIO_PORT13_BIT3,
    D_GPIO_PORT13_BIT4,
	D_GPIO_PORT13_BIT5,
	D_GPIO_PORT13_BIT6,
    D_GPIO_PORT13_BIT7,
    D_GPIO_PORT14_BIT0,//14.0
	D_GPIO_PORT14_BIT1,
	D_GPIO_PORT14_BIT2,
	D_GPIO_PORT14_BIT3,
	D_GPIO_PORT14_BIT4,
	D_GPIO_PORT14_BIT5,
	D_GPIO_PORT14_BIT6,
	D_GPIO_PORT14_BIT7,
	D_GPIO_PORT15_BIT0,//15.0
	D_GPIO_PORT15_BIT1,
	D_GPIO_PORT15_BIT2,
	D_GPIO_PORT15_BIT3,
	D_GPIO_PORT15_BIT4,
	D_GPIO_PORT15_BIT5,
	D_GPIO_PORT15_BIT6,
	D_GPIO_PORT15_BIT7,
    D_GPIO_INVALID = 0xff
}D_GPIO_PortBit;


D_Handle d_gpio_open(D_GPIO_PortBit port_bit, D_GPIO_BitConfig state) D_FUNCPOSTFIT;
D_Result d_gpio_close(D_Handle handle) D_FUNCPOSTFIT;
D_Result d_gpio_set(D_Handle handle) D_FUNCPOSTFIT;
D_Result d_gpio_clear(D_Handle handle) D_FUNCPOSTFIT;
D_U32 d_gpio_get(D_Handle handle) D_FUNCPOSTFIT;
D_Result d_gpio_setconfig(D_Handle handle, D_GPIO_BitConfig state)D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
