#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#include "mmt.h"
#include "matOps.h"

int main (int argc, char *argv[]){

    srand(time(NULL));  

    //get matSize
    int matSize = 0;
    sscanf(argv[1], "%i", &matSize);
    // printf("The size is %i\n",matSize);
    
    //build X and T matrices with matSize * matSize size
    float **X;
    X = malloc(matSize * sizeof(float *));
    for (int i = 0; i < matSize; i++){
        X[i] = malloc(matSize * sizeof(float));
    }

    // matPrint(X, matSize);
    int maxVal = 0;
    sscanf(argv[2], "%i", &maxVal);
    matPopulate(X, matSize, maxVal);

    printf("Initial Matrix: \n");
    matPrint(X, matSize);

    //init and get starting time
    struct timespec time_before, time_after;
    long long nanoseconds;
    clock_gettime(CLOCK_MONOTONIC, &time_before);

    mmt(X, matSize);

    clock_gettime(CLOCK_MONOTONIC, &time_after);

    printf("Resulting Matrix: \n");
    matPrint(X, matSize);

    nanoseconds = (time_after.tv_sec - time_before.tv_sec) * 1000000000LL + (time_after.tv_nsec - time_before.tv_nsec);
    printf("Time taken: %lld nanoseconds\n", nanoseconds);

    for (int i = 0; i < matSize; i++){
        free(X[i]);
    }
    free(X);

    return 0;
}