#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 2048
#define FactorIntToDouble 1.1;
double firstMatrix [N] [N] = {0.0};
double secondMatrix [N] [N] = {0.0};
double matrixMultiResult [N] [N] = {0.0};

void matrixMulti(){
    for(int row = 0 ; row < N ; row++){
        for(int col = 0; col < N ; col++){
            double resultValue = 0;
            for(int transNumber = 0 ; transNumber < N ; transNumber++) {
                resultValue += firstMatrix [row] [transNumber] * secondMatrix [transNumber] [col];
            }
            matrixMultiResult [row] [col] = resultValue;
        }
    }
}

void matrixInit(){
    for(int row = 0 ; row < N ; row++ ) {
        for(int col = 0 ; col < N ;col++){
            srand(row+col);
            firstMatrix [row] [col] = ( rand() % 10 ) * FactorIntToDouble;
            secondMatrix [row] [col] = ( rand() % 10 ) * FactorIntToDouble;
        }
    }
}


int main(){
    matrixInit();
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;

    gettimeofday(&tv1, &tz);
    matrixMulti();
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("elapsed time = %f seconds.\n", elapsed);
    return 0;
}

