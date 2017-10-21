#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *printMessages(void *value) {
    int *val = (int *) value;
    printf("Hello, This is philosopher : %d \n", *val);
}

void creatPhilosophers(int nthreads);

int main(int argc, char *argv[]) {
    int nthreads = 0;

    if (argv[1] > 0) {
        nthreads = atoi(argv[1]);
    } else {
        fprintf(stderr, "No thread created, Invalid arg");
        return 1;
    }

    creatPhilosophers(nthreads);

    return 0;
}

void creatPhilosophers(int nthreads) {
    pthread_t philosopherThread[nthreads];

    for (int i = 0; i < nthreads; i++) {
        if (pthread_create(&philosopherThread[i], NULL, printMessages, &i)) {
            fprintf(stderr, "Error in creating thread");
        }
    }

    for (int i = 0; i < nthreads; i++) {
        if (pthread_join(philosopherThread[i], NULL)) {
            fprintf(stderr, "Error in creating thread");
        }
    }

    printf("%d threads have been joined successfully now \n", nthreads);
}

