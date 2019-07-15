#ifndef _GOSCAS_STBINF_H
#define _GOSCAS_STBINF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "GOSCAS_STBDataPublic.h"

//һ���ĸ��ӿ���Ϊ��ά���ϵļ��ɽ��鲻���ã������µĽӿ�extern HRESULT GOSCASTB_MasterSlave_PareProcess( Master_Pare_Slave process) ;
extern HRESULT GOSCASTB_GetCardMontherSonInfo(SGOSCAMontherSonInfo *MontherSonInfo);
extern HRESULT GOSCASTB_SetCardSonInfo(SGOSCAMontherSonInfo *MontherSonInfo);
extern HRESULT GOSCASTB_IsMotherCard( ) ;
extern HRESULT GOSCASTB_MotherSon_Pair( ) ;



/*-----------------------------------���½ӿ���CAS�ṩ��STB����----------------------------------*/
/*
��ע����2.02�汾��ʼ�����ֽӿں����������������޸ģ����ֱ���滻������к���δ���������鿴���к������������
GOSSYS_GetSerNo()						�� GOSCASTB_GetSerNo()
GOSSYS_CasSysTime_Get()					�� GOSCASTB_GetCasSysTime()
GOSCASTB_GetVer()						�� GOSCASTB_GetCASVer()
GOSCA_ISSystemID()						�� GOSCASTB_ISSystemID()
GOSSTBCA_SetForceOSDStatusEnd() 		�� GOSCASTB_SetForceOSDStatusEnd()
GOSSTBCA_GetSTB_BindSerID() 			�� GOSCASTB_GetSTB_BindSerID()

GOSSYS_Parent_PassWord_Get() 			�� GOSCASTB_Parent_PassWord_Get()
GOSSYS_Parent_PassWord_Check() 			�� GOSCASTB_Parent_PassWord_Check()
GOSSYS_Parent_PassWord_Set() 			�� GOSCASTB_Parent_PassWord_Set()
GOSSYS_Parent_PassWord_Reset() 			�� GOSCASTB_Parent_PassWord_Reset()
extern void GOSCASTB_PVR_Process(void) ;�Ѿ�ȥ��������GOSCASTB_PVR_SetRunState������ִ��

*/
/*++

���ܣ�
�����е��øýӿڿ��ƿ���Ϣ�Ĵ�ӡ����

������bDebugMsgSign
1����ʾ�򿪿�Ĵ�ӡ������0���رտ���

����ֵ��
��
--*/
extern void GOSCASTB_AddDebugMsgSign(bool bDebugMsgSign) ;

/*++

���ܣ�
���ӿ���Խӿں�����ͨ������ĸ����Խӿں�����

������
��

����ֵ��
0 ��ʾ��ǰ�Ĵ�������OK!������ʾ������룬��ϸ�����������ʵ��������
--*/
extern HRESULT GOSCASTB_MasterSlave_PareProcess( Master_Pare_Slave process) ;

/*++

���ܣ�
������������ʱ����ã���CASģ���ʼ��

������
byReaderNo��StreamGuard���������ܿ��������ţ�һ������0

����ֵ��
true     ��ʼ���ɹ�
false    ��ʼ��ʧ��
--*/
extern bool GOSCASTB_Init(unsigned char byReaderNo) ;

#if (defined(GOSCA_V208))
/*++

���ܣ�
�����д�CAS���л�ȡ��Ի���

������
��

����ֵ��
�ĸ��ֽڵĻ��š��������0xFFFFFFFF����ʾ�û�����δ���г�ʼ��
--*/
extern unsigned long GOSCASTB_GetSerNo(void);
#elif (defined(GOSCA_V109))
/*++

���ܣ�
�����л�ȡ������Ժ�Ļ���

������
��

����ֵ��
�ĸ��ֽڵĻ��š����û�н��й�������ԡ�����0xFFFFFFFF
--*/
extern unsigned long GOSSYS_GetSerNo(void);
#endif
/*++

���ܣ�
�����л�ȡ��������Ϣ

������
*pCardWorkInfo:    ��ȡ�ṹ��SCardWorkInfo��Ϣ

����ֵ�� ==0 �ɹ�
!=0 ʧ��
˵����
pCardWorkInfo->bCardPinStatus <= 1 PINδ������>4PIN��������
pCardWorkInfo->bWatchRating   ʵ�ʵ�������ʾ��Ҫ��3
pCardWorkInfo->bMatureDays ������ʾ���������ò���(1-18�죩��
pCardWorkInfo->tStarttime
pCardWorkInfo->tEndtime
pCardWorkInfo->m_bIPPTWorkMode��0������ʹ�ã�1����̨ѡ��ʹ�ã��ù��ܲ���ʵ�֣�2����ʾʹ�ã�3����Զʹ�ã�
pCardWorkInfo->m_bReserved0
pCardWorkInfo->m_bReserved1
--*/
extern HRESULT GOSCASTB_GetCardWorkInfo(SCardWorkInfo* pCardWorkInfo);
/*++

���ܣ�
���������ÿ�������Ϣ

������
*pCardWorkInfo:    ���ýṹ��SCardWorkInfo��Ϣ�������ĳ���ṹ�������������
��Ҫ�ȶ����ýṹ����������޸���Ҫ���õĽṹ�������

����ֵ�� ==0 �ɹ�
!=0 ʧ��
˵����
ͬ��
--*/
extern HRESULT GOSCASTB_SetCardWorkInfo(SCardWorkInfo* pCardWorkInfo);

/*++

���ܣ�
OSD�Ĺ��������֡���������

������
��

����ֵ��
--*/
extern void GOSCASTB_ShowOSDMsgOver(signed short wDuration);

/*++

���ܣ�
ָ����ʾ�����øýӿڣ�

������
��

����ֵ��
--*/
extern void GOSCASTB_ShowFingerOver(unsigned long version);

#if (defined(GOSCA_V208))
/*++

���ܣ�
�������ĻͼƬ������棬��Ҫ������ǰ��CAǿ��OSD��Ҫ���ýӿڣ�

������
osd_Id��ǿ��OSD��ID

����ֵ��
--*/
extern void GOSCASTB_SetForceOSDStatusEnd(unsigned long osd_Id);

/*++

���ܣ�
�����л�ȡCAS��İ汾��

������
pdwVer:    �汾���ַ����������T���ǲ��԰汾
plen:		�ַ�����������С��ͨ����40B
����ֵ��
true	�ɹ�
false   ʧ��
˵����
����CAģ��İ汾��
����:Goscas_Ver:2.08T1
--*/
extern bool GOSCASTB_GetCASVer(char *pdwVer, unsigned short *plen) ;
#elif (defined(GOSCA_V109))
/*++

���ܣ�
�����л�ȡCAS��İ汾��

������
pdwVer:    ���ذ汾��

����ֵ��
true	�ɹ�
false   ʧ��
˵����
����CAģ��İ汾��
���������0x00000104��˼����0.00.01.04
--*/
extern bool GOSCASTB_GetVer(long *pdwVer) ;
#endif
/*++

���ܣ�
�����л�ȡCAS��ķ�����ID�ͷ�������

������
pid:    ����ID
pTime	�ⷢ������
����ֵ��
true	�ɹ�
false   ʧ��
˵����
����CA����Ϣ
pid = 0x00100 MSTAR
pTime = 0x20120514
--*/
extern bool GOSCASTB_GetCASLibInfo(unsigned long *pid, unsigned long *pTime) ;

/*++

���ܣ�
����CASģ�飬������ܿ��ڲ�ID��

������
*pID:    �������ܿ��š�
*pSoftVer ���ؿ�������汾��
���������0x32��˼����3.2

����ֵ��
true	�ɹ�
false   ʧ��
˵����

--*/
extern bool GOSCASTB_GetCardInfo(unsigned long* pID, unsigned char* pSoftVer) ;

#if (defined(GOSCA_V208))
/*++
���ܣ�
�����л��CASID����øýӿ��ж�CASID�Ƿ���Ч�������Ч�򷵻�true�����򷵻�false

������
wCaSystemID:		�����з���SI/PSI��Ϣ��õ�CASID

����ֵ��
true  (1)   CASID��Ч
false (0)   CASID��Ч
--*/
extern bool GOSCASTB_ISSystemID(const unsigned int wCaSystemID) ;

/*++
���ܣ�
���û��忨ʱ��������������ã�֪ͨCASģ��

������
pAtr:		����λ�󷵻ص�ATR����
atr_size��	ATR���ݵĴ�С��ͨ����4B)

����ֵ��
���ĳЩ�����������ȡ���������������Դ����ָ�룬atr_size = 0
--*/
extern unsigned char GOSCASTB_SCInsert(unsigned char *pAtr, unsigned short atr_size);
#elif (defined(GOSCA_V109))
/*++
���ܣ�
�����л��CASID����øýӿ��ж�CASID�Ƿ���Ч�������Ч�򷵻�true�����򷵻�false

������
wCaSystemID:		�����з���SI/PSI��Ϣ��õ�CASID

����ֵ��
true  (1)   CASID��Ч
false (0)   CASID��Ч
--*/
extern bool GOSCA_ISSystemID(const unsigned int wCaSystemID) ;

/*++
���ܣ�
���û��忨ʱ��������������ã�֪ͨCASģ��

������
byReaderNo:		�������ı��

����ֵ��
--*/
extern unsigned char GOSCASTB_SCInsert(void);
#endif
/*++
���ܣ�
��ȡCAS��ģ�����濨��״̬��ʶ����������˿���״̬
��Ȼ��GOSCAS_SC_OUT����Ҫ�Կ���λ����ִ��һ�²��
��������

������
*pState == GOSCAS_SC_OUT �������ؿ�ͨ�Ų����á�
*pState == GOSCAS_SC_IN  �������ؿ�ͨ��������
*pState == GOSCAS_SC_IN_ERROR  �������ؿ�ͨ�Ų�������

����ֵ��
--*/
extern void GOSCASTB_SCGetState( unsigned char* pState );

/*++

���ܣ�
���û��γ����ܿ�ʱ��������������ã�֪ͨCASģ��

������
����ֵ��
--*/
extern void GOSCASTB_SCRemove(void) ;

/*++
���ܣ�
	�û�ת��Ƶ����ʱ������������
	���õ�ǰ�����տ��Ľ�Ŀ����ϸ��Ϣ
������
pServiceInfos��	SGOSCAServiceInfo�ṹ��������Ŀ����ϸ��Ϣ��
	byCount:		EcmPid�ĸ�����Ŀǰֻ֧��byCount=1
ע�⣺�ýӿ���ÿ�λ�̨ǰ�����һ�£�ECM PID = 0x1FFF;��̨�����PMT����Ϣ�����CASID�Ϸ����ٵ���һ��
��ECM PIDΪʵ�ʵ�PID;

����ֵ
˵����
���û���Ƶ��ʱ����������Ҫ����CAS�ṩ�Ĵ˺���������ǰ��Ŀ��ԭʼ��Ϣ��ECM PID���ݸ�CASģ�飬CASģ���
���ݵ�ǰƵ������Ϣ�����뵱ǰƵ����صĲ����������ǰƵ��Ϊ�����ŵ�Ƶ��������Ҫ��ECM��PID��Ϊ0��
--*/
extern void GOSCASTB_SetCurEcmInfos(unsigned char byCount,const SGOSCAServiceInfo* pServiceInfos) ;

/*++

���ܣ�
����EMMPID��CASģ�齫�������õ�EMMPID��Ϣ����EMM���ݽ��մ���
������
pwEmmPids:	CAT���а�����descriptor�н���CA_system_ID��CA_PID������GOSCA_ISSystemID()У����Ч��CA_PID��ΪEMM PID��
nEmmCount��	EmmPid�ĸ�����Ŀǰֻ֧��nEmmCount��1
����ֵ��

˵��:
���������յ�CAT��󣬻�������Ҫ����CA�ṩ�Ĵ˺�������EMM PID������������CA����Ϳ��Ը��ݴ�PID��ȡ
˽�б������û��������Ȩ��Ϊ�û��ṩ��ֵ���񣬵�����EMM��PIDΪ0ʱ��CAģ���ֹͣ��ȡEMM��
--*/
extern void GOSCASTB_SetEmmPids(long nEmmCount,const unsigned short* pwEmmPids) ;

/*++

���ܣ�
���������������յ�CAS˽�����ݻ���Time_Out����������ӿڽ������ṩ��CASģ�鴦��
������
byReqID��			��ǰ������ȡ˽�б������ţ���GOSSTBCA_SetStreamGuardFilter���byReqID��Ӧ
bSuccess��			��ȡ������û�гɹ����ɹ�Ϊtrue��ʧ��Ϊfalse
wPID:				���յ����ݵ�����PID��
byszReceiveData��		��ȡ��˽������
wLen��				��ȡ����˽�����ݵĳ���
����ֵ��
true  (1)   ��Ч
false (0)   ��Ч
˵����
byReqID == GOSCA_STB_ECM_SLOT		����CASģ�������������ECM
byReqID == GOSCA_STB_EMM_Private_SLOT	����CASģ�������������EMM ˽��	
byReqID == GOSCA_STB_EMM_Public_SLOT	����CASģ�������������EMM ����	
byReqID == GOSCA_STB_EMM_Serial_SLOT	����CASģ��Ļ��������к�EMM ˽��	
byReqID == GOSCA_STB_EMM_SerialEx_SLOT	����CASģ��Ļ��������к�EMM ����	

wLen = Section_lenth 		
--*/
extern bool GOSCASTB_StreamGuardDataGet(unsigned char byReqID, bool bSuccess, unsigned short wPID,unsigned short wLen,unsigned char* byszReceiveData) ;

/*++
���ܣ�
�ж����ܿ���PIN��
������
sPin:				PIN��
����ֵ��
GOSSTB_OK          			�ɹ�
GOSCAERR_STB_DATA_LEN_ERROR		PIN�����ݳ��ȴ���
GOSCAERR_STB_PIN_ERR			����PIN�����
GOSCAERR_STB_PIN_LOCKED			PIN������
˵����
HRESULT Check_PinFunc(unsigned char* PINInput_Value){
SGOSPIN  verify_pin;
verify_pin.m_byLen = 3;
verify_pin.m_byszPin[0] = (PINInput_Value[0]<<4) | PINInput_Value[1];
verify_pin.m_byszPin[1] = (PINInput_Value[2]<<4) | PINInput_Value[3];
verify_pin.m_byszPin[2] = (PINInput_Value[4]<<4) | PINInput_Value[5];
if( GOSCASTB_VerifyPin(&verify_pin) != 0 )
{
return -1;
}
return 0;
}			
--*/
extern HRESULT GOSCASTB_VerifyPin(SGOSPIN *p_sPIN) ;

/*++
���ܣ�
	�жϿ��Ƿ���ס��

������
	pbLocked:					- ���ʱtrue��ʾ��ס�ˣ�false����ʾû�С�
						
����ֵ��
	��������ֵ1					- ���ע��

--*/
extern HRESULT GOSCASTB_IsPinLocked(bool * pbLocked) ;

/*++
���ܣ�
�޸����ܿ���PIN��
������
sNewPin:			   �µ�PIN��

����ֵ��
GOSSTB_OK          				�ɹ�
GOSCAERR_STB_PIN_LOCKED			PIN������
GOSCAERR_STB_DATA_LEN_ERROR		PIN�����ݳ��ȴ���

˵��:
���øú���֮ǰҪ��ȷ�����ù�GOSCASTB_VerifyPin()�������ǳɹ��ġ�

--*/
extern HRESULT GOSCASTB_ModifyPin(SGOSPIN *p_sNewPin) ;

/*++
���ܣ�
���CAS��Ӫ����Ϣ
������
pOperation   ָ�򱣴淵����Ϣ�������ַ
˵��:
��Ӫ��ִ���˷�����Ϣͨ��EMM���͸�������Ӧ����Ϣ����ʾ����,��������ݿ���ѡ����ʾ��
if(pOperation->m_dwMotherCardID == 0 )
{
�ÿ���һ��ĸ����
}
else
{
�ÿ���һ���ӿ�����ĸ�����Ǹúţ�
}

pOperation->m_bStandardFlag		��ĸ�����ʧЧ�жϱ�׼
pOperation->m_dwDecryptCWTimes		����CW �Ĵ���
pOperation->m_dwIntervalTime/86400	���ʱ��(��)
pOperation->m_wRunArea			����������Ӫ�ĵط�
pOperation->m_bUserVIPClass		�û��ȼ�
pOperation->m_dwUserArea		���������û�������
pOperation->m_bTVSName			��Ӫ�̵�����
pOperation->m_bTVSOtherInfo		��Ӫ�̵�������Ϣ
--*/
extern HRESULT GOSCASTB_GetOperation(SOperatorInfo *pOperation) ;

/*++

���ܣ�
�����ͨ��Ȩ��Ŀ���������������ڻ����н�������ʾ��

������
wTVSID:							- ��Ӫ�̵��ڲ����,��ʱδ�õ������ܡ�
pEntitleCount					- ����ʱΪ����������������ʱΪʵ�ʻ�õĸ�����
psEntitles:						- ���ص���Ȩ���顣

����ֵ�� ==0 �ɹ�
!=0 ʧ��
˵��:
psEntitles->m_wProductID;				��Ʒ��
psEntitles->m_tStartTime;				��ʼʱ��
psEntitles->m_tEndTime;					����ʱ��

--*/
extern HRESULT GOSCASTB_GetServiceEntitles(unsigned char *pEntitleCount, SGOSCAServiceEntitle_Ex* psEntitles) ;

#if (defined(GOSCA_V208))
/*++

���ܣ�
�����ͨ��Ȩ��Ŀ��������Ҫ��CA2.04���ϰ汾���øýӿڡ�

������
pEntitleCount					���ʱΪʵ�ʻ�õĸ�����

����ֵ�� ==0 �ɹ�
!=0 ʧ��
˵��:
--*/
extern HRESULT GOSCASTB_GetEntitlesSumEx(unsigned int *pEntitleCount) ;

/*++

���ܣ�
�����ͨ��Ȩ��ϸ��Ϣ����Ҫ��CA2.04���ϰ汾���øýӿڡ�

������
m_StartIndex					��Ȩ��Ϣ��ȡ��ʼ������,��0Ϊ��ʼ������
m_Readcount						�ƻ���ȡ������
*pReadedSCount					ʵ�ʶ�ȡ�����ķ���ֵ��
*psEntitles						ʵ�ʶ�ȡ��Ȩ��Ϣ��ӡ���ء�

����ֵ�� ==0 �ɹ�
!=0 ʧ��
˵��:
--*/
extern HRESULT GOSCASTB_GetEntitlesTotalEx(unsigned int m_StartIndex, unsigned int m_Readcount, unsigned int *pReadedSCount, SGOSCAServiceEntitle_Ex_Print* psEntitles) ;
#endif
/*++

���ܣ�
��������Ƶ�㣬������Ƶ��NIT������ID�͸����ӿڣ�ĳЩ�ͻ��ķ������ƻ�ʹ�����Ϲ���

������
NetID:							- ����Ƶ��NIT����ID��
ע�⣺�ö�����Ҫ�ڿ���ʱֻ��һ�Σ�

����ֵ�� ==0 �ɹ�
!=0 ʧ��

--*/
extern HRESULT GOSCASTB_SetNetWorkID(unsigned short  NetID);

#if (defined(GOSCA_V208))
/*++
���ܣ�
	��ȡ�����뿨�յ��İ󶨻���ID��Ϣ��
������
*ptrID��ID���飬�Լ���4���ֽڴճ������������0xFFFFFFFF��ʾ�յ�û�б��󶨡�	
*prtLen = 4����������������ʱ֧��3��Ű󶨡�
����ֵ��
	�ޡ�
--*/
extern HRESULT GOSCASTB_GetSmart_BindSerID(unsigned char*  ptrID, unsigned int *ptrLen );

/*++
���ܣ�
	��ȡ���������յ��İ󶨿���ID��Ϣ��
������
*ptrID��ID���飬�Լ���4���ֽڴճ������������0xFFFFFFFF��ʾ�յ�û�б��󶨡�	
*prtLen = 4����������������ʱ֧��3��Ű󶨡�
����ֵ��
	�ޡ�
--*/
extern HRESULT GOSCASTB_GetSTB_BindSerID( unsigned char *ptrID, unsigned int *prtLen ) ;
#endif
/*++
����:
�����л�ȡE-mail����Ϣ�ӿڡ�
����:
*pEmail_Total:		����ʱΪ�����ܸ��������ʱΪ��������E-mail�ܸ�����
����ֵ�� ==0 �ɹ�
!=0 ʧ��
˵��:

pEmail_Total->m_Email_All;
pEmail_Total->m_Email_New;
pEmail_Total->m_Email_versions[GOSCA_MAX_EMAIL_ID_COUNT].m_state == FREE; NEW ;OLD��ʾ��Ч���������ʼ����Ѷ��ʼ�
pEmail_Total->m_Email_versions[GOSCA_MAX_EMAIL_ID_COUNT].m_version �ʼ��İ汾
--*/
extern HRESULT GOSCASTB_GetEmailTotal(GOSCAEmailTotal *pEmail_Total);

/*++
����:
������ͨ���ʼ��İ汾��ȡ����E-mail�ı������ݡ�
����:
tVersion:			E-mail�汾��
*pEmail:			��ȡ��E-mail�ṹ��
����ֵ�� ==0 �ɹ�
!=0 ʧ��
--*/
extern HRESULT GOSCASTB_GetEmailTitle(unsigned long tVersion, GOSCAEmailHead *pEmail) ;


/*++
����:
������ͨ���ʼ��İ汾��ȡ����E-mail�����ݡ�
����:
tVersion:			E-mail�汾��
*pEmail:			��ȡ��E-mail�ṹ��
����ֵ�� ==0 �ɹ�
!=0 ʧ��
--*/
extern HRESULT GOSCASTB_GetEmailContent(unsigned long tVersion, GOSCAEmailContent *pEmail) ;

/*++
����:
�����п���E-mail��ͨ���ʼ��İ汾֪ͨCAS�Ľӿڸ��ʼ�����Ϊ�Ѷ�״̬��
����:
tVersion:			E-mail�汾��
����ֵ:
GOSCA_OK:						��ȡE-mail�ɹ���
--*/
extern HRESULT GOSCASTB_EmailRead(unsigned long tVersion) ;

/*++
����:
������ͨ���ʼ��İ汾ɾ������E-mail�ӿڡ�
����:
tVersion:			E-mail�汾�����Ϊ-1����ʾɾ������������email������Ϊ�����id��
����ֵ:
GOSCA_OK:						ɾ��E-mail�ɹ���
GOSCAERR_STB_NO_EMAIL:			Ҫɾ����E-mail�����ڡ�
--*/
extern HRESULT GOSCASTB_DelEmail(unsigned long tVersion) ;

/*++
����:
������ɾ������E-mail�ӿڡ�
����:

����ֵ�� ==0 �ɹ�
!=0 ʧ��
--*/
extern HRESULT GOSCASTB_DelAllEmail( void );

/*++
����:
�����л�̨ʱ���øýӿڡ�
����:

����ֵ�� ��
--*/
extern void GOSCASTB_SetCurIPPT(unsigned int nServerID) ;

/*++
���ܣ�
	���벥��PVR(��EMM����)ǰ���˳��������һ�θýӿڣ��Ա�CA��������ʶ������
������
	
����ֵ��
	�ޡ�
--*/
/*-----------------------------------���½ӿ���PVR��Ȩ���ýӿ�----------------------------------*/

/*++
���ܣ�
	¼��PVR��Ŀǰ����ȡPVR�ļ����ƣ��Ա��Ժ�ͨ���ϱ�PVR�ļ���������Ȩ��
������
	pFileID�������������ļ����ļ�ID���Ժ�Ĳ�����Ҫͨ�����ļ�ID������Ӧ�Ĳ�����
	pName�����Ƶ��ַ���������������
	pNamelen�����Ƶ��ַ������ȣ�
����ֵ�� ==0 �ɹ�
-1����ȡ��ǰϵͳʱ��ʧ�ܣ������ǵ��ýӿ�GOSSTBCA_GetSTB_CurrentTime��������ʧ�ܣ�
-2����ƷPVR�ļ����ַ���ʱ����
-3�����������ļ�ϵͳ����
--*/
extern HRESULT GOSCASTB_PVR_GetFileName(GOSCAPVR_File_ID* pFileID, unsigned char* pName, int* pNamelen) ;

/*++
���ܣ�
	����PVR�����ļ���ע��ͨ������¼��PVR��Ŀʱ��ȡEPG�������Ϣ���ݵ������ļ��У�һ����á���Ŀ��+��ǰEPG��Ϣ����
������
	pComments����Ŀ��+EPG��Ϣ,���Ȳ�����40���ַ���������������
	pCommentslen���ַ������ȣ�
����ֵ�� ==0 �ɹ�
!=0 ʧ��
--*/
extern HRESULT GOSCASTB_PVR_SetFileComments(GOSCAPVR_File_ID* pFileID, unsigned char* pComments, int* pCommentslen) ;

/*++
���ܣ�
	¼��PVR��Ŀ����״̬���ã�ͨ����Ϊ¼�ƿ�ʼ��¼�ƽ��������ſ�ʼ�����Ž��������̣�
������
nState:PVR_RECORD_START,PVR_RECORD_STOP,PVR_PLAY_START,PVR_PLAY_STOP
����ֵ�� ==0 �ɹ�
!=0 ʧ��
--*/
extern HRESULT GOSCASTB_PVR_SetRunState(GOSCAPVR_File_ID* pFileID, Pvr_Run_State nState ) ;

/*++
���ܣ�
	����PVR�ļ�ǰ����PVR���ļ���������У���Ƿ�Ϸ����Ϸ�ֱ�ӽ���PVR�Ĳ������̡���
������
	pName���������Ƶ��ַ���������������
	pNamelen�����Ƶ��ַ������ȣ�
	pComment�������ʾ��Ϣ���ַ���������������
	pCommentlen����ʾ��Ϣ���ַ������ȣ�
	pFileID������ļ���ID��
	pOverDueTime��PVR��Ȩ����ʱ���ַ�������2012-12-1��
	pSysCurTime��ϵͳ��ǰʱ�䣬��2012-12-1 19:24:12��
����ֵ�� ==0 �ɹ��Ϸ�
!=0 ʧ��
--*/
extern HRESULT GOSCASTB_PVR_CheckFileName(unsigned char* pName, int* pNamelen, unsigned char* pComment, int* pCommentlen, GOSCAPVR_File_ID* pFileID, unsigned char* pOverDueTime, unsigned char* pSysCurTime) ;

/*++
���ܣ�
	��ѯ�Ƿ�����PVR¼�ƽӿ�,�ù�����ǰ��ϵͳ�������Ĭ������²�����¼��
������
	pState��0����ֹ¼�ƣ�1������¼��
����ֵ�� ==0 �ɹ��Ϸ�
!=0 ʧ��
--*/
extern HRESULT GOSCASTB_PVR_RecordOk(unsigned char* pState) ;

/*++
���ܣ�
	PVR���ɵĲ��Դ�ӡ����ӡ�ؼ����ݱ��ڲ������⣬ͨ����ʽ�汾���ṩ�ýӿڣ�
��������

����ֵ�� ==0 �ɹ��Ϸ�
!=0 ʧ��
--*/
extern HRESULT GOSCAS_PVR_TestPrint(void) ;


/*-----------------------------------���½ӿ���ĳЩ����������ӿ�----------------------------------*/

/*++
���ܣ�
	���û����ж��嵽����ʾ�����ʣ�����Сʱ,�ýӿڵ�����Ҫ���±���ⶨ�����Ч��
������
	
����ֵ��
	�ޡ�
--*/
extern void GOSCASTB_SetLastDay_PromtHours( unsigned int nHours ) ;

/*++

���ܣ�
������ͨ��CAS��ȡ��ǰϵͳʱ�䣬�ýӿ�ͨ����ĳЩû��TDT��ϵͳ��ʹ�ã�

������
*year:    	xxxx��
*month		x��
*day		xx��
*week		����x
*hour		xxʱ
*min		xx��

����ֵ�� ==0 �ɹ�
!=0 ʧ��
˵����
ͬ��
--*/
extern HRESULT GOSCASTB_GetCasSysTime( unsigned int*  year, unsigned char*month, unsigned char*day, unsigned char* week, unsigned char* hour, unsigned char* min, unsigned char* sec);

/*-----------------------------------���½ӿ���CA���ṩһ������ӿڹ�ĳЩ��������----------------------------------*/

/*++

���ܣ�
��ȡһ����λ�����룬��������281201

������
*pOut ����ASC�ַ���

����ֵ�� ==0 �ɹ�
!=0 ʧ��
˵����
ͬ��
--*/
extern HRESULT GOSCASTB_Parent_PassWord_Get( unsigned char* pOut );

/*++

���ܣ�
У��һ����λ�����룬У���������������Զ���1������3������

������
*pIn ����ASC�ַ���

����ֵ�� ==0 �ɹ�
!=0 ʧ��
˵����
ͬ��
--*/
extern HRESULT GOSCASTB_Parent_PassWord_Check( unsigned char* pIn );

/*++

���ܣ�
����һ����λ�����룬��������281201��
ʹ�ó����������������룬�ù�����ĳЩ�ͻ�Ҫ��Ը�ĸ��Զ�̲�����ʹ�ã�
�����Թ�SMS����

������
*pIn ����ASC�ַ���

����ֵ�� ==0 �ɹ�
!=0 ʧ��
˵����
ͬ��
--*/
extern HRESULT GOSCASTB_Parent_PassWord_Set( unsigned char* pIn );

/*++

���ܣ�
��λ���һ����λ�����룬��������281201��
ʹ�ó����������������룬�ù�����ĳЩ�ͻ�Ҫ��Ը�ĸ��Զ�̲�����ʹ�ã�
�����Թ�SMS����

������
date_time ʱ���
version �汾��
����ֵ�� ==0 �ɹ�
!=0 ʧ��
˵����
ͬ��
--*/
extern HRESULT GOSCASTB_Parent_PassWord_Reset( unsigned long date_time, unsigned char version );

#ifdef __cplusplus
}
#endif

#endif
