#include <stdio.h>
#include <stdlib.h>

struct{
    float **X;
    int matSize;
    int colsPerThread;
    float *minXj;
    float *maxXj;
} typedef mmtArgs;

void* mmt(mmtArgs *args){
    float **X = args->X;
    int matSize = args->matSize;
    int colsPerThread = args->colsPerThread;
    float *minXj = args->minXj;
    float *maxXj = args->maxXj;

    for (int i = 0; i < matSize; i++) {       
        for (int j = 0; j < colsPerThread; j++) {             
            X[i][j] = (X[i][j] - minXj[j])/(maxXj[j]-minXj[j]);
            // printf("%f\n",X[i][j]);
        }
    }
}