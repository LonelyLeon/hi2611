#ifndef __Ioconfig_H_
#define __Ioconfig_H_
#ifdef  __cplusplus
extern "C"
{
#endif

#include "stddefs.h"
#include "dIO.h"

/*****���ļ��µ�IO���ǿ��Ա�ã����ݲ�ͬ�İ�ſ����޸Ĳ�ͬ��IO
ÿ�ΰ���Ҫ��IO��ӵ��Ｔ��*******/


/*******ǰ���ʱ���������ߣ����ݰ汾��ͬ�����޸Ĳ�ͬ��IO*********/
typedef struct
{
	D_GPIO_PortBit   FD650_sda;
	D_GPIO_PortBit   Fd650_scl;

}D_Fd650_data;

//D_Fd650_data  fd650_data= {D_GPIO_PORT6_BIT3,D_GPIO_PORT7_BIT0};
/*****************************************END************************/

/**********DTMB �����λ�߸��ݲ�ͬ���ӿ���ѡ��ͬIO**********/
typedef struct
{
    D_GPIO_PortBit   Dem_rest;
}
D_Dem_rest;
//D_Dem_rest dem_rest = {D_GPIO_INVALID};
/***************END***********************/

/********Ӧ���㲥��***********/
typedef struct
{
    D_GPIO_PortBit   Emergency_broadcast;
}
D_Emer_broad;
/*******************END*********/

/***************��ƵͷLNBʹ��***********/
typedef struct
{
	D_GPIO_PortBit Lnb_en;
}
D_Lnb_en;
/***************END*********/

/********��Ƶͷ13v/18V�л�*******/

typedef struct
{
	D_GPIO_PortBit  Tuner_power;
}
D_Tuner_power1318;

#ifdef  __cplusplus
}
#endif

#endif
