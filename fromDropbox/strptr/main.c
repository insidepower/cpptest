#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    char *pchar = "aaaaa";
	 char * pTemp = pchar;
	 int i;
    printf("%x\n", pchar);
    pchar = "vvvvvvvvvvvvv";
    printf("%x\n", pchar);
    //pchar[1] = 'c';
	 unsigned char *pchar2="c";
	 //strncpy(&pchar[2], pchar2, 1);

    for(i= 0; i < 6+14; i++)
        //printf("%c", *((char*)(0x422870+i)));
        printf("%c", *(pTemp+i));
	 printf("\n");

}
