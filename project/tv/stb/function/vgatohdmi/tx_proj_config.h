#ifndef _TX_PROJECT_CONFIG_H_
#define _TX_PROJECT_CONFIG_H_

/*
** PLEASE DON'T EDIT THESE LINES 
** TX Project Configurations
*/

/* Video parts */
#define  TX_RGB_CHANNEL_0   (0x0001)
#define  TX_RGB_CHANNEL_1   (0x0002) 

#define  TX_SP_EXT_SYNC1    (0x0004)
#define  TX_SP_EXT_SYNC2    (0x0008)

#define  TX_OUT_CS_RGB      (0x0010)
#define  TX_OUT_CS_YUV444   (0x0020)
#define  TX_OUT_CS_YUV422   (0x0040)

#define  TX_SINK_HDMI       (0x0100)
#define  TX_SINK_DVI        (0x0200)

/* Audio Parts */
#define  TX_AUD_INF_I2S     (0x0100)
#define  TX_AUD_INF_SPDIF   (0x0200)

/* Audio sample rate */
#define  TX_AUD_SAR_192K    (0)
#define  TX_AUD_SAR_96K     (1)
#define  TX_AUD_SAR_48K     (2)
#define  TX_AUD_SAR_176K    (3)
#define  TX_AUD_SAR_882K    (4)
#define  TX_AUD_SAR_441K    (5)
#define  TX_AUD_SAR_32K     (6)

/*
** PLEASE DON'T EDIT THESE LINES 
** === END === 
*/

/*========================================
 * User Configuration Area
 *=======================================*/
/* Refer to system-board for I2C-address */
#define  TX_I2C_ADDR            (0x7A)

#define  TX_VIDEO_SYSTEM_PARAM  (TX_RGB_CHANNEL_0 | TX_SP_EXT_SYNC2 | TX_SINK_HDMI)
#define  TX_AUDIO_SYSTEM_PARAM  (TX_AUD_INF_I2S | TX_AUD_SAR_48K)

#endif
