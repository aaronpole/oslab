#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty, full, mutex;

void* producer(void* arg) {
    int item;
    int id = *(int*)arg;
    while (1) {
        item = rand() % 100;
        sem_wait(&empty);   // Wait for empty slot
        sem_wait(&mutex);   // Enter critical section

        buffer[in] = item;
        printf("Producer %d produced %d at buffer[%d]\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);   // Exit critical section
        sem_post(&full);    // Increase full count
        sleep(1);
    }
}

void* consumer(void* arg) {
    int item;
    int id = *(int*)arg;
    while (1) {

        sem_wait(&full);    // Wait for full slot
        sem_wait(&mutex);   // Enter critical section

        item = buffer[out];
        printf("    Consumer %d consumed %d from buffer[%d]\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);   // Exit critical section
        sem_post(&empty);   // Increase empty count
        sleep(2);
    }
}


int main() {
    pthread_t prod[3], cons[3];
    int ids[3] = {1, 2, 3};
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    for (int i = 0; i < 3; i++) {
        pthread_create(&prod[i], NULL, producer, &ids[i]);
        pthread_create(&cons[i], NULL, consumer, &ids[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}