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
    struct sigaction action = { .sa_flags = SA_RESTART, .sa_handler = signal_handler };
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    sigaction(SIGTERM, &action, NULL);

    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigaddset(&mask, SIGTERM);

    sigprocmask(SIG_BLOCK, &mask, &oldmask);

    printf("%d\n", getpid());
    fflush(stdout);

    int cnt_sigusr1 = 0, cnt_sigusr2 = 0;
    while (42) {
        while(signal_in == 0) {
            sigsuspend(&oldmask);
        }
        switch (signal_in) {
            case 1:
                printf("%d %d\n", cnt_sigusr1, cnt_sigusr2);
                cnt_sigusr1 += 1;
            case 2:
                cnt_sigusr2 += 1;
            case 3:
                _exit(0);
        }
        fflush(stdout);
        signal_in = 0;
    }
}
