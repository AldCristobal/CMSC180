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
    sscanf(argv[3], "%i", &matSize);
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

    int doPrint = 0;
    sscanf(argv[1], "%i", &doPrint);

    if (doPrint){
        printf("Initial Matrix: \n");
        matPrint(X, matSize);
    }

    int threadCount = 0;
    sscanf(argv[4], "%i", &threadCount);
    printf("Thread count: %i\n", threadCount);

    float minXj[matSize], maxXj[matSize];
    getMinMax(X, matSize, minXj, maxXj);
    // printf("Min and Max\n");

    float ***subMats;
    int colsPerThread = matSize/threadCount;
    int extraCols = matSize % threadCount;
    subMats = (float ***) malloc(threadCount * sizeof(float **));
    for (int i = 0; i < threadCount; i++){
        subMats[i] =(float **) malloc(matSize * sizeof(float *));
        for (int j = 0; j < matSize; j++){
            subMats[i][j] = (float*) malloc((colsPerThread + (i < extraCols ? 1 : 0)) * sizeof(float));
        }
    }
    printf("Column/s per submatrix: %i, distribute %i extra columns\n", colsPerThread, extraCols);
    
    matDivide(X, matSize, threadCount, colsPerThread, extraCols, subMats);
    // printf("Matrix divided into submatrices\n");

    if (doPrint){
        printf("Submatrices: \n");
        subMatPrint(subMats, matSize, colsPerThread, extraCols, threadCount);
    }

    //init and get starting time
    struct timespec time_before, time_after;
    long long nanoseconds;

    clock_gettime(CLOCK_MONOTONIC, &time_before);

    mmt(X, matSize, minXj, maxXj);

    clock_gettime(CLOCK_MONOTONIC, &time_after);

    if (doPrint){
        printf("Resulting Matrix: \n");
        matPrint(X, matSize);
    }

    nanoseconds = (time_after.tv_sec - time_before.tv_sec) * 1000000000LL + (time_after.tv_nsec - time_before.tv_nsec);
    printf("Time taken: %lld nanoseconds\n", nanoseconds);

    for (int t = 0; t < threadCount; t++){
        for (int i = 0; i < matSize; i++){
            free(subMats[t][i]);
        }
        free(subMats[t]);
    }
    free(subMats);
    
    for (int i = 0; i < matSize; i++){
        free(X[i]);
    }
    free(X);

    return 0;
}