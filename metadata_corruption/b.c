#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

void* dlmalloc(size_t);
void  dlfree(void*);

int main(int argc, char* argv[])
{
    char *p1, *p2;

    p1 = dlmalloc(1024);
    p2 = dlmalloc(1024);

    // Make the heap executable.
    mprotect((void*) ((int) p1 &~(4096-1)), 1024, PROT_READ | PROT_WRITE | PROT_EXEC);

    strcpy(p1, argv[1]);

    dlfree(p2);
    dlfree(p1);

    return 0;
}
