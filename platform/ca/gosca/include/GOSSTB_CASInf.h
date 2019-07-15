#ifndef _GOSSTB_CASINF_H
#define _GOSSTB_CASINF_H

#ifdef __cplusplus
extern "C" {
#endif



/*----------------------------------���½ӿ���STB�ṩ��CAS����--------------------------------------------*/
#if (defined(GOSCA_V208))

/*++

���ܣ�
	CAS���ںʹ���ͨ��ʧ��һ�κ����������Զ���1����ֵ����GOSCA_UART_ERROR_MAX
	����øýӿڡ��ӿں���ʵ�ֿ���λ��ȷ��ATR ��ȷ��

������
-*/
extern void GOSSTBCA_SetSCReset() ;
/*++


���ܣ�
	�������ܿ���ǰ״̬

������
	pbySCStatus���������ܿ�״̬��ΪGOSCAS_SC_OUT��GOSCAS_SC_IN����֮һ��
--*/
extern void GOSSTBCA_GetSCStatus(unsigned char * pbySCStatus) ;

/*++

���ܣ�
	�������������С�

������
-*/
extern void GOSSTBCA_ReStartSTB()  ;


/*++

���ܣ�
	CA���ݵı���Ҫ��������ͬ�Ŀ飬ÿ�������һ��������CAS������Ҫ���ݵ�ʱ�����FLASH�Ķ�д������

������
	index��			�����飬ͨ�������з���������������ֵ��Ӧ��
	offset��		����������鿪ʼ��ַ��ƫ�Ƶ�ַ
	pbuf��          ���ݶ���BUF��
	len��			��Ҫ������ֽ����ݳ��ȣ�
	
����ֵ��
	0��	�ɹ��� ��0ʧ�ܣ�
	  
˵����
       
--*/
extern HRESULT GOSSTBCA_ReadFlash2Buffer(unsigned long gindex, unsigned long offset, void* pbuf, unsigned long len);

/*++

���ܣ�
	CA���ݵı���Ҫ��������ͬ�Ŀ飬ÿ�������һ��������CAS������Ҫ���ݵ�ʱ�����FLASH�Ķ�д������

������
	index��			�����飬ͨ�������з���������������ֵ��Ӧ��
	offset��		����������鿪ʼ��ַ��ƫ�Ƶ�ַ
	pbuf��          ����д��BUF��
	len��			��Ҫд����ֽ����ݳ��ȣ�
	
����ֵ��
	0��	�ɹ��� ��0ʧ�ܣ�
	  
˵����
       
--*/
extern HRESULT GOSSTBCA_WriteBuffer2Flash(unsigned long gindex, unsigned long offset, void* pbuf, unsigned long len);

/*++

���ܣ�
	CA���ݵı���Ҫ��������ͬ�Ŀ飬ÿ�������һ��������CAS������Ҫ���ݵ�ʱ�����FLASH�Ĳ���������

������
	index��			�����飬ͨ�������з���������������ֵ��Ӧ��������Ӧ���ȡ��д����
	
����ֵ��
	0��	�ɹ��� ��0ʧ�ܣ�
	  
˵����
       
--*/
extern HRESULT GOSSTBCA_EreseFlashBlack(unsigned long gindex);


/*++

���ܣ�
	�����ڴ�

������
	dwSize:		�����ڴ�Ŀռ�
						 
����ֵ��
	�����ڴ�ռ�ĵ�ַ
			
˵����
	   
--*/
extern void *GOSSTBCA_malloc( unsigned long dwSize ) ;

/*++

���ܣ�
	�ͷ��������ڴ�

������
	*pAddr: 	�����ڴ�ĵ�ַ
						 
����ֵ��
			
˵����
	   
--*/
extern void GOSSTBCA_free( unsigned char *pAddr ) ;


/*++

���ܣ�
	����ǰ�߳�

������
	dwSleepMicroseconds: 		����
	                     
����ֵ��
		    
˵����
       
--*/
extern HRESULT GOSSTBCA_Sleep( long dwSleepMicroseconds ) ;

/*++

���ܣ�
	��ʼ���ź���,��ʼ�����ź���û���źš�

������
	pSemaphore: 		ָ���ź�����ָ��
	                     
����ֵ��
		    
˵����
       
--*/
extern HRESULT GOSSTBCA_SemaphoreInit( GOSCA_Semaphore *pSemaphore ) ;
extern HRESULT GOSSTBCA_SemaphoreTimeOutInit( GOSCA_Semaphore *pSemaphore ) ;

/*++

���ܣ�
	�ͷ�һ���ź���

������
	pSemaphore: 		ָ���ź�����ָ��
	                     
����ֵ��
		    
˵����
       
--*/
extern HRESULT GOSSTBCA_SemaphoreDestory( GOSCA_Semaphore *pSemaphore ) ;

/*++
���ܣ�
	���ź������ź�

������
	pSemaphore: 		ָ���ź�����ָ��
	                     
����ֵ��
		    
˵����
       
--*/
extern HRESULT GOSSTBCA_SemaphoreSignal( GOSCA_Semaphore *pSemaphore ) ;

/*++
���ܣ�
	�ȴ��ź���,�ȴ��ɹ�֮��,�ź���Ϊ���ź�

������
	pSemaphore: 		ָ���ź�����ָ��
	                     
����ֵ��
		    
˵����
       
--*/
extern HRESULT GOSSTBCA_SemaphoreWait( GOSCA_Semaphore *pSemaphore ) ;
extern HRESULT GOSSTBCA_SemaphoreWait_TimeOut( GOSCA_Semaphore *pSemaphore, unsigned int timeout ) ;

/*++
���ܣ�
	CASģ���������ע���߳�

������
	szName:				ע����߳�����
	ProcessID:			ע����̵߳�ID
	pTaskFun:			Ҫע����̺߳���	                     

����ֵ��
	GOSCA_OK			�߳�ע��ɹ�
	
˵����
       
--*/
extern HRESULT GOSSTBCA_RegisterTask(const char* szName,const unsigned long ProcessID, pThreadFunc_gos pTaskFun) ;

/*++

���ܣ�
	���ù���������CAS˽�����ݡ�

������
	byReqID:	�����ձ������š�������Ӧ�ñ�������ݣ����յ�CAS˽�����ݺ����GOSCASTB_StreamGuardDataGot()ʱӦ�ý������ݷ��ء�
	wEcmPID:	��Ҫ���˵�����PID��
	szFilter:	��������ֵ��Ϊһ��8���ֽڵ����飬�൱��8*8�Ĺ�����
	szMask:		�����������룬Ϊһ��8���ֽڵ����飬��8*8�Ĺ�������Ӧ����szMask��ĳһbitλΪ0ʱ��ʾҪ���˵ı��Ӧ��bitλ����Ҫ��szFilter���Ӧ��bitλ��ͬ����szMaskĳһλΪ1ʱ��ʾҪ���˵ı��Ӧ��bitλһ��Ҫ��szFilter���Ӧ��bitλ��ͬ
	byLen:		�������ĳ��ȣ�Ϊ8
	bContiunue:	�Ƿ���������

--*/
extern HRESULT GOSSTBCA_SetStreamGuardFilter(unsigned char byReqID, unsigned short wPID,const unsigned char* szFilter,const unsigned char* szMask,
                                      unsigned char byLen, unsigned int bContiunue) ;

/*++

���ܣ�
	CA�����ô˺������ý�����������ǰ���ڼ���һ���ڵ�CW�͸���������

������
	wEcmPID:				CW������ECMPID��
	szOddKey:				��CW������
	szEvenKey:				żCW������
	byKeyLen:				CW�ĳ���
	bTaingControl           true������¼��,false��������¼��

	                     
����ֵ��
       
--*/
extern HRESULT GOSSTBCA_SetDescrCW(unsigned short wEcmPID,unsigned char byKeyLen,const unsigned char* szOddKey,const unsigned char* szEvenKey,
                             unsigned char bTaingControl) ;


/*++
���ܣ�
	   ��ӡ������Ϣ

������
	pszMsg:     ������Ϣ����
	                     
����ֵ��
	void

˵����
      
--*/
extern void GOSSTBCA_AddDebugMsg(char *pszMsg) ;

/*++
���ܣ�
	ʵ�������ܿ�֮���ͨѶ������7816��׼��
������
	byReaderNo��	��Ӧ�Ķ��������
	byLen:			����Ϊ�����������ֽڵĳ��ȣ����Ϊ�����ֽڳ���
	byszCommand:	�����͵�һ�������ֽ�
	szReply:		���ص����ݣ��ռ䳤�Ⱥ�Ϊ256�ֽ�
	
����ֵ��
      
--*/
extern HRESULT GOSSTBCA_SCAPDU(unsigned char byReaderNo, unsigned char* pbyLen, unsigned char* byszCommand, unsigned char* byszReply) ;

/*------------------------------------ ����1�Ľ��棺�������û�ͨ��ң����ȡ����ʾ�Ľ���--------------------------------*/
/*
���ܣ�
	��ʾ�û����ܹۿ���Ŀ����ʾ��Ϣ����������������Ӧʹ�á�
����:	
	byMesageNo:  Ҫ��ʾ����Ϣ���
	bShowInfo==1:��ʾ����ʾ��Ϣ��Ҫ��ʾ������ʾ��Ϣ��������ʾ��ʾ���ݣ�ǰ�˷������ʼ�����$#OperSvr*�����ʼ�����������ʾ��
	bShowInfo==0:����pString�Ͳ���strlen���ܣ�

--*/
extern void   GOSSTBCA_ShowPromptMessage(const char byMesageNo, unsigned int duration, unsigned long ippt, bool bShowInfo, unsigned char *pString, unsigned int strlen);
extern void   GOSSTBCA_HidePromptMessage(void) ;

/*
���ܣ�
	��ʾָ����Ϣ��
--*/
extern void	GOSSTBCA_ShowFingerPrinting(unsigned long version, unsigned long dwCardID,unsigned short wDuration) ;	/*��ʾָ�ƣ���STB������ʵ�֡�*/

/*------------------------------------ ����2�Ľ��棺�û�����ȡ����ʾ�Ľ���---------------------------------------------*/

/*
���ܣ�
	��ʾOSD��Ϣ��������ͬ����ʾ��Ҳ�������첽��ʾ��
����:	
	szOSD��		������ʾ��OSD��Ϣ
	wDuration��	0����ʾһ�κ��������أ�����Ϊ��ʾ�ľ���ʱ��
				
˵����
	�û�����ͨ��ң����ȡ����ǰOSD��ʾ��
--*/
extern void   GOSSTBCA_ShowOSDMsg(const char* szOSD, unsigned char OSD_len, unsigned long OSD_version, unsigned short wDuration) ;

/*++
���ܣ�
	��ʾ���ʼ��ı�־��
������
	byShow:		GOSCAS_NEW_EAMIL				���ʼ�֪ͨ
				GOSCAS_NEW_EMAIL_NO_ROOM		�����ʼ�����Email�ռ䲻��
				GOSCAS_EMAIL_NONE				û�����ʼ�
--*/
extern void GOSSTBCA_EmailNotify(unsigned char byShow, unsigned char gindex) ;

/*------------------------------------------���Ͻӿ���STB����CAS����---------------------------------------------------*/

/*++
���ܣ�
	��ȡ���������кţ���������Ҫ�����ҹ�˾��һ�����ܿ⣬��ɨ��ǹ��������кż��ܴ��������FLASH������Ϣ����
	�����������ñ�����CAS����ʱ���ȡ�����кű��ݸ�CAS����й���
������
	pSerialNo����������д�����кţ�4B�޷��������ģ�
	pRunArea����Ӫ�̰󶨵�����ID��2B�޷��������ģ�
����ֵ��
	��ȡ�ɹ����� 0��
��ע���ýӿ��滻��ԭ���� extern unsigned long GOSSTBCA_GetSerialNoBySTB( void ) ;
--*/
extern long GOSSTBCA_GetSerialNo_RunArea( unsigned long* pSerialNo, unsigned short* pRunArea ) ;

/*++
���ܣ�
	�û�������д����ID��2B�޷��������ġ�д����ID����Ӱ�����кŵ����ݣ���������ý��м򵥼��ܴ���FLASH.
������
	RunArea����Ӫ�̰󶨵�����ID��2B�޷��������ģ�
����ֵ��
	��д�ɹ����� 0��
--*/
extern long GOSSTBCA_SetRunArea( unsigned short RunArea ) ;

/*++
���ܣ�
	��д���������кţ��ýӿ��ɻ�������ʵ�֣�ʵ�ָýӿ�ǰ���������жϱ����Ƿ��кϷ���Ч��
	���кţ������ֱ�ӷ��ز���д���������Ϊ��д������к����������д�롣
������

����ֵ��
	���������к�,4B�޷��������ģ������ܣ�����д��FLASH��������򵥼��ܴ���
--*/
extern unsigned long GOSSTBCA_WriteSerialNo( unsigned long m_SerialNo ) ;

/*++
���ܣ�
	��ȡ������Ӳ���汾�š�
������

����ֵ��
	������Ӳ���汾�š���������ʱδ��ʹ��
--*/
extern unsigned long GOSSTBCA_GetHardVer(void) ;

/*++
���ܣ�
	��ȡ����������汾��
������
	dwVersion:	������Ӳ���汾�š�
����ֵ��
	����������汾�š���������ʱδ��ʹ��
--*/
extern unsigned long GOSSTBCA_GetSoftVer( unsigned long dwVersion ) ;


/*++
���ܣ�
	��ʾǿ��ָ�ơ�������������ʾ����ָ����Ҫһֱ��ʾ����������ʾ������Intervalʱ���������仯��
������
	version:			ָ�ư汾��Ψһ
	FontColor:			ָ������ɫ
	FontSize:			ָ���ֺ�
	BackGroundColor:	ָ�Ʊ�����ɫ����ʽΪARGB8888
	ChnlCnt:			ָ����ʾƵ���������Ϊ0 ����ʾ����Ƶ������ʾָ��
						��0����ʾServiceId����service id��Ŀ��Ŀǰ�汾���֧��ָ��10��Ƶ��						����ʽΪARGB8888
	ServiceId:			��ʾָ��Ƶ����service id
	IDType:				��2BITָ�����ͣ���00�����أ�01��ͨ��03�� ���ܣ�ע�⣬����ָ�Ƶ�����ΪpASC���ַ��������������ֻ֧��00,01,02������6λ��ʾ���ͣ���00�����ţ�01�����кţ�02���ż����кţ�0x03: ����+�û��Զ�������, 0x04: ���к�+�û��Զ�������, 0x05: ����+�����к�+�û��Զ������ݣ�
	Interval:			ʱ����,������ʾ֮��Ĳ���ʾָ�Ƶ�ʱ�䳤��
	Lock:				�Ƿ������û����� 1: �����û�������0: ������
	PosType:			ָ��λ�����ͣ�0 : �̶�λ����ʾ(ͨ�������Ͻǣ���1: ���û��Զ��壬����Pos_X,Pos_Y����������ʾ����2�����
	Pos_X:				�̶�λ��ָ�Ƶ�X ����
	Pos_Y:				�̶�λ��ָ�Ƶ�Y ����
	pASC��				�û��Զ����ַ�������(���20���ַ���
	len��				�û��Զ����ַ�������
����ֵ��
	������Ӳ���汾�š�
�����ر�˵����ָ�Ƶ����غ����ʾָ����ʾ����ʱ�����20,40,80�����ڿɵ�����ͨ��ʾָ��һֱ�ɼ���ʾ���������ָ����ָ���������ݼ�����ʾ����Ҫ��ר��������ܳ������ַ���
--*/
extern void	GOSSTBCA_ShowForceFingerPrinting(unsigned long version, unsigned long FontColor, unsigned char FontSize, unsigned long BackGroundColor,
			unsigned char ChnlCnt, unsigned short *ServiceId, unsigned char IDType, unsigned short Interval, unsigned char Lock,
				unsigned char PosType, unsigned short Pos_X, unsigned short Pos_Y, char* pASC, unsigned short len);


/*++
���ܣ�
	��ʾǿ��ָ�ơ�
������
	Version:				��ǰǿ��ָ�ư汾��
����ֵ��
--*/

extern void GOSSTBCA_CancleForceFingerPrinting(unsigned long Version);



/*++
���ܣ�
	ǿ�ƻ�̨
������
	pForceLockService:		ǿ�ƻ�̨�������μ�GOSCAS_STBDataPublic.h
	Version:				��ǰǿ�ƻ�̨�汾��
����ֵ��
--*/
extern void GOSSTBCA_ForceLockService(SGOSCALockService *pForceLockService, unsigned long Version);


/*++
���ܣ�
	ȡ��ǿ�ƻ�̨
������
	
����ֵ��
--*/
extern void GOSSTBCA_CancleForceLockService(unsigned long Version);

/*++
���ܣ�
	����Ĭ�ϻ�̨��Ŀ��ʵ�ַ�ʽ����ͨ������Ĳ���ѡ����ʵ�֡���������Ҫ�Լ���ϵͳ��������ı��洦��
������
	pStartService:		����Ĭ�ϻ�̨�������μ�GOSCAS_STBDataPublic.h
	flag:				1����ʾ������0����ʾȡ���������Ѿ����ڻ���ã�ȡ��ʱpStartService��ָ������Ч����
����ֵ��
--*/
extern void GOSSTBCA_StartService(SGOSCAStartService *pStartService, unsigned long flag);



/*++
���ܣ�
	ȡ��ǿ��OSD
������
	osdID:			ID��Ψһ
	Style:			0: ������ʾ��1: �ı���ʾ�������ţ�2����ʾ�ı��������
	Stylevalue:		styleΪ0 ��������Ϊ1: �Ϸ������� 2: �·�������3:Ϊ�м����
					styleΪ1��������Ϊ�趨�ı���ռ��Ļ�İٷֱȣ�ֵΪ20%-80%
	lock:				����ǰ����ң������
	FontColor:		OSD ��ʾ���ֵ���ɫ����ʽΪARGB8888
	FontSize:			OSD ��ʾ���ֺ�
	BackGroundColor:	�ı�OSD ��ʾ�ı�����ɫ����ʽΪARGB8888
	Showtimes:		���Ϊ������ʾOSD ���������趨����������������Ϊ�˼����ϵ�OSD ��ʽ
	Data_Body:		OSD ��ʾ����
	Data_Len:		OSD ��ʾ���ݳ���
����ֵ��
--*/
extern void	GOSSTBCA_ShowForceOSD(unsigned long osdID, unsigned char Style, unsigned char Stylevalue, unsigned char lock,unsigned long FontColor,
		unsigned char FontSize, unsigned long BackGroundColor, unsigned char Showtimes, unsigned char *Data_Body, unsigned short Data_Len);

/*++
���ܣ�
	ȡ��ǿ��OSD
������
	
����ֵ��
--*/
extern void GOSSTBCA_HideForceOSD();

/*++
���ܣ�
	CAS��ȡ�ⲿ�����е�ǰʱ��,�ر��Ǽ���PVR����ʱ��Ҫʵ�ָýӿڣ�
������
	pYear���ꣻpMonth���£�pDay���գ�pHour��24ʱ��pMin���֣�pSecon���룻
����ֵ��������û�л�ȡ��TDT��ʱ��ʱ���ط�0����ȡ������0����������ز���ֵ��
--*/
extern HRESULT GOSSTBCA_GetSTB_CurrentTime(unsigned int* pYear, unsigned char* pMonth, unsigned char* pDay, unsigned char* pHour, unsigned char* pMin, unsigned char* pSecon) ;

/*++
���ܣ�
	�ر��������
������
	
����ֵ��
--*/
extern void GOSSTBCA_TaskDispatchoff();

/*++
���ܣ�
	���������
������
	
����ֵ��
--*/
extern void GOSSTBCA_TaskDispatchon();

#else

/*++

���ܣ�
	CAS���ںʹ���ͨ��ʧ��һ�κ����������Զ���1����ֵ����GOSCA_UART_ERROR_MAX
	����øýӿڡ��ӿں���ʵ�ֿ���λ��ȷ��ATR ��ȷ��

������
-*/
extern void GOSSTBCA_SetSCReset(void) ;
/*++


���ܣ�
	�������ܿ���ǰ״̬

������
	pbySCStatus���������ܿ�״̬��ΪGOSCAS_SC_OUT��GOSCAS_SC_IN����֮һ��
--*/
extern void GOSSTBCA_GetSCStatus(unsigned char * pbySCStatus) ;

/*++

���ܣ�
	�������������С�

������
-*/
extern void GOSSTBCA_ReStartSTB(void) ;

/*++


���ܣ�
	��û����з����CAS�Ĵ洢�ռ������ַ�ʹ�С�����ֽ�Ϊ��λ��

������
	ppStartAddr:	     �����з����CAS�Ĵ洢�ռ�Ŀ�ʼ��ַ
	lSize:               ��������з����CAS�Ĵ���ռ�Ĵ�С��
	
����ֵ��
	GOSCA_OK	�ɹ�
	  
˵����
       
--*/
extern HRESULT GOSSTBCA_GetDataBufferAddr(unsigned int* lSize, unsigned long* pStartAddr) ;

/*++

���ܣ�
	��ȡ�����ڻ������е���Ϣ

������
	pStartAddr:	    Ҫ��ȡ�Ĵ洢�ռ�Ŀ�ʼ��ַ
	plDataLen:       ����ΪҪ��ȡ�������ֵ
	                ����ʵ�ʶ�ȡ�Ĵ�С
	pData��			����������

����ֵ��
	GOSCA_OK	�ɹ�
	       
--*/
extern HRESULT GOSSTBCA_ReadDataBuffer(const unsigned long pStartAddr, unsigned int DataLen, unsigned char* pData) ;

/*++

���ܣ�
	������еĴ洢�ռ�д��Ϣ

������
	lStartAddr:	     Ҫд�Ĵ洢�ռ�Ŀ�ʼ��ַ
	plDataLen:        Ҫд�����ݵĳ���
					 ����Ϊд���ʵ�ʳ���
	pData��			 Ҫд������
	
	                     
����ֵ��
	
˵����
	GOSCA_OK	�ɹ�
       
--*/
extern HRESULT GOSSTBCA_WriteDataBuffer(const unsigned long pStartAddr, const unsigned int DataLen, const unsigned char* pData)  ;
extern HRESULT GOSSTBCA_FlashErase(void);
/*++

���ܣ�
	������еı����ڴ���Ϣ

������
	
	                     
����ֵ��
	
˵����
	GOSCA_OK	�ɹ�
       
--*/
extern HRESULT GOSSTBCA_Data_Back(const unsigned long pStartAddr, const unsigned int DataLen)  ;

/*++

���ܣ�
	�����ڴ�

������
	dwSize:		�����ڴ�Ŀռ�
						 
����ֵ��
	�����ڴ�ռ�ĵ�ַ
			
˵����
	   
--*/
extern unsigned char *GOSSTBCA_malloc( unsigned int dwSize ) ;

/*++

���ܣ�
	�ͷ��������ڴ�

������
	*pAddr: 	�����ڴ�ĵ�ַ
						 
����ֵ��
			
˵����
	   
--*/
extern void GOSSTBCA_free( unsigned char *pAddr ) ;


/*++

���ܣ�
	����ǰ�߳�

������
	dwSleepMicroseconds: 		����
	                     
����ֵ��
		    
˵����
       
--*/
extern HRESULT GOSSTBCA_Sleep( long dwSleepMicroseconds ) ;

/*++

���ܣ�
	��ʼ���ź���,��ʼ�����ź���û���źš�

������
	pSemaphore: 		ָ���ź�����ָ��
	                     
����ֵ��
		    
˵����
       
--*/
extern HRESULT GOSSTBCA_SemaphoreInit( GOSCA_Semaphore *pSemaphore ) ;
extern HRESULT GOSSTBCA_SemaphoreTimeOutInit( GOSCA_Semaphore *pSemaphore ) ;

/*++

���ܣ�
	�ͷ�һ���ź���

������
	pSemaphore: 		ָ���ź�����ָ��
	                     
����ֵ��
		    
˵����
       
--*/
extern HRESULT GOSSTBCA_SemaphoreDestory( GOSCA_Semaphore *pSemaphore ) ;

/*++
���ܣ�
	���ź������ź�

������
	pSemaphore: 		ָ���ź�����ָ��
	                     
����ֵ��
		    
˵����
       
--*/
extern HRESULT GOSSTBCA_SemaphoreSignal( GOSCA_Semaphore *pSemaphore ) ;

/*++
���ܣ�
	�ȴ��ź���,�ȴ��ɹ�֮��,�ź���Ϊ���ź�

������
	pSemaphore: 		ָ���ź�����ָ��
	                     
����ֵ��
		    
˵����
       
--*/
extern HRESULT GOSSTBCA_SemaphoreWait( GOSCA_Semaphore *pSemaphore ) ;
extern HRESULT GOSSTBCA_SemaphoreWait_TimeOut( GOSCA_Semaphore *pSemaphore, unsigned int timeout ) ;

/*++
���ܣ�
	CASģ���������ע���߳�

������
	szName:				ע����߳�����
	ProcessID:			ע����̵߳�ID
	pTaskFun:			Ҫע����̺߳���	                     

����ֵ��
	GOSCA_OK			�߳�ע��ɹ�
	
˵����
       
--*/
extern HRESULT GOSSTBCA_RegisterTask(const char* szName,const unsigned long ProcessID, pThreadFunc_gos pTaskFun) ;

/*++

���ܣ�
	���ù���������CAS˽�����ݡ�

������
	byReqID:	�����ձ������š�������Ӧ�ñ�������ݣ����յ�CAS˽�����ݺ����GOSCASTB_StreamGuardDataGot()ʱӦ�ý������ݷ��ء�
	wEcmPID:	��Ҫ���˵�����PID��
	szFilter:	��������ֵ��Ϊһ��8���ֽڵ����飬�൱��8*8�Ĺ�����
	szMask:		�����������룬Ϊһ��8���ֽڵ����飬��8*8�Ĺ�������Ӧ����szMask��ĳһbitλΪ0ʱ��ʾҪ���˵ı��Ӧ��bitλ����Ҫ��szFilter���Ӧ��bitλ��ͬ����szMaskĳһλΪ1ʱ��ʾҪ���˵ı��Ӧ��bitλһ��Ҫ��szFilter���Ӧ��bitλ��ͬ
	byLen:		�������ĳ��ȣ�Ϊ8
	bContiunue:	�Ƿ���������

--*/
extern HRESULT GOSSTBCA_SetStreamGuardFilter(unsigned char byReqID, unsigned short wPID,const unsigned char* szFilter,const unsigned char* szMask,
                                      unsigned char byLen, unsigned int bContiunue) ;

/*++

���ܣ�
	CA�����ô˺������ý�����������ǰ���ڼ���һ���ڵ�CW�͸���������

������
	wEcmPID:				CW������ECMPID��
	szOddKey:				��CW������
	szEvenKey:				żCW������
	byKeyLen:				CW�ĳ���
	bTaingControl           true������¼��,false��������¼��

	                     
����ֵ��
       
--*/
extern HRESULT GOSSTBCA_SetDescrCW(unsigned short wEcmPID,unsigned char byKeyLen,const unsigned char* szOddKey,const unsigned char* szEvenKey,
                             unsigned char bTaingControl) ;


/*++
���ܣ�
	   ��ӡ������Ϣ

������
	pszMsg:     ������Ϣ����
	                     
����ֵ��
	void

˵����
      
--*/
extern void GOSSTBCA_AddDebugMsg(char *pszMsg) ;

/*++
���ܣ�
	ʵ�������ܿ�֮���ͨѶ������7816��׼��
������
	byReaderNo��	��Ӧ�Ķ��������
	byLen:			����Ϊ�����������ֽڵĳ��ȣ����Ϊ�����ֽڳ���
	byszCommand:	�����͵�һ�������ֽ�
	szReply:		���ص����ݣ��ռ䳤�Ⱥ�Ϊ256�ֽ�
	
����ֵ��
      
--*/
extern HRESULT GOSSTBCA_SCAPDU(unsigned char byReaderNo, unsigned char* pbyLen, const unsigned char* byszCommand, unsigned char* byszReply) ;

/*------------------------------------ ����1�Ľ��棺�������û�ͨ��ң����ȡ����ʾ�Ľ���--------------------------------*/
/*
���ܣ�
	��ʾ�û����ܹۿ���Ŀ����ʾ��Ϣ����������������Ӧʹ�á�
����:	
	byMesageNo:  Ҫ��ʾ����Ϣ���
	bShowInfo==1:��ʾ����ʾ��Ϣ��Ҫ��ʾ������ʾ��Ϣ��������ʾ��ʾ���ݣ�ǰ�˷������ʼ�����$#OperSvr*�����ʼ�����������ʾ��
	bShowInfo==0:����pString�Ͳ���strlen���ܣ�

--*/
extern void   GOSSTBCA_ShowPromptMessage(const char byMesageNo, unsigned int duration, unsigned long ippt, bool bShowInfo, unsigned char *pString, unsigned int strlen);
extern void   GOSSTBCA_HidePromptMessage(void) ;

/*
���ܣ�
	��ʾָ����Ϣ��
����:
	wDuration �����뼶��Ĭ����3���Զ���ʧ
--*/
extern void	GOSSTBCA_ShowFingerPrinting(unsigned long version, unsigned long dwCardID,unsigned short wDuration) ;	/*��ʾָ�ƣ���STB������ʵ�֡�*/

/*------------------------------------ ����2�Ľ��棺�û�����ȡ����ʾ�Ľ���---------------------------------------------*/

/*
���ܣ�
	��ʾOSD��Ϣ��������ͬ����ʾ��Ҳ�������첽��ʾ��
����:	
	szOSD��		������ʾ��OSD��Ϣ
	wTimes��	��ʾ�Ĵ���
				
˵����
	�û�����ͨ��ң����ȡ����ǰOSD��ʾ��
--*/
extern void   GOSSTBCA_ShowOSDMsg(const char* szOSD, unsigned char OSD_len, unsigned long OSD_version, unsigned short wTimes) ;

/*++
���ܣ�
	��ʾ���ʼ��ı�־��
������
	byShow:		GOSCAS_NEW_EAMIL				���ʼ�֪ͨ
				GOSCAS_NEW_EMAIL_NO_ROOM		�����ʼ�����Email�ռ䲻��
				GOSCAS_EMAIL_NONE				û�����ʼ�
--*/
extern void GOSSTBCA_EmailNotify(unsigned char byShow, unsigned char index) ;

/*------------------------------------------���Ͻӿ���STB����CAS����---------------------------------------------------*/

/*++
���ܣ�
	��ȡ���������кš�
������

����ֵ��
	���������кš������Ա���ڿ���ʹ��
--*/
extern unsigned long GOSSTBCA_GetSerialNo( void ) ;

/*++
���ܣ�
	��ȡ������Ӳ���汾�š�
������

����ֵ��
	������Ӳ���汾�š���������ʱδ��ʹ��
--*/
extern unsigned long GOSSTBCA_GetHardVer(void) ;

/*++
���ܣ�
	��ȡ����������汾��
������
����ֵ��
	����������汾�š���������ʱδ��ʹ��
--*/
extern unsigned long GOSSTBCA_GetSoftVer(void) ;


/*++
���ܣ�
	��ʾǿ��ָ�ơ�������������ʾ����ָ����Ҫһֱ��ʾ����������ʾ������Intervalʱ���������仯��
������
	version:			ָ�ư汾��Ψһ
	FontColor:			ָ������ɫ
	FontSize:			ָ���ֺ�
	BackGroundColor:	ָ�Ʊ�����ɫ����ʽΪARGB8888
	ChnlCnt:			ָ����ʾƵ���������Ϊ0 ����ʾ����Ƶ������ʾָ��
						��0����ʾServiceId����service id��Ŀ��Ŀǰ�汾���֧��ָ��10��Ƶ��
						����ʽΪARGB8888
	ServiceId:			��ʾָ��Ƶ����service id
	IDType:				������Ŀǰ�汾Ϊ0x00
	Interval:			ʱ����,������ʾ֮��Ĳ���ʾָ�Ƶ�ʱ�䳤��
	Lock:				�Ƿ������û����� 1: �����û�������0: ������
	PosType:			ָ��λ�����ͣ�0 : �����ʾ��1: �̶�λ��
	Pos_X:				�̶�λ��ָ�Ƶ�X ����
	Pos_Y:				�̶�λ��ָ�Ƶ�Y ����
����ֵ��
	������Ӳ���汾�š�
--*/
extern void	GOSSTBCA_ShowForceFingerPrinting(unsigned long version, unsigned long FontColor, unsigned char FontSize, unsigned long BackGroundColor,
			unsigned char ChnlCnt, unsigned short *ServiceId, unsigned char IDType, unsigned short Interval, unsigned char Lock,
				unsigned char PosType, unsigned short Pos_X, unsigned short Pos_Y);


/*++
���ܣ�
	��ʾǿ��ָ�ơ�
������
	Version:				��ǰǿ��ָ�ư汾��
����ֵ��
--*/

extern void GOSSTBCA_CancleForceFingerPrinting(unsigned long Version);



/*++
���ܣ�
	ǿ�ƻ�̨
������
	pForceLockService:		ǿ�ƻ�̨�������μ�GOSCAS_STBDataPublic.h
	Version:				��ǰǿ�ƻ�̨�汾��
����ֵ��
--*/
extern void GOSSTBCA_ForceLockService(SGOSCALockService *pForceLockService, unsigned long Version);

/*++
���ܣ�
	ȡ��ǿ�ƻ�̨
������
	
����ֵ��
--*/
extern void GOSSTBCA_CancleForceLockService(unsigned long Version);




/*++
���ܣ�
	ȡ��ǿ��OSD
������
	osdID:			ID��Ψһ
	Style:			0: ������ʾ��1: �ı���ʾ
	Stylevalue:		styleΪ0 ��������Ϊ1: �Ϸ������� 0: �·�����
					styleΪ1��������Ϊ�趨�ı���ռ��Ļ�İٷֱȣ�ֵΪ20%-80%
	lock:				ָ�Ʊ�����ɫ
	FontColor:		OSD ��ʾ���ֵ���ɫ����ʽΪARGB8888
	FontSize:			OSD ��ʾ���ֺ�
	BackGroundColor:	�ı�OSD ��ʾ�ı�����ɫ����ʽΪARGB8888
	Showtimes:		���Ϊ������ʾOSD ���������趨����������������Ϊ�˼����ϵ�OSD ��ʽ
	Data_Body:		OSD ��ʾ����
	Data_Len:		OSD ��ʾ���ݳ���
����ֵ��
--*/
extern void	GOSSTBCA_ShowForceOSD(unsigned long osdID, unsigned char Style, unsigned char Stylevalue, unsigned char lock,unsigned long FontColor,
		unsigned char FontSize, unsigned long BackGroundColor, unsigned char Showtimes, unsigned char *Data_Body, unsigned short Data_Len);

/*++
���ܣ�
	ȡ��ǿ��OSD
������
	
����ֵ��
--*/
extern void GOSSTBCA_HideForceOSD(void);

/*++
���ܣ�
	�ر��������
������
	
����ֵ��
--*/
extern void GOSSTBCA_TaskDispatchoff(void);

/*++
���ܣ�
	���������
������
	
����ֵ��
--*/
extern void GOSSTBCA_TaskDispatchon(void);


#endif
/*------------------------------���Ͻӿ���������Ѱַ-----------------------------------*/

#ifdef __cplusplus
}
#endif

#endif
