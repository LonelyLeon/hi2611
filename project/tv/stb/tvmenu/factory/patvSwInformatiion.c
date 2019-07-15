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
#include "sw_information_window.c"

typedef struct
{
    D_Char manu_name[34];
    D_Char hw_version[32];
    D_Char sw_version[32];
    D_Char stb_id[32];
    D_Char release_date[64];
	D_Char manu_id[34];
}D_AtvInfoData;


static D_AtvInfoData* atvinfo_data = NULL;

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
    sscanf(ptr,"%d", &tmp);
    date->hour = (D_U8)tmp; 
    
    ptr = strstr(ptr, ":");
    if(ptr)
    {
        ptr++;
        tmp = 0;
        sscanf(ptr,"%d", &tmp);
        date->min = (D_U8)tmp;
    }    

    ptr = strstr(ptr, ":");
    if(ptr)
    {
        ptr++;  
        tmp = 0;
        sscanf(ptr,"%d", &tmp);
        date->sec = (D_U8)tmp;
    }      
    
    return D_OK;
}



/** @brief 刷新序列号*/       
static void serial_number_flush(D_Visual *vis) D_FUNCPOSTFIT
{
#if (defined(D_CA_SUPPORT_ABVCA) && defined(D_CA_SUPPORT_COS)) //ABV 无卡, 从CA库中获得stb id
    D_U8        stbid[15] = {0};
    
    ABV_AS_GetSTBID(stbid);
    sprintf(atvinfo_data->stb_id, "%s", stbid); 
#else	
	D_LoaderParam loader_param = {0};
	D_U8 i = 0;

	p_conf_get_loader_param (&loader_param);	//获取loader参数
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
	d_label_set_text (vis, atvinfo_data->stb_id);
}

static void show_stb_info(void) D_FUNCPOSTFIT
{
    D_Frame *frm = &sw_information_window;
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

    vis = d_frame_get_control (frm, ID_SW_INFO_LABEL_5);        
    if(vis)
    {
        d_label_set_text(vis, atvinfo_data->release_date);
    }      

	vis = d_frame_get_control (frm, ID_SW_INFO_LABEL_6);        
    if(vis)
    {
        d_label_set_text(vis, atvinfo_data->manu_id);
    }  
}




/** @brief 事件处理*/       
static D_Result 
sw_information_window_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{	
	//D_Visual	*list;  
	D_Frame *frm = &sw_information_window;
	
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
			break;
			
		case D_EVT_DESTROY:
#ifdef D_BURNER_SERIAL_NUM       		
    #ifdef D_BURN_SN_MODE_A       
			p_combo_key_seq_dinit();			
#endif			
#endif			
			d_vis_unsubscribe_evt (vis);
                    PROJECT_FREE(atvinfo_data);
                    atvinfo_data = NULL;
			break;
		default:
			break;
	}

	return D_ERR;
} 

/** @brief 窗口初始化*/
D_Result    
sw_information_window_init (D_Frame *frm) D_FUNCPOSTFIT
{
	D_Visual		*vis;
       D_LoaderParam loader_param;
       D_U8 i = 0;
        D_Date_Ext date;
    
        atvinfo_data = (D_AtvInfoData*)PROJECT_ALLOC(sizeof(D_AtvInfoData));
        if(!atvinfo_data)
        {
            return D_ERR;
        }
        memset(atvinfo_data, 0x00, sizeof(D_AtvInfoData));

        p_conf_get_loader_param(&loader_param);
		sprintf(atvinfo_data->manu_id, "%d", g_custom_config.sys.manu_id);
        sprintf(atvinfo_data->manu_name, "%s", g_custom_config.sys.manuf_name);
        sprintf(atvinfo_data->hw_version, "%02X-%02X-%04X", g_custom_config.sys.hw_id, g_custom_config.sys.hw_major, g_custom_config.sys.hw_minor);
        sprintf(atvinfo_data->sw_version, "%02X-%02X-%04X", loader_param.stb_param_copy.sw_major, loader_param.stb_param_copy.sw_minor, loader_param.stb_param_copy.sw_build_num);

        if(get_standard_date(&date) == D_OK)
        {
            sprintf(atvinfo_data->release_date, "%04d/%02d/%02d  %02d:%02d", date.year + 1900, date.mon, date.day, date.hour, date.min);            
        }
        else
        {
        sprintf(atvinfo_data->release_date, "%s %s", __DATE__, __TIME__);
        }

#if (defined(D_CA_SUPPORT_ABVCA) && defined(D_CA_SUPPORT_COS)) //ABV 无卡, 从CA库中获得stb id
        {
            D_U8        stbid[15] = {0};
        
            ABV_AS_GetSTBID(stbid);
            sprintf(atvinfo_data->stb_id, "%s", stbid); 
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
   
	vis = d_frame_get_control (frm, 0);
	if (vis)  
	{		
		/*设定窗口事件回调*/
		d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK ,D_INVALID_HANDLE);		
		d_vis_set_handler (vis, sw_information_window_handler);		
	}

        show_stb_info();
        
	return D_OK;
}


/** @breif 显示本机信息窗口*/      
D_Result         
p_atv_info_window_show (void) D_FUNCPOSTFIT
{	
	return d_gui_enter_menu (&sw_information_window, D_TRUE);
}

