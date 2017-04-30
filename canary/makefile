.PHONY: usage

usage: a
	# Run ./a 'a'*100 (should crash because of canary corruption).
	./a `python -c "print('a'*100)"`

a: a.c
	gcc a.c -o a
