#ifndef _MCU_HAL_TYPEDEF_H_
#define _MCU_HAL_TYPEDEF_H_

#if defined(_IAR_STM8_COMPILER_)

typedef  bool           bool_t;
typedef  void           void_t;
#define  __CONST        const
#define  __CODE         const
#define  __XDATA    
#define  __DATA         
#define  __NEAR         __near

#elif defined(_COSMIC_COMPILER_)

typedef  _Bool          bool_t;
typedef  void           void_t;
#define  __CONST        const
#define  __CODE         const
#define  __XDATA    
#define  __DATA
#define  __NEAR         @near

#elif defined(_KEIL_COMPILER_)

typedef  bit            bool_t;
typedef  void           void_t;

/* Aditional TYPEDEF */ 
typedef  char           char_t;
typedef  char           int8_t;
typedef  int            int16_t;
typedef  long           int32_t;

#define  __CONST        const
#define  __CODE         code
#define  __XDATA        xdata
#define  __DATA         data
#define  __IO           volatile 
#define  __NEAR         xdata

typedef enum
{
    FALSE = 0,
    TRUE  = 1
} BOOL_;

#elif defined(_GNU_COMPILER_)

#include <stdbool.h>

typedef  bool           bool_t;
typedef  void           void_t;

/* Aditional TYPEDEF */ 
typedef  char           char_t;
//typedef  char           int8_t;
typedef  unsigned char  uint8_t;
typedef  short          int16_t;
typedef  unsigned short uint16_t;
typedef  int            int32_t;
typedef  unsigned int   uint32_t;

#define  __CONST        const
#define  __CODE
#define  __DATA
#define  __IO           volatile 
#define  __NEAR

typedef enum
{
    FALSE = false,
    TRUE  = true
}_BOOL;
#endif


typedef enum
{
    LOW    = 0,
    HIGH   = 1
}HIGHLOW;

typedef enum
{
    OFF    = 0,
    ON     = 1    
}ONOFF;

#ifndef _countof
    #define _countof(ARRAY) (sizeof(ARRAY)/sizeof(ARRAY[0]))
#endif

#define UNUSED_ALWAYS(x)    (x)

#endif
