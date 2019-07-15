/** @file
* @brief ǰ����豸����
* @author ����
* @date 2005-7-1 ����: �����ļ�
* @date 2013-03-20 lc: ͳһƽ̨, ��������
*/

#ifndef _D_FP_H_
#define _D_FP_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dIO.h"

/** @brief ǰ��尴����ֵ*/
typedef D_U32		D_FPKey;

/** @brief ǰ����״̬*/
typedef D_U8		D_FPStatus;

#define D_FP_STATUS_POWER_ON	0x01	/**< �������Ѽӵ�*/
#define D_FP_STATUS_LOCKED		0x02	/**< ��Ƶͷ�Ѿ�����*/
#define D_FP_STATUS_STANDBY		0x04	/**< �������Ѵ���*/
#define D_FD_STAUS_TIME         0x08   /**<ʱ����ʾ*/
#define D_FD_STAUS_LEDDOT       0x10   /**<LEDС����*/

/** @brief ǰ����豸���*/
typedef D_Handle	D_HFP;

/** @brief ǰ���ص�����*/
typedef void	(*D_FPCallback) (D_HFP hfp, D_FPKey key);

/** @brief ǰ����豸����*/
typedef struct {
	D_ID							id;					/**< �豸ID*/
} D_FPAttr;

/** @brief ��������*/
typedef enum {
	D_KEY_NUL = 0,	/* 0x00�հ��� */
	D_KEY_PNL_L,	/* 0x01ǰ������ */
	D_KEY_PNL_R,	/* 0x02ǰ����Ҽ� */
	D_KEY_CANCEL,	/* 0x03Ctrl+C */
	D_KEY_PNL_U,	/* 0x04ǰ����ϼ� */
	D_KEY_PNL_D,	/* 0x05ǰ����¼� */
	D_KEY_PNL_OK,	/* 0x06ǰ���OK�� */
	D_KEY_PNL_MENU,	/* 0x07ǰ���MENU�� */
	D_KEY_BACK,	/* 0x08���ؼ�*/
	D_KEY_TAB,	/* 0x09*/
	/* reserved*/
	/* reserved */
	D_KEY_CLEAR = 0x0C,/*ASCII���ַ�Ctrl+L��������ʱң������������*/
	D_KEY_OK,	/* 0x0Dȷ�ϼ�*/
	D_KEY_PNL_POWER,	/* 0x0Eǰ���POWER��*/
	D_KEY_PNL_ESC,	/* 0x0Fǰ����˳���*/
	D_KEY_SHIFT,	/* 0x10*/
	D_KEY_CTRL,	/* 0x11*/
	D_KEY_ALT,	/* 0x12*/
	D_KEY_PAUSE,	/* 0x13 ��ͣ,�����ϵİ���*/
	D_KEY_CAPITAL,	/* 0x14*/
	D_KEY_IME,	/* 0x15*/
	D_KEY_PNL_F1,	/* 0x16ǰ���δ֪���ܼ� */
	D_KEY_PNL_F2,	/* 0x17*/
	/* reserved*/
	/* reserved*/
	/* reserved*/
	D_KEY_ESC = 0x1B,	/* 0x1B�˳���*/
	D_KEY_TV_RADIO,	/* 0x1C���ӹ㲥һ����*/
	D_KEY_TV = D_KEY_TV_RADIO,	/* 0x1C���Ӽ�*/
	D_KEY_RADIO = 0x1D,	/* 0x1D�㲥��*/
	D_KEY_SOURCE,	/* 0x1E�л��ź�Դ�� */
	D_KEY_AUDIO,	/* 0x1F����Ƶ�л���ݼ�*/
	D_KEY_SPACE,	/* 0x20*/
	D_KEY_PGUP,	/* 0x21��ҳ*/
	D_KEY_PGDOWN,	/* 0x22��ҳ*/
	D_KEY_END,	/* 0x23*/
	D_KEY_HOME,	/* 0x24*/
	D_KEY_LEFT,	/* 0x25���*/
	D_KEY_UP,	/* 0x26�ϼ�*/
	D_KEY_RIGHT,	/* 0x27�Ҽ�*/
	D_KEY_DOWN,	/* 0x28�¼�*/
	D_KEY_AUD_TRACK,	/* 0x29������*/
	D_KEY_ASTERISK,	/* 0x2A*�ż� */
	D_KEY_ALARM,	/* 0x2B#�ż� */
	D_KEY_SNAPSHOT,	/* 0x2C*/
	D_KEY_INS,	/* 0x2D*/
	D_KEY_DEL,	/* 0x2E*/
	D_KEY_HELP,	/* 0x2F*/
	D_KEY_0,	/* 0x30*/
	D_KEY_1,	/* 0x31*/
	D_KEY_2,	/* 0x32*/
	D_KEY_3,	/* 0x33*/
	D_KEY_4,	/* 0x34*/
	D_KEY_5,	/* 0x35*/
	D_KEY_6,	/* 0x36*/
	D_KEY_7,	/* 0x37*/
	D_KEY_8,	/* 0x38*/
	D_KEY_9,	/* 0x39*/
	D_KEY_RED,	/* 0x3A���*/
	D_KEY_YELLOW,	/* 0x3B�Ƽ�*/
	D_KEY_BLUE,	/* 0x3C����*/
	D_KEY_GREEN,	/* 0x3D�̼�*/
	D_KEY_MENU,	/* 0x3E�˵���*/
	D_KEY_VOLUME_PLUS,	/* 0x3F��Ŀ+*/
	D_KEY_VOLUME_MINUS,	/* 0x40��Ŀ-*/
	D_KEY_A,	/* 0x41*/
	D_KEY_B,	/* 0x42*/
	D_KEY_C,	/* 0x43*/
	D_KEY_D,	/* 0x44*/
	D_KEY_E,	/* 0x45*/
	D_KEY_F,	/* 0x46*/
	D_KEY_G,	/* 0x47*/
	D_KEY_H,	/* 0x48*/
	D_KEY_I,	/* 0x49*/
	D_KEY_J,	/* 0x4A*/
	D_KEY_K,	/* 0x4B*/
	D_KEY_L,	/* 0x4C*/
	D_KEY_M,	/* 0x4D*/
	D_KEY_N,	/* 0x4E*/
	D_KEY_O,	/* 0x4F*/
	D_KEY_P,	/* 0x50*/
	D_KEY_Q,	/* 0x51*/
	D_KEY_R,	/* 0x52*/
	D_KEY_S,	/* 0x53*/
	D_KEY_T,	/* 0x54*/
	D_KEY_U,	/* 0x55*/
	D_KEY_V,	/* 0x56*/
	D_KEY_W,	/* 0x57*/
	D_KEY_X,	/* 0x58*/
	D_KEY_Y,	/* 0x59*/
	D_KEY_Z,	/* 0x5A*/
	D_KEY_FAVOR,	/* 0x5Bϲ��*/
	D_KEY_MUTE,	/* 0x5C����*/
	D_KEY_PROGRAM_PLUS,	/* 0x5D��Ŀ+*/
	D_KEY_PROGRAM_MINUS,	/* 0x5E��Ŀ-*/
	D_KEY_POWER,	/* 0x5F��Դ��*/
	D_KEY_NUM0,	/* 0x60*/
	D_KEY_NUM1,	/* 0x61*/
	D_KEY_NUM2,	/* 0x62*/
	D_KEY_NUM3,	/* 0x63*/
	D_KEY_NUM4,	/* 0x64*/
	D_KEY_NUM5,	/* 0x65*/
	D_KEY_NUM6,	/* 0x66*/
	D_KEY_NUM7,	/* 0x67*/
	D_KEY_NUM8,	/* 0x68*/
	D_KEY_NUM9,	/* 0x69*/
	/* reserved*/
	/* reserved*/
	/* reserved*/
	/* reserved*/
	/* reserved*/
	/* reserved*/
	D_KEY_F1 = 0x70,	/**/
	D_KEY_F2,	/* 0x71*/
	D_KEY_F3,	/* 0x72*/
	D_KEY_F4,	/* 0x73*/
	D_KEY_F5,	/* 0x74*/
	D_KEY_F6,	/* 0x75*/
	D_KEY_F7,	/* 0x76*/
	D_KEY_F8,	/* 0x77*/
	D_KEY_F9,	/* 0x78*/
	D_KEY_F10,	/* 0x79*/
	D_KEY_F11,	/* 0x7A*/
	D_KEY_F12,	/* 0x7B*/
	D_KEY_F13,	/* 0x7C*/
	D_KEY_F14,	/* 0x7D*/
	D_KEY_F15,	/* 0x7E*/
	D_KEY_F16,	/* 0x7F*/
	D_KEY_F17,	/* 0x80*/
	D_KEY_F18,	/* 0x81*/
	D_KEY_F19,	/* 0x82*/
	D_KEY_F20,	/* 0x83*/
	D_KEY_F21,	/* 0x84*/
	D_KEY_F22,	/* 0x85*/
	D_KEY_F23,	/* 0x86*/
	D_KEY_F24,	/* 0x87*/
	D_KEY_LBUTTON,	/* 0x88������ */
	D_KEY_RBUTTON,	/* 0x89����Ҽ� */
	D_KEY_MBUTTON,	/* 0x8A����м� */
	/* reserved*/
	/* reserved*/
	/* reserved*/
	/* reserved*/
	/* reserved*/
	D_KEY_NUMLOCK = 0x90,
	D_KEY_SCROLL,	/* 0x91*/
	D_KEY_VOD,	/* 0x92�㲥*/
	D_KEY_PLAY_STOP,	/* 0x93����/��ͣ */
	D_KEY_FF,	/* 0x94��� */
	D_KEY_REWIND,	/* 0x95���� */
	D_KEY_SCALE,	/* 0x96������� */
	D_KEY_EPG,	/* 0x97��Ŀָ��*/	
	D_KEY_LIST,	/* 0x98Ƶ���б� */
	D_KEY_INFO,	/* 0x99��Ŀ������Ϣ */
	D_KEY_MAIL,	/* 0x9A�ʼ�/����*/
	D_KEY_BROWSER,	/* 0x9B��Ϣ����/���*/
	D_KEY_GAME,	/* 0x9C��Ϸ��*/
	D_KEY_NEXT,	/* 0x9D��һ��*/
	D_KEY_LAST,	/* 0x9E��һ��*/
	D_KEY_MEDIA,	/* 0x9F��ý��*/
	D_KEY_RECORD,	/* 0xA0¼����*/
	D_KEY_TIMERSHIFT,	/* 0xA1ʱ��*/
	D_KEY_TIMER,	/* 0xA2��ʱ��*/
	D_KEY_USB,	/* 0xA3USB��ݼ�*/
	D_KEY_SUBTITLE,	/* 0xA4subtitle���ܼ�*/
	D_KEY_TTX,	/* 0xA5TTX��ݼ�*/
	D_KEY_PROJECT_EXT,	/* 0xA6��ֵΪ��Ŀ����չֵ�����������¹��ܰ������������Ŀ��pFp.h��ӣ�������ӵ����ļ����ƽ̨����ظ�����ȷ��*/
	/* reserved*/
	/* ...... */
	/* reserved*/
	D_KEY_DEADLINE = 0xFF
} D_KeyCode;


/** @brief ��ȱʡ���Գ�ʼ��ǰ����豸����*/
#define D_FP_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief ǰ���ϵͳ��ʼ���ṹ */
typedef struct
{
    D_GPIO_PortBit clock;    /**< ʱ�� */
    D_GPIO_PortBit data;     /**< ���� */
    D_GPIO_PortBit key_in;      /***<��ȡ����*/
    D_GPIO_PortBit stb;          /**<1642�����ƿ���/1658����*/
    D_U8 front_type;
    D_U8 data_a;   /**<�����A��**/
    D_U8 data_b; 
    D_U8 data_c; 
    D_U8 data_d; 
    D_U8 data_e; 
    D_U8 data_f; 
    D_U8 data_g; 
    D_U8 data_h;  /**<�����H*/
	D_U8 data_time1;  /**<��ʾʱ��*/
	D_U8 data_time2;  /**<��ʾʱ��*/
    D_U8 led_locked;  /**<tuner������*/
    D_U8 led_dot;     /**<led-dotѡ��*/
    D_U16 led_dig0;
    D_U16 led_dig1;
    D_U16 led_dig2;
    D_U16 led_dig3;
    D_U8  led_locked_polarity; /**<tuner�����Ƽ��ԣ�0�͵�ƽ����1�ߵ�ƽ��*/
    D_U8  led_standby_polarity; /**<�����Ƽ��ԣ�0�͵�ƽ����1�ߵ�ƽ��*/
}D_FpOpenParam;

/** @brief ǰ���ϵͳ��ʼ���ṹ */
typedef struct
{
    D_U8  led_locked_polarity; /**<tuner�����Ƽ��ԣ�0�͵�ƽ����1�ߵ�ƽ��*/
    D_U8  led_standby_polarity; /**<�����Ƽ��ԣ�0�͵�ƽ����1�ߵ�ƽ��*/
}D_FpInitOpenParam;


/** @brief ǰ��尴����ӳ�乳�ӽṹ */
typedef struct
{
	D_FPKey source_code;
	D_FPKey mapped_key;
}D_FPMapHookParam;

extern D_KeyCode mapped_key_fp[10];
/** @brief ǰ���ϵͳ��ʼ��
*
*	�ڵ���ǰ����������ʱ���ȵ��ô˺���
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result	d_fp_open (D_FpOpenParam *param) D_FUNCPOSTFIT;

/** @brief ǰ���ϵͳ��ֹ
*
* �������ʱ���ͷ�ǰ���ϵͳ�ڵ���Դ
* @retval D_OK	�����ɹ�
* @retval D_ERR	����ʧ��
*/
D_Result	d_fp_close (void) D_FUNCPOSTFIT;

/** @brief ����һ��ǰ����豸
* @param attr	ǰ����豸���Խṹָ�룬ΪNULLʱʹ��ȱʡֵ(id=0)
* @return �ɹ�ʱ����ǰ����豸�����ʧ�ܷ���D_INVALID_HANDLE
*/
D_HFP			d_fp_create (D_FPAttr *attr) D_FUNCPOSTFIT;

/** @brief ����һ��ǰ����豸
* @param hfp ǰ����豸���
* @retval D_OK	�ͷųɹ�
* @retval	D_ERR_INVALID_HANDLE	�����Ч
*/
D_Result	d_fp_destroy (D_HFP hfp) D_FUNCPOSTFIT;

/** @brief ����ǰ���4λ����LED��ʾ
* @param hfp 	ǰ����豸���
* @param led	4�ַ����ַ���,Ҫ��ʾ������
* @retval D_OK	�����ɹ�
* @retval	D_ERR_INVALID_HANDLE		�����Ч
* @retval	D_ERR_INVALID_ARGUMENT	������Ч
*/
D_Result	d_fp_set_led (D_HFP hfp, D_Char *led) D_FUNCPOSTFIT;

/** @brief ����ǰ���״̬����ʾ
* @param hfp 	ǰ����豸���
* @param status	ǰ���״̬
* @retval D_OK	�����ɹ�
* @retval	D_ERR_INVALID_HANDLE		�����Ч
* @retval	D_ERR_INVALID_ARGUMENT	������Ч
*/
D_Result	d_fp_set_status (D_HFP hfp, D_FPStatus status, D_FPStatus mask) D_FUNCPOSTFIT;

/** @brief ȡǰ��尴����Ϣ
* @param callback	ǰ��尴���ص�����
* @param old	��žɵĻص�����
* @retval D_OK	�����ɹ�
* @retval	D_ERR_INVALID_ARGUMENT	������Ч
*/
D_Result	d_fp_register_callback (D_FPCallback callback, D_FPCallback *old) D_FUNCPOSTFIT;

/** @breif ȡ�õ�ǰ����
* @param key	���ذ�����ֵ
* @retval D_OK	�����ɹ�
* @retval D_ERR_EMPTY		û�а�������
*/
D_Result  d_fp_poll_key (D_FPKey *key) D_FUNCPOSTFIT;
D_Result  d_fp_open_ex (void) D_FUNCPOSTFIT;
D_Result  d_fp_open_ex_new (D_FpInitOpenParam *param) D_FUNCPOSTFIT;
void  d_PowerOff_Led_Ctrl(D_U8 ctrl_en);
void  d_fp_led_turn_off (void) D_FUNCPOSTFIT;
void  d_fp_led_standby_show(void) D_FUNCPOSTFIT;
void  d_fp_Led_g_Ctrl(D_U8 ctrl_en);
void d_fp_set_rckey_mode(D_U8 mode) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
