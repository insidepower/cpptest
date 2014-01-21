#include <iostream>
#include <iomanip>
using namespace std;

typedef struct{
	unsigned int type;
	unsigned char	vid:4,
					cfi:1,
					priority:3;
	unsigned char vid2;
	unsigned int int1;
	unsigned short short1;
	unsigned int int2;
	unsigned short short2;
	unsigned short short3;
}t_vlan;

int main(void){
	t_vlan a;
	a.type=0x55667788;
	a.vid = 0x0f;
	a.cfi = 0;
	a.priority = 0x7;
	a.vid2 = 0xab;
	a.int1 = 0x22334455;
	a.short1 = 0x6677;
	a.int2 = 0xaa6677bb;
	a.short2 = 0xee;
	a.short3 = 0xdd;
	
	return 0;
}

/*------<result>-------
0012FF68  88 77 66 55 EF AB CC CC  .wfUï«ÌÌ
0012FF70  55 44 33 22 77 66 CC CC  UD3"wfÌÌ
0012FF78  BB 77 66 AA EE 00 DD 00  »wfªî.Ý.
*/