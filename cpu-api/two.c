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
    printf( "child: fd = %p\n", fd );
    for ( int i = 0; i < 1000; i++ )
        {
        fwrite( "data from child\n", sizeof(char), strlen( "data from child\n" ), fd );
        }
    fclose( fd );

    }
else
    {
    /* parent process */
    printf( "parent: fd = %p\n", fd );
    for ( int i = 0; i < 1000; i++ )
        {
        fwrite( "data from parent\n", sizeof(char), strlen( "data from parent\n" ), fd );
        }
    fclose( fd );

    }

return 0;

}