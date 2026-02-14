#include <stdio.h>
#include <stdlib.h>

void mmt(float** X, int matSize, int colsPerThread, float* minXj, float* maxXj){
    for (int i = 0; i < matSize; i++) {       
        for (int j = 0; j < colsPerThread; j++) {             
            X[i][j] = (X[i][j] - minXj[j])/(maxXj[j]-minXj[j]);
            // printf("%f\n",X[i][j]);
        }
    }
    return;
}