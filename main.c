#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void thinking(int threadIndex);

void pickUpChopsticks(int threadIndex);

void eating(int threadIndex);

void putDownChopsticks(int threadIndex);

void *runPhilosopher(void *nthread);

void createPhilosophers();

pthread_mutex_t *chopstick;
//pthread_mutex_t chopstick[5];

int nthreads;

int main(int argc, char *argv[]) {
    nthreads = 5;
    printf("Number of threads are %d\n", nthreads);

    chopstick = malloc(nthreads * sizeof(*chopstick));
//    printf("The number of %d chopstick.\n", (int) (sizeof(chopstick) / sizeof(pthread_mutex_t)));



    createPhilosophers();

    return 0;
}

void createPhilosophers() {
    pthread_t philosopherThread[nthreads];
    int i, j;
    for (i = 0; i < nthreads; ++i) {
        if (pthread_create(&philosopherThread[i], NULL, runPhilosopher, &i)) {
            fprintf(stderr, "Error in creating thread\n");
        }
    }

    for (j = 0; j < nthreads; ++j) {
        if (pthread_join(philosopherThread[j], NULL)) {
            fprintf(stderr, "Error in creating thread\n");
        }
    }

    printf("%d threads have been joined successfully now \n", nthreads);
}


void *runPhilosopher(void *nthread) {
    int threadIndex = *(int *) nthread;
//    printf("Thread Index is: %d \n", threadIndex);
    thinking(threadIndex);
    pickUpChopsticks(threadIndex);
    eating(threadIndex);
    putDownChopsticks(threadIndex);
    printf("I am philosopher %d and I finished Eating.\n", threadIndex);

}


void thinking(int threadIndex) {
    printf("I am philosopher %d and I am thinking now...\n", threadIndex);
    usleep(1000);
}

void eating(int threadIndex) {
    printf("I am philosopher %d and I am eating now...\n", threadIndex);
    usleep(5000);
}


void pickUpChopsticks(int threadIndex) {
    pthread_mutex_lock(&chopstick[threadIndex % nthreads]);
    pthread_mutex_lock(&chopstick[(threadIndex + 1) % nthreads]);
}

void putDownChopsticks(int threadIndex) {
    pthread_mutex_unlock(&chopstick[threadIndex % nthreads]);
    pthread_mutex_unlock(&chopstick[(threadIndex + 1) % nthreads]);
}
