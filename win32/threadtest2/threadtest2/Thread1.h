#pragma once
#include "ThreadCreator.h"

#include "Obj1.h"

class Thread1: public ThreadCreator
{
	public:
		Thread1();
		void run_me();
		Obj1 * pObj1;
};
