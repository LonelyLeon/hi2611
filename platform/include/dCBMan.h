/** @file
* @brief 回调管理头文件
* @author 李臣
* @date 2013-03-20 李臣: 建立文件
* @date 2013-08-09 李臣: 源码标准化
*/
#ifndef __D_CBMAN_H
#define __D_CBMAN_H
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 回调事件ID分配区间大小 */
#define D_CB_EVT_ID_SPACE_SHIFT	16
#define D_CB_EVT_ID_SPACE		(1 << D_CB_EVT_ID_SPACE_SHIFT) /* 0x10000 */

/** @brief 回调事件ID区间定义 */
#define D_CB_EVT_ID_BASE		0x00000000

#define D_CB_EVT_ID_OS_RESERVED	D_CB_EVT_ID_BASE
    #define PL_INTERRUPT_PVR            (D_CB_EVT_ID_OS_RESERVED)
#define D_CB_EVT_ID_DRIVER              (D_CB_EVT_ID_OS_RESERVED + D_CB_EVT_ID_SPACE)
    #define PL_FEND_LOCK_RET            (D_CB_EVT_ID_DRIVER) /**< fend设备查询锁定后钩子 */
    #define PL_FEND_LOCK_CHECK_LOOP     (D_CB_EVT_ID_DRIVER + 1) /**< fend设备锁频等待锁定循环 */
    #define PL_AV_CALLBACK              (D_CB_EVT_ID_DRIVER + 2) /**< 音视频驱动回调 */
    #define PL_FEND_SWITCH_CIRCUIT      (D_CB_EVT_ID_DRIVER + 3) /**< fend设备电路切换 */
    #define PL_USB_DEV_CONNECT          (D_CB_EVT_ID_DRIVER + 4) /**< USB设备链接 */
    #define PL_USB_DEV_DISCONNECT       (D_CB_EVT_ID_DRIVER + 5) /**< USB设备断开 */
    #define PL_USB_DEV_ATTACHED_DRIVER  (D_CB_EVT_ID_DRIVER + 6) /**< USB设备加载驱动 */
    #define PL_USB_DEV_DETACHED_DRIVER  (D_CB_EVT_ID_DRIVER + 7) /**< USB设备卸载驱动 */
#define D_CB_EVT_ID_PLATFORM1	(D_CB_EVT_ID_DRIVER + D_CB_EVT_ID_SPACE)
	#define PL_GUI_DISP_MSG_PRE 		(D_CB_EVT_ID_PLATFORM1) /**< GUI消息处理前钩子 */
	#define PL_GUI_DISP_MSG_RET 		(D_CB_EVT_ID_PLATFORM1 + 1) /**< GUI消息处理后钩子 */
	#define PL_GUI_IDLE         		(D_CB_EVT_ID_PLATFORM1 + 2) /**< GUI空闲 */
	#define PL_GUI_VIS_OP_DRAW_PRE		(D_CB_EVT_ID_PLATFORM1 + 3) /**< visual自绘前钩子 */
	#define PL_GUI_VIS_OP_DRAW_RET		(D_CB_EVT_ID_PLATFORM1 + 4) /**< visual自绘后钩子 */
	#define PL_GUI_CONTROL_NEW			(D_CB_EVT_ID_PLATFORM1 + 5) /**< 控件创建 */
	#define PL_GUI_CONTROL_DRAW			(D_CB_EVT_ID_PLATFORM1 + 6) /**< 控件绘图 */
	#define PL_GUI_NEW_FRAME_READY		(D_CB_EVT_ID_PLATFORM1 + 7) /**< GUI完成一次重绘, 缓冲区准备好一帧 */
	#define PL_GUI_VIS_DRAWTEXT			(D_CB_EVT_ID_PLATFORM1 + 8) /**< draw_text()钩子 */
	#define PL_GUI_IR_REMAP				(D_CB_EVT_ID_PLATFORM1 + 9) /**< ir重新映射键值钩子 */
    #define PL_GUI_VIS_NEW              (D_CB_EVT_ID_PLATFORM1 + 10) /**< d_vis_new()钩子 */
    #define PL_GUI_VIS_FREE             (D_CB_EVT_ID_PLATFORM1 + 11) /**< d_vis_free()钩子 */
    #define PL_GUI_VIS_UPDATE_RECT      (D_CB_EVT_ID_PLATFORM1 + 12) /**< d_vis_update()钩子 */
    #define PL_GUI_FP_REMAP             (D_CB_EVT_ID_PLATFORM1 + 13) /**< 前面板重新映射键值钩子 */
    #define PL_GUI_GENERATE_USER_KEY    (D_CB_EVT_ID_PLATFORM1 + 14) /**< 用户产生key钩子 */
    #define PL_GUI_INPUT_POLL           (D_CB_EVT_ID_PLATFORM1 + 15) /**< 处理输入(如按键、鼠标、触摸屏)事件的钩子*/
	#define PL_GUI_DRAWTEXT			    (D_CB_EVT_ID_PLATFORM1 + 16) /**< draw_text()钩子 */
    
#define D_CB_EVT_ID_PLATFORM2	(D_CB_EVT_ID_PLATFORM1 + D_CB_EVT_ID_SPACE)
	#define PL_CC_NEXT_CHAR				(D_CB_EVT_ID_PLATFORM2) /**< d_text_next_char()钩子 */
	#define PL_CC_PREV_CHAR				(D_CB_EVT_ID_PLATFORM2 + 1) /**< d_text_prev_char()钩子 */
	#define PL_CC_NEXT_WORD				(D_CB_EVT_ID_PLATFORM2 + 2) /**< d_text_next_word()钩子 */
	#define PL_FONT_OP_CHAR				(D_CB_EVT_ID_PLATFORM2 + 3) /**< font函数钩子, 用于字符编码转换 */
	#define PL_CC_DRAWTEXT				(D_CB_EVT_ID_PLATFORM2 + 4) /**< draw_text()钩子 */
	
	#define D_MONITOR_REG_PMT			(D_CB_EVT_ID_PLATFORM2 + 5) /**< 监控pmt表注册函数 */
	#define D_MONITOR_REG_SDT			(D_CB_EVT_ID_PLATFORM2 + 6) /**< 监控sdt表注册函数 */
	#define D_MONITOR_REG_NIT			(D_CB_EVT_ID_PLATFORM2 + 7) /**< 监控nit表注册函数 */
	#define D_MONITOR_PMT_TO_CA			(D_CB_EVT_ID_PLATFORM2 + 8) /**< pmt表向ca传递数据注册函数 */
	#define D_MONITOR_CAT_TO_CA			(D_CB_EVT_ID_PLATFORM2 + 9) /**< cat表向ca传递数据注册函数 */

	#define PL_TV_PLAY_CHANGE_FMAN		(D_CB_EVT_ID_PLATFORM2 + 10) /**< TV播放时, 前端类型改变钩子 */

	#define PL_SI_PARSE_DESC_PRE		(D_CB_EVT_ID_PLATFORM2 + 11) /**< SI分析描述子前钩子 */
	#define PL_SI_PARSE_DESC_RET		(D_CB_EVT_ID_PLATFORM2 + 12) /**< SI分析描述子后钩子 */

    #define D_MONITOR_REG_PAT			(D_CB_EVT_ID_PLATFORM2 + 13) /**< 监控nit表注册函数 */
    #define D_MONITOR_REG_NIT_TO_LOADER (D_CB_EVT_ID_PLATFORM2 + 14) /**< 监控nit表注册函数 */

    #define D_MON_TS_NOT_LOCK           (D_CB_EVT_ID_PLATFORM2 + 15) /**< 开机SI监控锁不定钩子 */
    #define D_MON_GET_NIT_FULL          (D_CB_EVT_ID_PLATFORM2 + 16) /**< 开机nit搜全钩子 */
    #define D_MON_GET_UMT_FULL          (D_CB_EVT_ID_PLATFORM2 + 17) /**< 开机UMT搜全钩子 */

    #define PL_FMAN_LOCK_RET             (D_CB_EVT_ID_PLATFORM2 + 18) /**< fman查询锁定后钩子 */
    #define PL_FMAN_SET_PARAM             (D_CB_EVT_ID_PLATFORM2 + 19) /**< fman设定频点参数钩子 */

#define D_CB_EVT_ID_PLATFORM3	(D_CB_EVT_ID_PLATFORM2 + D_CB_EVT_ID_SPACE)
    #define CA_GET_CUR_CAS			(D_CB_EVT_ID_PLATFORM3 ) /**get curca */
    #define CA_SET_CUR_CAS          (D_CB_EVT_ID_PLATFORM3 + 1) /**set curca */
    #define CA_GET_CUR_LAN		    (D_CB_EVT_ID_PLATFORM3 + 2) /**ca get cur language */
    #define CA_GET_CUR_STB_SERIALNO (D_CB_EVT_ID_PLATFORM3 + 3) /**ca get cur stb serialno */  
    #define D_MONITOR_NIT_TO_CA     (D_CB_EVT_ID_PLATFORM3 + 4) /**< NIT表向ca传递数据注册函数 */
    #define CA_GET_OTA_INFO         (D_CB_EVT_ID_PLATFORM3 + 5) /*获取当前软硬件版本号和厂商代码*/
    #define CA_GET_CA_PRIVATE_INFO  (D_CB_EVT_ID_PLATFORM3 + 6) /**get ca private info*/
    #define CA_SET_CA_PRIVATE_INFO  (D_CB_EVT_ID_PLATFORM3 + 7) /**set ca private info*/
    #define CA_GET_STB_SERIAL_STRING (D_CB_EVT_ID_PLATFORM3 + 8) /**ca get cur stb serialno string */
    #define CA_GET_SPECIAL_FUNC_INFO (D_CB_EVT_ID_PLATFORM3 + 9) /*获取当前CA是否有特别需求*/
    #define CA_GET_SYS_RESOLUTIONRATIO_INFO (D_CB_EVT_ID_PLATFORM3 + 10) /*获取当前系统分辨率*/
    #define CA_GET_STB_SERIAL_ABV_STRING    (D_CB_EVT_ID_PLATFORM3 + 11) /*获取序列号，目前只有jiangsu下联广CA用*/
    #define CA_SET_STB_SERIAL_STRING (D_CB_EVT_ID_PLATFORM3 + 12) /**ca set cur stb serialno string */

#define D_CB_EVT_ID_PLATFORM4	(D_CB_EVT_ID_PLATFORM3 + D_CB_EVT_ID_SPACE)
    #define PL_FILESYSTEM_HOTPLUG   (D_CB_EVT_ID_PLATFORM4) /**< 文件系统热插拔通知 */
    #define PL_APP_MAN_SYNC_LOCK    (D_CB_EVT_ID_PLATFORM4 + 1) /**< app管理同步锁查询钩子 */
    #define PL_SI_PARSE_SRV_TYPE (D_CB_EVT_ID_PLATFORM4 + 2) /**< SI分析描述子后钩子 */
   	#define PL_SI_PARSE_PMT	 (D_CB_EVT_ID_PLATFORM4 + 3) /**< SI分析pmt表里的钩子 */
    #define PL_SI_PARSE_PAT	 (D_CB_EVT_ID_PLATFORM4 + 4) /**< SI分析pat表钩子 */
	#define PL_MEDIA_PIC_PALY	 (D_CB_EVT_ID_PLATFORM4 + 5) /**< 多媒体图片播放钩子 */
	#define PL_MEDIA_PVR_PARSE_TS	 (D_CB_EVT_ID_PLATFORM4 + 6) /**<PVR播放模块解析非录制码流钩子 */
	#define PL_TV_AV_PLAY_PRE    (D_CB_EVT_ID_PLATFORM4 + 7) /**< tv里在调用d_av_play 前钩子 */
	#define PL_TV_AV_STOP_PRE    (D_CB_EVT_ID_PLATFORM4 + 8) /**< tv里在调用d_av_stop 前钩子 */
	#define PL_CVBS_CALLBACKE	 (D_CB_EVT_ID_PLATFORM4 + 9) /**< cvbs模块钩子 */
	#define PL_AUDIO_DAC_CTL	 (D_CB_EVT_ID_PLATFORM4 + 10) /**<音频输入源变化*/


#define D_CB_EVT_ID_PROJECT1	(D_CB_EVT_ID_PLATFORM4 + D_CB_EVT_ID_SPACE)
#define D_CB_EVT_ID_PROJECT2	(D_CB_EVT_ID_PROJECT1 + D_CB_EVT_ID_SPACE)
#define D_CB_EVT_ID_PROJECT3	(D_CB_EVT_ID_PROJECT2 + D_CB_EVT_ID_SPACE)
#define D_CB_EVT_ID_PROJECT4	(D_CB_EVT_ID_PROJECT3 + D_CB_EVT_ID_SPACE)
#define D_CB_EVT_ID_XMLJEC		(D_CB_EVT_ID_PROJECT4+D_CB_EVT_ID_SPACE)
#define D_CB_EVT_ID_SPACE_MAX	11

/** @brief 回调函数类型定义 */
typedef void (*D_CBFunc)(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT;

/** @brief 回调管理初始化
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_cbman_open(void) D_FUNCPOSTFIT;

/** @brief 回调管理释放
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_cbman_close(void) D_FUNCPOSTFIT;

/** @brief 注册一个事件的回调
* @param cb_id 事件ID
* @param obj 事件关联对象, 必须和产生事件的对象匹配才能被回调
* @param cb 回调函数
* @param cb_data 回调注册传入参数, 回调函数会带入此参数
* @return 成功返回回调句柄,失败返回D_INVALID_HANDLE
*/
D_Handle d_cbman_subscribe(D_U32 cb_id, D_Handle obj, D_CBFunc cb, D_Ptr cb_data) D_FUNCPOSTFIT;

/** @brief 反注册回调
* @param hcbm 回调句柄
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_cbman_unsubscribe(D_Handle hcbm) D_FUNCPOSTFIT;

/** @brief 产生一个事件通知
* @param cb_id 事件ID
* @param obj 事件关联对象
* @param obj_data 事件关联对象参数
*/
void d_cbman_notify(D_U32 cb_id, D_Handle obj, D_Ptr obj_data) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
