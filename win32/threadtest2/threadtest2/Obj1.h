#pragma once
#include <iostream>
#include "Windows.h"

using namespace std;

class Obj1
{
	public:
		Obj1();
		void call_me();
		void call_by_another_thread();
};
