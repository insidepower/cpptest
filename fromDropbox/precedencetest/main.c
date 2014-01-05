#include <stdio.h>

typedef struct my_stat
{
   int a;
}my_stat;

int main(void)
{
   my_stat stat1;
   my_stat * p_stat;
   stat1.a=5;
   printf("1: %d\n", stat1.a);
   stat1.a++;
   printf("2: %d\n", stat1.a);
   p_stat=&stat1;
   p_stat->a++;
   printf("3: %d\n", stat1.a);

   return 0;

}
