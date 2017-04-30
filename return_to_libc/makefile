.PHONY: no_exit

no_exit: a
	# Run exploit1.py (should open a shell and crash when it exits).
	python exploit1.py

.PHONY: with_exit

with_exit: a
	# Run exploit2.py (should open a shell, exit cleanly, and print its exit code (should be 3)).
	python exploit2.py || echo "exit code: $$?"

# NOTE: when a command returns a non-zero exit code (like exploit.py does), make thinks
# it failed and stops.
# || is bash for "if the left command failed, do the right command", so when exploit.py
# "fails", it runs "echo $?" ($ is escaped), which prints the last exit code, and since
# echo returns zero, the entire command succeeds and make is happy.

a: a.c
	gcc -fno-stack-protector a.c -o a
