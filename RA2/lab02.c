#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include "mmt.h"
#include "arrayOps.h"

int main (int argc, char *argv[]){

    srand(time(NULL));  

    //get arrSize
    int arrSize = 0;
    sscanf(argv[1], "%i", &arrSize);
    printf("The size is %i\n",arrSize);
    
    //build X and T matrices with arrSize * arrSize size
    float **X;
    X = malloc(arrSize * sizeof(float *));
    for (int i = 0; i < arrSize; i++){
        X[i] = malloc(arrSize * sizeof(float));
    }
    printf("%i\n",arrSize);

    arrPrint(X, arrSize);

    int maxVal = 0;
    sscanf(argv[2], "%i", &maxVal);
    arrPopulate(X, arrSize, maxVal);

    mmt(X, arrSize);

    arrPrint(X, arrSize);
    return 0;
}