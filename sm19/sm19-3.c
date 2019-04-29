#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int signal_in = 0;

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        signal_in = 1;
    } else if (signo == SIGUSR2) {
        signal_in = 2;
    } else if (signo == SIGTERM) {
        signal_in = 3;
    }
}

int main() {
    // initializing signal handler
    struct sigaction action = { .sa_flags = SA_RESTART, .sa_handler = signal_handler };
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    sigaction(SIGTERM, &action, NULL);

    // initializing:
    //     action_mask - blocks singals while process is working with the prev one
    //     wait_mask - used in sigsuspend while waiting for one of expected signals
    sigset_t action_mask, wait_mask;
    sigemptyset(&action_mask);
    sigaddset(&action_mask, SIGUSR1);
    sigaddset(&action_mask, SIGUSR2);
    sigaddset(&action_mask, SIGTERM);
    sigprocmask(SIG_BLOCK, &action_mask, &wait_mask);

    // printing PID
    printf("%d\n", getpid());
    fflush(stdout);

    int cnt_sigusr1 = 0, cnt_sigusr2 = 0;
    while (42) {
        while(signal_in == 0) {
            // waiting for the signal
            sigsuspend(&wait_mask);
        }
        if (signal_in == 1) {
            printf("%d %d\n", cnt_sigusr1, cnt_sigusr2);
            cnt_sigusr1 += 1;
        } else if (signal_in == 2) {
            cnt_sigusr2 += 1;
        } else if (signal_in == 3) {
            _exit(0);
        }
        fflush(stdout);
        signal_in = 0;
    }
}
