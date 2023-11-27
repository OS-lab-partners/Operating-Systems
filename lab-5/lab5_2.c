#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>  // sleep function
#include <stdlib.h>  // rand function

#define BUFF_SIZE 20
char buffer[BUFF_SIZE];
int nextIn = 0;
int nextOut = 0;
//used for synchronization – producer should be blocked if the buffer is full
sem_t empty_slots;
//used for synchronization – consumer should be blocked if the buffer is empty
sem_t full_slot;
//used for mutual exclusion – enforces mutual exclusion on the shared buffer
sem_t mutex;
void Put(char item)
{
 buffer[nextIn] = item;
 nextIn = (nextIn + 1) % BUFF_SIZE;
 printf("Producing %c ...\n", item);
}

void * Producer()
{
 int i;
 for(i = 0; i < 15; i++)
 {
 sleep(rand()%6);
 Put((char)('A'+ i % 26));
 }
}

void Get(char item)
{
 item = buffer[nextOut];
 nextOut = (nextOut + 1) % BUFF_SIZE;
 printf("Consuming %c ...\n", item);
}

void * Consumer()
{
 int i;
 char item;
 for(i = 0; i < 15; i++)
 {
 sleep(rand()%6);
 Get(item);
 }
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