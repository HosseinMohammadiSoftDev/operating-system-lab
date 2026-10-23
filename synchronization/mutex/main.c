#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 4
#define ITERATIONS 100000

int counter = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* increment(void* arg) {

    for (int i = 0; i < ITERATIONS; i++) {

        pthread_mutex_lock(&mutex);

        counter++;

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(void) {

    pthread_t threads[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Expected: %d\n", THREAD_COUNT * ITERATIONS);
    printf("Actual:   %d\n", counter);

    pthread_mutex_destroy(&mutex);

    return 0;
}
