kldmem: ./kldmem.c
	clang -march=native $? -o $@
