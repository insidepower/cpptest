#include <stdio.h>

int func1(void){
	printf("hello from func1\n");
	return 1;
}

int func2(void){
	printf("hello from func2\n");
	return 0;
}

char funcBool(int a){
	printf("hello from funcBool, a=%d\n", a);
	return 'a';
}

int main(void){
	/// take note func1=&func1, both are same!
	int (*pFuncPtr[3])(void) = { func1, func2, &func2};

	(*pFuncPtr[0])();
	(*pFuncPtr[1])();
	(*(pFuncPtr+1))();
	(*(pFuncPtr+0))();

	printf("with ampersand!\n");
	(*pFuncPtr[2])();

	typedef char (*pFuncBool)(int);
	pFuncBool myFuncBool = &funcBool;
	(*myFuncBool)(1);


	int (*vfp)(void) = &func1;
	(*vfp)();
	
	return 0;
}
