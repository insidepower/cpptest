
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
