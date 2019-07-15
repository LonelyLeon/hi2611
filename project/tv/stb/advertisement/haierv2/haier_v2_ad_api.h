/** @file
* @brief ���ģ��֧�Žӿ�
* @author huangq
* @date 2014-06-16 huangq: �����ļ�
*/
#ifndef _D_HIV2ADSTBAPI_H_
#define _D_HIV2ADSTBAPI_H_

#define AD_MAX_NUM				20//��������
#define PIC_MAX_NUM				50//����ͼƬ��
#define TXT_MAX_NUM				10//��������Դ����(ÿ��)
#define MAX_AREA_CODE_NUM		20
#define AD_LINK_PIC_MAX_NUM		20
#define AD_LINK_SERV_MAX_NUM	20

#define TOTAL_TXT_MAX_NUM				255//��������Դ����
#define TOTAL_TXT_SERV_MAX_NUM			255//��������Դ����

#define ADL_PLAY_PARAS_DES			0x80		//������������
#define ADL_AREA_ID_DES				0x82		//����ID������
#define ADL_DATA_DES				0x83        //�������������
#define	SCROLL_TXT_DES				0x84    //������Ļ������
#define	SERVICE_ID_DES				0x85    //����������
/** @brief �����ʾ��ʶ*/
#define HIV2AD_MSEEAGE_SHOWFULLSRCEEN_TYPE	(0X04)//��ʾ�ҽǹ��
#define HIV2AD_MSEEAGE_HIDEFULLSRCEEN_TYPE	(0X05)//���عҽǹ��

/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/** @brief haier���Ӧ������*/
typedef enum
{
    HIV2AD_STB_LOG = 0,         //0 �������
    HIV2AD_STB_BANNER, 					//1��̨��
    HIV2AD_STB_VOLUME,					//2������
    HIV2AD_STB_MENU, 						//3���˵�
    HIV2AD_STB_PROGRAM_LIST,		//4��Ŀ�б�
    HIV2AD_STB_EPG,             //5 EPG���
    HIV2AD_STB_RADIO_BACK,      //6 �㲥����
    HIV2AD_STB_NOSIGNAL,        //7 ���ź�
    HIV2AD_STB_NOPROGRAM,       //8 �޽�Ŀ
    HIV2AD_STB_FULLSCREEN,      //9 �ҽǹ��
    HIV2AD_STB_ROLL_TXT,        //10 ������Ļ���
    HIV2AD_STB_POS_UNKNOWN,     //11 δ֪����
} HIV2_Ad_Pos_Type;

/** @brief haier���ͼƬ����*/
typedef enum
{
    HIV2AD_IMAGE_JPEG = 1,
    HIV2AD_IMAGE_GIF,
    HIV2AD_IMAGE_MPEG2_FRAME_I,
    HIV2AD_IMAGE_BMP,
    HIV2AD_IMAGE_AUTO,
} HIV2_Ad_Pic_Type;

/** @brief haier ��Դ������*/
typedef enum
{
    HIV2AD_TYPE_PIC = 1,        //0 �������
    HIV2AD_TYPE_TXT,     				//11 δ֪����
		HIV2AD_TYPE_TS,		 					//11 δ֪����
} HIV2_Ad_Resource_Type;


/** @brief ���������ͱ�ʶ*/
typedef enum HIV2AD_FILTER_FLAG_
{
	HIV2AD_FILTER_FLAG_CONTROL = 0,
	HIV2AD_FILTER_FLAG_INFO = 1,
	HIV2AD_FILTER_FLAG_DATA = 2,
	HIV2AD_FILTER_FLAG_MAX ,
}HIV2AD_FILTER_FLAG;

/** @brief �������PID����*/
typedef enum HIV2AD_Msg_PID_Type_
{
    HIV2AD_PID_TYPE_ADLIST        =  0,
    HIV2AD_PID_TYPE_DESCRIPTOR      =  1,
    HIV2AD_PID_TYPE_PIC_DATA    =  2,
    HIV2AD_PID_TYPE_MAX_NUM,
} HIV2AD_Msg_PID_Type;

/** @brief ���ģ��򿪱�ʶ*/
typedef enum 
{
	HIV2AD_SETPID = 1,		//�򿪹��ģ��
}D_HIV2AD_Msg_Type;

/** @brief haier ��������Դ����*/
typedef struct
{
    D_U16             txt_id;         //ÿ����Ļ��id�ţ����ںͷ���������pic_id��Ӧ
		D_U8							flag; 			//���ڱ�ʶ��Դ��Ч��
    D_U32             back_color;     //��Ļ������ɫ
    D_U32             font_color;     //��Ļǰ����ɫ
    D_U16             font_size;      //�����С
    D_U32             language_code;  //�������
    D_U8              txt_speed;      //�����ٶ�
    D_U16             txt_length;     //��Ļ���ݳ���
    D_U8              *content;       //��Ļ����
}txt_res_info_t;


/** @brief haier ͼƬ��Դ����*/
typedef struct
{
	D_U16 				pic_id;			//ͼƬID
	D_U8					flag;				//���ڱ�ʶ��Դ��Ч��
	D_ImageType	  img_type;		//ͼƬ����
	D_U16					pic_width;		//ͼƬ���
	D_U16					pic_height;		//ͼƬ�߶�
	D_Size				pic_length;		//������ݳ���
	D_U8*					image;			//ͼƬ����
}pic_res_info_t;


/** @brief ��Դ��Ϣ*/
typedef	struct
{
	D_U8										cnt;	//����
	pic_res_info_t*					pictres;
}pic_resource_info;


/** @brief ��Դ��Ϣ*/
typedef	struct
{
	D_U8										cnt;	//����
	txt_res_info_t*					txtres;
}txt_resource_info;

/************************************************************************************/
/************************************************************************************/

/** @brief haier ��������������*/
typedef struct
{
    D_U16             ts_id;      //ָ��TS��ID
    D_U16             service_id; //ָ������ID
    D_U16             pic_id;     //��Ӧ�Ĺ��ID,txtʱ���ӦTXTID
}service_id_info_t;

/** @brief haier ��沥�Ų���*/
typedef	struct											//���������ʾ����
{
	D_U16 		posx;
	D_U16 		posy;
	D_U16 		disp_w;
	D_U16 		disp_h;
	D_U32			duration;	
}play_paras_t;

/** @brief haier ������Բ���*/
typedef struct
{
		D_U16 						ad_id;								//���ID
		D_U8							flag; 								//���ڱ�ʶ��Դ��Ч��
		D_U8							ad_ver; 							//���汾
		D_U8							ad_type;							//�������
    play_paras_t      play_paras;     			//��沥�Ų���
		D_U8							area_cnt;							//������������ID�ĸ���
		D_U32 						*area_code; 				  //����������ID
    D_U8              pic_cnt;              //�������͹�����
    D_U16   					*pic;
    D_U8              ser_cnt;  						//����
    service_id_info_t *service;
} ad_paras_info_t;

/************************************************************************************/
/************************************************************************************/

/************************************************************************************/
/************************************************************************************/

/** @brief ��Ϊͼ����Ĳ����ṹ*/
typedef struct _D_hiv2_fullscan
{
    D_U32          id;          /*ͼƬID       */
    D_Ad_Data_Type data_type;   /*ͼƬ����*/
    D_Ptr          data_ptr;    /*ͼƬ����ָ��*/
    D_U32          data_len;    /*ͼƬ���ݳ���*/
    D_U8           erase;   /*ͼƬ����*/
    D_U16          left;    /*ͼƬ��߾�*/
    D_U16          top;     /*ͼƬ�ϱ߾�*/
		D_U32 		duration; 
} D_hiv2_fullscan ;

/** @brief ��Ŀ����*/
typedef struct _hiv2ad_program_para
{
    D_U16 usNetworkId;
    D_U16 usTsId;
    D_U16 usServiceId;
} hiv2ad_program_para;

/** @brief OSD��ʾ��Ϣ*/
typedef struct _hiv2ad_osd_show_info
{
		D_U32 							txtId;//������ɫ
		D_U32               aucBackgroundColor;//������ɫ
    D_U32               aucDisplayColor;   //������ɫ
    D_U16               usContentSize;        //osd���ݳ���
    D_U16               usGetBufferSize;
    D_U8*               pucDisplayBuffer;     //osd����
    D_U16               ucFontType;           //��������
    D_U16               ucFontSize;           //�����С
    D_U8                ucShowTimes;          //��ʾ����
		D_U8								txtSpeed; 						//����
		D_U16 							ucstartposx;						//����
		D_U16 							ucstartposy;						//����
		D_U16 							ucendposx;						//����
		D_U16 							ucendposy;						//����
    D_U8                scrollend;          //��ʾ����
}hiv2ad_osd_show_info;

/** @brief MG���OSD��ʾ������Ϣ�ӿ�*/
typedef struct _hiv2ad_osd_prog_show_info
{
	hiv2ad_osd_show_info stTextShow[255];	
	D_U8 ucOsdNum;
}hiv2ad_osd_prog_show_info;

/** @brief ����û��Զ�����Ϣ*/
typedef struct 
{
	D_HIV2AD_Msg_Type	type;	/**< ��Ϣ����*/
	D_U32			param1;	/**< ����1*/
	D_U32			param2;	/**< ����2*/	
	D_U16			param3;	/**< ����3*/
} D_HIV2AD_Msg;



extern D_Result hiv2ad_open(D_U8 ucPriority,ADEVENTCALLBACK cb)D_FUNCPOSTFIT;
extern D_Result hiv2ad_Close(void)D_FUNCPOSTFIT;
extern D_Result hiv2ad_SetDataPid(void)D_FUNCPOSTFIT;
extern D_Result hiv2ad_chan_change(D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT;
extern void d_hiv2ad_ShowMessage(D_U8 ucMessageType, D_U8* pucMessage)D_FUNCPOSTFIT;
extern D_Image *hiv2ad_get_image_by_idx(HIV2_Ad_Pos_Type HiAd_type,hiv2ad_program_para *prog, D_U8 _idx, D_U8 *uctotal, D_U16 *left, D_U16 *top, D_U32 *time)D_FUNCPOSTFIT;
extern D_Result	 hiv2ad_ProgramGetOSD(hiv2ad_program_para prog, hiv2ad_osd_prog_show_info * pstOsdProgramShow)D_FUNCPOSTFIT;
extern D_Result hiv2ad_CallBackOSD(D_U32 txtid)D_FUNCPOSTFIT;
#endif

