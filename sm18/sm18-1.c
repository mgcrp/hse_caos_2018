#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    if (argc < 3) {
        return 1;
    }

    int fd[2];
    if (pipe(fd) < 0) {
        exit(1);
    }

    // Child #1 code
    int pid1 = fork();
    if (pid1 < 0) {
        exit(1);
    }
    if (!pid1) {
        // Child #1 - executing CMD1 from argv[1]
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }

    // Child #2 code
    int pid2 = fork();
    if (pid2 < 0) {
        exit(1);
    }
    if (!pid2) {
        // Child #2 - executing CMD2 from argv[2]
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[2], argv[2], NULL);
        _exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
