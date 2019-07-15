/** @file
* @brief ����Ƶ�豸����
* @author ����
* @date 2005-5-18 ����: �����ļ�
*   @date 2005-8-24 ����: �豸��������ǰ���豸ID��Ա
* @date 2006-8-2 shanzs:
        ����D_VidPicParam�ṹ
        ����D_VidPicRatio�ṹ
        ����D_VidRatioType����
        ����d_av_set_pic_param����
        ����d_av_set_pic_ratio����
*/

#ifndef _D_AV_H_
#define _D_AV_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dIO.h"

/** @brief N/P����*/
typedef enum
{
    PAL,
    NTSC,
} D_Current_Pal_Ntsc_Mode;

/** @brief video_ratio����*/
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

/** @brief ����Ƶ�豸���*/
typedef D_Handle    D_HAV;

/** @brief ����Ƶ�豸����*/
typedef struct
{
    D_ID                id;             /**< �豸ID*/
    D_ID                fend_id;    /**< ����Ƶ�豸��Ӧ��ǰ���豸ID*/
    D_U8               decodetype;  /**< ��Ƶ��������,���ڿ��Ʋ��Ż������ڴ��С*/
    D_U8               wait_sync_type;/**< ��ͬ����ʽ*/
} D_AVAttr;


/** @brief �����������ֵ*/
#define AUDIO_PLAY_CTRL_VOL_MODE        0
#define DSP_CTRL_VOL_MODE           1
#define AUDIO_VOL_CTRL      AUDIO_PLAY_CTRL_VOL_MODE//��Ҫ��ײ�����һ��
#if (AUDIO_VOL_CTRL == DSP_CTRL_VOL_MODE)
#define MAX_VOLUME  60
#else
#define MAX_VOLUME  79
#endif

/** @brief ��ȱʡֵ��ʼ������Ƶ�豸����*/
#define D_AV_ATTR_INIT(_a)\
    D_MACRO_BEGIN\
        (_a)->id = 0;\
    D_MACRO_END

/** @brief ����Ƶ�豸�¼�*/
typedef enum
{
    D_AV_EVT_VID_FMT_CHANGE,    /**< ��Ƶ��ʽ�仯*/
    D_AV_EVT_VID_INPUT_FMT_CHANGE,    /**< ������Ƶ��ʽ�仯*/
    D_AV_EVT_VID_lOCK_LOSE,    /**< ʧ��*/
    D_AV_EVT_NEW_PIC_START,     /**< ��Ƶ�»��濪ʼ����*/
    D_AV_EVT_NEW_AUD_START,     /**< ��Ƶ�����ݿ�ʼ����*/
    D_AV_EVT_HD_PIC_CANNOT_PLAY,/**< �����Ŀ���ɲ���*/
	D_AV_EVT_UNSUPPORTED_AUD,/**< ��֧�ֵ���Ƶ*/
} D_AVEvent;

/** @brief ����Ƶ�豸�¼����� */
typedef struct
{
    D_AVEvent evt;
    D_Ptr param;
} D_AVEventParam;

/** @brief ����Ƶ�豸�¼��ص�
*
*evt=D_AV_EVT_VID_FMT_CHANGE, paramΪD_VidFormat����
*/
typedef void (*D_AVCallback) (D_HAV hav, D_Handle handle, D_AVEvent evt, D_U32 param) D_FUNCPOSTFIT;

/** @brief ����Ƶ���ŷ�ʽ*/
typedef enum
{
    D_AV_PLAY_TV,           /**< ���ŵ��ӽ�Ŀ*/
    D_AV_PLAY_RADIO     /**< ���Ź㲥��Ŀ*/
} D_AVPlayMode;

/** @brief TV or PVR*/
typedef enum
{
    D_AVSourceMode_TV,          /**< TV*/
	D_AVSourceMode_PVR,		/**< PVR*/
	
	/* ������Ѷts�����Ź��ܣ�ʹ��pvr����¼����Ƶts�����ݣ�������Ȼ��pvr���Ź��ܲ��ţ�
	����ȴ������ƽ����˵�Ĵ�usb���ȡ�ļ���pvr��ͬ�����Ž�Ŀʱ���������ߵ������������̣�
	����ca�߰� dsp��ز��� ��������ʽ�������𣬹�����һ������Դ @20160912*/
	D_AVSourceMode_TS_scramble = 0x10,		/**< PVR*/
} D_AVSourceMode;

/** @brief HW or PVR*/
typedef enum
{
    D_PVR_START,
    D_PVR_WATINGHW = 1 << 1,    /**< �ȴ���Ƶ���*/
    D_PVR_VIDDECODE_OK = 1 << 2, /**< ��Ƶ����OK*/
    D_PVR_AUDDECODE_OK = 1 << 3, /**< ��Ƶ����OK*/
    D_PVR_AUD_VID_OK = 1 << 4,
    D_PVR_AUD_VID_MON = 1 << 5,
    D_PVR_STOP = 1 << 6
} D_AVPvrState;

/** @brief ��Ƶ��������*/
typedef enum
{
    D_VID_CODEC_MPEG = 0,
    D_VID_CODEC_MPEG2 = D_VID_CODEC_MPEG,
    D_VID_CODEC_AVS = 1,
    D_VID_CODEC_H264,
    D_VID_CODEC_MPEG4,
    D_VID_CODEC_VC1,
    D_VID_CODEC_MJPEG,
    /*********ģ�������ʽ**************/
    D_VID_CODEC_PAL,
    D_VID_CODEC_NTSC,
    D_VID_CODEC_SECAM,
    /***********����************/
	D_VID_CODEC_MAX = 0xFF,
} D_VidCodecType;

/** @brief ��Ƶ��������*/
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
    /*********ģ�������ʽ**************/
    D_AUD_CODEC_BG,
    D_AUD_CODEC_DK,
    D_AUD_CODEC_I,
    D_AUD_CODEC_M,
    /***********����************/
    D_AUD_CODEC_FDK,
	D_AUD_CODEC_MAX = 0xFF,
} D_AudCodecType;

//CVBS ģ�����lock����Ƶ��ʽ
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


/** @brief ��Ƶ��ʽ*/
typedef enum
{
    D_VID_FMT_AUTO = -1,    /**< �Զ���ʽ�л�*/
    D_VID_FMT_PAL = 0,      /**< PAL��*/
    D_VID_FMT_NTSC,         /**< NTSC��*/
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
	D_VID_FMT_1080P_50_TV_AUTO,//ֻ��PAL��ƥ��,����������֧�ֵķֱ��ʴӴ�С���μ���������֧�ֵ����ֱ��ʣ�����ȷ�����
	D_VID_FMT_1080P_60_TV_AUTO,//ֻ����NTSC��ƥ��,����������֧�ֵķֱ��ʴӴ�С���μ���������֧�ֵ����ֱ��ʣ�����ȷ�����
	D_VID_FMT_TV_AUTO,//���ֱ��ʣ�����n/p,����������֧�ֵķֱ��ʴӴ�С���μ���������֧�ֵ����ֱ��ʣ�����ȷ�����
} D_VidFormat;

/** @brief ��Ƶ������ʽ*/
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


	D_VID_INPUT_DVI_MIN,			//��ʵ���ô�������DVI
	
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
    D_VID_INPUT_UNDEFINE,//��֧�ֵĸ�ʽ

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

/** @brief ��Ƶ��Ϣ����*/
typedef enum
{
    D_Tv_Mes,
    D_Pvr_Mes,
    D_Logo_Mes,
} D_VidMesType;

/** @brief ����Ƶ�ص�������Ϣ���� */
typedef struct
{
    D_VidFormat VidFormat; /**< ��ǰ�����ʽ*/
    D_VidInputFormat VidInputFormat; /**< ��ǰ�����ĿԴ��ʽ*/
    D_U16 Vid_Width; /**< ��ƵԴ��*/
    D_U16 Vid_Height; /**< ��ƵԴ��*/
    D_VidMesType Mes_type;/**< ��Ƶ��Ϣ����*/
} D_VidInfo;

/** @brief ��Ƶ�������*/
typedef enum
{
    D_VID_OUTPUT_AV1    = 0x00000001,
    D_VID_OUTPUT_AV2    = 0x00000002,
    D_VID_OUTPUT_YPBPR  = 0x00000004,
    D_VID_OUTPUT_HDMI   = 0x00000008,
    D_VID_OUTPUT_VGA    = 0x00000010,
	D_VID_OUTPUT_LCD	= 0x00000020,
} D_VidOutputType;

/** @brief ��Ƶ��������*/
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
    D_VID_IUTPUT_TEST,//�ϻ�ģʽ
    D_VID_IUTPUT_WIFIDISPLAY,

#ifdef D_TV_LIULINK_SOURCE
    D_VID_IUTPUT_LIULINK,
#endif
#ifdef D_TV_SUPPORT_IPTV
    D_VID_IUTPUT_IPTV,
#endif
	D_VID_IUTPUT_MAX,
} D_VidInputType;

/**��Ƶ������Ϣ*/
typedef enum
{
	D_AUD_SAMPLE_RATE = 0,
	D_AUD_CHANNELS	= 1
}D_Audio_Steam_Info; 

typedef enum
{
    D_AUD_DRA_NORMAL_CHN = 0,
    D_AUD_DRA_LFE_CHN	= 1
} D_Audio_Dra_Chn_Info; 	//dra ��������Ϣ

typedef enum
{
    D_VID_BackGround_BLack,
    D_VID_BackGround_Blue,
    D_VID_BackGround_White,
    D_VID_BackGround_Red,
    D_VID_BackGround_Green,
} D_VidBackGroundColor_t;

/** @brief ��������*/
typedef enum
{
    D_AUD_STEREO,           /**< ������*/
    D_AUD_LEFT,             /**< ������*/
    D_AUD_RIGHT,            /**< ������*/
    D_AUD_MONO,             /**< ����������*/
    D_AUD_INVERTED_STEREO, /**<���� ������*/
    D_AUD_ONLY_LEFT, /**<ֻ�� ������ ����������*/
    D_AUD_ONLY_RIGHT, /**<ֻ�� ������ ����������*/
    D_AUD_QUIET_TRACK  /**��������*/
} D_AudTrack;

/** @brief ��Ƶ���*/
typedef D_VidOutputType D_VidOutput;
/** @brief ��Ƶ����*/
typedef D_VidInputType  D_VidInput;

/** @brief ��Ƶ�豸�豸��ʼ���漰IO�ṹ */
typedef struct
{
    D_GPIO_PortBit audio_mute;//���ڿ�����Ƶ���˷��Ƿ���
    D_GPIO_PortBit audio_broadcast_mute;//���ڿ���Ӧ���㲥�Ƿ���
    D_U8 audio_spdif_en;//�Ƿ�֧��spdif
    D_U8 dac_mode;
//-------2830��2610d���õ�--------
    D_U8 lvds_map;//���ģʽ
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
    D_U8 trigate;//������Ļ
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
	D_U16 display_invert;//= 0 ����ת// = 1����ת  //= 2 ����ת   //= 3 ���� ���򶼷�ת 
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



/** @brief ����Ƶͬ������ */
typedef enum
{
    D_AV_SYNC_AUTO = 0,/**< �Զ����� */
    D_AV_SYNC_PCR = 1, /**< PCRͬ��*/
    D_AV_SYNC_APTS = 2, /**< APTSͬ��*/
    D_AV_SYNC_NONE = 3,/**< ����ͬ������*/
    D_AV_SYNC_VPTS = 4, /**< VPTSͬ��*/
} D_AVSyncType;

/** @brief ����Ƶͬ������ */
typedef struct
{
    D_AVSyncType type; /**< ͬ������*/
    D_U32 min_threshold; /**< ��С������ֵ*/
    D_U32 max_threshold; /**< ��������ֵ*/
} D_AVSyncParam;

/** @brief ����Ƶ���Ų���*/
typedef union
{
    D_AVPlayMode    mode;   /**< ���ŷ�ʽ*/
    struct
    {
        D_AVPlayMode    mode;   /**< ���ŷ�ʽ*/
        D_U16       pcr_pid;/**< PCR PID*/
        D_U16       vid_pid;/**< ��ƵPID*/
        D_VidCodecType vid_codec;/**< ��Ƶ��������*/
        D_U16       aud_pid;/**< ��ƵPID*/
        D_AudCodecType aud_codec;/**< ��Ƶ��������*/
        D_AVSyncParam sync; /**< ����Ƶͬ������*/
        D_AVSourceMode source_mode; /**< ����Ƶ������Դ*/
        D_U8          I_Frame_Int_Flag;/**< I֡�жϼ���ʹ��*/
    } tv;                           /**< ���Ӳ��Ų���*/
    struct
    {
        D_AVPlayMode    mode;   /**< ���ŷ�ʽ*/
        D_U16       pcr_pid;/**< PCR PID*/
        D_U16       aud_pid;/**< ��ƵPID*/
        D_AudCodecType aud_codec;/**< ��Ƶ��������*/
        D_AVSyncParam sync; /**< ����Ƶͬ������*/
        D_AVSourceMode source_mode; /**< ����Ƶ������Դ*/
    } radio;                    /**< �㲥���Ų���*/
} D_AVPlayParam;

/** @brief ��Ƶ���� added by shanzs@06/08/02*/
typedef struct
{
    D_U8        brightness; /* ���� */
    D_U8        chroma;         /* ɫ�� */
    D_U8        contrast;       /* �Աȶ� */
} D_VidPicParam;

/** @brief ��Ƶ��߱������� added by shanzs@06/08/02*/
typedef enum
{
    D_VidRatio_TYPE_4_3_LB,
    D_VidRatio_TYPE_16_9_LB,
    D_VidRatio_TYPE_4_3_PS,
    D_VidRatio_TYPE_16_9_PS,
    D_VidRatio_TYPE_Auto
} D_VidRatioType;

/** @brief tv����ģʽ*/
typedef enum
{
    D_Full_Screen,//����
    D_4_to_3,//3//4:3
    D_ZOOM_1X,//�Ŵ�1
    D_ZOOM_2X, //�Ŵ�2
    D_Movie,//��Ӱ
    D_Overall_Screen,//ȫ��
    D_Overall_Horizon,//ȫ��
    D_NATURAL_RATIO,//���������ƵԴ�����������ȫ������¾��У�Ҳ���Ǿ��е�ͬʱ���Ҹ��Կ���2%
    D_NATURAL_RATIO_OVERALL_SCREEN,//��ȫ������¾���.����ʱ��һ��Ҳ����������
    D_16TO9_LB,
    D_4TO3_LB,
} D_tv_Display_Ratio_t;

/** @brief ��ƵDACѡ�� @13/09/14*/
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
    D_VL_DATA_MODE_YUV444 = 0, /**< ƽ��444 */
    D_VL_DATA_MODE_YUV411,  /**< ƽ��411 */
    D_VL_DATA_MODE_MB,  /**< �����ش��411 */
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
    D_Double freq;  // Ƶ�ʣ���λHz
    D_Double bw;        // ������λHz
    D_Double gain;  // ���棬��λdB
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
    D_U8               base_level;//�������level 0-40
    D_S32              base_avc;//�������level��Ӧ�Ļ���dacֵ
    D_U8               level_step;//level_offset�ĵ�λ
    D_S8               now_level_offset;//��ǰ����level��Ӧ����level��ƫ��=(now_level-base_level)*level_step
    D_S32              now_close_avc;//���鵱ǰlevel��Ӧ��close dacֵ
    D_S32              now_open_avc;//���鵱ǰlevel��Ӧ��open dacֵ
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
    D_S8   now_level_offset;//��ǰ����level��Ӧ����level��ƫ��=(now_level-base_level)*level_step
    D_S32  now_close_avc;//���鵱ǰlevel��Ӧ��close dacֵ
    D_S32  now_open_avc;//���鵱ǰlevel��Ӧ��open dacֵ
}D_audiodacctlNotifyInfo;


typedef struct
{
    D_U8 param1;  
    D_U8 param2;   
    D_U8 param3; 
} D_hdmi_param;

/** @brief ��Ƶ��߱��� added by shanzs@06/08/02*/
typedef D_VidRatioType D_VidPicRatio;

/** @brief ����Ƶϵͳ��ʼ��
*
*   �ڵ�������Ƶ��������ʱ���ȵ��ô˺���
* @retval D_OK  ��ʼ���ɹ�
* @retval D_ERR ��ʼ��ʧ��
*/
D_Result    d_av_open (D_AVOpenParam *param) D_FUNCPOSTFIT;

/** @brief ����Ƶϵͳ��ֹ
*
* �������ʱ���ͷ�����Ƶϵͳ�ڵ���Դ
* @retval D_OK  �����ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result    d_av_close (void) D_FUNCPOSTFIT;

/** @brief ����һ������Ƶ�豸
* @param attr   ����Ƶ�豸���Խṹָ�룬ΪNULLʱʹ��ȱʡֵ
* @param handle �ص�ʱ���صĲ������
* @return �ɹ�ʱ��������Ƶ�豸�����ʧ�ܷ���D_INVALID_HANDLE
*/
D_HAV           d_av_create (D_AVAttr *attr, D_Handle handle) D_FUNCPOSTFIT;

/** @brief ����һ������Ƶ�豸
* @param hav    ����Ƶ�豸���
* @retval D_OK  �ͷųɹ�
* @retval   D_ERR_INVALID_HANDLE    �����Ч
*/
D_Result    d_av_destroy (D_HAV hav) D_FUNCPOSTFIT;

/** @brief �л�����
* @param hav    ����Ƶ�豸���
* @param param  ����Ƶ���Ų���
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
* @retval D_ERR_FAULT   �豸����
* @retval D_ERR_INVALID_ARGUMENT    ������Ч
* @retval D_ERR_NOT_SUPPORT �˹��ܲ�֧��
*/
D_Result
d_av_change_audio (D_HAV hav, D_AVPlayParam *param) D_FUNCPOSTFIT;

/**��ȡ ��ǰ��Ƶ�Ƿ�֧�ֲ���,���й�d_av_play֮�����**/
D_U8 d_av_get_audio_support_flag(void);

/** @brief ��ʼ����Ƶ����
* @param hav    ����Ƶ�豸���
* @param param  ����Ƶ���Ų���
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
* @retval D_ERR_FAULT   �豸����
* @retval D_ERR_INVALID_ARGUMENT    ������Ч
* @retval D_ERR_NOT_SUPPORT �˹��ܲ�֧��
*/
D_Result    d_av_play (D_HAV hav, D_AVPlayParam *param) D_FUNCPOSTFIT;

/** @brief ԭ�������²�������Ƶ
* @param hav    ����Ƶ�豸���
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
*/
D_Result d_av_restart_play (D_HAV hav)D_FUNCPOSTFIT;

/** @brief ֹͣ����Ƶ����
* @param hav    ����Ƶ�豸���
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
* @retval D_ERR_FAULT   �豸����
*/
D_Result    d_av_stop (D_HAV hav) D_FUNCPOSTFIT;

/** @brief ��ʼ���������е�����Ƶ����
* @param hav    ����Ƶ�豸���
* @param param  ����Ƶ���Ų���
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
* @retval D_ERR_FAULT   �豸����
* @retval D_ERR_INVALID_ARGUMENT    ������Ч
* @retval D_ERR_NOT_SUPPORT �˹��ܲ�֧��
*/
D_Result
d_av_play_while_searching(D_HAV hav, D_AVPlayParam *param);

/** @brief ֹͣ���������е�����Ƶ����
* @param hav    ����Ƶ�豸���
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
* @retval D_ERR_FAULT   �豸����
*/
D_Result
d_av_stop_while_searching(D_HAV hav);

/** @brief atv�����Ĺ����м��cvbs����״̬
* @param hav    ����Ƶ�豸���
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
* @retval D_ERR_FAULT   �豸����
*/
D_U8  d_av_getcvbslock_while_searching(D_HAV hav);

/** @brief ������Ƶ��ʽ
* @param hav    ����Ƶ�豸���
* @param fmt    ��Ƶ��ʽ
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE      �豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT    ������Ч
* @retval D_ERR_NOT_SUPPORT �������ڲ�֧��
*/
D_Result    d_av_set_vid_format (D_HAV hav, D_VidFormat fmt) D_FUNCPOSTFIT;

/** @brief ������Ƶ���
* @param hav    ����Ƶ�豸���
* @param out    ��Ƶ���
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE      �豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT    ������Ч
* @retval D_ERR_NOT_SUPPORT �������ڲ�֧��
*/
D_Result    d_av_set_vid_output (D_HAV hav, D_VidOutput out) D_FUNCPOSTFIT;

/** @brief��ȡ��ǰ��ʽ
* @retval PAL   pal
* @retval NTSC  NTSC
*/
D_Current_Pal_Ntsc_Mode d_av_get_pal_ntsc_mode(void)D_FUNCPOSTFIT;

/** @brief��ȡ��ǰ��Ƶ����
* @retval v_4_3_TO_16_9_LB
* @retval v_4_3_TO_16_9_PS
* @retval v_16_9_TO_4_3_LB
* @retval v_16_9_TO_4_3_PS
* @retval v_DEFAULT_DISPLAY
*/
D_Current_display_ratio_Mode d_av_get_current_display_mode(void)D_FUNCPOSTFIT;
/** @brief ��Ƶ��ʾ����
* @param hav    ����Ƶ�豸���
* @param blank  D_TRUEʱ��ʾ������D_FALSEʱ��ʾ��Ƶ
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
* @retval D_ERR_FAULT   �豸����
*/
D_Result    d_av_set_vid_blank (D_HAV hav, D_Bool blank) D_FUNCPOSTFIT;

/** @brief �ı���Ƶ��ʾ���ڵĴ�С
* @param hav        ����Ƶ�豸���
* @param x      ��ʾ�������Ͻ�x����
* @param y      ��ʾ�������Ͻ�y����
* @param width  ��ʾ���ڿ��
* @param height ���Ǵ��ڸ߶�
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
* @retval D_ERR_NOT_SUPPORT �˹���Ŀǰ��֧��
* @retval D_ERR_INVALID_ARGUMENT    ���ô��ڴ�С������Χ
*/
D_Result    d_av_set_vid_window(D_HAV hav, D_Coord x, D_Coord y, D_Coord width, D_Coord height) D_FUNCPOSTFIT;

/** @brief ��������
* @param hav        ����Ƶ�豸���
* @param track  ����
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE      �豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT    ������Ч
*/
D_Result    d_av_set_aud_track (D_HAV hav, D_AudTrack track) D_FUNCPOSTFIT;

/** @brief ����/�ָ��������
* @param hav        ����Ƶ�豸���
* @param mute       D_TRUE������D_FALSE�������
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
*/
D_Result    d_av_set_aud_mute (D_HAV hav, D_Bool mute) D_FUNCPOSTFIT;

/** @brief ����/�ָ������������
* @param hav        ����Ƶ�豸���
* @param mute       D_TRUE������D_FALSE�������
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
*/
D_Result    d_av_set_earphone_mute (D_HAV hav, D_Bool mute) D_FUNCPOSTFIT;
/** @brief ��Ӧ�õ���muteʱ��,�����˷��Ƿ����ȿ����û�����
 * @param mute_IO_ctrl_right   1:����dsp״̬���ߵ�ǰ����״̬Ϊ׼�����ȿ���Ӧ������ 0:��1����
 * @retval D_OK  �����ɹ�
 */
D_Result d_av_mute_io_ctrl_right(D_HAV hav,D_U8 mute_io_right)D_FUNCPOSTFIT ;
/** @brief ����/�ָ������������
* @param hav        ����Ƶ�豸���
* @param mute       D_TRUE������D_FALSE�������
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
*/
D_Result d_av_set_loudspeaker_mute (D_HAV hav, D_Bool mute)D_FUNCPOSTFIT;
/** @brief �����������
*
*   0 ��С��100���
* @param hav        ����Ƶ�豸���
* @param vol        �������(0~100)
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE      �豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT    ��������0~100��Χ��
*/
D_Result    d_av_set_volume (D_HAV hav, D_U8 vol) D_FUNCPOSTFIT;

/** @brief ��ȡ����������
*
* @retval 	����������
*/
D_U8	d_av_get_max_volume (void) D_FUNCPOSTFIT;

/** @brief ��������Ƶ�����¼��ٵ�����
* @param callback   �ص�����ָ��
* @param old �����NULL,���ؾɵĻص�����ָ�롣
* @retval D_OK  �����ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result    d_av_register_callback (D_AVCallback callback, D_AVCallback *old) D_FUNCPOSTFIT;

/** @brief ��ʼ����Ƶ����
* @param hav    ����Ƶ�豸���
* @param param  ����Ƶ���Ų���
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
* @retval D_ERR_FAULT   �豸����
* @retval D_ERR_INVALID_ARGUMENT    ������Ч
* @retval D_ERR_NOT_SUPPORT �˹��ܲ�֧��
*/
D_Result    d_av_display_pic_I(D_HAV hav, D_U8 *address, D_U32 Size) D_FUNCPOSTFIT;

/** @brief ȡ������Ƶ������
* @param vEvtCnt ��Ƶ�¼�����
* @param aEvtCnt ��Ƶ�¼�����
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_ARGUMENT    ������Ч
*/

D_Result d_av_get_evt_cnt(D_U32 *vEvtCnt , D_U32 *aEvtCnt) D_FUNCPOSTFIT;

/** @brief ������Ƶ����  added by shanzs@06/08/02
*/
D_Result d_av_set_pic_param (D_HAV hav, D_VidPicParam *param) D_FUNCPOSTFIT;
/** @brief��ȡ��Ƶ������Ϣ
*/
D_U32 d_av_get_aud_stream_info (D_Audio_Steam_Info audio_info_type) D_FUNCPOSTFIT;

/** @brief  ��ȡDRA��Ƶ������Ϣ*/
D_U32 d_av_get_aud_dra_chn_info(D_Audio_Dra_Chn_Info chn_info_type)D_FUNCPOSTFIT;


/** @brief ������Ƶ��߱���  added by shanzs@06/08/02
*/
D_Result d_av_set_pic_ratio (D_HAV hav, D_VidPicRatio ratio) D_FUNCPOSTFIT;

D_Result d_av_open_ex(void);
typedef void (*DAVGUICALLBACK)(D_U32 event);

/** @brief ����NP��ʽ�仯ʱ��ص�����
* @param parm   cb �ص�����
*/
void d_av_setguicb(DAVGUICALLBACK cb)D_FUNCPOSTFIT;
void d_av_setinputcb(DAVGUICALLBACK cb)D_FUNCPOSTFIT;
D_Result d_av_set_video_layer_param(D_HAV hav, D_VideoLayerParam *param) D_FUNCPOSTFIT;
D_Result d_av_display_frame(D_HAV hav, D_U32 id) D_FUNCPOSTFIT;
D_Result d_av_video_layer_enable(D_HAV hav, D_Bool enable) D_FUNCPOSTFIT;
D_Result d_av_set_layer_mixer(D_HAV hav, D_LayerType layers[]) D_FUNCPOSTFIT;

/** @brief ��ȡ��ƵSTC  
*/
D_Result d_av_get_vid_stc (D_U32 *stc) D_FUNCPOSTFIT;

/** @brief ֹͣͬ�����
*/
D_Result d_av_stop_sync_monitor (void) D_FUNCPOSTFIT;

/** @brief �ر���Ƶdac
* @param state ����0:�أ�1:��
* @retval D_OK	�����ɹ�
*/
D_Result
d_av_set_Aud_dac_state(D_U8 state)D_FUNCPOSTFIT;

/** @brief ����ͬ�����
*/
D_Result d_av_restart_sync_monitor (void) D_FUNCPOSTFIT;

/** @brief ��ȡ��ƵSTC
*/
D_Result d_av_get_vid_stc (D_U32 *stc) D_FUNCPOSTFIT;

/** @brief ��Ƶdac����
* @param parm   en  1:��dac 0:��dac
*/
D_Result d_av_vdac_ctrl(D_U8 en)D_FUNCPOSTFIT;
/** @brief ������Ƶaudio_factor
* @param audio_factor ��������
* @param BackGround �Ƿ�ʹ�ò˵���ֵ����
* @param input_type ����Դ
*/
D_Result
d_av_audio_factor_set(D_HAV hav, D_U16 *audio_factor , D_U8 state, D_VidInputType input_type) D_FUNCPOSTFIT;

/** @brief ������Ƶ����
* @param hav    ����Ƶ�豸���
* @param input  ��Ƶ����
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE      �豸�����Ч
* @retval D_ERR_INVALID_ARGUMENT    ������Ч
* @retval D_ERR_NOT_SUPPORT �������ڲ�֧��
*/
D_Result d_av_set_vid_input (D_HAV hav, D_VidInputType input) D_FUNCPOSTFIT;

/** @brief �����������ƽ��*/
D_Result  d_av_set_balance (D_HAV hav, D_S8 val) D_FUNCPOSTFIT;

/** @brief ��ƵPEQ*/
D_Result
d_av_Audio_PEQ(D_HAV hav, D_AdjPointOfPeq *Hr_adjpCnt , D_U8 PEQ_num, D_U32 Hr_n_fft, D_Audio Format) D_FUNCPOSTFIT;
//??????
/** @brief ��ƵPEQ eq*/
D_Result
d_av_Audio_PEQ_EQ(D_HAV hav, D_Peq_eq_param *peq_eq) D_FUNCPOSTFIT;
/** @brief ��Ƶ����*/
D_Result d_av_audio_srs(D_HAV hav, D_AudioSrs en) D_FUNCPOSTFIT;

/** @brief ���������ڲ����弶�������Ʋ��Կ���
* @param hav        ����Ƶ�豸���
* @param en       D_TRUE����D_FALSE��
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
*/
D_Result
d_av_avc_ctl(D_HAV hav, D_U8 en)D_FUNCPOSTFIT;

/** @brief ���������ڲ����弶�������Ʋ��Լ��ʱ��
* @param hav        ����Ƶ�豸���
* @param avc_detect_time       ���ʱ��
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
*/
D_Result
d_av_avc_detect_time(D_HAV hav,D_U32 avc_detect_time)D_FUNCPOSTFIT;
/** @brief
* @param BackGround ������ɫ
*/
D_Result d_av_set_background(BackGroundColor_t BackGround)D_FUNCPOSTFIT;

/** @brief ����tv����ģʽ
*/
D_Result d_av_set_tv_ratio_mode (D_HAV hav, D_tv_Display_Ratio_t ratio_mode) D_FUNCPOSTFIT;

/**@brief ��Ƶ��Ծ�������ֶ�����ͬ��
* @param Skip_length: ��Ծ����  ��λΪ����, �൱����(1/������)sΪ��λ������Ӧ�ÿɼӴֵ���ϸ��
* @retval D_OK	�����ɹ�
*/
D_Result 
d_av_skip_pcm(D_U32 Skip_length) D_FUNCPOSTFIT;

/** @brief ��Ƶ�ز��������ֶ�����ͬ��
* @param replay_length: �ز����� ��λΪ���� �൱����(1/������)sΪ��λ������Ӧ�ÿɼӴֵ���ϸ��
* @retval D_OK	�����ɹ�
*/
D_Result 
d_av_replay_pcm(D_U32 replay_length) D_FUNCPOSTFIT;

/** @brief peq���ؿ���
* @param hav        ����Ƶ�豸���
* @param en       D_TRUE����D_FALSE��
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
*/
D_Result
d_av_peq_ctrl(D_HAV hav, D_U8 en) D_FUNCPOSTFIT;

/** @brief ���������ܿ���
* @param hav        ����Ƶ�豸���
* @param en       D_TRUE����D_FALSE��
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
*/
D_Result
d_av_avc_ctl_whole_en(D_HAV hav, D_U8 en)D_FUNCPOSTFIT;
/** @brief ��������������ڹص�ѹ���ȼ�
* @param hav     compress_coefficient����Χ(-40db~0db)
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE  �豸�����Ч
*/
D_Result
d_av_avc_set_intelligent_volume_compress_level(D_HAV hav,float compress_coefficient) D_FUNCPOSTFIT;
/** @brief������Ƶ��ӡ��*/
void d_audio_print_open(void)D_FUNCPOSTFIT;

/** @brief������Ƶ��ӡ��*/
void d_audio_print_close(void)D_FUNCPOSTFIT;

/** @briefcheck vblank raise edge _|
* @param nocard_ca_flag 1:���޿�ca ,0:�����޿�ca
*/
void d_audio_nocard_ca_flag_set(D_U8 ca_flag)D_FUNCPOSTFIT;

/** @brief ��ȡDac_Ctrl_L*/
D_U32 d_av_get_dac_ctrl_l(void) D_FUNCPOSTFIT;
/** @brief ��ȡDac_Ctrl_R*/
D_U32 d_av_get_dac_ctrl_r(void) D_FUNCPOSTFIT;
/** @brief ����Dac_Ctrl_L*/
void d_av_set_avc_ctrl_l(D_U32 dac_l)D_FUNCPOSTFIT;
/** @brief ����Dac_Ctrl_R*/
void d_av_set_avc_ctrl_r(D_U32 dac_r)D_FUNCPOSTFIT;

void d_av_set_avc_ctrl_ex(D_U32 dac_val)D_FUNCPOSTFIT;

/** @brief ��ȡ��Ƶavc level*/
D_U8 d_av_get_cur_vdac_ctrl(void)D_FUNCPOSTFIT;
/** @brief �л���̨�Ǻ������Ƕ�֡ģʽ*/
D_Result d_av_set_switch_mode(D_Switch_Mode video_switch_mode) D_FUNCPOSTFIT;
D_U8 d_av_video_wait_playreq(void) D_FUNCPOSTFIT;

/** @brief��������������
* @param weight_coefficient:[50~100],srs_time [0~70]
*/
void  d_av_audio_srs_param_set(D_U32 srs_time ,D_U32 weight_coefficient)D_FUNCPOSTFIT;


void d_av_setunlockcb(DAVGUICALLBACK cb)D_FUNCPOSTFIT;

void  d_av_Status_while_searching(D_HAV hav,D_U8 mode)D_FUNCPOSTFIT;

/** @brief��ȡ��ǰ���ŵĽ�Ŀ���*/
D_Result d_av_get_cur_hw(D_U16* Width,D_U16* Height);


/** @brief ��ȡ������ǰ״̬*/
D_Result d_av_get_earphone_status (D_HAV hav);

/** @brief vo����,����Ҫ��Ƶ����ʾ��ʱ����Թر�VO���Խ��͹���*/
D_Result d_av_vo_ctrl(D_U8 en)D_FUNCPOSTFIT;

/** @briefcheck vblank raise edge _|
* @param 
*/
D_Result d_av_hdmi_Status(D_U8 num)D_FUNCPOSTFIT;

/** @brief ��ʾ������ʼ��
*
* @retval D_OK  ��ʼ���ɹ�
* @retval D_ERR ��ʼ��ʧ��
*/
D_Result d_av_display_para_init (D_DisplayParam* screenparam)D_FUNCPOSTFIT;

/** @brief������Ƶspdif ����*/
void d_av_spdif_en(D_U8 en )D_FUNCPOSTFIT;;

/** @brief������Ƶspdif ����*/
void d_av_spdif_volume(D_U32 vol )D_FUNCPOSTFIT;

/*�򿪻�ر�DAC*/
void d_av_dac_set_pwm_on(D_U8 on_off);
	
/** @brief screen_Push����*/
void d_av_screen_push_en(D_U8 en )D_FUNCPOSTFIT;

/** @brief frame_rate ��Ҫ��Ͷ��ģʽ�´���Ӧ��֡�ʣ��ڷ�Ͷ��ģʽ�´�D_VID_FRM_RAT_RESERVED����ʱ�ײ����vpu��������Ϊ׼*/
void d_av_set_video_frame_rate(D_VidFrameRate frame_rate)D_FUNCPOSTFIT;

/** @brief ��Ƶ�����ݴ�����
* @param    error_deal_mode��Ƶ�ݴ���ʽ:  0--��������֡; 1--�����ų���B֡��2--�������д���֡
* @retval D_OK	�����ɹ�
*/
D_U8 d_av_error_deal_mode(D_U8 error_deal_mode)D_FUNCPOSTFIT;
 /** @brief���뿪������
* @param    noise_bypass_en���뿪������:  0--���뿪; 1--�����
* @retval D_OK	�����ɹ�
*/
D_U8 d_av_noise_bypass_en(D_U8 noise_bypass)D_FUNCPOSTFIT;

/** @brief �ڴ����ýӿ�
* @param 
*/
D_U8 d_av_mem_set(D_VideoMemParam *mem_info)D_FUNCPOSTFIT;

/** @brief mute io ��������Ӧ��IO�ø��õ��������
* @param mute_io_flag 1:IO�ø�ʱ���Ӧ������0:IO�õ�ʱ���Ӧ����
*/
void d_av_muteio_flag(D_U8 mute_io_flag)D_FUNCPOSTFIT;
D_U16 d_av_strategy_info(D_U16 tag,D_U8 param_size,void *payload)D_FUNCPOSTFIT;

/** @brief	����CPU����unref_frames�ĸ�����3֡��4֡��
�����ڴ�ʱ��ʹ��unref_framesΪ3֡�ķ����������ڸ���60֡��ƬԴ�������ʻ��ܵ�һ��Ӱ�졣
��������¿�ʹ��unref_framesΪ4֡�ķ�������������������
 * @param unref_frames 1:4֡��0:3֡
*/
void d_av_unref_frames(D_U8 unref_frames)D_FUNCPOSTFIT;

  /** @brief��ת��ʹ��
* @param   invert 0:����ת��1:��ת
* @retval D_OK	�����ɹ�
*/
D_U8 d_av_display_invert(D_U8 invert)D_FUNCPOSTFIT;

/** @brief	 ʹ��DAC BO�����DRC����
* @param	 en: 1--ʹ��DRC���ܣ�0--�ر�DRC����
* @retval D_OK	  �����ɹ�
*/
D_U8 d_av_audio_bo_drc_enable(D_U8 bo_drc_enable)D_FUNCPOSTFIT;


/** @brief	����DAC BO�����DRC����
* @param   threshold: DRC����ֵ��ȡֵ��Χ��0x0-0x1f
				  compress��������ֵ�Ĳ���Ҫ����ѹ����ϵ����ȡֵ��Χ��0x0-0x5
*/
D_U8 d_av_audio_bo_drc_set(D_U8 threshold,D_U8 compressibility)D_FUNCPOSTFIT;

/** @brief avc ����ֵ����
* @param num:HI_ATV 0;HI_DTV 1;HI_CVBS 2;HI_YCBCR 3;HI_HDMI 4;HI_USB 5
* @param avc_base_param
*/
D_Result
d_av_audio_avc_base_set(D_Avc_Param  avc_base_param,D_U8 num)D_FUNCPOSTFIT;


/** @brief lvds ��ʼ��
*
* @retval D_OK  ��ʼ���ɹ�
* @retval D_ERR ��ʼ��ʧ��
*/
D_Result
d_av_lvds_init (D_U8 lvds_type,D_LvdsInitParam *lvds_para)D_FUNCPOSTFIT;

/** @brief tven��lvds�����Ĳ��� ��ʼ��
*
* @retval D_OK  ��ʼ���ɹ�
* @retval D_ERR ��ʼ��ʧ��
*/
D_Result d_av_tven_lvds_para_init (D_TvenLvdsParam *screen_para)D_FUNCPOSTFIT;

/** @brief hmd������ַ��ʼ��
*
* @retval D_OK  ��ʼ���ɹ�
* @retval D_ERR ��ʼ��ʧ��
*/
D_Result
d_av_hmd_param_init (void)D_FUNCPOSTFIT;


/** @brief tcon ��ʼ��
*
* @retval D_OK  ��ʼ���ɹ�
* @retval D_ERR ��ʼ��ʧ��
*/
D_Result d_av_tcon_init (D_TCON_INIT_PARAM *param)D_FUNCPOSTFIT;
/** @brief ����cvbs��AD״̬
* @param lock:�������
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

 /** @brief cvbsģ����Ƶ�����num 0��1�Ի�
* @param    cvbs_num_invert  0:���Ի���1:�Ի�������Ӳ��ѡ��
* @retval D_OK	�����ɹ�
*/
D_U8 d_av_cvbs_num_invert(D_U8 cvbs_num_invert)D_FUNCPOSTFIT;

/** @brief
* @param */
void d_av_set_atv_test_unstandard(D_U8 flag)D_FUNCPOSTFIT;

/** @brief ��֧�ֵ���Ƶ��ʽ�Ļص�����
* @param parm   cb �ص�����
*/
void d_av_set_unsupported_aud_cb(DAVGUICALLBACK cb)D_FUNCPOSTFIT;
D_Result d_av_hdmi_monitor(void)D_FUNCPOSTFIT;

 /**@brief ��ȡʣ����֡������ÿ������VPU��֡����ǰ����ʣ���Ƿ�Ϊ0��
 ��Ϊ��ʱ���ܽ������á�airplay��Ļ������ʱʹ��
* @retval D_OK	�����ɹ�
*/
D_U8 d_av_get_video_jump_frame_left(void)D_FUNCPOSTFIT;

/** @brief ����VPU��֡�ĸ���������screen push����ʱ����
 airplay��Ļ������ʱʹ��
* @param num : ����֡��(<=15)
* @param interval : �����֡(<=15) ��һ֡
*/
void d_av_set_video_jump_frame(D_U8 num, D_U8 interval)D_FUNCPOSTFIT;
/**
@brief ����atv�Ǳ����*/
D_U8 d_av_set_atv_nonstd_param(D_Atv_Nonstd_Param* nonstd_param)D_FUNCPOSTFIT;

/** @brief hdmi*/
void
d_av_hmd_param_set (D_hdmi_param param)D_FUNCPOSTFIT;

 /** @brief dac�������-31~32db,��λ1db*/
void d_av_audio_dac_gain_ctrl (D_S32 dac_gain_ctrl)D_FUNCPOSTFIT;

 /** @brief line in�������0~63db,��λ1db*/
void d_av_audio_adc_gain_ctrl(D_U32 adc_gain_ctrl)D_FUNCPOSTFIT;
#ifdef  __cplusplus
}
#endif

#endif
