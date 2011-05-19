#include "Obj1.h"

Obj1::Obj1(){
	cout << "Obj1 created" << endl;
}

void Obj1::call_me(){
	cout << "Obj1 call_me: thread_id = " << GetCurrentThreadId() << endl;
}
