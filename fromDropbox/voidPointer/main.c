#include <stdio.h>

int main(void)
{
   void * myVoidPtr;
   int myvar = 5;
   myVoidPtr = &myvar;

   printf("%p\n", myVoidPtr);
   printf("%d\n", *((int *) myVoidPtr));
   return 0;
}
