#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t resource;
int read_count = 0;
pthread_mutex_t rmutex;

void *reader(void *arg)
{
    int id = *((int *)arg);

    // Reader tries to enter
    pthread_mutex_lock(&rmutex);
    read_count++;
    if (read_count == 1) // First reader locks resource
        sem_wait(&resource);
    pthread_mutex_unlock(&rmutex);

    // Reading section
    printf("Reader %d is reading\n", id);
    sleep(1);
    printf("Reader %d finished reading\n", id);

    // Reader leaves
    pthread_mutex_lock(&rmutex);
    read_count--;
    if (read_count == 0) // Last reader unlocks resource
        sem_post(&resource);
    pthread_mutex_unlock(&rmutex);

    return NULL;
}

void *writer(void *arg)
{
    int id = *((int *)arg);

    // Writer tries to enter
    sem_wait(&resource);

    // Writing section
    printf("Writer %d is writing\n", id);
    sleep(2);
    printf("Writer %d finished writing\n", id);

    // Writer leaves
    sem_post(&resource);

    return NULL;
}

int main()
{
    pthread_t readers[3], writers[2];
    int reader_ids[3] = {1, 2, 3};
    int writer_ids[2] = {1, 2};

    sem_init(&resource, 0, 1);
    pthread_mutex_init(&rmutex, NULL);

    for (int i = 0; i < 3; i++)
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);

    for (int i = 0; i < 2; i++)
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(readers[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(writers[i], NULL);

    sem_destroy(&resource);
    pthread_mutex_destroy(&rmutex);

    return 0;
}
