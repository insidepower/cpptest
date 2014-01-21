#include "LL.h"
#include "Node.h"
#include <stdio.h>

LL<Node> * pListHead = new LL<Node>;

void printList(LL<Node> * pListHead){
	int i = 0;
	LL<Node> * currList = pListHead;
	printf("\nLinkedList: \n");
    while(1)
    {
        printf("(%d) currList->priority = %d\n", i, currList->currNode->priority);
        if(currList->pNext==NULL) break;
        currList= currList->pNext;
    }
}


int main(void){
	
	Node * ptrNode[10];

	int status = -1;
	for (int i=0; i<10; i++){ 
		ptrNode[i] = new Node();
		ptrNode[i]->priority = i;
		status = pListHead->addNode(ptrNode[i]);
	}

	printList(pListHead);

	status = pListHead->deleteNode(ptrNode[2]);
	assert(status == 0);
	//deleteNode(ptrNode[2]);
	printList(pListHead);
	
	status = pListHead->deleteNode(ptrNode[0]);
	assert(status == 0);
	printList(pListHead);

	status = pListHead->deleteNode(ptrNode[9]);
	assert(status == 0);
	printList(pListHead);

	//deleteList(pListHead);

	status = pListHead->deleteList();
	assert(status == 0);
	printList(pListHead);

	//deleteNode(pListHead->currNode);

	//printList(pListHead);

	return 0;
}