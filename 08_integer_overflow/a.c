#include <stdio.h>
#include <string.h>

#define MAX_NAME_SIZE 32

int main(int argc, char* argv[])
{
    char size;
    char name[MAX_NAME_SIZE];

    if (argc < 2) {
        printf("USAGE: %s <name>\n", argv[0]);
        return -1;
    }

    size = strlen(argv[1]);

    if (size > MAX_NAME_SIZE) {
        printf("ERROR: name too long\n");
        return -1;
    }

    strncpy(name, argv[1], size);

    return 0;
}
