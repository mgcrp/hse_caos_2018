#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {
    if (argc < 3) {
        return 1;
    }

    int fd[2];
    int pid1, pid2;
    if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }

    if ((pid1 = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    if (!pid1) {
        /* child 1: "ls -l" */
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[1], argv[1], NULL);
        perror("execlp");
        _exit(1);
    }

    if ((pid2 = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    if (!pid2) {
        /* child 2: "wc -l" */
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[2], argv[2], NULL);
        perror("execlp");
        _exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
