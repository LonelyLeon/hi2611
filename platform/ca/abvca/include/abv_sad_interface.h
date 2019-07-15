/*****************************************************************************
File Name     	: abv_sad_interface.h

Description   	: 业务广告功能接口函数头文件

Copyright (C) : ABV 2009

R&D Group	: ABV_CA

Author(s)	    	:  liuch  

Notes          	: 

History	    	: 

Version 		Date   		Author(s) 	Desciption    Reference

1.0			2009.05.11	       liuch		created

*****************************************************************************/
#ifndef _ABV_SAD_INTERFACE_H
#define _ABV_SAD_INTERFACE_H

#ifdef __cplusplus
extern "C"
{
#endif
typedef struct _serach_sample
{
	ABV_UInt16 tsid;/*transpot stream id*/
	ABV_UInt16 onid;/*original network id*/
	ABV_UInt16 sid;/*service id*/
	
}Sad_Serach_Sample;



/*******************************************************************************************************************************
********************************************************************************************************************************
*******************************************       Provid By SAD LIB     *****************************************************
********************************************************************************************************************************
********************************************************************************************************************************/


/****************************************************************************
name          		: 	ABV_SAD_Get_Ad_By_Sample
Description  		:	按特征值得到图片
Parameters    		: 	sample(IN):特征值，由tsid，sid，osid组合成的特征值
					pic(IN_OU):调用该函数前，由调用者分配一个足够大得空间(大于20K)
					pic为该空间的首地址。
					pic_length(IN_OUT):图片的长度
					text:文本信息
					text_length:文本信息的长度
					
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 调用该函数前，调用者要合成sample参数，并分配一个足够大得空间
					用来存储图片。
****************************************************************************/
ABV_Boolean ABV_SAD_Get_Ad_By_Sample(Sad_Serach_Sample*sample, ABV_UInt8* pic, ABV_UInt32* pic_length,ABV_UInt8* text, ABV_UInt16* text_length);
/****************************************************************************
name          		: 	ABV_SAD_Get_Ad_By_Sample
Description  		:	按特征值得到图片
Parameters    		: 	sample(IN):特征值，由tsid，sid，osid组合成的特征值
					pic(IN_OU):调用该函数前，由调用者分配一个足够大得空间(大于20K)
					pic为该空间的首地址。
					pic_length(IN_OUT):图片的长度
					text:文本信息
					text_length:文本信息的长度
					
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 调用该函数前，调用者要合成sample参数，并分配一个足够大得空间
					用来存储图片。
****************************************************************************/
ABV_Boolean ABV_SAD_Get_Ad_By_Sample(Sad_Serach_Sample*sample, ABV_UInt8* pic, ABV_UInt32* pic_length,ABV_UInt8* text, ABV_UInt16* text_length);

/*******************************************************************************************************************************
********************************************************************************************************************************
*******************************************       Provid By STB    ***********************************************************
********************************************************************************************************************************
********************************************************************************************************************************/
/****************************************************************************
name          		: 	ABV_SAD_Notify_STB_Get_New_Ad
Description  		:	通知机顶盒收到新广告
Parameters    		: 	sample(IN):特征值，由tsid，sid，osid组合成的特征值		
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	收到新广告后，调用此函数，将特征值传给机顶盒，由机顶盒
					判断是否是当前节目的广告。
****************************************************************************/
ABV_Boolean ABV_SAD_Notify_STB_Get_New_Ad(Sad_Serach_Sample*sample);


/****************************************************************************
name          		: 	ABV_PDR_Get_Current_Date
Description  		:	得到当前日期
Parameters    		: 	MJD(IN_OUT):当前日期的MJD 数
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 该接口为中间件平台需要的接口
****************************************************************************/
ABV_Boolean ABV_PDR_Get_Current_Date(ABV_UInt32* MJD);


#ifdef __cplusplus
}
#endif
#endif

