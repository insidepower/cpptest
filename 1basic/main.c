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

void arraytest(){
#define X .525731112119133606
#define Z .850650808352039932

	/// note: &array is a pointer to the first element of the array, 
	//  where as "array" refers to the entire array. 
	//  compare sizeof(array) vs  sizeof(&array). 
	//  if pass array as an argument to a function, only &array[0] is in fact passed. 
	//  You cannot pass an array by value unless it is encapsulated withing a struct

	static float vdata[12][3] = {
		{-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
		{0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
		{Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
	};

	static int tindices[20][3] = {
		{0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
		{8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
		{7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
		{6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

	float color = 0.1;

	int i=0;
	for (i = 0; i < 20; i++) {
		/* color information here */
		printf("tindices[%d][0]=%d\n", i, tindices[i][0]);
		printf("vdata[tindices[i][0]]=%p\n", vdata[tindices[i][0]]);
		printf("vdata[tindices[i][0]][0]=%f\n", vdata[tindices[i][0]][0]);
		printf("&vdata[tindices[i][0]][0]=%p\n", &vdata[tindices[i][0]][0]);
	}
}

int main(void)
{
	/*
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
	*/
	/// === < /operator precedence > ===

	/// === < pointer > ===
	/// === < /pointer > ===

	/// === < pointer > ===
	/// === < /pointer > ===

	/// === < /pointer > ===
	/// === < /pointer > ===
	//
	
	arraytest();

	return 0;
}

/*
 *
tindices[0][0]=0
vdata[tindices[i][0]]=0x804a160
vdata[tindices[i][0]][0]=-0.525731
&vdata[tindices[i][0]][0]=0x804a160
tindices[1][0]=0
vdata[tindices[i][0]]=0x804a160
vdata[tindices[i][0]][0]=-0.525731
&vdata[tindices[i][0]][0]=0x804a160
tindices[2][0]=9
vdata[tindices[i][0]]=0x804a1cc
vdata[tindices[i][0]][0]=-0.850651
&vdata[tindices[i][0]][0]=0x804a1cc
tindices[3][0]=4
vdata[tindices[i][0]]=0x804a190
vdata[tindices[i][0]][0]=0.000000
&vdata[tindices[i][0]][0]=0x804a190
 
 * */
