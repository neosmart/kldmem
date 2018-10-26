#include <sys/param.h>
#include <sys/linker.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

void show(struct kld_file_stat *stat) {
	printf("%s\n", stat->name);
	printf("* Memory usage: %lu\n", stat->size);
	printf("* Modules referenced: %d\n", stat->refs);
	printf("* Path: %s\n", stat->pathname);
	printf("\n");
}

int main(int argc, const char *argv[]) {
	for (int kldId = kldnext(0); kldId > 0; kldId = kldnext(kldId)) {
		struct kld_file_stat stat = {
			.version = sizeof(struct kld_file_stat),
		};

		int result = kldstat(kldId, &stat);
		if (result != 0) {
			fprintf(stderr, "Error retrieving kld info from kldstat(2)\n");
			fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
			return errno;
		}

		show(&stat);
	}
}
