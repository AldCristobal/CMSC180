#include <stdio.h>
#include <stdlib.h>

void arrPopulate(float** X, int arrSize, int maxVal){
    for (int i = 0; i < arrSize; i++) {       
        for (int j = 0; j < arrSize; j++) {  
            if (maxVal > 0){
                X[i][j] = rand() % maxVal;
            }else{
                X[i][j] = rand();
            }
        }
    }
    return;
}

void arrPrint(float** X, int arrSize){
    for (int i = 0; i < arrSize; i++) {       
        for (int j = 0; j < arrSize; j++) {   
            printf("%f ", X[i][j]);
        }
        printf("\n"); 
    }
    return;
}