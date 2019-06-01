#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

enum { N = 6 };

pthread_t ids[N];
pthread_t ids2[N];

void *func2(void *arg)
{
    pause();
    return NULL;
}

void handler(int signo) {
    return;
}

void *func(void *arg)
{
    int serial = (int) (intptr_t) arg;
    switch (serial) {
    case 0:
        pthread_join(ids2[1], NULL);
        break;
    case 1:
        pthread_join(ids2[3], NULL);
        break;
    case 2:
        pthread_join(ids2[4], NULL);
        break;
    case 3:
        pthread_join(ids2[5], NULL);
        break;
    case 4:
        pthread_join(ids2[0], NULL);
    default:
        break;
    }
    printf("%d\n", serial);
    pthread_kill(ids2[serial], SIGABRT);
    return NULL;
}

int main() {
    struct sigaction sa = {
        .sa_handler = handler,
        .sa_flags = SA_RESTART
    };
    sigemptyset(&sa.sa_mask);
    sigaction(SIGABRT, &sa, NULL);
    for (int i = 0; i < N; ++i) {
        pthread_create(&ids2[i], NULL, func2, NULL);
    }
    for (int i = 0; i < N; ++i) {
        pthread_create(&ids[i], NULL, func, (void*) (intptr_t) i);
    }
    pthread_join(ids[2], NULL);
    return 0;
}