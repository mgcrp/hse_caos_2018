#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void child(int N, int index) {
    printf(" %d", index);
    if (index < N) {
        pid_t pid = fork();
        if (pid < 0) {
            exit(1);
        }
        if (pid == 0) {
            child(N, index + 1);
        }
        wait(NULL);
        exit(0);
    }
}

int main() {
    int N, index = 1;
    scanf("%d", &N);
    printf("%d", index);
    pid_t pid = fork();
    if (pid < 0) {
        exit(1);
    }
    if (pid == 0) {
        child(N, index + 1);
    }

    wait(NULL);
    printf("\n");
}
