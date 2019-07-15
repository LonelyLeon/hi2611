#ifndef _GOSCA_INTERNAL_H_
#define _GOSCA_INTERNAL_H_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#define CA_MAX_PIN_LENGTH_GOSCA         6U

#define MAX_TASK_NUMBER_GOSCA         	5U

#define MAX_SEMA_NUMBER_GOSCA         	30U

#define MAXLEN_TVSNAME_GOSCA  		    24U

#define MAXLEN_PRODUCT_NAME_IPP_GOSCA   24U

#define MAXLEN_FEEDDATA_LEN_GOSCA 	    256U

#define MAXLEN_EMAIL_SENDERNAME_GOSCA   12U

#define MAXLEN_EMAIL_TITLE_GOSCA 		32U

#define MAXLEN_EMAIL_CONTENT_GOSCA 	    1025U

#define EMAIL_COUNT_GOSCA				20U

#define OPERATOR_COUNT_GOSCA			5U

#define ENTITLE_COUNT_GOSCA 			250U

#define ENTITLE_COUNT_PER_PAGE_GOSCA 	10U

#define IPP_COUNT_GOSCA 				250U

#define SLOTID_TOTAL_GOSCA            	20U

#define CA_INNO_LEN_GOSCA          		20U

#define CA_EXNO_LEN_GOSCA          		64U

#define CA_PCARD_LEN_GOSCA		 	    24U

#define CA_COREVER_LEN_GOSCA       		20U

#define CA_SWVER_LEN_GOSCA         		21U

#define CA_AERA_LEN_GOSCA          		12U

#define CA_RATING_LEN_GOSCA         	20U

#define CA_WORKTIME_LEN_GOSCA         	20U

#define CA_COS_LEN_GOSCA				4U

#define MAXLEN_PRODUCT_NAME_GOSCA 	    24U

#define MAXLEN_SERVICE_NAME_GOSCA 	    24U

#define MAXLEN_OSD_GOSCA   	    255U

#define MAX_OSD_NUM_GOSCA               10U

#define CHIPID_LEN_GOSCA		    6U

typedef enum
{
     MASTER_CARD,
     SLAVE_CARD,
     EXIT_MASTER_SLAVE
} Pair_Type;


typedef struct{
	uint8_t newEmail;  			//�ʼ�״̬�����ʼ���ǣ�0���Ѷ��ʼ���1�����ʼ�
	char emaildate[40];                   //�ʼ����ڡ�ʱ��
    char emailtitle[CA_INNO_LEN_GOSCA];       //�ʼ�����
}hrgosca_emailInfo_t;								

typedef struct{
	char version[12];                        					//����ʱ��
	char emailLength[6];                     					//�ʼ����ݳ���
	int8_t	email[MAXLEN_EMAIL_CONTENT_GOSCA];        		//�ʼ�����
}hrgosca_emailContent_t;//GOSCA_V190

typedef struct{
   	char productId[5];     							//��ƷID   (SCDCAEntitle.m_dwProductID for cdca)	
	char startTime[30];//huangbo 40    							//��ʼʱ�䣬time_t��ʽ�� 2012-05-07  09:12:34
	char endTime[30];  //huangbo 40					//����ʱ�䣬time_t��ʽ�� 2012-08-08  09:12:34
}hrgosca_serviceEntitles_t;//GOSCA_V190


//������Ѷû�з���Ȩ
typedef struct{
    uint8_t Detitle[2];
}hrgosca_detitleInfo_t;

typedef struct {
    uint16_t OriNetID;
	uint16_t TSID;
	uint16_t ServiceID;
	uint16_t Duration;
	uint8_t lock_flag; //ǿ����̨���Ƿ���Ӧң����
}hrgosca_SwitchChannel_t;//huangbo 20130219

typedef struct {
	uint32_t price;     //  ��/����
	uint32_t balance;   //���  ��
	uint32_t time;      //ʣ��ʱ��
}hrgosca_ippBuyInfo_t;


typedef struct {
    uint8_t reserve;
}hrgosca_viewedIpp_t;



typedef struct {
    uint8_t scState;					//:���ܿ��Ѿ����룻0����������Ч���ܿ�
    char scNo[CA_INNO_LEN_GOSCA];			  		//���ܿ��ڲ�����
    char stbNo[CA_INNO_LEN_GOSCA];			//���������к�
    char scVer[CA_INNO_LEN_GOSCA];			//���ܿ��汾��;
    uint8_t isPinLocked;				//:���ܿ���������0��δ������
    char scRating[3];           			//���ܿ��ۿ�����
    char scWorktime[CA_WORKTIME_LEN_GOSCA];     	 	//���ܿ�����ʱ��
    char scMatureDays[CA_INNO_LEN_GOSCA];				//������ʾ����
    uint8_t ipptmode;				//IPPTģʽ
    char stbNo_v190[CA_INNO_LEN_GOSCA];		//���������к�,  V1.9�汾�Ŀ��V2.08�Ŀ���ڰ汾ר�� 
 //0����ʹ�ã�1��̨ѡ��ʹ��(�ݲ�֧�֣���2��̨��ʾ��3��Զʹ�ã���̨����ʾ
    char chipID[CHIPID_LEN_GOSCA];				//оƬID��һ����4���ֽ�
}hrgosca_scBasicInfo_t;


typedef struct {
	
	char  scMasterCardID[CA_INNO_LEN_GOSCA];					//	ĸ������
	char  scIntervaltime[CA_INNO_LEN_GOSCA];					//	��Լ��ʱ��
	char  scRunArea[CA_INNO_LEN_GOSCA];						//	��������
	char  scUserAreaCode[CA_INNO_LEN_GOSCA];					//	�û�������
	char   scUserVIPClass[CA_INNO_LEN_GOSCA];					//	�û�����
	char   scOperatorName[CA_INNO_LEN_GOSCA];					//	��Ӫ������
	char  scSTBAreaCode[CA_INNO_LEN_GOSCA];					//	������������
	uint8_t scardstate;//0 ��ʾΪ�ӿ� 1 ��ʾΪĸ��
	
}hrgosca_operatorInfo_t;
typedef struct {
	
	char  scStbSeriesID[20];							//	���������к�
	char  scSmartcardID[20];							//	���ܿ���
	char  scStbBindinfo[5][10];							//	�����а���Ϣ
	char  scCardBindinfo[10];							//	������Ϣ
}hrgosca_scBindInfo_t;//huangbo for STB

typedef struct {

    uint8_t scHour;          				//ʱ
    uint8_t scMin;						//��
    uint8_t scSec;						//��
    
}GOSTIME_SET;

typedef struct {

    uint8_t scRating;          				//���ܿ��ۿ�����
    uint8_t scMatureDays;				//������ʾ����
    GOSTIME_SET scStarttime;     	 	//���ܿ���ʼ����ʱ��
    GOSTIME_SET scEndtime;     	 		//���ܿ���������ʱ��
    uint8_t ipptmode;					//IPPTģʽ
	
}hrgosca_scCAOtherset_t;

typedef struct {
    uint8_t MesageNo;					//:��ʾ��Ϣ��ID��

	uint32_t Message_ParaH;				//:��ʾ��Ϣ����H��������ϢID�в�ͬ���壻
	uint32_t Message_ParaL;				//:��ʾ��Ϣ����L��������ϢID�в�ͬ���壻

	uint8_t bShowNotify;				//:�Ƿ����Զ����ַ�����ʾ��
    char Message_notify[1048];			//:�Զ����ַ�����ʾ���ݣ�
}hrgosca_caMessage;

typedef struct {
    uint8_t scType;                           		//������ 0:ĸ��1:�ӿ�
    char pCardNo[CA_PCARD_LEN_GOSCA];			  			//ĸ������
    uint8_t scPscData[MAXLEN_FEEDDATA_LEN_GOSCA];   		//ι������
    uint8_t scDataLen;                        		//ι�����ݳ���
    
}hrgosca_scAddedInfo_t;

typedef struct {
	uint8_t slotId;
    char  slotCreditLimit[12];    					//���ö�(����) 
    char  balance[12];    							//�ѻ��ĵ���
}hrgosca_slotInfo_t;

typedef struct{
   	char productId[5];     							//��ƷID   '0001'	
	char startTime[30];    							//��ʼʱ��'12/21/2012 09:12:34'
	char endTime[30];      						//����ʱ��'12/25/2012 23:59:59'
}hrgosca_Entitles_info_t;//GOSCA V208

typedef struct{
	char OsdMsg[CHIPID_LEN_GOSCA + 1];
	unsigned short times;
	char breakFlag;
}hrgosca_Osd_info_t;//huangbo 0326

typedef struct {
	uint16_t x;
	uint16_t y;	
}hrgosca_Point;

typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
}hrgosca_Rect;

typedef struct {
	uint8_t	region_no;	// ��ʾ������OSD��� 	�ڲ��̶�����ֵ���ô���																				
	hrgosca_Rect	bg_rect;	// ��ʾ�ķ�Χ��������ʼx���꣬��ʼY���꣬��ȣ��߶�				
	uint8_t	show_flag;	// �������� 0������ 1����ʾ																			

	uint8_t type;   		// osd type: 0: common 1: force
	uint8_t style;			//0: ������ʾ��1: �ı���ʾ�������ţ�2����ʾ�ı��������
	uint8_t stylevalue;	 // styleΪ0 ��������Ϊ1: �Ϸ������� 2: �·�������3:Ϊ�м����
				// styleΪ1��������Ϊ�趨�ı���ռ��Ļ�İٷֱȣ�ֵΪ20%-80%
	uint8_t lock;
	uint32_t bg_color; 	// OSD bg color	  AGRB	 ��0x80ffffff Ϊ��͸����ɫ
	hrgosca_Point fg_pos; 	// OSD fg pos	  ��ʾ�ַ���λ��
	uint32_t fg_color; 	// OSD fg color	  AGRB
	uint8_t font_size; 	// osd fg font size 18~72
	char * text; 		// osd fg test point   ��ʾ����ָ��
	uint16_t text_len; 		// osd fg test point   ��ʾ����ָ��
	uint8_t repeat;		// �������ظ��Ĵ���
	uint8_t time;			// ��������������ʱ��	  ����osdʱ��Ч
}hrgosca_ForceOSD_info;

typedef struct {
	uint8_t	region_no;		// ��ʾ������OSD��� �ڲ��̶�����ֵ���ô���																					
	hrgosca_Rect	bg_rect;		// ��ʾ�ķ�Χ��������ʼx���꣬��ʼY���꣬��ȣ��߶�				
	uint8_t	show_flag;		// �������� 0������ 1����ʾ	 ǰ�η�������																		

	uint8_t	type;   		//	fingerprint type: 0: common 1: force
	uint8_t	force_type; 	//	force fingerprint type: 0: not visible  1: show info
	uint32_t	bg_color; 	//	fingerprint bg color	  AGRB	��0x80ffffff Ϊ��͸����ɫ
//	D_Point fg_pos; 		//	fingerprint fg pos	  
	uint32_t	fg_color; 	//	fingerprint fg color	  AGRB
	uint8_t	font_size; 	//	osd fg font size 18~72
	uint8_t	text_type; 	//	��6λ��ʾ���ͣ���00�����ţ�01�����кţ�02���ż����кţ�0x03: ����+�û��Զ�������, 0x04: ���к�+�û��Զ�������, 0x05: ����+�����к�+�û��Զ������ݣ�
	char text[255]; 		//	fingerprint fg test point  Ҫ��ʾ���ַ���ָ��
	uint16_t	text_len; 	//	osd fg test point   ��ʾ����ָ��
	uint8_t	chnl_cnt;	//	ָ����ʾƵ���������Ϊ0 ����ʾ����Ƶ������ʾָ��  ��0����ʾServiceId����service id��Ŀ��Ŀǰ�汾���֧��ָ��10��Ƶ��
	uint16_t service_id[10];	//	��ʾָ��Ƶ����service id
	uint16_t	interval;		//	ʱ����,������ʾ֮��Ĳ���ʾָ�Ƶ�ʱ�䳤��
	uint8_t	lock;		//	�Ƿ������û����� 1: �����û�������0: ������
	uint8_t	pos_type;	//	ָ��λ�����ͣ�0 : �̶�λ����ʾ(ͨ�������Ͻǣ���1: ���û��Զ��壬����Pos_X,Pos_Y����������ʾ����2�����
}hrgosca_ForceFinger_info;


//�ۿ�����
extern uint8_t d_ViewRating;
//��Ӫ����Ϣ
extern uint8_t d_OperatorCount;
//��Ӫ�̱��
extern uint16_t d_TVSId[5];
//�ʼ�����
extern uint16_t d_EmailCount;
//δ���ʼ�����
extern uint16_t d_NewEmailCount;
//ʣ���ʼ�����
extern uint16_t d_EmptyEmailCount;

#endif

