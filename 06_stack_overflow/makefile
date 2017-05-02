.PHONY: usage

usage: a
	# Set the execstack bit (make the stack executable).
	execstack -s a
	# Query the execstack bit (should be "X a").
	execstack -q a
	# Run exploit.py and print its exit code (should be 3).
	python exploit.py || echo "exit code: $$?"

# NOTE: when a command returns a non-zero exit code (like exploit.py does), make thinks
# it failed and stops.
# || is bash for "if the left command failed, do the right command", so when exploit.py
# "fails", it runs "echo $?" ($ is escaped), which prints the last exit code, and since
# echo returns zero, the entire command succeeds and make is happy.

a: a.c
	gcc -fno-stack-protector a.c -o a
