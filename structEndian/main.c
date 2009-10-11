#include <stdio.h>
#include <string.h>

typedef struct t_tag{
	unsigned int empty_1:1,
				 usableSC:7,
				 tmArIndex:5,
				 empty_2:3,
				 empty_3:8,
				 fec:3,
				 mod:2,
				 empty_4:3;
	unsigned char uchar;
	unsigned short ushort;
	unsigned char uchar2;
}__attribute__((packed)) t_tag;

int main(void)
{
	t_tag mytag;
	memset(&mytag, 0, sizeof(mytag));
	mytag.empty_1=1;
	mytag.usableSC=5;
	mytag.tmArIndex=20;
	mytag.empty_2=1;
	mytag.empty_3=1;
	mytag.fec=2;
	mytag.mod=1;
	mytag.empty_4=3;
	mytag.uchar=5;
	mytag.ushort=0xAABB;
	mytag.uchar2=6;

	int a = 0xFF00AA05;

	return 0;
}

/*############################################################################
RESULT:
byte is big endian, bit is little endian (in struct)
[usableSC-empty_1]:[empty_2-tmArIndex]:[empty_3]:[empty_4-mod-fec]:[uchar]:
[ushort=0xbb, 0xaa]:[uchar2]

little endian
a(memory) [0x05] : [0xaa] : [0] : [0xff]
############################################################################*/

