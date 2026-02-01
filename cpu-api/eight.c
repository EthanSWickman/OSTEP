#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdbool.h>

int main
    (
    int argc,
    char* argv[]
    )
{
pid_t reader;
pid_t writer;
int fds[2];

pipe( fds );

reader = fork();
if( reader == 0 )
    {
    char buffer[6];
    /* reader process */
    while( true )
        {
        read( fds[ 0 ], buffer, 6 );
        printf( "%s\n", buffer );
        }
    }

writer = fork();
if( writer == 0 )
    {
    /* writer process */
    while( true )
        { 
        write( fds[ 1 ], "hello", 6 );
        sleep( 1 );
        }

    }

if( reader != 0 && writer != 0 )
    {
    /* parent process */
    waitpid( reader, NULL, 0 );
    waitpid( writer, NULL, 0 );

    }

return 0;

}
