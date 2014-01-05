#include <stdio.h>

int main(void)
{
   int a=5;
   long addrA=0;
   printf("a=0x%X\n", &a);
   addrA=virt_to_phys(&a);
   printf("A=%lX\n",addrA);
}
