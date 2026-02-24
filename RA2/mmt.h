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

    float minXj[matSize], maxXj[matSize];
    for (int i = 0; i < matSize; i++){
        minXj[i] = X[0][i];
        maxXj[i] = X[0][i];
    }
    for (int i = 0; i < matSize; i++) {       
        for (int j = 0; j < matSize; j++) {   
            // printf("%f\n", X[i][j]);
            if(minXj[j] > X[i][j]){
                minXj[j] = X[i][j];
            }
            if(maxXj[j] < X[i][j]){
                maxXj[j] = X[i][j];
            }
        }
    }

    for (int i = 0; i < matSize; i++) {
        int k = 0;
        for (int j = startCol; j < endCol; j++) {
            X[i][j] = (X[i][j] - minXj[k]) / (maxXj[k] - minXj[k]);
            k++;
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