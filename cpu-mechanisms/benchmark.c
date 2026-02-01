#define _GNU_SOURCE
#include <stdio.h>
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
#define NUM_CALLS 100000000

long int ms;
struct timeval time;

gettimeofday( &time, NULL ); 
ms = time.tv_sec * 1000 + time.tv_usec / 1000;

for( int i = 0; i < NUM_CALLS; i++ )
    {
    struct stat stats;
    stat( "benchmark.c", &stats );
    }

gettimeofday( &time, NULL );
ms = time.tv_sec * 1000 + time.tv_usec / 1000 - ms;

printf( "time taken: %f\n", (float) ms / 1000 );
printf( "per call: %f\n", (double) ( (double) ms / 1000 ) / NUM_CALLS );

return 0;

}