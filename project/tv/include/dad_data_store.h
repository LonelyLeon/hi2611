/** @file
* @brief 广告模块存取接口
* @author liuwf
* @date 2014-04-03 刘伟峰: 建立文件
*/

#ifndef __DESAI_DATA_STORE_H__
#define __DESAI_DATA_STORE_H__

#include "dGraph.h"
#include "dadporting.h"


/** @brief 图片信息描述*/
typedef struct
{
	D_U32 advType;		// 图片应用类型
	D_ImageType imgType;// 图片类型
	D_U32 id;			// id
	D_Size offset;		// img数据在flash分区中的偏移
	D_Size img_size;	// img数据大小
	D_U32 times;		// img显示时间 100ms
	D_U16 left;			// img显示相对坐标
	D_Int top;			// img显示相对坐标
	D_Int width;		// img显示宽度
	D_Int height;		// img显示高度
    D_U32 crc;
}D_Ad_Pict_Param;

/** @brief 图片信息解析之后的数据信息*/
typedef struct Ad_Data_Info_s
{
	D_Ad_Pict_Param item;	// 图片信息
    D_U32 picid;
	D_U8 *buffer;		//数据的指针
	struct Ad_Data_Info_s *next;
}Ad_Data_Info;

/** @brief 打开广告模块
* @return 成功返回D_OK,失败返回D_ERR
*/
extern D_Result d_ad_store_open (void) D_FUNCPOSTFIT;

/** @brief 关闭logo模块，释放资源
* @return 成功返回D_OK,失败返回D_ERR
*/
extern D_Result d_ad_store_close (void) D_FUNCPOSTFIT;

/** @brief 删除某种应用的图片数据和信息
* @param  type 图片应用类型
* @return D_OK	删除成功；D_ERR	删除成功
*/
extern D_Result d_ad_store_delete_by_type(D_Ad_Pos_Type type)D_FUNCPOSTFIT;

/** @brief 添加某种应用的图片数据和信息
* @param  type 图片应用类型
* @return D_OK	添加成功；D_ERR	添加失败
*/
extern D_Result d_ad_store_insert_by_type(D_Ad_Pos_Type type, D_Ad_Img_Param *img_param)D_FUNCPOSTFIT;


/***********以下函数是对存储的数据的接口**************/

/** @brief 获取某种应用的图片数量
* @param  type 图片应用类型
* @return 返回这种应用的图片的数量
*/
extern D_U8 d_ad_store_get_img_count (D_Ad_Pos_Type type) D_FUNCPOSTFIT;

/** @brief 获取某种应用的图片数据和信息
* @param  type 图片应用类型
* @param  no 第几个这个类型的图片
* @return 返回图片信息的指针
*/
extern Ad_Data_Info * d_ad_store_load_img_data(D_Ad_Pos_Type type, D_U8 no)D_FUNCPOSTFIT;

/** @brief 释放某个图片
* @param img_data	图片信息的指针
* @return 成功返回D_OK,失败返回D_ERR
* @note   给外部使用的接口
*/
extern D_Result d_ad_store_release_img_data(Ad_Data_Info *img_data)D_FUNCPOSTFIT;


/** @brief 删除某几种应用的图片数据和信息
* @param  types 图片应用类型数组
* @param  type_cnt 图片应用类型数组大小
* @return D_OK  删除成功；D_ERR 删除成功
*/
D_Result d_ad_store_delete_some_types(D_Ad_Pos_Type *types, D_U32 type_cnt)D_FUNCPOSTFIT;

/** @brief 添加某几种应用的图片数据和信息
* @return D_OK  添加成功；D_ERR 添加失败
*/
D_Result d_ad_store_insert_some_types(D_Ad_Store_Img_Param *param, D_U32 cnt)D_FUNCPOSTFIT;

/** @brief 删除所有
* @return D_OK  删除成功；D_ERR 删除成功
*/
D_Result d_ad_store_delete_all(void)D_FUNCPOSTFIT;

#endif
