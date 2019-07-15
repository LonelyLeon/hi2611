//���ļ�����Ҫ�������ʵ�ֲ��ṩ��CAģ��ʹ�õĽӿڡ�����HRESULT����ֵΪDVTCA_OK����ʾ�ɹ�������ֵ��ʾʧ�ܡ�

#ifndef _DVTSTB_CASINTERFACE_H_2004_12_31_
#define _DVTSTB_CASINTERFACE_H_2004_12_31_

#include "DVTCAS_STBDataPublic.h"

#ifdef  __cplusplus
extern "C" {
#endif 

/*----------------------------------���½ӿ���STB�ṩ��CAS����--------------------------------------------*/
#if (defined(DVTCA_BASE) || defined(DVTCA_SECURITY))
/*++
���ܣ��������ܿ���
--*/
HRESULT DVTSTBCA_SCReset(void);
#endif
/*++
���ܣ���û����з����CAS��flash�ռ������ַ�ʹ�С�����ֽ�Ϊ��λ����
������
	ppStartAddr:			�����з����CAS��flash�ռ�Ŀ�ʼ��ַ��
	lSize:					��������з����CAS��flash�ռ�Ĵ�С��
--*/
HRESULT DVTSTBCA_GetDataBufferAddr(long * lSize, char ** ppStartAddr);

/*++
���ܣ���ȡ�����ڻ�����flash�е���Ϣ��
������
	pStartAddr:				Ҫ��ȡ�Ĵ洢�ռ�Ŀ�ʼ��ַ��
	plDataLen:				����ΪҪ��ȡ�������ֵ�����Ϊʵ�ʶ�ȡ�Ĵ�С��
	pData:					���������ݡ�
--*/
HRESULT DVTSTBCA_ReadDataBuffer(const char * pStartAddr, long * plDataLen, BYTE * pData);

/*++
���ܣ�������еĴ洢�ռ�д��Ϣ��
������
	lStartAddr:				Ҫд�Ĵ洢�ռ�Ŀ�ʼ��ַ��
	plDataLen:				����ΪҪд�����ݵĳ��ȣ����Ϊд���ʵ�ʳ��ȡ�
	pData:					Ҫд�����ݡ�
--*/
HRESULT DVTSTBCA_WriteDataBuffer(const char * pStartAddr, long * plDataLen, const BYTE * pData);

/*++
���ܣ���ȡ�����ڻ�����eeprom�е���Ϣ��
������
	plDataLen:				����ΪҪ��ȡ�������ֵ�����Ϊʵ�ʶ�ȡ�Ĵ�С��
	pData:					���������ݡ�
--*/
HRESULT DVTSTBCA_GetDataFromEeprom(long * plDataLen, BYTE * pData);

/*++
���ܣ�������е�eeprom�洢�ռ�д��Ϣ��
������
	plDataLen:				����ΪҪд�����ݵĳ��ȣ����Ϊд���ʵ�ʳ��ȡ�
	pData:					Ҫд�����ݡ�
--*/
HRESULT DVTSTBCA_SaveDataToEeprom(long * plDataLen, const BYTE * pData);

/*++
���ܣ�����ǰ�̡߳�
������
	dwMicroseconds:			���롣
--*/
HRESULT DVTSTBCA_Sleep( int dwMicroseconds );

/*++
���ܣ���ʼ���ź���,��ʼ�����ź���û���źš�
������
	pSemaphore:				ָ���ź�����ָ�롣
--*/
HRESULT DVTSTBCA_SemaphoreInit( DVTCA_Semaphore * pSemaphore );

/*++
���ܣ����ź������źš�
������
	pSemaphore: 			ָ���ź�����ָ�롣
--*/
HRESULT DVTSTBCA_SemaphoreSignal( DVTCA_Semaphore * pSemaphore );

/*++
���ܣ��ȴ��ź���,�ȴ��ɹ�֮��,�ź���Ϊ���źš�
������
	pSemaphore: 			ָ���ź�����ָ�롣
--*/
HRESULT DVTSTBCA_SemaphoreWait( DVTCA_Semaphore * pSemaphore );

/*++
���ܣ�CASģ���������ע���̡߳�
������
	szName:					ע����߳����ơ�
	pTaskFun:				Ҫע����̺߳�����
--*/
HRESULT DVTSTBCA_RegisterTask(const char * szName, pThreadFunc pTaskFun);

/*++
���ܣ����ù���������CAS˽�����ݡ�
������
	byReqID:				�����ձ������š�������Ӧ�ñ�������ݣ����յ�CAS˽�����ݺ����DVTCASTB_StreamGuardDataGot()ʱӦ�ý������ݷ��ء�
	wEcmPID:				��Ҫ���˵�����PID��
	szFilter:				��������ֵ��Ϊһ��8���ֽڵ����顣
	szMask:					�����������룬Ϊһ��8���ֽڵ����飬���������Ӧ����szMask��ĳһbitλΪ0ʱ��ʾҪ���˵ı��Ӧ��bitλ����Ҫ��szFilter���Ӧ��bitλ��ͬ����szMaskĳһλΪ1ʱ��ʾҪ���˵ı��Ӧ��bitλһ��Ҫ��szFilter���Ӧ��bitλ��ͬ��
	byLen:					�������ĳ��ȣ�Ϊ8�� (DVTCA_COS_V20ʱ��������8��12)
	nWaitSeconds:			�մ˱���ĵȴ�ʱ�䣬���Ϊ0�����޵ȴ�����λ�롣
--*/
HRESULT DVTSTBCA_SetStreamGuardFilter(BYTE byReqID, WORD wPID, const BYTE * szFilter, const BYTE * szMask, BYTE byLen, int nWaitSeconds);

#if (defined(DVTCA_BASE)|| defined(DVTCA_COS_10) || defined(DVTCA_SECURITY))
#ifndef DVTCA_SECURITYCHIP

/*++
���ܣ�CA�����ô˺������ý�����������ǰ���ڼ���һ���ڵ�CW�͸���������
������
	wEcmPID:				CW������ECMPID��
	szOddKey:				��CW�����ݡ�
	szEvenKey:				żCW�����ݡ�
	byKeyLen:				CW�ĳ��ȡ�
	bTapingControl:			true������¼��,false��������¼��
--*/
HRESULT DVTSTBCA_SetDescrCW(WORD wEcmPID, BYTE byKeyLen, const BYTE * szOddKey, const BYTE * szEvenKey, bool bTapingControl);

#else

/*++
���ܣ�CA�����ô˺������ý�����������ǰ���ڼ���һ���ڵ�CW�͸���������
������
	wEcmPID:				CW������ECMPID��
	szOddKey:				��CW�����ݡ�
	szEvenKey:				żCW�����ݡ�
	byKeyLen:				CW�ĳ��ȡ�
	bTapingControl:			true������¼��,false��������¼��
	byCWEncrypt:			0:CW�����ģ�1:CW�����ģ���Ҫ��ȫоƬ���ܣ�����ֵ:����
--*/
HRESULT DVTSTBCA_SetDescrCW(WORD wEcmPID, BYTE byKeyLen, const BYTE * szOddKey, const BYTE * szEvenKey, bool bTapingControl,BYTE byCWEncrypt);

/*++
����:	���ü���оƬ��CK '
����:

	byszCK:	���ܿ����ص�CK' ��16���ֽ�
	byLen:	CK�ĳ���
����ֵ:
	  0 :				���óɹ�
	����ֵ:				����ʧ��
--*/
HRESULT DVTSTBCA_SetCK(const BYTE * byszCK,BYTE byLen);
#endif
#elif defined(DVTCA_COS_V20)
/*++
���ܣ�CA�����ô˺������������������ø��߰�оƬ��
������
	wEcmPID:				CW������ECMPID��
	byDataLen:				��оƬ�����ݳ��ȡ�
	szData:					�Ϳ�������
	byTapingControl:		0����ֹ¼��;1:ѡ��¼��;2:����¼��;3:������
����ֵ���轫��ʵ��оƬ�ײ�ӿڷ���ֱֵ�ӷ��ظ�CA
--*/
HRESULT DVTSTBCA_SetDescrCW(WORD wEcmPID, BYTE byDataLen, const BYTE * szData, BYTE byTapingControl);
#endif

/*++
���ܣ���ӡ������Ϣ��STB��С����800�ֽڡ�
������
	pszMsg:					������Ϣ���ݡ�
--*/
void DVTSTBCA_AddDebugMsg(const char * pszMsg);

/*++
���ܣ�ʵ�������ܿ�֮���ͨѶ������7816��׼��
������
	byReaderNo:				��Ӧ�Ķ�������š�
	pbyLen:					����Ϊ�����������ֽڵĳ���;���Ϊ�����ֽڳ��ȡ�
	byszCommand:			�����͵�һ�������ֽڡ�
	szReply:				���ص����ݣ��ռ䳤�Ⱥ�Ϊ256�ֽڡ�
--*/
HRESULT DVTSTBCA_SCAPDU(BYTE byReaderNo, BYTE * pbyLen, const BYTE * byszCommand, BYTE * byszReply);

/*--------------------------- ����1�Ľ��棺�������û�ͨ��ң����ȡ����ʾ�Ľ��� -----------------------*/

/*
���ܣ���ʾ�û����ܹۿ���Ŀ����ʾ��Ϣ����������������Ӧʹ�á�
������	
	byMesageNo:				Ҫ��ʾ����Ϣ��š�
--*/
void   DVTSTBCA_ShowPromptMessage(BYTE byMesageNo);
void   DVTSTBCA_HidePromptMessage(void);

#if (defined(DVTCA_BASE))
/*
���ܣ���ʾָ����Ϣ��
������
	dwCardID:				���š�
	wDuration:				����������
--*/
void	DVTSTBCA_ShowFingerPrinting(DWORD dwCardID, WORD wDuration);
#endif
#if (defined(DVTCA_SECURITY) || defined(DVTCA_COS_10) || defined(DVTCA_COS_20))
/*
���ܣ�֪ͨSTB����ָ�ơ�
--*/
void DVTSTBCA_HideFingerPrint (void);
/*
���ܣ�֪ͨSTB���ַ���ʽ��ʾָ�ơ�
--*/
void DVTSTBCA_ShowCharaterFingerPrint(const SDVTCACharaterFingerMsg *pCharaterFingerMsg);

/*
���ܣ�֪ͨSTB�������ʽ��ʾָ�ơ�
--*/
void DVTSTBCA_ShowDotMatrixFingerPrint(const SDVTCADotMatrixFingerMsg *pDotMatrixFingerMsg);
#endif
/*
���ܣ�CAģ���ô˺���֪ͨ�����а�CAǰ�˵ķ��͵�OSD���ȼ���0~3�������������ʾ��ͨ����ҪOSD����ҪOSD�ô�������������ɫ��ʾ��������ͬ����ʾ��Ҳ�������첽��ʾ��
����:	
	byPriority:	OSD���ȼ���0~3�����ȼ�������
	szOSD:		������ʾ��OSD��Ϣ��
˵����
	�û�����ͨ��ң����ȡ����ǰOSD��ʾ��
--*/
void	DVTSTBCA_ShowOSDMsg(BYTE byPriority,const char * szOSD);

/*--------------------------- ����2�Ľ��棺�û�����ȡ����ʾ�Ľ��� -----------------------*/
/*++
���ܣ���ʾ���ʼ��ı�־��
������
	byShow:					��־���͡��������£�
							DVTCAS_NEW_EAMIL				���ʼ�֪ͨ��
							DVTCAS_NEW_EMAIL_NO_ROOM		�����ʼ�����Email�ռ䲻����
							DVTCAS_EMAIL_NONE				û�����ʼ���
--*/
void DVTSTBCA_EmailNotify(BYTE byShow);
#if (defined(DVTCA_BASE))
/*++
���ܣ���Ҫ�ʼ�������ʾ���û�����ң���˳���
������
	pEmailMsg:				Ҫ��ʾ�����ݣ���������Ҫ��1500�ֽڿռ�
--*/
void DVTSTBCA_ShowEmailMsg(const SDVTCAEmailMsg *pEmailMsg );
#endif

/*--------------------------- Ӧ���㲥 -----------------------*/
/*++
���ܣ�Ӧ���㲥, �л���ָ��Ƶ����
������
	wOriNetID:				ԭʼ����ID��
	wTSID:					������ID��
	wServiceID:				ҵ��ID��
	wDuration:				����������
--*/
void DVTSTBCA_UrgencyBroadcast(WORD wOriNetID, WORD wTSID, WORD wServiceID, WORD wDuration);

/*++
���ܣ�ȡ��Ӧ���㲥���л���Ӧ���㲥ǰ�û��ۿ���Ƶ����
�������ޡ�
--*/
void DVTSTBCA_CancelUrgencyBroadcast( void );
#if (defined(DVTCA_COS_10) || defined(DVTCA_COS_20))
/*++
����:��ȡоƬ��CPUID��
����:
	pbyChipID:		оƬ�ṩ��ChipID�����8���ֽ�
	pbyChipIDLen:	ChipIDʵ�ʳ���
����ֵ:
	true:			��ȡChipID�ɹ�
	false:			��ȡChipIDʧ��
--*/
bool DVTSTBCA_GetChipID(BYTE * pbyChipID,BYTE * pbyChipIDLen);

/*++
����:	���ü���оƬ��K1'
����:

	byszCK:	K1��16���ֽ�
	byLen:	K1�ĳ���
����ֵ:
	  0 :				���óɹ�
	����ֵ:				����ʧ��
--*/
HRESULT DVTSTBCA_SetK1(const BYTE * byszK1,BYTE byLen);

/*++
����:	���ü���оƬ��K2'
����:

	byszCK:	���ܿ����ص�K2' ��16���ֽ�
	byLen:	K2�ĳ���
����ֵ:
	  0 :				���óɹ�
	����ֵ:				����ʧ��
--*/
HRESULT DVTSTBCA_SetK2(const BYTE * byszK2,BYTE byLen);
#endif
#if (defined(DVTCA_BASE) || defined(DVTCA_SECURITY))
/*--------------------------- IPPV/IPPT -----------------------*/
/*++
���ܣ�������ѯ���û��Ƿ�Ԥ����ǰIPP��Ŀ��
������
	wEcmPid:				IPP��Ӧ��EcmPID
	pIpp:					��ǰIPP����Ϣ��
--*/
void DVTSTBCA_InquireBookIpp(WORD wEcmPid, const SDVTCAIpp * pIpp );

/*++
���ܣ�֪ͨ��������Ҫ����������Ƶ�������������������(��Ƶ����������ʹ��)
������
	wWaitSeconds:			��ʱʱ�䣬��λ�롣
����ֵ��
	DVTCA_OK				�ɹ�
	����					ʧ��
--*/
HRESULT DVTSTBCA_SwitchChannel(WORD wWaitSeconds);

/*++
���ܣ�֪ͨ����������������������������ϡ�(��Ƶ����������ʹ��)
--*/
void DVTSTBCA_AreaLockOk(void);

/*++
���ܣ���ȡ����������汾��
����ֵ������������汾�š�
--*/
DWORD DVTSTBCA_GetSoftVer(void);

#ifndef DVTCA_SECURITYCHIP

/*++
����:��ȡоƬ��CPUID��
����:
	pbyCPUID:	оƬ�ṩ��CPUID�����20���ֽ�
����ֵ:
	0:		��ȡCPUID�ɹ�
	����ֵ:	��ȡCPUIDʧ��
--*/
HRESULT DVTSTBCA_GetCPUID(BYTE * pbyCPUID);

#else

/*++
����:��ȡоƬ��CPUID��
����:
	pbyCPUID:	оƬ�ṩ��CPUID��4���ֽ�
	pLen:		����ΪCPUDID����󳤶�;���ΪCPUID��ʵ�ʳ���
����ֵ:
	0:		��ȡCPUID�ɹ�
	����ֵ:	��ȡCPUIDʧ��
--*/
HRESULT DVTSTBCA_GetCPUID(BYTE * pbyCPUID,BYTE *pLen);

#endif

/*++
����:��ȡNIT���е�PDSDֵ������NIT������������
����:
	pdwData:	�������ṩ�ģ���NIT���л�ȡ��PDSDֵ
����ֵ:
	0:		��ȡ�ɹ�
	����ֵ:	��ȡʧ��
	
ʹ��˵��:
	�����ʵ��NIT�����������ܣ��˺�������-1��(*pdwData)��Ϊ0����
--*/
HRESULT	DVTSTBCA_GetNitValue(DWORD * pdwData);

/*++
���ܣ���Ҫ�ʼ�������ʾ���û�������ң���˳���
������
pEmailMsg:				Ҫ��ʾ�����ݣ���������Ҫ��1500�ֽڿռ�
--*/
void DVTSTBCA_ShowForceEmailMsg(const SDVTCAEmailMsg *pEmailMsg );

/*++
���ܣ�ȡ��ǿ����ʾ��Ϣ
������
��
--*/
void DVTSTBCA_HideForceEmailMsg(void);

/*++
���ܣ���ȡ���������кţ���Ҫ�����к�ת��Ϊ��Ӧ��ASCII��ֵ
������
		pbySTBSerial:	 ���������к�,��󳤶�Ϊ20�ֽ�
		pLen:		     ���������кŵ�ʵ�ʳ���
����ֵ��0���ɹ�����0��ʧ�ܣ�
--*/
HRESULT DVTSTBCA_GetSTBSerial (BYTE * pbySTBSerial,BYTE *pLen);

/*++
����:ʵ���ڴ濽��(���ST71ƽ̨�����Դ������Ŀ�������ص���
						   ���ܵ����ڴ濽��������Ҫ���¶���)��
����ֵ:
	pDest:Ŀ���ַ
	pSrc:  Դ��ַ
	iSize:  ��С
--*/
HRESULT DVTSTBCA_Memcpy(void  * pDest, const void * pSrc,  unsigned int iSize);

/*------------------------------------------���Ͻӿ���STB����CAS����---------------------------------------------------*/

#ifdef  __cplusplus
}
#endif
#endif  
#endif
