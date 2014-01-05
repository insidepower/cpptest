#include <stdio.h>

int main(void)
{
   int i=0;
   for(;i<3; i++)
   {
      static int a=0;
      printf("a = %d\n", ++a);
   }
   return 0;
}
