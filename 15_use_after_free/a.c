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

    log = malloc(32);
    log->write = log_write;
    
    // This is usually much more obscure (happens in some other object's destructor or in another thread).
    free(log);

    password = malloc(32);
    username = malloc(32);

    strcpy(username, argv[1]);
    strcpy(password, argv[2]);

    // Use after free.
    log->write(username);

    free(username);
    free(password);

    return 0;
}
