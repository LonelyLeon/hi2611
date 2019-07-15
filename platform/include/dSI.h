/** @file
* @brief SI数据结构定义
* @author 龚克
* @date 2005-6-10 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 代码整理
*/

#ifndef _D_SI_H_
#define _D_SI_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief PID*/
#define PID_PAT				0x00	/**< Program Association Table */
#define PID_CAT				0x01	/**< Conditional Access Table */
#define PID_TSDT			0x02	/**< Transport Stream Description Table*/
#define PID_NIT				0x10	/**< Network Information Table*/
#define PID_SDT				0x11	/**< Service Description Table */
#define PID_BAT				0x11	/**< Bouquet Association Table */
#define PID_EIT				0x12	/**< Event Information Table */
#define PID_RST				0x13	/**< Running Status Table */
#define PID_TDT				0x14	/**< Time Date Table */
#define PID_TOT				0x14	/**< Time Offset Table */
#define PID_ST				0x14	/**< Stuffing Table */
#define PID_NET_SYNC	0x15	/**< Network sync */
#define PID_DIT				0x1E	/**< Discontinuity Information Table*/
#define PID_SIT				0x1F	/**< Selection Information Table*/

/** @brief Table ID*/
#define TID_PAT				0x00	/**< Program Association Section */
#define TID_CAT				0x01	/**< Conditional Access Section */
#define TID_PMT				0x02	/**< Conditional Access Section */
#define TID_TSDT			0x03	/**< Transport Stream descriptor section */
#define TID_NIT_ACT		0x40	/**< Network Information Section actual */
#define TID_NIT_OTH		0x41	/**< Network Information Section other */
#define TID_SDT_ACT		0x42	/**< Service Description Section actual */
#define TID_SDT_OTH		0x46	/**< Service Description Section other */
#define TID_BAT				0x4A	/**< bouquet Association Section  */
#define TID_EIT_ACT		0x4E	/**< Event Information Section actual */
#define TID_EIT_OTH		0x4F	/**< Event Information Section other */
#define TID_EIT_ACT_SCH	0x50	/**< Event Information Section actual,schedule*/
#define TID_EIT_OTH_SCH	0x60	/**< Event Information Section other, schedule */
#define TID_TDT				0x70	/**< Time Date Section */
#define TID_RST				0x71	/**< Running States Section */
#define TID_ST				0x72	/**< Stuffing Section */
#define TID_TOT				0x73	/**< Time Offset Section */
#define TID_DIT				0x7E	/**< Discontinuity Information Section */
#define TID_SIT				0x7F	/**< Selection Information Section */

/** @brief 取一个字节n从a位开始,b个比特长度的数据(a,b为从最高为开始的位数)*/
#define D_SI_BIT(n,a,b)\
		((((D_U8)n) & (0xFF >> (a))) >> (8-(a)-(b)))
		
#define D_SI_HILO(h,l)\
		((((D_U16)h)<<8) | (((D_U16)l)&0xFF))

#define D_SI_BCD(x)	((((x) & 0xf0) >> 4)*10+((x)&0x0f))

#define D_SI_MJD2TIME(h, l)\
		(((((D_U32)h) << 8 | ((D_U32)l))-40587)*86400)

#define D_SI_BCD2SEC(h,m,s)\
		((3600 * ((10*(((h) & 0xF0)>>4)) + ((h) & 0xF))) + \
		(60 * ((10*(((m) & 0xF0)>>4)) + ((m) & 0xF))) + \
		((10*(((s) & 0xF0)>>4)) + ((s) & 0xF)))

#define D_SI_BCD2SECHM(h,m)\
		((3600 * ((10*(((h) & 0xF0)>>4)) + ((h) & 0xF))) + \
		(60 * ((10*(((m) & 0xF0)>>4)) + ((m) & 0xF))))

/** @brief PAT*/
#define PAT_LEN	8
#define PAT_BODY_LEN	4
#define CAT_LEN	8
#define PMT_LEN	12
#define PMT_INFO_LEN	5
#define NIT_LEN	10
#define NIT_TS_LOOP_LEN	2
#define NIT_TS_LOOP_BODY_LEN	6
#define BAT_LEN	10
#define BAT_TS_LOOP_LEN	2
#define BAT_TS_LOOP_BODY_LEN	6
#define SDT_LEN	11
#define SDT_BODY_LEN	5
#define EIT_LEN	14
#define EIT_BODY_LEN	12
#define TDT_LEN	8
#define TOT_LEN	10
#define RST_LEN	3
#define RST_BODY_LEN	9
#define ST_LEN	3

#ifdef  __cplusplus
}
#endif

#endif
