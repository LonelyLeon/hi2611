//���ļ�����Ҫ�������ʵ�ֲ��ṩ����ȫ�ܿ�ģ��ģ��ʹ�õĽӿڡ�����HRESULT����ֵΪDVTSTC_OK����ʾ�ɹ�������ֵ��ʾʧ�ܡ�

#ifndef _DVTSTB_STCSINTERFACE_H_2004_12_31_
#define _DVTSTB_STCSINTERFACE_H_2004_12_31_

#include "DVTSTCS_STBDataPublic.h"

#ifdef  __cplusplus
extern "C" {
#endif 
//�̺߳�����ַ����
typedef void (*pThreadFunc) (void);

/*----------------------------------���½ӿ���STB�ṩ��STCS����--------------------------------------------*/
/*++
���ܣ���û����з����STCS��flash�ռ������ַ�ʹ�С�����ֽ�Ϊ��λ����
������
	ppStartAddr:			�����з����STCS��flash�ռ�Ŀ�ʼ��ַ��
	lSize:					��������з����STCS��flash�ռ�Ĵ�С��
--*/
HRESULT DVTSTBSTC_GetDataBufferAddr(long * lSize, char ** ppStartAddr);

/*++
���ܣ���ȡ�����ڻ�����flash�е���Ϣ��
������
	pStartAddr:				Ҫ��ȡ�Ĵ洢�ռ�Ŀ�ʼ��ַ��
	plDataLen:				����ΪҪ��ȡ�������ֵ�����Ϊʵ�ʶ�ȡ�Ĵ�С��
	pData:					���������ݡ�
--*/
HRESULT DVTSTBSTC_ReadDataBuffer(const char * pStartAddr, long * plDataLen, BYTE * pData);

/*++
���ܣ�������еĴ洢�ռ�д��Ϣ��
������
	lStartAddr:				Ҫд�Ĵ洢�ռ�Ŀ�ʼ��ַ��
	plDataLen:				����ΪҪд�����ݵĳ��ȣ����Ϊд���ʵ�ʳ��ȡ�
	pData:					Ҫд�����ݡ�
--*/
HRESULT DVTSTBSTC_WriteDataBuffer(const char * pStartAddr, long * plDataLen, const BYTE * pData);

/*++
���ܣ���ȡ�����ڻ�����eeprom�е���Ϣ��
������
	plDataLen:				����ΪҪ��ȡ�������ֵ�����Ϊʵ�ʶ�ȡ�Ĵ�С��
	pData:					���������ݡ�
ע��: ��flashģ��Ļ����������һ��������page,�Է���ʧ
--*/
HRESULT DVTSTBSTC_GetDataFromEeprom(long * plDataLen, BYTE * pData);

/*++
���ܣ�������е�eeprom�洢�ռ�д��Ϣ��
������
	plDataLen:				����ΪҪд�����ݵĳ��ȣ����Ϊд���ʵ�ʳ��ȡ�
	pData:					Ҫд�����ݡ�
ע��: ��flashģ��Ļ����������һ��������page,�Է���ʧ
--*/
HRESULT DVTSTBSTC_SaveDataToEeprom(long * plDataLen, const BYTE * pData);

/*++
���ܣ�����ǰ�̡߳�
������
	dwMicroseconds:			���롣
--*/
HRESULT DVTSTBSTC_Sleep( int dwMicroseconds );

/*++
���ܣ���ʼ���ź���,��ʼ�����ź���û���źš�
������
	pSemaphore:				ָ���ź�����ָ�롣
--*/
HRESULT DVTSTBSTC_SemaphoreInit( DVTSTC_Semaphore * pSemaphore );

/*++
���ܣ����ź������źš�
������
	pSemaphore: 			ָ���ź�����ָ�롣
--*/
HRESULT DVTSTBSTC_SemaphoreSignal( DVTSTC_Semaphore * pSemaphore );

/*++
���ܣ��ȴ��ź���,�ȴ��ɹ�֮��,�ź���Ϊ���źš�
������
	pSemaphore: 			ָ���ź�����ָ�롣
--*/
HRESULT DVTSTBSTC_SemaphoreWait( DVTSTC_Semaphore * pSemaphore );

/*++
���ܣ�STCSģ���������ע���̡߳�
������
	szName:					ע����߳����ơ�
	pTaskFun:				Ҫע����̺߳�����
--*/
HRESULT DVTSTBSTC_RegisterTask(const char * szName, pThreadFunc pTaskFun);

/*++
���ܣ����ù���������STCS˽�����ݡ�
������
	byReqID:				�����ձ������š�������Ӧ�ñ�������ݣ����յ�STCS˽�����ݺ����DVTSTCSTB_StreamGuardDataGot()ʱӦ�ý������ݷ��ء�
	wEcmPID:				��Ҫ���˵�����PID��
	szFilter:				��������ֵ
	szMask:					�����������룬���������Ӧ����szMask��ĳһbitλΪ0ʱ��ʾҪ���˵ı��Ӧ��bitλ����Ҫ��szFilter���Ӧ��bitλ��ͬ����szMaskĳһλΪ1ʱ��ʾҪ���˵ı��Ӧ��bitλһ��Ҫ��szFilter���Ӧ��bitλ��ͬ��
	byLen:					�������ĳ��ȣ�Ϊ8��12��
	nWaitSeconds:			�մ˱���ĵȴ�ʱ�䣬���Ϊ0�����޵ȴ�����λ�롣
--*/
HRESULT DVTSTBSTC_SetStreamGuardFilter(BYTE byReqID, WORD wPID, const BYTE * szFilter, const BYTE * szMask, BYTE byLen, int nWaitSeconds);

/*++
���ܣ�CA�����ô˺������������������ø��߰�оƬ��
������
	wEcmPID:				CW������ECMPID��
	byDataLen:				szData�ĳ��ȡ�
	szData:					���ܵ�CW��Key��
	bTapingControl:			true������¼��,false��������¼��
����ֵ���轫��ʵ��оƬ�ײ�ӿڷ���ֱֵ�ӷ��ظ�CA
--*/
HRESULT DVTSTBSTC_SetDescrCW(WORD wEcmPID, BYTE byDataLen, const BYTE * szData, bool bTapingControl);
/*++
���ܣ���ӡ������Ϣ��
������
	pszMsg:					������Ϣ���ݡ�
--*/
void DVTSTBSTC_AddDebugMsg(const char * pszMsg);

/*--------------------------- ����1�Ľ��棺�������û�ͨ��ң����ȡ����ʾ�Ľ��� -----------------------*/

/*
���ܣ���ʾ�û����ܹۿ���Ŀ����ʾ��Ϣ����������������Ӧʹ�á�
������	
	byMesageNo:				Ҫ��ʾ����Ϣ��š�
--*/
void   DVTSTBSTC_ShowPromptMessage(BYTE byMesageNo);
void   DVTSTBSTC_HidePromptMessage(void);

/*
���ܣ�CAģ���ô˺���֪ͨ�����а�CAǰ�˵ķ��͵�OSD���ȼ���0~3�������������ʾ��ͨ����ҪOSD����ҪOSD�ô�������������ɫ��ʾ��������ͬ����ʾ��Ҳ�������첽��ʾ��
����:	
	byPriority:	OSD���ȼ���0~3�����ȼ�������
	szOSD:		������ʾ��OSD��Ϣ��
˵����
	�û�����ͨ��ң����ȡ����ǰOSD��ʾ��
--*/
void	DVTSTBSTC_ShowOSDMsg(BYTE byPriority,const char * szOSD);

/*--------------------------- Ӧ���㲥 -----------------------*/
/*++
���ܣ�Ӧ���㲥, �л���ָ��Ƶ����
������
	wOriNetID:				ԭʼ����ID��
	wTSID:					������ID��
	wServiceID:				ҵ��ID��
	wDuration:				����������
--*/
void DVTSTBSTC_UrgencyBroadcast(WORD wOriNetID, WORD wTSID, WORD wServiceID, WORD wDuration);

/*++
���ܣ�ȡ��Ӧ���㲥���л���Ӧ���㲥ǰ�û��ۿ���Ƶ����
�������ޡ�
--*/
void DVTSTBSTC_CancelUrgencyBroadcast( void );

/*++
����:��ȡоƬ��CPUID��
����:
	pbyChipID:		оƬ�ṩ��ChipID�����8���ֽ�
	pbyChipIDLen:	ChipIDʵ�ʳ���
����ֵ:
	true:			��ȡChipID�ɹ�
	false:			��ȡChipIDʧ��
--*/
bool DVTSTBSTC_GetChipID(BYTE * pbyChipID,BYTE * pbyChipIDLen);

/*++
����:��ȡPSI���е�̨վ�ţ�����̨վ��������
����:
	pdwData:	�������ṩ�ģ���Station���л�ȡ��PDSDֵ
����ֵ:
	0:		��ȡ�ɹ�
	����ֵ:	��ȡʧ��
	
ʹ��˵��:
	�����ʵ��Station�����������ܣ��˺�������-1��(*pdwData)��Ϊ0����
--*/
HRESULT	DVTSTBSTC_GetStationValue(DWORD * pdwData);

/*
���ܣ�֪ͨSTB����ָ�ơ�
--*/
void DVTSTBSTC_HideFingerPrint (void);
/*
���ܣ�֪ͨSTB���ַ���ʽ��ʾָ�ơ�
--*/
void DVTSTBSTC_ShowCharaterFingerPrint(const SDVTSTCCharaterFingerMsg *pCharaterFingerMsg);

/*
���ܣ�֪ͨSTB�������ʽ��ʾָ�ơ�
--*/
void DVTSTBSTC_ShowDotMatrixFingerPrint(const SDVTSTCDotMatrixFingerMsg *pDotMatrixFingerMsg);

/*++
���ܣ���ʾ���ʼ��ı�־��
������
	byShow:					��־���͡��������£�
							DVTSTCS_NEW_EAMIL				���ʼ�֪ͨ��
							DVTSTCS_NEW_EMAIL_NO_ROOM		�����ʼ�����Email�ռ䲻����
							DVTSTCS_EMAIL_NONE				û�����ʼ���
--*/
void DVTSTBSTC_EmailNotify(BYTE byShow);

/*++
���ܣ���Ҫ�ʼ�������ʾ���û�������ң���˳���
������
pEmailMsg:				Ҫ��ʾ�����ݣ���������Ҫ��1500�ֽڿռ�
--*/
void DVTSTBSTC_ShowForceEmailMsg(const SDVTSTCEmailMsg *pEmailMsg );

/*++
���ܣ�ȡ��ǿ����ʾ��Ϣ
������
��
--*/
void DVTSTBSTC_HideForceEmailMsg(void);
/*------------------------------------------���Ͻӿ���STB����STCS����---------------------------------------------------*/

#ifdef  __cplusplus
}
#endif
#endif  
