/** @file 
* @brief �������豸
* @author �
* @date 2015-07-10  ��С��: �����ļ�
*/
#ifndef __D_TOUCH_SCREEN_H
#define __D_TOUCH_SCREEN_H

#include "dTypes.h"
#include "dIO.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/** @brief �������ͺ�*/
typedef enum
{
    touchscreen_FT5x06,
    touchscreen_max,
}D_TouchScreenType_t;

/** @brief �������¼� */
typedef enum
{
	D_TOUCH_SCREEN_EVENT_DOWN = 0,
	D_TOUCH_SCREEN_EVENT_UP,
	D_TOUCH_SCREEN_EVENT_MOVE,
}D_TouchScreenEvent;

/** @brief ��������ѯ���� */
typedef struct
{
    D_TouchScreenEvent evt;  /**< �������¼� */
    D_U16 x;  /**< ������x���� */
    D_U16 y;  /**< ������y���� */
}D_TouchScreenPollData;


/** @brief ������open����*/
typedef struct
{
    D_Coord             xres;   /**< ˮƽ�ֱ��� */
    D_Coord             yres;   /**< ��ֱ�ֱ��� */
    D_S8                prio;   /* �������ȼ�*/
    D_TouchScreenType_t type;   /* �������ͺ�*/
    D_GPIO_PortBit      reset;  /* ��λ����io*/
    D_GPIO_PortBit      interrupt;  /* �ж�����io*/
}D_TouchScreenOpenParam;


/** @brief �����������ӿ�*/
typedef struct 
{
	D_Result (*init)(D_TouchScreenOpenParam *ts)D_FUNCPOSTFIT;
	D_Result (*deinit)(void)D_FUNCPOSTFIT;
	D_Result (*reset)(void)D_FUNCPOSTFIT;
    D_Result (*poll)(D_TouchScreenPollData *poll_data)D_FUNCPOSTFIT;
}D_TouchScreenOp;


/** @brief �������豸ע��
* @retval D_OK	ע��ɹ�
* @retval D_ERR	ע��ʧ��
*/
D_Result d_touchscreen_register_ops(D_TouchScreenType_t type, D_TouchScreenOp *op) D_FUNCPOSTFIT;

/** @brief �������豸��ʼ��
* @param[in]  ��ʼ������
* @retval D_OK	��ʼ���ɹ�
* @retval D_ERR	��ʼ��ʧ��
*/
D_Result d_touchscreen_open(D_TouchScreenOpenParam *ts) D_FUNCPOSTFIT;

/** @brief �������豸����ʼ��
* @retval D_OK	����ʼ���ɹ�
* @retval D_ERR	����ʼ��ʧ��
*/
D_Result d_touchscreen_close(void) D_FUNCPOSTFIT;

/** @brief �������豸��ѯ
* @param[out] poll_data ��ѯ��������
* @retval D_OK	��ѯ������
* @retval D_ERR	��ѯ������
*/
D_Result d_touchscreen_poll(D_TouchScreenPollData *poll_data) D_FUNCPOSTFIT;

/** @brief ���������񴴽�*/
D_Result d_touchscreen_init(void) D_FUNCPOSTFIT;


D_Result d_touchscreen_register_FT5x06(void) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif
#endif

