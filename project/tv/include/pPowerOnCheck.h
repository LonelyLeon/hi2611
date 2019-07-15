/**@defgroup MonitorTable 
*@{*/
/** @file
* @brief �������(����������)
* @author qiny
* @date 2013-09-09 qiny: �����ļ�
*/
#ifndef _D_POWERON_CHECK_H_
#define _D_POWERON_CHECK_H_

#ifdef  __cplusplus

extern "C"
{
#endif



/*���������*/
typedef struct
{
    D_Bool  network_match;
    D_U32   reserved;
}D_PowerOnCheck;




/** @brief ���������س�ʼ��
*@return D_ERR ��ʼ��ʧ�� D_OK ��ʼ���ɹ�
*/
D_Result p_power_on_check_init(void)D_FUNCPOSTFIT;

/** @brief ���������ط���ʼ��
*@return D_ERR ����ʼ��ʧ�� D_OK ����ʼ���ɹ�
*/
D_Result p_power_on_check_deinit(void)D_FUNCPOSTFIT;


/** @brief ��������������
*@return D_ERR ����ʼ��ʧ�� D_OK ����ʼ���ɹ�
*/
D_Result p_power_on_check_start(D_FEndType fendtype)D_FUNCPOSTFIT;


/** @brief ֹͣ����������
*@return D_ERR ����ʼ��ʧ�� D_OK ����ʼ���ɹ�
*/
D_Result p_power_on_check_stop(D_FEndType fendtype)D_FUNCPOSTFIT;


/** @brief ȡ�ÿ��������
*@return D_OK \D_ERR
*/
D_Bool p_power_on_check(D_PowerOnCheck *pow)D_FUNCPOSTFIT;



#ifdef  __cplusplus
}
#endif

#endif
/* @}*/

