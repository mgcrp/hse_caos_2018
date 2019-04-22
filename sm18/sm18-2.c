#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    // Creating pipe and checking for errors
    int fd[2];
    if (pipe(fd) < 0) {
        exit(1);
    }

    // Finishing the program
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return(0);
}
