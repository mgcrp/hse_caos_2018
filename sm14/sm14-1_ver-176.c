#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char ** argv) {
	long long int size_all = 0;
	char * dir = argv[1];
	DIR * current = opendir(dir);
	if (!current) {
		printf("0\n");
		return 0;
	}

	uid_t owner = getuid();
	struct dirent * file;
	while (file = readdir(current)) {
		char * file_name = file->d_name;

		char full_path[PATH_MAX];
		snprintf(full_path, PATH_MAX, "%s/%s", dir, file_name);

		struct stat buf;
		int ret = stat(full_path, &buf);
		if (ret) {
			continue;
		}
		if (!isupper(file_name[0])) {
			continue;
		}
		if (!S_ISREG(buf.st_mode)) {
			continue;
		}
		if (owner != buf.st_uid) {
			continue;
		}
		size_all += buf.st_size;
	}
	closedir(current);
	printf("%lld\n", size_all);
	return 0;
}
