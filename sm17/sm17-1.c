#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        int fdInput = open(argv[2], O_RDONLY);
        dup2(fd, STDIN_FILENO);

        int fdOutput = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(fdOutput, STDIN_FILENO);

        execlp(argv[1], argv[1], NULL);
        exit(1);
    }

    wait(NULL);
    return 0;
}
