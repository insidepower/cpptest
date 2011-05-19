#pragma once
#include "ThreadCreator.h"

#include "Obj2.h"

class Thread2: public ThreadCreator
{
	public:
		Thread2();
		void Thread2::run_me(void);
		Obj2 * pObj2;
};
