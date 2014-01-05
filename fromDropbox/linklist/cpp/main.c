#include <stdio.h>
#include "ll.h"

int main(void)
{
   ll pllHead;
   unsigned char * pch=(unsigned char *)malloc(10);
   pllHead.addNode(pch);
   pllHead.removeNode();
}
