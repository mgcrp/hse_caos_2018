#include <stdio.h>
#include <pthread.h>

void * thread_handler(void * params) {
    (void)(params);
    int number_in;
    if (scanf("%d", %number_in) == 1) {
        pthread_t thread;
        pthread_create(&thread, NULL, thread_handler, NULL);
        pthread_join(thread, NULL);
        printf("%d\n", number_in);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_handler, NULL);
    pthread_join(thread, NULL);
    return 0;
}
