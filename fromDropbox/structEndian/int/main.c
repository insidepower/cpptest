#include <stdio.h>

typedef struct struct_SOF
{
   unsigned int fl_1:5,       //frameLen: upper 5 bits
                dt:3,
                tmi:5,
                fl_2:3,       //frameLen: lower 3 bits
                cc:1,
                empty:7,      //not used at the moment
                empty_2:2,
                tmArIndex:5,
                subExtend:1;
}struct_SOF;

int main(void)
{
	struct_SOF sof;
	sof.dt=3;
	sof.fl_1=2;
	sof.fl_2=6;
	sof.tmi=4;

	sof.empty=2;
	sof.empty_2=3;
	sof.cc=1;
	sof.tmArIndex=5;
}
