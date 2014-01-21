#include <iostream>
#define NDEBUG //define this to turn off assert();
#include <assert.h>
using namespace std;

#pragma pack(1)
typedef struct{
	unsigned short a;
	unsigned char b;
}type;
#pragma pack()

bool check(){
	//return true;
	return false;
}

int main(void){
	int a;
	a = sizeof(type);

    cout << a << endl;
	
	assert(check());
	return 0;
}