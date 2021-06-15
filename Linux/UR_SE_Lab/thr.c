#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* gcc thr.c -o thr -lpthread */

#define NUM_THREAD 4

void *child_thread ();

int main ( int argc, char ** argv )

{

    pthread_t      pthread_hndl[NUM_THREAD];
    pthread_attr_t pthread_attr;
    int            ret_val[NUM_THREAD], arg_to_be_sent[NUM_THREAD], i;

    printf("Hello World from Main Program.\n");

    pthread_attr_init ( &pthread_attr );

    for ( i=0; i < NUM_THREAD; i++ )
    {
        arg_to_be_sent[i] = i;
        ret_val[i] = pthread_create ( &pthread_hndl[i], &pthread_attr, child_thread, &arg_to_be_sent[i] );
        if ( ret_val[i] != 0 )  printf ("Error in pthread_create\n");
    }


    for ( i=0; i < NUM_THREAD; i++ )
        pthread_join ( pthread_hndl[i], NULL );

    exit ( 0 );

}

void *child_thread ( int * num_ptr )
{

    int num, *number_ptr;

    number_ptr=num_ptr;
    num = *number_ptr;
    printf ("Hello from Child Thread: Received Number = %d\n", num );
    pthread_exit (0);

}
