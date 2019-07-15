#ifndef __ABV_LUD_INTERFACE__
#define __ABV_LUD_INTERFACE__

#ifdef __cplusplus
extern "C" {
#endif

#include "abv_ca_types.h"
#include "os_api.h"

/*******************************************************************************************************************************
********************************************************************************************************************************
*******************************************       Provid By LUD LIB     *****************************************************
********************************************************************************************************************************
********************************************************************************************************************************/


/****************************************************************************
name          		: 	ABV_LUD_Get_Total_Radio_Pic_Num
Description  		:	得到radio图片的总数
Parameters    		: 	num (IN_OUT):图片总数
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 
****************************************************************************/
ABV_Boolean ABV_LUD_Get_Total_Radio_Pic_Num(ABV_UInt16* num) ;

/****************************************************************************
name          		: 	ABV_LUD_Get_Pic_By_Index
Description  		:	按序号得到图片数据
Parameters    		: 	index (IN):图片序号. 
					pic(IN_OUT):图片数据buffer得首地址，传入参数，
					外部需要提前分配一个足够大得空间，来存储图片数据(大于150K)
					pic_length(IN_OUT):图片数据的长度
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 
****************************************************************************/
ABV_Boolean ABV_LUD_Get_Pic_By_Index(ABV_UInt16 index, ABV_UInt8*pic, ABV_UInt32* pic_length);


/****************************************************************************
name          		: 	ABV_LUD_Get_New_Logo
Description  		:	读取新的logo图片数据
Parameters    		: 	logo_length(IN_OUT):logo图片数据的长度
					logo(IN_OUT):logo图片的数据的首地址
					logo_ver(IN_OUT):logo 的版本
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 收到新的开机logo后机顶盒调用此接口，参数logo为二级指针，传入传出型。
					LUD_LIB将logo地址赋值给指针logo。
****************************************************************************/

ABV_Boolean ABV_LUD_Get_New_Logo(ABV_UInt32* logo_length, ABV_UInt8**logo,ABV_UInt8* logo_ver);

/****************************************************************************
name          		: 	ABV_LUD_Update_Logo_Finished
Description  		:	更新logo结束后，释放logo占用的空间。
Parameters    		: 	Void
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	STB更新完logo后调用此接口，通知LUD库更新结束。
****************************************************************************/

ABV_Boolean ABV_LUD_Update_Logo_Finished(void);



/****************************************************************************
name          		: 	ABV_LUD_Notify_To_Get_Date
Description  		:	通知LUD库区copy数据
Parameters    		: 	Void
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	STB收到库需要的数据时，调用此接口通知库。
****************************************************************************/

ABV_Boolean ABV_LUD_Notify_To_Get_Date(void);

/*******************************************************************************************************************************
********************************************************************************************************************************
********************************************       Provid By STB      *********************************************************
********************************************************************************************************************************
********************************************************************************************************************************/


/****************************************************************************
name          		: 	ABV_LUD_Notify_STB
Description  		:	通知机顶盒收到新的开机logo
Parameters    		: 	logo_length(IN):数据长度
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 LUD_LIB收到新的开机logo后调用此接口，通知机顶盒。
****************************************************************************/

ABV_Boolean ABV_LUD_Notify_STB_Get_New_Logo(void);


/****************************************************************************
name          		: 	ABV_LUD_Get_Current_Date
Description  		:	得到当前日期
Parameters    		: 	MJD(IN_OUT):当前日期的MJD 数
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 该接口为中间件平台需要的接口
****************************************************************************/
ABV_Boolean ABV_PDR_Get_Current_Date(ABV_UInt32* MJD);

/****************************************************************************
name          		: 	ABV_LUD_Get_Logo_Version
Description  		:	得到当前logo得版本
Parameters    		: 	logo_ver(IN_OUT): 当前logo得版本
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 
****************************************************************************/
ABV_Boolean ABV_LUD_Get_Logo_Version(ABV_UInt32* logo_ver);

/****************************************************************************
name          		: 	ABV_LUD_Notify_Get_New_Pic
Description  		:	通知机顶盒收到新的图片
Parameters    		: 	Void
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:
****************************************************************************/

ABV_Boolean ABV_LUD_Notify_Get_New_Pic(ABV_UInt16 total_pic_num);
#ifdef __cplusplus
}
#endif
#endif	
