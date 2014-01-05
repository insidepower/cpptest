#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netinet/ip.h>
//#include <netinet/udp.h>
#include <arpa/inet.h>
struct vlanhdr{
#if BYTE_ORDER == LITTLE_ENDIAN
	u_char	vid1:4,
		cfi:1,	
		priority:3;
	u_char	vid2;	
	u_short type;
#endif
#if BYTE_ORDER == BIG_ENDIAN
	u_char  cfi:1,	
		priority:3,
		vid1:4;
	u_char vid2;
	u_short type;
#endif
};
struct udphdr {

	u_short uh_sport;               /* source port */
	u_short uh_dport;               /* destination port */
	u_short uh_ulen;                /* udp length */
	u_short uh_sum;                 /* udp checksum */
};

// Function for checksum calculation
// From the RFC, the checksum algorithm is:
//  "The checksum field is the 16 bit one's complement of the one's
//  complement sum of all 16 bit words in the header.  For purposes of
//  computing the checksum, the value of the checksum field is zero."
unsigned short csum(unsigned short *buf, int nwords)
{       //
   unsigned long sum;
   for(sum=0; nwords>0; nwords--)
   {
      sum += *buf++;
      //printf("sum=%lx\n", sum);
   }
   sum = (sum >> 16) + (sum &0xffff);
   sum += (sum >> 16);
   sum =~sum;
   return (unsigned short)(sum);
}

//int bufferSize = ETH_FRAME_LEN;
int dataSize=1200;
int bufferSize=sizeof(struct ethhdr)+sizeof(struct vlanhdr)+sizeof(struct ip)+sizeof(struct udphdr);

int main(void)
{
   bufferSize += dataSize;
	/*target address*/
	struct sockaddr_ll socket_address;

	/*buffer for ethernet frame*/
	void* buffer = (void*)malloc(bufferSize);

	/*pointer to ethenet header*/
	unsigned char* etherhead = buffer;
	
	//point to vlan header
	struct vlanhdr *vlanhdr =buffer +sizeof(struct ethhdr);	
	/*userdata in ethernet frame*/
	unsigned char* data = buffer + sizeof(struct ethhdr)+sizeof(struct vlanhdr)+sizeof(struct ip) + sizeof(struct udphdr);
	
	struct ip *iph = (struct ip *)(buffer + sizeof(struct ethhdr)+4);
	struct udphdr *udph = (struct udphdr *)(buffer + sizeof(struct ethhdr)+4+sizeof(struct ip));

	/*another pointer to ethernet header*/
	struct ethhdr *eh = (struct ethhdr *)etherhead;
	int datalen= sizeof(struct ethhdr)+ 4+ sizeof(struct ip) + sizeof(struct udphdr)+dataSize;
	int send_result = 0;
	int j=0;
   unsigned long	counter=0;

	/*our MAC address*/
	//unsigned char src_mac[6] = {0x00, 0x01, 0x02, 0xFA, 0x70, 0xAA};
	/*other host MAC address*/
	//unsigned char dest_mac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

   unsigned char dest_mac[6] = {0x0 , 0x1A, 0xA0, 0xC5, 0xC6, 0x5A};
   //unsigned char dest_mac[6] = {0x0 , 0x1A, 0xA0, 0xC5, 0xC6, 0x5A};
   unsigned char src_mac[6] = {0x32, 0x75, 0xA5, 0x5A, 0x31, 0x0};

	int s; /*socketdescriptor*/

	//s = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
   s = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	if (s == -1) 
	{
		printf("Error-opening socket\n");
	 	if (errno == EPERM) {
 		    fprintf(stderr, "ping: permission denied. (are you root?)\n");
	 	}
		return 0;
	}

   //---------------------------------------------------------------
   //    F1: ask socket to use a specific interface, rather than 
   //        let it decided by routing table
   //    NOTE: bind has no effect if struct sockaddr_ll socket_address 
   //          was set manually. e.g. socket_address.sll_ifindex  = 3;
   //---------------------------------------------------------------
#if BIND_USING_ETH_NAME
   struct ifreq interface;
   strncpy(interface.ifr_ifrn.ifrn_name, "eth1", IFNAMSIZ);
   if((ioctl(s, SIOCGIFINDEX, &interface)) == -1)
   {
      printf("Error getting Interface index !\n");
      exit(-1);
   }
   else{ printf("%d", interface.ifr_ifrn.index);}


   if(setsockopt(s, SOL_SOCKET, SO_BINDTODEVICE, (char *)&interface, sizeof(interface)) <0 )
   {
      perror("SO_BINDTODEVICE failed");
   }
#else
#ifdef BIND_USING_IF_INDEX
   //YL method
   struct ifreq device;		//## attribute device 
   strcpy(device.ifr_name, "eth1");
   bcopy(device.ifr_hwaddr.sa_data, &src_mac[0], 6);
   //if((ioctl(s, SIOCGIFINDEX, &interface)) == -1)
   if (ioctl(s, SIOCGIFINDEX, &device) ==-1)
   {
      printf("Error getting Interface index !\n");
      exit(-1);
   }
   int deviceIndex=device.ifr_ifindex;             

   struct sockaddr_ll sll;		//## attribute sll 
   sll.sll_family=AF_PACKET;                 
   sll.sll_ifindex=deviceIndex;
   //printf("deviceIndex=%d\n",deviceIndex);
   sll.sll_protocol=htons( ETH_P_ALL );
   //bind the raw socket to the interface
   if (bind(s, (struct sockaddr *) &sll, sizeof(sll))==-1)
   {   
      perror("Error in binding socket to interface");
      return;
   }      
#endif
#endif
   //------------------------------------------------- F1 end //

	/*prepare sockaddr_ll*/
	//while (1)
	{
		/*RAW communication*/
		socket_address.sll_family   = PF_PACKET;	
		/*we don't use a protocoll above ethernet layer
		  ->just use anything here*/
		socket_address.sll_protocol = htons(ETH_P_IP);	
		
		/*index of the network device
		see full code later how to retrieve it*/
		//socket_address.sll_ifindex  = 2;
      //NOTE: getting correct index
      //---------------------------------------------------------------
      //    F2: ask socket to use a specific interface, rather than 
      //        let it decided by routing table
      //---------------------------------------------------------------
      struct ifreq device;		//## attribute device 
      strcpy(device.ifr_name, "eth1");
      //strcpy(device.ifr_name, "eth0");
      //bcopy(device.ifr_hwaddr.sa_data, &src_mac[0], 6);
      if (ioctl(s, SIOCGIFINDEX, &device) ==-1)
      {
         printf("Error getting Interface index !\n");
         exit(-1);
      }
      //if((ioctl(s, SIOCGIFINDEX, &interface)) == -1)
      socket_address.sll_ifindex  = device.ifr_ifindex;
      printf("deviceIndex2=%d\n",device.ifr_ifindex);
      //socket_address.sll_ifindex  = 3;
      //------------------------------------------------- F2 end //
		
		/*ARP hardware identifier is ethernet*/
		socket_address.sll_hatype   = ARPHRD_ETHER;
		
		/*target is another host*/
		socket_address.sll_pkttype  = PACKET_OTHERHOST;
		
		/*address length*/
		socket_address.sll_halen    = ETH_ALEN;		
		/*MAC - begin*/
      //memcpy(socket_address.sll_addr, src_mac, 6);
		socket_address.sll_addr[0]  = 0x00;
		socket_address.sll_addr[1]  = 0x04;
		socket_address.sll_addr[2]  = 0x75;
		socket_address.sll_addr[3]  = 0xC8;
		socket_address.sll_addr[4]  = 0x28;
		socket_address.sll_addr[5]  = 0xE5;
		/*MAC - end*/
		socket_address.sll_addr[6]  = 0x00;/*not used*/
		socket_address.sll_addr[7]  = 0x00;/*not used*/
		printf("ethhdr=%d\n", sizeof(struct ethhdr));
		/*set the frame header*/
		memcpy((void*)buffer, (void*)dest_mac, ETH_ALEN);
		memcpy((void*)(buffer+ETH_ALEN), (void*)src_mac, ETH_ALEN);
		//For VLAN tag
		eh->h_proto = htons(0x8100);
		vlanhdr->priority=7;
		vlanhdr->cfi=0;
		vlanhdr->vid1=0;
		vlanhdr->vid2=0;
		vlanhdr->type=htons(0x0800);
		
		/* we'll now fill in the ip/tcp header values, see above for explanations */
		iph->ip_hl = 5;
		iph->ip_v = 4;
		iph->ip_tos = 0;
		iph->ip_len = htons(sizeof (struct ip) + sizeof (struct udphdr) + dataSize);
		iph->ip_id = htonl (54321);	/* the value doesn't matter here */
		iph->ip_off = 0;
		iph->ip_ttl = 255;
		iph->ip_p = 17;
		iph->ip_sum = 0;		/* set it to 0 before computing the actual checksum later */
		//iph->ip_src.s_addr = inet_addr ("192.168.1.5");/* SYN's can be blindly spoofed */
		iph->ip_src.s_addr = inet_addr ("10.0.0.1");/* SYN's can be blindly spoofed */
		//iph->ip_dst.s_addr = inet_addr ("192.168.1.255");
		iph->ip_dst.s_addr = inet_addr ("10.0.0.2");


		// Fabricate the UDP header
		// Source port number, redundant
		udph->uh_sport = htons(888);
		// Destination port number
		udph->uh_dport = htons(889);
		udph->uh_ulen = htons(sizeof(struct udphdr)+dataSize);



		/*fill the frame with some data*/
		for (j = 0; j < (dataSize); j++) 
		{
#ifdef ENABLE_RANDOM_DATA
			if (j<4)
			{
				data[j]=(unsigned char)((counter>>(8*j))&0xff);	
				printf("data[%d]=0x%x\n", j, (unsigned int)data[j]);			
			}
			else			
				data[j] = (unsigned char)((int) (255.0*rand()/(RAND_MAX+1.0)));
#else
	       data[j]=j;
#endif
		}
		// Calculate the checksum for integrity	
		iph->ip_sum = csum((unsigned short *)iph, sizeof(struct ip)/2);

#if 0		
for (j=0; j<20; j++)
{
	unsigned short *test=buffer+j;
//	printf("test=0x%x\n", *test);
	printf("byte %d=0x%x\n", j, (unsigned char)*test);
}
#endif

		/*send the packet*/
		send_result = sendto(s, buffer, datalen, 0, 
			      (struct sockaddr*)&socket_address, sizeof(socket_address));
		if (send_result == -1) 
		{ 
         perror("Error");
			printf("Sending failed.error no=%d\n", errno);
		}
		else
		{
			printf("Send data successfully.bufferSize=%d\n", bufferSize);
         //print_data((const unsigned char *)buffer, bufferSize);
		}
		usleep(100);
		counter++;
		//return 0;
	}
}

print_data(unsigned char * pchBuf, int size)
{
   unsigned char * mybuffer=pchBuf;
   int i=0;
   for(;i<size; i++)
   {
      printf("0x%2X, ", mybuffer[i]);
      if(((i+1) % 10 == 0) && i>0)
         printf("\n");
   }
   printf("\n");
   //printf("%X, %X, %X, %X, %X\n", mybuffer[0], mybuffer[1], mybuffer[2], mybuffer[3], mybuffer[4]);
   //printf("Send data successfully.(%d)\n", j);
}
