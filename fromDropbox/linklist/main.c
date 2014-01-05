/* Link List
 * Based on first in first out 
 */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h> //free

typedef struct ll_tag
{
   struct ll_tag * pNext;
   char * ptrData;
   int len;
} ll;

ll * pllHead;
ll * pllTail;
int totalNode = 0;

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

int removeNode(void)
{
   assert(totalNode>0);
   totalNode--;
   if (totalNode == 0)
   {
      free(pllHead);
      pllHead = NULL;
      pllTail = NULL;
   }
   else
   {
      ll * pTemp = pllHead;
      pllHead = pllHead->pNext;
      free(pTemp);
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
	 printf("%d: ptrData (%s), len (%d) \n",totalNode-nTotalNode, 
	       pTemp->ptrData, pTemp->len);
	 pTemp=pTemp->pNext;
      }

      //process last node
	 printf("%d: ptrData (%s), len (%d) \n",totalNode-nTotalNode, pTemp->ptrData, pTemp->len);

   }
   else
   {
      printf("list is empty\n");
   }
   return 0;
}

static int index=0;
int fillNode()
{
   ll * newNode;
   newNode = (ll *) malloc(sizeof(ll));
   char * str;
   str = (char *) malloc(10);
   sprintf(str, "%d hello", index);
   //printf("%s\n", str);
   newNode->ptrData = str;
   newNode->len = index;
   ++index;

   addNode(newNode);
   return 0;
}

int main (void)
{
   //char str2[10];
   //sprintf(str2, "%d hello", index);
   //printf("%s\n", str2);
   //printf("index = %d\n", index);
   printf("sizeof(ll) = %d, sizeof(struct ll_tag *)=%d, sizeof(char *)=%d, sizeof(int)=%d\n", sizeof(ll), sizeof(struct ll_tag *), sizeof(char *), sizeof(int));
   fillNode();
   printf("added 1 node\n");
   traverselist();
   fillNode();
   fillNode();
   printf("added 2 node\n");
   traverselist();
   removeNode();
   printf("removed 1 node\n");
   traverselist();
   removeNode();
   printf("removed 1 node\n");
   traverselist();
   removeNode();
   printf("removed 1 node\n");
   traverselist();
   fillNode();
   printf("added 1 node\n");
   traverselist();
   removeNode();
   printf("removed 1 node\n");
   traverselist();
   fillNode();
   fillNode();
   printf("added 2 node\n");
   traverselist();
   removeNode();
   removeNode();
   printf("removed 2 node\n");
   traverselist();
   return 0;
}

