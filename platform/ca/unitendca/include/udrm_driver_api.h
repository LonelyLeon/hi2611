#ifndef _UDRM_DRIVER_API_H_
#define _UDRM_DRIVER_API_H_

#include "unitend.h"

UTI_SINT32 UTIDriverInit(void);

UTI_SINT32 UTIDriverReceiveDataFromApp(UTI_UINT8 *data, UTI_UINT32 len);

UTI_SINT32 UTIDriverReadRegU8(UTI_UINT32 address, UTI_UINT8 *value);

UTI_SINT32 UTIDriverWriteRegU8(UTI_UINT32 address, UTI_UINT8 value);

UTI_SINT32 UTIDriverReadRegU16(UTI_UINT32 address, UTI_UINT16 *value);

UTI_SINT32 UTIDriverWriteRegU16(UTI_UINT32 address, UTI_UINT16 value);

UTI_SINT32 UTIDriverReadRegU32(UTI_UINT32 address, UTI_UINT32 *value);

UTI_SINT32 UTIDriverWriteRegU32(UTI_UINT32 address, UTI_UINT32 value);

UTI_SINT32  UTIDriverReadRegBuffer(UTI_UINT32  address,  UTI_UINT8  *u8_data,  UTI_UINT32 buffer_len);

UTI_SINT32  UTIDriverWriteRegBuffer(UTI_UINT32  address,  UTI_UINT8  *u8_data,  UTI_UINT32 buffer_len);

#endif
