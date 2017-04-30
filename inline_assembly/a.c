#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int input, output;

    if (argc != 2) {
        printf("USAGE: %s <number>\n", argv[0]);
        return -1;
    }

    input = atoi(argv[1]);

    // This weird notation reads a C value into Assembly.
    asm("MOV EAX, %0"
       :
       : "r"(input));

    // To call Assembly in C code, use the asm("...") directive.
    asm("MOV EBX, 1");
    asm("ADD EAX, EBX");

    // This can also be done with a single asm("...") directive,
    // because adjacent C strings are concatenated.
    asm(
        "MOV EBX, 1;"
        "ADD EAX, EBX;"
    );

    // This weird notation read an Assembly value into C.
    asm("MOV %0, EAX"
        : "=r"(output));

    printf("%d\n", output);
    
    return 0;
}
