#include <pthread.h>
#include <stdio.h>

enum { THREAD_NUM = 10 };

struct ThreadConfig
{
    int id;
    pthread_t prev;
};

void * thread_handler(void * params) {
    struct ThreadConfig config = *((struct ThreadConfig *) params);
    if (config.id > 0) {
        pthread_join(config.prev, NULL);
    }
    printf("%d\n", config.id);
    fflush(stdout);
    return NULL;
}

int main() {
    struct ThreadConfig config[THREAD_NUM];
    pthread_t thread = 0;

    for (int i = 0; i < THREAD_NUM; ++i) {
        config[i].id = i;
        config[i].prev = thread;
        pthread_create(&thread, NULL, thread_handler, &config[i]);
    }

    pthread_join(thread, NULL);
    return 0;
}
