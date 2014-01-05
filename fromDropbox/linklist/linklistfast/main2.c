/*==============================================================================
==  INCLUDES
==============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct ll_tag
{
   struct ll_tag * pNext;
	int len;
} ll;


#define SPRINTF1(A,B) printf(A,B)
#define SPRINTF2(A,B,C) printf(A,B,C)
#define MEM_alloc(A,B,C) malloc(B)
#define ASSERT(A) assert(A)

void init_ll(ll ** pllHead);
ll *addNode(ll * pllHead);
void removeNode(ll * pllHead);

/*==============================================================================
==  GLOBAL VARIABLES
==============================================================================*/
ll g_pllNull;
static int totalCnt=0;

/*++++++++++++++++++++++++++++++< FUNCTION >++++++++++++++++++++++++++++++++++*/
/*==============================================================================
 ==  @ init_ll @
 ==
 ==  DESC: initialize link list
 ==  USAGE:
 ==  INPUTS:
 ==  OUTPUTS:
 ==  RETURN:
 ==  IMP NOTE:
==============================================================================*/
void init_ll(ll ** pllHead)
{
   ll * pHead = (ll *) MEM_alloc(DDR2, sizeof(ll), 0);

   //pHead->pNext=&g_pllNull;
   SPRINTF1("addNode:pllHead=%p",pHead);
   pHead->pNext=NULL;
	pHead->len=0;
   *pllHead=pHead;
}

/*==============================================================================
 ==  @ addNode @
 ==
 ==  DESC: add to the last node of link list
 ==  USAGE:
 ==  INPUTS:
 ==  OUTPUTS:
 ==  RETURN:
 ==  IMP NOTE:
==============================================================================*/
ll *addNode(ll * pllHead)
{
   ll * pTemp=pllHead;
   ll * pNew = (ll *) MEM_alloc(DDR2, sizeof(ll), 0);
   SPRINTF1("addNode:pllHead=%p",pllHead);
//   while(pTemp->pNext!=&g_pllNull)
   while(pTemp->pNext!=NULL)
   {
      SPRINTF1("addNode:pTemp->Next=%p",pTemp->pNext);
      pTemp=pTemp->pNext;
   }
   //pNew->pNext=pTemp->pNext;
   pNew->pNext=NULL;
   pTemp->pNext=pNew;
   ++totalCnt;
   SPRINTF2("addNode:pTemp->Next=%p,totalCnt=%d\n",pTemp->pNext,totalCnt);

   return pNew;
}

/*==============================================================================
 ==  @ removeNode @
 ==
 ==  DESC: remove the head of the link list
 ==  USAGE:
 ==  INPUTS:
 ==  OUTPUTS:
 ==  RETURN:
 ==  IMP NOTE:
==============================================================================*/
void removeNode(ll * pllHead)
{
   ll * pTemp=pllHead->pNext;
   SPRINTF2("removeNode:pllHead=%p,pNext=%p\n",pllHead,pTemp);
   ASSERT(pTemp!=NULL);
   --totalCnt;
   pllHead->pNext=pTemp->pNext;
   free(pTemp);
}

void printll(ll * pllHead)
{
   ll * pTemp = pllHead;
   int i=1;
   while(pTemp->pNext!=NULL)
   {
      printf("%d: pTemp->len=%d\n", i++, pTemp->len);
      pTemp=pTemp->pNext;
   }
   printf("%d: pTemp->len=%d\n", i++, pTemp->len);
}


int main(void)
{
   ll * pA;
   int i=1;
   init_ll(&pA);
   ll * pNew = addNode(pA);
   pNew->len=i++;
   removeNode(pA);
   ll * pNew2 = addNode(pA);
   pNew2->len=i++;
   removeNode(pA);
   ll * pNew3 = addNode(pA);
   pNew3->len=i++;
   printll(pA);

   return 0;
}

