#ifndef _GOSCAS_STBDATAPUBLIC_H
#define _GOSCAS_STBDATAPUBLIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
	PARE_STB_INSERT_MASTER,
	PARE_STB_INSERT_SLAVE,
	PARE_STB_EXIT
}Master_Pare_Slave;

typedef enum
{
	PVR_RECORD_START,
	PVR_RECORD_STOP,
	PVR_PLAY_START,
	PVR_PLAY_STOP
}Pvr_Run_State;

#ifndef HRESULT
#define	HRESULT			long
#endif
#ifndef bool
#define bool		   unsigned char
#endif
#define true           1                                          
#define false          0   

//ADD BY GOS
#define GOSCA_MAX_EMAIL_TITLE					20	
#define GOSCA_MAX_EMAIL_ID_COUNT				20						
#define GOSCA_MAX_EMAIL_CONTENT					(1024+1)				

#define GOS_MAX_ENTITLES						256
/*----------------------------------------------------------------------*/
/*                       �����ǳ���ֵ����                               */
/*----------------------------------------------------------------------*/
#define GOSCA_MAC_LENGTH						8

#define GOSCA_MAXLEN_TVSNAME					20		/*���Ӫ�����Ƴ���*/
#define GOSCA_MAXLEN_PINCODE					8		/*���PIN�볤��*/
#define GOSCA_MAXLEN_MANUFACTURERNAME			20		/*���CAS�������ֳ���*/ 
#define GOSCA_LEN_SMARTCARD_SN					32		/*�ֻ�ܿ����кų��ȣ��ⲿ���ţ�*/

#define MAX_FILTER_BYTES							8		/*����������*/
#define	GOSCA_STB_MAXNUMBER_ENTITLPRODUCT			250		/*һ�ſ�����������Ȩ��Ʒ�ĸ���*/
#define GOSCA_STB_MAXLEN_PROMPTMESSAGE				255		/*ÿ����ʾ��Ϣ����󳤶�*/
#define GOSCA_MAXLEN_SERVICEPERECM					2		/*ÿ��ECM֧�ֵ����Service��Ŀ*/

#define GOSCA_MAXLEN_PRODUCT_NAME					21		/*��Ĳ�Ʒ����,���20���ַ�+\0*/
#define	GOSCA_MAXLEN_EMAIL_SENDERNAME				11		/*E-mail���������������11���ַ�+\0*/
#define	GOSCA_MAXLEN_EMAIL_CONTENT					1025	/*E-mail��󳤶ȣ����1024���ַ�+\0*/
#define	GOSCA_MAXLEN_EMAIL_SHORT_CONTENT			20
#define GOSCA_MAXLEN_ESPN							20

/*������ȡ˽�����ݵ������*/
#define GOSCA_STB_ECM_SLOT						1
#define GOSCA_STB_EMM_Private_SLOT				2
#define GOSCA_STB_EMM_Public_SLOT				3
#define GOSCA_STB_EMM_Serial_SLOT				4
#define GOSCA_STB_EMM_SerialEx_SLOT				5

//---------- ECM_PID���õĲ�������
#define GOSCA_LIST_OK					0x00
#define GOSCA_LIST_FIRST				0x02	
#define GOSCA_LIST_ADD					0x01

/*EMM���ܵȴ����ʱ��*/
#define	GOSCAS_EMM_RECEIVING_WAIT_TIME			0

/*���ܿ�״̬����*/
#define GOSCAS_SC_OUT							0		/*���ܿ����ڶ�������*/
#define GOSCAS_SC_IN							1		/*���ܿ��ڶ������У���������*/
#define GOSCAS_SC_IN_ERROR						2		/*���ܿ��ڶ������У�����������*/

/*Emm������״̬����*/
#define GOSCAS_EMMFILTER_RECEIVING				1		/*Emm���������ڽ���Emm����*/
#define GOSCAS_EMMFILTER_FREE					0		/*Emm����������*/

/*�������״̬����*/
#define GOSCAS_SC_PAIR_OK						0		/*���ܿ��뵱ǰ���������*/
#define GOSCAS_SC_NO_Pairing					1		/*���ܿ�û�����κλ��������*/
#define GOSCAS_SC_PAIR_OTHER					2		/*���ܿ��뵱ǰ������û�����*/

/*�տ�������*/
#define GOSCAS_Rating_3							3		/*3��*/
#define GOSCAS_Rating_4							4		/*4��*/
#define GOSCAS_Rating_5							5		/*5��*/
#define GOSCAS_Rating_6							6		/*6��*/
#define GOSCAS_Rating_7							7		/*7��*/
#define GOSCAS_Rating_8							8		/*8��*/
#define GOSCAS_Rating_9							9		/*9��*/
#define GOSCAS_Rating_10						10		/*10��*/
#define GOSCAS_Rating_11						11		/*11��*/
#define GOSCAS_Rating_12						12		/*12��*/
#define GOSCAS_Rating_13						13		/*13��*/
#define GOSCAS_Rating_14						14		/*14��*/
#define GOSCAS_Rating_15						15		/*15��*/
#define GOSCAS_Rating_16						16		/*16��*/
#define GOSCAS_Rating_17						17		/*17��*/
#define GOSCAS_Rating_18						18		/*18��*/

//email ��ʾ��Ϣ��
#define GOSCAS_EMAIL_NEW						0		/*���ʼ�֪ͨ*/
#define GOSCAS_EMAIL_NEW_NO_ROOM				1		/*�����ʼ�����Email�ռ䲻��*/
#define GOSCAS_EMAIL_NONE						0xFF	/*���ر�־*/

//email ״̬��	
#define GOSCAS_EMAIL_STATUS_INI					0		/*��ʼֵ*/
#define GOSCAS_EMAIL_STATUS_GOT					1		/*��get����*/
#define GOSCAS_EMAIL_STATUS_READ				2		/*��������*/

/*----------------------------------------------------------------------*/
/*                       �����Ƿ���ֵ����                               */
/*----------------------------------------------------------------------*/

/*�����з���ֵ��ֵ����*/
#define GOSCAERR_BASE_STB						0xF1000000

/*����ֵ����*/
#define GOSCA_OK								0 
#define GOSCA_FAILED							(-1)

#define GOSCAERR_STB_POINTER_INVALID			(GOSCAERR_BASE_STB + 1)		/*�����ָ����Ч*/
#define GOSCAERR_STB_DATA_LEN_ERROR				(GOSCAERR_BASE_STB + 2)		/*��������ݳ��Ȳ��Ϸ�*/
#define GOSCAERR_STB_TVS_NOT_FOUND				(GOSCAERR_BASE_STB + 3)		/*û���ҵ�����Ҫ�����Ӫ��*/
#define GOSCAERR_STB_EXCEED_MAX_COUNT			(GOSCAERR_BASE_STB + 4)		/*��������������ĸ���*/
#define GOSCAERR_STB_KEY_NOT_FOUND				(GOSCAERR_BASE_STB + 5)		/*û���ҵ�������Կ*/
#define GOSCAERR_STB_PIN_INVALID				(GOSCAERR_BASE_STB + 6)		/*�����PIN����Ч*/
#define GOSCAERR_STB_PIN_LOCKED					(GOSCAERR_BASE_STB + 7)		/*PIN�뱻����*/
#define GOSCAERR_STB_CMD_INVALID				(GOSCAERR_BASE_STB + 8)		/*MACУ�����*/
#define GOSCAERR_STB_VER_EXPIRED				(GOSCAERR_BASE_STB + 9)		/*����İ汾û��IC���еĴ󣬼������Ѿ�����*/
#define GOSCAERR_STB_EXCEED_MAX_LEN				(GOSCAERR_BASE_STB + 10)	/*��Ӫ�̵����Ƴ������ĳ���*/
#define GOSCAERR_STB_NO_SPACE					(GOSCAERR_BASE_STB + 11)	/*�Ѿ�û�пռ�*/
#define GOSCAERR_STB_IS_PAIRED					(GOSCAERR_BASE_STB + 12)	/*���ܿ��뵱ǰ�����ж�Ӧ*/
#define GOSCAERR_STB_NOT_PAIRED					(GOSCAERR_BASE_STB + 13)	/*���ܿ��뵱ǰ������û�ж�Ӧ*/
#define GOSCAERR_STB_COUNT_ISZERO				(GOSCAERR_BASE_STB + 14)	/*�����CountΪ0. */
#define GOSCAERR_STB_WORKTIME_INVALID			(GOSCAERR_BASE_STB + 15)	/*����ʱ�����ò��Ϸ���������ʱ�䲻��00:00:00~23:59:59֮�䣬���߿�ʼʱ����ڽ���ʱ�䡣*/
#define	GOSCAERR_STB_OVERFLOW					(GOSCAERR_BASE_STB + 16)	
#define	GOSCAERR_STB_CARD_INVALID				(GOSCAERR_BASE_STB + 17)	/*���ܿ���Ч*/
#define	GOSCAERR_STB_Rating_LOW					(GOSCAERR_BASE_STB + 18)	/*���ܿ����õ��տ�����ȵ�ǰ�տ��Ľ�Ŀ��*/
#define GOSCAERR_STB_UNKNOWN					(GOSCAERR_BASE_STB + 19)	/*δ֪����*/

#define	GOSCAERR_STB_EMAILBOX_EMPTY				(GOSCAERR_BASE_STB + 20)	/*E-mail����Ϊ��*/
#define	GOSCAERR_STB_NO_EMAIL					(GOSCAERR_BASE_STB + 21)	/*û�д�E-mail*/
#define	GOSCAERR_STB_EMAILBOX_FULL				(GOSCAERR_BASE_STB + 22)	/*E-mail������*/
#define	GOSCAERR_STB_NO_SECTION					(GOSCAERR_BASE_STB + 23)	/*û���յ�����Section*/

#define	GOSCAPAIR_GETINF_ERROR					(GOSCAERR_BASE_STB + 24)	/*��ȡ��ĸ����Ϣ����*/
#define	GOSCAPAIR_NOPAIR_ID						(GOSCAERR_BASE_STB + 25)	/*ĸ�����ӿ��ź��ӿ���ĸ���Ų�ƥ��*/
#define	GOSCAPAIR_SMART_MOTHER					(GOSCAERR_BASE_STB + 26)	/*��ǰ��������ĸ��*/
#define	GOSCAPAIR_SMART_SON						(GOSCAERR_BASE_STB + 27)	/*��ǰ���������ӿ�*/

//��ĸ����Դ�����Ϣ
#define	GOSCAPAIR_GETOPERATION_ERROR			(GOSCAERR_BASE_STB + 30)	/*��ȡ��Ӫ�̷�����Ϣ�������ܿ�û�н��ܵ�������Ϣ��ͨ�Ŵ���*/
#define	GOSCAPAIR_SMART_TYPE_ERROR				(GOSCAERR_BASE_STB + 31)	/*������Ŀ�����Ҫ���������̲�ƥ�䣬��������Ҫ������ӿ���ʵ�ʼ�����Ĳ����ӿ�*/
#define	GOSCAPAIR_SMART_GETMASTERINF_ERROR		(GOSCAERR_BASE_STB + 32)	/*��ȡ������ĸ���������Ϣ����ʧ�ܣ�*/
#define	GOSCAPAIR_SMART_GETSLAVEINF_ERROR		(GOSCAERR_BASE_STB + 33)	/*��ȡ�ӿ����ӿ��������Ϣ����ʧ�ܣ�*/
#define	GOSCAPAIR_SMART_NOPAREID_ERROR			(GOSCAERR_BASE_STB + 34)	/*���ӿ���ԺŲ�һ�£�*/
#define	GOSCAPAIR_MSPARE_FAILURE_ERROR			(GOSCAERR_BASE_STB + 35)	/*���ӿ������ʧ�ܣ�*/
#define	GOSCAPAIR_PROCESS_TYPE_ERROR			(GOSCAERR_BASE_STB + 36)	/*�������̲��費�Ϸ���*/

//ǿ�ƻ�̨����
#define GOSCA_MAXNUM_COMPONENT	5
#define GOSCA_MAXLEN_LOCKMESS      	40

/*������ң��������ȡ������ʾ��Ϣ�б�*/
#define GOSCA_No_OSDPromt						0			/*��OSD��ʾ*/	

#define	GOSCA_SMART_STOP						1			/*���Ա�����*/
#define GOSCA_SMART_AREA_NOPAIR					2			/*��������ƥ��*/
#define GOSCA_SMART_IPPT_SWITCH					3			/*IPPT�û���ʾ*/
#define	GOSCA_SMART_STB_NOPAIR					4			/*���������,�����󶨲�ƥ��ʱ��ʾ*/
#define	GOSCA_SMART_PROG_NOENTITLE				5			/*��Ŀ��δ��Ȩ*/
#define	GOSCA_SMART_PROG_NOENTITLE_IPPT			6			/*��Ŀ��δ��Ȩ*/
#define	GOSCA_SMART_MOTHER_SON_PAIR				7			/*��ĸ����������*/
#define	GOSCA_SMART_MOTHER_SON_TIMEOUT			8			/*��ĸ����Գ�ʱ*/
#define	GOSCA_SMART_PAIR_OK						10			/*������ӦOK*/
#define	GOSCA_SMART_LAST_DAY					11			/*�����ʾ����*/

#define GOSCA_SMART_AREA_LOCK					0x10		/*���������� */
#define GOSCA_SMART_CARD_LOCK					0x11		/*���ѱ����� */
#define GOSCA_SMART_IPPT						0x12		/*IPPT��ʾ*/
#define GOSCA_SMART_LIMIT_WATCH					0x13		/*�������տ�*/
#define GOSCA_SMART_NO_WORK_TIME				0x14		/*�����ڹ���ʱ���*/
#define GOSCA_SMART_AREA_CONTROL_ERROR			0x15		/*��û�й�������ȷ�ķ�����*/
#define GOSCA_BIND_INFO_ERROR					0x16		/*�����󶨴���+����ID*/

#define GOSCA_SMART_IDRUN_ERROR					0x17		/*��������������Ч����*/
#define GOSCA_SMART_LEVEL_ERROR					0x18		/*���Ĺۿ�������ڽ�Ŀ����*/
#define GOSCA_PVR_ENTITLE_TIMEOUT				0x19		/*PVR ��Ȩ�ļ�����*/

#define GOSCA_SMART_OUT							0x20		/*��Ŀ���ţ���忨*/
#define GOSCA_SMART_INVALID						0x21		/*�����뿨�Ǹ�˹����CA��*/
#define	GOSCA_SMART_STB_NOBIND					0x22		/*����δ��ʱ��ʾ*/
#define	GOSCA_CASID_BIND_ERROR					0x23		/*��������Ӫ��ID����Ӫ��ID�󶨴���*/
#define	GOSCA_CASID_SOL_ERROR					0x24		/*��������SOL��Ϣ���մ���*/

#define	GOSCA_SMART_UNKNOWN_ERROR				0xFF		/*δ֪����*/

/*----------------------------------------------------------------------*/
/*                       ������һЩ���ݽṹ����                         */
/*----------------------------------------------------------------------*/
/*�ź�������*/

typedef unsigned int  GOSCA_Semaphore ;

//hourn ��������Ѷ�Ķ����ͻ,�޸�����
typedef void (*pThreadFunc_gos) (void);/*�̺߳�����ַ����*/

typedef struct _SGOSDate{
	unsigned int 	m_wYear;
	unsigned int 	m_wMonth;
	unsigned int 	m_wDay;
}SGOSDate;

typedef struct _SGOSTime{
	unsigned int 	m_wHour;
	unsigned int 	m_wMinute;
	unsigned int 	m_wSecond;
}SGOSTime;

typedef struct _SGOSDateTime{
	SGOSDate   	m_tDate;
	SGOSTime  	m_tTime;
}SGOSDateTime;

typedef struct _GOSCAServiceEntitle_Ex{
	unsigned short 		m_wProductID;
	unsigned long		m_tStartTime;				/*��ʼʱ��*/
	unsigned long		m_tEndTime;					/*����ʱ��*/
}SGOSCAServiceEntitle_Ex;		/*��ͨ��Ʒ��Ȩ*/

typedef struct _GOSCAServiceEntitle_Ex_Print{
	char 		m_ProductID[5];			/* "0001" */
	char		m_StartTime[20];		/* "06/15/2012 14:30:25" */
	char		m_EndTime[20];			/* "07/15/2012 14:30:25"��"N.A" */
}SGOSCAServiceEntitle_Ex_Print;		/*��ͨ��Ʒ��Ȩ��ӡ*/

typedef struct _GOSCAServiceInfo{
	unsigned short 	m_wEcmPid;			/*����*/
	unsigned short 	m_wOriNetworkID;	/*����2.0��չ*/
	unsigned short 	m_wTSID;			/*����2.0��չ*/
	unsigned char   m_byServiceCount;	/*����2.0��չ*/
	unsigned short 	m_wServiceID;	/*����2.0��չ*/
}SGOSCAServiceInfo;


typedef struct _SCAS2STBStatusInfo{
	unsigned char 	m_bStatusTpyeFlag;
	unsigned char 	m_bStatusInfo[6];
}SCAS2STBStatusInfo;

typedef struct _GOSPIN{
	unsigned char	m_byLen;
	unsigned char	m_byszPin[GOSCA_MAXLEN_PINCODE];
}SGOSPIN;

typedef struct _GOSCAEmailVersion{
	unsigned char	m_state;//0:��Ч��1��δ���ʼ���2�Ѷ��ʼ�
	unsigned long	m_version;//�����ʼ���ʱ�䡣
}GOSCAEmailVersion;

typedef struct _GOSCAEmailTotal{
	unsigned char		m_Email_All;//�ܵ��ʼ���
	unsigned char		m_Email_New;//δ���ʼ���
	GOSCAEmailVersion	m_Email_versions[GOSCA_MAX_EMAIL_ID_COUNT+1];
}GOSCAEmailTotal;

//ADD BY GOS
typedef struct _SCardWorkInfo{
	unsigned char	bCardPinStatus;
	unsigned char 	bWatchRating;
	unsigned char 	bMatureDays;
	SGOSTime 		tStarttime;
	SGOSTime 		tEndtime;
	unsigned char 	m_bIPPTWorkMode;
	unsigned char 	m_bReserved0;
	unsigned char 	m_bReserved1;
	unsigned char 	m_bReserved2;
	unsigned char 	m_bReserved3;
	unsigned char 	m_bReserved4;		
}SCardWorkInfo;

typedef struct _SOperatorInfo{
	unsigned long  	m_dwMotherCardID;  //1-4
	unsigned char   m_bStandardFlag;     //5
	unsigned long   m_dwDecryptCWTimes; //6-9
	unsigned long   m_dwIntervalTime;   //10-13
	unsigned int    m_wRunArea;         //14-15
	unsigned char   m_bUserVIPClass;    //16
	unsigned long   m_dwUserArea;       //17-20 
	unsigned char	m_bTVSName[GOSCA_MAXLEN_TVSNAME]; //21-40
	unsigned char   m_bTVSOtherInfo[GOSCA_MAXLEN_TVSNAME]; //41-60	
}SOperatorInfo;

typedef struct _GOSCAEmailHead{
	unsigned char		m_Slot;//��ʱδ��
	unsigned long		m_version;
	unsigned char		m_Title_len;
	unsigned char		m_Title[GOSCA_MAX_EMAIL_TITLE];
}GOSCAEmailHead;

typedef struct _GOSCAEmailContent{
	unsigned char		m_Slot;//��ʱδ��
	unsigned long		m_version;									
	unsigned int		m_Content_len;
	unsigned char		m_Content_Data[GOSCA_MAX_EMAIL_CONTENT];					
}GOSCAEmailContent;

typedef struct _GOSCAMontherSonInfo{
	unsigned long	m_dwMontherCardID;				//ĸ������
	unsigned long	m_dwSonCardID;					//�ӿ�����
	unsigned long	m_dwCardWorkTime;				//��ǰ���Ĺ���ʱ��
}SGOSCAMontherSonInfo;

typedef struct _SSC2STBConditionPlay{
	unsigned short 	m_wProductID;
	bool			m_bEnd;
	bool			m_bTapingFlag;
	unsigned long	m_tStartTime;
	unsigned long	m_tEndTime;
}SSC2STBConditionPlay;

/*-- Ƶ��������Ϣ --*/
/*-- ��Ŀ�����Ϣ --*/
typedef struct {    /* �������֪ͨ�����н�Ŀ���ͼ�PID����Ϣ��һ����Ŀ���ܰ��������� */
    unsigned short   m_wCompPID;     /* ���PID */
    unsigned short   m_wECMPID;      /* �����Ӧ��ECM����PID���������ǲ����ŵģ���Ӧȡ0�� */
    unsigned char    m_StreamContent;
    unsigned char    m_CompType;     /* ������� */
    unsigned char    m_byReserved[3];/* ���� */
}SGOSCAComponent;

/*-- Ƶ��������Ϣ --*/
typedef struct {    
    unsigned long    		m_dwFrequency;              /* Ƶ�ʣ�BCD�� */
    unsigned long   	 	m_symbol_rate;              /* �����ʣ�BCD�� */
	unsigned short			m_wServerid;                /* Servers id */
    unsigned short			m_wPcrPid;                  /* PCR PID */
    unsigned char    		m_Modulation;               /* ���Ʒ�ʽ */
    unsigned char    		m_ComponentNum;             /* ��Ŀ������� */
    SGOSCAComponent 		m_CompArr[GOSCA_MAXNUM_COMPONENT];       /* ��Ŀ����б� */
    unsigned char    		m_fec_outer;                /* ǰ��������� */
    unsigned char    		m_fec_inner;                /* ǰ��������� */
    char       				m_szBeforeInfo[GOSCA_MAXLEN_LOCKMESS+1]; /* ���� */
    char       				m_szQuitInfo[GOSCA_MAXLEN_LOCKMESS+1];   /* ���� */
    char       				m_szEndInfo[GOSCA_MAXLEN_LOCKMESS+1];    /* ���� */
    unsigned char			lock_flag;                               /* �Ƿ�����ǰ����ң������־ */
}SGOSCALockService;

/*-- PVR�����ļ�����ID --*/
typedef struct PVR_File_ID{
	unsigned long		m_TimeCreate;	/* PVR�ļ�����ʱ�� */
	unsigned long		m_SerialID;		/* �����е����к�ID */
	unsigned short		m_ServerID;		/* PVR��Ŀ�Ľ�Ŀ�� */
}GOSCAPVR_File_ID;

/*-- ����Ĭ�ϻ�̨��Ŀ --*/
typedef struct {    
	unsigned char			m_DVB_Type;					/* ָ��Ƶ���������0��DVBC 1��DVBS;2��DVBT*/
	unsigned char			m_TP[13];					/* ��׼����Ƶ����Ϣ���ݣ����������ʣ�Ƶ�ʣ����Ʒ�ʽ��*/

	unsigned short			m_wServerid;                /* Servers id */
	unsigned short			m_wPcrPid;                  /* PCR PID */

	unsigned char    		m_ComponentNum;             /* ��Ŀ������� */
	SGOSCAComponent 		m_CompArr[GOSCA_MAXNUM_COMPONENT];       /* ��Ŀ����б� */
	unsigned char			lock_flag;                               /* �Ƿ�����ǰ����ң������־ */
}SGOSCAStartService;

#ifdef __cplusplus
}
#endif

#endif	

