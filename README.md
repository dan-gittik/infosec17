# Introduction to Information Security 2017

This is an auxiliary repository with code examples to some of the vulnerabilities, exploits and other stuff I
covered in class. I've also added several links to cool articles and videos that demonstrate how to "harness"
what we learn to more effectively think about and solve problems.

## Examples

1. **Inline Assembly**

   This example demonstrates how to inline Assembly code in a C program, and even read/write values from C to Assembly.

2. **Linux**

   This example covers two Linux topics: how permissions on files and directories work, and how a filesystem is mounted.

3. **Binaries**

   This example demonstrates how the static linker does relocations and patches object files in the compilation process.

4. **Patching**

   This example demonstrates how a binary can be patched (with Python) to alter its execution flow.

5. **Variable Overflow**

   This example demonstrates how a buffer overflow on the stack can be used to overwrite a variable and thus alter the program execution flow.

6. **Stack Overflow**

   This example demonstrates how a buffer overflow on the stack can be used to overwrite the return address and hijack control.

7. **Unsigned Bug**
   
   This example demonstrates how an unsigned int can overflow (or rather, underflow) and cause a bug.

8. **Integer Overflow**

   This example demonstrates how a mixup between signed and unsigned integers can cause an integer overflow, bypass a seemingly safe copy, and overflow a buffer.

9. **Canary**

   This example demonstrates how canaries are used to protect from buffer overflows on the stack.

10. **Format String**

    This example demonstrates how format string vulnerabilities can cause information disclosure (which can then be used in another exploit).

11. **DEP**
   
    This example demonstrates how data execution prevention makes the stack non-executable.

12. **Return to Libc**

    This example demonstrates how a buffer overflow on a non-exectuable stack can hijack control by jumping to libc functions.

13. **ROP**

    This example demonstrates how a buffer overflow on a non-executable stack can hijack control by jumping to gadgets in executable segments.

14. **Heap Overflow**

    This example demonstrates how a buffer overflow on the heap can overwrite a function pointer and hijack control.

15. **Use After Free**

    This example demonstrates how a use after free bug can be exploited to acquire memory referenced by a wild pointer, rewrite it and hijack control.

16. **Metadata Corruption**

    This example demonstrates how a buffer overflow on the heap can overwrite dlmalloc metadata and write to arbitrary memory, and how this can be used to overwrite a PLT entry and hijack control.

## References

1. [Raymond Hettinger: Transforming Code into Beautiful, Idiomatic Python](https://www.youtube.com/watch?v=OSGv2VnC0go).

2. [Raymond Hettinger: Beyond Pep-8](https://www.youtube.com/watch?v=wf-BqAjZb8M).

3. [David Beazley: Python 3 Metaprogramming](https://www.youtube.com/watch?v=sPiWg5jSoZI).

4. [David Beazley: Python Concurrency from the Ground Up](https://www.youtube.com/watch?v=MCs5OvhV9S4).

5. [David Beazley: Discovering Python](https://www.youtube.com/watch?v=RZ4Sn-Y7AP8) (mainly inspirational).

6. [Brandon Rhodes: How to Shut Down Tolkien](https://www.youtube.com/watch?v=qVlqBxpCG24) (mainly inspirational).

7. [Gary Bernhardt: The Unix Chainsaw](https://www.youtube.com/watch?v=sCZJblyT_XM).

8. [Awesome Lists](https://github.com/sindresorhus/awesome).

   - [Awesome Python List](https://github.com/vinta/awesome-python).

   - [Awesome Bash List](https://github.com/awesome-lists/awesome-bash).

   - [Awesome Infosec List](https://github.com/onlurking/awesome-infosec).

   - [Awesome Reversing List](https://github.com/fdivrp/awesome-reversing).
