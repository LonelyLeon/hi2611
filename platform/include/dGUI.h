/** @file
* @brief GUI����
* @author ����
* @date 2005-8-4 ����: �����ļ�
* @date 2013-04-25 lc: ͳһƽ̨, ��������
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


/** @brief GUI��ʾ��*/
typedef enum {
	D_GUI_LAYER_BACKGROUND,	/**< ����*/
	D_GUI_LAYER_SUBTITLE,		/**< ��Ļ*/
	D_GUI_LAYER_VIDEO,			/**< ��Ƶ��ʾ*/
	D_GUI_LAYER_VIDEO_OSD,	/**< ��Ƶ����*/
	D_GUI_LAYER_VIDEO_MESSAGE,	/**< ��Ƶ�㵯��ʽ��Ϣ*/
	D_GUI_LAYER_MENU_0,				/**< �˵���0*/
	D_GUI_LAYER_USER_0,				/**< �û���0*/	
	D_GUI_LAYER_MENU,				/**< �˵���1*/
	D_GUI_LAYER_USER,				/**< �û���1*/
	D_GUI_LAYER_MENU_2,				/**< �˵���2*/
	D_GUI_LAYER_USER_2,				/**< �û���2*/	
	D_GUI_LAYER_MESSAGE,		/**< ����ʽ��Ϣ*/
	D_GUI_LAYER_CA_OSD,
	D_GUI_LAYER_CA_FINGER,
	D_GUI_LAYER_CA_ECM_FINGER,      /**ECMָ��*/
	D_GUI_LAYER_IME,				/**< ���뷨*/
	D_GUI_LAYER_VOLUME,			/**< ��������*/
    D_GUI_LAYER_VOLUME_1,			/**< ��������*/
    D_GUI_LAYER_LOGO,			/**< logo ˮӡ*/
	D_GUI_LAYER_HIGHEST,			/**< ��߲�*/
	D_GUI_LAYER_MAX			/**< ��������ֻ���ڼ���������������ʾ*/
} D_GUILayer;

/** @brief �˵��¼�*/
typedef enum {
	D_GUI_MENU_BEFORE_SHOW, /*��һ���˵�init֮ǰ���¼�*/
	D_GUI_MENU_SHOW,        /*��һ���˵�init֮����¼�*/
	D_GUI_MENU_HIDE,
	D_GUI_MENU_ENTER,
	D_GUI_MENU_LEAVE
} D_GUIMenuEvent;


/** @brief �˵�������Ķ���*/
typedef enum {
	D_GUI_MENU_GOTO_SUB,	/**< �����Ӳ˵�*/
	D_GUI_MENU_RUN_APP,		/**< ���г���*/	
	D_GUI_MENU_END				/**< �˵��������*/
} D_GUIMenuAction;


#define D_CLEAR_NONE    (D_FALSE)         /**< ������ϼ��˵�*/
#define D_CLEAR_ALL       (D_TRUE)       /**< ����ϼ����в˵�*/
#define D_CLEAR_ONE     (2)        /**< ֻ�����һ���˵�*/

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
       D_U32    reserved;     /**< ���ã�����Ӧ����Ҫ��ʹ��*/
} D_GUIMenuItem;

/** @brief �˵�*/
struct _D_GUIMenu {
	D_Frame *frm;			/**< �˵���Ӧ�Ĳ���*/
	D_GUIMenuItem *items;	/**< �˵��еĲ˵���*/
	D_ID	caption;			/**< �˵���ı����ı�ID*/
	D_ID	icon;		/**< �˵����Ӧ��ͼ��*/	
	D_Bool   clear;			/*����ϼ��˵�ģʽ*/	
	D_ID	focus;			/**< ����˵���*/
       D_U32    reserved;     /**< ���ã�����Ӧ����Ҫ��ʹ��*/    
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


/** @brief �˵��¼��ص�*/
typedef D_Result	(*D_GUIMenuEventCallback) (D_GUIMenuEvent evt, D_Visual *vis) D_FUNCPOSTFIT;

typedef struct
{
	D_GSurface *draw_surf;
	D_HQueue queue;
	D_MSec poll_time;
}D_GUIOpenParam;

/** @brief GUI�����¼����ӻص�����*/
typedef struct
{
	D_EventType input_type;
	D_Ptr       ptr_param;
}D_GUIInputPollHook;


/** @brief ע��gui�ĺ���������*/
typedef enum
{
	GUI_RESOURCE_OP,		/*�˵���Դ����*/
	GUI_OTHER_CALLBACK
}D_GuiCallbackType;

/** @brief ͼ��*/
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

/** @brief ��GUI��*/
D_Result	d_gui_open (D_GUIOpenParam *param) D_FUNCPOSTFIT;

/** @brief ����GUI��ѭ��*/
D_Result	d_gui_main (void) D_FUNCPOSTFIT;

/** @brief ����GUI����id */
D_HTask     d_gui_get_task(void)D_FUNCPOSTFIT;

/** @brief ����GUI��Ϣ���о��*/
D_HQueue	d_gui_get_queue (void) D_FUNCPOSTFIT;

/** @brief ����GUI�Ļ�ͼ����*/
D_GSurface*	d_gui_get_surface (void) D_FUNCPOSTFIT;

/** @brief ����GUIϵͳ�Ƿ������ʾ*/
D_Result	d_gui_show (D_Bool show) D_FUNCPOSTFIT;

/** @brief ������Ļ*/
D_Result	d_gui_update (void) D_FUNCPOSTFIT;

/** @brief �˳�GUI��ѭ��*/
D_Result	d_gui_exit (void) D_FUNCPOSTFIT;

/** @brief �ر�GUI��*/
D_Result	d_gui_close (void) D_FUNCPOSTFIT;

/** @brief ��GUIָ���Ĳ�����ʾ����*/
D_Result	d_gui_open_frame (D_Frame *frm, D_GUILayer layer) D_FUNCPOSTFIT;

/** @brief ����һ���������ʾ*/
D_Result	d_gui_close_frame (D_Frame *frm) D_FUNCPOSTFIT;

/** @brief ��GUIָ������ʾ��������*/
D_Result	d_gui_show_pop_frame (D_Frame *frm, D_GUILayer layer, D_U16 prio) D_FUNCPOSTFIT;

/** @brief ����һ������ʽ����*/
D_Result	d_gui_hide_pop_frame (D_U16 prio) D_FUNCPOSTFIT;

/** @brief ���һ���ϵĴ�����ʾ*/
D_Result	d_gui_clear_layer (D_GUILayer layer) D_FUNCPOSTFIT;

/** @brief �趨һ���ϵ���ʾ�ؼ�*/
D_Result	d_gui_set_layer_vis (D_Visual *vis, D_GUILayer layer) D_FUNCPOSTFIT;

/** @brief ����һ���˵�����
* @param frm		Ҫ���صĴ���
* @param vis		Ҫ���صĿؼ�
* @param menu		�˵�����
* @param clear	�Ƿ�Ҫ����ϼ��˵�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
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

/** @brief �˻ص��ϼ��˵�*/
D_Result	d_gui_upper_menu_ext(D_U32 menu_id)D_FUNCPOSTFIT;
#define d_gui_upper_menu() d_gui_upper_menu_ext(1)

/** @brief �����ʾ��ȫ���˵�*/
D_Result d_gui_clear_menu_ext(D_U32 menu_id)D_FUNCPOSTFIT;
#define d_gui_clear_menu() d_gui_clear_menu_ext(1)

/** @brief �������Ƿ��в˵�*/
D_Bool d_gui_judge_have_menu_ext(D_U32 menu_id)D_FUNCPOSTFIT;
#define  d_gui_judge_have_menu()d_gui_judge_have_menu_ext(1)

/** @brief ���´����滻��ǰ�˵�*/
D_Result	d_gui_replace_menu_ext (D_U32 menu_id, D_Frame *frm, D_Visual *vis, D_GUIMenu *menu) D_FUNCPOSTFIT;

#define d_gui_replace_menu(f)		d_gui_replace_menu_ext(1,f,NULL,NULL)
#define d_gui_replace_vis_menu(v)	d_gui_replace_menu_ext(1,NULL,v,NULL)
#define d_gui_replace_sys_menu(m)	d_gui_replace_menu_ext(1,NULL,NULL, m)

/** @brief ���ص�ǰ�˵�����*/
D_S16 d_gui_get_menu_level_ext(D_U32 menu_id) D_FUNCPOSTFIT;
#define d_gui_get_menu_level() d_gui_get_menu_level_ext(1)

/** @brief ȡ�õ�ǰ����ִ�еĲ˵�*/
D_GUIMenu *d_gui_get_curr_menu_ext(D_U32 menu_id) D_FUNCPOSTFIT;
#define d_gui_get_curr_menu() d_gui_get_curr_menu_ext(1)

/** @brief ע��˵��¼��ص�*/
D_Result d_gui_register_menu_callback_ext(D_U32 menu_id, D_GUIMenuEventCallback callback, D_GUIMenuEventCallback * old) D_FUNCPOSTFIT;
#define d_gui_register_menu_callback(_callback, _old) d_gui_register_menu_callback_ext(1, _callback, _old)

/** @brief ���ػ���ʾ�˵�*/
D_Result d_gui_show_menu(D_U32 menu_id, D_Bool show) D_FUNCPOSTFIT;

/** @brief ���¼���ȫ�������ڵ�ȫ���ַ���
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result	d_gui_reload_string (void) D_FUNCPOSTFIT;

/** @brief �趨��ʾ��ʽ
* @param fmt ��ʾ��ʽ
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result	d_gui_set_format (D_VidFormat fmt) D_FUNCPOSTFIT;

/** @brief ȡ�õ�ǰ��ʾ��ʽ
* @return ���ص�ǰGUI��ʾ��ʽ
*/
D_VidFormat	d_gui_get_format (void) D_FUNCPOSTFIT;

/** @brief GUI��Ϣ����, ������*/
D_Result d_gui_peek_message(D_Msg *msg, D_U32 min_filter, D_U32 max_filter, D_MSec time_out)D_FUNCPOSTFIT;

D_Result d_gui_dispatch_message(D_Msg *msg)D_FUNCPOSTFIT;

D_Result d_gui_do_model (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief ��gui����С��������Ϣ����ʾ��������Ϣ*/
D_Result d_gui_set_video_window_msg(D_Bool show, D_Char *msg)D_FUNCPOSTFIT;

/*ע��gui �ĺ���*/
D_Result
d_gui_register_callback(D_Ptr callback, D_GuiCallbackType type) D_FUNCPOSTFIT;

/*��gui��Դ���Ը��˵�ģ����Դ���г�ʼ��*/
D_Result d_gui_resource_open(void)D_FUNCPOSTFIT;

/*�޸�gui���ԡ��Ը��˵�ģ������趨����*/
D_Result d_gui_lang_set(D_U8 lang)D_FUNCPOSTFIT;

/*ȡ����ԴͼƬ*/
D_Image *d_gui_get_image_res(int image_id, D_U32 *res_type, D_U32 *addr) D_FUNCPOSTFIT;

/*ȡ����ԴͼƬ*/
#define d_gui_get_image(image_id) d_gui_get_image_res(image_id, NULL, NULL)

/*ȡ����Դ�ı�*/
D_Char *d_gui_get_text(int text_id) D_FUNCPOSTFIT;

/*ȡ����Դ��ɫֵ ARGB*/
D_Color d_gui_get_colour(int colour_id) D_FUNCPOSTFIT;


/** @brief ��ʼ������*/
D_Result d_theme_open (void) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif
