#include "ThreadCreator.h"

#define CAST(x)    (x)

ThreadCreator::ThreadCreator(void)
{
	this->mStackSize = 1024; 				/// in byte
    this->hThread = CreateThread( NULL,                                                 // pointer to security attributes
                                  CAST(DWORD)(this->mStackSize),                        // initial thread stack size
                                  CAST(LPTHREAD_START_ROUTINE)(&ThreadCreator::genericRun),    // pointer to thread function
                                  CAST(LPVOID)(this),                                   // argument for new thread
                                  CREATE_SUSPENDED,                                     // creation flags
                                  &this->mThreadId);                                    // pointer to receive thread ID

	if (this->hThread == NULL) {
		cout << "Error in creating thread: " << GetLastError() << endl;
	}
}

DWORD ThreadCreator::genericRun(LPVOID t)
{
    //dbgAssertPointer(t);
    (CAST(ThreadCreator*)(t))->run();

    return true;
}

void ThreadCreator::run(void)
{
	run_me();
}

void ThreadCreator::run_me(void)
{
	cout << "Should override this method!" << endl;
	Sleep(INFINITE );
}


