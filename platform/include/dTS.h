/** @file
* @brief TS packet格式
* @author 龚克
* @date 2005-6-6 龚克: 建立文件
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
	SYNC_MODE_BY_SOFTWARE=0,//选择软件同步，由软件同步0X47
	SYNC_MODE_BY_HARDWARE=1,//选择硬件方式，由解调给出同步头做为指示
	SYNC_MODE_BY_HARDWARE_AND_SOFTWARE=2,//选择软硬件方式，由解调给出同步头做为指示，并且软件检测该数据是否是0X47
}TS_SYNC_MODE;

typedef enum
{
	TS0_SELECT_DEMO_INNER=0,//选择HI3209片内解调HI3205
	TS0_SELECT_DEMO_OUTSIDE=1,//选择HI3209片外解调
	TS1_SELECT_DEMO_OUTSIDE=2,//选择HI3209片外解调
}TS_SELECT_CONSTANT;

typedef enum
{
	Ts0_parallel =0,//设置TS并行，正常时序D0~D7//片外解调时，受封装影响不能选择并行
	TS0_Serial=1,//设置TS串行
	Ts0_parallel_INVALID =2,//片外解调受封装影响，不能选择并行。
}TS0_DATA_MODE;

//主芯片时钟上升沿采数据，不能修改，只能由解调自行配置。
typedef struct
{
	TS_SELECT_CONSTANT demo_sel;		//选择DEMO芯片来源
	TS0_DATA_MODE datamode;		//demo芯片TS流的数据格式
	TS_SYNC_MODE ts_sync_mode;  //该TS流同步0X47包头的方式
}TS0_CONFIG;

#if 0
typedef enum
{
	TS1_SELECT_DEMO_hi3209_INVALID=0,//错误选择，不能选择片内解调
	TS1_SELECT_DEMO_OUTSIDE=1,//选择HI3209片外解调
}TS1_SELECT_CONSTANT;
#endif

typedef enum
{
	Ts1_parallel_INVALID =0,//受封装影响，不能选择并行。
	TS1_Serial=1,//设置TS串行
}TS1_DATA_MODE;

//主芯片时钟上升沿采数据，不能修改，只能由解调自行配置。
typedef struct
{
	TS_SELECT_CONSTANT demo_sel;		//选择DEMO芯片来源
	TS1_DATA_MODE datamode;		//demo芯片TS流的数据格式
	TS_SYNC_MODE ts_sync_mode;  //该TS流同步0X47包头的方式
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
