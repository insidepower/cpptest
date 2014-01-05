#include <stdio.h>
#include "ll.h"

#define CROP_MALLOC(A,B) malloc(A)
#define CROP_FREE(A,B) free(A)

//----------------------------------------------------------------------------
// ll.cpp                                                                  
//----------------------------------------------------------------------------

//## package Buffer 

//## class ll 


ll::ll() {
    //#[ operation ll() 
    pNext=NULL;
    //#]
}

ll::~ll() {
}

void ll::addNode(unsigned char * p_dataUnit) {
    //#[ operation addNode(DataUnit *) 
    ll ** pTemp=&pNext;
    ll * pNew = (ll *)CROP_MALLOC(sizeof(ll),"pNew");
    while(*pTemp!=NULL)
    {
    	*pTemp=(*pTemp)->pNext;
    }
    pNew->pNext=NULL;
    pNew->myDataUnit=p_dataUnit;
    *pTemp=pNew;
    //#]
}

void ll::init_ll(ll ** pllHead) {
    //#[ operation init_ll(ll **) 
    ll * pHead=(ll *)CROP_MALLOC(sizeof(ll),"pHead");
    pHead->pNext=NULL;
    *pllHead=pHead;
    //#]
}

void ll::printll() {
    //#[ operation printll() 
    ll * pllTemp = pNext;
    printf("BufSB:0x%x,",pllTemp);
    if (pllTemp != NULL)
    {
    	printf("%p,",pllTemp);
    	pllTemp=pllTemp->pNext;
    }
    printf("\n");
    //#]
}

unsigned char * ll::removeNode() {
    //#[ operation removeNode() 
    unsigned char * ptrDataUnit;
    //ll * pTemp=pllHead->pNext;
    //pllHead->pNext=pTemp->pNext;
    //mydata=pTemp->mydataUnit;
    //free(pTemp);
    //return mydata;
    
    ll * pTemp=pNext;
    pNext=pTemp->pNext;
    ptrDataUnit=pTemp->myDataUnit;
    assert(pTemp);
    CROP_FREE(pTemp, "pNew");
    return ptrDataUnit;
    //#]
}



/*********************************************************************
	File Path	: MAC/MAC/ll.cpp
*********************************************************************/
