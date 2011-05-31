#pragma once
#include "ThreadCreator.h"
#include "Thread1.h"

#include "Obj1.h"
#include "Obj2.h"

class Thread2: public ThreadCreator
{
	public:
		Thread2();
		void Thread2::run_me(void);
		Obj1 * pObj1;
		Obj2 * pObj2;
};
