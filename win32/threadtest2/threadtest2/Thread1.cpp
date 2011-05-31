#include "Thread1.h"

Obj1 * Thread1::pObj1 = NULL;
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

Obj1* Thread1::getObj1Instance(void)
{
	return pObj1;
}
