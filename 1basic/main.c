#include <stdio.h>

int DoIt (float a, char b, char c)
{
}

int DoIt2 (float a, char b, char c)
{
}

void my_void_func()
{
}

/// declare function list array
int (*func_list[2])(float a, char b, char c)={
	DoIt,
	DoIt2,
};

int main(void)
{
	/// === <numeric constants> ===
	int a = 0b1010;   	// decimal 10
	a=0xa;
	a=012;				// capital zero(0) for octal
	a=10;

	unsigned int b = 10U;
	long int c = 99L;
	unsigned long int d = 100UL;
	float e = 1.2F;
	char f = 'z';
	/// === </numeric constants> ===

	/// === < bitwise operation > ===
	int test = a >> 2;  // shift 2 bit, test=0x10=2
	test |= a;
	test = ~a;
	test ^= a;
	test &= a;
	/// === < /bitwise operation > ===

	/// === < pointer > ===
	unsigned char myvalue = 5;
	unsigned char myarr [2] = {1, 2};
	unsigned char * p1 = &myvalue;
	unsigned char ** pp2 = &p1;
	unsigned char *** ppp3 = &pp2;
	p1 = myarr;
	p1 = &myarr[0];
	/// === < /pointer > ===

	/// === < function pointer > ===
	int (*pt1Function)(float, char, char) = NULL;
    pt1Function = &DoIt;

    typedef int (*pt2Function)(float, char, char);
	pt2Function myFunc= &DoIt;

	myFunc = func_list[0];
	int func_return = (*myFunc)(5.5, 6, 6);

	void (*vfp)(void) = &my_void_func;
	(*vfp)();
	/// === < /function pointer > ===

	/// === < operator precedence > ===
	char temp1 = 1, temp2=2;
	char m, *p=&temp1; //e.
	m = *p++;   // m=*p=1; ++p
	p=&temp1;
	m = *++p;	// ++p, m=*p
	p=&temp1;
	m = ++*p; 	// char u=*p; m=++u; p value is untouched
	p=&temp1;
	m = (*p)++; // m = *p;
	/// === < /operator precedence > ===

	/// === < pointer > ===
	/// === < /pointer > ===

	/// === < pointer > ===
	/// === < /pointer > ===

	/// === < /pointer > ===
	/// === < /pointer > ===
}
