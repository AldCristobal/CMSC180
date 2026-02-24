#include <stdio.h>
#include <stdlib.h>

void mmt(void *args[]){
    float **X = (float **) args[0];
    int matSize = *(int *) args[1];
    int colsPerThread = *(int *) args[2];
    float *minXj = (float *) args[3];
    float *maxXj = (float *) args[4];
    for (int i = 0; i < matSize; i++) {       
        for (int j = 0; j < colsPerThread; j++) {             
            X[i][j] = (X[i][j] - minXj[j])/(maxXj[j]-minXj[j]);
            // printf("%f\n",X[i][j]);
        }
    }
    return;
}