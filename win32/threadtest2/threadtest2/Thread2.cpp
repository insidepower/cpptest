#include "Thread2.h"


Thread2::Thread2(void):ThreadCreator(), pObj1(NULL)
{
	/// call ThreadCreator to create a new thread
}

void Thread2::run_me(void)
{
	/// create class object
	this->pObj2 = new Obj2();
	this->pObj1 = Thread1::getObj1Instance();
	this->pObj1->call_by_another_thread();
	Sleep(INFINITE );
}
