#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int N = 0;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        if (i == N - 1) {
            printf("%d\n", i + 1);
        } else {
            printf("%d ", i + 1);
        }

        fflush(stdout);

        if (i == N - 1) {
            exit(0);
        }

        pid_t pid = fork();
        if (pid < 0) {
            exit(1);
        } else if (pid != 0) {
            break;
        }
    }
    wait(NULL);
}
