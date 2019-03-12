#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void printThree() {
    printf("3 ");
    exit(0);
}

void printTwo() {
    pid_t pid = fork();

    if (pid < 0) {
        exit(1);
    }

    if (pid == 0) {
        printThree();
    }

    wait(NULL);
    printf("2 ");
    exit(0);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        exit(1);
    }

    if (pid == 0) {
        printTwo();
    }

    wait(NULL);
    printf("1\n");
}
