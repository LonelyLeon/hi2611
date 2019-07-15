/**@defgroup tv vip功能实现
*@{*/
/** @file
* @brief vip功能实现
* @author hegx
* @date 2013-09-06 hegx: 建立文件
*/

#include <stdio.h>
#include <string.h>
#include "dSys.h"
#include "dVipPorting.h"
#include "ptvConfig.h"

static D_U32 lastvipinitinput = 0xffffffff;//记录上次的源
static D_U32 lastvipparaminput = 0xffffffff;//记录上次的源
static D_U8  lastvipparamflag = 0xff;//记录上次的高标清标识
static D_U8  lastvipparamntscflag = 0xff;//记录上次的高标清标识
static D_U8  lastvipparamprogflag = 0xff;//记录上次的高标清标识

D_U8 p_vip_get_dbinput(D_U32 input) D_FUNCPOSTFIT
{
    D_DBTvMode tinput = D_DB_TVMODE_TV;

    switch(input)
    {
        case D_VID_IUTPUT_TV:
            tinput = D_DB_TVMODE_TV;
            break;
        case D_VID_IUTPUT_DTV:
            tinput = D_DB_TVMODE_DTV;
            break;
        case D_VID_IUTPUT_AV1:
        case D_VID_IUTPUT_AV2:
            tinput = D_DB_TVMODE_AV;
            break;
#ifndef D_TV_IAMGE_SOURCE
        case D_VID_IUTPUT_YPBPR:
            tinput = D_DB_TVMODE_Component;
            break;
#endif			
        case D_VID_IUTPUT_HDMI1:
        case D_VID_IUTPUT_HDMI2:
        case D_VID_IUTPUT_HDMI3:
            tinput = D_DB_TVMODE_HDMI;
            break;
        case D_VID_IUTPUT_USB1:
        case D_VID_IUTPUT_USB2:
        case D_VID_IUTPUT_USB3:
#ifdef D_TV_LIULINK_SOURCE
        case D_VID_IUTPUT_LIULINK:
#endif
            tinput = D_DB_TVMODE_USB;
            break;
        default:
            tinput = D_DB_TVMODE_USB;
            break;
    }
    return tinput;
}


/** @brief 亮度
*/
void p_vip_set_Brightness(D_U32 input, D_U8 val) D_FUNCPOSTFIT
{
    D_PCURVE_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);

	if(lastvipparamflag)
	{
		if(p_tvconf_get_hdpcurve_param(&param, bdinput, 0) == D_OK)
		{
			d_vip_setBrightness(val, (D_U8*)&param);
		}
	}
	else
	{
		if(p_tvconf_get_pcurve_param(&param, bdinput, 0) == D_OK)
		{
			d_vip_setBrightness(val, (D_U8*)&param);
		}
	}


}
/** @brief 对比度
*/
void p_vip_set_Constrast(D_U32 input, D_U8 val) D_FUNCPOSTFIT
{
    D_PCURVE_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);
	if(lastvipparamflag)
	{
		if(p_tvconf_get_hdpcurve_param(&param, bdinput, 1) == D_OK)
		{
			d_vip_setConstrast(val, (D_U8*)&param);
		}

	}
	else
	{
		if(p_tvconf_get_pcurve_param(&param, bdinput, 1) == D_OK)
		{
			d_vip_setConstrast(val, (D_U8*)&param);
		}
	}


}

/** @brief 清晰度
*/
void p_vip_set_Sharpness(D_U32 input, D_U8 val) D_FUNCPOSTFIT
{
    D_PCURVE_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);
	if(lastvipparamflag)
	{
		if(p_tvconf_get_hdpcurve_param(&param, bdinput, 4) == D_OK)
		{
			d_vip_setSharpness(val, (D_U8*)&param);
		}
	}
	else
	{
		if(p_tvconf_get_pcurve_param(&param, bdinput, 4) == D_OK)
		{
			d_vip_setSharpness(val, (D_U8*)&param);
		}

	}

}
/** @brief 饱和度
*/
void p_vip_set_Saturation(D_U32 input, D_U8 val) D_FUNCPOSTFIT
{
    D_PCURVE_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);

	if(lastvipparamflag)
	{	
		if(p_tvconf_get_hdpcurve_param(&param, bdinput, 2) == D_OK)
		{
			d_vip_setSaturation(val, (D_U8*)&param);
		}
	}
	else
	{
		
		if(p_tvconf_get_pcurve_param(&param, bdinput, 2) == D_OK)
		{
			d_vip_setSaturation(val, (D_U8*)&param);
		}
	}

}
/** @brief 色调
*/
void p_vip_set_Hue(D_U32 input, D_U8 val) D_FUNCPOSTFIT
{
    D_PCURVE_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);

	if(lastvipparamflag)
	{	
		if(p_tvconf_get_hdpcurve_param(&param, bdinput, 3) == D_OK)
		{
			d_vip_setHue(val, (D_U8*)&param);
		}
	}
	else
	{
		
		if(p_tvconf_get_pcurve_param(&param, bdinput, 3) == D_OK)
		{
			d_vip_setHue(val, (D_U8*)&param);
		}
	}
}

/** @brief
*/
void p_vip_set_Temperature(D_U32 input, D_U8 val, D_U8 flag) D_FUNCPOSTFIT
{
    D_CTEMP_SET tparam;
    D_CSC_SET cscparam;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);

    if(p_tvconf_get_ctemp_param(&tparam, bdinput, val) == D_OK)
    {
        if(flag)
        {
            if(p_tvconf_get_hdcsc_set_param(&cscparam, bdinput) == D_OK)
            {
                d_vip_setTemperature(input, (D_U8*)&tparam, (D_U8*)&cscparam);
            }
        }
        else
        {
            if(p_tvconf_get_csc_set_param(&cscparam, bdinput) == D_OK)
            {
                d_vip_setTemperature(input, (D_U8*)&tparam, (D_U8*)&cscparam);
            }
        }

    }
}
/** @brief
*/
void p_vip_set_ImageMode(D_U32 input, D_U8 val, D_U8 ntscflag) D_FUNCPOSTFIT
{
    D_PMODE_SET tparam;
    D_PCURVE_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);

    if(p_tvconf_get_pmodeset_param(&tparam, bdinput, val) == D_OK)
    {
		if(ntscflag)
		{
	        if(p_tvconf_get_hdpcurve_param(&param, bdinput, 0) == D_OK)
	        {
	            d_vip_setBrightness(tparam.brightness, (D_U8*)&param);
	        }
	        if(p_tvconf_get_hdpcurve_param(&param, bdinput, 2) == D_OK)
	        {
	            d_vip_setSaturation(tparam.color, (D_U8*)&param);
	        }
	        if(p_tvconf_get_hdpcurve_param(&param, bdinput, 4) == D_OK)
	        {
	            d_vip_setSharpness(tparam.sharpness, (D_U8*)&param);
	        }
	        if(p_tvconf_get_hdpcurve_param(&param, bdinput, 1) == D_OK)
	        {
	            d_vip_setConstrast(tparam.contrast, (D_U8*)&param);
	        }
	        if(p_tvconf_get_hdpcurve_param(&param, bdinput, 3) == D_OK)
	        {
	            d_vip_setHue(tparam.tint, (D_U8*)&param);
	        }
		}
		else
		{
	        if(p_tvconf_get_pcurve_param(&param, bdinput, 0) == D_OK)
	        {
	            d_vip_setBrightness(tparam.brightness, (D_U8*)&param);
	        }
	        if(p_tvconf_get_pcurve_param(&param, bdinput, 2) == D_OK)
	        {
	            d_vip_setSaturation(tparam.color, (D_U8*)&param);
	        }
	        if(p_tvconf_get_pcurve_param(&param, bdinput, 4) == D_OK)
	        {
	            d_vip_setSharpness(tparam.sharpness, (D_U8*)&param);
	        }
	        if(p_tvconf_get_pcurve_param(&param, bdinput, 1) == D_OK)
	        {
	            d_vip_setConstrast(tparam.contrast, (D_U8*)&param);
	        }
	        if(p_tvconf_get_pcurve_param(&param, bdinput, 3) == D_OK)
	        {
	            d_vip_setHue(50, (D_U8*)&param);
	        }
		}
    }
}

/** @brief
*/
void p_vip_set_bldim(D_U32 input) D_FUNCPOSTFIT
{
    D_BLDIM_SET param;
    D_U8 bdinput, backlight;

    bdinput =  p_vip_get_dbinput(input);
    if(p_tvconf_get_bldim_set_param(&param, bdinput) == D_OK)
    {
        if(p_tvconf_get_bldim_backlight(&backlight, bdinput) == D_OK)
        {
            d_vip_setBldim((D_U8*)&param, backlight);
        }
    }
}
/** @brief
*/
void p_vip_set_nr(D_U32 input, D_U8 flag, D_U8 prog) D_FUNCPOSTFIT
{
    D_U8 val;
    D_NR_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);
    if(p_tvconf_get_cur_nrmode(&val, bdinput)  != D_OK)
    {
        return;
    }
    if(flag)
    {
        if(p_tvconf_get_hdnr_set_param(&param, bdinput, val) == D_OK)
        {
            d_vip_setNr((D_U8*)&param);
        }
    }
    else
    {
        if(p_tvconf_get_nr_set_param(&param, bdinput, val) == D_OK)
        {
            d_vip_setNr((D_U8*)&param);
        }
    }
    if(prog)
    {
        d_vip_setNr_Prog(val);
    }
}
/** @brief
*/
#ifndef D_TV_IAMGE_SOURCE
void p_vip_set_comb(D_U32 input, D_U8 flag) D_FUNCPOSTFIT
{
    D_COMB_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);
    if(flag)
    {
        if(p_tvconf_get_hdcomb_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setComb((D_U8*)&param);
        }
    }
    else
    {
        if(p_tvconf_get_comb_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setComb((D_U8*)&param);
        }
    }
}
/** @brief
*/
void p_vip_set_comp(D_U32 input, D_U8 flag) D_FUNCPOSTFIT
{
    D_COMP_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);
    if(flag)
    {
        if(p_tvconf_get_hdcomp_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setComp((D_U8*)&param);
        }
    }
    else
    {
        if(p_tvconf_get_comp_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setComp((D_U8*)&param);
        }
    }

}
/** @brief
*/
void p_vip_set_adc(D_U32 input, D_U8 flag) D_FUNCPOSTFIT
{
    D_ADC_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);
    if(flag)
    {
        if(p_tvconf_get_hdadc_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setAdc((D_U8*)&param);
        }
    }
    else
    {
        if(p_tvconf_get_adc_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setAdc((D_U8*)&param);
        }
    }

}

void p_vip_set_difm(D_U32 input, D_U8 flag) D_FUNCPOSTFIT
{
    D_DIFM_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);
    if(flag)
    {
        if(p_tvconf_get_hddifm_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setDifm((D_U8*)&param);
        }
    }
    else
    {
        if(p_tvconf_get_difm_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setDifm((D_U8*)&param);
        }
    }
}
/** @brief
*/
void p_vip_set_ce(D_U32 input, D_U8 flag) D_FUNCPOSTFIT
{
    D_CE_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);
    if(flag)
    {
        if(p_tvconf_get_hdce_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setCe((D_U8*)&param);
        }
    }
    else
    {
        if(p_tvconf_get_ce_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setCe((D_U8*)&param);
        }
    }
}
/** @brief
*/
void p_vip_set_ase(D_U32 input, D_U8 flag) D_FUNCPOSTFIT
{
    D_ASE_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);
    if(flag)
    {
        if(p_tvconf_get_hdase_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setAse((D_U8*)&param);
        }
    }
    else
    {
        if(p_tvconf_get_ase_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setAse((D_U8*)&param);
        }
    }
}
/** @brief
*/
void p_vip_set_ftc(D_U32 input, D_U8 flag) D_FUNCPOSTFIT
{
    D_FTC_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);
    if(flag)
    {
        if(p_tvconf_get_hdftc_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setFtc((D_U8*)&param);
        }
    }
    else
    {
        if(p_tvconf_get_ftc_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setFtc((D_U8*)&param);
        }
    }
}
/** @brief
*/
void p_vip_set_icm(D_U32 input, D_U8 flag) D_FUNCPOSTFIT
{
    D_ICM_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);
    if(flag)
    {
        if(p_tvconf_get_hdicm_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setIcm((D_U8*)&param);
        }
    }
    else
    {
        if(p_tvconf_get_icm_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setIcm((D_U8*)&param);
        }
    }
}
/** @brief
*/
#else
void p_vip_set_dce(D_U32 input, D_U8 flag) D_FUNCPOSTFIT
{
    D_DCE_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);

    if(p_tvconf_get_dce_set_param(&param, bdinput) == D_OK)
    {
        d_vip_setDce((D_U8*)&param);
    }

}

void p_vip_set_colorsettng(D_U32 input, D_U8 flag) D_FUNCPOSTFIT
{
    D_CHROMA_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);

    if(p_tvconf_get_colorsettng_param(&param, bdinput) == D_OK)
    {
        d_vip_setChroma((D_U8*)&param);
    }

}

void p_vip_set_cm(D_U32 input, D_U8 flag) D_FUNCPOSTFIT
{
    D_CM_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);

    if(p_tvconf_get_cmset_param(&param, bdinput) == D_OK)
    {
        d_vip_Set_CM((D_U8*)&param);
    }

}

#endif
void p_vip_set_de(D_U32 input, D_U8 flag) D_FUNCPOSTFIT
{
    D_DE_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);
    if(flag)
    {
        if(p_tvconf_get_hdde_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setDe((D_U8*)&param);
        }

    }
    else
    {
        if(p_tvconf_get_de_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setDe((D_U8*)&param);
        }
    }
}
/** @brief
*/

void p_vip_set_gamma(D_U32 input, D_U8 flag) D_FUNCPOSTFIT
{
    D_GAMMA_SET param;
    D_U8 bdinput;

    bdinput =  p_vip_get_dbinput(input);
    if(flag)
    {
        if(p_tvconf_get_hdgamma_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setGamma((D_U8*)&param);
        }

    }
    else
    {
        if(p_tvconf_get_gamma_set_param(&param, bdinput) == D_OK)
        {
            d_vip_setGamma((D_U8*)&param);
        }
    }
}
/** @brief
flag :0--apl;1---NTSC
*/


/** @brief
*/
void p_vip_set_audio(D_U32 input) D_FUNCPOSTFIT
{
    D_AUDIO_Peq param[TV_AUDIO_FEQ];
    D_U8 en;
    D_U8 bdinput, audio_mode, i;
    D_U16 t_ffft;
    D_U8 round_flag;
    D_DRC_SET audio_drc;

    bdinput =  p_vip_get_dbinput(input);
//模式
//环绕
    p_tvconf_get_cur_round(&round_flag, bdinput);
    p_tvconf_get_audio_drc(&audio_drc, bdinput);

    d_av_audio_bo_drc_set(audio_drc.drc_threshold, audio_drc.drc_compress);
    d_av_audio_bo_drc_enable(audio_drc.drc_en);

    p_tvconf_get_cur_audiomode(&audio_mode, bdinput);
    p_tvconf_get_cur_t_ffft(&t_ffft, bdinput, audio_mode);
#ifdef D_TV_IAMGE_SOURCE
    for(i = 0; i < TV_AUDIO_FEQ; i ++)
	{
		p_tvconf_get_audio_peq_set_param(&param[i], bdinput, audio_mode, i);
	}
    d_av_Audio_PEQ(0, param, TV_AUDIO_FEQ, t_ffft, D_Digital_Audio);
#else	
	if(audio_mode == 0)//标准模式
    {
        for(i = 0; i < 5; i ++)
        {
            p_tvconf_get_audio_peq_set_param(&param[i], bdinput, audio_mode, i);
        }
        d_av_Audio_PEQ(0, param, 5, t_ffft, D_PEQ);
    }
    else
    {
        for(i = 0; i < 9; i ++)
        {
            p_tvconf_get_audio_peq_set_param(&param[i], bdinput, audio_mode, i);
        }
        d_av_Audio_PEQ(0, param, 9, t_ffft, D_Digital_Audio);
    }
#endif	
    if(round_flag == 0)
    {
        d_av_audio_srs(0,D_Surround_close);
    }
    else
    {
        d_av_audio_srs(0,D_Surround_open);
    }

}

/** @brief
* @param[in] D_U32 input  输入源
* @param[in] D_U8 flag    0:标清 1:高清
* @param[in] D_U8 ntscflag    0:pal 1:ntsc
* @param[in] D_U8 force   是否强制
*/
void p_vip_init(D_U32 input, D_U8 flag, D_U8 ntscflag, D_U8 force) D_FUNCPOSTFIT
{
///////使能
    D_U8 bdinput;
    D_VE_SET param;
	D_U8 video_mode;
	D_U8   color_mode;

    if((lastvipinitinput == input)  && (force == 0))
    {
        return;
    }
    bdinput =  p_vip_get_dbinput(input);

    p_vip_set_bldim(input);
    if(input == D_VID_IUTPUT_AV1 || input == D_VID_IUTPUT_AV2 || input == D_VID_IUTPUT_TV)
    {
        if(p_tvconf_get_cur_imagemode(&video_mode, bdinput)  == D_OK)
        {
			p_vip_set_ImageMode(input,video_mode,ntscflag);
        }
        if(p_tvconf_get_cur_colormode(&color_mode, bdinput) == D_OK)
        {
 	       p_vip_set_Temperature(input, color_mode,ntscflag);        
        }      
        p_vip_set_de(input, ntscflag); // added by wangyg on 2015-09-29
        p_vip_set_nr(input, ntscflag, 0);
#ifndef D_TV_IAMGE_SOURCE
        p_vip_set_difm(input, ntscflag);
//        p_vip_set_de(input, ntscflag);    // moved upward by wangyg on 2015-09-29
        p_vip_set_ce(input, ntscflag);
        p_vip_set_ase(input, ntscflag);
        p_vip_set_ftc(input, ntscflag);
        p_vip_set_icm(input, ntscflag);
        p_vip_set_comb(input, ntscflag);
        p_vip_set_comp(input, ntscflag);
        p_vip_set_adc(input, ntscflag);
#else
        p_vip_set_dce(input, ntscflag);
        p_vip_set_colorsettng(input, ntscflag);
        p_vip_set_cm(input, ntscflag);
#endif
        d_av_vcom_get_vblank_exit();
        p_vip_set_gamma(input, ntscflag);
        lastvipparamflag = ntscflag;//记录上次的高标清标识
        lastvipparamntscflag = ntscflag;
    }
    else
    {
        if(p_tvconf_get_cur_imagemode(&video_mode, bdinput)  == D_OK)
        {
			p_vip_set_ImageMode(input,video_mode,flag);
        }
        if(p_tvconf_get_cur_colormode(&color_mode, bdinput) == D_OK)
        {
 	       p_vip_set_Temperature(input, color_mode,flag);        
        }     
        p_vip_set_de(input, flag);    // added by wangyg on 2015-09-29
        p_vip_set_nr(input, flag, 0);
#ifndef D_TV_IAMGE_SOURCE
        p_vip_set_difm(input, flag);
//        p_vip_set_de(input, flag);    // moved upward by wangyg on 2015-09-29
        p_vip_set_ce(input, flag);
        p_vip_set_ase(input, flag);
        p_vip_set_ftc(input, flag);
        p_vip_set_icm(input, flag);
        p_vip_set_comb(input, ntscflag);
        p_vip_set_comp(input, flag);
        p_vip_set_adc(input, flag);
#else
        p_vip_set_dce(input, ntscflag);
        p_vip_set_colorsettng(input, ntscflag);
        p_vip_set_cm(input, ntscflag);
#endif
        d_av_vcom_get_vblank_exit();
        p_vip_set_gamma(input, flag);
        lastvipparamflag = flag;//记录上次的高标清标识
        lastvipparamntscflag = flag;
    }
    //ve
    if(p_tvconf_get_veset_param(&param, bdinput)  == D_OK)
    {
        d_vip_Set_VE((D_U8*)&param);
    }
#ifdef D_TV_IAMGE_SOURCE
   //CM
    if(p_tvconf_get_cmset_param(&param, bdinput)  == D_OK)
    {
        d_vip_Set_CM((D_U8*)&param);
    }
#endif
    if((lastvipinitinput != input) || (force == 1))
    {
        p_vip_set_audio(input);
    }
    lastvipinitinput = input;//记录上次的源
    lastvipparamprogflag = 0;
}
/** @brief 切换通道前关闭相关功能
* @param[in] D_U32 input  输入源
* @param[in] D_U8 flag    0:标清 1:高清
* @param[in] D_U8 ntscflag    0:pal 1:ntsc
* @param[in] D_U8 force   是否强制
*/
void p_vip_changeinput(D_U32 lastinput,D_U32 input) D_FUNCPOSTFIT
{
    D_BLDIM_SET param;
    D_U8 bdinput, backlight;

    bdinput =  p_vip_get_dbinput(input);
    if(p_tvconf_get_bldim_set_param(&param, bdinput) == D_OK)
    {
        if(p_tvconf_get_bldim_backlight(&backlight, bdinput) == D_OK)
        {
#ifndef D_TV_IAMGE_SOURCE
        	param.gd_on = 0;//
 #endif
            d_vip_setBldim((D_U8*)&param, backlight);
        }
    }
}

/** @brief
* @param[in] D_U32 input  输入源
* @param[in] D_U8 flag    0:标清 1:高清
* @param[in] D_U8 ntscflag    0:pal 1:ntsc
* @param[in] D_U8 force   是否强制
*/
void p_vip_set_param(D_U32 input, D_U8 flag, D_U8 ntscflag, D_U8 prog, D_U8 force) D_FUNCPOSTFIT
{
///////使能
    D_U8 bdinput;
    D_VE_SET param;
	D_U8 video_mode;
	D_U8   color_mode;

    if ((lastvipparaminput == input) && (lastvipparamflag == flag) && (lastvipparamntscflag == ntscflag) && (force == 0))
    {
        return;
    }
    bdinput =  p_vip_get_dbinput(input);
    D_DUMP("p_vip_set_param flag %d ntscflag%d\n", flag, ntscflag);
    if(input == D_VID_IUTPUT_AV1 || input == D_VID_IUTPUT_AV2 || input == D_VID_IUTPUT_TV)
    {
        if(p_tvconf_get_cur_imagemode(&video_mode, bdinput)  == D_OK)
        {
			p_vip_set_ImageMode(input,video_mode,ntscflag);
        }
        if(p_tvconf_get_cur_colormode(&color_mode, bdinput) == D_OK)
        {
 	       p_vip_set_Temperature(input, color_mode,ntscflag);        
        }    
        p_vip_set_de(input, ntscflag);  // added by wangyg on 2015-09-29
        p_vip_set_nr(input, ntscflag, prog);
#ifndef D_TV_IAMGE_SOURCE
        p_vip_set_difm(input, ntscflag);
//        p_vip_set_de(input, ntscflag);    // moved upward by wangyg on 2015-09-29
        p_vip_set_ce(input, ntscflag);
        p_vip_set_ase(input, ntscflag);
        p_vip_set_ftc(input, ntscflag);
        p_vip_set_icm(input, ntscflag);
        p_vip_set_comb(input, ntscflag);
        p_vip_set_comp(input, ntscflag);
        p_vip_set_adc(input, ntscflag);
#else
        p_vip_set_dce(input, ntscflag);
        p_vip_set_colorsettng(input, ntscflag);
        p_vip_set_cm(input, ntscflag);
#endif
        d_av_vcom_get_vblank_exit();
       // p_vip_set_gamma(input, ntscflag);
        lastvipparamflag = ntscflag;//记录上次的高标清标识
        lastvipparamntscflag = ntscflag;
    }
    else
    {
        if(p_tvconf_get_cur_imagemode(&video_mode, bdinput)  == D_OK)
        {
			p_vip_set_ImageMode(input,video_mode,flag);
        }
        if(p_tvconf_get_cur_colormode(&color_mode, bdinput) == D_OK)
        {
 	       p_vip_set_Temperature(input, color_mode,flag);        
        }     
        p_vip_set_de(input, flag); // added by wangyg on 2015-09-29
        p_vip_set_nr(input, flag, prog);
#ifndef D_TV_IAMGE_SOURCE
        p_vip_set_difm(input, flag);
//        p_vip_set_de(input, flag);    // moved upward by wangyg on 2015-09-29
        p_vip_set_ce(input, flag);
        p_vip_set_ase(input, flag);
        p_vip_set_ftc(input, flag);
        p_vip_set_icm(input, flag);
	 p_vip_set_comb(input, ntscflag);
        p_vip_set_comp(input, flag);
        p_vip_set_adc(input, flag);
#else
        p_vip_set_dce(input, ntscflag);
        p_vip_set_colorsettng(input, ntscflag);
        p_vip_set_cm(input, ntscflag);
#endif
        d_av_vcom_get_vblank_exit();
        //p_vip_set_gamma(input, flag);
        lastvipparamflag = flag;//记录上次的高标清标识
        lastvipparamntscflag = flag;
    }
    lastvipparamprogflag = prog;
    lastvipparaminput = input;//记录上次的源

}

/** @brief
* @return  0:标清 1:高清
*/
D_U8 p_vip_get_hdflag(void) D_FUNCPOSTFIT
{
    return lastvipparamflag;
}

/** @brief
* @return   0:pal 1:ntsc
*/
D_U8 p_vip_get_ntscflag(void) D_FUNCPOSTFIT
{
    return lastvipparamntscflag;
}
D_U8 p_vip_get_progflag(void) D_FUNCPOSTFIT
{
    return lastvipparamprogflag;
}
/** @brief
* @return   0:pal 1:ntsc
*/
D_U8 p_vip_set_sscg(void) D_FUNCPOSTFIT
{
    D_LVDSSSCG_SET lvds;
    D_MIUSSCG_SET miu;

    p_tvconf_get_lvds_sscg (&lvds);
    p_tvconf_get_miu_sscg (&miu);
    d_lvds_Set_Sscg(lvds.enable, lvds.mode, lvds.ssc_span, lvds.ssc_step);
    d_miu_Set_Sscg(miu.enable, miu.mode, miu.ssc_span, miu.ssc_step);

}



/**@}*/
