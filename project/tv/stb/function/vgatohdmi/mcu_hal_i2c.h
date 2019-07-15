#ifndef _MCU_HAL_I2C_H_
#define _MCU_HAL_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 16-bit index */
MCU_HAL_API  uint8_t    hal_i2c_readbytex(uint8_t u8addr, uint16_t u16index);
MCU_HAL_API  void_t     hal_i2c_writebytex(uint8_t u8addr, uint16_t u16index, uint8_t u8value);

#ifdef __cplusplus
}
#endif

#endif
