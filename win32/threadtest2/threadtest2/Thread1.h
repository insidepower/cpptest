#pragma once
#include "ThreadCreator.h"

#include "Obj1.h"

class Thread1: public ThreadCreator
{
	public:
		Thread1();
		void run_me();
		static Obj1 * pObj1;
		static Obj1 * getObj1Instance();
};
