/*************************************************************************************************

File Name      :  hrca_flash.h

Description    :  External dmux definitions for ca module

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hourn

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-01-12     hourn          created              ---

**************************************************************************************************/
#ifndef _HRCA_FLASH_H_
#define _HRCA_FLASH_H_

#include <stdint.h>
#include "dNVPart_def.h"
#include "hrca_config.h"

#define CA_RAM_TO_SDRAM    1
#define CA_SDRAM_TO_RAM    2

#define _M_FLASH_HEAD_SIZE			0x0010
#define S_HEAD_SIZE					0x00010 //  4B + 12B = ( 4 + 12 ) = 16 
#define CAEMAIL_SIZE               (0x10000-0x00010)
#define CAFLASH_DATA_SIZE          0x10000

#define CA_FLASH_ADDR_BLOCK1		CA_FLASH_BAK1_ADDR //分给CA使用的3块64K flash 地址
#define CA_FLASH_ADDR_BLOCK2		CA_FLASH_BAK2_ADDR 
#define CA_FLASH_ADDR_BLOCK3		CA_FLASH_BAK3_ADDR 


#define CAFLASH_MAIN_BLOCK        1     /* BLOCK A *///用掉两个64Kflash,具有交替备份功能
#define CAFLASH_BAK_BLOCK        2     /* BLOCK B *///只有一个64K，写flash时不具备备份功能
#define CAFLASH_COS_BLOCK         3     /* BLOCK C *///只有一个64K，cos数据超过32K或者需要3块FLASH时，数据存于此块
#define CAFLASH_MAIL_BLOCK        8     /* BLOCK Mail *///只有一个64K，用于备份使用
#define CAFLASH_MAINEXT_BLOCK     9     
#define CAFLASH_MAIN_AND_MAINEXT_BLOCK    10 /*写128K的数据(跨64K)*/

typedef struct
{
	uint8_t 	sDataMainBlock;
	uint8_t 	sDataBakBlock;
	uint8_t 	sDateCunter0; //为了减少hrca_dataHeadInfo_t的大小, 将U32的sDateCunter分成4个U8类型的数据进行存放
	uint8_t 	sDateCunter1;
	uint8_t 	sDateCunter2;
	uint8_t 	sDateCunter3;
	uint16_t	crc_16;
}hrca_dataHeadInfo_t;

typedef enum
{
    FLASH_TO_SDRAM,
    SDRAM_TO_FLASH
} FS_DataDirection_t;

#ifndef	FLASH_SdramMalloc
	#define	FLASH_SdramMalloc(x)	d_mem_alloc(0, (x))
#endif

#ifndef	FLASH_SdramFree
	#define	FLASH_SdramFree(x)		d_mem_free((x))
#endif

extern D_HNVPart hnv_ca1;
extern D_HNVPart hnv_ca2;
extern D_HNVPart hnv_ca3;
extern D_HNVPart hnv_cabak;//用来实现1备3功能
extern D_HNVPart hnv_ca4;
extern D_HNVPart hnv_ca5;

extern uint32_t	MainSdramHandle;
extern uint32_t    BlockSdramHandle;
extern uint32_t	COSSdramHandle;

extern CA_BOOL  bFlashBak;

/********************************flash api**********************************************/

extern void HRCA_FlashBak(uint8_t u8BlockID, uint32_t SdramHandle, const uint8_t *data, uint32_t u32Size);
extern CA_BOOL HRCA_FlashInit(uint8_t u8BlockID, uint32_t* u32StartAddr, uint32_t* u32Size);
extern CA_BOOL HRCA_ReadDataBuffer(uint8_t u8BlockID, uint8_t* pu8Data, uint32_t* u32StartAddr, uint32_t u32Len);
extern CA_BOOL HRCA_WriteDataBuffer(uint8_t u8BlockID, const uint8_t* pu8Data, uint32_t* u32StartAddr, uint32_t u32Len);
extern uint8_t HRCA_FlashWrite(D_HNVPart hnvp, uint32_t addr, const uint8_t * src, uint32_t size, uint8_t wtail);
extern uint8_t HRCA_FlashWriteEx(D_HNVPart hnvp, uint32_t addr, const uint8_t * src, uint32_t size, uint8_t wtail);
extern uint8_t HRCA_FlashRead(D_HNVPart hnvp, uint32_t addr, uint8_t * src, uint32_t size );
extern void HRCA_FlashEraseBlock( int32_t sec_addr );
extern uint8_t HRCA_FlashIsAvailable (D_HNVPart hnvp) ;
extern void HRCA_XDataToSdram( uint32_t sdAddr, uint32_t byteNum, uint8_t *dataP );
extern void HRCA_FlashToXData( uint32_t fAddr, uint32_t byteNum, uint8_t * dataP );
extern uint8_t HRCA_DMA_Move(uint8_t dir, uint32_t SDRAM_Offset, uint32_t XDATA_Offset, uint32_t size);
extern void HRCA_CRC32Calculate(uint8_t *buffer, uint32_t size, uint32_t *CRC32);
extern void HRCA_GetSerial(uint8_t * buffer, uint8_t length);
extern void HRCA_GetPrivateData(uint8_t * buffer, uint8_t length);
extern void HRCA_SetPrivateData(uint8_t * buffer, uint8_t length);
extern void HRCA_GetCPUID(uint8_t *pbyCPUID, uint8_t *pLen);
extern void HRCA_GetSpecialSerial(uint8_t * buffer, uint8_t length);
#endif


