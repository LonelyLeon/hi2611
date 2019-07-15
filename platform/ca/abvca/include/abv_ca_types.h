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

/*�������ͺ궨��*/

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

/*���弸�ֲ������͵ĺ�*/
/*���к������õ�ָ��ָ��Ŀռ��ɵ��õĹ���*/
#define		FUNC_TYPE		//large reentrant /*hair �����뺯��*/
#define         far                     //����ƽ̨��far����ؼ��֣��κ겻�ô򿪡�����ƽ̨
//û��far�ؼ��֣���Ҫ�򿪴˺꣬��������鶨��ĵط���������
#define		OUT			       /*�����ó�ʼ�������������������*/
#define		IN				/*�����߳�ʼ�������������������*/			
#define		INOUT			/*�����������룬�������������*/


/* �����ź������*/
typedef   ABV_UInt32  ABV_Semaphore_Handle;

/* ������Ϣ���о��*/
typedef   ABV_UInt32  ABV_Queue_Handle;

/* ���嶨ʱ�����*/
typedef   ABV_UInt32  ABV_Timer_Handle;
/*���峬ʱ�ص���������*/
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

