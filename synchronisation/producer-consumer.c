#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 5

pthread_mutex_t mutex;
sem_t full, empty;
int buffer[BUFF_SIZE], in = 0, out = 0;

void *producer(void *arg)
{
    while (1)
    {
        int item = rand() % 100; // Produce an item
        sem_wait(&empty);        // Wait if buffer is full
        pthread_mutex_lock(&mutex);

        buffer[(in++) % BUFF_SIZE] = item; // Add item to buffer and move to next position
        printf("Producer produced: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&full); // Increments the full semaphore

        sleep(1); // Simulate production time
    }
}

void *consumer(void *arg)
{
    while (1)
    {
        sem_wait(&full); // Wait if buffer is empty
        pthread_mutex_lock(&mutex);

        int item = buffer[(out++) % BUFF_SIZE]; // Remove item from buffer and move to next position
        printf("Consumer consumed: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // Increments the empty semaphore

        sleep(1); // Simulate consumption time
    }
}

int main()
{
    pthread_t producer_tid, consumer_tid;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&full, 0, 0);          // Initially, buffer is empty
    sem_init(&empty, 0, BUFF_SIZE); // Buffer has BUFF_SIZE empty slots

    pthread_create(&producer_tid, NULL, producer, NULL);
    pthread_create(&consumer_tid, NULL, consumer, NULL);

    sleep(20); // Run the program for 20 seconds
    printf("Exiting...\n");

    exit(0);
}
