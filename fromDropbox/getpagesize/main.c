#include <stdio.h>

int main()
{
   int myshift=1ULL;
  int i;
  for (i = 11; i < 15; ++i) {
    if (getpagesize() <= 1 << i) {
      break;
    }
  }
  printf("%i\n", i);
  printf("%X\n", myshift<<31);
  return 0;
}
