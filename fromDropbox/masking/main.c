#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEG_CRC_LEN 2
#define ACK_RFCS_MASK	0x07FF	//LSB 11 bits

typedef struct data_tag
{
   unsigned char data[100];
   short seg;
}mydata;

int main(void)
{
   mydata mydataa;
   mydataa.seg=0xFFF;
   unsigned char * pdata= (unsigned char *) malloc(sizeof(mydata));
   memcpy(pdata, &mydataa, sizeof(mydata));

   printf("seg=%d\n", mydataa.seg);
   printf("seg=%d\n", ((mydata *) pdata)->seg);
   printf("seg=%d\n", (*((short *) (pdata+sizeof(mydata)-SEG_CRC_LEN))&ACK_RFCS_MASK));
   return 0;

}

/*
 *seg=4095
seg=4095
seg=2047
               pACK->rfcs=(*((short *) (pMsg->data+pMsg->data_len-SEG_CRC_LEN)))\
                          &ACK_RFCS_MASK;
 */
