#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#define NULL 0

//#define NDEBUG           //turn on to disable assertion
#include "assert.h"

template <class pNodeType>
class LinkedList
{
    public:
        typedef struct t_node
        {
            pNodeType * pNode;
            t_node * pPrev;
            t_node * pNext;
        }t_node;
        t_node * pListHead;         //First Node in the LinkedList
        t_node * pListTail;         //Last Node in the LinkedList
        t_node * newNode;
        int addNode(pNodeType * pNode);
        int deleteNode(pNodeType * pNode);
        int totalNode;
        LinkedList();                        //Constructor
        ~LinkedList();                        //Destructor
};

/**********************************************************
 *   addNode
 *
 *   Description:
 *   Add new node to the tail of LinkedList
 *********************************************************/
template <class pNodeType>
int LinkedList<pNodeType>::addNode(pNodeType * pNode)
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
    return 0;
}
/**********************************************************
 *  deleteNode
 *********************************************************/
template <class pNodeType>
int LinkedList<pNodeType>::deleteNode(pNodeType * pNode)
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
			pList = pList->pNext;
        }

        //delete the node and make itsNext connected to itsPrev
        assert(isFound==true);
        t_node * pPrevNode = pList->pPrev;
        t_node * pNextNode = pList->pNext;
        pPrevNode->pNext = pNextNode;
		if(pList!=pListTail) pNextNode->pPrev = pPrevNode;
        delete pList->pNode;
        delete pList;
    }
    totalNode--;
    return 0;
}

/**********************************************************
 *   Constructor
 *********************************************************/
template <class pNodeType>
LinkedList<pNodeType>::LinkedList(): totalNode(0)
{
    pListHead = NULL;
    pListTail = NULL;
	newNode = new t_node;
    newNode->pPrev = NULL;
    newNode->pNext = NULL;
}

/**********************************************************
 *  Destructor
 *********************************************************/
template <class pNodeType>
LinkedList<pNodeType>::~LinkedList()
{
    t_node * pList = pListHead;
    while(1)
    {
        delete pList->pNode;
		if(pList->pNext==NULL) break;
        pList = pList->pNext;
        delete pList->pPrev;
    }
	delete pList;
}



#endif






