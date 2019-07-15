/** @file
* @brief ���ģ���ȡ�ӿ�
* @author liuwf
* @date 2014-04-03 ��ΰ��: �����ļ�
*/

#ifndef __DESAI_DATA_STORE_H__
#define __DESAI_DATA_STORE_H__

#include "dGraph.h"
#include "dadporting.h"


/** @brief ͼƬ��Ϣ����*/
typedef struct
{
	D_U32 advType;		// ͼƬӦ������
	D_ImageType imgType;// ͼƬ����
	D_U32 id;			// id
	D_Size offset;		// img������flash�����е�ƫ��
	D_Size img_size;	// img���ݴ�С
	D_U32 times;		// img��ʾʱ�� 100ms
	D_U16 left;			// img��ʾ�������
	D_Int top;			// img��ʾ�������
	D_Int width;		// img��ʾ���
	D_Int height;		// img��ʾ�߶�
    D_U32 crc;
}D_Ad_Pict_Param;

/** @brief ͼƬ��Ϣ����֮���������Ϣ*/
typedef struct Ad_Data_Info_s
{
	D_Ad_Pict_Param item;	// ͼƬ��Ϣ
    D_U32 picid;
	D_U8 *buffer;		//���ݵ�ָ��
	struct Ad_Data_Info_s *next;
}Ad_Data_Info;

/** @brief �򿪹��ģ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
extern D_Result d_ad_store_open (void) D_FUNCPOSTFIT;

/** @brief �ر�logoģ�飬�ͷ���Դ
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
extern D_Result d_ad_store_close (void) D_FUNCPOSTFIT;

/** @brief ɾ��ĳ��Ӧ�õ�ͼƬ���ݺ���Ϣ
* @param  type ͼƬӦ������
* @return D_OK	ɾ���ɹ���D_ERR	ɾ���ɹ�
*/
extern D_Result d_ad_store_delete_by_type(D_Ad_Pos_Type type)D_FUNCPOSTFIT;

/** @brief ���ĳ��Ӧ�õ�ͼƬ���ݺ���Ϣ
* @param  type ͼƬӦ������
* @return D_OK	��ӳɹ���D_ERR	���ʧ��
*/
extern D_Result d_ad_store_insert_by_type(D_Ad_Pos_Type type, D_Ad_Img_Param *img_param)D_FUNCPOSTFIT;


/***********���º����ǶԴ洢�����ݵĽӿ�**************/

/** @brief ��ȡĳ��Ӧ�õ�ͼƬ����
* @param  type ͼƬӦ������
* @return ��������Ӧ�õ�ͼƬ������
*/
extern D_U8 d_ad_store_get_img_count (D_Ad_Pos_Type type) D_FUNCPOSTFIT;

/** @brief ��ȡĳ��Ӧ�õ�ͼƬ���ݺ���Ϣ
* @param  type ͼƬӦ������
* @param  no �ڼ���������͵�ͼƬ
* @return ����ͼƬ��Ϣ��ָ��
*/
extern Ad_Data_Info * d_ad_store_load_img_data(D_Ad_Pos_Type type, D_U8 no)D_FUNCPOSTFIT;

/** @brief �ͷ�ĳ��ͼƬ
* @param img_data	ͼƬ��Ϣ��ָ��
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
* @note   ���ⲿʹ�õĽӿ�
*/
extern D_Result d_ad_store_release_img_data(Ad_Data_Info *img_data)D_FUNCPOSTFIT;


/** @brief ɾ��ĳ����Ӧ�õ�ͼƬ���ݺ���Ϣ
* @param  types ͼƬӦ����������
* @param  type_cnt ͼƬӦ�����������С
* @return D_OK  ɾ���ɹ���D_ERR ɾ���ɹ�
*/
D_Result d_ad_store_delete_some_types(D_Ad_Pos_Type *types, D_U32 type_cnt)D_FUNCPOSTFIT;

/** @brief ���ĳ����Ӧ�õ�ͼƬ���ݺ���Ϣ
* @return D_OK  ��ӳɹ���D_ERR ���ʧ��
*/
D_Result d_ad_store_insert_some_types(D_Ad_Store_Img_Param *param, D_U32 cnt)D_FUNCPOSTFIT;

/** @brief ɾ������
* @return D_OK  ɾ���ɹ���D_ERR ɾ���ɹ�
*/
D_Result d_ad_store_delete_all(void)D_FUNCPOSTFIT;

#endif
