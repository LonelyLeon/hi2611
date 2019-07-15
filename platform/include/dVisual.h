
/** @file
* @brief 图形控件操作
* @author 龚克
* @date 2005-8-3  龚克: 建立文件
* @date 2006-1-16 刘勋: 修改文件
*                   加入字体属性
* 加入函数
*							d_vis_draw_text_ex
*							d_vis_draw_text_in_range_ex
* @date 2013-04-25 lc: 统一平台, 代码整理
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

/*角度定义*/
#define D_ANGLE_000 (0 * 64)
#define D_ANGLE_090 (90 * 64)
#define D_ANGLE_180 (180 * 64)
#define D_ANGLE_270 (270 * 64)
#define D_ANGLE_360 (360 * 64)

#define D_CONTROL_STYLE_NORMAL	0
#define D_CONTROL_STYLE_EXTEND	1 

/** @brief 列表关联ID，行/单元格移动时用到*/
typedef struct
{
    D_ID *rowids;
    D_ID *cellids;
}D_ListLinkIds;

/** @brief 图形控件*/
typedef struct _D_Visual	D_Visual;
typedef struct _D_VisualOp	D_VisualOp;

/** @brief 控件事件回调函数*/
typedef D_Result 	 (*D_EventHandler) (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT;

/** @brief 图形控件标志*/
typedef enum {
	D_VIS_FL_DESTROY		= 0x00000001,	/**< 控件已经销毁*/
	D_VIS_FL_UPDATE			= 0x00000002,	/**< 控件需要重新绘制*/
	D_VIS_FL_SHOW			= 0x00000004,	/**< 控件已经显示*/
	D_VIS_FL_TRANSPARENT	= 0x00000008,	/**< 控件是透明显示控件*/
	D_VIS_FL_FOCUSABLE		= 0x00000010,	/**< 控件可以获得焦点*/
	D_VIS_FL_FOCUSED		= 0x00000020,	/**< 控件已取得焦点*/
	D_VIS_FL_FOCUS_CHILD	= 0x00000040,	/**< 控件的ptr域包含焦点子控件指针*/
	D_VIS_FL_DISABLE		= 0x00000080,	/**< 控件处于不可用状态*/
	D_VIS_FL_SUB_EVT		= 0x00000100,	/**< 控件已经预订了事件*/
	D_VIS_FL_UNUSED			= 0x00000200,	/**< 没有分配*/
	D_VIS_FL_INPUT_CHAR		= 0x00000400,	/**< 控件接收字符输入*/
	D_VIS_FL_ANIMATE		= 0x00000800,	/**< 控件设定动画效果*/
	D_VIS_FL_SOLVE_DRAW_EVT	= 0x00001000,	/**< 控件处理重绘事件*/
	D_VIS_FL_SELECT		= 0x00002000,	/**< 控件已选中但非焦点状态, 暂时使用在列表里*/
	D_VIS_FL_CHECK		= 0x00004000,	/**< 控件已被指定, 暂时使用在列表里*/	
	D_VIS_FL_REMOVE		= 0x00008000,	/**< 控件移动状态, 暂时使用在列表里*/	
	D_VIS_FL_CAPTURE_MOUSE  = 0x00010000,   /**< 捕获鼠标状态, 用于记录鼠标按钮在控件区域内按下 */
} D_VisualFlag;

/** @brief 图形控件操作*/
struct _D_VisualOp {
	D_Result	(*init) (D_Visual *vis) D_FUNCPOSTFIT;
	D_Result	(*destroy) (D_Visual *vis) D_FUNCPOSTFIT;
	D_Result	(*draw)	 (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;
	D_Result	(*handler) (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT;
	D_Result	(*reload_CtrDescr)(D_Visual *vis); /**< 重新加载控件属性 */
};

/** @brief 图形控件*/
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

	D_Char			*text;	/*用于软件设置的文本*/
	D_Image			*img;	/*用于软件设置的图片*/
	D_Handle			handle;	/*可用于定时器*/
	
	union {
		struct{
			D_U16	cnt;			
			D_U16	page;
			D_U16	step;
			D_U16	val;	
            D_U8    dir; /*方向*/
		}scroll;
		
		struct{
			D_U16   	cnt;
			D_U16		val;
			D_Char  **textlist;
		}select;
		
		struct{
			D_U16		cnt;			/**< 可输入字符总数*/
			D_U16		val;			/**< 已输入数目*/			
			D_U16		val1;		/**< 当前光标位置*/
			D_U16		cursorType;	/**< 光标类型*/
			D_Char	  	chr1;		/**< 密码提示字符*/
			D_Char	  	chr2;		/**< 密码代替字符*/
		}input;
		
		struct {
			D_U16			cnt;				/**< 总行数*/
			D_U8			row;			/**< 显示一页行数*/
			D_U8			col;				/**< 列数*/
			D_U8	current_col;		/**< 当前列*/  
			D_U8	check_col;		/**< 指定列*/            
			D_U16	current_page;	/**< 当前页*/
			D_U16			current_row;	/**< 当前行*/
 			D_U16	check_row;	/**< 指定行*/
                     D_Ptr      pCheckAttr;	/**< 指定行列显示属性*/
                     D_ListLinkIds *pLinkIds;/**< 列表关联ID，行/单元格移动时用到*/
		}list;
		
		struct {
			D_Bool			checked;	/**< 单选框多选框是否已选中*/
		}check_radio;
		
		struct{
			D_Bool	focus_loop;	/**< group里进行焦点切换时，是否可以环形切换。
										即从第一个向前到最后一个，最后一个向后到第一个*/
		}group;

		struct{
			D_Image	*default_img;	/*image控件属性里定义的图片*/
            D_Image *temp_img;      /*动态gif，临时缓冲区，记录上一帧*/
		}image;
		
		struct{
			D_U16	cnt;
			D_U16   	step;
			D_U16	val;
			D_U16	colorid;	/*私有前景色*/
			D_U16	imgid;	/*私有前图*/            
            D_U8    dir; /*方向*/
		}progress;	
		
		struct{
            D_U16	time_ms;
			D_U16	cnt;
			D_S32  	val;
			D_S32	val1;
		}other;	
	}element;

	
	D_Ptr	pCurrAttr;	/**< 当前显示属性*/
	D_Ptr	pAttribute;	/**< 控件属性描述*/
};

/** @brief 控件自绘前钩子数据结构 */
typedef struct
{
	D_Rect *rect;
	D_Bool *op_draw_dis;
}D_VisDrawHookPre;

/** @brief 控件字符串绘制钩子数据结构 */
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

/** @brief 控件引起刷新区域钩子数据结构 */
typedef struct
{
    D_Visual *vis;
    D_Rect *update_rect;
}D_VisUpdateRectHook;

/** @brief 判断一个控件是否可以获得焦点*/
#define VIS_FOCUSABLE(_v)\
		(!((_v)->flags & D_VIS_FL_DESTROY) &&\
		((_v)->flags & D_VIS_FL_SHOW) &&\
		(!((_v)->flags & D_VIS_FL_DISABLE)) &&\
		(((_v)->flags & D_VIS_FL_FOCUSABLE) ||\
		(((_v)->flags & D_VIS_FL_FOCUS_CHILD) && (_v)->ptr)))
		
/** @brief 判断一个控件是否有效*/
#define VIS_ENABLE(_v)\
		((!((_v)->flags & D_VIS_FL_DESTROY)) &&\
		 ((_v)->flags & D_VIS_FL_SHOW) &&\
		 (!((_v)->flags & D_VIS_FL_DISABLE)))

/** @brief 判断一个控件是否已经捕获鼠标事件*/
#define VIS_CAPTURED(_v)  ((_v)->flags & D_VIS_FL_CAPTURE_MOUSE)

/** @brief 图形空间系统初始化*/
D_Result		d_vis_open (D_GSurface *surf, D_Coord w, D_Coord h) D_FUNCPOSTFIT;

/** @brief 图形空间系统终止*/
D_Result		d_vis_close (void) D_FUNCPOSTFIT;

/** @brief 创建新的图形控件*/
D_Visual*		d_vis_new (void) D_FUNCPOSTFIT;

/** @brief 释放图形控件资源*/
D_Result		d_vis_free (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 设定一个图形控件取得焦点*/
D_Result		d_vis_set_focus (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 设定一个图形控件选中但非焦点状态(暂时使用在列表里)*/
D_Result 		d_vis_set_select (D_Visual *vis, D_Bool sel) D_FUNCPOSTFIT;

/** @brief 取得一个图形控件树中的焦点控件*/
D_Visual*		d_vis_get_focus (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 设置一个控件所在的矩形*/
D_Result		d_vis_set_pos (D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Coord h) D_FUNCPOSTFIT;

/** @brief 设定控件的事件响应回调*/
D_Result		d_vis_set_handler (D_Visual *vis, D_EventHandler handler) D_FUNCPOSTFIT;

/** @brief 触发控件事件*/
D_Result		d_vis_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT;

/** @brief 触发控件用户事件*/
D_Result		d_vis_user_handler (D_Visual *vis, D_Event *evt) D_FUNCPOSTFIT;

/** @brief 在父控件末尾增加一个子控件*/
D_Result		d_vis_append_child (D_Visual *parent, D_Visual *child) D_FUNCPOSTFIT;

/** @brief 在父控件开始增加一个子控件*/
D_Result		d_vis_prepend_child (D_Visual *parent, D_Visual *child) D_FUNCPOSTFIT;

/** @brief 将一个控件加到另一个控件前*/
D_Result		d_vis_insert_before (D_Visual *vis, D_Visual *next) D_FUNCPOSTFIT;

/** @brief 将一个控件加到另一个控件后*/
D_Result		d_vis_insert_after (D_Visual *vis, D_Visual *prev) D_FUNCPOSTFIT;

/** @brief 开始绘制一个控件*/
D_Result		d_vis_draw_begin (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief 结束一个控件的绘制过程*/
D_Result		d_vis_draw_end (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 取得色彩对应的像素值*/
D_Pixel			d_vis_map_color (D_Color col) D_FUNCPOSTFIT;

/** @brief 取得像素值对应的色彩*/
D_Color			d_vis_map_pixel (D_Pixel pix) D_FUNCPOSTFIT;

/** @brief 设置前景色*/
D_Result		d_vis_set_fg (D_Pixel fg) D_FUNCPOSTFIT;

/** @brief 设置背景色*/
D_Result		d_vis_set_bg (D_Pixel bg) D_FUNCPOSTFIT;

/** @brief 设置绘图模式 */
D_Result		d_vis_set_mode(D_U32 draw_mode) D_FUNCPOSTFIT;

/** @brief 设置绘图参数 */
D_Result		d_vis_set_param(D_Ptr param) D_FUNCPOSTFIT;

/** @brief 设定一个控件上的剪切区域*/
D_Result		d_vis_set_clip (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief 在一个控件上画一个点*/
D_Result		d_vis_draw_point (D_Visual *vis, D_Coord x, D_Coord y) D_FUNCPOSTFIT;

/** @brief 在一个控件上画一条直线*/
D_Result		d_vis_draw_line (D_Visual *vis, D_Coord x1, D_Coord y1, D_Coord x2, D_Coord y2) D_FUNCPOSTFIT;

/** @brief 在一个控件上画一个矩形*/
D_Result		d_vis_draw_rect (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief 在一个控件上画一个填充矩形*/
D_Result		d_vis_draw_fill_rect (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;

#ifdef D_GUI_SUPPORT_ELLIPSE
/** @brief 在一个控件上画一个椭圆*/
D_Result		d_vis_draw_ellipse (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;
#endif

#ifdef D_GUI_SUPPORT_FILL_ELLIPSE
/** @brief 在一个控件上画一个填充椭圆*/
D_Result		d_vis_draw_fill_ellipse (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;
#endif

#ifdef D_GUI_SUPPORT_ARC
/** @brief 在一个控件上画一个弧*/
D_Result		d_vis_draw_arc (D_Visual *vis, D_Rect *rect, D_S32 start, D_S32 end) D_FUNCPOSTFIT;

/** @brief 在一个控件上画一个弧，指定厚度   @qiny 2013-11-15*/
D_Result d_vis_draw_arc_ex (D_Visual *vis, D_Rect *rect, D_S32 start, D_S32 end, D_Coord border) D_FUNCPOSTFIT;

/* @brief 在一个控件上画一个圆角矩形@qiny 2013-11-15
* @param border 边框厚度
* @param rad 圆角半径
*/
D_Result d_vis_draw_roundrect(D_Visual *vis, D_Rect *rect, D_Coord rad, D_Coord border)D_FUNCPOSTFIT;

/* @brief 在一个控件上画一个圆角矩形, 可选择圆角
如果type = 0 , 为直角矩形。@qiny 2013-11-15
* @param border 边框厚度
* @param r 圆角半径
*/
D_Result d_vis_draw_roundrect_sel(D_Visual *vis, D_Rect *rect, D_Coord rad, D_Coord border, D_RoundRectType type)D_FUNCPOSTFIT;

#endif

#ifdef D_GUI_SUPPORT_FILL_ARC
/** @brief 在一个控件上画一个填充弧*/
D_Result		d_vis_draw_fill_arc (D_Visual *vis, D_Rect *rect, D_S32 start, D_S32 end) D_FUNCPOSTFIT;
#endif

#ifdef D_GUI_SUPPORT_POLY
/** @brief 在一个控件上画一个多边形*/
D_Result		d_vis_draw_poly (D_Visual *vis, D_Point *pts, D_U8 cnt) D_FUNCPOSTFIT;
#endif

#ifdef D_GUI_SUPPORT_FILL_POLY
/** @brief 在一个控件上画一个填充多边形*/
D_Result		d_vis_draw_fill_poly (D_Visual *vis, D_Point *pts, D_U8 cnt) D_FUNCPOSTFIT;
#endif

/** @brief 在一个控件上画一个填充扇形*/
D_Result		d_vis_draw_fill_roundarc(D_Visual *vis, D_Rect *rect,D_Coord r, D_RoundRectType type)D_FUNCPOSTFIT;

/* @brief 在一个控件上画一个填充圆角矩形, 4个角都是圆角*/
D_Result		d_vis_draw_fill_roundrect(D_Visual *vis, D_Rect *rect, D_Coord r)D_FUNCPOSTFIT;

/* @brief 在一个控件上画一个填充圆角矩形, 可选择圆角
如果type = 0 , 为填充直角矩形。@qiny 2013-11-15*/
D_Result d_vis_draw_fill_roundrect_sel(D_Visual *vis, D_Rect *rect, D_Coord r, D_RoundRectType type)D_FUNCPOSTFIT;

/** @brief 在一个控件上画一个字符串*/
D_Result		d_vis_draw_text (D_Visual *vis, D_Coord x, D_Coord y, D_Char *txt, D_Size cnt) D_FUNCPOSTFIT;

/** @brief 在一个控件上的一个范围内画一个字符串*/
D_Result		d_vis_draw_text_in_range (D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Char **text, D_Size cnt, D_Bool draw_last) D_FUNCPOSTFIT;

/** @brief 在一个控件上画一个图像*/
D_Result		d_vis_draw_image (D_Visual *vis, D_Rect *dr, D_Image *img, D_Rect *sr) D_FUNCPOSTFIT;

/** @brief 在一个控件带屏蔽地上画一个图像*/
D_Result		d_vis_draw_image_mask (D_Visual *vis, D_Rect *dr, D_Image *img, D_Rect *sr) D_FUNCPOSTFIT;

/** @brief 显示一个控件*/
D_Result		d_vis_show (D_Visual *vis, D_Bool show) D_FUNCPOSTFIT;

/** @brief 设定一个控件的可用状态*/
D_Result		d_vis_enable (D_Visual *vis, D_Bool en) D_FUNCPOSTFIT;

/** @brief 设定一个控件的可聚焦状态*/
D_Result		d_vis_set_focusable (D_Visual *vis, D_Bool f) D_FUNCPOSTFIT;

/** @brief 取得一个控件的可聚焦状态,add by 覃宜2011-4-26*/
D_Bool d_vis_get_focusable (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief  更新重新绘制一个控件*/
D_Result		d_vis_update (D_Visual *vis, D_Rect *rect) D_FUNCPOSTFIT;

/** @brief 控件重新绘制(GUI模块调用)*/
D_Result		d_vis_redraw (void) D_FUNCPOSTFIT;

/** @brief 处理事件(GUI模块调用)*/
D_Result		d_vis_solve_event (D_Event *evt) D_FUNCPOSTFIT;

/** @brief 清除销毁的控件(GUI模块调用)*/
D_Result		d_vis_clear_destroy (void) D_FUNCPOSTFIT;

/** @brief 取为上一个可聚焦控件*/
D_Visual*	d_vis_prev_focus (D_Visual *vis)  D_FUNCPOSTFIT;

/** @brief 取下一个可聚焦控件*/
D_Visual*	d_vis_next_focus (D_Visual *vis)  D_FUNCPOSTFIT;

/** @brief 注册一个事件*/
D_Result	d_vis_subscribe_evt (D_Visual *vis, D_U32 mask, D_Handle handle) D_FUNCPOSTFIT;

/** @brief 对一个控件的所有注册事件进行反注册*/
D_Result	d_vis_unsubscribe_evt (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 反注册一个事件*/
D_Result	d_vis_unsubscribe_one_evt (D_Visual *vis, D_U32 mask, D_Handle handle) D_FUNCPOSTFIT;

/** @brief 取得一个控件在屏幕上的坐标*/
D_Result d_vis_get_pos (D_Visual *vis, D_Coord *x, D_Coord *y) D_FUNCPOSTFIT;

/* add by liux */
D_Result d_vis_draw_text_ex (D_Visual *vis, D_Coord x, D_Coord y, D_Char *txt, D_Size cnt, D_FontAttrType type) D_FUNCPOSTFIT;

/*add by qiny 2012-09-05*/
D_Result d_vis_draw_text_middle (D_Visual *vis, D_Coord x, D_Coord y, D_Char *text, D_Size cnt, D_Coord lineH) D_FUNCPOSTFIT;
/*add by qiny 2012-09-05*/
D_Result d_vis_draw_text_middle_ex (D_Visual *vis, D_Coord x, D_Coord y, D_Char *text, D_Size cnt, D_FontAttrType type, D_Coord lineH) D_FUNCPOSTFIT;

D_Result d_vis_draw_text_in_range_ex (D_Visual *vis, D_Coord x, D_Coord y, D_Coord w, D_Char **text, D_Size cnt, D_Bool draw_last, D_FontAttrType type) D_FUNCPOSTFIT;

/** @brief vis内坐标转换成屏幕坐标 */
D_Result d_vis_pos_v2s(D_Visual *vis, D_Coord *x, D_Coord *y) D_FUNCPOSTFIT;

/** @brief 屏幕坐标转换成vis坐标 */
D_Result d_vis_pos_s2v(D_Visual *vis, D_Coord *x, D_Coord *y) D_FUNCPOSTFIT;

/** @brief 设置控件的类型*/
D_Result d_vis_set_type (D_Visual *vis, D_U8 type) D_FUNCPOSTFIT;

/** @brief 设置控件的显示属性*/
D_Result d_vis_set_attribute(D_Visual *vis, D_Ptr pattr)D_FUNCPOSTFIT;

/** @brief 设置控件的是否处理重绘事件
特殊用法，使之能与area控件类似，可以处理
D_EVT_DRAW, 但先执行控件本身的绘制函数，
再交由用户处理D_EVT_DRAW事件*/
D_Result
d_vis_set_solve_draw_evt(D_Visual *vis, D_Bool solve)D_FUNCPOSTFIT;


D_Result d_vis_solve_mouse_event(D_MousePollData *mpd) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
