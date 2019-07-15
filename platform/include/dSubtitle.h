/** @file
* @brief Subtitle����
* @author ��ΰ��
* @date 2013-11-18 ��ΰ��: �����ļ�
*/
#ifndef __D_SUBTITLE_H__
#define __D_SUBTITLE_H__
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dScan.h"
#include "dFrame.h"
#include "dGUI.h"
#include "dGraph.h"
#include "dGDev.h"
#include "dVisual.h"


#define REGION_NUM				5		//һ��page������region��Ŀ 
#define PALLETTE_NUM			256 	//ɫ���С
#define OBJECT_NUM				5		//һ��region������object��Ŀ
#define PIXEL_PTR_LENGTH		1000
#define D_SUB_PES_MAX_LENGTH	0x6000	//�趨PES������󳤶�


// ��������
typedef enum
{
	P_SUB_PMT_ERROR,
	P_SUB_PES_ERROR,
	P_SUB_UNKNOW_ERROR		
}D_Sub_Error_Type;

/** @brief Ƶ��������������(�Զ�/�ֶ�)*/
typedef struct
{
	D_HQueue hqueue;			/*ע��������Ϣ����*/
	D_S8 	priority;
	D_U8 	*lang;
	D_U16 	pid;
	D_U8 	type;	
	D_U16	com_page_id;
	D_U16	anc_page_id;
} D_SubTaskConfig;

enum	//ҳ������״̬
{
	NORMAL_CASE,	
	ACQUISITON_POINT,
	MODE_CHANGE,
	RESERVED,
};

/** @brief ����Object����*/ //�ο�ets300743
typedef struct ObjectStruct_s
{
	D_U16 object_id;
	D_U8 object_type;					
	D_U8 object_provider_flag;
	D_U16 object_horizontal_position;//object ˮƽ��ַ
	D_U16 object_vertical_position;		//object ��ֱ��ַ
	D_U8 foreground_pixel_code;
	D_U8 background_pixel_code;
}ObjectStruct_t;

/** @brief ����ҳ����*/	//�ο�ets300743
typedef struct CompositionStruct_s
{
	D_U8 region_id;						
//	D_U16 region_horizontal_address;//����ֱ��ַ
//	D_U16 region_vertical_address;	//����ˮƽ��ַ
	D_U8 region_fill_flag;
	D_U8 region_level_of_compatibility;
	D_U8 region_depth;
//	D_U16 region_width;				//������
//	D_U16 region_height;			//����߶�
	D_U8 CLUT_id;
	ObjectStruct_t object_group[OBJECT_NUM];
	D_Image	*region_img;				//��������buffer
	D_U32 Pixel_Position;			//���ظ���
	D_Rect dr;
	D_Rect sr;
}CompositionStruct_t;

/** @brief ����ɫ������*/
typedef struct	PalletteStruct_s
{
	D_U8 Y;
	D_U8 Cb;
	D_U8 Cr;
	D_U8 weight;
}PalletteStruct_t;

typedef struct Color_s
{
	D_U8 R;
	D_U8 G;
	D_U8 B;
	D_U8 bSolid;
}Color_t;

/** @brief subtitle������Դ*/
typedef struct
{
    D_U32       table_mode;		/**@brief < ���˱��table id*/
	D_HQueue 	hqueue;			/*ע��������Ϣ����*/
    D_U8        *buf;			/**@brief < Ϊ����������ڴ��ַ*/
    D_U8        *sec;			/**@brief < ����demux���յ�����*/
    D_HDemux    hdemuxpes;		/**@brief< �� �� ��Demux���*/
    D_HMMan     hmm;			/**@brief < Ϊ����������ڴ洴�����ڴ���������*/
    D_HMMan     hsi_mm;		    /**@brief< ����ʱ�����ڴ��õ��ڴ���������*/
    D_HApp      hsub;			/**@brief< ����Ӧ�þ��*/
	D_U8 		lang[3];           /**@brief< ��������*/
	D_U16 		pid;
	D_U8 		type;	
	D_U16		com_page_id;
	D_U16		anc_page_id;

	D_U8* PixelPtr; 				//���ػ�����
	D_U16 		page_id;       
	D_U8 page_state;  
	CompositionStruct_t CompositionPtr[REGION_NUM];		 //ҳ���Խṹ��
	PalletteStruct_t	SubtitlePallette[REGION_NUM][PALLETTE_NUM];//ɫ�建����
	D_U32	SubPal[REGION_NUM][PALLETTE_NUM];//ɫ�建����2
	D_U8 region_num;				//�����
	D_U8 clut_num;					//ɫ�����
	D_U8 CLUT_IDT[REGION_NUM];		//ɫ��ID
	D_U8 clut_num_array[REGION_NUM];		//ɫ�����
	D_U8 RegionID[REGION_NUM];		//����ID
	D_U8 object_num[REGION_NUM];		//ÿ��������object�ĸ���
	D_U8 regionshownum;				//��ǰregion
	D_U8 byte_flag;					//�ֽڱ�־
	D_U16 pixel_num;				//���ظ���
	D_U16 pixelcount;				//���ش������
	D_U32 PixePos;					//���ظ���
	D_U8 linenum;					//�߸���
	D_U8 HideColor;	
	D_U32 tpage_time_out;
} D_SUBESData;

/** @brief ������ʾ�ӿ�*/
typedef struct	sub_osd_img_s
{
	D_U8 region_num;				//������
	D_Image	*region_img[REGION_NUM];				//��������buffer
	D_Rect dr[REGION_NUM];
	D_U32 tpage_time_out;
	D_S32 pts;
	D_U8 page_state;  	
}sub_osd_img_t;


/** @brief����Subtitle��������
* @param[in] priority �������ȼ�
* @return �ɹ������豸���,ʧ�ܷ���D_INVALID_HANDLE
*/
D_HScan d_sub_scan_create(D_SubTaskConfig taskconfig)D_FUNCPOSTFIT ;

D_Result d_sub_scan_destroy (D_HScan hscan)D_FUNCPOSTFIT;

/** @brief �����Ļ����Դָ��*/
sub_osd_img_t * p_get_subtitle_resource(void)D_FUNCPOSTFIT;

/** @brief ��ȡ��Ļ���ݽ�����ɱ��*/
D_Bool p_get_sub_ready_flag(void)D_FUNCPOSTFIT;

/** @brief ��ʼ����Ļ���ݽ�����ɱ��*/
void p_reset_sub_ready_flag(void)D_FUNCPOSTFIT;

sub_osd_img_t * p_get_sub_last_osd(void)D_FUNCPOSTFIT;

void p_set_sub_last_osd(sub_osd_img_t *sub)D_FUNCPOSTFIT;


/** @brief Ϊ��ʾ������subtitle����
* @param[in] es ��Դָ��
*/

#ifdef  __cplusplus
}
#endif
#endif
