#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

enum { N = 5 };

pthread_t ids[N];
pthread_t ids2[N];

void *func2(void *arg)
{
    pause();
    return NULL;
}

void handl(int s) {
    return;
}

void *func(void *arg)
{
    int serial = (int) (intptr_t) arg;
    if (serial == 1) {
        pthread_join(ids2[4], NULL);
        printf("1\n");
        pthread_kill(ids2[1], SIGABRT);
    }
    if (serial == 0) {
        pthread_join(ids2[2], NULL);
        printf("0\n");
        pthread_kill(ids2[0], SIGABRT);
    }
    if (serial == 3) {
        pthread_join(ids2[1], NULL);
        printf("3\n");
        pthread_kill(ids2[3], SIGABRT);
    }
    if (serial == 2) {
        pthread_join(ids2[3], NULL);
        printf("2\n");
        pthread_kill(ids2[2], SIGABRT);
    }
    if (serial == 4) {
        printf("4\n");
        pthread_kill(ids2[4], SIGABRT);
    }
    return NULL;
}

int main()
{
    signal(SIGABRT, handl);
    for (int i = 0; i < N; ++i) {
        pthread_create(&ids2[i], NULL, func2, NULL);
    }
    for (int i = 0; i < N; ++i) {
        pthread_create(&ids[i], NULL, func, (void*) (intptr_t) i);
    }
    pthread_join(ids[0], NULL);
    return 0;
}