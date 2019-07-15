/**@defgroup font �ֿ�
*@{*/
/** @file
* @brief �ַ�����
* @author ����
* @date 2005-7-17 ����: �����ļ�
* @date 2013-03-19 lc: ͳһƽ̨, ��������
*/

#ifndef _D_CHARSET_H_
#define _D_CHARSET_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

#if 1
#include <ctype.h>

#define D_IS_SPACE(_c)	isspace((D_U8)(_c))
#define D_IS_DIGIT(_c)	isdigit((D_U8)(_c))
#define D_IS_XDIGIT(_c)	isxdigit((D_U8)(_c))
#define D_IS_ALPHA(_c)	isalpha((D_U8)(_c))
#define D_IS_PRINT(_c)	isprint((D_U8)(_c))
#define D_IS_GRAPH(_c)	isgraph((D_U8)(_c))
#define D_IS_ASCII(_c)	isascii((D_U8)(_c))
#define D_IS_LOWER(_c)	islower((D_U8)(_c))
#define D_IS_UPPER(_c)	isupper((D_U8)(_c))
#define D_TO_LOWER(_c)	tolower((D_U8)(_c))
#define D_TO_UPPER(_c)	toupper((D_U8)(_c))
#else
#define D_IS_SPACE(_c)	((((D_U8)(_c))==' ') || ((((D_U8)(_c))>=0x09) && (((D_U8)(_c))<=0x0D)))
#define D_IS_DIGIT(_c)	((((D_U8)(_c))>='0') && (((D_U8)(_c))<='9'))
#define D_IS_XDIGIT(_c)	(D_IS_DIGIT(_c) || ((((D_U8)(_c))>='a') && (((D_U8)(_c))<='f')) || ((((D_U8)(_c))>='A') && (((D_U8)(_c))<='F')))
#define D_IS_ALPHA(_c)	(((((D_U8)(_c))>='a') && (((D_U8)(_c))<='z')) || ((((D_U8)(_c))>='A') && (((D_U8)(_c))<='Z')))
#define D_IS_PRINT(_c)	((((D_U8)(_c))>=0x20) && (((D_U8)(_c))<=0x7E))
#define D_IS_GRAPH(_c)	((((D_U8)(_c))>=0x21) && (((D_U8)(_c))<=0x7E))
#define D_IS_ASCII(_c)	(((D_U8)(_c))<= 0x7F)
#define D_IS_LOWER(_c)	(((((D_U8)(_c))>='a') && (((D_U8)(_c))<='z')))
#define D_IS_UPPER(_c)	(((((D_U8)(_c))>='A') && (((D_U8)(_c))<='Z')))
#define D_TO_LOWER(_c)	(D_IS_UPPER(_c)?((_c)-'A'+'a'):(_c))
#define D_TO_UPPER(_c)	(D_IS_LOWER(_c)?((_c)-'a'+'A'):(_c))
#endif

/** @brief �ַ���,��λ����*/
typedef enum {
	D_CHARSET_UNKNOWN	= 0x00000000,	/**< δ֪*/
	D_CHARSET_ISO8859	= 0x00000001,	/**< ISO8859*/
	D_CHARSET_GB2312	= 0x00000002,	/**< GB2312*/
	D_CHARSET_UTF16		= 0x00000004,   /**< UTF16 */
	D_CHARSET_UTF8		= 0x00000008,   /**< UTF8 */
	D_CHARSET_SYS		= 0x00000010,   /**< sys code */	
	D_CHARSET_GBK 	= 0x00000020, 	/**< GBK*/	
	D_CHARSET_BIG5		= 0x00000040, 	/**< BIG5*/ 
	D_CHARSET_NEWLINE	= 0x80000000,   /**< ����*/
} D_Charset;

typedef struct
{
	D_Char *str;
	D_Size cnt;
	D_Charset *cs;
	D_Result *ret;
}D_CCNextCharHookParam;

typedef struct
{
	D_Char *str;
	D_Char *first;
	D_Charset *cs;
	D_Result *ret;
}D_CCPrevCharHookParam;

typedef struct
{
	D_Char *str;
	D_Size cnt;
	D_Result *ret;
}D_CCNextWordHookParam;

typedef struct
{
	D_Char **text;
	D_Size *cnt;
}D_CCDrawTextHookParam;

/** @brief ȡ��һ���ַ����е�һ���ַ����������ַ���
* @param[in] str	�ַ�����ʼָ��
* @param[in] cnt	�ַ�������
* @param[in] cs		�����ַ��������ַ���
* @return	�ɹ�������һ���ַ���ָ�룬ʧ�ܷ���NULL
*/
D_Char*		d_text_next_char (D_Char *str, D_Size cnt, D_Charset *cs) D_FUNCPOSTFIT;

/** @brief ȡ��һ���ַ����е�ǰһ���ַ����������ַ���
* @param[in] first	�ַ�����ʼָ��
* @param[in] str	�ַ�������ָ��
* @param[in] cs		�����ַ��������ַ���
* @return	�ɹ�������һ���ַ���ָ�룬ʧ�ܻ��ַ�����������NULL
*/
D_Char*  d_text_prev_char (D_Char *str, D_Char *first, D_Charset *cs) D_FUNCPOSTFIT;

/** @brief ȡ��һ���ַ����е�һ����
* @param[in] str	�ַ�����ʼָ��
* @param[in] cnt	�ַ�������
* @return	�ɹ�����ָ����һ���ʵ�ָ�룬ʧ�ܷ���NULL
*/
D_Char*		d_text_next_word (D_Char *str, D_Size cnt) D_FUNCPOSTFIT;


/** @brief ȡ���ı��й��λ��ǰ/��һ���ַ��ĳ���
* @param[in] str	�ַ�����ʼָ��
* @param[in] cnt	�ַ�������
* @param[in] cursor ���λ��
* @param[in] forwd ��ǰ��־
* @return val	ǰ/��һ���ַ��ĳ��ȡ�ʧ��ʱΪ-1
*/
D_S32
d_text_get_char_len (D_Char *str, D_Size cnt, D_U32 cursor, D_Bool forwd) D_FUNCPOSTFIT;


/**@brief ���ı��й��λ�ò���(���滻)����
* @param[in] str	�ַ�����ʼָ��
* @param[in] cnt	�ַ�������
* @param[in] cursor ���λ��
* @param[in] chr	����(���滻)���ַ�����ʼָ��
* @param[in] addlen	����(���滻)���ַ�������
* @param[in] cover  �滻��־
* @return �ɹ�����D_OK��ʧ�ܷ���D_ERR
*/
D_Result
d_text_add_char (D_Char *str, D_Size cnt, D_U32 cursor, D_Char *chr, D_Size addlen, D_Bool cover) D_FUNCPOSTFIT;



/**@brief ���ı��й��λ����ǰ(�����)ɾ��һ���ַ�
* @param[in] str	�ַ�����ʼָ��
* @param[in] cnt	�ַ�������
* @param[in] cursor ���λ��
* @param[in] forwd ��ǰ��־
* @return �ɹ�����D_OK��ʧ�ܷ���D_ERR
*/
D_Result
d_text_delete_char (D_Char *str, D_Size cnt, D_U32 cursor, D_Bool forwd) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif

/**@}*/
