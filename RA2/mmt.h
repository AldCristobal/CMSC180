#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float **X;
    int matSize;
    int startCol;
    int endCol;
    int startRow;
    int endRow;
    float *minXj;
    float *maxXj;
    int doPrint;
} mmtArgs;

void* mmt(void *arg) {
    mmtArgs *args = (mmtArgs*) arg;

    float **X = args->X;
    int matSize = args->matSize;
    // int startCol = args->startCol;
    // int endCol = args->endCol;
    int startRow = args->startRow;
    int endRow = args->endRow;

    float *minXj = args->minXj;
    float *maxXj = args->maxXj;

    // float *minXj = malloc((endCol-startCol) * sizeof(float));
    // float *maxXj = malloc((endCol-startCol) * sizeof(float));

    // for (int j = 0; j < endCol-startCol; j++) {
    //     minXj[j] = X[0][startCol + j];
    //     maxXj[j] = X[0][startCol + j];
    // }

    // for (int i = 0; i < matSize; i++) {       
    //     for (int j = 0; j < endCol-startCol; j++) {   
    //         if(minXj[j] > X[i][startCol + j]){
    //             minXj[j] = X[i][startCol + j];
    //         }
    //         if(maxXj[j] < X[i][startCol + j]){
    //             maxXj[j] = X[i][startCol + j];
    //         }
    //     }
    // }

    // for (int i = 0; i < matSize; i++) {
    //     for (int j = 0; j < (endCol-startCol); j++) {
    //         X[i][startCol + j] = (X[i][startCol + j] - minXj[j]) / (maxXj[j] - minXj[j]);
    //     }
    // }

    for (int i = 0; i < endRow-startRow; i++) {
        for (int j = 0; j < matSize; j++) {
            X[startRow + i][j] = (X[startRow + i][j] - minXj[j]) / (maxXj[j] - minXj[j]);
        }
    }

    // if (args->doPrint) {
    //     printf("Thread handling columns %i to %i finished MMT. Submatrix:\n", startCol, endCol-1);
    //     for (int i = 0; i < matSize; i++) {
    //         for (int j = startCol; j < endCol; j++) {
    //             printf("%f ", X[i][j]);
    //         }
    //         printf("\n");
    //     }
    // }

    if (args->doPrint) {
        printf("Thread handling rows %i to %i finished MMT. Submatrix:\n", startRow, endRow-1);
        for (int i = startRow; i < endRow; i++) {
            for (int j = 0; j < matSize; j++) {
                printf("%f ", X[i][j]);
            }
            printf("\n");
        }
    }

    // free(minXj);
    // free(maxXj);

    return NULL;
}