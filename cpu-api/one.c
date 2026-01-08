#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int main
    (
    int argc,
    char* argv[]
    )
{
int x = 10;
int fork_id;

fork_id = fork();
assert( fork_id >= 0 );

if ( fork_id == 0 )
    {
    /* child process */
    printf( "child: x = %d\n", x );
    x -= 5;
    printf( "child: x = %d\n", x );
    }
else
    {
    /* parent process */
    printf( "parent: x = %d\n", x );
    x += 5;
    printf( "parent: x = %d\n", x );
    }

return 0;

}