#include <stdio.h>

int main(int argc, char* argv[])
{
    asm("PUSH 0xdeadbeaf");

    if (argc < 2) {
        printf("USAGE: %s <name>\n", argv[0]);
        return -1;
    }

    printf(argv[1]);
    printf("\n");

    asm("SUB ESP, 4");

    return 0;
}
