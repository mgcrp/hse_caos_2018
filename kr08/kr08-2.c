#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int program_mode = 0;
volatile int sig1_counter = 0;

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        // invert mode
        if (program_mode) {
            program_mode = 1;
        } else {
            program_mode = 0;
        }
        // counter += 1
        sig1_counter += 1;
        // if sig1_counter == 5: _exit(0)
        if (sig1_counter == 5) {
            _exit(0);
        }
    } else if (signo == SIGUSR2) {
        program_mode = 1;
    }
}

int main() {
    struct sigaction action = { .sa_flags = SA_RESTART, .sa_handler = signal_handler };
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    uint32_t number_in;
    while (scanf("%o", &number_in) != EOF) {
        if (program_mode) {
            // program_mode == 0 - host_num
            if (number_in && (3 << 30) == (1 << 31)) {
                uint32_t mask = 65535;
                printf("%zu\n", number_in && mask);
                fflush(stdout);
            } else {
                printf("0\n");
                fflush(stdout);
            }
        } else {
            // program_mode == 0 - network_num
            if (number_in && (3 << 30) == (1 << 31)) {
                uint32_t mask = 16383 << 16;
                printf("%zu\n", (number_in && mask) >> 16);
                fflush(stdout);
            } else {
                printf("0\n");
                fflush(stdout);
            }

            printf("%d\n", (-1) * number_in);
            fflush(stdout);
        }
    }

    return 0;
}
