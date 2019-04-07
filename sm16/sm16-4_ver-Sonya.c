#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdint.h>
#include <sys/mman.h>
#include <inttypes.h>

int main() {
    int n;
    pid_t st_pid = getpid();
    while (scanf("%d", &n) != EOF) {
        pid_t pid = fork();
        if (pid <= -1) {
            pid_t cur_pid = getpid();
            if (cur_pid == st_pid) {
                printf("-1\n");
                exit(0);
            }
            exit(1);
        }
        if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            pid_t cur_pid = getpid();
            if (!status) {
                printf("%d\n", n);
                exit(0);
            } else if (cur_pid == st_pid) {
                printf("-1\n");
                exit(0);
            } else if (WIFEXITED(status) != 0) {
                printf("%d\n", n);
                exit(0);
            } else if (WIFSIGNALED(status)) {
                printf("-1\n");
                exit(0);
            }
            exit(1);
        }
        break;
    }
}

Норм вы
