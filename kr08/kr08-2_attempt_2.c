#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// mode 0 - network num
// mode 1 - host num
volatile int program_mode = 0;
volatile int sigusr1_counter = 0;

enum {
    NETWORK_MASK = 0b111111111111110000000000000000,
    HOST_MASK = 0b1111111111111111,
    CHECK_CLASS_MASK = 0b11000000000000000000000000000000,
    B_CLASS_MASK = 0b10000000000000000000000000000000
};

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        // invert mode
        if (program_mode) {
            program_mode = 0;
        } else {
            program_mode = 1;
        }
        // counter += 1
        sigusr1_counter += 1;
        // if sig1_counter == 5: _exit(0)
        if (sigusr1_counter == 5) {
            _exit(0);
        }
    } else if (signo == SIGUSR2) {
        // reading number
        unsigned long ip_in;
        scanf("%lo", &ip_in);
        // checking if ip_in is a B-class IP
        if ((ip_in & CHECK_CLASS_MASK) == B_CLASS_MASK) {
            if (program_mode) {
                // 1 - host
                unsigned long host = ip_in & HOST_MASK;
                printf("%ld\n", host);
                fflush(stdout);
            } else {
                // 0 - network
                unsigned long network = (ip_in & NETWORK_MASK) >> 16;
                printf("%ld\n", network);
                fflush(stdout);
            }
        } else {
            // not a B-class IP
            printf("0\n");
            fflush(stdout);
        }
    }
}

int main() {
    struct sigaction action = { .sa_flags = SA_RESTART, .sa_handler = signal_handler };
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);

    sigset_t signal_mask, wait_mask;
    sigemptyset(&signal_mask);
    sigaddset(&signal_mask, SIGUSR1);
    sigaddset(&signal_mask, SIGUSR2);
    sigprocmask(SIG_BLOCK, &signal_mask, &wait_mask);

    printf("%d\n", getpid());
    fflush(stdout);

    while (42) {
        sigsuspend(&wait_mask);
    }

    sigprocmask(SIG_UNBLOCK, &signal_mask, NULL);
    return 0;
}
