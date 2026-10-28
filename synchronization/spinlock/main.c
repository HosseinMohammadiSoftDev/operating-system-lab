#define _GNU_SOURCE

#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 5
#define ITERATIONS 100000

int counter = 0;

pthread_spinlock_t lock;

void* increment(void* arg) {
    for(int i = 0; i < ITERATIONS; i++) {
//        pthread_spin_lock(&lock);

        counter++;

//        pthread_spin_unlock(&lock);
    }

    return NULL;
}

int main (void) {
    pthread_t threads[THREAD_COUNT];

    pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);

    for(int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }

    for(int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Ecpected: %d \n", THREAD_COUNT * ITERATIONS);
    printf("Actual: %d \n", counter);

//    pthread_spin_destroy(&lock);

    return 0;
}
