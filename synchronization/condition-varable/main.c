#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

int ready = 0;

void* consumer(void* arg) {
    pthread_mutex_lock(&mutex);

    while(!ready) {
        printf("consumer: waiting... \n");

        pthread_cond_wait(&condition, &mutex);        
    }

    printf("Consumer: data is ready \n");

    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* producer(void* arg) {
    sleep(2);

    pthread_mutex_lock(&mutex);

    ready = 1;

    printf("Procucer: data Prepared");

    pthread_cond_signal(&condition);

    pthread_mutex_unlock(&mutex);

    return NULL;
}


int main (void) {
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, consumer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_cond_destroy(&condition);
    pthread_mutex_destroy(&mutex);

   return 0;
}
