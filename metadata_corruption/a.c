#include <stdio.h>
#include <string.h>
#include "malloc.h"

int n = 1;

int main(int argc, char* argv[])
{
    char *p1, *p2;

    p1 = dlmalloc(1024);
    p2 = dlmalloc(1024);

    strcpy(p1, argv[1]);

    dlfree(p2);

    printf("%08x\n", n);

    dlfree(p1);

    return 0;
}
