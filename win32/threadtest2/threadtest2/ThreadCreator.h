#pragma once
#include "Windows.h"
#include <iostream>
using namespace std;


class ThreadCreator
{
	public:
		ThreadCreator();
		static DWORD WINAPI genericRun(LPVOID t);
		void run(void);
		virtual void run_me(void);
    	HANDLE hThread;
		DWORD mThreadId;
		SIZE_T mStackSize;
};
