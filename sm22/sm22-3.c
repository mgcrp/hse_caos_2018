#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void * thread_handler(void * params) {
    (void)(params);

    int number_in;
    long long * sum = malloc(sizeof(long long));
    *sum = 0;

    if (scanf("%d", &number_in) == 1) {
        *sum += number_in;
        sched_yield();
    }

    return sum;
}

int main(int argc, char * argv[]) {
    if (argc != 2) { return 1; }

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));

    int threads_num = strtol(argv[1], NULL, 10);
    pthread_t * threads = malloc(sizeof(pthread_t) * threads_num);
    for (int i = 0; i < threads_num; ++i) {
        if (pthread_create(&threads[i], &attr, thread_handler, NULL) != 0) {
            // if one of the threads can't be created - abort;
            exit(1);
        }
    }

    long long final_sum = 0;
    for (int i = 0; i < threads_num; ++i) {
        long long * temp_sum;
        pthread_join(threads[i], (void **)&temp_sum);
        final_sum += *temp_sum;
        free(temp_sum);
    }
    
    printf("%lld\n", final_sum);
    free(threads);
    return 0;
}
