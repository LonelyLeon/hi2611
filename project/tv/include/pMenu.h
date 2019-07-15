/** @file
* @brief 菜单结构定义
* @author 李臣
* @date 2013-06-19 李臣: 建立文件
*/
#ifndef __MENU_H
#define __MENU_H

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dVisual.h"
#include "dFrame.h"
#include "dGUI.h"
#if 0
/** @brief 菜单项产生的动作*/
typedef enum {
	D_GUI_MENU_GOTO_SUB,	/**< 进入子菜单*/
	D_GUI_MENU_RUN_APP,		/**< 运行程序*/	
	D_GUI_MENU_END				/**< 菜单定义结束*/
} D_GUIMenuAction;

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
} D_GUIMenuItem;

/** @brief 菜单*/
struct _D_GUIMenu {
	D_Frame *frm;			/**< 菜单对应的布局*/
	D_GUIMenuItem *items;	/**< 菜单中的菜单项*/
	D_ID	caption;			/**< 菜单项的标题文本ID*/
	D_ID	icon;		/**< 菜单项对应的图标*/	
	D_Bool	clear;			/*是否清除上一级菜单*/	
	D_ID	focus;			/**< 焦点菜单项*/
};

#define D_GUI_MENU_ITEM_RUN(_f,_p,_c,_i)\
		{NULL,D_GUI_MENU_RUN_APP,NULL,_f,_p,_c,_i}
#define D_GUI_MENU_ITEM_SUB(_s,_p,_c,_i)\
		{NULL,D_GUI_MENU_GOTO_SUB,_s,NULL,_p,_c,_i}
#define D_GUI_MENU_ITEM_END()\
		{NULL,D_GUI_MENU_END,NULL,NULL,D_FALSE,-1,-1}
#define D_GUI_DECL_MENU(_f,_t,_cap,_i,_clear)\
		{_f,_t,_cap,_i,_clear,0}

#define d_gui_enter_menu(f,c)		d_gui_enter_menu_ex(f,NULL,NULL,c)
#define d_gui_enter_vis_menu(v,c)	d_gui_enter_menu_ex(NULL,v,NULL,c)
#define d_gui_enter_sys_menu(m,c)	d_gui_enter_menu_ex((m)->frm,NULL,NULL,c)
#define d_gui_enter_sub_menu(m,c)	d_gui_enter_menu_ex(NULL,NULL,m,c)
#define d_gui_replace_menu(f)		d_gui_replace_menu_ex(f,NULL)
#define d_gui_replace_vis_menu(v)	d_gui_replace_menu_ex(NULL,v)
#define d_gui_replace_sys_menu(m)	d_gui_replace_menu_ex((m)->frm,NULL)
#endif
#ifdef  __cplusplus
}
#endif
#endif

