/** @file
* @brief 基本宏定义
* @author 龚克
* @date 2006-8-10 龚克: 建立文件
        2013-03-19 lc: 统一平台, 代码整理
*/

#ifndef _D_DEF_H_
#define _D_DEF_H_
#ifdef  __cplusplus
extern "C"
{
#endif

/** @brief 不再用以前的多值定义方式 */

/** @brief 此处放置硬件配置文件的TAG定义 */
#define CUSTOM_CONFIG_TAG_SYS           0x00
#define CUSTOM_CONFIG_TAG_IR            0x01
#define CUSTOM_CONFIG_TAG_FP            0x02
#define CUSTOM_CONFIG_TAG_DEMOD         0x03
#define CUSTOM_CONFIG_TAG_UART          0x04
#define CUSTOM_CONFIG_TAG_SC            0x05
#define CUSTOM_CONFIG_TAG_IIC           0x06
#define CUSTOM_CONFIG_TAG_RTC           0x07
#define CUSTOM_CONFIG_TAG_NET           0x08
#define CUSTOM_CONFIG_TAG_LCD           0x09
#define CUSTOM_CONFIG_TAG_IR2           0x0A
#define CUSTOM_CONFIG_TAG_AUDIO         0x0B
#define CUSTOM_CONFIG_TAG_APP_OFFSET    0x0C
#define CUSTOM_CONFIG_TAG_IRDBG         0x0D
#define CUSTOM_CONFIG_TAG_HW_POWEROFF   0x0E
#define CUSTOM_CONFIG_TAG_DEMOD2        0x0F
#define CUSTOM_CONFIG_TAG_TV_DMJ_BATTERY	0x10
#define CUSTOM_CONFIG_TAG_TV_DMJ_RF_CHOSE	0x11
#define CUSTOM_CONFIG_TAG_TV_DMJ_PWM 		0x12
#define CUSTOM_CONFIG_TAG_DEMOD3        0x13
#define CUSTOM_CONFIG_TAG_LVDS        	0x14
#define CUSTOM_CONFIG_TAG_HDMI        	0x15
#define CUSTOM_CONFIG_TAG_DISK          0x16
#define CUSTOM_CONFIG_TAG_TUNER         0x17
#define CUSTOM_CONFIG_TAG_IO            0x18
#define CUSTOM_CONFIG_TAG_AMPLIFIER            0x19
#define CUSTOM_CONFIG_TAG_SARADC            0x1a

#define CUSTOM_CONFIG_TAG_UTI1203RESET  0x1E

/** @brief 此处放置platform里用到的软件配置TAG定义 */
#define CUSTOM_CONFIG_TAG_FFMPEG        0x50
#define CUSTOM_CONFIG_TAG_PVR           0x51

#ifdef  __cplusplus
}
#endif
#endif

