#include <stdio.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h> // Library getpid
#include <unistd.h>    // Lib getpid
#include <time.h>      // Lib 4 rand

//Lab5_3_1Producer


#define BUFF_SIZE 20

typedef struct {
    char buffer[BUFF_SIZE];
    int nextIn;
    int nextOut;
} shared_data;

shared_data *shm, *s;
char sem_name1[] = "mutex";
char sem_name2[] = "empty_slots";
char sem_name3[] = "full_slots";
sem_t *empty_slots;
sem_t *full_slots;
sem_t *mutex;

void Put(char item) {
    sem_wait(empty_slots);
    sem_wait(mutex);
    s->buffer[s->nextIn] = item;
    s->nextIn = (s->nextIn + 1) % BUFF_SIZE;
    sem_post(mutex);
    //Next line includes the PID Novoskii 
    printf("Producer (PID %d) Producing %c ...\n", getpid(), item); 
    sem_post(full_slots);
}

void Producer() {
    int i;
    for (i = 0; i < 10; i++) {
        sleep(rand() % 3);
        Put((char)('A' + i % 26));
    }
}

int main() {
    // Semaphores 
    mutex = sem_open(sem_name1, O_CREAT, 0644, 1);
    full_slots = sem_open(sem_name3, O_CREAT, 0644, 0);
    empty_slots = sem_open(sem_name2, O_CREAT, 0644, 10);

    // Create a key for the segment
    key_t key;
    key = 1234; 

    // create the segment
    int shmid;
    if ((shmid = shmget(key, sizeof(shared_data), IPC_CREAT | 0666)) < 0) {
        perror("Shmget");
        exit(1);
    }

    // attach to the segment
    if ((shm = (shared_data *)shmat(shmid, NULL, 0)) == (shared_data *)-1) {
        perror("Shmat");
        exit(1);
    }

    s = shm;
    s->nextIn = 0;
    Producer();

    // detach from the segment
    shmdt((void *)shm);

    return 0;
}
