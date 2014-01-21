// generator.cpp: implementation of the generator class.
//
//////////////////////////////////////////////////////////////////////
#include "generator.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**********************************************************
 *   Constructor
 *********************************************************/
Generator::Generator()
{
	nodeID=0;
	//initialize random seed
	srand (time(NULL) );
}
/**********************************************************
 *   Destructor
 *********************************************************/
Generator::~Generator()
{

}


//////////////////////////////////////////////////////////////////////
// Attributes
//////////////////////////////////////////////////////////////////////

int Generator::nodeID;
//////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////////
int Generator::genNodeID()
{

	if (nodeID<MAX_NODE_ID)
		nodeID++;
	else
		nodeID=1;
	//printf("\n======================================\n");
	//printf("Node %d\n", nodeID);
	//printf("\n======================================\n");
	return nodeID;
}

int Generator::randomInt(int p_start, int p_end)
{
	int result;	
	//generate secret number
	result=rand() % (p_end-p_start) + p_start;
	return result;
		
}




/**********************************************************
 *   generateRandomNodes
 *
 *   Descripton: 
 *   Generate a random number of nodes based on Poisson 
 *   Arrival Distribution formula
 *********************************************************/
int Generator::generateRandomNodes(int timeInterval){
    int nodeNumber = 1;
    int factorial = 1;
	int random;
    int params = ARRIVING_RATE*timeInterval;
	double expValue = exp(-params);
	double temp=0;

    double ArrivalProb[MAX_NODE] = {0.0}; 
    ArrivalProb[0] = expValue*SCALE_UP;
	//printf("ArrivalProb[0] = %e\n", ArrivalProb[0]);

    //calculate Arrival Probability from 1 to MAX_NODE number of nodes
    for(;nodeNumber<MAX_NODE;nodeNumber++)
    {
		factorial = factorial*nodeNumber;
		temp = pow(params, nodeNumber)*expValue/factorial*SCALE_UP;
		ArrivalProb[nodeNumber] = temp + ArrivalProb[nodeNumber-1];
		//printf("ArrivalProb[%d] = %f, current = %e\n", nodeNumber,ArrivalProb[nodeNumber], temp);
    }

	//to ensure the range of arrival is between 0-100
	//i.e. ArrivalProb of last node should be more than 50
	while(ArrivalProb[MAX_NODE-1] < (SCALE_UP/2))
	{
		printf("Arrival Probability is within 0-10, increase it to 0-100\n");
		ArrivalProb[MAX_NODE-1] = 100 - ArrivalProb[MAX_NODE-2];
		//for(nodeNumber=1;nodeNumber<MAX_NODE;nodeNumber++)
		//{
		  //  ArrivalProb[nodeNumber] *= 10;
		//}
	}

    srand (time(NULL));
	random = rand()%100+1;
	//printf("addRandomNodes::Random = %d\n", random);
	for(nodeNumber=0;nodeNumber<MAX_NODE;nodeNumber++)
	{
	    if(random < ArrivalProb[nodeNumber]) break;
	}
	printf("addRandomNodes::Number of nodes arriving at this cycle = %d\n", nodeNumber); 

    return nodeNumber;
}



