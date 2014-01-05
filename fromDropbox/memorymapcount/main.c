#include <stdio.h>
#include "mem.h"
#define SIZE_96MB          0x6000000u 
#define SIZE_64MB          0x4000000u 

//#define  LINUXSIZE          (SIZE_64MB+0x100000u)
#define  LINUXSIZE          (SIZE_64MB)
#define  SHAREDMEMORYSIZE   (SHAREDMEMORYSIZE0+SHAREDMEMORYSIZE1)
//#define  TOTALMEMSIZE       (RESETCTRLSIZE+CODEMEMORYSIZE+SHAREDMEMORYSIZE+POOLMEMORYSIZE+DSPMEMORYSIZE0)

#define  LINUXADDR          0x80000000
//#define  TOTALMEMADDR       (DSPMEMORYADDR0 + DSPMEMORYSIZE0)

int main(void){
   int i =0;
   int totalSize=LINUXSIZE;
   int size = sizeof(LINKCFG_memTable_00)/sizeof(*LINKCFG_memTable_00);
   printf("===============================================================\n");
   printf(" i: %10s, \t%-10s \t%-10s \n", "name", "physAddr", "size");
   printf("===============================================================\n");

   printf("  : %10s, \t0x%-10X \t0x%-10X \t%-5d kB \t%5d MB\n", 
	 "Linux", 
	 LINUXADDR,
	 LINUXSIZE,
	 LINUXSIZE/1024,
	 LINUXSIZE/1024/1024
	 );

   for(;i<size;i++){
      printf("%2d: %10s, \t0x%-10X \t0x%-10X \t%-5d kB \t%5d MB\n", 
	    LINKCFG_memTable_00[i].entry, 
	    LINKCFG_memTable_00[i].name, 
	    LINKCFG_memTable_00[i].physAddr,
	    LINKCFG_memTable_00[i].size,
	    LINKCFG_memTable_00[i].size/1024,
	    LINKCFG_memTable_00[i].size/1024/1024
	    );
      totalSize+=LINKCFG_memTable_00[i].size;
   }
   i--;
   printf("  : %10s, \t0x%-10X \t0x%-10X \t%-5d kB \t%5d MB\n", 
	 "Total", 
	 LINKCFG_memTable_00[i].physAddr+LINKCFG_memTable_00[i].size,
	 totalSize,
	 totalSize/1024,
	 totalSize/1024/1024
	 );
   printf("sizeof memory_array %d %d %d\n", size, sizeof(LINKCFG_memTable_00), sizeof(*LINKCFG_memTable_00));
   printf("sizeof DSPLINK SHMEM = (%X + %X ) = %X \n", SHAREDMEMORYSIZE0, SHAREDMEMORYSIZE1, SHAREDMEMORYSIZE0+SHAREDMEMORYSIZE1);
   return 0;
}
