#include <stdio.h>
#define SIZE_96MB          0x6000000u 

#define  LINUXSIZE          (SIZE_96MB+0x100000u)
#define  RESETCTRLSIZE      0x400u
#define  CODEMEMORYSIZE     (0x2FFC00u+0x00900000u)
#define  SHAREDMEMORYSIZE0  0x5000u
#define  SHAREDMEMORYSIZE1  0xAB000u
#define  SHAREDMEMORYSIZE   (SHAREDMEMORYSIZE0+SHAREDMEMORYSIZE1)
#define  POOLMEMORYSIZE     0x00300000u
#define  DSPMEMORYSIZE0     0x0u
#define  TOTALMEMSIZE       (RESETCTRLSIZE+CODEMEMORYSIZE+SHAREDMEMORYSIZE+POOLMEMORYSIZE+DSPMEMORYSIZE0)

#define  LINUXADDR          0x80000000
#define  RESETCTRLADDR      (LINUXADDR+LINUXSIZE)
#define  CODEMEMORYADDR     (RESETCTRLADDR + RESETCTRLSIZE)
#define  SHAREDMEMORYADDR0  (CODEMEMORYADDR + CODEMEMORYSIZE)
#define  SHAREDMEMORYADDR1  (SHAREDMEMORYADDR0 + SHAREDMEMORYSIZE0)
#define  POOLMEMORYADDR     (SHAREDMEMORYADDR1 + SHAREDMEMORYSIZE1)
#define  DSPMEMORYADDR0     (POOLMEMORYADDR + POOLMEMORYSIZE)
#define  TOTALMEMADDR       (DSPMEMORYADDR0 + DSPMEMORYSIZE0)

#define MEM_MAP \
{\
   {"LINUX", LINUXADDR, LINUXSIZE},\
   {"RESET", RESETCTRLADDR, RESETCTRLSIZE},\
   {"CODE", CODEMEMORYADDR, CODEMEMORYSIZE},\
   {"SHARE", SHAREDMEMORYADDR0, SHAREDMEMORYSIZE},\
   {"POOL", POOLMEMORYADDR, POOLMEMORYSIZE},\
   {"DSPME", DSPMEMORYADDR0, DSPMEMORYSIZE0},\
   {"Total", TOTALMEMADDR, TOTALMEMSIZE},\
   {"VECS", TOTALMEMADDR, 0x800u},\
   {"VPSS", TOTALMEMADDR+0x800u, 0x10000u},\
   {"LAST", TOTALMEMADDR+0x800u+0x10000u, TOTALMEMSIZE+0x800+0x100000u}\
}

#define TOTAL_MEM_SEG 7

struct my_memory_map {
   char * name;
   unsigned int addr;
   unsigned int size;
}memory_array[]=MEM_MAP;

int main(void){
   int i =0;
   int size = sizeof(memory_array)/sizeof(*memory_array);
   for(;i<size;i++){
      printf("%10s, \t0x%-10X \t0x%-10X \t%-5d kB \t%5d MB\n", 
	    memory_array[i].name, 
	    memory_array[i].addr,
	    memory_array[i].size,
	    memory_array[i].size/1024,
	    memory_array[i].size/1024/1024
	    );
   }

   printf("sizeof memory_array %d %d %d\n", size, sizeof(memory_array), sizeof(*memory_array));
   return 0;
}
