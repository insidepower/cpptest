#include <stdio.h>

#define ASSERT(expr) \
   if(expr)\
      NULL;\
   else\
      printf(#expr)
     

int main(void)
{
   int a=1;
   ASSERT(a==0);
}
