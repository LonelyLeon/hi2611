/*****************************************************************************
File name     : abv_ca_types.h

Description   : base data types 

Copyright (C) : ABV 2006

R&D Group	    : Beijing Alliance Broadcast Vision Technology CO., LTD.

Author(s)	    :  zhangxl    

Notes          : 

History	    : 

Version 		Date   			Author(s) 	Desciption    Reference
2.0			2006.12.26	       zhangxl		Created
*****************************************************************************/
#ifndef __ABV_CA_TYPES_H__
#define __ABV_CA_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

/*数据类型宏定义*/

typedef unsigned char            	ABV_UInt8;
typedef unsigned short           	ABV_UInt16;
/*typedef unsigned int             	ABV_UInt16;*/
typedef unsigned long int        	ABV_UInt32;
typedef char                 ABV_Int8;
typedef short                ABV_Int16;
typedef long int             ABV_Int32;
/*typedef long int                 	ABV_Int64;*/
typedef float                    		ABV_Float;
typedef double                   	ABV_Double;
typedef void*                    		ABV_Pointer;
/*typedef ABV_Int8		             	ABV_Char;*/
typedef char		             	ABV_Char;
typedef void							ABV_VOID;
#define ABV_CONST 						const//far  

#ifndef  ABV_NULL
#define ABV_NULL  			(void *)0
#endif

typedef enum
{
    ABV_FALSE    	= 0,
    ABV_TRUE     	= 1
} ABV_Boolean;

/*定义几种参数类型的宏*/
/*所有函数调用的指针指向的空间由调用的管理*/
#define		FUNC_TYPE		//large reentrant /*hair 可重入函数*/
#define         far                     //海尔平台有far这个关键字，次宏不用打开。其他平台
//没有far关键字，需要打开此宏，否则大数组定义的地方会编译错误。
#define		OUT			       /*被调用初始化并填入内容填充内容*/
#define		IN				/*调用者初始化并填入内容填充内容*/			
#define		INOUT			/*调用者有输入，被调用者有输出*/


/* 定义信号量句柄*/
typedef   ABV_UInt32  ABV_Semaphore_Handle;

/* 定义消息队列句柄*/
typedef   ABV_UInt32  ABV_Queue_Handle;

/* 定义定时器句柄*/
typedef   ABV_UInt32  ABV_Timer_Handle;
/*定义超时回调函数类型*/
typedef  ABV_VOID (*ABV_Timer_CallBak)(ABV_Timer_Handle Timer_Handle);



/* abv tv mail types*/

#define ABV_STATIC				static
#define ABV_MAIL_POSTFIX
#define ABV_MAIL_NULL				0

typedef void						ABV_MAIL_VOID;
typedef char						ABV_MAIL_CHAR;
typedef unsigned char 				ABV_U8;
typedef unsigned short 			ABV_U16;
typedef unsigned long 				ABV_U32;
typedef signed char 				ABV_S8;
typedef signed short 				ABV_S16;
typedef signed long 				ABV_S32;

#ifdef __cplusplus
}
#endif
#endif

