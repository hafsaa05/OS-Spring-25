#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5  // buffer size

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty;   // counts empty slots
sem_t full;    // counts full slots
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100;
        sem_wait(&empty);              // wait for empty slot
        pthread_mutex_lock(&mutex);    // lock buffer

        buffer[in] = item;
        printf("Produced: %d at %d\n", item, in);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);  // unlock buffer
        sem_post(&full);               // increase full count

        sleep(1); // simulate time to produce
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);               // wait for full slot
        pthread_mutex_lock(&mutex);    // lock buffer

        item = buffer[out];
        printf("Consumed: %d from %d\n", item, out);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);  // unlock buffer
        sem_post(&empty);              // increase empty count

        sleep(2); // simulate time to consume
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, SIZE); // initially all slots empty
    sem_init(&full, 0, 0);     // initially no items
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
