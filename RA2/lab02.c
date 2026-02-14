#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#include "mmt.h"
#include "arrayOps.h"

int main (int argc, char *argv[]){

    srand(time(NULL));  

    //get arrSize
    int arrSize = 0;
    sscanf(argv[1], "%i", &arrSize);
    // printf("The size is %i\n",arrSize);
    
    //build X and T matrices with arrSize * arrSize size
    float **X;
    X = malloc(arrSize * sizeof(float *));
    for (int i = 0; i < arrSize; i++){
        X[i] = malloc(arrSize * sizeof(float));
    }

    // arrPrint(X, arrSize);

    int maxVal = 0;
    sscanf(argv[2], "%i", &maxVal);
    arrPopulate(X, arrSize, maxVal);

    printf("Initial Matrix: \n");
    arrPrint(X, arrSize);

    //init and get starting time
    struct timespec time_before, time_after;
    long long nanoseconds;
    clock_gettime(CLOCK_MONOTONIC, &time_before);

    mmt(X, arrSize);

    clock_gettime(CLOCK_MONOTONIC, &time_after);

    printf("Resulting Matrix: \n");
    arrPrint(X, arrSize);

    nanoseconds = (time_after.tv_sec - time_before.tv_sec) * 1000000000LL + (time_after.tv_nsec - time_before.tv_nsec);
    printf("Time taken: %lld nanoseconds\n", nanoseconds);

    for (int i = 0; i < arrSize; i++){
        free(X[i]);
    }
    free(X);

    return 0;
}