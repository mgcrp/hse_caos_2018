#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void ontimer_event(int signo) {
    exit(0);
}

int main() {
    struct sigaction action = { .sa_flags = SA_RESTART, .sa_handler = ontimer_event };
    sigemptyset(&action.sa_mask);
    sigaction(SIGALRM, &action, NULL);

    struct timespec timerIn;
    if (scanf("%ld %ld", &timerIn.tv_sec, &timerIn.tv_nsec) == 2) {
        // getting current time
        struct timeval currentTime;
        gettimeofday(&currentTime, NULL);
        // calculation timeout period
        long long timeoutMicrosec = (long long)(timerIn.tv_sec - currentTime.tv_sec) * 1000;
        timeoutMicrosec += (long long)(timerIn.tv_nsec/1000/1000 - currentTime.tv_usec/1000);
        // if event seems to be in the past - abort process
        if (timeoutMicrosec <= 0) { exit(0); }
        // setting up timer
        struct itimerval finishTime = {
            .it_value.tv_sec = timeoutMicrosec / 1000,
            .it_value.tv_usec = (timeoutMicrosec % 1000) * 1000
        };
        setitimer(ITIMER_REAL, &finishTime, NULL);
        // waiting for program to finish
        pause();
    }
    return 0;
}
