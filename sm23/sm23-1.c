#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

double values[3];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
enum { THREAD_NUMBER = 3, ITER_NUMBER = 1000000 };

void * thread_func(void * ptr) {
    int index = (int)(intptr_t) ptr;
    for (int i = 0; i < ITER_NUMBER; ++i) {
        if (pthread_mutex_lock(&mutex)) { exit(1); }
        // Actions here
        values[index] += (index + 1) * 100;
        values[(index + 1) % THREAD_NUMBER] -= (index + 1) * 100 + 1;
        if (pthread_mutex_unlock(&mutex)) { exit(1); }
    }
    return 0;
}

int main() {
    pthread_t threads[THREAD_NUMBER];
    for (int i = 0; i < THREAD_NUMBER; ++i) {
        if (pthread_create(&threads[i], NULL, thread_func, (void *)(intptr_t) i)) { return 1; }
    }
    for (int i = 0; i < THREAD_NUMBER; ++i) {
        if (pthread_join(threads[i], NULL)) { return 1; }
    }
    printf("%.10g %.10g %.10g\n", values[0], values[1], values[2]);
    return 0;
}
