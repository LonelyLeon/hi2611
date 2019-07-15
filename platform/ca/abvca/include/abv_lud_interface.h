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
Description  		:	�õ�radioͼƬ������
Parameters    		: 	num (IN_OUT):ͼƬ����
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 
****************************************************************************/
ABV_Boolean ABV_LUD_Get_Total_Radio_Pic_Num(ABV_UInt16* num) ;

/****************************************************************************
name          		: 	ABV_LUD_Get_Pic_By_Index
Description  		:	����ŵõ�ͼƬ����
Parameters    		: 	index (IN):ͼƬ���. 
					pic(IN_OUT):ͼƬ����buffer���׵�ַ�����������
					�ⲿ��Ҫ��ǰ����һ���㹻��ÿռ䣬���洢ͼƬ����(����150K)
					pic_length(IN_OUT):ͼƬ���ݵĳ���
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 
****************************************************************************/
ABV_Boolean ABV_LUD_Get_Pic_By_Index(ABV_UInt16 index, ABV_UInt8*pic, ABV_UInt32* pic_length);


/****************************************************************************
name          		: 	ABV_LUD_Get_New_Logo
Description  		:	��ȡ�µ�logoͼƬ����
Parameters    		: 	logo_length(IN_OUT):logoͼƬ���ݵĳ���
					logo(IN_OUT):logoͼƬ�����ݵ��׵�ַ
					logo_ver(IN_OUT):logo �İ汾
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 �յ��µĿ���logo������е��ô˽ӿڣ�����logoΪ����ָ�룬���봫���͡�
					LUD_LIB��logo��ַ��ֵ��ָ��logo��
****************************************************************************/

ABV_Boolean ABV_LUD_Get_New_Logo(ABV_UInt32* logo_length, ABV_UInt8**logo,ABV_UInt8* logo_ver);

/****************************************************************************
name          		: 	ABV_LUD_Update_Logo_Finished
Description  		:	����logo�������ͷ�logoռ�õĿռ䡣
Parameters    		: 	Void
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	STB������logo����ô˽ӿڣ�֪ͨLUD����½�����
****************************************************************************/

ABV_Boolean ABV_LUD_Update_Logo_Finished(void);



/****************************************************************************
name          		: 	ABV_LUD_Notify_To_Get_Date
Description  		:	֪ͨLUD����copy����
Parameters    		: 	Void
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	STB�յ�����Ҫ������ʱ�����ô˽ӿ�֪ͨ�⡣
****************************************************************************/

ABV_Boolean ABV_LUD_Notify_To_Get_Date(void);

/*******************************************************************************************************************************
********************************************************************************************************************************
********************************************       Provid By STB      *********************************************************
********************************************************************************************************************************
********************************************************************************************************************************/


/****************************************************************************
name          		: 	ABV_LUD_Notify_STB
Description  		:	֪ͨ�������յ��µĿ���logo
Parameters    		: 	logo_length(IN):���ݳ���
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 LUD_LIB�յ��µĿ���logo����ô˽ӿڣ�֪ͨ�����С�
****************************************************************************/

ABV_Boolean ABV_LUD_Notify_STB_Get_New_Logo(void);


/****************************************************************************
name          		: 	ABV_LUD_Get_Current_Date
Description  		:	�õ���ǰ����
Parameters    		: 	MJD(IN_OUT):��ǰ���ڵ�MJD ��
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 �ýӿ�Ϊ�м��ƽ̨��Ҫ�Ľӿ�
****************************************************************************/
ABV_Boolean ABV_PDR_Get_Current_Date(ABV_UInt32* MJD);

/****************************************************************************
name          		: 	ABV_LUD_Get_Logo_Version
Description  		:	�õ���ǰlogo�ð汾
Parameters    		: 	logo_ver(IN_OUT): ��ǰlogo�ð汾
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:	 
****************************************************************************/
ABV_Boolean ABV_LUD_Get_Logo_Version(ABV_UInt32* logo_ver);

/****************************************************************************
name          		: 	ABV_LUD_Notify_Get_New_Pic
Description  		:	֪ͨ�������յ��µ�ͼƬ
Parameters    		: 	Void
Return Value  		: 	success: ABV_FALSE  failed:ABV_TRUE
NOTES			:
****************************************************************************/

ABV_Boolean ABV_LUD_Notify_Get_New_Pic(ABV_UInt16 total_pic_num);
#ifdef __cplusplus
}
#endif
#endif	
