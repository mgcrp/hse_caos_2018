#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void child(int index) {
    // Get string
    char BUF[8];
    ssize_t result = read(0, BUF, 8);
    // Exit if error accured while reading
    if (result != 8) {
        exit(1);
    }
    // String to Int
    int32_t num = strtol(BUF, NULL, 10);
    // Output
    printf("%d %"PRId32"\n", index, num * num);
    exit(0);
}

int main() {
    for (int i = 1; i <= 3; ++i) {
        if (!fork()) {
            child(i);
        }
    }

    for (int i = 0; i < 3; ++i) {
        wait(NULL);
    }
}
