.PHONY: usage

usage: a
	# Patch ./a.
	python patch.py a
	# Make it executable.
	chmod +x a.patched
	# Run it. Impossible!
	./a.patched

a: a.c
	gcc a.c -o a
