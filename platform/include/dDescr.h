/** @file
* @brief SI描述符结构定义
* @author 龚克
* @date 2005-6-10 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 代码整理
*/

#ifndef _D_DESCR_H_
#define _D_DESCR_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/* defined by ISO/IEC 13818-1 */
#define DESCR_VIDEO_STREAM                   0x02
#define DESCR_AUDIO_STREAM                   0x03
#define DESCR_HIERARCHY                      0x04
#define DESCR_REGISTRATION                   0x05
#define DESCR_DATA_STREAM_ALIGN              0x06
#define DESCR_TARGET_BACKGRID                0x07
#define DESCR_VIDEO_WINDOW                   0x08
#define DESCR_CA                             0x09
#define DESCR_ISO_639_LANGUAGE               0x0A
#define DESCR_SYSTEM_CLOCK                   0x0B
#define DESCR_MULTIPLEX_BUFFER_UTIL          0x0C
#define DESCR_COPYRIGHT                      0x0D
#define DESCR_MAXIMUM_BITRATE                0x0E
#define DESCR_PRIVATE_DATA_IND               0x0F
#define DESCR_SMOOTHING_BUFFER               0x10
#define DESCR_STD                            0x11
#define DESCR_IBP                            0x12

/* defined by ETSI */
#define DESCR_NW_NAME                        0x40
#define DESCR_SERVICE_LIST                   0x41
#define DESCR_STUFFING                       0x42
#define DESCR_SAT_DEL_SYS                    0x43
#define DESCR_CABLE_DEL_SYS                  0x44
#define DESCR_VBI_DATA                       0x45
#define DESCR_VBI_TELETEXT                   0x46
#define DESCR_BOUQUET_NAME                   0x47
#define DESCR_SERVICE                        0x48
#define DESCR_COUNTRY_AVAIL                  0x49
#define DESCR_LINKAGE                        0x4A
#define DESCR_NVOD_REF                       0x4B
#define DESCR_TIME_SHIFTED_SERVICE           0x4C
#define DESCR_SHORT_EVENT                    0x4D
#define DESCR_EXTENDED_EVENT                 0x4E
#define DESCR_TIME_SHIFTED_EVENT             0x4F
#define DESCR_COMPONENT                      0x50
#define DESCR_MOSAIC                         0x51
#define DESCR_STREAM_ID                      0x52
#define DESCR_CA_IDENT                       0x53
#define DESCR_CONTENT                        0x54
#define DESCR_PARENTAL_RATING                0x55
#define DESCR_TELETEXT                       0x56
#define DESCR_TELEPHONE                      0x57
#define DESCR_LOCAL_TIME_OFF                 0x58
#define DESCR_SUBTITLING                     0x59
#define DESCR_TERR_DEL_SYS                   0x5A
#define DESCR_ML_NW_NAME                     0x5B
#define DESCR_ML_BQ_NAME                     0x5C
#define DESCR_ML_SERVICE_NAME                0x5D
#define DESCR_ML_COMPONENT                   0x5E
#define DESCR_PRIV_DATA_SPEC                 0x5F
#define DESCR_SERVICE_MOVE                   0x60
#define DESCR_SHORT_SMOOTH_BUF               0x61
#define DESCR_FREQUENCY_LIST                 0x62
#define DESCR_PARTIAL_TP_STREAM              0x63
#define DESCR_DATA_BROADCAST                 0x64
#define DESCR_CA_SYSTEM                      0x65
#define DESCR_DATA_BROADCAST_ID              0x66
#define DESCR_TRANSPORT_STREAM               0x67
#define DESCR_DSNG                           0x68
#define DESCR_PDC                            0x69
#define DESCR_AC3                            0x6A
#define DESCR_ANCILLARY_DATA                 0x6B
#define DESCR_CELL_LIST                      0x6C
#define DESCR_CELL_FREQ_LINK                 0x6D
#define DESCR_ANNOUNCEMENT_SUPPORT           0x6E

#define DESCR_EAC3                           0x7A
#define DESCR_DTS                            0x7B
#define DESCR_AAC                            0x7C


#define HILO(_a)	((((D_U16)_a##_hi)<<8) | ((D_U16)_a##_lo))
#define BCD_VAL(x)	((((x) & 0xf0) >> 4)*10+((x)&0x0f))
#define MjdToEpochTime(x) (((((D_U32)x##_hi) << 8 | ((D_U32)x##_lo))-40587)*86400)
#define BcdTimeToSeconds(x) ((3600 * ((10*((x##_h & 0xF0)>>4)) + ((x##_h) & 0xF))) + \
	                             (60 * ((10*((x##_m & 0xF0)>>4)) + (x##_m & 0xF))) + \
				                                  ((10*((x##_s & 0xF0)>>4)) + (x##_s & 0xF)))
#define BcdTimeToSecondsHM(x) ((3600 * ((10*((x##_h & 0xF0)>>4)) + (x##_h & 0xF))) + \
	                             (60 * ((10*((x##_m & 0xF0)>>4)) + (x##_m & 0xF))))

#define DESCR_LEN			2
#define CA_DESCR_LEN	6
#define ISO639_LANGUAGE_DESCR_LEN 2
#define ISO639_LANGUAGE_DESCR_BODY_LEN 4
#define BOUQUET_NAME_DESCR_LEN	2
#define CA_IDENTIFIER_DESCR_LEN	2
#define CA_IDENTIFIER_DESCR_BODY_LEN	2
#define COMPONENT_DESCR_LEN	8
#define CONTENT_DESCR_LEN	2
#define CONTENT_DESCR_BODY_LEN	2
#define COUNTRY_AVAILABILITY_DESCR_LEN	3
#define COUNTRY_AVAILABILITY_DESCR_BODY_LEN	3
#define DATA_BROADCAST_DESCR_LEN	6
#define DATA_BROADCAST_DESCR_TEXT_LEN	4
#define DATA_BROADCAST_ID_DESCR_LEN	4
#define CABLE_DELIVERY_SYSTEM_DESCR_LEN	13
#define SATELLITE_DELIVERY_SYSTEM_DESCR_LEN	13
#define TERRESTRIAL_DELIVERY_SYSTEM_DESCR_LEN	13
#define EXTENDED_EVENT_DESCR_LEN	7
#define FREQUENCY_LIST_DESCR_LEN	3
#define FREQUENCY_LIST_DESCR_BODY_LEN	4
#define LINKAGE_DESCR_LEN	9
#define LOCAL_TIME_OFFSET_DESCR_LEN	2
#define LOCAL_TIME_OFFSET_DESCR_BODY_LEN	13
#define MOSAIC_DESCR_LEN	3
#define MOSAIC_DESCR_BODY_LEN	3
#define MOSAIC_DESCR_ELEMENTARY_CELL_ID_LEN	1
#define MOSAIC_DESCR_BOUQUET_INFO_LEN	2
#define MOSAIC_DESCR_SERVICE_INFO_LEN	6
#define MOSAIC_DESCR_MOSAIC_INFO_LEN	6
#define MOSAIC_DESCR_EVENT_INFO_LEN	8
#define MULTILINGUAL_BOUQUET_NAME_DESCR_LEN	2
#define MULTILINGUAL_BOUQUET_NAME_DESCR_BODY_LEN	4
#define MULTILINGUAL_COMPONENT_DESCR_LEN	3
#define MULTILINGUAL_COMPONENT_DESCR_BODY_LEN	4
#define MULTILINGUAL_NETWORK_NAME_DESCR_LEN	2
#define MULTILINGUAL_NETWORK_NAME_DESCR_BODY_LEN	4
#define MULTILINGUAL_SERVICE_NAME_DESCR_LEN	2
#define MULTILINGUAL_SERVICE_NAME_DESCR_BODY_LEN	4
#define NVOD_REFERENCE_DESCR_LEN	2
#define NVOD_REFERENCE_DESCR_BODY_LEN	6
#define NETWORK_NAME_DESCR_LEN	2
#define PARENTAL_RATING_DESCR_LEN	2
#define PARENTAL_RATING_DESCR_BODY_LEN	4
#define PRIVATE_DATA_SPECIFIER_DESCR_LEN	6
#define SHORT_SMOOTHING_BUFFER_DESCR_LEN	3
#define SERVICE_DESCR_LEN	4
#define SERVICE_LIST_DESCR_LEN	2
#define SERVICE_LIST_DESCR_BODY_LEN	3
#define SERVICE_MOVE_DESCR_LEN	8
#define SHORT_EVENT_DESCR_LEN	6
#define STREAM_IDENTIFIER_DESCR_LEN	3
#define STUFFING_DESCR_LEN	2
#define SUBTITLING_DESCR_LEN	2
#define SUBTITLING_DESCR_BODY_LEN	8
#define TELEPHONE_DESCR_LEN	5
#define TELETEXT_DESCR_LEN	2
#define TELETEXT_DESCR_BODY_LEN	5
#define TIME_SHIFTED_EVENT_DESCR_LEN	6
#define TIME_SHIFTED_SERVICE_DESCR_LEN	4
/* add by liux  2006-8-23 */
#define PARENT_RATING_DESCR_LEN	2
#define PARENT_RATING_DESCR_BODY_LEN	3
/* 数字与实际代表年龄的偏移 */
#define PARENT_RATING_DESCR_OFFSET	3

#ifdef  __cplusplus
}
#endif

#endif
