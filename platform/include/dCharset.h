/**@defgroup font 字库
*@{*/
/** @file
* @brief 字符编码
* @author 龚克
* @date 2005-7-17 龚克: 建立文件
* @date 2013-03-19 lc: 统一平台, 代码整理
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

/** @brief 字符集,作位屏蔽*/
typedef enum {
	D_CHARSET_UNKNOWN	= 0x00000000,	/**< 未知*/
	D_CHARSET_ISO8859	= 0x00000001,	/**< ISO8859*/
	D_CHARSET_GB2312	= 0x00000002,	/**< GB2312*/
	D_CHARSET_UTF16		= 0x00000004,   /**< UTF16 */
	D_CHARSET_UTF8		= 0x00000008,   /**< UTF8 */
	D_CHARSET_SYS		= 0x00000010,   /**< sys code */	
	D_CHARSET_GBK 	= 0x00000020, 	/**< GBK*/	
	D_CHARSET_BIG5		= 0x00000040, 	/**< BIG5*/ 
	D_CHARSET_NEWLINE	= 0x80000000,   /**< 换行*/
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

/** @brief 取得一个字符串中的一个字符及其所属字符集
* @param[in] str	字符串起始指针
* @param[in] cnt	字符串长度
* @param[in] cs		返回字符所属的字符集
* @return	成功返回下一个字符的指针，失败返回NULL
*/
D_Char*		d_text_next_char (D_Char *str, D_Size cnt, D_Charset *cs) D_FUNCPOSTFIT;

/** @brief 取得一个字符串中的前一个字符及其所属字符集
* @param[in] first	字符串起始指针
* @param[in] str	字符串处理指针
* @param[in] cs		返回字符所属的字符集
* @return	成功返回下一个字符的指针，失败或字符串结束返回NULL
*/
D_Char*  d_text_prev_char (D_Char *str, D_Char *first, D_Charset *cs) D_FUNCPOSTFIT;

/** @brief 取得一个字符串中的一个词
* @param[in] str	字符串起始指针
* @param[in] cnt	字符串长度
* @return	成功返回指向下一个词的指针，失败返回NULL
*/
D_Char*		d_text_next_word (D_Char *str, D_Size cnt) D_FUNCPOSTFIT;


/** @brief 取得文本中光标位置前/后一个字符的长度
* @param[in] str	字符串起始指针
* @param[in] cnt	字符串长度
* @param[in] cursor 光标位置
* @param[in] forwd 向前标志
* @return val	前/后一个字符的长度。失败时为-1
*/
D_S32
d_text_get_char_len (D_Char *str, D_Size cnt, D_U32 cursor, D_Bool forwd) D_FUNCPOSTFIT;


/**@brief 在文本中光标位置插入(或替换)文字
* @param[in] str	字符串起始指针
* @param[in] cnt	字符串长度
* @param[in] cursor 光标位置
* @param[in] chr	插入(或替换)的字符串起始指针
* @param[in] addlen	插入(或替换)的字符串长度
* @param[in] cover  替换标志
* @return 成功返回D_OK，失败返回D_ERR
*/
D_Result
d_text_add_char (D_Char *str, D_Size cnt, D_U32 cursor, D_Char *chr, D_Size addlen, D_Bool cover) D_FUNCPOSTFIT;



/**@brief 在文本中光标位置向前(或向后)删除一个字符
* @param[in] str	字符串起始指针
* @param[in] cnt	字符串长度
* @param[in] cursor 光标位置
* @param[in] forwd 向前标志
* @return 成功返回D_OK，失败返回D_ERR
*/
D_Result
d_text_delete_char (D_Char *str, D_Size cnt, D_U32 cursor, D_Bool forwd) D_FUNCPOSTFIT;


#ifdef  __cplusplus
}
#endif

#endif

/**@}*/
