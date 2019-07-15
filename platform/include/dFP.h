/** @file
* @brief 前面板设备操作
* @author 龚克
* @date 2005-7-1 龚克: 建立文件
* @date 2013-03-20 lc: 统一平台, 代码整理
*/

#ifndef _D_FP_H_
#define _D_FP_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dIO.h"

/** @brief 前面板按键键值*/
typedef D_U32		D_FPKey;

/** @brief 前面板灯状态*/
typedef D_U8		D_FPStatus;

#define D_FP_STATUS_POWER_ON	0x01	/**< 机顶盒已加电*/
#define D_FP_STATUS_LOCKED		0x02	/**< 高频头已经锁定*/
#define D_FP_STATUS_STANDBY		0x04	/**< 机顶盒已待机*/
#define D_FD_STAUS_TIME         0x08   /**<时间显示*/
#define D_FD_STAUS_LEDDOT       0x10   /**<LED小数点*/

/** @brief 前面板设备句柄*/
typedef D_Handle	D_HFP;

/** @brief 前面板回调函数*/
typedef void	(*D_FPCallback) (D_HFP hfp, D_FPKey key);

/** @brief 前面板设备属性*/
typedef struct {
	D_ID							id;					/**< 设备ID*/
} D_FPAttr;

/** @brief 按键定义*/
typedef enum {
	D_KEY_NUL = 0,	/* 0x00空按键 */
	D_KEY_PNL_L,	/* 0x01前面板左键 */
	D_KEY_PNL_R,	/* 0x02前面板右键 */
	D_KEY_CANCEL,	/* 0x03Ctrl+C */
	D_KEY_PNL_U,	/* 0x04前面板上键 */
	D_KEY_PNL_D,	/* 0x05前面板下键 */
	D_KEY_PNL_OK,	/* 0x06前面板OK键 */
	D_KEY_PNL_MENU,	/* 0x07前面板MENU键 */
	D_KEY_BACK,	/* 0x08返回键*/
	D_KEY_TAB,	/* 0x09*/
	/* reserved*/
	/* reserved */
	D_KEY_CLEAR = 0x0C,/*ASCII码字符Ctrl+L，无需求时遥控器不用配置*/
	D_KEY_OK,	/* 0x0D确认键*/
	D_KEY_PNL_POWER,	/* 0x0E前面板POWER键*/
	D_KEY_PNL_ESC,	/* 0x0F前面板退出键*/
	D_KEY_SHIFT,	/* 0x10*/
	D_KEY_CTRL,	/* 0x11*/
	D_KEY_ALT,	/* 0x12*/
	D_KEY_PAUSE,	/* 0x13 暂停,键盘上的按键*/
	D_KEY_CAPITAL,	/* 0x14*/
	D_KEY_IME,	/* 0x15*/
	D_KEY_PNL_F1,	/* 0x16前面板未知功能键 */
	D_KEY_PNL_F2,	/* 0x17*/
	/* reserved*/
	/* reserved*/
	/* reserved*/
	D_KEY_ESC = 0x1B,	/* 0x1B退出键*/
	D_KEY_TV_RADIO,	/* 0x1C电视广播一个键*/
	D_KEY_TV = D_KEY_TV_RADIO,	/* 0x1C电视键*/
	D_KEY_RADIO = 0x1D,	/* 0x1D广播键*/
	D_KEY_SOURCE,	/* 0x1E切换信号源键 */
	D_KEY_AUDIO,	/* 0x1F多音频切换快捷键*/
	D_KEY_SPACE,	/* 0x20*/
	D_KEY_PGUP,	/* 0x21上页*/
	D_KEY_PGDOWN,	/* 0x22下页*/
	D_KEY_END,	/* 0x23*/
	D_KEY_HOME,	/* 0x24*/
	D_KEY_LEFT,	/* 0x25左键*/
	D_KEY_UP,	/* 0x26上键*/
	D_KEY_RIGHT,	/* 0x27右键*/
	D_KEY_DOWN,	/* 0x28下键*/
	D_KEY_AUD_TRACK,	/* 0x29声道键*/
	D_KEY_ASTERISK,	/* 0x2A*号键 */
	D_KEY_ALARM,	/* 0x2B#号键 */
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
	D_KEY_RED,	/* 0x3A红键*/
	D_KEY_YELLOW,	/* 0x3B黄键*/
	D_KEY_BLUE,	/* 0x3C蓝键*/
	D_KEY_GREEN,	/* 0x3D绿键*/
	D_KEY_MENU,	/* 0x3E菜单键*/
	D_KEY_VOLUME_PLUS,	/* 0x3F节目+*/
	D_KEY_VOLUME_MINUS,	/* 0x40节目-*/
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
	D_KEY_FAVOR,	/* 0x5B喜爱*/
	D_KEY_MUTE,	/* 0x5C静音*/
	D_KEY_PROGRAM_PLUS,	/* 0x5D节目+*/
	D_KEY_PROGRAM_MINUS,	/* 0x5E节目-*/
	D_KEY_POWER,	/* 0x5F电源键*/
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
	D_KEY_LBUTTON,	/* 0x88鼠标左键 */
	D_KEY_RBUTTON,	/* 0x89鼠标右键 */
	D_KEY_MBUTTON,	/* 0x8A鼠标中键 */
	/* reserved*/
	/* reserved*/
	/* reserved*/
	/* reserved*/
	/* reserved*/
	D_KEY_NUMLOCK = 0x90,
	D_KEY_SCROLL,	/* 0x91*/
	D_KEY_VOD,	/* 0x92点播*/
	D_KEY_PLAY_STOP,	/* 0x93播放/暂停 */
	D_KEY_FF,	/* 0x94快进 */
	D_KEY_REWIND,	/* 0x95快退 */
	D_KEY_SCALE,	/* 0x96画面比例 */
	D_KEY_EPG,	/* 0x97节目指南*/	
	D_KEY_LIST,	/* 0x98频道列表 */
	D_KEY_INFO,	/* 0x99节目参数信息 */
	D_KEY_MAIL,	/* 0x9A邮件/信箱*/
	D_KEY_BROWSER,	/* 0x9B信息服务/浏览*/
	D_KEY_GAME,	/* 0x9C游戏键*/
	D_KEY_NEXT,	/* 0x9D下一首*/
	D_KEY_LAST,	/* 0x9E上一首*/
	D_KEY_MEDIA,	/* 0x9F多媒体*/
	D_KEY_RECORD,	/* 0xA0录放像*/
	D_KEY_TIMERSHIFT,	/* 0xA1时移*/
	D_KEY_TIMER,	/* 0xA2定时器*/
	D_KEY_USB,	/* 0xA3USB快捷键*/
	D_KEY_SUBTITLE,	/* 0xA4subtitle功能键*/
	D_KEY_TTX,	/* 0xA5TTX快捷键*/
	D_KEY_PROJECT_EXT,	/* 0xA6此值为项目层扩展值，后续如有新功能按键添加请在项目层pFp.h添加，如需添加到此文件须和平台层相关负责人确认*/
	/* reserved*/
	/* ...... */
	/* reserved*/
	D_KEY_DEADLINE = 0xFF
} D_KeyCode;


/** @brief 按缺省属性初始化前面板设备属性*/
#define D_FP_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->id = 0;\
	D_MACRO_END

/** @brief 前面板系统初始化结构 */
typedef struct
{
    D_GPIO_PortBit clock;    /**< 时钟 */
    D_GPIO_PortBit data;     /**< 数据 */
    D_GPIO_PortBit key_in;      /***<获取按键*/
    D_GPIO_PortBit stb;          /**<1642锁定灯控制/1658控制*/
    D_U8 front_type;
    D_U8 data_a;   /**<数码管A段**/
    D_U8 data_b; 
    D_U8 data_c; 
    D_U8 data_d; 
    D_U8 data_e; 
    D_U8 data_f; 
    D_U8 data_g; 
    D_U8 data_h;  /**<数码管H*/
	D_U8 data_time1;  /**<显示时间*/
	D_U8 data_time2;  /**<显示时间*/
    D_U8 led_locked;  /**<tuner锁定灯*/
    D_U8 led_dot;     /**<led-dot选择*/
    D_U16 led_dig0;
    D_U16 led_dig1;
    D_U16 led_dig2;
    D_U16 led_dig3;
    D_U8  led_locked_polarity; /**<tuner锁定灯极性，0低电平亮，1高电平亮*/
    D_U8  led_standby_polarity; /**<待机灯极性，0低电平亮，1高电平亮*/
}D_FpOpenParam;

/** @brief 前面板系统初始化结构 */
typedef struct
{
    D_U8  led_locked_polarity; /**<tuner锁定灯极性，0低电平亮，1高电平亮*/
    D_U8  led_standby_polarity; /**<待机灯极性，0低电平亮，1高电平亮*/
}D_FpInitOpenParam;


/** @brief 前面板按键重映射钩子结构 */
typedef struct
{
	D_FPKey source_code;
	D_FPKey mapped_key;
}D_FPMapHookParam;

extern D_KeyCode mapped_key_fp[10];
/** @brief 前面板系统初始化
*
*	在调用前面板操作函数时首先调用此函数
* @retval D_OK	初始化成功
* @retval D_ERR	初始化失败
*/
D_Result	d_fp_open (D_FpOpenParam *param) D_FUNCPOSTFIT;

/** @brief 前面板系统中止
*
* 程序结束时，释放前面板系统内的资源
* @retval D_OK	操作成功
* @retval D_ERR	操作失败
*/
D_Result	d_fp_close (void) D_FUNCPOSTFIT;

/** @brief 创建一个前面板设备
* @param attr	前面板设备属性结构指针，为NULL时使用缺省值(id=0)
* @return 成功时返回前面板设备句柄，失败返回D_INVALID_HANDLE
*/
D_HFP			d_fp_create (D_FPAttr *attr) D_FUNCPOSTFIT;

/** @brief 销毁一个前面板设备
* @param hfp 前面板设备句柄
* @retval D_OK	释放成功
* @retval	D_ERR_INVALID_HANDLE	句柄无效
*/
D_Result	d_fp_destroy (D_HFP hfp) D_FUNCPOSTFIT;

/** @brief 设置前面板4位数码LED显示
* @param hfp 	前面板设备句柄
* @param led	4字符的字符串,要显示的内容
* @retval D_OK	操作成功
* @retval	D_ERR_INVALID_HANDLE		句柄无效
* @retval	D_ERR_INVALID_ARGUMENT	参数无效
*/
D_Result	d_fp_set_led (D_HFP hfp, D_Char *led) D_FUNCPOSTFIT;

/** @brief 设置前面板状态灯显示
* @param hfp 	前面板设备句柄
* @param status	前面板状态
* @retval D_OK	操作成功
* @retval	D_ERR_INVALID_HANDLE		句柄无效
* @retval	D_ERR_INVALID_ARGUMENT	参数无效
*/
D_Result	d_fp_set_status (D_HFP hfp, D_FPStatus status, D_FPStatus mask) D_FUNCPOSTFIT;

/** @brief 取前面板按键消息
* @param callback	前面板按键回调函数
* @param old	存放旧的回调函数
* @retval D_OK	操作成功
* @retval	D_ERR_INVALID_ARGUMENT	参数无效
*/
D_Result	d_fp_register_callback (D_FPCallback callback, D_FPCallback *old) D_FUNCPOSTFIT;

/** @breif 取得当前按键
* @param key	返回按键键值
* @retval D_OK	操作成功
* @retval D_ERR_EMPTY		没有按键按下
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
