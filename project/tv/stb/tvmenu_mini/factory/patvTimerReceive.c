#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "pConfig.h"
#include "pPlayer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"

D_HTask aging_ctrl_task_handle = D_INVALID_HANDLE;
static D_Bool aging_ctrl_running = D_FALSE;
static void aging_ctrl_task(void *p) D_FUNCPOSTFIT
{
    static D_U8 times = 0;

    while(aging_ctrl_running == D_TRUE)
    {
        if(times == 1)
        {
            times = 2;
            d_PowerOff_Led_Ctrl(0);
            D_DUMP("old_mod:0xFF, 0x00, 0x00\n");
            d_lvds_Set_Aging(1, 0xFF, 0x00, 0x00);
        }
        else if(times == 2)
        {
            times = 3;
            d_PowerOff_Led_Ctrl(1);
            D_DUMP("old_mod:0x00, 0xFF, 0x00\n");
            d_lvds_Set_Aging(1, 0x00, 0xFF, 0x00);
        }
        else if(times == 3)
        {
            times = 4;
            d_PowerOff_Led_Ctrl(0);
            D_DUMP("old_mod: 0x00, 0x00, 0xFF\n");
            d_lvds_Set_Aging(1, 0x00, 0x00, 0xFF);

        }
        else
        {
            times  = 1;
            d_PowerOff_Led_Ctrl(1);
            D_DUMP("old_mod: 0xFF, 0xFF, 0xFF\n");
            d_lvds_Set_Aging(1, 0xFF, 0xFF, 0xFF);

        }
        d_task_wait(3000);
    }
}
D_Result aging_Ctrl_open(void)
{
    D_TaskAttr ta;
    ta.id = 0;
    ta.name = "aging_ctrl";
    ta.priority = 3;
    ta.stack_size = 4096;
	if(aging_ctrl_task_handle != D_INVALID_HANDLE)
	{
	    d_task_join(aging_ctrl_task_handle);
	}	
    d_PowerOff_Led_Ctrl(0);
    aging_ctrl_running = D_TRUE;
    aging_ctrl_task_handle = d_task_create(&ta, aging_ctrl_task, NULL);
    if(aging_ctrl_task_handle == D_INVALID_HANDLE)
    {
        D_ERROR("Can not create aging_ctrl task!\n");
        return D_ERR;
    }
    return D_OK;
}

D_Result aging_Ctrl_close(void)
{
    D_U8 aging = 0;
	
    p_tvconf_set_aging(&aging);
	if(aging_ctrl_running == D_TRUE)
	{
	    aging_ctrl_running = D_FALSE;
	    d_PowerOff_Led_Ctrl(0);
	    d_task_join(aging_ctrl_task_handle);
	}
    aging_ctrl_task_handle = D_INVALID_HANDLE;
    d_lvds_Set_Aging(0, 0xFF, 0xFF, 0xFF);

    return D_OK;
}

/** @brief ¶¨Ê±Æ÷²Ëµ¥*/
D_Result
p_atv_timer_set_show (void) D_FUNCPOSTFIT
{
    D_U8 aging = 1;
    p_tvconf_set_aging(&aging);
    d_lvds_Set_Aging(1, 0xFF, 0xFF, 0xFF);
    d_PowerOff_Led_Ctrl(1);
    aging_Ctrl_open();
}

