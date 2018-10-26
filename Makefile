kldmem: ./kldmem.c
	clang -march=native $? -o $@

.PHONY: install
install: ./kldmem
	install kldmem /usr/local/bin/kldmem

.PHONY: uninstall
uninstall:
	rm /usr/local/bin/kldmem

clean:
	rm -f ./kldmem
