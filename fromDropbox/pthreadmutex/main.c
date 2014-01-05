#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int count = 0;

void* function1( void* arg )
{
    int tmp = 0;

    while( 1 ) {
        printf("f1 try to get lock\n");
        printf("f1 b4: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);
        pthread_mutex_lock( &mutex );
        printf("f1 start: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);
        tmp = ++count;
        printf( "Count is %d\n", tmp );
	sleep(10);
        printf("f1 end: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);
        pthread_mutex_unlock( &mutex );
        printf("f1 af: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);

        /* snooze for 1 second */
	sleep(1);
    }

    return 0;
}

void* function2( void* arg )
{
    int tmp = 0;

    while( 1 ) {
    sleep(1);
        printf("f2 try to get lock\n");
	printf("f2 b4: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);
        pthread_mutex_lock( &mutex );
        printf("f2 start: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);
        tmp = --count;
        printf( "** Count is %d\n", tmp );
        printf("f2 end: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);
        pthread_mutex_unlock( &mutex );
        printf("f2 af: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);

        /* snooze for 2 seconds */
	sleep(1);
    }

    return 0;
}


void* function3( void* arg )
{
    int tmp = 0;
    while( 1 ) {
    sleep(3);
        printf("f3 try to get lock\n");
	printf("f3 b4: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);
        pthread_mutex_lock( &mutex );
        printf("f3 start: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);
        tmp = --count;
        printf( "** Count is %d\n", tmp );
        printf("f3 end: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);
        pthread_mutex_unlock( &mutex );
        printf("f3 af: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);

        /* snooze for 3 seconds */
	sleep(1);
    }

    return 0;
}


void* function4( void* arg )
{
    int tmp = 0;
    while( 1 ) {
    sleep(4);
        printf("f4 try to get lock\n");
	printf("f4 b4: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);
        pthread_mutex_lock( &mutex );
        printf("f4 start: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);
        tmp = --count;
        printf( "** Count is %d\n", tmp );
        printf("f4 end: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);
        pthread_mutex_unlock( &mutex );
        printf("f4 af: mutex.__count(%d), mutex.__lock(%d)\n", mutex.__data.__count, mutex.__data.__lock);

        /* snooze for 3 seconds */
	sleep(1);
    }

    return 0;
}

int main( void )
{
   pthread_t thread1, thread2, thread3, thread4;
    pthread_create( &thread1, NULL, &function1, NULL );
    pthread_create( &thread2, NULL, &function2, NULL );
    pthread_create( &thread3, NULL, &function3, NULL );
    pthread_create( &thread4, NULL, &function4, NULL );

    /* Let the threads run for 60 seconds. */
    sleep( 60 );

    return 0;
}
