/** @file
* @brief CAģ��
* @author ����
* @date 2005-9-8 ����: �����ļ�
*/

#ifndef _D_CA_H_
#define _D_CA_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dQueue.h"
#include "dDBase.h"
#include "dScroll.h"

#define FINGER_LABEL_BUF_LEN 64
#define MAX_OSD_NUM 6
#define MAX_OSD_LEN 2048

/** @brief CAϵͳTS����������*/
typedef struct {
	D_DBTSID    db_ts_id;	/**< Ҫ������TS�����ݿ��¼ID*/
	D_ID		fend_id;    /**< ��Ӧǰ���豸ID*/
} D_CATSParam;

/** @brief CAϵͳ�����������*/
typedef struct {
	D_DBSrvID db_srv_id;    /**< Ҫ�����ķ������ݿ��¼ID*/
	D_ID	  fend_id;		/**< ��Ӧǰ���豸ID*/
} D_CASrvParam;

/** @brief CA������Ϣ*/
typedef struct {
	D_U16		srv_id;     //srvid
    D_U16		pcr_pid;    //pcrid
    D_U16		vid_pid;    //��Ƶid
    D_U16		aud1_pid;   //��Ƶ1id
    D_U16		aud2_pid;   //��Ƶ2id
    D_U16 		pmt_pid;    //pmtid
} D_CASrvInfo;

/**< @brief CA�¼�����*/
typedef enum {
	D_CA_EVT_SC_IN,		        //���ܿ�����
	D_CA_EVT_SC_OUT,	        //���ܿ��γ�
	
	D_CA_EVT_SHOWBUYMSG,        //ca��ʾ��Ϣ�¼�
	
	D_CA_EVT_FINGERMSG,	        //ָ����ʾ
	D_CA_EVT_HIDE_FINGERMSG,	//����ָ����ʾ
	
	D_CA_EVT_SHOWTOPOSDMSG,		//��ʾ����������
	D_CA_EVT_SHOWBOTTOMMSG,   	//��ʾ�ײ�������
	D_CA_EVT_HIDETOPOSDMSG,		//���ض���������
	D_CA_EVT_HIDEBOTTOMOSDMSG,	//���صײ�������
	
	D_CA_EVT_EMAILNOTIFY,		//��ʾ�����ʼ�
	D_CA_EVT_FULL_EMAILNOTIFY,  //��������
    D_CA_EVT_HIDE_EMAILNOTIFY,  //���ص����ʼ�
    
    D_CA_EVT_DETITLENOTIFY,		//��ʾ����Ȩͼ��
	D_CA_EVT_FULL_DETITLENOTIFY,//����Ȩ����ͼ��
    D_CA_EVT_HIDE_DETITLENOTIFY,//���ط���Ȩͼ��
    
    D_CA_SHOW_SUPERLOOK_NOTE,   //��ʾ�߼�Ԥ��
    D_CA_HIDE_SUPERLOOK_NOTE,   //���ظ߼�Ԥ��
    
	D_CA_EVT_SHOWIPPVDLG,		//��ʾippv	
	D_CA_EVT_HIDEIPPVDLG,		//����ippv
	
    D_CA_EVT_PROGRESS,          //��ʾ������
    D_CA_EVT_HIDE_PROGRESS,     //���ؽ�����
    
    D_CA_EVT_URGENCY_BRCAST,            //Ӧ���㲥
    D_CA_EVT_URGENCY_BRCAST_CANCEL,     //ȡ��Ӧ���㲥
    
    D_CA_EVT_SHOW_SUPER_OSD,    //��ʾ����OSD
    D_CA_EVT_HIDE_SUPER_OSD,    //�ڲس���OSD
    
	D_CA_EVT_SHOWIPPVICON,		//��ʾippvͼ��
    D_CA_EVT_SHOWIPPTICON,		//��ʾipptͼ��
	D_CA_EVT_HIDEIPPVICON,		//����ippvͼ��

	D_CA_EVT_SHOW_PREAUTH_ICON,	//��ʾԤ��ͼ��
	D_CA_EVT_HIDE_PREAUTH_ICON,	//����Ԥ��ͼ��

	D_CA_EVT_SHOW_AUTH_REMAINDLG,//��ʾ��Ȩʣ��xx��
	D_CA_EVT_HIDE_AUTH_REMAINDLG,//������Ȩʣ��xx��

	D_CA_EVT_SHOW_PURSEDLG,		//��ʾǮ����ֵ�������
	D_CA_EVT_HIDE_PURSEDLG,     //����Ǯ����ֵ�������

	D_CA_EVT_SHOW_EXPIRDLG,		//��ʾ��Ŀ��������
	D_CA_EVT_HIDE_EXPIRDLG,		//���ؽ�Ŀ��������
	
	D_CA_EVT_SHOW_NORMAL_FINGER, //��ʾ��ָͨ��
	D_CA_EVT_HIDE_NORMAL_FINGER, //������ָͨ��

	D_CA_EVT_SHOW_URGENCY_ICON, //Ӧ���㲥��ʾͼ��
	D_CA_EVT_HIDE_URGENCY_ICON, //����Ӧ���㲥��ʾͼ��
    	
	D_CA_EVT_SHOW_SENIOR_PREVIEW, //��ʾ�߼�Ԥ��		
	D_CA_EVT_HIDE_SENIOR_PREVIEW, //�ڲظ߼�Ԥ��

    D_CA_EVT_SHOW_TIP_ANNOUN,    //��ʾȫ������
	D_CA_EVT_HIDE_TIP_ANNOUN,    //�ڲ�ȫ������(Ŀǰ20131018����̨����)

	D_CA_EVT_SHOW_PARENTALCTRL,  //��ʾ��ĸ������
	D_CA_EVT_HIDE_PARENTALCTRL,  //�ڲظ�ĸ������

        D_CA_EVT_SHOW_INTERVAL_SCROLL, //��ʾ���������
	D_CA_EVT_HIDE_INTERVAL_SCROLL, //�ڲؼ��������

	D_CA_EVT_SHOW_AUTO_FEED,     //�Զ���ĸ�����
	D_CA_EVT_HIDE_AUTO_FEED,     //������ĸ�����

    D_CA_EVT_SHOW_PAIR,          //�Զ��������
    D_CA_EVT_HIDE_PAIR,          //�ڲػ������

	D_CA_EVT_SHOW_SKIP_SELECT,   //��ʾ��Ŀ��ת��ʾ
	D_CA_EVT_HIDE_SKIP_SELECT,   //���ؽ�Ŀ��ת��ʾ
	D_CA_EVT_RESHOW,             //ˢ�µ�ǰ�˵�
    
	D_CA_EVT_SWITCH_CA,          //�л�CA
	
	D_CA_EVT_TIMING_SHOWBUYMSG,  //CA��ʾ��Ϣ��ʱ��ʧ�¼�
    D_CA_EVT_FLASH_SHOWBUYMSG,   //CA��ʾ��Ϣ��˸(��ʾ����ʧ������ʱ��ɿ���)

    D_CA_EVT_SHOW_MAURITY_PROGRAM,  //���˼���Ŀ
	D_CA_EVT_HIDE_MAURITY_PROGRAM,  //���س��˼���Ŀ
	
	D_CA_EVT_SHOW_SUPER_FINGERMSG,  //��ʾ�����û�ָ��
	D_CA_EVT_HIDE_SUPER_FINGERMSG,  //���������û�ָ��
	
	D_CA_EVT_SHOW_EMM_FINGERMSG,    //��ʾ����EMMָ��
	D_CA_EVT_HIDE_EMM_FINGERMSG,    //��������EMMָ��
	
	D_CA_EVT_SHOW_COVERT_FINGERMSG, //��ʾ����ָ��
	D_CA_EVT_HIDE_COVERT_FINGERMSG, //��������ָ��
	
	D_CA_EVT_SEND_OTAMSG,           //����OTA��Ϣ
	D_CA_EVT_SENDMSG_TO_OTHERSTB,   //ͨ�����ڷ�����Ϣ
	
    D_CA_EVT_SHOWOPERTEMSG,         //��ʾ�ɲ�������ʾ��Ϣ
    D_CA_EVT_SHOW_FEED_STATUS,
    
    D_CA_EVT_REMOTE_LOCK,           //��ң����
    D_CA_EVT_REMOTE_UNLOCK,         //����ң����

    D_CA_EVT_START_SERVICE,         //����Ĭ�ϻ�̨��Ŀ
    D_CA_EVT_CANCLE_START_SERVICE,  //ȡ������Ĭ�ϻ�̨��Ŀ
    
    D_CA_EVT_RESTART_STB,           //����������
    
    D_CA_EVT_CA_CTL_PROG_OFF,       //CA����ֹͣ��Ƶ
    D_CA_EVT_CA_CTL_PROG_ON,        //CA���ƿ�����Ƶ

    D_CA_EVT_CA_CTL_NIT_SEARCH,     //��������
    
    D_CA_EVT_HIDE_AUTO_CHARGE,      //�ڲ��Զ���ֵ(for dvnca)
    D_CA_EVT_SHOW_AUTO_CHARGE,      //��ʾ�Զ���ֵ(for dvnca)
    
    D_CA_EVT_FlAG_CHANGE,           //��Ŀ��Ѽ����л���־

    D_CA_EVT_FORBID_PVR,           //��ֹ¼��(for  abvca)

    D_CA_EVT_ABV_TIMING_SHOWBUYMSG,//ABV��Ϣ
    D_CA_EVT_ABV_SERIALIZE_STATUS, //ABV���л�״̬

    D_CA_EVT_SHOW_NORMAL_EMMFINGER, //��ʾEMMָ��
	D_CA_EVT_HIDE_NORMAL_EMMFINGER, //����EMMָ��
	
    D_CA_EVT_SHOW_EMERGENCY_ICON,   //��ʾ"�����¼�"ͼ��
    D_CA_EVT_HIDE_EMERGENCY_ICON,   //����"�����¼�"ͼ��

    D_CA_EVT_SHOW_IMMOBILE_TOPSCROLL, //��ʾ��ֹ�������Ϲ�����
    D_CA_EVT_SHOW_IMMOBILE_BOTTOMSCROLL, //��ʾ��ֹ�������¹�����

    //�����ö�ٷ������֮ǰ
	D_CA_EVT_SC_USER
} D_CAEventType;

/**< @brief CA��ʾ��Ϣ*/
typedef struct
{
	D_U8 language;
	D_U8 prio; 
	D_U8 osd_number; 
	D_Char *ch_msg; /*��������*/
	D_Char *en_msg; /*Ӣ������*/
	D_Char *ot_msg; /*��������*/
}D_CaOSDPreDefined;

/**< @brief ca osd����*/

typedef struct
{
	D_CaOSDPreDefined *osd_predef;  //tig:�˱����ò���
	D_U8 show_icon;                 // 1 ��ʾ 0 ����ʾ	
}D_CaOSDMan;

typedef struct
{
	D_Char *osd_predef;             //ָ����ʾ���ݵ�ָ�룬ע:�洢��ʾ���ݵı���Ӧ��Ϊȫ�ֱ���
	D_U32 time;                     //��ʾʱ��(s) 0 ����ʾ 
}D_CaTimerOSDMan;

typedef struct
{
    D_Char *osd_predef;             //ָ����ʾ���ݵ�ָ�룬ע:�洢��ʾ���ݵı���Ӧ��Ϊȫ�ֱ���
    D_U32  time;                    //��ʾ����
    D_U32  show_time;               //ÿ����ʾ��ʱ��
    D_U32  hide_time;               //ÿ�����ص�ʱ��
}D_CaFlashOSDMan;

/*-- ��ָͨ����ʾ��Ϣ--*/
typedef struct{
	D_U8		byShowType; 	    //��ʾ��ʽ :0 ����˸  1��˸
	D_U32		Duration;		    //��ʾʱ�䣬��λ:�� .  ��ʱ������ʱ��ֵΪ0.
	char		szContent[FINGER_LABEL_BUF_LEN]; //��Ҫ��ʾ��ָ�����ݣ���0��β���ַ���
}D_CAOrdinaryFinger;

/*-- ����ָ����ʾ��Ϣ--*/
typedef struct {
	D_U8		byShowType; 	    //��ʾ��ʽ0���ַ���; 1������2����������ֵ������
	D_U8		byContentType; 	    //��ʾ����0�����ţ�1�������кţ�����ֵ������
	D_U8	    bIsVisible; 	    //�ɼ���0�����ԣ�1������
	D_U8        bIsForcedShow;      //�Ƿ�ǿ����ʾ 0����ǿ����ʾ 1��ǿ����ʾ��
	D_U8        byEncryption;       //�����㷨�� 0�������ܣ���0������
	D_U16       wFlashing_EachShowTime; //ÿ����˸��ʾʱ����Ϊ0ʱ��ʾ����˸��
	D_U16       wFlashing_EachHideTime; //ÿ����˸��ͣʱ����Ϊ0ʱ��ʾ����˸��
	D_U8        byFontSize; 	    //ָ�������С��ȡֵ��Χ[0,255]��0��ʾĬ�������С��1��ʾ�����壬2��ʾС���壬3~255��ʾʵ�������С����������в�֧��3~255����Ĭ�������С��ʾ��byShowTypeΪ1��2ʱ��ʾָ������Ĵ�С��
	D_U8		byReserved;	        //0x00	����
	D_U32	    dwFontColor;	    //������ɫ����׼RGBֵ��byShowTypeΪ1ʱ��ֵ�����塣
	D_U32	    dwBackgroundColor;	//������ɫ����׼RGBֵ��byShowTypeΪ1��2ʱ����Ҫ��
	D_U8		byX_position;		//ָ����ʾλ�õ�X�����꣬ȡֵ��Χ0~100
	D_U8		byY_position;		//ָ����ʾλ�õ�Y�����꣬ȡֵ��Χ0~100
	D_U8	    pbyMatrixInnerPos[16];	// byShowTypeΪ2ʱ��ʾ����ָ��ÿ���ַ���Ӧ���ڲ�����ֵ��byShowTypeΪ����ֵʱ���ֶ������塣
	char		szContent[21];      //��Ҫ��ʾ��ָ�����ݣ���0��β���ַ�����
}D_CAFingerInfo;
typedef struct {
	D_U8		byShowPosition; 	//��ʾλ��:0 ���� 1 ���� 2 ���� 3 ����
	D_U8	    bIsVisible; 	    //�ɼ���0�����ԣ�1������
	D_U8        byFontSize; 	    //ָ�������С��ȡֵ��Χ[0,255]��0��ʾĬ�������С��1��ʾ�����壬2��ʾС���壬3~255��ʾʵ�������С����������в�֧��3~255����Ĭ�������С��ʾ��byShowTypeΪ1��2ʱ��ʾָ������Ĵ�С��
	D_U32	    dwFontColor;	    //������ɫ
	D_U32	    dwBackgroundColor;	//������ɫ
	D_U8        ifShowBCflag;       //�Ƿ���ʾ������ɫ 0 ����ʾ 1 ��ʾ
	D_U16		byX_position;		//ָ����ʾλ�õ�X������
	D_U16		byY_position;		//ָ����ʾλ�õ�Y������
	char		szContent[21];      //��Ҫ��ʾ��ָ�����ݣ���0��β���ַ�����
}D_DSCAFingerInfo;

/*-- ��˹����CA����ָ����ʾ��Ϣ--*/
typedef struct {
	D_U8		byShowPosition;     //��ʾλ��:0  ���� 1 ��������ʾ 2 ���
	D_U8		byContentType;  	//��ʾ����0�����ţ�1�������кţ�2:����+ �����к�; 3: ����+ �û��Զ�������; 4:�����к�+�û��Զ�������; 5:����+�����к�+�û��Զ�������; ����ֵ������
	D_U8	    bIsVisible; 	    //�ɼ���0�����ԣ�1������
	D_U8        bIsForcedShow;      //�Ƿ�ǿ����ʾ 0����ǿ����ʾ 1��ǿ����ʾ��
	D_U16	    wInterval;		    //ʱ����,������ʾ֮��Ĳ���ʾָ�Ƶ�ʱ�䳤��
	D_U8        byFontSize; 	    //ָ�������С��ȡֵ��Χ[0,255]��0��ʾĬ�������С��1��ʾ�����壬2��ʾС���壬3~255��ʾʵ�������С����������в�֧��3~255����Ĭ�������С��ʾ��byShowTypeΪ1��2ʱ��ʾָ������Ĵ�С��
	D_U8		byReserved;	        //0x00	����
	D_U32	    dwFontColor;	    //������ɫ��ARGBֵ
	D_U32	    dwBackgroundColor;	//������ɫ��ARGBֵ��
	D_U8		byX_position;		//ָ����ʾλ�õ�X�����꣬
	D_U8		byY_position;		//ָ����ʾλ�õ�Y�����꣬
    D_U16       wContentLen;        //��Ҫ��ʾ��ָ�����ݵĳ���
	char		szContent[255];     //��Ҫ��ʾ��ָ�����ݣ���0��β���ַ�����
	D_U8        byChannelcnt;       //  ָ����ʾƵ���������Ϊ0 ����ʾ����Ƶ������ʾָ��  
    D_U16       wServiceID[10];     //��ʾָ��Ƶ����service id 
}D_GOSCAFingerInfo;

/*��˹����CA����OSD �ṹ*/
typedef	struct{
    D_U8   byShowType;              //0:��ǿ����ʾ��1:ǿ����ʾ
    D_U8   byFontSize;              //OSD�����С��
    D_U8   byBackgroundArea;        //��ʾռ��Ļ�����벿�ֵ�����ٷֱȣ�Ĭ��Ϊ80����Χ��20~80��
    D_U32  dwFontColor;	            //������ɫ��ARGBֵ
    D_U32  dwBackgroundColor;       //������ɫ��ARGBֵ��
    char   szContent[256+1];        //osd�ַ�������0��β���ַ���
    D_U8   byShowCardNo;            //0:�������� 1:������
}D_GOSCAOSDInfo;

/*����ָ�ƽṹ*/
typedef	struct{
    D_U16	byrepitition;           //��ʾ����
    D_U16   wFlashing_EachShowTime;  //ÿ����ʾʱ��
    D_U16   wFlashing_EachHideTime;  //ÿ����ʾ��ͣʱ��
    D_U8    byFontSize;		        //�����С
    D_U8    Sparkling;              // ��˸

    D_U16   byX_position;		    //ָ����ʾλ�õ�X������
    D_U16	byY_position;		    //ָ����ʾλ�õ�Y������
    D_U8    bywidth;                /* %   ex: 80(80%), 64(64%), 0x64(100%)*/
    D_U8    byheight;               /*%*/
    D_U32   dwFontColor;	        //֧��256ɫ
    D_U32   dwBackgroundColor;		//֧��256ɫ
    D_U8    disp_Background;        // 1:��ʾ����
    D_U8    forcefinger;            // 1:ǿ��ָ��
    D_U8    disp_cardnum;           // 1:��ʾ����
    D_U8    disp_stbnum;            // 1:��ʾ�����к�
	
    D_U8    Transparency;           //͸����
    D_U16   OsdLen;                 //osd���ݳ���
    char    szContent[1024];        //osd�ַ�������0��β���ַ���
}D_ABVCASuperFingerInfo;

/*����OSD �ṹ*/
typedef	struct{
    D_U8   byShowType;              //0:��ǿ����ʾ��1:ǿ����ʾ
    D_U8   byFontSize;		        //0��Ĭ�ϣ�1����ţ�2��С��
    D_U8   byBackgroundArea;		//��ʾռ��Ļ�����벿�ֵ�����ٷֱȣ�Ĭ��Ϊ80����Χ��20~80��
    D_U32  dwFontColor;	            //֧��256ɫ
    D_U32  dwBackgroundColor;		//֧��256ɫ    
    char   szContent[512];          //osd�ַ�������0��β���ַ���
}D_DCAOSDInfo;

/*����OSD �ṹ*/
typedef	struct{
    D_U16   byrepitition;           //��˸����
    D_U16   wFlashing_EachShowTime; //ÿ����˸��ʾʱ����Ϊ0ʱ��ʾ����˸��
    D_U16   wFlashing_EachHideTime; //ÿ����˸��ͣʱ����Ϊ0ʱ��ʾ����˸��
    D_U8    byFontSize;		        //�����С
    D_U8    disp_Background;        //�Ƿ���ʾ����
    D_U32   dwFontColor;	        //֧��256ɫ
    D_U32   dwBackgroundColor;		//֧��256ɫ
    D_U8    Transparency;           //͸����
    D_U16   OsdLen;                 //osd���ݳ���
    char    szContent[1024];        //osd�ַ�������0��β���ַ���
}D_ABVCAOSDInfo;

/*����OSD �ṹ*/
typedef struct
{
	D_U32 MaxNum;                   //OSD���洢��
    D_U32 MaxLen;                   //OSD����
    D_U32 CurNum;                   //OSD��ǰ����
    D_U32 SaveIndex;                //OSD������
    D_U32 GetIndex;                 //OSDȡ����
    
}D_CaSaveOSDInfo;

/*���OSD �ṹ*/
typedef struct
{
    D_U8 showPosition;              //0 top 2 bottom 3 top and tottom 
    D_U8 fontColor[4];              //R G B A   Ŀǰֻ�е���CA��OSD����Ҳ����͸����
    D_U8 bgColor[4];                //R G B A
    D_U8 osdType;                   //��ͬ�汾ʹ�õ�sod������һ��1 ֧����ɫ��0 ����֧��
    D_U8 showCount;                 //��ʾ����
    char osdMsg[MAX_OSD_NUM][MAX_OSD_LEN];
}MonitorOSDInfo;

/*--���OSD �ṹ--*/
typedef struct{
	D_U8		u8Style; 		  //��ʾ���
	D_U8        u8JudgeValue;   //����һ����ʾ����
	D_U32       u32Interval;      //�����ʾʱ��
	D_Char      u8OsdData[MAX_OSD_LEN];  //��ʾ����			
}D_CAIntervalScroll;

/*-- ��ֹ��������ʾ��Ϣ--*/
typedef struct{
	D_U32		Duration;		 //��ʾʱ�䣬��λ:�� .  ��ʱ������ʱ��ֵΪ0.
	char		szContent[256]; //��Ҫ��ʾ�Ĺ��������ݣ���0��β���ַ���
}D_CAImmobileScroll;

/*-- ������--*/
typedef struct
{
	D_U8   byProgress;              //�������ֵ
	D_Char ShowType;                // 1 ���ݽ����� 2 ���ܿ������� 
}D_ProgressStrip;

/*-- IPPV,����ʱΪNULL--*/
typedef struct{
	char productId[12];				//��Ŀ��ID
    char tvSId[6];    			    //��Ӫ�̱��
    D_U8 isIppvOrIppt;				//֧��ippv��ippt  1 ippv  2  ippt  3  ippv and ippt
    D_U8 ippStatus;					//�շѽ׶�   0 ippv��ѽ׶�  1 ippv�շѽ׶�  2 ippt�շѽ׶� 
    char ippCanTapPrice[6]; 		//��¼��Ľ�Ŀ�۸�
    char ippCanNotTapPrice[6]; 		//����¼��Ľ�Ŀ�۸�
	char ippvPeriod[12]; 			//ippv��Ŀ����ʱ��
	char ipptInterval[12];			//ippt��Ŀ�շѼ��
	D_U8 slotId;					//Ǯ��ID	
	D_U8 priceCode[2];              //�������ͣ�priceCode[0]����¼��Ľ�Ŀ��priceCode[1]��¼��Ľ�Ŀ
}D_IppBuyInfo;

typedef struct{
	D_U8 IPPV_Type;
	char  IPPV_Time_Price[7];
	char  IPPV_View_Price[7];
	char  IPPV_Name[24];
	char  Pro_Start_Time[17];
	char  Pro_End_Time[17];
	D_U8  IPPV_ID;	                //��Ŀ���
}D_abvca_IppBuyInfo;

/*-- Ӧ���㲥--*/
typedef struct {
    D_U8  RemoteCtl;                //0,����ң������ǰ��壬1��������
	D_U8  Modulation;               /* ���Ʒ�ʽ 32QAM 64QAM*/
    D_U16 VPid;
	D_U16 APid;
	D_U16 PcrPid; 	
	D_U32 Frequency;                //Ƶ��
	D_U32 symbol_rate;              //������
}D_Ca_SwitchChannel_t;

/*-- ȡ��Ӧ���㲥--*/
typedef struct {
    D_U8  CancelCtl;                //0,ȡ������ң������1,ȡ��������֮ǰ���ŵĽ�Ŀ
}D_Ca_Channel_cancel_t;


/*-- ����Ĭ�ϻ�̨--*/
typedef struct {
	D_U16 ServiceId;
	D_U16 PcrPid; 	
}D_Ca_StartChannel_t;

/*-- ��������л�--*/
typedef struct {
	D_U16   ServiceId;
	D_Bool  desflag; 	
}D_Ca_ProgDescflag_t;

/** @brief CA�¼���Ϣ�ص�����*/
typedef D_Result	(*D_CAEventCallback) (D_CAEventType type, D_Ptr param) D_FUNCPOSTFIT;

/** @brief CA������Ϣ�ص�����*/
typedef D_Result	(*D_CAComplieCallback) (D_U32* param) D_FUNCPOSTFIT;


/** @brief �жϵ�ǰ�Ƿ����޿�CA
* @return ����2��ʾ���޿�CA������Ϊ�п�CA
*/
D_Result    d_ca_get_sc_status(void);


/** @brief CAϵͳ��ʼ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_ca_open (void) D_FUNCPOSTFIT;

/** @brief ֪ͨCAϵͳ��ʼ����һ��TS���е��û���Ȩ����
* @param	param ����ָ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_ca_start_ts (D_CATSParam *param) D_FUNCPOSTFIT;

/** @brief ֪ͨCAϵͳֹͣ����һ��TS���е��û���Ȩ����
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_ca_stop_ts (D_DBTSID db_ts_id) D_FUNCPOSTFIT;

/** @brief ֪ͨCAϵͳ��ʼ����һ��������û���������
* @param	param ����ָ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_ca_start_srv (D_CASrvParam *param) D_FUNCPOSTFIT;

/** @brief ֪ͨCAϵͳֹͣ����һ��������û���������
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_ca_stop_srv (D_DBSrvID db_srv_id) D_FUNCPOSTFIT;

/** @brief ��CAϵͳͬ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_ca_sync (void) D_FUNCPOSTFIT;

/** @brief CAϵͳID���
* @param ca_sys_id	CAϵͳID
* @return �ǿ�ʶ���CA����D_TRUE,���򷵻�D_FALSE
*/
D_Bool		d_ca_sys_check (D_U16 ca_sys_id) D_FUNCPOSTFIT;

/** d_ca_sys_check ��д������1��Ϊ��Ӱ����ǰ���ܣ������Ӵ˽ӿ�*/
D_Bool d_ca_sys_id_check (D_U16 ca_sys_id) D_FUNCPOSTFIT;

/** @brief ע��CA��Ϣ�ص�����
* @param callback	Ҫע��Ļص�����ָ��
* @param old ���ؾɵĻص�����ָ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_ca_register_callback (D_CAEventCallback callback, D_CAEventCallback *old) D_FUNCPOSTFIT;


/** @brief ע��CA������Ϣ�ص�����
* @param callback	Ҫע��Ļص�����ָ��
* @param old ���ؾɵĻص�����ָ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_ca_register_comp_callback (D_CAComplieCallback callback, D_CAComplieCallback *old)D_FUNCPOSTFIT;


/** @brief ����CA����ϵͳ
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_ca_close (void) D_FUNCPOSTFIT;



/** @brief ֹͣCA����ϵͳ
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_ca_stop(void) D_FUNCPOSTFIT;


/** @brief ����CA����ϵͳ
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result
d_ca_run(void) D_FUNCPOSTFIT;

/** @brief ��ʾ��Ϣ�洢��ʼ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_ca_osd_man_init(void);

/** @brief ������ʾca��Ϣ���ʼ���ָ�Ƶ�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_ca_osd_reshow(void);

/** @brief ��ȡ��ǰ���ĸ�ca
* @return ���ص�ǰcaֵ �ο�hrca_config.h��caֵ����
*/
D_U32 d_ca_get_curcas(void);

/** @brief pmt cat����*/
D_Result d_ca_demux_data_cmp (D_U8 dType, D_U8 *buf, D_Size size) D_FUNCPOSTFIT;

/** @brief���������Ա仯��֪ͨCA�����ˢ����ʾ
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result d_ca_lan_change (D_U8 lanType);

/** @brief�����л�ȡ�����ַ���
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result d_ca_get_scid(D_Char *str_scid, D_Size *len);

/** @brief  �˽ӿڷ��ص� ChipID��4�ֽڵġ�
**��Ӧ�ò˵��е��ã�Ŀǰ��WFCAʹ��*/
D_Result
d_ca_get_chipid(D_U8 *len, D_U8 *chipid);

/** @brief  �˽ӿڷ��ص���cardno��
**��Ӧ�ò˵��е��ã�Ŀǰ��WFCAʹ��*/
D_Result
d_ca_get_cardno(D_U8 *len, D_U8 *cardno);

extern D_U16 g_CaNetWorkID;
D_Result d_ca_get_networkid(D_U16 *networkid);

/** @brief ����ca flash�����ݣ�Ŀǰֻ�е��ӻ������޿�CA�õ�*/
D_Result d_ca_erase_ca_flash(void);

/** @brief ca system����������(����CA�������"CA"����)ֹͣ����*/
D_Result d_ca_system_stop(void);

/** @brief ca system����������(����CA�������"CA"����)��������*/
D_Result d_ca_system_run(void);

/** @brief ͨ��usb��дotp��Ϣ*/
D_Result d_ca_burn_otpinfo_by_usb(void);

/** @brief ͨ��������дotp��Ϣ*/
D_Result d_ca_burn_otpinfo_by_serialport(D_U8 *potp, D_U16 len);

typedef void (*CallBackDspmessage)(D_U32 p);
extern CallBackDspmessage    SendMsgtoSC;

extern D_Bool	ca_inserted;

/*�������ص�����*/
typedef struct
{
    D_U32 curcas;
    D_U32 position;
    D_Char* text;
    D_U32 bg_color;
    D_U32 text_color;
    D_U8  font_size;
    D_U32 scroll_speed;
    D_U32 repeat_times;
    D_U32 duration;
    D_Bool immediate;
    D_ScrollCallback callback;
}D_CasScrollParam;

/*λ���� 1: �����  2: �һ���*/
#define D_CAS_SCROLL_POSITION_1  (1)
#define D_CAS_SCROLL_POSITION_2 (2)

/*��������������*/
#define D_CAS_SCROLL_ACTION_CREATE  (0)
#define D_CAS_SCROLL_ACTION_DESTROY (1)
#define D_CAS_SCROLL_ACTION_START   (2)
#define D_CAS_SCROLL_ACTION_STOP    (3)
#define D_CAS_SCROLL_ACTION_GETSTATE    (4)

typedef D_Result (*HRCAScrollAction)(D_Handle handle, D_U32 action, D_CasScrollParam *param);
extern HRCAScrollAction HRCA_Scroll_Action;
extern D_Result d_ca_register_scroll_callback(HRCAScrollAction callback, HRCAScrollAction *old);

typedef D_Result (*HRCABurnAction)(D_Ptr param);
extern HRCABurnAction HRCA_Burn_Action;
extern D_Result d_ca_register_burn_callback(HRCABurnAction callback, HRCABurnAction *old);

typedef D_Result (*HRCAScModeAction)(void);
extern HRCAScModeAction HRCA_ScMode_Action;
extern D_Result d_ca_register_scmode_callback(HRCAScModeAction callback, HRCAScModeAction *old);

#ifdef  __cplusplus
}
#endif

#endif
