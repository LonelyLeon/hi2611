#include "mcu_hal_comm.h"
#include "dIIC.h"
#include"dTypes.h"
#include"dTask.h"
#include "dDebug.h"

static D_HIIC hiic = 0;
MCU_HAL_API void_t hal_delay_us(uint8_t u8us)
{
#if 0
    volatile int i;
    int cnt = (u8us * 1000 / 25);
    for(i = 0; i < cnt; i++);
#else
    volatile int i = 0;
    D_U64 cnt, start, cur;

    cnt = d_rtc_timer_get_freq() /1000000 * ((D_U64)u8us);
    start = d_rtc_timer_get_counter();
    
    while(1)
    {
        i++;
        cur = d_rtc_timer_get_counter();
        if((cur - start) >= cnt)
        {
            break;
        }
        i = i;
    }
#endif
}

MCU_HAL_API void_t hal_delay_ms(uint16_t u16ms)
{
    d_task_wait(u16ms);
}

MCU_HAL_API uint8_t hal_i2c_readbytex(uint8_t u8addr, uint16_t u16index)
{
    uint8_t data_value = 0;
    uint8_t u8index[2];
    //u8addr = 0x7A;
    u8index[0] = u16index & 0xFF;
    u8index[1] = (u16index >> 8) & 0xFF;
    if(D_OK != d_iic_read(hiic, u8addr, u8index, &data_value, 1, 2))
    {
        D_ERROR("[vga2hdmi] i2c read error! %02X %04X\n", u8addr, u16index);
    }

    return data_value;
}
/*示例：完整的一次读写操作：I2CRW 7A 0184 A7;
解释：对应的I2C 时序为： 7A 84 01 A7；注意：寄存器索引的低字节先发，而后是高字节；
*/
MCU_HAL_API void_t hal_i2c_writebytex(uint8_t u8addr, uint16_t u16index, uint8_t u8value)
{
    uint8_t u8index[2];
    //u8addr = 0x7A;
    u8index[0] = u16index & 0xFF;
    u8index[1] = (u16index >> 8) & 0xFF;
    if(D_OK != d_iic_write(hiic, u8addr, u8index, &u8value, 1, 2))
    {
        D_ERROR("[vga2hdmi] i2c write error!%02X %04X %02X\n", u8addr, u16index, u8value);
    }
}


