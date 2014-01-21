// generator.h: interface for the generator class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>


#if !defined(AFX_GENERATOR_H__CB047C7E_EBF8_4C9D_8D64_BA47054B2DC7__INCLUDED_)
#define AFX_GENERATOR_H__CB047C7E_EBF8_4C9D_8D64_BA47054B2DC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define MAX_NODE_ID ((1<<16)-1)
#define BO_COUNTER_3	(7)
#define BO_COUNTER_2	(5)
#define BO_COUNTER_1	(3)
#define BO_COUNTER_0	(2)
#define BO_INCREMENT	(2)
#define MAX_FRAME_LENGTH (160)
#define ARRIVING_RATE  (1)
#define MAX_NODE       (12)
#define SCALE_UP       (100)
#define MIN_DATA_RATE  (6)
#define MAX_DATA_RATE  (14)


class Generator  
{
public:
	static int nodeID;
	static int genNodeID();
	static int randomInt(int p_start, int p_end);
	static int generateRandomNodes(int timeInterval);
	//Constructor
	Generator();
	//Destructor
	virtual ~Generator();

};

#endif // !defined(AFX_GENERATOR_H__CB047C7E_EBF8_4C9D_8D64_BA47054B2DC7__INCLUDED_)
