/** @file
* @brief ǰ���豸����
* @author ����
* @date 2005-5-16 ����: �����ļ�
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


/** @brief ǰ���豸���*/
typedef D_Handle    D_HFEnd;


// need detail information from ���˽�
#define KU_SWITCH_FREQ  11750
#define C_SWITCH_FREQ       3600
#define OSC_ABOVE_IS_KU 9000
#define OSC_BELOW_IS_C  6000



typedef enum
{
    demod_3205_inside,//HI2309Ƭ���Դ�HI3205
    demod_3205_outside,//оƬ���HI3205
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

/** @brief ǰ������*/
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
    D_FEND_AtvDem,				// ATV���    
    D_FEND_AvCvbsDc,			// ��ƵCVBS-ֱ����ϣ�ģ��ǯλ��
    D_FEND_AvCvbsAcNormal,		// ��ƵCVBS-������ϣ���ƽ������    
    D_FEND_AvCvbsAcInvert,		// ��ƵCVBS-������ϣ���ƽ������
} D_FEndWorkMode; //����CVBS�źŵ�ģʽ

/** @brief �û����tuner���� */
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
    D_U8 agc_polarity;  /**< AGC���� */
    D_U8 psd_polarity;  /**< �����׼��� */
    D_U8 mode;  /**< ����ģʽ, ��3121�Ĺ㲥����ģʽѡ�� */
    D_U8 led_polarity;  /**< LED���� */
    D_U8 iic_bus_repeat_sel;  /**< ѡ���ĸ����ת��I2C */
    D_U8 diseqc_22k_sel;  /**< ѡ���ĸ��������diseqc��22K */
    D_U8 tuner_sel;  /**< ռ�õ�tuner����, ���ڶ���������tunerʶ��  */
    D_U8 idle_action  /**< �������ʱ����, 0:GPIO����, 1:����״̬, ����ֵ������ */;
	D_U8 adc; /*ѡ��ADC Դ*/
} D_FEndConfigParam;

typedef D_FEndConfigParam D_DemoOpenParam;

/** @brief ���Ʒ�ʽ*/
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

/** @brief ����*/
typedef enum
{
    D_FEND_6MHZ,
    D_FEND_7MHZ,
    D_FEND_8MHZ,
    D_FEND_5MHZ,
    D_FEND_2MHZ,
    D_FEND_1_7MHZ,
} D_FEndBandWidth;

/** @brief ������ʽ*/
typedef enum
{
    D_FEND_HOR_POL,
    D_FEND_VER_POL,
    D_FEND_LEFT_POL,
    D_FEND_RIGHT_POL,
    D_FEND_POL
} D_FEndPol;

//��hi3701���Ӧ�İ���ϵͳ��ʽ
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

/** @brief ģ�������Ƶ��ʽ*/

typedef enum
{
    D_VideoP,       /* PAL  */
    D_VideoN,   /* NTSC */
    D_VideoSECAM,                       /* SECAM */
    D_VideoMax,                             /* SECAM */
} D_VideoMode;

/** @brief ģ�������Ƶ��ʽ*/
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


/** @brief ���Ʒ�ʽ*/
typedef enum
{
    D_FEND_DTMB_INFO,
    D_FEND_DTMB_DETAIL_INFO,
    D_FEND_DTMB_HN_INFO,
    D_FEND_DTMB_CARRIER_FREQ_INFO,
    D_FEND_DTMB_FREQ_INFO
} D_FEndadvanceStatusType;
/** @brief Ƶ��(HZ)*/
typedef D_U32   D_FEndFreq;

/** @brief ������(BPS)*/
typedef D_U32   D_FEndBaud;

/** @brief ����()*/
typedef D_U16   D_FEndBandWitch;

/** @brief 22K״̬*/
typedef enum
{
    D_F22KOff = 0,      // 22K�أ���ȷ״̬
    D_F22KOn,       // 22K������ȷ״̬
    D_F22KNone, // ������22K״̬
    D_F22KAuto = D_F22KNone,// ������22K״̬
} D_F22KSTATE;

typedef enum
{
    D_LNB_OFF,
    D_LNB_ON,
} D_FLNBSTATE;

/** @brief DISEQC �汾(����)*/
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

/** @brief DISEQC �˿�*/
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


// ���õģ�����Ӧ�õ�diseqc1.2/1.3������
typedef enum
{
    D_MOTOR_GOTO_NN,            // ת��Ԥ��λ��
    D_MOTOR_MOVE_EAST,      // ���������ƶ����
    D_MOTOR_MOVE_WEST,      // ���������ƶ����
    D_MOTOR_HALT,               // ʹ���ֹͣ�ƶ�
    D_MOTOR_STOR_NN,        // ����λ��
    D_MOTOR_LIMIT_EAST,     // ����������ƶ�����
    D_MOTOR_LIMIT_WEST,     // ������������ƶ�����
    D_MOTOR_LIMIT_OFF,      // ȡ������
    D_MOTOR_RECALCULATION,      // У׼���
    D_MOTOR_GOTO_ORIGINAL,  // �ص�ԭ��
    D_MOTOR_STEP_EAST,      // �򶫲������
    D_MOTOR_STEP_WEST,      // �����������
    D_MOTOR_GOTO_AZIMUTH,       // ʹ���ƫ��һ���ĽǶ�/    D_MOTOR_RAW_CMD,                // ֱ�ӿ���DiSEqC1.2����ﶯ��
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

/*DVBT2Э�����ź�����*/
typedef enum
{
    D_FEND_T2_TYPE_DVBT = 0, /**<DVBT*/
    D_FEND_T2_TYPE_DVBT2 = 1, /**< DVBT2*/
} D_FEndDvbt2Type;

/*DVBT2Э����tuner��Ƶģʽ*/
typedef enum
{
    D_FEND_T2_MODE_NORMAL = 0, /**< ����ȷ������Ƶģʽ��һ�����ڲ��Ž�Ŀʱ��Ƶ*/
    D_FEND_T2_MODE_AUTO = 1,    /**< ����Ӧ��Ƶ���������������ֱ�����������*/
    D_FEND_T2_MODE_SCAN = 2, /**< ������Ƶģʽ��һ������������Ŀʱ��һ����Ƶ��ȡ�����Ϣ*/
} D_FEndDvbt2Mode;

/*DVBT2Э���¹̶��ƶ���־*/
typedef enum
{
    D_FEND_T2_MOBILE_BASE = 0, /**< �̶�*/
    D_FEND_T2_MOBILE_LITE = 1, /**< �ƶ�*/
    D_FEND_T2_MOBILE_AUTO = 2, /**< �Զ�*/
} D_FEndDvbt2Mobile;

/** @brief ǰ�����ò���*/
// 2013-3-18 ����ǰ�˲������壬��abs��dvbs/dvbs2�ϲ���һ��by wy
typedef union
{
		/*��Ԫ��freq�Ƶ����棬����D_FEndParam p = {0}�ܽ����е�byteΪ0, @qiny 20150721*/
		//D_FEndFreq	freq;			/**< Ƶ��*/	
    struct
    {
        D_FEndFreq      freq;   /**< Ƶ��*/
        D_FEndBaud      baud;   /**< ������*/
        D_U16       mod;    /**< ���Ʒ�ʽ*/
        D_U16           freq_k; /*100k*/
    } dvbc;                     /**< DVB-C����*/
    struct
    {
        D_FEndFreq      freq;   /**< Ƶ��*/
        D_FEndBandWitch BandWidth; /**< ����*/
    } dvbt;                     /**< DVB-T����*/
    struct
    {
        D_FEndFreq      freq;   /**< Ƶ��*/
        D_U16              BandWidth; /**< ����*/
        D_U8                 type;        /**< �ź�����0 dvbt , 1 dvbt2*/
        D_U8            PLPID;  /**< PLP��*/
        D_U8            mobile; /**< 0 : �̶���1: �ƶ���2:�Զ�*/
        D_U8                 mode;        /**< ��Ƶ��ʽ0: ������ȷ��1: ģ������(��������)*/
    } dvbt2;                                    /**< DVB-T2����*/
    struct
    {
        D_FEndFreq      freq;   /**< Ƶ��*/
		D_U16	        BandWidth; /**< ����*/	
		D_U16           placeholder0;/*С�ˣ�ԭ������Ŀ���õ���Ƶ�㶼����dvbc�Ľṹ��洢�ģ�Ϊ�˱���mod��Ӱ�죬ʹ��ռλ�����Ժ���Ը���ʹ�� @qiny2015.07.07*/
		D_U16           placeholder1;/*ռλ��*/
		D_U16           freq_k; /*100k*/
    } dtmb;
    struct
    {
        D_FEndFreq      freq;   /**< Ƶ��*/
        D_FEndBaud      baud;   /**< ������*/
        D_FEndPol       pol;    /**< ������ʽ*/
    } abs;                      /**< ABS����*/
    struct
    {
        D_FEndFreq      freq;   /**< Ƶ��*/
        D_FEndBaud      baud;   /**< ������*/
        D_FEndPol       pol;    /**< ������ʽ*/
    } dvbs;                     /**< dvbs/s2���ô˲���*/
    struct
    {
        D_FEndFreq  freq;           /* kHz */
        D_U8    videoMode;      /* Video Mode */
        D_U8    audioMode;      /* Audio Mode */
        D_U8    SoundSys;		/**������ʽ  FmMono**/
		D_U8    mode;       	/* kHz */
				D_S8	fltCenterAdj; 	/* kHz */
				D_S8	fltBwAdj;				
    } atv;
	struct
    {
        D_U8      workmode;   /**< ����ģʽ*/
    } cvbs; 
		D_FEndFreq	freq;			/**< Ƶ��*/	
} D_FEndParam;

/** @diseqc������Ϣ*/
typedef struct
{
    D_FDiSEqCType  diseqc_type;  /**<diseqc �汾(����)*/
    //diseqc1.0/1.1 port
    D_FDiSEqCPort   diseqc_port; /**<diseqc 1.0/1.1 �˿�*/
    //diseqc1.2  position ( nn_value / x )
    D_U8    position_no;                     /**<diseqc1.2 ��λ*/
    //diseqc1.3 (usals)
    D_S16  local_longitude;   /**<diseqc1.3 (usals) ���ؾ���(-18000 ~ 18000)*/
    D_S16  local_latitude;      /**<diseqc1.3 (usals) ����γ��(-9000~ 9000)*/
    D_S16  sate_longitude;    /**<diseqc1.3 (usals) ���Ǿ���(-18000 ~ 18000)*/
} D_FEndDiseqcInfo;

/** @LNB��ز���*/
typedef struct
{
    D_FEndFreq          lnbfreq1;       /**<����Ƶ��1*/
    D_FEndFreq          lnbfreq2;       /**<����Ƶ��2*/
    D_F22KSTATE     f22k_state;     /**<22K����״̬*/
    D_FEndPol          pol_state;       /**<����״̬*/
    D_Bool              power_en;       /**<�Ƿ�������*/
    D_FEndDiseqcInfo diseqc_info; /**<diseqc������Ϣ*/
} D_FEndLnbInfo;


// äɨģʽ
typedef enum
{
    D_FEND_START,
    D_FEND_LAST,
    D_FEND_CONTINUE,
    D_FEND_LAST_CONTINUE,
	D_FEND_STOP		
} D_FEndBlindCmd;

// ����äɨ��ʽ���壬Ӧ�ò㶨������Щ��ʽ����������һ���ܹ�ʵ�֣�
// ����������֧�ֵķ�ʽ����Ҫ������ֶ���Э��
typedef enum
{
    D_FEND_BLIND_SCAN_INTERACTIVE,      /*ɨ�赽Ƶ��Ȼ��������Ŀ*/
    D_FEND_BLIND_SCAN_BY_SEGMENT,   /*�ֶ�ɨ��*/
    D_FEND_BLIND_SCAN_MONOLITHIC,   /*һ����ɨ������������*/
} D_FEndBlindScanType;

// äɨʹ�ò���
typedef struct
{
    D_U8             lnb_type;  /**<SINGLE /C_DOUBLE / KU_DOUBLE*/
    D_FEndFreq       lnbfreq1;  /**<����Ƶ��1*/
    D_FEndFreq       lnbfreq2;   /**<����Ƶ��2*/
    D_FEndFreq       startfreq;  /**<��ʼƵ��MHZ*/
    D_FEndBandWitch  bandwidth;  /**<����MHZ*/
    D_FEndPol        pol;   /**< ������ʽ*/
    D_F22KSTATE     f22kstate;
    D_FEndDiseqcInfo    diseqc;
    D_Ptr           ptr;
	D_FEndFreq       stopfreq;  /**<��ֹƵ��MHZ*/ 
} D_FBlindParam;


// äɨ����
typedef enum
{
    D_FEND_START_OK,
    D_FEND_START_ERROR,
    D_FEND_CONTINUE_OK,
    D_FEND_END_OK,
	D_FEND_STOP_OK
} D_FEndBlindResult;

// äɨ��׽��Ƶ��������壬������׽���������γ�����
typedef struct __D_FBlindTpItem
{
    D_FEndParam param;
    struct __D_FBlindTpItem *next;
} D_FBlindTpItem;

// äɨ��׽��Ƶ��������壬���������򷵻�
typedef struct
{
    D_Int count;                    // Ƶ�����
    D_FEndType type;                // ǰ������
    D_FBlindTpItem *tplist;     // Ƶ���б�
} D_FBlindTpList;

/*dvbt2��Ƶ�����������*/
typedef struct
{
    D_U8        type;        /**< �ź�����0 dvbt , 1 dvbt2*/
    D_U32      freq;        /**< Ƶ��*/
    D_U16       bw;         /**<����MHZ*/
    D_U16      PLP_cnt;  /**< ����ʱPLP����*/
    D_U8        PLP_id;         /**<ʵ��PLP ID*/
    D_U8        mobile; /**< 0 : �̶���1: �ƶ���2:�Զ�*/
} D_FEndDvbt2Info;


/** @brief ǰ��״̬*/
typedef struct
{
    D_Bool  locked;         /**< �Ƿ���ס*/
    D_U8        strength;       /**< �ź�ǿ��*/
    D_U8        quanlity;       /**< �ź�����*/
    D_U8    diseqc_set_result;
    D_U8     ber;
    D_U8     fec;
    D_Ptr     ptr;                  /**< T2ʱ���ڼ�¼D_FEndDvbt2Info���ݵ�ָ��*/
	D_S32	offset;					/**< ANALOGʱ���ڼ�¼freq offset*/
} D_FEndStatus;

/** @brief ǰ��״̬�߼��ӿ�*/
typedef struct
{
    D_FEndadvanceStatusType type;       /**< Ҫ��ȡ����Ϣ����*/
    D_U8        *Statusinfo;        /**< ��ȡ��Ϣͷָ��*/
    D_U32       Statusinfolength;       /**< ��ȡ��Ϣ����*/
} D_FEndadvanceStatus;

/** @brief ǰ���豸����*/
typedef struct
{
    DemodType_t demod;
    D_FEndType type;        /**< ǰ������*/
    D_ID id;            /**< ǰ���豸ID*/
} D_FEndAttr;


/** @brief ��ȱʡ���ó�ʼ��ǰ���豸����*/
#define D_FEND_ATTR_INIT(_a)\
    D_MACRO_BEGIN\
        (_a)->type = D_FEND_DVBC;\
        (_a)->id = 0;\
        (_a)->demod = demod_max;\
    D_MACRO_END

/** @brief ����Ƶ�豸�¼����� */
typedef struct
{
    DemodType_t tuner_type;
    D_FEndFreq freq;
    D_Ptr param;
} D_FEndEventParam;

typedef D_Result (*DFENDPLLCALLBACK)(DemodType_t tuner_type,D_FEndFreq freq);
void d_pll_jam_patchcb(DFENDPLLCALLBACK cb)D_FUNCPOSTFIT;
/** @brief ǰ��ϵͳ��ʼ��
*
*   �ڵ���ǰ�˲�������ʱ���ȵ��ô˺���
* @retval D_OK  ��ʼ���ɹ�
* @retval D_ERR ��ʼ��ʧ��
*/
D_Result    d_fend_open (D_DemoOpenParam *param) D_FUNCPOSTFIT;

/** @brief ǰ�ι���ϵͳ��ֹ
*
* �������ʱ���ͷ�ǰ��ϵͳ�ڵ���Դ
* @retval D_OK  �����ɹ�
* @retval D_ERR ����ʧ��
*/
D_Result    d_fend_close (void) D_FUNCPOSTFIT;

/** @brief ����һ��ǰ���豸
* @param attr   ǰ���豸���Խṹָ�룬ΪNULLʱʹ��ȱʡֵ
* @return �ɹ�ʱ����ǰ���豸�����ʧ�ܷ���D_INVALID_HANDLE
*/
D_HFEnd     d_fend_create (D_FEndAttr *attr) D_FUNCPOSTFIT;

/** @brief ����һ��ǰ���豸
* @param hfend ǰ���豸���
* @retval D_OK  �ͷųɹ�
* @retval   D_ERR_INVALID_HANDLE    �����Ч
*/
D_Result    d_fend_destroy (D_HFEnd hfend) D_FUNCPOSTFIT;

/** @brief �趨һ��ǰ���豸�Ĳ���
* @param hfend  ǰ���豸���
* @param param  ǰ�β���
* @retval D_OK  �����ɹ�
* @retval   D_ERR_INVALID_HANDLE        �����Ч
* @retval   D_ERR_INVALID_ARGUMENT  ���� @a param ��Ч
*/
D_Result    d_fend_set_param (D_HFEnd hfend, D_FEndParam *param, D_FEndFreq lnbfreq) D_FUNCPOSTFIT;

/** @brief ȡ��һ��ǰ���豸�Ƿ�������״̬
* @param hfend  ǰ���豸���
* @retval D_TRUE    ǰ���Ѿ�����
* @retval D_FALSE   ǰ��û������
*/
D_Bool      d_fend_is_locked (D_HFEnd hfend) D_FUNCPOSTFIT;

/** @brief ȡ��һ��ǰ���豸��ǰ״̬
* @param hfend  ǰ���豸���
* @param status ǰ���豸״̬�ṹ������ָ��
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE      �����Ч
* @retval D_ERR_INVALID_ARGUMENT    statusΪNULL
*/
D_Result    d_fend_get_status (D_HFEnd hfend, D_FEndStatus *status) D_FUNCPOSTFIT;

/** @brief ȡ��һ��ǰ���豸��ǰ״̬
* @param hfend  ǰ���豸���
* @param status ǰ���豸״̬�ṹ������ָ��
* @retval D_OK  �����ɹ�
* @retval D_ERR_INVALID_HANDLE      �����Ч
* @retval D_ERR_INVALID_ARGUMENT    statusΪNULL
*/
D_Result    d_fend_get_advance_status (D_HFEnd hfend, D_FEndadvanceStatus *status) D_FUNCPOSTFIT;
/****************
* ͨ�ò���
*****************/
/** @brief �������ǰ�˲����Ƿ���ͬ*/
D_Bool  d_fend_param_equal (D_FEndType type, const D_FEndParam *p1, const D_FEndParam *p2) D_FUNCPOSTFIT;
//D_Bool d_fend_param_equal (D_FEndType type, D_FEndParam *p1, D_FEndParam *p2) D_FUNCPOSTFIT;

/** @brief ͨ��id���ǰ���豸����
* @param hfend ǰ���豸���
* @param attr Ҫ��õ�ǰ���豸����
* @retval D_OK  �ͷųɹ�
*/
D_Result d_fend_get_attr(D_HFEnd hfend, D_FEndAttr *attr) D_FUNCPOSTFIT;

D_FEndBlindResult d_fend_blind_scan(D_HFEnd hfend, D_FEndBlindCmd blindcmd, D_FEndParam *param, D_FBlindParam *blindparam) D_FUNCPOSTFIT;

D_Result d_fend_set_diseqc(D_HFEnd hfend, D_FEndDiSEqC diseqc, D_F22KSTATE f22kstate, D_FEndPol pol) D_FUNCPOSTFIT;
D_Result d_fend_set_pol(D_HFEnd hfend, D_FEndPol pol);
D_Result d_fend_set_22k(D_HFEnd hfend, D_F22KSTATE f22kstate);
/** @brief �趨lnb�������*/
D_Result d_fend_set_lnb(D_HFEnd hfend, D_FLNBSTATE lnb) D_FUNCPOSTFIT;

/************************************
ע��:��Ҫ�����ڴ˺�������demod��ע�ᣬ
�������������е��ù��˺����Ŀ�Ĵ���ռ䣬
������Ŀproject����ô˺�֮�����ע��
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

