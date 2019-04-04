#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/wait.h>

void child(int index) {
    char BUF[8];
    ssize_t result = read(0, BUF, 8);
    if (result != 8) {
        exit(1);
    }
    int32_t num = strtol(BUF, NULL, 10);
    printf("%d %"PRId32"\n", index, num * num);
    exit(0);
}

int main() {
    for (int i = 0; i < 3; ++i) {
        if (!fork()) {
            child(i + 1);
        }
    }

    for (int i = 0; i < 3; ++i) {
        wait(NULL);
    }
}
