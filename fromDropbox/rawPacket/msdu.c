#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>
#include "MemDebug.h"

int count;
int packetSize=50;
int randRange;
int length;
unsigned char * ptrMSDU;
int false=0;
int true=1;

#define BIT_ORDER LITTLE_ENDIAN

#if (BYTE_ORDER==BIG_ENDIAN)    

  #define HTONS(A) (A)
  #define HTONL(A) (A)
  #define NTOHS(A) (A)
  #define NTOHL(A) (A)  
  
#elif (BYTE_ORDER ==LITTLE_ENDIAN)    

  #define HTONS(A) ((((unsigned short)(A) & 0xff00) >> 8) | \
                    (((unsigned short)(A) & 0x00ff) << 8))
  #define HTONL(A) ((((unsigned int)(A) & 0xff000000) >> 24) | \
                    (((unsigned int)(A) & 0x00ff0000) >> 8)  | \
                    (((unsigned int)(A) & 0x0000ff00) << 8)  | \
                    (((unsigned int)(A) & 0x000000ff) << 24))

  #define NTOHS(A)  HTONS(A)
  #define NTOHL(A)  HTONL(A)

#else

  #error "Must define one of BIG_ENDIAN or LITTLE_ENDIAN"

#endif


typedef struct{
   unsigned char destAddr[6];
   unsigned char srcAddr[6];
}t_ethhdr;

typedef struct
{     
#if BYTE_ORDER==LITTLE_ENDIAN
  unsigned char mgmtVersion:3,
  				mgmtType:5;	
#elif BYTE_ORDER==BIG_ENDIAN
  unsigned char mgmtType:5,
  				mgmtVersion:3;
#endif  				
  unsigned char length;
}t_mgmtEntryHdr;

enum E_TYPE_MGMT {
    E_CE_REQ,
    E_CE_RESP,
    E_STAT_COUNTER_REQ,
    E_STAT_COUNTER_RESP,
    E_STAT_COUNTER_SET
};

typedef struct
{   
#if BIT_ORDER==LITTLE_ENDIAN
    unsigned short tpid; //Tag Protocol Identifier
    unsigned char vid1:4,	//802.1p priority levels (0-7)
    				cfi:1,		//Canonical
    				priority:3;		//Unique VLAN id
	unsigned char vid2;		//Unique VLAN id    				 
#elif BIT_ORDER==BIG_ENDIAN
    unsigned short tpid; //Tag Protocol Identifier
    unsigned char priority:3,	//802.1p priority levels (0-7)
    				cfi:1,		//Canonical
    				vid1:4;		//Unique VLAN id
	unsigned char vid2;		//Unique VLAN id    				 
#endif	
}t_vlan;

typedef struct{
    /*unsigned char etherType1;
    unsigned char etherType2;
    */        
#if BIT_ORDER==LITTLE_ENDIAN
	unsigned short etherType;   //EtherType here-should be 0x999
    unsigned char rsvd:1,		//Reserved
    			  numEntry:7;	//Number of MAC Data Entries
#elif BIT_ORDER==BIG_ENDIAN
	unsigned short etherType;   //EtherType here-should be 0x999
    unsigned char numEntry:7,   //Number of MAC Data Entries
    			  rsvd:1;		//Reserved
#endif	    
    

}__attribute__((packed)) t_mgmtInfoHdr;       

#define ETHTYPE_IP 		(0x0800)    
#define ETHTYPE_MGMT 	(0x999)
#define ETHTYPE_VLAN 	(0x8100)

#define DATA_SIZE_RANDOM_ON
#define TOTAL_TEST_CASE 50 
#define MAX_MSDU_SIZE 1500

enum E_DATA_FORMAT {
   E_MME_STAT_COUNTER_REQ_OWN, //0
   //to request stat counter of others
   E_MME_STAT_COUNTER_REQ,     //1
   E_MME_STAT_COUNTER_SET,     //2
   E_MSDU_DATA_SMALL,          //3
   E_MSDU_DATA,                //4
   //not valid if only 2 node exist in the network
   E_MSDU_DATA_SMALL_DIFF_ADDR,//5
   E_MSDU_DATA_DIFF_ADDR,      //6
   E_MME_STAT_COUNTER_REQ_DIFF_ADDR //7
};

int testSequence[TOTAL_TEST_CASE] =
{
   E_MSDU_DATA_SMALL,
   E_MME_STAT_COUNTER_REQ_OWN,
   E_MME_STAT_COUNTER_REQ,
   E_MSDU_DATA,
   E_MSDU_DATA_SMALL_DIFF_ADDR,
   E_MME_STAT_COUNTER_REQ_DIFF_ADDR,
   E_MSDU_DATA_DIFF_ADDR,
   //bundle 1 (STAT_REQ + MSDU)
   E_MSDU_DATA,
   E_MME_STAT_COUNTER_REQ,
   E_MME_STAT_COUNTER_REQ,//this should be discarded
   E_MSDU_DATA,
   E_MME_STAT_COUNTER_SET,
   E_MME_STAT_COUNTER_REQ,
   E_MSDU_DATA
};
int gSeqIndex=0;
unsigned char * generateMSDU(int *p_len) {
   //#[ operation generateMSDU(int) 
   ++count;
   //------------<DA and SA>---------------//
   t_ethhdr ethhdr;
   CROP_MARRAY(&ethhdr, sizeof(ethhdr), "ethhdr");
   packetSize = MAX_MSDU_SIZE;
   randRange = 200; 

   //unsigned char src_mac[6] = {0x00, 0x01, 0x02, 0xFA, 0x70, 0xAA};
   unsigned char src_mac[6] = {0, 0x1E, 0x58, 0x3E, 0x83, 0x1E};

   /*other host MAC address*/
   //unsigned char dest_mac[6] = {0x00, 0x04, 0x75, 0xC8, 0x28, 0xE5};
   //unsigned char dest_mac[6] = {0xEF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF};
   unsigned char dest_mac[6] = {0x32, 0x31, 0xA5, 0x5A, 0x31, 0x32};
#define SIZE_MAC_ADDR 6
   CROP_MEMCPY(ethhdr.destAddr, &dest_mac[0], SIZE_MAC_ADDR, "ethhdr");  
   CROP_MEMCPY(ethhdr.srcAddr, &src_mac[0], SIZE_MAC_ADDR, "ethhdr");

   unsigned char * ptrTemp;
   t_mgmtInfoHdr * ptrMgmtInfo;
   printf("testDataSequence[%d]: %d\n", count-1, testSequence[count-1]);
   //switch(testSequence[count-1])evNumber
   //switch(evNumber)
   switch(testSequence[gSeqIndex++])
   {
      case E_MME_STAT_COUNTER_REQ_OWN: 
	 {
	    //ethhdr.srcAddr[0]--;
	    //ethhdr.destAddr[0]--;
	    //no break, continue to process
	 }
      case E_MME_STAT_COUNTER_REQ:
	 { 
	    length = sizeof(t_ethhdr) + sizeof(t_mgmtInfoHdr) + sizeof(t_mgmtEntryHdr);// ETHERNET_MSDU_SIZE need to be changed to a variable
	    ptrMSDU = CROP_MALLOC(length, "ptrMSDU");
	    CROP_MEMCPY(ptrMSDU, &ethhdr, sizeof(t_ethhdr), "ptrMSDU");

	    //create the Mac Mgmt Info Header
	    ptrTemp = ptrMSDU + sizeof(t_ethhdr);
	    ptrMgmtInfo = (t_mgmtInfoHdr *) ptrTemp;
	    ptrMgmtInfo->etherType=HTONS(ETHTYPE_MGMT);
	    ptrMgmtInfo->numEntry = 1;
	    ptrMgmtInfo->rsvd = 0;

	    //create the Mac Mgmt Entry Header	
	    ptrTemp = ptrTemp + sizeof(t_mgmtInfoHdr);
	    t_mgmtEntryHdr * ptrMgmtEntry = (t_mgmtEntryHdr *)ptrTemp;
	    ptrMgmtEntry->mgmtType = E_STAT_COUNTER_REQ;
	    ptrMgmtEntry->mgmtVersion = 0;
	    ptrMgmtEntry->length = 0;

	    break;
	 }
      case E_MME_STAT_COUNTER_REQ_DIFF_ADDR:
	 {
	    ethhdr.destAddr[0]++; 
	    length = sizeof(t_ethhdr) + sizeof(t_mgmtInfoHdr) + sizeof(t_mgmtEntryHdr);// ETHERNET_MSDU_SIZE need to be changed to a variable
	    ptrMSDU = CROP_MALLOC(length, "ptrMSDU");
	    //assert(ptrMSDU);
	    CROP_MEMCPY(ptrMSDU, &ethhdr, sizeof(t_ethhdr), "ptrMSDU");

	    //create the Mac Mgmt Info Header
	    ptrTemp = ptrMSDU + sizeof(t_ethhdr);
	    ptrMgmtInfo = (t_mgmtInfoHdr *) ptrTemp;
	    ptrMgmtInfo->etherType=HTONS(ETHTYPE_MGMT);
	    ptrMgmtInfo->numEntry = 1;
	    ptrMgmtInfo->rsvd = 0;

	    //create the Mac Mgmt Entry Header	
	    ptrTemp = ptrTemp + sizeof(t_mgmtInfoHdr);
	    t_mgmtEntryHdr * ptrMgmtEntry = (t_mgmtEntryHdr *)ptrTemp;
	    ptrMgmtEntry->mgmtType = E_STAT_COUNTER_REQ;
	    ptrMgmtEntry->mgmtVersion = 0;
	    ptrMgmtEntry->length = 0;

	    break;
	 }
      case E_MME_STAT_COUNTER_SET:
	 { 
	    length = sizeof(t_ethhdr) + sizeof(t_mgmtInfoHdr) + sizeof(t_mgmtEntryHdr);// ETHERNET_MSDU_SIZE need to be changed to a variable
	    ptrMSDU = CROP_MALLOC(length, "ptrMSDU");
	    //assert(ptrMSDU);
	    CROP_MEMCPY(ptrMSDU, &ethhdr, sizeof(t_ethhdr), "ptrMSDU");

	    //create the Mac Mgmt Info Header
	    ptrTemp = ptrMSDU + sizeof(t_ethhdr);	
	    ptrMgmtInfo = (t_mgmtInfoHdr *) ptrTemp;	
	    ptrMgmtInfo->etherType=HTONS(ETHTYPE_MGMT);
	    ptrMgmtInfo->numEntry = 1;
	    ptrMgmtInfo->rsvd = 0;

	    //create the Mac Mgmt Entry Header
	    ptrTemp = ptrTemp + sizeof(t_mgmtInfoHdr);
	    t_mgmtEntryHdr * ptrMgmtEntry = (t_mgmtEntryHdr *)ptrTemp;
	    ptrMgmtEntry->mgmtType = E_STAT_COUNTER_SET;
	    ptrMgmtEntry->mgmtVersion = 0;
	    ptrMgmtEntry->length = 0;

	    break;
	 }
      case E_MSDU_DATA_SMALL: 
	 packetSize = 60;
	 randRange = 5;
      case E_MSDU_DATA:
	 { 
	    t_vlan vlan;
	    int b_vlan = false;
	    if(1==rand()%2){  //vlan header
	       //------------<generate VLAN>---------------//
	       b_vlan = true;
	       //length = sizeof(t_vlan);
	       vlan.tpid = HTONS(ETHTYPE_VLAN);
	       vlan.priority = 0x6;
	       vlan.cfi = 0;
	       vlan.vid1 = 0;
	       vlan.vid2 = 0;
	    }

	    //-----<Ethernet Type: IP.type = 0x0800>----//
	    short type = HTONS(ETHTYPE_IP);

	    //------------<generate Data>---------------//
	    int i=0;

#ifdef RANDOM_ON
	    int dataLength = packetSize - rand() % randRange;
#else
	    int dataLength = packetSize;
#endif

	    if(dataLength>MAX_MSDU_SIZE)
	    {
	       dataLength = MAX_MSDU_SIZE;
	    }
	    unsigned char * ptrData = CROP_MALLOC(dataLength, "ptrData");
	    //assert(ptrData);

	    CROP_MARK(ptrData, dataLength, "ptrData");
	    ptrData[0] = count;//set for keeping track
	    for(i=1; i < dataLength; i++)
	    {   
	       //ptrData[i] = rand() % 30 + 10;
	       ptrData[i] = i;
	    }
	    //set for keeping track of outgoing msdu count
	    ptrData[i-1]=count;

	    //--------<**generate Ethernet MSDU**>---------//
	    //Check if Vlan tag exist
	    if(b_vlan)
	    {
	       //vlan tag exist
	       length = sizeof(t_ethhdr) + sizeof(type) + dataLength + sizeof(t_vlan);
	       ptrMSDU = CROP_MALLOC(length, "ptrMSDU");
	       //assert(ptrMSDU);

	       CROP_MEMCPY(ptrMSDU, &ethhdr, sizeof(t_ethhdr), "ptrMSDU");
	       CROP_MEMCPY(ptrMSDU+sizeof(t_ethhdr), &vlan, sizeof(t_vlan), "ptrMSDU");
	       CROP_MEMCPY(ptrMSDU+sizeof(t_ethhdr)+sizeof(t_vlan), &type, sizeof(type), "ptrMSDU");
	       CROP_MEMCPY(ptrMSDU+sizeof(t_ethhdr)+sizeof(t_vlan)+sizeof(type), ptrData, dataLength, "ptrMSDU");
	    }
	    else //no VLAN tag
	    {
	       length = sizeof(t_ethhdr) + sizeof(type) + dataLength;
	       ptrMSDU = CROP_MALLOC(length, "ptrMSDU");
	       //assert(ptrMSDU);

	       CROP_MEMCPY(ptrMSDU, &ethhdr, sizeof(t_ethhdr), "ptrMSDU");
	       CROP_MEMCPY(ptrMSDU+sizeof(t_ethhdr), &type, sizeof(type), "ptrMSDU");
	       CROP_MEMCPY(ptrMSDU+sizeof(t_ethhdr)+sizeof(type), ptrData, dataLength, "ptrMSDU");
	    }

	    CROP_FREE(ptrData, "ptrData"); 
	    break;
	 }
	 //different destination addr
      case E_MSDU_DATA_SMALL_DIFF_ADDR: 
	 packetSize = 20;
	 randRange = 5;
      case E_MSDU_DATA_DIFF_ADDR:
	 {
	    //inc the destAddr
	    ethhdr.destAddr[0]++; 
	    t_vlan vlan;
	    int b_vlan = false;
	    if(1==rand()%2){  //vlan header
	       //------------<generate VLAN>---------------//
	       b_vlan = true;
	       //length = sizeof(t_vlan);
	       vlan.tpid = HTONS(ETHTYPE_VLAN);
	       vlan.priority = 0x6;
	       vlan.cfi = 0;
	       vlan.vid1 = 0;
	       vlan.vid2 = 0;
	    }

	    //-----<Ethernet Type: IP.type = 0x0800>----//
	    short type = HTONS(ETHTYPE_IP);

	    //------------<generate Data>---------------//
	    int i=0;

#ifdef RANDOM_ON
	    int dataLength = packetSize - rand() % randRange;
#else
	    int dataLength = packetSize;
#endif

	    if(dataLength>MAX_MSDU_SIZE)
	    {
	       dataLength = MAX_MSDU_SIZE;
	    }
	    unsigned char * ptrData = CROP_MALLOC(dataLength, "ptrData");
	    //assert(ptrData);

	    ptrData[0] = count;//set for keeping track
	    for(i=1; i < dataLength; i++)
	    {   
	       //ptrData[i] = rand() % 30 + 10;
	       ptrData[i]=i;
	    }
	    //set for keeping track of outgoing msdu count
	    ptrData[i-1]=count;

	    //--------<**generate Ethernet MSDU**>---------//
	    //Check if Vlan tag exist
	    if(b_vlan)
	    {
	       //vlan tag exist
	       length = sizeof(t_ethhdr) + sizeof(type) + dataLength + sizeof(t_vlan);
	       ptrMSDU = CROP_MALLOC(length, "ptrMSDU");
	       //assert(ptrMSDU);

	       CROP_MEMCPY(ptrMSDU, &ethhdr, sizeof(t_ethhdr), "ptrMSDU");
	       CROP_MEMCPY(ptrMSDU+sizeof(t_ethhdr), &vlan, sizeof(t_vlan), "ptrMSDU");
	       CROP_MEMCPY(ptrMSDU+sizeof(t_ethhdr)+sizeof(t_vlan), &type, sizeof(type), "ptrMSDU");
	       CROP_MEMCPY(ptrMSDU+sizeof(t_ethhdr)+sizeof(t_vlan)+sizeof(type), ptrData, dataLength, "ptrMSDU");
	    }
	    else //no VLAN tag
	    {
	       length = sizeof(t_ethhdr) + sizeof(type) + dataLength;
	       ptrMSDU = CROP_MALLOC(length, "ptrMSDU");
	       //assert(ptrMSDU);

	       CROP_MEMCPY(ptrMSDU, &ethhdr, sizeof(t_ethhdr), "ptrMSDU");
	       CROP_MEMCPY(ptrMSDU+sizeof(t_ethhdr), &type, sizeof(type), "ptrMSDU");
	       CROP_MEMCPY(ptrMSDU+sizeof(t_ethhdr)+sizeof(type), ptrData, dataLength, "ptrMSDU");
	    }

	    CROP_FREE(ptrData, "ptrData"); 
	    break;
	 } 		    
      default: printf("error in generateMSDU_test()\n"); break;			    
   }
   
   *p_len = length;
   printf("p_len = %d\n", length);
   return ptrMSDU;


   //#]
}

