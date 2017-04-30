.PHONY: usage

usage: a
	# Run ./a 'a'*32 + 0x11111111 (should print "Impossible!").
	./a `python -c "print('a'*32 + '\x11\x11\x11\x11')"`

a: a.c
	gcc -fno-stack-protector a.c -o a
