.PHONY: usage

usage: a
	# Run ./a (should print 3).
	./a 1

a: a.c
	# -masm=intel makes GCC accept Intel syntax Assembly.
	gcc -masm=intel a.c -o a
