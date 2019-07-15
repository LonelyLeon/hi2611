#include "dFrame.h"
#include "atvlanresource.h"


static PREFIXCONST char POSTCONST atv_IDS_NULL_0[]="";
static PREFIXCONST char POSTCONST atv_IDS_NULL_1[]="";

static PREFIXCONST char POSTCONST atv_IDS_CONTRAST_0[]="Contrast";
static PREFIXCONST char POSTCONST atv_IDS_CONTRAST_1[]="对比度";

static PREFIXCONST char POSTCONST atv_IDS_BRIGHTNESS_0[]="Brightness";
static PREFIXCONST char POSTCONST atv_IDS_BRIGHTNESS_1[]="亮度";

static PREFIXCONST char POSTCONST atv_IDS_COLOR_0[]="Color";
static PREFIXCONST char POSTCONST atv_IDS_COLOR_1[]="色度";

static PREFIXCONST char POSTCONST atv_IDS_SHARPNESS_0[]="Sharpness";
static PREFIXCONST char POSTCONST atv_IDS_SHARPNESS_1[]="清晰度";

static PREFIXCONST char POSTCONST atv_IDS_PICTURE_MODE_0[]="Picture Mode";
static PREFIXCONST char POSTCONST atv_IDS_PICTURE_MODE_1[]="图像模式";

static PREFIXCONST char POSTCONST atv_IDS_ASPECT_RATIO_0[]="Aspect Ratio";
static PREFIXCONST char POSTCONST atv_IDS_ASPECT_RATIO_1[]="缩放模式";

static PREFIXCONST char POSTCONST atv_IDS_COLOR_TEMP_0[]="Color Temp";
static PREFIXCONST char POSTCONST atv_IDS_COLOR_TEMP_1[]="色温";

static PREFIXCONST char POSTCONST atv_IDS_PICTURE_0[]="Picture";
static PREFIXCONST char POSTCONST atv_IDS_PICTURE_1[]="图像";

static PREFIXCONST char POSTCONST atv_IDS_SOUND_0[]="Sound";
static PREFIXCONST char POSTCONST atv_IDS_SOUND_1[]="声音";

static PREFIXCONST char POSTCONST atv_IDS_CHANNEL_0[]="Channel";
static PREFIXCONST char POSTCONST atv_IDS_CHANNEL_1[]="调谐";

static PREFIXCONST char POSTCONST atv_IDS_FUNCTION_0[]="Function";
static PREFIXCONST char POSTCONST atv_IDS_FUNCTION_1[]="功能";

static PREFIXCONST char POSTCONST atv_IDS_ADJUST_0[]="Adjust";
static PREFIXCONST char POSTCONST atv_IDS_ADJUST_1[]="调整";

static PREFIXCONST char POSTCONST atv_IDS_TIME_0[]="Time";
static PREFIXCONST char POSTCONST atv_IDS_TIME_1[]="时间";

static PREFIXCONST char POSTCONST atv_IDS_BACK_0[]="Back";
static PREFIXCONST char POSTCONST atv_IDS_BACK_1[]="返回";

static PREFIXCONST char POSTCONST atv_IDS_MOVE_0[]="Move";
static PREFIXCONST char POSTCONST atv_IDS_MOVE_1[]="移动";

static PREFIXCONST char POSTCONST atv_IDS_OK_0[]="Ok";
static PREFIXCONST char POSTCONST atv_IDS_OK_1[]="确认";

static PREFIXCONST char POSTCONST atv_IDS_TINT_0[]="Tint";
static PREFIXCONST char POSTCONST atv_IDS_TINT_1[]="色调";

static PREFIXCONST char POSTCONST atv_IDS_VOLUME_0[]="Volume";
static PREFIXCONST char POSTCONST atv_IDS_VOLUME_1[]="音量";

static PREFIXCONST char POSTCONST atv_IDS_BALANCE_0[]="Balance";
static PREFIXCONST char POSTCONST atv_IDS_BALANCE_1[]="平衡";

static PREFIXCONST char POSTCONST atv_IDS_DIGITAL_TONE_0[]="Digital Tone";
static PREFIXCONST char POSTCONST atv_IDS_DIGITAL_TONE_1[]="数字音质";

static PREFIXCONST char POSTCONST atv_IDS_SRS_0[]="SRS";
static PREFIXCONST char POSTCONST atv_IDS_SRS_1[]="环绕声";

static PREFIXCONST char POSTCONST atv_IDS_AVL_0[]="AVL";
static PREFIXCONST char POSTCONST atv_IDS_AVL_1[]="智能音量";

static PREFIXCONST char POSTCONST atv_IDS_PROGRAM_EDIT_0[]="Program Edit";
static PREFIXCONST char POSTCONST atv_IDS_PROGRAM_EDIT_1[]="频道编辑";

static PREFIXCONST char POSTCONST atv_IDS_AUTO_TUNING_0[]="Auto Tuning";
static PREFIXCONST char POSTCONST atv_IDS_AUTO_TUNING_1[]="自动搜台";

static PREFIXCONST char POSTCONST atv_IDS_EXCHANGE_0[]="Exchange";
static PREFIXCONST char POSTCONST atv_IDS_EXCHANGE_1[]="频道交换";

static PREFIXCONST char POSTCONST atv_IDS_OSD_LANGUAGE_0[]="OSD Language";
static PREFIXCONST char POSTCONST atv_IDS_OSD_LANGUAGE_1[]="菜单语言";

static PREFIXCONST char POSTCONST atv_IDS_MENU_TIMEOUT_0[]="Menu Timeout";
static PREFIXCONST char POSTCONST atv_IDS_MENU_TIMEOUT_1[]="菜单时间";

static PREFIXCONST char POSTCONST atv_IDS_DNR_0[]="DNR";
static PREFIXCONST char POSTCONST atv_IDS_DNR_1[]="数字降噪";

static PREFIXCONST char POSTCONST atv_IDS_BULE_SCREEN_0[]="Bule Screen";
static PREFIXCONST char POSTCONST atv_IDS_BULE_SCREEN_1[]="背景";

static PREFIXCONST char POSTCONST atv_IDS_BACKLIGHT_0[]="Backlight";
static PREFIXCONST char POSTCONST atv_IDS_BACKLIGHT_1[]="背光调整";

static PREFIXCONST char POSTCONST atv_IDS_RESET_0[]="Reset";
static PREFIXCONST char POSTCONST atv_IDS_RESET_1[]="复位";

static PREFIXCONST char POSTCONST atv_IDS_IMAGE_POSITION_0[]="Image Position";
static PREFIXCONST char POSTCONST atv_IDS_IMAGE_POSITION_1[]="图像位置";

static PREFIXCONST char POSTCONST atv_IDS_HORIZONTAL_AMPLITUDE_0[]="Horizontal tal Size";
static PREFIXCONST char POSTCONST atv_IDS_HORIZONTAL_AMPLITUDE_1[]="水平幅度";

static PREFIXCONST char POSTCONST atv_IDS_VERTICAL_AMPLITUDE_0[]="Vertical Size";
static PREFIXCONST char POSTCONST atv_IDS_VERTICAL_AMPLITUDE_1[]="垂直幅度";

static PREFIXCONST char POSTCONST atv_IDS_AUTO_ADJUST_0[]="Auto Adjust";
static PREFIXCONST char POSTCONST atv_IDS_AUTO_ADJUST_1[]="自动调整";

static PREFIXCONST char POSTCONST atv_IDS_CLOCK_0[]="Clock";
static PREFIXCONST char POSTCONST atv_IDS_CLOCK_1[]="时钟";

static PREFIXCONST char POSTCONST atv_IDS_PHASE_0[]="Phase";
static PREFIXCONST char POSTCONST atv_IDS_PHASE_1[]="相位";

static PREFIXCONST char POSTCONST atv_IDS_CURRENT_TIME_0[]="Current Time";
static PREFIXCONST char POSTCONST atv_IDS_CURRENT_TIME_1[]="当前时间";

static PREFIXCONST char POSTCONST atv_IDS_OFF_TIME_0[]="Off Time";
static PREFIXCONST char POSTCONST atv_IDS_OFF_TIME_1[]="定时关机";

static PREFIXCONST char POSTCONST atv_IDS_ON_TIME_0[]="On Time";
static PREFIXCONST char POSTCONST atv_IDS_ON_TIME_1[]="定时开机";

static PREFIXCONST char POSTCONST atv_IDS_ON_CHANNEL_0[]="On Channel ";
static PREFIXCONST char POSTCONST atv_IDS_ON_CHANNEL_1[]="开机频道";

static PREFIXCONST char POSTCONST atv_IDS_REMIND_TIME_0[]="Remind Time";
static PREFIXCONST char POSTCONST atv_IDS_REMIND_TIME_1[]="预约时间";

static PREFIXCONST char POSTCONST atv_IDS_REMIND_CHANNEL_0[]="Remind Channel";
static PREFIXCONST char POSTCONST atv_IDS_REMIND_CHANNEL_1[]="预约频道";

static PREFIXCONST char POSTCONST atv_IDS_SLEEP_TIMER_0[]="Sleep Timer";
static PREFIXCONST char POSTCONST atv_IDS_SLEEP_TIMER_1[]="睡眠定时";

static PREFIXCONST char POSTCONST atv_IDS_TV_0[]="TV";
static PREFIXCONST char POSTCONST atv_IDS_TV_1[]="模拟电视";

static PREFIXCONST char POSTCONST atv_IDS_DTV_0[]="DTV";
static PREFIXCONST char POSTCONST atv_IDS_DTV_1[]="数字电视";

static PREFIXCONST char POSTCONST atv_IDS_AV_0[]="AV";
static PREFIXCONST char POSTCONST atv_IDS_AV_1[]="视频";

static PREFIXCONST char POSTCONST atv_IDS_AV1_0[]="AV1";
static PREFIXCONST char POSTCONST atv_IDS_AV1_1[]="视频1";

static PREFIXCONST char POSTCONST atv_IDS_AV2_0[]="AV2";
static PREFIXCONST char POSTCONST atv_IDS_AV2_1[]="视频2";

static PREFIXCONST char POSTCONST atv_IDS_YPBPR_0[]="YPbPr";
static PREFIXCONST char POSTCONST atv_IDS_YPBPR_1[]="分量";

static PREFIXCONST char POSTCONST atv_IDS_HDMI_0[]="HDMI";
static PREFIXCONST char POSTCONST atv_IDS_HDMI_1[]="HDMI";

static PREFIXCONST char POSTCONST atv_IDS_HDMI1_0[]="HDMI1";
static PREFIXCONST char POSTCONST atv_IDS_HDMI1_1[]="HDMI1";

static PREFIXCONST char POSTCONST atv_IDS_HDMI2_0[]="HDMI2";
static PREFIXCONST char POSTCONST atv_IDS_HDMI2_1[]="HDMI2";

static PREFIXCONST char POSTCONST atv_IDS_PC_0[]="PC";
static PREFIXCONST char POSTCONST atv_IDS_PC_1[]="电脑";

static PREFIXCONST char POSTCONST atv_IDS_USB_0[]="USB";
static PREFIXCONST char POSTCONST atv_IDS_USB_1[]="流媒体";

static PREFIXCONST char POSTCONST atv_IDS_SOURCE_0[]="Source";
static PREFIXCONST char POSTCONST atv_IDS_SOURCE_1[]="信号源";

static PREFIXCONST char POSTCONST atv_IDS_STANDARD_0[]="Standard";
static PREFIXCONST char POSTCONST atv_IDS_STANDARD_1[]="标准";

static PREFIXCONST char POSTCONST atv_IDS_MILD_0[]="Mild";
static PREFIXCONST char POSTCONST atv_IDS_MILD_1[]="柔和";

static PREFIXCONST char POSTCONST atv_IDS_USER_0[]="User";
static PREFIXCONST char POSTCONST atv_IDS_USER_1[]="用户";

static PREFIXCONST char POSTCONST atv_IDS_LIGHT_0[]="Brightness";
static PREFIXCONST char POSTCONST atv_IDS_LIGHT_1[]="明亮";

static PREFIXCONST char POSTCONST atv_IDS_FULL_SCREEN_0[]="Full_Screen";
static PREFIXCONST char POSTCONST atv_IDS_FULL_SCREEN_1[]="满屏";

static PREFIXCONST char POSTCONST atv_IDS_4TO3_0[]="4:3";
static PREFIXCONST char POSTCONST atv_IDS_4TO3_1[]="4:3";

static PREFIXCONST char POSTCONST atv_IDS_ZOOM_0[]="Zoom";
static PREFIXCONST char POSTCONST atv_IDS_ZOOM_1[]="放大";

static PREFIXCONST char POSTCONST atv_IDS_PANORAMA_0[]="Panorama";
static PREFIXCONST char POSTCONST atv_IDS_PANORAMA_1[]="全景";

static PREFIXCONST char POSTCONST atv_IDS_WARM_0[]="Warm";
static PREFIXCONST char POSTCONST atv_IDS_WARM_1[]="暖色";

static PREFIXCONST char POSTCONST atv_IDS_COOL_0[]="Cool";
static PREFIXCONST char POSTCONST atv_IDS_COOL_1[]="冷色";

static PREFIXCONST char POSTCONST atv_IDS_ON_0[]="On";
static PREFIXCONST char POSTCONST atv_IDS_ON_1[]="开";

static PREFIXCONST char POSTCONST atv_IDS_OFF_0[]="Off";
static PREFIXCONST char POSTCONST atv_IDS_OFF_1[]="关";

static PREFIXCONST char POSTCONST atv_IDS_PROGRAM_MANAGE_0[]="Program Manage";
static PREFIXCONST char POSTCONST atv_IDS_PROGRAM_MANAGE_1[]="频道管理";

static PREFIXCONST char POSTCONST atv_IDS_MANUAL_SEARCH_0[]="Manual Search";
static PREFIXCONST char POSTCONST atv_IDS_MANUAL_SEARCH_1[]="手动搜索";

static PREFIXCONST char POSTCONST atv_IDS_FINE_TUNE_0[]="Fine Tune";
static PREFIXCONST char POSTCONST atv_IDS_FINE_TUNE_1[]="微调";

static PREFIXCONST char POSTCONST atv_IDS_COLOR_SYSTEM_0[]="Color System";
static PREFIXCONST char POSTCONST atv_IDS_COLOR_SYSTEM_1[]="彩色制式";

static PREFIXCONST char POSTCONST atv_IDS_SOUND_SYSTEM_0[]="Sound System";
static PREFIXCONST char POSTCONST atv_IDS_SOUND_SYSTEM_1[]="声音制式";

static PREFIXCONST char POSTCONST atv_IDS_SKIP_0[]="Skip";
static PREFIXCONST char POSTCONST atv_IDS_SKIP_1[]="跳过";

static PREFIXCONST char POSTCONST atv_IDS_CANCEL_0[]="Cancel";
static PREFIXCONST char POSTCONST atv_IDS_CANCEL_1[]="取消";

static PREFIXCONST char POSTCONST atv_IDS_START_AUTO_SCAN_0[]="Do you want to start auto scan？";
static PREFIXCONST char POSTCONST atv_IDS_START_AUTO_SCAN_1[]="是否开始自动搜台？";

static PREFIXCONST char POSTCONST atv_IDS_ENGLISH_0[]="English";
static PREFIXCONST char POSTCONST atv_IDS_ENGLISH_1[]="English";

static PREFIXCONST char POSTCONST atv_IDS_CHINESE_0[]="简体中文";
static PREFIXCONST char POSTCONST atv_IDS_CHINESE_1[]="简体中文";

static PREFIXCONST char POSTCONST atv_IDS_HORIZONTAL_POS_0[]="Horizontal Pos";
static PREFIXCONST char POSTCONST atv_IDS_HORIZONTAL_POS_1[]="水平位置";

static PREFIXCONST char POSTCONST atv_IDS_VERTICAL_POS_0[]="Vertical Pos";
static PREFIXCONST char POSTCONST atv_IDS_VERTICAL_POS_1[]="垂直位置";

static PREFIXCONST char POSTCONST atv_IDS_15_MINUTE_0[]="15 Minute";
static PREFIXCONST char POSTCONST atv_IDS_15_MINUTE_1[]="15分钟";

static PREFIXCONST char POSTCONST atv_IDS_30_MINUTE_0[]="30 Minute";
static PREFIXCONST char POSTCONST atv_IDS_30_MINUTE_1[]="30分钟";

static PREFIXCONST char POSTCONST atv_IDS_60_MINUTE_0[]="60 Minute";
static PREFIXCONST char POSTCONST atv_IDS_60_MINUTE_1[]="60分钟";

static PREFIXCONST char POSTCONST atv_IDS_120_MINUTE_0[]="120 Minute";
static PREFIXCONST char POSTCONST atv_IDS_120_MINUTE_1[]="120分钟";

static PREFIXCONST char POSTCONST atv_IDS_240_MINUTE_0[]="240 Minute";
static PREFIXCONST char POSTCONST atv_IDS_240_MINUTE_1[]="240分钟";

static PREFIXCONST char POSTCONST atv_IDS_PTP_0[]="PTP";
static PREFIXCONST char POSTCONST atv_IDS_PTP_1[]="全真";

static PREFIXCONST char POSTCONST atv_IDS_5_S_0[]="5 S";
static PREFIXCONST char POSTCONST atv_IDS_5_S_1[]="5秒";

static PREFIXCONST char POSTCONST atv_IDS_10_S_0[]="10 S";
static PREFIXCONST char POSTCONST atv_IDS_10_S_1[]="10秒";

static PREFIXCONST char POSTCONST atv_IDS_15_S_0[]="15 S";
static PREFIXCONST char POSTCONST atv_IDS_15_S_1[]="15秒";

static PREFIXCONST char POSTCONST atv_IDS_CURRENT_CHANNEL_0[]="Current Channel";
static PREFIXCONST char POSTCONST atv_IDS_CURRENT_CHANNEL_1[]="当前频道";

static PREFIXCONST char POSTCONST atv_IDS_TO_CHANNEL_0[]="To Channel";
static PREFIXCONST char POSTCONST atv_IDS_TO_CHANNEL_1[]="交换到";

static PREFIXCONST char POSTCONST atv_IDS_MENU_0[]="Menu";
static PREFIXCONST char POSTCONST atv_IDS_MENU_1[]="菜单";

static PREFIXCONST char POSTCONST atv_IDS_MOVIE_0[]="Movie";
static PREFIXCONST char POSTCONST atv_IDS_MOVIE_1[]="电影";

static PREFIXCONST char POSTCONST atv_IDS_MUSIC_0[]="Music";
static PREFIXCONST char POSTCONST atv_IDS_MUSIC_1[]="音乐";

static PREFIXCONST char POSTCONST atv_IDS_SETTING_0[]="Setting";
static PREFIXCONST char POSTCONST atv_IDS_SETTING_1[]="设置";

static PREFIXCONST char POSTCONST atv_IDS_PLAY_0[]="Play";
static PREFIXCONST char POSTCONST atv_IDS_PLAY_1[]="播放";

static PREFIXCONST char POSTCONST atv_IDS_PAUSE_0[]="Pause";
static PREFIXCONST char POSTCONST atv_IDS_PAUSE_1[]="暂停";

static PREFIXCONST char POSTCONST atv_IDS_PICTURE_SPEED_0[]="Picture Speed";
static PREFIXCONST char POSTCONST atv_IDS_PICTURE_SPEED_1[]="图像播放速度";

static PREFIXCONST char POSTCONST atv_IDS_UP_LEVEL_0[]="Up Level";
static PREFIXCONST char POSTCONST atv_IDS_UP_LEVEL_1[]="上一级";

static PREFIXCONST char POSTCONST atv_IDS_HIGH_SPEED_0[]="High Speed";
static PREFIXCONST char POSTCONST atv_IDS_HIGH_SPEED_1[]="高速";

static PREFIXCONST char POSTCONST atv_IDS_LOW_SPEED_0[]="Low Speed";
static PREFIXCONST char POSTCONST atv_IDS_LOW_SPEED_1[]="低速";

static PREFIXCONST char POSTCONST atv_IDS_MIDDLE_SPEED_0[]="Middle Speed";
static PREFIXCONST char POSTCONST atv_IDS_MIDDLE_SPEED_1[]="中速";

static PREFIXCONST char POSTCONST atv_IDS_PICTURE_OPTIMIZE_0[]="Picture Optimize";
static PREFIXCONST char POSTCONST atv_IDS_PICTURE_OPTIMIZE_1[]="图像优化";

static PREFIXCONST char POSTCONST atv_IDS_HIGH_0[]="High";
static PREFIXCONST char POSTCONST atv_IDS_HIGH_1[]="高";

static PREFIXCONST char POSTCONST atv_IDS_LOW_0[]="Low";
static PREFIXCONST char POSTCONST atv_IDS_LOW_1[]="低";

static PREFIXCONST char POSTCONST atv_IDS_MIDDLE_0[]="Middle";
static PREFIXCONST char POSTCONST atv_IDS_MIDDLE_1[]="中";

static PREFIXCONST char POSTCONST atv_IDS_LAST_0[]="Last";
static PREFIXCONST char POSTCONST atv_IDS_LAST_1[]="上一张";

static PREFIXCONST char POSTCONST atv_IDS_NEXT_0[]="Next";
static PREFIXCONST char POSTCONST atv_IDS_NEXT_1[]="下一张";

static PREFIXCONST char POSTCONST atv_IDS_ROTATE_0[]="Rotate";
static PREFIXCONST char POSTCONST atv_IDS_ROTATE_1[]="旋转";

static PREFIXCONST char POSTCONST atv_IDS_STOP_AUTO_SCAN_0[]="Stop Auto Scan?";
static PREFIXCONST char POSTCONST atv_IDS_STOP_AUTO_SCAN_1[]="是否退出搜台？";

static PREFIXCONST char POSTCONST atv_IDS_CHANNEL_LIST_0[]="Channel List";
static PREFIXCONST char POSTCONST atv_IDS_CHANNEL_LIST_1[]="频道列表";

static PREFIXCONST char POSTCONST atv_IDS_TV_MANUAL_SCAN_0[]="TV Manual Scan";
static PREFIXCONST char POSTCONST atv_IDS_TV_MANUAL_SCAN_1[]="数字电视手动搜索";

static PREFIXCONST char POSTCONST atv_IDS_CHANNEL_SCAN_0[]="Channel Scan";
static PREFIXCONST char POSTCONST atv_IDS_CHANNEL_SCAN_1[]="频道搜索";

static PREFIXCONST char POSTCONST atv_IDS_NO_SIGNAL_0[]="No Signal";
static PREFIXCONST char POSTCONST atv_IDS_NO_SIGNAL_1[]="无信号";

static PREFIXCONST char POSTCONST atv_IDS_BAD_0[]="Bad";
static PREFIXCONST char POSTCONST atv_IDS_BAD_1[]="差";

static PREFIXCONST char POSTCONST atv_IDS_GOOD_0[]="Good";
static PREFIXCONST char POSTCONST atv_IDS_GOOD_1[]="好";

static PREFIXCONST char POSTCONST atv_IDS_FREQ_0[]="Freq:";
static PREFIXCONST char POSTCONST atv_IDS_FREQ_1[]="频率：";

static PREFIXCONST char POSTCONST atv_IDS_DIGI_TV_0[]="DIGI TV";
static PREFIXCONST char POSTCONST atv_IDS_DIGI_TV_1[]="电视节目";

static PREFIXCONST char POSTCONST atv_IDS_DIGI_RADIO_0[]="DIGI Radio";
static PREFIXCONST char POSTCONST atv_IDS_DIGI_RADIO_1[]="广播节目";

static PREFIXCONST char POSTCONST atv_IDS_QUIT_0[]="Quit";
static PREFIXCONST char POSTCONST atv_IDS_QUIT_1[]="退出";

static PREFIXCONST char POSTCONST atv_IDS_CH_ID_0[]="Channel Number";
static PREFIXCONST char POSTCONST atv_IDS_CH_ID_1[]="频道号";

static PREFIXCONST char POSTCONST atv_IDS_EBOOK_0[]="EBook";
static PREFIXCONST char POSTCONST atv_IDS_EBOOK_1[]="电子书";

static PREFIXCONST char POSTCONST atv_IDS_STOP_0[]="Stop";
static PREFIXCONST char POSTCONST atv_IDS_STOP_1[]="停止";

static PREFIXCONST char POSTCONST atv_IDS_AV_SIGNAL_SELECT_0[]="av signal select";
static PREFIXCONST char POSTCONST atv_IDS_AV_SIGNAL_SELECT_1[]="数字电视信号选择";

static PREFIXCONST char POSTCONST atv_IDS_AV_SIGNAL_0[]="av signal";
static PREFIXCONST char POSTCONST atv_IDS_AV_SIGNAL_1[]="数字电视信号";

static PREFIXCONST char POSTCONST atv_IDS_DVBC_0[]="DVBC";
static PREFIXCONST char POSTCONST atv_IDS_DVBC_1[]="DVBC";

static PREFIXCONST char POSTCONST atv_IDS_DTMB_0[]="DTMB";
static PREFIXCONST char POSTCONST atv_IDS_DTMB_1[]="DTMB";

static PREFIXCONST char POSTCONST atv_IDS_NO_USB_0[]="No USB";
static PREFIXCONST char POSTCONST atv_IDS_NO_USB_1[]="没有USB设备！";

static PREFIXCONST char POSTCONST atv_IDS_USB_CONNECT_0[]="Usb Connect";
static PREFIXCONST char POSTCONST atv_IDS_USB_CONNECT_1[]="USB设备已插入！";

static PREFIXCONST char POSTCONST atv_IDS_USB_DIS_CONNECT_0[]="USB DisConnect";
static PREFIXCONST char POSTCONST atv_IDS_USB_DIS_CONNECT_1[]="USB设备已移出！";

static PREFIXCONST char POSTCONST atv_IDS_SEARCH_AUTO_0[]="AUTO";
static PREFIXCONST char POSTCONST atv_IDS_SEARCH_AUTO_1[]="自动";

static PREFIXCONST char POSTCONST atv_IDS_SEARCH_PAL_0[]="PAL";
static PREFIXCONST char POSTCONST atv_IDS_SEARCH_PAL_1[]="PAL";

static PREFIXCONST char POSTCONST atv_IDS_SEARCH_SECAM_0[]="SECAM";
static PREFIXCONST char POSTCONST atv_IDS_SEARCH_SECAM_1[]="SECAM";

static PREFIXCONST char POSTCONST atv_IDS_SEARCH_NTSC_0[]="NTSC";
static PREFIXCONST char POSTCONST atv_IDS_SEARCH_NTSC_1[]="NTSC";

static PREFIXCONST char POSTCONST atv_IDS_SEARCH_DK_0[]="DK";
static PREFIXCONST char POSTCONST atv_IDS_SEARCH_DK_1[]="DK";

static PREFIXCONST char POSTCONST atv_IDS_SEARCH_BG_0[]="BG";
static PREFIXCONST char POSTCONST atv_IDS_SEARCH_BG_1[]="BG";

static PREFIXCONST char POSTCONST atv_IDS_SEARCH_I_0[]="I";
static PREFIXCONST char POSTCONST atv_IDS_SEARCH_I_1[]="I";

static PREFIXCONST char POSTCONST atv_IDS_SEARCH_M_0[]="M";
static PREFIXCONST char POSTCONST atv_IDS_SEARCH_M_1[]="M";

static PREFIXCONST char POSTCONST atv_IDS_DEFAULT_SET_0[]="Set to factory default ?";
static PREFIXCONST char POSTCONST atv_IDS_DEFAULT_SET_1[]="是否恢复默认设置";

static PREFIXCONST char POSTCONST atv_IDS_RESTORE_OK_0[]="Restore ok.";
static PREFIXCONST char POSTCONST atv_IDS_RESTORE_OK_1[]="恢复设置成功！";

static PREFIXCONST char POSTCONST atv_IDS_PROMPT_INFO_0[]="Prompt Info";
static PREFIXCONST char POSTCONST atv_IDS_PROMPT_INFO_1[]="提示信息";

static PREFIXCONST char POSTCONST atv_IDS_PLAY_FAILED_0[]="Play Failed";
static PREFIXCONST char POSTCONST atv_IDS_PLAY_FAILED_1[]="播放失败！";

static PREFIXCONST char POSTCONST atv_IDS_FREQ_SEARCH_0[]="Search All";
static PREFIXCONST char POSTCONST atv_IDS_FREQ_SEARCH_1[]="全频段";

static PREFIXCONST char POSTCONST atv_IDS_TV_AUTO_SCAN_0[]="TV Auto Scan";
static PREFIXCONST char POSTCONST atv_IDS_TV_AUTO_SCAN_1[]="数字电视自动搜索";

static PREFIXCONST char POSTCONST atv_IDS_START_ALL_SCAN_0[]="Do you want to start all scan？";
static PREFIXCONST char POSTCONST atv_IDS_START_ALL_SCAN_1[]="是否开始全频段搜索？";

static PREFIXCONST char POSTCONST atv_IDS_END_ALL_SCAN_0[]="Do you want to end all scan？";
static PREFIXCONST char POSTCONST atv_IDS_END_ALL_SCAN_1[]="是否结束全频段搜索？";

static PREFIXCONST char POSTCONST atv_IDS_SCANNING_0[]="Scanning,Please waitting…";
static PREFIXCONST char POSTCONST atv_IDS_SCANNING_1[]="搜台中，请稍等…";

static PREFIXCONST char POSTCONST atv_IDS_MONDAY_0[]="MON";
static PREFIXCONST char POSTCONST atv_IDS_MONDAY_1[]="周一";

static PREFIXCONST char POSTCONST atv_IDS_TUESDAY_0[]="TUE";
static PREFIXCONST char POSTCONST atv_IDS_TUESDAY_1[]="周二";

static PREFIXCONST char POSTCONST atv_IDS_WENDSDAY_0[]="WEN";
static PREFIXCONST char POSTCONST atv_IDS_WENDSDAY_1[]="周三";

static PREFIXCONST char POSTCONST atv_IDS_THURSDAY_0[]="THU";
static PREFIXCONST char POSTCONST atv_IDS_THURSDAY_1[]="周四";

static PREFIXCONST char POSTCONST atv_IDS_FRIDAY_0[]="FRI";
static PREFIXCONST char POSTCONST atv_IDS_FRIDAY_1[]="周五";

static PREFIXCONST char POSTCONST atv_IDS_SATURDAY_0[]="SAT";
static PREFIXCONST char POSTCONST atv_IDS_SATURDAY_1[]="周六";

static PREFIXCONST char POSTCONST atv_IDS_SUNDAY_0[]="SUN";
static PREFIXCONST char POSTCONST atv_IDS_SUNDAY_1[]="周日";

static PREFIXCONST char POSTCONST atv_IDS_INIT_TV_0[]="Init TV";
static PREFIXCONST char POSTCONST atv_IDS_INIT_TV_1[]="清EEP";

static PREFIXCONST char POSTCONST atv_IDS_GENERAL_SETTING_0[]="General Setting";
static PREFIXCONST char POSTCONST atv_IDS_GENERAL_SETTING_1[]="通用设置";

static PREFIXCONST char POSTCONST atv_IDS_DEBUG_0[]="Debug";
static PREFIXCONST char POSTCONST atv_IDS_DEBUG_1[]="调试";

static PREFIXCONST char POSTCONST atv_IDS_SW_INFORMATION_0[]="SW Information";
static PREFIXCONST char POSTCONST atv_IDS_SW_INFORMATION_1[]="软件信息";

static PREFIXCONST char POSTCONST atv_IDS_SOFTWARE_UPDATE_0[]="Software Update(USB)";
static PREFIXCONST char POSTCONST atv_IDS_SOFTWARE_UPDATE_1[]="软件升级(USB)";

static PREFIXCONST char POSTCONST atv_IDS_INIT_FAC_CHANNEL_0[]="Init Fac Channel";
static PREFIXCONST char POSTCONST atv_IDS_INIT_FAC_CHANNEL_1[]="频道预置";

static PREFIXCONST char POSTCONST atv_IDS_BURN_MODE_0[]="Burn Mode";
static PREFIXCONST char POSTCONST atv_IDS_BURN_MODE_1[]="老化模式";

static PREFIXCONST char POSTCONST atv_IDS_INIT_ALL_FOR_BOE_0[]="Init all for boe";
static PREFIXCONST char POSTCONST atv_IDS_INIT_ALL_FOR_BOE_1[]="BOE总复位";

static PREFIXCONST char POSTCONST atv_IDS_HOTEL_MODE_0[]="Hotel Mode";
static PREFIXCONST char POSTCONST atv_IDS_HOTEL_MODE_1[]="酒店模式";

static PREFIXCONST char POSTCONST atv_IDS_SOURCE_LOCK_0[]="Source Lock";
static PREFIXCONST char POSTCONST atv_IDS_SOURCE_LOCK_1[]="通道锁";

static PREFIXCONST char POSTCONST atv_IDS_CHANNEL_LOCK_0[]="Channel Lock";
static PREFIXCONST char POSTCONST atv_IDS_CHANNEL_LOCK_1[]="频道锁";

static PREFIXCONST char POSTCONST atv_IDS_DEFAULT_SOURCE_0[]="Default Source";
static PREFIXCONST char POSTCONST atv_IDS_DEFAULT_SOURCE_1[]="默认开机通道";

static PREFIXCONST char POSTCONST atv_IDS_DEFAULT_PROG_0[]="Default Prog";
static PREFIXCONST char POSTCONST atv_IDS_DEFAULT_PROG_1[]="默认开机频道";

static PREFIXCONST char POSTCONST atv_IDS_MAX_VOLUME_0[]="Max Volume";
static PREFIXCONST char POSTCONST atv_IDS_MAX_VOLUME_1[]="最大音量";

static PREFIXCONST char POSTCONST atv_IDS_DEFAULT_VOLUME_0[]="Default Volume";
static PREFIXCONST char POSTCONST atv_IDS_DEFAULT_VOLUME_1[]="默认音量";

static PREFIXCONST char POSTCONST atv_IDS_POWER_DOWN_RESET_0[]="Power down reset";
static PREFIXCONST char POSTCONST atv_IDS_POWER_DOWN_RESET_1[]="关机复位";

static PREFIXCONST char POSTCONST atv_IDS_RESET_HOTEL_0[]="Reset Hotel ";
static PREFIXCONST char POSTCONST atv_IDS_RESET_HOTEL_1[]="参数初始化";

static PREFIXCONST char POSTCONST atv_IDS_EXPORT_SETTINGS_0[]="Export Settings";
static PREFIXCONST char POSTCONST atv_IDS_EXPORT_SETTINGS_1[]="导出设置";

static PREFIXCONST char POSTCONST atv_IDS_IMPORT_SETTINGS_0[]="Import Settings ";
static PREFIXCONST char POSTCONST atv_IDS_IMPORT_SETTINGS_1[]="导入设置";

static PREFIXCONST char POSTCONST atv_IDS_KEY_LOCK_0[]="Key Lock";
static PREFIXCONST char POSTCONST atv_IDS_KEY_LOCK_1[]="按键锁";

static PREFIXCONST char POSTCONST atv_IDS_CAPTURE_LOGO_0[]="Capture Logo";
static PREFIXCONST char POSTCONST atv_IDS_CAPTURE_LOGO_1[]="抓图";

static PREFIXCONST char POSTCONST atv_IDS_LOGO_0[]="Logo";
static PREFIXCONST char POSTCONST atv_IDS_LOGO_1[]="开机画面";

static PREFIXCONST char POSTCONST atv_IDS_DEFAULT_0[]="Default";
static PREFIXCONST char POSTCONST atv_IDS_DEFAULT_1[]="默认";

static PREFIXCONST char POSTCONST atv_IDS_ADC_ADJUST_0[]="ADC Adjust";
static PREFIXCONST char POSTCONST atv_IDS_ADC_ADJUST_1[]="ADC 校正";

static PREFIXCONST char POSTCONST atv_IDS_EMC_SETTING_0[]="EMC Setting";
static PREFIXCONST char POSTCONST atv_IDS_EMC_SETTING_1[]="EMC 设置 ";

static PREFIXCONST char POSTCONST atv_IDS_BUILD_TIME_0[]="Build Time";
static PREFIXCONST char POSTCONST atv_IDS_BUILD_TIME_1[]="编译时间";

static PREFIXCONST char POSTCONST atv_IDS_VERSION_0[]="Version";
static PREFIXCONST char POSTCONST atv_IDS_VERSION_1[]="版本";

static PREFIXCONST char POSTCONST atv_IDS_LVDS_MAP_0[]="LVDS MAP";
static PREFIXCONST char POSTCONST atv_IDS_LVDS_MAP_1[]="LVDS MAP";

static PREFIXCONST char POSTCONST atv_IDS_POWER_MODE_0[]="power mode";
static PREFIXCONST char POSTCONST atv_IDS_POWER_MODE_1[]="power mode";

static PREFIXCONST char POSTCONST atv_IDS_WHITE_PATTERN_0[]="White pattern";
static PREFIXCONST char POSTCONST atv_IDS_WHITE_PATTERN_1[]="WHITE PATTERN";

static PREFIXCONST char POSTCONST atv_IDS_PWM_0[]="PWM";
static PREFIXCONST char POSTCONST atv_IDS_PWM_1[]="PWM";

static PREFIXCONST char POSTCONST atv_IDS_POWER_REF_0[]="Power Ref";
static PREFIXCONST char POSTCONST atv_IDS_POWER_REF_1[]="POWER REF";

static PREFIXCONST char POSTCONST atv_IDS_POWER_DIM_0[]="Power Dim";
static PREFIXCONST char POSTCONST atv_IDS_POWER_DIM_1[]="POWER DIM";

static PREFIXCONST char POSTCONST atv_IDS_BACKLIGHT_MAX_0[]="BackLight Max";
static PREFIXCONST char POSTCONST atv_IDS_BACKLIGHT_MAX_1[]="BackLight Max";

static PREFIXCONST char POSTCONST atv_IDS_BACKLIGHT_LEVEL_0[]="BackLight Level";
static PREFIXCONST char POSTCONST atv_IDS_BACKLIGHT_LEVEL_1[]="BackLight Level";

static PREFIXCONST char POSTCONST atv_IDS_BACKLIGHT_STEP_0[]="BackLight Step";
static PREFIXCONST char POSTCONST atv_IDS_BACKLIGHT_STEP_1[]="BackLight Step";

static PREFIXCONST char POSTCONST atv_IDS_STEP_TIME_0[]="Step Time";
static PREFIXCONST char POSTCONST atv_IDS_STEP_TIME_1[]="Step Time";

static PREFIXCONST char POSTCONST atv_IDS_FACTORY_SETTING_0[]="Factory Setting";
static PREFIXCONST char POSTCONST atv_IDS_FACTORY_SETTING_1[]="Factory Setting";

static PREFIXCONST char POSTCONST atv_IDS_NO_PROGRAM_0[]="No Program";
static PREFIXCONST char POSTCONST atv_IDS_NO_PROGRAM_1[]="无节目";

static PREFIXCONST char POSTCONST atv_IDS_SOUND_BACKLIGHT_0[]="Backlight";
static PREFIXCONST char POSTCONST atv_IDS_SOUND_BACKLIGHT_1[]="背光";

static PREFIXCONST char POSTCONST atv_IDS_WB_ADJUST_0[]="W/B Adjust";
static PREFIXCONST char POSTCONST atv_IDS_WB_ADJUST_1[]="白平衡调整";

static PREFIXCONST char POSTCONST atv_IDS_PQ_NONLINEAR_0[]="PQ Nonlinear";
static PREFIXCONST char POSTCONST atv_IDS_PQ_NONLINEAR_1[]="效果";

static PREFIXCONST char POSTCONST atv_IDS_SOUND_MODE_0[]="Sound Mode";
static PREFIXCONST char POSTCONST atv_IDS_SOUND_MODE_1[]="声音模式";

static PREFIXCONST char POSTCONST atv_IDS_VOLUME_CURVE_0[]="Volume Curve";
static PREFIXCONST char POSTCONST atv_IDS_VOLUME_CURVE_1[]="音量";

static PREFIXCONST char POSTCONST atv_IDS_SATURATION_0[]="Saturation";
static PREFIXCONST char POSTCONST atv_IDS_SATURATION_1[]="饱和度";

static PREFIXCONST char POSTCONST atv_IDS_PVR_0[]="Pvr";
static PREFIXCONST char POSTCONST atv_IDS_PVR_1[]="录像";

static PREFIXCONST char POSTCONST atv_IDS_STOP_RECORD_0[]="Stop Record";
static PREFIXCONST char POSTCONST atv_IDS_STOP_RECORD_1[]="是否停止录制？";

static PREFIXCONST char POSTCONST atv_IDS_ENTER_RECORD_0[]="Enter Record, Waiting…";
static PREFIXCONST char POSTCONST atv_IDS_ENTER_RECORD_1[]="开始录像,请稍等…";

static PREFIXCONST char POSTCONST atv_IDS_RECORD_FAILED_0[]="Record Failed";
static PREFIXCONST char POSTCONST atv_IDS_RECORD_FAILED_1[]="启动录制失败！";

static PREFIXCONST char POSTCONST atv_IDS_RECORD_TIME_OUT_0[]="Record Time Out";
static PREFIXCONST char POSTCONST atv_IDS_RECORD_TIME_OUT_1[]="录制时间已到";

static PREFIXCONST char POSTCONST atv_IDS_NO_SPACE_0[]="No Space";
static PREFIXCONST char POSTCONST atv_IDS_NO_SPACE_1[]="磁盘没有空间";

static PREFIXCONST char POSTCONST atv_IDS_REICORD_FILE_LARGE_0[]="The file's size more than 4G,saving andexit!";
static PREFIXCONST char POSTCONST atv_IDS_REICORD_FILE_LARGE_1[]="文件超过4G，保存数据并退出";

static PREFIXCONST char POSTCONST atv_IDS_BAD_SIGNAL_SAVING_0[]="Bad signal,saving and exit record !";
static PREFIXCONST char POSTCONST atv_IDS_BAD_SIGNAL_SAVING_1[]="信号中断，保存数据并退出";

static PREFIXCONST char POSTCONST atv_IDS_DEVICE_REMOVED_0[]="Mobile device is removed";
static PREFIXCONST char POSTCONST atv_IDS_DEVICE_REMOVED_1[]="移动设备已被移走";

static PREFIXCONST char POSTCONST atv_IDS_RECORD_NOT_CHANGE_CHANNEL_0[]="Recording…";
static PREFIXCONST char POSTCONST atv_IDS_RECORD_NOT_CHANGE_CHANNEL_1[]="录制中不允许换台！";

static PREFIXCONST char POSTCONST atv_IDS_NO_FIND_DISK_0[]="No Find Disk";
static PREFIXCONST char POSTCONST atv_IDS_NO_FIND_DISK_1[]="没有发现磁盘";

static PREFIXCONST char POSTCONST atv_IDS_RED_INPUT_0[]="Input Time By Red Button";
static PREFIXCONST char POSTCONST atv_IDS_RED_INPUT_1[]="按红色按键输入录制的时间！";

static PREFIXCONST char POSTCONST atv_IDS_BOXINFORMATION_0[]="Information";
static PREFIXCONST char POSTCONST atv_IDS_BOXINFORMATION_1[]="本机信息";

static PREFIXCONST char POSTCONST atv_IDS_PRODUCECOMPANY_0[]="Company";
static PREFIXCONST char POSTCONST atv_IDS_PRODUCECOMPANY_1[]="生产厂家";

static PREFIXCONST char POSTCONST atv_IDS_HARDWAREEDITION_0[]="Hardware";
static PREFIXCONST char POSTCONST atv_IDS_HARDWAREEDITION_1[]="硬件版本";

static PREFIXCONST char POSTCONST atv_IDS_SOFTWAREEDITION_0[]="Software";
static PREFIXCONST char POSTCONST atv_IDS_SOFTWAREEDITION_1[]="软件版本";

static PREFIXCONST char POSTCONST atv_IDS_SERIALNUMBER_0[]="Serial";
static PREFIXCONST char POSTCONST atv_IDS_SERIALNUMBER_1[]="序列号";

static PREFIXCONST char POSTCONST atv_IDS_COMPANYID_0[]="Company Id";
static PREFIXCONST char POSTCONST atv_IDS_COMPANYID_1[]="厂家 id";

static PREFIXCONST char POSTCONST atv_IDS_UPGRADE_FAIL_0[]="Upgrade failed!";
static PREFIXCONST char POSTCONST atv_IDS_UPGRADE_FAIL_1[]="升级失败";

static PREFIXCONST char POSTCONST atv_IDS_UPGRADE_SUC_0[]="Upgrade successfully!";
static PREFIXCONST char POSTCONST atv_IDS_UPGRADE_SUC_1[]="升级成功！";

static PREFIXCONST char POSTCONST atv_IDS_INVALID_FILE_0[]="Invalid file!";
static PREFIXCONST char POSTCONST atv_IDS_INVALID_FILE_1[]="无效文件";

static PREFIXCONST char POSTCONST atv_IDS_THEATRE_0[]="Theatre";
static PREFIXCONST char POSTCONST atv_IDS_THEATRE_1[]="剧场";

static PREFIXCONST char POSTCONST atv_IDS_SCAN_CONFIG_0[]="Scan Config";
static PREFIXCONST char POSTCONST atv_IDS_SCAN_CONFIG_1[]="搜索配置";

static PREFIXCONST char POSTCONST atv_IDS_TV_SCAN_CONFIG_0[]="Tv Scan Config";
static PREFIXCONST char POSTCONST atv_IDS_TV_SCAN_CONFIG_1[]="Tv 搜索配置";

static PREFIXCONST char POSTCONST atv_IDS_DTV_SCAN_CONFIG_0[]="Dtv Scan Config";
static PREFIXCONST char POSTCONST atv_IDS_DTV_SCAN_CONFIG_1[]="DTV 搜索配置";

static PREFIXCONST char POSTCONST atv_IDS_START_FREQ_0[]="Start Freq";
static PREFIXCONST char POSTCONST atv_IDS_START_FREQ_1[]="起始频率";

static PREFIXCONST char POSTCONST atv_IDS_END_FREQ_0[]="End Freq";
static PREFIXCONST char POSTCONST atv_IDS_END_FREQ_1[]="结束频率";

static PREFIXCONST char POSTCONST atv_IDS_BANDWIDTH_0[]="Bandwidth";
static PREFIXCONST char POSTCONST atv_IDS_BANDWIDTH_1[]="带  宽";

static PREFIXCONST char POSTCONST atv_IDS_BY_ROLE_0[]="With Role";
static PREFIXCONST char POSTCONST atv_IDS_BY_ROLE_1[]="按频率表";

static PREFIXCONST char POSTCONST atv_IDS_MODULATION_0[]="Modulation";
static PREFIXCONST char POSTCONST atv_IDS_MODULATION_1[]="调制方式";

static PREFIXCONST char POSTCONST atv_IDS_SYMBOL_RATE_0[]="Symbol rate";
static PREFIXCONST char POSTCONST atv_IDS_SYMBOL_RATE_1[]="符号率";

static PREFIXCONST char POSTCONST atv_IDS_FREQUENCY_0[]="Frequency";
static PREFIXCONST char POSTCONST atv_IDS_FREQUENCY_1[]="频率";

static PREFIXCONST char POSTCONST atv_IDS_YES_0[]="YES";
static PREFIXCONST char POSTCONST atv_IDS_YES_1[]="是";

static PREFIXCONST char POSTCONST atv_IDS_NO_0[]="NO";
static PREFIXCONST char POSTCONST atv_IDS_NO_1[]="否";

static PREFIXCONST char POSTCONST atv_IDS_CONFIG_ERROR_0[]="FullScan Config Error";
static PREFIXCONST char POSTCONST atv_IDS_CONFIG_ERROR_1[]="全频段配置错误";

static PREFIXCONST char POSTCONST atv_IDS_START_MANUAL_SCAN_0[]="Do you want to start manual scan？";
static PREFIXCONST char POSTCONST atv_IDS_START_MANUAL_SCAN_1[]="是否开始手动搜索？";

static PREFIXCONST char POSTCONST atv_IDS_END_MANUAL_SCAN_0[]="Do you want to end manual scan？";
static PREFIXCONST char POSTCONST atv_IDS_END_MANUAL_SCAN_1[]="是否结束手动搜索？";

static PREFIXCONST char POSTCONST atv_IDS_END_AUTO_SCAN_0[]="Do you want to end auto scan？";
static PREFIXCONST char POSTCONST atv_IDS_END_AUTO_SCAN_1[]="是否结束自动搜索？";

static PREFIXCONST char POSTCONST atv_IDS_SUB_START_0[]="Subscribed program\n%03d %s \n%s\nwill start at %02d:%02d - %02d:%02d, \nwheater watch it now ?";
static PREFIXCONST char POSTCONST atv_IDS_SUB_START_1[]="您预定的节目\n%03d %s \n%s \n将于%02d:%02d - %02d:%02d播出,\n是否马上收看 ?";

static PREFIXCONST char POSTCONST atv_IDS_SUB_START_CHAN_0[]="Subscribed program\n%03d\n\nwill start at %02d:%02d, \nwheater watch it now ?";
static PREFIXCONST char POSTCONST atv_IDS_SUB_START_CHAN_1[]="您预定的节目\n%03d\n\n将于%02d:%02d播出,\n是否马上收看 ?";

static PREFIXCONST char POSTCONST atv_IDS_EVENT_OUT_OF_TIME_0[]="Program is overdue";
static PREFIXCONST char POSTCONST atv_IDS_EVENT_OUT_OF_TIME_1[]="节目已过期";

static PREFIXCONST char POSTCONST atv_IDS_SUBSCRIBE_FAIL_0[]="Subscribed program fail\nwith subscribed program%s[%s]%02d:%02d - %02d:%02dtime conflict,replace this program？";
static PREFIXCONST char POSTCONST atv_IDS_SUBSCRIBE_FAIL_1[]="节目预定失败\n与预定的节目%s[%s]%02d:%02d - %02d:%02d时间冲突，替换该节目？";

static PREFIXCONST char POSTCONST atv_IDS_SWITCH_USER_MODE_0[]="Switch";
static PREFIXCONST char POSTCONST atv_IDS_SWITCH_USER_MODE_1[]="切换";

static PREFIXCONST char POSTCONST atv_IDS_EPG_HELP_0[]="Page";
static PREFIXCONST char POSTCONST atv_IDS_EPG_HELP_1[]="日期";

static PREFIXCONST char POSTCONST atv_IDS_CHOICE_0[]="Choice";
static PREFIXCONST char POSTCONST atv_IDS_CHOICE_1[]="选择";

static PREFIXCONST char POSTCONST atv_IDS_EPG_LIST_0[]="TV Epg list";
static PREFIXCONST char POSTCONST atv_IDS_EPG_LIST_1[]="电视节目指南";

static PREFIXCONST char POSTCONST atv_IDS_EPG_LIST_RADIO_0[]="Radio Epg list";
static PREFIXCONST char POSTCONST atv_IDS_EPG_LIST_RADIO_1[]="广播节目指南";

static PREFIXCONST char POSTCONST atv_IDS_REPEAT_TIME1_0[]="The book number is full!";
static PREFIXCONST char POSTCONST atv_IDS_REPEAT_TIME1_1[]="已经到达最大预约数 ";

static PREFIXCONST char POSTCONST atv_IDS_REPEAT_TIME_0[]="Time is booked! Overwrite?";
static PREFIXCONST char POSTCONST atv_IDS_REPEAT_TIME_1[]="预约相同时间，是否覆盖? ";

static PREFIXCONST char POSTCONST atv_IDS_PRO_NAME_0[]="Channel";
static PREFIXCONST char POSTCONST atv_IDS_PRO_NAME_1[]="频道";

static PREFIXCONST char POSTCONST atv_IDS_EVENT_NAME_0[]="Program";
static PREFIXCONST char POSTCONST atv_IDS_EVENT_NAME_1[]="节目";

static PREFIXCONST char POSTCONST atv_IDS_EVENT_SYNOPSIS_0[]="Prog Info";
static PREFIXCONST char POSTCONST atv_IDS_EVENT_SYNOPSIS_1[]="节目简介";

static PREFIXCONST char POSTCONST atv_IDS_EPGINFO_0[]="Info";
static PREFIXCONST char POSTCONST atv_IDS_EPGINFO_1[]="信息";

static PREFIXCONST char POSTCONST atv_IDS_LIST_LOOP_0[]="List Loop";
static PREFIXCONST char POSTCONST atv_IDS_LIST_LOOP_1[]="列表循环";

static PREFIXCONST char POSTCONST atv_IDS_SINGNAL_LOOP_0[]="Signal Loop";
static PREFIXCONST char POSTCONST atv_IDS_SINGNAL_LOOP_1[]="单曲循环";

static PREFIXCONST char POSTCONST atv_IDS_RANDOM_LOOP_0[]="Random Loop";
static PREFIXCONST char POSTCONST atv_IDS_RANDOM_LOOP_1[]="随机播放";

static PREFIXCONST char POSTCONST atv_IDS_LIST_PLAY_0[]="List Play";
static PREFIXCONST char POSTCONST atv_IDS_LIST_PLAY_1[]="顺序播放";

static PREFIXCONST char POSTCONST atv_IDS_PLAY_MODE_0[]="Play Mode";
static PREFIXCONST char POSTCONST atv_IDS_PLAY_MODE_1[]="播放模式";

static PREFIXCONST char POSTCONST atv_IDS_CARRIER_FREQ_0[]="carrier freq info";
static PREFIXCONST char POSTCONST atv_IDS_CARRIER_FREQ_1[]="信道载波频谱";

static PREFIXCONST char POSTCONST atv_IDS_DEM_OTHER_INFO_0[]="Other Info ";
static PREFIXCONST char POSTCONST atv_IDS_DEM_OTHER_INFO_1[]="其他信息";

static PREFIXCONST char POSTCONST atv_IDS_DEMO_DETIAL_0[]="demo detial info";
static PREFIXCONST char POSTCONST atv_IDS_DEMO_DETIAL_1[]="解调详细信息";

static PREFIXCONST char POSTCONST atv_IDS_DEM_SCATTER_0[]="Scatter & Demo info";
static PREFIXCONST char POSTCONST atv_IDS_DEM_SCATTER_1[]="星座图和解调基本信息";

static PREFIXCONST char POSTCONST atv_IDS_DEM_HN_0[]="channel Impulse response";
static PREFIXCONST char POSTCONST atv_IDS_DEM_HN_1[]="信道冲击响应";

static PREFIXCONST char POSTCONST atv_IDS_DEM_SP_0[]="channel Spectrum";
static PREFIXCONST char POSTCONST atv_IDS_DEM_SP_1[]="信道频谱";

static PREFIXCONST char POSTCONST atv_IDS_SIGNAL_DETECT_0[]="Signal";
static PREFIXCONST char POSTCONST atv_IDS_SIGNAL_DETECT_1[]="信号检测";

static PREFIXCONST char POSTCONST atv_IDS_STRENGH_BAR_0[]="Strength";
static PREFIXCONST char POSTCONST atv_IDS_STRENGH_BAR_1[]="强度";

static PREFIXCONST char POSTCONST atv_IDS_QUALITY_BAR_0[]="Quality";
static PREFIXCONST char POSTCONST atv_IDS_QUALITY_BAR_1[]="质量";

static PREFIXCONST char POSTCONST atv_IDS_UPDATE_SYMBOL_0[]="Symbol Rate";
static PREFIXCONST char POSTCONST atv_IDS_UPDATE_SYMBOL_1[]="符号率";

static PREFIXCONST char POSTCONST atv_IDS_NET_SEARCH_0[]="Net Search";
static PREFIXCONST char POSTCONST atv_IDS_NET_SEARCH_1[]="网络搜索";

static PREFIXCONST char POSTCONST atv_IDS_START_NET_SCAN_0[]="Do you want to start net scan？";
static PREFIXCONST char POSTCONST atv_IDS_START_NET_SCAN_1[]="是否开始网络搜索？";

static PREFIXCONST char POSTCONST atv_IDS_TV_NET_SCAN_0[]="TV Auto Scan";
static PREFIXCONST char POSTCONST atv_IDS_TV_NET_SCAN_1[]="数字电视网络搜索";

static PREFIXCONST char POSTCONST atv_IDS_END_NET_SCAN_0[]="Do you want to end auto scan？";
static PREFIXCONST char POSTCONST atv_IDS_END_NET_SCAN_1[]="是否结束网络搜索？";

static PREFIXCONST char POSTCONST atv_IDS_EARPHONE_IN_0[]="Earphone inset";
static PREFIXCONST char POSTCONST atv_IDS_EARPHONE_IN_1[]="已插入耳机";

static PREFIXCONST char POSTCONST atv_IDS_EARPHONE_OUT_0[]="Earphone outset";
static PREFIXCONST char POSTCONST atv_IDS_EARPHONE_OUT_1[]="已拔出耳机";

static PREFIXCONST char POSTCONST atv_IDS_SCRAMBLED_PROG_0[]="Scrambled program";
static PREFIXCONST char POSTCONST atv_IDS_SCRAMBLED_PROG_1[]="加密节目";

static PREFIXCONST char POSTCONST atv_IDS_SVN_VERSION_0[]="Svn Version";
static PREFIXCONST char POSTCONST atv_IDS_SVN_VERSION_1[]="Svn版本";

static PREFIXCONST char POSTCONST atv_IDS_BOARD_VER_0[]="Board";
static PREFIXCONST char POSTCONST atv_IDS_BOARD_VER_1[]="硬件版本";

static PREFIXCONST char POSTCONST atv_IDS_NOT_SUPPORT_PIC_SIZE_0[]="Can't support this file！";
static PREFIXCONST char POSTCONST atv_IDS_NOT_SUPPORT_PIC_SIZE_1[]="图片尺寸过大,不支持播放!";

static PREFIXCONST char POSTCONST atv_IDS_NOT_SUPPORT_FILE_0[]="Can't support this file！";
static PREFIXCONST char POSTCONST atv_IDS_NOT_SUPPORT_FILE_1[]="不支持播放该文件";

static PREFIXCONST char POSTCONST atv_IDS_FACTORY_RESET_0[]="Factory reset";
static PREFIXCONST char POSTCONST atv_IDS_FACTORY_RESET_1[]="工厂复位";

static PREFIXCONST char POSTCONST atv_IDS_DELETE_PVR_0[]="Delete PVR";
static PREFIXCONST char POSTCONST atv_IDS_DELETE_PVR_1[]="删除录像";

static PREFIXCONST char POSTCONST atv_IDS_DELETE_PVR_FILE_0[]="Do you want to delete pvr? ";
static PREFIXCONST char POSTCONST atv_IDS_DELETE_PVR_FILE_1[]="是否删除该录像？";

static PREFIXCONST char POSTCONST atv_IDS_EXIT_0[]="Exit";
static PREFIXCONST char POSTCONST atv_IDS_EXIT_1[]="退出";

static PREFIXCONST char POSTCONST atv_IDS_DVI1_0[]="DVI1";
static PREFIXCONST char POSTCONST atv_IDS_DVI1_1[]="DVI1";

static PREFIXCONST char POSTCONST atv_IDS_DVI2_0[]="DVI2";
static PREFIXCONST char POSTCONST atv_IDS_DVI2_1[]="DVI2";

static PREFIXCONST char POSTCONST atv_IDS_UNKNOW_FORMAT_0[]="Unknow format";
static PREFIXCONST char POSTCONST atv_IDS_UNKNOW_FORMAT_1[]="不支持的格式";

static PREFIXCONST char POSTCONST atv_IDS_INPUT_TIME_ERROR_0[]="Input Time is Error!";
static PREFIXCONST char POSTCONST atv_IDS_INPUT_TIME_ERROR_1[]="输入时间无效!";

static PREFIXCONST char POSTCONST atv_IDS_FILE_SIZE_0[]="File Size";
static PREFIXCONST char POSTCONST atv_IDS_FILE_SIZE_1[]="文件大小";

static PREFIXCONST char POSTCONST atv_IDS_BPS_0[]="Bps";
static PREFIXCONST char POSTCONST atv_IDS_BPS_1[]="文件码率";

static PREFIXCONST char POSTCONST atv_IDS_Bitrate_Excess_0[]="Bitrate Excess";
static PREFIXCONST char POSTCONST atv_IDS_Bitrate_Excess_1[]="码率过大";

static PREFIXCONST char POSTCONST atv_IDS_Resolution_0[]="Resolution";
static PREFIXCONST char POSTCONST atv_IDS_Resolution_1[]="分辨率";

static PREFIXCONST char POSTCONST atv_IDS_MULTI_AUDIO_0[]="Multi Audio";
static PREFIXCONST char POSTCONST atv_IDS_MULTI_AUDIO_1[]="伴音切换";

static PREFIXCONST char POSTCONST atv_IDS_LEFT_0[]="Left";
static PREFIXCONST char POSTCONST atv_IDS_LEFT_1[]="左声道";

static PREFIXCONST char POSTCONST atv_IDS_RIGHT_0[]="Right";
static PREFIXCONST char POSTCONST atv_IDS_RIGHT_1[]="右声道";

static PREFIXCONST char POSTCONST atv_IDS_STEREO_0[]="Stereo";
static PREFIXCONST char POSTCONST atv_IDS_STEREO_1[]="立体声";

static PREFIXCONST char POSTCONST atv_IDS_NONE_0[]="None";
static PREFIXCONST char POSTCONST atv_IDS_NONE_1[]="无";

static PREFIXCONST char POSTCONST atv_IDS_ACTION_INVALID_0[]="Invalid action";
static PREFIXCONST char POSTCONST atv_IDS_ACTION_INVALID_1[]="不允许此操作";

static PREFIXCONST char POSTCONST atv_IDS_DEVICE_BITRATE_BAD_0[]="Device bit-rate is bad for rec ";
static PREFIXCONST char POSTCONST atv_IDS_DEVICE_BITRATE_BAD_1[]="磁盘速率过低，不适合录像";

static PREFIXCONST char POSTCONST atv_IDS_RECEIVE_CHOISE_0[]="CA";
static PREFIXCONST char POSTCONST atv_IDS_RECEIVE_CHOISE_1[]="条件接收";

static PREFIXCONST char POSTCONST atv_IDS_RECEIVE_SERIAL_0[]="SERIAL";
static PREFIXCONST char POSTCONST atv_IDS_RECEIVE_SERIAL_1[]="序列化";

static PREFIXCONST char POSTCONST atv_IDS_CHIP_ID_0[]="Chip id";
static PREFIXCONST char POSTCONST atv_IDS_CHIP_ID_1[]="芯片id";

static PREFIXCONST char POSTCONST atv_IDS_VIDEO_FRMART_0[]="Video: ";
static PREFIXCONST char POSTCONST atv_IDS_VIDEO_FRMART_1[]="视频：";

static PREFIXCONST char POSTCONST atv_IDS_AUDIO_FRMART_0[]="Audio: ";
static PREFIXCONST char POSTCONST atv_IDS_AUDIO_FRMART_1[]="音频：";

static PREFIXCONST char POSTCONST atv_IDS_NEW_SOFTWARE_0[]="New Software";
static PREFIXCONST char POSTCONST atv_IDS_NEW_SOFTWARE_1[]="软件更新";

static PREFIXCONST char POSTCONST atv_IDS_SW_UPDATE_0[]="New software found,update now?";
static PREFIXCONST char POSTCONST atv_IDS_SW_UPDATE_1[]="已有新版本软件，是否立即升级？";

static PREFIXCONST char POSTCONST atv_IDS_SW_UPDATE_MUST_0[]="New software found,system will update automatic,please do not power off!";
static PREFIXCONST char POSTCONST atv_IDS_SW_UPDATE_MUST_1[]="已有新版本软件，将自动进行升级，请勿断电！";

#ifndef D_TV_UI_STYLE_MINI
static PREFIXCONST char POSTCONST atv_IDS_DVBS_SEARCH_0[]="DVBS Search";
static PREFIXCONST char POSTCONST atv_IDS_DVBS_SEARCH_1[]="DVBS搜索";

static PREFIXCONST char POSTCONST atv_IDS_SET_ANTENNA_0[]="Set Antenna";
static PREFIXCONST char POSTCONST atv_IDS_SET_ANTENNA_1[]="设置天线";

static PREFIXCONST char POSTCONST atv_IDS_SATELLITE_0[]="Satellite";
static PREFIXCONST char POSTCONST atv_IDS_SATELLITE_1[]="卫星";

static PREFIXCONST char POSTCONST atv_IDS_LNB_FREQ_0[]="LNB Freq";
static PREFIXCONST char POSTCONST atv_IDS_LNB_FREQ_1[]="LNB频率";

static PREFIXCONST char POSTCONST atv_IDS_TRANSPONDER_LIST_0[]="TP List";
static PREFIXCONST char POSTCONST atv_IDS_TRANSPONDER_LIST_1[]="转发器";

static PREFIXCONST char POSTCONST atv_IDS_22K_0[]="22K";
static PREFIXCONST char POSTCONST atv_IDS_22K_1[]="22K";

static PREFIXCONST char POSTCONST atv_IDS_TP_SCAN_0[]="TP Scan";
static PREFIXCONST char POSTCONST atv_IDS_TP_SCAN_1[]="单频点搜索";

static PREFIXCONST char POSTCONST atv_IDS_SATE_SCAN_0[]="Satellite Scan";
static PREFIXCONST char POSTCONST atv_IDS_SATE_SCAN_1[]="卫星搜索";

static PREFIXCONST char POSTCONST atv_IDS_SIGNAL_INTENSITY_0[]="Intensity";
static PREFIXCONST char POSTCONST atv_IDS_SIGNAL_INTENSITY_1[]="信号强度";

static PREFIXCONST char POSTCONST atv_IDS_SIGNAL_QUALITY_0[]="Quality";
static PREFIXCONST char POSTCONST atv_IDS_SIGNAL_QUALITY_1[]="信号质量";

static PREFIXCONST char POSTCONST atv_IDS_POLARITY_0[]="Polarity";
static PREFIXCONST char POSTCONST atv_IDS_POLARITY_1[]="极化方式";

static PREFIXCONST char POSTCONST atv_IDS_ADD_TP_0[]="Add Tp";
static PREFIXCONST char POSTCONST atv_IDS_ADD_TP_1[]="增加转发器";

static PREFIXCONST char POSTCONST atv_IDS_EDIT_TP_0[]="Edit Tp";
static PREFIXCONST char POSTCONST atv_IDS_EDIT_TP_1[]="编辑转发器";

static PREFIXCONST char POSTCONST atv_IDS_WIFI_SETTING_0[]="WIFI SETTING";
static PREFIXCONST char POSTCONST atv_IDS_WIFI_SETTING_1[]="WIFI 设置";

static PREFIXCONST char POSTCONST atv_IDS_WIFI_DISPLAY_0[]="Miracast";
static PREFIXCONST char POSTCONST atv_IDS_WIFI_DISPLAY_1[]="手机投屏";

static PREFIXCONST char POSTCONST atv_IDS_DEVICE_NAME_0[]="DEVICE_NAME";
static PREFIXCONST char POSTCONST atv_IDS_DEVICE_NAME_1[]="设备名称:";

static PREFIXCONST char POSTCONST atv_IDS_NET_MODE_0[]="Mode";
static PREFIXCONST char POSTCONST atv_IDS_NET_MODE_1[]="模式";

static PREFIXCONST char POSTCONST atv_IDS_IPADDRESS_0[]="IP Address";
static PREFIXCONST char POSTCONST atv_IDS_IPADDRESS_1[]="IP地址";

static PREFIXCONST char POSTCONST atv_IDS_SUBNET_MASK_0[]="Net Mask";
static PREFIXCONST char POSTCONST atv_IDS_SUBNET_MASK_1[]="掩码";

static PREFIXCONST char POSTCONST atv_IDS_GATE_WAY_0[]="Gate Way";
static PREFIXCONST char POSTCONST atv_IDS_GATE_WAY_1[]="网关";

static PREFIXCONST char POSTCONST atv_IDS_DNS_0[]="DNS";
static PREFIXCONST char POSTCONST atv_IDS_DNS_1[]="DNS";

static PREFIXCONST char POSTCONST atv_IDS_MAC_0[]="MAC";
static PREFIXCONST char POSTCONST atv_IDS_MAC_1[]="MAC";

static PREFIXCONST char POSTCONST atv_IDS_SCAN_0[]="Scan";
static PREFIXCONST char POSTCONST atv_IDS_SCAN_1[]="扫描";

static PREFIXCONST char POSTCONST atv_IDS_DELETE_0[]="Delete";
static PREFIXCONST char POSTCONST atv_IDS_DELETE_1[]="删除";

static PREFIXCONST char POSTCONST atv_IDS_CAPS_0[]="A-a";
static PREFIXCONST char POSTCONST atv_IDS_CAPS_1[]="大小写";

static PREFIXCONST char POSTCONST atv_IDS_NUMBER_0[]="number";
static PREFIXCONST char POSTCONST atv_IDS_NUMBER_1[]="数字";

static PREFIXCONST char POSTCONST atv_IDS_NUMBER_0TO9_0[]="0~9";
static PREFIXCONST char POSTCONST atv_IDS_NUMBER_0TO9_1[]="0~9";

static PREFIXCONST char POSTCONST atv_IDS_ZHILIAN_TV_0[]="ZhiLian Tv";
static PREFIXCONST char POSTCONST atv_IDS_ZHILIAN_TV_1[]="智联电视";

static PREFIXCONST char POSTCONST atv_IDS_NETWORK_SHARING_0[]="DLNA";
static PREFIXCONST char POSTCONST atv_IDS_NETWORK_SHARING_1[]="DLNA投屏";

static PREFIXCONST char POSTCONST atv_IDS_DTV_SHAREING_0[]="DTV Sharing";
static PREFIXCONST char POSTCONST atv_IDS_DTV_SHAREING_1[]="电视转发";
#endif

static PREFIXCONST char POSTCONST *language_prefix_English[]={
	atv_IDS_NULL_0,		// atv_atv_IDS_NULL
	atv_IDS_CONTRAST_0,		// atv_atv_IDS_CONTRAST
	atv_IDS_BRIGHTNESS_0,		// atv_atv_IDS_BRIGHTNESS
	atv_IDS_COLOR_0,		// atv_atv_IDS_COLOR
	atv_IDS_SHARPNESS_0,		// atv_atv_IDS_SHARPNESS
	atv_IDS_PICTURE_MODE_0,		// atv_atv_IDS_PICTURE_MODE
	atv_IDS_ASPECT_RATIO_0,		// atv_atv_IDS_ASPECT_RATIO
	atv_IDS_COLOR_TEMP_0,		// atv_atv_IDS_COLOR_TEMP
	atv_IDS_PICTURE_0,		// atv_atv_IDS_PICTURE
	atv_IDS_SOUND_0,		// atv_atv_IDS_SOUND
	atv_IDS_CHANNEL_0,		// atv_atv_IDS_CHANNEL
	atv_IDS_FUNCTION_0,		// atv_atv_IDS_FUNCTION
	atv_IDS_ADJUST_0,		// atv_atv_IDS_ADJUST
	atv_IDS_TIME_0,		// atv_atv_IDS_TIME
	atv_IDS_BACK_0,		// atv_atv_IDS_BACK
	atv_IDS_MOVE_0,		// atv_atv_IDS_MOVE
	atv_IDS_OK_0,		// atv_atv_IDS_OK
	atv_IDS_TINT_0,		// atv_atv_IDS_TINT
	atv_IDS_VOLUME_0,		// atv_atv_IDS_VOLUME
	atv_IDS_BALANCE_0,		// atv_atv_IDS_BALANCE
	atv_IDS_DIGITAL_TONE_0,		// atv_atv_IDS_DIGITAL_TONE
	atv_IDS_SRS_0,		// atv_atv_IDS_SRS
	atv_IDS_AVL_0,		// atv_atv_IDS_AVL
	atv_IDS_PROGRAM_EDIT_0,		// atv_atv_IDS_PROGRAM_EDIT
	atv_IDS_AUTO_TUNING_0,		// atv_atv_IDS_AUTO_TUNING
	atv_IDS_EXCHANGE_0,		// atv_atv_IDS_EXCHANGE
	atv_IDS_OSD_LANGUAGE_0,		// atv_atv_IDS_OSD_LANGUAGE
	atv_IDS_MENU_TIMEOUT_0,		// atv_atv_IDS_MENU_TIMEOUT
	atv_IDS_DNR_0,		// atv_atv_IDS_DNR
	atv_IDS_BULE_SCREEN_0,		// atv_atv_IDS_BULE_SCREEN
	atv_IDS_BACKLIGHT_0,		// atv_atv_IDS_BACKLIGHT
	atv_IDS_RESET_0,		// atv_atv_IDS_RESET
	atv_IDS_IMAGE_POSITION_0,		// atv_atv_IDS_IMAGE_POSITION
	atv_IDS_HORIZONTAL_AMPLITUDE_0,		// atv_atv_IDS_HORIZONTAL_AMPLITUDE
	atv_IDS_VERTICAL_AMPLITUDE_0,		// atv_atv_IDS_VERTICAL_AMPLITUDE
	atv_IDS_AUTO_ADJUST_0,		// atv_atv_IDS_AUTO_ADJUST
	atv_IDS_CLOCK_0,		// atv_atv_IDS_CLOCK
	atv_IDS_PHASE_0,		// atv_atv_IDS_PHASE
	atv_IDS_CURRENT_TIME_0,		// atv_atv_IDS_CURRENT_TIME
	atv_IDS_OFF_TIME_0,		// atv_atv_IDS_OFF_TIME
	atv_IDS_ON_TIME_0,		// atv_atv_IDS_ON_TIME
	atv_IDS_ON_CHANNEL_0,		// atv_atv_IDS_ON_CHANNEL
	atv_IDS_REMIND_TIME_0,		// atv_atv_IDS_REMIND_TIME
	atv_IDS_REMIND_CHANNEL_0,		// atv_atv_IDS_REMIND_CHANNEL
	atv_IDS_SLEEP_TIMER_0,		// atv_atv_IDS_SLEEP_TIMER
	atv_IDS_TV_0,		// atv_atv_IDS_TV
	atv_IDS_DTV_0,		// atv_atv_IDS_DTV
	atv_IDS_AV_0,		// atv_atv_IDS_AV
	atv_IDS_AV1_0,		// atv_atv_IDS_AV1
	atv_IDS_AV2_0,		// atv_atv_IDS_AV2
	atv_IDS_YPBPR_0,		// atv_atv_IDS_YPBPR
	atv_IDS_HDMI_0,		// atv_atv_IDS_HDMI
	atv_IDS_HDMI1_0,		// atv_atv_IDS_HDMI1
	atv_IDS_HDMI2_0,		// atv_atv_IDS_HDMI2
	atv_IDS_PC_0,		// atv_atv_IDS_PC
	atv_IDS_USB_0,		// atv_atv_IDS_USB
	atv_IDS_SOURCE_0,		// atv_atv_IDS_SOURCE
	atv_IDS_STANDARD_0,		// atv_atv_IDS_STANDARD
	atv_IDS_MILD_0,		// atv_atv_IDS_MILD
	atv_IDS_USER_0,		// atv_atv_IDS_USER
	atv_IDS_LIGHT_0,		// atv_atv_IDS_LIGHT
	atv_IDS_FULL_SCREEN_0,		// atv_atv_IDS_FULL_SCREEN
	atv_IDS_4TO3_0,		// atv_atv_IDS_4TO3
	atv_IDS_ZOOM_0,		// atv_atv_IDS_ZOOM
	atv_IDS_PANORAMA_0,		// atv_atv_IDS_PANORAMA
	atv_IDS_WARM_0,		// atv_atv_IDS_WARM
	atv_IDS_COOL_0,		// atv_atv_IDS_COOL
	atv_IDS_ON_0,		// atv_atv_IDS_ON
	atv_IDS_OFF_0,		// atv_atv_IDS_OFF
	atv_IDS_PROGRAM_MANAGE_0,		// atv_atv_IDS_PROGRAM_MANAGE
	atv_IDS_MANUAL_SEARCH_0,		// atv_atv_IDS_MANUAL_SEARCH
	atv_IDS_FINE_TUNE_0,		// atv_atv_IDS_FINE_TUNE
	atv_IDS_COLOR_SYSTEM_0,		// atv_atv_IDS_COLOR_SYSTEM
	atv_IDS_SOUND_SYSTEM_0,		// atv_atv_IDS_SOUND_SYSTEM
	atv_IDS_SKIP_0,		// atv_atv_IDS_SKIP
	atv_IDS_CANCEL_0,		// atv_atv_IDS_CANCEL
	atv_IDS_START_AUTO_SCAN_0,		// atv_atv_IDS_START_AUTO_SCAN
	atv_IDS_ENGLISH_0,		// atv_atv_IDS_ENGLISH
	atv_IDS_CHINESE_0,		// atv_atv_IDS_CHINESE
	atv_IDS_HORIZONTAL_POS_0,		// atv_atv_IDS_HORIZONTAL_POS
	atv_IDS_VERTICAL_POS_0,		// atv_atv_IDS_VERTICAL_POS
	atv_IDS_15_MINUTE_0,		// atv_atv_IDS_15_MINUTE
	atv_IDS_30_MINUTE_0,		// atv_atv_IDS_30_MINUTE
	atv_IDS_60_MINUTE_0,		// atv_atv_IDS_60_MINUTE
	atv_IDS_120_MINUTE_0,		// atv_atv_IDS_120_MINUTE
	atv_IDS_240_MINUTE_0,		// atv_atv_IDS_240_MINUTE
	atv_IDS_PTP_0,		// atv_atv_IDS_PTP
	atv_IDS_5_S_0,		// atv_atv_IDS_5_S
	atv_IDS_10_S_0,		// atv_atv_IDS_10_S
	atv_IDS_15_S_0,		// atv_atv_IDS_15_S
	atv_IDS_CURRENT_CHANNEL_0,		// atv_atv_IDS_CURRENT_CHANNEL
	atv_IDS_TO_CHANNEL_0,		// atv_atv_IDS_TO_CHANNEL
	atv_IDS_MENU_0,		// atv_atv_IDS_MENU
	atv_IDS_MOVIE_0,		// atv_atv_IDS_MOVIE
	atv_IDS_MUSIC_0,		// atv_atv_IDS_MUSIC
	atv_IDS_SETTING_0,		// atv_atv_IDS_SETTING
	atv_IDS_PLAY_0,		// atv_atv_IDS_PLAY
	atv_IDS_PAUSE_0,		// atv_atv_IDS_PAUSE
	atv_IDS_PICTURE_SPEED_0,		// atv_atv_IDS_PICTURE_SPEED
	atv_IDS_UP_LEVEL_0,		// atv_atv_IDS_UP_LEVEL
	atv_IDS_HIGH_SPEED_0,		// atv_atv_IDS_HIGH_SPEED
	atv_IDS_LOW_SPEED_0,		// atv_atv_IDS_LOW_SPEED
	atv_IDS_MIDDLE_SPEED_0,		// atv_atv_IDS_MIDDLE_SPEED
	atv_IDS_PICTURE_OPTIMIZE_0,		// atv_atv_IDS_PICTURE_OPTIMIZE
	atv_IDS_HIGH_0,		// atv_atv_IDS_HIGH
	atv_IDS_LOW_0,		// atv_atv_IDS_LOW
	atv_IDS_MIDDLE_0,		// atv_atv_IDS_MIDDLE
	atv_IDS_LAST_0,		// atv_atv_IDS_LAST
	atv_IDS_NEXT_0,		// atv_atv_IDS_NEXT
	atv_IDS_ROTATE_0,		// atv_atv_IDS_ROTATE
	atv_IDS_STOP_AUTO_SCAN_0,		// atv_atv_IDS_STOP_AUTO_SCAN
	atv_IDS_CHANNEL_LIST_0,		// atv_atv_IDS_CHANNEL_LIST
	atv_IDS_TV_MANUAL_SCAN_0,		// atv_atv_IDS_TV_MANUAL_SCAN
	atv_IDS_CHANNEL_SCAN_0,		// atv_atv_IDS_CHANNEL_SCAN
	atv_IDS_NO_SIGNAL_0,		// atv_atv_IDS_NO_SIGNAL
	atv_IDS_BAD_0,		// atv_atv_IDS_BAD
	atv_IDS_GOOD_0,		// atv_atv_IDS_GOOD
	atv_IDS_FREQ_0,		// atv_atv_IDS_FREQ
	atv_IDS_DIGI_TV_0,		// atv_atv_IDS_DIGI_TV
	atv_IDS_DIGI_RADIO_0,		// atv_atv_IDS_DIGI_RADIO
	atv_IDS_QUIT_0,		// atv_atv_IDS_QUIT
	atv_IDS_CH_ID_0,		// atv_atv_IDS_CH_ID
	atv_IDS_EBOOK_0,		// atv_atv_IDS_EBOOK
	atv_IDS_STOP_0,		// atv_atv_IDS_STOP
	atv_IDS_AV_SIGNAL_SELECT_0,		// atv_atv_IDS_AV_SIGNAL_SELECT
	atv_IDS_AV_SIGNAL_0,		// atv_atv_IDS_AV_SIGNAL
	atv_IDS_DVBC_0,		// atv_atv_IDS_DVBC
	atv_IDS_DTMB_0,		// atv_atv_IDS_DTMB
	atv_IDS_NO_USB_0,		// atv_atv_IDS_NO_USB
	atv_IDS_USB_CONNECT_0,		// atv_atv_IDS_USB_CONNECT
	atv_IDS_USB_DIS_CONNECT_0,		// atv_atv_IDS_USB_DIS_CONNECT
	atv_IDS_SEARCH_AUTO_0,		// atv_atv_IDS_SEARCH_AUTO
	atv_IDS_SEARCH_PAL_0,		// atv_atv_IDS_SEARCH_PAL
	atv_IDS_SEARCH_SECAM_0,		// atv_atv_IDS_SEARCH_SECAM
	atv_IDS_SEARCH_NTSC_0,		// atv_atv_IDS_SEARCH_NTSC
	atv_IDS_SEARCH_DK_0,		// atv_atv_IDS_SEARCH_DK
	atv_IDS_SEARCH_BG_0,		// atv_atv_IDS_SEARCH_BG
	atv_IDS_SEARCH_I_0,		// atv_atv_IDS_SEARCH_I
	atv_IDS_SEARCH_M_0,		// atv_atv_IDS_SEARCH_M
	atv_IDS_DEFAULT_SET_0,		// atv_atv_IDS_DEFAULT_SET
	atv_IDS_RESTORE_OK_0,		// atv_atv_IDS_RESTORE_OK
	atv_IDS_PROMPT_INFO_0,		// atv_atv_IDS_PROMPT_INFO
	atv_IDS_PLAY_FAILED_0,		// atv_atv_IDS_PLAY_FAILED
	atv_IDS_FREQ_SEARCH_0,		// atv_atv_IDS_FREQ_SEARCH
	atv_IDS_TV_AUTO_SCAN_0,		// atv_atv_IDS_TV_AUTO_SCAN
	atv_IDS_START_ALL_SCAN_0,		// atv_atv_IDS_START_ALL_SCAN
	atv_IDS_END_ALL_SCAN_0,		// atv_atv_IDS_END_ALL_SCAN
	atv_IDS_SCANNING_0,		// atv_atv_IDS_SCANNING
	atv_IDS_MONDAY_0,		// atv_atv_IDS_MONDAY
	atv_IDS_TUESDAY_0,		// atv_atv_IDS_TUESDAY
	atv_IDS_WENDSDAY_0,		// atv_atv_IDS_WENDSDAY
	atv_IDS_THURSDAY_0,		// atv_atv_IDS_THURSDAY
	atv_IDS_FRIDAY_0,		// atv_atv_IDS_FRIDAY
	atv_IDS_SATURDAY_0,		// atv_atv_IDS_SATURDAY
	atv_IDS_SUNDAY_0,		// atv_atv_IDS_SUNDAY
	atv_IDS_INIT_TV_0,		// atv_atv_IDS_INIT_TV
	atv_IDS_GENERAL_SETTING_0,		// atv_atv_IDS_GENERAL_SETTING
	atv_IDS_DEBUG_0,		// atv_atv_IDS_DEBUG
	atv_IDS_SW_INFORMATION_0,		// atv_atv_IDS_SW_INFORMATION
	atv_IDS_SOFTWARE_UPDATE_0,		// atv_atv_IDS_SOFTWARE_UPDATE
	atv_IDS_INIT_FAC_CHANNEL_0,		// atv_atv_IDS_INIT_FAC_CHANNEL
	atv_IDS_BURN_MODE_0,		// atv_atv_IDS_BURN_MODE
	atv_IDS_INIT_ALL_FOR_BOE_0,		// atv_atv_IDS_INIT_ALL_FOR_BOE
	atv_IDS_HOTEL_MODE_0,		// atv_atv_IDS_HOTEL_MODE
	atv_IDS_SOURCE_LOCK_0,		// atv_atv_IDS_SOURCE_LOCK
	atv_IDS_CHANNEL_LOCK_0,		// atv_atv_IDS_CHANNEL_LOCK
	atv_IDS_DEFAULT_SOURCE_0,		// atv_atv_IDS_DEFAULT_SOURCE
	atv_IDS_DEFAULT_PROG_0,		// atv_atv_IDS_DEFAULT_PROG
	atv_IDS_MAX_VOLUME_0,		// atv_atv_IDS_MAX_VOLUME
	atv_IDS_DEFAULT_VOLUME_0,		// atv_atv_IDS_DEFAULT_VOLUME
	atv_IDS_POWER_DOWN_RESET_0,		// atv_atv_IDS_POWER_DOWN_RESET
	atv_IDS_RESET_HOTEL_0,		// atv_atv_IDS_RESET_HOTEL
	atv_IDS_EXPORT_SETTINGS_0,		// atv_atv_IDS_EXPORT_SETTINGS
	atv_IDS_IMPORT_SETTINGS_0,		// atv_atv_IDS_IMPORT_SETTINGS
	atv_IDS_KEY_LOCK_0,		// atv_atv_IDS_KEY_LOCK
	atv_IDS_CAPTURE_LOGO_0,		// atv_atv_IDS_CAPTURE_LOGO
	atv_IDS_LOGO_0,		// atv_atv_IDS_LOGO
	atv_IDS_DEFAULT_0,		// atv_atv_IDS_DEFAULT
	atv_IDS_ADC_ADJUST_0,		// atv_atv_IDS_ADC_ADJUST
	atv_IDS_EMC_SETTING_0,		// atv_atv_IDS_EMC_SETTING
	atv_IDS_BUILD_TIME_0,		// atv_atv_IDS_BUILD_TIME
	atv_IDS_VERSION_0,		// atv_atv_IDS_VERSION
	atv_IDS_LVDS_MAP_0,		// atv_atv_IDS_LVDS_MAP
	atv_IDS_POWER_MODE_0,		// atv_atv_IDS_POWER_MODE
	atv_IDS_WHITE_PATTERN_0,		// atv_atv_IDS_WHITE_PATTERN
	atv_IDS_PWM_0,		// atv_atv_IDS_PWM
	atv_IDS_POWER_REF_0,		// atv_atv_IDS_POWER_REF
	atv_IDS_POWER_DIM_0,		// atv_atv_IDS_POWER_DIM
	atv_IDS_BACKLIGHT_MAX_0,		// atv_atv_IDS_BACKLIGHT_MAX
	atv_IDS_BACKLIGHT_LEVEL_0,		// atv_atv_IDS_BACKLIGHT_LEVEL
	atv_IDS_BACKLIGHT_STEP_0,		// atv_atv_IDS_BACKLIGHT_STEP
	atv_IDS_STEP_TIME_0,		// atv_atv_IDS_STEP_TIME
	atv_IDS_FACTORY_SETTING_0,		// atv_atv_IDS_FACTORY_SETTING
	atv_IDS_NO_PROGRAM_0,		// atv_atv_IDS_NO_PROGRAM
	atv_IDS_SOUND_BACKLIGHT_0,		// atv_atv_IDS_SOUND_BACKLIGHT
	atv_IDS_WB_ADJUST_0,		// atv_atv_IDS_WB_ADJUST
	atv_IDS_PQ_NONLINEAR_0,		// atv_atv_IDS_PQ_NONLINEAR
	atv_IDS_SOUND_MODE_0,		// atv_atv_IDS_SOUND_MODE
	atv_IDS_VOLUME_CURVE_0,		// atv_atv_IDS_VOLUME_CURVE
	atv_IDS_SATURATION_0,		// atv_atv_IDS_SATURATION
	atv_IDS_PVR_0,		// atv_atv_IDS_PVR
	atv_IDS_STOP_RECORD_0,		// atv_atv_IDS_STOP_RECORD
	atv_IDS_ENTER_RECORD_0,		// atv_atv_IDS_ENTER_RECORD
	atv_IDS_RECORD_FAILED_0,		// atv_atv_IDS_RECORD_FAILED
	atv_IDS_RECORD_TIME_OUT_0,		// atv_atv_IDS_RECORD_TIME_OUT
	atv_IDS_NO_SPACE_0,		// atv_atv_IDS_NO_SPACE
	atv_IDS_REICORD_FILE_LARGE_0,		// atv_atv_IDS_REICORD_FILE_LARGE
	atv_IDS_BAD_SIGNAL_SAVING_0,		// atv_atv_IDS_BAD_SIGNAL_SAVING
	atv_IDS_DEVICE_REMOVED_0,		// atv_atv_IDS_DEVICE_REMOVED
	atv_IDS_RECORD_NOT_CHANGE_CHANNEL_0,		// atv_atv_IDS_RECORD_NOT_CHANGE_CHANNEL
	atv_IDS_NO_FIND_DISK_0,		// atv_atv_IDS_NO_FIND_DISK
	atv_IDS_RED_INPUT_0,		// atv_atv_IDS_RED_INPUT
	atv_IDS_BOXINFORMATION_0,		// atv_atv_IDS_BOXINFORMATION
	atv_IDS_PRODUCECOMPANY_0,		// atv_atv_IDS_PRODUCECOMPANY
	atv_IDS_HARDWAREEDITION_0,		// atv_atv_IDS_HARDWAREEDITION
	atv_IDS_SOFTWAREEDITION_0,		// atv_atv_IDS_SOFTWAREEDITION
	atv_IDS_SERIALNUMBER_0,		// atv_atv_IDS_SERIALNUMBER
	atv_IDS_COMPANYID_0,		// atv_atv_IDS_COMPANYID
	atv_IDS_UPGRADE_FAIL_0,		// atv_atv_IDS_UPGRADE_FAIL
	atv_IDS_UPGRADE_SUC_0,		// atv_atv_IDS_UPGRADE_SUC
	atv_IDS_INVALID_FILE_0,		// atv_atv_IDS_INVALID_FILE
	atv_IDS_THEATRE_0,		// atv_atv_IDS_THEATRE
	atv_IDS_SCAN_CONFIG_0,		// atv_atv_IDS_SCAN_CONFIG
	atv_IDS_TV_SCAN_CONFIG_0,		// atv_atv_IDS_TV_SCAN_CONFIG
	atv_IDS_DTV_SCAN_CONFIG_0,		// atv_atv_IDS_DTV_SCAN_CONFIG
	atv_IDS_START_FREQ_0,		// atv_atv_IDS_START_FREQ
	atv_IDS_END_FREQ_0,		// atv_atv_IDS_END_FREQ
	atv_IDS_BANDWIDTH_0,		// atv_atv_IDS_BANDWIDTH
	atv_IDS_BY_ROLE_0,		// atv_atv_IDS_BY_ROLE
	atv_IDS_MODULATION_0,		// atv_atv_IDS_MODULATION
	atv_IDS_SYMBOL_RATE_0,		// atv_atv_IDS_SYMBOL_RATE
	atv_IDS_FREQUENCY_0,		// atv_atv_IDS_FREQUENCY
	atv_IDS_YES_0,		// atv_atv_IDS_YES
	atv_IDS_NO_0,		// atv_atv_IDS_NO
	atv_IDS_CONFIG_ERROR_0,		// atv_atv_IDS_CONFIG_ERROR
	atv_IDS_START_MANUAL_SCAN_0,		// atv_atv_IDS_START_MANUAL_SCAN
	atv_IDS_END_MANUAL_SCAN_0,		// atv_atv_IDS_END_MANUAL_SCAN
	atv_IDS_END_AUTO_SCAN_0,		// atv_atv_IDS_END_AUTO_SCAN
	atv_IDS_SUB_START_0,		// atv_atv_IDS_SUB_START
	atv_IDS_SUB_START_CHAN_0,		// atv_atv_IDS_SUB_START_CHAN
	atv_IDS_EVENT_OUT_OF_TIME_0,		// atv_atv_IDS_EVENT_OUT_OF_TIME
	atv_IDS_SUBSCRIBE_FAIL_0,		// atv_atv_IDS_SUBSCRIBE_FAIL
	atv_IDS_SWITCH_USER_MODE_0,		// atv_atv_IDS_SWITCH_USER_MODE
	atv_IDS_EPG_HELP_0,		// atv_atv_IDS_EPG_HELP
	atv_IDS_CHOICE_0,		// atv_atv_IDS_CHOICE
	atv_IDS_EPG_LIST_0,		// atv_atv_IDS_EPG_LIST
	atv_IDS_EPG_LIST_RADIO_0,		// atv_atv_IDS_EPG_LIST_RADIO
	atv_IDS_REPEAT_TIME1_0,		// atv_atv_IDS_REPEAT_TIME1
	atv_IDS_REPEAT_TIME_0,		// atv_atv_IDS_REPEAT_TIME
	atv_IDS_PRO_NAME_0,		// atv_atv_IDS_PRO_NAME
	atv_IDS_EVENT_NAME_0,		// atv_atv_IDS_EVENT_NAME
	atv_IDS_EVENT_SYNOPSIS_0,		// atv_atv_IDS_EVENT_SYNOPSIS
	atv_IDS_EPGINFO_0,		// atv_atv_IDS_EPGINFO
	atv_IDS_LIST_LOOP_0,		// atv_atv_IDS_LIST_LOOP
	atv_IDS_SINGNAL_LOOP_0,		// atv_atv_IDS_SINGNAL_LOOP
	atv_IDS_RANDOM_LOOP_0,		// atv_atv_IDS_RANDOM_LOOP
	atv_IDS_LIST_PLAY_0,		// atv_atv_IDS_LIST_PLAY
	atv_IDS_PLAY_MODE_0,		// atv_atv_IDS_PLAY_MODE
	atv_IDS_CARRIER_FREQ_0,		// atv_atv_IDS_CARRIER_FREQ
	atv_IDS_DEM_OTHER_INFO_0,		// atv_atv_IDS_DEM_OTHER_INFO
	atv_IDS_DEMO_DETIAL_0,		// atv_atv_IDS_DEMO_DETIAL
	atv_IDS_DEM_SCATTER_0,		// atv_atv_IDS_DEM_SCATTER
	atv_IDS_DEM_HN_0,		// atv_atv_IDS_DEM_HN
	atv_IDS_DEM_SP_0,		// atv_atv_IDS_DEM_SP
	atv_IDS_SIGNAL_DETECT_0,		// atv_atv_IDS_SIGNAL_DETECT
	atv_IDS_STRENGH_BAR_0,		// atv_atv_IDS_STRENGH_BAR
	atv_IDS_QUALITY_BAR_0,		// atv_atv_IDS_QUALITY_BAR
	atv_IDS_UPDATE_SYMBOL_0,		// atv_atv_IDS_UPDATE_SYMBOL
	atv_IDS_NET_SEARCH_0,		// atv_atv_IDS_NET_SEARCH
	atv_IDS_START_NET_SCAN_0,		// atv_atv_IDS_START_NET_SCAN
	atv_IDS_TV_NET_SCAN_0,		// atv_atv_IDS_TV_NET_SCAN
	atv_IDS_END_NET_SCAN_0,		// atv_atv_IDS_END_NET_SCAN
	atv_IDS_EARPHONE_IN_0,		// atv_atv_IDS_EARPHONE_IN
	atv_IDS_EARPHONE_OUT_0,		// atv_atv_IDS_EARPHONE_OUT
	atv_IDS_SCRAMBLED_PROG_0,		// atv_atv_IDS_SCRAMBLED_PROG
	atv_IDS_SVN_VERSION_0,		// atv_atv_IDS_SVN_VERSION
	atv_IDS_BOARD_VER_0,		// atv_atv_IDS_BOARD_VER
	atv_IDS_NOT_SUPPORT_PIC_SIZE_0,		// atv_atv_IDS_NOT_SUPPORT_PIC_SIZE
	atv_IDS_NOT_SUPPORT_FILE_0,		// atv_atv_IDS_NOT_SUPPORT_FILE
	atv_IDS_FACTORY_RESET_0,		// atv_atv_IDS_FACTORY_RESET
	atv_IDS_DELETE_PVR_0,		// atv_atv_IDS_DELETE_PVR
	atv_IDS_DELETE_PVR_FILE_0,		// atv_atv_IDS_DELETE_PVR_FILE
	atv_IDS_EXIT_0,		// atv_atv_IDS_EXIT
	atv_IDS_DVI1_0,		// atv_atv_IDS_DVI1
	atv_IDS_DVI2_0,		// atv_atv_IDS_DVI2
	atv_IDS_UNKNOW_FORMAT_0,		// atv_atv_IDS_UNKNOW_FORMAT
	atv_IDS_INPUT_TIME_ERROR_0,		// atv_atv_IDS_INPUT_TIME_ERROR
	atv_IDS_FILE_SIZE_0,		// atv_atv_IDS_FILE_SIZE
	atv_IDS_BPS_0,		// atv_atv_IDS_BPS
	atv_IDS_Bitrate_Excess_0,		// atv_atv_IDS_Bitrate_Excess
	atv_IDS_Resolution_0,		// atv_atv_IDS_Resolution
	atv_IDS_MULTI_AUDIO_0,		// atv_atv_IDS_MULTI_AUDIO
	atv_IDS_LEFT_0,		// atv_atv_IDS_LEFT
	atv_IDS_RIGHT_0,		// atv_atv_IDS_RIGHT
	atv_IDS_STEREO_0,		// atv_atv_IDS_STEREO
	atv_IDS_NONE_0,		// atv_atv_IDS_NONE
	atv_IDS_ACTION_INVALID_0,		// atv_atv_IDS_ACTION_INVALID
	atv_IDS_DEVICE_BITRATE_BAD_0,		// atv_atv_IDS_DEVICE_BITRATE_BAD
	atv_IDS_RECEIVE_CHOISE_0,		// atv_atv_IDS_RECEIVE_CHOISE
	atv_IDS_RECEIVE_SERIAL_0,		// atv_atv_IDS_RECEIVE_SERIAL
	atv_IDS_CHIP_ID_0,		// atv_atv_IDS_CHIP_ID
	atv_IDS_VIDEO_FRMART_0,		// atv_atv_IDS_VIDEO_FRMART
	atv_IDS_AUDIO_FRMART_0,		// atv_atv_IDS_AUDIO_FRMART
	atv_IDS_NEW_SOFTWARE_0,		// atv_atv_IDS_NEW_SOFTWARE
	atv_IDS_SW_UPDATE_0,		// atv_atv_IDS_SW_UPDATE
	atv_IDS_SW_UPDATE_MUST_0,		// atv_atv_IDS_SW_UPDATE_MUST
#ifndef D_TV_UI_STYLE_MINI
	atv_IDS_DVBS_SEARCH_0,
	atv_IDS_SET_ANTENNA_0,		// atv_atv_IDS_SET_ANTENNA
	atv_IDS_SATELLITE_0,		// atv_atv_IDS_SATELLITE
	atv_IDS_LNB_FREQ_0,		// atv_atv_IDS_LNB_FREQ
	atv_IDS_TRANSPONDER_LIST_0,		// atv_atv_IDS_TRANSPONDER_LIST
	atv_IDS_22K_0,		// atv_atv_IDS_22K
	atv_IDS_POLARITY_0,		// atv_IDS_POLARITY
	atv_IDS_SIGNAL_INTENSITY_0,		// atv_atv_IDS_SIGNAL_INTENSITY
	atv_IDS_SIGNAL_QUALITY_0,		// atv_atv_IDS_SIGNAL_QUALITY
	atv_IDS_TP_SCAN_0,		// atv_IDS_TP_SCAN
	atv_IDS_SATE_SCAN_0,		// atv_IDS_SATE_SCAN	
	atv_IDS_ADD_TP_0,
	atv_IDS_EDIT_TP_0,
	atv_IDS_WIFI_SETTING_0,
	atv_IDS_WIFI_DISPLAY_0,
	atv_IDS_DEVICE_NAME_0,
	atv_IDS_NET_MODE_0,
	atv_IDS_IPADDRESS_0,
	atv_IDS_SUBNET_MASK_0,
	atv_IDS_GATE_WAY_0,
	atv_IDS_DNS_0,
	atv_IDS_MAC_0,
	atv_IDS_SCAN_0,
	atv_IDS_DELETE_0,
	atv_IDS_CAPS_0,
	atv_IDS_NUMBER_0,
	atv_IDS_NUMBER_0TO9_0,
	atv_IDS_ZHILIAN_TV_0,
	atv_IDS_NETWORK_SHARING_0,
	atv_IDS_DTV_SHAREING_0,
#endif
};

static PREFIXCONST char POSTCONST *language_prefix_Chinese[]={
	atv_IDS_NULL_1,		// atv_atv_IDS_NULL
	atv_IDS_CONTRAST_1,		// atv_atv_IDS_CONTRAST
	atv_IDS_BRIGHTNESS_1,		// atv_atv_IDS_BRIGHTNESS
	atv_IDS_COLOR_1,		// atv_atv_IDS_COLOR
	atv_IDS_SHARPNESS_1,		// atv_atv_IDS_SHARPNESS
	atv_IDS_PICTURE_MODE_1,		// atv_atv_IDS_PICTURE_MODE
	atv_IDS_ASPECT_RATIO_1,		// atv_atv_IDS_ASPECT_RATIO
	atv_IDS_COLOR_TEMP_1,		// atv_atv_IDS_COLOR_TEMP
	atv_IDS_PICTURE_1,		// atv_atv_IDS_PICTURE
	atv_IDS_SOUND_1,		// atv_atv_IDS_SOUND
	atv_IDS_CHANNEL_1,		// atv_atv_IDS_CHANNEL
	atv_IDS_FUNCTION_1,		// atv_atv_IDS_FUNCTION
	atv_IDS_ADJUST_1,		// atv_atv_IDS_ADJUST
	atv_IDS_TIME_1,		// atv_atv_IDS_TIME
	atv_IDS_BACK_1,		// atv_atv_IDS_BACK
	atv_IDS_MOVE_1,		// atv_atv_IDS_MOVE
	atv_IDS_OK_1,		// atv_atv_IDS_OK
	atv_IDS_TINT_1,		// atv_atv_IDS_TINT
	atv_IDS_VOLUME_1,		// atv_atv_IDS_VOLUME
	atv_IDS_BALANCE_1,		// atv_atv_IDS_BALANCE
	atv_IDS_DIGITAL_TONE_1,		// atv_atv_IDS_DIGITAL_TONE
	atv_IDS_SRS_1,		// atv_atv_IDS_SRS
	atv_IDS_AVL_1,		// atv_atv_IDS_AVL
	atv_IDS_PROGRAM_EDIT_1,		// atv_atv_IDS_PROGRAM_EDIT
	atv_IDS_AUTO_TUNING_1,		// atv_atv_IDS_AUTO_TUNING
	atv_IDS_EXCHANGE_1,		// atv_atv_IDS_EXCHANGE
	atv_IDS_OSD_LANGUAGE_1,		// atv_atv_IDS_OSD_LANGUAGE
	atv_IDS_MENU_TIMEOUT_1,		// atv_atv_IDS_MENU_TIMEOUT
	atv_IDS_DNR_1,		// atv_atv_IDS_DNR
	atv_IDS_BULE_SCREEN_1,		// atv_atv_IDS_BULE_SCREEN
	atv_IDS_BACKLIGHT_1,		// atv_atv_IDS_BACKLIGHT
	atv_IDS_RESET_1,		// atv_atv_IDS_RESET
	atv_IDS_IMAGE_POSITION_1,		// atv_atv_IDS_IMAGE_POSITION
	atv_IDS_HORIZONTAL_AMPLITUDE_1,		// atv_atv_IDS_HORIZONTAL_AMPLITUDE
	atv_IDS_VERTICAL_AMPLITUDE_1,		// atv_atv_IDS_VERTICAL_AMPLITUDE
	atv_IDS_AUTO_ADJUST_1,		// atv_atv_IDS_AUTO_ADJUST
	atv_IDS_CLOCK_1,		// atv_atv_IDS_CLOCK
	atv_IDS_PHASE_1,		// atv_atv_IDS_PHASE
	atv_IDS_CURRENT_TIME_1,		// atv_atv_IDS_CURRENT_TIME
	atv_IDS_OFF_TIME_1,		// atv_atv_IDS_OFF_TIME
	atv_IDS_ON_TIME_1,		// atv_atv_IDS_ON_TIME
	atv_IDS_ON_CHANNEL_1,		// atv_atv_IDS_ON_CHANNEL
	atv_IDS_REMIND_TIME_1,		// atv_atv_IDS_REMIND_TIME
	atv_IDS_REMIND_CHANNEL_1,		// atv_atv_IDS_REMIND_CHANNEL
	atv_IDS_SLEEP_TIMER_1,		// atv_atv_IDS_SLEEP_TIMER
	atv_IDS_TV_1,		// atv_atv_IDS_TV
	atv_IDS_DTV_1,		// atv_atv_IDS_DTV
	atv_IDS_AV_1,		// atv_atv_IDS_AV
	atv_IDS_AV1_1,		// atv_atv_IDS_AV1
	atv_IDS_AV2_1,		// atv_atv_IDS_AV2
	atv_IDS_YPBPR_1,		// atv_atv_IDS_YPBPR
	atv_IDS_HDMI_1,		// atv_atv_IDS_HDMI
	atv_IDS_HDMI1_1,		// atv_atv_IDS_HDMI1
	atv_IDS_HDMI2_1,		// atv_atv_IDS_HDMI2
	atv_IDS_PC_1,		// atv_atv_IDS_PC
	atv_IDS_USB_1,		// atv_atv_IDS_USB
	atv_IDS_SOURCE_1,		// atv_atv_IDS_SOURCE
	atv_IDS_STANDARD_1,		// atv_atv_IDS_STANDARD
	atv_IDS_MILD_1,		// atv_atv_IDS_MILD
	atv_IDS_USER_1,		// atv_atv_IDS_USER
	atv_IDS_LIGHT_1,		// atv_atv_IDS_LIGHT
	atv_IDS_FULL_SCREEN_1,		// atv_atv_IDS_FULL_SCREEN
	atv_IDS_4TO3_1,		// atv_atv_IDS_4TO3
	atv_IDS_ZOOM_1,		// atv_atv_IDS_ZOOM
	atv_IDS_PANORAMA_1,		// atv_atv_IDS_PANORAMA
	atv_IDS_WARM_1,		// atv_atv_IDS_WARM
	atv_IDS_COOL_1,		// atv_atv_IDS_COOL
	atv_IDS_ON_1,		// atv_atv_IDS_ON
	atv_IDS_OFF_1,		// atv_atv_IDS_OFF
	atv_IDS_PROGRAM_MANAGE_1,		// atv_atv_IDS_PROGRAM_MANAGE
	atv_IDS_MANUAL_SEARCH_1,		// atv_atv_IDS_MANUAL_SEARCH
	atv_IDS_FINE_TUNE_1,		// atv_atv_IDS_FINE_TUNE
	atv_IDS_COLOR_SYSTEM_1,		// atv_atv_IDS_COLOR_SYSTEM
	atv_IDS_SOUND_SYSTEM_1,		// atv_atv_IDS_SOUND_SYSTEM
	atv_IDS_SKIP_1,		// atv_atv_IDS_SKIP
	atv_IDS_CANCEL_1,		// atv_atv_IDS_CANCEL
	atv_IDS_START_AUTO_SCAN_1,		// atv_atv_IDS_START_AUTO_SCAN
	atv_IDS_ENGLISH_1,		// atv_atv_IDS_ENGLISH
	atv_IDS_CHINESE_1,		// atv_atv_IDS_CHINESE
	atv_IDS_HORIZONTAL_POS_1,		// atv_atv_IDS_HORIZONTAL_POS
	atv_IDS_VERTICAL_POS_1,		// atv_atv_IDS_VERTICAL_POS
	atv_IDS_15_MINUTE_1,		// atv_atv_IDS_15_MINUTE
	atv_IDS_30_MINUTE_1,		// atv_atv_IDS_30_MINUTE
	atv_IDS_60_MINUTE_1,		// atv_atv_IDS_60_MINUTE
	atv_IDS_120_MINUTE_1,		// atv_atv_IDS_120_MINUTE
	atv_IDS_240_MINUTE_1,		// atv_atv_IDS_240_MINUTE
	atv_IDS_PTP_1,		// atv_atv_IDS_PTP
	atv_IDS_5_S_1,		// atv_atv_IDS_5_S
	atv_IDS_10_S_1,		// atv_atv_IDS_10_S
	atv_IDS_15_S_1,		// atv_atv_IDS_15_S
	atv_IDS_CURRENT_CHANNEL_1,		// atv_atv_IDS_CURRENT_CHANNEL
	atv_IDS_TO_CHANNEL_1,		// atv_atv_IDS_TO_CHANNEL
	atv_IDS_MENU_1,		// atv_atv_IDS_MENU
	atv_IDS_MOVIE_1,		// atv_atv_IDS_MOVIE
	atv_IDS_MUSIC_1,		// atv_atv_IDS_MUSIC
	atv_IDS_SETTING_1,		// atv_atv_IDS_SETTING
	atv_IDS_PLAY_1,		// atv_atv_IDS_PLAY
	atv_IDS_PAUSE_1,		// atv_atv_IDS_PAUSE
	atv_IDS_PICTURE_SPEED_1,		// atv_atv_IDS_PICTURE_SPEED
	atv_IDS_UP_LEVEL_1,		// atv_atv_IDS_UP_LEVEL
	atv_IDS_HIGH_SPEED_1,		// atv_atv_IDS_HIGH_SPEED
	atv_IDS_LOW_SPEED_1,		// atv_atv_IDS_LOW_SPEED
	atv_IDS_MIDDLE_SPEED_1,		// atv_atv_IDS_MIDDLE_SPEED
	atv_IDS_PICTURE_OPTIMIZE_1,		// atv_atv_IDS_PICTURE_OPTIMIZE
	atv_IDS_HIGH_1,		// atv_atv_IDS_HIGH
	atv_IDS_LOW_1,		// atv_atv_IDS_LOW
	atv_IDS_MIDDLE_1,		// atv_atv_IDS_MIDDLE
	atv_IDS_LAST_1,		// atv_atv_IDS_LAST
	atv_IDS_NEXT_1,		// atv_atv_IDS_NEXT
	atv_IDS_ROTATE_1,		// atv_atv_IDS_ROTATE
	atv_IDS_STOP_AUTO_SCAN_1,		// atv_atv_IDS_STOP_AUTO_SCAN
	atv_IDS_CHANNEL_LIST_1,		// atv_atv_IDS_CHANNEL_LIST
	atv_IDS_TV_MANUAL_SCAN_1,		// atv_atv_IDS_TV_MANUAL_SCAN
	atv_IDS_CHANNEL_SCAN_1,		// atv_atv_IDS_CHANNEL_SCAN
	atv_IDS_NO_SIGNAL_1,		// atv_atv_IDS_NO_SIGNAL
	atv_IDS_BAD_1,		// atv_atv_IDS_BAD
	atv_IDS_GOOD_1,		// atv_atv_IDS_GOOD
	atv_IDS_FREQ_1,		// atv_atv_IDS_FREQ
	atv_IDS_DIGI_TV_1,		// atv_atv_IDS_DIGI_TV
	atv_IDS_DIGI_RADIO_1,		// atv_atv_IDS_DIGI_RADIO
	atv_IDS_QUIT_1,		// atv_atv_IDS_QUIT
	atv_IDS_CH_ID_1,		// atv_atv_IDS_CH_ID
	atv_IDS_EBOOK_1,		// atv_atv_IDS_EBOOK
	atv_IDS_STOP_1,		// atv_atv_IDS_STOP
	atv_IDS_AV_SIGNAL_SELECT_1,		// atv_atv_IDS_AV_SIGNAL_SELECT
	atv_IDS_AV_SIGNAL_1,		// atv_atv_IDS_AV_SIGNAL
	atv_IDS_DVBC_1,		// atv_atv_IDS_DVBC
	atv_IDS_DTMB_1,		// atv_atv_IDS_DTMB
	atv_IDS_NO_USB_1,		// atv_atv_IDS_NO_USB
	atv_IDS_USB_CONNECT_1,		// atv_atv_IDS_USB_CONNECT
	atv_IDS_USB_DIS_CONNECT_1,		// atv_atv_IDS_USB_DIS_CONNECT
	atv_IDS_SEARCH_AUTO_1,		// atv_atv_IDS_SEARCH_AUTO
	atv_IDS_SEARCH_PAL_1,		// atv_atv_IDS_SEARCH_PAL
	atv_IDS_SEARCH_SECAM_1,		// atv_atv_IDS_SEARCH_SECAM
	atv_IDS_SEARCH_NTSC_1,		// atv_atv_IDS_SEARCH_NTSC
	atv_IDS_SEARCH_DK_1,		// atv_atv_IDS_SEARCH_DK
	atv_IDS_SEARCH_BG_1,		// atv_atv_IDS_SEARCH_BG
	atv_IDS_SEARCH_I_1,		// atv_atv_IDS_SEARCH_I
	atv_IDS_SEARCH_M_1,		// atv_atv_IDS_SEARCH_M
	atv_IDS_DEFAULT_SET_1,		// atv_atv_IDS_DEFAULT_SET
	atv_IDS_RESTORE_OK_1,		// atv_atv_IDS_RESTORE_OK
	atv_IDS_PROMPT_INFO_1,		// atv_atv_IDS_PROMPT_INFO
	atv_IDS_PLAY_FAILED_1,		// atv_atv_IDS_PLAY_FAILED
	atv_IDS_FREQ_SEARCH_1,		// atv_atv_IDS_FREQ_SEARCH
	atv_IDS_TV_AUTO_SCAN_1,		// atv_atv_IDS_TV_AUTO_SCAN
	atv_IDS_START_ALL_SCAN_1,		// atv_atv_IDS_START_ALL_SCAN
	atv_IDS_END_ALL_SCAN_1,		// atv_atv_IDS_END_ALL_SCAN
	atv_IDS_SCANNING_1,		// atv_atv_IDS_SCANNING
	atv_IDS_MONDAY_1,		// atv_atv_IDS_MONDAY
	atv_IDS_TUESDAY_1,		// atv_atv_IDS_TUESDAY
	atv_IDS_WENDSDAY_1,		// atv_atv_IDS_WENDSDAY
	atv_IDS_THURSDAY_1,		// atv_atv_IDS_THURSDAY
	atv_IDS_FRIDAY_1,		// atv_atv_IDS_FRIDAY
	atv_IDS_SATURDAY_1,		// atv_atv_IDS_SATURDAY
	atv_IDS_SUNDAY_1,		// atv_atv_IDS_SUNDAY
	atv_IDS_INIT_TV_1,		// atv_atv_IDS_INIT_TV
	atv_IDS_GENERAL_SETTING_1,		// atv_atv_IDS_GENERAL_SETTING
	atv_IDS_DEBUG_1,		// atv_atv_IDS_DEBUG
	atv_IDS_SW_INFORMATION_1,		// atv_atv_IDS_SW_INFORMATION
	atv_IDS_SOFTWARE_UPDATE_1,		// atv_atv_IDS_SOFTWARE_UPDATE
	atv_IDS_INIT_FAC_CHANNEL_1,		// atv_atv_IDS_INIT_FAC_CHANNEL
	atv_IDS_BURN_MODE_1,		// atv_atv_IDS_BURN_MODE
	atv_IDS_INIT_ALL_FOR_BOE_1,		// atv_atv_IDS_INIT_ALL_FOR_BOE
	atv_IDS_HOTEL_MODE_1,		// atv_atv_IDS_HOTEL_MODE
	atv_IDS_SOURCE_LOCK_1,		// atv_atv_IDS_SOURCE_LOCK
	atv_IDS_CHANNEL_LOCK_1,		// atv_atv_IDS_CHANNEL_LOCK
	atv_IDS_DEFAULT_SOURCE_1,		// atv_atv_IDS_DEFAULT_SOURCE
	atv_IDS_DEFAULT_PROG_1,		// atv_atv_IDS_DEFAULT_PROG
	atv_IDS_MAX_VOLUME_1,		// atv_atv_IDS_MAX_VOLUME
	atv_IDS_DEFAULT_VOLUME_1,		// atv_atv_IDS_DEFAULT_VOLUME
	atv_IDS_POWER_DOWN_RESET_1,		// atv_atv_IDS_POWER_DOWN_RESET
	atv_IDS_RESET_HOTEL_1,		// atv_atv_IDS_RESET_HOTEL
	atv_IDS_EXPORT_SETTINGS_1,		// atv_atv_IDS_EXPORT_SETTINGS
	atv_IDS_IMPORT_SETTINGS_1,		// atv_atv_IDS_IMPORT_SETTINGS
	atv_IDS_KEY_LOCK_1,		// atv_atv_IDS_KEY_LOCK
	atv_IDS_CAPTURE_LOGO_1,		// atv_atv_IDS_CAPTURE_LOGO
	atv_IDS_LOGO_1,		// atv_atv_IDS_LOGO
	atv_IDS_DEFAULT_1,		// atv_atv_IDS_DEFAULT
	atv_IDS_ADC_ADJUST_1,		// atv_atv_IDS_ADC_ADJUST
	atv_IDS_EMC_SETTING_1,		// atv_atv_IDS_EMC_SETTING
	atv_IDS_BUILD_TIME_1,		// atv_atv_IDS_BUILD_TIME
	atv_IDS_VERSION_1,		// atv_atv_IDS_VERSION
	atv_IDS_LVDS_MAP_1,		// atv_atv_IDS_LVDS_MAP
	atv_IDS_POWER_MODE_1,		// atv_atv_IDS_POWER_MODE
	atv_IDS_WHITE_PATTERN_1,		// atv_atv_IDS_WHITE_PATTERN
	atv_IDS_PWM_1,		// atv_atv_IDS_PWM
	atv_IDS_POWER_REF_1,		// atv_atv_IDS_POWER_REF
	atv_IDS_POWER_DIM_1,		// atv_atv_IDS_POWER_DIM
	atv_IDS_BACKLIGHT_MAX_1,		// atv_atv_IDS_BACKLIGHT_MAX
	atv_IDS_BACKLIGHT_LEVEL_1,		// atv_atv_IDS_BACKLIGHT_LEVEL
	atv_IDS_BACKLIGHT_STEP_1,		// atv_atv_IDS_BACKLIGHT_STEP
	atv_IDS_STEP_TIME_1,		// atv_atv_IDS_STEP_TIME
	atv_IDS_FACTORY_SETTING_1,		// atv_atv_IDS_FACTORY_SETTING
	atv_IDS_NO_PROGRAM_1,		// atv_atv_IDS_NO_PROGRAM
	atv_IDS_SOUND_BACKLIGHT_1,		// atv_atv_IDS_SOUND_BACKLIGHT
	atv_IDS_WB_ADJUST_1,		// atv_atv_IDS_WB_ADJUST
	atv_IDS_PQ_NONLINEAR_1,		// atv_atv_IDS_PQ_NONLINEAR
	atv_IDS_SOUND_MODE_1,		// atv_atv_IDS_SOUND_MODE
	atv_IDS_VOLUME_CURVE_1,		// atv_atv_IDS_VOLUME_CURVE
	atv_IDS_SATURATION_1,		// atv_atv_IDS_SATURATION
	atv_IDS_PVR_1,		// atv_atv_IDS_PVR
	atv_IDS_STOP_RECORD_1,		// atv_atv_IDS_STOP_RECORD
	atv_IDS_ENTER_RECORD_1,		// atv_atv_IDS_ENTER_RECORD
	atv_IDS_RECORD_FAILED_1,		// atv_atv_IDS_RECORD_FAILED
	atv_IDS_RECORD_TIME_OUT_1,		// atv_atv_IDS_RECORD_TIME_OUT
	atv_IDS_NO_SPACE_1,		// atv_atv_IDS_NO_SPACE
	atv_IDS_REICORD_FILE_LARGE_1,		// atv_atv_IDS_REICORD_FILE_LARGE
	atv_IDS_BAD_SIGNAL_SAVING_1,		// atv_atv_IDS_BAD_SIGNAL_SAVING
	atv_IDS_DEVICE_REMOVED_1,		// atv_atv_IDS_DEVICE_REMOVED
	atv_IDS_RECORD_NOT_CHANGE_CHANNEL_1,		// atv_atv_IDS_RECORD_NOT_CHANGE_CHANNEL
	atv_IDS_NO_FIND_DISK_1,		// atv_atv_IDS_NO_FIND_DISK
	atv_IDS_RED_INPUT_1,		// atv_atv_IDS_RED_INPUT
	atv_IDS_BOXINFORMATION_1,		// atv_atv_IDS_BOXINFORMATION
	atv_IDS_PRODUCECOMPANY_1,		// atv_atv_IDS_PRODUCECOMPANY
	atv_IDS_HARDWAREEDITION_1,		// atv_atv_IDS_HARDWAREEDITION
	atv_IDS_SOFTWAREEDITION_1,		// atv_atv_IDS_SOFTWAREEDITION
	atv_IDS_SERIALNUMBER_1,		// atv_atv_IDS_SERIALNUMBER
	atv_IDS_COMPANYID_1,		// atv_atv_IDS_COMPANYID
	atv_IDS_UPGRADE_FAIL_1,		// atv_atv_IDS_UPGRADE_FAIL
	atv_IDS_UPGRADE_SUC_1,		// atv_atv_IDS_UPGRADE_SUC
	atv_IDS_INVALID_FILE_1,		// atv_atv_IDS_INVALID_FILE
	atv_IDS_THEATRE_1,		// atv_atv_IDS_THEATRE
	atv_IDS_SCAN_CONFIG_1,		// atv_atv_IDS_SCAN_CONFIG
	atv_IDS_TV_SCAN_CONFIG_1,		// atv_atv_IDS_TV_SCAN_CONFIG
	atv_IDS_DTV_SCAN_CONFIG_1,		// atv_atv_IDS_DTV_SCAN_CONFIG
	atv_IDS_START_FREQ_1,		// atv_atv_IDS_START_FREQ
	atv_IDS_END_FREQ_1,		// atv_atv_IDS_END_FREQ
	atv_IDS_BANDWIDTH_1,		// atv_atv_IDS_BANDWIDTH
	atv_IDS_BY_ROLE_1,		// atv_atv_IDS_BY_ROLE
	atv_IDS_MODULATION_1,		// atv_atv_IDS_MODULATION
	atv_IDS_SYMBOL_RATE_1,		// atv_atv_IDS_SYMBOL_RATE
	atv_IDS_FREQUENCY_1,		// atv_atv_IDS_FREQUENCY
	atv_IDS_YES_1,		// atv_atv_IDS_YES
	atv_IDS_NO_1,		// atv_atv_IDS_NO
	atv_IDS_CONFIG_ERROR_1,		// atv_atv_IDS_CONFIG_ERROR
	atv_IDS_START_MANUAL_SCAN_1,		// atv_atv_IDS_START_MANUAL_SCAN
	atv_IDS_END_MANUAL_SCAN_1,		// atv_atv_IDS_END_MANUAL_SCAN
	atv_IDS_END_AUTO_SCAN_1,		// atv_atv_IDS_END_AUTO_SCAN
	atv_IDS_SUB_START_1,		// atv_atv_IDS_SUB_START
	atv_IDS_SUB_START_CHAN_1,		// atv_atv_IDS_SUB_START_CHAN
	atv_IDS_EVENT_OUT_OF_TIME_1,		// atv_atv_IDS_EVENT_OUT_OF_TIME
	atv_IDS_SUBSCRIBE_FAIL_1,		// atv_atv_IDS_SUBSCRIBE_FAIL
	atv_IDS_SWITCH_USER_MODE_1,		// atv_atv_IDS_SWITCH_USER_MODE
	atv_IDS_EPG_HELP_1,		// atv_atv_IDS_EPG_HELP
	atv_IDS_CHOICE_1,		// atv_atv_IDS_CHOICE
	atv_IDS_EPG_LIST_1,		// atv_atv_IDS_EPG_LIST
	atv_IDS_EPG_LIST_RADIO_1,		// atv_atv_IDS_EPG_LIST_RADIO
	atv_IDS_REPEAT_TIME1_1,		// atv_atv_IDS_REPEAT_TIME1
	atv_IDS_REPEAT_TIME_1,		// atv_atv_IDS_REPEAT_TIME
	atv_IDS_PRO_NAME_1,		// atv_atv_IDS_PRO_NAME
	atv_IDS_EVENT_NAME_1,		// atv_atv_IDS_EVENT_NAME
	atv_IDS_EVENT_SYNOPSIS_1,		// atv_atv_IDS_EVENT_SYNOPSIS
	atv_IDS_EPGINFO_1,		// atv_atv_IDS_EPGINFO
	atv_IDS_LIST_LOOP_1,		// atv_atv_IDS_LIST_LOOP
	atv_IDS_SINGNAL_LOOP_1,		// atv_atv_IDS_SINGNAL_LOOP
	atv_IDS_RANDOM_LOOP_1,		// atv_atv_IDS_RANDOM_LOOP
	atv_IDS_LIST_PLAY_1,		// atv_atv_IDS_LIST_PLAY
	atv_IDS_PLAY_MODE_1,		// atv_atv_IDS_PLAY_MODE
	atv_IDS_CARRIER_FREQ_1,		// atv_atv_IDS_CARRIER_FREQ
	atv_IDS_DEM_OTHER_INFO_1,		// atv_atv_IDS_DEM_OTHER_INFO
	atv_IDS_DEMO_DETIAL_1,		// atv_atv_IDS_DEMO_DETIAL
	atv_IDS_DEM_SCATTER_1,		// atv_atv_IDS_DEM_SCATTER
	atv_IDS_DEM_HN_1,		// atv_atv_IDS_DEM_HN
	atv_IDS_DEM_SP_1,		// atv_atv_IDS_DEM_SP
	atv_IDS_SIGNAL_DETECT_1,		// atv_atv_IDS_SIGNAL_DETECT
	atv_IDS_STRENGH_BAR_1,		// atv_atv_IDS_STRENGH_BAR
	atv_IDS_QUALITY_BAR_1,		// atv_atv_IDS_QUALITY_BAR
	atv_IDS_UPDATE_SYMBOL_1,		// atv_atv_IDS_UPDATE_SYMBOL
	atv_IDS_NET_SEARCH_1,		// atv_atv_IDS_NET_SEARCH
	atv_IDS_START_NET_SCAN_1,		// atv_atv_IDS_START_NET_SCAN
	atv_IDS_TV_NET_SCAN_1,		// atv_atv_IDS_TV_NET_SCAN
	atv_IDS_END_NET_SCAN_1,		// atv_atv_IDS_END_NET_SCAN
	atv_IDS_EARPHONE_IN_1,		// atv_atv_IDS_EARPHONE_IN
	atv_IDS_EARPHONE_OUT_1,		// atv_atv_IDS_EARPHONE_OUT
	atv_IDS_SCRAMBLED_PROG_1,		// atv_atv_IDS_SCRAMBLED_PROG
	atv_IDS_SVN_VERSION_1,		// atv_atv_IDS_SVN_VERSION
	atv_IDS_BOARD_VER_1,		// atv_atv_IDS_BOARD_VER
	atv_IDS_NOT_SUPPORT_PIC_SIZE_1,		// atv_atv_IDS_NOT_SUPPORT_PIC_SIZE
	atv_IDS_NOT_SUPPORT_FILE_1,		// atv_atv_IDS_NOT_SUPPORT_FILE
	atv_IDS_FACTORY_RESET_1,		// atv_atv_IDS_FACTORY_RESET
	atv_IDS_DELETE_PVR_1,		// atv_atv_IDS_DELETE_PVR
	atv_IDS_DELETE_PVR_FILE_1,		// atv_atv_IDS_DELETE_PVR_FILE
	atv_IDS_EXIT_1,		// atv_atv_IDS_EXIT
	atv_IDS_DVI1_1,		// atv_atv_IDS_DVI1
	atv_IDS_DVI2_1,		// atv_atv_IDS_DVI2
	atv_IDS_UNKNOW_FORMAT_1,		// atv_atv_IDS_UNKNOW_FORMAT
	atv_IDS_INPUT_TIME_ERROR_1,		// atv_atv_IDS_INPUT_TIME_ERROR
	atv_IDS_FILE_SIZE_1,		// atv_atv_IDS_FILE_SIZE
	atv_IDS_BPS_1,		// atv_atv_IDS_BPS
	atv_IDS_Bitrate_Excess_1,		// atv_atv_IDS_Bitrate_Excess
	atv_IDS_Resolution_1,		// atv_atv_IDS_Resolution
	atv_IDS_MULTI_AUDIO_1,		// atv_atv_IDS_MULTI_AUDIO
	atv_IDS_LEFT_1,		// atv_atv_IDS_LEFT
	atv_IDS_RIGHT_1,		// atv_atv_IDS_RIGHT
	atv_IDS_STEREO_1,		// atv_atv_IDS_STEREO
	atv_IDS_NONE_1,		// atv_atv_IDS_NONE
	atv_IDS_ACTION_INVALID_1,		// atv_atv_IDS_ACTION_INVALID
	atv_IDS_DEVICE_BITRATE_BAD_1,		// atv_atv_IDS_DEVICE_BITRATE_BAD
	atv_IDS_RECEIVE_CHOISE_1,		// atv_atv_IDS_RECEIVE_CHOISE
	atv_IDS_RECEIVE_SERIAL_1,		// atv_atv_IDS_RECEIVE_SERIAL
	atv_IDS_CHIP_ID_1,		// atv_atv_IDS_CHIP_ID
	atv_IDS_VIDEO_FRMART_1,		// atv_atv_IDS_VIDEO_FRMART
	atv_IDS_AUDIO_FRMART_1,		// atv_atv_IDS_AUDIO_FRMART
	atv_IDS_NEW_SOFTWARE_1,		// atv_atv_IDS_NEW_SOFTWARE
	atv_IDS_SW_UPDATE_1,		// atv_atv_IDS_SW_UPDATE
	atv_IDS_SW_UPDATE_MUST_1,		// atv_atv_IDS_SW_UPDATE_MUST
#ifndef D_TV_UI_STYLE_MINI
	atv_IDS_DVBS_SEARCH_1,
	atv_IDS_SET_ANTENNA_1,		// atv_atv_IDS_SET_ANTENNA
	atv_IDS_SATELLITE_1,		// atv_atv_IDS_SATELLITE
	atv_IDS_LNB_FREQ_1,		// atv_atv_IDS_LNB_FREQ
	atv_IDS_TRANSPONDER_LIST_1,		// atv_atv_IDS_TRANSPONDER_LIST
	atv_IDS_22K_1,		// atv_atv_IDS_22K
	atv_IDS_POLARITY_1,		// atv_IDS_POLARITY
	atv_IDS_SIGNAL_INTENSITY_1,		// atv_atv_IDS_SIGNAL_INTENSITY
	atv_IDS_SIGNAL_QUALITY_1,		// atv_atv_IDS_SIGNAL_QUALITY
	atv_IDS_TP_SCAN_1,		// atv_IDS_TP_SCAN
	atv_IDS_SATE_SCAN_1,		// atv_IDS_SATE_SCAN	
	atv_IDS_ADD_TP_1,
	atv_IDS_EDIT_TP_1,
	atv_IDS_WIFI_SETTING_1,
	atv_IDS_WIFI_DISPLAY_1,
	atv_IDS_DEVICE_NAME_1,
	atv_IDS_NET_MODE_1,
	atv_IDS_IPADDRESS_1,
	atv_IDS_SUBNET_MASK_1,
	atv_IDS_GATE_WAY_1,
	atv_IDS_DNS_1,
	atv_IDS_MAC_1,
	atv_IDS_SCAN_1,
	atv_IDS_DELETE_1,
	atv_IDS_CAPS_1,
	atv_IDS_NUMBER_1,
	atv_IDS_NUMBER_0TO9_1,
	atv_IDS_ZHILIAN_TV_1,
	atv_IDS_NETWORK_SHARING_1,
	atv_IDS_DTV_SHAREING_1,
#endif
};

static PREFIXCONST char POSTCONST **_language_resource_entry[]={
	language_prefix_English, 
	language_prefix_Chinese, 
};


#define	LAN_COUNT	2
PREFIXCONST char* POSTCONST atv_LoadIdsRes(int ids, int lanid)
{
	if(ids>=atv_IDS_ENUM_MAX||ids<atv_LAN_ENUM_START||lanid<0||lanid>=LAN_COUNT)
		return NULL;
	ids-=atv_LAN_ENUM_START;
	return _language_resource_entry[lanid][ids];
}

