#ifndef CAS_HCN_H
#define CAS_HCN_H
/*
typedef signed char INT8;
typedef unsigned char UINT8;
typedef signed short INT16;
typedef unsigned short UINT16;	
typedef long INT32;	
typedef unsigned long UINT32;	
typedef unsigned char 	bool;
*/

typedef long time_t;	
typedef signed short cas_channel_id;
typedef signed short cas_filter_id;


#define MAX_SEC_MASK_LEN 	16
#define INVALID_FILTER_ID	-1

#define HCN_RET_TRUE  		1
#define HCN_RET_FALSE 		0
#define HCN_RET_SUCCESS  	0
#define HCN_RET_FAILURE  	1

#define HCN_OUT
#define HCN_IN
#define HCN_IO

//���ܿ�״̬����ֵ
#define IRW_NO_ERROR					0/*��ȷ*/
#define IRW_ERROR						-1/*����*/
#define IRW_WRITE_ERROR					-2/*д����*/
#define IRW_READ_ERROR					-3/*������*/
#define IRW_STATUS_ERROR				-4/*״̬�ִ���*/
#define IRW_RESET_AUTHRITY_ERROR 		-5/*��֤����*/

/*�����Ҫ���ݲ�ͬ��ƽ̨����,
һ����˵C51��Ҫ�������壬����ƽ̨���Զ�Ϊ��
*/
#define CASDRVFUNCPOSTFIX //large reentrant 

typedef enum  
{	//��ʾ֪ͨ
	DISP_NO_MSG = 0,		//��CA��Ϣ
	DISP_PLS_INSERT_SMC,	//��忨
	DISP_SMC_INSERT,		//���ܿ�����
	DISP_SMC_REMOVED,		//���ܿ�ȡ��
	DISP_SMC_INIT_SUCCEES,	//���ܿ���ʼ���ɹ�
	DISP_SMC_INIT_FAIL,		//���ܿ���ʼ��ʧ��
	DISP_SMC_READ_ERROR, 	//��������
	DISP_CARD_NOMATCH,      //���������
	DISP_MATCH_SUCCESS,		//��Գɹ�
	DISP_MATCH_FAIL,		//���ʧ��
	DISP_NO_RIGHT,			//�޽�ĿȨ��010
	DISP_TIMEEXPIRED,		//��Ч���ѹ�
	DISP_INSTANCE_CLOSE,	//��ʱ�ض�
	DISP_OUT_WORKTIME,		//���ڹ���ʱ��
	DISP_MASK_LIMITED,		//�����޲�
	DISP_OUT_LEVEL,			//�������տ�����
	DISP_TYPE_LIMIT,		//¼���������
	DISP_PPV,				//ppv��Ŀ
	DISP_PPC,				//ppc��Ŀ
	DISP_PPV_AWARD_SUCCESS,	//ppv��Ŀ��Ȩ�ɹ�
	DISP_PPV_AWARD_FAIL,	//ppv��Ŀ��Ȩʧ��20
	DISP_PPC_AWARD_SUCCESS,	//ppc��Ŀ��Ȩ�ɹ�
	DISP_PPC_AWARD_FAIL,	//ppc��Ŀ��Ȩʧ��
	DISP_REMAIN_DAY,		//�տ���Ч�ڻ��� 9�죬������
//////////////////////
	DISP_CANCEL_MATCH,      //��ȡ�����
	DISP_CANCEL_MATCHFAIL,  //ȡ�����ʧ��
	DISP_SMC_NOTOPEN,//26		//���ܿ�δ����
    DISP_CREDIT_CONUT_FULL,	//��������
    DISP_UNRECOGNISED_CARD, //�޷�ʶ�����ܿ�
    DISP_ERRORVERSION_CARD, //���ܿ��汾����
    DISP_ippv_eventzreo, 	//ippv�¼���Ϊ��30
 /////////////////////////      
	//����֪ͨ
	HCNCAS_MAIL_NOTIFY = 0x62,//�ʼ�
	HCNCAS_SUBTITLE_NOTIFY,	//��Ļ
	HCNCAS_DISPALY_FINGER_NOTIFY,//��ʾָ��
	HCNCAS_STOP_FINGER_NOTIFY,	//ָֹͣ��	
	HCNCAS_DISPLAY_URGE_FEE_NOTIFY,//display upge_fee
	HCNCAS_STOP_URGE_FEE_NOTIFY,//stop display  upge_fee	
	HCNCAS_IPPV_SHOW,		//IPPV show
	HCNCAS_IPPV_CLOSE,		//IPPV close
	HCNCAS_REFILT_PMT,		//���´���PMT�����������������������CA
}cas_disp_msg;

#define MAX_PROVIDER_NAME 20
#define MAX_CARDPROVIDER_NAME 10
#define HCN_CHARACTER_MAX_NUM	(254+1)//�ֽ�


/****SMC info  for display***/
typedef struct hcnca_SMCinfor
{
	UINT8 CARD_LABEL[MAX_CARDPROVIDER_NAME];	//��Ӫ��
	UINT8 CAM_VER[4];	//CAS�汾
	UINT8 CARD_STATUS;	//���ܿ�״̬
	UINT8 PAIR_STATUS;	//���״̬
	UINT8 PARENTAL_RATING;	//���˼���
	UINT32 IC_NO;	//���ܿ�����
	UINT8 OPERATION_ID[3];	//��Ӫ��ID
}hcncas_smcinfo;

/****entitle  info  for display***/
typedef struct hcncastb_ppcentitle
{
	UINT8 index[1];		//ppc��Ŀ����Ȩ��Ϣid
	UINT8 Start_Time[4];	//��ʼʱ��
	UINT8 End_Time[4];	//����ʱ��
}HCNCAS_PPCENTITLE;
/****purse  info  for display***/
typedef struct hcncastb_purse
{
	UINT8 provider_id;	//��Ӫ��Ǯ��ID
	INT32 credit;			//��������
	INT32 consume;		//���ѵ���
}HCNCAS_PURSE;
/****ippv  info  for display***/
typedef struct hcncastb_ippv
{
	UINT8 provider_id;	//��Ŀ��Ӫ��ID
	UINT8 ippeventid[2];	//��Ŀ�¼���
	UINT8 tokenprice;		//�����۸񣬵�����ʾ
	UINT8 overtime[4];		//����ʱ�����ʱ��
}HCNCAS_IPPV;
/****ippv  info  for display***/
typedef struct hcncastb_ippv_all
{
	UINT8 ippeventid[2];//event id
	UINT8 overtime[4];	//end time 
}HCNCAS_IPPV_ALL;

/*�������������ýṹ*/
typedef struct HCN_RESTRICT{
	UINT8  mask[MAX_SEC_MASK_LEN];
	UINT8  value[MAX_SEC_MASK_LEN];
	UINT8  mask_len;
}hcn_restrict;
/****  for move osd***/
typedef struct hcncas_osd_g{	
	UINT8 id;
	UINT8 font_color;
	UINT8 bg_color;
	UINT8 subdata[HCN_CHARACTER_MAX_NUM];	
	UINT8 len;
}hcncas_osd;

/*time struct*/
typedef struct Time_T
{
	UINT16 year;	
	UINT8  month;
	UINT8  day;	
	UINT8  hour;
	UINT8  min;
	UINT8 sec;		
}ca_time;

/*
˵�� ��
	���ź������г�ʼ��
���õ����ӣ�
	UINT32  Semaphore1;
	hcncas_create_signal(&Semaphore1,1);
*/
void hcncas_create_signal(UINT32* pSemaphore , UINT8 bInitVal)CASDRVFUNCPOSTFIX;
void hcncas_send_signal(UINT32* pSemaphore)CASDRVFUNCPOSTFIX;
void hcncas_get_signal(UINT32* pSemaphore)CASDRVFUNCPOSTFIX;
void hcncas_del_signal(UINT32* pSemaphore)CASDRVFUNCPOSTFIX;
/*
˵�� ��
	����ǰ����time ��ʱ����ms
���õ����ӣ�
	hcncas_task_sleep(5);	
*/
void hcncas_task_sleep(UINT16 time)CASDRVFUNCPOSTFIX;
/*
˵�� ��
	����һ�� ��Ϣ����
���õ����ӣ�
	UINT32  msgid;
	hcncas_create_msgqe(&msgid,"HCNCAS");
*/
void hcncas_create_msgqe(UINT32 *message_queue_id ,UINT8 *queue_name)CASDRVFUNCPOSTFIX;
void hcncas_send_queue(UINT32 QUEUE_ID,UINT8 *DATA,UINT32 LEN,UINT32 TIME_DELAY)CASDRVFUNCPOSTFIX;
INT32 hcncas_receive_queue(UINT32 QUEUE_ID,UINT8 *DATA,UINT32 *LEN,UINT32 TIME_DELAY)CASDRVFUNCPOSTFIX;
/*
˵�� ��
	����һ���ں�����
���õ����ӣ�
	hcncas_register_task("HCNCASTASK",8,(void *)ca_man,NULL,0x4000);
*/
void hcncas_register_task(char *Name, UINT8 byPriority,void* pTaskFun,void* pParam, UINT32 nStackSize)CASDRVFUNCPOSTFIX;
/*
˵�� ���ڴ����
���õ�����:
	char  test[]="ABCDEFGHABCDEFGH";
	char* pTmp = (char*)hcncas_malloc(sizeof(test)+1);
	if(pTmp==NULL) return;
	hcncas_memset(pTmp,0,sizeof(test)+1);
	hcncas_memcpy(pTmp,test,sizeof(test));
	hcncas_free(pTmp);
*/
void hcncas_memcpy(void *des,void *src,UINT32 LEN)CASDRVFUNCPOSTFIX;
void hcncas_memset(void *des,UINT8 value,UINT32 LEN)CASDRVFUNCPOSTFIX;
INT32 hcncas_memcmp(void *src1,void *src2,UINT32 LEN)CASDRVFUNCPOSTFIX;
void* hcncas_malloc(UINT32 byBufSize)CASDRVFUNCPOSTFIX;
void  hcncas_free(void* pBuf)CASDRVFUNCPOSTFIX;
/*
˵�� ���ж��ʼ����Ƿ�����
���õ�����:
	if(hcncas_is_email_full(0) == 0)
		printf("�ʼ����������ֵ");
	else
	       printf("�ʼ���δ�ﵽ���ֵ");
*/
UINT8 hcncas_is_email_full(void)CASDRVFUNCPOSTFIX;
/*
˵�� ��ͨ������������
���õ�����:
	cas_channel_id cid;
	cas_filter_id fid;
	cid = hcncas_allocatechannel(emmpid,10);
	if(cid < 0)
	      printf("error");
	fid = hcncas_allocatefilter(cid,&mask);
	if(fid < 0)
	      printf("error");	
	hcncas_startchannel(cid);

	hcncas_freefilter(channel-d,fid);
	hcncas_freechannel(cid);
*/
cas_channel_id hcncas_allocatechannel(UINT16 PID,UINT8 wait_seconds)CASDRVFUNCPOSTFIX;
INT8 hcncas_freechannel(cas_channel_id channel_id)CASDRVFUNCPOSTFIX;
INT8 hcncas_startchannel(cas_channel_id channel_id)CASDRVFUNCPOSTFIX;
cas_filter_id hcncas_allocatefilter(cas_channel_id channel_id, hcn_restrict* MASK)CASDRVFUNCPOSTFIX;
UINT8  hcncas_freefilter(cas_channel_id channel_id,cas_filter_id filter_id)CASDRVFUNCPOSTFIX;
void hcncas_setcw(UINT8 *pbyOddKey,UINT8 *pbyEvenKey,UINT16 ECM_PID)CASDRVFUNCPOSTFIX;
/*
˵�� �����ܿ���λ
���õ�����:

	if(hcncas_smc_reset() == 0)
		printf("reset ok");

*/
INT32 hcncas_smc_reset(void)CASDRVFUNCPOSTFIX;
UINT8 hcncas_smc_status(void)CASDRVFUNCPOSTFIX;//:insert status;0:remove status
INT32 hcncas_smc_write(UINT8 *apdu_header, const UINT8 *apdu_body, UINT8 *sw1sw2)CASDRVFUNCPOSTFIX;
INT32 hcncas_smc_read(UINT8 *apdu_header, UINT8 *apdu_body, UINT8 *sw1sw2 )CASDRVFUNCPOSTFIX;
/*
˵�� ���õ�����ID��
���õ�����:

	UINT8 netid[2];
	hcncas_get_netid(netid);
*/
void hcncas_get_netid(UINT8 *net_id)CASDRVFUNCPOSTFIX;
/*
˵�� ��FLASH����,�ں���Ҫ�洢3�����ݣ������ֲ�ĵ�
���õ�����:

*/
INT8 hcncas_save_icno(UINT8 *src1,UINT8 LEN)CASDRVFUNCPOSTFIX;
INT8 hcncas_read_icno(UINT8 *src1,UINT8 LEN)CASDRVFUNCPOSTFIX;
INT8 hcncas_save_pack(UINT8 *src1,UINT16 LEN)CASDRVFUNCPOSTFIX;
INT8 hcncas_get_pack(UINT8 *src1,UINT16 LEN)CASDRVFUNCPOSTFIX;
INT32 hcncas_savepin_buffer(UINT8 *src1)CASDRVFUNCPOSTFIX;
INT32 hcncas_getpin_buffer(UINT8* src1)CASDRVFUNCPOSTFIX;
/*
˵�� �����ڴ�ӡ,��Ҫ����CA������Ϣ����ʽ�汾����ر���
���õ�����:

*/
INT8 hcncas_debug(char *Format_p, ...)CASDRVFUNCPOSTFIX;
/*
˵�� ��������������ֲ�ĵ�
���õ�����:

*/
UINT8 hcncas_report_status(UINT8* mesg,UINT32 para1,UINT32 para2)CASDRVFUNCPOSTFIX;
/*------------------------���Ͻӿ���STB�ṩ��CA_LIB----------------------------------------*/


/*------------------------���½ӿ���CA_LIB�ṩ��STB----------------------------------------*/
/*
˵�� ��CA�����������������Ϣ����
*/
UINT8 hcncas_init(void)CASDRVFUNCPOSTFIX;
/*
˵�� ���õ��ں˵İ汾��
���õ�����:
		INT8 version[8];
		hcncas_getca_version(version);
		printf("%s",version);
*/
void hcncas_getca_version(INT8* ver)CASDRVFUNCPOSTFIX;
/*
˵�� ���õ����ܿ�״̬
���õ�����:

*/
UINT8 hcncas_get_card_status(void)CASDRVFUNCPOSTFIX;
void  hcncas_card_insert(void)CASDRVFUNCPOSTFIX;
void  hcncas_card_remove(void)CASDRVFUNCPOSTFIX;
void hcncas_time_to_date(time_t *plTime, ca_time* ptDate)CASDRVFUNCPOSTFIX;
UINT8  hcncas_get_section(UINT16 PID, UINT8 *section_data)CASDRVFUNCPOSTFIX;
UINT8 hcncas_ismatch(UINT8* ca_systemid)CASDRVFUNCPOSTFIX;
/*
˵�� �����û����pid 
���õ�����:
		hcncas_set_ecmpid(ecmpid);
		hcncas_set_emmpid(emmpid);
*/
UINT8 hcncas_set_ecmpid(UINT16 ecmpid)CASDRVFUNCPOSTFIX;
void hcncas_clean_ecmpid(void)CASDRVFUNCPOSTFIX;
void hcncas_set_emmpid(UINT16 emmpid)CASDRVFUNCPOSTFIX;
void hcncas_clean_emmpid(void)CASDRVFUNCPOSTFIX;
void hcncas_clear_interface(void)CASDRVFUNCPOSTFIX;
void hcncas_ecm_stop(void)CASDRVFUNCPOSTFIX;
void hcncas_emm_stop(void)CASDRVFUNCPOSTFIX;
/*
˵�� �������ʼ���Ϣ,�����ֲ�ĵ�
���õ�����:
		UINT8 num;
		num=hcncas_get_email_count();
		hcncas_get_email(ptr,num)��
*/
UINT8 hcncas_get_email_count(void)CASDRVFUNCPOSTFIX;
void hcncas_get_email(UINT8 *email,UINT8 count_in)CASDRVFUNCPOSTFIX;
/*
˵�� ��������Ϣ����,�����ֲ�ĵ�
���õ�����:
		UINT8 num;
		num=hcncas_get_email_count();
		hcncas_get_email(ptr,num)��
*/
INT32 hcncas_get_move_osd(hcncas_osd* osd)CASDRVFUNCPOSTFIX;
/*
˵�� ���õ��û���Ϣ����,�����ֲ�ĵ�
���õ�����:
		hcncas_smcinfo card;
		hcncas_get_cardinfo(&card);

*/
UINT8 hcncas_get_cardinfo(hcncas_smcinfo *user)CASDRVFUNCPOSTFIX;
/*
˵�� ���߷���Ϣ����,�����ֲ�ĵ�
���õ�����:
		UINT16 len;
		UINT8 *bu=NULL;
		len=hcncas_get_hasten_len();
		bu=(UINT8 *)hcncas_malloc(len);
		printf("%s",bu);
*/
UINT16 hcncas_get_hasten_len(void)CASDRVFUNCPOSTFIX;
UINT16 hcncas_get_hasten(UINT8 *user)CASDRVFUNCPOSTFIX;
/*
˵�� ����ȡ��Ȩ��Ϣ����,�����ֲ�ĵ�
���õ�����:

*/
INT32 hcncas_get_entitle(HCNCAS_PPCENTITLE *entitle_infor,UINT8 *num)CASDRVFUNCPOSTFIX;
/*
˵�� ����ȡǮ����Ϣ����,�����ֲ�ĵ�
���õ�����:

*/
INT32 hcncas_get_purse(UINT8 *credit_count,UINT8 *consume_Count)CASDRVFUNCPOSTFIX;
/*
˵�� ����ȡIPPV��Ϣ����,�����ֲ�ĵ�
���õ�����:

*/
INT32 hcncas_get_ippvinfo(UINT8 * infor,UINT8* num)CASDRVFUNCPOSTFIX;	
/*
˵�� ����ȡ��Ȩ��Ϣ����,�����ֲ�ĵ�
���õ�����:

*/
INT32 hcncas_get_worktime(UINT8 *work_time)CASDRVFUNCPOSTFIX;
INT32 hcncas_verify_pin(UINT8 *pin,  UINT8 length, UINT8 *times)CASDRVFUNCPOSTFIX;
INT32 hcncas_modify_pin(UINT8* old_pin,  UINT8 old_pin_len,UINT8* new_pin,  UINT8 new_pin_len,UINT8* times)CASDRVFUNCPOSTFIX;
INT32 hcncas_set_worktime(UINT8 *work_time)CASDRVFUNCPOSTFIX;
INT32 hcncas_get_adultlevel(UINT8 *pa)CASDRVFUNCPOSTFIX;
INT32 hcncas_set_adultlevel(UINT8 work_time)CASDRVFUNCPOSTFIX;
UINT8 hcncas_get_is_finger(void)CASDRVFUNCPOSTFIX;
INT32 hcncas_get_ippvbuy_info(HCNCAS_IPPV *user)CASDRVFUNCPOSTFIX;
INT32 hcncas_buy_ippv(UINT8 provider_id, UINT8 *event_id, UINT8 tokenprice, UINT8 *overtime)CASDRVFUNCPOSTFIX;
#endif
