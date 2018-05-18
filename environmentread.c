#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf( "HOSTNAME = %s\n", getenv( "HOSTNAME"));
    printf( "UUID = %s\n", getenv( "UUID"));
    printf( "TERM     = %s\n", getenv( "TERM"    ));
    printf( "SHELL    = %s\n", getenv( "SHELL"   ));
    printf( "QTDIR    = %s\n", getenv( "QTDIR"   ));
    printf( "HOME     = %s\n", getenv( "HOME"    ));
    return 0;
}
