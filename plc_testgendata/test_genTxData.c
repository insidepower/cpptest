#include "crc16.h"
#include "crc32.h"
#include "test_genTxData.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef INSTRUCTION
gcc -o test_genTxData test_genTxData.c crc16.c crc16.h crc32.c crc32.h
#endif

#define HTONS(A) ((((unsigned short)(A) & 0xff00) >> 8) | \
                 (((unsigned short)(A) & 0x00ff) << 8))
#define HTONL(A) ((((unsigned int)(A) & 0xff000000) >> 24) | \
                 (((unsigned int)(A) & 0x00ff0000) >> 8)  | \
                 (((unsigned int)(A) & 0x0000ff00) << 8)  | \
                 (((unsigned int)(A) & 0x000000ff) << 24))

#define PRINT(A,B) fprintf(fp,A,B)
#define PRINT0(A) fprintf(fp,A)
#define PRINT1(A,B) fprintf(fp,A,B)

FILE * fp=NULL;
void print(unsigned char * p_data, int p_length);
void genData(
      unsigned char ** par,
      int arSize,
      int arSizeFirst,
      int arSizeLast,
      int dataSizeFirst,
      int dataSizeLast,
      unsigned char * pStr);

int main(void)
{
   int i;
   time_t myTime=time(NULL);
   char * timeStamp = asctime(localtime(&myTime));

   fp=fopen("test_genTxDataLog", "a+");
   PRINT0("=================================\n");
   PRINT("Date = %s", timeStamp);
   PRINT0("=================================\n");

   //--------ceReq---------//
   unsigned int crc32=compute_crc(&arData[5+12], 6);
   printf("arData[5+12]=%d, crc32=0x%X\n",arData[5+12], crc32);
   crc32=HTONL(crc32);
   memcpy(&arData[23], &crc32, sizeof(int));
   unsigned short crcFCS=crc16(&arData[0], sizeof(arData)/sizeof(char)-2);
   printf("crcFCS=0x%X\n", crcFCS);
   crcFCS=HTONS(crcFCS);
   memcpy(&arData[sizeof(arData)/sizeof(char)-2], &crcFCS, 2);
   print(&arData[0], sizeof(arData)/sizeof(char));


   //--------segmented data----------//
   unsigned char * pData = malloc(SYM40_RAWDATA*2+LAST_RAWDATA_LEN);
   memcpy(pData, &arSegData1[5+12], SYM40_RAWDATA);
   memcpy(pData+SYM40_RAWDATA, &arSegData2[5+12], SYM40_RAWDATA);
   memcpy(pData+SYM40_RAWDATA*2, &arSegData3[5+12], LAST_RAWDATA_LEN);
   unsigned char *pTemp2=&arSegData3[5+12+LAST_RAWDATA_LEN];
   printf("crc32(segmented)b4=0x%x,0x%X,0x%X,0x%X\n",pTemp2[0],pTemp2[1],pTemp2[2],pTemp2[3]);
   crc32=compute_crc(pData, SYM40_RAWDATA*2+LAST_RAWDATA_LEN);
   printf("crc32(segmented)=0x%X\n",crc32);
   crc32=HTONL(crc32);
   memcpy(&arSegData3[5+12+LAST_RAWDATA_LEN], &crc32, sizeof(int));

   //---crc16---//
   crcFCS=crc16(&arSegData1[0], sizeof(arSegData1)/sizeof(char)-2);
   printf("crcFCS=0x%X\n", crcFCS);
   crcFCS=HTONS(crcFCS);
   memcpy(&arData[sizeof(arSegData1)/sizeof(char)-2], &crcFCS, 2);
   crcFCS=crc16(&arSegData2[0], sizeof(arSegData2)/sizeof(char)-2);
   printf("crcFCS=0x%X\n", crcFCS);
   crcFCS=HTONS(crcFCS);
   memcpy(&arData[sizeof(arSegData2)/sizeof(char)-2], &crcFCS, 2);
   crcFCS=crc16(&arSegData3[0], sizeof(arSegData3)/sizeof(char)-2);
   printf("SegmentData:crcFCS=0x%X\n", crcFCS);
   crcFCS=HTONS(crcFCS);
   memcpy(&arData[sizeof(arSegData3)/sizeof(char)-2], &crcFCS, 2);

   //---log to file---//
   PRINT0("\n\n//---arSegData1---//\n");
   print(&arSegData1[0], sizeof(arSegData1)/sizeof(char));
   PRINT0("\n\n//---arSegData2---//\n");
   print(&arSegData2[0], sizeof(arSegData2)/sizeof(char));
   PRINT0("\n\n//---arSegData3---//\n");
   print(&arSegData3[0], sizeof(arSegData3)/sizeof(char));

 genData(
         parSegData,
         sizeof(parSegData)/sizeof(char *),
         sizeof(arSegData1)/sizeof(char),
         sizeof(arSegData3)/sizeof(char),
         SYM40_RAWDATA,
         LAST_RAWDATA_LEN,
         "arSegData"
         );

   //---arp req---//
   //unsigned char * pArpReq = malloc(SYM40_RAWDATA+LAST_RAWAPRREQ_LEN);
   int j;
   int arSize=sizeof(parArpData)/sizeof(char *);
   int arSizeFirst=sizeof(arArpData1)/sizeof(char);
   int arSizeLast=sizeof(arArpData2)/sizeof(char);
   int dataSizeFirst=SYM40_ROBO_LEN;
   int dataSizeLast=LAST_RAWAPRREQ_LEN;
   int dataSize=dataSizeFirst;
   unsigned char * pArpReq = malloc(arSizeFirst+arSizeLast);
   unsigned char * pOriginal=pArpReq;
   unsigned char * pTemp=pOriginal;
   unsigned char ** par=parArpData;
   for(j=0;j<arSize;j++)
   {
      if(j==arSize-1)
      {
         dataSize=dataSizeLast;
      }
      memcpy(pTemp, par[j]+(5+12), dataSize);
      pTemp+=dataSize;
   }
   --j;
   pTemp=pOriginal;
   crc32=compute_crc(pTemp, dataSizeFirst*(arSize-1)+dataSizeLast);
   printf("crc32=0x%X\n",crc32);
   crc32=HTONL(crc32);
   memcpy(par[j]+(5+12)+dataSizeLast, &crc32, sizeof(int));

   //---crc16---//
   dataSizeFirst=arSizeFirst;
   dataSizeLast=arSizeLast;
   dataSize=dataSizeFirst;
   for(j=0;j<arSize;j++)
   {
      if(j==arSize-1)
      {
         dataSize=dataSizeLast;
      }
      crcFCS=crc16(par[j], dataSize-2);
      printf("crcFCS=0x%X\n", crcFCS);
      crcFCS=HTONS(crcFCS);
      memcpy(par[j]+dataSize-2, &crcFCS, 2);
   }

   //---log to file---//
   dataSizeFirst=arSizeFirst;
   dataSizeLast=arSizeLast;
   dataSize=dataSizeFirst;
   for(j=0;j<arSize;j++)
   {
      if(j==arSize-1)
      {
         dataSize=dataSizeLast;
      }
      PRINT1("\n\n//---arArpData%d---//\n",j);
      print(par[j], dataSize);
   }

   //---ce resp---//
   //genData(
   //      parArpData,
   //      sizeof(parArpData)/sizeof(char *),
   //      sizeof(arArpData1)/sizeof(char),
   //      sizeof(arArpData2)/sizeof(char),
   //      SYM40_ROBO_LEN,
   //      LAST_RAWAPRREQ_LEN,
   //      "arArpData"
   //      );

   genData(
         parCeResp,
         sizeof(parCeResp)/sizeof(char *),
         0,
         sizeof(arCeResp1)/sizeof(char),
         0,
         LAST_CERESP_LEN,
         "arCeResp"
         );
   return 0;
}

void genData(
      unsigned char ** par,
      int arSize,
      int arSizeFirst,
      int arSizeLast,
      int dataSizeFirst,
      int dataSizeLast,
      unsigned char * pStr)
{
   int j=0;
   unsigned char * pchData = malloc(arSizeFirst+arSizeLast);
   int dataSize=dataSizeFirst;
   unsigned char * pOriginal=pchData;
   unsigned char * pTemp=pOriginal;
   unsigned int crc32=0;
   unsigned short crcFCS=0;
   time_t myTime=time(NULL);
   char * timeStamp = asctime(localtime(&myTime));

   for(j=0;j<arSize;j++)
   {
      if(j==arSize-1)
      {
         dataSize=dataSizeLast;
      }
      memcpy(pTemp, par[j]+(5+12), dataSize);
      pTemp+=dataSize;
   }
   --j;
   pTemp=pOriginal;
   unsigned char * pCopy=par[j]+(5+12)+dataSizeLast;
   printf("crc32(%s)b4=0x%x,0x%X,0x%X,0x%X\n",pStr, pCopy[0],pCopy[1],pCopy[2],pCopy[3]);
   crc32=compute_crc(pTemp, dataSizeFirst*(arSize-1)+dataSizeLast);
   printf("crc32(%s)=0x%X\n",pStr, crc32);
   crc32=HTONL(crc32);
   memcpy(pCopy, &crc32, sizeof(int));

   //---crc16---//
   dataSizeFirst=arSizeFirst;
   dataSizeLast=arSizeLast;
   dataSize=dataSizeFirst;
   for(j=0;j<arSize;j++)
   {
      if(j==arSize-1)
      {
         dataSize=dataSizeLast;
      }
      crcFCS=crc16(par[j], dataSize-2);
      printf("crcFCS=0x%X\n", crcFCS);
      crcFCS=HTONS(crcFCS);
      memcpy(par[j]+dataSize-2, &crcFCS, 2);
   }

   //---log to file---//
   dataSizeFirst=arSizeFirst;
   dataSizeLast=arSizeLast;
   dataSize=dataSizeFirst;
   for(j=0;j<arSize;j++)
   {
      if(j==arSize-1)
      {
         dataSize=dataSizeLast;
      }
      PRINT1("\n\n//---%s",pStr);
      PRINT1("%d---//\n",j);
      print(par[j], dataSize);
   }
   fflush(fp);
}

void print(unsigned char * p_data, int p_length) {
    int i = 0;
    unsigned char * ptrTemp = p_data;
   
    PRINT0("{\n");
    if(10 > p_length)
    {
       for(;i<p_length; i++) 
       {
          PRINT("0x%-2X, ", ptrTemp[i]);
       }
       PRINT0("\n");
    }
    else
    {
    	for(;i<10; i++) 
        {
          PRINT("0x%-2X, ", ptrTemp[i]);
        }
    	for (;i<p_length; i++)
    	{
    	   //if(0==i%10) PRINT("\n           ");
    	   if(0==i%10) PRINT0("\n");
    	   PRINT("0x%-2X, ", ptrTemp[i]);
    	}
    	PRINT0("\n");
    }
    PRINT0("};\n");
}

