#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    unsigned long long sum_size = 0;
    struct stat file_stats;
    for (int i = 1; i < argc; ++i) {
        int r_ret = lstat(argv[i], &file_stats);
        if (r_ret < 0) {
            continue;
        }
        if (!S_ISREG(file_stats.st_mode) || S_ISLNK(file_stats.st_mode)) {
            continue;
        }
        if (file_stats.st_nlink != 1) {
            continue;
        }
        sum_size += file_stats.st_size;
    }
    printf("%llu\n", sum_size);
    return 0;
}
