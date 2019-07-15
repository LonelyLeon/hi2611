#ifndef _MCU_HAL_TIMER_H_
#define _MCU_HAL_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Delay routines */
MCU_HAL_API  void_t     hal_delay_ms(uint16_t u16ms);
MCU_HAL_API  void_t     hal_delay_us(uint8_t u8us);

#ifdef __cplusplus
}
#endif

#endif 
