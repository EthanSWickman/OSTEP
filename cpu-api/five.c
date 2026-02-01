#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

int main
    (
    int argc,
    char* argv[]
    )
{
int fork_id;

fork_id = fork();
assert( fork_id >= 0 );

if( fork_id == 0 )
    {
    /* child process */
    printf( "hello\n" );
    printf( "hello again %d\n", wait( NULL ) );

    }
else 
    {
    /* parent process */
    printf( "goodbye %d\n", wait( NULL ) );

    }

return 0;

}

