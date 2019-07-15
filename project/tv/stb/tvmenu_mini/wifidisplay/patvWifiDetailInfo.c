
/** @file
@brief ip等网络信息菜单
*@date qiny 2017.11. 20
*/
#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "pConfig.h"
#include "dTimer.h"
#include "patvGuiResource.h"
#include "pStbAtvMenus.h"
#include "dNetwork.h"

#include "atv_wifi_detail_info_window.c"

#define WIFI_IP_STRING_LAN (24)

#define ERR_IPADDR (1)
#define ERR_MASK (2)
#define ERR_GATE (4)
#define ERR_DNS (8)

typedef struct
{
    D_Char  str_ipaddr[WIFI_IP_STRING_LAN];
    D_Char  str_mask[WIFI_IP_STRING_LAN];
    D_Char  str_gateway[WIFI_IP_STRING_LAN];
    D_Char  str_dns[WIFI_IP_STRING_LAN];
    D_Char  str_mac[WIFI_IP_STRING_LAN];
    D_Char  str_title[128];
    D_Char  str_msg[128];
    D_U8   menu_lang;
    D_U32   dhcp_mode;
    _net_cfg_t net_info;
    D_U32   ipaddr_value;
    D_U32   mask_value;
    D_U32   gateway_value;
    D_U32   dns_value;
    D_Bool  input_invalid;
    D_Visual *vis_group_ip, *vis_group_mask, *vis_group_way, *vis_group_dns;
    D_Visual *vis_ip, *vis_mask, *vis_way, *vis_dns, *vis_msg;
} D_WifiInfoData;
static D_WifiInfoData  *wifi_info_data = NULL;

static D_Char *dhcp_content_chn[2] = {"静态IP", "DHCP"};
static D_Char *dhcp_content_eng[2] = {"Static IP", "DHCP"};
static _net_cfg_t* pNetCfgInfo = NULL;
static D_Result (*user_handler) (_net_cfg_t *info, D_U32 param) D_FUNCPOSTFIT;
static D_U32 user_param;
static D_ID wifi_textid[4] = {atv_IDS_IPADDRESS, atv_IDS_SUBNET_MASK, atv_IDS_GATE_WAY, atv_IDS_DNS};
extern D_Bool d_ipv4_addr_check(char * str);
static D_U8 wifi_mac_addr[6] = {0};

/** @brief 将字符串的ip地址转换为32位数字*/
static D_U32 calc_ipaddr_value(const char *ipaddr)
{
    D_U32 ipval = 0, i = 0, len, val = 0;
    char *ptr = ipaddr;

    len = strlen(ipaddr);
    for(i = 0; i < len; i++)
    {
        if(isdigit(ptr[i]))
        {
            val = val * 10 +  (ptr[i] - '0');
        }
        else if(ptr[i] == '.')
        {
            ipval = (ipval << 8) + val;
            val = 0;
        }
    }
    ipval = (ipval << 8) + val;
    return ipval;
}

/** @brief 检查用户输入的地址是否有效*/
static D_Bool check_ipaddr_valid(D_U32 type, D_U32 *val)
{
    D_Bool ret = D_FALSE;
    D_U32 value, i;
    D_Char strip[16];

    if(val[0] <= 255 && val[1] <= 255 && val[2] <= 255 && val[3] <= 255)
    {
        sprintf(strip, "%d.%d.%d.%d", val[0], val[1], val[2], val[3]);
        ret = d_ipv4_addr_check(strip);
        if(ret && type == ERR_MASK)
        {
            /* net mask    11111111000000000*/
            value = ( (0xFF & val[0]) << 24) | ( (0xFF & val[1]) << 16) | ((0xFF & val[2]) << 8) | (0xFF & val[3]);
            for(i = 0; i < 32; i++)
            {
                if((value & 0x80000000) == 0)
                {
                    break;
                }
                value = ((value << 1) & 0xFFFFFFFE);
            }
            ret = (value) ? D_FALSE : D_TRUE;
        }
    }
    return ret;
}

/*@brief 保存用户参数*/
static D_Result
atv_wifi_info_save_info(void) D_FUNCPOSTFIT
{
    D_Bool change_flag = D_FALSE;
    D_U32 val_seg[4];
    D_U32   ipaddr_value;
    D_U32   mask_value;
    D_U32   gateway_value;
    D_U32   dns_value;

    if(user_handler && wifi_info_data)
    {
        if(wifi_info_data->dhcp_mode != wifi_info_data->net_info.method || wifi_info_data->dhcp_mode  == ROC_STATIC)
        {
            memset(val_seg, 0x00, sizeof(val_seg));
            d_input_box_get_segment_val(wifi_info_data->vis_ip, val_seg, 4);
            ipaddr_value = ( (0xFF & val_seg[0]) << 24) | ( (0xFF & val_seg[1]) << 16) | ((0xFF & val_seg[2]) << 8) | (0xFF & val_seg[3]);
            sprintf(wifi_info_data->net_info.ip, "%d.%d.%d.%d", (0xFF & val_seg[0]), (0xFF & val_seg[1]), (0xFF & val_seg[2]), (0xFF & val_seg[3]));
            memset(val_seg, 0x00, sizeof(val_seg));
            d_input_box_get_segment_val(wifi_info_data->vis_mask, val_seg, 4);
            mask_value = ( (0xFF & val_seg[0]) << 24) | ( (0xFF & val_seg[1]) << 16) | ((0xFF & val_seg[2]) << 8) | (0xFF & val_seg[3]);
            sprintf(wifi_info_data->net_info.mask, "%d.%d.%d.%d", (0xFF & val_seg[0]), (0xFF & val_seg[1]), (0xFF & val_seg[2]), (0xFF & val_seg[3]));
            memset(val_seg, 0x00, sizeof(val_seg));
            d_input_box_get_segment_val(wifi_info_data->vis_way, val_seg, 4);
            gateway_value = ( (0xFF & val_seg[0]) << 24) | ( (0xFF & val_seg[1]) << 16) | ((0xFF & val_seg[2]) << 8) | (0xFF & val_seg[3]);
            sprintf(wifi_info_data->net_info.gateway, "%d.%d.%d.%d", (0xFF & val_seg[0]), (0xFF & val_seg[1]), (0xFF & val_seg[2]), (0xFF & val_seg[3]));
            memset(val_seg, 0x00, sizeof(val_seg));
            d_input_box_get_segment_val(wifi_info_data->vis_dns, val_seg, 4);
            dns_value = ( (0xFF & val_seg[0]) << 24) | ( (0xFF & val_seg[1]) << 16) | ((0xFF & val_seg[2]) << 8) | (0xFF & val_seg[3]);
            sprintf(wifi_info_data->net_info.dns, "%d.%d.%d.%d", (0xFF & val_seg[0]), (0xFF & val_seg[1]), (0xFF & val_seg[2]), (0xFF & val_seg[3]));

            if(wifi_info_data->dhcp_mode != wifi_info_data->net_info.method)
            {
                change_flag = D_TRUE;
            }
            else if(wifi_info_data->dhcp_mode == ROC_STATIC)
            {
                if(ipaddr_value != wifi_info_data->ipaddr_value || mask_value != wifi_info_data->mask_value \
                   || gateway_value != wifi_info_data->gateway_value || dns_value != wifi_info_data->dns_value)
                {
                    change_flag = D_TRUE;
                }
            }

            wifi_info_data->net_info.method = wifi_info_data->dhcp_mode;
            if(change_flag)
            {
                user_handler(&(wifi_info_data->net_info), user_param);
            }
        }
    }
    return D_OK;
}

/*@brief 根据dhcp模式不否，设定IP等是否可选*/
static D_Result
atv_wifi_info_select_dhcp_mode(D_Bool dhcp) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_Bool enable = !dhcp;

    d_vis_enable(wifi_info_data->vis_group_ip, enable);
    d_vis_enable(wifi_info_data->vis_ip, enable);
    d_vis_enable(wifi_info_data->vis_group_mask, enable);
    d_vis_enable(wifi_info_data->vis_mask, enable);
    d_vis_enable(wifi_info_data->vis_group_way, enable);
    d_vis_enable(wifi_info_data->vis_way, enable);
    d_vis_enable(wifi_info_data->vis_group_dns, enable);
    d_vis_enable(wifi_info_data->vis_dns, enable);

    return D_OK;
}

/*@brief 检查显示错误提示*/
static D_Result
atv_wifi_info_check_warning(void) D_FUNCPOSTFIT
{
    if(wifi_info_data->dhcp_mode || wifi_info_data->input_invalid == 0)
    {
        d_label_set_text(wifi_info_data->vis_msg, "");
    }
    else if(wifi_info_data->input_invalid)
    {
        D_U32 id;
        for(id = 0; id < 4; id++)
        {
            if(wifi_info_data->input_invalid & (1 << id))
            {
                break;
            }
        }
        sprintf(wifi_info_data->str_msg, "请输入正确的%s !", d_gui_get_text(wifi_textid[id]));
        if(wifi_info_data->menu_lang == D_LANG_ENG)
        {
            sprintf(wifi_info_data->str_msg, "Plase input the correct %s !", d_gui_get_text(wifi_textid[id]));
        }
        d_label_set_text(wifi_info_data->vis_msg, wifi_info_data->str_msg);
        return D_TRUE;
    }

    return D_FALSE;
}

/*@brief dhcp选择框控件回调*/
static D_Result
atv_wifi_dhcp_mode_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_SELECTED:
            wifi_info_data->dhcp_mode = d_select_box_get_val(vis);
            atv_wifi_info_select_dhcp_mode(wifi_info_data->dhcp_mode);
            atv_wifi_info_check_warning();
            break;
        default:
            break;
    }
    return D_ERR;
}

/*@brief dhcp地址输入框控件回调*/
static D_Result
atv_wifi_address_input_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    D_Bool  invalid;
    D_U32 val_seg[4] = {0};
    D_ID id;

    switch(evt->type)
    {
        case D_EVT_DATA_CHANGED:
            id = d_frame_get_control_id(&atv_wifi_detail_info_window, vis) - ID_WIFIINFO_INPUT_IPADDR;
            d_input_box_get_segment_val(vis, val_seg, 4);
            invalid = !check_ipaddr_valid((1 << id), val_seg);
            if(invalid)
            {
                wifi_info_data->input_invalid |= (1 << id);
                sprintf(wifi_info_data->str_msg, "请输入正确的%s !", d_gui_get_text(wifi_textid[id]));
                if(wifi_info_data->menu_lang == D_LANG_ENG)
                {
                    sprintf(wifi_info_data->str_msg, "Plase input the correct %s !", d_gui_get_text(wifi_textid[id]));
                }
            }
            else
            {
                wifi_info_data->input_invalid &= (~(1 << id));
                sprintf(wifi_info_data->str_msg, "");
            }
            d_label_set_text(wifi_info_data->vis_msg, wifi_info_data->str_msg);
            break;
        default:
            break;
    }
    return D_ERR;
}

/*@brief dhcp窗口控件回调*/
static D_Result
atv_wifi_detail_info_window_handler(D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT
{
    switch(evt->type)
    {
        case D_EVT_FP:
            switch(evt->fp.key)
            {
                case D_KEY_ESC:
                case D_KEY_PNL_ESC:
                case D_KEY_BACK:
                    return p_atv_wifi_detail_info_window_colse();
                    break;
                case D_KEY_OK:
                    if(D_FALSE == atv_wifi_info_check_warning())
                    {
                        atv_wifi_info_save_info();
                        p_atv_wifi_detail_info_window_colse();
                    }
                    return D_OK;
                case D_KEY_SOURCE:
                    break;
                default:
                    break;
            }
            return D_OK;
            break;
        case D_EVT_DESTROY:
            d_vis_unsubscribe_evt(vis);
            if(wifi_info_data)
            {
                PROJECT_FREE(wifi_info_data);
                wifi_info_data = NULL;
            }
            break;
        default:
            break;
    }

    return D_ERR;

}

/** @breif 窗口加载时的初始化*/
D_Result
atv_wifi_detail_info_window_init(D_Frame *frm) D_FUNCPOSTFIT
{
    D_Visual *vis;
    D_U32 id;

    wifi_info_data = (D_WifiInfoData *)PROJECT_ALLOC(sizeof(D_WifiInfoData));
    if(wifi_info_data == NULL)
    {
        return D_ERR;
    }

    memset(wifi_info_data, 0x00, sizeof(D_WifiInfoData));
    if(pNetCfgInfo)
    {
        memcpy(&(wifi_info_data->net_info), pNetCfgInfo, sizeof(wifi_info_data->net_info));
    }
    wifi_info_data->menu_lang = p_conf_get_lang();
    wifi_info_data->dhcp_mode = wifi_info_data->net_info.method;

    vis = d_frame_get_control( frm, ID_WIFIINFO_LABEL_TITLE);
    sprintf( wifi_info_data->str_title, "%s", wifi_info_data->net_info.name);
    d_label_set_text( vis, wifi_info_data->str_title);
    vis = d_frame_get_control( frm, ID_WIFIINFO_LABEL_LEFT_MODE);
    d_label_set_text( vis, "<");
    vis = d_frame_get_control( frm, ID_WIFIINFO_LABEL_RIGHT_MODE);
    d_label_set_text( vis, ">");

    wifi_info_data->vis_group_ip = d_frame_get_control( frm, ID_WIFIINFO_GROUP_IPADDR);
    wifi_info_data->vis_group_mask = d_frame_get_control( frm, ID_WIFIINFO_GROUP_MASK);
    wifi_info_data->vis_group_way = d_frame_get_control( frm, ID_WIFIINFO_GROUP_GATEWAY);
    wifi_info_data->vis_group_dns = d_frame_get_control( frm, ID_WIFIINFO_GROUP_DNS);
    wifi_info_data->vis_msg = d_frame_get_control( frm, ID_WIFIINFO_LABEL_WARNING);
    vis = d_frame_get_control( frm, ID_WIFIINFO_SELECT_MODE);
    if(vis)
    {
        d_select_box_set_content( vis, ((wifi_info_data->menu_lang == D_LANG_ENG) ? dhcp_content_eng : dhcp_content_chn), 2);
        d_select_box_set_val(vis, (D_U16)wifi_info_data->dhcp_mode);
        d_vis_set_handler (vis, atv_wifi_dhcp_mode_handler);
    }

    vis = d_frame_get_control( frm, ID_WIFIINFO_INPUT_IPADDR);
    if(vis)
    {
        wifi_info_data->vis_ip = vis;
        id = calc_ipaddr_value(wifi_info_data->net_info.ip);
        wifi_info_data->ipaddr_value = id;
        sprintf(wifi_info_data->str_ipaddr, "%03d.%03d.%03d.%03d", (0xFF & (id >> 24)), (0xFF & (id >> 16)), (0xFF & (id >> 8)), (0xFF & id) );
        d_input_box_set_text(vis, wifi_info_data->str_ipaddr, strlen(wifi_info_data->str_ipaddr));
        d_vis_set_handler (vis, atv_wifi_address_input_handler);
    }

    vis = d_frame_get_control( frm, ID_WIFIINFO_INPUT_MASK);
    if(vis)
    {
        wifi_info_data->vis_mask = vis;
        id = calc_ipaddr_value(wifi_info_data->net_info.mask);
        wifi_info_data->mask_value = id;
        sprintf(wifi_info_data->str_mask, "%03d.%03d.%03d.%03d", (0xFF & (id >> 24)), (0xFF & (id >> 16)), (0xFF & (id >> 8)), (0xFF & id) );
        d_input_box_set_text(vis, wifi_info_data->str_mask, strlen(wifi_info_data->str_mask));
        d_vis_set_handler (vis, atv_wifi_address_input_handler);
    }

    vis = d_frame_get_control( frm, ID_WIFIINFO_INPUT_GATEWAY);
    if(vis)
    {
        wifi_info_data->vis_way = vis;
        id = calc_ipaddr_value(wifi_info_data->net_info.gateway);
        wifi_info_data->gateway_value = id;
        sprintf(wifi_info_data->str_gateway, "%03d.%03d.%03d.%03d", (0xFF & (id >> 24)), (0xFF & (id >> 16)), (0xFF & (id >> 8)), (0xFF & id) );
        d_input_box_set_text(vis, wifi_info_data->str_gateway, strlen(wifi_info_data->str_gateway));
        d_vis_set_handler (vis, atv_wifi_address_input_handler);
    }

    vis = d_frame_get_control( frm, ID_WIFIINFO_INPUT_DNS);
    if(vis)
    {
        wifi_info_data->vis_dns = vis;
        id = calc_ipaddr_value(wifi_info_data->net_info.dns);
        wifi_info_data->dns_value = id;
        sprintf(wifi_info_data->str_dns, "%03d.%03d.%03d.%03d", (0xFF & (id >> 24)), (0xFF & (id >> 16)), (0xFF & (id >> 8)), (0xFF & id) );
        d_input_box_set_text(vis, wifi_info_data->str_dns, strlen(wifi_info_data->str_dns));
        d_vis_set_handler (vis, atv_wifi_address_input_handler);
    }

    vis = d_frame_get_control( frm, ID_WIFIINFO_GROUP_DNS);
    if(vis)
    {
        d_vis_enable(vis, D_FALSE);
    }

    vis = d_frame_get_control( frm, ID_WIFIINFO_LABEL_MAC);
    if(vis)
    {
        D_U8 *mac = wifi_mac_addr;
        static D_Bool got_mac = D_FALSE;
        if(got_mac == D_FALSE)
        {
            Roc_Device_Cfg_t devcfg = {0};
            if(0 == d_network_get_device_info(wifi_info_data->net_info.devicename, &devcfg))
            {
                got_mac = D_TRUE;
                memcpy(wifi_mac_addr, devcfg.mac, sizeof(devcfg.mac));
            }
        }
        d_vis_enable(vis, D_FALSE);
        sprintf(wifi_info_data->str_mac, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        d_label_set_text( vis, wifi_info_data->str_mac);
    }

    vis = d_frame_get_control( frm, 0);
    if(vis)
    {
        d_vis_subscribe_evt (vis, D_EVT_ALL_KEY_MASK , D_INVALID_HANDLE);
        d_vis_set_handler (vis, atv_wifi_detail_info_window_handler);
    }

    atv_wifi_info_select_dhcp_mode(wifi_info_data->dhcp_mode);
    return D_OK;
}

/** @brief wifi 状态信息窗口显示*/
D_Result
p_atv_wifi_detail_info_window_show(_net_cfg_t *net_info,  D_Result (*handler) (_net_cfg_t *info, D_U32 param) D_FUNCPOSTFIT, D_U32 param )D_FUNCPOSTFIT
{
    if(D_FALSE == d_frame_is_loaded(&atv_wifi_detail_info_window))
    {
        pNetCfgInfo = net_info;
        user_handler = handler;
        user_param = param;
        d_gui_open_frame(&atv_wifi_detail_info_window, D_GUI_LAYER_USER);
    }
    return D_OK;
}

/** @brief wifi 状态信息窗口关闭*/
D_Result
p_atv_wifi_detail_info_window_colse(void)D_FUNCPOSTFIT
{
    if(D_TRUE == d_frame_is_loaded(&atv_wifi_detail_info_window))
    {
        d_gui_close_frame(&atv_wifi_detail_info_window);
    }

    return D_OK;
}


