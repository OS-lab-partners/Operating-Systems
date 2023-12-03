#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_STUDENTS 10
#define CHAIRS 3

sem_t ta_sem, student_sem, chair_sem;
int waiting_students = 0;
int terminate = 0;

void *student_function(void *arg) {
    int student_id = *((int *)arg);

    while (!terminate) {
        printf("Student %d (%ld) is programming.\n", student_id, pthread_self());
        sleep(rand() % 5 + 1);

        sem_wait(&chair_sem);

        if (waiting_students < CHAIRS) {
            // chair available
            waiting_students++;
            sem_post(&chair_sem);
            sem_post(&student_sem);

            sem_wait(&ta_sem);
            printf("Student %d (%ld) is getting help from TA.\n", student_id, pthread_self());
            sem_post(&ta_sem);

            sleep(rand() % 5 + 1);

            sem_wait(&ta_sem);
            printf("Student %d (%ld) got help and leaving.\n", student_id, pthread_self());
            sem_post(&ta_sem);

            sem_wait(&chair_sem);
            waiting_students--;
            sem_post(&chair_sem);
        } else {
            // no chairs available, go back to programming
            sem_post(&chair_sem);
            printf("Student %d (%ld) found no chairs, going back to programming.\n", student_id, pthread_self());
        }
    }

    printf("Student %d (%ld) is exiting.\n", student_id, pthread_self());
    pthread_exit(NULL);
}

void *ta_function(void *arg) {
    while (!terminate) {
        sem_wait(&student_sem);

        sem_wait(&ta_sem);
        printf("TA (%ld) is helping a student.\n", pthread_self());
        sem_post(&ta_sem);

        sleep(rand() % 5 + 1);

        sem_wait(&ta_sem);
        printf("TA (%ld) finished helping a student.\n", pthread_self());
        sem_post(&ta_sem);
    }

    printf("TA (%ld) is exiting.\n", pthread_self());
    pthread_exit(NULL);
}

int main() {
    pthread_t students[NUM_STUDENTS], ta;
    int student_ids[NUM_STUDENTS];

    sem_init(&ta_sem, 0, 1);
    sem_init(&student_sem, 0, 0);
    sem_init(&chair_sem, 0, 1);

    // create TA thread
    pthread_create(&ta, NULL, ta_function, NULL);

    // create 10 student threads
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        student_ids[i] = i + 1;
        pthread_create(&students[i], NULL, student_function, (void *)&student_ids[i]);
    }

    // sleep for a while to let the threads run
    sleep(20);

    // signal threads to exit
    terminate = 1;

    // join student threads
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        pthread_join(students[i], NULL);
    }

    // join TA thread
    pthread_join(ta, NULL);

    sem_destroy(&ta_sem);
    sem_destroy(&student_sem);
    sem_destroy(&chair_sem);

    return 0;
}
