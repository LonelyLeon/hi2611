#ifndef _D_SCROLL_H_
#define _D_SCROLL_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"
#include "dGraph.h"

typedef D_Handle D_HScroll;

typedef enum _Scroll_Type				/**<����������*/	
{
	H_SCROLL_RIGHT_TO_LEFT,			/**<���д����������*/	
	H_SCROLL_LEFT_TO_RIGHT,			/**<���д������ҹ���*/	
	V_SCROLL_BOTTOM_TO_TOP,			/**<���д������Ϲ���*/	
	V_SCROLL_TOP_TO_BOTTOM,			/**<���д������¹���*/	
//	MULTI_V_SCROLL_BOTTOM_TO_TOP,	/**<���д������Ϲ���*/	
//	MULTI_V_SCROLL_TOP_TO_BOTTOM,	/**<���д������¹���*/	
}D_ScrollType;

typedef enum _H_Scroll_Direction				/**<��������*/	
{
	H_SCROLL_HORIZONTAL,			/**<ˮƽ*/	
	H_SCROLL_VERTICAL,			    /**<��ֱ*/			
}D_ScrollDirection;

typedef struct {	
	D_Coord				pos_x;			/**< ��������ʾ���ڵ���ʼx����*/
	D_Coord				pos_y;			/**< ��������ʾ���ڵ���ʼy����*/
	D_Coord				win_w;			/**< ��������ʾ���ڵĳ���*/
	D_Coord				win_h;			/**< ��������ʾ���ڵĸ߶�*/
    D_Coord				win_max_w;		/**< ��������ʾ���ڵ���󳤶�*/
	D_Coord				win_max_h;		/**< ��������ʾ���ڵ����߶�*/
    D_ScrollDirection   direction;		/**< ��������ʾ���ڵķ���*/
    D_U8*               text;           /**<��������ʾ����*/
	D_Image*			image;			/**<��������ʾͼƬ*/
	D_U32				bg_color;		/**<������������ɫ*/
	D_U32				text_color;		/**<������������ɫ*/
    D_U8                font_size;      /**<���������ִ�С*/    
	//D_U32				transparence;
	D_ScrollType		scroll_type;	/**<����������*/		
	D_U32				scroll_speed;	/**<�����������ٶ�*/
	D_U32				repeat_times;	/**<�������ظ���������*/
	D_U32				duration;		/**<��������������ʱ��*/
    D_U32				repeat_times_duration;/**<����������������ʱ���ѵ�ʱ��(��λ����)*/
} D_ScrollUsrParas;

/** @brief �������豸����*/
typedef struct {
	D_Coord				w;	
	D_Coord				h;
	D_ScrollType			t;
} D_ScrollAttr;

/** @brief ������״̬*/
typedef enum 					
{
	SCROLL_IDLE = 1 << 0,					/*����������*/
	SCROLL_BEGINNING = 1<<1,				/*������ʼ*/
	SCROLL_CONTINUAL = 1<<2,				/*��������*/
	SCROLL_ENDING = 1<<3,					/*��������,����һ�ν���*/
	SCROLL_DONE = 1<<4 ,					/*�����������(���Ҫ���ʱ������)*/
	SCROLL_USED = 1<<5 ,					/*�������Ѿ�������*/
    SCROLL_VALID = 1<<31

}D_ScrollState;

/** @brief ��ȱʡֵ��ʼ���������豸����*/
#define D_SCROLL_ATTR_INIT(_a)\
	D_MACRO_BEGIN\
		(_a)->w = 720;\
		(_a)->h = 30;\
		(_a)->t = H_SCROLL_RIGHT_TO_LEFT;\
	D_MACRO_END

/** @brief ��������ʾ״̬*/
extern D_U32 ScrollShowStatus;

typedef D_Result (*D_ScrollCallback)(D_HScroll handle,D_ScrollUsrParas paras,D_ScrollState state);

/** @brief �����������ʼ��
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result d_scroll_open(void) D_FUNCPOSTFIT;

/** @brief �����������˳�
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_scroll_close(void) D_FUNCPOSTFIT;

/** @brief ����һ��������
* @param scroll_usr ���������õ���ز���
* @return �ɹ�ʱ���ع��������,ʧ��ʱ����D_INVALID_HANDLE
*/
D_HScroll d_scroll_create (D_Coord win_max_w,D_Coord win_max_h,D_ScrollDirection direction)D_FUNCPOSTFIT;

/** @brief ����һ��������
* @param handle ���������
* @return �ɹ�ʱ����D_OK, ʧ�ܷ���D_ERR
*/
D_Result d_scroll_destory(D_HScroll handle) D_FUNCPOSTFIT;

/** @brief ����������
* @param handle ���������
* @return �ɹ�ʱ����D_OK, ʧ�ܷ���D_ERR
*/
D_Result d_scroll_start(
 D_HScroll handle
,D_Coord win_w  
,D_Coord win_h
,D_ScrollType scroll_type
,D_Coord pos_x		
,D_Coord pos_y		
,D_U8* text		
,D_U32 bg_color	
,D_U32 text_color
,D_U8  font_size
,D_U32 scroll_speed
,D_U32 repeat_times
,D_U32 duration	
,D_Bool immediate
,D_ScrollCallback callback)D_FUNCPOSTFIT;

D_Result d_scroll_start_image(
    D_HScroll handle
    , D_Coord win_w
    , D_Coord win_h
    , D_ScrollType scroll_type
    , D_Coord pos_x
    , D_Coord pos_y
    , D_Image* image
    , D_U32 bg_color
    , D_U32 text_color
    , D_U8  font_size
    , D_U32 scroll_speed
    , D_U32 repeat_times
    , D_U32 duration
    , D_Bool immediate
    , D_ScrollCallback callback)D_FUNCPOSTFIT;

/** @brief ������ֹͣ
* @param handle ���������
* @return �ɹ�ʱ����D_OK, ʧ�ܷ���D_ERR
*/
D_Result d_scroll_stop(D_HScroll handle) D_FUNCPOSTFIT;

/** @brief �����������״̬
* @param handle ���������
* @return ���ʱ����D_TRUE, ʧ�ܷ���D_FALSE
*/
D_ScrollState d_scroll_state(D_HScroll handle) D_FUNCPOSTFIT;

/** @brief ���������
* @param handle ���������
* @return �ɹ�ʱ����D_OK, ʧ�ܷ���D_ERR
*/
D_Result d_scroll_clear(D_HScroll handle) D_FUNCPOSTFIT;

D_HScroll hr_test_scroll_create(void)D_FUNCPOSTFIT;
D_Result hr_test_scroll_start(D_HScroll handle)D_FUNCPOSTFIT;
D_Result hr_test_scroll_start2(D_HScroll handle)D_FUNCPOSTFIT;
	
#ifdef  __cplusplus
}
#endif

#endif

