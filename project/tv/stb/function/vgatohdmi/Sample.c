/* MAIN.C file
*
* Copyright (c)
*/
// Sample Main File


#include "mcu_hal_comm.h"
#include "TX_API.h"
#include"dTypes.h"
#include"dIO.h"
#include"tx_proj_config.h"
#include"dMsg.h"
#include"dApp.h"
#include"dResource.h"
#include"pVgatohdmi.h"
#include "dDebug.h"

//#define TXDEBUG (1)

#define  VGA_RESET_IO  D_GPIO_PORT10_BIT1
#define  UNKNOWN_MODE        (0xFF)
/*
** Global variables
*/
bool_t   g_bWriteOnce = TRUE;
uint8_t  g_u8preMode  = UNKNOWN_MODE;

/*
** Chip reset routine
*/
void_t hw_chip_reset(void_t)
{

    D_Handle reset_handle;
    reset_handle = d_gpio_open(VGA_RESET_IO, D_PIO_BIT_OUTPUT);
    if(reset_handle  == D_INVALID_HANDLE)
    {
        D_ERROR("[vga2hdmi] io open failed!");
    }
    else
    {
        d_gpio_set(reset_handle);
        hal_delay_ms(10);
        d_gpio_clear(reset_handle);
        hal_delay_ms(100);
        d_gpio_set(reset_handle);
        hal_delay_ms(10);
    }
}

/*
** Global system initialization
*/
void_t Init_System(void_t)
{
    hw_chip_reset();
}

void_t Init_TX_Local(void_t)
{
    INITCONFIG_T  stInitParam;
    stInitParam.video_cfg  = TX_VIDEO_SYSTEM_PARAM;
    stInitParam.audio_cfg  = TX_AUDIO_SYSTEM_PARAM;
    TXAPI_Init(&stInitParam);
}

/* Primary main loop */
void_t Media_Process(void_t)
{
    uint8_t u8inVIndex;
    /* Get the current mode. */
    TXAPI_Get_Mode(&u8inVIndex);

    if (u8inVIndex != UNKNOWN_MODE)
    {
        if (u8inVIndex != g_u8preMode)
        {
#ifdef TXDEBUG
            D_DUMP("[vga2hdmi] ==> Mode change to: %d\n", (int)u8inVIndex);
#endif
            TXAPI_Mute_All(TRUE);
            TXAPI_Set_Video(u8inVIndex);
            TXAPI_Set_Audio();
            TXAPI_Mute_All(FALSE);
        }
        g_u8preMode  = u8inVIndex;
        g_bWriteOnce = TRUE;
    }
    else
    {
        if (g_bWriteOnce)
        {
            TXAPI_Mute_All(TRUE);
            g_bWriteOnce = FALSE;
        }
#ifdef TXDEBUG
        D_DUMP("[vga2hdmi] No Signal\n");
#endif
        g_u8preMode = UNKNOWN_MODE;
    }
}

#if 0
/* system main loop */
void_t main(void_t)
{
    Init_System();
    Init_TX_Local();

    /* Power up */
    hal_timer_set(TIMER0, SYS_TIMEOUT_300MS);
    hal_timer_set(TIMER1, 0);
    hal_timer_set(TIMER2, 0);

    while (1)
    {
        if (hal_timer_get(TIMER0) >= SYS_TIMEOUT_300MS)
        {
            Media_Process();
            hal_timer_set(TIMER0, 0);
        }
        hal_delay_ms(5);
    }
}
#endif

static D_Result
vga_callback (D_Msg *msg) D_FUNCPOSTFIT
{

    /*消息处理*/
    switch (msg->type)
    {
        case D_MSG_APP_CREATE:
            /*任务创建*/
            Init_System();
            Init_TX_Local();
            d_app_set_timeout(d_app_self(), 300);
            break;
        case D_MSG_APP_DESTROY:
            /*应用销毁*/
            break;

        case D_MSG_APP_TIMEOUT:
            Media_Process();
            //hal_delay_ms(5);

            break;

        default:
            break;
    }

    return D_OK;
}
/** @brief TV模块初始化*/
D_HApp  vga_happ = D_INVALID_HANDLE;
D_Result
d_vga_open (void) D_FUNCPOSTFIT
{
    if(vga_happ == D_INVALID_HANDLE)
    {
        /*创建应用*/
        vga_happ = d_app_create ("vga2hdmi", 6, D_TV_TASK_STACK_SIZE, D_TV_QUEUE_SIZE, vga_callback, (D_Ptr) NULL);

        d_app_sync (vga_happ);
    }
    return D_OK;
}

/** @brief TV模块释放*/
D_Result
d_vga_close (void) D_FUNCPOSTFIT
{
    if(vga_happ != D_INVALID_HANDLE)
    {
        d_app_destroy (vga_happ);
        vga_happ = D_INVALID_HANDLE;
    }
    return D_OK;
}

