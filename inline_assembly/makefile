.PHONY: usage

usage: a
	# Run ./a (should print 3).
	./a 1

a: a.c
	# -masm=intel makes GCC accept intel syntax Assembly.
	gcc -masm=intel a.c -o a
