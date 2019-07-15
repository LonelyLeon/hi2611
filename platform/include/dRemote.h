/** @file
* @brief ң�����豸����
* @author majy
* @date 2013-7-26 majy: �����ļ�
* @date 2013-07-26 lc: ͳһƽ̨, ��������
*/

#ifndef _D_REMOTE_H_
#define _D_REMOTE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dFP.h"


/** @brief ң����������ֵ*/
typedef D_U32	D_RemoteKey;
typedef enum{
NEC = 1,
BESC,
DONGZHI,
RC_5
}D_RemoteCode;

/*typedef struct  
{
    D_U8   	RomoteSlaveAdd;   
    D_U32  	PulsePilot;
    D_U32  	PulseZero;
    D_U32  	PulseOne;
    D_U32  	RepeatTime;
    D_Float	ErrRange;
}D_REMOTE_Para;*/

typedef struct
{
	D_S8 repeat;
	D_U8 guid_code;
	D_U16 machine_code;
	D_U16 source_code;
}D_RemoteKeyParam;

typedef struct
{
	D_RemoteKeyParam *key;
	D_RemoteKey mapped_key;
}D_RemoteMapHookParam;

typedef struct
{   
    D_U8  remotetpye;
    D_U16  pulsepilot;
    D_U16  pulsesecondpilot;
    D_U16  pulselong;
    D_U16  pulseshort;
    D_U16  repeattime;
    D_U8  errorrange;
}D_IRDbgOpenParam;

/** @brief ң������ʼ�� 
* 
*�ڵ���ң��������ʱ���ȵ��ô˺��� 
* @retval D_OK	��ʼ���ɹ� 
* @retval D_ERR	��ʼ��ʧ�� 
*/ 
D_Result 
d_remote_open (void) D_FUNCPOSTFIT;

D_Result d_remote_open_ex (void) D_FUNCPOSTFIT;

/** @brief ����ң��������
* @param NecRemoteType
* @param BesconRemoteType
* @param DongzhiRemoteType
* @param Rc_5RemoteType
* @retval D_OK	���óɹ�
* @retval D_ERR	����ʧ��
*/
D_Result
d_set_remote_para(D_IRDbgOpenParam *irdbg_open_param) D_FUNCPOSTFIT;

/** @brief ����֧��ң����������
*param code ң��������
*param flag 1֧��0��֧��
* @retval D_OK	���óɹ�
* @retval D_ERR	����ʧ��
*/

D_Result  d_remote_poll_key (D_RemoteKeyParam *key) D_FUNCPOSTFIT;

/** @brief IRת��
*param code ң��������
*param DVDHeadValue
*param DVDCmdValue
* @retval D_OK	���óɹ�
* @retval D_ERR	����ʧ��
*/
D_Result d_remote_send_dvdir (D_U8 type,D_U16 DVDHeadValue,D_U8 DVDCmdValue) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif

#endif
