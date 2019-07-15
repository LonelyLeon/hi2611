/** @file
* @brief TS packet��ʽ
* @author ����
* @date 2005-6-6 ����: �����ļ�
*/

#ifndef _D_TS_H_
#define _D_TS_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"


typedef enum
{
	SYNC_MODE_BY_SOFTWARE=0,//ѡ�����ͬ���������ͬ��0X47
	SYNC_MODE_BY_HARDWARE=1,//ѡ��Ӳ����ʽ���ɽ������ͬ��ͷ��Ϊָʾ
	SYNC_MODE_BY_HARDWARE_AND_SOFTWARE=2,//ѡ����Ӳ����ʽ���ɽ������ͬ��ͷ��Ϊָʾ������������������Ƿ���0X47
}TS_SYNC_MODE;

typedef enum
{
	TS0_SELECT_DEMO_INNER=0,//ѡ��HI3209Ƭ�ڽ��HI3205
	TS0_SELECT_DEMO_OUTSIDE=1,//ѡ��HI3209Ƭ����
	TS1_SELECT_DEMO_OUTSIDE=2,//ѡ��HI3209Ƭ����
}TS_SELECT_CONSTANT;

typedef enum
{
	Ts0_parallel =0,//����TS���У�����ʱ��D0~D7//Ƭ����ʱ���ܷ�װӰ�첻��ѡ����
	TS0_Serial=1,//����TS����
	Ts0_parallel_INVALID =2,//Ƭ�����ܷ�װӰ�죬����ѡ���С�
}TS0_DATA_MODE;

//��оƬʱ�������ز����ݣ������޸ģ�ֻ���ɽ���������á�
typedef struct
{
	TS_SELECT_CONSTANT demo_sel;		//ѡ��DEMOоƬ��Դ
	TS0_DATA_MODE datamode;		//demoоƬTS�������ݸ�ʽ
	TS_SYNC_MODE ts_sync_mode;  //��TS��ͬ��0X47��ͷ�ķ�ʽ
}TS0_CONFIG;

#if 0
typedef enum
{
	TS1_SELECT_DEMO_hi3209_INVALID=0,//����ѡ�񣬲���ѡ��Ƭ�ڽ��
	TS1_SELECT_DEMO_OUTSIDE=1,//ѡ��HI3209Ƭ����
}TS1_SELECT_CONSTANT;
#endif

typedef enum
{
	Ts1_parallel_INVALID =0,//�ܷ�װӰ�죬����ѡ���С�
	TS1_Serial=1,//����TS����
}TS1_DATA_MODE;

//��оƬʱ�������ز����ݣ������޸ģ�ֻ���ɽ���������á�
typedef struct
{
	TS_SELECT_CONSTANT demo_sel;		//ѡ��DEMOоƬ��Դ
	TS1_DATA_MODE datamode;		//demoоƬTS�������ݸ�ʽ
	TS_SYNC_MODE ts_sync_mode;  //��TS��ͬ��0X47��ͷ�ķ�ʽ
}TS1_CONFIG;

#define TS_PACKET_LEN	(4)
#define ADAPTATION_FIELD_LEN	(2)
#define ADAPTION_FIELD_PCR_LEN	(6)
#define ADAPTION_FIELD_OPCR_LEN	(6)
#define ADAPTATION_FIELD_SPLICING_POINT	(1)
#define ADAPTATION_FIELD_DATA_LEN	(1)
#define ADAPTATION_FIELD_EXTENTION_LEN	(2)
#define ADAPTATION_FIELD_EXTENTION_LTW_LEN	(2)
#define ADAPTATION_FIELD_EXTENTION_PIECEWISE_RATE_LEN	(3)
#define ADAPTATION_FIELD_EXTENTION_SEAMLESS_SPLICE_LEN	(5)

#ifdef  __cplusplus
}
#endif

#endif
