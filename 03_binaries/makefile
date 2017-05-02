no_relocation: a.o
	# Local variables are embedded directly into the code, so no relocations by the static linker are necessary.
	# The only symbol in a is main (T stands for text, as it's a function).
	nm a.o
	# x and y are embedded as "MOV [EBP-8], 1" and "MOV [EBP-4], 2".
	objdump -M intel -d a.o
	# This stand-alone code compiles and runs as expected.
	gcc a.o -o a
	./a || echo "exit code: $$?"

undefined_reference: b.o
	# Global variables need to be relocated by the static linker once all the binaries are available to it.
	# x and y are missing symbols (U stands for undefined).
	nm b.o
	# The code contains zeroes that will be rewired by the static linker to x and y once they're available.
	objdump -M intel -d b.o
	# See how the relocation instructions point exactly to the offsets of the zeroes that must be patched?
	objdump -r b.o
	# Without them, this code won't compile.
	gcc b.o -o b

undefined_main: c.o
	# This code defines x and y, but has no main, so it won't compile.
	nm c.o
	objdump -M intel -d c.o
	gcc c.o -o c

static_linking: b.o c.o
	# However, together b.o and c.o can complete each other.
	gcc b.o c.o -o bc
	./bc || echo "exit code: $$?"
	# All the symbols are resolved.
	nm bc | grep -wE 'x|y'
	# All the zeroes were patched (see how the point to x and y?).
	objdump -M intel -d bc | grep '<main>' -A10

global_variables: d.o
	# In fact, global variables are always postponed for relocation, even in this stand-alone code:
	nm d.o
	objdump -M intel -d d.o
	# However, since it does contain all the information necessary for the relocations, it can be compiled.
	gcc d.o -o d
	./d || echo "exit code: $$?"
	nm d | grep -wE 'x|y'
	objdump -M intel -d d | grep '<main>' -A10

a.o: a.c
	gcc -c a.c -o a.o

b.o: b.c
	gcc -c b.c -o b.o

c.o: c.c
	gcc -c c.c -o c.o

d.o: d.c
	gcc -c d.c -o d.o
