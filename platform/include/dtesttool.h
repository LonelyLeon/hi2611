/*****************************************************************************

File name   : dtesttool.h

Description : main development API

haier-ic  qiny   @2012-03-12
*****************************************************************************/

#ifndef __DTESTTOOL_H
#define __DTESTTOOL_H

#include "dTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Constants -------------------------------------------------------------- */

#define HRTST_MAX_TOK_LEN          80 /* nb max of bytes for one token      */

#define HRTST_INTERACTIVE_MODE              0x00  /* testtool prompt available (default mode) */
#define HRTST_BATCH_MODE                    0x01  /* batch mode : no testtool prompt available, auto leave */
#define HRTST_NO_ABBREVIATION_MODE          0x02  /* no symbol name abbreviation allowed */
#define HRTST_HIT_KEY_TO_ENTER_MODE         0x04  /* if HRTST_INTERACTIVE_MODE, hit key to enter testtool */
#define HRTST_KEEP_CONTROL_VARIABLE_MODE    0x08  /* if/then/else, for, while controls: do not delete variables */
#define HRTST_SUPPORTED_MODES_MASK          0x0F  /* OR of supported modes */


/* Initialization parameters ---------------------------------------------- */

typedef struct HRTST_InitParams_s
{
    D_S16  NbMaxOfSymbols;             /* size of the internal symbols table  */
} HRTST_InitParams_t;

/* Tokeniser data structure ----------------------------------------------- */

struct parse
{
  D_Char    *line_p;   /* string under examination                            */
  D_S16     par_pos;   /* index of current position, at delimiter or EOL      */
  D_S16     par_sta;   /* index of start position for last operation          */
  D_S16     tok_len;   /* length of identified token                          */
  D_Char    tok_del;   /* delimiter of current token (not part of token)      */
  D_Char    token[HRTST_MAX_TOK_LEN]; /* token found. Space allocated on need, constant kept for backward compatibility */
};
typedef struct parse HRTST_Parse_t;
typedef struct parse parse_t; /* old prototype (before year 2000) */

typedef D_S16 HRTST_RunningMode_t; /* bit 1=abbreviation; bit 0=interactive   */

/* Revision structure */
typedef const D_Char *HRTST_Revision_t;

/* Functions and variables NOT TO BE USED by users of the API --------------- */
void hrtst_Print(const D_Char *, ...); 

/* Function prototypes for user (since February 2000) -----------------------*/

#define HRTBX_Print(msg) hrtst_Print msg


D_Bool HRTST_Init(const HRTST_InitParams_t *);
D_Bool HRTST_Start(void);
D_Bool HRTST_Term(void);
D_Bool HRTST_SetMode(HRTST_RunningMode_t);

HRTST_Revision_t HRTST_GetRevision(void);

D_Bool HRTST_GetString (HRTST_Parse_t *pars_p, const D_Char *const default_p, D_Char *const result_p, D_S16 max_len);
D_Bool HRTST_GetItem   (HRTST_Parse_t *pars_p, const D_Char *const default_p, D_Char *const result_p, D_S16 max_len);
D_Bool HRTST_GetInteger(HRTST_Parse_t *pars_p, D_S32    def_int, D_S32    *result_p);
D_Bool HRTST_GetFloat  (HRTST_Parse_t *pars_p, D_Double def_flt, D_Double *result_p);
D_Bool HRTST_GetTokenCount(HRTST_Parse_t *pars_p, D_S16 *result_p);

void HRTST_TagCurrentLine (HRTST_Parse_t *pars_p, const D_Char *const message_p);

D_Bool HRTST_AssignInteger(const D_Char *const token_p, D_S32        value         , D_Bool constant);
D_Bool HRTST_AssignFloat  (const D_Char *const token_p, D_Double     value         , D_Bool constant);
D_Bool HRTST_AssignString (const D_Char *const token_p, const D_Char *const value_p, D_Bool constant);

D_Bool HRTST_DeleteSymbol (const D_Char *const token_p);

D_Bool HRTST_EvaluateInteger(const D_Char *const token_p, D_S32    *value_p,  D_S16 default_base);
D_Bool HRTST_EvaluateFloat  (const D_Char *const token_p, D_Double *value_p);
D_Bool HRTST_EvaluateString (const D_Char *const token_p, D_Char *  string_p, D_S16 max_len);

D_Bool HRTST_RegisterCommand(const D_Char *const token_p, D_Bool (*action)(HRTST_Parse_t*, D_Char*), const D_Char *const help_p);

#define register_command(t,a,h) HRTST_RegisterCommand(t,(D_Bool (*)(HRTST_Parse_t*, D_Char*)) a,h)
#define TESTTOOL_InitParams_t   HRTST_InitParams_t

#ifdef __cplusplus
}
#endif

#endif /* ifndef __TESTTOOL_H */
