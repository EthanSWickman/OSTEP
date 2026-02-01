#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

int main
    (
    int argc,
    char* argv[]
    )
{
#define NUM_CALLS ( 100000000 )

int fds[ 2 ];
pid_t fork_id;
long int ms;
struct timeval time;
cpu_set_t cpuset;

pipe( fds );

gettimeofday( &time, NULL ); 
ms = time.tv_sec * 1000 + time.tv_usec / 1000;

fork_id = fork();

if( fork_id == 0 )
    {
    /* child process (writer) */
    CPU_SET( 0, &cpuset );
    sched_setaffinity( 0, sizeof(cpu_set_t), &cpuset );
    close( fds[ 0 ] );
    for( int i = 0; i < NUM_CALLS; i++)
        {
        write( fds[ 1 ], "x", 1 );
        }
    close( fds[ 1 ] );
    exit( 0 );

    }
else 
    {
    /* parent process (reader) */
    CPU_SET( 0, &cpuset );
    sched_setaffinity( 0, sizeof(cpu_set_t), &cpuset );
    char buffer[1];

    close( fds[ 1 ] );
    while( read( fds[ 0 ], buffer, 1 ) )
        {
        }
    close( fds[ 0 ] );

    }

gettimeofday( &time, NULL );
ms = time.tv_sec * 1000 + time.tv_usec / 1000 - ms;

printf( "time taken: %d\n", ms );
printf( "per call: %f\n", (double) ( ms ) / NUM_CALLS );

return 0;

}