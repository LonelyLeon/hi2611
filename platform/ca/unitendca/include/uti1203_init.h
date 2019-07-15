#ifndef _UTI1203_INIT_H_
#define _UTI1203_INIT_H_

typedef struct _UDRM_UTI1203_TS_CONFIG_st
{
	/* 
		u16TSI_Mode,
			function : TS input mode.  
			value : 0, parallel; 1, serial;
	*/
	UTI_UINT16			u16TSI_Mode;
	/* 
		u16TSI_SampleEdge,
			function : TS input sample data edge.
			value : 0, rising edge to sample data;
					1, falling edge to sample data
	*/
	UTI_UINT16			u16TSI_SampleEdge;
	/* 
		u16TSI_BitOrder,
			function : TS serial input bit order. 
			value : 0, MSB; 1, LSB. This is variable useful just when "u8TSI_Mode" is 1.
	*/
	UTI_UINT16			u16TSI_BitOrder;

	/* 
		u32TSO_Mode,
			function : TS output mode.
			value : 0, parallel; 1, serial
	*/
	UTI_UINT32			u32TSO_Mode;
	
	/* 
		u32TSO_BitSwap,
			function : TS output mode.
			value : 0, parallel mode, data[7:0]; serial mode, MSB;
					1, parallel mode, data[0:7]; serial mode, LSB. 
	*/
	UTI_UINT32			u32TSO_BitSwap;
	
	/* 
		u16TSO_ChangeEdge,
			function : TS output change data edge (Device sample data at opposite,
					If UTi1203 change data at falling edge, then device sample data at rising edge):  
			value : 0, falling edge to change data;
					1, rising edge to change data
	*/
	UTI_UINT16			u16TSO_ChangeEdge;
	

}UDRM_UTI1203_TS_CONFIG_st;

extern UTI_RESULT UTi1203_Init(UDRM_UTI1203_TS_CONFIG_st stUTi1203TSConfig);


#endif
