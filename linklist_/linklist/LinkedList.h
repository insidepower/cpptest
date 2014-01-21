#ifndef __MQUEUE_H__
#define __MQUEUE_H__

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
	t_node * pListHead; 	//First Node in the LinkedList
	t_node * pListTail; 	//Last Node in the LinkedList
	t_node * newNode;
	void addNode(pNodeType * pNode);
	void deleteNode(pNodeType * pNode);
	int totalNode;
	LinkedList();			//Constructor
	~LinkedList();			//Destructor
};

#endif







