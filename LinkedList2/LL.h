#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#define NULL 0
#include "assert.h"

template <class pNodeType>
class LL
{
    public:
		pNodeType * currNode;
		//LL * pTail;
		LL * pNext;
		LL * getNextNode();
		int deleteList();
		int addNode(pNodeType * pNode);
		int deleteNode(pNodeType * pNode);
        int totalNode;
        LL();                        //Constructor
        ~LL();                        //Destructor
};

template <class pNodeType>
LL<pNodeType> * LL<pNodeType>::getNextNode()
{
	return pNext;	
}

/**********************************************************
 *   addNode
 *
 *   Description:
 *   Add new node to the tail of LinkedList
 *********************************************************/
template <class pNodeType>
int LL<pNodeType>::addNode(pNodeType * pNode)
{
	totalNode++;
	if(currNode == NULL) 
	{
		currNode = pNode;
		//pTail = this;
	}
	else
	{
		LL * ptrOld = this;
		LL* ptrLL=pNext;	
		while (ptrLL!=NULL)	
		{
			ptrOld = ptrLL;
			ptrLL=ptrLL->pNext;
		}
		//add new Node
		LL * newLL = new LL;
		newLL->currNode = pNode;
		newLL->pNext = NULL;
		//link to prev Node
		ptrOld->pNext = newLL;
		//pTail = newLL;
	}

	return 0;
}	

/**********************************************************
 *   deleteNode()
 *********************************************************/
template <class pNodeType>
int LL<pNodeType>::deleteNode(pNodeType * pNode)
{
	assert(totalNode!=0);
	totalNode--;
	
	//is the node to be deleted the first node
	if(currNode==pNode) 
	{
		//yes, node to be deleted is first node
		if(pNext!=NULL) 
		{
			//delete first node's currNode and link it to 3rd node's currNode
			delete currNode;
			currNode = pNext->currNode;

			//link first node' pNext to 3rd node
			LL * ptrTemp = pNext->pNext;
			pNext->currNode = NULL;
			delete pNext;
			pNext = ptrTemp;
		}
		else //pNext == NULL
		{
			delete currNode;
		}
	}
	else if(pNext!=NULL)
	{
		LL * ptrOld = this;
		LL * ptrLL = pNext;
		while(ptrLL!=NULL)
		{
			if(ptrLL->currNode==pNode)
			{
				//is the node we going to delete is the last node?
				//if so then set pTail to ptrOld
				//if(ptrLL->pNext == NULL) pTail = ptrOld;
				ptrOld->pNext = ptrLL->pNext;
				delete ptrLL;
				break;
			}
			ptrOld = ptrLL;
			ptrLL=ptrLL->pNext;
		}
	}
	else
	{
		printf("LL::error in deleting Node\n");
	}

	return 0;
}

/**********************************************************
 *   deleteList()
 *********************************************************/
template <class pNodeType>
int LL<pNodeType>::deleteList(){
	//keep pListHead and current node's pNext, then delete current node
	LL * ptrTemp = pNext;
	LL * ptrCurrNode = this;
	while(ptrTemp != NULL)
	{
		ptrCurrNode = ptrTemp;
		ptrTemp = ptrCurrNode->pNext;
		delete ptrCurrNode;
	}
	//reset firstNode in the List to null;
	pNext = NULL;
	totalNode = 0;
	delete currNode;

	return 0;
}

/**********************************************************
 *   Constructor
 *********************************************************/
template <class pNodeType>
LL<pNodeType>::LL(): totalNode(0)
{
	currNode = NULL;
	//pTail = NULL;
	pNext = NULL;
}

/**********************************************************
 *  Destructor
 *********************************************************/
template <class pNodeType>
LL<pNodeType>::~LL()
{
	delete currNode;
}
	
#endif
