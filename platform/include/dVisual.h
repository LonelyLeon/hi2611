
/** @file
* @brief ͼ�οؼ�����
* @author ����
* @date 2005-8-3  ����: �����ļ�
* @date 2006-1-16 ��ѫ: �޸��ļ�
*                   ������������
* ���뺯��
*							d_vis_draw_text_ex
*							d_vis_draw_text_in_range_ex
* @date 2013-04-25 lc: ͳһƽ̨, ��������
* 
*/


#ifndef _D_VISUAL_H_
#define _D_VISUAL_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dGraph.h"
#include "dVisEvent.h"
#include "dTimer.h"
#include "dTouchScreen.h"
#include "dMouse.h"

/*�Ƕȶ���*/
#define D_ANGLE_000 (0 * 64)
#define D_ANGLE_090 (90 * 64)
#define D_ANGLE_180 (180 * 64)
#define D_ANGLE_270 (270 * 64)
#define D_ANGLE_360 (360 * 64)

#define D_CONTROL_STYLE_NORMAL	0
#define D_CONTROL_STYLE_EXTEND	1 

/** @brief �б����ID����/��Ԫ���ƶ�ʱ�õ�*/
typedef struct
{
    D_ID *rowids;
    D_ID *cellids;
}D_ListLinkIds;

/** @brief ͼ�οؼ�*/
typedef struct _D_Visual	D_Visual;
typedef struct _D_VisualOp	D_VisualOp;

/** @brief �ؼ��¼��ص�����*/
typedef D_Result 	 (*D_EventHandler) (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT;

/** @brief ͼ�οؼ���־*/
typedef enum {
	D_VIS_FL_DESTROY		= 0x00000001,	/**< �ؼ��Ѿ�����*/
	D_VIS_FL_UPDATE			= 0x00000002,	/**< �ؼ���Ҫ���»���*/
	D_VIS_FL_SHOW			= 0x00000004,	/**< �ؼ��Ѿ���ʾ*/
	D_VIS_FL_TRANSPARENT	= 0x00000008,	/**< �ؼ���͸����ʾ�ؼ�*/
	D_VIS_FL_FOCUSABLE		= 0x00000010,	/**< �ؼ����Ի�ý���*/
	D_VIS_FL_FOCUSED		= 0x00000020,	/**< �ؼ���ȡ�ý���*/
	D_VIS_FL_FOCUS_CHILD	= 0x00000040,	/**< �ؼ���ptr����������ӿؼ�ָ��*/
	D_VIS_FL_DISABLE		= 0x00000080,	/**< �ؼ����ڲ�����״̬*/
	D_VIS_FL_SUB_EVT		= 0x00000100,	/**< �ؼ��Ѿ�Ԥ�����¼�*/
	D_VIS_FL_UNUSED			= 0x00000200,	/**< û�з���*/
	D_VIS_FL_INPUT_CHAR		= 0x00000400,	/**< �ؼ������ַ�����*/
	D_VIS_FL_ANIMATE		= 0x00000800,	/**< �ؼ��趨����Ч��*/
	D_VIS_FL_SOLVE_DRAW_EVT	= 0x00001000,	/**< �ؼ������ػ��¼�*/
	D_VIS_FL_SELECT		= 0x00002000,	/**< �ؼ���ѡ�е��ǽ���״̬, ��ʱʹ�����б���*/
	D_VIS_FL_CHECK		= 0x00004000,	/**< �ؼ��ѱ�ָ��, ��ʱʹ�����б���*/	
	D_VIS_FL_REMOVE		= 0x00008000,	/**< �ؼ��ƶ�״̬, ��ʱʹ�����б���*/	
	D_VIS_FL_CAPTURE_MOUSE  = 0x00010000,   /**< �������״̬, ���ڼ�¼��갴ť�ڿؼ������ڰ��� */
} D_VisualFlag;

/** @brief ͼ�οؼ�����*/
struct _D_VisualOp {
	D_Result	(*init) (D_Visual *vis) D_FUNCPOSTFIT;
	D_Result	(*destroy) (D_Visual *vis) D_FUNCPOSTFIT;
	D_Result	(*draw)	 (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;
	D_Result	(*handler) (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT;
	D_Result	(*reload_CtrDescr)(D_Visual *vis); /**< ���¼��ؿؼ����� */
};

/** @brief ͼ�οؼ�*/
struct _D_Visual {
	const D_VisualOp	*op;
	D_EventHandler		handler;
	D_Visual			*parent;
	D_Visual			*children;
	D_Visual			*prev;
	D_Visual			*next;
	D_Rect			 	rect;
	D_U32				evt_mask;
	D_U32			 	flags;
	D_Ptr				ptr;
	D_U8				type;
	D_U8				style;	

	D_Char			*text;	/*����������õ��ı�*/
	D_Image			*img;	/*����������õ�ͼƬ*/
	D_Handle			handle;	/*�����ڶ�ʱ��*/
	
	union {
		struct{
			D_U16	cnt;			
			D_U16	page;
			D_U16	step;
			D_U16	val;	
            D_U8    dir; /*����*/
		}scroll;
		
		struct{
			D_U16   	cnt;
			D_U16		val;
			D_Char  **textlist;
		}select;
		
		struct{
			D_U16		cnt;			/**< �������ַ�����*/
			D_U16		val;			/**< ��������Ŀ*/			
			D_U16		val1;		/**< ��ǰ���λ��*/
			D_U16		cursorType;	/**< �������*/
			D_Char	  	chr1;		/**< ������ʾ�ַ�*/
			D_Char	  	chr2;		/**< ��������ַ�*/
		}input;
		
		struct {
			D_U16			cnt;				/**< ������*/
			D_U8			row;			/**< ��ʾһҳ����*/
			D_U8			col;				/**< ����*/
			D_U8	current_col;		/**< ��ǰ��*/  
			D_U8	check_col;		/**< ָ����*/            
			D_U16	current_page;	/**< ��ǰҳ*/
			D_U16			current_row;	/**< ��ǰ��*/
 			D_U16	check_row;	/**< ָ����*/
                     D_Ptr      pCheckAttr;	/**< ָ��������ʾ����*/
                     D_ListLinkIds *pLinkIds;/**< �б����ID����/��Ԫ���ƶ�ʱ�õ�*/
		}list;
		
		struct {
			D_Bool			checked;	/**< ��ѡ���ѡ���Ƿ���ѡ��*/
		}check_radio;
		
		struct{
			D_Bool	focus_loop;	/**< group����н����л�ʱ���Ƿ���Ի����л���
										���ӵ�һ����ǰ�����һ�������һ����󵽵�һ��*/
		}group;

		struct{
			D_Image	*default_img;	/*image�ؼ������ﶨ���ͼƬ*/
            D_Image *temp_img;      /*��̬gif����ʱ����������¼��һ֡*/
		}image;
		
		struct{
			D_U16	cnt;
			D_U16   	step;
			D_U16	val;
			D_U16	colorid;	/*˽��ǰ��ɫ*/
			D_U16	imgid;	/*˽��ǰͼ*/            
            D_U8    dir; /*����*/
		}progress;	
		
		struct{
            D_U16	time_ms;
			D_U16	cnt;
			D_S32  	val;
			D_S32	val1;
		}other;	
	}element;

	
	D_Ptr	pCurrAttr;	/**< ��ǰ��ʾ����*/
	D_Ptr	pAttribute;	/**< �ؼ���������*/
};

/** @brief �ؼ��Ի�ǰ�������ݽṹ */
typedef struct
{
	D_Rect *rect;
	D_Bool *op_draw_dis;
}D_VisDrawHookPre;

/** @brief �ؼ��ַ������ƹ������ݽṹ */
typedef struct
{
    D_Visual *vis;
	D_Rect *rect;
	D_Char *text;
	D_Size cnt;
	void *format;
	void *pcontrol;
    void *pTextShowInfo;
    D_Result *ret;
}D_VisDrawTextHook;

/** @brief �ؼ�����ˢ�����������ݽṹ */
typedef struct
{
    D_Visual *vis;
    D_Rect *update_rect;
}D_VisUpdateRectHook;

/** @brief �ж�һ���ؼ��Ƿ���Ի�ý���*/
#define VIS_FOCUSABLE(_v)\
		(!((_v)->flags & D_VIS_FL_DESTROY) &&\
		((_v)->flags & D_VIS_FL_SHOW) &&\
		(!((_v)->flags & D_VIS_FL_DISABLE)) &&\
		(((_v)->flags & D_VIS_FL_FOCUSABLE) ||\
		(((_v)->flags & D_VIS_FL_FOCUS_CHILD) && (_v)->ptr)))
		
/** @brief �ж�һ���ؼ��Ƿ���Ч*/
#define VIS_ENABLE(_v)\
		((!((_v)->flags & D_VIS_FL_DESTROY)) &&\
		 ((_v)->flags & D_VIS_FL_SHOW) &&\
		 (!((_v)->flags & D_VIS_FL_DISABLE)))

/** @brief �ж�һ���ؼ��Ƿ��Ѿ���������¼�*/
#define VIS_CAPTURED(_v)  ((_v)->flags & D_VIS_FL_CAPTURE_MOUSE)

/** @brief ͼ�οռ�ϵͳ��ʼ��*/
D_Result		d_vis_open (D_GSurface *surf, D_Coord w, D_Coord h) D_FUNCPOSTFIT;

/** @brief ͼ�οռ�ϵͳ��ֹ*/
D_Result		d_vis_close (void) D_FUNCPOSTFIT;

/** @brief �����µ�ͼ�οؼ�*/
D_Visual*		d_vis_new (void) D_FUNCPOSTFIT;

/** @brief �ͷ�ͼ�οؼ���Դ*/
D_Result		d_vis_free (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief �趨һ��ͼ�οؼ�ȡ�ý���*/
D_Result		d_vis_set_focus (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief �趨һ��ͼ�οؼ�ѡ�е��ǽ���״̬(��ʱʹ�����б���)*/
D_Result 		d_vis_set_select (D_Visual *vis, D_Bool sel) D_FUNCPOSTFIT;

/** @brief ȡ��һ��ͼ�οؼ����еĽ���ؼ�*/
D_Visual*		d_vis_get_focus (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief ����һ���ؼ����ڵľ���*/
D_Result		d_vis_set_pos (D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h) D_FUNCPOSTFIT;

/** @brief �趨�ؼ����¼���Ӧ�ص�*/
D_Result		d_vis_set_handler (D_Visual *vis, D_EventHandler handler) D_FUNCPOSTFIT;

/** @brief �����ؼ��¼�*/
D_Result		d_vis_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT;

/** @brief �����ؼ��û��¼�*/
D_Result		d_vis_user_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT;

/** @brief �ڸ��ؼ�ĩβ����һ���ӿؼ�*/
D_Result		d_vis_append_child (D_Visual *parent, D_Visual *child) D_FUNCPOSTFIT;

/** @brief �ڸ��ؼ���ʼ����һ���ӿؼ�*/
D_Result		d_vis_prepend_child (D_Visual *parent, D_Visual *child) D_FUNCPOSTFIT;

/** @brief ��һ���ؼ��ӵ���һ���ؼ�ǰ*/
D_Result		d_vis_insert_before (D_Visual *vis, D_Visual *next) D_FUNCPOSTFIT;

/** @brief ��һ���ؼ��ӵ���һ���ؼ���*/
D_Result		d_vis_insert_after (D_Visual *vis, D_Visual *prev) D_FUNCPOSTFIT;

/** @brief ��ʼ����һ���ؼ�*/
D_Result		d_vis_draw_begin (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief ����һ���ؼ��Ļ��ƹ���*/
D_Result		d_vis_draw_end (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief ȡ��ɫ�ʶ�Ӧ������ֵ*/
D_Pixel			d_vis_map_color (D_Color col) D_FUNCPOSTFIT;

/** @brief ȡ������ֵ��Ӧ��ɫ��*/
D_Color			d_vis_map_pixel (D_Pixel pix) D_FUNCPOSTFIT;

/** @brief ����ǰ��ɫ*/
D_Result		d_vis_set_fg (D_Pixel fg) D_FUNCPOSTFIT;

/** @brief ���ñ���ɫ*/
D_Result		d_vis_set_bg (D_Pixel bg) D_FUNCPOSTFIT;

/** @brief ���û�ͼģʽ */
D_Result		d_vis_set_mode(D_U32 draw_mode) D_FUNCPOSTFIT;

/** @brief ���û�ͼ���� */
D_Result		d_vis_set_param(D_Ptr param) D_FUNCPOSTFIT;

/** @brief �趨һ���ؼ��ϵļ�������*/
D_Result		d_vis_set_clip (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief ��һ���ؼ��ϻ�һ����*/
D_Result		d_vis_draw_point (D_Visual *vis, D_Coord x, D_Coord y) D_FUNCPOSTFIT;

/** @brief ��һ���ؼ��ϻ�һ��ֱ��*/
D_Result		d_vis_draw_line (D_Visual *vis, D_Coord x1, D_Coord y1, D_Coord x2, D_Coord y2) D_FUNCPOSTFIT;

/** @brief ��һ���ؼ��ϻ�һ������*/
D_Result		d_vis_draw_rect (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief ��һ���ؼ��ϻ�һ��������*/
D_Result		d_vis_draw_fill_rect (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;

#ifdef D_GUI_SUPPORT_ELLIPSE
/** @brief ��һ���ؼ��ϻ�һ����Բ*/
D_Result		d_vis_draw_ellipse (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;
#endif

#ifdef D_GUI_SUPPORT_FILL_ELLIPSE
/** @brief ��һ���ؼ��ϻ�һ�������Բ*/
D_Result		d_vis_draw_fill_ellipse (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;
#endif

#ifdef D_GUI_SUPPORT_ARC
/** @brief ��һ���ؼ��ϻ�һ����*/
D_Result		d_vis_draw_arc (D_Visual *vis, D_Rect *rect, D_S32 start, D_S32 end) D_FUNCPOSTFIT;

/** @brief ��һ���ؼ��ϻ�һ������ָ�����   @qiny 2013-11-15*/
D_Result d_vis_draw_arc_ex (D_Visual *vis, D_Rect *rect, D_S32 start, D_S32 end, D_Coord border) D_FUNCPOSTFIT;

/* @brief ��һ���ؼ��ϻ�һ��Բ�Ǿ���@qiny 2013-11-15
* @param border �߿���
* @param rad Բ�ǰ뾶
*/
D_Result d_vis_draw_roundrect(D_Visual *vis, D_Rect *rect, D_Coord rad, D_Coord border)D_FUNCPOSTFIT;

/* @brief ��һ���ؼ��ϻ�һ��Բ�Ǿ���, ��ѡ��Բ��
���type = 0 , Ϊֱ�Ǿ��Ρ�@qiny 2013-11-15
* @param border �߿���
* @param r Բ�ǰ뾶
*/
D_Result d_vis_draw_roundrect_sel(D_Visual *vis, D_Rect *rect, D_Coord rad, D_Coord border, D_RoundRectType type)D_FUNCPOSTFIT;

#endif

#ifdef D_GUI_SUPPORT_FILL_ARC
/** @brief ��һ���ؼ��ϻ�һ����仡*/
D_Result		d_vis_draw_fill_arc (D_Visual *vis, D_Rect *rect, D_S32 start, D_S32 end) D_FUNCPOSTFIT;
#endif

#ifdef D_GUI_SUPPORT_POLY
/** @brief ��һ���ؼ��ϻ�һ�������*/
D_Result		d_vis_draw_poly (D_Visual *vis, D_Point *pts, D_U8 cnt) D_FUNCPOSTFIT;
#endif

#ifdef D_GUI_SUPPORT_FILL_POLY
/** @brief ��һ���ؼ��ϻ�һ���������*/
D_Result		d_vis_draw_fill_poly (D_Visual *vis, D_Point *pts, D_U8 cnt) D_FUNCPOSTFIT;
#endif

/** @brief ��һ���ؼ��ϻ�һ���������*/
D_Result		d_vis_draw_fill_roundarc(D_Visual *vis, D_Rect *rect,D_Coord r, D_RoundRectType type)D_FUNCPOSTFIT;

/* @brief ��һ���ؼ��ϻ�һ�����Բ�Ǿ���, 4���Ƕ���Բ��*/
D_Result		d_vis_draw_fill_roundrect(D_Visual *vis, D_Rect *rect, D_Coord r)D_FUNCPOSTFIT;

/* @brief ��һ���ؼ��ϻ�һ�����Բ�Ǿ���, ��ѡ��Բ��
���type = 0 , Ϊ���ֱ�Ǿ��Ρ�@qiny 2013-11-15*/
D_Result d_vis_draw_fill_roundrect_sel(D_Visual *vis, D_Rect *rect, D_Coord r, D_RoundRectType type)D_FUNCPOSTFIT;

/** @brief ��һ���ؼ��ϻ�һ���ַ���*/
D_Result		d_vis_draw_text (D_Visual *vis, D_Coord x, D_Coord y, D_Char *txt, D_Size cnt) D_FUNCPOSTFIT;

/** @brief ��һ���ؼ��ϵ�һ����Χ�ڻ�һ���ַ���*/
D_Result		d_vis_draw_text_in_range (D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Char **text, D_Size cnt, D_Bool draw_last) D_FUNCPOSTFIT;

/** @brief ��һ���ؼ��ϻ�һ��ͼ��*/
D_Result		d_vis_draw_image (D_Visual *vis, D_Rect *dr, D_Image *img, D_Rect *sr) D_FUNCPOSTFIT;

/** @brief ��һ���ؼ������ε��ϻ�һ��ͼ��*/
D_Result		d_vis_draw_image_mask (D_Visual *vis, D_Rect *dr, D_Image *img, D_Rect *sr) D_FUNCPOSTFIT;

/** @brief ��ʾһ���ؼ�*/
D_Result		d_vis_show (D_Visual *vis, D_Bool show) D_FUNCPOSTFIT;

/** @brief �趨һ���ؼ��Ŀ���״̬*/
D_Result		d_vis_enable (D_Visual *vis, D_Bool en) D_FUNCPOSTFIT;

/** @brief �趨һ���ؼ��Ŀɾ۽�״̬*/
D_Result		d_vis_set_focusable (D_Visual *vis, D_Bool f) D_FUNCPOSTFIT;

/** @brief ȡ��һ���ؼ��Ŀɾ۽�״̬,add by ����2011-4-26*/
D_Bool d_vis_get_focusable (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief  �������»���һ���ؼ�*/
D_Result		d_vis_update (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief �ؼ����»���(GUIģ�����)*/
D_Result		d_vis_redraw (void) D_FUNCPOSTFIT;

/** @brief �����¼�(GUIģ�����)*/
D_Result		d_vis_solve_event (D_Event *evt) D_FUNCPOSTFIT;

/** @brief ������ٵĿؼ�(GUIģ�����)*/
D_Result		d_vis_clear_destroy (void) D_FUNCPOSTFIT;

/** @brief ȡΪ��һ���ɾ۽��ؼ�*/
D_Visual*	d_vis_prev_focus (D_Visual *vis)  D_FUNCPOSTFIT;

/** @brief ȡ��һ���ɾ۽��ؼ�*/
D_Visual*	d_vis_next_focus (D_Visual *vis)  D_FUNCPOSTFIT;

/** @brief ע��һ���¼�*/
D_Result	d_vis_subscribe_evt (D_Visual *vis, D_U32 mask, D_Handle handle) D_FUNCPOSTFIT;

/** @brief ��һ���ؼ�������ע���¼����з�ע��*/
D_Result	d_vis_unsubscribe_evt (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief ��ע��һ���¼�*/
D_Result	d_vis_unsubscribe_one_evt (D_Visual *vis, D_U32 mask, D_Handle handle) D_FUNCPOSTFIT;

/** @brief ȡ��һ���ؼ�����Ļ�ϵ�����*/
D_Result d_vis_get_pos (D_Visual *vis, D_Coord *x, D_Coord *y) D_FUNCPOSTFIT;

/* add by liux */
D_Result d_vis_draw_text_ex (D_Visual *vis, D_Coord x, D_Coord y, D_Char *txt, D_Size cnt, D_FontAttrType type) D_FUNCPOSTFIT;

/*add by qiny 2012-09-05*/
D_Result d_vis_draw_text_middle (D_Visual *vis, D_Coord x, D_Coord y, D_Char *text, D_Size cnt, D_Coord lineH) D_FUNCPOSTFIT;
/*add by qiny 2012-09-05*/
D_Result d_vis_draw_text_middle_ex (D_Visual *vis, D_Coord x, D_Coord y, D_Char *text, D_Size cnt, D_FontAttrType type, D_Coord lineH) D_FUNCPOSTFIT;

D_Result d_vis_draw_text_in_range_ex (D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Char **text, D_Size cnt, D_Bool draw_last, D_FontAttrType type) D_FUNCPOSTFIT;

/** @brief vis������ת������Ļ���� */
D_Result d_vis_pos_v2s(D_Visual *vis, D_Coord *x, D_Coord *y) D_FUNCPOSTFIT;

/** @brief ��Ļ����ת����vis���� */
D_Result d_vis_pos_s2v(D_Visual *vis, D_Coord *x, D_Coord *y) D_FUNCPOSTFIT;

/** @brief ���ÿؼ�������*/
D_Result d_vis_set_type (D_Visual *vis, D_U8 type) D_FUNCPOSTFIT;

/** @brief ���ÿؼ�����ʾ����*/
D_Result d_vis_set_attribute(D_Visual *vis, D_Ptr pattr)D_FUNCPOSTFIT;

/** @brief ���ÿؼ����Ƿ����ػ��¼�
�����÷���ʹ֮����area�ؼ����ƣ����Դ���
D_EVT_DRAW, ����ִ�пؼ�����Ļ��ƺ�����
�ٽ����û�����D_EVT_DRAW�¼�*/
D_Result
d_vis_set_solve_draw_evt(D_Visual *vis, D_Bool solve)D_FUNCPOSTFIT;


D_Result d_vis_solve_mouse_event(D_MousePollData *mpd) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
