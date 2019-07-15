/** @file 
* @brief ����豸
* @author �
* @date 2014-07-10  �: �����ļ�
*/
#ifndef __D_MOUSE_H
#define __D_MOUSE_H

#include "dTypes.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/** @brief ����¼� */
typedef enum
{
	D_MOUSE_EVENT_LBUTTON_DOWN = 0,
	D_MOUSE_EVENT_LBUTTON_UP,
	D_MOUSE_EVENT_RBUTTON_DOWN,
	D_MOUSE_EVENT_RBUTTON_UP,
	D_MOUSE_EVENT_MBUTTON_DOWN,
	D_MOUSE_EVENT_MBUTTON_UP,
	D_MOUSE_EVENT_MOVE,
	D_MOUSE_EVENT_WHEEL,
}D_MouseEvent;

#define MOUSE_BUTTON_LEFT      0x0001
#define MOUSE_BUTTON_RIGHT     0x0002
#define MOUSE_BUTTON_MIDDLE    0x0004

/** @brief ����豸��ʼ���ṹ */
typedef struct
{
    D_Coord xres;  /**< ˮƽ�ֱ��� */
    D_Coord yres;  /**< ��ֱ�ֱ��� */
}D_MouseOpenParam;

/** @brief ����ѯ���� */
typedef struct
{
    D_MouseEvent evt;  /**< ����¼� */
    D_U16 button;  /**< ��갴��(���) */
    D_U16 x;  /**< ���x���� */
    D_U16 y;  /**< ���y���� */
    D_S16 z;  /**< ���ֻ���λ�� */
}D_MousePollData;

/** @brief ����豸��ʼ��
* @param[in]  ��ʼ������
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result d_mouse_open(D_MouseOpenParam *param) D_FUNCPOSTFIT;

/** @brief ����豸����ʼ��
* @retval D_OK	����ʼ���ɹ�
* @retval D_ERR	����ʼ��ʧ��
*/
D_Result d_mouse_close(void) D_FUNCPOSTFIT;

/** @brief ����豸��ѯ
* @param[out] poll_data ��ѯ��������
* @retval D_OK	��ѯ������
* @retval D_ERR	��ѯ������
*/
D_Result d_mouse_poll(D_MousePollData *poll_data) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
