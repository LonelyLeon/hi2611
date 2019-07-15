/** @file
* @brief 音视频设备操作
* @author 龚克
* @date 2005-5-18 龚克: 建立文件
*   @date 2005-8-24 龚克: 设备属性增加前端设备ID成员
* @date 2006-8-2 shanzs:
        增加D_VidPicParam结构
        增加D_VidPicRatio结构
        增加D_VidRatioType类型
        增加d_av_set_pic_param函数
        增加d_av_set_pic_ratio函数
*/

#ifndef _D_AV_H_
#define _D_AV_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dIO.h"

/** @brief N/P参数*/
typedef enum
{
    PAL,
    NTSC,
} D_Current_Pal_Ntsc_Mode;

/** @brief video_ratio参数*/
typedef enum
{
    v_4_3_TO_16_9_LB,
    v_4_3_TO_16_9_PS,
    v_16_9_TO_4_3_LB,
    v_16_9_TO_4_3_PS,
    v_tv_zoom_1x,
    v_tv_4_to_3,
    v_tv_overall_screen,
    v_tv_center_display,
    v_DEFAULT_DISPLAY,
} D_Current_display_ratio_Mode;

/** @brief 音视频设备句柄*/
typedef D_Handle    D_HAV;

/** @brief 音视频设备属性*/
typedef struct
{
    D_ID                id;             /**< 设备ID*/
    D_ID                fend_id;    /**< 音视频设备对应的前端设备ID*/
    D_U8               decodetype;  /**< 视频解码类型,用于控制播放缓冲区内存大小*/
    D_U8               wait_sync_type;/**< 等同步方式*/
} D_AVAttr;


/** @brief 最大音量参数值*/
#define AUDIO_PLAY_CTRL_VOL_MODE        0
#define DSP_CTRL_VOL_MODE           1
#define AUDIO_VOL_CTRL      AUDIO_PLAY_CTRL_VOL_MODE//需要与底层驱动一致
#if (AUDIO_VOL_CTRL == DSP_CTRL_VOL_MODE)
#define MAX_VOLUME  60
#else
#define MAX_VOLUME  79
#endif

/** @brief 按缺省值初始化音视频设备参数*/
#define D_AV_ATTR_INIT(_a)\
    D_MACRO_BEGIN\
        (_a)->id = 0;\
    D_MACRO_END

/** @brief 音视频设备事件*/
typedef enum
{
    D_AV_EVT_VID_FMT_CHANGE,    /**< 视频制式变化*/
    D_AV_EVT_VID_INPUT_FMT_CHANGE,    /**< 输入视频制式变化*/
    D_AV_EVT_VID_lOCK_LOSE,    /**< 失锁*/
    D_AV_EVT_NEW_PIC_START,     /**< 视频新画面开始播放*/
    D_AV_EVT_NEW_AUD_START,     /**< 音频信数据开始播放*/
    D_AV_EVT_HD_PIC_CANNOT_PLAY,/**< 高清节目不可播放*/
	D_AV_EVT_UNSUPPORTED_AUD,/**< 不支持的音频*/
} D_AVEvent;

/** @brief 音视频设备事件参数 */
typedef struct
{
    D_AVEvent evt;
    D_Ptr param;
} D_AVEventParam;

/** @brief 音视频设备事件回调
*
*evt=D_AV_EVT_VID_FMT_CHANGE, param为D_VidFormat类型
*/
typedef void (*D_AVCallback) (D_HAV hav, D_Handle handle, D_AVEvent evt, D_U32 param) D_FUNCPOSTFIT;

/** @brief 音视频播放方式*/
typedef enum
{
    D_AV_PLAY_TV,           /**< 播放电视节目*/
    D_AV_PLAY_RADIO     /**< 播放广播节目*/
} D_AVPlayMode;

/** @brief TV or PVR*/
typedef enum
{
    D_AVSourceMode_TV,          /**< TV*/
	D_AVSourceMode_PVR,		/**< PVR*/
	
	/* 数码视讯ts包加扰功能，使用pvr功能录音视频ts包数据，解析后，然后经pvr播放功能播放，
	但是却不是与平常所说的从usb里读取文件的pvr相同，播放节目时基本还是走的正常电视流程，
	但因ca高安 dsp相关参数 与其它方式略有区别，故增加一种特殊源 @20160912*/
	D_AVSourceMode_TS_scramble = 0x10,		/**< PVR*/
} D_AVSourceMode;

/** @brief HW or PVR*/
typedef enum
{
    D_PVR_START,
    D_PVR_WATINGHW = 1 << 1,    /**< 等待视频宽高*/
    D_PVR_VIDDECODE_OK = 1 << 2, /**< 视频解码OK*/
    D_PVR_AUDDECODE_OK = 1 << 3, /**< 音频解码OK*/
    D_PVR_AUD_VID_OK = 1 << 4,
    D_PVR_AUD_VID_MON = 1 << 5,
    D_PVR_STOP = 1 << 6
} D_AVPvrState;

/** @brief 视频编码类型*/
typedef enum
{
    D_VID_CODEC_MPEG = 0,
    D_VID_CODEC_MPEG2 = D_VID_CODEC_MPEG,
    D_VID_CODEC_AVS = 1,
    D_VID_CODEC_H264,
    D_VID_CODEC_MPEG4,
    D_VID_CODEC_VC1,
    D_VID_CODEC_MJPEG,
    /*********模拟电视制式**************/
    D_VID_CODEC_PAL,
    D_VID_CODEC_NTSC,
    D_VID_CODEC_SECAM,
    /***********结束************/
	D_VID_CODEC_MAX = 0xFF,
} D_VidCodecType;

/** @brief 音频编码类型*/
typedef enum
{
    D_AUD_CODEC_MPEG2 = 0,
    D_AUD_CODEC_AC3,
    D_AUD_CODEC_AAC,
    D_AUD_CODEC_DRA,    
    D_AUD_CODEC_DTS,
    D_AUD_CODEC_PCM,
    D_AUD_CODEC_ADPCM,
    D_AUD_CODEC_INTERPHONE,
	D_AUD_CODEC_MP3,
	D_AUD_CODEC_WMA,
	D_AUD_CODEC_AMR,
	D_AUD_CODEC_VORBIS,
    /*********模拟电视制式**************/
    D_AUD_CODEC_BG,
    D_AUD_CODEC_DK,
    D_AUD_CODEC_I,
    D_AUD_CODEC_M,
    /***********结束************/
    D_AUD_CODEC_FDK,
	D_AUD_CODEC_MAX = 0xFF,
} D_AudCodecType;

//CVBS 模块可以lock的视频制式
typedef enum 
{
    D_CVBS_UNLOCK = 0,
//50hz    
    D_CVBS_PAL,
    D_CVBS_Y_50,
//60hz
    D_CVBS_NTSC,
    D_CVBS_PAL_M,
    D_CVBS_NTSC_M,
    D_CVBS_Y_60,
    D_CVBS_NTSC_443,  
    D_CVBS_PAL_60,    
    D_CVBS_UNDEFINE
}D_CVBS_Input_Mode;


/** @brief 视频制式*/
typedef enum
{
    D_VID_FMT_AUTO = -1,    /**< 自动制式切换*/
    D_VID_FMT_PAL = 0,      /**< PAL制*/
    D_VID_FMT_NTSC,         /**< NTSC制*/
    D_VID_FMT_480I_60 = D_VID_FMT_NTSC,
    D_VID_FMT_480P_60 = 2,
    D_VID_FMT_576I_50 = D_VID_FMT_PAL,
    D_VID_FMT_576P_50 = 3,
    D_VID_FMT_720P_50,
    D_VID_FMT_720P_60,
    D_VID_FMT_1080I_50,
    D_VID_FMT_1080I_60,
    D_VID_FMT_1080P_50,
    D_VID_FMT_1080P_60,
    D_VID_FMT_768P_50,
    D_VID_FMT_768P_60,
    D_VID_FMT_1440_900,
    D_VID_FMT_1024_600,
	D_VID_FMT_1280_800,
	D_VID_FMT_1280_1024,
	D_VID_FMT_1080I_AUTO,
	D_VID_FMT_720P_AUTO,
	D_VID_FMT_1080P_AUTO,
	D_VID_FMT_1080P_50_TV_AUTO,//只能PAL中匹配,依据我们所支持的分辨率从大到小依次检索电视所支持的最大分辨率，依次确定输出
	D_VID_FMT_1080P_60_TV_AUTO,//只能在NTSC中匹配,依据我们所支持的分辨率从大到小依次检索电视所支持的最大分辨率，依次确定输出
	D_VID_FMT_TV_AUTO,//保分辨率，无论n/p,依据我们所支持的分辨率从大到小依次检索电视所支持的最大分辨率，依次确定输出
} D_VidFormat;

/** @brief 视频输入制式*/
typedef enum
{
    D_VID_INPUT_480I,  //30HZ              //720*480        (858*525)
    D_VID_INPUT_480I_1440,//30HZ  
    D_VID_INPUT_576I,    //25HZ              //720*576        (864*625)
    D_VID_INPUT_576I_1440,//25HZ  
    D_VID_INPUT_480P,    //60HZ              //720*480        (858*525)
    D_VID_INPUT_480P_1440, //60HZ      //1440*480       (1728*525)
    D_VID_INPUT_576P,    //50HZ              //720*576        (864*625)
    D_VID_INPUT_576P_1440,//50HZ            //1440*576   (1728*625)
    D_VID_INPUT_720P_50, //50HZ              //1280*720       (1980*750)
    D_VID_INPUT_720P_60,  //60HZ             //1280*720       (1650*750)
    D_VID_INPUT_1080I_25, //25HZ             //1920*1088      (2640*1125)
    D_VID_INPUT_1080I_30, //30HZ             //1920*1088      (2200*1125)
    D_VID_INPUT_1080P_24,//25HZ  
    D_VID_INPUT_1080P_25,//25HZ  
    D_VID_INPUT_1080P_30,//30HZ  
    D_VID_INPUT_1080P_50,//50HZ              //1920*1088      (2640*1125)
    D_VID_INPUT_1080P_60, //60HZ             //1920*1088      (2200*1125)

	//HDMI VESA
	
	D_VID_INPUT_640_480_60,			//640*480		(800*525)
	D_VID_INPUT_800_600_56,			//800*600		(1024*625) 
	D_VID_INPUT_800_600_60,			//800*600		(1056*628)
	
	D_VID_INPUT_848_480_60,			//848*480	(1088*517)
    
    D_VID_INPUT_1024_768_60,			//1024*768	(1344*806)
    
	D_VID_INPUT_1280_768_60_RB,		//1280*768	(1440*790)
	D_VID_INPUT_1280_768_60,			//1280*768	(1664*798)
	
	D_VID_INPUT_1280_960_60,			//1280*960	(1800*1000)
	
	D_VID_INPUT_1280_1024_60,			//1280*1024	(1688*1066)
	
    D_VID_INPUT_1360_768_60,			//1360*768	(1792*795)
    D_VID_INPUT_1366_768_60,			//1366*768	(1792*798)
    
	D_VID_INPUT_1400_1050_60_RB,		//1400*1050	(1560*1080)
	D_VID_INPUT_1400_1050_60, 		//1400*1050 (1864*1089)

	D_VID_INPUT_1440_900_60_RB,		//1440*900	(1600*926)
	D_VID_INPUT_1440_900_60, 			//1440*900 (1904*934)

	D_VID_INPUT_1600_1200_60,			//1600*1200	(2160*1250)
	
	D_VID_INPUT_1680_1050_60_RB, 		//1680*1050 (1840*1080)
 	D_VID_INPUT_1680_1050_60, 		//1680*1050 (2240*1089) 


	D_VID_INPUT_DVI_MIN,			//无实际用处，区分DVI
	
    D_VID_INPUT_VESA_720_480_I,                //720*480        (858*525)
    D_VID_INPUT_VESA_1440_480_I,
    D_VID_INPUT_VESA_720_576_I,                //720*576        (864*625)
    D_VID_INPUT_VESA_1440_576_I,

    D_VID_INPUT_VESA_720_480_60_P,
    D_VID_INPUT_VESA_720_576_50_P,
    D_VID_INPUT_VESA_1440_480_60_P,
    D_VID_INPUT_VESA_1440_576_50_P,
    D_VID_INPUT_VESA_1280_720_50_P,
    D_VID_INPUT_VESA_1280_720_60_P,
	
	//VESA DVI mode
	D_VID_INPUT_VESA_640_480_60,			//640*480		(800*525)
	D_VID_INPUT_VESA_800_600_56,			//800*600		(1024*625) 
	D_VID_INPUT_VESA_800_600_60,			//800*600		(1056*628)
	D_VID_INPUT_VESA_848_480_60,		//848*480	(1088*517)
	D_VID_INPUT_VESA_1024_768_60, 		//1024*768	(1344*806)
	D_VID_INPUT_VESA_1280_768_60_RB,		//1280*768	(1440*790)
	D_VID_INPUT_VESA_1280_768_60, 		//1280*768	(1664*798)
	D_VID_INPUT_VESA_1280_960_60, 		//1280*960	(1800*1000)
	D_VID_INPUT_VESA_1280_1024_60,			//1280*1024 (1688*1066)
	D_VID_INPUT_VESA_1360_768_60, 		//1360*768	(1792*795)
	D_VID_INPUT_VESA_1366_768_60, 		//1366*768	(1792*798)
	D_VID_INPUT_VESA_1400_1050_60_RB, 	//1400*1050 (1560*1080)
	D_VID_INPUT_VESA_1400_1050_60,		//1400*1050 (1864*1089)
	
	D_VID_INPUT_VESA_1440_900_60_RB,		//1400*900	(1600*926)
	D_VID_INPUT_VESA_1440_900_60, 			//1400*900 (1904*934)
	
	D_VID_INPUT_VESA_1600_1200_60,			//1600*1200 (2160*1250)
	
	D_VID_INPUT_VESA_1680_1050_60_RB, 		//1680*1050 (1840*1080)
	D_VID_INPUT_VESA_1680_1050_60,		//1680*1050 (2240*1089) 
	D_VID_INPUT_VESA_1080P_60,		   //1920*1088		(2200*1125)
    D_VID_INPUT_UNDEFINE,//不支持的格式

    D_VID_INPUT_ENCODE_MAX
} D_VidInputFormat;
typedef enum
{
    D_VID_FRM_RAT_FORBIDDEN,
    D_VID_FRM_RATE_COMPONENT,
    D_VID_FRM_RAT_23_97,
    D_VID_FRM_RAT_24,
    D_VID_FRM_RAT_25,
    D_VID_FRM_RAT_29_97,
    D_VID_FRM_RAT_30,
    D_VID_FRM_RAT_50,
    D_VID_FRM_RAT_59_94,
    D_VID_FRM_RAT_60,
    D_VID_FRM_RAT_RESERVED
} D_VidFrameRate;

/** @brief 视频消息类型*/
typedef enum
{
    D_Tv_Mes,
    D_Pvr_Mes,
    D_Logo_Mes,
} D_VidMesType;

/** @brief 音视频回调反馈信息参数 */
typedef struct
{
    D_VidFormat VidFormat; /**< 当前输出制式*/
    D_VidInputFormat VidInputFormat; /**< 当前输入节目源制式*/
    D_U16 Vid_Width; /**< 视频源宽*/
    D_U16 Vid_Height; /**< 视频源高*/
    D_VidMesType Mes_type;/**< 视频消息类型*/
} D_VidInfo;

/** @brief 视频输出类型*/
typedef enum
{
    D_VID_OUTPUT_AV1    = 0x00000001,
    D_VID_OUTPUT_AV2    = 0x00000002,
    D_VID_OUTPUT_YPBPR  = 0x00000004,
    D_VID_OUTPUT_HDMI   = 0x00000008,
    D_VID_OUTPUT_VGA    = 0x00000010,
	D_VID_OUTPUT_LCD	= 0x00000020,
} D_VidOutputType;

/** @brief 视频输入类型*/
typedef enum
{
    D_VID_IUTPUT_TV,
    D_VID_IUTPUT_DTV,
    D_VID_IUTPUT_AV1,
    D_VID_IUTPUT_AV2,
    D_VID_IUTPUT_S,
    D_VID_IUTPUT_YPBPR,
    D_VID_IUTPUT_VGA,
    D_VID_IUTPUT_HDMI1,
    D_VID_IUTPUT_HDMI2,
    D_VID_IUTPUT_HDMI3,
    D_VID_IUTPUT_USB1,
    D_VID_IUTPUT_USB2,
    D_VID_IUTPUT_USB3,
    D_VID_IUTPUT_DVI1,
    D_VID_IUTPUT_DVI2,
    D_VID_IUTPUT_DVI3,    
    D_VID_IUTPUT_TEST,//老化模式
    D_VID_IUTPUT_WIFIDISPLAY,

#ifdef D_TV_LIULINK_SOURCE
    D_VID_IUTPUT_LIULINK,
#endif
#ifdef D_TV_SUPPORT_IPTV
    D_VID_IUTPUT_IPTV,
#endif
	D_VID_IUTPUT_MAX,
} D_VidInputType;

/**音频码流信息*/
typedef enum
{
	D_AUD_SAMPLE_RATE = 0,
	D_AUD_CHANNELS	= 1
}D_Audio_Steam_Info; 

typedef enum
{
    D_AUD_DRA_NORMAL_CHN = 0,
    D_AUD_DRA_LFE_CHN	= 1
} D_Audio_Dra_Chn_Info; 	//dra 声道数信息

typedef enum
{
    D_VID_BackGround_BLack,
    D_VID_BackGround_Blue,
    D_VID_BackGround_White,
    D_VID_BackGround_Red,
    D_VID_BackGround_Green,
} D_VidBackGroundColor_t;

/** @brief 声道设置*/
typedef enum
{
    D_AUD_STEREO,           /**< 立体声*/
    D_AUD_LEFT,             /**< 左声道*/
    D_AUD_RIGHT,            /**< 右声道*/
    D_AUD_MONO,             /**< 单声道混音*/
    D_AUD_INVERTED_STEREO, /**<反向 立体声*/
    D_AUD_ONLY_LEFT, /**<只有 左声道 右声道静音*/
    D_AUD_ONLY_RIGHT, /**<只有 右声道 左声道静音*/
    D_AUD_QUIET_TRACK  /**声道静音*/
} D_AudTrack;

/** @brief 视频输出*/
typedef D_VidOutputType D_VidOutput;
/** @brief 视频输入*/
typedef D_VidInputType  D_VidInput;

/** @brief 音频设备设备初始化涉及IO结构 */
typedef struct
{
    D_GPIO_PortBit audio_mute;//用于控制音频的运放是否工作
    D_GPIO_PortBit audio_broadcast_mute;//用于控制应急广播是否工作
    D_U8 audio_spdif_en;//是否支持spdif
    D_U8 dac_mode;
//-------2830、2610d上用到--------
    D_U8 lvds_map;//输出模式
//LVDS
    D_GPIO_PortBit lvds_clock;
    D_GPIO_PortBit lvds_bl_on;
    D_GPIO_PortBit lvds_panel_on;
//HDMI
    D_GPIO_PortBit hdmi_0_hpd;
    D_GPIO_PortBit hdmi_0_5v_on;
    D_GPIO_PortBit hdmi_1_hpd;
    D_GPIO_PortBit hdmi_1_5v_on;
    D_GPIO_PortBit hdmi_1_sda;
    D_GPIO_PortBit hdmi_1_scl;
    D_GPIO_PortBit hdmi_sda;
    D_GPIO_PortBit hdmi_scl;
    D_GPIO_PortBit hdmi_5v_on;
//---------------
} D_AVOpenParam;
typedef struct 
{
    D_U16 lvds_h_total;
    D_U16 lvds_v_total;
    
    D_U16 lvds_h_active_width;
    D_U16 lvds_h_sync_width;
    D_U16 lvds_h_active_start;    
    D_U16 lvds_h_active_end;

    D_U16 lvds_v_active_height;    
    D_U16 lvds_v_sync_width;
    D_U16 lvds_v_active_start;    
    D_U16 lvds_v_active_end;

    D_U8 lvds_channel_mode;
    D_U8 lvds_exchange_mode;
    D_U8 lvds_foramt;
    D_U8 lvds_div;
	D_U8  lvds_sync_mode;
	D_U8 lvds_l_p_n_sel;
	D_U8 lvds_r_p_n_sel;

//IO set
    D_U8 lvds_da_tx_pds;
    D_U8 lvds_clk_tx_pds;

//clk para
    D_U16 pll_freq;//lvds_clk = pll_freq/vp_div
    D_U8 vp_div;
    D_U8 lvds_x;
 
}D_LvdsInitParam;


typedef struct  
{
	D_U8 val_0;
	D_U8 val_1;
	D_U8 val_2;
	D_U8 val_3;
	D_U8 val_4;
	D_U8 val_5;
	D_U8 val_6;
	D_U8 val_7;
	D_U8 val_8;
	D_U8 val_9;
	D_U8 val_10;
}D_TCON_CTR_GPO;

typedef struct  
{
	D_U8 val_0;
	D_U8 val_1;
	D_U8 val_2;
	D_U8 val_3;
	D_U8 val_4;
	D_U8 val_5;
	D_U8 val_6;
	D_U8 val_7;
	D_U8 val_8;
} D_TCON_GPO_INITIAL;

typedef struct  
{
	D_U16 h_cnt_s;
	D_U16 h_cnt_e;
	D_U16 h_cnt_s1;
	D_U16 h_cnt_e1;
	D_U16 v_cnt_s;
	D_U16 v_cnt_e;
} D_TCON_GPO_PARAM;

typedef struct  
{
	D_TCON_CTR_GPO ctr_gpo;
	D_TCON_GPO_INITIAL gpo_initial;
	D_TCON_GPO_PARAM gpo0_cnt;
	D_TCON_GPO_PARAM gpo1_cnt;
	D_TCON_GPO_PARAM gpo2_cnt;
	D_TCON_GPO_PARAM gpo3_cnt;
	D_TCON_GPO_PARAM gpo4_cnt;
	D_TCON_GPO_PARAM gpo5_cnt;
	D_TCON_GPO_PARAM gpo6_cnt;
	D_TCON_GPO_PARAM gpo7_cnt;
	D_TCON_GPO_PARAM gpo8_cnt;
	D_U16 tri1_cnt;
	D_U16 tri2_cnt;
	D_U16 tri3_cnt;
	D_U16 tri4_cnt;
	
    D_U8 mini_mode;//MINI_MODE;// 				 <= 2'd3; 
    D_U8 ser_mode;//SER_MODE;//					 <= 2'd2;
    D_U8 reset_pos;//reset_pos;//					 <= 1'd1;// 	  
    D_U8 diff_pos;//DIFF_POS;//					 <= 3'd7;// 1560*806*60 =75.4			  
    D_U16 fifo_hs_start;//FIFO_HS_start;//					 <= 'd10 ;
    D_U16 h_active_start;//					<= 11'd950; //11'd450;
    D_U16 h_read_cnt;//H_READ_CNT;//						<=12'd958 ;
    D_U16 r_clr_cnt;//R_CLR_CNT;//						<=12'd860 ;
    D_U16 clk_v_cnt;//CLK_V_CNT;//					   <=12'd14 ;
    D_U16 vclk_h_cnt;//CLK_H_CNT;//						<=12'd550 ;
    D_U16 clk_mode;//CLK_MOD;//						  <=12'b100100100100 ;
    D_U16 pol_cnt;//POL_CNT;// 						<=12'd160 ;
    D_U8 sgate;//SGATE;// 						 <= 1'b0 ;
    D_U8 ram12_l;//RAM12_L;//						  <= 8'd30;
    D_U8 new_de1_s;//NEW_DE1_S;//					  <= 8'd58;
    D_U16 hstart;	  
    D_U16 h_end;//						  <= 13'd49;//13'd7409 ;//13'd3401 ;//13'd49 ;		  
    D_U16 h_start1;//						 <= 13'd2087;//13'd7360 ;//13'd40;		  
    D_U16 h_end1;// 						 <= 13'd2097;//13'd7409 ;//13'd3401 ;//13'd49 ; 	  
    D_U16 h_start2;//						 <= 13'd4127;//13'd7360 ;//13'd40;		  
    D_U16 h_end2;// 						 <= 13'd4137;//13'd7409 ;//13'd3401 ;//13'd49 ;
    D_U16 vdd_v_cnt;//						   <= 11'd1124 ;
    D_U16 vdd_h_cnt;//						   <= 11'd1100 ;
    D_U8 vdd_cnt_fram;//					  <= 8'd179 ;
    D_U16 cpv2_h;//						 <= 'd16;
    D_U16 cpv2_h1;//						 <= 'd16;
    D_U16 cpv2_h2;//						 <= 'd16;
    D_U8 n_clk;//N_CLK;// 						 <= 1'b1  ;
    D_U8 n_clk1;//						  <= 1'b0	;
    D_U8 mode;//							 <='b1 ;
    D_U8 dual_mode;// 					 <=2'b10 ; //	00: N40 N10 	01:N81		10:N56
    D_U8 trigate;//华星屏幕
    D_U8 split_en;// 

} D_TCON_INIT_PARAM;

typedef struct
{
       D_U8  ycs_mode; 	// R_YC_SEP_TECH: 0 - BPF; 1 - Comb; 2 - NTSC443 mode
	D_U8  vs_th1_msb; 	// ck48m_vsync_thr MSB8
	D_U8  vs_th1_lsb; 	// ck48m_vsync_thr LSB8
	D_U8  vs_th2_msb; 	// ck4fs_vsync_cnt_thr MSB4
	D_U8  vs_th2_lsb; 	// ck4fs_vsync_cnt_thr LSB8
       D_U16 slice1_off; 	// ck48m_slicLevel: -1024~1023 s11b
	D_U16 slice2_off; 	// ck4fs_slice_level: -1024~1023 s11b
	D_U8  vo_md_th_gn;	// R_DI_MC_THD_GAIN: 8b
} D_Atv_Nonstd_Param; // Params for Non-standard signals in CVBS decoder


typedef struct 
{
    D_U16 v_max_50 ;
    D_U16 v_min_60;
    D_U16 screenwidth;
    D_U16 screenheight;
    D_U32 out_freq_50;
    D_U32 out_freq_60;
    D_U16 total_pix_per_line_50 ;
    D_U16 total_line_50 ;
    D_U16 total_pix_per_line_60 ;
    D_U16 total_line_60 ;
	D_U16 display_invert;//= 0 不翻转// = 1横向翻转  //= 2 纵向翻转   //= 3 横向 纵向都翻转 
    D_U8 vsync_lastde_delay_50;
    D_U8 vsync_lastde_delay_60;

    D_U8 speed_adj_line;
}D_TvenLvdsParam;

typedef struct 
{
    D_U16 VCOM_DE_start_pix;
    D_U16 VCOM_DE_start_line;
    D_U16 VCOM_DE_end_line;    

    D_U16 SP_StartPix;
    D_U16 SP_StartLine;
    D_U16 VCOM_StartPix;
    D_U16 VCOM_StartLine;
    
    D_U16 VO_feeder_vsync_line;
    D_U16 VO_hs_vsync_pix;
    D_U16 VO_hs_vsync_line;
    D_U16 VO_set_pix_to_VeBypass;
    D_U16 VO_set_pix_to_VeEnable;

    D_U16 OSD_set_pix_to;
    D_U16 OSD_set_line_to_top;
	D_U16 AV_Pal_x;
	D_U16 AV_Pal_y;
	D_U16 AV_NTSC_x;
	D_U16 AV_NTSC_y;	
}D_DisplayParam;



/** @brief 音视频同步类型 */
typedef enum
{
    D_AV_SYNC_AUTO = 0,/**< 自动调整 */
    D_AV_SYNC_PCR = 1, /**< PCR同步*/
    D_AV_SYNC_APTS = 2, /**< APTS同步*/
    D_AV_SYNC_NONE = 3,/**< 不做同步调整*/
    D_AV_SYNC_VPTS = 4, /**< VPTS同步*/
} D_AVSyncType;

/** @brief 音视频同步参数 */
typedef struct
{
    D_AVSyncType type; /**< 同步类型*/
    D_U32 min_threshold; /**< 最小调整阀值*/
    D_U32 max_threshold; /**< 最大调整阀值*/
} D_AVSyncParam;

/** @brief 音视频播放参数*/
typedef union
{
    D_AVPlayMode    mode;   /**< 播放方式*/
    struct
    {
        D_AVPlayMode    mode;   /**< 播放方式*/
        D_U16       pcr_pid;/**< PCR PID*/
        D_U16       vid_pid;/**< 视频PID*/
        D_VidCodecType vid_codec;/**< 视频编码类型*/
        D_U16       aud_pid;/**< 音频PID*/
        D_AudCodecType aud_codec;/**< 音频编码类型*/
        D_AVSyncParam sync; /**< 音视频同步参数*/
        D_AVSourceMode source_mode; /**< 音视频参数来源*/
        D_U8          I_Frame_Int_Flag;/**< I帧中断计数使能*/
    } tv;                           /**< 电视播放参数*/
    struct
    {
        D_AVPlayMode    mode;   /**< 播放方式*/
        D_U16       pcr_pid;/**< PCR PID*/
        D_U16       aud_pid;/**< 音频PID*/
        D_AudCodecType aud_codec;/**< 音频编码类型*/
        D_AVSyncParam sync; /**< 音视频同步参数*/
        D_AVSourceMode source_mode; /**< 音视频参数来源*/
    } radio;                    /**< 广播播放参数*/
} D_AVPlayParam;

/** @brief 视频参数 added by shanzs@06/08/02*/
typedef struct
{
    D_U8        brightness; /* 亮度 */
    D_U8        chroma;         /* 色度 */
    D_U8        contrast;       /* 对比度 */
} D_VidPicParam;

/** @brief 视频宽高比例常量 added by shanzs@06/08/02*/
typedef enum
{
    D_VidRatio_TYPE_4_3_LB,
    D_VidRatio_TYPE_16_9_LB,
    D_VidRatio_TYPE_4_3_PS,
    D_VidRatio_TYPE_16_9_PS,
    D_VidRatio_TYPE_Auto
} D_VidRatioType;

/** @brief tv比例模式*/
typedef enum
{
    D_Full_Screen,//满屏
    D_4_to_3,//3//4:3
    D_ZOOM_1X,//放大1
    D_ZOOM_2X, //放大2
    D_Movie,//电影
    D_Overall_Screen,//全真
    D_Overall_Horizon,//全景
    D_NATURAL_RATIO,//输出按照视频源本身比例，在全屏情况下居中，也就是居中的同时左右各自砍掉2%
    D_NATURAL_RATIO_OVERALL_SCREEN,//在全真情况下居中.居中时候一点也不砍掉内容
    D_16TO9_LB,
    D_4TO3_LB,
} D_tv_Display_Ratio_t;

/** @brief 视频DAC选择 @13/09/14*/
typedef enum
{
    POWER_DOWN_B  = 1,
    POWER_DOWN_G  = (1 << 1),
    POWER_DOWN_R  = (1 << 2),
} VDAC_POWER_DOWN;
typedef enum
{
    BackGround_BLack,
    BackGround_Blue,
    BackGround_White,
    BackGround_Red,
    BackGround_Green,
    BackGround_AUTO,
} BackGroundColor_t;

typedef enum
{
    D_VL_DATA_MODE_YUV444 = 0, /**< 平面444 */
    D_VL_DATA_MODE_YUV411,  /**< 平面411 */
    D_VL_DATA_MODE_MB,  /**< 宏像素打包411 */
} D_VL_DataMode;

typedef enum
{
    D_VL_FRAME_SWITCH_TOP_FIELD = 0,
    D_VL_FRAME_SWITCH_BOTTOM_FIELD,
    D_VL_FRAME_SWITCH_BOTH_FIELD,
} D_VL_FrameSwitchMode;

typedef struct
{
    D_U16 out_x, out_y, out_w, out_h;       // out pos on screen
    D_U8 out_mode;                          // out mode: 0--full | 1--4:3 | 2--16:9 | other
    void *img_buffer;
    D_U16 img_w, img_h;
    D_VL_DataMode data_mode;
    D_VL_FrameSwitchMode frame_switch_mode;
} D_VideoLayerParam;

typedef enum
{
    D_Layer_Video = 0,
    D_Layer_SimpleShow,
    D_Layer_Osd,
} D_LayerType;

typedef enum
{
    D_Black_Screen,
    D_Force_Screen,
}D_Switch_Mode;

typedef enum
{
    D_PEQ = 0,
    D_Digital_Audio = 1,
} D_Audio;

typedef enum
{
    D_Surround_open ,
    D_Surround_close ,
} D_AudioSrs;

typedef struct
{
    D_Double freq;  // 频率，单位Hz
    D_Double bw;        // 带宽，单位Hz
    D_Double gain;  // 增益，单位dB
} D_AdjPointOfPeq;

typedef struct
{
    D_AdjPointOfPeq *peq;  
    D_AdjPointOfPeq *eq;        
    D_U8 peq_en;
    D_U8 eq_en;
    D_U32 nfft;
    D_U8 section_num;
} D_Peq_eq_param;

typedef struct
{
    D_U8               base_level;//本组基础level 0-40
    D_S32              base_avc;//本组基础level对应的基础dac值
    D_U8               level_step;//level_offset的单位
    D_S8               now_level_offset;//当前本组level对应基础level的偏移=(now_level-base_level)*level_step
    D_S32              now_close_avc;//本组当前level对应的close dac值
    D_S32              now_open_avc;//本组当前level对应的open dac值
} D_Avc_Param;


typedef struct
{
	D_U8 pic_en ;
	D_U32 pic_size;
	D_U32 pic_size_media;
	D_U8 work_en ;
	D_U32 work_size;
	D_U32 work_size_media;
	D_U8 switch_en;
	D_U32 switch_size;
	D_U8 pa_od_en;
	D_U32 pa_od_size;	
}D_VideoMemParam;

typedef struct
{
    D_Bool project_ctrl;
	D_U8   cur_avc_dac;
    D_S8   now_level_offset;//当前本组level对应基础level的偏移=(now_level-base_level)*level_step
    D_S32  now_close_avc;//本组当前level对应的close dac值
    D_S32  now_open_avc;//本组当前level对应的open dac值
}D_audiodacctlNotifyInfo;


typedef struct
{
    D_U8 param1;  
    D_U8 param2;   
    D_U8 param3; 
} D_hdmi_param;

/** @brief 视频宽高比例 added by shanzs@06/08/02*/
typedef D_VidRatioType D_VidPicRatio;

/** @brief 音视频系统初始化
*
*   在调用音视频操作函数时首先调用此函数
* @retval D_OK  初始化成功
* @retval D_ERR 初始化失败
*/
D_Result    d_av_open (D_AVOpenParam *param) D_FUNCPOSTFIT;

/** @brief 音视频系统中止
*
* 程序结束时，释放音视频系统内的资源
* @retval D_OK  操作成功
* @retval D_ERR 操作失败
*/
D_Result    d_av_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个音视频设备
* @param attr   音视频设备属性结构指针，为NULL时使用缺省值
* @param handle 回调时返回的参数句柄
* @return 成功时返回音视频设备句柄，失败返回D_INVALID_HANDLE
*/
D_HAV           d_av_create (D_AVAttr *attr, D_Handle handle) D_FUNCPOSTFIT;

/** @brief 销毁一个音视频设备
* @param hav    音视频设备句柄
* @retval D_OK  释放成功
* @retval   D_ERR_INVALID_HANDLE    句柄无效
*/
D_Result    d_av_destroy (D_HAV hav) D_FUNCPOSTFIT;

/** @brief 切换伴音
* @param hav    音视频设备句柄
* @param param  音视频播放参数
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
* @retval D_ERR_FAULT   设备出错
* @retval D_ERR_INVALID_ARGUMENT    参数无效
* @retval D_ERR_NOT_SUPPORT 此功能不支持
*/
D_Result
d_av_change_audio (D_HAV hav, D_AVPlayParam *param) D_FUNCPOSTFIT;

/**获取 当前音频是否支持播放,运行过d_av_play之后调用**/
D_U8 d_av_get_audio_support_flag(void);

/** @brief 开始音视频播放
* @param hav    音视频设备句柄
* @param param  音视频播放参数
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
* @retval D_ERR_FAULT   设备出错
* @retval D_ERR_INVALID_ARGUMENT    参数无效
* @retval D_ERR_NOT_SUPPORT 此功能不支持
*/
D_Result    d_av_play (D_HAV hav, D_AVPlayParam *param) D_FUNCPOSTFIT;

/** @brief 原参数重新播放音视频
* @param hav    音视频设备句柄
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
*/
D_Result d_av_restart_play (D_HAV hav)D_FUNCPOSTFIT;

/** @brief 停止音视频播放
* @param hav    音视频设备句柄
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
* @retval D_ERR_FAULT   设备出错
*/
D_Result    d_av_stop (D_HAV hav) D_FUNCPOSTFIT;

/** @brief 开始搜索过程中的音视频播放
* @param hav    音视频设备句柄
* @param param  音视频播放参数
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
* @retval D_ERR_FAULT   设备出错
* @retval D_ERR_INVALID_ARGUMENT    参数无效
* @retval D_ERR_NOT_SUPPORT 此功能不支持
*/
D_Result
d_av_play_while_searching(D_HAV hav, D_AVPlayParam *param);

/** @brief 停止搜索过程中的音视频播放
* @param hav    音视频设备句柄
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
* @retval D_ERR_FAULT   设备出错
*/
D_Result
d_av_stop_while_searching(D_HAV hav);

/** @brief atv搜索的过程中检查cvbs锁定状态
* @param hav    音视频设备句柄
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
* @retval D_ERR_FAULT   设备出错
*/
D_U8  d_av_getcvbslock_while_searching(D_HAV hav);

/** @brief 设置视频制式
* @param hav    音视频设备句柄
* @param fmt    视频制式
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE      设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT    参数无效
* @retval D_ERR_NOT_SUPPORT 功能现在不支持
*/
D_Result    d_av_set_vid_format (D_HAV hav, D_VidFormat fmt) D_FUNCPOSTFIT;

/** @brief 设置视频输出
* @param hav    音视频设备句柄
* @param out    视频输出
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE      设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT    参数无效
* @retval D_ERR_NOT_SUPPORT 功能现在不支持
*/
D_Result    d_av_set_vid_output (D_HAV hav, D_VidOutput out) D_FUNCPOSTFIT;

/** @brief获取当前制式
* @retval PAL   pal
* @retval NTSC  NTSC
*/
D_Current_Pal_Ntsc_Mode d_av_get_pal_ntsc_mode(void)D_FUNCPOSTFIT;

/** @brief获取当前视频比例
* @retval v_4_3_TO_16_9_LB
* @retval v_4_3_TO_16_9_PS
* @retval v_16_9_TO_4_3_LB
* @retval v_16_9_TO_4_3_PS
* @retval v_DEFAULT_DISPLAY
*/
D_Current_display_ratio_Mode d_av_get_current_display_mode(void)D_FUNCPOSTFIT;
/** @brief 视频显示黑屏
* @param hav    音视频设备句柄
* @param blank  D_TRUE时显示黑屏，D_FALSE时显示视频
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
* @retval D_ERR_FAULT   设备出错
*/
D_Result    d_av_set_vid_blank (D_HAV hav, D_Bool blank) D_FUNCPOSTFIT;

/** @brief 改变视频显示窗口的大小
* @param hav        音视频设备句柄
* @param x      显示窗口左上角x坐标
* @param y      显示窗口右上角y坐标
* @param width  显示窗口宽度
* @param height 先是窗口高度
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
* @retval D_ERR_NOT_SUPPORT 此功能目前不支持
* @retval D_ERR_INVALID_ARGUMENT    设置窗口大小超出范围
*/
D_Result    d_av_set_vid_window(D_HAV hav, D_Coord x, D_Coord y, D_Coord width, D_Coord height) D_FUNCPOSTFIT;

/** @brief 设置声道
* @param hav        音视频设备句柄
* @param track  声道
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE      设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT    参数无效
*/
D_Result    d_av_set_aud_track (D_HAV hav, D_AudTrack track) D_FUNCPOSTFIT;

/** @brief 静音/恢复声音输出
* @param hav        音视频设备句柄
* @param mute       D_TRUE静音，D_FALSE声音输出
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
*/
D_Result    d_av_set_aud_mute (D_HAV hav, D_Bool mute) D_FUNCPOSTFIT;

/** @brief 静音/恢复耳机声音输出
* @param hav        音视频设备句柄
* @param mute       D_TRUE静音，D_FALSE声音输出
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
*/
D_Result    d_av_set_earphone_mute (D_HAV hav, D_Bool mute) D_FUNCPOSTFIT;
/** @brief 当应用调用mute时候,开关运放是否优先考虑用户需求
 * @param mute_IO_ctrl_right   1:不以dsp状态或者当前音量状态为准，优先考虑应用需求 0:与1反义
 * @retval D_OK  操作成功
 */
D_Result d_av_mute_io_ctrl_right(D_HAV hav,D_U8 mute_io_right)D_FUNCPOSTFIT ;
/** @brief 静音/恢复喇叭声音输出
* @param hav        音视频设备句柄
* @param mute       D_TRUE静音，D_FALSE声音输出
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
*/
D_Result d_av_set_loudspeaker_mute (D_HAV hav, D_Bool mute)D_FUNCPOSTFIT;
/** @brief 设置输出音量
*
*   0 最小，100最大
* @param hav        音视频设备句柄
* @param vol        输出音量(0~100)
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE      设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT    音量不在0~100范围内
*/
D_Result    d_av_set_volume (D_HAV hav, D_U8 vol) D_FUNCPOSTFIT;

/** @brief 获取最大输出音量
*
* @retval 	最大输出音量
*/
D_U8	d_av_get_max_volume (void) D_FUNCPOSTFIT;

/** @brief 设置音视频播放事件毁掉函数
* @param callback   回调函数指针
* @param old 如果非NULL,返回旧的回调函数指针。
* @retval D_OK  操作成功
* @retval D_ERR 操作失败
*/
D_Result    d_av_register_callback (D_AVCallback callback, D_AVCallback *old) D_FUNCPOSTFIT;

/** @brief 开始音视频播放
* @param hav    音视频设备句柄
* @param param  音视频播放参数
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
* @retval D_ERR_FAULT   设备出错
* @retval D_ERR_INVALID_ARGUMENT    参数无效
* @retval D_ERR_NOT_SUPPORT 此功能不支持
*/
D_Result    d_av_display_pic_I(D_HAV hav, D_U8 *address, D_U32 Size) D_FUNCPOSTFIT;

/** @brief 取得音视频缓冲区
* @param vEvtCnt 视频事件计数
* @param aEvtCnt 音频事件计数
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_ARGUMENT    参数无效
*/

D_Result d_av_get_evt_cnt(D_U32 *vEvtCnt , D_U32 *aEvtCnt) D_FUNCPOSTFIT;

/** @brief 设置视频参数  added by shanzs@06/08/02
*/
D_Result d_av_set_pic_param (D_HAV hav, D_VidPicParam *param) D_FUNCPOSTFIT;
/** @brief获取音频码流信息
*/
D_U32 d_av_get_aud_stream_info (D_Audio_Steam_Info audio_info_type) D_FUNCPOSTFIT;

/** @brief  获取DRA音频声道信息*/
D_U32 d_av_get_aud_dra_chn_info(D_Audio_Dra_Chn_Info chn_info_type)D_FUNCPOSTFIT;


/** @brief 设置视频宽高比例  added by shanzs@06/08/02
*/
D_Result d_av_set_pic_ratio (D_HAV hav, D_VidPicRatio ratio) D_FUNCPOSTFIT;

D_Result d_av_open_ex(void);
typedef void (*DAVGUICALLBACK)(D_U32 event);

/** @brief 设置NP制式变化时候回调函数
* @param parm   cb 回调函数
*/
void d_av_setguicb(DAVGUICALLBACK cb)D_FUNCPOSTFIT;
void d_av_setinputcb(DAVGUICALLBACK cb)D_FUNCPOSTFIT;
D_Result d_av_set_video_layer_param(D_HAV hav, D_VideoLayerParam *param) D_FUNCPOSTFIT;
D_Result d_av_display_frame(D_HAV hav, D_U32 id) D_FUNCPOSTFIT;
D_Result d_av_video_layer_enable(D_HAV hav, D_Bool enable) D_FUNCPOSTFIT;
D_Result d_av_set_layer_mixer(D_HAV hav, D_LayerType layers[]) D_FUNCPOSTFIT;

/** @brief 获取视频STC  
*/
D_Result d_av_get_vid_stc (D_U32 *stc) D_FUNCPOSTFIT;

/** @brief 停止同步监控
*/
D_Result d_av_stop_sync_monitor (void) D_FUNCPOSTFIT;

/** @brief 关闭音频dac
* @param state 开关0:关；1:开
* @retval D_OK	操作成功
*/
D_Result
d_av_set_Aud_dac_state(D_U8 state)D_FUNCPOSTFIT;

/** @brief 启动同步监控
*/
D_Result d_av_restart_sync_monitor (void) D_FUNCPOSTFIT;

/** @brief 获取视频STC
*/
D_Result d_av_get_vid_stc (D_U32 *stc) D_FUNCPOSTFIT;

/** @brief 视频dac开关
* @param parm   en  1:开dac 0:关dac
*/
D_Result d_av_vdac_ctrl(D_U8 en)D_FUNCPOSTFIT;
/** @brief 设置音频audio_factor
* @param audio_factor 音量参数
* @param BackGround 是否使用菜单传值开关
* @param input_type 输入源
*/
D_Result
d_av_audio_factor_set(D_HAV hav, D_U16 *audio_factor , D_U8 state, D_VidInputType input_type) D_FUNCPOSTFIT;

/** @brief 设置视频输入
* @param hav    音视频设备句柄
* @param input  视频输入
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE      设备句柄无效
* @retval D_ERR_INVALID_ARGUMENT    参数无效
* @retval D_ERR_NOT_SUPPORT 功能现在不支持
*/
D_Result d_av_set_vid_input (D_HAV hav, D_VidInputType input) D_FUNCPOSTFIT;

/** @brief 设置输出音量平衡*/
D_Result  d_av_set_balance (D_HAV hav, D_S8 val) D_FUNCPOSTFIT;

/** @brief 音频PEQ*/
D_Result
d_av_Audio_PEQ(D_HAV hav, D_AdjPointOfPeq *Hr_adjpCnt , D_U8 PEQ_num, D_U32 Hr_n_fft, D_Audio Format) D_FUNCPOSTFIT;
//??????
/** @brief 音频PEQ eq*/
D_Result
d_av_Audio_PEQ_EQ(D_HAV hav, D_Peq_eq_param *peq_eq) D_FUNCPOSTFIT;
/** @brief 音频环绕*/
D_Result d_av_audio_srs(D_HAV hav, D_AudioSrs en) D_FUNCPOSTFIT;

/** @brief 智能音量内部的五级音量控制策略开关
* @param hav        音视频设备句柄
* @param en       D_TRUE开，D_FALSE关
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
*/
D_Result
d_av_avc_ctl(D_HAV hav, D_U8 en)D_FUNCPOSTFIT;

/** @brief 智能音量内部的五级音量控制策略检测时间
* @param hav        音视频设备句柄
* @param avc_detect_time       检测时间
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
*/
D_Result
d_av_avc_detect_time(D_HAV hav,D_U32 avc_detect_time)D_FUNCPOSTFIT;
/** @brief
* @param BackGround 背景颜色
*/
D_Result d_av_set_background(BackGroundColor_t BackGround)D_FUNCPOSTFIT;

/** @brief 设置tv比例模式
*/
D_Result d_av_set_tv_ratio_mode (D_HAV hav, D_tv_Display_Ratio_t ratio_mode) D_FUNCPOSTFIT;

/**@brief 音频跳跃，用于手动调节同步
* @param Skip_length: 跳跃长度  单位为样点, 相当于以(1/采样率)s为单位调整，应用可加粗调与细调
* @retval D_OK	操作成功
*/
D_Result 
d_av_skip_pcm(D_U32 Skip_length) D_FUNCPOSTFIT;

/** @brief 音频重播，用于手动调节同步
* @param replay_length: 重播长度 单位为样点 相当于以(1/采样率)s为单位调整，应用可加粗调与细调
* @retval D_OK	操作成功
*/
D_Result 
d_av_replay_pcm(D_U32 replay_length) D_FUNCPOSTFIT;

/** @brief peq开关控制
* @param hav        音视频设备句柄
* @param en       D_TRUE开，D_FALSE关
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
*/
D_Result
d_av_peq_ctrl(D_HAV hav, D_U8 en) D_FUNCPOSTFIT;

/** @brief 智能音量总开关
* @param hav        音视频设备句柄
* @param en       D_TRUE开，D_FALSE关
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
*/
D_Result
d_av_avc_ctl_whole_en(D_HAV hav, D_U8 en)D_FUNCPOSTFIT;
/** @brief 智能音量开相对于关的压缩等级
* @param hav     compress_coefficient，范围(-40db~0db)
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE  设备句柄无效
*/
D_Result
d_av_avc_set_intelligent_volume_compress_level(D_HAV hav,float compress_coefficient) D_FUNCPOSTFIT;
/** @brief控制音频打印开*/
void d_audio_print_open(void)D_FUNCPOSTFIT;

/** @brief控制音频打印关*/
void d_audio_print_close(void)D_FUNCPOSTFIT;

/** @briefcheck vblank raise edge _|
* @param nocard_ca_flag 1:是无卡ca ,0:不是无卡ca
*/
void d_audio_nocard_ca_flag_set(D_U8 ca_flag)D_FUNCPOSTFIT;

/** @brief 获取Dac_Ctrl_L*/
D_U32 d_av_get_dac_ctrl_l(void) D_FUNCPOSTFIT;
/** @brief 获取Dac_Ctrl_R*/
D_U32 d_av_get_dac_ctrl_r(void) D_FUNCPOSTFIT;
/** @brief 设置Dac_Ctrl_L*/
void d_av_set_avc_ctrl_l(D_U32 dac_l)D_FUNCPOSTFIT;
/** @brief 设置Dac_Ctrl_R*/
void d_av_set_avc_ctrl_r(D_U32 dac_r)D_FUNCPOSTFIT;

void d_av_set_avc_ctrl_ex(D_U32 dac_val)D_FUNCPOSTFIT;

/** @brief 获取音频avc level*/
D_U8 d_av_get_cur_vdac_ctrl(void)D_FUNCPOSTFIT;
/** @brief 切换换台是黑屏还是定帧模式*/
D_Result d_av_set_switch_mode(D_Switch_Mode video_switch_mode) D_FUNCPOSTFIT;
D_U8 d_av_video_wait_playreq(void) D_FUNCPOSTFIT;

/** @brief环绕声参数调节
* @param weight_coefficient:[50~100],srs_time [0~70]
*/
void  d_av_audio_srs_param_set(D_U32 srs_time ,D_U32 weight_coefficient)D_FUNCPOSTFIT;


void d_av_setunlockcb(DAVGUICALLBACK cb)D_FUNCPOSTFIT;

void  d_av_Status_while_searching(D_HAV hav,D_U8 mode)D_FUNCPOSTFIT;

/** @brief获取当前播放的节目宽高*/
D_Result d_av_get_cur_hw(D_U16* Width,D_U16* Height);


/** @brief 获取耳机当前状态*/
D_Result d_av_get_earphone_status (D_HAV hav);

/** @brief vo开关,不需要视频层显示的时候可以关闭VO，以降低功耗*/
D_Result d_av_vo_ctrl(D_U8 en)D_FUNCPOSTFIT;

/** @briefcheck vblank raise edge _|
* @param 
*/
D_Result d_av_hdmi_Status(D_U8 num)D_FUNCPOSTFIT;

/** @brief 显示参数初始化
*
* @retval D_OK  初始化成功
* @retval D_ERR 初始化失败
*/
D_Result d_av_display_para_init (D_DisplayParam* screenparam)D_FUNCPOSTFIT;

/** @brief控制音频spdif 开关*/
void d_av_spdif_en(D_U8 en )D_FUNCPOSTFIT;;

/** @brief控制音频spdif 音量*/
void d_av_spdif_volume(D_U32 vol )D_FUNCPOSTFIT;

/*打开或关闭DAC*/
void d_av_dac_set_pwm_on(D_U8 on_off);
	
/** @brief screen_Push开关*/
void d_av_screen_push_en(D_U8 en )D_FUNCPOSTFIT;

/** @brief frame_rate 需要在投屏模式下传对应的帧率，在非投屏模式下传D_VID_FRM_RAT_RESERVED，此时底层会以vpu解析出的为准*/
void d_av_set_video_frame_rate(D_VidFrameRate frame_rate)D_FUNCPOSTFIT;

/** @brief 视频解码容错配置
* @param    error_deal_mode视频容错处理方式:  0--播放所有帧; 1--不播放出错B帧；2--丢掉所有错误帧
* @retval D_OK	操作成功
*/
D_U8 d_av_error_deal_mode(D_U8 error_deal_mode)D_FUNCPOSTFIT;
 /** @brief降噪开关配置
* @param    noise_bypass_en降噪开关配置:  0--降噪开; 1--降噪关
* @retval D_OK	操作成功
*/
D_U8 d_av_noise_bypass_en(D_U8 noise_bypass)D_FUNCPOSTFIT;

/** @brief 内存配置接口
* @param 
*/
D_U8 d_av_mem_set(D_VideoMemParam *mem_info)D_FUNCPOSTFIT;

/** @brief mute io 静音与否对应的IO置高置低情况设置
* @param mute_io_flag 1:IO置高时候对应静音，0:IO置低时候对应静音
*/
void d_av_muteio_flag(D_U8 mute_io_flag)D_FUNCPOSTFIT;
D_U16 d_av_strategy_info(D_U16 tag,D_U8 param_size,void *payload)D_FUNCPOSTFIT;

/** @brief	可由CPU配置unref_frames的个数是3帧或4帧。
缩减内存时可使用unref_frames为3帧的方案，但对于高清60帧的片源解码速率会受到一定影响。
正常情况下可使用unref_frames为4帧的方案，给解码留出余量
 * @param unref_frames 1:4帧，0:3帧
*/
void d_av_unref_frames(D_U8 unref_frames)D_FUNCPOSTFIT;

  /** @brief翻转屏使能
* @param   invert 0:不翻转，1:翻转
* @retval D_OK	操作成功
*/
D_U8 d_av_display_invert(D_U8 invert)D_FUNCPOSTFIT;

/** @brief	 使能DAC BO输出的DRC功能
* @param	 en: 1--使能DRC功能，0--关闭DRC功能
* @retval D_OK	  操作成功
*/
D_U8 d_av_audio_bo_drc_enable(D_U8 bo_drc_enable)D_FUNCPOSTFIT;


/** @brief	配置DAC BO输出的DRC参数
* @param   threshold: DRC的阈值，取值范围：0x0-0x1f
				  compress：超过阈值的部分要进行压缩的系数，取值范围：0x0-0x5
*/
D_U8 d_av_audio_bo_drc_set(D_U8 threshold,D_U8 compressibility)D_FUNCPOSTFIT;

/** @brief avc 基础值配置
* @param num:HI_ATV 0;HI_DTV 1;HI_CVBS 2;HI_YCBCR 3;HI_HDMI 4;HI_USB 5
* @param avc_base_param
*/
D_Result
d_av_audio_avc_base_set(D_Avc_Param  avc_base_param,D_U8 num)D_FUNCPOSTFIT;


/** @brief lvds 初始化
*
* @retval D_OK  初始化成功
* @retval D_ERR 初始化失败
*/
D_Result
d_av_lvds_init (D_U8 lvds_type,D_LvdsInitParam *lvds_para)D_FUNCPOSTFIT;

/** @brief tven由lvds决定的参数 初始化
*
* @retval D_OK  初始化成功
* @retval D_ERR 初始化失败
*/
D_Result d_av_tven_lvds_para_init (D_TvenLvdsParam *screen_para)D_FUNCPOSTFIT;

/** @brief hmd参数地址初始化
*
* @retval D_OK  初始化成功
* @retval D_ERR 初始化失败
*/
D_Result
d_av_hmd_param_init (void)D_FUNCPOSTFIT;


/** @brief tcon 初始化
*
* @retval D_OK  初始化成功
* @retval D_ERR 初始化失败
*/
D_Result d_av_tcon_init (D_TCON_INIT_PARAM *param)D_FUNCPOSTFIT;
/** @brief 设置cvbs的AD状态
* @param lock:锁定与否
*/
void d_av_set_cvbs_adstatus(D_U8 val)D_FUNCPOSTFIT;
/** @brief
* @param */
void d_av_set_local_adc_clk(D_U8 local_adc_clk)D_FUNCPOSTFIT;

/** @brief
* @param */
D_U8 d_av_get_local_adc_clk(void)D_FUNCPOSTFIT;
/** @brief
* @param */
D_Float d_av_get_sourcefreq_colorburst(void)D_FUNCPOSTFIT;
/** @brief
* @param */
D_Float d_av_get_cur_sourcefreq(void)D_FUNCPOSTFIT;
/** @brief
* @param */
void d_av_set_outputFreq(void)D_FUNCPOSTFIT;

 /** @brief cvbs模拟音频输入端num 0和1对换
* @param    cvbs_num_invert  0:不对换，1:对换；根据硬件选择
* @retval D_OK	操作成功
*/
D_U8 d_av_cvbs_num_invert(D_U8 cvbs_num_invert)D_FUNCPOSTFIT;

/** @brief
* @param */
void d_av_set_atv_test_unstandard(D_U8 flag)D_FUNCPOSTFIT;

/** @brief 不支持的音频格式的回调函数
* @param parm   cb 回调函数
*/
void d_av_set_unsupported_aud_cb(DAVGUICALLBACK cb)D_FUNCPOSTFIT;
D_Result d_av_hdmi_monitor(void)D_FUNCPOSTFIT;

 /**@brief 获取剩余跳帧个数，每次设置VPU跳帧个数前需检查剩余是否为0，
 不为零时不能进行设置。airplay屏幕镜像功能时使用
* @retval D_OK	操作成功
*/
D_U8 d_av_get_video_jump_frame_left(void)D_FUNCPOSTFIT;

/** @brief 设置VPU跳帧的个数，仅在screen push开启时启用
 airplay屏幕镜像功能时使用
* @param num : 跳的帧数(<=15)
* @param interval : 间隔几帧(<=15) 跳一帧
*/
void d_av_set_video_jump_frame(D_U8 num, D_U8 interval)D_FUNCPOSTFIT;
/**
@brief 设置atv非标参数*/
D_U8 d_av_set_atv_nonstd_param(D_Atv_Nonstd_Param* nonstd_param)D_FUNCPOSTFIT;

/** @brief hdmi*/
void
d_av_hmd_param_set (D_hdmi_param param)D_FUNCPOSTFIT;

 /** @brief dac增益控制-31~32db,单位1db*/
void d_av_audio_dac_gain_ctrl (D_S32 dac_gain_ctrl)D_FUNCPOSTFIT;

 /** @brief line in增益控制0~63db,单位1db*/
void d_av_audio_adc_gain_ctrl(D_U32 adc_gain_ctrl)D_FUNCPOSTFIT;
#ifdef  __cplusplus
}
#endif

#endif
