#include <stdio.h>
#include <stdlib.h>

struct{
    float **X;
    int matSize;
    int colsPerThread;
    float *minXj;
    float *maxXj;
} typedef mmtArgs;

void* mmt(void *arg) {
    mmtArgs *args = (mmtArgs*) arg;

    float **X = args->X;
    int matSize = args->matSize;
    int startCol = args->startCol;
    int endCol = args->endCol;
    float *minXj = args->minXj;
    float *maxXj = args->maxXj;

    for (int j = startCol; j < endCol; j++) {
        float minVal = minXj[j];
        float range = maxXj[j] - minVal;

        for (int i = 0; i < matSize; i++) {
            X[i][j] = (X[i][j] - minVal) / range;
        }
    }

    return NULL;
}