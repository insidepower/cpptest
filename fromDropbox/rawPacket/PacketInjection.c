#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<features.h>
#include<linux/if_packet.h>
#include<linux/if_ether.h>
#include<errno.h>
#include<sys/ioctl.h>
#include<net/if.h>
#include <string.h>

#define PACKET_LENGTH	1024


int CreateRawSocket(int protocol_to_sniff)
{
	int rawsock;

	if((rawsock = socket(PF_PACKET, SOCK_RAW, htons(protocol_to_sniff)))== -1)
	{
		perror("Error creating raw socket: ");
		exit(-1);
	}

	return rawsock;
}

int BindRawSocketToInterface(char *device, int rawsock, int protocol)
{
	
	struct sockaddr_ll sll;
	struct ifreq ifr;

	//bzero(&sll, sizeof(sll));
	//bzero(&ifr, sizeof(ifr));
	memset(&sll, 0, sizeof(sll));
	memset(&ifr, 0, sizeof(ifr));
	
	/* First Get the Interface Index  */


	strncpy((char *)ifr.ifr_name, device, IFNAMSIZ);
	if((ioctl(rawsock, SIOCGIFINDEX, &ifr)) == -1)
	{
		printf("Error getting Interface index !\n");
		exit(-1);
	}

	/* Bind our raw socket to this interface */

	sll.sll_family = AF_PACKET;
	sll.sll_ifindex = ifr.ifr_ifindex;
	sll.sll_protocol = htons(protocol); 


	if((bind(rawsock, (struct sockaddr *)&sll, sizeof(sll)))== -1)
	{
		perror("Error binding raw socket to interface\n");
		exit(-1);
	}

	return 1;
	
}


int SendRawPacket(int rawsock, unsigned char *pkt, int pkt_len)
{
	int sent= 0;

	/* A simple write on the socket ..thats all it takes ! */

	if((sent = write(rawsock, pkt, pkt_len)) != pkt_len)
	{
		return 0;
	}

	return 1;
	

}


/* argv[1] is the device e.g. eth0
   argv[2] is the number of packets to send
*/
 
main(int argc, char **argv)
{

	int raw;
	unsigned char packet[PACKET_LENGTH];
	int num_of_pkts;
	
	/* Set the packet to all A's */
	
	memset(packet, 'A', PACKET_LENGTH);

	/* Create the raw socket */

	raw = CreateRawSocket(ETH_P_ALL);

	/* Bind raw socket to interface */

	BindRawSocketToInterface(argv[1], raw, ETH_P_ALL);

	num_of_pkts = atoi(argv[2]);

	while((num_of_pkts--)>0)
	{

		if(!SendRawPacket(raw, packet, PACKET_LENGTH))
		{
			perror("Error sending packet");
		}
		else
		{
			printf("Packet sent successfully\n");
		}
	}

	close(raw);

	return 0;
}

