/** @file
* @brief �ص�����ͷ�ļ�
* @author �
* @date 2013-03-20 �: �����ļ�
* @date 2013-08-09 �: Դ���׼��
*/
#ifndef __D_CBMAN_H
#define __D_CBMAN_H
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief �ص��¼�ID���������С */
#define D_CB_EVT_ID_SPACE_SHIFT	16
#define D_CB_EVT_ID_SPACE		(1 << D_CB_EVT_ID_SPACE_SHIFT) /* 0x10000 */

/** @brief �ص��¼�ID���䶨�� */
#define D_CB_EVT_ID_BASE		0x00000000

#define D_CB_EVT_ID_OS_RESERVED	D_CB_EVT_ID_BASE
    #define PL_INTERRUPT_PVR            (D_CB_EVT_ID_OS_RESERVED)
#define D_CB_EVT_ID_DRIVER              (D_CB_EVT_ID_OS_RESERVED + D_CB_EVT_ID_SPACE)
    #define PL_FEND_LOCK_RET            (D_CB_EVT_ID_DRIVER) /**< fend�豸��ѯ�������� */
    #define PL_FEND_LOCK_CHECK_LOOP     (D_CB_EVT_ID_DRIVER + 1) /**< fend�豸��Ƶ�ȴ�����ѭ�� */
    #define PL_AV_CALLBACK              (D_CB_EVT_ID_DRIVER + 2) /**< ����Ƶ�����ص� */
    #define PL_FEND_SWITCH_CIRCUIT      (D_CB_EVT_ID_DRIVER + 3) /**< fend�豸��·�л� */
    #define PL_USB_DEV_CONNECT          (D_CB_EVT_ID_DRIVER + 4) /**< USB�豸���� */
    #define PL_USB_DEV_DISCONNECT       (D_CB_EVT_ID_DRIVER + 5) /**< USB�豸�Ͽ� */
    #define PL_USB_DEV_ATTACHED_DRIVER  (D_CB_EVT_ID_DRIVER + 6) /**< USB�豸�������� */
    #define PL_USB_DEV_DETACHED_DRIVER  (D_CB_EVT_ID_DRIVER + 7) /**< USB�豸ж������ */
#define D_CB_EVT_ID_PLATFORM1	(D_CB_EVT_ID_DRIVER + D_CB_EVT_ID_SPACE)
	#define PL_GUI_DISP_MSG_PRE 		(D_CB_EVT_ID_PLATFORM1) /**< GUI��Ϣ����ǰ���� */
	#define PL_GUI_DISP_MSG_RET 		(D_CB_EVT_ID_PLATFORM1 + 1) /**< GUI��Ϣ������� */
	#define PL_GUI_IDLE         		(D_CB_EVT_ID_PLATFORM1 + 2) /**< GUI���� */
	#define PL_GUI_VIS_OP_DRAW_PRE		(D_CB_EVT_ID_PLATFORM1 + 3) /**< visual�Ի�ǰ���� */
	#define PL_GUI_VIS_OP_DRAW_RET		(D_CB_EVT_ID_PLATFORM1 + 4) /**< visual�Ի���� */
	#define PL_GUI_CONTROL_NEW			(D_CB_EVT_ID_PLATFORM1 + 5) /**< �ؼ����� */
	#define PL_GUI_CONTROL_DRAW			(D_CB_EVT_ID_PLATFORM1 + 6) /**< �ؼ���ͼ */
	#define PL_GUI_NEW_FRAME_READY		(D_CB_EVT_ID_PLATFORM1 + 7) /**< GUI���һ���ػ�, ������׼����һ֡ */
	#define PL_GUI_VIS_DRAWTEXT			(D_CB_EVT_ID_PLATFORM1 + 8) /**< draw_text()���� */
	#define PL_GUI_IR_REMAP				(D_CB_EVT_ID_PLATFORM1 + 9) /**< ir����ӳ���ֵ���� */
    #define PL_GUI_VIS_NEW              (D_CB_EVT_ID_PLATFORM1 + 10) /**< d_vis_new()���� */
    #define PL_GUI_VIS_FREE             (D_CB_EVT_ID_PLATFORM1 + 11) /**< d_vis_free()���� */
    #define PL_GUI_VIS_UPDATE_RECT      (D_CB_EVT_ID_PLATFORM1 + 12) /**< d_vis_update()���� */
    #define PL_GUI_FP_REMAP             (D_CB_EVT_ID_PLATFORM1 + 13) /**< ǰ�������ӳ���ֵ���� */
    #define PL_GUI_GENERATE_USER_KEY    (D_CB_EVT_ID_PLATFORM1 + 14) /**< �û�����key���� */
    #define PL_GUI_INPUT_POLL           (D_CB_EVT_ID_PLATFORM1 + 15) /**< ��������(�簴������ꡢ������)�¼��Ĺ���*/
	#define PL_GUI_DRAWTEXT			    (D_CB_EVT_ID_PLATFORM1 + 16) /**< draw_text()���� */
    
#define D_CB_EVT_ID_PLATFORM2	(D_CB_EVT_ID_PLATFORM1 + D_CB_EVT_ID_SPACE)
	#define PL_CC_NEXT_CHAR				(D_CB_EVT_ID_PLATFORM2) /**< d_text_next_char()���� */
	#define PL_CC_PREV_CHAR				(D_CB_EVT_ID_PLATFORM2 + 1) /**< d_text_prev_char()���� */
	#define PL_CC_NEXT_WORD				(D_CB_EVT_ID_PLATFORM2 + 2) /**< d_text_next_word()���� */
	#define PL_FONT_OP_CHAR				(D_CB_EVT_ID_PLATFORM2 + 3) /**< font��������, �����ַ�����ת�� */
	#define PL_CC_DRAWTEXT				(D_CB_EVT_ID_PLATFORM2 + 4) /**< draw_text()���� */
	
	#define D_MONITOR_REG_PMT			(D_CB_EVT_ID_PLATFORM2 + 5) /**< ���pmt��ע�ắ�� */
	#define D_MONITOR_REG_SDT			(D_CB_EVT_ID_PLATFORM2 + 6) /**< ���sdt��ע�ắ�� */
	#define D_MONITOR_REG_NIT			(D_CB_EVT_ID_PLATFORM2 + 7) /**< ���nit��ע�ắ�� */
	#define D_MONITOR_PMT_TO_CA			(D_CB_EVT_ID_PLATFORM2 + 8) /**< pmt����ca��������ע�ắ�� */
	#define D_MONITOR_CAT_TO_CA			(D_CB_EVT_ID_PLATFORM2 + 9) /**< cat����ca��������ע�ắ�� */

	#define PL_TV_PLAY_CHANGE_FMAN		(D_CB_EVT_ID_PLATFORM2 + 10) /**< TV����ʱ, ǰ�����͸ı乳�� */

	#define PL_SI_PARSE_DESC_PRE		(D_CB_EVT_ID_PLATFORM2 + 11) /**< SI����������ǰ���� */
	#define PL_SI_PARSE_DESC_RET		(D_CB_EVT_ID_PLATFORM2 + 12) /**< SI���������Ӻ��� */

    #define D_MONITOR_REG_PAT			(D_CB_EVT_ID_PLATFORM2 + 13) /**< ���nit��ע�ắ�� */
    #define D_MONITOR_REG_NIT_TO_LOADER (D_CB_EVT_ID_PLATFORM2 + 14) /**< ���nit��ע�ắ�� */

    #define D_MON_TS_NOT_LOCK           (D_CB_EVT_ID_PLATFORM2 + 15) /**< ����SI������������� */
    #define D_MON_GET_NIT_FULL          (D_CB_EVT_ID_PLATFORM2 + 16) /**< ����nit��ȫ���� */
    #define D_MON_GET_UMT_FULL          (D_CB_EVT_ID_PLATFORM2 + 17) /**< ����UMT��ȫ���� */

    #define PL_FMAN_LOCK_RET             (D_CB_EVT_ID_PLATFORM2 + 18) /**< fman��ѯ�������� */
    #define PL_FMAN_SET_PARAM             (D_CB_EVT_ID_PLATFORM2 + 19) /**< fman�趨Ƶ��������� */

#define D_CB_EVT_ID_PLATFORM3	(D_CB_EVT_ID_PLATFORM2 + D_CB_EVT_ID_SPACE)
    #define CA_GET_CUR_CAS			(D_CB_EVT_ID_PLATFORM3 ) /**get curca */
    #define CA_SET_CUR_CAS          (D_CB_EVT_ID_PLATFORM3 + 1) /**set curca */
    #define CA_GET_CUR_LAN		    (D_CB_EVT_ID_PLATFORM3 + 2) /**ca get cur language */
    #define CA_GET_CUR_STB_SERIALNO (D_CB_EVT_ID_PLATFORM3 + 3) /**ca get cur stb serialno */  
    #define D_MONITOR_NIT_TO_CA     (D_CB_EVT_ID_PLATFORM3 + 4) /**< NIT����ca��������ע�ắ�� */
    #define CA_GET_OTA_INFO         (D_CB_EVT_ID_PLATFORM3 + 5) /*��ȡ��ǰ��Ӳ���汾�źͳ��̴���*/
    #define CA_GET_CA_PRIVATE_INFO  (D_CB_EVT_ID_PLATFORM3 + 6) /**get ca private info*/
    #define CA_SET_CA_PRIVATE_INFO  (D_CB_EVT_ID_PLATFORM3 + 7) /**set ca private info*/
    #define CA_GET_STB_SERIAL_STRING (D_CB_EVT_ID_PLATFORM3 + 8) /**ca get cur stb serialno string */
    #define CA_GET_SPECIAL_FUNC_INFO (D_CB_EVT_ID_PLATFORM3 + 9) /*��ȡ��ǰCA�Ƿ����ر�����*/
    #define CA_GET_SYS_RESOLUTIONRATIO_INFO (D_CB_EVT_ID_PLATFORM3 + 10) /*��ȡ��ǰϵͳ�ֱ���*/
    #define CA_GET_STB_SERIAL_ABV_STRING    (D_CB_EVT_ID_PLATFORM3 + 11) /*��ȡ���кţ�Ŀǰֻ��jiangsu������CA��*/
    #define CA_SET_STB_SERIAL_STRING (D_CB_EVT_ID_PLATFORM3 + 12) /**ca set cur stb serialno string */

#define D_CB_EVT_ID_PLATFORM4	(D_CB_EVT_ID_PLATFORM3 + D_CB_EVT_ID_SPACE)
    #define PL_FILESYSTEM_HOTPLUG   (D_CB_EVT_ID_PLATFORM4) /**< �ļ�ϵͳ�Ȳ��֪ͨ */
    #define PL_APP_MAN_SYNC_LOCK    (D_CB_EVT_ID_PLATFORM4 + 1) /**< app����ͬ������ѯ���� */
    #define PL_SI_PARSE_SRV_TYPE (D_CB_EVT_ID_PLATFORM4 + 2) /**< SI���������Ӻ��� */
   	#define PL_SI_PARSE_PMT	 (D_CB_EVT_ID_PLATFORM4 + 3) /**< SI����pmt����Ĺ��� */
    #define PL_SI_PARSE_PAT	 (D_CB_EVT_ID_PLATFORM4 + 4) /**< SI����pat���� */
	#define PL_MEDIA_PIC_PALY	 (D_CB_EVT_ID_PLATFORM4 + 5) /**< ��ý��ͼƬ���Ź��� */
	#define PL_MEDIA_PVR_PARSE_TS	 (D_CB_EVT_ID_PLATFORM4 + 6) /**<PVR����ģ�������¼���������� */
	#define PL_TV_AV_PLAY_PRE    (D_CB_EVT_ID_PLATFORM4 + 7) /**< tv���ڵ���d_av_play ǰ���� */
	#define PL_TV_AV_STOP_PRE    (D_CB_EVT_ID_PLATFORM4 + 8) /**< tv���ڵ���d_av_stop ǰ���� */
	#define PL_CVBS_CALLBACKE	 (D_CB_EVT_ID_PLATFORM4 + 9) /**< cvbsģ�鹳�� */
	#define PL_AUDIO_DAC_CTL	 (D_CB_EVT_ID_PLATFORM4 + 10) /**<��Ƶ����Դ�仯*/


#define D_CB_EVT_ID_PROJECT1	(D_CB_EVT_ID_PLATFORM4 + D_CB_EVT_ID_SPACE)
#define D_CB_EVT_ID_PROJECT2	(D_CB_EVT_ID_PROJECT1 + D_CB_EVT_ID_SPACE)
#define D_CB_EVT_ID_PROJECT3	(D_CB_EVT_ID_PROJECT2 + D_CB_EVT_ID_SPACE)
#define D_CB_EVT_ID_PROJECT4	(D_CB_EVT_ID_PROJECT3 + D_CB_EVT_ID_SPACE)
#define D_CB_EVT_ID_XMLJEC		(D_CB_EVT_ID_PROJECT4+D_CB_EVT_ID_SPACE)
#define D_CB_EVT_ID_SPACE_MAX	11

/** @brief �ص��������Ͷ��� */
typedef void (*D_CBFunc)(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT;

/** @brief �ص������ʼ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_cbman_open(void) D_FUNCPOSTFIT;

/** @brief �ص������ͷ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_cbman_close(void) D_FUNCPOSTFIT;

/** @brief ע��һ���¼��Ļص�
* @param cb_id �¼�ID
* @param obj �¼���������, ����Ͳ����¼��Ķ���ƥ����ܱ��ص�
* @param cb �ص�����
* @param cb_data �ص�ע�ᴫ�����, �ص����������˲���
* @return �ɹ����ػص����,ʧ�ܷ���D_INVALID_HANDLE
*/
D_Handle d_cbman_subscribe(D_U32 cb_id, D_Handle obj, D_CBFunc cb, D_Ptr cb_data) D_FUNCPOSTFIT;

/** @brief ��ע��ص�
* @param hcbm �ص����
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_cbman_unsubscribe(D_Handle hcbm) D_FUNCPOSTFIT;

/** @brief ����һ���¼�֪ͨ
* @param cb_id �¼�ID
* @param obj �¼���������
* @param obj_data �¼������������
*/
void d_cbman_notify(D_U32 cb_id, D_Handle obj, D_Ptr obj_data) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
