/** @file
* @brief ��Ϣ����ģ��
* @author ����
* @date 2005-9-13 ����: �����ļ�
* @date 2013-06-20 �: ��������ʵ��
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

/** @brief ��Ϣ������*/
typedef enum {
	D_POP_MSG_MSG,			/**< ��ͨ��Ϣ*/
	D_POP_MSG_ERROR,		/**< ������Ϣ*/
	D_POP_MSG_WARNING		/**< ������Ϣ*/
} D_PopMsgType;

/** @brief �û���Ӧ��������*/
typedef enum {
	D_POP_MSG_RESPONSE_NOT,		/*����Ӧ�κΰ���*/
	D_POP_MSG_RESPONSE_ANY,		/*�������ʧ*/
	D_POP_MSG_RESPONSE_OK,		/*OK����ʧ*/
	D_POP_MSG_RESPONSE_ALL_NOT	/*���м���ӦD_OK, ����ʵ���Բ���*/
} D_PopMsgResponseType;

enum{
	D_MULTI_SEL_VALUE_REPLACE = 0,
	D_MULTI_SEL_VALUE_INSERT,
	D_MULTI_SEL_VALUE_CANCEL,
	D_MULTI_SEL_VALUE_COUNT
};

/** @brief �û����������*/
typedef enum {
	D_POP_INPUT_NORMAL,		/**< ��ͨ*/
	D_POP_INPUT_POWER_ON,	/**< ���������*/
	D_POP_INPUT_PROG_LOCK	/**< ��Ŀ�������*/
} D_PopInputType;


/*�����˵����ȼ�����*/
#define D_POP_MSG_PRIO_MIN			(0)
#define D_POP_MSG_PRIO_MAX			D_POP_PRIO_MAX

/*��Щ���ȼ���Video message��ʹ��*/
#define D_POP_MSG_PRIO_VIDEO_MSG_1	(0)
#define D_POP_MSG_PRIO_VIDEO_MSG_2	(1)
#define D_POP_MSG_PRIO_VIDEO_MSG_3	(2)
#define D_POP_MSG_PRIO_VIDEO_MSG_4	(3)

/*��Щ���ȼ���Message��ʹ��*/
#define D_POP_MSG_PRIO_MSG_1		(4)
#define D_POP_MSG_PRIO_MSG_2		(5)
#define	D_POP_MSG_PRIO_MSG_3		(6)
#define D_POP_MSG_PRIO_MSG_4		(7)

/** @brief ��ʾ��������Ϣ����
* @param prio			��Ϣ������ȼ�
* @param layer			��ʾ���ڵĲ�
* @param type			��Ϣ������
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣid
* @param timeout��		��������Ļ��������ʱ�䣬С�ڵ��ڣ���ʾ��Զ��ʾ,ֱ������d_pop_msg_hide
						���û��ֶ�����
* @param pop_msg_resp_type	��Ӧ����
* @param video_win_show	��С��Ƶ�������Ƿ���ʾ
* @param handler		�û�ȷ�Ϻ���õĺ���ָ��
* @param param			�����û��ص��Ĳ���
* @return ��ʾ�ɹ�����D_OK,��ʾʧ�ܷ���D_ERR
*/
D_Result d_stb_pop_msg_show (D_U16 prio,
		D_GUILayer layer,
		D_PopMsgType type, const D_Char *str_title, const D_Char *msg, 
		D_MSec timeout, D_PopMsgResponseType pop_msg_resp_type, 
		D_Bool video_win_show,
		D_Result (*handler) (D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT;

/** @brief ��˸��ʾ��������Ϣ����
* @param prio			��Ϣ������ȼ�
* @param layer			��ʾ���ڵĲ�
* @param type			��Ϣ������
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣ�ı�
* @param flash_times        ��˸����
* @param show_time��	��˸ʱ��ʾʱ��
* @param hide_time		��˸ʱ����ʱ��
* @param pop_msg_resp_type	��Ӧ����
* @param video_win_show	��С��Ƶ�������Ƿ���ʾ
* @param handler		�û�ȷ�Ϻ���õĺ���ָ��
* @param param			�����û��ص��Ĳ���
* @return ��ʾ�ɹ�����D_OK,��ʾʧ�ܷ���D_ERR
*/
D_Result d_stb_pop_msg_flash_show (D_U16 prio, D_GUILayer layer,
		D_PopMsgType type, const D_Char *str_title, const D_Char *msg, 
		D_U16 flash_times, D_MSec show_time, D_MSec hide_time, 
		D_PopMsgResponseType pop_msg_resp_type, D_Bool video_win_show,
		D_Result (*handler) (D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT;

/** @brief ������ʾ����Ϣ����
* @param prio			��Ϣ������ȼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_stb_pop_msg_hide (D_U16 prio) D_FUNCPOSTFIT;

/** @brief ��ʾ�������û�ѡ�񴰿�,�û�����ѡ��ȷ�ϻ�ȡ��
* @param prio			��Ϣ������ȼ�
* @param layer			��ʾ���ڵĲ�
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣ
* @param timeout��		��������Ļ��������ʱ�䣬С�ڵ��ڣ���ʾ��Զ��ʾ,ֱ������d_pop_select_hide
						���û��ֶ�����
* @param def			D_TRUE��ʾ��ʱ����û�����ȷ��Ч����ͬ��D_FALSE��ʾ��ʱ����û�����ȡ��
						Ч����ͬ
* @param handler		ѡ����ص�����ָ��
* @param param			�����û��ص��Ĳ���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
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
/** @brief ������ʾ���û�ѡ�񴰿�
* @param prio			��Ϣ������ȼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_stb_pop_select_hide (D_U16 prio) D_FUNCPOSTFIT;


/** @brief ��ʾ���봰��(��ȷ�����˳���ʾ)
* @param prio			��Ϣ������ȼ�
* @param layer		��ʾ���ڵĲ�
* @param type		���������
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣ
* @param len			�����ַ�����
* @param user_hide	�û��Ƿ�����ֶ��˳�
* @param handler	ѡ����ص�����ָ��
* @param param		�����û��ص��Ĳ���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_stb_pop_input_show (D_U16 prio,
		D_GUILayer layer,
		D_PopInputType type,
		const D_Char *str_title,
		const D_Char *msg,
		D_U16 len, D_Bool user_hide,
		D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT,
		D_U32	param) D_FUNCPOSTFIT;


/** @brief ��ʾ���봰��(����ֻ��ȷ����ʾ)
* @param prio			��Ϣ������ȼ�
* @param layer		��ʾ���ڵĲ�
* @param type		���������
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣ
* @param len			�����ַ�����
* @param user_hide	�û��Ƿ�����ֶ��˳�
* @param handler	ѡ����ص�����ָ��
* @param param		�����û��ص��Ĳ���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_stb_pop_input_show_ex (D_U16 prio,
		D_GUILayer layer,
		D_PopInputType type,
		const D_Char *str_title,
		const D_Char *msg,
		D_U16 len, D_Bool user_hide,
		D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT,
		D_U32	param) D_FUNCPOSTFIT;


/** @brief ������ʾ���û�ѡ�񴰿�
* @param prio			��Ϣ������ȼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_stb_pop_input_hide (D_U16 prio) D_FUNCPOSTFIT;


/** @brief ��ʾ�������û�ѡ�񴰿�,�û�����ѡ��ȷ�ϻ�ȡ��
* @param prio			��Ϣ������ȼ�
* @param layer			��ʾ���ڵĲ�
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣ
* @param timeout��		��������Ļ��������ʱ�䣬С�ڵ��ڣ���ʾ��Զ��ʾ,ֱ������d_pop_select_hide
						���û��ֶ�����
* @param def			D_TRUE��ʾ��ʱ����û�����ȷ��Ч����ͬ��D_FALSE��ʾ��ʱ����û�����ȡ��
						Ч����ͬ
* @param handler		ѡ����ص�����ָ��
* @param param			�����û��ص��Ĳ���
* @para posx, posy       ��ʾλ������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
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


/** @brief ��ʾ�������û�ѡ�񴰿�,�û�����ѡ��ȷ�ϻ�ȡ��
* @param prio			��Ϣ������ȼ�
* @param layer			��ʾ���ڵĲ�
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣ
* @param timeout��		��������Ļ��������ʱ�䣬С�ڵ��ڣ���ʾ��Զ��ʾ,ֱ������d_pop_select_hide
						���û��ֶ�����
* @param def			D_TRUE��ʾ��ʱ����û�����ȷ��Ч����ͬ��D_FALSE��ʾ��ʱ����û�����ȡ��
						Ч����ͬ
* @param handler		ѡ����ص�����ָ��
* @param param			�����û��ص��Ĳ���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
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

/** @brief ������ʾ���û�ѡ�񴰿�
* @param prio			��Ϣ������ȼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_atv_pop_select_hide (D_U16 prio) D_FUNCPOSTFIT;

/** @brief ��ʾ�������û�ѡ�񴰿�,�û�����ѡ��ȷ�ϻ�ȡ��
* @param prio			��Ϣ������ȼ�
* @param layer			��ʾ���ڵĲ�
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣ
* @param timeout��		��������Ļ��������ʱ�䣬С�ڵ��ڣ���ʾ��Զ��ʾ,ֱ������d_pop_select_hide
						���û��ֶ�����
* @param def			D_TRUE��ʾ��ʱ����û�����ȷ��Ч����ͬ��D_FALSE��ʾ��ʱ����û�����ȡ��
						Ч����ͬ
* @param handler		ѡ����ص�����ָ��
* @param param			�����û��ص��Ĳ���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
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

/** @brief ������ʾ���û�ѡ�񴰿�
* @param prio			��Ϣ������ȼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_atv_pop_select_center_hide (D_U16 prio) D_FUNCPOSTFIT;

/** @brief ��ʾ��������Ϣ����
* @param prio			��Ϣ������ȼ�
* @param layer			��ʾ���ڵĲ�
* @param type			��Ϣ������
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣ�ı�
* @param timeout��		��������Ļ��������ʱ�䣬С�ڵ��ڣ���ʾ��Զ��ʾ,ֱ������d_pop_msg_hide
						���û��ֶ�����
* @param pop_msg_resp_type	��Ӧ����
* @param video_win_show	��С��Ƶ�������Ƿ���ʾ
* @param handler		�û�ȷ�Ϻ���õĺ���ָ��
* @param param			�����û��ص��Ĳ���
* @return ��ʾ�ɹ�����D_OK,��ʾʧ�ܷ���D_ERR
*/
D_Result d_atv_pop_msg_show (D_U16 prio,
		D_GUILayer layer,
		D_PopMsgType type, const D_Char *str_title, const D_Char *msg, 
		D_MSec timeout, D_PopMsgResponseType pop_msg_resp_type, 
		D_Bool video_win_show,
		D_Result (*handler) (D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT;

/** @brief ��˸��ʾ��������Ϣ����
* @param prio			��Ϣ������ȼ�
* @param layer			��ʾ���ڵĲ�
* @param type			��Ϣ������
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣ�ı�
* @param flash_times        ��˸����
* @param show_time��	��˸ʱ��ʾʱ��
* @param hide_time		��˸ʱ����ʱ��
* @param pop_msg_resp_type	��Ӧ����
* @param video_win_show	��С��Ƶ�������Ƿ���ʾ
* @param handler		�û�ȷ�Ϻ���õĺ���ָ��
* @param param			�����û��ص��Ĳ���
* @return ��ʾ�ɹ�����D_OK,��ʾʧ�ܷ���D_ERR
*/
D_Result d_atv_pop_msg_flash_show (D_U16 prio, D_GUILayer layer,
		D_PopMsgType type, const D_Char *str_title, const D_Char *msg, 
		D_U16 flash_times, D_MSec show_time, D_MSec hide_time, 
		D_PopMsgResponseType pop_msg_resp_type, D_Bool video_win_show,
		D_Result (*handler) (D_U32 param) D_FUNCPOSTFIT,
		D_U32 param) D_FUNCPOSTFIT;

/** @brief ������ʾ����Ϣ����
* @param prio			��Ϣ������ȼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_atv_pop_msg_hide (D_U16 prio) D_FUNCPOSTFIT;

/** @brief ��ʾ���봰��(��ȷ�����˳���ʾ)
* @param prio			��Ϣ������ȼ�
* @param layer		��ʾ���ڵĲ�
* @param type		���������
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣ
* @param len			�����ַ�����
* @param user_hide	�û��Ƿ�����ֶ��˳�
* @param handler	ѡ����ص�����ָ��
* @param param		�����û��ص��Ĳ���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_atv_pop_input_show (D_U16 prio,
		D_GUILayer layer,
		D_PopInputType type,
		const D_Char *str_title,
		const D_Char *msg,
		D_U16 len, D_Bool user_hide,
		D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT,
		D_U32	param) D_FUNCPOSTFIT;


/** @brief ��ʾ���봰��(����ֻ��ȷ����ʾ)
* @param prio			��Ϣ������ȼ�
* @param layer		��ʾ���ڵĲ�
* @param type		���������
* @param str_title			Ҫ��ʾ�ı����ı�
* @param msg			Ҫ��ʾ����Ϣ
* @param len			�����ַ�����
* @param user_hide	�û��Ƿ�����ֶ��˳�
* @param handler	ѡ����ص�����ָ��
* @param param		�����û��ص��Ĳ���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_atv_pop_input_show_ex (D_U16 prio,
		D_GUILayer layer,
		D_PopInputType type,
		const D_Char *str_title,
		const D_Char *msg,
		D_U16 len, D_Bool user_hide,
		D_Result (*handler) (D_Char *input, D_U32 param) D_FUNCPOSTFIT,
		D_U32	param) D_FUNCPOSTFIT;


/** @brief ������ʾ���û�ѡ�񴰿�
* @param prio			��Ϣ������ȼ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_atv_pop_input_hide (D_U16 prio) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

