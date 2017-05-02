#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct log_t {
    void (*write)(char* message);
};

void log_write(char* message)
{
    printf("%s\n", message);
}

int main(int argc, char* argv[])
{
    char* username;
    char* password;
    struct log_t* log;

    if (argc < 3) {
        printf("USAGE: %s <username> <password>\n", argv[0]);
        return -1;
    }

    username = malloc(32);
    password = malloc(32);

    log = malloc(sizeof(struct log_t));
    log->write = log_write;

    strcpy(username, argv[1]);
    strcpy(password, argv[2]);

    log->write(username);

    free(log);
    free(password);
    free(username);

    return 0;
}
