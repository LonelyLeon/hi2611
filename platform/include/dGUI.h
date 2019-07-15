/** @file
* @brief GUI操作
* @author 龚克
* @date 2005-8-4 龚克: 建立文件
* @date 2013-04-25 lc: 统一平台, 代码整理
*/

#ifndef _D_GUI_H_
#define _D_GUI_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dGraph.h"
#include "dVisual.h"
#include "dFrame.h"
#include "dQueue.h"
#include "dTask.h"
#include "dMsg.h"


/** @brief GUI显示层*/
typedef enum {
	D_GUI_LAYER_BACKGROUND,	/**< 背景*/
	D_GUI_LAYER_SUBTITLE,		/**< 字幕*/
	D_GUI_LAYER_VIDEO,			/**< 视频显示*/
	D_GUI_LAYER_VIDEO_OSD,	/**< 视频控制*/
	D_GUI_LAYER_VIDEO_MESSAGE,	/**< 视频层弹出式信息*/
	D_GUI_LAYER_MENU_0,				/**< 菜单层0*/
	D_GUI_LAYER_USER_0,				/**< 用户层0*/	
	D_GUI_LAYER_MENU,				/**< 菜单层1*/
	D_GUI_LAYER_USER,				/**< 用户层1*/
	D_GUI_LAYER_MENU_2,				/**< 菜单层2*/
	D_GUI_LAYER_USER_2,				/**< 用户层2*/	
	D_GUI_LAYER_MESSAGE,		/**< 弹出式消息*/
	D_GUI_LAYER_CA_OSD,
	D_GUI_LAYER_CA_FINGER,
	D_GUI_LAYER_CA_ECM_FINGER,      /**ECM指纹*/
	D_GUI_LAYER_IME,				/**< 输入法*/
	D_GUI_LAYER_VOLUME,			/**< 音量调节*/
    D_GUI_LAYER_VOLUME_1,			/**< 音量调节*/
    D_GUI_LAYER_LOGO,			/**< logo 水印*/
	D_GUI_LAYER_HIGHEST,			/**< 最高层*/
	D_GUI_LAYER_MAX			/**< 最大层数，只用于计数，不可用于显示*/
} D_GUILayer;

/** @brief 菜单事件*/
typedef enum {
	D_GUI_MENU_BEFORE_SHOW, /*第一个菜单init之前的事件*/
	D_GUI_MENU_SHOW,        /*第一个菜单init之后的事件*/
	D_GUI_MENU_HIDE,
	D_GUI_MENU_ENTER,
	D_GUI_MENU_LEAVE
} D_GUIMenuEvent;


/** @brief 菜单项产生的动作*/
typedef enum {
	D_GUI_MENU_GOTO_SUB,	/**< 进入子菜单*/
	D_GUI_MENU_RUN_APP,		/**< 运行程序*/	
	D_GUI_MENU_END				/**< 菜单定义结束*/
} D_GUIMenuAction;


#define D_CLEAR_NONE    (D_FALSE)         /**< 不清除上级菜单*/
#define D_CLEAR_ALL       (D_TRUE)       /**< 清除上级所有菜单*/
#define D_CLEAR_ONE     (2)        /**< 只清除上一级菜单*/

typedef struct _D_GUIMenu D_GUIMenu;

/** @brief 菜单项*/
typedef struct _D_GUIMenuItem {
	D_Visual *vis;			/**< 菜单项对应的控件*/
	D_GUIMenuAction action;		/**< 菜单项对应的动作*/
	D_GUIMenu *sub_menu;/**< 菜单项对应的子菜单*/
	D_Result (*app) (void) D_FUNCPOSTFIT;	/**<　菜单项对应的应用*/
	D_Bool passwd;		/**< 进入菜单项是否需要输入密码*/
	D_ID	caption;		/**< 菜单项的标题文本ID*/
	D_ID	icon;		/**< 菜单项对应的图标*/	
       D_U32    reserved;     /**< 备用，根据应用需要求使用*/
} D_GUIMenuItem;

/** @brief 菜单*/
struct _D_GUIMenu {
	D_Frame *frm;			/**< 菜单对应的布局*/
	D_GUIMenuItem *items;	/**< 菜单中的菜单项*/
	D_ID	caption;			/**< 菜单项的标题文本ID*/
	D_ID	icon;		/**< 菜单项对应的图标*/	
	D_Bool   clear;			/*清除上级菜单模式*/	
	D_ID	focus;			/**< 焦点菜单项*/
       D_U32    reserved;     /**< 备用，根据应用需要求使用*/    
};

#define D_GUI_MENU_ITEM_RUN(_f,_p,_c,_i)\
		{NULL,D_GUI_MENU_RUN_APP,NULL,_f,_p,_c,_i, 0}
#define D_GUI_MENU_ITEM_SUB(_s,_p,_c,_i)\
		{NULL,D_GUI_MENU_GOTO_SUB,_s,NULL,_p,_c,_i, 0}
#define D_GUI_MENU_ITEM_END()\
		{NULL,D_GUI_MENU_END,NULL,NULL,D_FALSE,-1,-1,0}
#define D_GUI_DECL_MENU(_f,_t,_cap,_i,_clear)\
		{_f,_t,_cap,_i,_clear,0,0}

#define D_GUI_MENU_ITEM_RUN_EX(_f,_p,_c,_i,_r)\
		{NULL,D_GUI_MENU_RUN_APP,NULL,_f,_p,_c,_i,_r}
#define D_GUI_MENU_ITEM_SUB_EX(_s,_p,_c,_i,_r)\
		{NULL,D_GUI_MENU_GOTO_SUB,_s,NULL,_p,_c,_i,_r}
#define D_GUI_DECL_MENU_EX(_f,_t,_cap,_i,_clear,_r)\
		{_f,_t,_cap,_i,_clear,0,_r}


/** @brief 菜单事件回调*/
typedef D_Result	(*D_GUIMenuEventCallback) (D_GUIMenuEvent evt, D_Visual *vis) D_FUNCPOSTFIT;

typedef struct
{
	D_GSurface *draw_surf;
	D_HQueue queue;
	D_MSec poll_time;
}D_GUIOpenParam;

/** @brief GUI输入事件钩子回调参数*/
typedef struct
{
	D_EventType input_type;
	D_Ptr       ptr_param;
}D_GUIInputPollHook;


/** @brief 注册gui的函数的类型*/
typedef enum
{
	GUI_RESOURCE_OP,		/*菜单资源操作*/
	GUI_OTHER_CALLBACK
}D_GuiCallbackType;

/** @brief 图像*/
typedef struct 
{
	unsigned char D_FAR *buffer;
	D_S32		 size;
	D_Image	*img;
} SysImage;

typedef struct 
{
	SysImage image[2];
}D_SysImage;



typedef D_Result (*GuiToolDrawVis) (D_Visual *vis) D_FUNCPOSTFIT;
typedef D_Result (*fGuiTool)(D_Visual *vis) D_FUNCPOSTFIT;


typedef D_Result (*D_GuiResourceInit)(void) D_FUNCPOSTFIT;
typedef D_Result (*D_GuiResourceSetLan)(D_U8 lan) D_FUNCPOSTFIT;
typedef D_Image * (*D_GuiGetImageCallback) (int image_id, D_U32 *res_type, D_U32* addr) D_FUNCPOSTFIT;
typedef D_Char * (*D_GuiGetTextCallback) (int text_id) D_FUNCPOSTFIT;
typedef D_Color (*D_GuiGetColourCallback) (int colour_id) D_FUNCPOSTFIT;



#define D_GUI_RES_SEC_CNT 16
typedef struct
{
	D_Bool used;
	D_U8 module_no;
	D_U16 idstart;
	D_U16 idend;
	D_GuiResourceInit res_init;
	D_GuiResourceSetLan set_lan;
	D_GuiGetTextCallback get_text;
	D_GuiGetColourCallback get_color;
	D_GuiGetImageCallback get_image;
}D_GuiResourceOp;

/** @brief 打开GUI库*/
D_Result	d_gui_open (D_GUIOpenParam *param) D_FUNCPOSTFIT;

/** @brief 进入GUI主循环*/
D_Result	d_gui_main (void) D_FUNCPOSTFIT;

/** @brief 返回GUI任务id */
D_HTask     d_gui_get_task(void)D_FUNCPOSTFIT;

/** @brief 返回GUI消息队列句柄*/
D_HQueue	d_gui_get_queue (void) D_FUNCPOSTFIT;

/** @brief 返回GUI的绘图表面*/
D_GSurface*	d_gui_get_surface (void) D_FUNCPOSTFIT;

/** @brief 设置GUI系统是否进行显示*/
D_Result	d_gui_show (D_Bool show) D_FUNCPOSTFIT;

/** @brief 更新屏幕*/
D_Result	d_gui_update (void) D_FUNCPOSTFIT;

/** @brief 退出GUI主循环*/
D_Result	d_gui_exit (void) D_FUNCPOSTFIT;

/** @brief 关闭GUI库*/
D_Result	d_gui_close (void) D_FUNCPOSTFIT;

/** @brief 在GUI指定的层中显示窗体*/
D_Result	d_gui_open_frame (D_Frame *frm, D_GUILayer layer) D_FUNCPOSTFIT;

/** @brief 隐藏一个窗体的显示*/
D_Result	d_gui_close_frame (D_Frame *frm) D_FUNCPOSTFIT;

/** @brief 在GUI指定层显示弹出窗口*/
D_Result	d_gui_show_pop_frame (D_Frame *frm, D_GUILayer layer, D_U16 prio) D_FUNCPOSTFIT;

/** @brief 隐藏一个弹出式窗口*/
D_Result	d_gui_hide_pop_frame (D_U16 prio) D_FUNCPOSTFIT;

/** @brief 清除一层上的窗体显示*/
D_Result	d_gui_clear_layer (D_GUILayer layer) D_FUNCPOSTFIT;

/** @brief 设定一层上的显示控件*/
D_Result	d_gui_set_layer_vis (D_Visual *vis, D_GUILayer layer) D_FUNCPOSTFIT;

/** @brief 进入一个菜单窗体
* @param frm		要加载的窗口
* @param vis		要加载的控件
* @param menu		菜单定义
* @param clear	是否要清除上级菜单
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result	d_gui_enter_menu_ext (D_U32 menu_id, D_Frame *frm, D_Visual *vis, D_GUIMenu *menu, D_Bool clear) D_FUNCPOSTFIT;

#define d_gui_enter_menu(f,c)		d_gui_enter_menu_ext(1,f,NULL,NULL,c)
#define d_gui_enter_vis_menu(v,c)	d_gui_enter_menu_ext(1,NULL,v,NULL,c)
#define d_gui_enter_sys_menu(m,c)	d_gui_enter_menu_ext(1,(m)->frm,NULL,m,c)
#define d_gui_enter_sub_menu(m,c)	d_gui_enter_menu_ext(1,(m)->frm,NULL,m,c)

#define d_gui_enter_menu_new(i,f,c)		d_gui_enter_menu_ext(i,f,NULL,NULL,c)
#define d_gui_enter_vis_menu_new(i,v,c)	d_gui_enter_menu_ext(i,NULL,v,NULL,c)
#define d_gui_enter_sys_menu_new(i,m,c)	d_gui_enter_menu_ext(i,(m)->frm,NULL,m,c)
#define d_gui_enter_sub_menu_new(i,m,c)	d_gui_enter_menu_ext(i,(m)->frm,NULL,m,c)

/** @brief 退回到上级菜单*/
D_Result	d_gui_upper_menu_ext(D_U32 menu_id)D_FUNCPOSTFIT;
#define d_gui_upper_menu() d_gui_upper_menu_ext(1)

/** @brief 清除显示的全部菜单*/
D_Result d_gui_clear_menu_ext(D_U32 menu_id)D_FUNCPOSTFIT;
#define d_gui_clear_menu() d_gui_clear_menu_ext(1)

/** @brief 界面上是否有菜单*/
D_Bool d_gui_judge_have_menu_ext(D_U32 menu_id)D_FUNCPOSTFIT;
#define  d_gui_judge_have_menu()d_gui_judge_have_menu_ext(1)

/** @brief 用新窗体替换当前菜单*/
D_Result	d_gui_replace_menu_ext (D_U32 menu_id, D_Frame *frm, D_Visual *vis, D_GUIMenu *menu) D_FUNCPOSTFIT;

#define d_gui_replace_menu(f)		d_gui_replace_menu_ext(1,f,NULL,NULL)
#define d_gui_replace_vis_menu(v)	d_gui_replace_menu_ext(1,NULL,v,NULL)
#define d_gui_replace_sys_menu(m)	d_gui_replace_menu_ext(1,NULL,NULL, m)

/** @brief 返回当前菜单级数*/
D_S16 d_gui_get_menu_level_ext(D_U32 menu_id) D_FUNCPOSTFIT;
#define d_gui_get_menu_level() d_gui_get_menu_level_ext(1)

/** @brief 取得当前正在执行的菜单*/
D_GUIMenu *d_gui_get_curr_menu_ext(D_U32 menu_id) D_FUNCPOSTFIT;
#define d_gui_get_curr_menu() d_gui_get_curr_menu_ext(1)

/** @brief 注册菜单事件回调*/
D_Result d_gui_register_menu_callback_ext(D_U32 menu_id, D_GUIMenuEventCallback callback, D_GUIMenuEventCallback * old) D_FUNCPOSTFIT;
#define d_gui_register_menu_callback(_callback, _old) d_gui_register_menu_callback_ext(1, _callback, _old)

/** @brief 隐藏或显示菜单*/
D_Result d_gui_show_menu(D_U32 menu_id, D_Bool show) D_FUNCPOSTFIT;

/** @brief 重新加载全部窗体内的全部字符串
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result	d_gui_reload_string (void) D_FUNCPOSTFIT;

/** @brief 设定显示制式
* @param fmt 显示制式
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result	d_gui_set_format (D_VidFormat fmt) D_FUNCPOSTFIT;

/** @brief 取得当前显示制式
* @return 返回当前GUI显示制式
*/
D_VidFormat	d_gui_get_format (void) D_FUNCPOSTFIT;

/** @brief GUI消息接收, 处理函数*/
D_Result d_gui_peek_message(D_Msg *msg, D_U32 min_filter, D_U32 max_filter, D_MSec time_out)D_FUNCPOSTFIT;

D_Result d_gui_dispatch_message(D_Msg *msg)D_FUNCPOSTFIT;

D_Result d_gui_do_model (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 向gui发送小窗口里信息的显示与隐藏消息*/
D_Result d_gui_set_video_window_msg(D_Bool show, D_Char *msg)D_FUNCPOSTFIT;

/*注册gui 的函数*/
D_Result
d_gui_register_callback(D_Ptr callback, D_GuiCallbackType type) D_FUNCPOSTFIT;

/*打开gui资源。对各菜单模块资源进行初始化*/
D_Result d_gui_resource_open(void)D_FUNCPOSTFIT;

/*修改gui语言。对各菜单模块进行设定语言*/
D_Result d_gui_lang_set(D_U8 lang)D_FUNCPOSTFIT;

/*取得资源图片*/
D_Image *d_gui_get_image_res(int image_id, D_U32 *res_type, D_U32 *addr) D_FUNCPOSTFIT;

/*取得资源图片*/
#define d_gui_get_image(image_id) d_gui_get_image_res(image_id, NULL, NULL)

/*取得资源文本*/
D_Char *d_gui_get_text(int text_id) D_FUNCPOSTFIT;

/*取得资源颜色值 ARGB*/
D_Color d_gui_get_colour(int colour_id) D_FUNCPOSTFIT;


/** @brief 初始化主题*/
D_Result d_theme_open (void) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif
