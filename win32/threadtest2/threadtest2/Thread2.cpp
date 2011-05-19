#include "Thread2.h"

Thread2::Thread2(void):ThreadCreator()
{
	/// call ThreadCreator to create a new thread
}

void Thread2::run_me(void)
{
	/// create class object
	this->pObj2 = new Obj2();
	Sleep(INFINITE );
}
