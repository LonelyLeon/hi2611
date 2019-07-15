/** @file
* @brief 电视设置参数结构
* @author
* @date 2005-6-30 龚克: 建立文件
*/
#ifndef _P_ATVCONFIG_H_
#define _P_ATVCONFIG_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dDBase.h"
#define VALID_FLAG (0x33557766)//无特殊意义，只对读出的数做简单比较。

#define TV_COLOR_MODE_MAX      3//色温模式
#define TV_IMAGE_MODE_MAX      4//图像模式
#define TV_IMAGE_CURVE_MAX      5//图像模式
#define TV_NR_MODE_MAX      4//数字降噪

#define TV_USER_PMODE_NUM  2//图像模式中用户模式的序号
#define TV_AUDIO_MODE_NUM  4//声音模式
#define TV_AUDIO_FEQ       18//声音PEQ

#define TV_VOL_MODE_NUM  4//vol模式
#define TV_VOL_WAVE       20//声音曲线

#define TV_AVC_INPUT_NUM       6//AVC 输入源个数

/** @brief 电视模式*/
typedef enum
{
    D_DB_TVMODE_TV = 0,
    D_DB_TVMODE_DTV,
    D_DB_TVMODE_AV,
#ifndef D_TV_IAMGE_SOURCE
    D_DB_TVMODE_Component,
#endif
    D_DB_TVMODE_USB,
    D_DB_TVMODE_HDMI,
    D_DB_MODE_NUM
} D_DBTvMode;

#ifdef D_TV_IAMGE_SOURCE

//CM
typedef struct
{
    D_U8            cm_on;                          // on: NR/CM on; off: NR/CM off
} D_CM_SET;

//DCE
typedef struct
{
    D_U8            dce_idx;
} D_DCE_SET;

//ILP
typedef struct
{
    D_S8            rlp;
    D_S8            glp;
    D_S8            blp;
    D_S8            clp;
    D_S8            mlp;
    D_S8            ylp;
} D_ILP_SET;

//IHP
typedef struct
{
    D_U8            rhp;
    D_U8            ghp;
    D_U8            bhp;
    D_U8            chp;
    D_U8            mhp;
    D_U8            yhp;
} D_IHP_SET;

//ISP
typedef struct
{
    D_U8            rsp;
    D_U8            gsp;
    D_U8            bsp;
    D_U8            csp;
    D_U8            msp;
    D_U8            ysp;
} D_ISP_SET;

//COLOR_SETTING
typedef struct
{
    D_U8            ase_on;
    D_U8            ase_weight;
    D_U8            icm_on;
} D_CHROMA_SET;

//GAMMA
typedef struct
{
    D_U8            gamma_idx;
} D_GAMMA_SET;

typedef struct
{
    D_U8            rgain;
    D_U8            ggain;
    D_U8            bgain;
    D_U16            roffset;
    D_U16            goffset;
    D_U16           boffset;
} D_CTEMP_SET;

//BL_DIM
typedef struct
{
    //  D_U8            blacklight;
    D_U8            bl_min;
    D_U8            bl_max;
} D_BLDIM_SET;

//NR
typedef struct
{
    D_U8            luma_snr_on;
    D_U8            chroma_snr_on;
    D_U8            luma_tnr_on;
    D_U8            chroma_tnr_on;
    D_U8            luma_snr;
    D_U8            luma_tnr;
    D_U8            chroma_snr;
    D_U8            chroma_tnr;
    D_U8            luma_core;
    D_U8            luma_gain;
    D_U8            chroma_core;
    D_U8            chroma_gain;
} D_NR_SET;

//DE
typedef struct
{
    D_U8            lti_on;
    D_U8            cti_on;
    D_U8            peak_on;
    D_U8            comb_lti;
    D_U8            comb_cti;
    D_U8            sts_on;
} D_DE_SET;


#else
//DE
typedef struct
{
    D_U8            lti_on;
    D_U8            cti_on;
    D_U8            peak_on;
    D_U8     de_core;
    D_U8     de_nl_en;
    D_U8     lti_gain;
    D_U8     cti_gain;
    D_U8     pk_core;
    D_U16    pk_up;
    D_S8     pk_beta;
    D_U8     pk_gain;
    D_U8     pk_cfg;
    D_U8     pk_negain;
    D_U8     lti_f_idx;
    D_U8     cti_f_idx;
    D_U8     pk_f_idx;
    D_U8     sts_on;
} D_DE_SET;


//NR
typedef struct
{
    D_U8            snr_on;                         // 0: SNR off; 1: SNR on
    D_U8     snr_uv_on;
    D_U8            snr_prev_on;
    D_U8            snr_adp_on;
    D_U8            snr_gain;
    D_U8     snr_uv_gain;
    D_U8            tnr_on;                         // 0: TNR off; 1: TNR on
    D_U8     tnr_uv_on;
    D_U8     tnr_upper;
    D_U8            tnr_gain;
    D_U8            tnr_dynrnd;
    D_U8     md_core;
    D_U8            md_gain;
    D_U8           md_con;
    D_U8            mnr_on;                         // 0: MNR off; 1: MNR on
    D_U8            mnr_db_thr;
    D_U8            mnr_dr_thr;
    D_U8     mnr_db_coeff;
    D_U8           tnr_adp_on;
    D_U8           md_pflt_on;
} D_NR_SET;

//BL_DIM
typedef struct
{
    D_U8            bl_min;
    D_U8            bl_max;
    D_U8            gd_on;
    D_U8            gd_res;
    D_U8            pwm_freq;
    D_U8            gd_con_gain;
} D_BLDIM_SET;

typedef struct
{
    D_U8            rgain;
    D_U8            ggain;
    D_U8            bgain;
    D_U8            roffset;
    D_U8            goffset;
    D_U8            boffset;
} D_CTEMP_SET;

//GAMMA
typedef struct
{
    D_U8            gamma_idx;
    D_U8            gamma_on;
} D_GAMMA_SET;

//DI/FM
typedef struct
{
    D_U8            di_si_on;
    D_U8            di_ti_on;
    D_U8            di_fc_on;
    D_U8            ci_2d_gn;
    D_U8           ci_tgn;
    D_U8           ci_mgn;
    D_U8           ci_bgn;
    D_U8           di_dbg;
    D_U8            fm_rescsd_on;
    D_U8            fm_resc22_on;
    D_U8            fm_resc32_on;
    D_U8            fm_loctic_mode;
    D_U8            fm_loc22_on;
    D_U8            fm_loc32_on;
    D_U8            fm_usest_on;
    D_U8            fm_clip32;
    D_U8            fm_clip22;
    D_U8            scl_bicubic;
    D_U8            cs_idx;
    D_U8            fm_fld_tgn;
    D_U8            fm_fld_zgn;
    D_U8            fm_frm_tgn;
    D_U8            fm_frm_zgn;
} D_DIFM_SET;

//CE
typedef struct
{
    D_U8           ce_on;                          // 0: CE off; 1: CE on
    D_U8           bs_on;                          // 0: BS off; 1: BS on
    D_U8           ws_on;                          // 0: WS off; 1: WS on
    D_U8           cc_on;
    D_U8           ce_gain;                        // CE gain
    D_U8           bbd_mode;                   // bbd mode: 0-auto;1-manual;2-off
    D_U8           histq_on;
    D_U8           ropc_on;
} D_CE_SET;

//ASE
typedef struct
{
    D_U8            ase_on;                         // 0: ASE off; 1: ASE on
    D_U8            ase_gain;                       // ASE gain
    D_U8            ase_stl;
    D_U8            ase_ssl;
    D_U8            ase_stu;
    D_U8            ase_ssu;
    D_U8     ase_ftg_gain;
} D_ASE_SET;

//FTC
typedef struct
{
    D_U8            ftc_on;                         // 0: FTC off; 1: FTC on
    D_S8            ftc_adj;                        // FTC angle: 0~63
    D_U8            ftd_htl;
    D_U8            ftd_htu;
    D_U8            ftd_hsl;
    D_U8            ftd_hsu;
    D_U8            ftd_ctl;
    D_U8            ftd_ctu;
    D_U8            ftd_csl;
    D_U8            ftd_csu;
    D_U8            ftc_hgy;
    D_U8            ftc_hgr;
    D_U8            ftc_hcy;
    D_U8            ftc_hcr;
} D_FTC_SET;

//ICM
typedef struct
{
    D_U8           icm_on;
    D_U8           icm_rhr;                        // red hue range: 0~7
    D_U16           icm_rhm;                        // red hue mid: 0~360
    D_U8           icm_rhp;                        // red hue param.: 0~63(-32~31)
    D_U16           icm_rsp;                        // red saturation param.: 0~63(-1024~1023)
    D_U8           icm_ghr;
    D_U16           icm_ghm;
    D_U8           icm_ghp;
    D_U16          icm_gsp;
    D_U8           icm_bhr;
    D_U16           icm_bhm;
    D_U8           icm_bhp;
    D_U16           icm_bsp;
    D_U8           icm_chr;
    D_U16           icm_chm;
    D_U8           icm_chp;
    D_U16           icm_csp;
    D_U8           icm_mhr;
    D_U16           icm_mhm;
    D_U8           icm_mhp;
    D_U16           icm_msp;
    D_U8           icm_yhr;
    D_U16           icm_yhm;
    D_U8           icm_yhp;
    D_U16           icm_ysp;
    D_U8           icm_xhr;
    D_U16           icm_xhm;
    D_U8           icm_xhp;
    D_U16           icm_xsp;

} D_ICM_SET;

//ADC
typedef struct
{
    D_U16          r_gain;      // 9bit 65[4],66
    D_U16          g_gain;      // 9bit 65[5],67
    D_U16          b_gain;      // 9bit 65[6],68
    D_U8            r_offset;       // 8bit 7A
    D_U8            g_offset;       // 8bit 7B
    D_U8            b_offset;       // 8bit 7C
} D_ADC_SET;

//COMB
typedef struct
{
    D_U8            comb_2d_on;
    D_U8            comb_3d_on;                     // 0: 3D comb filter off; 1: 3D comb filter on
    D_U8            comb_thr_curr_y;
    D_U8            comb_thr_curr_c;
    D_U8            comb_thr_f_y;
    D_U8            comb_thr_f_c;
    D_U8            comb_thr_ff_y;
    D_U8            comb_thr_ff_c;
    D_U8            comb_td_flt_thr;
    D_U8            comb_td_org_thr;
    D_U8            comb_td_mflt_thr;
    D_U8            comb_md_core;
    D_U8            comb_md_gain;
    D_U8            comb_coef_pb;
    D_U8            comb_coef_pl1;
    D_U8            comb_coef_pl2;
    D_U8            comb_coef_pl3;
    D_U8            comb_coef_nb;
    D_U8            comb_coef_nl1;
    D_U8            comb_coef_nl2;
    D_U8            comb_coef_nl3;
    D_U8            comb_y_level_msb;
    D_U8            comb_y_level_lsb;
    D_U8            comb_y_gain_msb;
    D_U8            comb_y_gain_lsb;
    D_U8            comb_u_gain_msb;
    D_U8            comb_u_gain_lsb;
    D_U8            comb_v_gain_msb;
    D_U8            comb_v_gain_lsb;
    D_U8            wavePos_msb;            //0~255
    D_U8            wavePos_lsb;            //0~255
    D_U8            comb_agc_c0;            //0~255
    D_U8            comb_agc_c1;            //0~63
    D_U8            comb_agc_c2;            //0~255
} D_COMB_SET;


//COMP
typedef struct
{
    D_U8           comp_flip_clk;           // 1bit 02[0]
    D_U8           comp_gain_b;             // 3bit 02[3:1]
    D_U8           comp_gain_g;             // 3bit 03[2:0]
    D_U8           comp_gain_r;             // 3bit 03[5:3]
    D_U8           comp_i_adc;              // 2bit 03[7:6]
    D_U8           comp_i_pga;              // 2bit 04[1:0]
    D_U8           comp_vclampimp;      // 3bit 04[4:2]
    D_U8           comp_inbw_b;             // 3bit 04[7:5]
    D_U8           comp_inbw_g;             // 3bit 05[2:0]
    D_U8           comp_inbw_r;             // 3bit 05[5:3]
    D_U8           comp_offs_b;             // 8bit 06
    D_U8           comp_offs_g;             // 8bit 07
    D_U8           comp_offs_r;             // 8bit 08
    D_U8           comp_pga_ref;            // 2bit 09[1:0]
    D_U8           comp_iclamp_b;           // 4bit 0A[3:0]
    D_U8           comp_iclamp_g;           // 4bit 0A[7:4]
    D_U8           comp_iclamp_r;           // 4bit 0B[3:0]
    D_U8           comp_imaxsel;            // 4bit 0B[7:4]
    D_U8           comp_pwdb_lsb;           // 4bit 0C[3:0]
    D_U8           comp_pwdb_msb;           // 4bit 0C[7:4]
    D_U8           comp_test_adcref;    // 2bit 0D[1:0]
    D_U8           comp_vclamplevel_b;// 3bit   0D[4:2]
    D_U8           comp_vclamplevel_g;// 3bit   0D[7:5]
    D_U8           comp_vclamplevel_r;// 3bit   0E[2:0]
    D_U8           comp_clampselect;    // 1bit 0E[3]
    D_U8           comp_vcom1_sel;      // 2bit 0E[5:4]
} D_COMP_SET;
#endif

typedef struct
{
    D_U8            ve_on;                          // on: NR/VE on; off: NR/VE off
} D_VE_SET;

//Picture Mode
typedef struct
{
    D_U8            brightness;                     // brightness
    D_U8            contrast;                       // contrast
    D_U8            color;                          // color/saturation
    D_U8            tint;                           // tint/hue
    D_U8            sharpness;                      // sharpness
} D_PMODE_SET;

//Picture Curve
typedef struct
{
    D_U8            osd_0;
    D_U8            osd_1;
    D_U8            osd_25;
    D_U8            osd_50;
    D_U8            osd_75;
    D_U8            osd_100;
} D_PCURVE_SET;

//CSC
typedef struct
{
    D_U8                        y2r_sign;
    D_U16                   y2r_coef;
    D_U8                        u2r_sign;
    D_U16                   u2r_coef;
    D_U8                    v2r_sign;
    D_U16                   v2r_coef;
    D_U8                    y2g_sign;
    D_U16                   y2g_coef;
    D_U8                    u2g_sign;
    D_U16                   u2g_coef;
    D_U8                    v2g_sign;
    D_U16                   v2g_coef;
    D_U8                    y2b_sign;
    D_U16                   y2b_coef;
    D_U8                    u2b_sign;
    D_U16                   u2b_coef;
    D_U8                    v2b_sign;
    D_U16                   v2b_coef;
    D_U8                    roff_sign;
    D_U32                   roff;
    D_U8                    goff_sign;
    D_U32                   goff;
    D_U8                    boff_sign;
    D_U32                   boff;
    D_U16                   top_level;
    D_U16                   bot_level;
    D_U8           expand;
    D_U8           contract;
} D_CSC_SET;

//SRS
typedef struct
{
    D_U32  srs_time ;
    D_U32  weight_coefficient;
} D_SRS_SET;
//SRS
typedef struct
{
    D_U8 drc_en; 			/*DAC BO输出的DRC功能使能，0--关闭，1--打开*/
    D_U8 drc_threshold;	/*DAC 阈值，超过该阈值的部分进行压缩，单位-db，范围0~31*/
    D_U8 drc_compress;	 /*DAC 压缩比例，超过drc_threshold阈值的部分进行压缩，范围1~32*/

} D_DRC_SET;

//lvds_sscg
typedef struct
{
    D_U8  enable;
    D_U8  mode;
    D_Float ssc_span;
    D_Float ssc_step;
} D_LVDSSSCG_SET;

//MIU_sscg
typedef struct
{
    D_U8    enable;
    D_U8    mode;
    D_Float ssc_span;
    D_Float ssc_step;
} D_MIUSSCG_SET;

typedef struct
{
    D_Double freq;  // 频率，单位Hz
    D_Double bw;        // 带宽，单位Hz
    D_Double gain;  // 增益，单位dB
} D_AUDIO_Peq;

typedef struct
{
    D_S8    fltCenterAdj;       /* kHz */
    D_S8    fltBwAdj;
} D_ATVSCAN_SET;

typedef struct
{
    D_Bool      standard_freq_list_flag; /*是否按标准频率表*/
    D_U32   start_freq; //起始频率
    D_U32   end_freq; //结束频率
    D_U16 bandwitch; //带宽
} D_FULLSCAN_CONFIG;


typedef struct
{
#ifdef D_TV_IAMGE_SOURCE
    D_PCURVE_SET pcurve_set[TV_IMAGE_CURVE_MAX];
    D_CTEMP_SET  ctemp_set[TV_COLOR_MODE_MAX];
    D_BLDIM_SET  bldim_set;
    D_DE_SET         de_set;
    D_CHROMA_SET  color_set;
    D_DCE_SET  dce_set;
    D_GAMMA_SET  gamma_set;
    D_CSC_SET    csc_set;
    D_CM_SET  cm_set;
    D_VE_SET     ve_set;
    D_PCURVE_SET hdpcurve_set[TV_IMAGE_CURVE_MAX];
    D_DE_SET         hdde_set;
    D_GAMMA_SET  hdgamma_set;
    D_CSC_SET    hdcsc_set;
    D_VE_SET    hdve_set;
#else
    D_PCURVE_SET pcurve_set[TV_IMAGE_CURVE_MAX];
    D_CTEMP_SET  ctemp_set[TV_COLOR_MODE_MAX];
    D_BLDIM_SET  bldim_set;
    D_NR_SET         nr_set[TV_NR_MODE_MAX];
    D_DIFM_SET   difm_set;
    D_DE_SET         de_set;
    D_CE_SET         ce_set;
    D_ASE_SET    ase_set;
    D_FTC_SET    ftc_set;
    D_ICM_SET    icm_set;
    D_GAMMA_SET  gamma_set;
    D_COMB_SET   comb_set;
    D_CSC_SET    csc_set;
    D_COMP_SET   comp_set;
    D_PCURVE_SET hdpcurve_set[TV_IMAGE_CURVE_MAX];
    D_NR_SET         hdnr_set[TV_NR_MODE_MAX];
    D_DIFM_SET   hddifm_set;
    D_DE_SET         hdde_set;
    D_CE_SET         hdce_set;
    D_ASE_SET    hdase_set;
    D_FTC_SET    hdftc_set;
    D_ICM_SET    hdicm_set;
    D_GAMMA_SET  hdgamma_set;
    D_COMB_SET   hdcomb_set;
    D_CSC_SET    hdcsc_set;
    D_COMP_SET   hdcomp_set;
    D_ADC_SET    adc_set;
    D_ADC_SET    hdadc_set;
    D_VE_SET     ve_set;
    D_VE_SET    hdve_set;
#endif
} D_Tv_Config_Sub; //各个通道下参数不一样的放在这个结构体里面

typedef struct
{
    D_U8        image_mode;//图像模式
    D_U8        color_mode;//色温
    D_U8        zoom_mode;//缩放模式
    D_U8        nr_mode;
    D_PMODE_SET  pmode_set[TV_IMAGE_MODE_MAX];

} D_Tv_Config_Usr_Sub; //各个通道下用户数据

typedef struct
{
    D_U8        audio_mode;
    D_U8        round;
    D_U8        backlight;
    D_U8        bluescreen;
} D_Tv_Config_Usr; //用户数据


typedef struct
{
    D_U8                     en;
    D_U8                     hour;
    D_U8                     min;
} D_Tv_Config_Poweron_Order; //定时开机

typedef struct
{
    D_U8                     en;
    D_U8                     hour;
    D_U8                     min;
} D_Tv_Config_Poweroff_Order; //定时关机

typedef struct
{
    D_U8                     motionless;
    D_U8                     motion;//
} D_Tv_Config_EEI; //能效参数

typedef struct
{
    D_U16                t2ms;//延时t2
    D_U16               t3ms;
    D_U16                t4ms;
    D_U16                t5ms;
    D_U8                 vcc_bl_swapon;
    D_U8                 vcc_bl_swapoff;
} D_Tv_Config_Lvds_Sequence; //能效参数

#define D_TV_NETWORK_VALID_MAGIC (0xfae5)
#define D_TV_WIFI_AP_CNT (8)
typedef struct
{
    D_U32   valid_magic;
    D_U8    type;
    D_U8    disable;
    D_U8    method;
    D_U8    connected;
    D_Char devicename[8];
    D_Char name[32];
    D_U8    bssid[6];      /* AP的bssid, 即addr */
    D_U32   ipaddr;
    D_U32   mask;
    D_U32   gateway;
    D_U32   dns;
} D_NetWorkSettingDat;

typedef struct
{
    D_U16   valid_magic;
    D_U16   version;
    D_Char  essid[32];      /* AP的essid, 即name */
    D_U8    bssid[6];      /* AP的bssid, 即addr */
    D_S16   key_len;       /*  密钥长度,-1或0代表不需要密码*/
    D_Char    key[64];      /*  密钥*/
} D_WifiApConfig;

//AVC
typedef struct
{
    D_U8               base_level;//本组基础level 0-40
    D_S32              base_avc;//本组基础level对应的基础dac值
    D_U8               level_step;//level_offset的单位
    D_S8               now_level_offset;//当前本组level对应基础level的偏移=(now_level-base_level)*level_step
    D_S32              now_close_avc;//本组当前level对应的close dac值
    D_S32              now_open_avc;//本组当前level对应的open dac值
} D_AVC_SET;

typedef struct
{
    D_U32 flag_valid;
    D_Tv_Config_Sub sub[D_DB_MODE_NUM];
#ifdef D_TV_IAMGE_SOURCE
    D_NR_SET    sd_nr_set[D_DB_MODE_NUM][TV_NR_MODE_MAX];
    D_NR_SET    hd_nr_set[D_DB_MODE_NUM][TV_NR_MODE_MAX];
#endif
    D_Tv_Config_Usr_Sub Usr_sub[D_DB_MODE_NUM];
    D_Tv_Config_Usr    usr_param;
    D_U16        t_ffft[D_DB_MODE_NUM];
    D_AUDIO_Peq  audio_peq_set[TV_AUDIO_MODE_NUM][TV_AUDIO_FEQ];
    D_SRS_SET srs;
//展频
    D_LVDSSSCG_SET lvds_sscg;
    D_MIUSSCG_SET  miu_sscg;
//控制
    D_U8           aging;//老化
    D_U8                     logo;//开机logo
    D_U8                     standard;
    D_U8                     passway;//开机数字电视
    D_ATVSCAN_SET    atvscanset;
    D_FULLSCAN_CONFIG fullscan_config;
    D_S16           tvbootchan;//模拟电视开机频道
    D_Tv_Config_Poweron_Order  poweron_order;
    D_Tv_Config_Poweroff_Order  poweroff_order;
    D_U8        avc_ctl_whole_en;
    D_U8        avc_peq_en;
    D_U8        debug_en; /* 调试 使能标志*/
    D_Tv_Config_EEI eei_param;
#ifdef D_TV_SUPPORT_WIFI
    D_NetWorkSettingDat  network_setting; /* 网络配置*/
    D_WifiApConfig          wifiapconfig[D_TV_WIFI_AP_CNT]; /* wifi ap记录*/
#endif
    D_U16  vol[TV_VOL_MODE_NUM][TV_VOL_WAVE];
    D_AVC_SET avc[TV_AVC_INPUT_NUM];
    D_U32 device_id; /* 设备id，机器维一标识码*/
    D_DRC_SET audio_drc[D_DB_MODE_NUM];
} D_Tv_Config;


// 白平衡调整预置尺度系数(/255)
// 白平衡调整预置增益 和预置偏置
typedef struct
{
    D_U32          scale_factor;        //
    D_U32          preset_gain_r;       //
    D_U32          preset_gain_g;       //
    D_U32          preset_gain_b;       //
    D_U32          preset_offs_r;       //
    D_U32          preset_offs_g;       //
    D_U32          preset_offs_b;       //
} D_VIP_WBA_CONFIG;

typedef struct
{
    D_U8           y_limit_lower;
    D_U8           y_limit_upper;
    D_U8           c_limit_lower;
    D_U8           c_limit_upper;
    D_U16         ce_c1_core;
    D_U16         ce_c2_core;
} D_VIP_YCCLIP_SET;

/** @brief 初始化配置信息*/
D_Result p_tvconf_init (void) D_FUNCPOSTFIT;

/** @brief 恢复为最初配置信息*/
D_Result p_tvconf_restore (D_Bool update) D_FUNCPOSTFIT;

D_Result  p_tvconf_get_veset_param(D_VE_SET *param, D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_veset_param  (D_VE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_pmodeset_param  (D_PMODE_SET *param, D_U8 input,  D_U8 idx) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_pmodeset_param  (D_PMODE_SET *param, D_U8 input,  D_U8 idx) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_bldim_set_param  (D_BLDIM_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_bldim_set_param  (D_BLDIM_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_de_set_param  (D_DE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_de_set_param  (D_DE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_gamma_set_param  (D_GAMMA_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_gamma_set_param  (D_GAMMA_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_csc_set_param  (D_CSC_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result   p_tvconf_set_cse_set_param  (D_CSC_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_cur_imagemode  (D_U8 *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_cur_imagemode  (D_U8 *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_cur_colormode  (D_U8 *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_cur_colormode  (D_U8 *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_cur_zoommode  (D_U8 *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_cur_zoommode  (D_U8 *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_pcurve_param(D_PCURVE_SET *param, D_U8 input, D_U8 idx) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_pcurve_param  (D_PCURVE_SET *param, D_U8 input,  D_U8 idx) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_ctemp_param(D_CTEMP_SET *param, D_U8 input, D_U8 idx) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_ctemp_param  (D_CTEMP_SET *param, D_U8 input,  D_U8 idx) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_cur_nrmode  (D_U8 *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_cur_nrmode  (D_U8 *param,  D_U8 input) D_FUNCPOSTFIT;
/** @brief 取得声音参数设置*/
D_Result  p_tvconf_get_audio_peq_set_param(D_AUDIO_Peq *param, D_U8 input, D_U8 mode,  D_U8 idx) D_FUNCPOSTFIT;
/** @brief 设置声音参数*/
D_Result  p_tvconf_set_audio_peq_set_param  (D_AUDIO_Peq *param,  D_U8 input, D_U8 mode, D_U8 idx) D_FUNCPOSTFIT;
/** @brief*/
D_Result  p_tvconf_get_srs (D_U8 *param) D_FUNCPOSTFIT;
/** @brief*/
D_Result p_tvconf_set_srs (D_U8 *param) D_FUNCPOSTFIT;
/** @brief*/
D_Result  p_tvconf_get_lvds_sscg (D_U8 *param) D_FUNCPOSTFIT;
/** @brief */
D_Result  p_tvconf_set_lvds_sscg  (D_U8 *param) D_FUNCPOSTFIT;
/** @brief*/
D_Result  p_tvconf_get_miu_sscg (D_U8 *param) D_FUNCPOSTFIT;
/** @brief */
D_Result  p_tvconf_set_miu_sscg  (D_U8 *param) D_FUNCPOSTFIT;
/** @brief*/
D_Result  p_tvconf_get_aging (D_U8 *param) D_FUNCPOSTFIT;
/** @brief */
D_Result  p_tvconf_set_aging  (D_U8 *param) D_FUNCPOSTFIT;
/** @brief*/
D_Result  p_tvconf_get_logomode (D_U8 *param) D_FUNCPOSTFIT;
/** @brief */
D_Result  p_tvconf_set_logomode  (D_U8 *param) D_FUNCPOSTFIT;
/** @brief */
D_Result  p_tvconf_get_cur_audiomode  (D_U8 *param,  D_U8 input) D_FUNCPOSTFIT;
/** @brief */
D_Result  p_tvconf_set_cur_audiomode  (D_U8 *param,  D_U8 input) D_FUNCPOSTFIT;
/** @brief */
D_Result  p_tvconf_get_cur_t_ffft(D_U16 *param,  D_U8 input, D_U8 audiomode) D_FUNCPOSTFIT;
/** @brief */
D_Result  p_tvconf_set_cur_t_ffft(D_U8 *param,  D_U8 input, D_U8 audiomode) D_FUNCPOSTFIT;
/** @brief 取得环绕声设置*/
D_Result  p_tvconf_get_cur_round  (D_U8 *param,  D_U8 input) D_FUNCPOSTFIT;
/** @brief 设置环绕声参数*/
D_Result p_tvconf_set_cur_round (D_U8 *param,  D_U8 input) D_FUNCPOSTFIT;
/** @brief */
D_Result  p_tvconf_get_cur_atvscan(D_ATVSCAN_SET *param) D_FUNCPOSTFIT;
/** @brief 设置*/
D_Result p_tvconf_set_cur_atvscan(D_U8 *param) D_FUNCPOSTFIT;
/** @brief */
D_Result  p_tvconf_get_fullscan_config(D_U8 *param) D_FUNCPOSTFIT;
/** @brief 设置*/
D_Result p_tvconf_set_fullscan_config(D_U8 *param) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_boot_chan(D_U8 *param) D_FUNCPOSTFIT;
D_Result p_tvconf_set_boot_chan(D_U8 *param) D_FUNCPOSTFIT;
D_Result p_tvconf_restore_usr(void)D_FUNCPOSTFIT;
/** @brief */
D_Result  p_tvconf_get_poweron_order(D_Tv_Config_Poweron_Order *param) D_FUNCPOSTFIT;
/** @brief 设置*/
D_Result p_tvconf_set_poweron_order(D_Tv_Config_Poweron_Order *param) D_FUNCPOSTFIT;
/** @brief */
D_Result  p_tvconf_get_poweroff_order(D_Tv_Config_Poweron_Order *param) D_FUNCPOSTFIT;
/** @brief 设置*/
D_Result p_tvconf_set_poweroff_order(D_Tv_Config_Poweron_Order *param) D_FUNCPOSTFIT;
/** @brief */
D_U8  p_tvconf_get_avc_whole_en(void) D_FUNCPOSTFIT;
/** @brief 设置*/
D_Result p_tvconf_set_avc_whole_en(D_U8 en) D_FUNCPOSTFIT;
/** @brief */
D_U8  p_tvconf_get_avc_peq_en(void) D_FUNCPOSTFIT;
/** @brief 设置*/
D_Result p_tvconf_set_avc_peq_en(D_U8 en) D_FUNCPOSTFIT;
/** @brief 恢复为最初配置信息*/
D_Result p_tvconf_restore_eep (void) D_FUNCPOSTFIT;

/** @brief 取得背光参数设置*/
D_Result p_tvconf_get_bldim_backlight(D_U8 *param,  D_U8 input) D_FUNCPOSTFIT;

/** @brief 设置背光参数*/
D_Result p_tvconf_set_bldim_backlight(D_U8 *param,  D_U8 input) D_FUNCPOSTFIT;

/** @brief 取得蓝屏参数设置*/
D_Result p_tvconf_get_blue_screen(D_U8 *param) D_FUNCPOSTFIT;

/** @brief 设置蓝屏参数*/
D_Result p_tvconf_set_blue_screen(D_U8 *param) D_FUNCPOSTFIT;

D_Result p_tvconf_restore_input_usr (D_U8 input) D_FUNCPOSTFIT;

/** @brief 取得调试使能设置*/
D_U8  p_tvconf_get_debug_en(void) D_FUNCPOSTFIT;

/** @brief 设置调试使能与否*/
D_Result p_tvconf_set_debug_en(D_U8 en) D_FUNCPOSTFIT;

D_Result p_tvconf_get_eei_param(D_U8 *param) D_FUNCPOSTFIT;
D_Result p_tvconf_set_eei_param(D_U8 *param) D_FUNCPOSTFIT;

D_Result  p_tvconf_get_hdde_set_param  (D_DE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_hdde_set_param  (D_DE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_hdgamma_set_param  (D_GAMMA_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_hdgamma_set_param  (D_GAMMA_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_hdcsc_set_param  (D_CSC_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_hdcsc_set_param  (D_CSC_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_hdpcurve_param(D_PCURVE_SET *param, D_U8 input, D_U8 idx) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_hdpcurve_param  (D_PCURVE_SET *param, D_U8 input,  D_U8 idx) D_FUNCPOSTFIT;
#ifdef D_TV_IAMGE_SOURCE
D_Result        p_tvconf_get_cmset_param(D_CM_SET *param, D_U8 input) D_FUNCPOSTFIT;
D_Result        p_tvconf_set_cmset_param  (D_CM_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_dce_set_param  (D_DCE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result        p_tvconf_set_dce_set_param  (D_DCE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result        p_tvconf_get_colorsettng_param(D_CHROMA_SET *param, D_U8 input) D_FUNCPOSTFIT;
D_Result        p_tvconf_set_colorsetting_param  (D_CHROMA_SET *param, D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_nr_set_param  (D_NR_SET *param,  D_U8 input, D_U8 idx) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_nr_set_param  (D_NR_SET *param,   D_U8 input, D_U8 idx) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_hdnr_set_param  (D_NR_SET *param,   D_U8 input, D_U8 idx) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_hdnr_set_param  (D_NR_SET *param,  D_U8 input, D_U8 idx) D_FUNCPOSTFIT;
#else
D_Result  p_tvconf_get_comp_set_param  (D_COMP_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_comp_set_param  (D_COMP_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_comb_set_param  (D_COMB_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_comb_set_param  (D_COMB_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_hdcomb_set_param  (D_COMB_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_hdcomb_set_param  (D_COMB_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_hdcomp_set_param  (D_COMP_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_hdcomp_set_param  (D_COMP_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_adc_set_param  (D_ADC_SET *param,  D_U8 input) D_FUNCPOSTFIT;
/** @brief 设置ADC参数*/
D_Result  p_tvconf_set_adc_set_param  (D_ADC_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_hdadc_set_param  (D_ADC_SET *param,  D_U8 input) D_FUNCPOSTFIT;
/** @brief 设置ADC参数*/
D_Result  p_tvconf_set_hdadc_set_param  (D_ADC_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_difm_set_param  (D_DIFM_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_difm_set_param  (D_DIFM_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_ce_set_param  (D_CE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_ce_set_param  (D_CE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_ase_set_param  (D_ASE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_ase_set_param  (D_ASE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_ftc_set_param  (D_FTC_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_ftc_set_param  (D_FTC_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_icm_set_param  (D_ICM_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_icm_set_param  (D_ICM_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_hddifm_set_param  (D_DIFM_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_hddifm_set_param  (D_DIFM_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_hdce_set_param  (D_CE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_hdce_set_param  (D_CE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_hdase_set_param  (D_ASE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_hdase_set_param  (D_ASE_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_hdftc_set_param  (D_FTC_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_hdftc_set_param  (D_FTC_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_hdicm_set_param  (D_ICM_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_hdicm_set_param  (D_ICM_SET *param,  D_U8 input) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_nr_set_param  (D_NR_SET *param,  D_U8 input, D_U8 idx) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_nr_set_param  (D_NR_SET *param,   D_U8 input, D_U8 idx) D_FUNCPOSTFIT;
D_Result  p_tvconf_get_hdnr_set_param  (D_NR_SET *param,   D_U8 input, D_U8 idx) D_FUNCPOSTFIT;
D_Result  p_tvconf_set_hdnr_set_param  (D_NR_SET *param,  D_U8 input, D_U8 idx) D_FUNCPOSTFIT;
#endif

/** @brief 取得 网络配置*/
D_Result  p_tvconf_get_network_setting_param  (D_NetWorkSettingDat *param) D_FUNCPOSTFIT;

/** @brief 设置网络配置参数*/
D_Result p_tvconf_set_network_setting_param  (D_NetWorkSettingDat *param) D_FUNCPOSTFIT;

/** @brief 取得 wifi ap 配置*/
D_Result  p_tvconf_get_wifiap_param  (D_WifiApConfig*param, D_U8 idx) D_FUNCPOSTFIT;

/** @brief 设置wifi ap 参数*/
D_Result p_tvconf_set_wifiap_param  (D_WifiApConfig *param) D_FUNCPOSTFIT;

/** @brief 取得设备id，机器维一标识码*/
D_U32  p_tvconf_get_device_id  (void) D_FUNCPOSTFIT;

/** @brief 设置设备id，机器维一标识码*/
D_Result p_tvconf_set_device_id  (D_U32 device_id) D_FUNCPOSTFIT;

D_Result p_tvconf_get_vol (D_U8 *param , D_U8 input) D_FUNCPOSTFIT;
D_Result p_tvconf_set_vol(D_U8 *param , D_U8 input) D_FUNCPOSTFIT;
D_Result p_tvconf_get_avc (D_U8 *param) D_FUNCPOSTFIT;
D_Result p_tvconf_set_avc(D_U8 *param) D_FUNCPOSTFIT;
/** @brief*/
D_Result p_tvconf_get_audio_drc (D_U8 *param , D_U8 input) D_FUNCPOSTFIT;
/** @brief */
D_Result p_tvconf_set_audio_drc(D_U8 *param , D_U8 input) D_FUNCPOSTFIT;
#ifdef  __cplusplus
}
#endif
#endif
