/** @file
* @brief 屏参处理相关设置调用
* @author 刘爽
* @date 2017-01-22 lius: 建立文件
*/
#include "stdio.h"
#include "dPanel.h"
#include "ppanelset.h"
#include "pConfig.h"
#include "ptvConfig.h"
#include "dTask.h"
#include "dDebug.h"

/********
GPO0 :TP
GPO1 :pol
GPO2:CKV
GPO3:VGH 
GPO4:STV
GPO5:OE
*******/
static const D_TCON_INIT_PARAM    tcon_param_PT320 =
{
    {2, 4, 2,6, 7,  6, 6, 6, 6, 6, 6}, //ctr_gpo;
    {1, 1, 1, 0, 1, 0, 0, 0, 0}, //gpo_initial;
    {116,140,506,530,1, 800}, //gpo0_cnt;
    {0, 0, 0, 0, 0, 0}, //gpo1_cnt;
    {120, 320, 510, 710, 1, 800}, //gpo2_cnt;
    {2, 122, 392, 512, 0, 0}, //gpo3_cnt;
    {480, 100, 0, 0, 18, 19},//{68, 182, 446, 560, 0, 0}, ////{68, 182, 446, 560, 0, 0}, //gpo4_cnt;
    {58, 172, 448, 562, 0, 0}, //{88, 202, 450, 580, 0, 0}, ////{88, 202, 466, 580, 0, 0}, //gpo5_cnt;
    {0, 0, 0, 0, 0, 0}, //gpo6_cnt;
    {0, 0, 0, 0, 0, 0}, //gpo7_cnt;
    {0, 0, 0, 0, 0, 0}, //gpo8_cnt;
    0,//tri1_cnt;
    0,//tri2_cnt;
    0,//tri3_cnt;
    0,//tri4_cnt;
    3,//MINI_MODE;
    2,//SER_MODE;
    1,//reset_pos;  
    7,//DIFF_POS;
    10,//FIFO_HS_start;
    950,//h_active_start;
    958,//H_READ_CNT;
    860,//R_CLR_CNT;
    14,//CLK_V_CNT;
    550,//CLK_H_CNT;
    0x924,//CLK_MOD;
    160,//POL_CNT;
    0,//SGATE;
    30,//RAM12_L;
    58,//NEW_DE1_S;
    20,//hstart;
    49,//h_end;
    2087,//h_start1;
    2097,//h_end1;
    4127,//h_start2;
    4137,//h_end2;
    1124,//vdd_v_cnt;
    1100,//vdd_h_cnt;
    179,//vdd_cnt_fram;
    16,//cpv2_h;
    218,//cpv2_h1;
    600,//cpv2_h2;
    1,//n_clk;
    0,//n_clk1;
    1,//mode;
    1,//dual_mode;
    0,//trigate;
    0,//split_en;
};;
/********
GPO0 :
GPO1 :
GPO2:
GPO3:
GPO4:
GPO5:
*******/
static const D_TCON_INIT_PARAM    tcon_param_N10 =
{
    {14, 13, 12, 11, 10, 9, 5, 17, 16, 18, 19}, //ctr_gpo;
    {1, 1, 1, 1, 1, 0, 1, 1, 1}, //gpo_initial;
    {91, 110, 0, 0, 0, 0}, //gpo0_cnt;
    {0, 0, 0, 0, 0, 0}, //gpo1_cnt;
    {91, 481, 469, 657, 16, 785}, //gpo2_cnt;
    {130, 130, 0, 130, 16, 17}, //gpo3_cnt;
    {34, 125, 466, 489, 0, 0}, //gpo4_cnt;
    {5, 97, 446, 469, 0, 0}, //gpo5_cnt;
    {1024, 1056, 0, 0, 1, 1125}, //gpo6_cnt;
    {0, 0, 0, 0, 0, 0}, //gpo7_cnt;
    {14, 550, 15, 16, 17, 550}, //gpo8_cnt;
    744,//tri1_cnt;
    262,//tri2_cnt;
    489,//tri3_cnt;
    517,//tri4_cnt;
    0,//MINI_MODE;
    2,//SER_MODE;
	0,//reset_pos;  
    7,//DIFF_POS;
    10,//FIFO_HS_start;
    950,//h_active_start;
    958,//H_READ_CNT;
    860,//R_CLR_CNT;
    14,//CLK_V_CNT;
    550,//CLK_H_CNT;
    0x924,//CLK_MOD;
    160,//POL_CNT;
    1,//SGATE;
    30,//RAM12_L;
    58,//NEW_DE1_S;
    7360,//hstart;
    7409,//h_end;
    2087,//h_start1;
    2097,//h_end1;
    4127,//h_start2;
    4137,//h_end2;
    1124,//vdd_v_cnt;
    1100,//vdd_h_cnt;
    179,//vdd_cnt_fram;
    16,//cpv2_h;
    218,//cpv2_h1;
    600,//cpv2_h2;
    1,//n_clk;
    0,//n_clk1;
    0,//mode;
    0,//dual_mode;
    0,//trigate;
    1,//split_en;
};
/********
GPO0 :
GPO1 :
GPO2:
GPO3:
GPO4:
GPO5:
*******/
static const D_TCON_INIT_PARAM    tcon_param_N86 =
{
    {6, 4, 0, 15, 7, 7, 6, 4, 8, 18, 19}, //ctr_gpo;
    {1, 1, 1, 1, 1, 1, 1, 1, 1}, //gpo_initial;
    {90 + 36, 105 + 36, 478 + 36, 493 + 36, 1, 800}, //gpo0_cnt;
    {0, 0, 0, 0, 0, 0}, //gpo1_cnt;
    {771, 104, 360, 493, 1, 800}, //gpo2_cnt;
    {771, 104, 360, 493, 1, 800}, //gpo3_cnt;
    {389, 11, 1, 0, 15, 16}, //gpo4_cnt;
    {12, 358, 436, 489, 16, 17}, //gpo5_cnt;
    {91, 110, 0, 0, 0, 0}, //gpo6_cnt;
    {0, 0, 0, 0, 0, 0}, //gpo7_cnt;
    {0, 1200, 0, 130, 14, 16}, //gpo8_cnt;
    744,//tri1_cnt;
    262,//tri2_cnt;
    489,//tri3_cnt;
    517,//tri4_cnt;
    3,//MINI_MODE;
    2,//SER_MODE;
	1,//reset_pos;	
    7,//DIFF_POS;
    10,//FIFO_HS_start;
    950,//h_active_start;
    958,//H_READ_CNT;
    860,//R_CLR_CNT;
    14,//CLK_V_CNT;
    550,//CLK_H_CNT;
    0x924,//CLK_MOD;
    160,//POL_CNT;
    0,//SGATE;
    30,//RAM12_L;
    58,//NEW_DE1_S;
    20,//hstart;
    49,//h_end;
    2087,//h_start1;
    2097,//h_end1;
    4127,//h_start2;
    4137,//h_end2;
    1124,//vdd_v_cnt;
    1100,//vdd_h_cnt;
    179,//vdd_cnt_fram;
    16,//cpv2_h;
    218,//cpv2_h1;
    600,//cpv2_h2;
    1,//n_clk;
    0,//n_clk1;
    1,//mode;
    2,//dual_mode;
    0,//trigate;
    0,//split_en;
};

/********
GPO0 :
GPO1 :
GPO2:
GPO3:
GPO4:
GPO5:
*******/
static const D_TCON_INIT_PARAM    tcon_param_N56 =
{
    {6, 4, 0, 15, 7, 7, 6, 4, 8, 18, 19}, //ctr_gpo;
    {1, 1, 1, 1, 1, 1, 1, 1, 1}, //gpo_initial;
    {90 + 36, 105 + 36, 478 + 36, 493 + 36, 1, 800}, //gpo0_cnt;
    {0, 0, 0, 0, 0, 0}, //gpo1_cnt;
    {771, 104, 360, 493, 1, 800}, //gpo2_cnt;
    {771, 104, 360, 493, 1, 800}, //gpo3_cnt;
    {389, 11, 1, 0, 15, 16}, //gpo4_cnt;
    {12, 358, 436, 489, 16, 17}, //gpo5_cnt;
    {91, 110, 0, 0, 0, 0}, //gpo6_cnt;
    {0, 0, 0, 0, 0, 0}, //gpo7_cnt;
    {0, 1200, 0, 130, 14, 16}, //gpo8_cnt;
    744,//tri1_cnt;
    262,//tri2_cnt;
    489,//tri3_cnt;
    517,//tri4_cnt;
    3,//MINI_MODE;
    2,//SER_MODE;
	1,//reset_pos;	
    7,//DIFF_POS;
    10,//FIFO_HS_start;
    950,//h_active_start;
    958,//H_READ_CNT;
    860,//R_CLR_CNT;
    14,//CLK_V_CNT;
    550,//CLK_H_CNT;
    0x924,//CLK_MOD;
    160,//POL_CNT;
    0,//SGATE;
    30,//RAM12_L;
    58,//NEW_DE1_S;
    40,//hstart;
    49,//h_end;
    2087,//h_start1;
    2097,//h_end1;
    4127,//h_start2;
    4137,//h_end2;
    1124,//vdd_v_cnt;
    1100,//vdd_h_cnt;
    179,//vdd_cnt_fram;
    16,//cpv2_h;
    218,//cpv2_h1;
    600,//cpv2_h2;
    1,//n_clk;
    0,//n_clk1;
    1,//mode;
    2,//dual_mode;
    0,//trigate;
    0,//split_en;
};

void p_panel_get_tcon_info(D_U8 lvds_type,D_TCON_INIT_PARAM* param) D_FUNCPOSTFIT
{
	switch(lvds_type)
	   {
	   case 1://,BOE_768P_N56,BOE_768P_N56
		   memcpy((D_U8*)param,(D_U8*)&tcon_param_N56,sizeof(D_TCON_INIT_PARAM));
		   break;		   
	   case 2://,BOE_768P_N86,BOE_768P_N86
		   memcpy((D_U8*)param,(D_U8*)&tcon_param_N86,sizeof(D_TCON_INIT_PARAM));
		   break;	
	   case 3://,BOE_768P_N81,BOE_768P_N81
		   memcpy((D_U8*)param,(D_U8*)&tcon_param_N86,sizeof(D_TCON_INIT_PARAM));
		   break;		   
	   case 4://,HK_768P_PT320,HK_768P_PT320
		   memcpy((D_U8*)param,(D_U8*)&tcon_param_PT320,sizeof(D_TCON_INIT_PARAM));
		   break;			   
	   case 5://,BOE_1080P_N10,BOE_1080P_N10	   
	   case 6://,BOE_1080P_N40,BOE_1080P_N40
	   case 7://,TCL_1080P_ST48,TCL_1080P_ST48	
		   memcpy((D_U8*)param,(D_U8*)&tcon_param_N10,sizeof(D_TCON_INIT_PARAM));
		   break;	   
	   default:
		   memcpy((D_U8*)param,(D_U8*)&tcon_param_N86,sizeof(D_TCON_INIT_PARAM));
		   break;				   
	   }

}


void p_vip_set_panel_open(void) D_FUNCPOSTFIT
{
#if defined(D_SYSTEM_WIN32)
	return;
#else
	D_Lvds_Sequence sequence = {10,10,10,0,0};
	D_Tv_Config_Lvds_Sequence	 lvds_sequence;
#ifdef D_TV_IAMGE_SOURCE
	D_PanelParam panel_param;
	
	p_conf_get_panel_param(&panel_param); 
	if(panel_param.size)
	{
		memcpy((D_U8*)&sequence,(D_U8*)&panel_param.lvds_sequence,sizeof(D_Lvds_Sequence));
	}
#endif
	if(sequence.vcc_bl_swapon == 0)
	{
		d_panel_Set_LvdsVcc(1);
		d_task_wait(sequence.t2ms);
		d_panel_Set_LvdsData(1);
		d_task_wait(sequence.t3ms);
		d_panel_Set_LvdsBacklight(1);
	}
	else
	{
		d_panel_Set_LvdsBacklight(1);
		d_task_wait(sequence.t2ms);
		d_panel_Set_LvdsData(1);
		d_task_wait(sequence.t3ms);
		d_panel_Set_LvdsVcc(1);
	}
#endif
}

void p_vip_set_panel_close(void) D_FUNCPOSTFIT
{
#if defined(D_SYSTEM_WIN32)
		return;
#else
	D_Lvds_Sequence sequence = {10,10,10,0,0};
	D_Tv_Config_Lvds_Sequence	 lvds_sequence;
#ifdef D_TV_IAMGE_SOURCE
	D_PanelParam panel_param;
	
	p_conf_get_panel_param(&panel_param); 
	if(panel_param.size)
	{
		memcpy((D_U8*)&sequence,(D_U8*)&panel_param.lvds_sequence,sizeof(D_Lvds_Sequence));
	}
#endif

    if(sequence.vcc_bl_swapoff == 0)
    {
		d_panel_Set_LvdsBacklight(0);
        d_task_wait(sequence.t4ms);
        d_panel_Set_LvdsData(0);
        d_task_wait(sequence.t5ms);
		d_panel_Set_LvdsVcc(0);
    }
    else
    {
		d_panel_Set_LvdsVcc(0);
        d_task_wait(sequence.t4ms);
        d_panel_Set_LvdsData(0);
        d_task_wait(sequence.t5ms);
		d_panel_Set_LvdsBacklight(0);
    }
#endif
}


void p_vip_set_panel_init(void) D_FUNCPOSTFIT
{
#if defined(D_SYSTEM_WIN32)
		return;
#else
	d_panel_init();
	d_panel_Set_LvdsBacklight(0);
	d_panel_Set_LvdsVcc(0);
#endif
}

void p_tven_lvds_init(void) D_FUNCPOSTFIT
{
#if defined(D_SYSTEM_WIN32)
		return;
#else
#ifdef D_TV_IAMGE_SOURCE
	D_PanelParam panel_param;	
	D_U8 mini_mode;
	
	d_av_hmd_param_init();
	p_conf_get_panel_param(&panel_param); 
	mini_mode = panel_param.lvds_type;
	
	d_av_display_para_init(&panel_param.screenparam);	
    d_av_tven_lvds_para_init(&panel_param.tven_para);	
	d_av_display_invert(panel_param.tven_para.display_invert);
	d_av_lvds_init(mini_mode,&panel_param.lvds_init_param);
	
	if(mini_mode)
	{
		d_av_tcon_init(&panel_param.tcon_param);
	}	
	if(mini_mode == 4||mini_mode == 2)//pt320
	{
	  d_panel_Set_LVDS_TXCTRL(0x3f,0x01);
	}
#endif
#endif

}

static D_U8  c_lvds_freq =0;
void p_vip_set_panel_param(D_U8 val) D_FUNCPOSTFIT
{
#if defined(D_SYSTEM_WIN32)
		return;
#else
#ifdef D_TV_IAMGE_SOURCE
#if defined(D_SYSTEM_HROS)
	D_PanelParam panel_param;	
	D_U8 mini_mode;
	
	p_conf_get_panel_param(&panel_param); 
	if(panel_param.lvds_init_param.pll_freq != 384)return;
	if(val == 0)
	{
		D_U32 pll_freq;
		if(c_lvds_freq == 0)return;
		pll_freq = panel_param.lvds_init_param.pll_freq;
		d_pll_set_param_pll3(pll_freq,8);
	    d_av_tven_lvds_para_init(&panel_param.tven_para);	
		d_av_set_outputFreq();
		if(panel_param.lvds_type)panel_param.tven_para.total_line_60 +=210; 
		d_panel_Set_Lvds_vtotal(panel_param.tven_para.total_line_60);
		c_lvds_freq = 0;
		D_DUMP("c_lvds_freq(76.8) \n");

	}
	else
	{
		D_U32 vtotal50_t, vtotal60_t;
		D_U32 pll3_freq,pll_freq,v_total_50, v_total_60,h_total;
		D_U8 vp_div;
		
		if(c_lvds_freq == 1)return;
		
		vtotal50_t = panel_param.tven_para.total_line_50;
		vtotal60_t = panel_param.tven_para.total_line_60;
		
		vp_div = panel_param.lvds_init_param.vp_div;
		pll_freq = panel_param.lvds_init_param.pll_freq;
		pll3_freq = (pll_freq / vp_div);
		pll3_freq = (pll3_freq+3);
		pll_freq = pll3_freq*vp_div;
		panel_param.tven_para.out_freq_50 = (D_U32)pll_freq * 1000000 / vp_div;
		panel_param.tven_para.out_freq_60 = (D_U32)pll_freq * 1000000 / vp_div;
		h_total = panel_param.tven_para.total_pix_per_line_60;
		panel_param.tven_para.total_line_50 = pll3_freq*1000000/(h_total*50);
		panel_param.tven_para.total_line_50 &= (~0x01);
		panel_param.tven_para.total_line_60 = pll3_freq*1000000/(h_total*60);
		panel_param.tven_para.total_line_60 &= (~0x01);

		panel_param.tven_para.vsync_lastde_delay_50 += (panel_param.tven_para.total_line_50-vtotal50_t);
		panel_param.tven_para.vsync_lastde_delay_60 += (panel_param.tven_para.total_line_60-vtotal60_t);

		d_pll_set_param_pll3(pll_freq,8);
	    d_av_tven_lvds_para_init(&panel_param.tven_para);		
		d_av_set_outputFreq();
		if(panel_param.lvds_type)panel_param.tven_para.total_line_60 +=210; 
		d_panel_Set_Lvds_vtotal(panel_param.tven_para.total_line_60);
		c_lvds_freq = 1;
		D_DUMP("c_lvds_freq(79) \n");
	}
#endif
#endif
#endif

}




















