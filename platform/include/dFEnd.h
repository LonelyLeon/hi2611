/** @file
* @brief 前端设备操作
* @author 龚克
* @date 2005-5-16 龚克: 建立文件
*/

#ifndef _D_FEND_H_
#define _D_FEND_H_

#include "dTypes.h"
#include "dIIC.h"
#include "dIO.h"

#ifdef  __cplusplus
extern "C"
{
#endif


/** @brief 前端设备句柄*/
typedef D_Handle    D_HFEnd;


// need detail information from 田兴杰
#define KU_SWITCH_FREQ  11750
#define C_SWITCH_FREQ       3600
#define OSC_ABOVE_IS_KU 9000
#define OSC_BELOW_IS_C  6000



typedef enum
{
    demod_3205_inside,//HI2309片内自带HI3205
    demod_3205_outside,//芯片外挂HI3205
    demod_3103,
    demod_3308,
    demod_3111,
    demod_3121,
    demod_MN88473,
    demod_3700,
    demod_3308_inside,
    demod_3321,
    demod_3123,
    demod_3112,
    demod_3308E_inside,
    demod_3701 = 14,
    demod_3701CVBS,
    demod_max,
} DemodType_t;

/** @brief 前段类型*/
typedef enum
{
    D_FEND_DVBC,    /**< DVB-C*/
    D_FEND_DVBT,    /**< DVB-T*/
    D_FEND_DVBS,    /**< DVB-S*/
    D_FEND_DTMB,    /**< DTMB*/
    D_FEND_ABS, /**< ABS*/
    D_FEND_ANALOG,  /**< ANALOG*/
    D_FEND_DVBT2,   /**< DVB-T2*/
	D_FEND_CVBS,	/**< CVBS*/
} D_FEndType;

typedef enum
{
    D_FEND_DTMB_ADC,    
    D_FEND_ATVDVBC_ADC,   
    D_FEND_CVBS_ADC,    
    D_FEND_CVBS_AFE,   
} D_FEndADC;    //Hi3701 ADC choose

typedef enum
{
    D_FEND_AtvDem,				// ATV解调    
    D_FEND_AvCvbsDc,			// 视频CVBS-直流耦合（模拟钳位）
    D_FEND_AvCvbsAcNormal,		// 视频CVBS-交流耦合，电平正极性    
    D_FEND_AvCvbsAcInvert,		// 视频CVBS-交流耦合，电平负极性
} D_FEndWorkMode; //接收CVBS信号的模式

/** @brief 用户解调tuner配置 */
typedef struct
{
    DemodType_t type;
    D_U8 demod_i2c_addr;
    D_U8 ts_sel;
    D_U8 i2c_no;
    D_U8 ts_data_mode;
    D_GPIO_PortBit reset;
    D_GPIO_PortBit sw_13_18v;
    D_GPIO_PortBit lnb;
    D_U32 xtalFreqKHz;
    D_U8 cfg_13v_18v;
    D_U8 cfg_lnb;
    D_U8 agc_polarity;  /**< AGC极性 */
    D_U8 psd_polarity;  /**< 功率谱极性 */
    D_U8 mode;  /**< 特殊模式, 如3121的广播调试模式选择 */
    D_U8 led_polarity;  /**< LED极性 */
    D_U8 iic_bus_repeat_sel;  /**< 选择哪个解调转发I2C */
    D_U8 diseqc_22k_sel;  /**< 选择哪个解调发送diseqc和22K */
    D_U8 tuner_sel;  /**< 占用的tuner代号, 用于多个解调共用tuner识别  */
    D_U8 idle_action  /**< 解调空闲时动作, 0:GPIO高阻, 1:休眠状态, 其它值不操作 */;
	D_U8 adc; /*选择ADC 源*/
} D_FEndConfigParam;

typedef D_FEndConfigParam D_DemoOpenParam;

/** @brief 调制方式*/
typedef enum
{
    D_FEND_QAM16,
    D_FEND_QAM32,
    D_FEND_QAM64,
    D_FEND_QAM128,
    D_FEND_QAM256,
    D_FEND_QPSK,
    D_FEND_MODE_AUTO
} D_FEndMod;

/** @brief 带宽*/
typedef enum
{
    D_FEND_6MHZ,
    D_FEND_7MHZ,
    D_FEND_8MHZ,
    D_FEND_5MHZ,
    D_FEND_2MHZ,
    D_FEND_1_7MHZ,
} D_FEndBandWidth;

/** @brief 极化方式*/
typedef enum
{
    D_FEND_HOR_POL,
    D_FEND_VER_POL,
    D_FEND_LEFT_POL,
    D_FEND_RIGHT_POL,
    D_FEND_POL
} D_FEndPol;

//与hi3701相对应的伴音系统制式
typedef enum
{
	SoundSys_FmMono = 1, 
	SoundSys_FmGermany,    
	SoundSys_FmKorea,      
	SoundSys_FmA2,         

	SoundSys_NicamBG,      
	SoundSys_NicamDK,      
	SoundSys_NicamDC,      
	SoundSys_NicamI,       
	SoundSys_NicamL,       
	SoundSys_Btsc,         
	SoundSys_AmL,
	SoundSys_MAX,
} D_SoundSys;

/** @brief 模拟电视视频格式*/

typedef enum
{
    D_VideoP,       /* PAL  */
    D_VideoN,   /* NTSC */
    D_VideoSECAM,                       /* SECAM */
    D_VideoMax,                             /* SECAM */
} D_VideoMode;

/** @brief 模拟电视音频格式*/
typedef enum
{
    D_AudioBG,      /* B/G */
    D_AudioDK,      /* D/K */
    D_AudioI,   /* I   */
    D_AudioM,       /* M */
    D_AudioN,       /* N */
    D_AudioNc,      /* Nc */
	D_AudioL,		/* L */
    D_AudioMax,     /* Nc */
} D_AudioMode;


/** @brief 调制方式*/
typedef enum
{
    D_FEND_DTMB_INFO,
    D_FEND_DTMB_DETAIL_INFO,
    D_FEND_DTMB_HN_INFO,
    D_FEND_DTMB_CARRIER_FREQ_INFO,
    D_FEND_DTMB_FREQ_INFO
} D_FEndadvanceStatusType;
/** @brief 频率(HZ)*/
typedef D_U32   D_FEndFreq;

/** @brief 符号率(BPS)*/
typedef D_U32   D_FEndBaud;

/** @brief 带宽()*/
typedef D_U16   D_FEndBandWitch;

/** @brief 22K状态*/
typedef enum
{
    D_F22KOff = 0,      // 22K关，明确状态
    D_F22KOn,       // 22K开，明确状态
    D_F22KNone, // 不关心22K状态
    D_F22KAuto = D_F22KNone,// 不关心22K状态
} D_F22KSTATE;

typedef enum
{
    D_LNB_OFF,
    D_LNB_ON,
} D_FLNBSTATE;

/** @brief DISEQC 版本(类型)*/
typedef enum
{
    D_DISEQC_TYPE_NONE = 0,
    D_DISEQC_TYPE_10,
    D_DISEQC_TYPE_11,
    D_DISEQC_TYPE_12,
    D_DISEQC_TYPE_13,
    D_DISEQC_TYPE_USALS = D_DISEQC_TYPE_13,
    D_DISEQC_TYPE_20,
    D_DISEQC_TYPE_21,
    D_DISEQC_TYPE_22,
    D_DISEQC_TYPE_23,
} D_FDiSEqCType;

/** @brief DISEQC 端口*/
typedef enum
{
    D_PORT_OFF = 0,
    D_PORT_NONE = 0,
    D_PORT_A = 1,
    D_PORT_B,
    D_PORT_C,
    D_PORT_D,
    D_PORT_01 = D_PORT_A,
    D_PORT_02 = D_PORT_B,
    D_PORT_03 = D_PORT_C,
    D_PORT_04 = D_PORT_D,
    D_PORT_05,
    D_PORT_06,
    D_PORT_07,
    D_PORT_08,
    D_PORT_09,
    D_PORT_10,
    D_PORT_11,
    D_PORT_12,
    D_PORT_13,
    D_PORT_14,
    D_PORT_15,
    D_PORT_16,
    D_PORT_BOUNDARY,
} D_FDiSEqCPort;


// 常用的，可能应用的diseqc1.2/1.3的命令
typedef enum
{
    D_MOTOR_GOTO_NN,            // 转到预存位置
    D_MOTOR_MOVE_EAST,      // 连续往西移动马达
    D_MOTOR_MOVE_WEST,      // 连续往东移动马达
    D_MOTOR_HALT,               // 使马达停止移动
    D_MOTOR_STOR_NN,        // 保存位置
    D_MOTOR_LIMIT_EAST,     // 设置马达向东移动界限
    D_MOTOR_LIMIT_WEST,     // 设置马达向西移动界限
    D_MOTOR_LIMIT_OFF,      // 取消界限
    D_MOTOR_RECALCULATION,      // 校准马达
    D_MOTOR_GOTO_ORIGINAL,  // 回到原点
    D_MOTOR_STEP_EAST,      // 向东步进马达
    D_MOTOR_STEP_WEST,      // 向西步进马达
    D_MOTOR_GOTO_AZIMUTH,       // 使马达偏移一定的角度/    D_MOTOR_RAW_CMD,                // 直接控制DiSEqC1.2的马达动作
} D_FDiSEqC12CmdType;

typedef union
{
    // GOTO_ORIGINAL/MOVE XX/STEP XX/HALT/LIMIT XX/RECALCULATION
    D_FDiSEqC12CmdType type;
    // GOTO_NN/STOR_NN
    struct
    {
        D_FDiSEqC12CmdType type;
        D_U8 nn_value;
    } NN_cmd;
    // AZIMUTH
    struct
    {
        D_FDiSEqC12CmdType type;
        D_U8 cmd1;
        D_U8 cmd2;
    } AZIMUTH;
    // RAW_CMD
    struct
    {
        D_FDiSEqC12CmdType type;
        D_U8 cmdlen;
        D_U8 cmd[8];
    } RAW_CMD;
} D_FDiSEqC12Cmd;

// need diseqc driving
typedef struct
{
    D_FDiSEqCType diseqc_type;
    D_FDiSEqCPort diseqc_port;
    // diseqc 1.2/1.3(USALS): motor postion: 0-63, 0 is original postion also
    // diseqc 2.2: bidirection motor postion: 0-63, 0 is original postion also
    D_FDiSEqC12Cmd motor_cmd;
} D_FEndDiSEqC;

/*DVBT2协议下信号类型*/
typedef enum
{
    D_FEND_T2_TYPE_DVBT = 0, /**<DVBT*/
    D_FEND_T2_TYPE_DVBT2 = 1, /**< DVBT2*/
} D_FEndDvbt2Type;

/*DVBT2协议下tuner锁频模式*/
typedef enum
{
    D_FEND_T2_MODE_NORMAL = 0, /**< 参数确定的锁频模式，一般用于播放节目时锁频*/
    D_FEND_T2_MODE_AUTO = 1,    /**< 自适应锁频，锁定所有情况，直到锁定或结束*/
    D_FEND_T2_MODE_SCAN = 2, /**< 特殊锁频模式，一般用于搜索节目时第一次锁频获取相关信息*/
} D_FEndDvbt2Mode;

/*DVBT2协议下固定移动标志*/
typedef enum
{
    D_FEND_T2_MOBILE_BASE = 0, /**< 固定*/
    D_FEND_T2_MOBILE_LITE = 1, /**< 移动*/
    D_FEND_T2_MOBILE_AUTO = 2, /**< 自动*/
} D_FEndDvbt2Mobile;

/** @brief 前端设置参数*/
// 2013-3-18 调整前端参数定义，将abs和dvbs/dvbs2合并在一起。by wy
typedef union
{
		/*将元素freq移到后面，这样D_FEndParam p = {0}能将所有的byte为0, @qiny 20150721*/
		//D_FEndFreq	freq;			/**< 频率*/	
    struct
    {
        D_FEndFreq      freq;   /**< 频率*/
        D_FEndBaud      baud;   /**< 符号率*/
        D_U16       mod;    /**< 调制方式*/
        D_U16           freq_k; /*100k*/
    } dvbc;                     /**< DVB-C参数*/
    struct
    {
        D_FEndFreq      freq;   /**< 频率*/
        D_FEndBandWitch BandWidth; /**< 带宽*/
    } dvbt;                     /**< DVB-T参数*/
    struct
    {
        D_FEndFreq      freq;   /**< 频率*/
        D_U16              BandWidth; /**< 带宽*/
        D_U8                 type;        /**< 信号类型0 dvbt , 1 dvbt2*/
        D_U8            PLPID;  /**< PLP号*/
        D_U8            mobile; /**< 0 : 固定，1: 移动，2:自动*/
        D_U8                 mode;        /**< 锁频方式0: 参数明确，1: 模糊参数(用于搜索)*/
    } dvbt2;                                    /**< DVB-T2参数*/
    struct
    {
        D_FEndFreq      freq;   /**< 频率*/
		D_U16	        BandWidth; /**< 带宽*/	
		D_U16           placeholder0;/*小端，原来的项目配置的主频点都是以dvbc的结构体存储的，为了避免mod的影响，使用占位符，以后可以改名使用 @qiny2015.07.07*/
		D_U16           placeholder1;/*占位符*/
		D_U16           freq_k; /*100k*/
    } dtmb;
    struct
    {
        D_FEndFreq      freq;   /**< 频率*/
        D_FEndBaud      baud;   /**< 符号率*/
        D_FEndPol       pol;    /**< 极化方式*/
    } abs;                      /**< ABS参数*/
    struct
    {
        D_FEndFreq      freq;   /**< 频率*/
        D_FEndBaud      baud;   /**< 符号率*/
        D_FEndPol       pol;    /**< 极化方式*/
    } dvbs;                     /**< dvbs/s2共用此参数*/
    struct
    {
        D_FEndFreq  freq;           /* kHz */
        D_U8    videoMode;      /* Video Mode */
        D_U8    audioMode;      /* Audio Mode */
        D_U8    SoundSys;		/**伴音制式  FmMono**/
		D_U8    mode;       	/* kHz */
				D_S8	fltCenterAdj; 	/* kHz */
				D_S8	fltBwAdj;				
    } atv;
	struct
    {
        D_U8      workmode;   /**< 工作模式*/
    } cvbs; 
		D_FEndFreq	freq;			/**< 频率*/	
} D_FEndParam;

/** @diseqc参数信息*/
typedef struct
{
    D_FDiSEqCType  diseqc_type;  /**<diseqc 版本(类型)*/
    //diseqc1.0/1.1 port
    D_FDiSEqCPort   diseqc_port; /**<diseqc 1.0/1.1 端口*/
    //diseqc1.2  position ( nn_value / x )
    D_U8    position_no;                     /**<diseqc1.2 点位*/
    //diseqc1.3 (usals)
    D_S16  local_longitude;   /**<diseqc1.3 (usals) 本地经度(-18000 ~ 18000)*/
    D_S16  local_latitude;      /**<diseqc1.3 (usals) 本地纬度(-9000~ 9000)*/
    D_S16  sate_longitude;    /**<diseqc1.3 (usals) 卫星经度(-18000 ~ 18000)*/
} D_FEndDiseqcInfo;

/** @LNB相关参数*/
typedef struct
{
    D_FEndFreq          lnbfreq1;       /**<本振频率1*/
    D_FEndFreq          lnbfreq2;       /**<本振频率2*/
    D_F22KSTATE     f22k_state;     /**<22K开关状态*/
    D_FEndPol          pol_state;       /**<极化状态*/
    D_Bool              power_en;       /**<是否允许供电*/
    D_FEndDiseqcInfo diseqc_info; /**<diseqc参数信息*/
} D_FEndLnbInfo;


// 盲扫模式
typedef enum
{
    D_FEND_START,
    D_FEND_LAST,
    D_FEND_CONTINUE,
    D_FEND_LAST_CONTINUE,
	D_FEND_STOP		
} D_FEndBlindCmd;

// 驱动盲扫方式定义，应用层定义了这些方式，但驱动不一定能够实现，
// 对于驱动不支持的方式，需要另外的手段来协调
typedef enum
{
    D_FEND_BLIND_SCAN_INTERACTIVE,      /*扫描到频点然后搜索节目*/
    D_FEND_BLIND_SCAN_BY_SEGMENT,   /*分段扫描*/
    D_FEND_BLIND_SCAN_MONOLITHIC,   /*一次性扫描完整个带宽*/
} D_FEndBlindScanType;

// 盲扫使用参数
typedef struct
{
    D_U8             lnb_type;  /**<SINGLE /C_DOUBLE / KU_DOUBLE*/
    D_FEndFreq       lnbfreq1;  /**<本振频率1*/
    D_FEndFreq       lnbfreq2;   /**<本振频率2*/
    D_FEndFreq       startfreq;  /**<起始频率MHZ*/
    D_FEndBandWitch  bandwidth;  /**<带宽MHZ*/
    D_FEndPol        pol;   /**< 极化方式*/
    D_F22KSTATE     f22kstate;
    D_FEndDiseqcInfo    diseqc;
    D_Ptr           ptr;
	D_FEndFreq       stopfreq;  /**<终止频率MHZ*/ 
} D_FBlindParam;


// 盲扫返回
typedef enum
{
    D_FEND_START_OK,
    D_FEND_START_ERROR,
    D_FEND_CONTINUE_OK,
    D_FEND_END_OK,
	D_FEND_STOP_OK
} D_FEndBlindResult;

// 盲扫捕捉的频点参数定义，驱动捕捉到参数后形成链表
typedef struct __D_FBlindTpItem
{
    D_FEndParam param;
    struct __D_FBlindTpItem *next;
} D_FBlindTpItem;

// 盲扫捕捉的频点参数定义，由驱动程序返回
typedef struct
{
    D_Int count;                    // 频点个数
    D_FEndType type;                // 前端类型
    D_FBlindTpItem *tplist;     // 频点列表
} D_FBlindTpList;

/*dvbt2锁频后的其它参数*/
typedef struct
{
    D_U8        type;        /**< 信号类型0 dvbt , 1 dvbt2*/
    D_U32      freq;        /**< 频率*/
    D_U16       bw;         /**<带宽MHZ*/
    D_U16      PLP_cnt;  /**< 搜索时PLP数量*/
    D_U8        PLP_id;         /**<实际PLP ID*/
    D_U8        mobile; /**< 0 : 固定，1: 移动，2:自动*/
} D_FEndDvbt2Info;


/** @brief 前端状态*/
typedef struct
{
    D_Bool  locked;         /**< 是否锁住*/
    D_U8        strength;       /**< 信号强度*/
    D_U8        quanlity;       /**< 信号质量*/
    D_U8    diseqc_set_result;
    D_U8     ber;
    D_U8     fec;
    D_Ptr     ptr;                  /**< T2时用于记录D_FEndDvbt2Info数据的指针*/
	D_S32	offset;					/**< ANALOG时用于记录freq offset*/
} D_FEndStatus;

/** @brief 前端状态高级接口*/
typedef struct
{
    D_FEndadvanceStatusType type;       /**< 要获取的信息类型*/
    D_U8        *Statusinfo;        /**< 获取信息头指针*/
    D_U32       Statusinfolength;       /**< 获取信息长度*/
} D_FEndadvanceStatus;

/** @brief 前端设备属性*/
typedef struct
{
    DemodType_t demod;
    D_FEndType type;        /**< 前端类型*/
    D_ID id;            /**< 前端设备ID*/
} D_FEndAttr;


/** @brief 用缺省配置初始化前端设备属性*/
#define D_FEND_ATTR_INIT(_a)\
    D_MACRO_BEGIN\
        (_a)->type = D_FEND_DVBC;\
        (_a)->id = 0;\
        (_a)->demod = demod_max;\
    D_MACRO_END

/** @brief 音视频设备事件参数 */
typedef struct
{
    DemodType_t tuner_type;
    D_FEndFreq freq;
    D_Ptr param;
} D_FEndEventParam;

typedef D_Result (*DFENDPLLCALLBACK)(DemodType_t tuner_type,D_FEndFreq freq);
void d_pll_jam_patchcb(DFENDPLLCALLBACK cb)D_FUNCPOSTFIT;
/** @brief 前端系统初始化
*
*   在调用前端操作函数时首先调用此函数
* @retval D_OK  初始化成功
* @retval D_ERR 初始化失败
*/
D_Result    d_fend_open (D_DemoOpenParam *param) D_FUNCPOSTFIT;

/** @brief 前段管理系统中止
*
* 程序结束时，释放前端系统内的资源
* @retval D_OK  操作成功
* @retval D_ERR 操作失败
*/
D_Result    d_fend_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个前端设备
* @param attr   前端设备属性结构指针，为NULL时使用缺省值
* @return 成功时返回前端设备句柄，失败返回D_INVALID_HANDLE
*/
D_HFEnd     d_fend_create (D_FEndAttr *attr) D_FUNCPOSTFIT;

/** @brief 销毁一个前端设备
* @param hfend 前端设备句柄
* @retval D_OK  释放成功
* @retval   D_ERR_INVALID_HANDLE    句柄无效
*/
D_Result    d_fend_destroy (D_HFEnd hfend) D_FUNCPOSTFIT;

/** @brief 设定一个前端设备的参数
* @param hfend  前端设备句柄
* @param param  前段参数
* @retval D_OK  操作成功
* @retval   D_ERR_INVALID_HANDLE        句柄无效
* @retval   D_ERR_INVALID_ARGUMENT  参数 @a param 无效
*/
D_Result    d_fend_set_param (D_HFEnd hfend, D_FEndParam *param, D_FEndFreq lnbfreq) D_FUNCPOSTFIT;

/** @brief 取得一个前端设备是否处于锁定状态
* @param hfend  前端设备句柄
* @retval D_TRUE    前端已经锁定
* @retval D_FALSE   前端没有锁定
*/
D_Bool      d_fend_is_locked (D_HFEnd hfend) D_FUNCPOSTFIT;

/** @brief 取得一个前端设备当前状态
* @param hfend  前端设备句柄
* @param status 前段设备状态结构缓冲区指针
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE      句柄无效
* @retval D_ERR_INVALID_ARGUMENT    status为NULL
*/
D_Result    d_fend_get_status (D_HFEnd hfend, D_FEndStatus *status) D_FUNCPOSTFIT;

/** @brief 取得一个前端设备当前状态
* @param hfend  前端设备句柄
* @param status 前段设备状态结构缓冲区指针
* @retval D_OK  操作成功
* @retval D_ERR_INVALID_HANDLE      句柄无效
* @retval D_ERR_INVALID_ARGUMENT    status为NULL
*/
D_Result    d_fend_get_advance_status (D_HFEnd hfend, D_FEndadvanceStatus *status) D_FUNCPOSTFIT;
/****************
* 通用部分
*****************/
/** @brief 检查两个前端参数是否相同*/
D_Bool  d_fend_param_equal (D_FEndType type, const D_FEndParam *p1, const D_FEndParam *p2) D_FUNCPOSTFIT;
//D_Bool d_fend_param_equal (D_FEndType type, D_FEndParam *p1, D_FEndParam *p2) D_FUNCPOSTFIT;

/** @brief 通过id获得前端设备属性
* @param hfend 前端设备句柄
* @param attr 要获得的前端设备属性
* @retval D_OK  释放成功
*/
D_Result d_fend_get_attr(D_HFEnd hfend, D_FEndAttr *attr) D_FUNCPOSTFIT;

D_FEndBlindResult d_fend_blind_scan(D_HFEnd hfend, D_FEndBlindCmd blindcmd, D_FEndParam *param, D_FBlindParam *blindparam) D_FUNCPOSTFIT;

D_Result d_fend_set_diseqc(D_HFEnd hfend, D_FEndDiSEqC diseqc, D_F22KSTATE f22kstate, D_FEndPol pol) D_FUNCPOSTFIT;
D_Result d_fend_set_pol(D_HFEnd hfend, D_FEndPol pol);
D_Result d_fend_set_22k(D_HFEnd hfend, D_F22KSTATE f22kstate);
/** @brief 设定lnb供电与否*/
D_Result d_fend_set_lnb(D_HFEnd hfend, D_FLNBSTATE lnb) D_FUNCPOSTFIT;

/************************************
注意:不要总是在此宏里增加demod的注册，
这样会增加所有调用过此宏的项目的代码空间，
请在项目project里调用此宏之后添加注册
************************************/
#define d_demod_open_ex()   D_MACRO_BEGIN \
                                d_fend_open_ex();\
                                d_fend_register_hi3205_inside();\
                                d_fend_register_hi3205();\
                                d_fend_register_hi3308();\
                                d_fend_register_hi3111();\
                                d_fend_register_hi3103();\
                                d_fend_register_hi3121();\
                                d_fend_register_MN88473();\
                                d_fend_register_hi3701();\
                                d_fend_register_hi3308E();\
                            D_MACRO_END

D_Result d_fend_open_ex(void) D_FUNCPOSTFIT;

D_Result d_fend_set_tuner_reset(D_HFEnd hfend);
D_Result d_fend_set_tuner_standby(D_HFEnd hfend, D_U8 flag) D_FUNCPOSTFIT;
D_Result d_fend_acquire_tuner(D_HFEnd hfend) D_FUNCPOSTFIT;

D_Result d_fend_release_tuner(D_HFEnd hfend) D_FUNCPOSTFIT;

D_Bool d_fend_is_same_device(D_HFEnd hfend1, D_HFEnd hfend2)D_FUNCPOSTFIT;

D_Result d_fend_register_hi3205_inside(void) D_FUNCPOSTFIT;
D_Result d_fend_register_hi3205(void) D_FUNCPOSTFIT;
D_Result d_fend_register_hi3308(void) D_FUNCPOSTFIT;
D_Result d_fend_register_hi3111(void) D_FUNCPOSTFIT;
D_Result d_fend_register_hi3103(void) D_FUNCPOSTFIT;
D_Result d_fend_register_hi3121(void) D_FUNCPOSTFIT;
D_Result d_fend_register_MN88473(void) D_FUNCPOSTFIT;
D_Result d_fend_register_hi3700(void) D_FUNCPOSTFIT;
D_Result d_fend_register_hi3308_inside(void) D_FUNCPOSTFIT;
D_Result d_fend_register_hi3701(void) D_FUNCPOSTFIT;
D_Result d_fend_register_hi3308E(void) D_FUNCPOSTFIT;
D_Result d_fend_register_hi3701CVBS(void) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif

