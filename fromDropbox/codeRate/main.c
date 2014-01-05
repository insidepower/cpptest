#include <stdio.h>

//unsigned char arLastBlk[8][6]=
//{
//289,121,0,0,0,0,
//324,144,361,169,0,0,
//400,196,441,225,484,256,
//529,289,576,324,0,0,
//625,361,676,400,0,0,
//729,441,784,484,0,0,
//841,529,0,0,0,0,
//900,576,961,625,0,0
//}
//

//bit can be sent corresponding to arRmnBit[]
unsigned int arBitToSend2[15]=
{121,144,169,196,225,256,289,324,361,400,441,484,529,576,625};
//remaining bits after dividing by 1024
unsigned int arRmnBit2[15]=
{289,324,361,400,441,484,529,576,625,676,729,784,841,900,961};


#define RAW_BIT_1024    676

int main()
{
   int bitToSend[]={1029,1200,2000,1500};
   int i;

//   for(i=0;i<3;i++)
//   {
//      int actualBitToSend=0;
//      actualBitToSend+=bitToSend[i]/1024;
//      int index = (bitToSend[i]%1024)%100-2;
//      while(index<48)
//      {
//         if()}
//   }

   for(i=0;i<sizeof(bitToSend)/sizeof(int);i++)
   {
      int actualBitToSend=0;
      int j=14;

      actualBitToSend += (bitToSend[i]/1024)*RAW_BIT_1024;
      printf("%d:\tbitToSend=%d, actualBitToSend=%d, bitToSend/1024=%d\n", 
            i, bitToSend[i], actualBitToSend, bitToSend[i]/1024);

      for(j=14;j>=0;j--)
      {
         //printf("j=%d",j);
         if((bitToSend[i]%1024)>arRmnBit2[j])
         {
            actualBitToSend += arBitToSend2[j];
            printf("actualBitToSend=%d, ActualRemainingBit=%d, mappedRemainingBit=%d, bitToSend=%d\n",
                  actualBitToSend, bitToSend[i]%1024, arRmnBit2[j], arBitToSend2[j]);
            break;
         }
      }

      if(j==-1)
      {
         //no raw data can be sent in the last block
         printf("j=0: actualBitToSend=%d, remainingBit=%d, bitToSend=%d\n",
               actualBitToSend, bitToSend[i]%1024, arRmnBit2[j]);
      }
      printf("\n");
   }

   return 0;
}
