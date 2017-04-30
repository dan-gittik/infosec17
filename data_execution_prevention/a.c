int main()
{
    char shellcode[] = (
        "\xb8\x01\x00\x00\x00" // MOV EAX, 1 # exit syscall
        "\xbb\x03\x00\x00\x00" // MOV EBX, 3 # exit code
        "\xcd\x80"             // INT 80
    );

    // Cast the shellcode into a function (that receives nothing and returns void).
    void (*f)() = (void (*)) shellcode;

    // Call the function (and thus invoke the shellcode).
    f();

    return 0;
}
