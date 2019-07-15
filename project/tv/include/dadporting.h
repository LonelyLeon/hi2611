/** @file
* @brief ���ģ��֧�Žӿ�
* @author hegx
* @date 2014-03-03 �͹���: �����ļ�
*/
#ifndef _D_ADPORTING_H_
#define _D_ADPORTING_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dDebug.h"
#include <string.h>
#include "dMMan.h"
#include "dMem.h"
#include "dDemux.h"
#include "dTimer.h"
#include "dGraph.h"
#include "dResource.h"

#define D_AD_MODULE_TASK_PRIO			3

/** @brief ���汾*/
#define AD_STB_HAIERV1  0x0 //�������V1.0
#define AD_STB_HAIERV2  0x1 //�������V2.0
#define AD_STB_DESAI 	0x2 //�������
#define AD_STB_MG 		0x3 //���޹��
#define AD_STB_IFABOO   0x4 //�������
#define AD_STB_DIVI	    0x5 //����ͨ���
#define AD_STB_DVT	    0x6 //������Ѷ���
#define AD_STB_MAX  	0x7 //δ֪����

/** @brief  ����������Դ���ͣ��ı�����ͼƬ*/
#define P_SCROLL_SRC_TYPE_TEXT (0)
#define P_SCROLL_SRC_TYPE_IMAGE (1)

#define DAD_DEMUX_TOTAL_TYPE  0x10//����demux֧����
#define DAD_PIC_TOTAL_TYPE    20//����ͼƬ��
#define DAD_TIMER_TOTAL_TYPE  0x20//���Ķ�ʱ��

/** @brief �����*/
typedef D_Handle	D_AdHand;

/** @brief ������ƽ̨*/
typedef enum 
{
	DAD_STB_SD=1, 	/*����*/
	DAD_STB_HD=2, 	/*����*/
	DAD_STB_UNKNOWN,/*δ֪����*/
}D_Ad_Stb_Decode_Type;

/** @brief ���Ӧ������*/
typedef enum 
{
	DAD_STB_LOG = 1,         /*�������*/
	DAD_STB_EPG ,         /*EPG���*/
	DAD_STB_FULLSCREEN ,  /*���͹��*/
	DAD_STB_VOLUME,      /*�������*/
	DAD_STB_MENU ,		 /*���˵����*/
	DAD_STB_MENU_UP,	 /*���˵������*/
	DAD_STB_MENU_DOWN,	 /*���˵������*/
	DAD_STB_UNAUTHORIZED,/*δ��Ȩ��Ŀ���*/
	DAD_STB_BANNER,      /*��Ŀ��Ϣ�����*/
	DAD_STB_OSD,         /*OSD���*/
	DAD_STB_RadioBackGround,
	DAD_STB_Nosignal,
	DAD_STB_NoProgram ,
	DAD_STB_ProgramList,//��Ŀ�б���
	DAD_STB_PICOSD,		 /*ͼƬOSD���*/
	DAD_STB_FavorList,//ϲ���б��� @qiny add 2015.03.20
	DAD_STB_POS_UNKNOWN,     /*δ֪����*/
}D_Ad_Pos_Type;

/** @brief �����������*/
typedef enum 
{
	DAD_PIC_DATA = 1,       /*ͼƬ����*/
	DAD_M2V_DATA = 2,       /*��Ƶ���� */  
}D_Ad_Data_Type;

/** @brief OSD��ʾλ��*/
typedef enum  
{
	TOP_BOTTOM = 1,				/*�ڶ����͵ײ�ͬʱ��ʾ*/  
	LEFT_RIGHT,				    /*����ߺ��ұ�ͬʱ��ʾ*/  
	LOCAL_HORIZONTAL, 			/*������ʾ*/  
	LOCAL_VERTICAL,				/*������ʾ*/  
	UNKNOWN_TYPE,
}D_Ad_Osd_Show_Pos;


/** @brief ֧�ֵĹ������*/
typedef enum 
{
	DAD_OPEN = 1,		 //�򿪹��ģ��
	DAD_CLOSE ,		 	 //�رչ��ģ��
	DAD_APP_INIT ,		 //����һ�����Ӧ��
	DAD_APP_EXIT ,		 //�˳�һ�����Ӧ��
	DAD_SET_PARAM ,	 	 //���ý�Ŀ����
	DAD_RESET_DATA , 	 //���ý�Ŀ����
	DAD_APP_RELEASEDATA, //�ͷ�����
	DAD_UPDATE_DATA ,	 //���ݸ���
	DAD_ERASE_DATA ,  //���ݲ���
}D_Ad_Msg_Type;


/** @brief ������ò���*/
typedef struct
{
	D_Ad_Stb_Decode_Type type;  /*���ƽ̨*/  
	D_U8 dstag;					/*DS���TAG*/  
	D_U8 mgtag;					/*MG���TAG*/  
	D_U8 ifabootag;				/*�������TAG*/  
	D_U8 hitag;					/*�������TAG*/  
	D_U8 divitag;				/*����ͨ���TAG*/ 
	D_U8 ucPriority;			/*����������ȼ�*/  
	D_U32 uiFlashStartAddress;  /*���Flash ��ʼ��ַ*/  
}d_ad_config;


/** @brief ��Ϊͼ����Ĳ����ṹ*/
typedef struct _D_Ad_Image_Param
{
	D_Ad_Data_Type data_type;   //ͼƬ����
	D_U32 		   id;		    //ͼƬID      
	D_U32 		   times;		//��ʾʱ�䣬0xffffffffΪ һֱ��ʾ
	D_Ptr 		   data_rsc_ptr;//����ָ�봫�ݣ������ͷ�������Դ
	D_U8 		   if_erase;	//���������־  
	D_U16		   left;		//��ʼ����x
	D_U16		   top;			//��ʼ����y
	D_Image* 	   image;		//ͼƬ��Դ
	D_U8 		   uctotal;     //ͼƬ������������1ʱ����һ��ͼƬ����ʾʱ�䵽֮��ȡ��һ��ͼƬ
}D_Ad_Image_Param ;

/** @brief ��ΪOSD���Ĳ����ṹ*/
typedef struct _D_Ad_Osd_Param
{
	D_Ptr data_rsc_ptr;			//����ָ�봫�ݣ������ͷ�������Դ
	D_U8  if_erase;				//���������־  
	D_U8  enDisplayPos; 		//osd��ʾλ������
	D_U32 aucBackgroundColor;	//������ɫ
	D_U32 aucDisplayColor;   	//������ɫ
	D_U8* pucDisplayBuffer;     //osd����
	D_U16 usContentSize;        //osd���ݳ���
	D_U16 ucFontType;           //��������
	D_U16 ucFontSize;           //�����С
	D_U32 ucShowTimes;          //��ʾ����
	D_U32 id;		   			//ͼƬID ,��id�൱ʱ���ϲ㴦��Ϊ��ͬһ�����������¹���  
	D_U8  uctotal;          	//����
	D_U8  idx;          		//��ǰ��������idx�����ڲ�����һ��
	D_U8  txtSpeed;          	//�ٶ�
	D_U16 ucstartposx;          //��ʼ����x
	D_U16 ucstartposy;          //��ʼ����y
	D_U16 ucendposx;          	//�յ�����x,��TOP_BOTTOM/LEFT_RIGHTʱ��ʹ��Ϊ�ڶ�������ʼ����x
	D_U16 ucendposy;          	//�յ�����y,��TOP_BOTTOM/LEFT_RIGHTʱ��ʹ��Ϊ�ڶ�������ʼ����y
	D_U8  ucType;               //ͼƬ�������ı������� Ĭ�����ı�����
}D_Ad_Osd_Param;


/** @brief �ص�����*/
typedef struct {
	D_U32			param1;	/**< ����1*/
	D_U32			param2;	/**< ����2*/
	D_U8*			param3;	/**< ����2*/
} D_AdFunBack;

typedef void (* ADFunctionBack)(D_AdFunBack *param,D_U8* sec,D_U32 len);


/** @brief �û��Զ�����Ϣ*/
typedef struct {
	D_MsgType		type;		/**< ��Ϣ����*/
	D_U32			param1;	/**< ����1*/
	D_U32			param2;	/**< ����2*/
	D_Ptr 			handle;
	D_U16 			usNetworkId;
	D_U16 			usTsId;
	D_U16 			usServiceId;	
} D_AdMsg;

/** @brief �¼�����*/
typedef struct _D_Ad_Event_Param
{
	D_U8 		use_flag;
	D_HMutex	hm;						/*������*/
	D_HDemux    hdemux;
	D_U32 		starttime;
	ADFunctionBack Function;
	D_AdFunBack param;
    D_HTimer    htimer;	
	D_DemuxType	type;			/**< �⸴���豸����*/
	D_Size		buf_size;	/**< �⸴���豸��������С*/
	D_Bool	    one_shot;	/**< �Ƿ��ǵ����Ͷ�ʱ��*/
	
}D_Ad_Event_Param;

/** @brief ��Ŀ����*/
typedef struct _D_Ad_Service_Param
{
	D_U16 usNetworkId;
	D_U16 usTsId;
	D_U16 usServiceId;
}D_Ad_Service_Param;

typedef D_Handle (*ADEVENTCALLBACK)(D_U8 event, D_Ad_Event_Param *param);

typedef struct _D_Ad_Init_Param
{
	D_Ad_Stb_Decode_Type type;
	D_HQueue	queue;
	D_U32 		uiFlashStartAddress;		
	D_Size		buf_size;	/**< �⸴���豸��������С*/
	D_U8 ucPriority;
	ADEVENTCALLBACK cb;
}D_Ad_Init_Param;

typedef struct _D_Ad_Start_Param
{
	D_FEndAttr attr;
}D_Ad_Start_Param;

/** @brief ͼƬ��Ϣ����*/
typedef struct
{
	D_ImageType imgType;// ͼƬ����
	D_U32 id;			// id
	D_U16 times;		// img��ʾʱ�� 100ms
	D_U16 left;			// img��ʾ�������
	D_Int top;			// img��ʾ�������
	D_Int width;		// img��ʾ���
	D_Int height;		// img��ʾ�߶�
	D_U8 *buf;			// img������ָ��
	D_Size img_size;	// img���ݴ�С
}D_Ad_Img_Param;

typedef struct
{
	D_Ad_Pos_Type posType;
	D_Ad_Img_Param img_param;
}D_Ad_Store_Img_Param;


/** @brief ͼƬ��Ϣ����֮���Ӧ�õ�������Ϣ*/
typedef struct d_ad_pict_info_s
{
	D_U32 advType;		// ͼƬӦ������
	D_ImageType imgType;// ͼƬ����
	D_U32 id;			// id
	D_U8 *buffer;		//���ݵ�ָ��
	D_Size img_size;	// img���ݴ�С
	D_U32 times;		// img��ʾʱ��
	D_U16 left;			// img��ʾ�������
	D_Int top;			// img��ʾ�������
	D_Int width;		// img��ʾ���
	D_Int height;		// img��ʾ�߶�
	D_U8 *hand;			//�����ָ��
}d_ad_pict_info;

/** @brief �ص��¼�*/
typedef enum  
{
	DAD_EVENT_CREATE_DEMUX = 1,				/*����ͨ��*/  
	DAD_EVENT_START_DEMUX,					/*��ͨ��*/  
	DAD_EVENT_DESTROY_DEMUX,				/*����ͨ��*/  
	DAD_EVENT_STOP_DEMUX,					/*ֹͣͨ��*/  
	DAD_EVENT_CREATE_TIMER, 			    /*������ʱ��*/	
	DAD_EVENT_DESTROY_TIMER,				/*���ٶ�ʱ��*/  
	DAD_EVENT_UPDATE_DATA,				/*�и���*/	
	DAD_EVENT_ERASE_DATA,					/*����*/	
	DAD_EVENT_MAX,
}D_Ad_EVENT_TYPE;

typedef struct _D_Ad_Op	D_Ad_Op;

struct _D_Ad_Op {
	D_Result (*check_scan)(void)D_FUNCPOSTFIT;
	D_Result (*init)(D_Ad_Init_Param *cfg)D_FUNCPOSTFIT;
	D_Result (*exit)(void)D_FUNCPOSTFIT;
	D_Result (*start)(D_Ad_Start_Param *cfg)D_FUNCPOSTFIT;
	D_Result (*reset)(void)D_FUNCPOSTFIT;
	D_Result (*getversion)(D_U8 *sversion)D_FUNCPOSTFIT;
	D_Result (*enter_app)(D_Ad_Pos_Type type)D_FUNCPOSTFIT;
	D_Result (*exit_app)(D_Ad_Pos_Type type)D_FUNCPOSTFIT;
	D_Result (*get_img)(D_Ad_Service_Param *chan_param,D_Ad_Pos_Type type,D_U8 idx,D_U8* info)D_FUNCPOSTFIT;
	D_Result (*release_img)(D_Ad_Pos_Type type,D_U8* image)D_FUNCPOSTFIT;
	D_Result (*setdescr)(D_U8 * descr,D_U32 id)D_FUNCPOSTFIT;
	D_Result (*settag)(D_U8 ttag,D_U32 id)D_FUNCPOSTFIT;
	D_Result (*check_app)(D_Ad_Pos_Type type,D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT;
	D_Result (*set_fp_key)(D_U32 key)D_FUNCPOSTFIT;
	D_Result (*check_fp_key)(D_Ad_Pos_Type type,D_U32 key)D_FUNCPOSTFIT;	
	D_Result (*scroll_callback)(D_U8 idx,D_U8 total)D_FUNCPOSTFIT;	
	D_Result (*chan_change)(D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT;	
/**���¼���������ֱ��ȡ��������ݣ��������ϲ��Լ���ʾ��ʱ��ʹ��*/
	D_U8 (*get_img_count_ex)(D_Ad_Pos_Type type)D_FUNCPOSTFIT;
	D_Result (*load_img_data_ex)(D_Ad_Pos_Type type, D_U8 no,d_ad_pict_info *info)D_FUNCPOSTFIT;
	D_Result (*release_img_data_ex)(d_ad_pict_info *img_data)D_FUNCPOSTFIT;
};
extern D_U8 * d_dad_getop(void)D_FUNCPOSTFIT;
extern D_Result d_ad_modlue_Open(d_ad_config *cfg)D_FUNCPOSTFIT;
extern D_Result d_ad_enter_menu_ex(D_Ad_Pos_Type type,D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT;
extern D_Result d_ad_exit_menu_ex(D_Ad_Pos_Type type)D_FUNCPOSTFIT;
extern D_Result d_ad_set_chan_ex(D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT;
extern D_Ptr  d_ad_get_img_ex(D_Ad_Pos_Type type)D_FUNCPOSTFIT;
extern D_Result d_ad_release_img_ex(D_Ad_Pos_Type type,D_Ptr handle)D_FUNCPOSTFIT;
extern D_Result d_ad_modlue_start(D_Ad_Start_Param *cfg)D_FUNCPOSTFIT;
extern D_Result d_ad_Check_App(D_Ad_Pos_Type type,D_Ad_Service_Param *chan_param)D_FUNCPOSTFIT;
extern D_Result d_ad_set_fpkey_ex(D_U8 key)D_FUNCPOSTFIT;
extern D_Result d_ad_check_fpkey_ex(D_Ad_Pos_Type type,D_U8 key)D_FUNCPOSTFIT;
extern D_Result d_ad_scroll_callback(D_U8 idx,D_U8 total)D_FUNCPOSTFIT;
extern D_U8 d_ad_get_img_count (D_Ad_Pos_Type type) D_FUNCPOSTFIT;
extern D_Result d_ad_load_img_data(D_Ad_Pos_Type type, D_U8 no, d_ad_pict_info *info)D_FUNCPOSTFIT;
extern D_Result d_ad_release_img_data(d_ad_pict_info *img_data)D_FUNCPOSTFIT;
extern D_Result d_ad_SetDescr(D_U8 * descr, D_U32 id)D_FUNCPOSTFIT;
#ifdef  __cplusplus
}
#endif


#endif

