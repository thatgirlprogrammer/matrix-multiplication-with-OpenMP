#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define FactorIntToDouble 1.1;
#define N 2048
int mat1[N][N];
int mat2[N][N];
int res[N][N];

void fill_matrix(){
        int row, col;
        for (row = 0; row < N; row++){
                for (col = 0; col < N; col++){
                        res[row][col] = 0;
                        mat1[row][col] = ( rand() % 10 ) * FactorIntToDouble;
                        mat2[row][col] = ( rand() % 10 ) * FactorIntToDouble;
                }
        }
}

int main(int argc, char *argv[]){
        int block_size = 256;
        int block_row, block_col, k;
        memset(res, 0, sizeof(res[0][0]) * N * N);

        struct timeval tv1, tv2;
        struct timezone tz;
        double elapsed;
        gettimeofday(&tv1, &tz);
        fill_matrix();

        // Do the calculations
        for (int row = 0; row < N; row += block_size){
                for (int col = 0; col < N; col += block_size){
                        #pragma omp parallel for collapse(2)
                        for (block_row = 0; block_row < block_size; ++block_row){
                               for (block_col = 0; block_col < block_size; ++block_col){
                                        for (k = 0; k < N; k++){
                                                #pragma omp critical
                                                res[row + block_row][col + block_col] += mat1[row + block_row][k] * >
                                        };
                                }
                        }
                }
        }

        /*for (int row = 0; row < N; row++){
                for (int col = 0; col < N; col++){
                        printf("%d\t",res[row][col]);
                }
                printf("\n");
        }*/

        gettimeofday(&tv2, &tz);
        elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
        printf("elapsed time = %f seconds.\n", elapsed);
        return 0;
}
