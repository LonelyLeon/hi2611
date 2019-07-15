/** @file
* @brief 窗体管理模块
*
*	一个窗体由多个控件组成,窗体通过一个数据结构加载,窗体内的
*	控件可以通过预先设定的ID进行索引
* @author 覃宜
* @date 2013-05-08 覃宜: 建立文件
*/
#ifndef _D_FRAME_H_
#define _D_FRAME_H_

#include "dAV.h"
#include "dVisual.h"

#ifdef  __cplusplus
extern "C"
{
#endif

typedef D_U16  	D_ColourID;
typedef D_U16  	D_ImageID;
typedef D_U16  	D_TextID;
typedef	D_U16   	D_Align;

/** @brief 字体类型定义*/
#define D_FONT_DOT_MATRIX 0	/**< 点阵*/
#define D_FONT_TRUE_TYPE 1		/**< */

/** @brief 单行多行定义*/
#define D_LINE_SINGLE 0
#define D_LINE_MULTI 1

/** @brief 控件状态类型定义*/
#define D_CTR_STATUS_NORMAL		0	/**< 平常状态*/
#define D_CTR_STATUS_FOCUSED		1	/**< 焦点状态*/
#define D_CTR_STATUS_DISABLE		2	/**< 失效状态*/
#define D_CTR_STATUS_MAX			3	/**< 其它*/	


/** @brief 对齐方式*/
#define D_ALIGN_LEFT		1	/**< 水平左对齐*/
#define D_ALIGN_RIGHT		2	/**< 水平右对齐*/
#define D_ALIGN_CENTER		4	/**< 水平居中对齐*/
#define D_ALIGN_TOP			8	/**< 垂直上对齐*/
#define D_ALIGN_BOTTOM		16	/**< 垂直下对齐*/
#define D_ALIGN_MIDDLE		32	/**< 垂直居中对齐*/
#define D_ALIGN_WHOLE_CENTER 64	/**< 整体水平居中，多行时行之间左对齐*/

/** @brief 垂直水平方向定义*/
#define D_DIR_HORIZONTAL	0	/**< 水平方向*/
#define D_DIR_VERTICAL		1	/**< 垂直方向*/


/** @brief 几种拼图类型，图片id排列*/
#define D_COMB_IMG_HOR_LEFT		0
#define D_COMB_IMG_HOR_CENTER	1
#define D_COMB_IMG_HOR_RIGHT		2

#define D_COMB_IMG_VER_TOP		0
#define D_COMB_IMG_VER_MIDDLE		1
#define D_COMB_IMG_VER_BOTTOM	2

#define D_COMB_IMG_MATRIX_TOP_LEFT			0
#define D_COMB_IMG_MATRIX_TOP_CENTER		1
#define D_COMB_IMG_MATRIX_TOP_RIGHT			2
#define D_COMB_IMG_MATRIX_MIDDLE_LEFT		3
#define D_COMB_IMG_MATRIX_MIDDLE_CENTER		4
#define D_COMB_IMG_MATRIX_MIDDLE_RIGHT		5
#define D_COMB_IMG_MATRIX_BOTTOM_LEFT		6
#define D_COMB_IMG_MATRIX_BOTTOM_CENTER		7
#define D_COMB_IMG_MATRIX_BOTTOM_RIGHT		8


#define D_IMAGE_ID_RES_TYPE_INVALID			0
#define D_IMAGE_ID_RES_TYPE_SINGLE_IMAGE		1
#define D_IMAGE_ID_RES_TYPE_COMB_IMAGES		2
#define D_IMAGE_ID_RES_TYPE_FREE_SHAPE		3


/** @brief 颜色是否有效 */
#define D_IS_VALID_COLOR(_a_)	(_a_ != ((D_ColourID)(-1)))

/** @brief 图片是否有效 */
#define D_IS_VALID_IMAGE(_a_)	(_a_ != ((D_ImageID)(-1)))

/** @brief 是否是组合图*/
#define D_IS_COMB_IMAGES(_t_)	(_t_ == D_IMAGE_ID_RES_TYPE_COMB_IMAGES)

/** @brief 是否是回调函数*/
#define D_IS_DRAW_CALLBACK(_t_)	(_t_ == D_IMAGE_ID_RES_TYPE_FREE_SHAPE)




/** @brief 控件类型定义*/
typedef enum {
	D_CTRL_DESKTOP = 0,		/**< 背景桌面*/
	D_CTRL_WINDOW,		/**< 窗口*/
	D_CTRL_LABEL,			/**< 文本*/
	D_CTRL_BUTTON,		/**< 按钮*/
	D_CTRL_SELECT,/**< 选择框*/
	D_CTRL_CHECK,	/**< 多选框*/
	D_CTRL_RADIO,	/**< 单选框*/
	D_CTRL_INPUT,	/**< 文本输入框*/
	D_CTRL_LIST,			/**< 列表*/
	D_CTRL_LIST_ROW,	/**< 列表行*/
	D_CTRL_LIST_CELL,	/**< 列表表格*/
	D_CTRL_PROGRESS,	/**< 进度条*/
	D_CTRL_SCROLL,		/**< 滚动条*/
	D_CTRL_GROUP,			/**< 组容器*/
	D_CTRL_DRAW_AREA,	/**< 绘图区*/
	D_CTRL_IMAGE,			/**< 图像控件*/
} D_ControlType;


/** @brief label框类型*/	
typedef enum {
 	D_LABEL_TYPE_NORMAL		 	= 0,		/*平常标签*/
 	D_LABEL_TYPE_VIDEO_WIN_MSG	= 1,		/*小视频消息提示标签*/
 	D_LABEL_TYPE_PAGE_SWITCH	= 2,		/*按页显示标签*/
 	D_LABEL_TYPE_OTHER					/**< 其它*/
}D_LabelType;


/** @brief文本滚动方式*/
typedef enum {
	D_SCROLL_TYPE_NO					= 0,		/**< 不滚流动*/
	D_SCROLL_TYPE_R2L_PIXSEL			= 1,		/**< 右向左像素滚动*/
	D_SCROLL_TYPE_L2R_PIXSEL			= 2,		/**< 左向右像素滚动*/
	D_SCROLL_TYPE_R2L_CHAR			= 3,		/**< 右向左字符滚动*/
	D_SCROLL_TYPE_L2R_CHAR			= 4,		/**< 左向右字符滚动*/
	D_SCROLL_TYPE_DOWN2UP_PIXSEL	= 5,		/**< 下向上像素滚动*/
	D_SCROLL_TYPE_UP2DOWN_PIXSEL	= 6,		/**< 上向下像素滚动*/
	D_SCROLL_TYPE_LINE				= 7,		/**< 行滚动(向上)*/
	D_SCROLL_TYPE_PAGE				= 8,		/**< 页滚动(向上)*/
	D_SCROLL_TYPE_OTHER						/**< 其它*/	
}D_TextScrollType;


/** @brief 输入框类型*/	
typedef enum {
	D_INPUTBOX_TYPE_NUMBER			= 0,		/**< 数字输入框*/
	D_INPUTBOX_TYPE_CHAR				= 1,		/**< 英文字母(包括数字字符)输入框*/
	D_INPUTBOX_TYPE_TEXT				= 2,		/**< 任意字符输入框*/
	D_INPUTBOX_TYPE_PASSWD_NUMBER	= 3,		/**< 数字密码输入框*/
	D_INPUTBOX_TYPE_PASSWD_CHAR	= 4,		/**< 英文字母(包括数字字符)输入框*/
	D_INPUTBOX_TYPE_FORMAT			= 5,		/**< 格式化输入(如时间、日期、IP等)*/
	D_INPUTBOX_TYPE_OTHER					/**< 其它*/	
}D_InputBoxType;


/** @brief 列表聚焦类型*/	
typedef enum {
	D_LIST_FOCUS_TYPE_NO			= 0,		/**<不聚焦*/
	D_LIST_FOCUS_TYPE_ROW		= 1,		/**< 行聚焦*/
	D_LIST_FOCUS_TYPE_CELL		= 2,		/**< 单元格聚焦*/
	D_LIST_FOCUS_TYPE_ALL			= 3,		/**< 整个列表聚焦*/
	D_LIST_FOCUS_TYPE_OTHER				/**< 其它*/
}D_ListFocusType;


/** @brief image框类型*/	
typedef enum {
 	D_IMAGEBOX_TYPE_NORMAL		 	= 0,		/*平常图片控件*/
 	D_IMAGEBOX_TYPE_IMAGE_USE_ALIGN	= 0x20,	/*画图片时使用对齐方式*/
 	D_LABELBOX_TYPE_OTHER					/**< 其它*/
}D_ImageBoxType;


/** @brief 光标类型*/	
typedef enum {
	D_CURSOR_TYPE_NO			= 0,		/**< 无光标*/
	D_CURSOR_TYPE_UNDERLINE	= 1,		/**< 下横线光标*/
	D_CURSOR_TYPE_VERTICAL	= 2,		/**< 竖线光标*/
	D_CURSOR_TYPE_OTHER				/**< 其它*/
}D_CursorType;

/** @brief 组合图类型*/	
typedef enum {
	D_IMG_COMB_TYPE_HOR		= 0,		/**< 水平组合*/
	D_IMG_COMB_TYPE_VER		= 1,		/**< 垂直组合*/
	D_IMG_COMB_TYPE_MATRIX	= 2,		/**< 九宫格矩阵组合*/
	D_IMG_COMB_TYPE_OTHER			/**< 其它*/ 
}D_ImgCombType;


/** @brief 组合图结构*/
typedef struct
{
	D_U16	combtype;
	D_U16	imgids[9];	/*最多9张，但水平垂直的只用到3张*/
}D_ImageCombInfo;	
	

/** @brief 格式描述*/
typedef struct
{
	D_ColourID	frontColourId;		/**< 前景颜色ID*/
	D_U8		fontType;			/**< 字体*/
	D_U8		fontSize;			/**< 字体大小*/
	D_U8		multiLine;			/**< 单行多行*/
	D_Coord		hOffset;				/**< 水平偏移*/
	D_Coord		vOffset;				/**< 垂直偏移*/	
	D_Align		align;				/**< 对齐方式*/	
	D_TextScrollType	scrollType;		/**< 滚动类型*/
	D_U16		scrollVelocity;		/**< 滚动速度，时间(单位ms)*/
	D_U16		scrollGranularity;	/**< 滚动粒度(像素/ 字符数/ 行数)*/
	D_U32		reserved;
	D_U32		reserved1;
}D_Format;


/** @brief 属性描述*/
typedef struct{
	D_ColourID	bgColourId;		/**< 背景颜色ID*/
	D_ImageID	bgImageId;		/**< 背景图片ID*/
	D_TextID		textId;			/**< 文本ID*/
	D_Format	*pFormat;		/**< 显示格式*/
}D_CtrlAttribute;



/** @brief 一般控件描述*/
typedef struct {
	D_CtrlAttribute *ctrlAttributeList[D_CTR_STATUS_MAX];/**< 控件显示属性表*/
	D_U32		transparence;						/*控件透明标志*/
} D_FrameCtrlDescr;	



/** @brief 选择框描述*/
typedef struct {
	D_CtrlAttribute *ctrlAttributeList[D_CTR_STATUS_MAX];/**< 控件显示属性表*/
	D_U32		transparence;			/*控件透明标志*/
	D_U16			 	cnt;				/**< 选项总数*/
	D_TextID const D_FAR	*text_id_list;	/**<各 选项显示文本信息*/
} D_FrameSelectDescr;	


/** @brief 输入框描述*/
typedef struct {
	D_CtrlAttribute 	*ctrlAttributeList[D_CTR_STATUS_MAX];/**< 控件显示属性表*/
	D_U32		transparence;						/*控件透明标志*/
	D_InputBoxType	type;	/**< 输入框类型*/	
	D_U16			cnt;			/**< 可输入字符总数*/
	D_Char	  		*text;		/**< 输入框文本缓冲区*/
	D_CursorType		cursorType;	/**< 光标类型*/
	D_Char	  		chr1;		/**< 密码提示字符*/
	D_Char	  		chr2;		/**< 密码代替字符*/
} D_FrameInputBoxDescr;	


/** @brief 进度条描述*/
typedef struct {
	D_CtrlAttribute 	*ctrlAttributeList[D_CTR_STATUS_MAX];/**< 控件显示属性表*/
	D_U32			transparence;						/*控件透明标志*/
	D_U16			max;		/**< 总步数*/
	D_U16			step;		/**< 步进*/
	D_U8			HV_flag;		/**< 水平垂直方向标识*/
	D_ColourID		frontColourId;	/**< 前景颜色ID*/
	D_ImageID		frontImageId;	/**< 前景图片ID*/
} D_FrameProgressBarDescr;


/** @brief 列表行属性*/
typedef struct {
	D_CtrlAttribute *pRowAttr;          /**< 行属性*/	
	D_CtrlAttribute **pCellAttrList;     /**< 行里单元格属性表*/
}D_RowCtrlAttribute;

/** @brief 列表描述*/
typedef struct {
	D_CtrlAttribute 	*ctrlAttributeList[D_CTR_STATUS_MAX];/**< 控件显示属性表*/
	D_U32			transparence;						/*控件透明标志*/
	D_U16			max;			/**< 总行数*/
	D_U16			pal_row;		/**< 显示一页行数*/
	D_U16			ntsc_row;		/**< 显示一页行数*/
	D_U16			col;				/**< 列数*/
	D_Coord			rh;				/**< 行高*/
	D_Coord	const D_FAR	*cw;		/**< 列宽数组*/
	D_U16			rowSpace;		/**< 行间距*/
	D_U16			colSpace;		/**< 列间距*/
	D_ListFocusType	focusType;		/**< 聚焦类型(无/ 行/ 单元格  聚集)*/
	D_Ptr	 	cellCtrDescr;		/**< 各单元格属性表*/
	D_Ptr	 	rowCtrDescr;		/**< 各行属性表*/	
} D_FrameListDescr;




/** @brief 滚动条描述*/
typedef struct {
	D_ImageID	startImageId;	/**< 起始图id*/
	D_ImageID	endImageId;	/**< 结尾图id*/
	D_ImageID	middleImageId;	/**< 中间图id*/
	D_ImageID	vernierImageId;	/**< 游标图id*/
}D_ScrollBarImage;

typedef struct {
	D_CtrlAttribute 	*ctrlAttributeList[D_CTR_STATUS_MAX];/**< 控件显示属性表*/	
	D_U32			transparence;						/*控件透明标志*/
	D_U16			max;			/**< 总步数*/
	D_U16			step;			/**< 步进*/
	D_U8			HV_flag;			/**< 水平垂直方向标识*/
	D_ScrollBarImage	image;			/**< 滚动条图片 资源*/	
} D_FrameScrollBarDescr;

/** @brief 窗体内部控件描述*/
typedef struct {
	D_ControlType	type;			/**< 控件类型*/
	D_ID			parent_id;		/**< 父控件ID*/
	D_Coord		 	x;				/**< x坐标*/
	D_Coord		 	paly;			/**< PAL制下的y坐标*/
	D_Coord		 	ntscy;			/**< NTSC制下的y坐标*/
	D_Coord		 	w;				/**< 控件宽度*/
	D_Coord		 	palh;			/**< PAL制下的控件高度*/
	D_Coord		 	ntsch;			/**< NTSC制下的控件高度*/
	//D_Ptr			ptr;				/**< 控件数据指针*/
	D_ID			param_id;		/**< 参数控件ID*/
	D_FrameCtrlDescr	*pCtrlDescr;		/**< 控件其它属性描述指针*/
} D_FrameControlDescr;

/** @brief 窗体数据*/
typedef struct _D_Frame D_Frame;
struct _D_Frame {
	D_Visual*	*ctrls;			/**< 存放窗体内控件数组指针*/
	D_FrameControlDescr	const D_FAR *ctrl_descrs;		/**< 控件描述*/
	D_Result	(*init) (D_Frame *frm); /**< 窗体初始化*/
	D_Bool		 loaded;		/**< 窗体是否已经加载*/
};

/** @brief 检查一个窗体是否已经加载*/
#define d_frame_is_loaded(_f)	((_f)->loaded)

/** @brief 加载一个窗体
* @param frm	要加载的窗体数据结构指针
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result	d_frame_load (D_Frame *frm) D_FUNCPOSTFIT;

/** @brief 卸载一个窗体
* @param frm	要卸载的窗体数据结构指针
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result	d_frame_unload (D_Frame *frm) D_FUNCPOSTFIT;

/** @brief 返回窗体内一个控件的指针
* @param frm	窗体数据结构指针
* @param id		控件ID
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Visual*	d_frame_get_control (D_Frame *frm, D_ID id) D_FUNCPOSTFIT;

/** @brief 返回窗体内一个控件的ID
* @param frm	窗体数据结构指针
* @param vis	控件
* @return 成功返回控件ID, 失败返回-1
*/
D_ID d_frame_get_control_id (D_Frame *frm, D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 重新设置窗体内的全部控件的位置大小
* @param frm 窗体数据结构指针
* @return 成功返回D_OK, 失败返回D_ERR
*/
D_Result	d_frame_reload_size (D_Frame *frm) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

