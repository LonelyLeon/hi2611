#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dTime.h"
#include "dDate.h"
#include "dDBase.h"
#include "pConfig.h"
#include "pPlayer.h"
#include "pUSBUpGrade.h"
#include "dSys.h"
#include "dCBMan.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "software_update_window.c"

#define TV_USB_FILE_NAME                "c:/usb_upgrade.bin"

typedef struct
{
    D_Char manu_name[34];
    D_Char hw_version[32];
    D_Char sw_version[32];
    D_Char stb_id[32];
    D_Char manu_id[34];
    D_Char release_date[64];
    D_Char chip_id[32];
    D_U32  chip_id_length;
} D_AtvInfoData;

static D_AtvInfoData* atvinfo_data = NULL;
static D_U16 usb_total_partition;
D_U8 usb_vol_index[D_DEVICE_PARTITION_MAX];
static D_Handle fs;
static D_Handle usb_upgrade_end;
static D_Int logic_drv;
static char UpgradeProcess[8];

/** @brief 解析编译时间*/
static D_Result get_standard_date(D_Date_Ext *date)
{
    D_Char *ptr;
    D_Char *mon[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    D_U32 idx;
    D_U32 tmp;

    if(!date)
        return D_ERR;

    memset(date, 0, sizeof(D_Date_Ext));

    ptr = __DATE__;
    for(idx = 0; idx < 12; idx++)
    {
        if(strstr(ptr, mon[idx]))
        {
            date->mon = idx + 1;
            break;
        }
    }

    while(*ptr != ' ')
        ptr ++;
    while(*ptr == ' ')
        ptr ++;
    if(ptr)
    {
        date->day = (D_U8)strtoul(ptr, NULL, 10);
    }

    while(*ptr != ' ')
        ptr ++;
    while(*ptr == ' ')
        ptr ++;
    if(ptr)
    {
        date->year = (D_U16)strtoul(ptr, NULL, 10) - 1900;
    }

    ptr = __TIME__;
    tmp = 0;
    sscanf(ptr, "%d", &tmp);
    date->hour = (D_U8)tmp;

    ptr = strstr(ptr, ":");
    if(ptr)
    {
        ptr++;
        tmp = 0;
        sscanf(ptr, "%d", &tmp);
        date->min = (D_U8)tmp;
    }

    ptr = strstr(ptr, ":");
    if(ptr)
    {
        ptr++;
        tmp = 0;
        sscanf(ptr, "%d", &tmp);
        date->sec = (D_U8)tmp;
    }

    return D_OK;
}

/** @brief 升级失败提示*/
static D_Result show_failed_msg (void) D_FUNCPOSTFIT
{
    D_Visual *vis;
    //需要添加升级失败提示信息
    D_DUMP("show_failed_msg \n");
    if(usb_upgrade_end == D_INVALID_HANDLE)
    {
        return D_ERR;
    }
    d_usb_upgrade_destroy(usb_upgrade_end);
    usb_upgrade_end = D_INVALID_HANDLE;
    p_fp_set_enable(D_TRUE);
    vis = d_frame_get_control( &software_update_window, ID_UPGRADE_LABEL_PROGRESS );
    if(vis)
    {
        d_vis_show(vis, D_FALSE);
    }
    vis = d_frame_get_control( &software_update_window, ID_UPGRADE_PROGRESS );
    if(vis)
    {
        d_vis_show(vis, D_FALSE);
    }
    d_atv_pop_msg_show (D_POP_MSG_PRIO_MSG_2,
    D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG,
    NULL, d_gui_get_text(atv_IDS_UPGRADE_FAIL),
    1500, D_POP_MSG_RESPONSE_ALL_NOT, D_FALSE, NULL, 0);
    return D_OK;
}

/** @brief 升级成功提示*/
static D_Result show_success_msg (void) D_FUNCPOSTFIT
{
    D_Visual *vis;

    //需要添加升级成功提示信息
    D_DUMP("show_success_msg \n");
    if(usb_upgrade_end == D_INVALID_HANDLE)
    {
        return D_ERR;
    }
    d_usb_upgrade_destroy(usb_upgrade_end);
    usb_upgrade_end = D_INVALID_HANDLE;
    vis = d_frame_get_control( &software_update_window, ID_UPGRADE_LABEL_PROGRESS );
    if(vis)
    {
        d_vis_show(vis, D_FALSE);
    }
    vis = d_frame_get_control( &software_update_window, ID_UPGRADE_PROGRESS );
    if(vis)
    {
        d_vis_show(vis, D_FALSE);
    }
    p_fp_set_enable(D_TRUE);
    d_atv_pop_msg_show (D_POP_MSG_PRIO_MSG_2,
    D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG,
    NULL, d_gui_get_text(atv_IDS_UPGRADE_SUC),
    1500, D_POP_MSG_RESPONSE_ALL_NOT, D_FALSE, d_sys_reboot, 0);

}

/** @brief 升级进度提示*/
static void show_process_msg (D_U8 process) D_FUNCPOSTFIT
{
    D_Visual *vis;
    //需要添加升级进度提示信息
    D_DUMP("show_process_msg[%d] \n", process);
    vis = d_frame_get_control( &software_update_window, ID_UPGRADE_LABEL_PROGRESS );
    if(vis)
    {
        if (! (vis->flags & D_VIS_FL_SHOW))
        {
            d_vis_show(vis, D_TRUE);
        }
        sprintf(UpgradeProcess, "%d %%", process);
        d_label_set_text( vis, UpgradeProcess );
    }
    vis = d_frame_get_control( &software_update_window, ID_UPGRADE_PROGRESS );
    if(vis)
    {
        if (! (vis->flags & D_VIS_FL_SHOW))
        {
            d_vis_show(vis, D_TRUE);
        }
        d_progress_bar_set_val ( vis, process) ;
    }
}

static D_Result upgrade_file_init(void)
{
    D_Visual *vis;
    vis = d_frame_get_control( &software_update_window, ID_UPGRADE_LABEL_2);
    if(vis)
    {
        if(usb_total_partition <= 0)
        {
            d_label_set_text (vis, d_gui_get_text(atv_IDS_NO_USB));
        }
        else
        {
            fs = d_fs_open(TV_USB_FILE_NAME, 1);
            if((fs == 0) || (fs == -1))
            {
                d_label_set_text (vis, "NULL");
            }
            else
            {
                d_fs_close(fs);
                d_label_set_text (vis,  "usb_upgrade.bin");
            }
        }

    }

    return D_OK;
}


static D_Result
upgrade_tv_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &software_update_window;

    switch (evt->type)
    {
        case D_EVT_ENTER:
            break;
        case D_EVT_PRESSED:
            if(usb_total_partition <= 0)
            {
                d_atv_pop_msg_show (D_POP_MSG_PRIO_MSG_2,
                D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG,
                NULL, d_gui_get_text(atv_IDS_NO_USB),
                1500, D_POP_MSG_RESPONSE_ALL_NOT, D_FALSE, NULL, 0);
            }
            else
            {
                fs = d_fs_open(TV_USB_FILE_NAME, 1);
                if((fs == 0) || (fs == -1))
                {
                    d_atv_pop_msg_show (D_POP_MSG_PRIO_MSG_2,
                                        D_GUI_LAYER_MESSAGE, D_POP_MSG_MSG,
                                        NULL, d_gui_get_text(atv_IDS_INVALID_FILE),
                                        1500, D_POP_MSG_RESPONSE_ALL_NOT, D_FALSE, NULL, 0);
                }
                else
                {
                    d_fs_close(fs);
                    usb_upgrade_end = d_usb_upgrade_create(d_gui_get_queue(), TV_USB_FILE_NAME, D_USB_UPGRADE_TASK_PRIO);
                    if(usb_upgrade_end != D_INVALID_HANDLE)
                    {
                        D_Visual           *vis1;
                        vis1 = d_frame_get_control (&software_update_window, 0);
                        /*处理用户事件*/
                        d_vis_subscribe_evt (vis1, D_EVT_USER_MASK, usb_upgrade_end);
                        p_fp_set_enable(D_FALSE);
                    }
                }
            }
        case D_EVT_LEAVE:
            break;
        default:
            break;
    }
    d_gui_update();
    return D_OK;
}

static D_Result
software_update_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Frame *frm = &software_update_window;

    switch (evt->type)
    {
        case D_EVT_FP:
            switch (evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                    return d_gui_clear_menu();
                case D_KEY_MENU:
                    return d_gui_upper_menu();
                default:
                    break;
            }
            return D_OK;
        case D_EVT_USER:
            if(evt->user.handle == usb_upgrade_end)
            {
                switch(evt->user.param1)
                {
                    case D_MSG_USBUPGRADE_PROGRESS:
                        show_process_msg((D_U8)evt->user.param2);
                        break;
                    case D_MSG_USBUPGRADE_OK:
                        show_success_msg();
                        break;
                    case D_MSG_USBUPGRADE_FAILED:
                        show_failed_msg();
                        break;
                }
            }
            break;
        case D_EVT_DESTROY:
#ifdef D_BURNER_SERIAL_NUM
#ifdef D_BURN_SN_MODE_A
            p_combo_key_seq_dinit();
#endif
#endif
            d_vis_unsubscribe_evt (vis);
        default:
            break;
    }
    return D_ERR;
}

static void show_stb_info(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &software_update_window;
    D_Visual *vis;

    vis = d_frame_get_control (frm, ID_SW_INFO_LABEL_1);
    if(vis)
    {
        d_label_set_text(vis, atvinfo_data->manu_name);
    }

    vis = d_frame_get_control (frm, ID_SW_INFO_LABEL_2);
    if(vis)
    {
        d_label_set_text(vis, atvinfo_data->hw_version);
    }

    vis = d_frame_get_control (frm, ID_SW_INFO_LABEL_3);
    if(vis)
    {
        d_label_set_text(vis, atvinfo_data->sw_version);
    }

    vis = d_frame_get_control (frm, ID_SW_INFO_LABEL_4);
    if(vis)
    {
        d_label_set_text(vis, atvinfo_data->stb_id);
    }

    vis = d_frame_get_control (frm, ID_SW_INFO_LABEL_6);
    if(vis)
    {
        d_label_set_text(vis, atvinfo_data->manu_id);
    }
    vis = d_frame_get_control (frm, ID_SW_INFO_LABEL_5);
    if(vis)
    {
        d_label_set_text(vis, atvinfo_data->release_date);
    }
    vis = d_frame_get_control (frm, ID_SW_INFO_LABEL_7);
    if(vis)
    {
        d_label_set_text(vis, atvinfo_data->chip_id);
    }	
}

D_Result
software_update_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_LoaderParam loader_param;
    D_U8 i = 0;
    D_Date_Ext date;
    D_U8 *prt;

    d_fsm_get_volumes(usb_vol_index, &usb_total_partition);

    d_cbman_subscribe(PL_FILESYSTEM_HOTPLUG, D_INVALID_HANDLE, NULL, NULL);

    vis = d_frame_get_control(frm, ID_UPGRADE_LABEL_UPGRADE);
    {
        d_label_set_text(vis, "Upgrade");
    }

    vis = d_frame_get_control(frm, ID_UPGRADE_BUTTON_1);
    {
        d_label_set_text(vis, "Upgrade Tv");
        d_vis_set_handler(vis, upgrade_tv_handler);
    }

    vis = d_frame_get_control(frm, ID_UPGRADE_BUTTON_2);
    {
        d_label_set_text(vis, "Bin name");
    }

    vis = d_frame_get_control(frm, ID_UPGRADE_LABEL_1);
    {
        d_label_set_text(vis, ">>>");
    }
    /*
        vis = d_frame_get_control(frm, ID_UPGRADE_LABEL_2);
        {
            d_label_set_text(vis, "usb_update.bin");
        }
    */
    atvinfo_data = (D_AtvInfoData*)PROJECT_ALLOC(sizeof(D_AtvInfoData));
    if(!atvinfo_data)
    {
        return D_ERR;
    }
    memset(atvinfo_data, 0x00, sizeof(D_AtvInfoData));

    p_conf_get_loader_param(&loader_param);
    sprintf(atvinfo_data->manu_id, "%04x", g_custom_config.sys.manu_id);
    sprintf(atvinfo_data->manu_name, "%s", g_custom_config.sys.manuf_name);
    sprintf(atvinfo_data->hw_version, "%02X-%02X-%04X", g_custom_config.sys.hw_id, g_custom_config.sys.hw_major, g_custom_config.sys.hw_minor);
    sprintf(atvinfo_data->sw_version, "%02X-%02X-%04X", loader_param.stb_param_copy.sw_major, loader_param.stb_param_copy.sw_minor, loader_param.stb_param_copy.sw_build_num);

#if (defined(D_CA_SUPPORT_ABVCA) && defined(D_CA_SUPPORT_COS)) //ABV 无卡, 从CA库中获得stb id
    {
        D_U8        stbid[30] = {0};

        ABV_AS_GetSTBID(stbid);
        sprintf(atvinfo_data->stb_id, "%s", stbid);
    }
#else
#ifdef D_JIANGSU_BURNER_SERIAL_NUM
	{
		prt = atvinfo_data->stb_id;
		sprintf(prt, "%08x", loader_param.lnbfreq1);
		sprintf(prt+8, "%08x", loader_param.lnbfreq2);
		if(loader_param.lnbfreq1 == 0)
		{
			atvinfo_data->stb_id[0] = '\0';
		}
		for(i = 0; i < D_CONF_DEF_STB_ID_LEN; i++)
		{
			if(loader_param.stb_param_copy.stb_id[i] != -1 && loader_param.stb_param_copy.stb_id[i] != 0)
			{
				atvinfo_data->stb_id[i+16] = loader_param.stb_param_copy.stb_id[i];
			}
			else
			{           
				break;
			}
		}

		atvinfo_data->stb_id[i+17] = '\0';
	}
#else
    for(i = 0; i < D_CONF_DEF_STB_ID_LEN; i++)
    {
        if(loader_param.stb_param_copy.stb_id[i] != -1 && loader_param.stb_param_copy.stb_id[i] != 0)
        {
            atvinfo_data->stb_id[i] = loader_param.stb_param_copy.stb_id[i];
        }
        else
        {
            break;
        }
    }

    atvinfo_data->stb_id[i] = '\0';
#endif
#endif
    if(get_standard_date(&date) == D_OK)
    {
        sprintf(atvinfo_data->release_date, "%04d/%02d/%02d  %02d:%02d", date.year + 1900, date.mon, date.day, date.hour, date.min);
    }
    else
    {
        sprintf(atvinfo_data->release_date, "%s %s", __DATE__, __TIME__);
    }
	{
	    D_U8 tempchip_id[32];
		
		memset(&(tempchip_id[0]),0,sizeof(tempchip_id));
		memset(&(atvinfo_data->chip_id[0]),0,sizeof(atvinfo_data->chip_id));
	    d_get_chipid_16bytes(&(atvinfo_data->chip_id_length), &(tempchip_id[0]));
#ifdef D_CA_SUPPORT_ABVCA
		sprintf(atvinfo_data->chip_id, "%02x%02x%02x%02x%02x%02x", tempchip_id[10], tempchip_id[11], tempchip_id[12], tempchip_id[13], tempchip_id[14], tempchip_id[15]);
#endif
#ifdef D_CA_SUPPORT_UNITENDCA
		memcpy(&(atvinfo_data->chip_id[0]),&(tempchip_id[0]),16);
#endif
    }

    show_stb_info();

    vis = d_frame_get_control (frm, 0);
    if (vis)
    {
        /*设定窗口事件回调*/
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_subscribe_evt (vis, D_EVT_HOTPLUG_MSG_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, software_update_window_handler);
    }

    upgrade_file_init();
    vis = d_frame_get_control( frm, ID_UPGRADE_LABEL_PROGRESS );
    if(vis)
    {
        d_vis_show(vis, D_FALSE);
    }
    vis = d_frame_get_control( frm, ID_UPGRADE_PROGRESS );
    if(vis)
    {
        d_vis_show(vis, D_FALSE);
    }

    return D_OK;
}

/** @brief  升级菜单*/
D_Result
p_atv_software_update_show (void) D_FUNCPOSTFIT
{
    return d_gui_enter_menu (&software_update_window, D_TRUE);
}
