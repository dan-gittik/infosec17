#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int  auth;
    char name[32];

    if (argc < 2) {
        printf("USAGE: %s <name>\n", argv[0]);
        return -1;
    }

    auth = 0;

    strcpy(name, argv[1]);

    if (auth) {
        printf("Impossible!\n");
    }

    return 0;
}
