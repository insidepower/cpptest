#include <stdio.h>
#include <stdlib.h>

/*==============================================================================
 ==  
initial: pHead->pNull;
addNode: pHead->pNew->pNull;
removeNode: pHead->pNull;

the initial(pHead) and last node(pNull) should be always there, even when no node
==============================================================================*/
typedef struct ll_tag
{
   struct ll_tag * pNext;
   int len;
   int * pData;
} ll;

ll pNull;

void init_ll(ll ** pllHead)
{
   ll * pHead = (ll *) malloc(sizeof(ll));

   pHead->pNext=&pNull;
   *pllHead=pHead;
}

ll * addNode(ll * pllHead)
{
   ll * pTemp=pllHead;
   ll * pNew = (ll *) malloc(sizeof(ll));
   while(pTemp->pNext!=&pNull)
   {
      pTemp=pTemp->pNext;
   }
   pNew->pNext=pTemp->pNext;
   pTemp->pNext=pNew;
}

void removeNode(ll * pllHead)
{
   ll * pTemp=pllHead->pNext;
   pllHead->pNext=pTemp->pNext;
   free(pTemp);
}

void printll(ll * pllHead)
{
   ll * pTemp = pllHead;
   int i=1;
   while(pTemp->pNext!=&pNull)
   {
      printf("%d: pTemp->len=%d\n", i++, pTemp->len);
      pTemp=pTemp->pNext;
   }
   printf("%d: pTemp->len=%d\n", i++, pTemp->len);
   printf("%d: pTemp->len=%d\n", i++, pTemp->pNext->len);
}

int main(void)
{
   ll * pA;
   int i=1;
   init_ll(&pA);
   ll * pNew = addNode(pA);
   pNew->len=i++;
   ll * pNew2 = addNode(pA);
   pNew2->len=i++;
   removeNode(pA);
   removeNode(pA);
   ll * pNew3 = addNode(pA);
   pNew3->len=i++;
   printll(pA);

   return 0;
}
