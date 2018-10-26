#include <sys/param.h>
#include <sys/linker.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#if !defined(__cplusplus)
#define bool uint8_t
#define false 0
#define true 1
#endif

void show(struct kld_file_stat *stat, bool human) {
	printf("%s\n", stat->name);

	if (!human) {
		printf("* Memory usage: %lu\n", stat->size);
	} else if (stat->size < 1024) {
		printf("* Memory usage: %lub\n", stat->size);
	} else if (stat-> size < 1024 * 1024) {
		printf("* Memory usage: %.1fk\n", stat->size / 1024.);
	} else {
		printf("* Memory usage: %.1fm\n", stat->size / 1024. / 1024.);
	}

	printf("* Modules referenced: %d\n", stat->refs);
	printf("* Path: %s\n", stat->pathname);
	printf("\n");
}

int main(int argc, const char *argv[]) {
	bool human = false;
	if (argc > 1 && (strcmp(argv[1], "-h") == 0 ||
			 strcmp(argv[1], "--human") == 0)) {
		human = true;
	}

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

		show(&stat, human);
	}
}
