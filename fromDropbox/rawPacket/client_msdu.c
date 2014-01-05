#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <errno.h>
//#include <net/if.h>
#include<sys/ioctl.h>
#include <netinet/in.h>

#include "MemDebug.h"
#include "client_msdu.h"
/*==============================================================================
 == global 
==============================================================================*/
int count;
int packetSize;
int randRange;
int length;
unsigned char * ptrMSDU;
int false=0;
int true=1;

int testSequence[TOTAL_TEST_CASE] =
{
   E_MSDU_DATA,
   //E_MSDU_DATA_SMALL,
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
//unsigned char src_mac[6] = {0x0 , 0x1A, 0xA0, 0xC5, 0xC6, 0x5A};
//unsigned char dest_mac[6] = {0x32, 0x75, 0xA5, 0x5A, 0x31, 0x0};
unsigned char dest_mac[6] = {0x0 , 0x1A, 0xA0, 0xC5, 0xC6, 0x5A};
unsigned char src_mac[6] = {0x32, 0x75, 0xA5, 0x5A, 0x31, 0x0};

struct ifreq interface;
/*==============================================================================
 ==  @ generateMSDU @
 ==
 ==  DESC:
 ==  USAGE:
 ==  INPUTS:
 ==  OUTPUTS:
 ==  RETURN:
 ==  IMP NOTE:
==============================================================================*/

unsigned char * generateMSDU(int *p_len) {
   //#[ operation generateMSDU(int) 
   ++count;
   //------------<DA and SA>---------------//
   t_ethhdr ethhdr;
   CROP_MARRAY(&ethhdr, sizeof(ethhdr), "ethhdr");
   //packetSize = MAX_MSDU_SIZE-110;
   //packetSize=900;
   packetSize = 42;
   randRange = 200; 

   //unsigned char src_mac[6] = {0x00, 0x01, 0x02, 0xFA, 0x70, 0xAA};
   //unsigned char src_mac[6] = {0, 0x1E, 0x58, 0x3E, 0x83, 0x1E};

   /*other host MAC address*/
   //unsigned char dest_mac[6] = {0x00, 0x04, 0x75, 0xC8, 0x28, 0xE5};
   //unsigned char dest_mac[6] = {0xEF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF};
   //unsigned char dest_mac[6] = {0x32, 0x31, 0xA5, 0x5A, 0x31, 0x32};
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
	 packetSize = 42;
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
	       //vlan.priority = 0x6;
	       vlan.priority = 0x2;
	       vlan.cfi = 0;
	       vlan.vid1 = 0;
	       vlan.vid2 = 0;
	    }

	    //-----<Ethernet Type: IP.type = 0x0800>----//
	    short type = HTONS(ETHTYPE_IP);
	    //short type = 0x0888;

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
          printf("vlan priority=%d\n", vlan.priority);
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
}

/*==============================================================================
 ==  @ main @
 ==
 ==  DESC:
 ==  USAGE:
 ==  INPUTS:
 ==  OUTPUTS:
 ==  RETURN:
 ==  IMP NOTE:
==============================================================================*/
int main()
{
	/*target address*/
	struct sockaddr_ll socket_address;
	
	/*buffer for ethernet frame*/
	void* buffer = (void*)malloc(ETH_FRAME_LEN);
	 
	/*pointer to ethenet header*/
	unsigned char* etherhead = buffer;
		
	/*userdata in ethernet frame*/
	unsigned char* data = buffer + 14;
		
	/*another pointer to ethernet header*/
	struct ethhdr *eh = (struct ethhdr *)etherhead;
	 
	int send_result = 0;
	int j=0;
	
	/*our MAC address*/
	//unsigned char src_mac[6] = {0x00, 0x01, 0x02, 0xFA, 0x70, 0xAA};
	
	/*other host MAC address*/
	//unsigned char dest_mac[6] = {0x00, 0x04, 0x75, 0xC8, 0x28, 0xE5};
	//unsigned char dest_mac[6] = {0xEF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF};
	//unsigned char dest_mac[6] = {0x32, 0x75, 0xA5, 0x5A, 0x31, 0};

	int s; /*socketdescriptor*/

	s = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (s == -1) 
	{
		printf("Error-opening socket\n");
	 	if (errno == EPERM) {
 		    fprintf(stderr, "ping: permission denied. (are you root?)\n");
	 	}
		return 0;
	}

	/* ask socket to use a specific interface, rather than let it decided
	 * by routing table
	 */
	strncpy(interface.ifr_ifrn.ifrn_name, "eth1", IFNAMSIZ);
	if((ioctl(s, SIOCGIFINDEX, &interface)) == -1)
	{
		printf("Error getting Interface index !\n");
		exit(-1);
	}


	if(setsockopt(s, SOL_SOCKET, SO_BINDTODEVICE, (char *)&interface, sizeof(interface)) <0 )
	{
	    perror("SO_BINDTODEVICE failed");
	}

	int optval=0;
	int optlen=sizeof(int);
	//if(getsockopt(s, SOL_SOCKET, ))

	/*prepare sockaddr_ll*/

	/*RAW communication*/
	socket_address.sll_family   = PF_PACKET;	
	/*we don't use a protocoll above ethernet layer
	  ->just use anything here*/
	socket_address.sll_protocol = htons(ETH_P_IP);	

	/*index of the network device
	  see full code later how to retrieve it*/
	//socket_address.sll_ifindex  = 2;
	socket_address.sll_ifindex = interface.ifr_ifindex;

	/*ARP hardware identifier is ethernet*/
	socket_address.sll_hatype   = ARPHRD_ETHER;

	/*target is another host*/
	socket_address.sll_pkttype  = PACKET_OTHERHOST;

	/*address length*/
	socket_address.sll_halen    = ETH_ALEN;		
	/*MAC - begin*/
	socket_address.sll_addr[0]  = 0x00;		
	socket_address.sll_addr[1]  = 0x04;		
	socket_address.sll_addr[2]  = 0x75;
	socket_address.sll_addr[3]  = 0xC8;
	socket_address.sll_addr[4]  = 0x28;
	socket_address.sll_addr[5]  = 0xE5;
	/*MAC - end*/
	socket_address.sll_addr[6]  = 0x00;/*not used*/
	socket_address.sll_addr[7]  = 0x00;/*not used*/

	if((bind(s, (struct sockaddr *)&socket_address, sizeof(socket_address)))== -1)
	{
		perror("Error binding raw socket to interface\n");
		exit(-1);
	}

	/*set the frame header*/
	memcpy((void*)buffer, (void*)dest_mac, ETH_ALEN);
	memcpy((void*)(buffer+ETH_ALEN), (void*)src_mac, ETH_ALEN);
	eh->h_proto = htons(0x8100);
	/*fill the frame with some data*/
	//for (j = 0; j < (1500); j++) {
	for (j = 0; j < (50); j++) {
	   //data[j] = (unsigned char)((int) (255.0*rand()/(RAND_MAX+1.0)));
	   data[j]=j;
	}
      #define IFNAME "eth1"
	strncpy(interface.ifr_ifrn.ifrn_name, IFNAME, IFNAMSIZ);
	if (setsockopt(s, SOL_SOCKET, SO_BINDTODEVICE, \
		 (char *)&interface, sizeof(interface))  < 0) {
	   perror("SO_BINDTODEVICE failed");
	}

	/*send the packet*/
	//send_result = sendto(s, buffer, ETH_FRAME_LEN, 0, 
#define WAIT_TIME 50000000
//#define WAIT_TIME 10000000
//#define WAIT_TIME 1000000000
	int wait = WAIT_TIME;
	int msdu_len;
	 unsigned char * ptrMSDU;
	for(j=0; j<1; j++)
	{
	   data[49]=0xAA;
#define USE_MSDU
#ifdef USE_MSDU
      printf("use_MSDU\n");
	 ptrMSDU= generateMSDU(&msdu_len);
#else
	   msdu_len=14+50;
	   ptrMSDU=buffer;
#endif
	   send_result = sendto(s, ptrMSDU, msdu_len, 0, 
		 (struct sockaddr*)&socket_address, sizeof(socket_address));
	   if (send_result == -1) 
	   { 	
	      printf("Sending failed.\n");
	   }
	   else
	   {
	      unsigned char * mybuffer =buffer;
	      int i=0;
	      for(;i< msdu_len; i++)
	      {
		  printf("0x%2X, ", ptrMSDU[i]) ;
		  if(((i+1) % 10 == 0) && i>0)
		     printf("\n");
	      }
	      printf("\n");
	      //printf("%X, %X, %X, %X, %X\n", mybuffer[0], mybuffer[1], mybuffer[2], mybuffer[3], mybuffer[4]);
	      printf("Send data successfully.(%d)\n", j);
	   }
	   //sleep(1);
	   while(wait--);
	   wait = WAIT_TIME;
	}
	return 0;
}
