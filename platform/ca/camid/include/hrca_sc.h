/*************************************************************************************************

File Name      :  hrca_sc.h

Description    :  External dmux definitions for ca module

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hourn

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-01-12     hourn          created              ---

**************************************************************************************************/
#ifndef _HRCA_SC_H_
#define _HRCA_SC_H_

#include <stdint.h>
#include "hrca_config.h"
#include "dSCI.h"

extern uint8_t ATRflag; //CA_TRUE: ATR ok; CA_FALSE: ATR fail

/********************************sc api**********************************************/

extern CA_BOOL HRCA_SCReset(uint8_t* u8ATR, uint8_t* u8Len);
extern CA_BOOL HRCA_SCDeactivate(void);
extern CA_BOOL HRCA_SCGetATR(uint8_t* u8ATR, uint8_t* u8Len);
extern CA_BOOL HRCA_SCGetHistory(uint8_t* u8History, uint8_t* u8Len);
extern uint8_t HRCA_SCRead(uint8_t* u8Buffer, uint16_t u16NumberToRead, uint16_t* u16NumberReaded, uint16_t u16Timeout);
extern uint8_t HRCA_SCWrite(uint8_t* u8Buffer, uint16_t u16NumberToWrite, uint16_t* u16NumberWrited, uint16_t u16Timeout);

extern uint8_t HRCA_SCInit(void);
extern uint8_t HRCA_SCClose(void);
extern CA_BOOL HRCA_SCTest(void);
extern CA_BOOL HRCA_SCATRState(void);
extern CA_BOOL HRCA_SCSetParam(D_SCIParam* param);

#endif

