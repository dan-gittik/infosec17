.PHONY: usage

usage: a
	# Run ./a and print 13*4 bytes off the stack.
	./a "%08x %08x %08x %08x %08x %08x %08x %08x %08x %08x %08x %08x %08x"
	# Disassemble ./a to check out what's going on.
	objdump -M intel -d a | grep '<main>' -A17
	# I got (right to left):
	#   00000002  That's argc (call ./a "%08x %08x %08x %08x %08x %08x %08x %08x %08x %08x %08x %08x %08x" "foo" and see it become 00000003)
	#   b7e29637  That's main's return address to some libc initialization function.
	#   00000000
	#   b7fc3000
	#   b7fc3000
	#   b7e29637  16 bytes of garbage due to stack alignment (AND ESP, 0xfffffff0)
	#   00000000  That looks like EBP, which may be initially 0.
	#   bffff630  That's ECX (since we have PUSH ECX (notice this looks like a stack address, and indeed earlier we have LEA ECX, [ESP+4]))
	#   b7fc33dc  4 bytes of garbage due to stack alignment (SUB ESP, 0x4)
	#   deadbeaf  That's us!
	#   bffff6d0
	#   bffff6c4  8 bytes of garbage due to stack alignment (SUB ESP, 0x8)
	#   00000002  That's EAX (since we have PUSH EAX).

a: a.c
	# -masm=intel makes GCC accept Intel syntax Assembly.
	# -Wno-format-security removes GCC's warning that format is not a string literal.
	gcc -masm=intel -Wno-format-security a.c -o a -Wno-format-security
