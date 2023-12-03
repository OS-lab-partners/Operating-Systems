#include <stdio.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h> // Header toupper and tolower functions

//Producer Modified Lab5_3_2

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
    printf("Producer (PID %d) Producing %c ...\n", getpid(), item);
    sem_post(full_slots);
}

void Process(char *item) {
    // Modified change case in between
    for (int i = 0; item[i] != '\0'; i++) {
        item[i] = isupper(item[i]) ? tolower(item[i]) : toupper(item[i]);
    }
}

void Get(char *item) {
    sem_wait(full_slots);
    sem_wait(mutex);
    *item = s->buffer[s->nextOut];
    s->nextOut = (s->nextOut + 1) % BUFF_SIZE;
    sem_post(mutex);
    printf("Consumer (PID %d) Consuming %c ...\n", getpid(), *item);
    sem_post(empty_slots);
}

void Producer() {
    int i;
    for (i = 0; i < 10; i++) {
        sleep(rand() % 3);
        Put((char)('A' + i % 26));
    }
}

void ProcessItems() {
    char item;
    for (int i = 0; i < 10; i++) {
        sleep(rand() % 3);
        Get(&item);
        Process(&item);
        Put(item);
    }
}

int main() {
    mutex = sem_open(sem_name1, O_CREAT, 0644, 1);
    full_slots = sem_open(sem_name3, O_CREAT, 0644, 0);
    empty_slots = sem_open(sem_name2, O_CREAT, 0644, 10);

    key_t key;
    key = 1234;

    int shmid;
    if ((shmid = shmget(key, sizeof(shared_data), IPC_CREAT | 0666)) < 0) {
        perror("Shmget");
        exit(1);
    }

    if ((shm = (shared_data *)shmat(shmid, NULL, 0)) == (shared_data *)-1) {
        perror("Shmat");
        exit(1);
    }

    s = shm;
    s->nextIn = 0;

    // new process created here
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork");
        exit(1);
    } else if (pid == 0) {
        // Child process - basically an Item processing
        ProcessItems();
        exit(0);
    } else {
        // Producer Parent process 
        Producer();
        wait(NULL); // sync type of wait
    }

    shmdt((void *)shm);

    return 0;
}
