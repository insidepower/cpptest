#if 0
#include <iostream>
#include "time.h"
#include <stdio.h>
using namespace std;

int main(void){
	time_t myTime;
	time_t myTime2;
	myTime = time(NULL);
	//myTime = time(&myTime);

	cout << myTime << endl; //1211768933
	cout << asctime(localtime(&myTime)) << endl; //Mon May 26 10:28:53 2008
	cout << localtime(&myTime) << endl; //00478E80

	char * timeStamp = asctime(localtime(&myTime));
	printf("mytime: %s\n", timeStamp); //mytime: Mon May 26 10:28:53 2008

	return 0;
}

#endif

#include <stdio.h>

int main(void){
	char mgmtType[][30] = {"CE Request", "CE Response", "Stat Requese", 
   								"Stat Response", "Stat Counter Reset"};
	
	char * ptr = mgmtType[3];
	printf("ptr = %s\n", ptr);

	return 0;
}




