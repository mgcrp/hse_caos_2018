#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    unsigned long long answer = 0;
    struct stat stats;

    for (int agrId = 1; argId < argc; ++argId) {
        int result = lstat(argv[argId], &stats);
        if (result < 0) {
            continue;
        }
        if (!S_ISREG(stats.st_mode) || S_ISLNK(stats.st_mode)) {
            continue;
        }
        if (stats.st_nlink != 1) {
            continue;
        }
        answer += stats.st_size;
    }
    printf("%llu\n", answer);
    return 0;
}
