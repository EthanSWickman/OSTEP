#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

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
    printf( "child execing\n" );

    }
else 
    {
    /* parent process */
    execl( "/bin/ls", "/home/wickman" );
    printf( "parent exiting\n" );

    }

return 0;

}

