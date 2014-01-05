#include <stdio.h>

struct strA{
	int a;
}strA;

modifyPtrToPtr(struct strA ** pp)
{
	(*pp)->a=10;
}

modifySinglePtr(struct strA * p)
{
	p->a=30;
}


int main(void)
{
	struct strA mystra;
	mystra.a=20;

	struct strA * pmystra = &mystra;

	modifyPtrToPtr(&pmystra);
	modifySinglePtr(pmystra);

}
