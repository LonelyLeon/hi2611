/*************************************************************************************************

File Name      :  hrca_dmux.h

Description    :  External dmux definitions for ca module

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hanjf

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012.1.13  	hanjf           created             ---

**************************************************************************************************/
#ifndef _HRCA_DMUX_H_
#define _HRCA_DMUX_H_


#define CADMUX_INVALID_CHANNEL_ID      0xffff
#define CADMUX_INVALID_FILTER_ID       0xffff
#define CADMUX_INVALID_DESCRAMBLER_ID  0xffff 

#define CADMUX_BUF_SIZE  (32*1024)  //CA DEMUX(ECM, EMM表)环形buffer的大小

typedef enum
{
    CA_DSC_OK,			        // operation success 
    CA_DSC_ERROR,               // operation fail 
    CA_DSC_ERROR_UNKNOWN_ID,	// the key with these id donn't open 
    CA_DSC_ERROR_BAD_PID	    // invalid PID 
} hrca_desc_status_t;

typedef enum
{
    CA_DESCRAMBLE_TS,		   // TS lay scrambler 
    CA_DESCRAMBLE_PES,		   // PES lay scrambler 
    CA_DESCRAMBLE_OFF, 	
    CA_DESCRAMBLE_RESERVE 
} hrca_descramble_type_t;

typedef enum
{
    EVEN_CW,		           // TS lay scrambler 
    ODD_CW,		               // PES lay scrambler 
    EVEN_ODD_CW 	
} hrca_CW_flag_t;

typedef struct CaDscChan
{
    uint8_t	 SlotAlloc;
    uint8_t	 AVFlag;          //0--video;1--audio;2--all	
} hrca_deschan_t;


extern int32_t ECMSecSlot[2];
extern int32_t EMMSecSlot;

extern uint16_t ECMPID[2];
extern uint16_t EMMPID;
extern uint16_t EMMPIDBak; //备份EMMPID

extern uint8_t CatBuf[DATA_TEMP_BUF];
extern uint8_t PmtBuf[DATA_TEMP_BUF];
extern uint8_t NitBuf[DATA_TEMP_BUF];

extern DemuxFor_CA hDmuxForCASelf[DMUX_FORCALIB_CNT];
extern D_CADev  ca_dev;//CA 任务使用的消息队列及demux句柄
extern uint16_t EmmDmuxAndReqId[EMM_USED_FILTER_CNT];

/********************************dmux api**********************************************/

extern uint8_t ReqNitCaSelf(void);
extern CA_BOOL HRCA_DMUXInit(void);
extern uint16_t HRCA_DMUXRequestSectionChannel(uint8_t u8Receive, uint8_t u8CRC);
extern CA_BOOL HRCA_DMUXCloseSectionChannel(uint16_t u16ChannelID);
extern CA_BOOL HRCA_DMUXSetChannelPID(uint16_t u16ChannelID, uint16_t u16PID);
extern uint16_t HRCA_DMUXAllocateFilter(uint16_t u16ChannelID);
extern uint16_t HRCA_DMUXSetFilter( uint16_t u16ChannelID, uint8_t  u8FilterID, uint8_t  *pu8Data, uint8_t  *pu8Mask,uint8_t  u8MaskLength );
extern CA_BOOL HRCA_DMUXCloseFilter(uint16_t u16ChannelID, uint8_t  u8FilterID);
extern CA_BOOL HRCA_DMUXControlChannelState(uint16_t u16ChannelID, uint8_t u8WorkStatus);
extern uint16_t HRCA_SectionRequest(uint16_t ReqPid, uint8_t bCont, uint8_t bCRC, uint8_t *filterdata, uint8_t *filtermask, uint8_t filterlenth, uint16_t *filterid);
extern CA_BOOL HRCA_DMUXDataReady(int32_t u8Slot, uint8_t *pu8Data, uint16_t u16Len);
extern void HRCA_DMUXRegisterChannelCallback(uint16_t u16ChannelID, void (*upfct)(uint16_t u16ChannelID));
extern CA_BOOL HRCA_DMUXGetChannelData(uint16_t u16ChannelID,uint8_t * pu8Data,uint16_t u16Size);
extern uint8_t ReqEmm(uint8_t byReqID, uint16_t emmpid, uint8_t* filter, uint8_t* mask, uint8_t fmlenth, uint8_t timeout);
extern uint8_t ReqEcmAudio(uint16_t ecmpid, uint8_t* filter, uint8_t* mask, uint8_t fmlenth, uint8_t timeout);
extern uint8_t ReqEcmVideo(uint16_t ecmpid, uint8_t* filter, uint8_t* mask, uint8_t fmlenth, uint8_t timeout);
extern uint8_t ReqNitCaSelf(void);

/********************************desc api**********************************************/

extern void HRCA_DESCInit(void);
extern uint16_t HRCA_DESCOpen(uint8_t *pu8DescramblerID);
extern hrca_desc_status_t HRCA_DESCClose(uint8_t u8DescramblerID);
extern hrca_desc_status_t HRCA_DESCSetPid(uint8_t u8DescramblerID, uint16_t u16StreamPid);
extern void HRCA_DESCSetEvenCWKey(uint8_t u8DescramblerID, uint16_t u16StreamPid, uint8_t *pu8CWKey, uint8_t u8Length, uint8_t bycwe);
extern void HRCA_DESCSetOddCWKey(uint8_t u8DescramblerID, uint16_t u16StreamPid, uint8_t *pu8CWKey, uint8_t u8Length, uint8_t bycwe);
extern void HRCA_SetCWKey(uint8_t *CWKey, uint8_t Length, uint8_t OddOrEven,uint8_t AV_FLAG, uint8_t bycwe); 
extern void HRCA_Set_HecDecryption(uint8_t type, uint8_t rtkeyctrl, uint8_t *endata);
extern void HRCA_Set_HecDecryption2(uint8_t type, uint8_t rtkeyctrl, uint8_t *endata);
extern void HRCA_Get_ChipID(uint8_t *len, uint8_t *chipid);
extern void HRCA_Get_ChipID_16Bytes(uint8_t *len, uint8_t *chipid);
extern void HRCA_Get_CardNO(uint8_t *len, uint8_t *cardno);
#endif

