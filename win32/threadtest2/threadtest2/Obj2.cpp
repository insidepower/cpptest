#include "Obj2.h"

Obj2::Obj2(){
	DWORD threadid =  GetCurrentThreadId();
	cout << "Obj2 created: thread_id2 =" <<  threadid << endl;
	flush(cout);
}

void Obj2::call_me(){
	cout << "Obj2 call_me: thread_id = " << GetCurrentThreadId() << endl;
}
