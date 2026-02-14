#include <stdio.h>
#include <stdlib.h>

void mmt(float** X, int arrSize){
    float minXj[arrSize], maxXj[arrSize];
    for (int i = 0; i < arrSize; i++){
        minXj[i] = X[0][i];
        maxXj[i] = X[0][i];
    }
    for (int i = 0; i < arrSize; i++) {       
        for (int j = 0; j < arrSize; j++) {   
            // printf("%f\n", X[i][j]);
            if(minXj[j] > X[i][j]){
                minXj[j] = X[i][j];
            }
            if(maxXj[j] < X[i][j]){
                maxXj[j] = X[i][j];
            }
        }
    }
    // for (int i = 0; i < arrSize; i++){
    //     printf("%i min %f, max %f\n",i,minXj[i],maxXj[i]);
    // }
    for (int i = 0; i < arrSize; i++) {       
        for (int j = 0; j < arrSize; j++) {             
            X[i][j] = (X[i][j] - minXj[j])/(maxXj[j]-minXj[j]);
            // printf("%f\n",X[i][j]);
        }
    }
    return;
}