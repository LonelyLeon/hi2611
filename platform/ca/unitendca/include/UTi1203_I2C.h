#ifndef _UTI1203_I2C_H_
#define _UTI1203_I2C_H_
/***********************************************************************
	Copyright(C), 2005-2011, Unitend Technologies Inc.
	FileName:	    UTi1203_I2C.h
	Author:			ym.li
	Description:	I2C protocol interface for UTi1203
	Version:		0.1
	Buid Date:			2011-01-20
	Modify Date:		2011-10-21
***********************************************************************/

/****************************
	include
****************************/
//#include<linux/module.h>
//#include<linux/kernel.h>

//#include "i2c.h"
#include "unitend.h"

/****************************
	define
****************************/
/*
UTi1203_I2C_ADDR:
	When asel is 0, I2C slave Address is 7bits 0x22(8bits 0x44). 
	When asel is 1, I2C slave Address is 7bits 0x23(8bits 0x46).
*/
#define UTi1203_I2C_ADDR						(0x44)//(0x46)
#define UTi1203_I2C_OPERATE_WIDTH_BITS8			(0x0F)
#define UTi1203_I2C_OPERATE_WIDTH_BITS16		(0x4F)

/*******************************************
API called by UDRM drivers
UDRM drivers please reference 《UTI移植UDRM驱动硬件接口.pdf》
*******************************************/
//write UTi1203
extern UTI_SINT32 UTi1203_I2CWrite8(UTI_UINT16 RegAddr, UTI_UINT8 RegData);

extern UTI_SINT32 UTi1203_I2CWrite16(UTI_UINT16 RegAddr, UTI_UINT16 RegData);

extern UTI_SINT32 UTi1203_I2CWrite32(UTI_UINT16 RegAddr, UTI_UINT32 RegData);

extern UTI_SINT32 UTi1203_I2CWriteFIFO(UTI_UINT16 RegAddr, UTI_UINT8 *pBuffer, UTI_INT Length);

//read UTi1203
extern UTI_SINT32 UTi1203_I2CRead8(UTI_UINT16 RegAddr, UTI_UINT8 *pBuffer);

extern UTI_SINT32 UTi1203_I2CRead16(UTI_UINT16 RegAddr, UTI_UINT16 *pBuffer);

extern UTI_SINT32 UTi1203_I2CRead32(UTI_UINT16 RegAddr, UTI_UINT32 *pBuffer);

extern UTI_SINT32 UTi1203_I2CReadFIFO(UTI_UINT16 RegAddr, UTI_UINT8 *pBuffer, UTI_INT Length);

/********************************************
platform interface porting by developers
********************************************/
//Send start signal to I2C
extern UTI_VOID UTI_I2cStart(/*UTI_VOID*/void);

/**********************************************
UTI_I2cWriteOneByte:
	Send one byte to I2C
Parameter:
	bData: data that send to I2C bus
***********************************************/
extern UTI_VOID UTI_I2cWriteOneByte(UTI_BYTE bData);

/**********************************************
UTI_I2cReadOneByte:
	Receive one byte from I2C
Parameter:
	pbData: the storage address of data which read
		from I2C bus
***********************************************/
extern UTI_VOID UTI_I2cReadOneByte(UTI_BYTE *pbData);

/**********************************************
UTI_I2cCheckACK:
	Check ACK from I2C. 
return :
	UTI_ERROR_OK is ACK, 
	UTI_ERROR_DEVICE_NOT_PRESENT is NACK.
***********************************************/
extern UTI_RESULT UTI_I2cCheckACK(/*UTI_VOID*/void);

/**********************************************
UTI_I2cSendACK:
	Send ACK to I2C. 
***********************************************/
extern UTI_VOID UTI_I2cSendACK(/*UTI_VOID*/void);

/**********************************************
UTI_I2cSendNACK:
	Send NACK to I2C. 
***********************************************/
extern UTI_VOID UTI_I2cSendNACK(/*UTI_VOID*/void);

/**********************************************
UTI_I2cStop:
	Send stop to I2C. 
***********************************************/
extern UTI_VOID UTI_I2cStop(/*UTI_VOID*/void);
extern void I2CTest(void);

#endif


