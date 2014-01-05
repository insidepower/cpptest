#include <stdio.h>
typedef struct TmMsg {
   unsigned int type;
   unsigned int cap;			   //to send to TxPduMgmtCap3
	unsigned int empty_1:1,   //***NOTE: beware of signed & unsigned 
   	 usableSC:7,            //empty_1=1 ==> 0xFFFF_FFFF
       tmArIndex:5,
   	 empty_2:3,
   	 empty_3:8,
   	 fec:3,
   	 mod:2,
   	 empty_4:3;
short tmi; 
unsigned char vt[16];  //16*8=128 subcarrier
//unsigned char tmArIndex; 
unsigned char arDestAddr[6];
int sum20symRawBits;
int sum40symRawBits;
}TmMsg;

int main(){
   TmMsg new;
   TmMsg * pqTmMsg = &new;
   pqTmMsg->type=1;
   pqTmMsg->cap=2;
   pqTmMsg->empty_1=1;
   pqTmMsg->usableSC=3;
   pqTmMsg->tmArIndex=4;
   pqTmMsg->empty_2=2;
   pqTmMsg->empty_3=6;
   pqTmMsg->fec=7;
   pqTmMsg->mod=1;
   pqTmMsg->empty_4=7;
   pqTmMsg->tmi=8; 
}
