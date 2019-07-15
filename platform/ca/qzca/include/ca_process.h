#ifndef _GS_CA_PROCESS_H_
#define _GS_CA_PROCESS_H_
/* 包类型常数 */
#define PACK_TYPE_CHECK       0x01    /* 卡检测 */
#define PACK_TYPE_EMM         0x03    /* EMM数据 */
#define PACK_TYPE_ECM         0x04    /* ECM数据 */
#define PACK_TYPE_DATE        0x05    /* 日期 */

/* 错误码 */
#define ERR_OK                0x00    //正常
#define ERR_INVALID_ADDRESS   0x01    //智能卡序号错误
#define ERR_CRC               0x02    //CRC错误
#define ERR_NOT_INI           0x03    //卡未初始化
#define ERR_INVALID_TYPE      0x04    //错误的数据包类型
#define ERR_UNKNOWN           0x06    //未知的错误
#define ERR_COMM              0x80    //通讯错误

#endif
