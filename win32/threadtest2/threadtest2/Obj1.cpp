#include "Obj1.h"

Obj1::Obj1(){
	DWORD threadid =  GetCurrentThreadId();
	/// cout could be preempted as its priority is low
	cout << "Obj1 created: thread_id =" << threadid << endl;
	flush(cout);
}

void Obj1::call_me(){
	cout << "Obj1 call_me: thread_id = " << GetCurrentThreadId() << endl;
	flush(cout);
}

void Obj1::call_by_another_thread()
{
	cout << "Called by thread_id " << GetCurrentThreadId() << endl;
}
