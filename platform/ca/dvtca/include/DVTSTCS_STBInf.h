//���ļ�����CAģ��ʵ���ṩ��STB���õĽӿ�

#ifndef _DVTSTCS_STBINTERFACE_H_2004_12_31_
#define _DVTSTCS_STBINTERFACE_H_2004_12_31_

#include "DVTSTCS_STBDataPublic.h"

#ifdef  __cplusplus
extern "C" {
#endif 

/*-----------------------------------���½ӿ���STCS�ṩ��STB����----------------------------------*/

/*++
���ܣ�������������ʱ����ã���STCSģ���ʼ����
����ֵ��
	true				��ʼ���ɹ���
	false				��ʼ��ʧ�ܡ�
--*/
bool DVTSTCSTB_Init(void);

/*++
���ܣ������л��STCSID����øýӿ��ж�STCSID�Ƿ���Ч�������Ч�򷵻�true�����򷵻�false��
������
	wCaSystemID:		�����з���SI/PSI��Ϣ��õ�STCSID��
����ֵ��
	true				STCSID��Ч
	false				STCSID��Ч
--*/
bool DVTSTCSTB_STCSIDVerify(WORD wCaSystemID);

/*++
���ܣ����õ�ǰ�����տ��Ľ�Ŀ����ϸ��Ϣ��
������
	pServiceInfo:		SDVTSTCServiceInfo�ṹ��������Ŀ����ϸ��Ϣ��
˵����
	���û���Ƶ��ʱ�������б���Ҫ���ô˺����������ǰƵ��Ϊ�����ŵ�Ƶ������������m_wEcmPid��Ϊ0��
--*/
void DVTSTCSTB_SetCurEcmInfo(const SDVTSTCServiceInfo * pServiceInfo);

/*++
���ܣ�����EMMPID��STCSģ�齫�������õ�EMMPID��Ϣ����EMM���ݽ��մ���
������
	wEmmPid:			CAT���а�����descriptor�н���CA_system_ID��CA_PID������DVTSTCSTB_STCSIDVerify()У����Ч��CA_PID��ΪEMM PID��
˵��:
	���������յ�CAT��󣬻�������Ҫ���ô˺�������EMM PID��������
--*/
void DVTSTCSTB_SetEmmPid(WORD wEmmPid);

/*++
���ܣ����������������յ�STCS˽�����ݻ���Time_Out����������ӿڽ������ṩ��STCSģ�鴦��
������
	byReqID��				��ǰ������ȡ˽�б������ţ���DVTSTBSTC_SetStreamGuardFilter���byReqID��Ӧ
	bSuccess��				��ȡ������û�гɹ����ɹ�Ϊtrue��ʧ��Ϊfalse
	wPID:					���յ����ݵ�����PID��
	byszReceiveData��		��ȡ��˽������
	wLen��					��ȡ����˽�����ݵĳ���
--*/
void DVTSTCSTB_StreamGuardDataGot(BYTE byReqID, bool bSuccess, WORD wPID, WORD wLen, const BYTE * byszReceiveData);

/*++
���ܣ����STCS��Ӧ����Ϣ��
������
	pManu					ָ�򱣴淵����Ϣ�������ַ��
����ֵ��
	DVTSTC_OK				�ɹ�
	����					ʧ��
--*/
HRESULT DVTSTCSTB_GetStreamGuardManuInfo(SDVTSTCManuInfo * pManu);

/*++
���ܣ����STCS��Ӫ����Ϣ��
������
	wTVSID:					STCS��Ӫ�̵�ID  ����ǣ�1 �򷵻����е���Ӫ����Ϣ
	pOperatorInfo:			ָ�򱣴淵����Ϣ�������ַ
	pbyCount:				��������������ĳ��ȣ�����ʱ��ʵ�ʷ�����Ӫ����Ϣ�ĸ���
����ֵ��
	DVTSTC_OK				�ɹ�
	����					ʧ��
--*/
HRESULT DVTSTCSTB_GetOperatorInfo(WORD wTVSID, BYTE * pbyCount, SDVTSTCTvsInfo * pOperatorInfo);

/*++
���ܣ������ͨ��Ȩ��Ŀ���������������ڻ����н�������ʾ��
������
	wTVSID:					��Ӫ�̵��ڲ���š�
	pEntitleCount:			����ʱΪ����������������ʱΪʵ�ʻ�õĸ�����
	psEntitles:				���ص���Ȩ���顣						
����ֵ��
	DVTSTC_OK					�ɹ�
	DVTSTCERR_STB_TVS_NOT_FOUND	û���ҵ�����Ҫ�����Ӫ��
	����						ʧ��
--*/
HRESULT DVTSTCSTB_GetServiceEntitles(WORD wTVSID, BYTE * pEntitleCount, SDVTSTCServiceEntitle * psEntitles);

/*++
���ܣ��򿪻�رյ�����Ϣ��
������
	bDebugMsgSign:			�򿪵�����Ϣ��־��1:�򿪵�����Ϣ;0:�رյ�����Ϣ��
--*/
void DVTSTCSTB_AddDebugMsgSign(bool bDebugMsgSign);

/*
���ܣ���������ʾ��һ��OSD��Ϣ��������ӿ���֪ͨCAģ�顣
����:	
	wDuration:				��Ϣ��ʾ�ľ���ʱ�䣬��λΪ�롣
--*/
void DVTSTCSTB_ShowOSDMsgOver(WORD wDuration);

/*++
����:�����л�ȡE-mail�����ӿڡ�
����:
	*pEmailCount:			��������E-mail�ܸ�����
	*pNewEmailCount:		��������δ������E-mail������
����ֵ��
	DVTSTC_OK				�ɹ�
	����					ʧ��
--*/
HRESULT DVTSTCSTB_GetEmailCount(WORD * pEmailCount, WORD * pNewEmailCount);

/*++
����:�����л�ȡ���E-mail��Ҫ��Ϣ�ӿڡ�
����:
	*pEmailCount:			����ʱΪ�����ܸ��������ʱΪ��������E-mail�ܸ�����
	*pEmail:				��ȡ��E-mail���顣
����ֵ:
	DVTSTC_OK:				��ȡE-mail�ɹ���
	DVTSTCERR_STB_EMAILBOX_EMPTY:	E-mail����Ϊ�ա�
--*/
HRESULT DVTSTCSTB_GetEmailHead(WORD * pEmailCount, SDVTSTCEmailInfo * pEmail);

/*++
����:�����л�ȡһ��E-mail�����ݡ�
����:
	tVersion:				E-mail�汾��
	*pEmail:				��ȡ��E-mail�ṹ��
����ֵ:
	DVTSTC_OK:				��ȡE-mail�ɹ���
	DVTSTCERR_STB_NO_EMAIL:	û�д�E-mail��
--*/
HRESULT DVTSTCSTB_GetEmailContent(DWORD tVersion, SDVTSTCEmailContent * pEmail);

/*++
����:�����п���E-mail��֪ͨSTCS�Ľӿڡ�
����:
	tVersion:				E-mail�汾��
����ֵ:
	DVTSTC_OK:				����E-mailΪ�Ѷ��ɹ���
	����					ʧ��
--*/
HRESULT DVTSTCSTB_EmailRead(DWORD tVersion);

/*++
����:������ɾ��E-mail�ӿڡ�
����:
	tVersion:				E-mail�汾�����Ϊ-1����ʾɾ������������email������Ϊ�����id��
����ֵ:
	DVTSTC_OK:				ɾ��E-mail�ɹ���
	DVTSTCERR_STB_NO_EMAIL:	Ҫɾ����E-mail�����ڡ�
	����					ʧ��
--*/
HRESULT DVTSTCSTB_DelEmail(DWORD tVersion);

/*
����: ��ȡ������Ϣ
����:
	psStationInfo				������Ϣ
����ֵ:
	0:						�ɹ�
	����ֵ:					ʧ��
*/	
HRESULT DVTSTCSTB_GetStationInfo(SDVTCAStationInfo * psStationInfo);

/*++
���ܣ������л������ͼƬ����øýӿڴ���ͼƬ��CRC32�ж�ͼƬ�Ƿ�Ϸ�������Ϸ��򷵻�true�����򷵻�false��
������
	 dwPicCRC32		ͼƬ��CRC32
����ֵ��
	true				����ͼƬ�Ϸ�
	false				����ͼƬ�Ƿ�
--*/
bool DVTCASTB_PICVerify(DWORD dwPicCRC32);
/*----------------------------------���Ͻӿ���STCS�ṩ��STB����--------------------------------------------*/




/*----------------------------------���½ӿ��ݲ�ʵ�֣�ֱ�ӷ��سɹ�����--------------------------------------------*/

/*++
���ܣ��ж����ܿ���PIN��
������
	pPin:					PIN��
����ֵ��
	DVTSTC_OK          				�ɹ�
	DVTSTCERR_STB_PIN_INVALID		����PIN�����
	DVTSTCERR_STB_PIN_LOCKED			PIN������
--*/
HRESULT DVTSTCSTB_VerifyPin(const SDVTSTCPin * pPIN);

/*++
���ܣ��жϿ��Ƿ���ס��
������
	pbLocked:				���������true��ʾ��ס�ˣ�false��ʾû�С�
����ֵ��
	DVTSTC_OK				�ɹ�
	����					ʧ��
--*/
HRESULT DVTSTCSTB_IsPinLocked(bool * pbLocked);

/*
���ܣ��ж��û��Ƿ�ͨ��pin����֤��
������
	pbPass:				���ʱtrue��ʾͨ�����ˣ�false����ʾû�С�
*/
HRESULT DVTSTCSTB_IsPinPass(bool * pbPass);

/*++
���ܣ��޸����ܿ���PIN�롣
������
	pNewPin:				�µ�PIN�롣	
����ֵ��
	DVTSTC_OK          				�ɹ�
	DVTSTCERR_STB_PIN_LOCKED			PIN������
˵��:
	���øú���֮ǰҪ��ȷ�����ù�VerifyPin�����ҳɹ���
--*/
HRESULT DVTSTCSTB_ChangePin(const SDVTSTCPin * pNewPin);

/*++
���ܣ�������ܿ�Ŀǰ��߹ۿ�����
������
	pbyRating:				����ۿ�����
����ֵ��
	DVTSTC_OK				�ɹ�
	����					ʧ��
˵��:
	�ۿ�����Ϊ3~18����15������ʼֵΪ18�������Թۿ����м���Ľ�Ŀ��
--*/
HRESULT DVTSTCSTB_GetRating(BYTE * pbyRating);

/*++
���ܣ��������ܿ��ۿ�����
������
	byRating:				Ҫ���õ��µĹۿ�����
����ֵ��
	DVTSTC_OK				�ɹ�
	����					ʧ��
˵��:
	���øú���֮ǰҪ��ȷ�����ù�VerifyPin�����ҳɹ���
--*/
HRESULT DVTSTCSTB_SetRating(BYTE byRating);

/*++
���ܣ�������ܿ���ǰ���õĹ���ʱ��Ρ�
˵��������ʱ�ι���Ĭ�Ϲرգ���ʱ�����Ĺ���ʱ��ʼ����Ĭ��ֵ00:00-23:59���ַ���Ҫʱ��������ǰ�˿�����
������
	pbyStartHour			��ʼ������Сʱ
	pbyStartMinute			��ʼ�����ķ���
	pbyEndHour				����������Сʱ
	pbyEndMinute			���������ķ���
����ֵ��
	DVTSTC_OK				�ɹ�
	����					ʧ��
˵��:
	����ʱ�γ�ʼֵΪ00:00~23:59����ȫ�춼���տ���
--*/
HRESULT DVTSTCSTB_GetWorkTime(BYTE * pbyStartHour, BYTE * pbyStartMinute, BYTE * pbyEndHour, BYTE * pbyEndMinute);

/*++
���ܣ��������ܿ�����ʱ�Ρ�
������
	byStartHour			��ʼ������Сʱ
	byStartMinute			��ʼ�����ķ���
	byEndHour				����������Сʱ
	byEndMinute			���������ķ���
����ֵ��
	DVTSTC_OK				�ɹ�
	����					ʧ��
˵��:
	���øú���֮ǰҪ��ȷ�����ù�VerifyPin�����ҳɹ���
--*/
HRESULT DVTSTCSTB_SetWorkTime(BYTE byStartHour, BYTE byStartMinute, BYTE byEndHour, BYTE byEndMinute);

/*
����:��ȡ�û��Զ�������
����:
	byType					�Զ�����������
	pdwUserDefData			�û��Զ������ݵ�DWORD����ָ��
����ֵ:
	0:						�ɹ�
	����ֵ:					ʧ��
*/
HRESULT DVTSTCSTB_GetUserDefData(BYTE byType, DWORD *pdwUserDefData);

/*
����:�л���ʾ���ԣ�������CAģ���ʼ�������
����:
	byLanguage               ��������DVTSTC_LANG_CHN_SIMΪ��������(Ĭ��) 	DVTSTC_LANG_ENGΪӢ��
*/
void DVTSTCSTB_ChangeLanguage(BYTE byLanguage);
#ifdef  __cplusplus
}
#endif
#endif  

