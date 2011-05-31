// threadtest.cpp : Defines the entry point for the console application.
//

#include "Thread1.h"
#include "Thread2.h"
#include <stdio.h>

DWORD WINAPI MyThread( LPVOID lpParam ) 
{
	printf("haha\n");
	return 0;
}

int main(void)
{
	Thread1 first_thread;
	Thread2 second_thread;

	DWORD dwThreadId;
	int pData;
	HANDLE hThread = CreateThread( 
            NULL,              // default security attributes
            0,                 // use default stack size  
            MyThread,          // thread function 
            &pData,             // argument to thread function 
            0,                 // use default creation flags 
            &dwThreadId);   // returns the thread identifier 
	
	WaitForSingleObject(hThread, INFINITE);
	ResumeThread(first_thread.hThread);
	ResumeThread(second_thread.hThread);
	WaitForSingleObject(first_thread.hThread, INFINITE);
	Sleep(5000);
	Sleep(0);
	first_thread.pObj1->call_me();
	return 0;
}

