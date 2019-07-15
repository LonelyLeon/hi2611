#ifndef _ca_D_PALLETE_H_
#define _ca_D_PALLETE_H_


#ifdef	__cplusplus
extern "C" {
#endif//__cplusplus

#define	ca_ENUM_START_VALUE	0x2000
enum{
	ca_COLOR_ENUM_0=ca_ENUM_START_VALUE,
	ca_COLOR_ENUM_1,	//=0x0001,
	ca_COLOR_ENUM_2,	//=0x0002,
	ca_COLOR_ENUM_3,	//=0x0003,
	ca_COLOR_ENUM_4,	//=0x0004,
	ca_COLOR_ENUM_5,	//=0x0005,
	ca_COLOR_ENUM_6,	//=0x0006,
	ca_COLOR_ENUM_7,	//=0x0007,
	ca_COLOR_ENUM_8,	//=0x0008,
	ca_COLOR_ENUM_9,	//=0x0009,
	ca_COLOR_ENUM_10,	//=0x000a,
	ca_COLOR_ENUM_11,	//=0x000b,
	ca_COLOR_ENUM_12,	//=0x000c,
	ca_COLOR_ENUM_13,	//=0x000d,
	ca_COLOR_ENUM_14,	//=0x000e,
	ca_COLOR_ENUM_15,	//=0x000f,
	ca_COLOR_ENUM_16,	//=0x0010,
	ca_COLOR_ENUM_17,	//=0x0011,
	ca_COLOR_ENUM_18,	//=0x0012,
	ca_COLOR_ENUM_19,	//=0x0013,
	ca_COLOR_ENUM_20,	//=0x0014,
	ca_COLOR_ENUM_21,	//=0x0015,
	ca_COLOR_ENUM_22,	//=0x0016,
	ca_COLOR_ENUM_23,	//=0x0017,
	ca_COLOR_ENUM_24,	//=0x0018,
	ca_COLOR_ENUM_25,	//=0x0019,
	ca_COLOR_ENUM_26,	//=0x001a,
	ca_COLOR_ENUM_27,	//=0x001b,
	ca_COLOR_ENUM_28,	//=0x001c,
	ca_COLOR_ENUM_29,	//=0x001d,
	ca_COLOR_ENUM_30,	//=0x001e,
	ca_COLOR_ENUM_31,	//=0x001f,
	ca_COLOR_ENUM_32,	//=0x0020,
	ca_COLOR_ENUM_33,	//=0x0021,
};


unsigned long ca_GetColorData( int color_id );

#ifdef	__cplusplus
}
#endif//__cplusplus


#endif
