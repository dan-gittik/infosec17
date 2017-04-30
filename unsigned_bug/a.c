#include <stdio.h>

int main()
{
    unsigned int counter;

    // counter is unsigned, so when it reaches 0, counter-- will cause
    // it to underflow and become 2**32, making this an infinite loop.
    for (counter = 9; counter >= 0; counter--)
        printf("%u\n", counter);

    return 0;
}
