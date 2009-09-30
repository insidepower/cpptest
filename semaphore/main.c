/*============================================================================
  ==  @ main @
  ==
  ==  DESC: to test if two sem_post, whether two sem_wait can be executed w/o 
  			stop
  ==  USAGE:
  ==  INPUTS:
  ==  OUTPUTS:
  ==  RETURN:
  ==  IMP NOTE: gcc main.c -lpthread
  ============================================================================*/
#include <stdio.h>
#include <semaphore.h>

int main(void)
{
	sem_t  sem;
	if(-1==sem_init(&sem, 0, 0)){
		printf("err! sem_init\n");
	}

	sem_post(&sem);
	sem_post(&sem);
	sem_wait(&sem);
	sem_wait(&sem);

	printf("dada... done!\n");
	return 0;
}
