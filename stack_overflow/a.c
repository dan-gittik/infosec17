#include <stdio.h>
#include <string.h>

void f(char* arg)
{
    char buff[1024];
    strcpy(buff, arg);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("USAGE: %s <buff>\n", argv[0]);
        return -1;
    }
    
    f(argv[1]);

    return 0;
}
