#include <stdio.h>
#include <pthread.h>

# define THREAD_COUNT 4
# define ITERATION 1000

int counter = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* increment(void* arg) {
    // critical section 
    for (int i = 0; i < ITERATION; i++) {
        // Entry section 
        pthread_mutex_lock(&lock);

        // critical section
        counter++;

        // exit section
        pthread_mutex_unlock(&lock);
    }

    return NULL;

} 


int main (void) {
    pthread_t threads[THREAD_COUNT];
    
    // create threads
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }

    // wate to done threads 
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    // clear all mutex 
    pthread_mutex_destroy(&lock);

    printf("Expected: %d", THREAD_COUNT * ITERATION);
    printf("Actual:   %d", counter);

    return 0;
}

