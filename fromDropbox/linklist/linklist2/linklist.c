/* Link List
 * Based on first in first out 
 */
#include "linklist.h"
#include "myAssert.h"

#ifndef TI_DSP
#define MEM_valloc((A), (B), (C), (D)) \
   malloc(B)
#define MEM_free((A), (B), (C)) \
   free(B)
#endif //TI_DSP

/* global variable */
static ll * pllHead;
static ll * pllTail;
static int totalNode = 0;

int getTotalNode(void)
{
   return totalNode;
}

int addNode(ll * newNode)
{
   if(totalNode == 0)
   {
      pllHead=newNode;
      pllTail=pllHead;
   }
   else
   {
      pllTail->pNext=newNode;
      pllTail = newNode;
   }
   totalNode++;
   return 0;
}

int removeNode(unsigned char * pchData, int * nLen)
{
   assert(totalNode>0);
   totalNode--;
   if (totalNode == 0)
   {
      pchData=pllHead->pchData;
      nLen=pllHead->len;
      memset(pllHead, sizeof(ll), GARBAGE);
      MEM_free(DDR2, pllHead, sizeof(ll));
      pllHead = NULL;
      pllTail = NULL;
   }
   else
   {
      ll * pTemp = pllHead;
      pllHead = pllHead->pNext;
      memset(pTemp, sizeof(ll), GARBAGE);
      MEM_free(DDR2, pTemp, sizeof(ll));
   }
   return 0;
}

int traverselist(void)
{
   if(totalNode > 0)
   {
      ll * pTemp = pllHead;
      int nTotalNode = totalNode;

      //if there are 2 or more node, continue
      while((nTotalNode--) >= 2)
      {
	 //	 printf("%d: pchData (%s), len (%d) \n",totalNode-nTotalNode, 
	 //pTemp->pchData, pTemp->len);
	 pTemp=pTemp->pNext;
      }

      //process last node
//	 printf("%d: pchData (%s), len (%d) \n",totalNode-nTotalNode, pTemp->pchData, pTemp->len);

   }
   else
   {
//      printf("list is empty\n");
   }
   return 0;
}

/* for unit testing only */
static int index=0;
int fillNode()
{
   ll * newNode;
   unsigned char * str;
   newNode = (ll *) MEM_valloc(DDR2, sizeof(ll), 0, GARBAGE);
   str = (char *) MEM_valloc(DDR2, 10, 0, GARBAGE);
   //sprintf(str, "%d hello", index);
   //printf("%s\n", str);
   newNode->pchData = str;
   newNode->len = index;
   ++index;

   //addNode(newNode);
   return 0;
}

/* for unit testing only */
int main (void)
{
   unsigned char * pchData;
   int len;
   //char str2[10];
   //sprintf(str2, "%d hello", index);
   //printf("%s\n", str2);
   //printf("index = %d\n", index);
   //printf("sizeof(ll) = %d\n", sizeof(ll));
   fillNode();
//   printf("added 1 node\n");
   traverselist();
   fillNode();
   fillNode();
//   printf("added 2 node\n");
   traverselist();
   removeNode(pchData, &len);
//   printf("removed 1 node\n");
   traverselist();
   removeNode(pchData, &len);
//   printf("removed 1 node\n");
   traverselist();
   removeNode(pchData, &len);
//   printf("removed 1 node\n");
   traverselist();
   fillNode();
//   printf("added 1 node\n");
   traverselist();
   removeNode(pchData, &len);
//   printf("removed 1 node\n");
   traverselist();
   fillNode();
   fillNode();
//   printf("added 2 node\n");
   traverselist();
   removeNode(pchData, &len);
   removeNode(pchData, &len);
//   printf("removed 2 node\n");
   traverselist();
   return 0;
}
