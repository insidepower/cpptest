// Node.h: interface for the Node class.
//
//////////////////////////////////////////////////////////////////////
#include "generator.h"
#if !defined(AFX_NODE_H__951854B5_C559_4E7F_959F_38D3AC784498__INCLUDED_)
#define AFX_NODE_H__951854B5_C559_4E7F_959F_38D3AC784498__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class Node  
{

public:
	Node();
	Node(bool p_staticFlag, short p_priority);
	virtual ~Node();
	short getPriority();
private:
	void randomisePriority(Node * p_node);
	void randomiseNode(Node * p_node);
public:
	int nodeID;
	short priority;
	short RemainingDataLength;
	short backoffCounter;
	short collisionCounter;
	short retxCounter;
	short destNodeID;
	time_t startTimestamp;
	time_t endTimestamp;
	bool staticFlag;

};


#endif // !defined(AFX_NODE_H__951854B5_C559_4E7F_959F_38D3AC784498__INCLUDED_)
