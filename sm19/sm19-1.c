#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int counter = 0;

void signal_handler(int signo) {
    if (counter == 4) {
        _exit(0);
    } else {
        printf("%d\n", counter++);
        fflush(stdout);
    }
}

int main() {
    struct sigaction action = { .sa_flags = SA_RESTART, .sa_handler = signal_handler };
    sigaction(SIGINT, &action, NULL);

    sigset_t signal_mask;                           // creating signal mask
    sigemptyset(&signal_mask);                      // initializing mask with empty mask
    sigaddset(&signal_mask, SIGINT);                // addind SIGINT signal to mask
    sigprocmask(SIG_BLOCK, &signal_mask, NULL);     // changing current mask to one we just set up

    // printing PID
    printf("%d\n", getpid());
    fflush(stdout);

    sigprocmask(SIG_UNBLOCK, &signal_mask, NULL);   // deleting signals from current mask
    while (42) {
        pause();
    }
}
