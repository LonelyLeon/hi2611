/*****************************************************************************

File name   : dclilib.h

Description : command line interpreter

haier-ic  qiny   @2012-03-12
*****************************************************************************/

#ifndef __DCLILIB_H
#define __DCLILIB_H

#include "dtesttool.h"

#ifdef __cplusplus
extern "C" {
#endif

/* constants -------------------------------------------------------------- */

#define CLI_SPACE_CHAR  0x20
#define CLI_TAB_CHAR    0x09
#define CLI_ESCAPE_CHAR '\\'
#define CLI_NL_CHAR     '\n'
#define CLI_CR_CHAR     '\r'

#define CLI_COMMENT_CHAR ';'  /* semi-colon */

enum
{
    CLI_NO_CONST,
    CLI_DEFINE_CONST,
    CLI_IF_CONST,
    CLI_ELIF_CONST,
    CLI_ELSE_CONST,
    CLI_WHILE_CONST,
    CLI_FOR_CONST
};

#define CLI_MAX_LINE_LENGTH 255

/* macro store structure -------------------------------------------------- */

struct macro_s
{
    struct macro_s *line_p;
    char           line[CLI_MAX_LINE_LENGTH];
};
typedef struct macro_s macro_t;

/* symbol table data structure and types ---------------------------------- */

#define CLI_NO_SYMBOL  0
#define CLI_INT_SYMBOL 1             /* integer symbol                          */
#define CLI_FLT_SYMBOL 2             /* floating point symbol                   */
#define CLI_STR_SYMBOL 4             /* string symbol                           */
#define CLI_COM_SYMBOL 8             /* command symbol                          */
#define CLI_MAC_SYMBOL 16            /* macro symbol                            */
#define CLI_ANY_SYMBOL 0xFF          /* matches all symbol types                */

struct symtab_s
{
    D_Char *name_p;                    /* symbol id                               */
    D_S16  type;                       /* type of symbol                          */
    D_S16  name_len;                   /* length of symbol name                   */
    union
    {
        D_S32     int_val;
        D_Double  flt_val;
        D_Char    *str_val;
        D_Bool    (*com_val)(HRTST_Parse_t*, D_Char*);
        macro_t *mac_val;
    } value;                         /* value of symbol                         */
    D_Bool fixed;                      /* flag for symbol                         */
    D_S16  depth;                      /* nesting depth at which declaration made */
    const D_Char *info_p;              /* informational string                    */
};
typedef struct symtab_s symtab_t;

/* prototypes ------------------------------------------------------------- */

void hrtst_CliInit(D_Bool (*setup_r)(void), D_S16 max_symbols, D_S16 default_base );
void hrtst_CliRun (D_Char *const ip_prompt_p);
void hrtst_CliTerm(void);

int hrtst_ReadLineNumber(void);

#ifdef __cplusplus
}
#endif

#endif
