/** @file
* @brief 控件模块
* @author 龚克
* @date 2005-8-10  龚克: 建立文件
  @date 2005-12-29 刘勋: 修改文件  
  加入新窗口、按钮、选择框、单/复选框和滚动/滑动条类型
*/

#ifndef _D_CONTROL_H_
#define _D_CONTROL_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dVisual.h"
#include "dFrame.h"

/** @brief 控件创建回调结构 */
typedef struct
{
	D_Visual *vis;
	D_ControlType type;
}D_ControlCallbackParam;

/** @brief 控件绘图回调结构 */
typedef struct
{
	D_Visual *vis;
	D_ControlType type;
	D_Rect *r;
}D_ControlCallbackDrawParam;

/** @brief 创建一个新的控件
* @param type 控件类型
* @return 成功返回控件指针,失败返回 NULL
*/
D_Visual*	d_control_new (D_ControlType type) D_FUNCPOSTFIT;

/** @brief 获得控件类型
* @param[in] vis  控件句柄
* @return 成功返回控件类型,失败返回D_ERR
*/
D_ControlType d_control_get_class(D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 设定一个标签的文本
* @param vis	标签控件
* @param text	标签文本
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_label_set_text (D_Visual *vis, D_Char *text) D_FUNCPOSTFIT;

/** @brief 设定一个标签控件类型
* @param vis	标签控件
* @param type	标签类型
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result
d_label_set_type (D_Visual *vis, D_U8 type) D_FUNCPOSTFIT;

/** @brief 取得一个标签的文本总页数
* @param vis	标签控件
* @return	总页数
*/
D_U16
d_label_get_page_cnt(D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 设定一个标签的文本当前页
* @param vis	标签控件
* @param page_no 	当前页号(从0开始)
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result
d_label_set_page(D_Visual *vis, D_U16 page_no) D_FUNCPOSTFIT;


/** @brief 将单选框加入单选框组中
* @param vis	单选框控件
* @param grp	单选框组
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_radio_box_add_to_group (D_Visual *vis, D_Visual *grp) D_FUNCPOSTFIT;

/** @brief 设定选择框内容
* @param vis	选择框控件
* @param content	选择框显示字符串数组
* @param cnt			选择框选购数目
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_select_box_set_content (D_Visual *vis, D_Char **content, D_U16 cnt) D_FUNCPOSTFIT;

/** @brief 设定选择框对应值
* @param vis	选择框控件
* @param val	选择框值
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_select_box_set_val (D_Visual *vis, D_U16 val) D_FUNCPOSTFIT;

/** @brief 取选择框对应值
* @param vis	选择框控件
* @return	成功返回选择值,失败返回-1
*/
D_S16			d_select_box_get_val (D_Visual *vis) D_FUNCPOSTFIT;


/** @brief 设定进度条前景色
此函数用于改变进度条的显示样式。
* @param vis	进度条控件
* @param colorid	前景色ID，(-1时使用原有前景色)
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result
d_progress_bar_set_front_colour(D_Visual *vis, D_U16 colorid) D_FUNCPOSTFIT;

/** @brief 设定进度条前景图
此函数用于改变进度条的显示样式。
* @param vis	进度条控件
* @param imgid	前景图ID，(-1时使用原有前景图)
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result
d_progress_bar_set_front_img(D_Visual *vis, D_U16 imgid) D_FUNCPOSTFIT;

/** @brief 设定进度条进度最大值
* @param vis	进度条控件
* @param cnt	进度条进度值最大值
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result d_progress_bar_set_cnt(D_Visual *vis, D_U16 cnt) D_FUNCPOSTFIT;


/** @brief 设定进度条进度
* @param vis	进度条控件
* @param val	进度条进度值
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_progress_bar_set_val (D_Visual *vis, D_U16 val) D_FUNCPOSTFIT;

/** @brief 设定滚动条数值范围
* @param vis	滚动条控件
* @param max	滚动条最大数值
* @param page	一页的数值
* @param val	当前值
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_scroll_bar_set_range (D_Visual *vis, D_U16 max, D_U16 page, D_U16 step, D_U16 val) D_FUNCPOSTFIT;

/** @brief 设定滚动条数值
* @param vis	滚动条控件
* @param val	滚动条数值
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_scroll_bar_set_val (D_Visual *vis, D_U16 val) D_FUNCPOSTFIT;


/** @brief 移动输入框输入光标位置
* @param vis	输入框控件
* @param forwd	向前标志
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_input_box_move_cursor(D_Visual *vis, D_Bool forwd)D_FUNCPOSTFIT;

/**@brief 在输入框光标处添加(或替换)文本
* @param vis	输入框控件
* @param chr	插入(或替换)的字符串起始指针
* @param addlen	插入(或替换)的字符串长度
* @param cover  替换标志
* @return 成功返回D_OK，失败返回D_ERR
*/
D_Result d_input_box_add_char(D_Visual *vis, D_Char *chr, D_Size addlen, D_Bool cover)D_FUNCPOSTFIT;

/**@brief 在字符输入框光标处删除一个字符
* @param vis	输入框控件
* @param forwd	向前标志
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_input_box_delete_char(D_Visual *vis, D_Bool forwd)D_FUNCPOSTFIT;

/** @brief 设定输入框输入字符的长度
* @param vis	输入框控件
* @param len	输入字符串长度
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_input_box_set_len (D_Visual *vis, D_U16 len) D_FUNCPOSTFIT;

/** @brief 设定输入框文本缓冲区
* @param vis	输入框控件
* @param buf	输入框缓冲区
* @param len	输入字符长度
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_input_box_set_buf (D_Visual *vis, D_Char *buf, D_Size len) D_FUNCPOSTFIT;

/** @brief 设定输入框显示文本
* @param vis	输入框控件
* @param text	显示文本
* @param len	显示文本长度长度
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_input_box_set_text (D_Visual *vis, D_Char *text, D_Size len) D_FUNCPOSTFIT;

/** @brief 取得输入框显示文本
* @param vis	输入框控件
* @return	成功返回输入框文本指针,失败返回NULL
*/
D_Char*		d_input_box_get_text (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 取得输入框输入数字
* @param vis	输入框控件
* @return	成功返回输入数字,失败返回-1
*/
D_S32			d_input_box_get_num (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 取得格式输入框里各段的值
* @param vis	输入框控件
* @param segment_val	保存各段的值
* @param segment_cnt	段的数量值
* @return	成功返回输入数字,失败返回-1
*/
D_Result d_input_box_get_segment_val (D_Visual *vis, D_U32 *segment_val, D_U32 segment_cnt) D_FUNCPOSTFIT;


/** @brief 设定列表的行列
* @param vis	列表控件
* @param title	是否含有标题行
* @param max	最大行数
* @param row	列表的显示行数
* @param col	列表列数
* @param rh		列表每行高度
* @param cw		列表每一列的宽度
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result d_list_set_row_col (D_Visual *vis, D_U16 max, D_U16 row, D_U16 col, D_Coord rh, D_Coord *cw, D_U16 rowSpace, D_U16 colSpace, D_Ptr pAttribute) D_FUNCPOSTFIT;

/** @brief 重新设定列表框行最大值
* @param vis	列表控件
* @param max	最大行数
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_list_set_max_row (D_Visual *vis, D_U16 max) D_FUNCPOSTFIT;

/** @brief 清空列表数据
* @param vis	列表控件
* @param clear_title	是否清空标题栏
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_list_clear (D_Visual *vis, D_Bool clear_title) D_FUNCPOSTFIT;

/** @brief 取得列表指定行控件
* @param list	列表控件
* @param row	列表行号(第一行行号:0)
*/
D_Visual* d_list_get_row (D_Visual *list, D_U16 row) D_FUNCPOSTFIT;

/** @brief 取得列表指定单元格控件
* @param list	列表控件
* @param row	列表行号(第一行行号:0)
* @param col	列表列号(第一列列号:0)
*/
D_Visual* d_list_get_cell (D_Visual *list, D_U16 row, D_U16 col) D_FUNCPOSTFIT;

/** @brief 设定列表表格的文字
* @param vis	列表控件
* @param row	列表行号(第一行行号:0)
* @param col	列表列号(第一列列号:0)
* @param text	设定文字
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_list_set_text (D_Visual *vis, D_U16 row, D_U16 col, D_Char *text) D_FUNCPOSTFIT;

/** @brief 设定列表表格的图像
* @param vis	列表控件
* @param row	列表行号(第一行行号:0)
* @param col	列表列号(第一列列号:0)
* @param img	设定图像
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_list_set_image (D_Visual *vis, D_U16 row, D_U16 col, D_Image *img) D_FUNCPOSTFIT;

/** @brief 设定列表框中一行得到焦点
* @param vis	列表控件
* @param row	列表行号(第一行行号:0)
* @param col	列表列号(第一列列号:0)
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_list_set_focus (D_Visual *vis, D_U16 row, D_U16 col) D_FUNCPOSTFIT;

/** @brief 设定一个列表对应的滚动条
* @param vis	列表控件
* @param sbar	滚动条控件
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result	d_list_set_scroll_bar (D_Visual *vis, D_Visual *sbar) D_FUNCPOSTFIT;

/** @brief 取得列表当前的起始行ID*/
D_ID			d_list_get_first_line_id (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 取得列表中焦点行的ID*/
D_ID d_list_get_focus (D_Visual *vis, D_U16 *row, D_U16 *col) D_FUNCPOSTFIT;

/** @brief  取得列表的显示行数*/
D_U32			d_list_get_row_cnt (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 指定列表焦点上移*/
D_Result d_list_option_up (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 指定列表焦点下移*/
D_Result d_list_option_down (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 指定列表焦点上翻页*/
D_Result d_list_option_page_up (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 指定列表焦点下翻页*/
D_Result d_list_option_page_down (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief 设定列表表格无效
* @param vis	列表控件
* @param  type 操作类型，行还是单元格
* @param row	列表行号(第一行行号:0)
* @param col	列表列号(第一列列号:0)
* @param img	设定图像
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result
d_list_set_disable(D_Visual *vis, D_ControlType type, D_U16 row, D_U16 col, D_Bool dis) D_FUNCPOSTFIT;


/** @brief 设定列表表格是否显示
* @param vis	列表控件
* @param  type 操作类型，行还是单元格
* @param row	列表行号(第一行行号:0)
* @param col	列表列号(第一列列号:0)
* @param img	设定图像
* @return	成功返回D_OK,失败返回D_ERR
*/
D_Result
d_list_set_show(D_Visual *vis, D_ControlType type, D_U16 row, D_U16 col, D_Bool show) D_FUNCPOSTFIT;


/** @brief 设定列表框中指定行显示属性
* @param vis	列表控件
* @param pcheck	指定行显示属性
* @return	成功返回D_OK,失败返回D_ERR
@qiny 2013-10-30*/
D_Result
d_list_set_check_attr (D_Visual *vis, D_RowCtrlAttribute *pcheck) D_FUNCPOSTFIT;

/** @brief 指定列表框中一行
* @param vis	列表控件
* @param row	列表行号(第一行行号:0) (-1时清除)
* @param col	列表列号(第一列列号:0) (-1时清除)
* @return	成功返回D_OK,失败返回D_ERR
@qiny 2013-10-30*/
D_Result
d_list_set_check (D_Visual *vis, D_U16 row, D_U16 col) D_FUNCPOSTFIT;

/** @brief 指定列表框是否是移动状态
* @param vis	列表控件
* @param move	是否是移动状态
* @param pLinkIds	关联的id列表
* @return	成功返回D_OK,失败返回D_ERR
@qiny 2013-10-30*/
D_Result
d_list_set_remove (D_Visual *vis, D_Bool move, D_ListLinkIds *pLinkIds) D_FUNCPOSTFIT;

/** @brief 设置一个图像
* @param vis  图像控键
* @param image	图像
* @return 成功返回D_OK, 失败返回D_ERR
*/

D_Result  d_image_box_set_image (D_Visual *vis, D_Image *img) D_FUNCPOSTFIT;

/** @brief 弹出列表框
* @param select_box 激活的选择框
* @return 成功返回控件指针,失败返回 NULL
*/
D_Result d_select_box_show_list(D_Visual	*select_box) D_FUNCPOSTFIT;

/** @brief 销毁列表框对应的下拉窗口
* @param pop_win 列表框
* @return 成功返回控件指针,失败返回 NULL
* @control.c 中调用
*/
D_Result d_select_box_hide_list(D_Visual	*select) D_FUNCPOSTFIT;

/** @brief 设置列表移动类型
* @param select 列表框
* @param Bool 是否设置移动
* @return 成功返回控件指针,失败返回 NULL
*/
D_Result d_list_set_move_type(D_Visual	*select, D_Bool Bool) D_FUNCPOSTFIT;


/*设置group里的焦点是否可以循环切换*/
D_Result d_group_set_focus_loop(D_Visual *vis, D_Bool loop) D_FUNCPOSTFIT;

/*设定文本*/
D_Result
d_button_set_text (D_Visual *vis, D_Char *text) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
