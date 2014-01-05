#include <stdio.h>

typedef struct
{
	unsigned char 	sl_1;   //Segment Length
	unsigned char 	sl_2:7, //Segment Length
					lsf:1;	//Last Segment Flag
}segCtrl;

int main(void)
{
   int myNum=0xFFFF;
   segCtrl myseg;
   myseg.sl_1=(unsigned char) (myNum & (0xFF>>1));
   myseg.sl_2=(unsigned char) (myNum >> 7);

   return 0;
}
