/** @file
* @brief �ؼ�ģ��
* @author ����
* @date 2005-8-10  ����: �����ļ�
  @date 2005-12-29 ��ѫ: �޸��ļ�  
  �����´��ڡ���ť��ѡ��򡢵�/��ѡ��͹���/����������
*/

#ifndef _D_CONTROL_H_
#define _D_CONTROL_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dVisual.h"
#include "dFrame.h"

/** @brief �ؼ������ص��ṹ */
typedef struct
{
	D_Visual *vis;
	D_ControlType type;
}D_ControlCallbackParam;

/** @brief �ؼ���ͼ�ص��ṹ */
typedef struct
{
	D_Visual *vis;
	D_ControlType type;
	D_Rect *r;
}D_ControlCallbackDrawParam;

/** @brief ����һ���µĿؼ�
* @param type �ؼ�����
* @return �ɹ����ؿؼ�ָ��,ʧ�ܷ��� NULL
*/
D_Visual*	d_control_new (D_ControlType type) D_FUNCPOSTFIT;

/** @brief ��ÿؼ�����
* @param[in] vis  �ؼ����
* @return �ɹ����ؿؼ�����,ʧ�ܷ���D_ERR
*/
D_ControlType d_control_get_class(D_Visual *vis) D_FUNCPOSTFIT;

/** @brief �趨һ����ǩ���ı�
* @param vis	��ǩ�ؼ�
* @param text	��ǩ�ı�
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_label_set_text (D_Visual *vis, D_Char *text) D_FUNCPOSTFIT;

/** @brief �趨һ����ǩ�ؼ�����
* @param vis	��ǩ�ؼ�
* @param type	��ǩ����
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_label_set_type (D_Visual *vis, D_U8 type) D_FUNCPOSTFIT;

/** @brief ȡ��һ����ǩ���ı���ҳ��
* @param vis	��ǩ�ؼ�
* @return	��ҳ��
*/
D_U16
d_label_get_page_cnt(D_Visual *vis) D_FUNCPOSTFIT;

/** @brief �趨һ����ǩ���ı���ǰҳ
* @param vis	��ǩ�ؼ�
* @param page_no 	��ǰҳ��(��0��ʼ)
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_label_set_page(D_Visual *vis, D_U16 page_no) D_FUNCPOSTFIT;


/** @brief ����ѡ����뵥ѡ������
* @param vis	��ѡ��ؼ�
* @param grp	��ѡ����
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_radio_box_add_to_group (D_Visual *vis, D_Visual *grp) D_FUNCPOSTFIT;

/** @brief �趨ѡ�������
* @param vis	ѡ���ؼ�
* @param content	ѡ�����ʾ�ַ�������
* @param cnt			ѡ���ѡ����Ŀ
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_select_box_set_content (D_Visual *vis, D_Char **content, D_U16 cnt) D_FUNCPOSTFIT;

/** @brief �趨ѡ����Ӧֵ
* @param vis	ѡ���ؼ�
* @param val	ѡ���ֵ
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_select_box_set_val (D_Visual *vis, D_U16 val) D_FUNCPOSTFIT;

/** @brief ȡѡ����Ӧֵ
* @param vis	ѡ���ؼ�
* @return	�ɹ�����ѡ��ֵ,ʧ�ܷ���-1
*/
D_S16			d_select_box_get_val (D_Visual *vis) D_FUNCPOSTFIT;


/** @brief �趨������ǰ��ɫ
�˺������ڸı����������ʾ��ʽ��
* @param vis	�������ؼ�
* @param colorid	ǰ��ɫID��(-1ʱʹ��ԭ��ǰ��ɫ)
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_progress_bar_set_front_colour(D_Visual *vis, D_U16 colorid) D_FUNCPOSTFIT;

/** @brief �趨������ǰ��ͼ
�˺������ڸı����������ʾ��ʽ��
* @param vis	�������ؼ�
* @param imgid	ǰ��ͼID��(-1ʱʹ��ԭ��ǰ��ͼ)
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_progress_bar_set_front_img(D_Visual *vis, D_U16 imgid) D_FUNCPOSTFIT;

/** @brief �趨�������������ֵ
* @param vis	�������ؼ�
* @param cnt	����������ֵ���ֵ
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_progress_bar_set_cnt(D_Visual *vis, D_U16 cnt) D_FUNCPOSTFIT;


/** @brief �趨����������
* @param vis	�������ؼ�
* @param val	����������ֵ
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_progress_bar_set_val (D_Visual *vis, D_U16 val) D_FUNCPOSTFIT;

/** @brief �趨��������ֵ��Χ
* @param vis	�������ؼ�
* @param max	�����������ֵ
* @param page	һҳ����ֵ
* @param val	��ǰֵ
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_scroll_bar_set_range (D_Visual *vis, D_U16 max, D_U16 page, D_U16 step, D_U16 val) D_FUNCPOSTFIT;

/** @brief �趨��������ֵ
* @param vis	�������ؼ�
* @param val	��������ֵ
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_scroll_bar_set_val (D_Visual *vis, D_U16 val) D_FUNCPOSTFIT;


/** @brief �ƶ������������λ��
* @param vis	�����ؼ�
* @param forwd	��ǰ��־
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_input_box_move_cursor(D_Visual *vis, D_Bool forwd)D_FUNCPOSTFIT;

/**@brief ��������괦���(���滻)�ı�
* @param vis	�����ؼ�
* @param chr	����(���滻)���ַ�����ʼָ��
* @param addlen	����(���滻)���ַ�������
* @param cover  �滻��־
* @return �ɹ�����D_OK��ʧ�ܷ���D_ERR
*/
D_Result d_input_box_add_char(D_Visual *vis, D_Char *chr, D_Size addlen, D_Bool cover)D_FUNCPOSTFIT;

/**@brief ���ַ�������괦ɾ��һ���ַ�
* @param vis	�����ؼ�
* @param forwd	��ǰ��־
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_input_box_delete_char(D_Visual *vis, D_Bool forwd)D_FUNCPOSTFIT;

/** @brief �趨����������ַ��ĳ���
* @param vis	�����ؼ�
* @param len	�����ַ�������
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_input_box_set_len (D_Visual *vis, D_U16 len) D_FUNCPOSTFIT;

/** @brief �趨������ı�������
* @param vis	�����ؼ�
* @param buf	����򻺳���
* @param len	�����ַ�����
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_input_box_set_buf (D_Visual *vis, D_Char *buf, D_Size len) D_FUNCPOSTFIT;

/** @brief �趨�������ʾ�ı�
* @param vis	�����ؼ�
* @param text	��ʾ�ı�
* @param len	��ʾ�ı����ȳ���
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_input_box_set_text (D_Visual *vis, D_Char *text, D_Size len) D_FUNCPOSTFIT;

/** @brief ȡ���������ʾ�ı�
* @param vis	�����ؼ�
* @return	�ɹ�����������ı�ָ��,ʧ�ܷ���NULL
*/
D_Char*		d_input_box_get_text (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief ȡ���������������
* @param vis	�����ؼ�
* @return	�ɹ�������������,ʧ�ܷ���-1
*/
D_S32			d_input_box_get_num (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief ȡ�ø�ʽ���������ε�ֵ
* @param vis	�����ؼ�
* @param segment_val	������ε�ֵ
* @param segment_cnt	�ε�����ֵ
* @return	�ɹ�������������,ʧ�ܷ���-1
*/
D_Result d_input_box_get_segment_val (D_Visual *vis, D_U32 *segment_val, D_U32 segment_cnt) D_FUNCPOSTFIT;


/** @brief �趨�б������
* @param vis	�б�ؼ�
* @param title	�Ƿ��б�����
* @param max	�������
* @param row	�б����ʾ����
* @param col	�б�����
* @param rh		�б�ÿ�и߶�
* @param cw		�б�ÿһ�еĿ��
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_list_set_row_col (D_Visual *vis, D_U16 max, D_U16 row, D_U16 col, D_Coord rh, D_Coord *cw, D_U16 rowSpace, D_U16 colSpace, D_Ptr pAttribute) D_FUNCPOSTFIT;

/** @brief �����趨�б�������ֵ
* @param vis	�б�ؼ�
* @param max	�������
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_list_set_max_row (D_Visual *vis, D_U16 max) D_FUNCPOSTFIT;

/** @brief ����б�����
* @param vis	�б�ؼ�
* @param clear_title	�Ƿ���ձ�����
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_list_clear (D_Visual *vis, D_Bool clear_title) D_FUNCPOSTFIT;

/** @brief ȡ���б�ָ���пؼ�
* @param list	�б�ؼ�
* @param row	�б��к�(��һ���к�:0)
*/
D_Visual* d_list_get_row (D_Visual *list, D_U16 row) D_FUNCPOSTFIT;

/** @brief ȡ���б�ָ����Ԫ��ؼ�
* @param list	�б�ؼ�
* @param row	�б��к�(��һ���к�:0)
* @param col	�б��к�(��һ���к�:0)
*/
D_Visual* d_list_get_cell (D_Visual *list, D_U16 row, D_U16 col) D_FUNCPOSTFIT;

/** @brief �趨�б��������
* @param vis	�б�ؼ�
* @param row	�б��к�(��һ���к�:0)
* @param col	�б��к�(��һ���к�:0)
* @param text	�趨����
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_list_set_text (D_Visual *vis, D_U16 row, D_U16 col, D_Char *text) D_FUNCPOSTFIT;

/** @brief �趨�б����ͼ��
* @param vis	�б�ؼ�
* @param row	�б��к�(��һ���к�:0)
* @param col	�б��к�(��һ���к�:0)
* @param img	�趨ͼ��
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_list_set_image (D_Visual *vis, D_U16 row, D_U16 col, D_Image *img) D_FUNCPOSTFIT;

/** @brief �趨�б����һ�еõ�����
* @param vis	�б�ؼ�
* @param row	�б��к�(��һ���к�:0)
* @param col	�б��к�(��һ���к�:0)
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_list_set_focus (D_Visual *vis, D_U16 row, D_U16 col) D_FUNCPOSTFIT;

/** @brief �趨һ���б��Ӧ�Ĺ�����
* @param vis	�б�ؼ�
* @param sbar	�������ؼ�
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_list_set_scroll_bar (D_Visual *vis, D_Visual *sbar) D_FUNCPOSTFIT;

/** @brief ȡ���б�ǰ����ʼ��ID*/
D_ID			d_list_get_first_line_id (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief ȡ���б��н����е�ID*/
D_ID d_list_get_focus (D_Visual *vis, D_U16 *row, D_U16 *col) D_FUNCPOSTFIT;

/** @brief  ȡ���б����ʾ����*/
D_U32			d_list_get_row_cnt (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief ָ���б�������*/
D_Result d_list_option_up (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief ָ���б�������*/
D_Result d_list_option_down (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief ָ���б����Ϸ�ҳ*/
D_Result d_list_option_page_up (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief ָ���б����·�ҳ*/
D_Result d_list_option_page_down (D_Visual *vis) D_FUNCPOSTFIT;

/** @brief �趨�б�����Ч
* @param vis	�б�ؼ�
* @param  type �������ͣ��л��ǵ�Ԫ��
* @param row	�б��к�(��һ���к�:0)
* @param col	�б��к�(��һ���к�:0)
* @param img	�趨ͼ��
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_list_set_disable(D_Visual *vis, D_ControlType type, D_U16 row, D_U16 col, D_Bool dis) D_FUNCPOSTFIT;


/** @brief �趨�б����Ƿ���ʾ
* @param vis	�б�ؼ�
* @param  type �������ͣ��л��ǵ�Ԫ��
* @param row	�б��к�(��һ���к�:0)
* @param col	�б��к�(��һ���к�:0)
* @param img	�趨ͼ��
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_list_set_show(D_Visual *vis, D_ControlType type, D_U16 row, D_U16 col, D_Bool show) D_FUNCPOSTFIT;


/** @brief �趨�б����ָ������ʾ����
* @param vis	�б�ؼ�
* @param pcheck	ָ������ʾ����
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
@qiny 2013-10-30*/
D_Result
d_list_set_check_attr (D_Visual *vis, D_RowCtrlAttribute *pcheck) D_FUNCPOSTFIT;

/** @brief ָ���б����һ��
* @param vis	�б�ؼ�
* @param row	�б��к�(��һ���к�:0) (-1ʱ���)
* @param col	�б��к�(��һ���к�:0) (-1ʱ���)
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
@qiny 2013-10-30*/
D_Result
d_list_set_check (D_Visual *vis, D_U16 row, D_U16 col) D_FUNCPOSTFIT;

/** @brief ָ���б���Ƿ����ƶ�״̬
* @param vis	�б�ؼ�
* @param move	�Ƿ����ƶ�״̬
* @param pLinkIds	������id�б�
* @return	�ɹ�����D_OK,ʧ�ܷ���D_ERR
@qiny 2013-10-30*/
D_Result
d_list_set_remove (D_Visual *vis, D_Bool move, D_ListLinkIds *pLinkIds) D_FUNCPOSTFIT;

/** @brief ����һ��ͼ��
* @param vis  ͼ��ؼ�
* @param image	ͼ��
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/

D_Result  d_image_box_set_image (D_Visual *vis, D_Image *img) D_FUNCPOSTFIT;

/** @brief �����б��
* @param select_box �����ѡ���
* @return �ɹ����ؿؼ�ָ��,ʧ�ܷ��� NULL
*/
D_Result d_select_box_show_list(D_Visual	*select_box) D_FUNCPOSTFIT;

/** @brief �����б���Ӧ����������
* @param pop_win �б��
* @return �ɹ����ؿؼ�ָ��,ʧ�ܷ��� NULL
* @control.c �е���
*/
D_Result d_select_box_hide_list(D_Visual	*select) D_FUNCPOSTFIT;

/** @brief �����б��ƶ�����
* @param select �б��
* @param Bool �Ƿ������ƶ�
* @return �ɹ����ؿؼ�ָ��,ʧ�ܷ��� NULL
*/
D_Result d_list_set_move_type(D_Visual	*select, D_Bool Bool) D_FUNCPOSTFIT;


/*����group��Ľ����Ƿ����ѭ���л�*/
D_Result d_group_set_focus_loop(D_Visual *vis, D_Bool loop) D_FUNCPOSTFIT;

/*�趨�ı�*/
D_Result
d_button_set_text (D_Visual *vis, D_Char *text) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
