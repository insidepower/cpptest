#include <stdio.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define ARRIVING_RATE  (1)
#define MAX_NODE       (12)
#define SCALE_UP       (100)

/**********************************************************
 *   addRandomNodes
 *
 *   Descripton: 
 *   Generate a random number of nodes based on Poisson 
 *   Arrival Distribution formula
 *********************************************************/
int addRandomNodes(){
    int timeInterval = 1;
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
		for(nodeNumber=1;nodeNumber<MAX_NODE;nodeNumber++)
		{
		    ArrivalProb[nodeNumber] *= 10;
		}
	}

    srand (time(NULL));
	random = rand()%100+1;
	printf("addRandomNodes::Random = %d\n", random);
	for(nodeNumber=1;nodeNumber<MAX_NODE;nodeNumber++)
	{
	    if(random < ArrivalProb[nodeNumber]) break;
	}
	printf("addRandomNodes::Number of nodes arriving at this cycle = %d\n", nodeNumber); 

    return nodeNumber;
}

