#include "Thread1.h"

Thread1::Thread1(void)
{
	/// call ThreadCreator to create a new thread
}

void Thread1::run_me(void)
{
	/// create class object
	this->pObj1 = new Obj1();
	Sleep(INFINITE );
}
