/*****************************************************************************
File Name     	: abv_sad_interface.h

Description   	: ҵ���湦�ܽӿں���ͷ�ļ�

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
Description  		:	������ֵ�õ�ͼƬ
Parameters    		: 	sample(IN):����ֵ����tsid��sid��osid��ϳɵ�����ֵ
					pic(IN_OU):���øú���ǰ���ɵ����߷���һ���㹻��ÿռ�(����20K)
					picΪ�ÿռ���׵�ַ��
					pic_length(IN_OUT):ͼƬ�ĳ���
					text:�ı���Ϣ
					text_length:�ı���Ϣ�ĳ���
					
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 ���øú���ǰ��������Ҫ�ϳ�sample������������һ���㹻��ÿռ�
					�����洢ͼƬ��
****************************************************************************/
ABV_Boolean ABV_SAD_Get_Ad_By_Sample(Sad_Serach_Sample*sample, ABV_UInt8* pic, ABV_UInt32* pic_length,ABV_UInt8* text, ABV_UInt16* text_length);
/****************************************************************************
name          		: 	ABV_SAD_Get_Ad_By_Sample
Description  		:	������ֵ�õ�ͼƬ
Parameters    		: 	sample(IN):����ֵ����tsid��sid��osid��ϳɵ�����ֵ
					pic(IN_OU):���øú���ǰ���ɵ����߷���һ���㹻��ÿռ�(����20K)
					picΪ�ÿռ���׵�ַ��
					pic_length(IN_OUT):ͼƬ�ĳ���
					text:�ı���Ϣ
					text_length:�ı���Ϣ�ĳ���
					
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 ���øú���ǰ��������Ҫ�ϳ�sample������������һ���㹻��ÿռ�
					�����洢ͼƬ��
****************************************************************************/
ABV_Boolean ABV_SAD_Get_Ad_By_Sample(Sad_Serach_Sample*sample, ABV_UInt8* pic, ABV_UInt32* pic_length,ABV_UInt8* text, ABV_UInt16* text_length);

/*******************************************************************************************************************************
********************************************************************************************************************************
*******************************************       Provid By STB    ***********************************************************
********************************************************************************************************************************
********************************************************************************************************************************/
/****************************************************************************
name          		: 	ABV_SAD_Notify_STB_Get_New_Ad
Description  		:	֪ͨ�������յ��¹��
Parameters    		: 	sample(IN):����ֵ����tsid��sid��osid��ϳɵ�����ֵ		
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	�յ��¹��󣬵��ô˺�����������ֵ���������У��ɻ�����
					�ж��Ƿ��ǵ�ǰ��Ŀ�Ĺ�档
****************************************************************************/
ABV_Boolean ABV_SAD_Notify_STB_Get_New_Ad(Sad_Serach_Sample*sample);


/****************************************************************************
name          		: 	ABV_PDR_Get_Current_Date
Description  		:	�õ���ǰ����
Parameters    		: 	MJD(IN_OUT):��ǰ���ڵ�MJD ��
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 �ýӿ�Ϊ�м��ƽ̨��Ҫ�Ľӿ�
****************************************************************************/
ABV_Boolean ABV_PDR_Get_Current_Date(ABV_UInt32* MJD);


#ifdef __cplusplus
}
#endif
#endif

