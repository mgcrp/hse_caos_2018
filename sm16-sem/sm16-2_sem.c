#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/wait.h>

void child(int ch_index) {
    char buf[8];
    int res = read(0, buf, 8);

    if (res < 8) {
        exit(1);
    }

    int32_t num = strtol(buf, NULL, 10);
    printf("%d %"PRId32"\n", ch_index, num*num);
    exit(0);
}

int main() {
    for (int i = 0; i < 3; ++i) {
        if (!fork()) {
            child(i);
        }
    }

    for (int i = 0; i < 3; ++i) {
        wait(NULL);
    }
}
