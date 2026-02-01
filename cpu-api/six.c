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

    }
else 
    {
    /* parent process */
    printf( "fork_id: %d\n", fork_id );
    printf( "goodbye %d\n", waitpid( fork_id, NULL, 0) );

    }

return 0;

}

