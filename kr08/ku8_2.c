#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

enum
{
    B_CLASS_MASK = 0x80000000,
    CLASS_MASK = 0xc0000000,
    HOST_MASK = 0x0000ffff,
    NETWORK_MASK = 0x3fff0000,
    BIT_SHIFT = 16
};

volatile int work_type;

void handler(int signum) {
    static int counter = 0;

    if (signum == SIGUSR1) {
        ++counter;

        if (counter == 5) {
            exit(EXIT_SUCCESS);
        }

        work_type = work_type == 1 ? 2 : 1;  /* changing from 1 to 2 and from 2 to 1 */
    } else {
        unsigned long cur_IP;

        if (scanf("%lo", &cur_IP) == EOF) {
            exit(EXIT_SUCCESS);
        }

        if ((cur_IP & CLASS_MASK) == B_CLASS_MASK) {
            if (work_type == 1) {
                unsigned long host = cur_IP & HOST_MASK;
                printf("%ld", host);
            } else {
                unsigned long network = (cur_IP & NETWORK_MASK) >> BIT_SHIFT;
                printf("%ld", network);
            }
        } else {
            putchar('0');
        }

        putchar('\n');
        fflush(stdout);
    }
}

sigset_t init_mask() {
    sigset_t mask;

    if (sigemptyset(&mask) < 0) {
        perror("sigemtyset");
        exit(EXIT_FAILURE);
    }

    if (sigaddset(&mask, SIGUSR1) < 0) {
        perror("sigaddset");
        exit(EXIT_FAILURE);
    }

    if (sigaddset(&mask, SIGUSR2) < 0) {
        perror("sigaddset");
        exit(EXIT_FAILURE);
    }

    return mask;
}

void init_sa(struct sigaction *sa) {
    sa->sa_flags = 0;
    sa->sa_handler = handler;
    sa->sa_mask = init_mask();
}

void block(struct sigaction *sa, sigset_t *old) {
    if (sigprocmask(SIG_BLOCK, &sa->sa_mask, old) < 0) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }
}

void unblock(struct sigaction *sa) {
    if (sigprocmask(SIG_UNBLOCK, &sa->sa_mask, NULL) < 0) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }
}

void print_info() {
    int cur_pid = getpid();
    printf("%d\n", cur_pid);
    fflush(stdout);
}

void install_handling(struct sigaction *sa) {
    if (sigaction(SIGUSR1, sa, NULL) < 0) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    if (sigaction(SIGUSR2, sa, NULL) < 0) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    struct sigaction sa;
    init_sa(&sa);
    install_handling(&sa);
    sigset_t old;
    block(&sa, &old);
    work_type = 2;

    print_info();

    while (1) {
        sigsuspend(&old);
    }

    unblock(&sa);

    return 0;
}
