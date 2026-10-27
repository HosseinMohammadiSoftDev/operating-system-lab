#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define THREAD_COUNT 5
#define MAX_ACCESS 2


sem_t semaphore;

void* task(void* arg) {
    int id = *(int*)arg;

    printf("thread %d waithing ... \n", id);

    sem_wait(&semaphore);

    printf("thread %d entered \n", id);

    sleep(2);

    printf("thread %d leaving \n", id);

    sem_post(&semaphore);

    return NULL;
}

int main(void) {
    pthread_t threads[THREAD_COUNT];
    int ids[THREAD_COUNT];

    sem_init(&semaphore, 0, MAX_ACCESS);

    for (int i = 0; i < THREAD_COUNT; i++) {
        ids[i] = i + 1; 

        pthread_create(&threads[1], NULL, task, &ids[1]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);
    
    return 0;
}





