/*
 * passing signal to another process
 * through kill() function
 */

#include <signal.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
   int pid = atoi(argv[1]);
   printf("pid received: %d\n",pid);
   kill(pid, SIGUSR1);
   return 0;
}
