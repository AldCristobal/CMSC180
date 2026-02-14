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