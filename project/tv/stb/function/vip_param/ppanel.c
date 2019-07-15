/** @file
* @brief 屏参默认配置调用
* @author
* @date 2018-07-10
*/

#include "ppanel.h"


/** @brief 根据工厂菜单panel配置的分辨率为panel_param配置参数
* @param 无
* @return 无
*/
void parse_partpanel_to_panel(D_PanelParam* panle_param , D_PartPanelParam* part_panle_param) D_FUNCPOSTFIT
{
    panle_param->lvds_init_param.lvds_v_total = part_panle_param->v_total_60;
    panle_param->lvds_init_param.lvds_h_active_width = part_panle_param->h_active_width;
    panle_param->lvds_init_param.lvds_h_sync_width = part_panle_param->h_sync_width;
    panle_param->lvds_init_param.lvds_h_active_start = part_panle_param->h_active_start;
    panle_param->lvds_init_param.lvds_v_active_height = part_panle_param->v_active_width;
    panle_param->lvds_init_param.lvds_v_sync_width = part_panle_param->v_sync_width;
    panle_param->lvds_init_param.lvds_v_active_start = part_panle_param->v_active_start;
    panle_param->lvds_init_param.lvds_v_active_end = part_panle_param->v_active_start + part_panle_param->v_active_width;
    panle_param->lvds_init_param.lvds_channel_mode = part_panle_param->channel_mode;
    panle_param->lvds_init_param.lvds_exchange_mode = part_panle_param->exchange_mode;
    panle_param->lvds_init_param.lvds_foramt = part_panle_param->lvds_foramt;
    panle_param->lvds_init_param.lvds_div = 0;
    if(part_panle_param->channel_mode)
    {
        panle_param->lvds_init_param.lvds_h_total = part_panle_param->h_total / 2 + 10;
        panle_param->lvds_init_param.lvds_h_active_end = part_panle_param->h_active_start + part_panle_param->h_active_width / 2;
    }
    else
    {
        panle_param->lvds_init_param.lvds_h_total = part_panle_param->h_total;
        panle_param->lvds_init_param.lvds_h_active_end = part_panle_param->h_active_start + part_panle_param->h_active_width ;
    }
    if(part_panle_param->channel_mode == 1 || part_panle_param->lvds_type)
    {
        panle_param->lvds_init_param.lvds_sync_mode = 1;
    }
    else
    {
        panle_param->lvds_init_param.lvds_sync_mode = 0;
    }
    panle_param->lvds_init_param.lvds_l_p_n_sel = 0xff;
    panle_param->lvds_init_param.lvds_r_p_n_sel = 0xff;
    panle_param->lvds_init_param.lvds_da_tx_pds = part_panle_param->lvds_da_tx_pds;
    panle_param->lvds_init_param.lvds_clk_tx_pds = part_panle_param->lvds_clk_tx_pds;
    panle_param->lvds_init_param.pll_freq = part_panle_param->pll_freq;//lvds_clk = pll_freq/vp_div
    panle_param->lvds_init_param.vp_div = part_panle_param->vp_div;
    panle_param->lvds_init_param.lvds_x = part_panle_param->lvds_x;

    panle_param->lvds_type = part_panle_param->lvds_type;//mini是1，lvds是0

    if((part_panle_param->h_active_width == 1366) && (part_panle_param->v_active_width == 768))
    {
        panle_param->screenparam.OSD_set_line_to_top = 0x12;
        panle_param->screenparam.OSD_set_pix_to = 0x32;
        panle_param->screenparam.VCOM_DE_start_pix = 0x4a;
        panle_param->screenparam.VCOM_DE_start_line = 0x35;
    }
    else if((part_panle_param->h_active_width == 1920) && (part_panle_param->v_active_width == 1080))
    {
        panle_param->screenparam.OSD_set_line_to_top = 0x05;
        panle_param->screenparam.OSD_set_pix_to = 0x28;
        panle_param->screenparam.VCOM_DE_start_pix = 0x4a;
        panle_param->screenparam.VCOM_DE_start_line = 0x35;
    }
    else if((part_panle_param->h_active_width == 1024) && (part_panle_param->v_active_width == 600))
    {
        panle_param->screenparam.OSD_set_pix_to = 0x18;
        panle_param->screenparam.OSD_set_line_to_top = 0x1f;
        panle_param->screenparam.VCOM_DE_start_pix = 0x4a;
        panle_param->screenparam.VCOM_DE_start_line = 0x35;
    }
    else
    {
        panle_param->screenparam.OSD_set_line_to_top = 0x10;
        panle_param->screenparam.OSD_set_pix_to = 0x2c;
        panle_param->screenparam.VCOM_DE_start_pix = 0x4a;
        panle_param->screenparam.VCOM_DE_start_line = 0x35;
    }
    if (part_panle_param->invert)
        panle_param->screenparam.SP_StartLine = 0x33;//----------tanys==0x34->0x33,,,要对倒装作区分
    else
        panle_param->screenparam.SP_StartLine = 0x34;
    panle_param->screenparam.SP_StartPix = 0x02;
    panle_param->screenparam.VCOM_StartLine = 0x35;
    panle_param->screenparam.VCOM_StartPix = 0x45;
    panle_param->screenparam.VO_feeder_vsync_line = 0x3;
    panle_param->screenparam.VO_hs_vsync_line = 0x31;
    panle_param->screenparam.VO_hs_vsync_pix = 0x53;
    panle_param->screenparam.VO_set_pix_to_VeBypass = 0xf7;
    panle_param->screenparam.VO_set_pix_to_VeEnable = 0xf7;

    panle_param->tven_para.display_invert = part_panle_param->invert;
    panle_param->tven_para.v_max_50 = 1280;
    panle_param->tven_para.v_min_60 = 778;
    panle_param->tven_para.out_freq_50 = (D_U32)part_panle_param->pll_freq * 1000000 / part_panle_param->vp_div; //148500000;
    panle_param->tven_para.out_freq_60 = (D_U32)part_panle_param->pll_freq * 1000000 / part_panle_param->vp_div; //148500000;
    panle_param->tven_para.total_line_50 = part_panle_param->v_total_50;
    panle_param->tven_para.total_line_60 = part_panle_param->v_total_60;
    panle_param->tven_para.total_pix_per_line_50 = part_panle_param->h_total;
    panle_param->tven_para.total_pix_per_line_60 = part_panle_param->h_total;
    panle_param->tven_para.screenwidth = part_panle_param->h_active_width;
    panle_param->tven_para.screenheight = part_panle_param->v_active_width;

    switch(part_panle_param->lvds_type)
    {
        case 1://,BOE_768P_N56,BOE_768P_N56
        case 3://,BOE_768P_N81,BOE_768P_N81
            panle_param->tven_para.vsync_lastde_delay_50 = 0xd4;
            panle_param->tven_para.vsync_lastde_delay_60 = 0x30;
            panle_param->tven_para.speed_adj_line = 0;
            panle_param->screenparam.VCOM_DE_end_line = part_panle_param->v_active_width + 3;
            panle_param->screenparam.VCOM_DE_start_line = 0x35;
            break;
        case 2://,BOE_768P_N86,BOE_768P_N86
            panle_param->tven_para.vsync_lastde_delay_50 = 0xd4;
            panle_param->tven_para.vsync_lastde_delay_60 = 0x30;
            panle_param->tven_para.speed_adj_line = 0;
            panle_param->screenparam.VCOM_DE_end_line = part_panle_param->v_active_width + 3;
            panle_param->screenparam.VCOM_DE_start_line = 0x35;
            break;
        case 4://,HK_768P_PT320,HK_768P_PT320
            panle_param->tven_para.vsync_lastde_delay_50 = 0xd6;
            panle_param->tven_para.vsync_lastde_delay_60 = 0x32;
            panle_param->tven_para.speed_adj_line = 0;
            panle_param->screenparam.VCOM_DE_end_line = part_panle_param->v_active_width + 1;
            panle_param->screenparam.VCOM_DE_start_line = 0x35;
            break;
        case 5://,BOE_1080P_N10,BOE_1080P_N10
        case 6://,BOE_1080P_N40,BOE_1080P_N40
        case 7://,TCL_1080P_ST48,TCL_1080P_ST48
        default:
            panle_param->tven_para.vsync_lastde_delay_50 = 0x04;
            panle_param->tven_para.vsync_lastde_delay_60 = 0x04;
            panle_param->tven_para.speed_adj_line = 0x10;
            panle_param->screenparam.VCOM_DE_end_line = part_panle_param->v_active_width;
            break;
    }
    p_panel_get_tcon_info(part_panle_param->lvds_type, &panle_param->tcon_param);
}


/** @brief 各个分辨率屏参数配置
* @param [in]  rp
* @param [out]  panle_param
* @return 无
*/
void get_part_panel_param(D_PartPanelParam* part_panle_param , D_U8 rp , D_U8 model)
{
    switch(rp)
    {
        case 1://1024x600
        {
            part_panle_param->exchange_mode = 1;//ch_sl
            part_panle_param->exchange_pn = 0;
            part_panle_param->lvds_foramt = 0;//lvds_map
            part_panle_param->lvds_da_tx_pds = 1;
            part_panle_param->lvds_clk_tx_pds = 1;
            part_panle_param->channel_mode = 0;//split_en
            part_panle_param->h_active_width = 1024;
            part_panle_param->v_active_width = 600;
            part_panle_param->h_total = 1293;
            part_panle_param->v_total_50 = 792;
            part_panle_param->v_total_60 = 660;
            part_panle_param->h_active_start = 70;//h_active_start
            part_panle_param->v_active_start = 16;//v_active_start
            part_panle_param->h_sync_width = 40;//hsync_width
            part_panle_param->v_sync_width = 6;//vsync_width
            part_panle_param->pll_freq = 256;
            part_panle_param->vp_div = 5;
            part_panle_param->lvds_x = 28;
            part_panle_param->invert = 0;
            part_panle_param->lvds_type = 0;
        }
        break;
        case 2://1280x800
        {
            part_panle_param->exchange_mode = 1;//ch_sl
            part_panle_param->exchange_pn = 0;
            part_panle_param->lvds_foramt = 0;//lvds_map
            part_panle_param->lvds_da_tx_pds = 2;
            part_panle_param->lvds_clk_tx_pds = 3;
            part_panle_param->channel_mode = 0;//split_en
            part_panle_param->h_active_width = 1280;
            part_panle_param->v_active_width = 800;
            part_panle_param->h_total = 1439;
            part_panle_param->v_total_50 = 1032;
            part_panle_param->v_total_60 = 860;
            part_panle_param->h_active_start = 70;//h_active_start
            part_panle_param->v_active_start = 16;//v_active_start
            part_panle_param->h_sync_width = 40;//hsync_width
            part_panle_param->v_sync_width = 6;//vsync_width
            part_panle_param->pll_freq = 297;
            part_panle_param->vp_div = 4;
            part_panle_param->lvds_x = 28;
            part_panle_param->invert = 0;
            part_panle_param->lvds_type = 0;
        }
        break;
        case 3://1366x768
        {
            part_panle_param->exchange_mode = 1;//ch_sl
            part_panle_param->exchange_pn = 0;
            if(model == 5)//奇美32寸v320BJ6-q01
                part_panle_param->lvds_foramt = 0;//lvds_map
            else
                part_panle_param->lvds_foramt = 1;//lvds_map
            part_panle_param->lvds_da_tx_pds = 2;
            part_panle_param->lvds_clk_tx_pds = 3;
            part_panle_param->channel_mode = 0;//split_en
            part_panle_param->h_active_width = 1366;
            part_panle_param->v_active_width = 768;
            part_panle_param->h_total = 1538;
            part_panle_param->v_total_50 = 999;
            part_panle_param->v_total_60 = 832;
            part_panle_param->h_active_start = 70;//h_active_start
            part_panle_param->v_active_start = 16;//v_active_start
            part_panle_param->h_sync_width = 40;//hsync_width
            part_panle_param->v_sync_width = 6;//vsync_width
            part_panle_param->pll_freq = 384;
            part_panle_param->vp_div = 5;
            part_panle_param->lvds_x = 28;
            part_panle_param->invert = 0;
            part_panle_param->lvds_type = 0;
        }
        break;
        case 4://1920x1080
        {
            if((model == 5) || (model == 6))//riqin14 & riqin16
                part_panle_param->exchange_mode = 0;//ch_sl
            else
                part_panle_param->exchange_mode = 1;//ch_sl
            part_panle_param->exchange_pn = 0;
            if(model == 6)
                part_panle_param->lvds_foramt = 0;//1'b0: JEIDA standard  1'b1: VESA standard
            else
                part_panle_param->lvds_foramt = 1;
            part_panle_param->lvds_da_tx_pds = 3;
            part_panle_param->lvds_clk_tx_pds = 3;
            part_panle_param->channel_mode = 1;//split_en
            part_panle_param->h_active_width = 1920;
            part_panle_param->v_active_width = 1080;
            part_panle_param->h_total = 2152;
            part_panle_param->v_total_50 = 1380;
            part_panle_param->v_total_60 = 1150;
            part_panle_param->h_active_start = 70;//h_active_start
            part_panle_param->v_active_start = 41;//v_active_start
            part_panle_param->h_sync_width = 40;//hsync_width
            part_panle_param->v_sync_width = 6;//vsync_width
            part_panle_param->pll_freq = 297;
            part_panle_param->vp_div = 2;
            part_panle_param->lvds_x = 14;
            part_panle_param->invert = 0;
            part_panle_param->lvds_type = 0;
        }
        break;
        default: 
        break;
    }
}





































