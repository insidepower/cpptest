#include "Obj2.h"

Obj2::Obj2(){
	cout << "Obj2 created" << endl;
}

void Obj2::call_me(){
	cout << "Obj2 call_me: thread_id = " << GetCurrentThreadId() << endl;
}
