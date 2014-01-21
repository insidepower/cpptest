#include <iostream>
#include <iomanip>
using namespace std;

typedef struct t_my{
	unsigned int a;
	t_my * next;
} t_my;

typedef struct {
	unsigned short b;
	unsigned short c;
	t_my * d;
} t_myy;

char alpha[]= "abcdefghijklmnopqrstuvwxyz";

char * p_alpha = alpha;

int main(void){
	t_my u;
	u.a = 0x77558855;
	t_myy * m;
	m = (t_myy *) &u;
	
	cout << hex << m->b << endl;
	cout << hex << m->c << endl;

	t_myy * m2 = (t_myy *) p_alpha;
	t_myy m3;

	cout << hex << "alpha offset 2 bytes is = " << ((t_myy *) p_alpha)->c << endl;
	cout << hex << "alpha offset 2 bytes is = " << m2->c << endl;
	
	m3.b = 2;
	m3.c = 3;
	m3.d = &u;

	cout << m3.d->a << endl;
	
	t_my u2;
	u2.a = 0x77558866;
	m3.d->next = &u2;
	
	cout << m3.d->next->a << endl;

	return 0;
}
