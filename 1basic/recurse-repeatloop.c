#include <stdio.h>

void count_to_ten ( int count )
{
	printf("count is %d\n", count);
       if ( count < 10 )   
       {
           count_to_ten( count + 1 );
       }
}

int main()
{
  count_to_ten ( 0 ); 
}
