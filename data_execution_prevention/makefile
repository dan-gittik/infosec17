all: no_dep

dep:
	gcc a.c -o a
	execstack -c a
	execstack -q a
	./a || echo "exit code: $$?"

no_dep:
	gcc a.c -o a
	execstack -s a
	execstack -q a
	./a || echo "exit code: $$?"
