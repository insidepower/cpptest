/* 
 * usage: will call sigHandler when SIGUSR1 
 * is received 
 */

#include <stdio.h>
#include <signal.h>

void sigHandler(int sigNum)
{
   printf("SIGUSR1 received\n");
}

int main(void)
{
   signal (SIGUSR1, sigHandler);
   while(1);
}
