#include <stdio.h>

int main()
{
   unsigned char arBitCount[256];
   int i=20;
   for(i=0;i<256;i++)
   {
      //int temp=i;
      //int bitcount=0;
      //int j;
      //for(j=0;j<8;j++)
      //{
      //   printf("temp&j>>j=%d,j=%d\n",(temp&j)>>j, j);
      //   bitcount+=(temp&j)>>j;
      //}
      //printf("%d,%d,%d,%d,%d,%d,%d,%d\n",
      //            (i&1),(i&2)>>1,(i&4)>>2,(i&8)>>3,(i&16)>>4,(i&32)>>5,(i&64)>>6,(i&128)>>7);
      arBitCount[i]=((i&1))+((i&2)>>1)+((i&4)>>2)+((i&8)>>3)+
         ((i&16)>>4)+((i&32)>>5)+((i&64)>>6)+((i&128)>>7);
         printf("%2X, ", arBitCount[i]);
      //if(0==(i+1%10)&&i>0)
		if(((i+1) % 10 == 0) && i>0)
      {
         printf("\n");
      }
   }
   printf("\n");
}
