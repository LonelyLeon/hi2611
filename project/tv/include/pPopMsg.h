/** @file
* @brief 信息窗口模块
* @author 龚克
* @date 2005-9-13 龚克: 建立文件
* @date 2013-06-20 李臣: 整理并重新实现
*/

#ifndef _D_POP_MSG_H_
#define _D_POP_MSG_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dGUI.h"
#include "dFrame.h"
#include "dPop.h"

/** @brief 消息框类型*/
typedef enum {
	D_POP_MSG_MSG,			/**< 普通消息*/
	D_POP_MSG_ERROR,		/**< 错误信息*/
	D_POP_MSG_WARNING		/**< 警告信息*/
} D_PopMsgType;

/** @brief 用户响应键的类型*/
typedef enum {
	D_POP_MSG_RESPONSE_NOT,		/*不响应任何按键*/
	D_POP_MSG_RESPONSE_ANY,		/*任意键消失*/
	D_POP_MSG_RESPONSE_OK,		/*OK键消失*/
	D_POP_MSG_RESPONSE_ALL_NOT	/*所有键响应D_OK, 但无实质性操作*/
} D_PopMsgResponseType;

enum{
	D_MULTI_SEL_VALUE_REPLACE = 0,
	D_MULTI_SEL_VALUE_INSERT,
	D_MULTI_SEL_VALUE_CANCEL,
	D_MULTI_SEL_VALUE_COUNT
};

/** @brief 用户密码框类型*/
typedef enum {
	D_POP_INPUT_NORMAL,		/**< 普通*/
	D_POP_INPUT_POWER_ON,	/**< 开机密码框*/
	D_POP_INPUT_PROG_LOCK	/**< 节目锁密码框*/
} D_PopInputType;


/*弹出菜单优先级定义*/
#define D_POP_MSG_PRIO_MIN			(0)
#define D_POP_MSG_PRIO_MAX			D_POP_PRIO_MAX

/*这些优先级在Video message层使用*/
#define D_POP_MSG_PRIO_VIDEO_MSG_1	(0)
#define D_POP_MSG_PRIO_VIDEO_MSG_2	(1)
#define D_POP_MSG_PRIO_VIDEO_MSG_3	(2)
#define D_POP_MSG_PRIO_VIDEO_MSG_4	(3)

/*这些优先级在Message层使用*/
#define D_POP_MSG_PRIO_MSG_1		(4)
#define D_POP_MSG_PRIO_MSG_2		(5)
#define	D_POP_MSG_PRIO_MSG_3		(6)
#define D_POP_MSG_PRIO_MSG_4		(7)

/** @brief 显示机顶盒信息窗口
* @param prio			消息框的优先级
* @param layer			显示所在的层
* @param type			消息框类型
* @param str_title			要显示的标题文本
* @param msg			要显示的消息id
* @param timeout　		窗口在屏幕上滞留的时间，小于等于０表示永远显示,直到调用d_pop_msg_hide
						或用户手动消除
* @param pop_msg_resp_type	响应类型
* @param video_win_show	在小视频窗口里是否显示
* @param handler		用户确认后调用的函数指针
* @param param			传给用户回调的参数
* @return 显示成功返回D_OK,显示失败返回D_ERR
*/
D_Result d_stb_pop_msg_show (D_U16 prio,
		D_GUILayer layer,
		D_PopMsgType type, const D_Char *str_title, const D_Char *msg, 
		D_MSec timeout, D_PopMsgResponseType pop_msg_resp_type, 
		D_Bool video_win_show,
		D_Result (*handler) (D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT;

/** @brief 闪烁显示机顶盒信息窗口
* @param prio			消息框的优先级
* @param layer			显示所在的层
* @param type			消息框类型
* @param str_title			要显示的标题文本
* @param msg			要显示的消息文本
* @param flash_times        闪烁次数
* @param show_time　	闪烁时显示时间
* @param hide_time		闪烁时隐藏时间
* @param pop_msg_resp_type	响应类型
* @param video_win_show	在小视频窗口里是否显示
* @param handler		用户确认后调用的函数指针
* @param param			传给用户回调的参数
* @return 显示成功返回D_OK,显示失败返回D_ERR
*/
D_Result d_stb_pop_msg_flash_show (D_U16 prio, D_GUILayer layer,
		D_PopMsgType type, const D_Char *str_title, const D_Char *msg, 
		D_U16 flash_times, D_MSec show_time, D_MSec hide_time, 
		D_PopMsgResponseType pop_msg_resp_type, D_Bool video_win_show,
		D_Result (*handler) (D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT;

/** @brief 隐藏显示的消息窗口
* @param prio			消息框的优先级
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_stb_pop_msg_hide (D_U16 prio) D_FUNCPOSTFIT;

/** @brief 显示机顶盒用户选择窗口,用户可以选择确认或取消
* @param prio			消息框的优先级
* @param layer			显示所在的层
* @param str_title			要显示的标题文本
* @param msg			要显示的信息
* @param timeout　		窗口在屏幕上滞留的时间，小于等于０表示永远显示,直道调用d_pop_select_hide
						或用户手动消除
* @param def			D_TRUE表示超时后和用户输入确认效果相同，D_FALSE表示超时后和用户输入取消
						效果相同
* @param handler		选择处理回调函数指针
* @param param			传给用户回调的参数
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_stb_pop_select_show (D_U16 prio,
		D_GUILayer layer,
		const D_Char *str_title,
		const D_Char *msg, D_MSec timeout, 
		D_Bool def, 
		D_Result (*handler) (D_Bool sel, D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT;

D_Result d_stb_pop_select_show_with_prompt (D_U16 prio,
		D_GUILayer layer,
		const D_Char *str_title,
		const D_Char *msg, D_MSec timeout, 
		D_Bool def, 
		D_Result (*handler) (D_Bool sel, D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT;
/** @brief 隐藏显示的用户选择窗口
* @param prio			消息框的优先级
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_stb_pop_select_hide (D_U16 prio) D_FUNCPOSTFIT;


/** @brief 显示输入窗口(有确认与退出提示)
* @param prio			消息框的优先级
* @param layer		显示所在的层
* @param type		输入框类型
* @param str_title			要显示的标题文本
* @param msg			要显示的信息
* @param len			输入字符长度
* @param user_hide	用户是否可以手动退出
* @param handler	选择处理回调函数指针
* @param param		传给用户回调的参数
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_stb_pop_input_show (D_U16 prio,
		D_GUILayer layer,
		D_PopInputType type,
		const D_Char *str_title,
		const D_Char *msg,
		D_U16 len, D_Bool user_hide,
		D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT,
		D_U32	param) D_FUNCPOSTFIT;


/** @brief 显示输入窗口(下面只有确认提示)
* @param prio			消息框的优先级
* @param layer		显示所在的层
* @param type		输入框类型
* @param str_title			要显示的标题文本
* @param msg			要显示的信息
* @param len			输入字符长度
* @param user_hide	用户是否可以手动退出
* @param handler	选择处理回调函数指针
* @param param		传给用户回调的参数
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_stb_pop_input_show_ex (D_U16 prio,
		D_GUILayer layer,
		D_PopInputType type,
		const D_Char *str_title,
		const D_Char *msg,
		D_U16 len, D_Bool user_hide,
		D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT,
		D_U32	param) D_FUNCPOSTFIT;


/** @brief 隐藏显示的用户选择窗口
* @param prio			消息框的优先级
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_stb_pop_input_hide (D_U16 prio) D_FUNCPOSTFIT;


/** @brief 显示机顶盒用户选择窗口,用户可以选择确认或取消
* @param prio			消息框的优先级
* @param layer			显示所在的层
* @param str_title			要显示的标题文本
* @param msg			要显示的信息
* @param timeout　		窗口在屏幕上滞留的时间，小于等于０表示永远显示,直道调用d_pop_select_hide
						或用户手动消除
* @param def			D_TRUE表示超时后和用户输入确认效果相同，D_FALSE表示超时后和用户输入取消
						效果相同
* @param handler		选择处理回调函数指针
* @param param			传给用户回调的参数
* @para posx, posy       显示位置坐标
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_atv_pop_select_show_new (D_U16 prio,
		D_GUILayer layer,
		const D_Char *str_title,
		const D_Char *msg, D_MSec timeout, 
		D_Bool def, 
		D_Result (*handler) (D_Bool sel, D_U32 param) D_FUNCPOSTFIT,
		D_U32 param, D_S32 posx, D_S32 posy) D_FUNCPOSTFIT;


D_Result d_atv_pop_select_show_with_prompt_new (D_U16 prio,
		D_GUILayer layer,
		const D_Char *str_title,
		const D_Char *msg, D_MSec timeout, 
		D_Bool def, 
		D_Result (*handler) (D_Bool sel, D_U32 param) D_FUNCPOSTFIT,
		D_U32 param, D_S32 posx, D_S32 posy) D_FUNCPOSTFIT;


/** @brief 显示机顶盒用户选择窗口,用户可以选择确认或取消
* @param prio			消息框的优先级
* @param layer			显示所在的层
* @param str_title			要显示的标题文本
* @param msg			要显示的信息
* @param timeout　		窗口在屏幕上滞留的时间，小于等于０表示永远显示,直道调用d_pop_select_hide
						或用户手动消除
* @param def			D_TRUE表示超时后和用户输入确认效果相同，D_FALSE表示超时后和用户输入取消
						效果相同
* @param handler		选择处理回调函数指针
* @param param			传给用户回调的参数
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_atv_pop_select_show (D_U16 prio,
		D_GUILayer layer,
		const D_Char *str_title,
		const D_Char *msg, D_MSec timeout, 
		D_Bool def, 
		D_Result (*handler) (D_Bool sel, D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT;

D_Result d_atv_pop_select_show_with_prompt (D_U16 prio,
		D_GUILayer layer,
		const D_Char *str_title,
		const D_Char *msg, D_MSec timeout, 
		D_Bool def, 
		D_Result (*handler) (D_Bool sel, D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT;

/** @brief 隐藏显示的用户选择窗口
* @param prio			消息框的优先级
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
d_atv_pop_select_hide (D_U16 prio) D_FUNCPOSTFIT;

/** @brief 显示机顶盒用户选择窗口,用户可以选择确认或取消
* @param prio			消息框的优先级
* @param layer			显示所在的层
* @param str_title			要显示的标题文本
* @param msg			要显示的信息
* @param timeout　		窗口在屏幕上滞留的时间，小于等于０表示永远显示,直道调用d_pop_select_hide
						或用户手动消除
* @param def			D_TRUE表示超时后和用户输入确认效果相同，D_FALSE表示超时后和用户输入取消
						效果相同
* @param handler		选择处理回调函数指针
* @param param			传给用户回调的参数
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_atv_pop_select_center_show (D_U16 prio,
		D_GUILayer layer,
		const D_Char *str_title,
		const D_Char *msg, D_MSec timeout, 
		D_Bool def, 
		D_Result (*handler) (D_Bool sel, D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT;

D_Result d_atv_pop_select_center_show_with_prompt (D_U16 prio,
		D_GUILayer layer,
		const D_Char *str_title,
		const D_Char *msg, D_MSec timeout, 
		D_Bool def, 
		D_Result (*handler) (D_Bool sel, D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT;

/** @brief 隐藏显示的用户选择窗口
* @param prio			消息框的优先级
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
d_atv_pop_select_center_hide (D_U16 prio) D_FUNCPOSTFIT;

/** @brief 显示机顶盒信息窗口
* @param prio			消息框的优先级
* @param layer			显示所在的层
* @param type			消息框类型
* @param str_title			要显示的标题文本
* @param msg			要显示的消息文本
* @param timeout　		窗口在屏幕上滞留的时间，小于等于０表示永远显示,直到调用d_pop_msg_hide
						或用户手动消除
* @param pop_msg_resp_type	响应类型
* @param video_win_show	在小视频窗口里是否显示
* @param handler		用户确认后调用的函数指针
* @param param			传给用户回调的参数
* @return 显示成功返回D_OK,显示失败返回D_ERR
*/
D_Result d_atv_pop_msg_show (D_U16 prio,
		D_GUILayer layer,
		D_PopMsgType type, const D_Char *str_title, const D_Char *msg, 
		D_MSec timeout, D_PopMsgResponseType pop_msg_resp_type, 
		D_Bool video_win_show,
		D_Result (*handler) (D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT;

/** @brief 闪烁显示机顶盒信息窗口
* @param prio			消息框的优先级
* @param layer			显示所在的层
* @param type			消息框类型
* @param str_title			要显示的标题文本
* @param msg			要显示的消息文本
* @param flash_times        闪烁次数
* @param show_time　	闪烁时显示时间
* @param hide_time		闪烁时隐藏时间
* @param pop_msg_resp_type	响应类型
* @param video_win_show	在小视频窗口里是否显示
* @param handler		用户确认后调用的函数指针
* @param param			传给用户回调的参数
* @return 显示成功返回D_OK,显示失败返回D_ERR
*/
D_Result d_atv_pop_msg_flash_show (D_U16 prio, D_GUILayer layer,
		D_PopMsgType type, const D_Char *str_title, const D_Char *msg, 
		D_U16 flash_times, D_MSec show_time, D_MSec hide_time, 
		D_PopMsgResponseType pop_msg_resp_type, D_Bool video_win_show,
		D_Result (*handler) (D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT;

/** @brief 隐藏显示的消息窗口
* @param prio			消息框的优先级
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result
d_atv_pop_msg_hide (D_U16 prio) D_FUNCPOSTFIT;

/** @brief 显示输入窗口(有确认与退出提示)
* @param prio			消息框的优先级
* @param layer		显示所在的层
* @param type		输入框类型
* @param str_title			要显示的标题文本
* @param msg			要显示的信息
* @param len			输入字符长度
* @param user_hide	用户是否可以手动退出
* @param handler	选择处理回调函数指针
* @param param		传给用户回调的参数
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_atv_pop_input_show (D_U16 prio,
		D_GUILayer layer,
		D_PopInputType type,
		const D_Char *str_title,
		const D_Char *msg,
		D_U16 len, D_Bool user_hide,
		D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT,
		D_U32	param) D_FUNCPOSTFIT;


/** @brief 显示输入窗口(下面只有确认提示)
* @param prio			消息框的优先级
* @param layer		显示所在的层
* @param type		输入框类型
* @param str_title			要显示的标题文本
* @param msg			要显示的信息
* @param len			输入字符长度
* @param user_hide	用户是否可以手动退出
* @param handler	选择处理回调函数指针
* @param param		传给用户回调的参数
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_atv_pop_input_show_ex (D_U16 prio,
		D_GUILayer layer,
		D_PopInputType type,
		const D_Char *str_title,
		const D_Char *msg,
		D_U16 len, D_Bool user_hide,
		D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT,
		D_U32	param) D_FUNCPOSTFIT;


/** @brief 隐藏显示的用户选择窗口
* @param prio			消息框的优先级
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_atv_pop_input_hide (D_U16 prio) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

