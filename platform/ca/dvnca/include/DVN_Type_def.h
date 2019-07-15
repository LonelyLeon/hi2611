#ifndef __DVN_TYPE_def_h__
#define __DVN_TYPE_def_h__

/* basic */
/*
typedef  char           		INT8;
typedef  unsigned char   		UINT8;
typedef  short          		INT16;
typedef  unsigned short  		UINT16;
typedef  int            		INT32;
typedef  unsigned int    		UINT32;
*/

#ifndef BYTE
typedef	 unsigned char			BYTE;
#endif

#ifndef WORD
typedef	 unsigned short int		WORD;
#endif

#ifndef DWORD
typedef	 unsigned long			DWORD;
#else 
#undef DWORD
typedef	 unsigned long			DWORD;
#endif 

#define CAK_OK	1
#define CAK_ERR	-1
#define	CAK_TIMEOUT				TIMEOUT_INFINITY


/* Smartcard */
typedef enum{
	SC_COMPLETE_OK,
	SC_NO_CARD_ERROR,
	SC_MUTE_ERROR,
	SC_ERROR,
	SC_TIMEOUT
} SC_RESULT_CODE;

typedef enum{
	SC_CARD_IN,
	SC_CARD_OUT
} SC_EVENT_TYPE;

/* RTOS */
typedef	unsigned long	DVN_RTOS_SEMAPHORE;
typedef	unsigned long	DVN_RTOS_MSG_QUEUE;

typedef enum {
	DVN_RTOS_OK,
	DVN_RTOS_FAIL
} DVN_RTOS_RESULT;

typedef enum {
	DVN_RTOS_QUEUE_BLOCKING,
	DVN_RTOS_QUEUE_NONBLOCKING
} DVN_RTOS_QUEUE_MODE;



#endif /* __DVN_TYPE_def_h__ */
