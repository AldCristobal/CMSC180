#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

float **arrInput(int *rows) {
    FILE *file = fopen("./RA1/input.txt", "r");
    float **array = NULL;
    char line[1024];
    *rows = 0;

    fgets(line, sizeof(line), file);
    *rows = atoi(line);

    array = malloc(*rows * sizeof(float *));

    for (int i = 0; i < *rows; i++){
        array[i] = malloc(*rows * sizeof(float));
    }

    for (int i = 0; i < *rows; i++) {
        fgets(line, sizeof(line), file);

        char *token = strtok(line, ",\n");
        for (int j = 0; j < *rows && token != NULL; j++) {
            array[i][j] = atof(token);
            token = strtok(NULL, ",\n");
        }
    }

    fclose(file);
    return array;
}

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

void arrPrint(float** X, int arrSize){
    for (int i = 0; i < arrSize; i++) {       
        for (int j = 0; j < arrSize; j++) {   
            printf("%f ", X[i][j]);
        }
        printf("\n"); 
    }
    return;
}

int main (int argc, char *argv[0]){
    //init val for randomizer
    srand(time(NULL));
    
    // //get arrSize
    // int arrSize = 0;
    // sscanf(argv[1], "%i", &arrSize);
    // // printf("The size is %i\n",arrSize);
    
    // //build X and T matrices with arrSize * arrSize size
    // float **X, **T;
    // X = malloc(arrSize * sizeof(float *));
    // // T = malloc(arrSize * sizeof(int *));     
    // for (int i = 0; i < arrSize; i++){
    //     X[i] = malloc(arrSize * sizeof(float));
    //     // T[i] = malloc(arrSize * sizeof(int));
    // }

    float **X;
    int arrSize = 0;
    X = arrInput(&arrSize);
    // printf("%i\n",arrSize);

    // arrPrint(X, arrSize);
    // arrPrint(T, arrSize);

    // //populate here
    // int maxVal = 0;
    // sscanf(argv[2], "%i", &maxVal);
    // arrPopulate(X, arrSize, maxVal);

    // arrPrint(X, arrSize);
    // arrPrint(T, arrSize);

    //init and get starting time
    struct timespec time_before, time_after;
    long long nanoseconds;

    clock_gettime(CLOCK_MONOTONIC, &time_before);

    //do mmt
    mmt(X, arrSize);

    // arrPrint(X, arrSize);
    // arrPrint(T, arrSize);
    
    //get end time
    clock_gettime(CLOCK_MONOTONIC, &time_after);

    //compute the difference
    nanoseconds = (time_after.tv_sec - time_before.tv_sec) * 1e9 + (time_after.tv_nsec - time_before.tv_nsec);
    printf("Time elapsed: %lld nanoseconds\n", nanoseconds);

    // printf("Done in %is",&diff);

    //dealloc
    for (int i = 0; i < arrSize; i++){
        free(X[i]);
        // free(T[i]);
    }
    free(X);
    // free(T);

    return 0;
}