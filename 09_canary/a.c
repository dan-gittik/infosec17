#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char name[32];

    if (argc < 2) {
        printf("USAGE: %s <name>\n", argv[0]);
        return -1;
    }

    strcpy(name, argv[1]);

    return 0;
}
