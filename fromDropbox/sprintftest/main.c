#include <string.h>
#include <stdio.h>

int main(void)
{
   int a=10;
   char b[100];
   sprintf(&b[0], "harlo %d", a);
   printf("%s\n", &b[0]);

   return 0;
}
