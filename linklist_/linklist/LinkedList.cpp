#include "LinkedList.h"
//#define NDEBUG   	//turn on to disable assertion
#include "assert.h"

/**********************************************************
 *   addNode
 *   
 *   Description:
 *   Add new node to the tail of LinkedList
 *********************************************************/
template <class pNodeType> void LinkedList::addNode(pNodeType * pNode)
{    
    totalNode++;
    newNode = new t_node;
    newNode->pNode = pNode;

    //check if it is the first item in LinkedList 
    if(pListHead!=NULL)
    {
	//it is not the first item
	pListTail->pNext = newNode;
	newNode->pPrev = pListTail;
	newNode->pNext = NULL;
	pListTail = newNode;	
    }
    else
    {
	//it is the first item
	newNode->pPrev = NULL;
	newNode->pNext = NULL;
	pListHead = newNode;
	pListTail = newNode;
    }
}
/**********************************************************
 *  deleteNode 
 *********************************************************/
template <class pNodeType> void LinkedList::deleteNode(pNodeType * pNode)
{
    //error if totalNode is zero 
    assert(totalNode!=0); 
    
    if(pListHead->pNode==pNode) 
    {
	//pNode is the first item in the list 
	//delete it and make the second one as the first item in the list
	t_node * pSecondNode;	
	pSecondNode = pListHead->pNext;
	pSecondNode->pPrev = NULL;
	delete pListHead->pNode;
	delete pListHead;
	pListHead = pSecondNode;
    }
    else
    {
	//pNode is in the middle/last item of the list
	int i=1;
	bool isFound=false;
	t_node * pList = pListHead->pNext;
	for(;i<=totalNode;i++)
	{
	    if(pList->pNode==pNode)
	    {
		isFound = true;
		break;
	    }
	}

	//delete the node and make itsNext connected to itsPrev
	assert(isFound);
	t_node * pPrevNode = pList->pPrev;
	t_node * pNextNode = pList->pNext;
	pPrevNode->pNext = pNextNode;
	pNextNode->pPrev = pPrevNode;
	delete pList->pNode;
	delete pList;
    }
    totalNode--;  
}

/**********************************************************
 *   Constructor
 *********************************************************/
LinkedList::LinkedList(): totalNode(0)
{
    pListHead = NULL;
    pListTail = NULL;
    pNode->pPrev = NULL;
    pNode->pNext = NULL;
}

/**********************************************************
 *  Destructor 
 *********************************************************/
LinkedList::~LinkedList()
{
    t_node * pList = pListHead;
    while()
    {
	delete pList->pNode;
	pList = pList->pNext;
	delete pList->pPrev;
	if(pList->pNext!=NULL) break;
    }
}

