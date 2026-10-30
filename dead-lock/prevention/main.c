#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_b = PTHREAD_MUTEX_INITIALIZER;

void* thread_one(void* arg) {
    pthread_mutex_lock(&mutex_a);
    printf("Thread 1 acquired Mutex A\n");

    pthread_mutex_lock(&mutex_b);
    printf("Thread 1 acquired Mutex B\n");

    printf("Thread 1 executing critical section\n");

    pthread_mutex_unlock(&mutex_b);
    pthread_mutex_unlock(&mutex_a);

    return NULL;
}

void* thread_two(void* arg) {
    pthread_mutex_lock(&mutex_a);
    printf("Thread 2 acquired Mutex A\n");

    pthread_mutex_lock(&mutex_b);
    printf("Thread 2 acquired Mutex B\n");

    printf("Thread 2 executing critical section\n");

    pthread_mutex_unlock(&mutex_b);
    pthread_mutex_unlock(&mutex_a);

    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread_one, NULL);
    pthread_create(&t2, NULL, thread_two, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex_a);
    pthread_mutex_destroy(&mutex_b);

    return 0;
}
