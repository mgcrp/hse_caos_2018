#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int multiplication_mode = 0;

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        multiplication_mode = 0;
    } else if (signo == SIGUSR2) {
        multiplication_mode = 1;
    }
}

int main() {
    struct sigaction action = { .sa_flags = SA_RESTART, .sa_handler = signal_handler };
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    int number_in;
    while (scanf("%d", &number_in) != EOF) {
        if (multiplication_mode) {
            printf("%d\n", number_in * number_in);
            fflush(stdout);
        } else {
            printf("%d\n", (-1) * number_in);
            fflush(stdout);
        }
    }

    return 0;
}
