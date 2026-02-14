#include <stdio.h>
#include <stdlib.h>

void matPopulate(float** X, int matSize, int maxVal){
    for (int i = 0; i <matSize; i++) {       
        for (int j = 0; j < matSize; j++) {  
            if (maxVal > 0){
                X[i][j] = (rand() % maxVal) +1;
            }else{
                X[i][j] = rand() + 1;
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

void matDivide(float** X, float* minXj, float* maxXj, int matSize, int threadCount, int colsPerThread,  int extraCols, float ***subMats, float **minXjSub, float **maxXjSub){
    int t = 0;
    int j = 0;
    for (t; t < threadCount; t++){
        for (int k = 0; k < colsPerThread; k++) {       
            for (int i = 0; i < matSize; i++) {
                // printf("Assigning subMats[%i][%i][%i] = X[%i][%i]\n", t, i, k, i, j);
                subMats[t][i][k] = X[i][j];
                minXjSub[t][k] = minXj[j];
                maxXjSub[t][k] = maxXj[j];
            }
            j++;
        }
        if (extraCols > 0){
            extraCols--;
            for (int i = 0; i < matSize; i++) {
                // printf("Assigning subMats[%i][%i][%i] = X[%i][%i]\n", t, i, colsPerThread, i, j);
                subMats[t][i][colsPerThread] = X[i][j];
                minXjSub[t][colsPerThread] = minXj[j];
                maxXjSub[t][colsPerThread] = maxXj[j];
            }
            j++;
        }
    }

}

void subMatPrint(float*** subMats, int matSize, int colsPerThread,  int extraCols, int threadCount, float **minXjSub, float **maxXjSub){
    for (int t = 0; t < threadCount; t++){
        printf("Submatrix %i:\n", t+1);
        for (int i = 0; i < matSize; i++) {       
            for (int j = 0; j < colsPerThread + (t < extraCols ? 1 : 0); j++) {   
                printf("%f ", subMats[t][i][j]);
            }
            printf("\n"); 
        }
        printf("Min and Max for submatrix %i:\n", t+1);
        for (int j = 0; j < colsPerThread + (t < extraCols ? 1 : 0); j++) {
            printf("Column %i: min = %f, max = %f\n", j, minXjSub[t][j], maxXjSub[t][j]);
        }
    }

}