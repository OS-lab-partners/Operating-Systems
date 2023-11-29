#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFF_SIZE 20
char buffer[BUFF_SIZE];
int nextIn = 0;
int nextOut = 0;

//used for synchronization – producer should be blocked if the buffer is full
sem_t empty_slots;
//used for synchronization – consumer should be blocked if the buffer is empty
sem_t full_slots;
//used for mutual exclusion – enforces mutual exclusion on the shared buffer
sem_t mutex;

void Put(char item, pthread_t tid)
{
    // the sem_wait function will make sure there is enough room in the buffer
    // producers will wait if there is no room
    sem_wait(&empty_slots); // producer should be blocked if the buffer is full
    sem_wait(&mutex); // enforces mutual exclusion on the shared buffer

    buffer[nextIn] = item;
    nextIn = (nextIn + 1) % BUFF_SIZE;
    printf("Producer %lu producing %c ...\n", tid, item);

    // the sem_post function "signals" sem
    sem_post(&mutex); // enforces mutual exclusion on the shared buffer, now new producers can enter
    sem_post(&full_slots); // signals consumers if there are any waiting
}

void *Producer(void *arg)
{
    pthread_t tid = pthread_self();
    int i;
    for (i = 0; i < 15; i++)
    {
        sleep(rand() % 6);
        char item = (char)('A' + i % 26);
        Put(item, tid);
    }
    pthread_exit(NULL);
}

void Get(pthread_t tid)
{
    // requires consumer to wait if the buffer is empty
    // if the sem value is 0 -> no filled slots
    sem_wait(&full_slots);
    // if mutex value is 0 -> there is a thread in critical section
    // if mutex value > 0 it will decrease value and continue
    sem_wait(&mutex);

    char item = buffer[nextOut];
    nextOut = (nextOut + 1) % BUFF_SIZE;
    printf("Consumer %lu consuming %c ...\n", tid, item);

    // after the "critical section":
    sem_post(&mutex); // after finished this will allow others to enter
    sem_post(&empty_slots); // means procucer has produced a letter and there is now a free buffer slot
}

void *Consumer(void *arg)
{
    pthread_t tid = pthread_self();
    int i;
    for (i = 0; i < 15; i++)
    {
        sleep(rand() % 6);
        Get(tid);
    }
    pthread_exit(NULL);
}

void main()
{
    /* Initialize semaphores */
    pthread_t pid, cid;
    pthread_create(&pid, NULL, Producer, NULL);
    pthread_create(&cid, NULL, Consumer, NULL);
    // create more consumer & producer threads.
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
}