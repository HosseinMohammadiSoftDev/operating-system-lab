#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#define THREAD_COUNT 5
#define ITERATIONS 100000

typedef struct {
    atomic_flag flag;
} Spinlock;

Spinlock lock = {
    .flag = ATOMIC_FLAG_INIT
};

int counter = 0;

void spin_lock(Spinlock* lock) {
    while (atomic_flag_test_and_set_explicit(
        &lock->flag, 
        memory_order_acquire        
    )) {
        // Busy Waiting
    }
}

void spin_unlock(Spinlock* lock) {

    atomic_flag_clear_explicit(
        &lock->flag,
        memory_order_release
    );
}

void* increment(void* arg) {
    for(int i = 0; i < ITERATIONS; i++) {
        spin_lock(&lock);

        counter++;

        spin_unlock(&lock);
    }

    return NULL;
}

int main (void) {
    pthread_t threads[THREAD_COUNT];

    for(int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }

    for(int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Expected: %d \n", THREAD_COUNT * ITERATIONS);
    printf("Actual: %d \n", counter);

    return 0;
}
