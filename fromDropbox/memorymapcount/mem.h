typedef struct LINKCFG_MemEntry_tag {
    unsigned int                   entry ;
    char                    	   name [32] ;
    unsigned int                   physAddr ;
    unsigned int                   dspVirtAddr ;
    unsigned int                   gppVirtAddr ;
    unsigned int                   size ;
    int                     shared ;
    int                     syncd  ;
} LINKCFG_MemEntry ;

#define STATIC static
#define TRUE 1
#define FALSE 0
typedef unsigned int Uint32;

//--------------------- paste here -----------------------

/** ============================================================================
 *  @name   DRVHANDSHAKEPOLLCOUNT
 *
 *  @desc   POLL Count for Driver handshake.
 *  ============================================================================
 */
#define  DRVHANDSHAKEPOLLCOUNT        ((Uint32) 100000000u)

/** ============================================================================
 *  @name   RESETCTRLADDR
 *
 *  @desc   Indicates the start address of Reset Ctrl memory region.
 *          last two nibbles must be zero i.e. align to 256 boundary.
 *  ============================================================================
 */
#define  RSTENTRYID         0
#define  RESETCTRLADDR      0x86100000
#define  RESETCTRLSIZE      0x400u

/** ============================================================================
 *  @name   CODEMEMORYADDR/CODEMEMORYSIZE
 *
 *  @desc   Indicates startaddress/size for dsplink code region.
 *  ============================================================================
 */
#define  CODEENTRYID        1
#define  CODEMEMORYADDR     (RESETCTRLADDR + RESETCTRLSIZE)
#define  CODEMEMORYSIZE     0xBFFC00u

/** ============================================================================
 *  @name   SHAREDENTRYID/SHAREDMEMORYADDR/SHAREDMEMORYSIZE
 *
 *  @desc   Indicates startaddress/size for dsplink shared memory region.
 *  ============================================================================
 */
#define  SHAREDENTRYID0     2
#define  SHAREDMEMORYADDR0  (CODEMEMORYADDR + CODEMEMORYSIZE)
#define  SHAREDMEMORYSIZE0  0x5000u

/** ============================================================================
 *  @name   SHAREDENTRYID/SHAREDMEMORYADDR/SHAREDMEMORYSIZE
 *
 *  @desc   Indicates startaddress/size for dsplink shared memory region.
 *  ============================================================================
 */
#define  SHAREDENTRYID1     3
#define  SHAREDMEMORYADDR1  (SHAREDMEMORYADDR0 + SHAREDMEMORYSIZE0)
#define  SHAREDMEMORYSIZE1  0xAB000u

/** ============================================================================
 *  @name   POOLMEMORYADDR/POOLMEMORYSIZE
 *
 *  @desc   Indicates startaddress/size for dsplink POOL memory region.
 *  ============================================================================
 */
#define  POOLENTRYID        4
#define  POOLMEMORYADDR     (SHAREDMEMORYADDR1 + SHAREDMEMORYSIZE1)
//#define  POOLMEMORYSIZE     (0x00300000+0x00200000) 
#define  POOLMEMORYSIZE     (0x00500000u) 

/*   
#define  DSPMEMENTRYID0        7
#define  DSPMEMORYADDR0     (POOLMEMORYADDR + POOLMEMORYSIZE)
#define  DSPMEMORYSIZE0     0x00900000u
*/

#define  VECSENTRYID        7
#define  VECSADDR     (POOLMEMORYADDR+POOLMEMORYSIZE)
#define  VECSSIZE     0x800u


#define  VPSSENTRYID        8
#define  VPSSADDR     (VECSADDR+VECSSIZE)
#define  VPSSSIZE     0x10000u

#define  DEBUGENTRYID       9 
#define  DEBUGADDR     (VPSSADDR+VPSSSIZE)
#define  DEBUGSIZE     0x00000700u

#define  POOL_MSGQ_ID       10 
#define  POOL_MSGQ_ADDR     (DEBUGADDR+DEBUGSIZE)
#define  POOL_MSGQ_SIZE     0x00200000u

/** ============================================================================
 *  @name   LINKCFG_memTable_00
 *
 *  @desc   Memory table ID 0.
 *  ============================================================================
 */
STATIC LINKCFG_MemEntry  LINKCFG_memTable_00 [] =
{
    {
        RSTENTRYID,                        /* ENTRY          : Entry number */
        "RESETCTRL",                       /* NAME           : Name of the memory region */
        RESETCTRLADDR,                     /* ADDRPHYS       : Physical address */
        RESETCTRLADDR,                     /* ADDRDSPVIRT    : DSP virtual address */
        (Uint32) -1,                       /* ADDRGPPVIRT    : GPP virtual address (if known) */
        RESETCTRLSIZE,                     /* SIZE           : Size of the memory region */
        TRUE,                              /* SHARED         : Shared access memory? */
        FALSE,                             /* SYNCD          : Synchornized? */
    },
    {
        CODEENTRYID,                       /* ENTRY          : Entry number */
        "DDR2",                            /* NAME           : Name of the memory region */
        CODEMEMORYADDR,                    /* ADDRPHYS       : Physical address */
        CODEMEMORYADDR,                    /* ADDRDSPVIRT    : DSP virtual address */
        (Uint32) -1,                       /* ADDRGPPVIRT    : GPP virtual address (if known) */
        CODEMEMORYSIZE,                    /* SIZE           : Size of the memory region */
        TRUE,                              /* SHARED         : Shared access memory? */
        FALSE,                             /* SYNCD          : Synchornized? */
    },
    {
        SHAREDENTRYID0,                   /* ENTRY          : Entry number */
        "DSPLINKMEM",                     /* NAME           : Name of the memory region */
        SHAREDMEMORYADDR0,                /* ADDRPHYS       : Physical address */
        SHAREDMEMORYADDR0,                /* ADDRDSPVIRT    : DSP virtual address */
       (Uint32) -1,                      /* ADDRGPPVIRT    : GPP virtual address (if known) */
        SHAREDMEMORYSIZE0,                /* SIZE           : Size of the memory region */
        TRUE,                             /* SHARED         : Shared access memory? */
        FALSE,                            /* SYNCD          : Synchornized? */
    },
    {
        SHAREDENTRYID1,                   /* ENTRY          : Entry number */
        "DSPLINKMEM1",                     /* NAME           : Name of the memory region */
        SHAREDMEMORYADDR1,                /* ADDRPHYS       : Physical address */
        SHAREDMEMORYADDR1,                /* ADDRDSPVIRT    : DSP virtual address */
        (Uint32) -1,                      /* ADDRGPPVIRT    : GPP virtual address (if known) */
        SHAREDMEMORYSIZE1,                /* SIZE           : Size of the memory region */
        TRUE,                             /* SHARED         : Shared access memory? */
        FALSE,                            /* SYNCD          : Synchornized? */
    },
    {
        POOLENTRYID,                       /* ENTRY          : Entry number */
        "POOLMEM",                         /* NAME           : Name of the memory region */
        POOLMEMORYADDR,                    /* ADDRPHYS       : Physical address */
        POOLMEMORYADDR,                    /* ADDRDSPVIRT    : DSP virtual address */
        (Uint32) -1,                       /* ADDRGPPVIRT    : GPP virtual address (if known) */
        POOLMEMORYSIZE,                    /* SIZE           : Size of the memory region */
        TRUE,                              /* SHARED         : Shared access memory? Logically */
        FALSE,                             /* SYNCD          : Synchornized? */
    },
    {
        5,                     /* ENTRY          : Entry number */
        "DSPIRAM",             /* NAME           : Name of the memory region */
        0x11800000,            /* ADDRPHYS       : Physical address */
        0x11800000,            /* ADDRDSPVIRT    : DSP virtual address */
        (Uint32) -1,           /* ADDRGPPVIRT    : GPP virtual address (if known) */
        0x10000,               /* SIZE           : Size of the memory region */
        TRUE,                  /* SHARED         : Shared access memory? */
        FALSE,                 /* SYNCD          : Synchornized? */
    },
    {
        6,                     /* ENTRY          : Entry number */
        "DSPL1DRAM",           /* NAME           : Name of the memory region */
        0x11F04000,            /* ADDRPHYS       : Physical address */
        0x11F04000,            /* ADDRDSPVIRT    : DSP virtual address */
        (Uint32) -1,           /* ADDRGPPVIRT    : GPP virtual address (if known) */
        0xC000,                /* SIZE           : Size of the memory region */
        TRUE,                  /* SHARED         : Shared access memory? */
        FALSE,                 /* SYNCD          : Synchornized? */
    },
   {
       VECSENTRYID,                     /* ENTRY          : Entry number */
       "VECSENTRYID",           /* NAME           : Name of the memory region */
       VECSADDR,            /* ADDRPHYS       : Physical address */
       VECSADDR,            /* ADDRDSPVIRT    : DSP virtual address */
       (Uint32) -1,           /* ADDRGPPVIRT    : GPP virtual address (if known) */
       VECSSIZE,                /* SIZE           : Size of the memory region */
       FALSE,                  /* SHARED         : Shared access memory? */
       FALSE,                 /* SYNCD          : Synchornized? */
    },
    {
       VPSSENTRYID,                     /* ENTRY          : Entry number */
       "VPSSENTRYID",           /* NAME           : Name of the memory region */
       VPSSADDR,            /* ADDRPHYS       : Physical address */
       VPSSADDR,            /* ADDRDSPVIRT    : DSP virtual address */
       (Uint32) -1,           /* ADDRGPPVIRT    : GPP virtual address (if known) */
       VPSSSIZE,                /* SIZE           : Size of the memory region */
       FALSE,                  /* SHARED         : Shared access memory? */
       FALSE,                 /* SYNCD          : Synchornized? */
    },
    {
       DEBUGENTRYID,                     /* ENTRY          : Entry number */
       "DEBUGENTRYID",           /* NAME           : Name of the memory region */
       DEBUGADDR,            /* ADDRPHYS       : Physical address */
       DEBUGADDR,            /* ADDRDSPVIRT    : DSP virtual address */
       (Uint32) -1,           /* ADDRGPPVIRT    : GPP virtual address (if known) */
       DEBUGSIZE,                /* SIZE           : Size of the memory region */
       FALSE,                  /* SHARED         : Shared access memory? */
       FALSE,                 /* SYNCD          : Synchornized? */
    },
    //{
    //   POOL_MSGQ_ID,                     /* ENTRY          : Entry number */
    //   "POOL_MSGQ_ID",           /* NAME           : Name of the memory region */
    //   POOL_MSGQ_ADDR,            /* ADDRPHYS       : Physical address */
    //   POOL_MSGQ_ADDR,            /* ADDRDSPVIRT    : DSP virtual address */
    //   (Uint32) -1,           /* ADDRGPPVIRT    : GPP virtual address (if known) */
    //   POOL_MSGQ_SIZE,                /* SIZE           : Size of the memory region */
    //   TRUE,                  /* SHARED         : Shared access memory? */
    //   FALSE,                 /* SYNCD          : Synchornized? */
    //},
} ;
