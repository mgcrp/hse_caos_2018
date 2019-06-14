#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum {
    THREAD_NUMBER = 3,
    ITER_NUMBER = 1000000
};
double values[3];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * thread_func(void * ptr) {
    int index = (int)(intptr_t) ptr;
    for (int i = 0; i < ITER_NUMBER; ++i) {
        if (pthread_mutex_lock(&mutex)) { exit(1); }

        // Actions here
        values[index] += (index + 1) * 100;
        values[(index + 1) % THREAD_NUMBER] -= (index + 1) * 100 + 1;

        if (pthread_mutex_unlock(&mutex)) { exit(1); }
    }
}

int main() {
    pthread_t threads;
    for (int i = 0; i < THREAD_NUMBER; ++i) {
        if (pthread_create(&threads[i], NULL, thread_func, (void *)(intptr_t) i)) { return 1; }
    }
    for (int i = 0; i < THREAD_NUMBER; ++i) {
        if (pthread_join(threads[i], NULL)) { return 1; }
    }
    for (int i = 0; i < THREAD_NUMBER; ++i) {
        printf("%.10g\n", values[i]);
    }
    return 0;
}
