#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float **X;
    int matSize;
    int startCol;
    int endCol;
    float *minXj;
    float *maxXj;
    int doPrint;
} mmtArgs;

void* mmt(void *arg) {
    mmtArgs *args = (mmtArgs*) arg;

    float **X = args->X;
    int matSize = args->matSize;
    int startCol = args->startCol;
    int endCol = args->endCol;
    float *minXj = args->minXj;
    float *maxXj = args->maxXj;

    for (int i = 0; i < matSize; i++) {
        for (int j = startCol; j < endCol; j++) {
            X[i][j] = (X[i][j] - minXj[j]) / (maxXj[j] - minXj[j]);
        }
    }

    if (args->doPrint) {
        printf("Thread handling columns %i to %i finished MMT. Submatrix:\n", startCol, endCol-1);
        for (int i = 0; i < matSize; i++) {
            for (int j = startCol; j < endCol; j++) {
                printf("%f ", X[i][j]);
            }
            printf("\n");
        }
    }

    return NULL;
}