#include <stdio.h>
#include <stdlib.h>

void matPopulate(float** X, int matSize, int maxVal){
    for (int i = 0; i <matSize; i++) {       
        for (int j = 0; j < matSize; j++) {  
            if (maxVal > 0){
                X[i][j] = rand() % maxVal;
            }else{
                X[i][j] = rand();
            }
        }
    }
    return;
}

void matPrint(float** X, int matSize){
    for (int i = 0; i < matSize; i++) {       
        for (int j = 0; j < matSize; j++) {   
            printf("%f ", X[i][j]);
        }
        printf("\n"); 
    }
    return;
}

void getMinMax(float** X, int matSize, float* minXj, float* maxXj){
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
    // for (int i = 0; i < matSize; i++){
    //     printf("%i min %f, max %f\n",i,minXj[i],maxXj[i]);
    // }
    return;
}

void matDivide(float** X, int matSize, int threadCount, float ***subMats){
    int rowsPerThread = matSize/threadCount;
    for (int t = 0; t < threadCount; t++){
        for (int i = 0; i < matSize; i++) {       
            for (int j = 0; j < matSize; j++) {   
                if (i >= t*rowsPerThread && i < (t+1)*rowsPerThread){
                    subMats[t][i][j] = X[i][j];
                }else{
                    subMats[t][i][j] = -1;
                }
            }
        }
    }
}

void subMatPrint(float*** subMats, int matSize, int threadCount){
    for (int t = 0; t < threadCount; t++){
        printf("Submatrix %i:\n", t);
        for (int i = 0; i < matSize; i++) {       
            for (int j = 0; j < matSize; j++) {   
                printf("%f ", subMats[t][i][j]);
            }
            printf("\n"); 
        }
    }

}