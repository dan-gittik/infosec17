all: no_dep

no_dep:
	gcc a.c -o a
	# set the execstack bit (make the stack executable).
	execstack -s a
	# query the execstack bit (should be "X a").
	execstack -q a
	# Run ./a and print its exit code (should be 3).
	./a || echo "exit code: $$?"

dep:
	gcc a.c -o a
	# clear the execstack bit (make the stack NOT executable).
	execstack -c a
	# query the execstack bit (should be "- a").
	execstack -q a
	# Run ./a and print its exit code (should crash).
	./a || echo "exit code: $$?"

