#include <iostream>
using namespace std;

class myclass {
	public:
	int a;
	int b;
}myclass_obj;

int main()
{
	unsigned char * pch = (unsigned char *) &myclass_obj;
	myclass_obj.a=5;
	myclass_obj.b=6;

	int i=0;
	for(;i<sizeof(myclass);i++)
	printf("0x%2X, ", pch[i]);

	printf("\n");
	return 0;	
}
