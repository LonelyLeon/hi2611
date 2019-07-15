/******************************************************************************
 * p4vLocalTypes.h: ����Lib�����ԭʼ��������
 *-----------------------------------------------------------------------------
 *  ����ͬ����Ѷ�Ƽ����޹�˾
 *
 *  2008����Ȩ���У�����һ��Ȩ����
 *-----------------------------------------------------------------------------
 *
 * �޶���ʷ
 *     Ҷκ��   2009/01/06      �����ļ���
 *
 ******************************************************************************/

#ifndef P4V_LOCAL_TYPES_H
#define P4V_LOCAL_TYPES_H

// ��λ�޷�������
typedef unsigned char   ird_uint8_t;
// ʮ��λ�޷�������
typedef unsigned short  ird_uint16_t;
// ��ʮ��λ�޷�������
typedef unsigned int    ird_uint32_t;

// ��λ�з�������
typedef char            ird_int8_t;
// ʮ��λ�з�������
typedef short           ird_int16_t;
// ��ʮ��λ�з�������
typedef int             ird_int32_t;
// �����ļ�����������
typedef ird_uint32_t    ird_FILE_t;

// ��������
typedef ird_uint8_t     ird_bool_t;

// ��Чָ��
#ifndef NULL
#define NULL (void *)0
#endif

#ifndef P4V_TRUE
#define P4V_TRUE    1
#endif

#ifndef P4V_FALSE
#define P4V_FALSE   0
#endif

#endif  /* end_of_file */
