#include <stdio.h>


#define STATIC static
#define Uint32 unsigned int
#define SHAREDENTRYID1 0x1
#define POOLENTRYID 0x2
#define Char8 char
#define DSP_MAX_STRLEN 32

typedef struct LINKCFG_Pool_tag {
    Char8                    name [DSP_MAX_STRLEN] ;
    Uint32                   memEntry ;
    Uint32                   poolSize ;
    Uint32                   ipsId ;
    Uint32                   ipsEventNo ;
    Uint32                   poolMemEntry ;
    Uint32                   arg1 ;
    Uint32                   arg2 ;
} LINKCFG_Pool ;

STATIC LINKCFG_Pool  LINKCFG_poolTable_00 [] =
{
   {
      "SMAPOOL",                /* NAME           : Name of the pool */
      (Uint32) SHAREDENTRYID1,  /* MEMENTRY       : Memory entry ID (-1 if not needed) */
      (Uint32) 0x70000,         /* POOLSIZE       : Size of the pool (-1 if not needed) */
      (Uint32) -1,              /* IPSID          : ID of the IPS used */
      (Uint32) -1,              /* IPSEVENTNO     : IPS Event number associated with POOL */
      POOLENTRYID,              /* POOLMEMENTRY   : Pool memory region section ID  */
      0x0,                      /* ARGUMENT1      : First Pool-specific argument */
      0x0                       /* ARGUMENT2      : Second Pool-specific argument */
   },
   {
      "SMAPOOL",                /* NAME           : Name of the pool */
      (Uint32) SHAREDENTRYID1,  /* MEMENTRY       : Memory entry ID (-1 if not needed) */
      (Uint32) 0x70000,         /* POOLSIZE       : Size of the pool (-1 if not needed) */
      (Uint32) -1,              /* IPSID          : ID of the IPS used */
      (Uint32) -1,              /* IPSEVENTNO     : IPS Event number associated with POOL */
      POOLENTRYID,              /* POOLMEMENTRY   : Pool memory region section ID  */
      0x0,                      /* ARGUMENT1      : First Pool-specific argument */
      0x0                       /* ARGUMENT2      : Second Pool-specific argument */
   }
} ;

STATIC LINKCFG_Pool * LINKCFG_poolTables [] =
{
   LINKCFG_poolTable_00       /* Pool Table 0 */
} ;

int main(void)
{

   printf("sizeof(LINKCFG_poolTable_00) = %d\n", sizeof(LINKCFG_poolTable_00)); //120
   printf("sizeof(LINKCFG_poolTables) = %d\n", sizeof(LINKCFG_poolTables)); //4
   printf("sizeof(LINKCFG_Pool *) = %d\n", sizeof(LINKCFG_Pool *)); //4
   printf("sizeof(LINKCFG_Pool) = %d\n", sizeof(LINKCFG_Pool)); //60
   return 0;
}

/*
#define DSP_MAX_STRLEN 32

sizeof(LINKCFG_poolTable_00) = 120
sizeof(LINKCFG_poolTables) = 4
sizeof(LINKCFG_Pool *) = 4
sizeof(LINKCFG_Pool) = 60

 */

/*
 * if #define DSP_MAX_STRLEN 33
 * sizeof(LINKCFG_poolTable_00) = 128
 * sizeof(LINKCFG_poolTables) = 4
 * sizeof(LINKCFG_Pool *) = 4
 * sizeof(LINKCFG_Pool) = 64
 * */

