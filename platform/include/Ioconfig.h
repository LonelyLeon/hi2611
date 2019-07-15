#ifndef __Ioconfig_H_
#define __Ioconfig_H_
#ifdef  __cplusplus
extern "C"
{
#endif

#include "stddefs.h"
#include "dIO.h"

/*****该文件下的IO都是可以变得，根据不同的版号可以修改不同的IO
每次把需要的IO添加到里即可*******/


/*******前面板时钟线数据线，根据版本不同可以修改不同的IO*********/
typedef struct
{
	D_GPIO_PortBit   FD650_sda;
	D_GPIO_PortBit   Fd650_scl;

}D_Fd650_data;

//D_Fd650_data  fd650_data= {D_GPIO_PORT6_BIT3,D_GPIO_PORT7_BIT0};
/*****************************************END************************/

/**********DTMB 解调复位线根据不同板子可以选择不同IO**********/
typedef struct
{
    D_GPIO_PortBit   Dem_rest;
}
D_Dem_rest;
//D_Dem_rest dem_rest = {D_GPIO_INVALID};
/***************END***********************/

/********应急广播控***********/
typedef struct
{
    D_GPIO_PortBit   Emergency_broadcast;
}
D_Emer_broad;
/*******************END*********/

/***************高频头LNB使能***********/
typedef struct
{
	D_GPIO_PortBit Lnb_en;
}
D_Lnb_en;
/***************END*********/

/********高频头13v/18V切换*******/

typedef struct
{
	D_GPIO_PortBit  Tuner_power;
}
D_Tuner_power1318;

#ifdef  __cplusplus
}
#endif

#endif
