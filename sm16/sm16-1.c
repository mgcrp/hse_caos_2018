#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void print_three() {
    printf("3 ");
    exit(0);
}

void print_two() {
    pid_t pid = fork();
    if (pid < 0) {
        exit(1);
    }
    if (pid == 0) {
        print_three();
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
        print_two();
    }

    wait(NULL);
    printf("1\n");
}
