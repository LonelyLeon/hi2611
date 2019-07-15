/** @file
* @brief ������ģ��
* @author ����
* @date 2005-9-13 ����: �����ļ�
*/

#ifndef _D_STB_PLAYER_H_
#define _D_STB_PLAYER_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTV.h"


#define P_VOLUME_MAX 100


/** @brief ������״̬*/
typedef enum {
	D_STB_PLAYER_STATUS_STOPPED,
	D_STB_PLAYER_STATUS_PLAYING
} D_StbPlayerStatus;


#define D_PLAYER_FLAGS_EN_CHANNEL_CHANGE	1	/**< �����û����л�̨*/
#define D_PLAYER_FLAGS_URGENCY				2	/**< ��Ӧ���㲥ģʽ*/

#define D_PLAYER_FLAGS_PVR				              4	/**< ��PVR ģʽ*/

/** @brief �����н�Ŀ�����豸*/
typedef struct {
	D_StbPlayerStatus	status;			/**< ��������ǰ״̬*/
	D_HTV			htv;				/**< TV�豸���*/
	D_FEndType	   	fendtype;		/**< ��ǰ���Ž�Ŀ��ǰ������*/	
	D_HFMan			hfman;			/**< ǰ���豸������*/

	D_Bool                  play_emc_flag; 	/**< ���ڲ���Ӧ���㲥Ƶ��*/	
	D_Bool			play_srv;		/**< ���ڷ��񲥷�״̬*/	

	D_DBSrvID		tv_id;			/**< ���ڲ��ŵĵ��ӽ�Ŀ*/
	D_S16			tv_num;			/**< ��ǰ���ӽ�ĿƵ����*/
	D_DBSrvID		prev_tv_id;		/**< ��һ�����ŵĵ��ӽ�Ŀ*/
	
	D_Bool			play_radio;		/**< ���ڲ��Ź㲥��Ŀ*/	
	D_DBSrvID		radio_id;		/**< ���ڲ��ŵĹ㲥��Ŀ*/
	D_S16			radio_num;		/**< ��ǰ�㲥��ĿƵ����*/
	D_DBSrvID		prev_radio_id;	/**< ��һ�����ŵĹ㲥��Ŀ*/
	
	D_Bool			play_atv;		/**< ���ڲ���ģ���Ŀ*/	
	D_DBSrvID		atv_id;		/**< ���ڲ��ŵ�ģ���Ŀ*/
	D_S16			atv_num;		/**< ��ǰģ���ĿƵ����*/
	D_DBSrvID		prev_atv_id;	/**< ��һ�����ŵ�ģ���Ŀ*/

	D_DBSrvID		srv_id;			/**< �̶����ŵķ���ID*/
	
	D_DBSrvID		unlock_srv_id;	/**< ��ǰ�Ѿ������ķ���ID*/	
	
	D_HTimer		urgency_timer;	/**< Ӧ���㲥��ʱ��*/
	D_DBSrvID		urgency_prev_srv_id;	/**< Ӧ���㲥���Ų���ǰ�ķ���*/
	D_U32			playflags;			/**< ������״̬��־*/
} D_StbPlayer;



/** @brief ����ָ��ID�Ĳ�����*/
D_StbPlayer*	p_stb_get_player (D_ID player_id) D_FUNCPOSTFIT;

/** @brief ��ʼ��һ��������
* @param player_id		������ID
* @param hfman	ǰ���豸���,����D_INVALID_HANDLE
* @param htv		TV�豸���
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	p_stb_player_init (D_ID player_id, D_HFMan hfman, D_HTV htv) D_FUNCPOSTFIT;

/** @brief �������ò������ڲ�����
* @param player_id		������ID
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	p_stb_player_reset (D_ID player_id) D_FUNCPOSTFIT;

/** @brief �趨���������ű�־
* @param player_id ������ID
* @param flags	��������־
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	p_stb_player_set_flags (D_ID player_id, D_U32 flags) D_FUNCPOSTFIT;

/** @brief ȡ�ò��������ű�־
* @param player_id ������ID
* @return ���ص�ǰ�Ĳ���״̬
*/
D_U32	p_stb_player_get_flags (D_ID player_id) D_FUNCPOSTFIT;

/** @brief ���Բ���һ��Ƶ��
* @param 	player_id	������ID
* @param	num	��ĿƵ����
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	p_stb_player_play (D_ID player_id, D_U16 num) D_FUNCPOSTFIT;

/** @brief ���Բ���һ������
* @param 	player_id	������ID
* @param	srv	��Ŀ��¼ID
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	p_stb_player_play_srv (D_ID player_id, D_DBSrvID srv) D_FUNCPOSTFIT;

/** @brief ����Ӧ���㲥
* @param[in] player_id	������ID
* @param[in] srv	��Ŀ��¼ID
* @param[in] ms	Ӧ���㲥�ӳ�ʱ��(����)��<= 0��ʾһֱ����
* @retval D_OK ��ȷ, D_ERRʧ��
*/
D_Result	p_stb_player_play_urgency_srv (D_ID player_id, D_DBSrvID srv, D_MSec ms) D_FUNCPOSTFIT;

/** @brief ֹͣӦ���㲥
* @param[in] player_id	������ID
* @param[in] play_prev �Ƿ񷵻ز���֮ǰ�Ľ�Ŀ
* @retval D_OK ��ȷ, D_ERRʧ��
*/
D_Result	p_stb_player_stop_urgency_srv (D_ID player_id, D_Bool play_prev) D_FUNCPOSTFIT;

/** @brief ���Խ�������Ƶ���Ų�����CA
* @param 	player_id	������ID
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	p_stb_player_try_play (D_ID player_id) D_FUNCPOSTFIT;

/** @brief ���Բ��Ÿ��ֿ��ܵĽ�Ŀ
* @param 	player_id	������ID
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	p_stb_player_play_valid (D_ID player_id) D_FUNCPOSTFIT;

/** @brief ֹͣ����
* @param 	player_id	������ID
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	p_stb_player_stop (D_ID player_id) D_FUNCPOSTFIT;

/** @brief ������һ��Ƶ��
* @param 	player_id	������ID
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	p_stb_player_channel_up (D_ID player_id) D_FUNCPOSTFIT;

/** @brief ������һ��Ƶ��
* @param 	player_id	������ID
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	p_stb_player_channel_down (D_ID player_id) D_FUNCPOSTFIT;

/** @brief �л����Ӻ͹㲥����ģʽ
* @param 	player_id	������ID
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	p_stb_player_switch_tv_radio (D_ID player_id,D_Bool play_tv) D_FUNCPOSTFIT;


/** @brief ȡ�õ�ǰ���ŵķ���ID*/
D_DBSrvID	p_stb_player_get_curr_srv (D_ID player_id) D_FUNCPOSTFIT;

/** @brief ȡ�õ�ǰ���ŵ�Ƶ���źͷ�������*/
D_S16			p_stb_player_get_curr_chan_num (D_ID player_id, D_DBSrvType *type) D_FUNCPOSTFIT;

/**@brief �����Ŀ��ʾ(Added by licc 2006-07-06)*/
/* @param 	player_id	������ID
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result p_stb_player_alt_srv(D_ID player_id) D_FUNCPOSTFIT;

/** @brief �õ��������м�¼�ķ���ID*/
D_DBSrvID	p_stb_player_get_rec_srv (D_ID player_id, D_DBSrvType type) D_FUNCPOSTFIT;

/** @brief ����I֡*/
D_Result p_stb_player_display_pic_I (D_ID player_id, D_ID pic, D_ID no) D_FUNCPOSTFIT;

/** @brief ���������Ƶ ֡(��������)��stop֮�����*/	
D_Result p_stb_player_clear_vid(D_ID player_id)  D_FUNCPOSTFIT;

/** @brief ����������������ֵת��Ϊ������������ֵ*/
D_Result p_stb_player_set_vol (D_ID player_id, D_U8 vol) D_FUNCPOSTFIT;

/** @brief ��������*/
D_Result p_stb_player_set_track (D_ID player_id, D_AudTrack track) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif
