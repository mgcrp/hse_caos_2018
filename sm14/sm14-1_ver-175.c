#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char * argv[]) {
	/*
	struct stat dir_stat;

	int res = stat(argv[1], &dir_stat);

	if (res != 0 || !S_ISDIR(dir_stat.st_mode)) {
		printf("0\n");
		return 0;
	}
	*/

	DIR * dir = opendir(argv[1]);

	if (!dir) {
		printf("0\n");
		return 0;
	}

	struct dirent * entry = readdir(dir);

	/*
	THE REST IS MISSING
	*/

	return 0;
}
