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

#include "msdu.h"
struct ifreq interface;

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
	unsigned char src_mac[6] = {0x00, 0x01, 0x02, 0xFA, 0x70, 0xAA};
	
	/*other host MAC address*/
	//unsigned char dest_mac[6] = {0x00, 0x04, 0x75, 0xC8, 0x28, 0xE5};
	//unsigned char dest_mac[6] = {0xEF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF};
	unsigned char dest_mac[6] = {0x32, 0x75, 0xA5, 0x5A, 0x31, 0};

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
