// Node.cpp: implementation of the Node class.
//
//////////////////////////////////////////////////////////////////////
#include "Node.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Node::Node()
{
	nodeID=Generator::genNodeID();
	staticFlag=false;
	collisionCounter=0;
	retxCounter=0;
	//Randomise priority
	randomisePriority(this);
	randomiseNode(this);
	//printf("Time created=%ld\n", startTimestamp);
	//printf("Priority=%d\tBackoff Counter=%d\n", priority, backoffCounter);

}

Node::Node(bool p_staticFlag, short p_priority)
{
	nodeID=Generator::genNodeID();
	staticFlag=p_staticFlag;
	priority=p_priority;
}


Node::~Node()
{

}


short Node::getPriority()
{
	return priority;
}


void Node::randomisePriority(Node * p_node)
{
	p_node->priority=Generator::randomInt(0, 3);
}


void Node::randomiseNode(Node * p_node)
{
	int cw[2][4]={7,15,15,31,7,15,31,63};

	//Randomise backoff counter
	switch (p_node->priority)
	{
	case 3:	
	case 2:
			if (collisionCounter<3)
				p_node->backoffCounter=Generator::randomInt(1, cw[0][collisionCounter]);
			else
				p_node->backoffCounter=Generator::randomInt(1, cw[0][3]);
			break;
	case 1:	
	case 0:	
			if (collisionCounter<3)
				p_node->backoffCounter=Generator::randomInt(1, cw[1][collisionCounter]);
			else
				p_node->backoffCounter=Generator::randomInt(1, cw[1][3]);
			break;
	default:
			perror("No such priority\n");
	}
	//Randomise Frame Length
	p_node->RemainingDataLength=Generator::randomInt(0, MAX_FRAME_LENGTH);
	//Randomise Dest Node ID
	p_node->destNodeID=Generator::randomInt(1, MAX_NODE_ID);
	p_node->startTimestamp=time(NULL);
}
