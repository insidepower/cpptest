/// compile : gcc main.c -lpthread
#include <stdio.h>
#include <pthread.h>

#define IS_THREAD 'y'
void *datafile_write_function(void *ptr);
char message_write = IS_THREAD;

void *thread_function2(void *ptr)
{
	printf("thread going to return ")
}

int main(void)
{
	pthread_t write_thread;
	int res = pthread_create( &write_thread, NULL, datafile_write_function, (void*) &message_write);
	printf("thread has been created, waiting for thread to end\n");
	pthread_join(write_thread, NULL);
	printf("thread ended\n");

	int res = pthread_create( &write_thread, NULL, thread_function2, (void*) &message_write);
}

void *datafile_write_function(void *ptr)
{
	if (ptr==NULL){
		printf("ptr is NULL\n");
	}else if ( IS_THREAD == *((char *)ptr) ){
		printf("ptr is %c\n", *((char *) ptr));
	}
	getchar();

	int a=50000;
	while(a--)
		printf("waiting...");

	printf("thread going to end...\n");
}
