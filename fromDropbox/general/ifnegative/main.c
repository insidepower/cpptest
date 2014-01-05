#include <stdio.h>

int main(void)
{
   if(0)
      printf("if 0\n");
   
   if(-1)
      printf("if -1\n");

   if(3)
      printf("if 3\n");

   return 0;
}

/*
result:
if -1
if 3
*/
