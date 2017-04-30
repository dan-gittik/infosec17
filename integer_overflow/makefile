.PHONY: usage

usage: a
	# Run ./a foo (should work).
	./a "foo"
	# Run ./a 'a'*100 (should print "ERROR: name too long").
	./a `python -c "print('a'*100)"` || true
	# Run ./a 'a'*150 (should crash, since (signed char) 150 == -22 < MAX_NAME_SIZE, (unsigned char) 150 overflows char name[32]).
	./a `python -c "print('a'*150)"`

# NOTE: when a command returns a non-zero exit code (like ./a 'a'*100 does), make thinks
# it failed and stops.
# || is bash for "if the left command failed, do the right command", and true is a dummy
# command that always returns zero, so adding "|| true" makes the entire command succeed
# and keep make happy.

a: a.c
	gcc a.c -o a
