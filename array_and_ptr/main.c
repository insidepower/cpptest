#include <stdio.h>
#include <string.h> //for memset

unsigned char myvar[50];

void myfunc(unsigned char * pch)
{
	unsigned char * pnew=pch;
	pnew[20]=20+50;
}

int main(void)
{
	memset(myvar, 0, 50);
	myvar[30]=30+50;

	myfunc(&myvar[0]);

	return 0;
}
