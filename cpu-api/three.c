#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

int main
    (
    int argc,
    char* argv[]
    )
{
int fork_id;
FILE* fd;

fd = fopen( "file.txt", "w" );

fork_id = fork();
assert( fork_id >= 0 );

if ( fork_id == 0 )
    {
    /* child process */
    printf( "hello" );

    }
else 
    {
    /* parent process */
    printf( "goodbye" );

    }

return 0;
}


// todo ESW -- finish these 
// two ways to make sure that child finishes first without wait: 
//  1) parent waits for child to write to a pipe 
//  2) parent waits for a signal from child 