/* INSERT INCLUDE DIRECTIVES HERE */
#include <fcntl.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

enum { N = 5 };

pthread_t ids[N];
pthread_t ids2[N];

void *func2(void *arg)
{
    pause();
    return NULL;
}

/* INSERT YOUR CODE HERE */
volatile int f = 0;

void *func(void * arg)
{
    int serial = (int) (intptr_t) arg;

    /* INSERT YOUR CODE HERE */
    while (!f) { continue; }
    if (serial == 0) {
        pthread_join(ids[2], NULL);
    }
    else if (serial == 1) {
        pthread_join(ids[4], NULL);
    }
    else if (serial == 3) {
        pthread_join(ids[0], NULL);
    }
    else if (serial == 4) {
        pthread_join(ids[3], NULL);
    }
    printf("%d\n", serial);

    return NULL;
}

int main()
{
    for (int i = 0; i < N; ++i) {
        pthread_create(&ids2[i], NULL, func2, NULL);
    }
    for (int i = 0; i < N; ++i) {
        pthread_create(&ids[i], NULL, func, (void*) (intptr_t) i);
    }
    for (int i = 0; i < N; ++i) {
        pthread_cancel(ids2[i]);
    }

    /* INSERT YOUR CODE HERE */
    f = 1;
    pthread_join(ids[1], NULL);

    return 0;
}
