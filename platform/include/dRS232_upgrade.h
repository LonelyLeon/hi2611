
#ifndef _D_RS232_UPGRADE_H_
#define _D_RS232_UPGRADE_H_

#include "dTypes.h"
#include "dSerial.h"

//----------------------------------------------------------------
//��������״̬ -- ��������״̬
//----------------------------------------------------------------
//----------------------------------------------------------------
#define	RECCANCEL		1
#define	RECFAIL			2
//----------------------------------------------------------------
#define	SENDOK			4
#define	SENDCANCEL		5
#define	SENDFAIL		6
//----------------------------------------------------------------
#define SEND_OK			SENDOK
#define SEND_CANCEL		SENDCANCEL
#define SEND_FAIL		SENDFAIL

#define RET_OK				0x3C
#define RET_FAIL			0x3D
#define VAVILIDATE			0xFF

#define READID				0x40
#define SETBAUD				0x41
#define SECTORERASE			0x42
#define PROGRAM				0x43
#define READDATA			0x44
#define CHIPERASE			0x45

#define UART_WAIT_TIMEOUT	0xFFFFFFFF
#define UART_WAIT_OBJECT_0	0x00000000


#define TAG_SIZE			1
#define CMD_SIZE			1
#define ASS_SIZE			4
#define END_SIZE			1

#define LEN_SIZE_4K			2
#define CRC_SIZE_4K			4
#define DAT_SIZE_4K			0x1000 

#define VALID_TAG			0x66
#define MAX_VALID_END		101
#define TMIN_PACK_SIZE		( TAG_SIZE + LEN_SIZE_4K + CRC_SIZE_4K + CMD_SIZE + ASS_SIZE + END_SIZE ) //�����ڴ棬�����4K�֣��ʲ�֧�ִ���4K�ķ�ʽ
#define TMAX_PACK_SIZE		( TMIN_PACK_SIZE + DAT_SIZE_4K )



typedef D_Size (*RS232UPGRADEFLASHERASE)(D_Handle handle, D_Size offset, D_Size size);
typedef D_Size (*RS232UPGRADEFLASHWRITE)(D_Handle handle, D_Size offset,D_U8 *buff, D_Size size);

typedef struct
{
	D_HSerial hs; 
	D_SerialMode boot1sm;
	D_SerialMode boot2sm;
	
	D_U32 	start_addr; 
	D_U32 	size; 
	
	const char* BurnSign;
	D_U8 		BurnSignlength;
	const char* Boot2Code;
	D_U8 	Boot2Length; 

	D_U8* 	serial_buf;
	D_U8* 	sysup_dat;//�洢���͵����ݣ�һ����෢��140���ֽ�
	D_U32	datalength;
	
	D_U32	wait_time_0;//			0x1000000	//5000ms
	D_U32	wait_time_1;//			0x0800000//2500ms
	D_U32	wait_time_2;//			0x0500000	//23ms*5
	D_U32 	block_size;//				0x10000
	D_U32 	small_block_size;//		0x1000	
	D_U32	cfg_flash_base;// CFG_FLASH_BASE;
	D_U32	flash_size;//FLASH_SIZE;	
	D_U32	tail_block_addr;//TAIL_BLOCK_ADDR;

	D_U32	cmd_len_size;
	D_U32	cmd_crc_size	;
	D_U32	cmd_dat_size	;
	D_U32	cmd_exclude_size;

}D_RS232_Upgrade_Data;

/** @brief Uart������붨��				
*/

typedef enum
{
	RS232_NO_ERROR = 0,	
	RS232_SETSERIALMODE_ERROR,  //�������ô���
	RS232_BUFFLENGTH_ERROR,  //�ڴ����
	RS232_READ_ERROR,  //��ȡ���ݴ���
	RS232_ERASE_ERROR,  //��ȡ���ݴ���
	RS232_WRITE_ERROR,  //��ȡ���ݴ���
	RS232_DATA_CRC_ERROR,//����У�����
	RS232_UNKNOW_ERROR,  //��������	
	
}D_RS232ResultCode;


typedef void (*RS232UPGRADEEVENTCALLBACK)(D_U8 event,D_U8 param);


/** @brief ���ûص�����
* @param parm	cb �ص�����
*/
void D_RS232SetEventCB(RS232UPGRADEEVENTCALLBACK cb);
void D_RS232SetKill(void);

/** @brief rs232��������
*@param[in] config �������ò���
*/
D_RS232ResultCode start_rs232_upgrade(D_RS232_Upgrade_Data config)D_FUNCPOSTFIT ;

#endif
