/** @file
* @brief 声音相关配置
* @author hegx
* @date 2017-6-13 hegx: 建立文件
*/
#include <stdio.h>
#include <string.h>
#include "dDebug.h"
#include "dAV.h"
#include "ptvConfig.h"

/** @breif  根据20个音量计算中间值*/
static void check_audio_factor(D_U16* output,D_U16* vol) D_FUNCPOSTFIT
{
	D_U16 i,j,vol_diff;
	for(i = 0; i < TV_VOL_WAVE; i++)
	{
		(i == 0) ? (vol_diff = vol[i] / 5) : (vol_diff = (vol[i] - vol[i - 1]) / 5);
		for(j = 1; j < 5; j++)
		{
			(i == 0) ? (output[5 * i + j] = j * vol_diff) : (output[5 * i + j] = vol[i - 1] + j * vol_diff);
		}
		output[5 * (i + 1)] = vol[i];
	}

}

/** @breif */
static D_U8 get_vol_db_idx(D_VidInputType input) D_FUNCPOSTFIT
{
	D_U8 idx = 0;

	switch(input)
	{
		case D_VID_IUTPUT_TV:
  		case D_VID_IUTPUT_AV1:
  		case D_VID_IUTPUT_AV2:
    		idx = 0;
			break;
		case D_VID_IUTPUT_DTV:
			idx = 1;
			break;
		case D_VID_IUTPUT_USB1:
		case D_VID_IUTPUT_USB2:
			idx = 2;
			break;
		case D_VID_IUTPUT_HDMI1:
		case D_VID_IUTPUT_HDMI2:
			idx = 3;
			break;
		default:
    		idx = 0;
			break;
	}
	return idx;
}
/** @breif 
param num:HI_ATV 0;HI_DTV 1;HI_CVBS 2;HI_YCBCR 3;HI_HDMI 4;HI_USB 5
*/
static D_U8 get_avc_db_idx(D_VidInputType input) D_FUNCPOSTFIT
{
	D_U8 idx = 0;

	switch(input)
	{
		case D_VID_IUTPUT_TV:
    		idx = 0;
			break;
		case D_VID_IUTPUT_DTV:
			idx = 1;
			break;
  		case D_VID_IUTPUT_AV1:
  		case D_VID_IUTPUT_AV2:
			idx = 2;
			break;	
		case D_VID_IUTPUT_S:
		case D_VID_IUTPUT_YPBPR:
		case D_VID_IUTPUT_VGA:
			idx = 3;
			break;				
		case D_VID_IUTPUT_HDMI1:
		case D_VID_IUTPUT_HDMI2:
		case D_VID_IUTPUT_HDMI3:
			idx = 4;
			break;
		case D_VID_IUTPUT_USB1:
		case D_VID_IUTPUT_USB2:
			idx = 5;
			break;			
		default:
    		idx = 0;
			break;
	}
	return idx;
}

/** @breif */
void audio_config_init(void) D_FUNCPOSTFIT
{
	D_U16 cur_audio_factor[100+1] ={0};
	D_U16 db_audio_factor[20+1] ={0};
    D_AVC_SET avc[TV_AVC_INPUT_NUM];
    D_Avc_Param avc_param;	
	D_U8 i;   
	p_tvconf_get_avc(avc);
	for(i = 0; i < D_VID_IUTPUT_MAX;i ++)
	{
		D_U8 dbid;  
		dbid=get_vol_db_idx((D_VidInputType)i);
		p_tvconf_get_vol(db_audio_factor,dbid);
		check_audio_factor(cur_audio_factor,db_audio_factor);	
		d_av_audio_factor_set(0,&cur_audio_factor[0],1,(D_VidInputType)i);
        memset(&avc_param , 0 , sizeof(avc_param));
		
		dbid=get_avc_db_idx((D_VidInputType)i);		
        avc_param.base_level = avc[dbid].base_level;
        avc_param.base_avc = avc[dbid].base_avc;
        avc_param.level_step = avc[dbid].level_step;
        avc_param.now_level_offset = avc[dbid].now_level_offset;
        avc_param.now_close_avc = avc[dbid].now_close_avc;
        avc_param.now_open_avc = avc[dbid].now_open_avc;
        d_av_audio_avc_base_set(avc_param , dbid);		
	}	

    return ;
}
