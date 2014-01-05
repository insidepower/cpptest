#include <stdio.h>

#define MY_BITSHIFT 7
#define IRQ52_PRIORITY_SHIFT (16)
#define IRQ55_PRIORITY_SHIFT (28)

int main(void)
{
unsigned int value=0;
unsigned int myvar = 0;
myvar |= (1<<5) | (6<<MY_BITSHIFT);
value |= (6<<IRQ52_PRIORITY_SHIFT) | (5<<IRQ55_PRIORITY_SHIFT);
printf("myvar 0x%X\n", myvar);
printf("value 0x%X\n", value);
return 0;
}
