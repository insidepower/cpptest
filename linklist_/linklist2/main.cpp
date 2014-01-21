#include "LinkedList.h"
#include <iostream>
#include <stdio.h>
using namespace std;

class myVar{
public:
	int number;
	myVar():number(0){};
};

int main(void)
{
    LinkedList<myVar> myList; 
    int i=0;
	int status;
	//myVar * node = new myVar[10];
	myVar * node;
	myVar * temp[10];
	//unsigned char * a = new unsigned char;
	//unsigned char b = 1;
	
	for(;i<10;i++)
    {
		node = new myVar;
		temp[i] = node;
		node->number = i;
		status=myList.addNode(node);
		assert(status==0);
    }

	LinkedList<myVar>::t_node * curNode = myList.pListHead;
	cout << "LinkedList: " << endl;

	while(1)
	{
		printf("%d\n", curNode->pNode->number);
		if(curNode->pNext==NULL) break;
		curNode = curNode->pNext;
	}

	status=myList.deleteNode(temp[5]);
	status=myList.deleteNode(temp[0]);
	status=myList.deleteNode(temp[9]);

	return 0;
}

