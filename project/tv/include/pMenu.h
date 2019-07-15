/** @file
* @brief �˵��ṹ����
* @author �
* @date 2013-06-19 �: �����ļ�
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
/** @brief �˵�������Ķ���*/
typedef enum {
	D_GUI_MENU_GOTO_SUB,	/**< �����Ӳ˵�*/
	D_GUI_MENU_RUN_APP,		/**< ���г���*/	
	D_GUI_MENU_END				/**< �˵��������*/
} D_GUIMenuAction;

typedef struct _D_GUIMenu D_GUIMenu;

/** @brief �˵���*/
typedef struct _D_GUIMenuItem {
	D_Visual *vis;			/**< �˵����Ӧ�Ŀؼ�*/
	D_GUIMenuAction action;		/**< �˵����Ӧ�Ķ���*/
	D_GUIMenu *sub_menu;/**< �˵����Ӧ���Ӳ˵�*/
	D_Result (*app) (void) D_FUNCPOSTFIT;	/**<���˵����Ӧ��Ӧ��*/
	D_Bool passwd;		/**< ����˵����Ƿ���Ҫ��������*/
	D_ID	caption;		/**< �˵���ı����ı�ID*/
	D_ID	icon;		/**< �˵����Ӧ��ͼ��*/	
} D_GUIMenuItem;

/** @brief �˵�*/
struct _D_GUIMenu {
	D_Frame *frm;			/**< �˵���Ӧ�Ĳ���*/
	D_GUIMenuItem *items;	/**< �˵��еĲ˵���*/
	D_ID	caption;			/**< �˵���ı����ı�ID*/
	D_ID	icon;		/**< �˵����Ӧ��ͼ��*/	
	D_Bool	clear;			/*�Ƿ������һ���˵�*/	
	D_ID	focus;			/**< ����˵���*/
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

