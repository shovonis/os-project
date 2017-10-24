//
// Created by rifatul on 10/24/17.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void thinking(int threadIndex);

void pickUpChopsticks(int threadIndex);

void eating(int threadIndex);

void putDownChopsticks(int threadIndex);

void *runPhilosopher(void *nthread);

void createPhilosophers(pthread_t philosopherThread[]);

void initMutex();

void joinThread(pthread_t philosopherThread[]);

pthread_mutex_t mutex;
pthread_cond_t conditional;
int nthreads;
int index = 0;

int main(int argc, char *argv[]) {
    nthreads = atoi(argv[1]);
    pthread_t philosopherThread[nthreads];

    initMutex();
    createPhilosophers(philosopherThread);
    joinThread(philosopherThread);

    return 0;
}

void initMutex() {
    int i;
    for (i = 0; i < nthreads; ++i) {
        pthread_mutex_init(&mutex, NULL);
    }
}

void joinThread(pthread_t philosopherThread[]) {
    int j;
    for (j = 0; j < nthreads; ++j) {
        if (pthread_join(philosopherThread[j], NULL)) {
            fprintf(stderr, "Error in creating thread\n");
        }
    }
    printf("%d threads have been joined successfully now \n", nthreads);
}

void createPhilosophers(pthread_t philosopherThread[]) {
    int i;
    for (i = 0; i < nthreads; ++i) {
        if (pthread_create(&philosopherThread[i], NULL, runPhilosopher, (void *) i)) {
            fprintf(stderr, "Error in creating thread\n");
        }
    }
}

void *runPhilosopher(void *nthread) {
    int threadIndex = (int) nthread;

    thinking(threadIndex);
    pickUpChopsticks(threadIndex);
    eating(threadIndex);

    putDownChopsticks(threadIndex);
    printf("I am philosopher %d and I finished Eating.\n", threadIndex);

}

void thinking(int threadIndex) {
    srandom((unsigned int) time(0));
    long time = random() % (500);
    usleep((__useconds_t) time);
}

void eating(int threadIndex) {
    printf("I am philosopher %d and I am eating now...\n", threadIndex);
    srandom((unsigned int) time(0));
    long time = random() % (500);
    usleep((__useconds_t) time);
}

void pickUpChopsticks(int threadIndex) {
    pthread_mutex_lock(&mutex);
    while (threadIndex != index) {
        pthread_cond_wait(&conditional, &mutex);
    }
}

void putDownChopsticks(int threadIndex) {
    index++;
    pthread_mutex_unlock(&mutex);
    pthread_cond_broadcast(&conditional);
}
