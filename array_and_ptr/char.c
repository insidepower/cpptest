#include <stdio.h>

int main(void){
	char mgmtType[][30] = {"CE Request\0", "CE Response\0", "Stat Requese\0", 
   								"Stat Response\0", "Stat Counter Reset\0"};
	
	char * ptr = mgmtType[3];
	printf("ptr = %p\n", ptr);
	printf("ptr string = %s\n", ptr);

	return 0;
}

