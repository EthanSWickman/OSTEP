#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int pipe_wait
    (
    void
    );

int signal_wait 
    (
    void
    );

int main
    (
    int argc,
    char* argv[]
    )
{

// return pipe_wait();
return signal_wait();

}

int pipe_wait
    (
    void
    )
{
int fork_id;
int fds[2];

pipe2( fds, O_NONBLOCK );
fork_id = fork();
assert( fork_id >= 0 );

if( fork_id == 0 )
    {
    /* child process */
    close( fds[0] ); // close read end
    printf( "hello (%d)\n", getpid() );
    write( fds[1], "x", 1 ); // signal parent
    close( fds[1] ); // close write end

    }
else 
    {
    /* parent process */
    char buf[1];
    close( fds[1] ); // close write end
    while( read( fds[0], &buf, 1 ) <= 0 ) // wait for child
        {
        // printf( "spin\n" );
        }
    printf( "goodbye (%d)\n", getpid() );
    close( fds[0] ); // close read end

    }

return 0;

}

void handle
    (
    int signum
    )
{
    // empty handler to interrupt pause
}

int signal_wait
    (
    void
    )
{
int fork_id;

fork_id = fork();
assert( fork_id >= 0 );

signal( SIGUSR1, handle ); // ignore signal to avoid default termination

if( fork_id == 0 )
    {
    /* child process */
    sleep( 1 );
    printf( "hello (%d)\n", getpid() );
    kill( getppid(), SIGUSR1 ); 

    }
else 
    {
    /* parent process */
    pause();
    printf( "goodbye (%d)\n", getpid() );

    }

return 0;

}
