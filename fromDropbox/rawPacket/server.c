#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <errno.h>
#include <netinet/in.h>


int s; /*socketdescriptor*/
int length = 0; /*length of the received frame*/
int main()
{
        FILE * fp;
	int i;
	fp=fopen("/log/server.log", "a+");
	unsigned char * buffer = (unsigned char *)malloc(ETH_FRAME_LEN); /*Buffer for ethernet frame*/
	unsigned char dest_mac[6] = {0x32, 0x31, 0xA5, 0x5A, 0x31, 0x32};
	unsigned char src_mac[6] = {0x32, 0x75, 0xA5, 0x5A, 0x31, 0x81};

	s= socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (s == -1) 
	{
	   printf("Error-opening socket\n");
	   if (errno == EPERM) {
	      fprintf(stderr, "ping: permission denied. (are you root?)\n");
	   }
	   return 0;
	}

	while (1)	
	{ 
	   length = recvfrom(s, buffer, ETH_FRAME_LEN, 0, NULL, NULL);
	   if (length == -1) 
	   {
	      printf("Error-length\n");
	      return 0;
	   }
	   else
	   {
	      //printf("%X %X %X %X %X %X, memcmp(%d)\n", buffer[0], buffer[1],buffer[2],buffer[3],buffer[4],buffer[5], memcmp(buffer, &dest_mac[0], 6));
	      if (memcmp(buffer, &dest_mac[0], 6) == 0 && memcmp(buffer+6, src_mac, 6) == 0)
         {
            printf("Server received: Size of Data =%d\n", length);
            fprintf(fp, "\n\nSize of Data: %d\n", length);
            for(i=0; i<length; i++)
            {
               fprintf(fp, "0x%2X, ", buffer[i]);
               if(i>0 && ((i+1)%10 == 0))
               {
                  fprintf(fp, "\n");
               }
            }
            fprintf(fp, "\n");
            fflush(fp);
         }
	   }
	}
	fclose(fp);
}


