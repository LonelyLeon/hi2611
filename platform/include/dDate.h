/** @file
* @brief ���ڼ���
* @author ����
* @date 2005-10-25 ����: �����ļ�
* @date 2013-03-19 lc: ͳһƽ̨, ��������
*/

#ifndef _D_DATE_H_
#define _D_DATE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief ����*/
typedef struct {
	D_S16	year;	/**< ��(��1900����)*/
	D_U8	mon;	/**< ��(0Ϊ1��...*/
	D_U16	yday;	/**< һ���еĵڼ���*/
	D_U8	mday;	/**< ÿ�µĵڼ���*/
	D_U8	wday;	/**< ÿ�ܵĵڼ���*/
	D_U8	hour;	/**< Сʱ*/
	D_U8	min;	/**< ����*/
	D_U8	sec;	/**< ��*/
} D_Date;

typedef struct{
	D_U16	year;	/**< ��*/
	D_U8	mon;	/**< ��(1Ϊ1��...*/
	D_U8    day;      /** ��*/
	D_U8	hour;	/**< Сʱ*/
	D_U8	min;	/**< ����*/
	D_U8	sec;	/**< ��*/
}D_Date_Ext;

/** @brief ��ʱ��ת��Ϊ����
* @param[in] time	ʱ��(��1970-1-1��ʼ������)
* @param[out] date ������ڵĻ�����
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result	d_date (D_Time time, D_Date *date) D_FUNCPOSTFIT;

/** @brief ������ת��Ϊʱ��(��1970-1-1��ʼ������)
* @param[in] date ������ڵĻ�����
* @return ʱ��(��1970-1-1��ʼ������)
*/
D_Time d_date_anti (D_Date *date) D_FUNCPOSTFIT;

/** @brief ������ʱ�����Ч��
* @param[in] date ������ڵĻ�����
* @return �Ƿ���Ч
*/
D_Bool d_date_valid (D_Date *date) D_FUNCPOSTFIT;

/** @brief ��ʱ��ת��Ϊ����
* @param[in] time	ʱ��(��1970-1-1��ʼ������)
* @param[out] date_ext ������ڵĻ�����
* @return �ɹ�����D_OK,ʧ�ܷ���D_ERR
*/
D_Result d_date_ext (D_Time time, D_Date_Ext *date_ext) D_FUNCPOSTFIT;

/** @brief ������ת��Ϊʱ��(��1970-1-1��ʼ������)
* @param[in] date_ext ������ڵĻ�����
* @return ʱ��(��1970-1-1��ʼ������)
*/
D_Time d_date_anti_ext (D_Date_Ext*date_ext) D_FUNCPOSTFIT;

/** @brief ������ʱ�����Ч��
* @param[in] date_ext ������ڵĻ�����
* @return �Ƿ���Ч
*/
D_Bool d_date_valid_ext (D_Date_Ext*date_ext) D_FUNCPOSTFIT;

/** @brief �Ƚ����ڵ��Ⱥ�
*@param [in] date1 ����
*@param [in] date2 ����
* @return date1>date2 ����1,date1<date2 ����1,date1==date2 ����0
*/
D_U8 d_compare_date(D_Date_Ext date1, D_Date_Ext date2) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif
