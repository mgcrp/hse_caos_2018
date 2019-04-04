#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int N;
    scanf("%d", N);
    for (int i = 0; i < N; ++i) {
        printf("%d" , i + 1);
        if (i == N - 1) {
            exit(0);
        }
        pid_t pid = fork();
        if (pid != 0) {
            break;
        }
    }
    wait(NULL);
}
