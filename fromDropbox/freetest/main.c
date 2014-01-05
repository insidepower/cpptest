#include <stdlib.h>
#include <stdio.h>

int main(void)
{

   unsigned char * myA = (unsigned char *) malloc(10);
   unsigned char * myB = (unsigned char *) malloc(10);
   unsigned char * myC = (unsigned char *) malloc(10);
   
   printf("myA=%p; myB=%p; myC=%p\n", myA, myB, myC);
   free(myB);

   return 0;

}
