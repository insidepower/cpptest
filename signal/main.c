#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void ctrlzHandler(int sig)
{
	printf("haha, ctrlzHandler\n");
}

void end_program(int sig)
{
	printf("end_program\n");
	exit(0);
}

int main(void)
{
	struct sigaction act;
	act.sa_handler = ctrlzHandler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if(-1==sigaction(SIGTSTP, &act, 0)){
		perror("sigaction failed");
	}

	act.sa_handler = end_program;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if(-1==sigaction(SIGINT, &act, 0)){
		perror("sigaction failed");
	}

	while(1);

	return 0;
}

