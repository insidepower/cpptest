#include <stdio.h>
#include <assert.h>
#include "MemDebug.h"

#define FID MAIN_C


//#define TEST_LINK_LIST
//#define TEST_NAME
//#define TEST_FREE
#define TEST_FREE_FENCE
//#define TEST_MEMCPY
//#define TEST_ARRAY_DOUBLE
//#define TEST_MARK

//#define TEST_FREE_ARRAY
#define TEST_FREE_MALLOC

unsigned char * initData(int size)
{
   int i=0;
   unsigned char * myspace1 = CROP_MALLOC(size, "myspace1");

   CROP_MARK(myspace1, size, "myspace1");
   for(;i<size;i++)
   {
      myspace1[i]=i;
   }
   //crop_memPrintData(pData-2*FENCE_TOP, size);
   return myspace1;
}

int main(void)
{
   unsigned char * myspace1 = initData(50);
   unsigned char * myspace2 = CROP_MALLOC(30, "myspace2");
   unsigned char * myspace3 = CROP_MALLOC(30, "myspace3");
   unsigned char myspace4[30];
   CROP_MARRAY(myspace4, 30, "myspace4");
   unsigned char * myspace5 = CROP_MALLOC(30, "myspace5");
   unsigned char * myspace6 = CROP_MALLOC(30, "myspace6");
   unsigned char * myspace7 = CROP_MALLOC(30, "myspace7");
   unsigned char * myspace8 = CROP_MALLOC(30, "myspace8");


#ifdef TEST_LINK_LIST
   crop_memPrintTable();
   CROP_FREE_ARR(myspace4, "myspace4");
   crop_memPrintTable();
   CROP_FREE(myspace2, "myspace2");
   crop_memPrintTable();
   CROP_FREE(myspace6, "myspace6");
   crop_memPrintTable();
   CROP_FREE(myspace7, "myspace7");
   crop_memPrintTable();
   CROP_FREE(myspace3, "myspace3");
   crop_memPrintTable();
   CROP_FREE(myspace8, "myspace8");
   crop_memPrintTable();
   CROP_FREE(myspace1, "myspace1");
   crop_memPrintTable();
   CROP_FREE(myspace5, "myspace5");
   crop_memPrintTable();
   unsigned char * myspace9 = CROP_MALLOC(50, "myspace9");
   crop_memPrintTable();
   CROP_FREE(myspace9, "myspace9");
   crop_memPrintTable();
#endif

#ifdef TEST_NAME
   crop_memPrintTable();
   CROP_FREE_ARR(myspace4, "myspace4");
   crop_memPrintTable();
   CROP_FREE(myspace2, "myspac34");
   crop_memPrintTable();
   CROP_FREE(myspace6, "myspace6");
   crop_memPrintTable();
   crop_memPrintTable();
   crop_memPrintTable();
   CROP_FREE(myspace7, "myspace7");
   crop_memPrintTable();
   CROP_FREE(myspace3, "myspace3");
   crop_memPrintTable();
#endif

#ifdef TEST_FREE
   crop_memPrintTable();
   CROP_FREE_ARR(myspace4, "myspace4");
   crop_memPrintTable();
   CROP_FREE(myspace2, "myspace2");
   crop_memPrintTable();
   CROP_FREE(myspace6, "myspace6");
   crop_memPrintTable();
   crop_memPrintTable();
   crop_memPrintTable();
   CROP_FREE(myspace7, "myspace7");
   crop_memPrintTable();
   CROP_FREE(myspace3, "myspace3");
   crop_memPrintTable();
#ifdef TEST_FREE_ARRAY
   CROP_FREE_ARR(myspace4, "myspace4"); //error:
#endif
#ifdef TEST_FREE_MALLOC
   CROP_FREE(myspace2, "myspace2"); //error: this will try to free myspace8
#endif
#endif

#ifdef TEST_FREE_FENCE
   crop_memPrintTable();
   CROP_FREE_ARR(myspace4, "myspace4");
   crop_memPrintTable();
   CROP_FREE(myspace2, "myspace2");
   crop_memPrintTable();
   CROP_FREE(myspace6, "myspace6");
   crop_memPrintTable();
   myspace7[30]=0xAA; //error: writing to fence, last byte
   //myspace7[32]=0xAA; //error: writing to fence, last+2 byte
   //myspace7[34]=0xAA; //error: writing to fence, last+2 byte
   //*(myspace7-8)=0xAA; //error: writing to fence
   unsigned char * myspace9 = CROP_MALLOC(50, "myspace9");
   CROP_FREE(myspace7, "myspace7");
   crop_memPrintTable();
   CROP_FREE(myspace3, "myspace3");
   crop_memPrintTable();
#endif

#ifdef TEST_MEMCPY
   CROP_MEMCPY(myspace2, myspace1, 20, "myspace2");
   //crop_memPrintTable();
   CROP_MEMCPY(myspace3, myspace1, 30, "myspace3");
   //crop_memPrintTable();
   //CROP_MEMCPY(myspace4, myspace1, 31, "myspace4");//error
   //CROP_MEMCPY(myspace5+10, myspace1, 30, "myspace5");//error
   //CROP_MEMCPY(myspace6-10, myspace1, 30, "myspace6");//error
   //crop_memPrintTable();
#endif

#ifdef TEST_ARRAY_DOUBLE
   CROP_MARRAY(myspace4, 30, "myspace4");
#endif

#ifdef TEST_MARK
   CROP_MARK(myspace4, 30, "myspace4");
   //CROP_MARK(myspace4+10, 30, "myspace4");
   CROP_MARK(myspace4-10, 30, "myspace4");
#endif
   printf("return from main\n");
   return 0;
}
