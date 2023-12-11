#include <stdio.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

//Lab5_3_1Consumer


int my_rand() {
    return rand();
}


void my_exit(int status) {
    exit(status);
}

#define BUFF_SIZE 20

char sem_name1[] = "mutex";
char sem_name2[] = "empty_slots";
char sem_name3[] = "full_slots";
sem_t *empty_slots;
sem_t *full_slots;
sem_t *mutex;

typedef struct {
    char buffer[BUFF_SIZE];
    int nextIn;
    int nextOut;
} shared_data;

shared_data *shm, *s;

void Get(char item) {
    sem_wait(full_slots);
    sem_wait(mutex);
    item = s->buffer[s->nextOut];
    s->nextOut = (s->nextOut + 1) % BUFF_SIZE;
    sem_post(mutex);
    printf("Consumer (PID %d) Consuming %c ...\n", getpid(), item); // Pid addition here
    sem_post(empty_slots);
}

void Consumer() {
    int i;
    char item;
    for (i = 0; i < 10; i++) {
        sleep(my_rand() % 9);
        Get(item);
    }
}

int main() {
    // Open existing semaphores from consumer PID
    mutex = sem_open(sem_name1, O_CREAT, 0644, 1);
    full_slots = sem_open(sem_name3, O_CREAT, 0644, 0);
    empty_slots = sem_open(sem_name2, O_CREAT, 0644, 10);

    // Create a key for the segment
    key_t key;
    key = 1234; 

    // locate the segment
    int shmid;
    if ((shmid = shmget(key, sizeof(shared_data), 0666)) < 0) {
        perror("Shmget");
        my_exit(1); // Use the wrapper function for exit()
    }

    // attach to the segment
    if ((shm = (shared_data *)shmat(shmid, NULL, 0)) == (shared_data *)-1) {
        perror("Shmat");
        my_exit(1); 
    }

    s = shm;
    s->nextOut = 0;
    Consumer();

    my_exit(0); 

    return 0;
}
