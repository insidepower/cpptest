#include <stdio.h>

/*
 * when store an integer 1 in the memory
 *
 * (Little Endian)
    higher memory
          ----->
    +----+----+----+----+
    |0x01|0x00|0x00|0x00|
    +----+----+----+----+
    A
    |
   &x
 *
 *
 * (Big Endian)
    higher memory
          ----->
    +----+----+----+----+
    |0x00|0x00|0x00|0x01|
    +----+----+----+----+
    A
    |
   &x
 *
 * */

int main(void){
  int x = 1;

  char *y = (char*)&x;

  if ( '1' == *y+'0'){
	  printf("little endian.\n");
  } else if ( '0' == *y+'0'){
	  printf("big endian.\n");
  }

  return 0;
}
