#include <stdio.h>
#include <string.h>

#define LITTLE_ENDIAN 1
#define BIG_ENDIAN 1

#define BIT_ORDER LITTLE_ENDIAN
//#define BIT_ORDER BIG_ENDIAN

typedef struct 
{         
#if BIT_ORDER==LITTLE_ENDIAN   
	unsigned char	fpv:3, //Frame Protocol Version
					rsvd:2, //Reserved					
					mcf:1,	//Multicast Flag         
					cap:2;	//Channel Access Priority
	unsigned char 	sl_1;   //Segment Length
	unsigned char 	sl_2:7, //Segment Length
					lsf:1;	//Last Segment Flag
	unsigned char 	sc:6,   //Segment Count
					sn_1:2; //Segment Number
	unsigned char 	sn_2;   //Segment Number
#elif BIT_ORDER==BIG_ENDIAN
	unsigned char	cap:2,	//Channel Access Priority
					mcf:1,	//Multicast Flag
					rsvd:2, //Reserved
					fpv:3;	//Frame Protocol Version
	unsigned char 	sl_1;	//Segment Length
	unsigned char 	lsf:1,	//Last Segment Flag	
					sl_2:7; //Segment Length
	unsigned char 	sn_1:2, //Segment Number
					sc:6;   //Segment Count
	unsigned char 	sn_2;   //Segment Number
#endif	
}__attribute__((packed)) t_segControl;


typedef struct struct_FC
{
#if BIT_ORDER==LITTLE_ENDIAN   
   unsigned int vf_1:5,
                dt:3,
                vf_2:8,
                cc:1,
                empty:6,
                rfe:1,
                fccs:8;
#elif BIT_ORDER==BIG_ENDIAN
   unsigned char dt:3,
                 vf_1:5;
   unsigned char vf_2;
   unsigned char rfe:1,
                 rsvd:6,
                 cc:1;
   unsigned char fccs;
   //   unsigned int	fccs:8,		//FCCS	-can be ignored
   //		vf:13,		//Variant Field 
   //		dt:3,		//Delimiter Type
   //		cc:1;		//Contention Control
#endif	
}struct_FC;


typedef struct struct_SOF
{
#if BIT_ORDER==LITTLE_ENDIAN   
   unsigned int fl_1:5,       //frameLen: upper 5 bits
                dt:3,
                tmi:5,
                fl_2:3,       //frameLen: lower 3 bits
                cc:1,
                empty:7,      //not used at the moment
                fccs:8;
//   unsigned char  fl_1:5,
//                  dt:3;		   //Delimiter Type
//	unsigned char	tmi:5,		//Variant Field -Tone Map Index
//		            fl_2:3; 		//Variant Field	-Frame Length
//   unsigned char	fccs;		   //FCCS	-can be ignored
//   unsigned char	cc:1, 		//Contention Control
#elif BIT_ORDER==BIG_ENDIAN
   unsigned char  dt:3,
                  fl_1:5;		   //Delimiter Type
	unsigned char	fl_2:3,		//Variant Field -Tone Map Index
		            tmi:5; 		//Variant Field	-Frame Length
   unsigned char	fccs;		   //FCCS	-can be ignored
   unsigned char	rsvd:7, 		//Contention Control
                  cc:1;
#endif	
}struct_SOF;

typedef struct struct_EOF
{
#if BIT_ORDER==LITTLE_ENDIAN   
   unsigned int rsvd_1:2,     //upper 2 bits
                invalid:1,
                cap:2,
                dt:3,
                rsvd_2:8,     //lower 8 bits
                cc:1,
                empty:7,
                fccs:8;
   //unsigned char  rsvd_1:2,
   //               invalid:1,
   //               cap:2,
   //               dt:3;		   //Delimiter Type
   //unsigned char  rsvd_2;
   //unsigned char	fccs;		   //FCCS	-can be ignored
   //unsigned char	cc:1, 		//Contention Control
   //               rsvd:7;
#elif BIT_ORDER==BIG_ENDIAN
   unsigned char  dt:3,
                  cap:2,
                  invalid:1,
                  rsvd_1:2;		   //Delimiter Type
   unsigned char  rsvd_2;
   unsigned char	fccs;		   //FCCS	-can be ignored
   unsigned char	rsvd:7, 		//Contention Control
                  cc:1;
#endif	
}struct_EOF;

inline unsigned char swapBitsInByte(unsigned char n)
{
  n = (n & 0xF0) >> 4 | (n & 0x0F) << 4;
  n = (n & 0xCC) >> 2 | (n & 0x33) << 2;
  n = (n & 0xAA) >> 1 | (n & 0x55) << 1;
  return n;
}

#define SWAP5BITS(n) (((n&1)?16:0)|((n&2)?8:0)|((n&4)?4:0)|((n&8)?2:0)|((n&16)?1:0))
#define SWAP3BITS(n) (((n&1)?4:0)|((n&2)?2:0)|((n&4)?1:0))
//FL_1 has the msb 5-bits, FL_2 has the lsb 3-bits
#define FL_1(n) ((n&0xF8)>>3)
#define FL_2(n) (n&7)

int main(void)
{
#ifdef TEST_SEGCONTROL
   int i;
   t_segControl structSegCtrl;
   memset(&structSegCtrl, 0xcd, sizeof(t_segControl));
   printf("structSegCtrl: segCount(): ");
   for (i=0; i< sizeof(structSegCtrl); i++)
      printf("%X, ", *(((unsigned char *) &structSegCtrl)+i));
   printf("\n");
   structSegCtrl.sc=0;
   structSegCtrl.sn_1=0; 
   structSegCtrl.sn_2=5&0xFF;                  
   structSegCtrl.sl_2=6;
   structSegCtrl.sl_1=3;         
   structSegCtrl.cap=2;    
#endif

#define TEST_SOF
#ifdef TEST_SOF
   struct_SOF mysof;
   char fl=0xfF;
   memset(&mysof, 0,sizeof(mysof));
   mysof.cc=0;
   //mysof.dt=SWAP3BITS(7);
   mysof.dt=3;
   //mysof.fl_1=FL_1(fl);
   //mysof.fl_2=FL_2(fl);
   mysof.fl_1=fl>>3;
   mysof.fl_2=fl;
   //mysof.tmi=SWAP5BITS(3);
   mysof.tmi=7;
   mysof.fccs=0xff;

   struct_EOF myeof;
   memset(&myeof, 0, sizeof(myeof));
   myeof.cap=3;
   myeof.dt=3;
   myeof.cc=1;
   myeof.invalid=1;
   myeof.rsvd_1=1;
   myeof.rsvd_2=1;

   struct_FC myfc;
   memset(&myfc, 0, sizeof(myfc));
   myfc.dt=3;
   myfc.vf_1=0xF;
   myfc.vf_2=0x2F;
   myfc.rfe=1;
   myfc.cc=1;
   myfc.fccs=0x8E;
#endif
   short a=-5;
   printf("a is %X, sizeof(a)=%d\n", a, sizeof(a));

   unsigned short myvar=0x3210;
   unsigned short myvar2=0;
   //error if using memset, since myvar is 16 bits
   //use memcpy instead
   memset(&myvar2, myvar, 2);
   printf("\nmyvar2=%X\n", myvar2);
   memcpy(&myvar2, &myvar, 2);
   printf("\nmyvar2=%X\n", myvar2);
   return 0;
}
