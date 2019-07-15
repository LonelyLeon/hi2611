#ifndef _DVTSTCS_STBDataPublic_H_2004_12_31_
#define _DVTSTCS_STBDataPublic_H_2004_12_31_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef  __cplusplus
extern "C" {
#endif


#ifndef BYTE //8bit
#define BYTE unsigned char
#endif
#ifndef WORD //16bit
#define WORD unsigned short
#endif
#ifndef HRESULT
#define	HRESULT long
#endif
#ifndef DWORD
#define DWORD unsigned long
#endif
#ifndef bool //8bit
#define bool unsigned char
#endif
#ifndef NULL
#define NULL 0
#endif
#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif
	
//�ź�������
typedef long  DVTSTC_Semaphore ;

//�̺߳�����ַ����
//typedef void (*pThreadFunc) (void);
	
/*----------------------------------------------------------------------*/
/*                       �����ǳ���ֵ����                               */
/*----------------------------------------------------------------------*/

#define DVTSTC_MAXLEN_PINCODE						8		//���PIN�볤��
#define DVTSTC_LEN_SMARTCARD_SN					64		//�ֻ�ܿ����кų��ȣ��ⲿ���ţ�

#define DVTSTC_MAXLEN_SERVICEPERECM				10		//ÿ��ECM֧�ֵ����Service��Ŀ

#define DVTSTC_MAXLEN_TVSNAME						21		//���Ӫ�����Ƴ���+\0
#define DVTSTC_MAXLEN_MANUFACTURERNAME			21		//���STCS�������ֳ���+\0 
#define DVTSTC_MAXLEN_PRODUCT_NAME				21		//��Ĳ�Ʒ����,���20���ַ�+\0
#define DVTSTC_MAXLEN_SERVICE_NAME				21		//���ҵ������,���20���ַ�+\0
#define DVTSTC_MAXLEN_EMAIL_SENDERNAME			11		//E-mail���������������10���ַ�+\0
#define DVTSTC_MAXLEN_EMAIL_CONTENT				1001	//E-mail��󳤶ȣ����1000���ַ�+\0
#define DVTSTC_MAXLEN_EMAIL_SHORT_CONTENT		21		//E-mail���ⳤ�ȣ����20���ַ�+\0
#define	DVTSTC_MAXNUMBER_TVSID					5		//֧�ֵ���Ӫ��������

//������ȡ˽�����ݵ������
#define DVTSTC_STB_ECM_SLOT						1
#define DVTSTC_STB_EMM_Private_SLOT				2
#define DVTSTC_STB_EMM_Public_SLOT					3
#define DVTSTC_STB_EMM_Group_SLOT					4  //for Group Address 
//���ܿ�״̬����
#define DVTSTCS_SC_OUT								0		//���ܿ����ڶ�������
#define DVTSTCS_SC_INIT								1		//���ܿ��ڶ������У����ڳ�ʼ��
#define DVTSTCS_SC_IN								2		//���ܿ��ڶ������У���������

//�������״̬����
#define DVTSTCS_SC_PAIR_OK							0		//���ܿ��뵱ǰ���������
#define DVTSTCS_SC_NO_Pairing						1		//���ܿ�û�����κλ��������
#define DVTSTCS_SC_PAIR_OTHER						2		//���ܿ��뵱ǰ������û�����

//�տ�������
#define DVTSTCS_Rating_3								3		//3��
#define DVTSTCS_Rating_4								4		//4��
#define DVTSTCS_Rating_5								5		//5��
#define DVTSTCS_Rating_6								6		//6��
#define DVTSTCS_Rating_7								7		//7��
#define DVTSTCS_Rating_8								8		//8��
#define DVTSTCS_Rating_9								9		//9��
#define DVTSTCS_Rating_10							10		//10��
#define DVTSTCS_Rating_11							11		//11��
#define DVTSTCS_Rating_12							12		//12��
#define DVTSTCS_Rating_13							13		//13��
#define DVTSTCS_Rating_14							14		//14��
#define DVTSTCS_Rating_15							15		//15��
#define DVTSTCS_Rating_16							16		//16��
#define DVTSTCS_Rating_17							17		//17��
#define DVTSTCS_Rating_18							18		//18��

//email ��ʾ��Ϣ��
#define DVTSTCS_EMAIL_NEW							0		//���ʼ�֪ͨ
#define DVTSTCS_EMAIL_NEW_NO_ROOM				1		//�����ʼ�����Email�ռ䲻��
#define DVTSTCS_EMAIL_NONE							0xFF	//���ر�־

//email ״̬��	
#define DVTSTCS_EMAIL_STATUS_INI					0		//��ʼֵ
#define DVTSTCS_EMAIL_STATUS_READ					2		//��������

//�۸����Ͷ��塣
#define	TPP_TAP_PRICE								0		//���ش���¼��
#define	TPP_NOTAP_PRICE							1		//���ش�����¼��
#define	CPP_TAP_PRICE								2		//�ش���¼��
#define	CPP_NOTAP_PRICE							3		//�ش�����¼��


/*----------------------------------------------------------------------*/
/*                       �����Ƿ���ֵ����                               */
/*----------------------------------------------------------------------*/

//�����з���ֵ��ֵ����
#define DVTSTCERR_BASE_STB						0xF1000000

//����ֵ����
#define DVTSTC_OK								0 

#define DVTSTCERR_STB_POINTER_INVALID			(DVTSTCERR_BASE_STB + 1)		//�����ָ����Ч
#define DVTSTCERR_STB_DATA_LEN_ERROR				(DVTSTCERR_BASE_STB + 2)		//��������ݳ��Ȳ��Ϸ�
#define DVTSTCERR_STB_TVS_NOT_FOUND				(DVTSTCERR_BASE_STB + 3)		//û���ҵ�����Ҫ�����Ӫ��
#define DVTSTCERR_STB_EXCEED_MAX_COUNT			(DVTSTCERR_BASE_STB + 4)		//��������������ĸ���
#define DVTSTCERR_STB_KEY_NOT_FOUND				(DVTSTCERR_BASE_STB + 5)		//û���ҵ�������Կ
#define DVTSTCERR_STB_PIN_INVALID				(DVTSTCERR_BASE_STB + 6)		//�����PIN����Ч
#define DVTSTCERR_STB_PIN_LOCKED					(DVTSTCERR_BASE_STB + 7)		//PIN�뱻����
#define DVTSTCERR_STB_CMD_INVALID				(DVTSTCERR_BASE_STB + 8)		//MACУ�����
#define DVTSTCERR_STB_VER_EXPIRED				(DVTSTCERR_BASE_STB + 9)		//����İ汾û��IC���еĴ󣬼������Ѿ�����
#define DVTSTCERR_STB_EXCEED_MAX_LEN				(DVTSTCERR_BASE_STB + 10)	//��Ӫ�̵����Ƴ������ĳ���
#define DVTSTCERR_STB_NO_SPACE					(DVTSTCERR_BASE_STB + 11)	//�Ѿ�û�пռ�
//#define DVTSTCERR_STB_IS_PAIRED					(DVTSTCERR_BASE_STB + 12)	//���ܿ��뵱ǰ�����ж�Ӧ
#define DVTSTCERR_STB_NOT_PAIRED					(DVTSTCERR_BASE_STB + 13)	//���ܿ��뵱ǰ������û�ж�Ӧ
//#define DVTSTCERR_STB_COUNT_ISZERO				(DVTSTCERR_BASE_STB + 14)	//�����CountΪ0. 
#define DVTSTCERR_STB_WORKTIME_INVALID			(DVTSTCERR_BASE_STB + 15)	//����ʱ�����ò��Ϸ���������ʱ�䲻��00:00:00~23:59:59֮�䣬���߿�ʼʱ����ڽ���ʱ�䡣
//#define	DVTSTCERR_STB_OVERFLOW					(DVTSTCERR_BASE_STB + 16)	
#define	DVTSTCERR_STB_CARD_INVALID				(DVTSTCERR_BASE_STB + 17)	//���ܿ���Ч
#define	DVTSTCERR_STB_Rating_LOW					(DVTSTCERR_BASE_STB + 18)	//���ܿ����õ��տ�����ȵ�ǰ�տ��Ľ�Ŀ��
#define DVTSTCERR_STB_UNKNOWN					(DVTSTCERR_BASE_STB + 19)	//δ֪����STB�����κ���ʾ����ͨ������λ�ָ���

//#define	DVTSTCERR_STB_EMAILBOX_EMPTY				(DVTSTCERR_BASE_STB + 20)	//E-mail����Ϊ��
#define	DVTSTCERR_STB_NO_EMAIL					(DVTSTCERR_BASE_STB + 21)	//û�д�E-mail
#define	DVTSTCERR_STB_EMAILBOX_FULL				(DVTSTCERR_BASE_STB + 22)	//E-mail������
//#define	DVTSTCERR_STB_NO_SECTION					(DVTSTCERR_BASE_STB + 23)	//û���յ�����Section

#define DVTSTCERR_STB_MONEY_LACK					(DVTSTCERR_BASE_STB + 24)	//���ֻ࣬��Ԥ��ʱ�᷵�ظô�����Ҫ��ʾ�û�"Ԥ���ɹ��������࣬�뼰ʱ��ֵ"��
#define DVTSTCERR_STB_PROD_NOT_FOUND				(DVTSTCERR_BASE_STB + 25)	//��Ʒδ�ҵ�
#define DVTSTCERR_STB_OPER_INVALID				(DVTSTCERR_BASE_STB + 26)	//��Ʒ�Ѵ��ڣ����ܲ���
#define DVTSTCERR_STB_NEED_PIN_PASS				(DVTSTCERR_BASE_STB + 27)	//��ҪPIN��֤ͨ��
#define DVTSTCERR_STB_IC_COMMUNICATE				(DVTSTCERR_BASE_STB + 28)	//��IC��ͨѶ����
#define DVTSTCERR_STB_SLOT_NOT_FOUND				(DVTSTCERR_BASE_STB + 29)	//��Ӫ��Ǯ��û�з���
#define DVTSTCERR_STB_PRICE_INVALID				(DVTSTCERR_BASE_STB + 30)	//�۸���Ч
#define DVTSTCERR_STB_PRODUCT_EXPIRED			(DVTSTCERR_BASE_STB + 31)	//��Ʒ�Ѿ�����

//xb:20050617 ++
#define DVTSTCERR_STB_EXPIRED					(DVTSTCERR_BASE_STB + 33)	//��Ʒ�Ѿ�����
#define DVTSTCERR_IPPREC_NOT_FOUND				(DVTSTCERR_BASE_STB + 34)	//IPP��¼������
#define DVTSTCERR_TIME_INVALID					(DVTSTCERR_BASE_STB + 35)	//��ǰʱ����Ч
#define DVTSTCERR_NOT_BOOKED						(DVTSTCERR_BASE_STB + 37)	//��ƷδԤ��
#define DVTSTCERR_CONFIRMED						(DVTSTCERR_BASE_STB + 38)	//��Ʒ�Ѿ�ȷ��
#define DVTSTCERR_UNCONFIRMED					(DVTSTCERR_BASE_STB + 39)	//��Ʒ�Ѿ�ȡ��ȷ��
#define DVTSTCERR_INPUT_DATA_INVALID				(DVTSTCERR_BASE_STB + 40)	//�����������Ч

#define DVTSTCERR_TERMINAL_NOT_ACTIVATE		(DVTSTCERR_BASE_STB + 51)	//�ն�δ����
#define DVTSTCERR_TERMINAL_NOT_SERVER			(DVTSTCERR_BASE_STB + 52)	//�ն˱�����
#define DVTSTCERR_FREEPREVIEW_OVER				(DVTSTCERR_BASE_STB + 53)	//�������Ԥ���ѽ���
#define DVTSTCERR_FREEPREVIEW_ALLOVER			(DVTSTCERR_BASE_STB + 54)	//Ԥ���ܴ����ѵ�
#define DVTSTCERR_AREA_RESTRICT					(DVTSTCERR_BASE_STB + 55)	//��Ӫ����������ۿ�
#define DVTSTCERR_NO_ENTITLE						(DVTSTCERR_BASE_STB + 56)	//û�й���˽�ĿProgram not paid

//----------------------------------------------
//������ң��������ȡ������ʾ��Ϣ�б�
#define DVTSTC_RATING_TOO_LOW					0			//�տ����𲻹�watching level not enough 
#define DVTSTC_NOT_IN_WATCH_TIME					1			//�����տ�ʱ����Not in working period
#define DVTSTC_NO_ENTITLE						5			//û�й���˽�ĿProgram not paid
#define DVTSTC_PRODUCT_RESTRICT					6			//��Ӫ�����ƹۿ��ý�ĿProgram Restricted by Operator
#define DVTSTC_AREA_RESTRICT						7			//��Ӫ����������ۿ�Region Restricted by Operator
#define DVTSTC_FREE_PREVIEWING					22			//�û����ã��˽�Ŀ����δ�����������Ԥ����This program is not paid, free viewing
//wy:20071022���û��Զ�����������
#define DVTSTC_BOUQUETID							254			//�Զ�����������-Bouquet_id

//+++++++++++++++++++++++++++++++++STCS����
#define DVTSTC_TERMINAL_NOT_ACTIVATE			101			//�ն�δ����terminal is not activated
#define DVTSTC_TERMINAL_NOT_SERVER				102			//�ն˱�����terminal is forbidden 
#define DVTSTC_FREEPREVIEW_OVER					103			//����Ԥ������preview is over
#define DVTSTC_FREEPREVIEW_ALLOVER				104			//����Ŀ����Ԥ�������ѵ�today's preview of this program has been used up  
//----------------------------------------------

//kfd:2007-11-16---�ַ�����������
#define DVTSTC_LANG_CHN_SIM						1			//��������(Ĭ��)
#define DVTSTC_LANG_ENG							2			//Ӣ��

/*----------------------------------------------------------------------*/
/*                       ������һЩ���ݽṹ����                         */
/*----------------------------------------------------------------------*/

typedef struct _SDVTSTCPin{
	BYTE	m_byLen;
	BYTE	m_byszPin[DVTSTC_MAXLEN_PINCODE];
}SDVTSTCPin;

typedef struct _SDVTSTCManuInfo{
	DWORD	m_dwCardID;											//���ڲ�ID
	DWORD	m_dwSTBSTCSVer;										//������STCSģ��İ汾��
	char	m_szSCSTCSManuName[DVTSTC_MAXLEN_MANUFACTURERNAME];	//STCS��Ӧ�̵�����
}SDVTSTCManuInfo;

typedef struct _SDVTSTCTvsInfo{
	WORD	m_wTVSID; 											//��Ӫ�̵��ⲿ���
	char	m_szTVSName[DVTSTC_MAXLEN_TVSNAME];					//��Ӫ������
}SDVTSTCTvsInfo;

typedef struct _SDVTSTCServiceEntitle{
	WORD 	m_wProductID;										//��ƷID
	DWORD	m_tEntitleTime;										//��Ȩʱ�䣬time_t��ʽ��
	DWORD	m_tStartTime;										//��ʼʱ�䣬time_t��ʽ��
	DWORD	m_tEndTime;											//����ʱ�䣬time_t��ʽ��
	char	m_szProductName[DVTSTC_MAXLEN_PRODUCT_NAME];			//��Ʒ����
	bool	m_bTapingFlag;										//¼���ʶ��
}SDVTSTCServiceEntitle;											//��ͨ��Ʒ��Ȩ

typedef struct _SDVTSTCServiceInfo{
	WORD 	m_wEcmPid;											//���ŵ�ECMPID
	WORD 	m_wServiceID;										//����Ƶ����ServiceID
}SDVTSTCServiceInfo;

typedef struct _SDVTSTCEmailInfo{
	DWORD	m_dwVersion;										//����ʱ��
	char	m_szSenderName[DVTSTC_MAXLEN_EMAIL_SENDERNAME];		//����������
	BYTE	m_Status;											//�ʼ���״̬��ΪDVTSTCS_EMAIL_STATUS_���е�һ��
	WORD	m_wEmailLength;										//�ʼ����ݳ���
	char	m_szTitle[DVTSTC_MAXLEN_EMAIL_SHORT_CONTENT];		//�ʼ������ݣ�������Ҫ�Ը����ݵı����ʽ����У��
}SDVTSTCEmailInfo;

typedef struct _SDVTSTCEmailContent{
	DWORD	m_dwVersion;										//����ʱ��
	WORD	m_wEmailLength;										//�ʼ����ݳ���
	char	m_szEmail[DVTSTC_MAXLEN_EMAIL_CONTENT];				//�ʼ�����
}SDVTSTCEmailContent;

typedef struct _SDVTSTCIpp{
	WORD	m_wTVSID;					//��Ӫ�̱��
	WORD	m_wProdID;					//��ƷID
	BYTE	m_bySlotID;					//Ǯ��ID
	char	m_szProdName[DVTSTC_MAXLEN_PRODUCT_NAME];	//��Ʒ����
	DWORD	m_tStartTime;				//��ʼʱ�䣬time_t��ʽ��
	DWORD	m_dwDuration;				//��������
	char	m_szServiceName[DVTSTC_MAXLEN_SERVICE_NAME];	//ҵ������
	WORD	m_wCurTppTapPrice;			//��ǰ�Ĳ��ش�����¼��۸�(��)���۸�����ֵΪ0
	WORD	m_wCurTppNoTapPrice;		//��ǰ�Ĳ��ش�������¼��۸�(��)���۸�����ֵΪ1
	WORD	m_wCurCppTapPrice;			//��ǰ��Ҫ�ش�����¼��۸�(��)���۸�����ֵΪ2
	WORD	m_wCurCppNoTapPrice;		//��ǰ��Ҫ�ش�������¼��۸�(��)���۸�����ֵΪ3
	WORD	m_wBookedPrice;			//�Ѿ�Ԥ���ļ۸�(��)
	BYTE	m_byBookedPriceType;		//�Ѿ�Ԥ���ļ۸����ͣ�ȡֵ��Χ0~3
	BYTE	m_byBookedInterval;		//Ԥ���շѼ��
	BYTE	m_byCurInterval;			//��ǰ�շѼ��
	BYTE	m_byIppStatus;				//Ipp��Ʒ״̬
	BYTE	m_byUnit;					//�շѼ���ĵ�λ0 -����1-Сʱ2-��3-��4-��
	WORD	m_wIpptPeriod; 			//�û�����IPPT�Ĺۿ�������,for Philippines LongIPPT��
}SDVTSTCIpp;

typedef struct _SDVTSTCViewedIpp{
	WORD	m_wTVSID;											//��Ӫ�̱��
	char	m_szProdName[DVTSTC_MAXLEN_PRODUCT_NAME];		//��Ʒ����
	DWORD	m_tStartTime;						//��ʼʱ�䣬time_t��ʽ��
	DWORD	m_dwDuration;						//��������
	WORD	m_wBookedPrice;						//Ԥ���۸�(��)
	BYTE	m_byBookedPriceType;					//Ԥ���۸����ͣ�0:TppTap;1:TppNoTap;2:CppTap;3:CppNoTap;
	BYTE	m_byBookedInterval;					//Ԥ���շѼ��
	char   	m_szOtherInfo[44];					//ippvʱΪ���˲�ƷΪippv��Ʒ����ipptʱΪ���ۿ���ʱ�䣺�����ӣ���Ǯ���������֡�
	BYTE	m_byUnit;						//�շѵ�λ��0 -����1-Сʱ2-��3-��4-��
}SDVTSTCViewedIpp;

typedef struct _SDVTCAStationInfo{
	DWORD		m_dwCardArea;			//����������
	DWORD		m_tSetCardAreaTime;		//STCS��Ϊ0���趨����ʱ�䡣
	BYTE		m_byStartFlag;			//STCS��Ϊ0��������־��1:������0:û�С�
	DWORD		m_tSetFlagTime;			//STCS��Ϊ0�����ñ�־ʱ�䡣
	DWORD		m_tSetStreamTime;		//STCS��Ϊ0����������������ʱ�䡣(�յ���������ʱ��)
	DWORD		m_dwIntervalTime;		//STCS��Ϊ0�����е�ǰʱ���ȥ������ʱ������ֵ��
	DWORD		m_dwStreamMinArea;		//STCS��Ϊ0����������С������
	DWORD		m_dwStreamMaxArea;		//STCS��Ϊ0�����������������
}SDVTCAStationInfo;

typedef struct _SDVTSTCEmailMsg{
	DWORD		m_dwVersion;										//����ʱ��
	char		m_szSenderName[DVTSTC_MAXLEN_EMAIL_SENDERNAME];	//����������
	WORD		m_wEmailLength;									//�ʼ����ݳ���
	char		m_szEmail[DVTSTC_MAXLEN_EMAIL_CONTENT];			//�ʼ�����
}SDVTSTCEmailMsg;

typedef struct _SDVTSTCCharaterFingerMsg{
	bool    m_bVisionType;			//�������ͣ�0-Covert��1-Overt����covertʱ��duration����Ч��
	BYTE	m_byszContent[8];		//ָ���ַ�����
	WORD	m_wDuration;			//ָ����ʾʱ�䳤�ȣ�-1����ʼ����ʾ��
	BYTE	m_byLocationFromTop;	//ָ�����ϽǾ�����Ļ����λ��(��ռ�߶ȱ���)�����λ�������ֵΪ-1������ȡֵ��Χ0-100��
	BYTE	m_byLocationFromLeft;	//ָ�����ϽǾ�����Ļ���λ�ã���ռ��ȱ����������λ�������ֵΪ-1������ȡֵ��Χ0-100��
	BYTE	m_bySize;				//�ַ�ָ�ƿ����ռ��Ļ��ȱ�����ȡֵ��Χ0-100��
	DWORD	m_dwFontARGB;			//����͸���ȣ�1�ֽڣ�+������ɫ������ɫ
	DWORD	m_dwBackgroundARGB; 	//����͸���ȣ�1�ֽڣ�+������ɫ������ɫ
	BYTE	m_byFontType;			//��������
}SDVTSTCCharaterFingerMsg;

typedef struct _SDVTSTCDotMatrixFingerMsg {
	bool    m_bVisionType;			//�������ͣ�0-Covert��1-Overt��.covertʱ��duration����Ч��
	BYTE	m_byszContent[10];	//10���ֽڹ�80bit��ǰ77��bit��Ч��
	WORD	m_wDuration;			//ָ����ʾʱ�䳤�ȣ�-1����ʼ����ʾ��
	BYTE	m_byLocationFromTop;	//ָ�����ϽǾ�����Ļ����λ��(��ռ�߶ȱ���)�����λ�������ֵΪ-1������ȡֵ��Χ0-100��
	BYTE	m_byLocationFromLeft;	//ָ�����ϽǾ�����Ļ���λ�ã���ռ��ȱ����������λ�������ֵΪ-1������ȡֵ��Χ0-100��
	BYTE	m_bySize;				//����ָ�������ռ��Ļ������ȡֵ��Χ0-100��
	DWORD	m_dwFontARGB;			//���͸���ȣ�1�ֽڣ�+�����ɫ������ɫ
}SDVTSTCDotMatrixFingerMsg;
#ifdef  __cplusplus
}
#endif

#endif	
